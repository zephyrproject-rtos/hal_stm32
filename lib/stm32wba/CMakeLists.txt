# Copyright (c) 2025 STMicroelectronics
#
# SPDX-License-Identifier: Apache-2.0
zephyr_include_directories(Common/WPAN/Interfaces)
zephyr_include_directories(Common/WPAN/Modules)
zephyr_include_directories(Common/WPAN/Modules/Flash)
zephyr_include_directories(Common/WPAN/Modules/RTDebug)
zephyr_include_directories(Common/WPAN/Modules/Log)
if(CONFIG_IEEE802154_STM32WBA)
  zephyr_include_directories(Common/WPAN/Modules/BasicAES)
endif()
zephyr_include_directories(Utilities/misc)
zephyr_include_directories(Utilities/tim_serv)
zephyr_include_directories(Utilities/trace/adv_trace)
zephyr_include_directories(STM32_WPAN)

zephyr_sources(Common/WPAN/Modules/Log/log_module.c)
zephyr_sources(Common/WPAN/Interfaces/hw_pka.c)
zephyr_sources(Common/WPAN/Interfaces/hw_pka_p256.c)
zephyr_sources(Common/WPAN/Modules/RTDebug/RTDebug.c)

if(CONFIG_FLASH)
  zephyr_sources(Common/WPAN/Modules/Flash/flash_manager.c)
  zephyr_sources(Common/WPAN/Modules/Flash/flash_driver.c)
  zephyr_sources(Common/WPAN/Modules/stm_list.c)
  zephyr_sources(Common/WPAN/Modules/Flash/rf_timing_synchro.c)
endif()

if(CONFIG_IEEE802154_STM32WBA)
  zephyr_sources(Common/WPAN/Modules/BasicAES/baes_ccm.c)
  zephyr_sources(Common/WPAN/Modules/BasicAES/baes_cmac.c)
  zephyr_sources(Common/WPAN/Modules/BasicAES/baes_ecb.c)
  zephyr_sources(Common/WPAN/Interfaces/hw_aes.c)
endif()

set(STM32WBA_LIB_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../../zephyr/blobs/stm32wba/lib)

# select the type of BLE library
if(CONFIG_BT_STM32WBA)
  if(CONFIG_BT_EXT_ADV
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

  set(STM32WBA_BLE_LIB_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/STM32_WPAN/ble/stack)

  add_library(stm32wba_ble_lib STATIC IMPORTED GLOBAL)

  add_dependencies(
    stm32wba_ble_lib
    stm32wba_ll_lib
  )
  if(BLE_LIB_TYPE STREQUAL "BLE_LIB_BASIC")
    set_target_properties(
      stm32wba_ble_lib PROPERTIES IMPORTED_LOCATION ${STM32WBA_LIB_DIR}/stm32wba_ble_stack_llobasic.a
    )
  elseif(BLE_LIB_TYPE STREQUAL "BLE_LIB_FULL")
    set_target_properties(
      stm32wba_ble_lib PROPERTIES IMPORTED_LOCATION ${STM32WBA_LIB_DIR}/stm32wba_ble_stack_llo.a
    )
  endif()

  # Setting the right Cube define according to the Zephyr configuration
  if(NOT CONFIG_BT_STM32WBA_USE_TEMP_BASED_CALIB)
    zephyr_compile_definitions( -DUSE_TEMPERATURE_BASED_RADIO_CALIBRATION=0 )
  endif()

  # Using the selected version of ble lib
  set_target_properties(stm32wba_ble_lib PROPERTIES INTERFACE_INCLUDE_DIRECTORIES ${STM32WBA_BLE_LIB_INCLUDE_DIR})

  target_link_libraries(app PUBLIC stm32wba_ble_lib)
endif()

# Distinguish STM32WBA6x from STM32WBA5x lines
if(CONFIG_SOC_STM32WBA65XX)
  set(libname_prefix "WBA6_")
elseif(CONFIG_SOC_STM32WBA55XX OR CONFIG_SOC_STM32WBA52XX)
  set(libname_prefix "")
else()
  message(FATAL_ERROR "Unsupported SoC: ${CONFIG_SOC}")
endif()

# Selecting the proper version of link layer lib and its associated configuration header file
if(CONFIG_BT_STM32WBA AND CONFIG_IEEE802154_STM32WBA)
  message(STATUS "Wireless stack enabled in concurrent mode (BLE+IEEE 802.15.4)")
  if(BLE_LIB_TYPE STREQUAL "BLE_LIB_BASIC")
    set(LL_LIB_CFG_DIR concurrent/ble_15_4)
    set(LL_LIB LinkLayer_BLE_Basic_15_4_lib_Zephyr.a)
  elseif(BLE_LIB_TYPE STREQUAL "BLE_LIB_FULL")
    set(LL_LIB_CFG_DIR concurrent/ble_full_15_4)
    set(LL_LIB LinkLayer_BLE_Full_15_4_lib_Zephyr.a)
  endif()
elseif(CONFIG_BT_STM32WBA)
  message(STATUS "Wireless stack enabled in BLE mode")
  if(BLE_LIB_TYPE STREQUAL "BLE_LIB_BASIC")
    set(LL_LIB_CFG_DIR ble_basic)
    set(LL_LIB LinkLayer_BLE_Basic_lib.a)
  elseif(BLE_LIB_TYPE STREQUAL "BLE_LIB_FULL")
    set(LL_LIB_CFG_DIR ble_full)
    set(LL_LIB LinkLayer_BLE_Full_lib.a)
  endif()
elseif(CONFIG_IEEE802154_STM32WBA)
  message(STATUS "Wireless stack enabled in IEEE 802.15.4 mode")
  if(CONFIG_SOC_STM32WBA65XX)
    if(CONFIG_OPENTHREAD)
      set(LL_LIB_CFG_DIR thread)
      set(LL_LIB LinkLayer_Thread_lib_Zephyr.a)
    else()
      set(LL_LIB_CFG_DIR ieee_15_4_basic)
      set(LL_LIB LinkLayer15_4_Zephyr.a)
    endif()
  endif()
endif()

if(LL_LIB)
  zephyr_include_directories(STM32_WPAN/link_layer/ll_cmd_lib/config/${LL_LIB_CFG_DIR})
  add_library(stm32wba_ll_lib STATIC IMPORTED GLOBAL)
  set(STM32WBA_LL_LIB_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/STM32_WPAN/link_layer/ll_cmd_lib)
  set_target_properties(stm32wba_ll_lib PROPERTIES IMPORTED_LOCATION ${STM32WBA_LIB_DIR}/${libname_prefix}${LL_LIB})
  set_target_properties(stm32wba_ll_lib PROPERTIES INTERFACE_INCLUDE_DIRECTORIES ${STM32WBA_LL_LIB_INCLUDE_DIR})
  target_link_libraries(app PUBLIC stm32wba_ll_lib)
endif()

add_subdirectory(STM32_WPAN)
if(CONFIG_BT_STM32WBA AND CONFIG_IEEE802154_STM32WBA)
  zephyr_include_directories(IEEE802154/Inc)
  add_subdirectory(concurrent)
else()
  add_subdirectory_ifdef(CONFIG_BT_STM32WBA ble)
  add_subdirectory_ifdef(CONFIG_IEEE802154_STM32WBA IEEE802154)
endif()
