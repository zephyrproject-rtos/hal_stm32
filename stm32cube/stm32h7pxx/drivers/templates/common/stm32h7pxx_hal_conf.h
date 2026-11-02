/**
  ******************************************************************************
  * @file    stm32h7pxx_hal_conf.h
  * @brief   HAL configuration file.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2026 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef  STM32H7PXX_HAL_CONF_H
#define  STM32H7PXX_HAL_CONF_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/

/** @defgroup HAL_Conf_How_To_Use HAL Conf How to Use
  * @{
  - The STM32 HAL configuration file, stm32tnxx_hal_conf.h, is designed to customize the behaviour of the HAL modules.
  - The users can utilize the provided file as-is, where all HAL modules are enabled with their default settings.
  - Alternatively, users have the flexibility to customize the file based on their application's requirements.
  - For example, they can enable only the necessary HAL modules or modify the predefined settings to achieve
    the desired functionality.
  */

/**
  * @}
  */

/** @defgroup HAL_Conf_Exported_Constants HAL Conf Constants
  * @{
  */

/** @defgroup HAL_System_Configuration HAL System Configuration
  * @{
  */

/* ########################### System Configuration ############################# */
/**
  * @brief This is the HAL system configuration section
  */
/**
  * @}
  */

/** @defgroup HAL_MUTEX_Usage_Activation HAL MUTEX Usage Activation
  * @{
  */
/* ########################## HAL MUTEX usage activation  ####################### */
/**
  * @brief Used by the HAL PPP Acquire/Release APIs when the define USE_HAL_MUTEX is set to 1
  */
#define USE_HAL_MUTEX                           0U
/**
  * @}
  */

/** @defgroup HAL_API_Parameters_Check HAL API Parameters Check
  * @{
  */
/* ########################## HAL API parameters check  ##################### */
/**
  * @brief Run time parameter check activation
  */
#define USE_HAL_CHECK_PARAM                     0U
#define USE_HAL_SECURE_CHECK_PARAM              0U
/**
  * @}
  */

/** @defgroup HAL_State_Transition HAL State Transition
  * @{
  */
/* ########################## State transition   ################################ */
/**
  * @brief Enable protection of state transition in thread safe
  */
#define USE_HAL_CHECK_PROCESS_STATE             0U
/**
  * @}
  */

/* ########################## Peripheral configuration  ######################### */

/** @defgroup HAL_ADC_Config HAL ADC Configuration
  * @{
  */
/* ########################## HAL_ADC Config #################################### */
#define USE_HAL_ADC_MODULE                      1U
#define USE_HAL_ADC_CLK_ENABLE_MODEL            HAL_CLK_ENABLE_NO
#define USE_HAL_ADC_REGISTER_CALLBACKS          0U
#define USE_HAL_ADC_USER_DATA                   0U
#define USE_HAL_ADC_GET_LAST_ERRORS             0U
#define USE_HAL_ADC_DMA                         1U
/**
  * @}
  */

/** @defgroup HAL_ADF_Config HAL ADF Configuration
  * @{
  */
/* ########################## HAL_ADF Config #################################### */
#define USE_HAL_ADF_MODULE                      1U
#define USE_HAL_ADF_CLK_ENABLE_MODEL            HAL_CLK_ENABLE_NO
#define USE_HAL_ADF_REGISTER_CALLBACKS          0U
#define USE_HAL_ADF_USER_DATA                   0U
#define USE_HAL_ADF_GET_LAST_ERRORS             0U
#define USE_HAL_ADF_DMA                         1U
/**
  * @}
  */

/** @defgroup HAL_AXIM_Config HAL AXIM Configuration
  * @{
  */
/* ########################## HAL_AXIM Config #################################### */
#define USE_HAL_AXIM_MODULE                      1U
/**
  * @}
  */

/** @defgroup HAL_COMP_Config HAL COMP Configuration
  * @{
  */
