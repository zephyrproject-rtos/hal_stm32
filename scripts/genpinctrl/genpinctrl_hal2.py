"""
Utility to autogenerate Zephyr DT pinctrl files for all STM32 microcontrollers.

Usage::

    python3 genpinctrl_hal2.py -p /path/to/CubeXX-family/cube package
                          [-o /path/to/output_dir]

Copyright (c) 2025 STMicroelectronics

SPDX-License-Identifier: Apache-2.0
"""

import os
import yaml
import json
import re
import logging
import glob
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

PINCTRL_TEMPLATE = "pinctrl-template_hal2.j2"
"""pinctrl template file."""


SUPPORTED_FAMILIES = [
    "stm32c5",
]
"""Supported SoC families."""


def get_all_group(path_yaml: str) -> List[str]:
    """
    Retrieves all signals groups from a YAML configuration file.

    This function loads a YAML file containing pin group configurations, extracts
    the names of all signals groups, and returns them as a list of strings.

    Args:
        path_yaml (str): The path to the YAML file containing pin group configurations.

    Returns:
        List[str]: A list of pin group names.

    Examples:
        >>> signal_groups = get_all_group("path/to/stm32-pinctrl-config.yaml")
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


def get_analog_pins(path_json: str) -> List[str]:
    """
    Retrieves a sorted list of pins to be configured as analog from a JSON file.

    This function loads a JSON file containing pinout configuration data, extracts
    the pins to be configured as analog, and returns a sorted list of these pins
    in a natural alphanumeric order.

    Args:
        path_json (str): The path to the JSON file containing the pin
                         configuration data.

    Returns:
        List[str]: A sorted list of pin names to be configured as analog.

    Examples:
        >>> get_analog_pins("path/to/stm32*_pinout.json")
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


def get_mcu_signals(path_json: str) -> List[Dict]:
    """
    Retrieves a list of MCU signals from a JSON file, excluding signals named "GPIO".

    This function loads a JSON file containing MCU signal data, filters out signals
    with the name "GPIO", and returns a list of the remaining signals.

    Args:
        path_json (str): The path to the JSON file containing the MCU signal data.

    Returns:
        List[Dict]: A list of dictionaries representing the MCU signals,
                    excluding those named "GPIO".

    Examples:
        >>> get_mcu_signals("path/to/stm32*_pinout.json")
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
    mcu_signals: List[Dict], path_json: str, path_yaml: str
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
        path_json (str): The path to the JSON file with the pin configuration data.
        path_yaml (str): The path to the YAML file with signal properties.

    Returns:
        Tuple[List[Dict], List[Dict]]: A tuple containing:
            - A list of dictionaries representing the enhanced MCU signals.
            - A list of dictionaries representing the analog signals.

    Examples:
        >>> mcu_signals = [{'name': 'SIGNAL1', 'die_pad': 'PA10', 'function':
                           {'type': 'alternate', 'id': 'AF1'}}, ... ]
        >>> path_json = "path/to/stm32*_pinout.json"
        >>> path_yaml = "path/to/stm32-pinctrl-config.yaml"
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


def combine_group_signals(path_yaml: str, path_json: str) -> Dict[str, List[Dict]]:
    """
    Combines MCU signals into groups based on YAML and JSON configurations.

    It then combines the signals into their respective groups based on the
    configurations. Analog signals are handled separately and added to the
    "Analog" group. The function returns a dictionary where the keys are group
    names and the values are lists of signals belonging to those groups.

    Args:
        path_yaml (str): The path to the YAML file containing group configurations.
        path_json (str): The path to the JSON file containing MCU signal data.

    Returns:
        Dict[str, List[Dict]]: A dictionary where the keys are group names and
                               the values are lists of dictionaries representing
                               the signals in each group.

    Examples:
        >>> group_signals = combine_group_signals("path/to/stm32-pinctrl-cfg.yaml",
                                                  "path/to/stm32*_pinout.json")
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


