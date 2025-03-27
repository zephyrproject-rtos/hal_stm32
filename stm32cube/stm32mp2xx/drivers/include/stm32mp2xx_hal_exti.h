/**
  ******************************************************************************
  * @file    stm32mp2xx_hal_exti.h
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
#ifndef STM32MP2xx_HAL_EXTI_H
#define STM32MP2xx_HAL_EXTI_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32mp2xx_hal_def.h"

/** @addtogroup STM32MP2xx_HAL_Driver
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
/**
  * @brief  EXTI callback ID definition
  */
typedef enum
{
  HAL_EXTI_COMMON_CB_ID          = 0x00U,
  HAL_EXTI_RISING_CB_ID          = 0x01U,   /*!<  Exti rising callback ID */
  HAL_EXTI_FALLING_CB_ID         = 0x02U,   /*!<  Exti falling callback ID */
} EXTI_CallbackIDTypeDef;


/**
  * @brief  EXTI Handle structure definition
  */
typedef struct
{
  EXTI_TypeDef  *Instance;          /*!< Register base address */
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
                           can be a value of @ref EXTI1_Line or EXTI2_Line */
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

/** @defgroup EXTI1_Line  EXTI1 Line
  * @{
  */
#if ! defined (STM32MP2XX_ASSY3_1_0 )
/* GPIO */
#define EXTI1_LINE_0                         (EXTI_EXTI1|EXTI_GPIO     | EXTI_EVENT | 0x00u)
#define EXTI1_LINE_1                         (EXTI_EXTI1|EXTI_GPIO     | EXTI_EVENT | 0x01u)
#define EXTI1_LINE_2                         (EXTI_EXTI1|EXTI_GPIO     | EXTI_EVENT | 0x02u)
#define EXTI1_LINE_3                         (EXTI_EXTI1|EXTI_GPIO     | EXTI_EVENT | 0x03u)
#define EXTI1_LINE_4                         (EXTI_EXTI1|EXTI_GPIO     | EXTI_EVENT | 0x04u)
#define EXTI1_LINE_5                         (EXTI_EXTI1|EXTI_GPIO     | EXTI_EVENT | 0x05u)
#define EXTI1_LINE_6                         (EXTI_EXTI1|EXTI_GPIO     | EXTI_EVENT | 0x06u)
#define EXTI1_LINE_7                         (EXTI_EXTI1|EXTI_GPIO     | EXTI_EVENT | 0x07u)
#define EXTI1_LINE_8                         (EXTI_EXTI1|EXTI_GPIO     | EXTI_EVENT | 0x08u)
#define EXTI1_LINE_9                         (EXTI_EXTI1|EXTI_GPIO     | EXTI_EVENT | 0x09u)
#define EXTI1_LINE_10                        (EXTI_EXTI1|EXTI_GPIO     | EXTI_EVENT | 0x0Au)
#define EXTI1_LINE_11                        (EXTI_EXTI1|EXTI_GPIO     | EXTI_EVENT | 0x0Bu)
#define EXTI1_LINE_12                        (EXTI_EXTI1|EXTI_GPIO     | EXTI_EVENT | 0x0Cu)
#define EXTI1_LINE_13                        (EXTI_EXTI1|EXTI_GPIO     | EXTI_EVENT | 0x0Du)
#define EXTI1_LINE_14                        (EXTI_EXTI1|EXTI_GPIO     | EXTI_EVENT | 0x0Eu)
#define EXTI1_LINE_15                        (EXTI_EXTI1|EXTI_GPIO     | EXTI_EVENT | 0x0Fu)
#else   /* !defined (STM32MP2XX_ASSY3_1_0 ) */
#define EXTI1_LINE_0                         (EXTI_EXTI1|EXTI_RESERVED |              0x00u)
#define EXTI1_LINE_1                         (EXTI_EXTI1|EXTI_RESERVED |              0x01u)
#define EXTI1_LINE_2                         (EXTI_EXTI1|EXTI_RESERVED |              0x02u)
#define EXTI1_LINE_3                         (EXTI_EXTI1|EXTI_RESERVED |              0x03u)
#define EXTI1_LINE_4                         (EXTI_EXTI1|EXTI_RESERVED |              0x04u)
#define EXTI1_LINE_5                         (EXTI_EXTI1|EXTI_RESERVED |              0x05u)
#define EXTI1_LINE_6                         (EXTI_EXTI1|EXTI_RESERVED |              0x06u)
#define EXTI1_LINE_7                         (EXTI_EXTI1|EXTI_RESERVED |              0x07u)
#define EXTI1_LINE_8                         (EXTI_EXTI1|EXTI_RESERVED |              0x08u)
#define EXTI1_LINE_9                         (EXTI_EXTI1|EXTI_RESERVED |              0x09u)
#define EXTI1_LINE_10                        (EXTI_EXTI1|EXTI_RESERVED |              0x0Au)
#define EXTI1_LINE_11                        (EXTI_EXTI1|EXTI_RESERVED |              0x0Bu)
#define EXTI1_LINE_12                        (EXTI_EXTI1|EXTI_RESERVED |              0x0Cu)
#define EXTI1_LINE_13                        (EXTI_EXTI1|EXTI_RESERVED |              0x0Du)
#define EXTI1_LINE_14                        (EXTI_EXTI1|EXTI_RESERVED |              0x0Eu)
#define EXTI1_LINE_15                        (EXTI_EXTI1|EXTI_RESERVED |              0x0Fu)
#endif  /* !defined (STM32MP2XX_ASSY3_1_0 ) */
#define EXTI1_LINE_16                        (EXTI_EXTI1|EXTI_CONFIG   |              0x10u)
#define EXTI1_LINE_17                        (EXTI_EXTI1|EXTI_CONFIG   |              0x11u)
#if (STM32MP2_DEV_ID == 0x503)
#define EXTI1_LINE_18                        (EXTI_EXTI1|EXTI_DIRECT   |              0x12u)
#else
#define EXTI1_LINE_18                        (EXTI_EXTI1|EXTI_CONFIG   |              0x12u)
#endif
#if ! defined (STM32MP2XX_ASSY3_1_0 )
#define EXTI1_LINE_19                        (EXTI_EXTI1|EXTI_DIRECT   |              0x13u)
#else   /* !defined (STM32MP2XX_ASSY3_1_0 ) */
#define EXTI1_LINE_19                        (EXTI_EXTI1|EXTI_CONFIG   |              0x13u)
#endif  /* !defined (STM32MP2XX_ASSY3_1_0 ) */
#define EXTI1_LINE_20                        (EXTI_EXTI1|EXTI_RESERVED |              0x14u)
#define EXTI1_LINE_21                        (EXTI_EXTI1|EXTI_DIRECT   |              0x15u)
#define EXTI1_LINE_22                        (EXTI_EXTI1|EXTI_DIRECT   |              0x16u)
#define EXTI1_LINE_23                        (EXTI_EXTI1|EXTI_DIRECT   |              0x17u)
#if (STM32MP2_DEV_ID == 0x503)
#define EXTI1_LINE_24                        (EXTI_EXTI1|EXTI_RESERVED |              0x18u)
#define EXTI1_LINE_25                        (EXTI_EXTI1|EXTI_RESERVED |              0x19u)
#else
#define EXTI1_LINE_24                        (EXTI_EXTI1|EXTI_DIRECT   |              0x18u)
#define EXTI1_LINE_25                        (EXTI_EXTI1|EXTI_DIRECT   |              0x19u)
#endif
#define EXTI1_LINE_26                        (EXTI_EXTI1|EXTI_DIRECT   |              0x1Au)
#define EXTI1_LINE_27                        (EXTI_EXTI1|EXTI_DIRECT   |              0x1Bu)
#define EXTI1_LINE_28                        (EXTI_EXTI1|EXTI_DIRECT   |              0x1Cu)
#define EXTI1_LINE_29                        (EXTI_EXTI1|EXTI_DIRECT   |              0x1Du)
#define EXTI1_LINE_30                        (EXTI_EXTI1|EXTI_DIRECT   |              0x1Eu)
#define EXTI1_LINE_31                        (EXTI_EXTI1|EXTI_DIRECT   |              0x1Fu)
#define EXTI1_LINE_32                        (EXTI_EXTI1|EXTI_DIRECT   |              0x20u)
#if (STM32MP2_DEV_ID == 0x503)
#define EXTI1_LINE_33                        (EXTI_EXTI1|EXTI_RESERVED |              0x21u)
#define EXTI1_LINE_34                        (EXTI_EXTI1|EXTI_RESERVED |              0x22u)
#else
#define EXTI1_LINE_33                        (EXTI_EXTI1|EXTI_DIRECT   |              0x21u)
#define EXTI1_LINE_34                        (EXTI_EXTI1|EXTI_DIRECT   |              0x22u)
#endif
#define EXTI1_LINE_35                        (EXTI_EXTI1|EXTI_RESERVED |              0x23u)
#define EXTI1_LINE_36                        (EXTI_EXTI1|EXTI_DIRECT   |              0x24u)
#define EXTI1_LINE_37                        (EXTI_EXTI1|EXTI_DIRECT   |              0x25u)
#define EXTI1_LINE_38                        (EXTI_EXTI1|EXTI_DIRECT   |              0x26u)
#define EXTI1_LINE_39                        (EXTI_EXTI1|EXTI_DIRECT   |              0x27u)
#define EXTI1_LINE_40                        (EXTI_EXTI1|EXTI_DIRECT   |              0x28u)
#define EXTI1_LINE_41                        (EXTI_EXTI1|EXTI_DIRECT   |              0x29u)
#if (STM32MP2_DEV_ID == 0x503)
#define EXTI1_LINE_42                        (EXTI_EXTI1|EXTI_RESERVED |              0x2Au)
#else
#define EXTI1_LINE_42                        (EXTI_EXTI1|EXTI_DIRECT   |              0x2Au)
#endif
#define EXTI1_LINE_43                        (EXTI_EXTI1|EXTI_CONFIG   |              0x2Bu)
#define EXTI1_LINE_44                        (EXTI_EXTI1|EXTI_CONFIG   |              0x2Cu)
#if (STM32MP2_DEV_ID == 0x503)
#define EXTI1_LINE_45                        (EXTI_EXTI1|EXTI_RESERVED |              0x2Du)
#else
#define EXTI1_LINE_45                        (EXTI_EXTI1|EXTI_CONFIG   |              0x2Du)
#endif
#if ! defined (STM32MP2XX_ASSY3_1_0 )
#if (STM32MP2_DEV_ID == 0x503)
#define EXTI1_LINE_46                        (EXTI_EXTI1|EXTI_RESERVED |              0x2Eu)
#else
#define EXTI1_LINE_46                        (EXTI_EXTI1|EXTI_DIRECT   |              0x2Eu)
#endif
#else   /* !defined (STM32MP2XX_ASSY3_1_0 ) */
#define EXTI1_LINE_46                        (EXTI_EXTI1|EXTI_CONFIG   |              0x2Eu)
#endif  /* !defined (STM32MP2XX_ASSY3_1_0 ) */
#define EXTI1_LINE_47                        (EXTI_EXTI1|EXTI_DIRECT   |              0x2Fu)
#define EXTI1_LINE_48                        (EXTI_EXTI1|EXTI_DIRECT   |              0x30u)
#if (STM32MP2_DEV_ID == 0x503)
#define EXTI1_LINE_49                        (EXTI_EXTI1|EXTI_RESERVED |              0x31u)
#define EXTI1_LINE_50                        (EXTI_EXTI1|EXTI_RESERVED |              0x32u)
#else
#define EXTI1_LINE_49                        (EXTI_EXTI1|EXTI_DIRECT   |              0x31u)
#define EXTI1_LINE_50                        (EXTI_EXTI1|EXTI_DIRECT   |              0x32u)
#endif
#define EXTI1_LINE_51                        (EXTI_EXTI1|EXTI_RESERVED |              0x33u)
#define EXTI1_LINE_52                        (EXTI_EXTI1|EXTI_DIRECT   |              0x34u)
#define EXTI1_LINE_53                        (EXTI_EXTI1|EXTI_DIRECT   |              0x35u)
#define EXTI1_LINE_54                        (EXTI_EXTI1|EXTI_DIRECT   |              0x36u)
#define EXTI1_LINE_55                        (EXTI_EXTI1|EXTI_DIRECT   |              0x37u)
#define EXTI1_LINE_56                        (EXTI_EXTI1|EXTI_DIRECT   |              0x38u)
#define EXTI1_LINE_57                        (EXTI_EXTI1|EXTI_DIRECT   |              0x39u)
#define EXTI1_LINE_58                        (EXTI_EXTI1|EXTI_RESERVED |              0x3Au)
#if defined (CORE_CM33)
#define EXTI1_LINE_59                        (EXTI_EXTI1|EXTI_RESERVED |              0x3Bu)
#define EXTI1_LINE_60                        (EXTI_EXTI1|EXTI_DIRECT   |              0x3Cu)
#define EXTI1_LINE_61                        (EXTI_EXTI1|EXTI_RESERVED |              0x3Du)
#define EXTI1_LINE_62                        (EXTI_EXTI1|EXTI_DIRECT   |              0x3Eu)
#else   /* CORE_CM33 */
#define EXTI1_LINE_59                        (EXTI_EXTI1|EXTI_DIRECT   |              0x3Bu)
#define EXTI1_LINE_60                        (EXTI_EXTI1|EXTI_RESERVED |              0x3Cu)
#define EXTI1_LINE_61                        (EXTI_EXTI1|EXTI_DIRECT   |              0x3Du)
#define EXTI1_LINE_62                        (EXTI_EXTI1|EXTI_RESERVED |              0x3Eu)
#endif  /* CORE_CM33 */
#define EXTI1_LINE_63                        (EXTI_EXTI1|EXTI_RESERVED |              0x3Fu)
#if defined (CORE_CA35)
#define EXTI1_LINE_64                        (EXTI_EXTI1|EXTI_CONFIG   |              0x40u)
#else   /* CORE_CA35 */
#define EXTI1_LINE_64                        (EXTI_EXTI1|EXTI_RESERVED |              0x40u)
#endif  /* CORE_CA35 */
#if defined (CORE_CM33)
#define EXTI1_LINE_65                        (EXTI_EXTI1|EXTI_CONFIG   | EXTI_EVENT | 0x41u)
#else   /* CORE_CM33 */
#define EXTI1_LINE_65                        (EXTI_EXTI1|EXTI_RESERVED |              0x41u)
#endif  /* CORE_CM33 */
#define EXTI1_LINE_66                        (EXTI_EXTI1|EXTI_RESERVED |              0x42u)
#if defined (CORE_CA35)
#define EXTI1_LINE_67                        (EXTI_EXTI1|EXTI_CONFIG   |              0x43u)
#else   /* CORE_CA35 */
#define EXTI1_LINE_67                        (EXTI_EXTI1|EXTI_RESERVED |              0x43u)
#endif  /* CORE_CA35 */
#define EXTI1_LINE_68                        (EXTI_EXTI1|EXTI_DIRECT   |              0x44u)
#if ! defined (STM32MP2XX_ASSY3_1_0 )
#define EXTI1_LINE_69                        (EXTI_EXTI1|EXTI_RESERVED |              0x45u)
#else   /* !defined (STM32MP2XX_ASSY3_1_0 ) */
#define EXTI1_LINE_69                        (EXTI_EXTI1|EXTI_DIRECT   |              0x45u)
#endif  /* !defined (STM32MP2XX_ASSY3_1_0 ) */
#define EXTI1_LINE_70                        (EXTI_EXTI1|EXTI_DIRECT   |              0x46u)
#if ! defined (STM32MP2XX_ASSY3_1_0 )
#define EXTI1_LINE_71                        (EXTI_EXTI1|EXTI_RESERVED |              0x47u)
#else   /* !defined (STM32MP2XX_ASSY3_1_0 ) */
#define EXTI1_LINE_71                        (EXTI_EXTI1|EXTI_DIRECT   |              0x47u)
#endif  /* !defined (STM32MP2XX_ASSY3_1_0 ) */
#define EXTI1_LINE_72                        (EXTI_EXTI1|EXTI_DIRECT   |              0x48u)
#if defined (CORE_CA35)
#define EXTI1_LINE_73                        (EXTI_EXTI1|EXTI_CONFIG   |              0x49u)
#else   /* CORE_CA35 */
#define EXTI1_LINE_73                        (EXTI_EXTI1|EXTI_RESERVED |              0x49u)
#endif  /* CORE_CA35 */
#define EXTI1_LINE_74                        (EXTI_EXTI1|EXTI_DIRECT   |              0x4Au)
#define EXTI1_LINE_75                        (EXTI_EXTI1|EXTI_DIRECT   |              0x4Bu)
#define EXTI1_LINE_76                        (EXTI_EXTI1|EXTI_DIRECT   |              0x4Cu)
#if defined (CORE_CA35)
#define EXTI1_LINE_77                        (EXTI_EXTI1|EXTI_DIRECT   |              0x4Du)
#define EXTI1_LINE_78                        (EXTI_EXTI1|EXTI_DIRECT   |              0x4Eu)
#define EXTI1_LINE_79                        (EXTI_EXTI1|EXTI_DIRECT   |              0x4Fu)
#else   /* CORE_CA35 */
#define EXTI1_LINE_77                        (EXTI_EXTI1|EXTI_RESERVED |              0x4Du)
#define EXTI1_LINE_78                        (EXTI_EXTI1|EXTI_RESERVED |              0x4Eu)
#define EXTI1_LINE_79                        (EXTI_EXTI1|EXTI_RESERVED |              0x4Fu)
#endif  /* CORE_CA35 */
#if defined (CORE_CM33)
#define EXTI1_LINE_80                        (EXTI_EXTI1|EXTI_DIRECT   |              0x50u)
#define EXTI1_LINE_81                        (EXTI_EXTI1|EXTI_DIRECT   |              0x51u)
#define EXTI1_LINE_82                        (EXTI_EXTI1|EXTI_DIRECT   |              0x52u)
#else   /* CORE_CM33 */
#define EXTI1_LINE_80                        (EXTI_EXTI1|EXTI_RESERVED |              0x50u)
#define EXTI1_LINE_81                        (EXTI_EXTI1|EXTI_RESERVED |              0x51u)
#define EXTI1_LINE_82                        (EXTI_EXTI1|EXTI_RESERVED |              0x52u)
#endif  /* CORE_CM33 */
#if (STM32MP2_DEV_ID == 0x503)
#define EXTI1_LINE_83                        (EXTI_EXTI1|EXTI_RESERVED |              0x53u)
#define EXTI1_LINE_84                        (EXTI_EXTI1|EXTI_RESERVED |              0x54u)
#else
#define EXTI1_LINE_83                        (EXTI_EXTI1|EXTI_CONFIG   |              0x53u)
#define EXTI1_LINE_84                        (EXTI_EXTI1|EXTI_CONFIG   |              0x54u)
#endif
/**
  * @brief  EXTI1 Line number
  */
#define EXTI1_LINE_NB                        85U

/**
  * @brief  EXTI1 GPIO Pin Max  (GPIO not available on EXTI1)
  */

#if ! defined (STM32MP2XX_ASSY3_1_0 )
#define EXTI1_GPIO_PIN_MAX                    16u
#else   /* !defined (STM32MP2XX_ASSY3_1_0 ) */
#define EXTI1_GPIO_PIN_MAX                    0u
#endif  /* !defined (STM32MP2XX_ASSY3_1_0 ) */

/**
  * @}
  */

/** @defgroup EXTI2_Line  EXTI2 Line
  * @{
  */
#define EXTI2_LINE_0                         (EXTI_EXTI2|EXTI_GPIO     | EXTI_EVENT | 0x00u)
#define EXTI2_LINE_1                         (EXTI_EXTI2|EXTI_GPIO     | EXTI_EVENT | 0x01u)
#define EXTI2_LINE_2                         (EXTI_EXTI2|EXTI_GPIO     | EXTI_EVENT | 0x02u)
#define EXTI2_LINE_3                         (EXTI_EXTI2|EXTI_GPIO     | EXTI_EVENT | 0x03u)
#define EXTI2_LINE_4                         (EXTI_EXTI2|EXTI_GPIO     | EXTI_EVENT | 0x04u)
#define EXTI2_LINE_5                         (EXTI_EXTI2|EXTI_GPIO     | EXTI_EVENT | 0x05u)
#define EXTI2_LINE_6                         (EXTI_EXTI2|EXTI_GPIO     | EXTI_EVENT | 0x06u)
#define EXTI2_LINE_7                         (EXTI_EXTI2|EXTI_GPIO     | EXTI_EVENT | 0x07u)
#define EXTI2_LINE_8                         (EXTI_EXTI2|EXTI_GPIO     | EXTI_EVENT | 0x08u)
#define EXTI2_LINE_9                         (EXTI_EXTI2|EXTI_GPIO     | EXTI_EVENT | 0x09u)
#define EXTI2_LINE_10                        (EXTI_EXTI2|EXTI_GPIO     | EXTI_EVENT | 0x0Au)
#define EXTI2_LINE_11                        (EXTI_EXTI2|EXTI_GPIO     | EXTI_EVENT | 0x0Bu)
#define EXTI2_LINE_12                        (EXTI_EXTI2|EXTI_GPIO     | EXTI_EVENT | 0x0Cu)
#define EXTI2_LINE_13                        (EXTI_EXTI2|EXTI_GPIO     | EXTI_EVENT | 0x0Du)
#define EXTI2_LINE_14                        (EXTI_EXTI2|EXTI_GPIO     | EXTI_EVENT | 0x0Eu)
#define EXTI2_LINE_15                        (EXTI_EXTI2|EXTI_GPIO     | EXTI_EVENT | 0x0Fu)

#if ! defined (STM32MP2XX_ASSY3_1_0 )
/* no more events */
#if defined (CORE_CA35)
#define EXTI2_LINE_16                        (EXTI_EXTI2|EXTI_DIRECT   |              0x10u)
#define EXTI2_LINE_17                        (EXTI_EXTI2|EXTI_DIRECT   |              0x11u)
#else   /* CORE_CA35 */
#define EXTI2_LINE_16                        (EXTI_EXTI2|EXTI_RESERVED |              0x10u)
#define EXTI2_LINE_17                        (EXTI_EXTI2|EXTI_RESERVED |              0x11u)
#endif  /* CORE_CA35 */
#if defined (CORE_CM33)
#define EXTI2_LINE_18                        (EXTI_EXTI2|EXTI_DIRECT   |              0x12u)
#define EXTI2_LINE_19                        (EXTI_EXTI2|EXTI_DIRECT   |              0x13u)
#else   /* CORE_CM33 */
#define EXTI2_LINE_18                        (EXTI_EXTI2|EXTI_RESERVED |              0x12u)
#define EXTI2_LINE_19                        (EXTI_EXTI2|EXTI_RESERVED |              0x13u)
#endif  /* CORE_CM33 */
#if defined (CORE_CM0PLUS)
#define EXTI2_LINE_20                        (EXTI_EXTI2|EXTI_DIRECT   |              0x14u)
#else   /* CORE_CM0PLUS */
#define EXTI2_LINE_20                        (EXTI_EXTI2|EXTI_RESERVED |              0x14u)
#endif  /* CORE_CM0PLUS */
#if defined (CORE_CA35)
#define EXTI2_LINE_21                        (EXTI_EXTI2|EXTI_DIRECT   |              0x15u)
#define EXTI2_LINE_22                        (EXTI_EXTI2|EXTI_DIRECT   |              0x16u)
#else   /* CORE_CA35 */
#define EXTI2_LINE_21                        (EXTI_EXTI2|EXTI_RESERVED |              0x15u)
#define EXTI2_LINE_22                        (EXTI_EXTI2|EXTI_RESERVED |              0x16u)
#endif  /* CORE_CA35 */
#if defined (CORE_CM33)
#define EXTI2_LINE_23                        (EXTI_EXTI2|EXTI_DIRECT   |              0x17u)
#define EXTI2_LINE_24                        (EXTI_EXTI2|EXTI_DIRECT   |              0x18u)
#else   /* CORE_CM33 */
#define EXTI2_LINE_23                        (EXTI_EXTI2|EXTI_RESERVED |              0x17u)
#define EXTI2_LINE_24                        (EXTI_EXTI2|EXTI_RESERVED |              0x18u)
#endif  /* CORE_CM33 */
#else   /* !defined (STM32MP2XX_ASSY3_1_0 ) */
#if defined (CORE_CA35)
#define EXTI2_LINE_16                        (EXTI_EXTI2|EXTI_DIRECT   | EXTI_EVENT | 0x10u)
#define EXTI2_LINE_17                        (EXTI_EXTI2|EXTI_DIRECT   | EXTI_EVENT | 0x11u)
#else   /* CORE_CA35 */
#define EXTI2_LINE_16                        (EXTI_EXTI2|EXTI_RESERVED |              0x10u)
#define EXTI2_LINE_17                        (EXTI_EXTI2|EXTI_RESERVED |              0x11u)
#endif  /* CORE_CA35 */
#if defined (CORE_CM33)
#define EXTI2_LINE_18                        (EXTI_EXTI2|EXTI_DIRECT   | EXTI_EVENT | 0x12u)
#define EXTI2_LINE_19                        (EXTI_EXTI2|EXTI_DIRECT   | EXTI_EVENT | 0x13u)
#else   /* CORE_CM33 */
#define EXTI2_LINE_18                        (EXTI_EXTI2|EXTI_RESERVED |              0x12u)
#define EXTI2_LINE_19                        (EXTI_EXTI2|EXTI_RESERVED |              0x13u)
#endif  /* CORE_CM33 */
#if defined (CORE_CM0PLUS)
#define EXTI2_LINE_20                        (EXTI_EXTI2|EXTI_DIRECT   | EXTI_EVENT | 0x14u)
#else   /* CORE_CM0PLUS */
#define EXTI2_LINE_20                        (EXTI_EXTI2|EXTI_RESERVED |              0x14u)
#endif  /* CORE_CM0PLUS */
#if defined (CORE_CA35)
#define EXTI2_LINE_21                        (EXTI_EXTI2|EXTI_DIRECT   | EXTI_EVENT | 0x15u)
#define EXTI2_LINE_22                        (EXTI_EXTI2|EXTI_DIRECT   | EXTI_EVENT | 0x16u)
#else   /* CORE_CA35 */
#define EXTI2_LINE_21                        (EXTI_EXTI2|EXTI_RESERVED |              0x15u)
#define EXTI2_LINE_22                        (EXTI_EXTI2|EXTI_RESERVED |              0x16u)
#endif  /* CORE_CA35 */
#if defined (CORE_CM33)
#define EXTI2_LINE_23                        (EXTI_EXTI2|EXTI_DIRECT   | EXTI_EVENT | 0x17u)
#define EXTI2_LINE_24                        (EXTI_EXTI2|EXTI_DIRECT   | EXTI_EVENT | 0x18u)
#else   /* CORE_CM33 */
#define EXTI2_LINE_23                        (EXTI_EXTI2|EXTI_RESERVED |              0x17u)
#define EXTI2_LINE_24                        (EXTI_EXTI2|EXTI_RESERVED |              0x18u)
#endif  /* CORE_CM33 */
#endif  /* !defined (STM32MP2XX_ASSY3_1_0 ) */


#if (STM32MP2_DEV_ID == 0x503)
#define EXTI2_LINE_25                        (EXTI_EXTI2|EXTI_RESERVED |              0x19u)
#else
#define EXTI2_LINE_25                        (EXTI_EXTI2|EXTI_DIRECT   |              0x19u)
#endif
#define EXTI2_LINE_26                        (EXTI_EXTI2|EXTI_DIRECT   |              0x1Au)
#if (STM32MP2_DEV_ID == 0x503)
#define EXTI2_LINE_27                        (EXTI_EXTI2|EXTI_RESERVED |              0x1Bu)
#else
#define EXTI2_LINE_27                        (EXTI_EXTI2|EXTI_DIRECT   |              0x1Bu)
#endif
#define EXTI2_LINE_28                        (EXTI_EXTI2|EXTI_RESERVED |              0x1Cu)
#define EXTI2_LINE_29                        (EXTI_EXTI2|EXTI_DIRECT   |              0x1Du)
#define EXTI2_LINE_30                        (EXTI_EXTI2|EXTI_DIRECT   |              0x1Eu)
#define EXTI2_LINE_31                        (EXTI_EXTI2|EXTI_DIRECT   |              0x1Fu)
#define EXTI2_LINE_32                        (EXTI_EXTI2|EXTI_RESERVED |              0x20u)
#if (STM32MP2_DEV_ID == 0x503)
#define EXTI2_LINE_33                        (EXTI_EXTI2|EXTI_RESERVED |              0x21u)
#else
#define EXTI2_LINE_33                        (EXTI_EXTI2|EXTI_DIRECT   |              0x21u)
#endif
#if defined (CORE_CA35)
#define EXTI2_LINE_34                        (EXTI_EXTI2|EXTI_DIRECT   |              0x22u)
#else   /* CORE_CA35 */
#if (STM32MP2_DEV_ID == 0x503)
#define EXTI2_LINE_34                        (EXTI_EXTI2|EXTI_CONFIG   |              0x22u)
#else
#define EXTI2_LINE_34                        (EXTI_EXTI2|EXTI_RESERVED |              0x22u)
#endif
#endif  /* CORE_CA35 */
#if defined (CORE_CM33)
#if (STM32MP2_DEV_ID == 0x503)
#define EXTI2_LINE_35                        (EXTI_EXTI2|EXTI_CONFIG |              0x23u)
#else
#define EXTI2_LINE_35                        (EXTI_EXTI2|EXTI_DIRECT   |              0x23u)
#endif
#else   /* CORE_CM33 */
#define EXTI2_LINE_35                        (EXTI_EXTI2|EXTI_RESERVED |              0x23u)
#endif  /* CORE_CM33 */
#if defined (CORE_CM0PLUS)
#define EXTI2_LINE_36                        (EXTI_EXTI2|EXTI_DIRECT   |              0x24u)
#else   /* CORE_CM0PLUS */
#define EXTI2_LINE_36                        (EXTI_EXTI2|EXTI_RESERVED |              0x24u)
#endif  /* CORE_CM0PLUS */
#if defined (CORE_CA35)
#define EXTI2_LINE_37                        (EXTI_EXTI2|EXTI_DIRECT   |              0x25u)
#else   /* CORE_CA35 */
#if (STM32MP2_DEV_ID == 0x503)
#define EXTI2_LINE_37                        (EXTI_EXTI2|EXTI_CONFIG   |              0x25u)
#else
#define EXTI2_LINE_37                        (EXTI_EXTI2|EXTI_RESERVED |              0x25u)
#endif
#endif  /* CORE_CA35 */
#if defined (CORE_CM33)
#if (STM32MP2_DEV_ID == 0x503)
#define EXTI2_LINE_38                        (EXTI_EXTI2|EXTI_RESERVED |              0x26u)
#else
#define EXTI2_LINE_38                        (EXTI_EXTI2|EXTI_DIRECT   |              0x26u)
#endif
#else   /* CORE_CM33 */
#define EXTI2_LINE_38                        (EXTI_EXTI2|EXTI_RESERVED |              0x26u)
#endif  /* CORE_CM33 */
#define EXTI2_LINE_39                        (EXTI_EXTI2|EXTI_RESERVED |              0x27u)
#if defined (CORE_CA35)
#define EXTI2_LINE_40                        (EXTI_EXTI2|EXTI_DIRECT   |              0x28u)
#else   /* CORE_CA35 */
#define EXTI2_LINE_40                        (EXTI_EXTI2|EXTI_RESERVED |              0x28u)
#endif  /* CORE_CA35 */
#if defined (CORE_CM33)
#define EXTI2_LINE_41                        (EXTI_EXTI2|EXTI_DIRECT   |              0x29u)
#else   /* CORE_CM33 */
#define EXTI2_LINE_41                        (EXTI_EXTI2|EXTI_RESERVED |              0x29u)
#endif  /* CORE_CM33 */
#if defined (CORE_CM0PLUS)
#define EXTI2_LINE_42                        (EXTI_EXTI2|EXTI_DIRECT   |              0x2Au)
#else   /* CORE_CM0PLUS */
#if (STM32MP2_DEV_ID == 0x503)
#define EXTI2_LINE_42                        (EXTI_EXTI2|EXTI_DIRECT   |              0x2Au)
#else
#define EXTI2_LINE_42                        (EXTI_EXTI2|EXTI_RESERVED |              0x2Au)
#endif
#endif  /* CORE_CM0PLUS */
#if defined (CORE_CA35)
#define EXTI2_LINE_43                        (EXTI_EXTI2|EXTI_DIRECT   |              0x2Bu)
#else   /* CORE_CA35 */
#define EXTI2_LINE_43                        (EXTI_EXTI2|EXTI_RESERVED |              0x2Bu)
#endif  /* CORE_CA35 */
#if defined (CORE_CM33)
#if (STM32MP2_DEV_ID == 0x503)
#define EXTI2_LINE_44                        (EXTI_EXTI2|EXTI_RESERVED |              0x2Cu)
#else
#define EXTI2_LINE_44                        (EXTI_EXTI2|EXTI_DIRECT   |              0x2Cu)
#endif
#else   /* CORE_CM33 */
#define EXTI2_LINE_44                        (EXTI_EXTI2|EXTI_RESERVED |              0x2Cu)
#endif  /* CORE_CM33 */
#define EXTI2_LINE_45                        (EXTI_EXTI2|EXTI_RESERVED |              0x2Du)
#if defined (CORE_CA35) || defined (CORE_CM33)
#if (STM32MP2_DEV_ID == 0x503)
#define EXTI2_LINE_46                        (EXTI_EXTI2|EXTI_RESERVED |              0x2Eu)
#else
#define EXTI2_LINE_46                        (EXTI_EXTI2|EXTI_CONFIG   |              0x2Eu)
#endif
#else   /* CORE_CA35 || CORE_CM33 */
#define EXTI2_LINE_46                        (EXTI_EXTI2|EXTI_RESERVED |              0x2Eu)
#endif  /* CORE_CA35 || CORE_CM33 */
#if defined (CORE_CM33)
#if (STM32MP2_DEV_ID == 0x503)
#define EXTI2_LINE_47                        (EXTI_EXTI2|EXTI_RESERVED |              0x2Fu)
#else
#define EXTI2_LINE_47                        (EXTI_EXTI2|EXTI_CONFIG   |              0x2Fu)
#endif
#else   /* CORE_CM33 */
#define EXTI2_LINE_47                        (EXTI_EXTI2|EXTI_RESERVED |              0x2Fu)
#endif  /* CORE_CM33 */
#if defined (CORE_CA35) || defined (CORE_CM33)
#if (STM32MP2_DEV_ID == 0x503)
#define EXTI2_LINE_48                        (EXTI_EXTI2|EXTI_RESERVED |              0x30u)
#else
#define EXTI2_LINE_48                        (EXTI_EXTI2|EXTI_CONFIG   |              0x30u)
#endif
#else   /* CORE_CA35 || CORE_CM33 */
#define EXTI2_LINE_48                        (EXTI_EXTI2|EXTI_RESERVED |              0x30u)
#endif  /* CORE_CA35 || CORE_CM33 */
#if defined (CORE_CA35)
#define EXTI2_LINE_49                        (EXTI_EXTI2|EXTI_CONFIG   |              0x31u)
#else   /* CORE_CA35 */
#define EXTI2_LINE_49                        (EXTI_EXTI2|EXTI_RESERVED |              0x31u)
#endif  /* CORE_CA35 */
#if defined (CORE_CA35) || defined (CORE_CM33)
#if (STM32MP2_DEV_ID == 0x503)
#define EXTI2_LINE_50                        (EXTI_EXTI2|EXTI_RESERVED |              0x32u)
#else
#define EXTI2_LINE_50                        (EXTI_EXTI2|EXTI_CONFIG   |              0x32u)
#endif
#define EXTI2_LINE_51                        (EXTI_EXTI2|EXTI_CONFIG   |              0x33u)
#else   /* CORE_CA35 || CORE_CM33 */
#define EXTI2_LINE_50                        (EXTI_EXTI2|EXTI_RESERVED |              0x32u)
#define EXTI2_LINE_51                        (EXTI_EXTI2|EXTI_RESERVED |              0x33u)
#endif  /* CORE_CA35 || CORE_CM33 */
#if defined (CORE_CA35)
#define EXTI2_LINE_52                        (EXTI_EXTI2|EXTI_DIRECT   |              0x34u)
#define EXTI2_LINE_53                        (EXTI_EXTI2|EXTI_DIRECT   |              0x35u)
#else   /* CORE_CA35 */
#if (STM32MP2_DEV_ID == 0x503)
#define EXTI2_LINE_52                        (EXTI_EXTI2|EXTI_CONFIG   |              0x34u)
#else
#define EXTI2_LINE_52                        (EXTI_EXTI2|EXTI_RESERVED |              0x34u)
#endif
#define EXTI2_LINE_53                        (EXTI_EXTI2|EXTI_RESERVED |              0x35u)
#endif  /* CORE_CA35 */
#if defined (CORE_CM33)
#if (STM32MP2_DEV_ID == 0x503)
#define EXTI2_LINE_54                        (EXTI_EXTI2|EXTI_RESERVED |              0x36u)
#define EXTI2_LINE_55                        (EXTI_EXTI2|EXTI_RESERVED |              0x37u)
#else
#define EXTI2_LINE_54                        (EXTI_EXTI2|EXTI_DIRECT   |              0x36u)
#define EXTI2_LINE_55                        (EXTI_EXTI2|EXTI_DIRECT   |              0x37u)
#endif
#else   /* CORE_CM33 */
#define EXTI2_LINE_54                        (EXTI_EXTI2|EXTI_RESERVED |              0x36u)
#define EXTI2_LINE_55                        (EXTI_EXTI2|EXTI_RESERVED |              0x37u)
#endif  /* CORE_CM33 */
#if defined (CORE_CM0PLUS)
#define EXTI2_LINE_56                        (EXTI_EXTI2|EXTI_DIRECT   |              0x38u)
#else   /* CORE_CM0PLUS */
#define EXTI2_LINE_56                        (EXTI_EXTI2|EXTI_RESERVED |              0x38u)
#endif  /* CORE_CM0PLUS */
#define EXTI2_LINE_57                        (EXTI_EXTI2|EXTI_RESERVED |              0x39u)
#define EXTI2_LINE_58                        (EXTI_EXTI2|EXTI_RESERVED |              0x3Au)
#if defined (CORE_CM0PLUS)
#define EXTI2_LINE_59                        (EXTI_EXTI2|EXTI_CONFIG   | EXTI_EVENT | 0x3Bu)
#define EXTI2_LINE_60                        (EXTI_EXTI2|EXTI_CONFIG   | EXTI_EVENT | 0x3Cu)
#else   /* CORE_CM0PLUS */
#define EXTI2_LINE_59                        (EXTI_EXTI2|EXTI_RESERVED |              0x3Bu)
#define EXTI2_LINE_60                        (EXTI_EXTI2|EXTI_RESERVED |              0x3Cu)
#endif  /* CORE_CM0PLUS */
#if defined (CORE_CA35) || defined (CORE_CM33)
#if (STM32MP2_DEV_ID == 0x503)
#define EXTI2_LINE_61                        (EXTI_EXTI2|EXTI_RESERVED |              0x3Du)
#else
#define EXTI2_LINE_61                        (EXTI_EXTI2|EXTI_CONFIG   |              0x3Du)
#endif
#else   /* CORE_CA35 || CORE_CM33 */
#define EXTI2_LINE_61                        (EXTI_EXTI2|EXTI_RESERVED |              0x3Du)
#endif  /* CORE_CA35 || CORE_CM33 */
#if defined (CORE_CA35)
#define EXTI2_LINE_62                        (EXTI_EXTI2|EXTI_DIRECT   |              0x3Eu)
#else   /* CORE_CA35 */
#define EXTI2_LINE_62                        (EXTI_EXTI2|EXTI_RESERVED |              0x3Eu)
#endif  /* CORE_CA35 */
#if defined (CORE_CM33)
#if (STM32MP2_DEV_ID == 0x503)
#define EXTI2_LINE_63                        (EXTI_EXTI2|EXTI_RESERVED |              0x3Fu)
#else
#define EXTI2_LINE_63                        (EXTI_EXTI2|EXTI_DIRECT   |              0x3Fu)
#endif
#else   /* CORE_CM33 */
#define EXTI2_LINE_63                        (EXTI_EXTI2|EXTI_RESERVED |              0x3Fu)
#endif  /* CORE_CM33 */
#define EXTI2_LINE_64                        (EXTI_EXTI2|EXTI_CONFIG   |              0x40u)
#define EXTI2_LINE_65                        (EXTI_EXTI2|EXTI_CONFIG   |              0x41u)
#if defined (CORE_CA35)
#define EXTI2_LINE_66                        (EXTI_EXTI2|EXTI_CONFIG   |              0x42u)
#else   /* CORE_CA35 */
#define EXTI2_LINE_66                        (EXTI_EXTI2|EXTI_RESERVED |              0x42u)
#endif  /* CORE_CA35 */
#if defined (CORE_CA35)
#define EXTI2_LINE_67                        (EXTI_EXTI2|EXTI_DIRECT   |              0x43u)
#else   /* CORE_CA35 */
#define EXTI2_LINE_67                        (EXTI_EXTI2|EXTI_RESERVED |              0x43u)
#endif  /* CORE_CA35 */
#if defined (CORE_CM33)
#define EXTI2_LINE_68                        (EXTI_EXTI2|EXTI_DIRECT   |              0x44u)
#else   /* CORE_CM33 */
#define EXTI2_LINE_68                        (EXTI_EXTI2|EXTI_RESERVED |              0x44u)
#endif  /* CORE_CM33 */
#if defined (CORE_CM0PLUS)
#define EXTI2_LINE_69                        (EXTI_EXTI2|EXTI_DIRECT   |              0x45u)
#else   /* CORE_CM0PLUS */
#define EXTI2_LINE_69                        (EXTI_EXTI2|EXTI_RESERVED |              0x45u)
#endif  /* CORE_CM0PLUS */
#define EXTI2_LINE_70                        (EXTI_EXTI2|EXTI_DIRECT   |              0x46u)
#define EXTI2_LINE_71                        (EXTI_EXTI2|EXTI_RESERVED |              0x47u)
#define EXTI2_LINE_72                        (EXTI_EXTI2|EXTI_RESERVED |              0x48u)
#define EXTI2_LINE_73                        (EXTI_EXTI2|EXTI_RESERVED |              0x49u)
#define EXTI2_LINE_74                        (EXTI_EXTI2|EXTI_RESERVED |              0x4Au)
#define EXTI2_LINE_75                        (EXTI_EXTI2|EXTI_RESERVED |              0x4Bu)
#define EXTI2_LINE_76                        (EXTI_EXTI2|EXTI_DIRECT   |              0x4Cu)

/**
  * @brief  EXTI2 Line number
  */
#if (STM32MP2_DEV_ID == 0x503)
#define EXTI2_LINE_NB                        64U
#else
#define EXTI2_LINE_NB                        77U
#endif /* EXTI LINE 64 */

/**
  * @brief  EXTI2 GPIO Pin Max
  */

#define EXTI2_GPIO_PIN_MAX                    16u

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
  * @{
  */
#if defined (CORE_CA35) || defined (CORE_CM33)
#define EXTI_GPIOA                          0x00000000U
#define EXTI_GPIOB                          0x00000001U
#define EXTI_GPIOC                          0x00000002U
#define EXTI_GPIOD                          0x00000003U
#define EXTI_GPIOE                          0x00000004U
#define EXTI_GPIOF                          0x00000005U
#define EXTI_GPIOG                          0x00000006U
#define EXTI_GPIOH                          0x00000007U
#define EXTI_GPIOI                          0x00000008U
#if (STM32MP2_DEV_ID == 0x503)
#define EXTI_GPIOZ                          0x00000009U
#else
#define EXTI_GPIOJ                          0x00000009U
#define EXTI_GPIOK                          0x0000000AU
#define EXTI_GPIOZ                          0x0000000BU
#endif
#else   /* CORE_CA35 || CORE_CM33 */
#define EXTI_GPIOZ                          0x0000000Bu
#endif  /* CORE_CA35 || CORE_CM33 */

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
#define EXTI_PROPERTY_SHIFT                  24U
#define EXTI_DIRECT                         (0x01U << EXTI_PROPERTY_SHIFT)
#define EXTI_CONFIG                         (0x02U << EXTI_PROPERTY_SHIFT)
#define EXTI_GPIO                           ((0x04U << EXTI_PROPERTY_SHIFT) | EXTI_CONFIG)
#define EXTI_RESERVED                       (0x08U << EXTI_PROPERTY_SHIFT)
#define EXTI_PROPERTY_MASK                  (EXTI_DIRECT | EXTI_CONFIG | EXTI_GPIO)

/**
  * @brief  EXTI Event presence definition
  */
#define EXTI_EVENT_PRESENCE_SHIFT           28U
#define EXTI_EVENT_PRESENCE_MASK            (0x01U << EXTI_EVENT_PRESENCE_SHIFT)
#define EXTI_EVENT                          EXTI_EVENT_PRESENCE_MASK

/**
  * @brief  EXTI Index definition
  */
#define EXTI_INDEX_SHIFT                    30U
#define EXTI_INDEX_MASK                     (0x01U << EXTI_INDEX_SHIFT)
#define EXTI_EXTI1                          (0x00U << EXTI_INDEX_SHIFT)
#define EXTI_EXTI2                          (0x01U << EXTI_INDEX_SHIFT)
#define EXTI_INDEX                          EXTI_INDEX_MASK

/**
  * @brief  EXTI Pin definition
  * max 256 lines per EXTI
  */
#define EXTI_PIN_MASK                       0x000000FFu

/**
  * @brief  EXTI Mask for interrupt & event mode
  */
#define EXTI_MODE_MASK                      (EXTI_MODE_EVENT | EXTI_MODE_INTERRUPT)

/**
  * @brief  EXTI Mask for trigger possibilities
  */
#define EXTI_TRIGGER_MASK                   (EXTI_TRIGGER_RISING | EXTI_TRIGGER_FALLING)

/**
  * @}
  */

/** @defgroup EXTI_Access_filtering EXTI Access filtering (Global lock and EVENT line)
  * @{
  */

#define EXTI_LINE_ATTR_PRIV_SELECT         0x01000000U
#define EXTI_LINE_ATTR_SEC_SELECT          0x02000000U
#define EXTI_LINE_ATTR_CID_STATIC_SELECT   0x20000000U
#define EXTI_LINE_CID_DISABLE              0x80000000U

#define EXTI_LINE_PRIV_VAL_Pos             0
#define EXTI_LINE_PRIV                     (EXTI_LINE_ATTR_PRIV_SELECT | (1U<<EXTI_LINE_PRIV_VAL_Pos)) /*!< Resource is privileged   */
#define EXTI_LINE_NPRIV                    (EXTI_LINE_ATTR_PRIV_SELECT)                            /*!< Resource is unprivileged */

#if defined (CORTEX_IN_SECURE_STATE)
#define EXTI_LINE_SEC_VAL_Pos              1
#define EXTI_LINE_SEC                      (EXTI_LINE_ATTR_SEC_SELECT | (1U<<EXTI_LINE_SEC_VAL_Pos))  /*!< Resource is secure       */
#define EXTI_LINE_NSEC                     (EXTI_LINE_ATTR_SEC_SELECT)                            /*!< Resource is non-secure   */
#endif /* __ARM_SECURE_STATE */

#define EXTI_LINE_CID_STATIC_0             (EXTI_LINE_ATTR_CID_STATIC_SELECT|(0<<EXTI_E0CIDCFGR_SCID_Pos))   /*!< Enable CID filtering (static mode) and give pin control  to CID0 */
#define EXTI_LINE_CID_STATIC_1             (EXTI_LINE_ATTR_CID_STATIC_SELECT|(1<<EXTI_E0CIDCFGR_SCID_Pos))   /*!< Enable CID filtering (static mode) and give pin control  to CID1 */
#define EXTI_LINE_CID_STATIC_2             (EXTI_LINE_ATTR_CID_STATIC_SELECT|(2<<EXTI_E0CIDCFGR_SCID_Pos))   /*!< Enable CID filtering (static mode) and give pin control  to CID2 */
#define EXTI_LINE_CID_STATIC_3             (EXTI_LINE_ATTR_CID_STATIC_SELECT|(3<<EXTI_E0CIDCFGR_SCID_Pos))   /*!< Enable CID filtering (static mode) and give pin control  to CID3 */


/**
  * @}
  */

/* Private macros ------------------------------------------------------------*/
/** @defgroup EXTI_Private_Macros EXTI Private Macros
  * @{
  */
#if ! defined (STM32MP2XX_ASSY3_1_0 )
#if defined (CORE_CA35) || defined (CORE_CM33)
#define IS_EXTI_LINE(__LINE__)    ((IS_EXTI1_LINE(__LINE__)) || (IS_EXTI2_LINE(__LINE__)))
#else   /* CORE_CA35 || CORE_CM33 */
/* M0+ access only EXTI2 */
#define IS_EXTI_LINE(__LINE__)    (IS_EXTI2_LINE(__LINE__))
#endif  /* CORE_CA35 || CORE_CM33 */


/* remark: no GPIO on EXTI1 */
#define IS_EXTI1_LINE(__LINE__)         ( \
                                          (((__LINE__) & EXTI_INDEX ) == EXTI_EXTI1)                           \
                                          &&                                                                   \
                                          (  ((__LINE__) & ~(EXTI_PROPERTY_MASK | EXTI_EVENT_PRESENCE_MASK     \
                                                             | EXTI_INDEX_MASK | EXTI_PIN_MASK)                \
                                             ) == 0x00u                                                        \
                                          )                                                                    \
                                          &&                                                                   \
                                          ( \
                                            (((__LINE__) & EXTI_PROPERTY_MASK) == EXTI_DIRECT)   ||            \
                                            (((__LINE__) & EXTI_PROPERTY_MASK) == EXTI_CONFIG)   ||            \
                                            (((__LINE__) & EXTI_PROPERTY_MASK) == EXTI_GPIO)                   \
                                          )                                                                    \
                                          &&                                                                   \
                                          (((__LINE__) & EXTI_PIN_MASK)< EXTI1_LINE_NB)                        \
                                        )


#define IS_EXTI2_LINE(__LINE__)         ( \
                                          (((__LINE__) & EXTI_INDEX ) == EXTI_EXTI2)                           \
                                          &&                                                                   \
                                          (  ((__LINE__) & ~(EXTI_PROPERTY_MASK | EXTI_EVENT_PRESENCE_MASK |   \
                                                             EXTI_INDEX_MASK | EXTI_PIN_MASK)                  \
                                             ) == 0x00u                                                        \
                                          )                                                                    \
                                          &&                                                                   \
                                          ( \
                                            (((__LINE__) & EXTI_PROPERTY_MASK) == EXTI_DIRECT)   ||            \
                                            (((__LINE__) & EXTI_PROPERTY_MASK) == EXTI_CONFIG)   ||            \
                                            (((__LINE__) & EXTI_PROPERTY_MASK) == EXTI_GPIO)                   \
                                          )                                                                    \
                                          &&                                                                   \
                                          (((__LINE__) & EXTI_PIN_MASK) < EXTI2_LINE_NB)                       \
                                        )