/* ########################## HAL_COMP Config ################################### */
#define USE_HAL_COMP_MODULE                     1U
#define USE_HAL_COMP_CLK_ENABLE_MODEL           HAL_CLK_ENABLE_NO
#define USE_HAL_COMP_REGISTER_CALLBACKS         0U
#define USE_HAL_COMP_USER_DATA                  0U
/* Use comparator with EXTI (needed to generate system wake-up event and CPU event) */
#define USE_HAL_COMP_EXTI                       0U
/* Use comparators window mode feature */
#define USE_HAL_COMP_WINDOW_MODE                0U
/**
  * @}
  */

/** @defgroup HAL_CORDIC_Config HAL CORDIC Configuration
  * @{
  */
/* ########################## HAL_CORDIC Config ################################# */
#define USE_HAL_CORDIC_MODULE                   1U
#define USE_HAL_CORDIC_CLK_ENABLE_MODEL         HAL_CLK_ENABLE_NO
#define USE_HAL_CORDIC_REGISTER_CALLBACKS       0U
#define USE_HAL_CORDIC_USER_DATA                0U
#define USE_HAL_CORDIC_GET_LAST_ERRORS          0U
#define USE_HAL_CORDIC_DMA                      1U
/**
  * @}
  */

/** @defgroup HAL_CORTEX_Config HAL CORTEX Configuration
  * @{
  */
/* ########################## HAL_CORTEX Config ################################# */
#define USE_HAL_CORTEX_MODULE                   1U
/**
  * @}
  */

/** @defgroup HAL_CRC_Config HAL CRC Configuration
  * @{
  */
/* ########################## HAL_CRC Config #################################### */
#define USE_HAL_CRC_MODULE                      1U
#define USE_HAL_CRC_CLK_ENABLE_MODEL            HAL_CLK_ENABLE_NO
#define USE_HAL_CRC_USER_DATA                   0U
/**
  * @}
  */

/** @defgroup HAL_CRS_Config HAL CRS Configuration
  * @{
  */
/* ########################## HAL_CRS Config #################################### */
#define USE_HAL_CRS_MODULE                      1U
#define USE_HAL_CRS_CLK_ENABLE_MODEL            HAL_CLK_ENABLE_NO
#define USE_HAL_CRS_REGISTER_CALLBACKS          0U
#define USE_HAL_CRS_USER_DATA                   0U
#define USE_HAL_CRS_GET_LAST_ERRORS             0U
/**
  * @}
  */

/** @defgroup HAL_DAC_Config HAL DAC Configuration
  * @{
  */
/* ########################## HAL_DAC Config #################################### */
#define USE_HAL_DAC_MODULE                      1U
#define USE_HAL_DAC_CLK_ENABLE_MODEL            HAL_CLK_ENABLE_NO
#define USE_HAL_DAC_REGISTER_CALLBACKS          0U
#define USE_HAL_DAC_USER_DATA                   0U
#define USE_HAL_DAC_GET_LAST_ERRORS             0U
#define USE_HAL_DAC_DMA                         1U
#define USE_HAL_DAC_DUAL_CHANNEL                0U
/**
  * @}
  */

/** @defgroup HAL_DBGMCU_Config HAL DBGMCU Configuration
  * @{
  */
/* ########################## HAL_DBGMCU Config ################################# */
#define USE_HAL_DBGMCU_MODULE                   1U
/**
  * @}
  */

/** @defgroup HAL_DMA_Config HAL DMA Configuration
  * @{
  */
/* ########################## HAL_DMA Config #################################### */
#define USE_HAL_DMA_MODULE                      1U
#define USE_HAL_DMA_CLK_ENABLE_MODEL            HAL_CLK_ENABLE_NO
#define USE_HAL_DMA_USER_DATA                   0U
#define USE_HAL_DMA_GET_LAST_ERRORS             0U
#define USE_HAL_DMA_LINKEDLIST                  0U
/**
  * @}
  */

/** @defgroup HAL_DTS_Config HAL DTS Configuration
  * @{
  */
/* ########################## HAL_DTS Config #################################### */
#define USE_HAL_DTS_MODULE                      1U
#define USE_HAL_DTS_CLK_ENABLE_MODEL            HAL_CLK_ENABLE_NO
#define USE_HAL_DTS_REGISTER_CALLBACKS          0U
#define USE_HAL_DTS_USER_DATA                   0U
/**
  * @}
  */

