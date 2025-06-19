# Copyright (c) 2024 STMicroelectronics
#
# SPDX-License-Identifier: Apache-2.0

zephyr_compile_definitions( -DBLE )

zephyr_include_directories(BLE_TransparentMode/Core/Inc)
zephyr_include_directories(BLE_TransparentMode/STM32_WPAN/Target)
zephyr_include_directories(BLE_TransparentMode/System/Config/Debug_GPIO)
zephyr_include_directories(BLE_TransparentMode/System/Config/Log)
zephyr_include_directories(Common/WPAN/Interfaces)
zephyr_include_directories(Common/WPAN/Modules)
zephyr_include_directories(Common/WPAN/Modules/Flash)
zephyr_include_directories(Common/WPAN/Modules/RTDebug)
zephyr_include_directories(Common/WPAN/Modules/Log)
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
zephyr_sources(Common/WPAN/Modules/Log/log_module.c)
zephyr_sources(Common/WPAN/Interfaces/hw_pka.c)
zephyr_sources(Common/WPAN/Interfaces/hw_pka_p256.c)
zephyr_sources(Common/WPAN/Modules/RTDebug/RTDebug.c)
zephyr_sources(STM32_WPAN/link_layer/ll_sys/src/ll_sys_cs.c)
zephyr_sources(STM32_WPAN/link_layer/ll_sys/src/ll_sys_dp_slp.c)
zephyr_sources(STM32_WPAN/link_layer/ll_sys/src/ll_sys_intf.c)
zephyr_sources(STM32_WPAN/link_layer/ll_sys/src/ll_sys_startup.c)

if(CONFIG_FLASH)
  zephyr_sources(Common/WPAN/Modules/Flash/flash_manager.c)
  zephyr_sources(Common/WPAN/Modules/Flash/flash_driver.c)
  zephyr_sources(Common/WPAN/Modules/stm_list.c)
  zephyr_sources(Common/WPAN/Modules/Flash/rf_timing_synchro.c)
endif()

if (CONFIG_BT_EXT_ADV
    OR (CONFIG_BT_PER_ADV OR CONFIG_BT_PER_ADV_SYNC)
    OR CONFIG_BT_SCA_UPDATE
    OR (CONFIG_BT_DF_CTE_RX_AOA OR CONFIG_BT_CTLR_DF_ANT_SWITCH_RX OR CONFIG_BT_CTLR_DF_ANT_SWITCH_TX OR CONFIG_BT_DF_CTE_TX_AOD)
    OR (CONFIG_BT_PER_ADV_SYNC_TRANSFER_RECEIVER OR CONFIG_BT_PER_ADV_SYNC_TRANSFER_SENDER OR CONFIG_BT_CTLR_SYNC_PERIODIC)
    OR CONFIG_BT_ISO_UNICAST
    OR CONFIG_BT_ISO_BROADCASTER
    OR CONFIG_BT_ISO_SYNC_RECEIVER
    OR CONFIG_BT_TRANSMIT_POWER_CONTROL
    OR CONFIG_BT_SUBRATING
    OR CONFIG_BT_CTLR_ADV_PERIODIC_ADI_SUPPORT
    OR CONFIG_BT_EXT_ADV_CODING_SELECTION)
  message(STATUS "link layer FULL lib selected")
  set(BLE_LIB_TYPE "BLE_LIB_FULL")
else()
  message(STATUS "link layer BASIC lib selected")
  set(BLE_LIB_TYPE "BLE_LIB_BASIC")
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
if (BLE_LIB_TYPE STREQUAL "BLE_LIB_BASIC")
  set_target_properties(
    stm32wba_ble_lib PROPERTIES IMPORTED_LOCATION ${STM32WBA_BLE_LIB_DIR}/stm32wba_ble_stack_llobasic.a
  )
elseif (BLE_LIB_TYPE STREQUAL "BLE_LIB_FULL")
  set_target_properties(
    stm32wba_ble_lib PROPERTIES IMPORTED_LOCATION ${STM32WBA_BLE_LIB_DIR}/stm32wba_ble_stack_llo.a
  )
endif()

# Setting the right Cube define according to the Zephyr configuration
if(NOT CONFIG_BT_STM32WBA_USE_TEMP_BASED_CALIB)
  zephyr_compile_definitions( -DUSE_TEMPERATURE_BASED_RADIO_CALIBRATION=0 )
endif()

# Selecting the proper version of link layer lib according the soc
# Checking all the soc variants and not simply relying on board name 

if(CONFIG_SOC_STM32WBA65XX)
  message(STATUS "STM32WBA6 link layer lib selected")
  if (BLE_LIB_TYPE STREQUAL "BLE_LIB_BASIC")
    set(LL_LIB "WBA6_LinkLayer_BLE_Basic_lib.a")
  elseif (BLE_LIB_TYPE STREQUAL "BLE_LIB_FULL")
    set(LL_LIB "WBA6_LinkLayer_BLE_Full_lib.a")
  endif()
endif()

if(CONFIG_SOC_STM32WBA55XX OR SOC_STM32WBA52XX)
  message(STATUS "STM32WBA5 link layer lib selected")
  if (BLE_LIB_TYPE STREQUAL "BLE_LIB_BASIC")
    set(LL_LIB "LinkLayer_BLE_Basic_lib.a")
  elseif (BLE_LIB_TYPE STREQUAL "BLE_LIB_FULL")
    set(LL_LIB "LinkLayer_BLE_Full_lib.a")
  endif()
endif()

# Using the selected version of link layer lib
set_target_properties(stm32wba_ll_lib PROPERTIES IMPORTED_LOCATION ${STM32WBA_BLE_LIB_DIR}/${LL_LIB})
set_target_properties(stm32wba_ble_lib PROPERTIES INTERFACE_INCLUDE_DIRECTORIES ${STM32WBA_BLE_LIB_INCLUDE_DIR})
set_target_properties(stm32wba_ll_lib PROPERTIES INTERFACE_INCLUDE_DIRECTORIES ${STM32WBA_LL_LIB_INCLUDE_DIR})

target_link_libraries(app PUBLIC stm32wba_ble_lib)
target_link_libraries(app PUBLIC stm32wba_ll_lib)