#define IS_EXTI_MODE(__MODE__)          ((((__MODE__) & EXTI_MODE_MASK) != 0x00u) && \
                                         (((__MODE__) & ~EXTI_MODE_MASK) == 0x00u))

#define IS_EXTI_TRIGGER(__TRIGGER__)    (((__TRIGGER__) & ~EXTI_TRIGGER_MASK) == 0x00u)
#define IS_EXTI_PENDING_EDGE(__EDGE__) (((__EDGE__) == EXTI_TRIGGER_RISING) || \
                                        ((__EDGE__) == EXTI_TRIGGER_FALLING)|| \
                                        ((__EDGE__) == EXTI_TRIGGER_RISING_FALLING) )

#define IS_EXTI_CONFIG_LINE(__LINE__)   (((__LINE__) & EXTI_CONFIG) != 0x00u)

#define IS_EXTI_GPIO_LINE(__LINE__)     (((__LINE__) & EXTI_GPIO) == EXTI_GPIO)

#define IS_EXTI_EVENT_PRESENT(__LINE__) (((__LINE__) & EXTI_EVENT) != 0x00u)

#define EXTI_GET_PIN(__LINE__)          ( (__LINE__) & EXTI_PIN_MASK)

#if (STM32MP2_DEV_ID == 0x503)
#define EXTI1_GPIO_PORT_NB                (10)
#else
#define EXTI1_GPIO_PORT_NB                (12)
#endif

