/**
  *********************************************************************************************************************
  * @file    stm32h7pxx_ll_exti.h
  * @brief   Header file of EXTI LL module.
  *********************************************************************************************************************
  * @attention
  *
  * Copyright (c) 2026 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  *********************************************************************************************************************
  */

/* Define to prevent recursive inclusion ----------------------------------------------------------------------------*/
#ifndef  STM32H7PXX_LL_EXTI_H
#define  STM32H7PXX_LL_EXTI_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ---------------------------------------------------------------------------------------------------------*/
#include "stm32h7pxx.h"

/** @addtogroup STM32H7Pxx_LL_Driver
  * @{
  */

#if defined (EXTI)

/** @defgroup EXTI_LL EXTI
  * @{
  */

/* Private types ----------------------------------------------------------------------------------------------------*/
/* Private variables ------------------------------------------------------------------------------------------------*/
/* Private constants ------------------------------------------------------------------------------------------------*/
/** @defgroup EXTI_LL_Private_Constants EXTI Private Constants
  * @{
  */
/**
  * @brief  EXTI Register Pin Position Shift.
  */
#define LL_EXTI_REGISTER_PINPOS_SHFT        16U   /*!< Definition used to shift the pin position in the EXTICR register */

/**
  * @brief  EXTI Line property definition.
  */
#define LL_EXTI_PROPERTY_SHIFT              24U
#define LL_EXTI_DIRECT                      (0x01UL << LL_EXTI_PROPERTY_SHIFT)
#define LL_EXTI_CONFIG                      (0x02UL << LL_EXTI_PROPERTY_SHIFT)
#define LL_EXTI_GPIO                        ((0x04UL << LL_EXTI_PROPERTY_SHIFT) | LL_EXTI_CONFIG)
#define LL_EXTI_RESERVED                    (0x08UL << LL_EXTI_PROPERTY_SHIFT)
#define LL_EXTI_PROPERTY_MASK               (LL_EXTI_DIRECT | LL_EXTI_CONFIG | LL_EXTI_GPIO)

/**
  * @brief  EXTI Source register number.
  */
#define LL_EXTI_CR_REGISTER_SHIFT           8U
#define LL_EXTI_CR1                         (0x00U << LL_EXTI_CR_REGISTER_SHIFT)
#define LL_EXTI_CR2                         (0x01UL << LL_EXTI_CR_REGISTER_SHIFT)
#define LL_EXTI_CR3                         (0x02UL << LL_EXTI_CR_REGISTER_SHIFT)
#define LL_EXTI_CR4                         (0x03UL << LL_EXTI_CR_REGISTER_SHIFT)

/**
  * @brief  EXTI Register and bit usage.
  */
#define LL_EXTI_REG_SHIFT                   16U
#define LL_EXTI_REG1                        (0x01UL << LL_EXTI_REG_SHIFT)
#define LL_EXTI_REG2                        (0x02UL << LL_EXTI_REG_SHIFT)
#define LL_EXTI_REG3                        (0x04UL << LL_EXTI_REG_SHIFT)
#define LL_EXTI_REG_MASK                    (LL_EXTI_REG1 | LL_EXTI_REG2 | LL_EXTI_REG3)
#define LL_EXTI_PIN_MASK                    0x0000001FU

/**
  * @brief  EXTI Line number.
  */
#define LL_EXTI_LINE_NB                     78U
/**
  * @}
  */
/* Private Macros ---------------------------------------------------------------------------------------------------*/
/** @defgroup EXTI_LL_Private_Macros EXTI Private Macros
  * @{
  */
/**
  * @}
  */

/* Exported types ---------------------------------------------------------------------------------------------------*/
/** @defgroup EXTI_LL_ES_INIT LL EXTI Init structure
  * @{
  */
/**
  * @}
  */

/* Exported constants -----------------------------------------------------------------------------------------------*/
/** @defgroup EXTI_LL_Exported_Constants LL EXTI Constants
  * @{
  */

/** @defgroup EXTI_LL_EC_LINE LINE
  * @{
  */
#define LL_EXTI_LINE_0                EXTI_IMR1_IM0           /*!< Extended line 0 */
#define LL_EXTI_LINE_1                EXTI_IMR1_IM1           /*!< Extended line 1 */
#define LL_EXTI_LINE_2                EXTI_IMR1_IM2           /*!< Extended line 2 */
#define LL_EXTI_LINE_3                EXTI_IMR1_IM3           /*!< Extended line 3 */
#define LL_EXTI_LINE_4                EXTI_IMR1_IM4           /*!< Extended line 4 */
#define LL_EXTI_LINE_5                EXTI_IMR1_IM5           /*!< Extended line 5 */
#define LL_EXTI_LINE_6                EXTI_IMR1_IM6           /*!< Extended line 6 */
#define LL_EXTI_LINE_7                EXTI_IMR1_IM7           /*!< Extended line 7 */
#define LL_EXTI_LINE_8                EXTI_IMR1_IM8           /*!< Extended line 8 */
#define LL_EXTI_LINE_9                EXTI_IMR1_IM9           /*!< Extended line 9 */
#define LL_EXTI_LINE_10               EXTI_IMR1_IM10          /*!< Extended line 10 */
#define LL_EXTI_LINE_11               EXTI_IMR1_IM11          /*!< Extended line 11 */
#define LL_EXTI_LINE_12               EXTI_IMR1_IM12          /*!< Extended line 12 */
#define LL_EXTI_LINE_13               EXTI_IMR1_IM13          /*!< Extended line 13 */
#define LL_EXTI_LINE_14               EXTI_IMR1_IM14          /*!< Extended line 14 */
#define LL_EXTI_LINE_15               EXTI_IMR1_IM15          /*!< Extended line 15 */
#define LL_EXTI_LINE_16               EXTI_IMR1_IM16          /*!< Extended line 16 */
#define LL_EXTI_LINE_17               EXTI_IMR1_IM17          /*!< Extended line 17 */
#define LL_EXTI_LINE_18               EXTI_IMR1_IM18          /*!< Extended line 18 */
#define LL_EXTI_LINE_19               EXTI_IMR1_IM19          /*!< Extended line 19 */
#define LL_EXTI_LINE_20               EXTI_IMR1_IM20          /*!< Extended line 20 */
#define LL_EXTI_LINE_21               EXTI_IMR1_IM21          /*!< Extended line 21 */
#define LL_EXTI_LINE_22               EXTI_IMR1_IM22          /*!< Extended line 22 */
#define LL_EXTI_LINE_23               EXTI_IMR1_IM23          /*!< Extended line 23 */
#define LL_EXTI_LINE_24               EXTI_IMR1_IM24          /*!< Extended line 24 */
#define LL_EXTI_LINE_25               EXTI_IMR1_IM25          /*!< Extended line 25 */
#define LL_EXTI_LINE_26               EXTI_IMR1_IM26          /*!< Extended line 26 */
#define LL_EXTI_LINE_27               EXTI_IMR1_IM27          /*!< Extended line 27 */
#define LL_EXTI_LINE_28               EXTI_IMR1_IM28          /*!< Extended line 28 */
#define LL_EXTI_LINE_29               EXTI_IMR1_IM29          /*!< Extended line 29 */
#define LL_EXTI_LINE_30               EXTI_IMR1_IM30          /*!< Extended line 30 */
#define LL_EXTI_LINE_31               EXTI_IMR1_IM31          /*!< Extended line 31 */
#define LL_EXTI_LINE_ALL_0_31         0xFFFFFFFFU             /*!< All extended lines */

#define LL_EXTI_LINE_32               EXTI_IMR2_IM32          /*!< Extended line 32 */
#define LL_EXTI_LINE_33               EXTI_IMR2_IM33          /*!< Extended line 33 */
#define LL_EXTI_LINE_34               EXTI_IMR2_IM34          /*!< Extended line 34 */
#define LL_EXTI_LINE_35               EXTI_IMR2_IM35          /*!< Extended line 35 */
#define LL_EXTI_LINE_36               EXTI_IMR2_IM36          /*!< Extended line 36 */
#define LL_EXTI_LINE_37               EXTI_IMR2_IM37          /*!< Extended line 37 */
#define LL_EXTI_LINE_38               EXTI_IMR2_IM38          /*!< Extended line 38 */
#define LL_EXTI_LINE_39               EXTI_IMR2_IM39          /*!< Extended line 39 */
#define LL_EXTI_LINE_40               EXTI_IMR2_IM40          /*!< Extended line 40 */
#define LL_EXTI_LINE_41               EXTI_IMR2_IM41          /*!< Extended line 41 */
#define LL_EXTI_LINE_42               EXTI_IMR2_IM42          /*!< Extended line 42 */
#define LL_EXTI_LINE_43               EXTI_IMR2_IM43          /*!< Extended line 43 */
#define LL_EXTI_LINE_44               EXTI_IMR2_IM44          /*!< Extended line 44 */
#define LL_EXTI_LINE_45               EXTI_IMR2_IM45          /*!< Extended line 45 */
#define LL_EXTI_LINE_46               EXTI_IMR2_IM46          /*!< Extended line 46 */
#define LL_EXTI_LINE_47               EXTI_IMR2_IM47          /*!< Extended line 47 */
#define LL_EXTI_LINE_48               EXTI_IMR2_IM48          /*!< Extended line 48 */
#define LL_EXTI_LINE_49               EXTI_IMR2_IM49          /*!< Extended line 49 */
#define LL_EXTI_LINE_50               EXTI_IMR2_IM50          /*!< Extended line 50 */
#define LL_EXTI_LINE_51               EXTI_IMR2_IM51          /*!< Extended line 51 */
#define LL_EXTI_LINE_52               EXTI_IMR2_IM52          /*!< Extended line 52 */
#define LL_EXTI_LINE_53               EXTI_IMR2_IM53          /*!< Extended line 53 */
#define LL_EXTI_LINE_55               EXTI_IMR2_IM55          /*!< Extended line 55 */
#define LL_EXTI_LINE_56               EXTI_IMR2_IM56          /*!< Extended line 56 */
#define LL_EXTI_LINE_57               EXTI_IMR2_IM57          /*!< Extended line 57 */
#define LL_EXTI_LINE_58               EXTI_IMR2_IM58          /*!< Extended line 58 */
#define LL_EXTI_LINE_59               EXTI_IMR2_IM59          /*!< Extended line 59 */
#define LL_EXTI_LINE_60               EXTI_IMR2_IM60          /*!< Extended line 60 */
#define LL_EXTI_LINE_61               EXTI_IMR2_IM61          /*!< Extended line 61 */
#define LL_EXTI_LINE_62               EXTI_IMR2_IM62          /*!< Extended line 62 */
#define LL_EXTI_LINE_63               EXTI_IMR2_IM63          /*!< Extended line 63 */
#define LL_EXTI_LINE_ALL_32_63        0xFFBFFFFFU             /*!< All extended lines */

#define LL_EXTI_LINE_64               EXTI_IMR3_IM64          /*!< Extended line 64 */
#define LL_EXTI_LINE_65               EXTI_IMR3_IM65          /*!< Extended line 65 */
#define LL_EXTI_LINE_66               EXTI_IMR3_IM66          /*!< Extended line 66 */
#define LL_EXTI_LINE_67               EXTI_IMR3_IM67          /*!< Extended line 67 */
#define LL_EXTI_LINE_68               EXTI_IMR3_IM68          /*!< Extended line 68 */
#define LL_EXTI_LINE_69               EXTI_IMR3_IM69          /*!< Extended line 69 */
#define LL_EXTI_LINE_70               EXTI_IMR3_IM70           /*!< Extended line 70 */
#define LL_EXTI_LINE_71               EXTI_IMR3_IM71           /*!< Extended line 71 */
#define LL_EXTI_LINE_77               EXTI_IMR3_IM77           /*!< Extended line 77 */
#define LL_EXTI_LINE_ALL_64_95        0x000020FFU              /*!< All extended lines */
/**
  * @}
  */


