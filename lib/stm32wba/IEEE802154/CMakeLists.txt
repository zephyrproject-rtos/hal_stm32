# Copyright (c) 2025 STMicroelectronics
#
# SPDX-License-Identifier: Apache-2.0
zephyr_include_directories(Core/Inc)
zephyr_include_directories(System/Config/Debug_GPIO)
zephyr_include_directories(System/Config/Log)
zephyr_include_directories(STM32_WPAN/Target)

if(CONFIG_IEEE802154_STM32WBA)
  zephyr_include_directories(Inc)
  if(NOT CONFIG_NET_L2_CUSTOM_IEEE802154_STM32WBA)
    zephyr_include_directories(Core/Inc/802154)
  endif()
endif()

zephyr_sources(STM32_WPAN/Target/linklayer_plat.c)
zephyr_sources(STM32_WPAN/Target/ll_sys_if.c)
zephyr_sources(STM32_WPAN/Target/power_table.c)