#if (STM32MP2_DEV_ID == 0x503)
#define IS_EXTI1_GPIO_PORT(__PORT__)     (((__PORT__) == EXTI_GPIOA) || \
                                          ((__PORT__) == EXTI_GPIOB) || \
                                          ((__PORT__) == EXTI_GPIOC) || \
                                          ((__PORT__) == EXTI_GPIOD) || \
                                          ((__PORT__) == EXTI_GPIOE) || \
                                          ((__PORT__) == EXTI_GPIOF) || \
                                          ((__PORT__) == EXTI_GPIOG) || \
                                          ((__PORT__) == EXTI_GPIOH) || \
                                          ((__PORT__) == EXTI_GPIOI) || \
                                          ((__PORT__) == EXTI_GPIOZ))
#else
#define IS_EXTI1_GPIO_PORT(__PORT__)     (((__PORT__) == EXTI_GPIOA) || \
                                          ((__PORT__) == EXTI_GPIOB) || \
                                          ((__PORT__) == EXTI_GPIOC) || \
                                          ((__PORT__) == EXTI_GPIOD) || \
                                          ((__PORT__) == EXTI_GPIOE) || \
                                          ((__PORT__) == EXTI_GPIOF) || \
                                          ((__PORT__) == EXTI_GPIOG) || \
                                          ((__PORT__) == EXTI_GPIOH) || \
                                          ((__PORT__) == EXTI_GPIOI) || \
                                          ((__PORT__) == EXTI_GPIOJ) || \
                                          ((__PORT__) == EXTI_GPIOK) || \
                                          ((__PORT__) == EXTI_GPIOZ))