/** @defgroup EXTI_LL_EC_MODE Mode
  * @{
  */
#define LL_EXTI_MODE_IT                 ((uint8_t)0x01U) /*!< Interrupt Mode */
#define LL_EXTI_MODE_EVENT              ((uint8_t)0x02U) /*!< Event Mode */
#define LL_EXTI_MODE_IT_EVENT           ((uint8_t)0x03U) /*!< Interrupt & Event Mode */
/**
  * @}
  */

/** @defgroup EXTI_LL_EC_TRIGGER Edge Trigger
  * @{
  */
#define LL_EXTI_TRIGGER_NONE            ((uint8_t)0x00U) /*!< No Trigger Mode */
#define LL_EXTI_TRIGGER_RISING          ((uint8_t)0x01U) /*!< Trigger Rising Mode */
#define LL_EXTI_TRIGGER_FALLING         ((uint8_t)0x02U) /*!< Trigger Falling Mode */
#define LL_EXTI_TRIGGER_RISING_FALLING  ((uint8_t)0x03U) /*!< Trigger Rising & Falling Mode */
/**
  * @}
  */

/**
  * @}
  */

/* Exported macros ---------------------------------------------------------------------------------------------------*/
/** @defgroup EXTI_LL_Exported_Macros LL EXTI Macros
  * @{
  */

/** @defgroup EXTI_LL_EM_WRITE_READ Common Write and read registers Macros
  * @{
  */

/**
  * @brief  Write a value in EXTI register.
  * @param reg Register to be written.
  * @param value Value to be written in the register.
  */
#define LL_EXTI_WRITE_REG(reg, value) STM32_WRITE_REG(EXTI->reg, (value))

/**
  * @brief  Read a value in EXTI register.
  * @param reg Register to be read.
  * @retval Register value
  */
#define LL_EXTI_READ_REG(reg) STM32_READ_REG(EXTI->reg)
/**
  * @}
  */


/**
  * @}
  */


/* Exported functions -----------------------------------------------------------------------------------------------*/
/** @defgroup EXTI_LL_Exported_Functions LL EXTI Functions
  * @{
  */
/** @defgroup EXTI_LL_EF_IT_Management IT_Management
  * @{
  */

/**
  * @brief  Enable EXTI Line Interrupt request for Lines in range 0 to 31.
  * @rmtoll
  *  IMR1         IMx           LL_EXTI_EnableIT_0_31
  * @param exti_line This parameter can be one of the following values:
  *         @arg @ref LL_EXTI_LINE_0
  *         @arg @ref LL_EXTI_LINE_1
  *         @arg @ref LL_EXTI_LINE_2
  *         @arg @ref LL_EXTI_LINE_3
  *         @arg @ref LL_EXTI_LINE_4
  *         @arg @ref LL_EXTI_LINE_5
  *         @arg @ref LL_EXTI_LINE_6
  *         @arg @ref LL_EXTI_LINE_7
  *         @arg @ref LL_EXTI_LINE_8
  *         @arg @ref LL_EXTI_LINE_9
  *         @arg @ref LL_EXTI_LINE_10
  *         @arg @ref LL_EXTI_LINE_11
  *         @arg @ref LL_EXTI_LINE_12
  *         @arg @ref LL_EXTI_LINE_13
  *         @arg @ref LL_EXTI_LINE_14
  *         @arg @ref LL_EXTI_LINE_15
  *         @arg @ref LL_EXTI_LINE_16
  *         @arg @ref LL_EXTI_LINE_17
  *         @arg @ref LL_EXTI_LINE_18
  *         @arg @ref LL_EXTI_LINE_19
  *         @arg @ref LL_EXTI_LINE_20
  *         @arg @ref LL_EXTI_LINE_21
  *         @arg @ref LL_EXTI_LINE_22
  *         @arg @ref LL_EXTI_LINE_23
  *         @arg @ref LL_EXTI_LINE_24
  *         @arg @ref LL_EXTI_LINE_25
  *         @arg @ref LL_EXTI_LINE_26
  *         @arg @ref LL_EXTI_LINE_27
  *         @arg @ref LL_EXTI_LINE_28
  *         @arg @ref LL_EXTI_LINE_29
  *         @arg @ref LL_EXTI_LINE_30
  *         @arg @ref LL_EXTI_LINE_31
  *         @arg @ref LL_EXTI_LINE_ALL_0_31
  * @note The reset value for the direct or internal lines (see RM)
  *       is set to 1 in order to enable the interrupt by default.
  *       Bits are set automatically at power-on.
  * @note (*)Please check each device line mapping for EXTI Line availability.
  */
__STATIC_INLINE void LL_EXTI_EnableIT_0_31(uint32_t exti_line)
{
  STM32_ATOMIC_SET_BIT_32(EXTI->IMR1, exti_line);
}

/**
  * @brief  Enable EXTI Line Interrupt request for Lines in range 32 to 63.
  * @rmtoll
  *  IMR2         IMx           LL_EXTI_EnableIT_32_63
  * @param exti_line This parameter can be one of the following values:
  *         @arg @ref LL_EXTI_LINE_32
  *         @arg @ref LL_EXTI_LINE_33
  *         @arg @ref LL_EXTI_LINE_34
  *         @arg @ref LL_EXTI_LINE_35
  *         @arg @ref LL_EXTI_LINE_36
  *         @arg @ref LL_EXTI_LINE_37
  *         @arg @ref LL_EXTI_LINE_38
  *         @arg @ref LL_EXTI_LINE_39
  *         @arg @ref LL_EXTI_LINE_40
  *         @arg @ref LL_EXTI_LINE_41
  *         @arg @ref LL_EXTI_LINE_42
  *         @arg @ref LL_EXTI_LINE_43
  *         @arg @ref LL_EXTI_LINE_44
  *         @arg @ref LL_EXTI_LINE_45
  *         @arg @ref LL_EXTI_LINE_46
  *         @arg @ref LL_EXTI_LINE_47
  *         @arg @ref LL_EXTI_LINE_48
  *         @arg @ref LL_EXTI_LINE_49
  *         @arg @ref LL_EXTI_LINE_50
  *         @arg @ref LL_EXTI_LINE_51
  *         @arg @ref LL_EXTI_LINE_52
  *         @arg @ref LL_EXTI_LINE_53
  *         @arg @ref LL_EXTI_LINE_55
  *         @arg @ref LL_EXTI_LINE_56
  *         @arg @ref LL_EXTI_LINE_57
  *         @arg @ref LL_EXTI_LINE_58
  *         @arg @ref LL_EXTI_LINE_59
  *         @arg @ref LL_EXTI_LINE_60
  *         @arg @ref LL_EXTI_LINE_61
  *         @arg @ref LL_EXTI_LINE_62
  *         @arg @ref LL_EXTI_LINE_63
  *         @arg @ref LL_EXTI_LINE_ALL_32_63
  * @note The reset value for the direct or internal lines (see RM)
  *       is set to 1 in order to enable the interrupt by default.
  *       Bits are set automatically at power-on.
  * @note (*)Please check each device line mapping for EXTI Line availability.
  */
__STATIC_INLINE void LL_EXTI_EnableIT_32_63(uint32_t exti_line)
{
  STM32_ATOMIC_SET_BIT_32(EXTI->IMR2, exti_line);
}

/**
  * @brief  Enable EXTI Line Interrupt request for Lines in range 64 to 95.
  * @rmtoll
  *  IMR3         IMx           LL_EXTI_EnableIT_64_95
  * @param exti_line This parameter can be one of the following values:
  *         @arg @ref LL_EXTI_LINE_64
  *         @arg @ref LL_EXTI_LINE_65
  *         @arg @ref LL_EXTI_LINE_66
  *         @arg @ref LL_EXTI_LINE_67
  *         @arg @ref LL_EXTI_LINE_68
  *         @arg @ref LL_EXTI_LINE_69
  *         @arg @ref LL_EXTI_LINE_70
  *         @arg @ref LL_EXTI_LINE_71
  *         @arg @ref LL_EXTI_LINE_77
  *         @arg @ref LL_EXTI_LINE_ALL_64_95
  * @note The reset value for the direct or internal lines (see RM)
  *       is set to 1 in order to enable the interrupt by default.
  *       Bits are set automatically at power-on.
  * @note (*)Please check each device line mapping for EXTI Line availability.
  */
__STATIC_INLINE void LL_EXTI_EnableIT_64_95(uint32_t exti_line)
{
  STM32_ATOMIC_SET_BIT_32(EXTI->IMR3, exti_line);
}

/**
  * @brief  Disable EXTI Line Interrupt request for Lines in range 0 to 31.
  * @rmtoll
  *  IMR1         IMx           LL_EXTI_DisableIT_0_31
  * @param exti_line This parameter can be one of the following values:
  *         @arg @ref LL_EXTI_LINE_0
  *         @arg @ref LL_EXTI_LINE_1
  *         @arg @ref LL_EXTI_LINE_2
  *         @arg @ref LL_EXTI_LINE_3
  *         @arg @ref LL_EXTI_LINE_4
  *         @arg @ref LL_EXTI_LINE_5
  *         @arg @ref LL_EXTI_LINE_6
  *         @arg @ref LL_EXTI_LINE_7
  *         @arg @ref LL_EXTI_LINE_8
  *         @arg @ref LL_EXTI_LINE_9
  *         @arg @ref LL_EXTI_LINE_10
  *         @arg @ref LL_EXTI_LINE_11
  *         @arg @ref LL_EXTI_LINE_12
  *         @arg @ref LL_EXTI_LINE_13
  *         @arg @ref LL_EXTI_LINE_14
  *         @arg @ref LL_EXTI_LINE_15
  *         @arg @ref LL_EXTI_LINE_16
  *         @arg @ref LL_EXTI_LINE_17
  *         @arg @ref LL_EXTI_LINE_18
  *         @arg @ref LL_EXTI_LINE_19
  *         @arg @ref LL_EXTI_LINE_20
  *         @arg @ref LL_EXTI_LINE_21
  *         @arg @ref LL_EXTI_LINE_22
  *         @arg @ref LL_EXTI_LINE_23
  *         @arg @ref LL_EXTI_LINE_24
  *         @arg @ref LL_EXTI_LINE_25
  *         @arg @ref LL_EXTI_LINE_26
  *         @arg @ref LL_EXTI_LINE_27
  *         @arg @ref LL_EXTI_LINE_28
  *         @arg @ref LL_EXTI_LINE_29
  *         @arg @ref LL_EXTI_LINE_30
  *         @arg @ref LL_EXTI_LINE_31
  *         @arg @ref LL_EXTI_LINE_ALL_0_31
  * @note The reset value for the direct or internal lines (see RM)
  *       is set to 1 in order to enable the interrupt by default.
  *       Bits are set automatically at power-on.
  * @note (*)Please check each device line mapping for EXTI Line availability.
  */
__STATIC_INLINE void LL_EXTI_DisableIT_0_31(uint32_t exti_line)
{
  STM32_ATOMIC_CLEAR_BIT_32(EXTI->IMR1, exti_line);
}

