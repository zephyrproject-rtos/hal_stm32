# Copyright (c) 2024 STMicroelectronics
#
# SPDX-License-Identifier: Apache-2.0

if(DEFINED CONFIG_BOARD_NUCLEO_WBA52CG)
  message(FATAL_ERROR "BLE library is not compatible with nucleo_wba52cg")
endif()

zephyr_compile_definitions( -DBLE )

zephyr_include_directories(BLE_TransparentMode/Core/Inc)
zephyr_include_directories(BLE_TransparentMode/STM32_WPAN/Target)
zephyr_include_directories(BLE_TransparentMode/System/Config/Debug_GPIO)
zephyr_include_directories(BLE_TransparentMode/System/Config/Log)
zephyr_include_directories(BLE_TransparentMode/System/Interfaces)
zephyr_include_directories(BLE_TransparentMode/System/Modules)
zephyr_include_directories(BLE_TransparentMode/System/Modules/Flash)
zephyr_include_directories(BLE_TransparentMode/System/Modules/RTDebug)
zephyr_include_directories(STM32_WPAN)
zephyr_include_directories(STM32_WPAN/ble/stack/include)
zephyr_include_directories(STM32_WPAN/ble/stack/include/auto)
zephyr_include_directories(STM32_WPAN/link_layer/ll_cmd_lib/config/ble_full)
zephyr_include_directories(STM32_WPAN/link_layer/ll_cmd_lib/inc)
zephyr_include_directories(STM32_WPAN/link_layer/ll_cmd_lib/inc/_40nm_reg_files)
zephyr_include_directories(STM32_WPAN/link_layer/ll_sys/inc)
zephyr_include_directories(Utilities/misc)
zephyr_include_directories(Utilities/tim_serv)
zephyr_include_directories(Utilities/trace/adv_trace)

zephyr_sources(BLE_TransparentMode/STM32_WPAN/Target/bpka.c)
zephyr_sources(BLE_TransparentMode/STM32_WPAN/Target/linklayer_plat.c)
zephyr_sources(BLE_TransparentMode/STM32_WPAN/Target/ll_sys_if.c)
zephyr_sources(BLE_TransparentMode/STM32_WPAN/Target/power_table.c)
zephyr_sources(BLE_TransparentMode/System/Config/Log/log_module.c)
zephyr_sources(BLE_TransparentMode/System/Interfaces/hw_pka.c)
zephyr_sources(BLE_TransparentMode/System/Interfaces/hw_pka_p256.c)
zephyr_sources(BLE_TransparentMode/System/Modules/scm.c)
zephyr_sources(BLE_TransparentMode/System/Modules/RTDebug/RTDebug.c)
zephyr_sources(STM32_WPAN/link_layer/ll_sys/src/ll_sys_cs.c)
zephyr_sources(STM32_WPAN/link_layer/ll_sys/src/ll_sys_dp_slp.c)
zephyr_sources(STM32_WPAN/link_layer/ll_sys/src/ll_sys_intf.c)
zephyr_sources(STM32_WPAN/link_layer/ll_sys/src/ll_sys_startup.c)

if(CONFIG_FLASH)
  zephyr_sources(BLE_TransparentMode/System/Modules/Flash/flash_manager.c)
  zephyr_sources(BLE_TransparentMode/System/Modules/Flash/flash_driver.c)
  zephyr_sources(BLE_TransparentMode/System/Modules/stm_list.c)
  zephyr_sources(BLE_TransparentMode/System/Modules/Flash/rf_timing_synchro.c)
endif()

set(STM32WBA_BLE_LIB_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../../zephyr/blobs/stm32wba/lib)
set(STM32WBA_BLE_LIB_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/STM32_WPAN/ble/stack)
set(STM32WBA_LL_LIB_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/STM32_WPAN/link_layer/ll_cmd_lib)

add_library(stm32wba_ble_lib STATIC IMPORTED GLOBAL)
add_library(stm32wba_ll_lib STATIC IMPORTED GLOBAL)

add_dependencies(
  stm32wba_ble_lib
  stm32wba_ll_lib
)
set_target_properties(
  stm32wba_ble_lib PROPERTIES IMPORTED_LOCATION ${STM32WBA_BLE_LIB_DIR}/stm32wba_ble_stack_llo.a
)
set_target_properties(
  stm32wba_ll_lib PROPERTIES IMPORTED_LOCATION ${STM32WBA_BLE_LIB_DIR}/LinkLayer_BLE_Full_lib.a
)

set_target_properties(stm32wba_ble_lib PROPERTIES INTERFACE_INCLUDE_DIRECTORIES ${STM32WBA_BLE_LIB_INCLUDE_DIR})
set_target_properties(stm32wba_ll_lib PROPERTIES INTERFACE_INCLUDE_DIRECTORIES ${STM32WBA_LL_LIB_INCLUDE_DIR})

target_link_libraries(app PUBLIC stm32wba_ble_lib)
target_link_libraries(app PUBLIC stm32wba_ll_lib)