/** @defgroup HAL_EXTI_Config HAL EXTI Configuration
  * @{
  */
/* ########################## HAL_EXTI Config ################################### */
#define USE_HAL_EXTI_MODULE                     1U
#define USE_HAL_EXTI_CLK_ENABLE_MODEL           HAL_CLK_ENABLE_NO
#define USE_HAL_EXTI_REGISTER_CALLBACKS         0U
#define USE_HAL_EXTI_USER_DATA                  0U
/**
  * @}
  */

/** @defgroup HAL_FDCAN_Config HAL FDCAN Configuration
  * @{
  */
/* ########################## HAL_FDCAN Config ################################## */
#define USE_HAL_FDCAN_MODULE                    1U
#define USE_HAL_FDCAN_CLK_ENABLE_MODEL          HAL_CLK_ENABLE_NO
#define USE_HAL_FDCAN_REGISTER_CALLBACKS        0U
#define USE_HAL_FDCAN_USER_DATA                 0U
#define USE_HAL_FDCAN_GET_LAST_ERRORS           0U
/**
  * @}
  */

/** @defgroup HAL_FLASH_Config HAL FLASH Configuration
  * @{
  */
/* ########################## HAL_FLASH Config ################################## */
#define USE_HAL_FLASH_MODULE                    1U
#define USE_HAL_FLASH_REGISTER_CALLBACKS        0U
#define USE_HAL_FLASH_USER_DATA                 0U
#define USE_HAL_FLASH_GET_LAST_ERRORS           0U
/* Use the FLASH program by address feature */
#define USE_HAL_FLASH_PROGRAM_BY_ADDR           1U
/* Use the FLASH erase by address feature */
#define USE_HAL_FLASH_ERASE_BY_ADDR             1U
/* Use the FLASH erase by PAGE feature */
#define USE_HAL_FLASH_ERASE_PAGE                1U
/* Use the FLASH bank erase feature */
#define USE_HAL_FLASH_ERASE_BANK                1U
/* Use the FLASH mass erase feature */
#define USE_HAL_FLASH_MASS_ERASE                1U
/* Use ECC errors handling APIs */
#define USE_HAL_FLASH_ECC                       1U
/* Use CRC Calculation APIs */
#define USE_HAL_FLASH_CALCULATE_CRC             1U
/**
  * @}
  */

/** @defgroup HAL_FMAC_Config HAL FMAC Configuration
  * @{
  */
/* ########################## HAL_FMAC Config ################################### */
#define USE_HAL_FMAC_MODULE                     1U
#define USE_HAL_FMAC_CLK_ENABLE_MODEL           HAL_CLK_ENABLE_NO
#define USE_HAL_FMAC_REGISTER_CALLBACKS         0U
#define USE_HAL_FMAC_USER_DATA                  0U
#define USE_HAL_FMAC_GET_LAST_ERRORS            0U
#define USE_HAL_FMAC_DMA                        1U
/**
  * @}
  */

/** @defgroup HAL_GPIO_Config HAL GPIO Configuration
  * @{
  */
/* ########################## HAL_GPIO Config ################################### */
#define USE_HAL_GPIO_MODULE                     1U
#define USE_HAL_GPIO_CLK_ENABLE_MODEL           HAL_CLK_ENABLE_NO
/* The I/O HSLV configuration bit must not be set if the I/O supply is above a defined voltage.
 * Setting it while the voltage is higher than the threshold can damage the device.
 * There is no hardware protection associated to this feature so it is recommended to use it
 * only as a static configuration for fixed I/O supply.
 */
#define USE_HAL_GPIO_HSLV                       0U
/**
  * @}
  */

/** @defgroup HAL_HASH_Config HAL HASH Configuration
  * @{
  */
/* ########################## HAL_HASH Config ################################### */
#define USE_HAL_HASH_MODULE                     1U
#define USE_HAL_HASH_CLK_ENABLE_MODEL           HAL_CLK_ENABLE_NO
#define USE_HAL_HASH_REGISTER_CALLBACKS         0U
#define USE_HAL_HASH_USER_DATA                  0U
#define USE_HAL_HASH_GET_LAST_ERRORS            0U
#define USE_HAL_HASH_DMA                        1U
/**
  * @}
  */