#endif

#if defined (CORE_CA35) || defined (CORE_CM33)
#if (STM32MP2_DEV_ID == 0x503)
#define EXTI2_GPIO_PORT_NB                (10)
#else
#define EXTI2_GPIO_PORT_NB                (12)
#endif

#if (STM32MP2_DEV_ID == 0x503)
#define IS_EXTI2_GPIO_PORT(__PORT__)     (((__PORT__) == EXTI_GPIOA) || \
                                          ((__PORT__) == EXTI_GPIOB) || \
                                          ((__PORT__) == EXTI_GPIOC) || \
                                          ((__PORT__) == EXTI_GPIOD) || \
                                          ((__PORT__) == EXTI_GPIOE) || \
                                          ((__PORT__) == EXTI_GPIOF) || \
                                          ((__PORT__) == EXTI_GPIOG) || \
                                          ((__PORT__) == EXTI_GPIOH) || \
                                          ((__PORT__) == EXTI_GPIOI) || \
                                          ((__PORT__) == EXTI_GPIOZ))
#else
#define IS_EXTI2_GPIO_PORT(__PORT__)     (((__PORT__) == EXTI_GPIOA) || \
                                          ((__PORT__) == EXTI_GPIOB) || \
                                          ((__PORT__) == EXTI_GPIOC) || \
                                          ((__PORT__) == EXTI_GPIOD) || \
                                          ((__PORT__) == EXTI_GPIOE) || \
                                          ((__PORT__) == EXTI_GPIOF) || \
                                          ((__PORT__) == EXTI_GPIOG) || \
                                          ((__PORT__) == EXTI_GPIOH) || \
                                          ((__PORT__) == EXTI_GPIOI) || \
                                          ((__PORT__) == EXTI_GPIOJ) || \
                                          ((__PORT__) == EXTI_GPIOK) || \
                                          ((__PORT__) == EXTI_GPIOZ))