/**
  * @brief  Disable EXTI Line Interrupt request for Lines in range 32 to 63.
  * @rmtoll
  *  IMR2         IMx           LL_EXTI_DisableIT_32_63
  * @param exti_line This parameter can be one of the following values:
  *         @arg @ref LL_EXTI_LINE_32
  *         @arg @ref LL_EXTI_LINE_33
  *         @arg @ref LL_EXTI_LINE_34
  *         @arg @ref LL_EXTI_LINE_35
  *         @arg @ref LL_EXTI_LINE_36
  *         @arg @ref LL_EXTI_LINE_37
  *         @arg @ref LL_EXTI_LINE_38
  *         @arg @ref LL_EXTI_LINE_39
  *         @arg @ref LL_EXTI_LINE_40
  *         @arg @ref LL_EXTI_LINE_41
  *         @arg @ref LL_EXTI_LINE_42
  *         @arg @ref LL_EXTI_LINE_43
  *         @arg @ref LL_EXTI_LINE_44
  *         @arg @ref LL_EXTI_LINE_45
  *         @arg @ref LL_EXTI_LINE_46
  *         @arg @ref LL_EXTI_LINE_47
  *         @arg @ref LL_EXTI_LINE_48
  *         @arg @ref LL_EXTI_LINE_49
  *         @arg @ref LL_EXTI_LINE_50
  *         @arg @ref LL_EXTI_LINE_51
  *         @arg @ref LL_EXTI_LINE_52
  *         @arg @ref LL_EXTI_LINE_53
  *         @arg @ref LL_EXTI_LINE_55
  *         @arg @ref LL_EXTI_LINE_56
  *         @arg @ref LL_EXTI_LINE_57
  *         @arg @ref LL_EXTI_LINE_58
  *         @arg @ref LL_EXTI_LINE_59
  *         @arg @ref LL_EXTI_LINE_60
  *         @arg @ref LL_EXTI_LINE_61
  *         @arg @ref LL_EXTI_LINE_62
  *         @arg @ref LL_EXTI_LINE_63
  *         @arg @ref LL_EXTI_LINE_ALL_32_63
  * @note The reset value for the direct or internal lines (see RM)
  *       is set to 1 in order to enable the interrupt by default.
  *       Bits are set automatically at power-on.
  * @note (*)Please check each device line mapping for EXTI Line availability.
  */
__STATIC_INLINE void LL_EXTI_DisableIT_32_63(uint32_t exti_line)
{
  STM32_ATOMIC_CLEAR_BIT_32(EXTI->IMR2, exti_line);
}

/**
  * @brief  Disable EXTI Line Interrupt request for Lines in range 64 to 95.
  * @rmtoll
  *  IMR3         IMx           LL_EXTI_DisableIT_64_95
  * @param exti_line This parameter can be one of the following values:
  *         @arg @ref LL_EXTI_LINE_64
  *         @arg @ref LL_EXTI_LINE_65
  *         @arg @ref LL_EXTI_LINE_66
  *         @arg @ref LL_EXTI_LINE_67
  *         @arg @ref LL_EXTI_LINE_68
  *         @arg @ref LL_EXTI_LINE_69
  *         @arg @ref LL_EXTI_LINE_70
  *         @arg @ref LL_EXTI_LINE_71
  *         @arg @ref LL_EXTI_LINE_77
  *         @arg @ref LL_EXTI_LINE_ALL_64_95
  * @note The reset value for the direct or internal lines (see RM)
  *       is set to 1 in order to enable the interrupt by default.
  *       Bits are set automatically at power-on.
  * @note (*)Please check each device line mapping for EXTI Line availability.
  * @note Please check each device line mapping for EXTI Line availability.
  */
__STATIC_INLINE void LL_EXTI_DisableIT_64_95(uint32_t exti_line)
{
  STM32_ATOMIC_CLEAR_BIT_32(EXTI->IMR3, exti_line);
}

/**
  * @brief  Indicate if EXTI Line Interrupt request is enabled for Lines in range 0 to 31.
  * @rmtoll
  *  IMR1         IMx           LL_EXTI_IsEnabledIT_0_31
  * @param exti_line This parameter can be one of the following values:
  *         @arg @ref LL_EXTI_LINE_0
  *         @arg @ref LL_EXTI_LINE_1
  *         @arg @ref LL_EXTI_LINE_2
  *         @arg @ref LL_EXTI_LINE_3
  *         @arg @ref LL_EXTI_LINE_4
  *         @arg @ref LL_EXTI_LINE_5
  *         @arg @ref LL_EXTI_LINE_6
  *         @arg @ref LL_EXTI_LINE_7
  *         @arg @ref LL_EXTI_LINE_8
  *         @arg @ref LL_EXTI_LINE_9
  *         @arg @ref LL_EXTI_LINE_10
  *         @arg @ref LL_EXTI_LINE_11
  *         @arg @ref LL_EXTI_LINE_12
  *         @arg @ref LL_EXTI_LINE_13
  *         @arg @ref LL_EXTI_LINE_14
  *         @arg @ref LL_EXTI_LINE_15
  *         @arg @ref LL_EXTI_LINE_16
  *         @arg @ref LL_EXTI_LINE_17
  *         @arg @ref LL_EXTI_LINE_18
  *         @arg @ref LL_EXTI_LINE_19
  *         @arg @ref LL_EXTI_LINE_20
  *         @arg @ref LL_EXTI_LINE_21
  *         @arg @ref LL_EXTI_LINE_22
  *         @arg @ref LL_EXTI_LINE_23
  *         @arg @ref LL_EXTI_LINE_24
  *         @arg @ref LL_EXTI_LINE_25
  *         @arg @ref LL_EXTI_LINE_26
  *         @arg @ref LL_EXTI_LINE_27
  *         @arg @ref LL_EXTI_LINE_28
  *         @arg @ref LL_EXTI_LINE_29
  *         @arg @ref LL_EXTI_LINE_30
  *         @arg @ref LL_EXTI_LINE_31
  * @note The reset value for the direct or internal lines (see RM)
  *       is set to 1 in order to enable the interrupt by default.
  *       Bits are set automatically at power-on.
  * @note (*)Please check each device line mapping for EXTI Line availability.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_EXTI_IsEnabledIT_0_31(uint32_t exti_line)
{
  return ((STM32_READ_BIT(EXTI->IMR1, exti_line) == (exti_line)) ? 1UL : 0UL);
}

/**
  * @brief  Indicate if EXTI Line Interrupt request is enabled for Lines in range 32 to 63.
  * @rmtoll
  *  IMR2         IMx           LL_EXTI_IsEnabledIT_32_63
  * @param exti_line This parameter can be one of the following values:
  *         @arg @ref LL_EXTI_LINE_32
  *         @arg @ref LL_EXTI_LINE_33
  *         @arg @ref LL_EXTI_LINE_34
  *         @arg @ref LL_EXTI_LINE_35
  *         @arg @ref LL_EXTI_LINE_36
  *         @arg @ref LL_EXTI_LINE_37
  *         @arg @ref LL_EXTI_LINE_38
  *         @arg @ref LL_EXTI_LINE_39
  *         @arg @ref LL_EXTI_LINE_40
  *         @arg @ref LL_EXTI_LINE_41
  *         @arg @ref LL_EXTI_LINE_42
  *         @arg @ref LL_EXTI_LINE_43
  *         @arg @ref LL_EXTI_LINE_44
  *         @arg @ref LL_EXTI_LINE_45
  *         @arg @ref LL_EXTI_LINE_46
  *         @arg @ref LL_EXTI_LINE_47
  *         @arg @ref LL_EXTI_LINE_48
  *         @arg @ref LL_EXTI_LINE_49
  *         @arg @ref LL_EXTI_LINE_50
  *         @arg @ref LL_EXTI_LINE_51
  *         @arg @ref LL_EXTI_LINE_52
  *         @arg @ref LL_EXTI_LINE_53
  *         @arg @ref LL_EXTI_LINE_55
  *         @arg @ref LL_EXTI_LINE_56
  *         @arg @ref LL_EXTI_LINE_57
  *         @arg @ref LL_EXTI_LINE_58
  *         @arg @ref LL_EXTI_LINE_59
  *         @arg @ref LL_EXTI_LINE_60
  *         @arg @ref LL_EXTI_LINE_61
  *         @arg @ref LL_EXTI_LINE_62
  *         @arg @ref LL_EXTI_LINE_63
  * @note The reset value for the direct or internal lines (see RM)
  *       is set to 1 in order to enable the interrupt by default.
  *       Bits are set automatically at power-on.
  * @note (*)Please check each device line mapping for EXTI Line availability.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_EXTI_IsEnabledIT_32_63(uint32_t exti_line)
{
  return ((STM32_READ_BIT(EXTI->IMR2, exti_line) == (exti_line)) ? 1U : 0U);
}

/**
  * @brief  Indicate if EXTI Line Interrupt request is enabled for Lines in range 64 to 95.
  * @rmtoll
  *  IMR3         IMx           LL_EXTI_IsEnabledIT_64_95
  * @param exti_line This parameter can be one of the following values:
  *         @arg @ref LL_EXTI_LINE_64
  *         @arg @ref LL_EXTI_LINE_65
  *         @arg @ref LL_EXTI_LINE_66
  *         @arg @ref LL_EXTI_LINE_67
  *         @arg @ref LL_EXTI_LINE_68
  *         @arg @ref LL_EXTI_LINE_69
  *         @arg @ref LL_EXTI_LINE_70
  *         @arg @ref LL_EXTI_LINE_71
  *         @arg @ref LL_EXTI_LINE_77
  * @note The reset value for the direct or internal lines (see RM)
  *       is set to 1 in order to enable the interrupt by default.
  *       Bits are set automatically at power-on.
  * @note (*)Please check each device line mapping for EXTI Line availability.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_EXTI_IsEnabledIT_64_95(uint32_t exti_line)
{
  return ((STM32_READ_BIT(EXTI->IMR3, exti_line) == (exti_line)) ? 1U : 0U);
}

/**
  * @}
  */

/** @defgroup EXTI_LL_EF_Event_Management Event_Management
  * @{
  */

/**
  * @brief  Enable EXTI Line Event request for Lines in range 0 to 31.
  * @rmtoll
  *  EMR1         EMx           LL_EXTI_EnableEvent_0_31
  * @param exti_line This parameter can be one of the following values:
  *         @arg @ref LL_EXTI_LINE_0
  *         @arg @ref LL_EXTI_LINE_1
  *         @arg @ref LL_EXTI_LINE_2
  *         @arg @ref LL_EXTI_LINE_3
  *         @arg @ref LL_EXTI_LINE_4
  *         @arg @ref LL_EXTI_LINE_5
  *         @arg @ref LL_EXTI_LINE_6
  *         @arg @ref LL_EXTI_LINE_7
  *         @arg @ref LL_EXTI_LINE_8
  *         @arg @ref LL_EXTI_LINE_9
  *         @arg @ref LL_EXTI_LINE_10
  *         @arg @ref LL_EXTI_LINE_11
  *         @arg @ref LL_EXTI_LINE_12
  *         @arg @ref LL_EXTI_LINE_13
  *         @arg @ref LL_EXTI_LINE_14
  *         @arg @ref LL_EXTI_LINE_15
  *         @arg @ref LL_EXTI_LINE_16
  *         @arg @ref LL_EXTI_LINE_17
  *         @arg @ref LL_EXTI_LINE_18
  *         @arg @ref LL_EXTI_LINE_19
  *         @arg @ref LL_EXTI_LINE_20
  *         @arg @ref LL_EXTI_LINE_21
  *         @arg @ref LL_EXTI_LINE_22
  *         @arg @ref LL_EXTI_LINE_23
  *         @arg @ref LL_EXTI_LINE_24
  *         @arg @ref LL_EXTI_LINE_25
  *         @arg @ref LL_EXTI_LINE_26
  *         @arg @ref LL_EXTI_LINE_27
  *         @arg @ref LL_EXTI_LINE_28
  *         @arg @ref LL_EXTI_LINE_29
  *         @arg @ref LL_EXTI_LINE_30
  *         @arg @ref LL_EXTI_LINE_31
  *         @arg @ref LL_EXTI_LINE_ALL_0_31
  * @note   (*)Please check each device line mapping for EXTI Line availability
  */