/** @defgroup HAL_HCD_Config HAL HCD Configuration
  * @{
  */
/* ########################## HAL_HCD Config #################################### */
#define USE_HAL_HCD_MODULE                      1U
#define USE_HAL_HCD_REGISTER_CALLBACKS          0U
#define USE_HAL_HCD_USER_DATA                   0U
#define USE_HAL_HCD_GET_LAST_ERRORS             0U
#define USE_HAL_HCD_USB_EP_TYPE_ISOC            0U
#define USE_HAL_HCD_MAX_CHANNEL_NB              16U
/**
  * @}
  */

/** @defgroup HAL_HRTIM_Config HAL HRTIM Configuration
  * @{
  */
/* ########################## HAL_HRTIM Config ################################## */
#define USE_HAL_HRTIM_MODULE                    1U
#define USE_HAL_HRTIM_CLK_ENABLE_MODEL          HAL_CLK_ENABLE_NO
#define USE_HAL_HRTIM_REGISTER_CALLBACKS        0U
#define USE_HAL_HRTIM_USER_DATA                 0U
#define USE_HAL_HRTIM_DMA                       1U
/* Constants used to fine tune the HRTIM callback registration capabilities
   to the application's need. By default, all the HRTIM callback functions
   can be registered.
 */
#define USE_HAL_HRTIM_GLOBAL_CALLBACKS          1U
#define USE_HAL_HRTIM_TIMER_CALLBACKS           1U
#define USE_HAL_HRTIM_CAPTURE_COMPARE_CALLBACKS 1U
#define USE_HAL_HRTIM_OUTPUT_CALLBACKS          1U
#define USE_HAL_HRTIM_XBAR_OVR_CALLBACKS        1U
/**
  * @}
  */

/** @defgroup HAL_HSP_Config HAL HSP Configuration
  * @{
  */
/* ########################## HAL_HSP Config #################################### */
#define USE_HAL_HSP_MODULE                      1U
#define USE_HAL_HSP_CLK_ENABLE_MODEL            HAL_CLK_ENABLE_NO
#define USE_HAL_HSP_REGISTER_CALLBACKS          0U
#define USE_HAL_HSP_USER_DATA                   0U
#define USE_HAL_HSP_GET_LAST_ERRORS             0U
#define USE_HAL_HSP_MSGBOX_GET_LAST_ERROR       0U
#define USE_HAL_HSP_TRGIN_IT                    0U
#define USE_HAL_HSP_STREAM_IT                   0U
#define USE_HAL_HSP_TCU_IT                      0U
#define USE_HAL_HSP_TSC_IT                      0U
#define USE_HAL_HSP_PROCLIST_NOTIFICATION_IT    0U
/**
  * @}
  */

/** @defgroup HAL_I2C_Config HAL I2C Configuration
  * @{
  */
/* ########################## HAL_I2C Config #################################### */
#define USE_HAL_I2C_MODULE                      1U
#define USE_HAL_I2C_CLK_ENABLE_MODEL            HAL_CLK_ENABLE_NO
#define USE_HAL_I2C_REGISTER_CALLBACKS          0U
#define USE_HAL_I2C_USER_DATA                   0U
#define USE_HAL_I2C_GET_LAST_ERRORS             0U
#define USE_HAL_I2C_DMA                         1U
/**
  * @}
  */

/** @defgroup HAL_I3C_Config HAL I3C Configuration
  * @{
  */
/* ########################## HAL_I3C Config #################################### */
#define USE_HAL_I3C_MODULE                      1U
#define USE_HAL_I3C_CLK_ENABLE_MODEL            HAL_CLK_ENABLE_NO
#define USE_HAL_I3C_REGISTER_CALLBACKS          0U
#define USE_HAL_I3C_USER_DATA                   0U
#define USE_HAL_I3C_GET_LAST_ERRORS             0U
#define USE_HAL_I3C_DMA                         1U
/**
  * @}
  */

