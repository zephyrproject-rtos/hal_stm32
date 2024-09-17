# Makefile - STM32Cube SDK
#
# Copyright (c) 2020 Linaro Limited
#
# SPDX-License-Identifier: Apache-2.0

add_subdirectory_ifdef(CONFIG_HAS_STM32CUBE stm32cube)
add_subdirectory_ifdef(CONFIG_HAS_STM32LIB lib)