__STATIC_INLINE void LL_EXTI_EnableEvent_0_31(uint32_t exti_line)
{
  STM32_ATOMIC_SET_BIT_32(EXTI->EMR1, exti_line);
}

/**
  * @brief  Enable EXTI Line Event request for Lines in range 32 to 63.
  * @rmtoll
  *  EMR2         EMx           LL_EXTI_EnableEvent_32_63
  * @param exti_line This parameter can be a combination of the following values:
  *         @arg @ref LL_EXTI_LINE_32
  *         @arg @ref LL_EXTI_LINE_33
  *         @arg @ref LL_EXTI_LINE_34
  *         @arg @ref LL_EXTI_LINE_35
  *         @arg @ref LL_EXTI_LINE_36
  *         @arg @ref LL_EXTI_LINE_37
  *         @arg @ref LL_EXTI_LINE_38
  *         @arg @ref LL_EXTI_LINE_39
  *         @arg @ref LL_EXTI_LINE_40
  *         @arg @ref LL_EXTI_LINE_41
  *         @arg @ref LL_EXTI_LINE_42
  *         @arg @ref LL_EXTI_LINE_43
  *         @arg @ref LL_EXTI_LINE_44
  *         @arg @ref LL_EXTI_LINE_45
  *         @arg @ref LL_EXTI_LINE_46
  *         @arg @ref LL_EXTI_LINE_47
  *         @arg @ref LL_EXTI_LINE_48
  *         @arg @ref LL_EXTI_LINE_49
  *         @arg @ref LL_EXTI_LINE_50
  *         @arg @ref LL_EXTI_LINE_51
  *         @arg @ref LL_EXTI_LINE_52
  *         @arg @ref LL_EXTI_LINE_53
  *         @arg @ref LL_EXTI_LINE_55
  *         @arg @ref LL_EXTI_LINE_56
  *         @arg @ref LL_EXTI_LINE_57
  *         @arg @ref LL_EXTI_LINE_58
  *         @arg @ref LL_EXTI_LINE_59
  *         @arg @ref LL_EXTI_LINE_60
  *         @arg @ref LL_EXTI_LINE_61
  *         @arg @ref LL_EXTI_LINE_62
  *         @arg @ref LL_EXTI_LINE_63
  *         @arg @ref LL_EXTI_LINE_ALL_32_63
  * @note   (*)Please check each device line mapping for EXTI Line availability
  */
__STATIC_INLINE void LL_EXTI_EnableEvent_32_63(uint32_t exti_line)
{
  STM32_ATOMIC_SET_BIT_32(EXTI->EMR2, exti_line);
}

/**
  * @brief  Enable EXTI Line Event request for Lines in range 64 to 95.
  * @rmtoll
  *  EMR3         EMx           LL_EXTI_EnableEvent_64_95
  * @param exti_line This parameter can be a combination of the following values:
  *         @arg @ref LL_EXTI_LINE_64
  *         @arg @ref LL_EXTI_LINE_65
  *         @arg @ref LL_EXTI_LINE_66
  *         @arg @ref LL_EXTI_LINE_67
  *         @arg @ref LL_EXTI_LINE_68
  *         @arg @ref LL_EXTI_LINE_69
  *         @arg @ref LL_EXTI_LINE_70
  *         @arg @ref LL_EXTI_LINE_71
  *         @arg @ref LL_EXTI_LINE_77
  *         @arg @ref LL_EXTI_LINE_ALL_64_95
  * @note (*)Please check each device line mapping for EXTI Line availability.
  */
__STATIC_INLINE void LL_EXTI_EnableEvent_64_95(uint32_t exti_line)
{
  STM32_ATOMIC_SET_BIT_32(EXTI->EMR3, exti_line);
}

/**
  * @brief  Disable EXTI Line Event request for Lines in range 0 to 31.
  * @rmtoll
  *  EMR1         EMx           LL_EXTI_DisableEvent_0_31
  * @param exti_line This parameter can be one of the following values:
  *         @arg @ref LL_EXTI_LINE_0
  *         @arg @ref LL_EXTI_LINE_1
  *         @arg @ref LL_EXTI_LINE_2
  *         @arg @ref LL_EXTI_LINE_3
  *         @arg @ref LL_EXTI_LINE_4
  *         @arg @ref LL_EXTI_LINE_5
  *         @arg @ref LL_EXTI_LINE_6
  *         @arg @ref LL_EXTI_LINE_7
  *         @arg @ref LL_EXTI_LINE_8
  *         @arg @ref LL_EXTI_LINE_9
  *         @arg @ref LL_EXTI_LINE_10
  *         @arg @ref LL_EXTI_LINE_11
  *         @arg @ref LL_EXTI_LINE_12
  *         @arg @ref LL_EXTI_LINE_13
  *         @arg @ref LL_EXTI_LINE_14
  *         @arg @ref LL_EXTI_LINE_15
  *         @arg @ref LL_EXTI_LINE_16
  *         @arg @ref LL_EXTI_LINE_17
  *         @arg @ref LL_EXTI_LINE_18
  *         @arg @ref LL_EXTI_LINE_19
  *         @arg @ref LL_EXTI_LINE_20
  *         @arg @ref LL_EXTI_LINE_21
  *         @arg @ref LL_EXTI_LINE_22
  *         @arg @ref LL_EXTI_LINE_23
  *         @arg @ref LL_EXTI_LINE_24
  *         @arg @ref LL_EXTI_LINE_25
  *         @arg @ref LL_EXTI_LINE_26
  *         @arg @ref LL_EXTI_LINE_27
  *         @arg @ref LL_EXTI_LINE_28
  *         @arg @ref LL_EXTI_LINE_29
  *         @arg @ref LL_EXTI_LINE_30
  *         @arg @ref LL_EXTI_LINE_31
  *         @arg @ref LL_EXTI_LINE_ALL_0_31
  * @note   (*)Please check each device line mapping for EXTI Line availability
  */
__STATIC_INLINE void LL_EXTI_DisableEvent_0_31(uint32_t exti_line)
{
  STM32_ATOMIC_CLEAR_BIT_32(EXTI->EMR1, exti_line);
}

/**
  * @brief  Disable EXTI Line Event request for Lines in range 32 to 63.
  * @rmtoll
  *  EMR2         EMx           LL_EXTI_DisableEvent_32_63
  * @param exti_line This parameter can be a combination of the following values:
  *         @arg @ref LL_EXTI_LINE_32
  *         @arg @ref LL_EXTI_LINE_33
  *         @arg @ref LL_EXTI_LINE_34
  *         @arg @ref LL_EXTI_LINE_35
  *         @arg @ref LL_EXTI_LINE_36
  *         @arg @ref LL_EXTI_LINE_37
  *         @arg @ref LL_EXTI_LINE_38
  *         @arg @ref LL_EXTI_LINE_39
  *         @arg @ref LL_EXTI_LINE_40
  *         @arg @ref LL_EXTI_LINE_41
  *         @arg @ref LL_EXTI_LINE_42
  *         @arg @ref LL_EXTI_LINE_43
  *         @arg @ref LL_EXTI_LINE_44
  *         @arg @ref LL_EXTI_LINE_45
  *         @arg @ref LL_EXTI_LINE_46
  *         @arg @ref LL_EXTI_LINE_47
  *         @arg @ref LL_EXTI_LINE_48
  *         @arg @ref LL_EXTI_LINE_49
  *         @arg @ref LL_EXTI_LINE_50
  *         @arg @ref LL_EXTI_LINE_51
  *         @arg @ref LL_EXTI_LINE_52
  *         @arg @ref LL_EXTI_LINE_53
  *         @arg @ref LL_EXTI_LINE_55
  *         @arg @ref LL_EXTI_LINE_56
  *         @arg @ref LL_EXTI_LINE_57
  *         @arg @ref LL_EXTI_LINE_58
  *         @arg @ref LL_EXTI_LINE_59
  *         @arg @ref LL_EXTI_LINE_60
  *         @arg @ref LL_EXTI_LINE_61
  *         @arg @ref LL_EXTI_LINE_62
  *         @arg @ref LL_EXTI_LINE_63
  *         @arg @ref LL_EXTI_LINE_ALL_32_63
  * @note   (*)Please check each device line mapping for EXTI Line availability
  */
__STATIC_INLINE void LL_EXTI_DisableEvent_32_63(uint32_t exti_line)
{
  STM32_ATOMIC_CLEAR_BIT_32(EXTI->EMR2, exti_line);
}

/**
  * @brief  Disable EXTI Line Event request for Lines in range 64 to 95.
  * @rmtoll
  *  EMR3         EMx           LL_EXTI_DisableEvent_64_95
  * @param exti_line This parameter can be a combination of the following values:
  *         @arg @ref LL_EXTI_LINE_64
  *         @arg @ref LL_EXTI_LINE_65
  *         @arg @ref LL_EXTI_LINE_66
  *         @arg @ref LL_EXTI_LINE_67
  *         @arg @ref LL_EXTI_LINE_68
  *         @arg @ref LL_EXTI_LINE_69
  *         @arg @ref LL_EXTI_LINE_70
  *         @arg @ref LL_EXTI_LINE_71
  *         @arg @ref LL_EXTI_LINE_77
  *         @arg @ref LL_EXTI_LINE_ALL_64_95
  * @note (*)Please check each device line mapping for EXTI Line availability.
  */
__STATIC_INLINE void LL_EXTI_DisableEvent_64_95(uint32_t exti_line)
{
  STM32_ATOMIC_CLEAR_BIT_32(EXTI->EMR3, exti_line);
}

