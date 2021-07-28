"""
Utility to autogenerate Zephyr DT pinctrl files for all STM32 microcontrollers.

Usage::

    python3 genpinctrl.py -p /path/to/stm32-open-pin-data-repository
                          [-o /path/to/output_dir]

Copyright (c) 2020 Teslabs Engineering S.L.

SPDX-License-Identifier: Apache-2.0
"""

import argparse
from collections import OrderedDict
import logging
from pathlib import Path
import re
import shutil
from subprocess import check_output
import xml.etree.ElementTree as ET

from jinja2 import Environment, FileSystemLoader
import yaml


logger = logging.getLogger(__name__)


SCRIPT_DIR = Path(__file__).absolute().parent
"""Script directory."""

REPO_ROOT = SCRIPT_DIR / ".." / ".."
"""Repository root (used for defaults)."""

CONFIG_FILE = SCRIPT_DIR / "stm32-pinctrl-config.yaml"
"""Configuration file."""

CONFIG_F1_FILE = SCRIPT_DIR / "stm32f1-pinctrl-config.yaml"
"""Configuration file for F1 series."""

PINCTRL_TEMPLATE = "pinctrl-template.j2"
"""pinctrl template file."""

README_TEMPLATE = "readme-template.j2"
"""Readme template file."""

NS = "{http://dummy.com}"
"""MCU XML namespace."""

PINCTRL_ADDRESSES = {
    "stm32f0": 0x48000000,
    "stm32f1": 0x40010800,
    "stm32f2": 0x40020000,
    "stm32f3": 0x48000000,
    "stm32f4": 0x40020000,
    "stm32f7": 0x40020000,
    "stm32g0": 0x50000000,
    "stm32g4": 0x48000000,
    "stm32h7": 0x58020000,
    "stm32l0": 0x50000000,
    "stm32l1": 0x40020000,
    "stm32l4": 0x48000000,
    "stm32l5": 0x42020000,
    "stm32mp1": 0x50002000,
    "stm32u5": 0x42020000,
    "stm32wb": 0x48000000,
    "stm32wl": 0x48000000,
}
"""pinctrl peripheral addresses for each family."""


def validate_config_entry(entry, family):
    """Validates pin configuration entry.

    Args:
        entry: Pin configuration entry.
        family: STM32 family, e.g. "STM32F1".

    Raises:
        ValueError: If entry is not valid.
    """

    if not entry.get("name"):
        raise ValueError("Missing entry name")

    if not entry.get("match"):
        raise ValueError(f"Missing entry match for {entry['name']}")

    if family == "STM32F1":
        if not entry.get("mode"):
            raise ValueError(f"Missing entry mode for {entry['name']}")
        if entry["mode"] not in ("analog", "input", "alternate"):
            raise ValueError(f"Invalid mode for {entry['name']}: {entry['mode']}")
    else:
        if entry.get("mode"):
            if entry["mode"] not in ("analog", "alternate"):
                raise ValueError(f"Invalid mode for {entry['name']}: {entry['mode']}")

    if entry.get("bias"):
        if entry["bias"] not in ("disable", "pull-up", "pull-down"):
            raise ValueError(f"Invalid bias for {entry['name']}: {entry['bias']}")

        if (
            family == "STM32F1"
            and entry["mode"] != "input"
            and entry["bias"] != "disable"
        ):
            raise ValueError(
                f"Bias can only be set for input mode on F1 (entry: {entry['name']})"
            )

    if entry.get("drive"):
        if entry["drive"] not in ("push-pull", "open-drain"):
            raise ValueError(f"Invalid drive for {entry['name']}: {entry['drive']}")

    if entry.get("slew-rate"):
        if family == "STM32F1":
            if entry["slew-rate"] not in (
                "max-speed-10mhz",
                "max-speed-2mhz",
                "max-speed-50mhz",
            ):
                raise ValueError(
                    f"Invalid slew rate for {entry['name']}: {entry['slew-rate']}"
                )
        else:
            if entry["slew-rate"] not in (
                "low-speed",
                "medium-speed",
                "high-speed",
                "very-high-speed",
            ):
                raise ValueError(
                    f"Invalid slew rate for {entry['name']}: {entry['slew-rate']}"
                )


