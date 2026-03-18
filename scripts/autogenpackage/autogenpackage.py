"""
Automatic generator for hal_stm32 repository

Handles generation of the following files:
        - stm32cube/stm32NNNxx/CMakeLists.txt            (per-series CMakeLists)
        - stm32cube/common/include/stm32_assert.h        (global HAL assert header)
        - stm32cube/series_list.cmake                    (global series list)

This script can also generate the following Zephyr-side files:
        - zephyr/modules/Kconfig.stm32

Usage::

    python3 autogenpackage.py
        [-p /path/to/HAL/repo]
        [--modules-kconfig-dst /path/to/zephyrproject/zephyr/modules/Kconfig.stm32]

Copyright (c) 2025 STMicroelectonics

SPDX-License-Identifier: Apache-2.0
"""

import argparse
from datetime import datetime
import logging
from pathlib import Path
import re

from jinja2 import Environment, FileSystemLoader

SCRIPT_DIR = Path(__file__).absolute().parent
"""Script directory"""

STM32CUBE_DIR = "stm32cube/"
"""Path to 'stm32cube' directory, relative to hal_stm32 repository root

This is the directory in which STM32Cube HAL packages are expected to be placed.
"""

# General HAL layout configuration

SERIES_DRIVERS_PATH = "drivers/"
"""Path to drivers files, relative to serie's root directory"""

SERIES_DRIVERS_SRC_PATH = SERIES_DRIVERS_PATH + "src/"
"""Path to drivers source files, relative to serie's root directory"""

# Settings for 'series_list.cmake' generation

SERIES_LIST_TEMPLATE = "series_list.j2"
SERIES_LIST_OUTPUT = STM32CUBE_DIR + "series_list.cmake"
"""Destination for generated file (absolute path)"""

# Settings for per-series 'CMakeLists.txt' generation

SERIES_CMAKELIST_TEMPLATE = "series_cmakelists.j2"
SERIES_CMAKELIST_OUTPUT = "CMakeLists.txt"
"""Destination for generated file, relative to serie's root directory"""

CMSIS_SYSTEM_REQUIRED_SERIES = ["stm32n6x", "stm32mp1x", "stm32mp2x"]
"""List of series that need 'soc/system_stm32XXXxx.c' in CMakeLists."""

# Settings for per-series 'stm32_assert.h' generation

STM32_ASSERT_H_TEMPLATE = "stm32_assert.j2"
STM32_ASSERT_H_OUTPUT = STM32CUBE_DIR + "common/include/stm32_assert.h"
"""Destination for generated file, relative to serie's root directory"""

# Settings for Zephyr-side 'zephyr/modules/Kconfig.stm32' generation

MODULES_KCONFIG_TEMPLATE = "modules_kconfig.j2"

# Settings for the shared driver parser

DRIVER_REMAP_TABLE = {
    # FSMC is an old version of the FMC IP.
    # It is never present at the same time as the FMC IP,
    # and the HAL usually provides a compatibility layer
    # allowing to use the FSMC as if it was an FMC.
    # The proper driver will be selected by SoC defines.
    "fsmc": "fmc",
    # The "delayblock" name is only found on H7 and MP1/MP13;
    # newer series use "dlyb" but hardware is the same.
    "delayblock": "dlyb",
}
"""List of drivers that are remapped to another driver for uniformity."""

UNGATED_DRIVERS = [
    "hal",      # "stm32XXxx_hal.c" pseudo-driver
    "hal:rcc",  # "stm32XXxx_hal_rcc.c" driver
]
"""List of drivers that should always be included in build.

These drivers are added to the per-series 'CMakeLists.txt' as a
zephyr_library_sources() instead of zephyr_library_sources_ifdef(),
and no Kconfig symbol is generated for them in 'modules/Kconfig.stm32'.

Each entry can be either a driver name (marks all types as ungated) or
"type:name" where type is "ll", "hal" or "util". Note that the name is
compared after remapping, so the REMAP_TABLE must be taken into account!
"""