#endif
#else   /* CORE_CA35 || CORE_CM33 */

#define EXTI2_GPIO_PORT_NB                (1)

#define IS_EXTI2_GPIO_PORT(__PORT__)     ((__PORT__) == EXTI_GPIOZ)
#endif  /* CORE_CA35 || CORE_CM33 */

#if defined (CORE_CA35) || defined (CORE_CM33)
#define IS_EXTI_GPIO_PORT(__INSTANCE__, __PORT__)                 \
  ((((__INSTANCE__) == EXTI1) && IS_EXTI1_GPIO_PORT(__PORT__))  \
   ||                                                       \
   ((((__INSTANCE__) == EXTI2) && IS_EXTI2_GPIO_PORT(__PORT__))))
#else   /* CORE_CA35 || CORE_CM33 */
#define IS_EXTI_GPIO_PORT(__INSTANCE__, __PORT__)     (((__INSTANCE__) == EXTI2) && (__PORT__) == EXTI_GPIOZ)
#endif  /* CORE_CA35 || CORE_CM33 */

#define IS_EXTI1_GPIO_PIN(__PIN__)      ((__PIN__) < EXTI1_GPIO_PIN_MAX)

#define IS_EXTI2_GPIO_PIN(__PIN__)      ((__PIN__) < EXTI2_GPIO_PIN_MAX)

