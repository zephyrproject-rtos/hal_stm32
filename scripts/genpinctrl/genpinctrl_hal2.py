"""
Utility to autogenerate Zephyr DT pinctrl files for all STM32 microcontrollers.

Usage::

    python3 genpinctrl_hal2.py -p /path/to/CubeXX-family/cube package
                          [-o /path/to/output_dir]

Copyright (c) 2025 STMicroelectronics

SPDX-License-Identifier: Apache-2.0
"""

import yaml
import json
import re
import logging
import argparse
from pathlib import Path
from typing import Tuple, Optional, List, Dict
from jinja2 import Environment, FileSystemLoader

logger = logging.getLogger(__name__)

SCRIPT_DIR = Path(__file__).absolute().parent
"""Script directory."""

REPO_ROOT = SCRIPT_DIR / ".." / ".."
"""Repository root (used for defaults)."""

CONFIG_FILE = SCRIPT_DIR / "stm32-pinctrl-config.yaml"
"""Configuration file."""

PINCTRL_TEMPLATE = "pinctrl-template.j2"
"""pinctrl template file."""


SUPPORTED_FAMILIES = [
    "stm32c5",
]
"""Supported SoC families."""


def get_all_group(path_yaml: Path) -> List[str]:
    """
    Retrieves all signals groups from a YAML configuration file.

    This function loads a YAML file containing pin group configurations, extracts
    the names of all signals groups, and returns them as a list of strings.

    Args:
        path_yaml (Path): The path to the YAML file containing pin group configurations.

    Returns:
        List[str]: A list of pin group names.

    Examples:
        >>> signal_groups = get_all_group(Path("path/to/stm32-pinctrl-config.yaml"))
        >>> print(signal_groups)
            [ "Analog", "ADC_VINM / ADC_VINP", "CAN_TX", "I2C_SDA", ... ]
    """
    signal_groups = []

    with open(path_yaml) as file_:
        datas = yaml.safe_load(file_)

        for data in datas:
            signal_groups.append(data["name"])

    return signal_groups


def split_pins(pin_name: str) -> Tuple[Optional[str], Optional[str], Optional[str]]:
    """
    Splits a pin name into its components if it matches the pattern 'PXYY'.

    The function checks if the input string starts with 'P', followed by a
    capital letter, and then one or two digits. If the string matches this
    pattern, it extracts and returns the components of the pin name.
    Args:
        pin_name (str): The pin name to be split.

    Returns:
        Tuple[Optional[str], Optional[str], Optional[str]]: A tuple containing:
            - The full pin name in lowercase (str) if the pattern matches,
              otherwise None.
            - The port name (str) if the pattern matches, otherwise None.
            - The pin number (str) if the pattern matches, otherwise None.

    Examples:
        >>> split_pins("PA10")
        ('pa10', 'A', '10')

        >>> split_pins("PB3")
        ('pb3', 'B', '3')
        >>> split_pins("PD678")
        Wrong pin format for PD678
        (None, None, None)
    """
    pattern = r"^P([A-Z])([0-9]{1,2})"  # match PXYY

    # Use regular expression to match the pattern
    match = re.match(pattern, pin_name)

    if match:
        # Extract the part starting with 'P' and ending after one or two digits
        pin_name = match.group(0)

        # Extract the capital letter and digits
        port_name = match.group(1)
        pin_number = match.group(2)

        return pin_name.lower(), port_name, pin_number
    else:
        logger.error(f"Wrong pin format for {pin_name}")
        return None, None, None


# Function to split the string into parts
def alphanum_key(s):
    return [
        int(text) if text.isdigit() else text.lower()
        for text in re.split("([0-9]+)", s)
    ]