/** @defgroup HAL_I2S_Config HAL I2S Configuration
  * @{
  */
/* ########################## HAL_I2S Config #################################### */
#define USE_HAL_I2S_MODULE                      1U
#define USE_HAL_I2S_CLK_ENABLE_MODEL            HAL_CLK_ENABLE_NO
#define USE_HAL_I2S_REGISTER_CALLBACKS          0U
#define USE_HAL_I2S_USER_DATA                   0U
#define USE_HAL_I2S_GET_LAST_ERRORS             0U
#define USE_HAL_I2S_OVR_UDR_ERRORS              0U
#define USE_HAL_I2S_DMA                         1U
/**
  * @}
  */

/** @defgroup HAL_IWDG_Config HAL IWDG Configuration
  * @{
  */
/* ########################## HAL_IWDG Config ################################### */
#define USE_HAL_IWDG_MODULE                     1U
#define USE_HAL_IWDG_REGISTER_CALLBACKS         0U
#define USE_HAL_IWDG_USER_DATA                  0U
/* IWDG time unit configuration */
#define USE_HAL_IWDG_TIME_UNIT                  HAL_IWDG_TIME_UNIT_MS
/* IWDG hardware start configuration
   warning: In case of starting IWDG in Hardware mode, make sure that
   USE_HAL_IWDG_HARDWARE_START is aligned with OB activated set for IWDG */
#define USE_HAL_IWDG_HARDWARE_START             0U
/* User can choose the value of the LSI frequency with the USE_HAL_IWDG_LSI_FREQ define:
  - 0U : Dynamic LSI to be computed and set by the user.
  - LSI_VALUE : LSI value of 32KHz.
  - (LSI_VALUE / 128U): LSI value of 250Hz */
#define USE_HAL_IWDG_LSI_FREQ                      LSI_VALUE
/**
  * @}
  */

/** @defgroup HAL_LPTIM_Config HAL LPTIM Configuration
  * @{
  */
/* ########################## HAL_LPTIM Config ################################## */
#define USE_HAL_LPTIM_MODULE                    1U
#define USE_HAL_LPTIM_CLK_ENABLE_MODEL          HAL_CLK_ENABLE_NO
#define USE_HAL_LPTIM_REGISTER_CALLBACKS        0U
#define USE_HAL_LPTIM_USER_DATA                 0U
#define USE_HAL_LPTIM_GET_LAST_ERRORS           0U
#define USE_HAL_LPTIM_DMA                       1U
/**
  * @}
  */

/** @defgroup HAL_MMC_Config HAL MMC Configuration
  * @{
  */
/* ########################## HAL_MMC Config #################################### */
#define USE_HAL_MMC_MODULE                      1U
#define USE_HAL_MMC_CLK_ENABLE_MODEL            HAL_CLK_ENABLE_NO
#define USE_HAL_MMC_REGISTER_CALLBACKS          0U
#define USE_HAL_MMC_USER_DATA                   0U
#define USE_HAL_MMC_GET_LAST_ERRORS             0U
/* Use the MMC in linked-list mode */
#define USE_HAL_MMC_LINKEDLIST                  0U
/* Enable or Disable MMC Custom Frequency */
#define USE_HAL_MMC_AUTO_DETECTION_FREQUENCY    0U
#define USE_HAL_MMC_GET_SPEC_VERSION            0U
#define USE_HAL_MMC_GET_CID                     0U
#define USE_HAL_MMC_RPMB_FEATURE                0U
/**
  * @}
  */

/** @defgroup HAL_NAND_Config HAL NAND Configuration
  * @{
  */
/* ########################## HAL_NAND Config ################################### */
#define USE_HAL_NAND_MODULE                     1U
#define USE_HAL_NAND_USER_DATA                  0U
#define USE_HAL_NAND_ECC                        0U
#define USE_HAL_NAND_EXTRA_CMD                  0U
/**
  * @}
  */

/** @defgroup HAL_NOR_Config HAL NOR Configuration
  * @{
  */