IGNORED_DRIVERS = [
    "system",  # LL driver on STM32WB0 series only; not useful

    # TODO: handle this difference in STM32MP2 vs. other SoCs
    "pcd_drd", "pcd_otg", "usb_drd", "usb_otg",
]
"""List of drivers that are ignored by the script.

No Kconfig symbol to enable them is generated and they are not added
to the per-series CMakeLists.txt so they cannot be used at all!

Refer to UNGATED_DRIVERS for entries format.
"""

# TODO: HAL exposes separate SD/MMC whereas LL has SDMMC unified - cleanup?
# TODO: review FMPI2C and (currently missing) FMPSMBUS (apply only to F4 series?)
DRIVER_LONG_NAMES = {
    "adc": "Analog-to-Digital Converter",
    "bdma": "Basic Direct Memory Access controller",
    "bsec": "Boot and Security Control",
    "cacheaxi": "AXI Cache controller",
    "can": "Controller Area Network",
    "ccb": "Coupling and Chaining Bridge",
    "cec": "HDMI-CEC controller",
    "comp": "Analog Comparator",
    "cordic": "CORDIC math coprocessor",
    "cortex": "Cortex processor",
    "crc": "Cyclic Redundancy Check calculation unit",
    "crs": "Clock Recovery System",
    "cryp": "Cryptographic accelerator",
    "dac": "Digital-to-Analog Converter",
    "dcache": "Data cache",
    "dcmi": "Digital Camera Management Interface",
    "dcmipp": "DCMI Pixel Pipeline",
    "ddr": "DDR SDRAM",
    "dfsdm": "Digital Filter for Sigma-Delta Modulator",
    "dlyb": "Delay Block",
    "dma": "Direct Memory Access controller",
    "dma2d": "Chrom-Art Accelerator™ controller",
    "dsi": "MIPI Display Serial Interface host",
    "dts": "Digital Temperature Sensor",
    "eth": "Ethernet",
    "exti": "Extended interrupt and event controller",
    "fdcan": "Controller Area Network with flexible data rate",
    "firewall": "Firewall",
    "flash_ramfunc": "Flash Memory RAM functions",
    "flash": "Embedded Flash Memory controller",
    "fmac": "Filter Math Accelerator",
    "fmc": "Flexible Memory Controller",
    "fmpi2c": "Fast-Mode Plus Inter-Integrated Circuit",
    "fmpsmbus": "Fast-Mode Plus System Management Bus",
    "fsmc": "Flexible Static Memory Controller",  # Remapped to FMC
    "gfxmmu": "Chrom-GRC™",
    "gfxtim": "Graphics Timer",
    "gpio": "General Purpose Input/Outputs",
    "gpu2d": "Neo-Chrom graphic processor",
    "gtzc": "Global TrustZone Controller",
    "hash": "Hash processor",
    "hcd": "USB Host Controller Device",
    "hrtim": "High-Resolution Timer",
    "hsem": "Hardware Semaphore",
    "i2c": "Inter-Integrated Circuit",
    "i2s": "Inter-IC Sound",
    "i3c": "Improved Inter-Integrated Circuit",
    "icache": "Instruction cache",
    "ipcc": "Inter-Processor Communication Controller",
    "irda": "Infrared Data Association",
    "iwdg": "Independent watchdog",
    "jpeg": "JPEG codec",
    "lcd": "LCD controller",
    "lpgpio": "Low-Power GPIO",
    "lptim": "Low-Power Timer",
    "lpuart": "Low-Power UART",
    "ltdc": "LCD-TFT Display Controller",
    "mce": "Memory Cipher Engine",
    "mdf": "Multi-function Digital Filter",
    "mdios": "Management Data Input/Output slave",
    "mdma": "Master Direct Memory Access controller",
    "mmc": "MultiMediaCard interface",
    "msp": "MCU Support Package",
    "nand": "NAND controller",
    "nor": "NOR controller",
    "opamp": "Operational amplifier",
    "ospi": "Octo-SPI interface",
    "otfdec": "On-the-fly decryption engine",
    "pccard": "PCCard memories",
    "pcd": "USB Peripheral Controller",
    "pch": "USB Host Controller",
    "pka": "Public Key Accelerator",
    "pssi": "Parallel Synchronous Slave Interface",
    "pwr": "Power control",
    "qspi": "Quad-SPI interface",
    "radio_timer": "Radio Timer",
    "radio": "Radio",
    "ramcfg": "RAMs configuration controller",
    "ramecc": "RAM ECC monitoring",
    "rcc": "Reset and Clock Controller",
    "rif": "Resource Isolation Framework",
    "rng": "Random Number Generator",
    "rtc": "Real-Time Clock",
    "sai": "Serial Audio Interface",
    "sd": "Secure Digital interface",
    "sdadc": "Sigma-Delta Analog-to-Digital Converter",
    "sdio": "Secure Digital Input/Output interface",
    "sdmmc": "Secure Digital / MultiMediaCard interface",
    "sdram": "SDRAM controller",
    "smartcard": "Smartcard controller",
    "smbus": "System Management Bus",
    "spdifrx": "SPDIF receiver interface",
    "spi": "Serial Peripheral Interface",
    "sram": "SRAM controller",
    "subghz": "Sub-GHz Radio",
    "swpmi": "Single Wire Protocol Master Interface",
    "system": None,  # TODO?
    "tim": "Timer",
    "tsc": "Touch Sensing Controller",
    "uart": "Universal Asynchronous Receiver Transmitter",
    "ucpd": "USB Type-C®/USB Power Delivery interface",
    "usart": "Universal Synchronous/Asynchronous Receiver Transmitter",
    "usb": "Universal Serial Bus",
    "utils": "Miscellaneous utilities",
    "venc": "Video encoder",
    "wwdg": "System window watchdog",
    "xspi": "Extended SPI interface",
}
"""Long names for each HAL driver.

Set entry to None if a given driver has no corresponding long name."""