def get_analog_pins(path_json: Path) -> List[str]:
    """
    Retrieves a sorted list of pins to be configured as analog from a JSON file.

    This function loads a JSON file containing pinout configuration data, extracts
    the pins to be configured as analog, and returns a sorted list of these pins
    in a natural alphanumeric order.

    Args:
        path_json (Path): The path to the JSON file containing the pin
                         configuration data.

    Returns:
        List[str]: A sorted list of pin names to be configured as analog.

    Examples:
        >>> get_analog_pins(Path("path/to/stm32*_pinout.json"))
        ['pa0', 'pa1', 'pa2', 'pa3', ... ]
    """
    analog_pins = []

    # Load the JSON data
    with open(path_json) as file_:
        soc = json.load(file_)
        # get all all MCU pins
        soc_pads = soc["die_pads"]

        for key, value in soc_pads.items():
            if "pin_type" in value:
                # match all PXY pins - Eg : PA1, PB10, etc...
                check = re.findall("^P[A-Z][0-9]+", key)

                if check:
                    analog_pins.append(check[0].lower())

    sorted_pins = sorted(analog_pins, key=alphanum_key)

    return sorted_pins


def get_mcu_signals(path_json: Path) -> List[Dict]:
    """
    Retrieves a list of MCU signals from a JSON file, excluding signals named "GPIO".

    This function loads a JSON file containing MCU signal data, filters out signals
    with the name "GPIO", and returns a list of the remaining signals.

    Args:
        path_json (Path): The path to the JSON file containing the MCU signal data.

    Returns:
        List[Dict]: A list of dictionaries representing the MCU signals,
                    excluding those named "GPIO".

    Examples:
        >>> get_mcu_signals(Path("path/to/stm32*_pinout.json"))
        [ {
            "name": "SIGNAL1",
            "instance": "instancex",
            "die_pad": "PXX",
            "function": {
                "type": "alternate",
                "id": "AFX"
            }
          },
          {
            "name": "SIGNAL2",
            "instance": "instancex",
            "die_pad": "PXX",
            "function": {
                "type": "analog"
            }
          },
            ...
        ]
    """
    mcu_signals = []

    with open(path_json) as file_:
        soc = json.load(file_)
        soc_signals = soc["signals"]

        # Remove signals with the name "GPIO"
        for soc_signal in soc_signals:
            if soc_signal["name"] != "GPIO":
                mcu_signals.append(soc_signal)

    return mcu_signals


def add_signal_properties(
    mcu_signals: List[Dict], path_json: Path, path_yaml: Path
) -> Tuple[List[Dict], List[Dict]]:
    """
    Adds additional properties to MCU signals based on JSON and YAML configurations.

    This function enhances the given list of MCU signals by adding additional
    properties according to the configurations specified in a JSON file and a
    YAML file. It adds signal mode (AFX or ANALOG), signal name in lower case,
    port (A, B, etc..) and pin number, I2C properties like drive, bias or
    slew_rate properties. It also creates a list of analog signals based on the
    analog pins extracted from the JSON file.

    Args:
        mcu_signals (List[Dict]): A list of dictionaries representing the MCU signals.
        path_json (Path): The path to the JSON file with the pin configuration data.
        path_yaml (Path): The path to the YAML file with signal properties.

    Returns:
        Tuple[List[Dict], List[Dict]]: A tuple containing:
            - A list of dictionaries representing the enhanced MCU signals.
            - A list of dictionaries representing the analog signals.

    Examples:
        >>> mcu_signals = [{'name': 'SIGNAL1', 'die_pad': 'PA10', 'function':
                           {'type': 'alternate', 'id': 'AF1'}}, ... ]
        >>> path_json = Path("path/to/stm32*_pinout.json")
        >>> path_yaml = Path("path/to/stm32-pinctrl-config.yaml")
        >>> enhanced_signals, analog_signals = add_signal_properties(mcu_signals,
                                                    path_json, path_yaml)
        >>> print(enhanced_signals)
        >>> print(analog_signals)
    """
    # List of some specific signals that will have pins configured as analog
    analog_list = [
        "ADC_VINM / ADC_VINP",
        "ADC_IN / ADC_INN / ADC_INP",
        "DAC_OUT",
        "UCPD",
    ]
    analog_signals = []
    analog_pins = get_analog_pins(path_json)

    # Create a list of analog pins
    analog_signals = [
        {
            "name": "analog",
            "mode": "ANALOG",
            "signal": signal,
            "port": signal[1],
            "pin": signal[2:],
        }
        for signal in analog_pins
    ]

    with open(path_yaml) as file_:
        configs = yaml.safe_load(file_)
        for config in configs:
            for mcu_signal in mcu_signals:
                # Handle signals of other groups
                m = re.search(config["match"], mcu_signal["name"])

                if m:
                    # Add additional signal properties according to config.yaml
                    if "slew-rate" in config.keys():
                        mcu_signal["slew-rate"] = config["slew-rate"]

                    if "bias" in config.keys():
                        mcu_signal["bias"] = config["bias"]

                    if "drive" in config.keys():
                        mcu_signal["drive"] = config["drive"]

                    pin_name, port, pin_number = split_pins(mcu_signal["die_pad"])
                    mcu_signal["pin"] = pin_number
                    mcu_signal["port"] = port
                    mcu_signal["signal"] = pin_name

                    if (
                        mcu_signal["function"]["type"] == "alternate"
                        and config["name"] not in analog_list
                    ):
                        mcu_signal["mode"] = mcu_signal["function"]["id"]  # AFX

                    if (
                        mcu_signal["function"]["type"] == "analog"
                        or mcu_signal["function"]["type"] == "additional"
                    ):  # for DAC_OUT, etc.
                        mcu_signal["mode"] = "ANALOG"

    return mcu_signals, analog_signals


