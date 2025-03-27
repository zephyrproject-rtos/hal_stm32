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
#   * CONFIG_SOC_SERIES_{SERIES_NAME}: name of the STM32 series
#     - Corresponding STM32Cube package is included in the build
#       - Found in subfolder "{SERIES_NAME}" or "{SERIES_NAME}x"
#     - ${supported_series} below lists all supported series
#       - The SERIES_NAME is lowercase in this list
#       - The SERIES_NAME **always** ends with a single `x`

zephyr_library()

# Convert the Zephyr lowercase SoC name to the value expected by STM32Cube
# Example: "stm32f030xc" --TOUPPER--> "STM32F030XC" --REPLACE--> "STM32F030xC"
string(TOUPPER ${CONFIG_SOC} _STM32CUBE_CPU)
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

# List of all supported STM32 SoC series
set(supported_series
  stm32c0x
  stm32f0x
  stm32f1x
  stm32f2x
  stm32f3x
  stm32f4x
  stm32f7x
  stm32g0x
  stm32g4x
  stm32h5x
  stm32h7x
  stm32h7rsx
  stm32l0x
  stm32l1x
  stm32l4x
  stm32l5x
  stm32mp1x
  stm32mp13x
  stm32mp2x
  stm32n6x
  stm32u0x
  stm32u3x
  stm32u5x
  stm32wb0x
  stm32wbax
  stm32wbx
  stm32wlx
)

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

    zephyr_include_directories(
	    ${cube_dir}/soc
	    ${cube_dir}/drivers/include
	  )

    add_subdirectory(${cube_dir})
  endif()
endforeach()

# Enable HAL asserts if requested by Zephyr
if(CONFIG_USE_STM32_ASSERT)
	zephyr_compile_definitions( -DUSE_FULL_ASSERT )
endif()

# Add the series-agnostic LL headers to include directories
zephyr_include_directories(common_ll/include)
