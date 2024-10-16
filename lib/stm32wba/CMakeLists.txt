# Copyright (c) 2024 STMicroelectronics
#
# SPDX-License-Identifier: Apache-2.0

if(DEFINED CONFIG_BOARD_NUCLEO_WBA52CG)
  message(FATAL_ERROR "BLE library is not compatible with nucleo_wba52cg")
endif()

zephyr_compile_definitions( -DBLE )

zephyr_include_directories(hci)
zephyr_include_directories(hci/ll)

zephyr_sources(hci/ll_sys_cs.c)
zephyr_sources(hci/ll_sys_intf.c)
zephyr_sources(hci/ll_sys_dp_slp.c)
zephyr_sources(hci/ll_sys_startup.c)
zephyr_sources(hci/RTDebug.c)
zephyr_sources(hci/hw_pka.c)
zephyr_sources(hci/pka_p256.c)
zephyr_sources(hci/bpka.c)
zephyr_sources(hci/power_table.c)
zephyr_sources(hci/scm.c)
zephyr_sources(hci/log_module.c)
zephyr_sources(hci/linklayer_plat.c)
zephyr_sources(hci/ll_sys_if.c)
if(CONFIG_FLASH)
  zephyr_sources(hci/flash_manager.c)
  zephyr_sources(hci/flash_driver.c)
  zephyr_sources(hci/stm_list.c)
  zephyr_sources(hci/rf_timing_synchro.c)
endif()

set(STM32WBA_BLE_LIB_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../../zephyr/blobs/stm32wba/lib)
set(STM32WBA_BLE_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/hci)

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

set_target_properties(stm32wba_ble_lib PROPERTIES INTERFACE_INCLUDE_DIRECTORIES ${STM32WBA_BLE_INCLUDE_DIR})
set_target_properties(stm32wba_ll_lib PROPERTIES INTERFACE_INCLUDE_DIRECTORIES ${STM32WBA_BLE_INCLUDE_DIR})

target_link_libraries(app PUBLIC stm32wba_ble_lib)
target_link_libraries(app PUBLIC stm32wba_ll_lib)