#if defined (CORE_CA35) || defined (CORE_CM33)
#define IS_EXTI_GPIO_PIN(__INSTANCE__, __PIN__)                 \
  ((((__INSTANCE__) == EXTI1) && IS_EXTI1_GPIO_PIN(__PIN__))  \
   ||                                                       \
   ((((__INSTANCE__) == EXTI2) && IS_EXTI2_GPIO_PIN(__PIN__))))
#else   /* CORE_CA35 || CORE_CM33 */
#define IS_EXTI_GPIO_PIN(__INSTANCE__, __PIN__)      (((__INSTANCE__) == EXTI2) && (__PIN__) < EXTI2_GPIO_PIN_MAX)
#endif  /* CORE_CA35 || CORE_CM33 */
#else   /* !defined (STM32MP2XX_ASSY3_1_0 ) */
#if defined (CORE_CA35) || defined (CORE_CM33)
#define IS_EXTI_LINE(__LINE__)    ((IS_EXTI1_LINE(__LINE__)) || (IS_EXTI2_LINE(__LINE__)))
#else   /* CORE_CA35 || CORE_CM33 */
/* M0+ access only EXTI2 */
#define IS_EXTI_LINE(__LINE__)    (IS_EXTI2_LINE(__LINE__))
#endif  /* CORE_CA35 || CORE_CM33 */