/**
  * @brief  Indicate if EXTI Line Event request is enabled for Lines in range 0 to 31.
  * @rmtoll
  *  EMR1         EMx           LL_EXTI_IsEnabledEvent_0_31
  * @param exti_line This parameter can be one of the following values:
  *         @arg @ref LL_EXTI_LINE_0
  *         @arg @ref LL_EXTI_LINE_1
  *         @arg @ref LL_EXTI_LINE_2
  *         @arg @ref LL_EXTI_LINE_3
  *         @arg @ref LL_EXTI_LINE_4
  *         @arg @ref LL_EXTI_LINE_5
  *         @arg @ref LL_EXTI_LINE_6
  *         @arg @ref LL_EXTI_LINE_7
  *         @arg @ref LL_EXTI_LINE_8
  *         @arg @ref LL_EXTI_LINE_9
  *         @arg @ref LL_EXTI_LINE_10
  *         @arg @ref LL_EXTI_LINE_11
  *         @arg @ref LL_EXTI_LINE_12
  *         @arg @ref LL_EXTI_LINE_13
  *         @arg @ref LL_EXTI_LINE_14
  *         @arg @ref LL_EXTI_LINE_15
  *         @arg @ref LL_EXTI_LINE_16
  *         @arg @ref LL_EXTI_LINE_17
  *         @arg @ref LL_EXTI_LINE_18
  *         @arg @ref LL_EXTI_LINE_19
  *         @arg @ref LL_EXTI_LINE_20
  *         @arg @ref LL_EXTI_LINE_21
  *         @arg @ref LL_EXTI_LINE_22
  *         @arg @ref LL_EXTI_LINE_23
  *         @arg @ref LL_EXTI_LINE_24
  *         @arg @ref LL_EXTI_LINE_25
  *         @arg @ref LL_EXTI_LINE_26
  *         @arg @ref LL_EXTI_LINE_27
  *         @arg @ref LL_EXTI_LINE_28
  *         @arg @ref LL_EXTI_LINE_29
  *         @arg @ref LL_EXTI_LINE_30
  *         @arg @ref LL_EXTI_LINE_31
  * @note   (*)Please check each device line mapping for EXTI Line availability
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_EXTI_IsEnabledEvent_0_31(uint32_t exti_line)
{
  return ((STM32_READ_BIT(EXTI->EMR1, exti_line) == (exti_line)) ? 1UL : 0UL);
}

/**
  * @brief  Indicate if EXTI Line Event request is enabled for Lines in range 32 to 63.
  * @rmtoll
  *  EMR2         EMx           LL_EXTI_IsEnabledEvent_32_63
  * @param exti_line This parameter can be a combination of the following values:
  *         @arg @ref LL_EXTI_LINE_32
  *         @arg @ref LL_EXTI_LINE_33
  *         @arg @ref LL_EXTI_LINE_34
  *         @arg @ref LL_EXTI_LINE_35
  *         @arg @ref LL_EXTI_LINE_36
  *         @arg @ref LL_EXTI_LINE_37
  *         @arg @ref LL_EXTI_LINE_38
  *         @arg @ref LL_EXTI_LINE_39
  *         @arg @ref LL_EXTI_LINE_40
  *         @arg @ref LL_EXTI_LINE_41
  *         @arg @ref LL_EXTI_LINE_42
  *         @arg @ref LL_EXTI_LINE_43
  *         @arg @ref LL_EXTI_LINE_44
  *         @arg @ref LL_EXTI_LINE_45
  *         @arg @ref LL_EXTI_LINE_46
  *         @arg @ref LL_EXTI_LINE_47
  *         @arg @ref LL_EXTI_LINE_48
  *         @arg @ref LL_EXTI_LINE_49
  *         @arg @ref LL_EXTI_LINE_50
  *         @arg @ref LL_EXTI_LINE_51
  *         @arg @ref LL_EXTI_LINE_52
  *         @arg @ref LL_EXTI_LINE_53
  *         @arg @ref LL_EXTI_LINE_55
  *         @arg @ref LL_EXTI_LINE_56
  *         @arg @ref LL_EXTI_LINE_57
  *         @arg @ref LL_EXTI_LINE_58
  *         @arg @ref LL_EXTI_LINE_59
  *         @arg @ref LL_EXTI_LINE_60
  *         @arg @ref LL_EXTI_LINE_61
  *         @arg @ref LL_EXTI_LINE_62
  *         @arg @ref LL_EXTI_LINE_63
  * @note   (*)Please check each device line mapping for EXTI Line availability
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_EXTI_IsEnabledEvent_32_63(uint32_t exti_line)
{
  return ((STM32_READ_BIT(EXTI->EMR2, exti_line) == (exti_line)) ? 1U : 0U);
}

/**
  * @brief  Indicate if EXTI Line Event request is enabled for Lines in range 64 to 95.
  * @rmtoll
  *  EMR3         EMx           LL_EXTI_IsEnabledEvent_64_95
  * @param exti_line This parameter can be a combination of the following values:
  *         @arg @ref LL_EXTI_LINE_64
  *         @arg @ref LL_EXTI_LINE_65
  *         @arg @ref LL_EXTI_LINE_66
  *         @arg @ref LL_EXTI_LINE_67
  *         @arg @ref LL_EXTI_LINE_68
  *         @arg @ref LL_EXTI_LINE_69
  *         @arg @ref LL_EXTI_LINE_70
  *         @arg @ref LL_EXTI_LINE_71
  *         @arg @ref LL_EXTI_LINE_77
  * @note (*)Please check each device line mapping for EXTI Line availability.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_EXTI_IsEnabledEvent_64_95(uint32_t exti_line)
{
  return ((STM32_READ_BIT(EXTI->EMR3, exti_line) == (exti_line)) ? 1U : 0U);
}

/**
  * @}
  */

/** @defgroup EXTI_LL_EF_Rising_Trigger_Management Rising_Trigger_Management
  * @{
  */

/**
  * @brief  Enable EXTI Line Rising Edge Trigger for Lines in range 0 to 31.
  * @rmtoll
  *  RTSR1        RTx           LL_EXTI_EnableRisingTrig_0_31
  * @param exti_line This parameter can be a combination of the following values:
  *         @arg @ref LL_EXTI_LINE_0
  *         @arg @ref LL_EXTI_LINE_1
  *         @arg @ref LL_EXTI_LINE_2
  *         @arg @ref LL_EXTI_LINE_3
  *         @arg @ref LL_EXTI_LINE_4
  *         @arg @ref LL_EXTI_LINE_5
  *         @arg @ref LL_EXTI_LINE_6
  *         @arg @ref LL_EXTI_LINE_7
  *         @arg @ref LL_EXTI_LINE_8
  *         @arg @ref LL_EXTI_LINE_9
  *         @arg @ref LL_EXTI_LINE_10
  *         @arg @ref LL_EXTI_LINE_11
  *         @arg @ref LL_EXTI_LINE_12
  *         @arg @ref LL_EXTI_LINE_13
  *         @arg @ref LL_EXTI_LINE_14
  *         @arg @ref LL_EXTI_LINE_15
  *         @arg @ref LL_EXTI_LINE_16
  *         @arg @ref LL_EXTI_LINE_20
  *         @arg @ref LL_EXTI_LINE_21
  * @note The configurable wakeup lines are edge-triggered. No glitch must be generated on these lines.
  *         If a rising edge on a configurable interrupt
  *         line occurs during a write operation in the EXTI_RTSR register, the
  *         pending bit is not set.
  *         Rising and falling edge triggers can be set for
  *         the same interrupt line. In this case, both generate a trigger
  *         condition.
  * @note (*)Please check each device line mapping for EXTI Line availability.
  */
__STATIC_INLINE void LL_EXTI_EnableRisingTrig_0_31(uint32_t exti_line)
{
  STM32_ATOMIC_SET_BIT_32(EXTI->RTSR1, exti_line);
}

/**
  * @brief  Enable EXTI Line Rising Edge Trigger for Lines in range 32 to 63.
  * @rmtoll
  *  RTSR2        RTx           LL_EXTI_EnableRisingTrig_32_63
  * @param exti_line This parameter can be a combination of the following values:
  *         @arg @ref LL_EXTI_LINE_34
  *         @arg @ref LL_EXTI_LINE_46
  *         @arg @ref LL_EXTI_LINE_49
  *         @arg @ref LL_EXTI_LINE_51
  *         @arg @ref LL_EXTI_LINE_60
  *         @arg @ref LL_EXTI_LINE_61
  *         @arg @ref LL_EXTI_LINE_62
  *         @arg @ref LL_EXTI_LINE_63
  * @note The configurable wakeup lines are edge-triggered. No glitch must be generated on these lines.
  *         If a rising edge on a configurable interrupt
  *         line occurs during a write operation in the EXTI_RTSR register, the
  *         pending bit is not set.
  *         Rising and falling edge triggers can be set for
  *         the same interrupt line. In this case, both generate a trigger
  *         condition.
  * @note (*)Please check each device line mapping for EXTI Line availability.
  */
__STATIC_INLINE void LL_EXTI_EnableRisingTrig_32_63(uint32_t exti_line)
{
  STM32_ATOMIC_SET_BIT_32(EXTI->RTSR2, exti_line);
}

/**
  * @brief  Enable EXTI Line Rising Edge Trigger for Lines in range 64 to 95.
  * @rmtoll
  *  RTSR3        RTx           LL_EXTI_EnableRisingTrig_64_95
  * @param exti_line This parameter can be a combination of the following values:
  *         @arg @ref LL_EXTI_LINE_68
  *         @arg @ref LL_EXTI_LINE_69
  *         @arg @ref LL_EXTI_LINE_70
  *         @arg @ref LL_EXTI_LINE_71
  * @note The configurable wakeup lines are edge-triggered. No glitch must be generated on these lines.
  *         If a rising edge on a configurable interrupt
  *         line occurs during a write operation in the EXTI_RTSR register, the
  *         pending bit is not set.
  *         Rising and falling edge triggers can be set for
  *         the same interrupt line. In this case, both generate a trigger
  *         condition.
  * @note (*)Please check each device line mapping for EXTI Line availability.
  */
__STATIC_INLINE void LL_EXTI_EnableRisingTrig_64_95(uint32_t exti_line)
{
  STM32_ATOMIC_SET_BIT_32(EXTI->RTSR3, exti_line);
}

/**
  * @brief  Disable EXTI Line Rising Edge Trigger for Lines in range 0 to 31.
  * @rmtoll
  *  RTSR1        RTx           LL_EXTI_DisableRisingTrig_0_31
  * @param exti_line This parameter can be a combination of the following values:
  *         @arg @ref LL_EXTI_LINE_0
  *         @arg @ref LL_EXTI_LINE_1
  *         @arg @ref LL_EXTI_LINE_2
  *         @arg @ref LL_EXTI_LINE_3
  *         @arg @ref LL_EXTI_LINE_4
  *         @arg @ref LL_EXTI_LINE_5
  *         @arg @ref LL_EXTI_LINE_6
  *         @arg @ref LL_EXTI_LINE_7
  *         @arg @ref LL_EXTI_LINE_8
  *         @arg @ref LL_EXTI_LINE_9
  *         @arg @ref LL_EXTI_LINE_10
  *         @arg @ref LL_EXTI_LINE_11
  *         @arg @ref LL_EXTI_LINE_12
  *         @arg @ref LL_EXTI_LINE_13
  *         @arg @ref LL_EXTI_LINE_14
  *         @arg @ref LL_EXTI_LINE_15
  *         @arg @ref LL_EXTI_LINE_16
  *         @arg @ref LL_EXTI_LINE_20
  *         @arg @ref LL_EXTI_LINE_21
  * @note The configurable wakeup lines are edge-triggered. No glitch must be generated on these lines.
  *         If a rising edge on a configurable interrupt
  *         line occurs during a write operation in the EXTI_RTSR register, the
  *         pending bit is not set.
  *         Rising and falling edge triggers can be set for
  *         the same interrupt line. In this case, both generate a trigger
  *         condition.
  * @note (*)Please check each device line mapping for EXTI Line availability.
  */
__STATIC_INLINE void LL_EXTI_DisableRisingTrig_0_31(uint32_t exti_line)
{
  STM32_ATOMIC_CLEAR_BIT_32(EXTI->RTSR1, exti_line);
}

