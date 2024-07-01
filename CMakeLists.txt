# Makefile - STM32Cube SDK
#
# Copyright (c) 2020 Linaro Limited
#
# SPDX-License-Identifier: Apache-2.0

add_subdirectory_ifdef(CONFIG_HAS_STM32CUBE stm32cube)
add_subdirectory_ifdef(CONFIG_HAS_STM32LIB lib)

# Add BT firmware images upgrade support for STEVAL-MKBOX board family
if(CONFIG_DT_HAS_ST_HCI_SPI_V1_ENABLED OR CONFIG_DT_HAS_ST_HCI_SPI_V2_ENABLED)
  add_subdirectory(ble_fw_mkbox)
endif()
