import os

import pytest

from genpinctrl import (
    validate_config_entry,
    format_mode,
    format_mode_f1,
    format_remap,
    get_gpio_ip_afs,
    get_mcu_signals,
    main,
)


def test_validate_config_entry():
    """Check that config entries are validated correctly"""

    # no name
    entry = {}
    with pytest.raises(ValueError):
        validate_config_entry(entry, "")

    # no match
    entry = {"name": "TEST"}
    with pytest.raises(ValueError):
        validate_config_entry(entry, "")

    # no mode
    entry = {"name": "TEST", "match": "TEST"}
    with pytest.raises(ValueError):
        validate_config_entry(entry, "")

    # invalid mode
    entry = {"name": "TEST", "match": "TEST"}
    entry["mode"] = "INVALID"
    with pytest.raises(ValueError):
        validate_config_entry(entry, "STM32F0")
    with pytest.raises(ValueError):
        validate_config_entry(entry, "STM32F1")

    # valid modes
    entry = {"name": "TEST", "match": "TEST"}
    entry["mode"] = "analog"
    validate_config_entry(entry, "STM32F0")
    validate_config_entry(entry, "STM32F1")
    entry["mode"] = "alternate"
    validate_config_entry(entry, "STM32F0")
    validate_config_entry(entry, "STM32F1")
    entry["mode"] = "input"
    validate_config_entry(entry, "STM32F1")

    # invalid bias
    entry = {"name": "TEST", "match": "TEST", "mode": "alternate"}
    entry["bias"] = "INVALID"
    with pytest.raises(ValueError):
        validate_config_entry(entry, "STM32F0")

    entry["bias"] = "pull-up"
    with pytest.raises(ValueError):
        validate_config_entry(entry, "STM32F1")

    # valid bias
    entry = {"name": "TEST", "match": "TEST"}
    entry["bias"] = "disable"
    entry["mode"] = "alternate"
    validate_config_entry(entry, "STM32F0")
    validate_config_entry(entry, "STM32F1")
    entry["mode"] = "input"
    validate_config_entry(entry, "STM32F1")

    entry["bias"] = "pull-up"
    entry["mode"] = "alternate"
    validate_config_entry(entry, "STM32F0")
    entry["mode"] = "input"
    validate_config_entry(entry, "STM32F1")

    entry["bias"] = "pull-down"
    entry["mode"] = "alternate"
    validate_config_entry(entry, "STM32F0")
    entry["mode"] = "input"
    validate_config_entry(entry, "STM32F1")

    # invalid drive
    entry = {"name": "TEST", "match": "TEST", "mode": "alternate"}
    entry["drive"] = "INVALID"
    with pytest.raises(ValueError):
        validate_config_entry(entry, "STM32F0")

    # valid drive
    entry = {"name": "TEST", "match": "TEST", "mode": "alternate"}
    entry["drive"] = "push-pull"
    validate_config_entry(entry, "STM32F0")
    entry["bias"] = "open-drain"

    # invalid slew-rate
    entry = {"name": "TEST", "match": "TEST", "mode": "alternate"}
    entry["slew-rate"] = "INVALID"
    with pytest.raises(ValueError):
        validate_config_entry(entry, "STM32F0")
    with pytest.raises(ValueError):
        validate_config_entry(entry, "STM32F1")

    # valid slew-rate
    entry = {"name": "TEST", "match": "TEST", "mode": "alternate"}
    entry["slew-rate"] = "low-speed"
    validate_config_entry(entry, "STM32F0")
    entry["slew-rate"] = "medium-speed"
    validate_config_entry(entry, "STM32F0")
    entry["slew-rate"] = "high-speed"
    validate_config_entry(entry, "STM32F0")
    entry["slew-rate"] = "very-high-speed"
    validate_config_entry(entry, "STM32F0")

    entry["slew-rate"] = "max-speed-10mhz"
    validate_config_entry(entry, "STM32F1")
    entry["slew-rate"] = "max-speed-2mhz"
    validate_config_entry(entry, "STM32F1")
    entry["slew-rate"] = "max-speed-50mhz"
    validate_config_entry(entry, "STM32F1")


