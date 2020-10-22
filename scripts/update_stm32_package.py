#!/usr/bin/python
"""
SPDX-License-Identifier: Apache-2.0
Copyright (c) 2019 STMicroelectronics.
This script will update the stm32cube module for Zephyr
from the latest version on https://github.com/STMicroelectronics
get the patch between initial version and latest version
apply this patch on the zephyr module
basic usage for a single serie update :
   'python3 update_stm32_package.py -s <stm32_serie>'
basic usage for all serie update at once:
   'python3 update_stm32_package.py
"""

import os
import subprocess
import argparse
from pathlib import Path
import serie_update
import logging

logging.basicConfig(level=logging.INFO)

parser = argparse.ArgumentParser()
parser.add_argument(
    "-s",
    "--stm32_serie",
    type=str,
    help="Update a stm32 serie. ex: stm32f1.\n"
    + "If omitted all STM32 series will be updated,\n"
    + "a commit is created for each serie. ",
)
parser.add_argument(
    "-c",
    "--noclean",
    action="store_true",
    default=False,
    help="Do NOT clean the STM32Cube repo directory",
)
parser.add_argument(
    "-f",
    "--force",
    action="store_true",
    default=False,
    help="Forces the merge except .rej files \n"
    + "applicable only with -s option. "
    + "Otrherwise merge is forced systematically "
    + "for each serie",
)
parser.add_argument(
    "-r",
    "--repo",
    type=str,
    help="Allows to provide path where STM32Cube repo " + "are stored",
)
args = parser.parse_args()


def update_cubes():
    """Update all STM32Cubes"""
    module_path = (
        Path(os.getenv("ZEPHYR_BASE")).absolute()
        / r".."
        / "modules"
        / "hal"
        / "stm32"
        / "stm32cube"
    )
    if not module_path.exists():
        raise Exception("Error: cannot find ./zephyr project")

    for stmyyxx in module_path.iterdir():
        if stmyyxx.is_dir():
            logging.info("updating module " + stmyyxx.name)
            # Force the commit for each serie
            update_serie = serie_update.Stm32SerieUpdate(
                stmyyxx.name[:-2], repo_path, force=True, noclean=args.noclean
            )
            update_serie.update_stm32_hal_serie()


################################################
# Main
################################################
if args.repo:
    repo_path = Path(args.repo)
else:
    repo_path = Path(os.getenv("HOME")) / "STM32Cube_repo"

if args.stm32_serie:
    update = serie_update.Stm32SerieUpdate(
        args.stm32_serie, repo_path, args.force, args.noclean
    )
    update.update_stm32_hal_serie()
else:
    update_cubes()

logging.info("The end")
