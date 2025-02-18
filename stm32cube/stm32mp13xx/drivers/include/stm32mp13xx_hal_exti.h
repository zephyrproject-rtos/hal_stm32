/**
  ******************************************************************************
  * @file    stm32mp13xx_hal_exti.h
  * @author  MCD Application Team
  * @brief   Header file of EXTI HAL module.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef STM32MP13xx_HAL_EXTI_H
#define STM32MP13xx_HAL_EXTI_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32mp13xx_hal_def.h"

/** @addtogroup STM32MP13xx_HAL_Driver
  * @{
  */

/** @defgroup EXTI EXTI
  * @brief EXTI HAL module driver
  * @{
  */

/* Exported types ------------------------------------------------------------*/

/** @defgroup EXTI_Exported_Types EXTI Exported Types
  * @{
  */
typedef enum
{
  HAL_EXTI_COMMON_CB_ID          = 0x00U,
  HAL_EXTI_RISING_CB_ID          = 0x01U,
  HAL_EXTI_FALLING_CB_ID         = 0x02U,
} EXTI_CallbackIDTypeDef;


/**
  * @brief  EXTI Handle structure definition
  */
typedef struct
{
  uint32_t Line;                    /*!<  Exti line number */
  void (* RisingCallback)(void);    /*!<  Exti rising callback */
  void (* FallingCallback)(void);   /*!<  Exti falling callback */
} EXTI_HandleTypeDef;

/**
  * @brief  EXTI Configuration structure definition
  */
typedef struct
{
  uint32_t Line;      /*!< The Exti line to be configured. This parameter
                           can be a value of @ref EXTI_Line */
  uint32_t Mode;      /*!< The Exit Mode to be configured for a core.
                           This parameter can be a combination of @ref EXTI_Mode */
  uint32_t Trigger;   /*!< The Exti Trigger to be configured. This parameter
                           can be a value of @ref EXTI_Trigger */
  uint32_t GPIOSel;   /*!< The Exti GPIO multiplexer selection to be configured.
                           This parameter is only possible for line 0 to 15. It
                           can be a value of @ref EXTI_GPIOSel */
} EXTI_ConfigTypeDef;

/**
  * @}
  */

/* Exported constants --------------------------------------------------------*/
/** @defgroup EXTI_Exported_Constants EXTI Exported Constants
  * @{
  */

/** @defgroup EXTI_Line  EXTI Line
  * @{
  */
#define EXTI_LINE_0                         (EXTI_GPIO     | EXTI_EVENT | EXTI_REG1 | 0x00U)  /* EXTI_GPIO */
#define EXTI_LINE_1                         (EXTI_GPIO     | EXTI_EVENT | EXTI_REG1 | 0x01U)  /* EXTI_GPIO */
#define EXTI_LINE_2                         (EXTI_GPIO     | EXTI_EVENT | EXTI_REG1 | 0x02U)  /* EXTI_GPIO */
#define EXTI_LINE_3                         (EXTI_GPIO     | EXTI_EVENT | EXTI_REG1 | 0x03U)  /* EXTI_GPIO */
#define EXTI_LINE_4                         (EXTI_GPIO     | EXTI_EVENT | EXTI_REG1 | 0x04U)  /* EXTI_GPIO */
#define EXTI_LINE_5                         (EXTI_GPIO     | EXTI_EVENT | EXTI_REG1 | 0x05U)  /* EXTI_GPIO */
#define EXTI_LINE_6                         (EXTI_GPIO     | EXTI_EVENT | EXTI_REG1 | 0x06U)  /* EXTI_GPIO */
#define EXTI_LINE_7                         (EXTI_GPIO     | EXTI_EVENT | EXTI_REG1 | 0x07U)  /* EXTI_GPIO */
#define EXTI_LINE_8                         (EXTI_GPIO     | EXTI_EVENT | EXTI_REG1 | 0x08U)  /* EXTI_GPIO */
#define EXTI_LINE_9                         (EXTI_GPIO     | EXTI_EVENT | EXTI_REG1 | 0x09U)  /* EXTI_GPIO */
#define EXTI_LINE_10                        (EXTI_GPIO     | EXTI_EVENT | EXTI_REG1 | 0x0AU)  /* EXTI_GPIO */
#define EXTI_LINE_11                        (EXTI_GPIO     | EXTI_EVENT | EXTI_REG1 | 0x0BU)  /* EXTI_GPIO */
#define EXTI_LINE_12                        (EXTI_GPIO     | EXTI_EVENT | EXTI_REG1 | 0x0CU)  /* EXTI_GPIO */
#define EXTI_LINE_13                        (EXTI_GPIO     | EXTI_EVENT | EXTI_REG1 | 0x0DU)  /* EXTI_GPIO */
#define EXTI_LINE_14                        (EXTI_GPIO     | EXTI_EVENT | EXTI_REG1 | 0x0EU)  /* EXTI_GPIO */
#define EXTI_LINE_15                        (EXTI_GPIO     | EXTI_EVENT | EXTI_REG1 | 0x0FU)  /* EXTI_GPIO */
#define EXTI_LINE_16                        (EXTI_CONFIG   |              EXTI_REG1 | 0x10U)  /* PVD and AVD */
#define EXTI_LINE_17                        (EXTI_DIRECT   | EXTI_EVENT | EXTI_REG1 | 0x11U)  /* RTC timestamp and\
                                                                                                 SecureError wakeup */