/* ########################## HAL_NOR Config #################################### */
#define USE_HAL_NOR_MODULE                      1U
#define USE_HAL_NOR_USER_DATA                   0U
#define USE_HAL_NOR_PROTECTION                  0U
/**
  * @}
  */

/** @defgroup HAL_PCD_Config HAL PCD Configuration
  * @{
  */
/* ########################## HAL_PCD Config #################################### */
#define USE_HAL_PCD_MODULE                      1U
#define USE_HAL_PCD_REGISTER_CALLBACKS          0U
#define USE_HAL_PCD_USER_DATA                   0U
#define USE_HAL_PCD_GET_LAST_ERRORS             0U
#define USE_HAL_PCD_USB_LPM                     1U
#define USE_HAL_PCD_USB_BCD                     1U
#define USE_HAL_PCD_USB_EP_TYPE_ISOC            1U
#define USE_HAL_PCD_MAX_ENDPOINT_NB             16U
/**
  * @}
  */

/** @defgroup HAL_PWR_Config HAL PWR Configuration
  * @{
  */
/* ########################## HAL_PWR Config #################################### */
#define USE_HAL_PWR_MODULE                      1U
/**
  * @}
  */

/** @defgroup HAL_RAMECC_Config HAL RAMECC Configuration
  * @{
  */
/* ########################## HAL_RAMECC Config ################################# */
#define USE_HAL_RAMECC_MODULE                   1U
/**
  * @}
  */

/** @defgroup HAL_RCC_Config HAL RCC Configuration
  * @{
  */
/* ########################## HAL_RCC Config #################################### */
#define USE_HAL_RCC_MODULE                      1U
/* Use RCC HAL API for Reset function */
#define USE_HAL_RCC_RESET_PERIPH_CLOCK_MANAGEMENT 0U
#define USE_HAL_RCC_RESET_RTC_DOMAIN              0U
/**
  * @}
  */

/** @defgroup HAL_RNG_Config HAL RNG Configuration
  * @{
  */
/* ########################## HAL_RNG Config #################################### */
#define USE_HAL_RNG_MODULE                      1U
#define USE_HAL_RNG_CLK_ENABLE_MODEL            HAL_CLK_ENABLE_NO
#define USE_HAL_RNG_REGISTER_CALLBACKS          0U
#define USE_HAL_RNG_USER_DATA                   0U
#define USE_HAL_RNG_GET_LAST_ERRORS             0U
/**
  * @}
  */

/** @defgroup HAL_RTC_Config HAL RTC Configuration
  * @{
  */
/* ########################## HAL_RTC Config #################################### */
#define USE_HAL_RTC_MODULE                      1U
/**
  * @}
  */

/** @defgroup HAL_SBS_Config HAL SBS Configuration
  * @{
  */
/* ########################## HAL_SBS Config #################################### */
#define USE_HAL_SBS_MODULE                      1U
/**
  * @}
  */

/** @defgroup HAL_SD_Config HAL SD Configuration
  * @{
  */
/* ########################## HAL_SD Config ##################################### */
#define USE_HAL_SD_MODULE                       1U
#define USE_HAL_SD_CLK_ENABLE_MODEL             HAL_CLK_ENABLE_NO
#define USE_HAL_SD_REGISTER_CALLBACKS           0U
#define USE_HAL_SD_USER_DATA                    0U
#define USE_HAL_SD_GET_LAST_ERRORS              0U
/* Use the SD in linked-list mode */
#define USE_HAL_SD_LINKEDLIST                   0U
/* Enable or Disable SD Custom Frequency */
#define USE_HAL_SD_AUTO_DETECTION_FREQUENCY     0U
#define USE_HAL_SD_GET_SPEC_VERSION             0U
#define USE_HAL_SD_GET_CID                      0U
/**
  * @}
  */

/** @defgroup HAL_SDIO_Config HAL SDIO Configuration
  * @{
  */
/* ########################## HAL_SDIO Config ################################### */
#define USE_HAL_SDIO_MODULE                     1U
#define USE_HAL_SDIO_CLK_ENABLE_MODEL           HAL_CLK_ENABLE_NO
#define USE_HAL_SDIO_REGISTER_CALLBACKS         0U
#define USE_HAL_SDIO_USER_DATA                  0U
#define USE_HAL_SDIO_GET_LAST_ERRORS            0U
/**
  * @}
  */

