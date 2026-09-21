# SPDX-License-Identifier: Apache-2.0

zephyr_library_link_libraries(tfpsacrypto)
# Crypto drivers need access to internal TF-PSA-Crypto headers
zephyr_library_include_directories($<TARGET_PROPERTY:tfpsacrypto,INCLUDE_DIRECTORIES>)

zephyr_include_directories(config)
zephyr_include_directories(include)
zephyr_include_directories(dispatch/include)
# psa_crypto_driver_wrappers.h located in dispatch/ is needed by interface/src/stm32_hal_psa_hash.c
zephyr_include_directories(dispatch)

zephyr_include_directories(stm32_psa_transparent_drivers/config)
zephyr_include_directories(stm32_psa_transparent_drivers/core/include)
zephyr_include_directories(stm32_psa_transparent_drivers/interface/include)

# We need some USE_HAL_xxx_SUSPEND_RESUME in some HAL versions
zephyr_compile_definitions(USE_HAL_HASH_SUSPEND_RESUME=1)
zephyr_compile_definitions(USE_HAL_CRYP_SUSPEND_RESUME=1)

zephyr_sources(stm32_psa_transparent_drivers/interface/src/stm32_hal_psa_translator.c)

if(CONFIG_USE_STM32_HAL_PSA_CRYPTO_DRIVERS_AES OR
   CONFIG_USE_STM32_HAL_PSA_CRYPTO_DRIVERS_CRYP OR
   CONFIG_USE_STM32_HAL_PSA_CRYPTO_DRIVERS_SAES)
  zephyr_compile_definitions(USE_STM32_HAL_PSA_AES_DRIVER)
  zephyr_compile_definitions_ifdef(CONFIG_USE_STM32_HAL_PSA_CRYPTO_DRIVERS_SAES,
    USE_STM32_HAL_PSA_AES_DPA_DRIVER=1
  )

  zephyr_sources(stm32_psa_transparent_drivers/core/src/stm32_hal_aes.c)
  zephyr_sources(stm32_psa_transparent_drivers/core/src/stm32_hal_cipher.c)
  zephyr_sources(stm32_psa_transparent_drivers/interface/src/stm32_hal_psa_aead.c)
  zephyr_sources(stm32_psa_transparent_drivers/interface/src/stm32_hal_psa_cipher.c)
endif()

if(CONFIG_USE_STM32_HAL_PSA_CRYPTO_DRIVERS_HASH)
  zephyr_compile_definitions(USE_STM32_HAL_PSA_HASH_DRIVER)

  zephyr_sources(stm32_psa_transparent_drivers/core/src/stm32_hal_hash.c)
  zephyr_sources(stm32_psa_transparent_drivers/interface/src/stm32_hal_psa_hash.c)
endif()

if(CONFIG_USE_STM32_HAL_PSA_CRYPTO_DRIVERS_RNG)
  zephyr_compile_definitions(USE_STM32_HAL_PSA_RNG_DRIVER)

  zephyr_sources(stm32_psa_transparent_drivers/core/src/stm32_hal_rng.c)
  zephyr_sources(stm32_psa_transparent_drivers/interface/src/stm32_hal_psa_random.c)
endif()