class NullWriter:
    """A file-like object that ignores all writes."""
    def write(self, _):
        pass

    def flush(self):
        pass

    def __enter__(self):
        return self

    def __exit__(self, exc_type, exc_val, exc_tb):
        pass


class HalDriver:
    def __init__(self, driver_path: Path, serie_name: str, serie_root: Path):
        self.path = driver_path
        self.relative_path = driver_path.relative_to(serie_root).as_posix()

        # Extract all required information from driver filename:
        #   - driver type (HAL/LL/UTIL)
        #   - driver name
        #   - regular/extended driver
        drv_filename = driver_path.name.removeprefix(serie_name + "_")

        match = re.match(r"^(hal|ll|util)_(.+?)(_ex)?.c$", drv_filename)
        if not match:
            # SPECIAL CASE for "stm32XXxx_hal.c" pseudo-driver.
            # Treating it as a driver simplifies processing.
            if drv_filename == "hal.c":
                self.type = ""
                self._true_name = self._name = "hal"
                self.extended = False
                return

            raise ValueError(f"Unsupported driver filename '{driver_path}'!")

        self.type = match.group(1)
        self._true_name = match.group(2)
        self.extended = bool(match.group(3))

        if self._true_name in DRIVER_REMAP_TABLE:
            self._name = DRIVER_REMAP_TABLE[self._true_name]
        else:
            self._name = self._true_name

    def __repr__(self) -> str:
        return (f"<HalDriver name={self.name} type={self.type} "
                f"extended={self.extended} relative_path={self.relative_path}>")

    def __lt__(self, other):
        # Sort by type, then by name, then by extended
        if self.type != other.type:
            return self.type < other.type

        if self.name != other.name:
            return self.name < other.name

        # Group aliased drivers toghether
        # but sort them by driver filename
        if self.true_name != other.true_name:
            return self.true_name < other.true_name

        assert (not self.extended and other.extended) or \
               (self.extended and not other.extended)

        # Extended driver comes after the non-extended variant
        return not self.extended

    @property
    def true_name(self):
        """Returns the driver name as found verbatim in its filename"""
        return self._true_name

    @property
    def name(self):
        """Returns the driver name after aliasing (if applicable)"""
        return self._name

    @property
    def kconfig_symbol(self):
        """Return Kconfig symbol gating this driver"""
        sym = f"USE_STM32_{self.type}_{self.name}"
        if self.extended:
            sym += "_EX"
        return sym.upper()

    @staticmethod
    def _parse_list_entry(entry: str):
        # Per format definition, each entry can be either
        # plain driver name or '<drv_type>:<drv_name>'
        split_entry = entry.split(":")
        if len(split_entry) > 2:
            raise ValueError(f"Too many columns in '{entry}'")

        if len(split_entry) == 1:
            return None, split_entry[0]
        elif len(split_entry) == 2:
            drv_type, drv_name = split_entry
            DRIVER_TYPES = ["hal", "ll", "util"]
            if drv_type not in DRIVER_TYPES:
                raise ValueError(f"Illegal type '{drv_type}' in entry '{entry}'"
                                 f"(must be one of {DRIVER_TYPES})")

            return drv_type, drv_name
        else:
            assert False

    @staticmethod
    def _validate_driver_list(drv_list: list[str]):
        for entry in drv_list:
            # Ignore the result - we only care about validation
            HalDriver._parse_list_entry(entry)

    @staticmethod
    def _parse_serie_drivers(serie_dir: Path):
        """Obtain a list of all HAL drivers for specified serie."""
        serie_name = serie_dir.name

        drivers: list[HalDriver] = []
        for f in (serie_dir / SERIES_DRIVERS_SRC_PATH).iterdir():
            if not f.is_file() or not f.name.startswith(serie_name):
                continue

            # The following files are useless in Zephyr context:
            # - stm32XXXxx_hal_msp.c
            # - stm32XXXxx_hal_YYY_template.c
            #
            # Skip these files if any is found, even though
            # they should really be excluded from this repo.
            drv_noprefix = f.name.removeprefix(serie_name + "_")
            if (drv_noprefix == "hal_msp.c" or drv_noprefix.endswith("_template.c")
               or drv_noprefix.find("timebase") != -1):
                # TODO: remove the find("timebase") check when all non-template
                # timebase files have been removed from the repository!
                continue

            drv = HalDriver(f, serie_name, serie_dir)

            if drv.is_ignored:
                continue

            drivers.append(drv)
        return list(sorted(drivers))

    def _in_list(self, drv_list: list[str]):
        for entry in drv_list:
            etype, ename = HalDriver._parse_list_entry(entry)

            if self.name != ename:  # Names don't match - keep searching
                continue

            if etype is not None and etype != self.type:
                # Entry has a type which isn't ours - keep searching
                continue

            return True
        return False

    @property
    def is_ignored(self):
        return self._in_list(IGNORED_DRIVERS)

    @property
    def is_ungated(self):
        return self._in_list(UNGATED_DRIVERS)