def combine_group_signals(path_yaml: Path, path_json: Path) -> Dict[str, List[Dict]]:
    """
    Combines MCU signals into groups based on YAML and JSON configurations.

    It then combines the signals into their respective groups based on the
    configurations. Analog signals are handled separately and added to the
    "Analog" group. The function returns a dictionary where the keys are group
    names and the values are lists of signals belonging to those groups.

    Args:
        path_yaml (Path): The path to the YAML file containing group configurations.
        path_json (Path): The path to the JSON file containing MCU signal data.

    Returns:
        Dict[str, List[Dict]]: A dictionary where the keys are group names and
                               the values are lists of dictionaries representing
                               the signals in each group.

    Examples:
        >>> group_signals = combine_group_signals(
                                Path("path/to/stm32-pinctrl-cfg.yaml"),
                                Path("path/to/stm32*_pinout.json"))
        >>> print(group_signals)
        {
            "Analog" : [ {signal1_description}, {signal1_description}, ... ],
            "ADC_IN / ADC_INN / ADC_INP" : [ {signal1_description}, ... ],
            "USB_OTG_FS" : [ {signal1_description}, {signal2_description}, ... ],
            "I2C_SDA" : [ {signal1_description}, {signal2_description}, ... ],
            ...
        }
    """
    groups = get_all_group(path_yaml)

    # Initialize an empty list for each group
    group_and_signals = {key: [] for key in groups}

    mcu_signals = get_mcu_signals(path_json)

    mcu_signals, analogs_signals = add_signal_properties(
        mcu_signals, path_json, path_yaml
    )

    with open(path_yaml) as file_:
        configs = yaml.safe_load(file_)
        for config in configs:
            # Handle analog signals: Analog group
            if config["name"] == "Analog":
                group_and_signals[config["name"]] = analogs_signals

            # Handle other signals group
            for mcu_signal in mcu_signals:
                m = re.search(config["match"], mcu_signal["name"])

                if m:
                    group_and_signals[config["name"]].append(mcu_signal)

    # Filter by removing all groups that don't have signals
    group_and_signals = {
        key: value for key, value in group_and_signals.items() if value
    }

    return group_and_signals


