# Makefile - STM32Cube SDK
#
# Copyright (c) 2016 Linaro Limited
# Copyright (c) 2024 STMicroelectronics
#
# SPDX-License-Identifier: Apache-2.0
#
# This file enables compilation of the STM32Cube library
# for a target STM32 series as part of the Zephyr RTOS.
#
# The following symbols are provided by the Zephyr build system:
#   * CONFIG_SOC: name of the SoC
#     - Converted to HAL/LL model selection define
#       (c.f. `*/soc/stm32*xx.h` for list of allowed values)
#     - In Zephyr, the value should be fully lower-cased
#       (inverse conversion is performed by this script)
#       - e.g.: CONFIG_SOC = "stm32f030xc" -> #define STM32F030xC
#
#   * CONFIG_STM32CUBE_SOC_NAME_OVERRIDE (optional): SoC name override
#     There are a few cases where the value of CONFIG_SOC does not match
#     what the HAL/LL model selection define should be. For example, on
#     STM32F4 series, both STM32F401xD and STM32F401xE SoCs share the same
#     define `STM32F401xE`. The value of CONFIG_STM32CUBE_SOC_NAME_OVERRIDE
#     is used in place of CONFIG_SOC if the option exists (which is not the
#     case by default, since most SoC names match the CMSIS define).
#
#   * CONFIG_SOC_SERIES_{SERIES_NAME}: name of the STM32 series
#     - Corresponding STM32Cube package is included in the build
#       - Found in subfolder "{SERIES_NAME}" or "{SERIES_NAME}x"
#     - ${supported_series} from `series_list.cmake` lists all supported series
#       - The SERIES_NAME is lowercase in this list
#       - The SERIES_NAME **always** ends with a single `x`

zephyr_library()

# Convert the Zephyr lowercase SoC name to the value expected by STM32Cube
# Example: "stm32f030xc" --TOUPPER--> "STM32F030XC" --REPLACE--> "STM32F030xC"
# Use CONFIG_STM32CUBE_SOC_NAME_OVERRIDE as source if it exists which indicates
# a special case SoC; otherwise, CONFIG_SOC should have the right value.
if(CONFIG_STM32CUBE_SOC_NAME_OVERRIDE)
  string(TOUPPER ${CONFIG_STM32CUBE_SOC_NAME_OVERRIDE} _STM32CUBE_CPU)
else()
  string(TOUPPER ${CONFIG_SOC} _STM32CUBE_CPU)
endif()
string(REPLACE "X" "x" STM32CUBE_CPU ${_STM32CUBE_CPU})

# Provide the minimal definitions needed by Cube to function
# properly. This includes the SoC definition, but also the
# USE_HAL_DRIVER and USE_FULL_LL_DRIVER defines, which control
# whether or not the code in HAL/LL source files in compiled
# or not. Since we want this code, we have to define these too.
#
# Note that this does not add any HAL or LL source files to the
# build: this is controlled by the various USE_STM32_{HAL/LL}_<PPP>
# Kconfig symbols instead (see per-series CMakeLists for details).
zephyr_compile_definitions(
  -D${STM32CUBE_CPU}
  -DUSE_HAL_DRIVER
  -DUSE_FULL_LL_DRIVER
)

# Include list of all supported STM32 SoC series
include(series_list.cmake)

# On dual-core MCUs, we must inform Cube which CPU we are building for.
# Provide the Cube definition based on the active CPU Kconfig symbols.
if(CONFIG_CPU_CORTEX_M4)
  zephyr_compile_definitions( -DCORE_CM4 )
elseif(CONFIG_CPU_CORTEX_M7)
  zephyr_compile_definitions( -DCORE_CM7 )
elseif(CONFIG_CPU_CORTEX_M55)
  zephyr_compile_definitions( -DCORE_CM55 )
elseif(CONFIG_CPU_CORTEX_A7)
  zephyr_compile_definitions( -DCORE_CA7 )
elseif(CONFIG_CPU_CORTEX_M33)
  zephyr_compile_definitions( -DCORE_CM33 )
endif()

# Define the HSE frequency visible to Cube if a value is specified in Zephyr.
if(CONFIG_CLOCK_STM32_HSE_CLOCK)
  zephyr_compile_definitions( -DHSE_VALUE=${CONFIG_CLOCK_STM32_HSE_CLOCK} )
endif()

# Ethernet HAL API v2 specifics
if(CONFIG_ETH_STM32_HAL_API_V2)
  # Enable PTP support in HAL if requested by Zephyr
  zephyr_compile_definitions_ifdef(CONFIG_PTP_CLOCK_STM32_HAL
    -DHAL_ETH_USE_PTP)
endif()

# Search which STM32 series was selected
foreach(series ${supported_series})
  string(TOUPPER ${series} series_to_upper)
  if(CONFIG_SOC_SERIES_${series_to_upper})
    # Found the series - now look for its Cube package.
    # Depending on the naming convention used in the package,
    # this will be either the raw ${series}, or ${series}
    # suffixed with a single `x` (i.e., `${series}x`).
    #
    # Check if the former exists:
    #   - if yes, correct subdirectory is the raw variant
    #   - if no, correct subdirectory is the suffixed variant
    #
    # Note that `IS_DIRECTORY` checks for existence, so it
    # is more appropriate than `EXISTS` for this usecase.
    if (IS_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/${series}")
      set(cube_dir ${series})
    else()
      set(cube_dir ${series}x)
    endif()

   if(CONFIG_STM32_HAL2)
      zephyr_compile_definitions(USE_EXTERNAL_ENV)
      zephyr_include_directories(
        ${cube_dir}/dfp/Include
        ${cube_dir}/dfp/Include/Templates
        ${cube_dir}/drivers/hal
        ${cube_dir}/drivers/ll
        ${cube_dir}/drivers/templates/common
      )
   else()
      zephyr_include_directories(
        ${cube_dir}/soc
        ${cube_dir}/drivers/include
      )
    endif()

    add_subdirectory(${cube_dir})
  endif()
endforeach()

# Enable HAL asserts if requested by Zephyr
if(CONFIG_USE_STM32_ASSERT)
	zephyr_compile_definitions( -DUSE_FULL_ASSERT )
endif()

# Add the series-agnostic LL headers to include directories
zephyr_include_directories(common_ll/include)
