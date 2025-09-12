# Copyright (c) 2025 STMicroelectronics
#
# SPDX-License-Identifier: Apache-2.0
if (CONFIG_BT_STM32WBA)
zephyr_compile_definitions( -DBLE )
endif()

if (CONFIG_BT_STM32WBA)
zephyr_include_directories(ble/stack/include)
zephyr_include_directories(ble/stack/include/auto)
zephyr_include_directories(link_layer/ll_cmd_lib/config/ble_full)
endif()
zephyr_include_directories(inc)
zephyr_include_directories(link_layer/ll_cmd_lib/inc)
zephyr_include_directories(link_layer/ll_cmd_lib/inc/_40nm_reg_files)
zephyr_include_directories(link_layer/ll_sys/inc)

zephyr_sources(link_layer/ll_sys/src/ll_sys_cs.c)
zephyr_sources(link_layer/ll_sys/src/ll_sys_dp_slp.c)
zephyr_sources(link_layer/ll_sys/src/ll_sys_intf.c)
zephyr_sources(link_layer/ll_sys/src/ll_sys_startup.c)