#define EXTI_LINE_18                        (EXTI_DIRECT   | EXTI_EVENT | EXTI_REG1 | 0x12U)  /* TAMP tamper and\
                                                                                                 SecureError wakeup */
#define EXTI_LINE_19                        (EXTI_DIRECT   | EXTI_EVENT | EXTI_REG1 | 0x13U)  /* RTC Wakeup timer and\
                                                                                                 Alarms (A and B) and\
                                                                                                 SecureError wakeup */
#define EXTI_LINE_20                        (EXTI_RESERVED | EXTI_REG1 | 0x14U)  /* RESERVED */
#define EXTI_LINE_21                        (EXTI_DIRECT   | EXTI_REG1 | 0x15U)  /* I2C1 wakeup */
#define EXTI_LINE_22                        (EXTI_DIRECT   | EXTI_REG1 | 0x16U)  /* I2C2 wakeup */
#define EXTI_LINE_23                        (EXTI_DIRECT   | EXTI_REG1 | 0x17U)  /* I2C3 wakeup */
#define EXTI_LINE_24                        (EXTI_DIRECT   | EXTI_REG1 | 0x18U)  /* I2C4 wakeup */
#define EXTI_LINE_25                        (EXTI_DIRECT   | EXTI_REG1 | 0x19U)  /* I2C5 wakeup */
#define EXTI_LINE_26                        (EXTI_DIRECT   | EXTI_REG1 | 0x1AU)  /* USART1 wakeup */
#define EXTI_LINE_27                        (EXTI_DIRECT   | EXTI_REG1 | 0x1BU)  /* USART2 wakeup */
#define EXTI_LINE_28                        (EXTI_DIRECT   | EXTI_REG1 | 0x1CU)  /* USART3 wakeup */
#define EXTI_LINE_29                        (EXTI_DIRECT   | EXTI_REG1 | 0x1DU)  /* USART6 wakeup */
#define EXTI_LINE_30                        (EXTI_DIRECT   | EXTI_REG1 | 0x1EU)  /* UART4 wakeup */
#define EXTI_LINE_31                        (EXTI_DIRECT   | EXTI_REG1 | 0x1FU)  /* UART5 wakeup */
#define EXTI_LINE_32                        (EXTI_DIRECT   | EXTI_REG2 | 0x00U)  /* UART7 wakeup */
#define EXTI_LINE_33                        (EXTI_DIRECT   | EXTI_REG2 | 0x01U)  /* UART8 wakeup */
#define EXTI_LINE_34                        (EXTI_RESERVED | EXTI_REG2 | 0x02U)  /* RESERVED */
#define EXTI_LINE_35                        (EXTI_RESERVED | EXTI_REG2 | 0x03U)  /* RESERVED */
#define EXTI_LINE_36                        (EXTI_DIRECT   | EXTI_REG2 | 0x04U)  /* SPI1 wakeup */
#define EXTI_LINE_37                        (EXTI_DIRECT   | EXTI_REG2 | 0x05U)  /* SPI2 wakeup */
#define EXTI_LINE_38                        (EXTI_DIRECT   | EXTI_REG2 | 0x06U)  /* SPI3 wakeup */
#define EXTI_LINE_39                        (EXTI_DIRECT   | EXTI_REG2 | 0x07U)  /* SPI4 wakeup */
#define EXTI_LINE_40                        (EXTI_DIRECT   | EXTI_REG2 | 0x08U)  /* SPI5 wakeup */
#define EXTI_LINE_41                        (EXTI_RESERVED | EXTI_REG2 | 0x09U)  /* RESERVED */
#define EXTI_LINE_42                        (EXTI_DIRECT   | EXTI_REG2 | 0x0AU)  /* USBH port 1 wakeup */
#define EXTI_LINE_43                        (EXTI_DIRECT   | EXTI_REG2 | 0x0BU)  /* USBH port 2 wakeup */
#define EXTI_LINE_44                        (EXTI_DIRECT   | EXTI_REG2 | 0x0CU)  /* OTG wakeup */
#define EXTI_LINE_45                        (EXTI_DIRECT   | EXTI_REG2 | 0x0DU)  /* IWDG1 early wake */
#define EXTI_LINE_46                        (EXTI_DIRECT   | EXTI_REG2 | 0x0EU)  /* IWDG1 early wake */
#define EXTI_LINE_47                        (EXTI_DIRECT   | EXTI_REG2 | 0x0FU)  /* LPTIM1 wakeup */
#define EXTI_LINE_48                        (EXTI_DIRECT   | EXTI_REG2 | 0x10U)  /* LPTIM2 wakeup */
#define EXTI_LINE_49                        (EXTI_RESERVED | EXTI_REG2 | 0x11U)  /* RESERVED */
#define EXTI_LINE_50                        (EXTI_DIRECT   | EXTI_REG2 | 0x12U)  /* LPTIM3 wakeup */
#define EXTI_LINE_51                        (EXTI_RESERVED | EXTI_REG2 | 0x13U)  /* RESERVED */
#define EXTI_LINE_52                        (EXTI_DIRECT   | EXTI_REG2 | 0x14U)  /* LPTIM4 wakeup */
#define EXTI_LINE_53                        (EXTI_DIRECT   | EXTI_REG2 | 0x15U)  /* LPTIM5 wakeup */
#define EXTI_LINE_54                        (EXTI_RESERVED | EXTI_REG2 | 0x16U)  /* RESERVED */
#define EXTI_LINE_55                        (EXTI_DIRECT   | EXTI_REG2 | 0x17U)  /* WKUP1 wakeup */
#define EXTI_LINE_56                        (EXTI_DIRECT   | EXTI_REG2 | 0x18U)  /* WKUP2 wakeup */
#define EXTI_LINE_57                        (EXTI_DIRECT   | EXTI_REG2 | 0x19U)  /* WKUP3 wakeup */
#define EXTI_LINE_58                        (EXTI_DIRECT   | EXTI_REG2 | 0x1AU)  /* WKUP4 wakeup */
#define EXTI_LINE_59                        (EXTI_DIRECT   | EXTI_REG2 | 0x1BU)  /* WKUP5 wakeup */
#define EXTI_LINE_60                        (EXTI_DIRECT   | EXTI_REG2 | 0x1CU)  /* WKUP6 wakeup */
#define EXTI_LINE_61                        (EXTI_RESERVED | EXTI_REG2 | 0x1DU)  /* RESERVED */
#define EXTI_LINE_62                        (EXTI_RESERVED | EXTI_REG2 | 0x1EU)  /* RESERVED */
#define EXTI_LINE_63                        (EXTI_RESERVED | EXTI_REG2 | 0x1FU)  /* RESERVED */
#define EXTI_LINE_64                        (EXTI_RESERVED | EXTI_REG3 | 0x00U)  /* RESERVED */
#define EXTI_LINE_65                        (EXTI_RESERVED | EXTI_REG3 | 0x01U)  /* RESERVED */
#define EXTI_LINE_66                        (EXTI_RESERVED | EXTI_REG3 | 0x02U)  /* RESERVED */
#define EXTI_LINE_67                        (EXTI_RESERVED | EXTI_REG3 | 0x03U)  /* RESERVED */
#define EXTI_LINE_68                        (EXTI_DIRECT   | EXTI_REG3 | 0x04U)  /* ETH1 pmt_intr_o wakeup */
#define EXTI_LINE_69                        (EXTI_DIRECT   | EXTI_REG3 | 0x05U)  /* ETH1 lpi_intr_o wakeup */
#define EXTI_LINE_70                        (EXTI_DIRECT   | EXTI_REG3 | 0x06U)  /* ETH2 pmt_intr_o wakeup */
#define EXTI_LINE_71                        (EXTI_DIRECT   | EXTI_REG3 | 0x07U)  /* ETH2 lpi_intr_o wakeup */
#define EXTI_LINE_72                        (EXTI_DIRECT   | EXTI_REG3 | 0x08U)  /* DTS wakeup */
#define EXTI_LINE_73                        (EXTI_RESERVED | EXTI_REG3 | 0x09U)  /* RESERVED */
#define EXTI_LINE_74                        (EXTI_RESERVED | EXTI_REG3 | 0x0AU)  /* RESERVED */
#define EXTI_LINE_75                        (EXTI_DIRECT   | EXTI_REG3 | 0x0BU)  /* CDBGPWRUPREQ event */