/** @defgroup HAL_SMARTCARD_Config HAL SMARTCARD Configuration
  * @{
  */
/* ########################## HAL_SMARTCARD Config ############################## */
#define USE_HAL_SMARTCARD_MODULE                1U
#define USE_HAL_SMARTCARD_CLK_ENABLE_MODEL      HAL_CLK_ENABLE_NO
#define USE_HAL_SMARTCARD_REGISTER_CALLBACKS    0U
#define USE_HAL_SMARTCARD_USER_DATA             0U
#define USE_HAL_SMARTCARD_GET_LAST_ERRORS       0U
#define USE_HAL_SMARTCARD_DMA                   1U
/* #################### SMARTCARD FIFO configuration ######################## */
#define USE_HAL_SMARTCARD_FIFO                  1U
/**
  * @}
  */

/** @defgroup HAL_SMBUS_Config HAL SMBUS Configuration
  * @{
  */
/* ########################## HAL_SMBUS Config ################################## */
#define USE_HAL_SMBUS_MODULE                    1U
#define USE_HAL_SMBUS_CLK_ENABLE_MODEL          HAL_CLK_ENABLE_NO
#define USE_HAL_SMBUS_REGISTER_CALLBACKS        0U
#define USE_HAL_SMBUS_MASTER_ALERT_CALLBACK     0U
#define USE_HAL_SMBUS_USER_DATA                 0U
#define USE_HAL_SMBUS_GET_LAST_ERRORS           0U
#define USE_HAL_SMBUS_DMA                       1U

/**
  * @}
  */

/** @defgroup HAL_SPI_Config HAL SPI Configuration
  * @{
  */
/* ########################## HAL_SPI Config #################################### */
#define USE_HAL_SPI_MODULE                      1U
#define USE_HAL_SPI_CLK_ENABLE_MODEL            HAL_CLK_ENABLE_NO
#define USE_HAL_SPI_REGISTER_CALLBACKS          0U
#define USE_HAL_SPI_USER_DATA                   0U
#define USE_HAL_SPI_GET_LAST_ERRORS             0U
#define USE_HAL_SPI_DMA                         1U
/* CRC FEATURE: Use to activate CRC feature inside HAL SPI Driver
 * Activated: CRC code is present inside driver
 * Deactivated: CRC code cleaned from driver
 */
#define USE_HAL_SPI_CRC                         0U
/**
  * @}
  */

/** @defgroup HAL_SDRAM_Config HAL SDRAM Configuration
  * @{
  */
/* ########################## HAL_SDRAM Config ################################### */
#define USE_HAL_SDRAM_MODULE                     1U
#define USE_HAL_SDRAM_REGISTER_CALLBACKS         0U
#define USE_HAL_SDRAM_USER_DATA                  0U
/**
  * @}
  */

/** @defgroup HAL_SRAM_Config HAL SRAM Configuration
  * @{
  */
/* ########################## HAL_SRAM Config ################################### */
#define USE_HAL_SRAM_MODULE                     1U
#define USE_HAL_SRAM_USER_DATA                  0U
/**
  * @}
  */

/** @defgroup HAL_TAMP_Config HAL TAMP Configuration
  * @{
  */
/* ########################## HAL_TAMP Config ################################### */
#define USE_HAL_TAMP_MODULE                     1U
/**
  * @}
  */

/** @defgroup HAL_TIM_Config HAL TIM Configuration
  * @{
  */
/* ########################## HAL_TIM Config #################################### */
#define USE_HAL_TIM_MODULE                      1U
#define USE_HAL_TIM_CLK_ENABLE_MODEL            HAL_CLK_ENABLE_NO
#define USE_HAL_TIM_REGISTER_CALLBACKS          0U
#define USE_HAL_TIM_USER_DATA                   0U
#define USE_HAL_TIM_GET_LAST_ERRORS             0U
#define USE_HAL_TIM_DMA                         1U
/**
  * @}
  */