def format_mode(mode, af):
    """Format mode for FT (non-F1 series).

    Args:
        mode: Operation mode (analog, alternate).
        af: Alternate function ("analog" or AF number).

    Returns:
        DT AF definition.
    """

    if mode == "analog":
        return "ANALOG"
    elif mode == "alternate":
        return f"AF{af:d}"

    raise ValueError(f"Unsupported mode: {mode}")


def format_mode_f1(mode):
    """Format mode for DT (F1 series).

    Args:
        mode: Mode (analog, input, alternate).

    Returns:
        DT mode definition.
    """

    if mode == "analog":
        return "ANALOG"
    elif mode == "input":
        return "GPIO_IN"
    elif mode == "alternate":
        return "ALTERNATE"

    raise ValueError(f"Unsupported mode: {mode}")


def format_remap(remap):
    """Format remap number for DT.

    Args:
        remap: Remap number (0..3).

    Returns:
        DT remap definition.
    """

    if remap is None or remap == 0:
        return "NO_REMAP"
    elif remap == 1:
        return "REMAP_1"
    elif remap == 2:
        return "REMAP_2"
    elif remap == 3:
        return "REMAP_FULL"

    raise ValueError(f"Unsupported remap: {remap}")


def get_gpio_ip_afs(data_path):
    """Obtain all GPIO IP alternate functions.

    Example output::

        {
            "STM32L4P_gpio_v1_0": {
                "PA2": {
                    "ADC1_IN2": "analog",
                    "EVENTOUT": 15,
                    "LPUART1_TX": 8,
                    ...
                },
                ...
            },
            "STM32F103x4_gpio_v1_0": {
                "PB3": {
                    "ADC1_IN2": "analog",
                    "EVENTOUT": [0],
                    "LPUART1_TX": [0, 1],
                    ...
                },
                ...
            },
            ...
        }

    Notes:
        F1 series AF number corresponds to remap numbers.

    Args:
        data_path: STM32 Open Pin Data repository path.

    Returns:
        Dictionary of alternate functions.
    """

    ip_path = data_path / "mcu" / "IP"
    if not ip_path.exists():
        raise FileNotFoundError(f"IP DB folder '{ip_path}' does not exist")

    results = dict()

    for gpio_file in ip_path.glob("GPIO-*_Modes.xml"):
        m = re.search(r"GPIO-(.*)_Modes.xml", gpio_file.name)
        gpio_ip = m.group(1)

        gpio_ip_entries = dict()
        results[gpio_ip] = gpio_ip_entries

        gpio_tree = ET.parse(gpio_file)
        gpio_root = gpio_tree.getroot()

        for pin in gpio_root.findall(NS + "GPIO_Pin"):
            pin_name = pin.get("Name")

            pin_entries = dict()
            gpio_ip_entries[pin_name] = pin_entries

            for signal in pin.findall(NS + "PinSignal"):
                signal_name = signal.get("Name")

                if "STM32F1" in gpio_ip:
                    remap_blocks = signal.findall(NS + "RemapBlock")
                    if remap_blocks is None:
                        logger.error(
                            f"Missing remaps for {signal_name} (ip: {gpio_ip})"
                        )
                        continue

                    for remap_block in remap_blocks:
                        name = remap_block.get("Name")
                        m = re.search(r"^[A-Z0-9]+_REMAP(\d+)", name)
                        if not m:
                            logger.error(
                                f"Unexpected remap format: {name} (ip: {gpio_ip})"
                            )
                            continue

                        remap_num = int(m.group(1))
                        if signal_name not in pin_entries:
                            pin_entries[signal_name] = list()
                        pin_entries[signal_name].append(remap_num)
                else:
                    param = signal.find(NS + "SpecificParameter")
                    if param is None:
                        logger.error(
                            f"Missing parameters for {signal_name} (ip: {gpio_ip})"
                        )
                        continue

                    value = param.find(NS + "PossibleValue")
                    if value is None:
                        logger.error(
                            f"Missing signal value for {signal_name} (ip: {gpio_ip})"
                        )
                        continue

                    m = re.search(r"^GPIO_AF(\d+)_[A-Z0-9]+", value.text)
                    if not m:
                        logger.error(
                            f"Unexpected AF format: {value.text} (ip: {gpio_ip})"
                        )
                        continue

                    af_n = int(m.group(1))
                    pin_entries[signal_name] = af_n

    return results