class HalAutogenerator:
    @staticmethod
    def _parse_args(argv):
        parser = argparse.ArgumentParser()

        # Set default root to './../..'
        default_root = SCRIPT_DIR.parents[1]

        parser.add_argument("-p", "--hal-repo-root",
                            type=Path,
                            default=default_root,
                            help="Root of hal_stm32 repository on which to operate")

        parser.add_argument("-v", "--verbose",
                            action="count",
                            default=0,
                            help="Increase verbosity level (-v, -vv, -vvv, ...)")

        parser.add_argument("--dry-run",
                            action="store_true",
                            help="Perform processing but don't write anything")

        parser.add_argument("--modules-kconfig-dst",
                            type=Path,
                            help="Destination for Zephyr 'modules/Kconfig.stm32' file")

        parser.add_argument("--destination",
                            type=Path,
                            default=default_root,
                            help=("Root of output hal_stm32 repository\n"
                                  "(THIS OPTION IS RESERVED FOR DEBUGGING)"))

        return parser.parse_args(argv)

    def __init__(self, argv=None):
        # Parse arguments
        args = HalAutogenerator._parse_args(argv)
        self.hal_repo_root: Path = args.hal_repo_root
        self.output_root: Path = args.destination
        self.dry_run: bool = args.dry_run
        self.zeph_mod_kconfig: Path = args.modules_kconfig_dst

        # Initialize logger
        self.logger = logging.getLogger(__name__)
        if args.verbose == 0:
            self.logger.setLevel(logging.WARNING)
        elif args.verbose == 1:
            self.logger.setLevel(logging.INFO)
        else:  # verbose >= 2
            self.logger.setLevel(logging.DEBUG)
        self.logger.addHandler(logging.StreamHandler())

        # Initialize Jinja
        self.env = Environment(trim_blocks=True,
                               lstrip_blocks=True,
                               loader=FileSystemLoader(SCRIPT_DIR))

        # Pre-compute pathes we will be using later
        self.stm32cube_dir = self.hal_repo_root / STM32CUBE_DIR

        # Find all series in source hal_stm32 repo
        def _is_series_folder(p: Path):
            return p.is_dir() and p.name.startswith("stm32")

        def _rel_to_root(p: Path):
            return p.relative_to(self.hal_repo_root)

        series_folders = sorted([p for p in self.stm32cube_dir.iterdir()
                                 if _is_series_folder(p)], key=lambda p: p.name)

        self.all_series = list(map(_rel_to_root, series_folders))
        """Sorted list of all series' folders, relative to repo root"""

    def _series_names(self, no_double_x=False):
        names = map(lambda p: p.name, self.all_series)
        if no_double_x:
            names = map(lambda s: s.replace("xx", "x"), names)
        return list(names)

    def _outpath(self, rpath: str | Path):
        """Get output path for relative path to root 'rpath'"""
        return self.output_root / rpath

    def _open(self, rpath: str | Path, mode):
        """Open 'rpath' for writing.

        During dry run, writing to the returned FD is a no-op.
        Otherwise, this function behaves exactly like open().

        Parameters:
            rpath: path relative to hal_stm32 repo root (str/Path)
            mode: file open mode (must be "w")

        Note:
            If they don't exist, parents of 'rpath' will be created.
        """
        if mode != "w":
            raise ValueError("self._open() can only be used for writes")

        if self.dry_run:
            return NullWriter()
        else:
            target_path = self._outpath(rpath)

            # Create parent directories of target
            # if they don't exist yet
            if not target_path.parent.exists():
                target_path.parent.mkdir(parents=True)

            return open(file=target_path, mode=mode)

    def _render_to(self, destination_rpath, template_name, **kwargs):
        """Renders Jinja template

        The following parameters are injected in addition to **kwargs:
            - current_year: the current year (from datetime.now())

        Parameters:
            template_name: name of the Jinja template file
            **kwargs: Jinja template parameters
        """
        template = self.env.get_template(template_name)
        rendering_result = template.render(current_year=datetime.now().year, **kwargs)
        with self._open(destination_rpath, "w") as fd:
            fd.write(rendering_result)

    def generate_series_list(self):
        self._render_to(SERIES_LIST_OUTPUT, SERIES_LIST_TEMPLATE,
                        series_name_list=self._series_names(no_double_x=True))

    def generate_zephyr_module_kconfig(self):
        # Make a list of driver Kconfig across all series.
        # Also keep track of which symbols have been remapped
        # to any given symbol (for documentation purposes).
        all_kconfig = set()
        all_drivers = []
        remap_info = {}  # [target] = set(drivers remapped to target)

        for serie_rpath in self.all_series:
            for d in HalDriver._parse_serie_drivers(self.hal_repo_root / serie_rpath):
                if d.is_ungated:  # We don't generate Kconfig for ungated drivers
                    continue

                if d.kconfig_symbol not in all_kconfig:
                    # NOTE: we don't use any series-specific info
                    # from HalDriver so it doesn't matter *which*
                    # series the object comes from.
                    all_drivers.append(d)
                    all_kconfig.add(d.kconfig_symbol)

                if d.name != d.true_name:
                    remaps = remap_info.get(d.name, set())
                    remaps.add(d.true_name)
                    remap_info[d.name] = remaps

        def _template_info_for_drv(drv: HalDriver):
            """Generates tuple consumed by Jinja template for provided driver"""
            description = []

            no_uds_name = drv.name.upper().replace("_", " ")
            type = drv.type.upper()
            ext = "Extended " if drv.extended else ""

            long_name = DRIVER_LONG_NAMES.get(drv.name)
            if long_name is None:
                self.logger.warning((f"Unknown long name for '{drv.name}'; "
                                     "please update script!"))

            # Handle UTIL-type module in a special way to make
            # the resulting symbol description more readable
            if type == "UTIL":
                description.append(
                    f"Enable STM32Cube {ext}{no_uds_name} utility functions module")
                # Ignore long name for utility function modules
            else:
                description.append(
                    f"Enable STM32Cube {ext}{type} {no_uds_name} driver module")
                if long_name is not None:
                    description.append(f"({long_name})")

            if remap_info.get(drv.name) is not None:
                gated_drivers = remap_info[drv.name]
                gated_drivers.add(drv.name)  # Add ourselves to gated drivers list
                description.append("")
                description.append("This option controls the following drivers:")
                for drv_name in sorted(gated_drivers):
                    description.append(f" - {drv_name.upper()}")

            return drv.kconfig_symbol, description

        drv_list = [_template_info_for_drv(drv) for drv in all_drivers]
        drv_list = sorted(drv_list, key=lambda e: e[0])

        self._render_to(self.zeph_mod_kconfig, MODULES_KCONFIG_TEMPLATE,
                        drivers=drv_list)

    def generate_stm32_assert_header(self):
        names = self._series_names()
        self._render_to(STM32_ASSERT_H_OUTPUT, STM32_ASSERT_H_TEMPLATE,
                        series_name_list=names)

    def foreach_serie(self, predicate):
        for serie_rpath in self.all_series:
            predicate(serie_rpath.name, serie_rpath)

    # The following functions are designed to be provided to foreach_serie()

    def _generate_one_serie_cmakelists(self, serie_name: str, serie_rpath: Path):
        all_drivers = HalDriver._parse_serie_drivers(self.hal_repo_root / serie_rpath)

        gated_drivers = list(filter(lambda d: not d.is_ungated, all_drivers))
        ungated_drivers = list(filter(lambda d: d.is_ungated, all_drivers))
        assert len(gated_drivers) + len(ungated_drivers) == len(all_drivers)

        def _pgd(d: HalDriver):
            """Pack gated driver (for consumption by Jinja template)"""
            return (d.kconfig_symbol, d.relative_path)

        # Create a sorted list mapping each driver file to its Kconfig symbol
        gated_drv_list = list(map(_pgd, gated_drivers))
        ungated_drv_list = list(map(lambda d: d.relative_path, ungated_drivers))

        self._render_to(serie_rpath / SERIES_CMAKELIST_OUTPUT,
                        SERIES_CMAKELIST_TEMPLATE,
                        serie_name=serie_name,
                        gated_drivers_list=gated_drv_list,
                        ungated_drivers_list=ungated_drv_list,
                        include_system=serie_name in CMSIS_SYSTEM_REQUIRED_SERIES)

    # Top-level generation logic

    def generate_everything(self):
        self.logger.info("Generating series list CMake helper...")
        self.generate_series_list()

        self.logger.info("Generating per-series CMakeLists.txt file...")
        self.foreach_serie(self._generate_one_serie_cmakelists)

        self.logger.info("Generating per-series stm32_assert.h file...")
        self.generate_stm32_assert_header()

        if self.zeph_mod_kconfig is not None:
            self.logger.info("Generating Zephyr modules Kconfig file...")
            self.generate_zephyr_module_kconfig()
            self.logger.info(
                f"Generated Zephyr modules Kconfig: {self.zeph_mod_kconfig}")
        else:
            self.logger.info(
                "Skipping Zephyr modules Kconfig generation (no output specified)")


if __name__ == "__main__":
    generator = HalAutogenerator()
    generator.generate_everything()
