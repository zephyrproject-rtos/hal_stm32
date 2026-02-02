# Copyright (c) 2025 STMicroelectronics
#
# SPDX-License-Identifier: Apache-2.0
zephyr_include_directories(Common/WPAN/Interfaces)
zephyr_include_directories(Common/WPAN/Modules)
zephyr_include_directories(Common/WPAN/Modules/Flash)
zephyr_include_directories(Common/WPAN/Modules/RTDebug)
zephyr_include_directories(Common/WPAN/Modules/Log)
zephyr_include_directories(Common/WPAN/Modules/BasicAES)
zephyr_include_directories(Utilities/misc)
zephyr_include_directories(Utilities/tim_serv)
zephyr_include_directories(Utilities/trace/adv_trace)
zephyr_include_directories(STM32_WPAN)

zephyr_sources(Common/WPAN/Modules/RTDebug/RTDebug.c)
zephyr_sources(Common/WPAN/Modules/Log/log_module.c)
zephyr_sources(Common/WPAN/Interfaces/hw_pka.c)
zephyr_sources(Common/WPAN/Interfaces/hw_pka_p256.c)

if(CONFIG_FLASH)
  zephyr_sources(Common/WPAN/Modules/Flash/flash_manager.c)
  zephyr_sources(Common/WPAN/Modules/Flash/flash_driver.c)
  zephyr_sources(Common/WPAN/Modules/Flash/rf_timing_synchro.c)
endif()
zephyr_sources(Common/WPAN/Modules/stm_list.c)

zephyr_sources(Common/WPAN/Modules/BasicAES/baes_ccm.c)
zephyr_sources(Common/WPAN/Modules/BasicAES/baes_cmac.c)
zephyr_sources(Common/WPAN/Modules/BasicAES/baes_ecb.c)
zephyr_sources(Common/WPAN/Interfaces/hw_aes.c)


set(STM32WBA_LIB_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../../zephyr/blobs/stm32wba/lib)

# select the type of BLE library
if(CONFIG_BT_STM32WBA)
  set(STM32WBA_BLE_LIB_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/STM32_WPAN/ble/stack)
  if(CONFIG_BT_STM32WBA_BASIC_LIB)
    message(STATUS "BLE Basic configuration is selected")
  elseif(CONFIG_BT_STM32WBA_FULL_LIB)
    message(STATUS "BLE Full configuration is selected")
  endif()
  add_library(stm32wba_ble_lib STATIC IMPORTED GLOBAL)

  add_dependencies(
    stm32wba_ble_lib
    stm32wba_ll_lib
  )
  set_target_properties(
    stm32wba_ble_lib PROPERTIES IMPORTED_LOCATION ${STM32WBA_LIB_DIR}/stm32wba_ble_stack_llo.a
  )

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
  set(libname_prefix "WBA5_")
else()
  message(FATAL_ERROR "Unsupported SoC: ${CONFIG_SOC}")
endif()

# Selecting the proper version of link layer lib and its associated configuration header file
if(CONFIG_BT_STM32WBA AND CONFIG_IEEE802154_STM32WBA)
  message(STATUS "Wireless stack enabled in concurrent mode (BLE+IEEE 802.15.4)")
  if(CONFIG_BT_STM32WBA_BASIC_LIB)
    set(LL_LIB_CFG_DIR concurrent/ble_15_4)
    set(LL_LIB LinkLayer_BLE_Basic_15_4_lib_Zephyr.a)
  elseif(CONFIG_BT_STM32WBA_FULL_LIB)
    message(FATAL_ERROR "Unsupported BLE feature in concurrent mode (BLE+IEEE 802.15.4)")
  endif()
elseif(CONFIG_BT_STM32WBA)
  message(STATUS "Wireless stack enabled in BLE mode")
  if(CONFIG_BT_STM32WBA_BASIC_LIB)
    set(LL_LIB_CFG_DIR ble_basic)
    set(LL_LIB LinkLayer_BLE_Basic_lib.a)
  elseif(CONFIG_BT_STM32WBA_FULL_LIB)
    set(LL_LIB_CFG_DIR ble_full)
    set(LL_LIB LinkLayer_BLE_Full_lib.a)
  endif()
elseif(CONFIG_IEEE802154_STM32WBA)
  message(STATUS "Wireless stack enabled in IEEE 802.15.4 mode")
  set(LL_LIB_CFG_DIR ieee_15_4_basic)
  set(LL_LIB LinkLayer15_4_Zephyr.a)
endif()

if(LL_LIB)
  message(STATUS "LL Library : ${libname_prefix}${LL_LIB}")
  zephyr_include_directories(STM32_WPAN/link_layer/ll_cmd_lib/config/${LL_LIB_CFG_DIR})
  add_library(stm32wba_ll_lib STATIC IMPORTED GLOBAL)
  set(STM32WBA_LL_LIB_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/STM32_WPAN/link_layer/ll_cmd_lib)
  set_target_properties(stm32wba_ll_lib PROPERTIES IMPORTED_LOCATION ${STM32WBA_LIB_DIR}/${libname_prefix}${LL_LIB})
  set_target_properties(stm32wba_ll_lib PROPERTIES INTERFACE_INCLUDE_DIRECTORIES ${STM32WBA_LL_LIB_INCLUDE_DIR})
  target_link_libraries(app PUBLIC stm32wba_ll_lib)
endif()

add_subdirectory(STM32_WPAN)
add_subdirectory(RF_Integration)