def get_mcu_signals(data_path, gpio_ip_afs):
    """Obtain all MCU signals.

    Example output::

        {
            "STM32WB": [
                {
                    "name": "STM32WB30CEUx"
                    "pins: [
                        {
                            "port": "a",
                            "number": 0,
                            "signals" : [
                                {
                                    "name": "ADC1_IN5",
                                    "af": None,
                                },
                                {
                                    "name": "UART1_TX",
                                    "af": 3,
                                },
                                ...
                            ]
                        },
                        ...
                    ]
                },
                ...
            ]
        }

    Args:
        data_path: STM32 Open Pin Data repository path.
        gpio_ip_afs: GPIO IP alternate functions.

    Returns:
        Dictionary with all MCU signals.
    """

    mcus_path = data_path / "mcu"
    if not mcus_path.exists():
        raise FileNotFoundError(f"MCU DB folder '{mcus_path}' does not exist")

    results = dict()

    for mcu_file in mcus_path.glob("STM32*.xml"):
        mcu_tree = ET.parse(mcu_file)
        mcu_root = mcu_tree.getroot()

        # obtain family, reference and GPIO IP
        family = mcu_root.get("Family").replace("+", "")
        ref = mcu_root.get("RefName")

        gpio_ip_version = None
        for ip in mcu_root.findall(NS + "IP"):
            if ip.get("Name") == "GPIO":
                gpio_ip_version = ip.get("Version")
                break

        if not gpio_ip_version:
            logger.error(f"GPIO IP version not specified (mcu: {mcu_file})")
            continue

        if gpio_ip_version not in gpio_ip_afs:
            logger.error(f"GPIO IP version {gpio_ip_version} not available")
            continue

        gpio_ip = gpio_ip_afs[gpio_ip_version]

        # create reference entry on its family
        if family not in results:
            family_entries = list()
            results[family] = family_entries
        else:
            family_entries = results[family]

        pin_entries = list()
        family_entries.append({"name": ref, "pins": pin_entries})

        # process all pins
        for pin in mcu_root.findall(NS + "Pin"):
            if pin.get("Type") != "I/O":
                continue

            # obtain pin port (A, B, ...) and number (0, 1, ...)
            pin_name = pin.get("Name")
            m = re.search(r"^P([A-Z])(\d+).*$", pin_name)
            if not m:
                continue

            pin_port = m.group(1).lower()
            pin_number = int(m.group(2))

            if pin_name not in gpio_ip:
                continue

            pin_afs = gpio_ip[pin_name]

            pin_signals = list()
            pin_entries.append(
                {
                    "port": pin_port,
                    "pin": pin_number,
                    "signals": pin_signals,
                }
            )

            # process all pin signals
            for signal in pin.findall(NS + "Signal"):
                if signal.get("Name") == "GPIO":
                    continue

                signal_name = signal.get("Name")
                if signal_name is None:
                    continue

                if signal_name in pin_afs:
                    pin_af = pin_afs[signal_name]
                    if not isinstance(pin_af, list):
                        pin_af = [pin_af]
                    found_afs = pin_af
                # STM32F1: assume NO_REMAP (af=0) if signal is not listed in pin_afs
                elif family == "STM32F1":
                    found_afs = [0]
                # Non STM32F1: No alternate function found, mode is analog
                else:
                    found_afs = [None]

                for af in found_afs:
                    pin_signals.append({"name": signal_name, "af": af})

    return results