/**
  * @brief  Disable EXTI Line Rising Edge Trigger for Lines in range 32 to 63.
  * @rmtoll
  *  RTSR2        RTx           LL_EXTI_DisableRisingTrig_32_63
  * @param exti_line This parameter can be a combination of the following values:
  *         @arg @ref LL_EXTI_LINE_34
  *         @arg @ref LL_EXTI_LINE_46
  *         @arg @ref LL_EXTI_LINE_49
  *         @arg @ref LL_EXTI_LINE_51
  *         @arg @ref LL_EXTI_LINE_60
  *         @arg @ref LL_EXTI_LINE_61
  *         @arg @ref LL_EXTI_LINE_62
  *         @arg @ref LL_EXTI_LINE_63
  * @note The configurable wakeup lines are edge-triggered. No glitch must be generated on these lines.
  *         If a rising edge on a configurable interrupt
  *         line occurs during a write operation in the EXTI_RTSR register, the
  *         pending bit is not set.
  *         Rising and falling edge triggers can be set for
  *         the same interrupt line. In this case, both generate a trigger
  *         condition.
  * @note (*)Please check each device line mapping for EXTI Line availability.
  */
__STATIC_INLINE void LL_EXTI_DisableRisingTrig_32_63(uint32_t exti_line)
{
  STM32_ATOMIC_CLEAR_BIT_32(EXTI->RTSR2, exti_line);
}

/**
  * @brief  Disable EXTI Line Rising Edge Trigger for Lines in range 64 to 95.
  * @rmtoll
  *  RTSR3        RTx           LL_EXTI_DisableRisingTrig_64_95
  * @param exti_line This parameter can be a combination of the following values:
  *         @arg @ref LL_EXTI_LINE_68
  *         @arg @ref LL_EXTI_LINE_69
  *         @arg @ref LL_EXTI_LINE_70
  *         @arg @ref LL_EXTI_LINE_71
  * @note The configurable wakeup lines are edge-triggered. No glitch must be generated on these lines.
  *         If a rising edge on a configurable interrupt
  *         line occurs during a write operation in the EXTI_RTSR register, the
  *         pending bit is not set.
  *         Rising and falling edge triggers can be set for
  *         the same interrupt line. In this case, both generate a trigger
  *         condition.
  * @note (*)Please check each device line mapping for EXTI Line availability.
  */
__STATIC_INLINE void LL_EXTI_DisableRisingTrig_64_95(uint32_t exti_line)
{
  STM32_ATOMIC_CLEAR_BIT_32(EXTI->RTSR3, exti_line);
}

/**
  * @brief  Check if rising edge trigger is enabled for Lines in range 0 to 31.
  * @rmtoll
  *  RTSR1        RTx           LL_EXTI_IsEnabledRisingTrig_0_31
  * @param exti_line This parameter can be a combination of the following values:
  *         @arg @ref LL_EXTI_LINE_0
  *         @arg @ref LL_EXTI_LINE_1
  *         @arg @ref LL_EXTI_LINE_2
  *         @arg @ref LL_EXTI_LINE_3
  *         @arg @ref LL_EXTI_LINE_4
  *         @arg @ref LL_EXTI_LINE_5
  *         @arg @ref LL_EXTI_LINE_6
  *         @arg @ref LL_EXTI_LINE_7
  *         @arg @ref LL_EXTI_LINE_8
  *         @arg @ref LL_EXTI_LINE_9
  *         @arg @ref LL_EXTI_LINE_10
  *         @arg @ref LL_EXTI_LINE_11
  *         @arg @ref LL_EXTI_LINE_12
  *         @arg @ref LL_EXTI_LINE_13
  *         @arg @ref LL_EXTI_LINE_14
  *         @arg @ref LL_EXTI_LINE_15
  *         @arg @ref LL_EXTI_LINE_16
  *         @arg @ref LL_EXTI_LINE_20
  *         @arg @ref LL_EXTI_LINE_21
  * @note (*)Please check each device line mapping for EXTI Line availability.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_EXTI_IsEnabledRisingTrig_0_31(uint32_t exti_line)
{
  return ((STM32_READ_BIT(EXTI->RTSR1, exti_line) == (exti_line)) ? 1UL : 0UL);
}

/**
  * @brief  Check if rising edge trigger is enabled for Lines in range 32 to 63.
  * @rmtoll
  *  RTSR2        RTx           LL_EXTI_IsEnabledRisingTrig_32_63
  * @param exti_line This parameter can be a combination of the following values:
  *         @arg @ref LL_EXTI_LINE_34
  *         @arg @ref LL_EXTI_LINE_46
  *         @arg @ref LL_EXTI_LINE_49
  *         @arg @ref LL_EXTI_LINE_51
  *         @arg @ref LL_EXTI_LINE_60
  *         @arg @ref LL_EXTI_LINE_61
  *         @arg @ref LL_EXTI_LINE_62
  *         @arg @ref LL_EXTI_LINE_63
  * @note (*)Please check each device line mapping for EXTI Line availability.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_EXTI_IsEnabledRisingTrig_32_63(uint32_t exti_line)
{
  return ((STM32_READ_BIT(EXTI->RTSR2, exti_line) == (exti_line)) ? 1U : 0U);
}

/**
  * @brief  Check if rising edge trigger is enabled for Lines in range 64 to 95.
  * @rmtoll
  *  RTSR3        RTx           LL_EXTI_IsEnabledRisingTrig_64_95
  * @param exti_line This parameter can be a combination of the following values:
  *         @arg @ref LL_EXTI_LINE_68
  *         @arg @ref LL_EXTI_LINE_69
  *         @arg @ref LL_EXTI_LINE_70
  *         @arg @ref LL_EXTI_LINE_71
  * @note (*)Please check each device line mapping for EXTI Line availability.
  */
__STATIC_INLINE uint32_t LL_EXTI_IsEnabledRisingTrig_64_95(uint32_t exti_line)
{
  return ((STM32_READ_BIT(EXTI->RTSR3, exti_line) == (exti_line)) ? 1U : 0U);
}

/**
  * @}
  */

/** @defgroup EXTI_LL_EF_Falling_Trigger_Management Falling_Trigger_Management
  * @{
  */

/**
  * @brief  Enable EXTI Line Falling Edge Trigger for Lines in range 0 to 31.
  * @rmtoll
  *  FTSR1        FTx           LL_EXTI_EnableFallingTrig_0_31
  * @param exti_line This parameter can be a combination of the following values:
  *         @arg @ref LL_EXTI_LINE_0
  *         @arg @ref LL_EXTI_LINE_1
  *         @arg @ref LL_EXTI_LINE_2
  *         @arg @ref LL_EXTI_LINE_3
  *         @arg @ref LL_EXTI_LINE_4
  *         @arg @ref LL_EXTI_LINE_5
  *         @arg @ref LL_EXTI_LINE_6
  *         @arg @ref LL_EXTI_LINE_7
  *         @arg @ref LL_EXTI_LINE_8
  *         @arg @ref LL_EXTI_LINE_9
  *         @arg @ref LL_EXTI_LINE_10
  *         @arg @ref LL_EXTI_LINE_11
  *         @arg @ref LL_EXTI_LINE_12
  *         @arg @ref LL_EXTI_LINE_13
  *         @arg @ref LL_EXTI_LINE_14
  *         @arg @ref LL_EXTI_LINE_15
  *         @arg @ref LL_EXTI_LINE_16
  *         @arg @ref LL_EXTI_LINE_20
  *         @arg @ref LL_EXTI_LINE_21
  * @note The configurable wakeup lines are edge-triggered. No glitch must be generated on these lines.
  *         If a falling edge on a configurable interrupt
  *         line occurs during a write operation in the EXTI_FTSR register, the
  *         pending bit is not set.
  *         Rising and falling edge triggers can be set for
  *         the same interrupt line. In this case, both generate a trigger
  *         condition.
  * @note (*)Please check each device line mapping for EXTI Line availability.
  */
__STATIC_INLINE void LL_EXTI_EnableFallingTrig_0_31(uint32_t exti_line)
{
  STM32_ATOMIC_SET_BIT_32(EXTI->FTSR1, exti_line);
}

/**
  * @brief  Enable EXTI Line Falling Edge Trigger for Lines in range 32 to 63.
  * @rmtoll
  *  FTSR2        FTx           LL_EXTI_EnableFallingTrig_32_63
  * @param exti_line This parameter can be a combination of the following values:
  *         @arg @ref LL_EXTI_LINE_34
  *         @arg @ref LL_EXTI_LINE_46
  *         @arg @ref LL_EXTI_LINE_49
  *         @arg @ref LL_EXTI_LINE_51
  *         @arg @ref LL_EXTI_LINE_60
  *         @arg @ref LL_EXTI_LINE_61
  *         @arg @ref LL_EXTI_LINE_62
  *         @arg @ref LL_EXTI_LINE_63
  * @note The configurable wakeup lines are edge-triggered. No glitch must be generated on these lines.
  *         If a falling edge on a configurable interrupt
  *         line occurs during a write operation in the EXTI_FTSR register, the
  *         pending bit is not set.
  *         Rising and falling edge triggers can be set for
  *         the same interrupt line. In this case, both generate a trigger
  *         condition.
  * @note (*)Please check each device line mapping for EXTI Line availability.
  */
__STATIC_INLINE void LL_EXTI_EnableFallingTrig_32_63(uint32_t exti_line)
{
  STM32_ATOMIC_SET_BIT_32(EXTI->FTSR2, exti_line);
}

/**
  * @brief  Enable EXTI Line Falling Edge Trigger for Lines in range 64 to 95.
  * @rmtoll
  *  FTSR3        FTx           LL_EXTI_EnableFallingTrig_64_95
  * @param exti_line This parameter can be a combination of the following values:
  *         @arg @ref LL_EXTI_LINE_68
  *         @arg @ref LL_EXTI_LINE_69
  *         @arg @ref LL_EXTI_LINE_70
  *         @arg @ref LL_EXTI_LINE_71
  * @note The configurable wakeup lines are edge-triggered. No glitch must be generated on these lines.
  *         If a falling edge on a configurable interrupt
  *         line occurs during a write operation in the EXTI_FTSR register, the
  *         pending bit is not set.
  *         Rising and falling edge triggers can be set for
  *         the same interrupt line. In this case, both generate a trigger
  *         condition.
  * @note (*)Please check each device line mapping for EXTI Line availability.
  */
__STATIC_INLINE void LL_EXTI_EnableFallingTrig_64_95(uint32_t exti_line)
{
  STM32_ATOMIC_SET_BIT_32(EXTI->FTSR3, exti_line);
}

/**
  * @brief  Disable EXTI Line Falling Edge Trigger for Lines in range 0 to 31.
  * @rmtoll
  *  FTSR1        FTx           LL_EXTI_DisableFallingTrig_0_31
  * @param exti_line This parameter can be a combination of the following values:
  *         @arg @ref LL_EXTI_LINE_0
  *         @arg @ref LL_EXTI_LINE_1
  *         @arg @ref LL_EXTI_LINE_2
  *         @arg @ref LL_EXTI_LINE_3
  *         @arg @ref LL_EXTI_LINE_4
  *         @arg @ref LL_EXTI_LINE_5
  *         @arg @ref LL_EXTI_LINE_6
  *         @arg @ref LL_EXTI_LINE_7
  *         @arg @ref LL_EXTI_LINE_8
  *         @arg @ref LL_EXTI_LINE_9
  *         @arg @ref LL_EXTI_LINE_10
  *         @arg @ref LL_EXTI_LINE_11
  *         @arg @ref LL_EXTI_LINE_12
  *         @arg @ref LL_EXTI_LINE_13
  *         @arg @ref LL_EXTI_LINE_14
  *         @arg @ref LL_EXTI_LINE_15
  *         @arg @ref LL_EXTI_LINE_16
  *         @arg @ref LL_EXTI_LINE_20
  *         @arg @ref LL_EXTI_LINE_21
  * @note The configurable wakeup lines are edge-triggered. No glitch must be generated on these lines.
  *         If a falling edge on a configurable interrupt
  *         line occurs during a write operation in the EXTI_FTSR register, the
  *         pending bit is not set.
  *         Rising and falling edge triggers can be set for
  *         the same interrupt line. In this case, both generate a trigger
  *         condition.
  * @note (*)Please check each device line mapping for EXTI Line availability.
  */