def get_soc_family_pinouts(directory_path: str) -> Dict[str, List[str]]:
    """
    Retrieves JSON file paths for each SoC family directory within a given
    directory.

    This function lists all directories within the specified directory path,
    identifies each as an SoC family directory, and searches for JSON files
    within the "Descriptors/pinout" subdirectory of each SoC family directory.
    It returns a dictionary where the keys are the SoC family directory names
    and the values are lists of JSON pinouts paths within those directories.

    Args:
        directory_path (str): The path to the directory containing SoC family
                              directories.

    Returns:
        Dict[str, List[str]]: A dictionary where the keys are SoC family directory
                              names and the values are lists of JSON file paths
                              within those directories.

    Examples:
        >>> soc_files = get_soc_family_pinouts("/path/to/soc_families")
        >>> print(soc_files)
        {
            "stm32c5xx": ["path1/to/pinout1.json", "path/to/pinout2.json", ... ],
            "stm32yzxx": ["path1/to/pinout1.json", "path/to/pinout2.json", ... ],
             ...
        }
    """
    try:
        # List all entries in the given directory
        entries = os.listdir(directory_path)

        # Filter out only directories
        soc_folders = [
            entry
            for entry in entries
            if os.path.isdir(os.path.join(directory_path, entry))
        ]

        # Dictionary to store folder names and their JSON file paths
        soc_folder_json_files = {}

        for soc_folder in soc_folders:
            soc_path = os.path.join(directory_path, soc_folder, "Descriptors/pinout")
            # Find all JSON files in the folder
            json_files = glob.glob(os.path.join(soc_path, "*.json"))
            soc_folder_json_files[soc_folder] = json_files

        return soc_folder_json_files

    except FileNotFoundError:
        logger.error(f"The directory {directory_path} does not exist.")
        return {}
    except PermissionError:
        logger.error(f"Permission denied to access the directory {directory_path}.")
        return {}


def main(data_path, output):

    env = Environment(loader=FileSystemLoader(SCRIPT_DIR))
    pinctrl_template = env.get_template(PINCTRL_TEMPLATE)

    # List of all JSON files in the soc_folder
    soc_json_files = get_soc_family_pinouts(data_path)

    for soc, soc_files in soc_json_files.items():
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
                os.makedirs(OUTPUT_PATH, exist_ok=True)
                logger.info(f"Directory '{OUTPUT_PATH}' created or already exists.")
            except Exception as e:
                logger.error(f"An error occurred while creating the directory: {e}")
            for soc_file in soc_files:
                all_signals = combine_group_signals(CONFIG_FILE, soc_file)
                # Normalize the path to handle '..'
                normalized_path = os.path.normpath(soc_file)

                # Use regular expression to extract json file name
                # Check both for / and \ in file path for Unix and Windows compatibility
                match = re.search(
                    r"[\/\\]pinout[\/\\]([^/]+)_pinout\.json$", normalized_path
                )

                if match:
                    extracted_part = match.group(1)
                    json_name = extracted_part.lower()

                    # output_file = output / family_id / f"{json_name}-pinctrl.dtsi"
                    output_file = OUTPUT_PATH / f"{json_name}-pinctrl.dtsi"

                    with open(output_file, "w") as f:
                        f.write(
                            pinctrl_template.render(entries=all_signals)
                        )
                else:
                    logger.error(f"No soc/pinout file detected in: {normalized_path}")
        else:
            logger.warning(
                f"unsupported stm32 soc family {family}, missing peripheral address ?"
            )


if __name__ == "__main__":

    """Entry point.

    Args:
        data_path: Path to STM32 cube v2 package dfp folder.
        output: Output directory.
    """

    parser = argparse.ArgumentParser()
    parser.add_argument(
        "-p",
        "--data-path",
        type=Path,
        required=True,
        help="Path to STM32 cube v2 dfp folder",
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
