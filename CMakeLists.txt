# Makefile - STM32Cube SDK
#
# Copyright (c) 2020 Linaro Limited
#
# SPDX-License-Identifier: Apache-2.0

add_subdirectory_ifdef(CONFIG_HAS_STM32CUBE stm32cube)
add_subdirectory_ifdef(CONFIG_HAS_STM32LIB lib)

# Add BT firmware images upgrade support for STEVAL-MKBOX board family
if(CONFIG_BOARD_SENSORTILE_BOX OR CONFIG_BOARD_SENSORTILE_BOX_PRO)
  add_subdirectory(ble_fw_mkbox)
endif()