__STATIC_INLINE void LL_EXTI_DisableFallingTrig_0_31(uint32_t exti_line)
{
  STM32_ATOMIC_CLEAR_BIT_32(EXTI->FTSR1, exti_line);
}

/**
  * @brief  Disable EXTI Line Falling Edge Trigger for Lines in range 32 to 63.
  * @rmtoll
  *  FTSR2        FTx           LL_EXTI_DisableFallingTrig_32_63
  * @param exti_line This parameter can be a combination of the following values:
  *         @arg @ref LL_EXTI_LINE_34
  *         @arg @ref LL_EXTI_LINE_46
  *         @arg @ref LL_EXTI_LINE_49
  *         @arg @ref LL_EXTI_LINE_51
  *         @arg @ref LL_EXTI_LINE_60
  *         @arg @ref LL_EXTI_LINE_61
  *         @arg @ref LL_EXTI_LINE_62
  *         @arg @ref LL_EXTI_LINE_63
  * @note The configurable wakeup lines are edge-triggered. No glitch must be generated on these lines.
  *         If a falling edge on a configurable interrupt
  *         line occurs during a write operation in the EXTI_FTSR register, the
  *         pending bit is not set.
  *         Rising and falling edge triggers can be set for
  *         the same interrupt line. In this case, both generate a trigger
  *         condition.
  * @note (*)Please check each device line mapping for EXTI Line availability.
  */
__STATIC_INLINE void LL_EXTI_DisableFallingTrig_32_63(uint32_t exti_line)
{
  STM32_ATOMIC_CLEAR_BIT_32(EXTI->FTSR2, exti_line);
}

/**
  * @brief  Disable EXTI Line Falling Edge Trigger for Lines in range 64 to 95.
  * @rmtoll
  *  FTSR3        FTx           LL_EXTI_DisableFallingTrig_64_95
  * @param exti_line This parameter can be a combination of the following values:
  *         @arg @ref LL_EXTI_LINE_68
  *         @arg @ref LL_EXTI_LINE_69
  *         @arg @ref LL_EXTI_LINE_70
  *         @arg @ref LL_EXTI_LINE_71
  * @note The configurable wakeup lines are edge-triggered. No glitch must be generated on these lines.
  *         If a falling edge on a configurable interrupt
  *         line occurs during a write operation in the EXTI_FTSR register, the
  *         pending bit is not set.
  *         Rising and falling edge triggers can be set for
  *         the same interrupt line. In this case, both generate a trigger
  *         condition.
  * @note (*)Please check each device line mapping for EXTI Line availability.
  */
__STATIC_INLINE void LL_EXTI_DisableFallingTrig_64_95(uint32_t exti_line)
{
  STM32_ATOMIC_CLEAR_BIT_32(EXTI->FTSR3, exti_line);
}

/**
  * @brief  Check if falling edge trigger is enabled for Lines in range 0 to 31.
  * @rmtoll
  *  FTSR1        FTx           LL_EXTI_IsEnabledFallingTrig_0_31
  * @param exti_line This parameter can be a combination of the following values:
  *         @arg @ref LL_EXTI_LINE_0
  *         @arg @ref LL_EXTI_LINE_1
  *         @arg @ref LL_EXTI_LINE_2
  *         @arg @ref LL_EXTI_LINE_3
  *         @arg @ref LL_EXTI_LINE_4
  *         @arg @ref LL_EXTI_LINE_5
  *         @arg @ref LL_EXTI_LINE_6
  *         @arg @ref LL_EXTI_LINE_7
  *         @arg @ref LL_EXTI_LINE_8
  *         @arg @ref LL_EXTI_LINE_9
  *         @arg @ref LL_EXTI_LINE_10
  *         @arg @ref LL_EXTI_LINE_11
  *         @arg @ref LL_EXTI_LINE_12
  *         @arg @ref LL_EXTI_LINE_13
  *         @arg @ref LL_EXTI_LINE_14
  *         @arg @ref LL_EXTI_LINE_15
  *         @arg @ref LL_EXTI_LINE_16
  *         @arg @ref LL_EXTI_LINE_20
  *         @arg @ref LL_EXTI_LINE_21
  * @note (*)Please check each device line mapping for EXTI Line availability.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_EXTI_IsEnabledFallingTrig_0_31(uint32_t exti_line)
{
  return ((STM32_READ_BIT(EXTI->FTSR1, exti_line) == (exti_line)) ? 1UL : 0UL);
}

/**
  * @brief  Check if falling edge trigger is enabled for Lines in range 32 to 63.
  * @rmtoll
  *  FTSR2        FTx           LL_EXTI_IsEnabledFallingTrig_32_63
  * @param exti_line This parameter can be a combination of the following values:
  *         @arg @ref LL_EXTI_LINE_34
  *         @arg @ref LL_EXTI_LINE_46
  *         @arg @ref LL_EXTI_LINE_49
  *         @arg @ref LL_EXTI_LINE_51
  *         @arg @ref LL_EXTI_LINE_60
  *         @arg @ref LL_EXTI_LINE_61
  *         @arg @ref LL_EXTI_LINE_62
  *         @arg @ref LL_EXTI_LINE_63
  * @note (*)Please check each device line mapping for EXTI Line availability.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_EXTI_IsEnabledFallingTrig_32_63(uint32_t exti_line)
{
  return ((STM32_READ_BIT(EXTI->FTSR2, exti_line) == (exti_line)) ? 1U : 0U);
}

/**
  * @brief  Check if falling edge trigger is enabled for Lines in range 64 to 95.
  * @rmtoll
  *  FTSR3        FTx           LL_EXTI_IsEnabledFallingTrig_64_95
  * @param exti_line This parameter can be a combination of the following values:
  *         @arg @ref LL_EXTI_LINE_68
  *         @arg @ref LL_EXTI_LINE_69
  *         @arg @ref LL_EXTI_LINE_70
  *         @arg @ref LL_EXTI_LINE_71
  * @note (*)Please check each device line mapping for EXTI Line availability.
  */
__STATIC_INLINE uint32_t LL_EXTI_IsEnabledFallingTrig_64_95(uint32_t exti_line)
{
  return ((STM32_READ_BIT(EXTI->FTSR3, exti_line) == (exti_line)) ? 1U : 0U);
}

/**
  * @}
  */

/** @defgroup EXTI_LL_EF_Software_Interrupt_Management Software_Interrupt_Management
  * @{
  */

/**
  * @brief  Generate a software Interrupt Event for Lines in range 0 to 31.
  * @rmtoll
  *  SWIER1       SWIx          LL_EXTI_GenerateSWI_0_31
  * @param exti_line This parameter can be a combination of the following values:
  *         @arg @ref LL_EXTI_LINE_0
  *         @arg @ref LL_EXTI_LINE_1
  *         @arg @ref LL_EXTI_LINE_2
  *         @arg @ref LL_EXTI_LINE_3
  *         @arg @ref LL_EXTI_LINE_4
  *         @arg @ref LL_EXTI_LINE_5
  *         @arg @ref LL_EXTI_LINE_6
  *         @arg @ref LL_EXTI_LINE_7
  *         @arg @ref LL_EXTI_LINE_8
  *         @arg @ref LL_EXTI_LINE_9
  *         @arg @ref LL_EXTI_LINE_10
  *         @arg @ref LL_EXTI_LINE_11
  *         @arg @ref LL_EXTI_LINE_12
  *         @arg @ref LL_EXTI_LINE_13
  *         @arg @ref LL_EXTI_LINE_14
  *         @arg @ref LL_EXTI_LINE_15
  *         @arg @ref LL_EXTI_LINE_16
  *         @arg @ref LL_EXTI_LINE_20
  *         @arg @ref LL_EXTI_LINE_21
  * @note If the interrupt is enabled on this line in the EXTI_IMR, writing a 1 to
  *         this bit sets the corresponding pending bit in EXTI_PR
  *         resulting in an interrupt request generation.
  *         This bit is auto cleared by hardware.
  * @note (*)Please check each device line mapping for EXTI Line availability.
  */
__STATIC_INLINE void LL_EXTI_GenerateSWI_0_31(uint32_t exti_line)
{
  STM32_WRITE_REG(EXTI->SWIER1, exti_line);
}

/**
  * @brief  Generate a software Interrupt Event for Lines in range 32 to 63.
  * @rmtoll
  *  SWIER2       SWIx          LL_EXTI_GenerateSWI_32_63
  * @param exti_line This parameter can be a combination of the following values:
  *         @arg @ref LL_EXTI_LINE_34
  *         @arg @ref LL_EXTI_LINE_46
  *         @arg @ref LL_EXTI_LINE_49
  *         @arg @ref LL_EXTI_LINE_51
  *         @arg @ref LL_EXTI_LINE_60
  *         @arg @ref LL_EXTI_LINE_61
  *         @arg @ref LL_EXTI_LINE_62
  *         @arg @ref LL_EXTI_LINE_63
  * @note If the interrupt is enabled on this line in the EXTI_IMR2, writing a 1 to
  *         this bit when it is at '0' sets the corresponding pending bit in EXTI_PR2
  *         resulting in an interrupt request generation.
  *         This bit is cleared by clearing the corresponding bit in the EXTI_PR2
  *         register (by writing a 1 into the bit)
  * @note (*)Please check each device line mapping for EXTI Line availability.
  */
__STATIC_INLINE void LL_EXTI_GenerateSWI_32_63(uint32_t exti_line)
{
  STM32_WRITE_REG(EXTI->SWIER2, exti_line);
}

/**
  * @brief  Generate a software Interrupt Event for Lines in range 64 to 95.
  * @rmtoll
  *  SWIER3       SWIx          LL_EXTI_GenerateSWI_64_95
  * @param exti_line This parameter can be a combination of the following values:
  *         @arg @ref LL_EXTI_LINE_68
  *         @arg @ref LL_EXTI_LINE_69
  *         @arg @ref LL_EXTI_LINE_70
  *         @arg @ref LL_EXTI_LINE_71
  * @note If the interrupt is enabled on this line in the EXTI_IMR3, writing a 1 to
  *         this bit when it is at '0' sets the corresponding pending bit in EXTI_PR3
  *         resulting in an interrupt request generation.
  *         This bit is cleared by clearing the corresponding bit in the EXTI_PR3
  *         register (by writing a 1 into the bit)
  * @note (*)Please check each device line mapping for EXTI Line availability.
  */
__STATIC_INLINE void LL_EXTI_GenerateSWI_64_95(uint32_t exti_line)
{
  STM32_WRITE_REG(EXTI->SWIER3, exti_line);
}

/**
  * @}
  */

/** @defgroup EXTI_LL_EF_Flag_Management Flag_Management
  * @{
  */

