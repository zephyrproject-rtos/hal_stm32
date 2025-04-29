# Makefile - STLIB SDK
#
# Copyright (c) 2016 Linaro Limited
# Copyright (c) 2024 STMicroelectronics
#
# SPDX-License-Identifier: Apache-2.0

if(CONFIG_HAS_STM32LIB)
  add_subdirectory_ifdef(CONFIG_BT_STM32_IPM stm32wb)
  if(CONFIG_BT_STM32WBA OR CONFIG_IEEE802154_STM32WBA)
    add_subdirectory(stm32wba)
  endif()
  add_subdirectory_ifdef(CONFIG_BT_STM32WB0 stm32wb0)
  add_subdirectory_ifdef(CONFIG_VIDEO_STM32_VENC vc8000nanoe)
endif()
