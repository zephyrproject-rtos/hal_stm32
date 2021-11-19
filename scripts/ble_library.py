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
from jinja2 import Environment, FileSystemLoader
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


def create_ble_lib_readme(dest_lib_path, version, commit):
    """Create README for ble library """

    # prepare variables for jinja2 template
    extracted_file_list = ""
    for file in file_list:
        extracted_file_list = extracted_file_list + "     " + file + "\n"

    # Create file from Jinja2 template
    templates_dir = dest_lib_path / ".." / "scripts"
    j2_env = Environment(
        loader=FileSystemLoader(str(templates_dir)),
        trim_blocks=True,
        lstrip_blocks=True,
    )
    readme_j2_template = j2_env.get_template("ble_README_template.txt")
    readme_path = dest_lib_path / "stm32wb" / "hci" / "README"
    with open(readme_path, "w") as readme:
        readme.write(
            readme_j2_template.render(
                version=version,
                extracted_file_list=extracted_file_list,
                commit=commit,
            )
        )


def create_ble_lib_cmakelist(dest_lib_path):
    """Create CMakeLists.txt for ble library """
    # remove CMakeLists.txt file before re-creating it
    cmakelist_path = Path(dest_lib_path / "CMakeLists.txt")
    cmakelist_path.unlink()

    # prepare variables for jinja2 template
    include_dir_list = ""
    source_file_list = ""
    for directory in include_dir:
        include_dir_list = (
            f"{include_dir_list}    zephyr_include_directories({directory})\n"
        )
    for child in Path(dest_lib_path / "stm32wb" / "hci").iterdir():
        if child.is_file and child.suffix == ".c":
            source_file_list = (
                f"{source_file_list}    "
                + f"zephyr_sources(stm32wb/hci/{str(child.name)})\n"
            )

    # Create file from Jinja2 template
    templates_dir = dest_lib_path / ".." / "scripts"
    j2_env = Environment(
        loader=FileSystemLoader(str(templates_dir)),
        trim_blocks=True,
        lstrip_blocks=True,
    )
    cmakelists_j2_template = j2_env.get_template("ble_CMakeLists_template.txt")
    cmakelists_txt = dest_lib_path / "CMakeLists.txt"
    with open(cmakelists_txt, "w") as cmakelists:
        cmakelists.write(
            cmakelists_j2_template.render(
                include_dir_list=include_dir_list,
                source_file_list=source_file_list,
            )
        )


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
    create_ble_lib_readme(dest_lib_path, update_version, commit)
    create_ble_lib_cmakelist(dest_lib_path)


if __name__ == "__main__":
    print("This script is not intend to be called directly\n")
    print("It is used through serie_update.py\n")
    sys.exit()
