# Copyright (c) 2025 STMicroelectronics
#
# SPDX-License-Identifier: Apache-2.0
if (CONFIG_IEEE802154_STM32WBA)
zephyr_include_directories(IEEE802154)
endif()
if (CONFIG_BT_STM32WBA)
zephyr_include_directories(ble/stack/include)
zephyr_include_directories(ble/stack/include/auto)
endif()

add_subdirectory(link_layer)