/**
  * @}
  */

/** @defgroup EXTI_Mode  EXTI Mode
  * @{
  */
#define EXTI_MODE_NONE                      0x00000000U
#define EXTI_MODE_INTERRUPT                 0x00000001U
#define EXTI_MODE_EVENT                     0x00000002U

/**
  * @}
  */

/** @defgroup EXTI_Trigger  EXTI Trigger
  * @{
  */
#define EXTI_TRIGGER_NONE                   0x00000000U
#define EXTI_TRIGGER_RISING                 0x00000001U
#define EXTI_TRIGGER_FALLING                0x00000002U
#define EXTI_TRIGGER_RISING_FALLING         (EXTI_TRIGGER_RISING | EXTI_TRIGGER_FALLING)
/**
  * @}
  */

/** @defgroup EXTI_GPIOSel  EXTI GPIOSel
  * @brief
  * @{
  */
#define EXTI_GPIOA                          0x00000000U
#define EXTI_GPIOB                          0x00000001U
#define EXTI_GPIOC                          0x00000002U
#define EXTI_GPIOD                          0x00000003U
#define EXTI_GPIOE                          0x00000004U
#define EXTI_GPIOF                          0x00000005U
#define EXTI_GPIOG                          0x00000006U
#define EXTI_GPIOH                          0x00000007U
#define EXTI_GPIOI                          0x00000008U
/**
  * @}
  */

