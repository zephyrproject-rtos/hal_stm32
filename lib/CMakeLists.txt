# Makefile - STLIB SDK
#
# Copyright (c) 2016 Linaro Limited
# Copyright (c) 2024 STMicroelectronics
#
# SPDX-License-Identifier: Apache-2.0

if(CONFIG_HAS_STM32LIB)
  add_subdirectory_ifdef(CONFIG_BT_STM32_IPM stm32wb)
  add_subdirectory_ifdef(CONFIG_BT_STM32WBA stm32wba)
  add_subdirectory_ifdef(CONFIG_BT_STM32WB0 stm32wb0)
endif()
