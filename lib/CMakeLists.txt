# Makefile - STLIB SDK
#
# Copyright (c) 2016 Linaro Limited
#
# SPDX-License-Identifier: Apache-2.0

if(CONFIG_HAS_STM32LIB)
  if(CONFIG_BT_STM32_IPM)
    zephyr_include_directories(stm32wb/hci)

    zephyr_sources(stm32wb/hci/hw_ipcc.c)
    zephyr_sources(stm32wb/hci/shci.c)
    zephyr_sources(stm32wb/hci/shci_tl.c)
    zephyr_sources(stm32wb/hci/shci_tl_if.c)
    zephyr_sources(stm32wb/hci/stm_list.c)
    zephyr_sources(stm32wb/hci/tl_mbox.c)

  endif()

  if(CONFIG_BT_STM32WBA)

    if(DEFINED CONFIG_BOARD_NUCLEO_WBA52CG)
      message(FATAL_ERROR "BLE library is not compatible with nucleo_wba52cg")
    endif()

    zephyr_compile_definitions( -DBLE )

    zephyr_include_directories(stm32wba/hci)
    zephyr_include_directories(stm32wba/hci/ll)

    zephyr_sources(stm32wba/hci/ll_sys_cs.c)
    zephyr_sources(stm32wba/hci/ll_sys_intf.c)
    zephyr_sources(stm32wba/hci/ll_sys_dp_slp.c)
    zephyr_sources(stm32wba/hci/ll_sys_startup.c)
    zephyr_sources(stm32wba/hci/RTDebug.c)
    zephyr_sources(stm32wba/hci/hw_pka.c)
    zephyr_sources(stm32wba/hci/pka_p256.c)
    zephyr_sources(stm32wba/hci/bpka.c)
    zephyr_sources(stm32wba/hci/power_table.c)
    zephyr_sources(stm32wba/hci/scm.c)
    zephyr_sources(stm32wba/hci/log_module.c)
    zephyr_sources(stm32wba/hci/linklayer_plat.c)
    zephyr_sources(stm32wba/hci/ll_sys_if.c)
    if(CONFIG_FLASH)
      zephyr_sources(stm32wba/hci/flash_manager.c)
      zephyr_sources(stm32wba/hci/flash_driver.c)
      zephyr_sources(stm32wba/hci/stm_list.c)
      zephyr_sources(stm32wba/hci/rf_timing_synchro.c)
    endif()

    set(STM32WBA_BLE_LIB_DIR     ${CMAKE_CURRENT_SOURCE_DIR}/../zephyr/blobs/stm32wba/lib)
    set(STM32WBA_BLE_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/stm32wba/hci)

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

  endif()
  add_subdirectory_ifdef(CONFIG_BT_STM32WB0 stm32wb0)
endif()