def get_series_pinout_files(root_or_dfp_path: Path) -> tuple[str, list[Path]]:
    """
    Probe an STM32Cube HAL2 package and returns the name of the package's series
    as well as a list of all pinout JSON files contained in the DFP.

    Args:
        root_or_dfp_path (Path): Path to root OR dfp folder of target HAL2 package

    Returns:
        tuple[str, list[Path]]: A tuple containing the series name and a list of all
                                pinout JSON files contained in the package's DFP
    """
    if root_or_dfp_path.is_file():
        raise ValueError(f"Expected a directory path, got a file: '{root_or_dfp_path}'")
    if not root_or_dfp_path.is_dir():
        raise ValueError(f"'{root_or_dfp_path}' is not a valid directory path")

    # Check if provided path points to a DFP folder: "stm32XXXXxx_dfp"
    if root_or_dfp_path.name.endswith("_dfp"):
        dfp_dir = root_or_dfp_path
    else:
        # Not a DFP folder: the path must point to a root.
        # The DFP folder is a direct child of the root;
        # check if it exists in the directory we were given.
        if not (dfp_dirs := list(root_or_dfp_path.glob("*_dfp"))):
            raise ValueError(f"No DFP folder found in '{root_or_dfp_path}'")

        if len(dfp_dirs) > 1:
            logging.warning(f"More than one DFP folder found in '{root_or_dfp_path}'!")
            logging.warning(f"Generating pinctrl from the first one: '{dfp_dirs[0]}'")

        dfp_dir = dfp_dirs[0]

    series_name = dfp_dir.stem.removesuffix("_dfp")
    pinouts_dir = dfp_dir / "Descriptors/pinout"
    return series_name, list(pinouts_dir.glob("*.json"))


def main(data_path: Path, output):
    """Entry point.

    Args:
        data_path: Path to STM32Cube package root or dfp folder
        output: Output directory
    """
    env = Environment(loader=FileSystemLoader(SCRIPT_DIR),
                      keep_trailing_newline=True,
                      lstrip_blocks=True, trim_blocks=True,
                      )
    pinctrl_template = env.get_template(PINCTRL_TEMPLATE)

    # List of all JSON files in the soc_folder
    soc, soc_files = get_series_pinout_files(data_path)

    family = soc[:7]
    family_id = family[5:]

    try:
        # Create the directory if it does not exist
        family_dir = output / "st"
        if not family_dir.exists():
            family_dir.mkdir(parents=True)
            logger.info("Directory st created or already exists.")
    except Exception as e:
        logger.error(f"An error occurred while creating the directory: {e}")

    if family in SUPPORTED_FAMILIES:
        logger.info(
            f" ==== Processing SOC family : {soc},  id family :  {family_id} ===="
        )
        try:
            # Create the directory if it does not exist
            OUTPUT_PATH = family_dir / family_id
            OUTPUT_PATH.mkdir(parents=True, exist_ok=True)
            logger.info(f"Directory '{OUTPUT_PATH}' created or already exists.")
        except Exception as e:
            logger.error(f"An error occurred while creating the directory: {e}")
        for soc_file in soc_files:
            all_signals = combine_group_signals(CONFIG_FILE, soc_file)
            match = re.match(
                r"([^/]+)_pinout\.json$", soc_file.name
            )

            if match:
                extracted_part = match.group(1)
                json_name = extracted_part.lower()

                # output_file = output / family_id / f"{json_name}-pinctrl.dtsi"
                output_file = OUTPUT_PATH / f"{json_name}-pinctrl.dtsi"

                with open(output_file, "w") as f:
                    f.write(
                        pinctrl_template.render(hal2=True, entries=all_signals)
                    )
            else:
                logger.error(f"No soc/pinout file detected in: {soc_file}")
    else:
        logger.warning(
            f"unsupported stm32 soc family {family}, missing peripheral address ?"
        )


if __name__ == "__main__":
    parser = argparse.ArgumentParser()
    parser.add_argument(
        "-p",
        "--data-path",
        type=Path,
        required=True,
        help=("Path to STM32Cube package root or DFP folder "
              "(the package must be in HAL2 format)"),
    )
    parser.add_argument(
        "-o",
        "--output",
        type=Path,
        default=REPO_ROOT / "dts",
        help="Output directory",
    )
    parser.add_argument(
        "-v", "--verbose", action="store_true", help="Make script verbose"
    )

    args = parser.parse_args()

    logger.setLevel(logging.INFO if args.verbose else logging.WARN)
    logger.addHandler(logging.StreamHandler())

    main(args.data_path, args.output)