def main(data_path, output):
    """Entry point.

    Args:
        data_path: STM32 Open Pin Data repository path.
        output: Output directory.
    """

    with open(CONFIG_FILE) as f:
        config = yaml.load(f, Loader=yaml.Loader)

    with open(CONFIG_F1_FILE) as f:
        config_f1 = yaml.load(f, Loader=yaml.Loader)

    env = Environment(
        trim_blocks=True, lstrip_blocks=True, loader=FileSystemLoader(SCRIPT_DIR)
    )
    env.filters["format_mode"] = format_mode
    env.filters["format_mode_f1"] = format_mode_f1
    env.filters["format_remap"] = format_remap
    pinctrl_template = env.get_template(PINCTRL_TEMPLATE)
    readme_template = env.get_template(README_TEMPLATE)

    gpio_ip_afs = get_gpio_ip_afs(data_path)
    mcu_signals = get_mcu_signals(data_path, gpio_ip_afs)

    if output.exists():
        shutil.rmtree(output)
    output.mkdir(parents=True)

    for family, refs in mcu_signals.items():
        # obtain family pinctrl address
        pinctrl_addr = PINCTRL_ADDRESSES.get(family.lower())
        if not pinctrl_addr:
            logger.error(f"Unsupported family: {family}")
            continue

        # create directory for each family
        family_dir = output / "st" / family.lower()[5:]
        if not family_dir.exists():
            family_dir.mkdir(parents=True)

        # process each reference
        for ref in refs:
            entries = dict()

            # process each pin in the current reference
            for pin in ref["pins"]:
                # process each pin available signal (matched against regex)
                for signal in pin["signals"]:
                    if family == "STM32F1":
                        selected_config = config_f1
                    else:
                        selected_config = config

                    for af in selected_config:
                        validate_config_entry(af, family)

                        m = re.search(af["match"], signal["name"])
                        if not m:
                            continue

                        if af["name"] not in entries:
                            entries[af["name"]] = list()

                        # Define the signal mode using, by priority order:
                        # 1- the config mode (ie: "af["mode"]")
                        # 2- the inferred mode (an alternate function was found)
                        if af.get("mode") or family == "STM32F1":
                            signal["mode"] = af["mode"]
                        else:
                            if signal["af"] is not None:
                                signal["mode"] = "alternate"
                            else:
                                signal["mode"] = "analog"

                        entries[af["name"]].append(
                            {
                                "port": pin["port"],
                                "pin": pin["pin"],
                                "signal": signal["name"].lower(),
                                "af": signal["af"],
                                "mode": signal["mode"],
                                "drive": af.get("drive"),
                                "bias": af.get("bias"),
                                "slew-rate": af.get("slew-rate"),
                                "variant": af.get("variant"),
                            }
                        )

            if not entries:
                continue

            # sort entries by group name
            entries = OrderedDict(sorted(entries.items(), key=lambda kv: kv[0]))

            # sort entries in each group by signal, port, pin
            for group in entries:
                entries[group] = sorted(
                    entries[group],
                    key=lambda entry: (
                        str(entry["signal"]).split("_")[0][-1],
                        entry["port"],
                        entry["pin"],
                    ),
                )

            # write pinctrl file
            ref_file = family_dir / (ref["name"].lower() + "-pinctrl.dtsi")
            with open(ref_file, "w") as f:
                f.write(
                    pinctrl_template.render(
                        family=family, pinctrl_addr=pinctrl_addr, entries=entries
                    )
                )

    # write readme file
    commit_raw = check_output(["git", "rev-parse", "HEAD"], cwd=data_path)
    commit = commit_raw.decode("utf-8").strip()
    with open(output / "README.md", "w") as f:
        f.write(readme_template.render(commit=commit))


if __name__ == "__main__":
    parser = argparse.ArgumentParser()
    parser.add_argument(
        "-p",
        "--data-path",
        type=Path,
        required=True,
        help="Path to STM32 Open Pin Data repository",
    )
    parser.add_argument(
        "-o",
        "--output",
        type=Path,
        default=REPO_ROOT / "dts",
        help="Output directory",
    )
    args = parser.parse_args()

    main(args.data_path, args.output)
