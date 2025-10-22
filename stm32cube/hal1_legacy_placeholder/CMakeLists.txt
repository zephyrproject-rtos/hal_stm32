# SPDX-FileCopyrightText: Copyright (c) 2026 STMicroelectronics
# SPDX-License-Identifier: Apache-2.0

# Adds the placeholder HAL1 Legacy definitions header to include path.
#
# Every HAL1 package contains a file "stm32_hal_legacy.h" filled
# with aliases added whenever an HAL function or macro is renamed.
# This is provided for backwards compatibility but we don't have
# a need for it in Zephyr: the STM32-specific code is kept aligned
# with the HAL's API even when it changes. In addition to being
# useless, this header also contains `#define`s that conflict with
# macros provided by Zephyr, causing build errors if unpatched.
#
# The Legacy definitions header is included as follows by one
# of the HAL's most important headers ("stm32XXXxx_hal_def.h"):
#
#     #include "Legacy/stm32_hal_legacy.h"
#
# By adding the current directory in the include path, this directive
# will include the placeholder file `./Legacy/stm32_hal_legacy.h` and
# we can safely dispose of the real Legacy definitions header.
zephyr_include_directories(.)
