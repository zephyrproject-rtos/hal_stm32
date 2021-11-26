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
import sys
import subprocess
import argparse
from pathlib import Path
import serie_update
import logging
from genllheaders import genllheaders

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
    "-r",
    "--repo",
    type=str,
    help="Allows to provide path where STM32Cube repo are stored",
)
parser.add_argument(
    "-v",
    "--version",
    default="",
    type=str,
    help="select to which version to update.\n",
)
parser.add_argument(
    "-d",
    "--debug",
    action="store_true",
    default=False,
    help="select to which version to update.\n",
)
args = parser.parse_args()

SCRIPT_DIR = Path(__file__).absolute().parent
"""Script directory."""

REPO_ROOT = SCRIPT_DIR / ".."
"""Repository root (used for input/output default folders)."""


def update_cubes():
    """Update all STM32Cubes"""
    module_path = REPO_ROOT / "stm32cube"
    if not module_path.exists():
        raise Exception("Error: cannot find ./zephyr project")

    for stmyyxx in module_path.iterdir():
        if stmyyxx.is_dir() and "common_ll" not in stmyyxx.name:
            logging.info(
                "%s",
                f"***************  updating module {stmyyxx.name} *****************",
            )
            # Force the commit for each serie
            update_serie = serie_update.Stm32SerieUpdate(
                stmyyxx.name[:-2],
                repo_path,
                noclean=args.noclean,
                debug=args.debug,
                version_update="",
            )
            update_serie.update_stm32_hal_serie()


################################################
# Main
################################################
if args.repo:
    repo_path = Path(args.repo)
else:
    repo_path = Path(os.getenv("HOME")) / "STM32Cube_repo"

if args.debug:
    print("Debug")
    logging.basicConfig(format="%(levelname)s:%(message)s", level=logging.DEBUG)
    std_dest = None
else:
    logging.basicConfig(format="%(levelname)s:%(message)s", level=logging.INFO)
    std_dest = subprocess.DEVNULL

if not args.noclean:
    print(
        f"Do you want to clean downloaded repo {str(repo_path)} at the end of updates?"
    )
    res = input("(Enter y/n) ").lower()
    while res not in ("y", "n"):
        res = input("(Enter y/n) ").lower()
    if res == "n":
        logging.info("%s", "Add option --noclean")
        args.noclean = True

# prevent losing data in an unclean repo
git_status = subprocess.check_output(
    ("git", "status", "-s"),
    cwd=SCRIPT_DIR,
).splitlines()
# status = [x.decode("utf-8") for x in git_status]
for status in git_status:
    if not status.decode("utf-8").startswith("?") and not status.decode(
        "utf-8"
    ).startswith("!"):
        logging.error(
            "%s",
            "It seems that script repo "
            + str(SCRIPT_DIR)
            + "\n           is not clean:\n           git status -s:"
            + status.decode("utf-8"),
        )
        logging.error("%s", "It is suggested to clean your repo first.")

        print("Do you want to continue update ?")
        res = input("(Enter y/n) ").lower()
        while res not in ("y", "n"):
            res = input("(Enter y/n) ").lower()
        if res == "n":
            sys.exit()
        break

if args.stm32_serie:
    update = serie_update.Stm32SerieUpdate(
        args.stm32_serie,
        repo_path,
        args.noclean,
        args.version,
        args.debug,
    )
    update.update_stm32_hal_serie()
else:
    update_cubes()

logging.info("%s", "Cube update: Done")

print("Do you want to autogenerate generic LL HAL headers (genllheaders.py) ?")
res = input("(Enter y/n) ").lower()
while res not in ("y", "n"):
    res = input("(Enter y/n) ").lower()
if res == "y":
    genllheaders.main(
        REPO_ROOT / "stm32cube",
        REPO_ROOT / "stm32cube" / "common_ll",
    )

    genllheaders.main(REPO_ROOT / "stm32cube", REPO_ROOT / "stm32cube" / "common_ll")

    # commit autogenerate generic LL HAL headers
    commit_file_path = REPO_ROOT / "commit.msg"
    with open(commit_file_path, "w") as commit:
        commit.write("stm32cube: common_ll: Regeneration after cube updates\n")
        commit.write("\n")
        commit.write("Re - generate common_ll headers after Cube updates\n")

    subprocess.check_call(
        ("git", "commit", "-as", "-F", commit_file_path),
        cwd=REPO_ROOT,
    )

    subprocess.check_call(
        ("git", "rebase", "--whitespace=fix", "HEAD~1"),
        stdout=std_dest,
        stderr=std_dest,
        cwd=REPO_ROOT,
    )
    Path(commit_file_path).unlink()

    logging.info("%s", "LL HAL header update: Done")