/** @defgroup HAL_UART_Config HAL UART Configuration
  * @{
  */
/* ########################## HAL_UART Config ################################### */
#define USE_HAL_UART_MODULE                     1U
#define USE_HAL_UART_CLK_ENABLE_MODEL           HAL_CLK_ENABLE_NO
#define USE_HAL_UART_REGISTER_CALLBACKS         0U
#define USE_HAL_UART_USER_DATA                  0U
#define USE_HAL_UART_GET_LAST_ERRORS            0U
#define USE_HAL_UART_DMA                        1U
/**
  * @}
  */

/** @defgroup HAL_UCPD_Config HAL UCPD Configuration
  * @{
  */
/* ########################## HAL_UCPD Config ################################### */
#define USE_HAL_UCPD_MODULE                     1U
#define USE_HAL_UCPD_CLK_ENABLE_MODEL           HAL_CLK_ENABLE_NO
#define USE_HAL_UCPD_REGISTER_CALLBACKS         0U
#define USE_HAL_UCPD_USER_DATA                  0U
#define USE_HAL_UCPD_GET_LAST_ERRORS            0U
#define USE_HAL_UCPD_POWER_DELIVERY             1U
/**
  * @}
  */

/** @defgroup HAL_USART_Config HAL USART Configuration
  * @{
  */
/* ########################## HAL_USART Config ################################## */
#define USE_HAL_USART_MODULE                    1U
#define USE_HAL_USART_CLK_ENABLE_MODEL          HAL_CLK_ENABLE_NO
#define USE_HAL_USART_REGISTER_CALLBACKS        0U
#define USE_HAL_USART_USER_DATA                 0U
#define USE_HAL_USART_GET_LAST_ERRORS           0U
#define USE_HAL_USART_DMA                       1U
#define USE_HAL_USART_FIFO                      0U
/**
  * @}
  */

/** @defgroup HAL_VREFBUF_Config HAL VREFBUF Configuration
  * @{
  */
/* ########################## HAL_VREFBUF Config ################################ */
#define USE_HAL_VREFBUF_MODULE                  1U
/**
  * @}
  */

/** @defgroup HAL_WWDG_Config HAL WWDG Configuration
  * @{
  */
/* ########################## HAL_WWDG Config ################################### */
#define USE_HAL_WWDG_MODULE                     1U
#define USE_HAL_WWDG_CLK_ENABLE_MODEL           HAL_CLK_ENABLE_NO
#define USE_HAL_WWDG_REGISTER_CALLBACKS         0U
#define USE_HAL_WWDG_USER_DATA                  0U
/* WWDG time unit configuration */
#define USE_HAL_WWDG_TIME_UNIT                  HAL_WWDG_TIME_UNIT_MS
/* WWDG hardware start configuration
   warning: In case of starting WWDG in Hardware mode, make sure that
   USE_HAL_WWDG_HARDWARE_START is aligned with OB activated set for WWDG */
#define USE_HAL_WWDG_HARDWARE_START             0U
/**
  * @}
  */

/** @defgroup HAL_XSPI_Config HAL XSPI Configuration
  * @{
  */
/* ########################## HAL_XSPI Config ################################### */
#define USE_HAL_XSPI_MODULE                     1U
#define USE_HAL_XSPI_CLK_ENABLE_MODEL           HAL_CLK_ENABLE_NO
#define USE_HAL_XSPI_REGISTER_CALLBACKS         0U
#define USE_HAL_XSPI_USER_DATA                  0U
#define USE_HAL_XSPI_GET_LAST_ERRORS            0U
#define USE_HAL_XSPI_DMA                        1U
#define USE_HAL_XSPI_HYPERBUS                   1U
/**
  * @}
  */

/** @defgroup CORE_FMC_Config CORE FMC Configuration
  * @{
  */
/* ########################## CORE_FMC Config ################################### */
#define USE_FMC_CLK_ENABLE_MODEL                HAL_CLK_ENABLE_NO
/**
  * @}
  */

/**
  * @}
  */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /*  STM32H7PXX_HAL_CONF_H */
