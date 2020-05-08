# Makefile - STLIB SDK
#
# Copyright (c) 2016 Linaro Limited
#
# SPDX-License-Identifier: Apache-2.0

if(CONFIG_HAS_STM32LIB)
  if(CONFIG_BT_STM32_IPM)
    zephyr_include_directories(stm32wb/hci)
    zephyr_sources(stm32wb/hci/shci.c)
    zephyr_sources(stm32wb/hci/shci_tl.c)
    zephyr_sources(stm32wb/hci/hw_ipcc.c)
    zephyr_sources(stm32wb/hci/stm_list.c)
    zephyr_sources(stm32wb/hci/tl_mbox.c)
    zephyr_sources(stm32wb/hci/tl_if.c)
  endif()
endif()