/**
  * @}
  */

/* Exported macro ------------------------------------------------------------*/
/** @defgroup EXTI_Exported_Macros EXTI Exported Macros
  * @{
  */

/**
  * @}
  */

/* Private constants --------------------------------------------------------*/
/** @defgroup EXTI_Private_Constants EXTI Private Constants
  * @{
  */
/**
  * @brief  EXTI Line property definition
  */
#define EXTI_PROPERTY_SHIFT                 24U
#define EXTI_DIRECT                         (0x01UL << EXTI_PROPERTY_SHIFT)
#define EXTI_CONFIG                         (0x02UL << EXTI_PROPERTY_SHIFT)
#define EXTI_GPIO                           ((0x04UL << EXTI_PROPERTY_SHIFT) | EXTI_CONFIG)
#define EXTI_RESERVED                       (0x08UL << EXTI_PROPERTY_SHIFT)
#define EXTI_PROPERTY_MASK                  (EXTI_DIRECT | EXTI_CONFIG | EXTI_GPIO)

/**
  * @brief  EXTI Event presence definition
  */
#define EXTI_EVENT_PRESENCE_SHIFT           28U
#define EXTI_EVENT                          (0x01UL << EXTI_EVENT_PRESENCE_SHIFT)
#define EXTI_EVENT_PRESENCE_MASK            (EXTI_EVENT)

/**
  * @brief  EXTI Register and bit usage
  */
#define EXTI_REG_SHIFT                      16U
#define EXTI_REG1                           (0x00UL << EXTI_REG_SHIFT)
#define EXTI_REG2                           (0x01UL << EXTI_REG_SHIFT)
#define EXTI_REG3                           (0x02UL << EXTI_REG_SHIFT)
#define EXTI_REG_MASK                       (EXTI_REG1 | EXTI_REG2 | EXTI_REG3)
#define EXTI_PIN_MASK                       0x0000001FUL

/**
  * @brief  EXTI Mask for interrupt & event mode
  */
#define EXTI_MODE_MASK                      (EXTI_MODE_EVENT | EXTI_MODE_INTERRUPT)

/**
  * @brief  EXTI Mask for trigger possibilities
  */
#define EXTI_TRIGGER_MASK                   (EXTI_TRIGGER_RISING | EXTI_TRIGGER_FALLING)

/**
  * @brief  EXTI Line number
  */
#define EXTI_LINE_NB                        76UL

/**
  * @}
  */

/* Private macros ------------------------------------------------------------*/
/** @defgroup EXTI_Private_Macros EXTI Private Macros
  * @{
  */
