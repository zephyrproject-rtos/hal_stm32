# Copyright (c) 2025 STMicroelectronics
#
# SPDX-License-Identifier: Apache-2.0
zephyr_include_directories(Core/Inc)
zephyr_include_directories(STM32_WPAN/Target)
zephyr_include_directories(System/Config/Debug_GPIO)
zephyr_include_directories(System/Config/Log)
zephyr_sources(STM32_WPAN/Target/bpka.c)
zephyr_sources(STM32_WPAN/Target/linklayer_plat.c)
zephyr_sources(STM32_WPAN/Target/ll_sys_if.c)
zephyr_sources(STM32_WPAN/Target/power_table.c)
