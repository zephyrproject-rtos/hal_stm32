#!/usr/bin/python
"""
SPDX-License-Identifier: Apache-2.0
Copyright (c) 2021 STMicroelectronics.
This script updates ble library
"""

import sys
import os
import shutil
import subprocess
from pathlib import Path
import logging
from common_utils import common_utils

include_dir = ["stm32wb/hci"]

file_list = [
    "Middlewares/ST/STM32_WPAN/ble/core/ble_bufsize.h",
    "Middlewares/ST/STM32_WPAN/interface/patterns/ble_thread/hw.h",
    "Middlewares/ST/STM32_WPAN/interface/patterns/ble_thread/shci/shci.c",
    "Middlewares/ST/STM32_WPAN/interface/patterns/ble_thread/shci/shci.h",
    "Middlewares/ST/STM32_WPAN/interface/patterns/ble_thread/tl/hci_tl.h",
    "Middlewares/ST/STM32_WPAN/interface/patterns/ble_thread/tl/mbox_def.h",
    "Middlewares/ST/STM32_WPAN/interface/patterns/ble_thread/tl/shci_tl_if.c",
    "Middlewares/ST/STM32_WPAN/interface/patterns/ble_thread/tl/shci_tl.c",
    "Middlewares/ST/STM32_WPAN/interface/patterns/ble_thread/tl/shci_tl.h",
    "Middlewares/ST/STM32_WPAN/interface/patterns/ble_thread/tl/tl.h",
    "Middlewares/ST/STM32_WPAN/interface/patterns/ble_thread/tl/tl_mbox.c",
    "Middlewares/ST/STM32_WPAN/stm32_wpan_common.h",
    "Middlewares/ST/STM32_WPAN/utilities/dbg_trace.h",
    "Middlewares/ST/STM32_WPAN/utilities/stm_list.c",
    "Middlewares/ST/STM32_WPAN/utilities/stm_list.h",
    "Middlewares/ST/STM32_WPAN/utilities/utilities_common.h",
    "Projects/P-NUCLEO-WB55.Nucleo/Applications/BLE/BLE_Hid/Core/Inc/app_common.h",
    "Projects/P-NUCLEO-WB55.Nucleo/Applications/BLE/BLE_Hid/Core/Inc/app_conf.h",
    "Projects/P-NUCLEO-WB55.Nucleo/Applications/BLE/BLE_Hid/Core/Inc/hw_if.h",
    "Projects/P-NUCLEO-WB55.Nucleo/Applications/BLE/BLE_Hid/STM32_WPAN/Target/"
    + "hw_ipcc.c",
    "Projects/P-NUCLEO-WB55.Nucleo/Applications/BLE/BLE_Hid/STM32_WPAN/App/"
    + "tl_dbg_conf.h",
]


def os_cmd(cmd, cwd=None, shell=False):
    """Execute a command with subprocess.check_call()
    Args:
        cmd: string command to execute.
        cwd: directory where to run command
        shell: boolean to enable command interpretation by the shell

    Returns:
        return the returncode of the command after execution.
    """
    logging.debug("%s", f"{str(cmd)}      cwd:{str(cwd)}")

    return subprocess.check_call(
        cmd,
        shell=shell,
        cwd=cwd,
        stdout=subprocess.DEVNULL,
        stderr=subprocess.DEVNULL,
    )


def copy_hci_files(src_repo_path, dest_lib_path):
    """Copy sources files from Cube Firmware to zephyr"""
    # remove existing *.c and *.h files
    hci_path = Path(dest_lib_path / "stm32wb" / "hci")
    if hci_path.exists():
        for item in os.listdir(hci_path):
            if item.endswith(".c") or item.endswith(".h"):
                os.remove(hci_path / item)

    for file in file_list:
        file_path = Path(src_repo_path / file)
        file_name = file_path.name
        if file_path.exists:
            # copy each file to destination
            if not Path(dest_lib_path / "stm32wb" / "hci" / file_name).parent.exists():
                Path(dest_lib_path / "stm32wb" / "hci" / file_name).parent.mkdir(
                    parents=True
                )
            shutil.copy(file_path, Path(dest_lib_path / "stm32wb" / "hci" / file_name))
        else:
            logging.error(f"File : {file_path} not found")
            logging.error("Abort")
            sys.exit()