/**
  * @brief  Check if the EXTI Line Trigger Flag is set or not for Lines in range 0 to 31.
  * @rmtoll
  *  PR1          PRx           LL_EXTI_IsActiveTriggerFlag_0_31
  * @param exti_line This parameter can be a combination of the following values:
  *         @arg @ref LL_EXTI_LINE_0
  *         @arg @ref LL_EXTI_LINE_1
  *         @arg @ref LL_EXTI_LINE_2
  *         @arg @ref LL_EXTI_LINE_3
  *         @arg @ref LL_EXTI_LINE_4
  *         @arg @ref LL_EXTI_LINE_5
  *         @arg @ref LL_EXTI_LINE_6
  *         @arg @ref LL_EXTI_LINE_7
  *         @arg @ref LL_EXTI_LINE_8
  *         @arg @ref LL_EXTI_LINE_9
  *         @arg @ref LL_EXTI_LINE_10
  *         @arg @ref LL_EXTI_LINE_11
  *         @arg @ref LL_EXTI_LINE_12
  *         @arg @ref LL_EXTI_LINE_13
  *         @arg @ref LL_EXTI_LINE_14
  *         @arg @ref LL_EXTI_LINE_15
  *         @arg @ref LL_EXTI_LINE_16
  *         @arg @ref LL_EXTI_LINE_20
  *         @arg @ref LL_EXTI_LINE_21
  * @note This bit is set when the Trigger edge event arrives on the interrupt
  *         line. This bit is cleared by writing a 1 to the bit.
  * @note (*)Please check each device line mapping for EXTI Line availability.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_EXTI_IsActiveTriggerFlag_0_31(uint32_t exti_line)
{
  return ((STM32_READ_BIT(EXTI->PR1, exti_line) == (exti_line)) ? 1UL : 0UL);
}

/**
  * @brief  Check if the EXTI Line Trigger Flag is set or not for Lines in range 32 to 63.
  * @rmtoll
  *  PR2          PRx           LL_EXTI_IsActiveTriggerFlag_32_63
  * @param exti_line This parameter can be a combination of the following values:
  *         @arg @ref LL_EXTI_LINE_34
  *         @arg @ref LL_EXTI_LINE_46
  *         @arg @ref LL_EXTI_LINE_49
  *         @arg @ref LL_EXTI_LINE_51
  *         @arg @ref LL_EXTI_LINE_60
  *         @arg @ref LL_EXTI_LINE_61
  *         @arg @ref LL_EXTI_LINE_62
  *         @arg @ref LL_EXTI_LINE_63
  * @note This bit is set when the Trigger edge event arrives on the interrupt
  *         line. This bit is cleared by writing a 1 to the bit.
  * @note (*)Please check each device line mapping for EXTI Line availability.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_EXTI_IsActiveTriggerFlag_32_63(uint32_t exti_line)
{
  return ((STM32_READ_BIT(EXTI->PR2, exti_line) == (exti_line)) ? 1UL : 0UL);
}

/**
  * @brief  Check if the EXTI Line Trigger Flag is set or not for Lines in range 64 to 95.
  * @rmtoll
  *  PR3          PRx           LL_EXTI_IsActiveTriggerFlag_64_95
  * @param exti_line This parameter can be a combination of the following values:
  *         @arg @ref LL_EXTI_LINE_68
  *         @arg @ref LL_EXTI_LINE_69
  *         @arg @ref LL_EXTI_LINE_70
  *         @arg @ref LL_EXTI_LINE_71
  * @note This bit is set when the Trigger edge event arrives on the interrupt
  *         line. This bit is cleared by writing a 1 to the bit.
  * @note (*)Please check each device line mapping for EXTI Line availability.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_EXTI_IsActiveTriggerFlag_64_95(uint32_t exti_line)
{
  return ((STM32_READ_BIT(EXTI->PR3, exti_line) == (exti_line)) ? 1UL : 0UL);
}

/**
  * @brief  Read EXTI Line Combination Trigger Flag for Lines in range 0 to 31.
  * @rmtoll
  *  PR1          PRx           LL_EXTI_ReadTriggerFlag_0_31
  * @param exti_line This parameter can be a combination of the following values:
  *         @arg @ref LL_EXTI_LINE_0
  *         @arg @ref LL_EXTI_LINE_1
  *         @arg @ref LL_EXTI_LINE_2
  *         @arg @ref LL_EXTI_LINE_3
  *         @arg @ref LL_EXTI_LINE_4
  *         @arg @ref LL_EXTI_LINE_5
  *         @arg @ref LL_EXTI_LINE_6
  *         @arg @ref LL_EXTI_LINE_7
  *         @arg @ref LL_EXTI_LINE_8
  *         @arg @ref LL_EXTI_LINE_9
  *         @arg @ref LL_EXTI_LINE_10
  *         @arg @ref LL_EXTI_LINE_11
  *         @arg @ref LL_EXTI_LINE_12
  *         @arg @ref LL_EXTI_LINE_13
  *         @arg @ref LL_EXTI_LINE_14
  *         @arg @ref LL_EXTI_LINE_15
  *         @arg @ref LL_EXTI_LINE_16
  *         @arg @ref LL_EXTI_LINE_20
  *         @arg @ref LL_EXTI_LINE_21
  * @note This bit is set when the Trigger edge event arrives on the interrupt
  *         line. This bit is cleared by writing a 1 to the bit.
  * @note (*)Please check each device line mapping for EXTI Line availability.
  * @note This bit is set when the selected edge event arrives on the interrupt.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_EXTI_ReadTriggerFlag_0_31(uint32_t exti_line)
{
  return (uint32_t)(STM32_READ_BIT(EXTI->PR1, exti_line));
}

/**
  * @brief  Read ExtLine Combination Falling Flag for Lines in range 32 to 63.
  * @rmtoll
  *  PR2          PRx           LL_EXTI_ReadTriggerFlag_32_63
  * @param exti_line This parameter can be a combination of the following values:
  *         @arg @ref LL_EXTI_LINE_34
  *         @arg @ref LL_EXTI_LINE_46
  *         @arg @ref LL_EXTI_LINE_49
  *         @arg @ref LL_EXTI_LINE_51
  *         @arg @ref LL_EXTI_LINE_60
  *         @arg @ref LL_EXTI_LINE_61
  *         @arg @ref LL_EXTI_LINE_62
  *         @arg @ref LL_EXTI_LINE_63
  * @note This bit is set when the falling edge event arrives on the interrupt
  *         line. This bit is cleared by writing a 1 to the bit.
  * @note (*)Please check each device line mapping for EXTI Line availability.
  * @note This bit is set when the selected edge event arrives on the interrupt.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_EXTI_ReadTriggerFlag_32_63(uint32_t exti_line)
{
  return (uint32_t)(STM32_READ_BIT(EXTI->PR2, exti_line));
}

/**
  * @brief  Read ExtLine Combination Falling Flag for Lines in range 64 to 95.
  * @rmtoll
  *  PR3          PRx           LL_EXTI_ReadTriggerFlag_64_95
  * @param exti_line This parameter can be a combination of the following values:
  *         @arg @ref LL_EXTI_LINE_68
  *         @arg @ref LL_EXTI_LINE_69
  *         @arg @ref LL_EXTI_LINE_70
  *         @arg @ref LL_EXTI_LINE_71
  * @note This bit is set when the falling edge event arrives on the interrupt
  *         line. This bit is cleared by writing a 1 to the bit.
  * @note (*)Please check each device line mapping for EXTI Line availability.
  * @note This bit is set when the selected edge event arrives on the interrupt.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_EXTI_ReadTriggerFlag_64_95(uint32_t exti_line)
{
  return (uint32_t)(STM32_READ_BIT(EXTI->PR3, exti_line));
}

/**
  * @brief  Clear EXTI Line Trigger Flags for Lines in range 0 to 31.
  * @rmtoll
  *  PR1          PRx           LL_EXTI_ClearTriggerFlag_0_31
  * @param exti_line This parameter can be a combination of the following values:
  *         @arg @ref LL_EXTI_LINE_0
  *         @arg @ref LL_EXTI_LINE_1
  *         @arg @ref LL_EXTI_LINE_2
  *         @arg @ref LL_EXTI_LINE_3
  *         @arg @ref LL_EXTI_LINE_4
  *         @arg @ref LL_EXTI_LINE_5
  *         @arg @ref LL_EXTI_LINE_6
  *         @arg @ref LL_EXTI_LINE_7
  *         @arg @ref LL_EXTI_LINE_8
  *         @arg @ref LL_EXTI_LINE_9
  *         @arg @ref LL_EXTI_LINE_10
  *         @arg @ref LL_EXTI_LINE_11
  *         @arg @ref LL_EXTI_LINE_12
  *         @arg @ref LL_EXTI_LINE_13
  *         @arg @ref LL_EXTI_LINE_14
  *         @arg @ref LL_EXTI_LINE_15
  *         @arg @ref LL_EXTI_LINE_16
  *         @arg @ref LL_EXTI_LINE_20
  *         @arg @ref LL_EXTI_LINE_21
  * @note This bit is set when the Trigger edge event arrives on the interrupt
  *         line. This bit is cleared by writing a 1 to the bit.
  * @note (*)Please check each device line mapping for EXTI Line availability.
  */
__STATIC_INLINE void LL_EXTI_ClearTriggerFlag_0_31(uint32_t exti_line)
{
  STM32_WRITE_REG(EXTI->PR1, exti_line);
}

/**
  * @brief  Clear EXTI Line Trigger Flags for Lines in range 32 to 63.
  * @rmtoll
  *  PR2          PRx           LL_EXTI_ClearTriggerFlag_32_63
  * @param exti_line This parameter can be a combination of the following values:
  *         @arg @ref LL_EXTI_LINE_34
  *         @arg @ref LL_EXTI_LINE_46
  *         @arg @ref LL_EXTI_LINE_49
  *         @arg @ref LL_EXTI_LINE_51
  *         @arg @ref LL_EXTI_LINE_60
  *         @arg @ref LL_EXTI_LINE_61
  *         @arg @ref LL_EXTI_LINE_62
  *         @arg @ref LL_EXTI_LINE_63
  * @note This bit is set when the Trigger edge event arrives on the interrupt
  *         line. This bit is cleared by writing a 1 to the bit.
  * @note (*)Please check each device line mapping for EXTI Line availability.
  */
__STATIC_INLINE void LL_EXTI_ClearTriggerFlag_32_63(uint32_t exti_line)
{
  STM32_WRITE_REG(EXTI->PR2, exti_line);
}

/**
  * @brief  Clear EXTI Line Trigger Flags for Lines in range 64 to 95.
  * @rmtoll
  *  PR3          PRx           LL_EXTI_ClearTriggerFlag_64_95
  * @param exti_line This parameter can be a combination of the following values:
  *         @arg @ref LL_EXTI_LINE_68
  *         @arg @ref LL_EXTI_LINE_69
  *         @arg @ref LL_EXTI_LINE_70
  *         @arg @ref LL_EXTI_LINE_71
  * @note This bit is set when the Trigger edge event arrives on the interrupt
  *         line. This bit is cleared by writing a 1 to the bit.
  * @note (*)Please check each device line mapping for EXTI Line availability.
  */
__STATIC_INLINE void LL_EXTI_ClearTriggerFlag_64_95(uint32_t exti_line)
{
  STM32_WRITE_REG(EXTI->PR3, exti_line);
}

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

#endif /* EXTI */

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /* STM32H7PXX_LL_EXTI_H */