/* remark: no GPIO on EXTI1 */
#define IS_EXTI1_LINE(__LINE__)         ( \
                                          (((__LINE__) & EXTI_INDEX ) == EXTI_EXTI1)                          \
                                          &&                                                                  \
                                          (  ((__LINE__) & ~(EXTI_PROPERTY_MASK | EXTI_EVENT_PRESENCE_MASK |  \
                                                             EXTI_INDEX_MASK | EXTI_PIN_MASK)                 \
                                             ) == 0x00u                                                       \
                                          )                                                                   \
                                          &&                                                                  \
                                          ( \
                                            (((__LINE__) & EXTI_PROPERTY_MASK) == EXTI_DIRECT) ||             \
                                            (((__LINE__) & EXTI_PROPERTY_MASK) == EXTI_CONFIG)                \
                                          )                                                                   \
                                          &&                                                                  \
                                          (((__LINE__) & EXTI_PIN_MASK) < EXTI1_LINE_NB)                      \
                                        )


#define IS_EXTI2_LINE(__LINE__)         ( \
                                          (((__LINE__) & EXTI_INDEX ) == EXTI_EXTI2)                          \
                                          &&                                                                  \
                                          (  ((__LINE__) & ~(EXTI_PROPERTY_MASK | EXTI_EVENT_PRESENCE_MASK |  \
                                                             EXTI_INDEX_MASK  | EXTI_PIN_MASK)                \
                                             ) == 0x00u                                                       \
                                          )                                                                   \
                                          &&                                                                  \
                                          ( \
                                            (((__LINE__) & EXTI_PROPERTY_MASK) == EXTI_DIRECT) ||             \
                                            (((__LINE__) & EXTI_PROPERTY_MASK) == EXTI_CONFIG) ||             \
                                            (((__LINE__) & EXTI_PROPERTY_MASK) == EXTI_GPIO)                  \
                                          )                                                                   \
                                          &&                                                                  \
                                          (((__LINE__) & EXTI_PIN_MASK) < EXTI2_LINE_NB)                      \
                                        )