def test_format_mode():
    """Test that format_mode works."""

    assert format_mode("analog", None) == "ANALOG"
    assert format_mode("alternate", 0) == "AF0"

    with pytest.raises(ValueError):
        format_mode("INVALID", 0)


def test_format_mode_f1():
    """Test that format_mode_f1 works."""

    assert format_mode_f1("analog") == "ANALOG"
    assert format_mode_f1("input") == "GPIO_IN"
    assert format_mode_f1("alternate") == "ALTERNATE"

    with pytest.raises(ValueError):
        format_mode_f1("INVALID")


def test_format_remap():
    """Test that format_remap works."""

    assert format_remap(None) == "NO_REMAP"
    assert format_remap(0) == "NO_REMAP"
    assert format_remap(1) == "REMAP_1"
    assert format_remap(2) == "REMAP_2"
    assert format_remap(3) == "FULL_REMAP"

    with pytest.raises(ValueError):
        format_remap(5)


def test_get_gpio_ip_afs(cubemx):
    """Test that IP AF files part of test CubeMX files are parsed correctly."""

    afs = get_gpio_ip_afs(cubemx)
    assert afs == {
        "STM32F0TESTIP": {
            "PA0": {
                "UART1_TX": 0,
                "UART1_RX": 1,
            }
        },
        "STM32F1TESTIP": {
            "PA0": {
                "UART1_TX": 0,
                "UART1_RX": 1,
            }
        },
    }


def test_get_mcu_signals(cubemx):
    """Test that MCU files part of test CubeMX are parsed correctly."""

    afs = get_gpio_ip_afs(cubemx)
    signals = get_mcu_signals(cubemx, afs)
    assert signals == {
        "STM32F0": [
            {
                "name": "STM32F0TESTDIE",
                "pins": [
                    {
                        "port": "a",
                        "pin": 0,
                        "signals": [
                            {"name": "UART1_TX", "af": 0},
                            {"name": "UART1_RX", "af": 1},
                            {"name": "ADC1_IN0", "af": None},
                        ],
                    },
                ],
            },
        ],
        "STM32F1": [
            {
                "name": "STM32F1TESTDIE",
                "pins": [
                    {
                        "port": "a",
                        "pin": 0,
                        "signals": [
                            {"name": "UART1_TX", "af": 0},
                            {"name": "UART1_RX", "af": 1},
                            {"name": "ADC1_IN0", "af": None},
                        ],
                    },
                ],
            },
        ],
    }


def test_cubemx_missing():
    """Test that missing CubeMX folders is handled correctly by parsing functions."""

    with pytest.raises(FileNotFoundError):
        get_gpio_ip_afs("MISSING_PATH")

    with pytest.raises(FileNotFoundError):
        get_mcu_signals("MISSING_PATH", dict())


def test_main(data, cubemx, tmp_path):
    """Test that DTS files are generated correctly."""

    main(cubemx, tmp_path)

    # check f0 file
    ref_pinctrl_file = os.path.join(data, "stm32f0testdie-pinctrl.dtsi")
    gen_pinctrl_file = os.path.join(tmp_path, "f0", "stm32f0testdie-pinctrl.dtsi")

    assert os.path.exists(gen_pinctrl_file)

    with open(ref_pinctrl_file) as ref, open(gen_pinctrl_file) as gen:
        assert ref.read() == gen.read()

    # check f1 file
    ref_pinctrl_file = os.path.join(data, "stm32f1testdie-pinctrl.dtsi")
    gen_pinctrl_file = os.path.join(tmp_path, "f1", "stm32f1testdie-pinctrl.dtsi")

    assert os.path.exists(gen_pinctrl_file)

    with open(ref_pinctrl_file) as ref, open(gen_pinctrl_file) as gen:
        assert ref.read() == gen.read()
