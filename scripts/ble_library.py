#!/usr/bin/python
"""
SPDX-License-Identifier: Apache-2.0
Copyright (c) 2021 STMicroelectronics.
This script updates ble library
"""

import sys
import os
import shutil
from pathlib import Path
import logging
from jinja2 import Environment, FileSystemLoader

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


def copy_hci_files(src_repo_path, dest_lib_path):
    """Copy sources files from Cube Firmware to zephyr"""
    # remove existing *.c and *.h files
    for item in os.listdir(Path(dest_lib_path / "stm32wb" / "hci")):
        if item.endswith(".c") or item.endswith(".h"):
            os.remove(Path(dest_lib_path / "stm32wb" / "hci" / item))

    for file in file_list:
        file_path = Path(src_repo_path / file)
        file_name = file_path.name
        if file_path.exists:
            # copy each file to destination
            shutil.copy(file_path, Path(dest_lib_path / "stm32wb" / "hci" / file_name))
        else:
            logging.error(f"File : {file_path} not found")
            logging.error("Abort")
            sys.exit()


def apply_ble_patches(dest_lib_path):
    """Copy sources files from Cube Firmware to zephyr"""
    patch_file = str(dest_lib_path / "ble_zephyr.patch")

    # Apply patch
    cmd = (
        "git",
        "apply",
        "--recount",
        "--reject",
        patch_file,
    )
    ble_log_path = dest_lib_path / "ble_patch.log"
    with open(ble_log_path, "w") as output_log:
        if subprocess.call(cmd, stderr=output_log, cwd=dest_lib_path):
            logging.error(
                "##########################  "
                + "ERROR when applying ble library patch to zephyr: "
                + "###########################\n"
                + f"           see str(ble_log_path)\n"
                + f"patch file:{patch_file}"
            )

            # Print list of conflicting file
            conflict = "Potential merge conflict:\n"
            with open(str(ble_log_path), "r") as f:
                previous_conflict_file = ""
                for line in f:
                    if line.startswith("error: patch failed:"):
                        conflict_file = line.split(":")[2]
                        if conflict_file != previous_conflict_file:
                            previous_conflict_file = conflict_file
                            conflict = (
                                conflict + "                " + conflict_file + "\n"
                            )
            logging.error(conflict)


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
    for dir in include_dir:
        include_dir_list = f"{include_dir_list}    zephyr_include_directories({dir})\n"
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


def update(src_repo_path, dest_lib_path, version, commit):
    """Update ble library"""
    logging.info(" ... Updating ble library ...")
    copy_hci_files(src_repo_path, dest_lib_path)
    apply_ble_patches(dest_lib_path)
    create_ble_lib_readme(dest_lib_path, version, commit)
    create_ble_lib_cmakelist(dest_lib_path)


if __name__ == "__main__":
    print("This script is not intend to be called directly\n")
    print("It is used through serie_update.py\n")
    sys.exit()