#define IS_EXTI_MODE(__MODE__)          ((((__MODE__) & EXTI_MODE_MASK) != 0x00u) && \
                                         (((__MODE__) & ~EXTI_MODE_MASK) == 0x00u))

#define IS_EXTI_TRIGGER(__TRIGGER__)    (((__TRIGGER__) & ~EXTI_TRIGGER_MASK) == 0x00u)
#define IS_EXTI_PENDING_EDGE(__EDGE__) (((__EDGE__) == EXTI_TRIGGER_RISING) || \
                                        ((__EDGE__) == EXTI_TRIGGER_FALLING)|| \
                                        ((__EDGE__) == EXTI_TRIGGER_RISING_FALLING) )

#define IS_EXTI_CONFIG_LINE(__LINE__)   (((__LINE__) & EXTI_CONFIG) != 0x00u)

#define IS_EXTI_GPIO_LINE(__LINE__)     (((__LINE__) & EXTI_GPIO) == EXTI_GPIO)

#define IS_EXTI_EVENT_PRESENT(__LINE__) (((__LINE__) & EXTI_EVENT) != 0x00u)

#define EXTI_GET_PIN(__LINE__)          ( (__LINE__) & EXTI_PIN_MASK)


/* remark: no GPIO on EXTI1 */
#define EXTI1_GPIO_PORT_NB                (0)

/* always return false */
#define IS_EXTI1_GPIO_PORT(__PORT__)      (1<0)

#if defined (CORE_CA35) || defined (CORE_CM33)
#if (STM32MP2_DEV_ID == 0x503)
#define EXTI2_GPIO_PORT_NB                (10)
#else
#define EXTI2_GPIO_PORT_NB                (12)
#endif
#if (STM32MP2_DEV_ID == 0x503)
#define IS_EXTI2_GPIO_PORT(__PORT__)     (((__PORT__) == EXTI_GPIOA) || \
                                          ((__PORT__) == EXTI_GPIOB) || \
                                          ((__PORT__) == EXTI_GPIOC) || \
                                          ((__PORT__) == EXTI_GPIOD) || \
                                          ((__PORT__) == EXTI_GPIOE) || \
                                          ((__PORT__) == EXTI_GPIOF) || \
                                          ((__PORT__) == EXTI_GPIOG) || \
                                          ((__PORT__) == EXTI_GPIOH) || \
                                          ((__PORT__) == EXTI_GPIOI) || \
                                          ((__PORT__) == EXTI_GPIOZ))
#else
#define IS_EXTI2_GPIO_PORT(__PORT__)     (((__PORT__) == EXTI_GPIOA) || \
                                          ((__PORT__) == EXTI_GPIOB) || \
                                          ((__PORT__) == EXTI_GPIOC) || \
                                          ((__PORT__) == EXTI_GPIOD) || \
                                          ((__PORT__) == EXTI_GPIOE) || \
                                          ((__PORT__) == EXTI_GPIOF) || \
                                          ((__PORT__) == EXTI_GPIOG) || \
                                          ((__PORT__) == EXTI_GPIOH) || \
                                          ((__PORT__) == EXTI_GPIOI) || \
                                          ((__PORT__) == EXTI_GPIOJ) || \
                                          ((__PORT__) == EXTI_GPIOK) || \
                                          ((__PORT__) == EXTI_GPIOZ))
#endif
#else   /* CORE_CA35 || CORE_CM33 */

#define EXTI2_GPIO_PORT_NB                (1)

#define IS_EXTI2_GPIO_PORT(__PORT__)     ((__PORT__) == EXTI_GPIOZ)
#endif  /* CORE_CA35 || CORE_CM33 */

#if defined (CORE_CA35) || defined (CORE_CM33)
#define IS_EXTI_GPIO_PORT(__INSTANCE__, __PORT__)                 \
  ((((__INSTANCE__) == EXTI1) && IS_EXTI1_GPIO_PORT(__PORT__))  \
   ||                                                       \
   ((((__INSTANCE__) == EXTI2) && IS_EXTI2_GPIO_PORT(__PORT__))))
#else   /* CORE_CA35 || CORE_CM33 */
#define IS_EXTI_GPIO_PORT(__INSTANCE__, __PORT__)     (((__INSTANCE__) == EXTI2) && (__PORT__) == EXTI_GPIOZ)
#endif  /* CORE_CA35 || CORE_CM33 */

#define IS_EXTI1_GPIO_PIN(__PIN__)      (1<0)

#define IS_EXTI2_GPIO_PIN(__PIN__)      ((__PIN__) < EXTI2_GPIO_PIN_MAX)

#if defined (CORE_CA35) || defined (CORE_CM33)
#define IS_EXTI_GPIO_PIN(__INSTANCE__, __PIN__)                 \
  ((((__INSTANCE__) == EXTI1) && IS_EXTI1_GPIO_PIN(__PIN__))  \
   ||                                                       \
   ((((__INSTANCE__) == EXTI2) && IS_EXTI2_GPIO_PIN(__PIN__))))
#else   /* CORE_CA35 || CORE_CM33 */
#define IS_EXTI_GPIO_PIN(__INSTANCE__, __PIN__)      (((__INSTANCE__) == EXTI2) && (__PIN__) < EXTI2_GPIO_PIN_MAX)
#endif  /* CORE_CA35 || CORE_CM33 */
#endif  /* !defined (STM32MP2XX_ASSY3_1_0 ) */

#if defined (CORTEX_IN_SECURE_STATE)
#define IS_EXTI_LINE_ATTRIBUTES(__ATTRIBUTES__)   ( \
                                                    (((__ATTRIBUTES__)&EXTI_LINE_ATTR_CID_STATIC_SELECT ) ==   \
                                                     EXTI_LINE_ATTR_CID_STATIC_SELECT                   )      \
                                                    ||                                                         \
                                                    (((__ATTRIBUTES__)&EXTI_LINE_CID_DISABLE            ) ==   \
                                                     EXTI_LINE_CID_DISABLE                              )      \
                                                    ||                                                         \
                                                    (((__ATTRIBUTES__)&EXTI_LINE_ATTR_SEC_SELECT        ) ==   \
                                                     EXTI_LINE_ATTR_SEC_SELECT                          )      \
                                                    ||                                                         \
                                                    (((__ATTRIBUTES__)&EXTI_LINE_ATTR_PRIV_SELECT       ) ==   \
                                                     EXTI_LINE_ATTR_PRIV_SELECT                         )      \
                                                  )
#else   /* CORTEX_IN_SECURE_STATE */
#define IS_EXTI_LINE_ATTRIBUTES(__ATTRIBUTES__)   ( \
                                                    (((__ATTRIBUTES__)&EXTI_LINE_ATTR_CID_STATIC_SELECT ) ==   \
                                                     EXTI_LINE_ATTR_CID_STATIC_SELECT                   )      \
                                                    ||                                                         \
                                                    (((__ATTRIBUTES__)&EXTI_LINE_CID_DISABLE            ) ==   \
                                                     EXTI_LINE_CID_DISABLE                              )      \
                                                    ||                                                         \
                                                    (((__ATTRIBUTES__)&EXTI_LINE_ATTR_PRIV_SELECT       ) ==   \
                                                     EXTI_LINE_ATTR_PRIV_SELECT                         )      \
                                                  )
#endif  /* CORTEX_IN_SECURE_STATE */
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
HAL_StatusTypeDef HAL_EXTI_SetConfigLine(EXTI_HandleTypeDef *hexti, const EXTI_ConfigTypeDef *pExtiConfig);
HAL_StatusTypeDef HAL_EXTI_GetConfigLine(EXTI_HandleTypeDef *hexti, EXTI_ConfigTypeDef *pExtiConfig);
HAL_StatusTypeDef HAL_EXTI_ClearConfigLine(EXTI_HandleTypeDef *hexti);
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
void              HAL_EXTI_IRQHandler(EXTI_HandleTypeDef *hexti);
uint32_t          HAL_EXTI_GetPending(const EXTI_HandleTypeDef *hexti, uint32_t Edge);
void              HAL_EXTI_ClearPending(EXTI_HandleTypeDef *hexti, uint32_t Edge);
void              HAL_EXTI_GenerateSWI(const EXTI_HandleTypeDef *hexti);

/**
  * @}
  */

/* Register Access control  functions  *******************************************/
/** @defgroup EXTI_Exported_Functions_Group3 Register Access control functions
  * @{
  */
void              HAL_EXTI_ConfigLineAttributes(uint32_t ExtiLine, uint32_t LineAttributes);
HAL_StatusTypeDef HAL_EXTI_GetConfigLineAttributes(uint32_t ExtiLine, uint32_t *pLineAttributes);

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

#endif /* STM32MP2xx_HAL_EXTI_H */