#define IS_EXTI_LINE(__EXTI_LINE__)          ((((__EXTI_LINE__) & ~(EXTI_PROPERTY_MASK | EXTI_EVENT_PRESENCE_MASK | \
                                                                    EXTI_REG_MASK | EXTI_PIN_MASK)) == 0x00UL) && \
                                              ((((__EXTI_LINE__) & EXTI_PROPERTY_MASK) == EXTI_DIRECT)   || \
                                               (((__EXTI_LINE__) & EXTI_PROPERTY_MASK) == EXTI_CONFIG)   || \
                                               (((__EXTI_LINE__) & EXTI_PROPERTY_MASK) == EXTI_GPIO))    && \
                                              (((__EXTI_LINE__) & (EXTI_REG_MASK | EXTI_PIN_MASK))      < \
                                               (((EXTI_LINE_NB / 32U) << EXTI_REG_SHIFT) | (EXTI_LINE_NB % 32UL))))

#define IS_EXTI_MODE(__EXTI_LINE__)          ((((__EXTI_LINE__) & EXTI_MODE_MASK) != 0x00UL) && \
                                              (((__EXTI_LINE__) & ~EXTI_MODE_MASK) == 0x00UL))

#define IS_EXTI_TRIGGER(__EXTI_LINE__)       (((__EXTI_LINE__) & ~EXTI_TRIGGER_MASK) == 0x00UL)

#define IS_EXTI_PENDING_EDGE(__EXTI_LINE__)  (((__EXTI_LINE__) == EXTI_TRIGGER_RISING) || \
                                              ((__EXTI_LINE__) == EXTI_TRIGGER_FALLING))

#define IS_EXTI_CONFIG_LINE(__EXTI_LINE__)   (((__EXTI_LINE__) & EXTI_CONFIG) != 0x00UL)

#define IS_EXTI_GPIO_PORT(__PORT__)     (((__PORT__) == EXTI_GPIOA) || \
                                         ((__PORT__) == EXTI_GPIOB) || \
                                         ((__PORT__) == EXTI_GPIOC) || \
                                         ((__PORT__) == EXTI_GPIOD) || \
                                         ((__PORT__) == EXTI_GPIOE) || \
                                         ((__PORT__) == EXTI_GPIOF) || \
                                         ((__PORT__) == EXTI_GPIOG) || \
                                         ((__PORT__) == EXTI_GPIOH) || \
                                         ((__PORT__) == EXTI_GPIOI))
#define IS_EXTI_GPIO_PIN(__PIN__)       ((__PIN__) < 16UL)

/**
  * @}
  */


/* Exported functions --------------------------------------------------------*/
/** @defgroup EXTI_Exported_Functions EXTI Exported Functions
  * @brief    EXTI Exported Functions
  * @{
  */

/** @defgroup EXTI_Exported_Functions_Group1 Configuration functions
  * @brief    Configuration functions
  * @{
  */
/* Configuration functions ****************************************************/
HAL_StatusTypeDef HAL_EXTI_SetConfigLine(EXTI_HandleTypeDef *hexti, EXTI_ConfigTypeDef *pExtiConfig);
HAL_StatusTypeDef HAL_EXTI_GetConfigLine(const EXTI_HandleTypeDef *hexti, EXTI_ConfigTypeDef *pExtiConfig);
HAL_StatusTypeDef HAL_EXTI_ClearConfigLine(const EXTI_HandleTypeDef *hexti);
HAL_StatusTypeDef HAL_EXTI_RegisterCallback(EXTI_HandleTypeDef *hexti, EXTI_CallbackIDTypeDef CallbackID,
                                            void (*pPendingCbfn)(void));
HAL_StatusTypeDef HAL_EXTI_GetHandle(EXTI_HandleTypeDef *hexti, uint32_t ExtiLine);
/**
  * @}
  */

/** @defgroup EXTI_Exported_Functions_Group2 IO operation functions
  * @brief    IO operation functions
  * @{
  */
/* IO operation functions *****************************************************/
void              HAL_EXTI_IRQHandler(const EXTI_HandleTypeDef *hexti);
uint32_t          HAL_EXTI_GetPending(const EXTI_HandleTypeDef *hexti, uint32_t Edge);
void              HAL_EXTI_ClearPending(const EXTI_HandleTypeDef *hexti, uint32_t Edge);
void              HAL_EXTI_GenerateSWI(const EXTI_HandleTypeDef *hexti);

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /* STM32MP13xx_HAL_EXTI_H */
