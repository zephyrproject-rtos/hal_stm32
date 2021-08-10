"""
Utility to autogenerate generic LL HAL headers.

Usage::

    python3 genllheaders.py [-p /path/to/HAL] [-o /path/to/output_dir]

Copyright (c) 2020 Teslabs Engineering S.L.

SPDX-License-Identifier: Apache-2.0
"""

import argparse
import logging
from pathlib import Path
import re
import shutil

from jinja2 import Environment, FileSystemLoader


logger = logging.getLogger(__name__)


SCRIPT_DIR = Path(__file__).absolute().parent
"""Script directory."""

README_TEMPLATE_FILE = "readme-template.j2"
"""Readme template file."""

HEADER_TEMPLATE_FILE = "header-template.j2"
"""Header template file."""

REPO_ROOT = SCRIPT_DIR / ".." / ".."
"""Repository root (used for input/output default folders)."""

LL_API_IGNORE = ["usb"]
"""List of LL APIs to be ignored."""


def main(hal_path, output):
    """Entry point.

    Args:
        hal_path: Zephyr CubeMX HAL path.
        output: Output directory.
    """

    # obtain all available LL APIs for each series
    ll_apis = dict()
    versions = dict()
    for entry in sorted(hal_path.iterdir()):
        if not entry.is_dir() or not entry.name.startswith("stm32"):
            continue

        series = entry.name

        # collect version
        with open(entry / "README") as f:
            readme = f.read()
            m = re.search(r"version v?([0-9\.]+)", readme)
            if not m:
                logger.error(f"Could not determine version for {series}")
                continue

            versions[series] = m.group(1)

        # obtain series LL headers
        series_headers = entry / "drivers" / "include"
        for header in series_headers.iterdir():
            m = re.match(r"^stm32[a-z0-9]+_ll_([a-z0-9]+)\.h$", header.name)
            if not m:
                continue

            ll_api = m.group(1)

            if ll_api in LL_API_IGNORE:
                continue

            if ll_api not in ll_apis:
                ll_apis[ll_api] = list()
            ll_apis[ll_api].append(series)

    # write header files
    env = Environment(
        trim_blocks=True, lstrip_blocks=True, loader=FileSystemLoader(SCRIPT_DIR)
    )
    readme_template = env.get_template(README_TEMPLATE_FILE)
    header_template = env.get_template(HEADER_TEMPLATE_FILE)

    if output.exists():
        shutil.rmtree(output)
    output.mkdir(parents=True)

    readme_file = output / "README.rst"
    with open(readme_file, "w") as f:
        f.write(readme_template.render(versions=versions))

    output_headers = output / "include"
    output_headers.mkdir()

    for ll_api, all_series in ll_apis.items():
        header_file = output_headers / ("stm32_ll_" + ll_api + ".h")
        with open(header_file, "w") as f:
            f.write(header_template.render(ll_api=ll_api, all_series=all_series))


if __name__ == "__main__":
    parser = argparse.ArgumentParser()
    parser.add_argument(
        "-p",
        "--hal-path",
        type=Path,
        default=REPO_ROOT / "stm32cube",
        help="Zephyr CubeMX HAL path",
    )
    parser.add_argument(
        "-o",
        "--output",
        type=Path,
        default=REPO_ROOT / "stm32cube" / "common_ll",
        help="Output directory",
    )
    args = parser.parse_args()

    main(args.hal_path, args.output)