def update_ble_lib_readme(lib_path, make_version, make_commit):
    """Update README file

    Args:
        dest_lib_path: library path
        make_version: latest STM32Cube version.
        make_commit: Commit corresponding to latest STM32Cube version.
    """

    readme_path = Path(lib_path / "stm32wb" / "hci" / "README")

    with readme_path.open(mode="r") as readme_prev:
        lines = (x for x in readme_prev.read().splitlines())

    readme_path.unlink()

    # Write README from previous one if exists
    with open(str(readme_path), "w") as readme_file:
        for LineItem in lines:
            # change version nb
            if "status" in LineItem.lower():
                readme_file.write("Status:\n")
                readme_file.write(f"   version {make_version}\n")
                next(lines)  # skip next line
            elif "commit" in LineItem.lower():
                readme_file.write("Commit:\n")
                readme_file.write(f"   {make_commit}")
                next(lines)  # skip next line
            # change patch list with a link to the release_note.html
            elif "Patch List" in LineItem:
                readme_file.write("Patch List:\n")
                readme_file.write(
                    "--> please check that the following list "
                    + "is still valid:\n"
                )
            else:
                readme_file.write(f"{LineItem}\n")

        readme_file.flush()


def build_patch_from_current_zephyr_version(
    src_repo_path, temp_source_path, zephyr_lib_path, version
):
    """ Rebuild zephyr patch compare to cube files (current zephyr version) """

    temp_source_lib_path = Path(temp_source_path / "lib")

    # reset the STM32Cube repo to this current version
    os_cmd(
        ("git", "reset", "--hard", version),
        cwd=src_repo_path,
    )

    # create Cube reference from zephyr version
    shutil.rmtree(temp_source_path, onerror=common_utils.remove_readonly)
    temp_source_lib_path.mkdir(parents=True)

    copy_hci_files(
        src_repo_path,
        temp_source_lib_path,
    )
    os_cmd(("git", "init"), cwd=temp_source_path)
    os_cmd(
        ("git", "commit", "--allow-empty", "-m", "'Trigger notification'"),
        cwd=temp_source_path,
    )
    os_cmd(
        ("git", "add", "-A", Path(temp_source_lib_path / "*")),
        cwd=temp_source_path,
    )
    os_cmd(
        ("git", "commit", "-am", "ble lib from zephyr version"),
        cwd=temp_source_path,
    )

    # Remove trailing whitespaces
    os_cmd(
        ("git", "rebase", "--whitespace=fix", "HEAD~1"),
        cwd=temp_source_path,
    )

    # copy zephyr files
    shutil.rmtree(temp_source_lib_path, onerror=common_utils.remove_readonly)
    shutil.copytree(zephyr_lib_path, temp_source_lib_path)

    # remove all files at root dir (like readme and cmakelist)
    # so that it is not part of the patch
    for file in temp_source_lib_path.glob("*"):
        if file.is_file():
            file.unlink()
    Path(temp_source_lib_path / "stm32wb" / "hci" / "README").unlink()

    # commit this current zephyr library file
    os_cmd(("git", "add", "*"), cwd=temp_source_path)
    os_cmd(("git", "commit", "-am", '"module"'), cwd=temp_source_path)

    # Remove trailing space
    os_cmd(
        ("git", "rebase", "--whitespace=fix", "HEAD~1"),
        cwd=temp_source_path,
    )

    # For unclear reason, using tuple ("git", "diff", ...) is failing on Linux
    # especially for this command. Keep a single string.
    os_cmd(
        (
            "git diff --ignore-space-at-eol HEAD~1 --output="
            + str(zephyr_lib_path)
            + "/ble_zephyr.patch"
        ),
        shell=True,
        cwd=temp_source_path,
    )
    os_cmd(("dos2unix", "ble_zephyr.patch"), cwd=zephyr_lib_path)


def update(
    src_repo_path,
    dest_lib_path,
    temp_source_path,
    current_version,
    update_version,
    commit,
):
    """Update ble library"""
    logging.info(" ... Updating ble library ...")
    build_patch_from_current_zephyr_version(
        src_repo_path, temp_source_path, dest_lib_path, current_version
    )
    # reset the STM32Cube repo to this update version
    os_cmd(
        ("git", "reset", "--hard", update_version),
        cwd=src_repo_path,
    )
    copy_hci_files(src_repo_path, dest_lib_path)
    common_utils.apply_patch(dest_lib_path / "ble_zephyr.patch", dest_lib_path)
    update_ble_lib_readme(dest_lib_path, update_version, commit)


if __name__ == "__main__":
    print("This script is not intend to be called directly\n")
    print("It is used through serie_update.py\n")
    sys.exit()
