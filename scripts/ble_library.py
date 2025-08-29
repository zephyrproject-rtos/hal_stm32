#!/usr/bin/python
"""
SPDX-License-Identifier: Apache-2.0
Copyright (c) 2024 STMicroelectronics.
This script updates ble library
"""

import sys
import os
import shutil
import subprocess
from pathlib import Path
import logging
from common_utils import common_utils

file_list_wb = [
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

ble_transparent_mode_app_path = "Projects/NUCLEO-WBA65RI/Applications/BLE/" \
                                + "BLE_TransparentMode"
file_list_wba = {
    "STM32_WPAN": [
        "Middlewares/ST/STM32_WPAN/ble/stack/include/auto/ble_types.h",
        "Middlewares/ST/STM32_WPAN/link_layer/ll_cmd_lib/inc/_40nm_reg_files/"
        + "DWC_ble154combo.h",
        "Middlewares/ST/STM32_WPAN/link_layer/ll_cmd_lib/inc/bsp.h",
        "Middlewares/ST/STM32_WPAN/link_layer/ll_cmd_lib/inc/common_types.h",
        "Middlewares/ST/STM32_WPAN/link_layer/ll_cmd_lib/inc/event_manager.h",
        "Middlewares/ST/STM32_WPAN/link_layer/ll_cmd_lib/inc/evnt_schdlr_gnrc_if.h",
        "Middlewares/ST/STM32_WPAN/link_layer/ll_cmd_lib/inc/hci.h",
        "Middlewares/ST/STM32_WPAN/link_layer/ll_cmd_lib/inc/ll_intf.h",
        "Middlewares/ST/STM32_WPAN/link_layer/ll_cmd_lib/inc/ll_intf_cmn.h",
        "Middlewares/ST/STM32_WPAN/link_layer/ll_cmd_lib/inc/mem_intf.h",
        "Middlewares/ST/STM32_WPAN/link_layer/ll_cmd_lib/inc/os_wrapper.h",
        "Middlewares/ST/STM32_WPAN/link_layer/ll_cmd_lib/inc/power_table.h",
        "Middlewares/ST/STM32_WPAN/link_layer/ll_cmd_lib/inc/pta.h",
        "Middlewares/ST/STM32_WPAN/link_layer/ll_cmd_lib/config/ble_full/"
        + "ll_fw_config.h",
        "Middlewares/ST/STM32_WPAN/ble/stack/include/ble_bufsize.h",
        "Middlewares/ST/STM32_WPAN/ble/stack/include/ble_const.h",
        "Middlewares/ST/STM32_WPAN/ble/stack/include/ble_defs.h",
        "Middlewares/ST/STM32_WPAN/ble/stack/include/ble_std.h",
        "Middlewares/ST/STM32_WPAN/ble/stack/include/bleplat.h",
        "Middlewares/ST/STM32_WPAN/ble/stack/include/blestack.h",
        "Middlewares/ST/STM32_WPAN/link_layer/ll_sys/inc/linklayer_plat.h",
        "Middlewares/ST/STM32_WPAN/link_layer/ll_sys/inc/ll_sys.h",
        "Middlewares/ST/STM32_WPAN/link_layer/ll_sys/src/ll_sys_cs.c",
        "Middlewares/ST/STM32_WPAN/link_layer/ll_sys/src/ll_sys_dp_slp.c",
        "Middlewares/ST/STM32_WPAN/link_layer/ll_sys/src/ll_sys_intf.c",
        "Middlewares/ST/STM32_WPAN/link_layer/ll_sys/src/ll_sys_startup.c",
        "Middlewares/ST/STM32_WPAN/link_layer/ll_sys/inc/ll_sys_startup.h",
        "Middlewares/ST/STM32_WPAN/stm32_wpan_common.h",
    ],
    "BLE_TransparentMode": [
        ble_transparent_mode_app_path + "/Core/Inc/app_common.h",
        ble_transparent_mode_app_path + "/Core/Inc/app_conf.h",
        ble_transparent_mode_app_path + "/Core/Inc/app_entry.h",
        ble_transparent_mode_app_path + "/Core/Inc/utilities_conf.h",
        ble_transparent_mode_app_path + "/Core/Inc/main.h",
        ble_transparent_mode_app_path + "/System/Config/Debug_GPIO/app_debug.h",
        ble_transparent_mode_app_path + "/System/Config/Debug_GPIO/debug_config.h",
        ble_transparent_mode_app_path + "/STM32_WPAN/Target/power_table.c",
        ble_transparent_mode_app_path + "/STM32_WPAN/Target/bpka.c",
        ble_transparent_mode_app_path + "/STM32_WPAN/Target/bpka.h",
        ble_transparent_mode_app_path + "/STM32_WPAN/Target/linklayer_plat.c",
        ble_transparent_mode_app_path + "/STM32_WPAN/Target/ll_sys_if.c",
        ble_transparent_mode_app_path + "/STM32_WPAN/Target/ll_sys_if.h",
    ],
    "Common": [
        "Projects/Common/WPAN/Modules/Flash/rf_timing_synchro.c",
        "Projects/Common/WPAN/Modules/Flash/rf_timing_synchro.h",
        "Projects/Common/WPAN/Modules/Flash/flash_driver.c",
        "Projects/Common/WPAN/Modules/Flash/flash_driver.h",
        "Projects/Common/WPAN/Modules/Flash/flash_manager.c",
        "Projects/Common/WPAN/Modules/Flash/flash_manager.h",
        "Projects/Common/WPAN/Modules/RTDebug/debug_signals.h",
        "Projects/Common/WPAN/Modules/RTDebug/RTDebug.c",
        "Projects/Common/WPAN/Modules/RTDebug/RTDebug.h",
        "Projects/Common/WPAN/Modules/RTDebug/local_debug_tables.h",
        "Projects/Common/WPAN/Modules/stm_list.c",
        "Projects/Common/WPAN/Modules/stm_list.h",
        "Projects/Common/WPAN/Modules/utilities_common.h",
        "Projects/Common/WPAN/Interfaces/hw.h",
        "Projects/Common/WPAN/Interfaces/hw_aes.c",
        "Projects/Common/WPAN/Interfaces/hw_if.h",
        "Projects/Common/WPAN/Interfaces/hw_pka.c",
        "Projects/Common/WPAN/Interfaces/hw_pka_p256.c",
        "Projects/Common/WPAN/Modules/Log/log_module.c",
        "Projects/Common/WPAN/Modules/Log/log_module.h",
    ],
    "Utilities": [
        "Utilities/trace/adv_trace/stm32_adv_trace.h",
        "Utilities/misc/stm32_mem.h",
        "Utilities/tim_serv/stm32_timer.h",
        "Utilities/misc/stm32_tiny_vsnprintf.h",
    ],
}


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


def copy_ble_lib_files(src_repo_path, dest_lib_path, stm32_serie):
    """Copy BLE lib related files from Cube Firmware to hal_stm32"""
    if stm32_serie == "stm32wb":
        # Remove existing *.c and *.h files
        hci_path = Path(dest_lib_path / "hci")
        if hci_path.exists():
            for item in os.listdir(hci_path):
                if item.endswith(".c") or item.endswith(".h"):
                    os.remove(hci_path / item)

        # Create hci folder if does not exist
        if not hci_path.exists():
            hci_path.mkdir(parents=True)

        # Copy files
        for file in file_list_wb:
            src_file_path = Path(src_repo_path / file)
            file_name = src_file_path.name
            if src_file_path.exists():
                # copy each file to destination
                shutil.copy(src_file_path, Path(hci_path / file_name))
            else:
                logging.error(f"File : {src_file_path} not found")
                logging.error("Abort")
                sys.exit()

    elif stm32_serie == "stm32wba":
        # Remove existing *.c and *.h files
        for root, _, files in os.walk(dest_lib_path):
            for file in files:
                if file.endswith(".c") or file.endswith(".h"):
                    os.remove(os.path.join(root, file))

        for dir_name in file_list_wba:
            for file in file_list_wba[dir_name]:
                # Src file path to be copied
                src_file_path = Path(src_repo_path / file)
                if src_file_path.exists():
                    # Extract the relevant part of the path from "dir_name" onwards
                    start_index = file.find(dir_name)
                    relative_path = file[start_index:]
                    # Create the full destination path
                    destination_path = os.path.join(dest_lib_path, relative_path)
                    # Create (if does not exist) all directories in the destination path
                    os.makedirs(os.path.dirname(destination_path), exist_ok=True)
                    # Copy the file to the destination path
                    shutil.copy(src_file_path, destination_path)
                else:
                    # Raise all the errors but not aborting to allow a manual check
                    logging.error(f"File : {src_file_path} not found")


def update_ble_lib_readme(lib_path, make_version, make_commit):
    """Update README.rst file

    Args:
        dest_lib_path: library path
        make_version: latest STM32Cube version.
        make_commit: Commit corresponding to latest STM32Cube version.
    """

    readme_path = Path(lib_path / "README.rst")

    with readme_path.open(mode="r") as readme_prev:
        lines = (x for x in readme_prev.read().splitlines())

    readme_path.unlink()

    # Write README.rst from previous one if exists
    with open(str(readme_path), "w") as readme_file:
        for line_item in lines:
            # change version nb
            if "status" in line_item.lower():
                readme_file.write("Status:\n")
                readme_file.write(f"   version {make_version}\n")
                next(lines)  # skip next line
            elif "commit" in line_item.lower():
                readme_file.write("Commit:\n")
                readme_file.write(f"   {make_commit}")
                next(lines)  # skip next line
            # change patch list with a link to the release_note.html
            elif "Patch List" in line_item:
                readme_file.write("Patch List:\n")
                readme_file.write(
                    "--> please check that the following list "
                    + "is still valid:\n"
                )
            else:
                readme_file.write(f"{line_item}\n")

        readme_file.flush()


def build_patch_from_current_zephyr_version(
    src_repo_path, temp_source_path, zephyr_lib_path, version, stm32_serie
):
    """ Rebuild zephyr patch compare to cube files (current zephyr version) """

    temp_source_lib_path = Path(temp_source_path / "lib" / stm32_serie)

    # Checkout the current Zephyr version of the STM32Cube repo
    os_cmd(
        ("git", "checkout", "-f", "--recurse-submodules", version),
        cwd=src_repo_path,
    )

    # create Cube reference from zephyr version
    shutil.rmtree(temp_source_path, onerror=common_utils.remove_readonly)
    temp_source_lib_path.mkdir(parents=True)

    copy_ble_lib_files(
        src_repo_path,
        temp_source_lib_path,
        stm32_serie,
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
    if Path(temp_source_lib_path / "README.rst").exists():
        Path(temp_source_lib_path / "README.rst").unlink()

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
    stm32_serie
):
    """Update ble library"""
    logging.info(" ... Updating ble library ...")
    if not dest_lib_path.exists():
        dest_lib_path.mkdir(parents=True)

    build_patch_from_current_zephyr_version(
        src_repo_path, temp_source_path, dest_lib_path, current_version,
        stm32_serie
    )
    # Checkout the latest version of the STM32Cube repo
    os_cmd(
        ("git", "checkout", "-f", "--recurse-submodules", update_version),
        cwd=src_repo_path,
    )
    copy_ble_lib_files(src_repo_path, dest_lib_path, stm32_serie)
    common_utils.apply_patch(dest_lib_path / "ble_zephyr.patch", dest_lib_path)
    if Path(dest_lib_path / "README.rst").exists():
        update_ble_lib_readme(dest_lib_path, update_version, commit)


if __name__ == "__main__":
    print("This script is not intend to be called directly\n")
    print("It is used through serie_update.py\n")
    sys.exit()
