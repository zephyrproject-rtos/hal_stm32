/**
  ******************************************************************************
  * @file    stm32mp2xx_hal_pwr_ex.h
  * @author  MCD Application Team
  * @brief   Header file of PWR HAL Extension module.
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
#ifndef __STM32MP2xx_HAL_PWR_EX_H
#define __STM32MP2xx_HAL_PWR_EX_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32mp2xx_hal_def.h"


/** @addtogroup STM32MP2xx_HAL_Driver
  * @{
  */

/** @addtogroup PWREx
  * @{
  */

/* Exported types ------------------------------------------------------------*/

/** @defgroup PWREx_Exported_Types PWREx Exported Types
  * @{
  */

/**
  * @brief  PWREx voltage detector configuration structure definition
  */
typedef struct
{
  uint32_t Level;          /*!<   Level: Specifies the  detection level.
                                  This parameter can be a value of @ref PWREx  detection level */
  uint32_t Mode;           /*!<   Mode: Specifies the wake-up operating mode (see EXTI) for the selected pins
                                  This parameter can be a value of @ref PWR_EXTI_Mode */
} PWREx_DetectionTypeDef;
/**
  * @}
  */


/* Exported constants --------------------------------------------------------*/

/** @defgroup PWREx_Exported_Constants PWREx Exported Constants
  * @{
  */

/** @defgroup PWR_Exported_Constants_Group1 PWR_WakeUp_Pins
  * @{
  */

#if defined(CORE_CA35)
#define PWR_CPU_TO_WAKE_UP                   PWR_WKUPCR1_WKUPENCPU1
#endif /* CORE_CA35 */
#if defined(CORE_CM33)
#define PWR_CPU_TO_WAKE_UP                   PWR_WKUPCR1_WKUPENCPU2
#endif /* CORE_CM33 */

/*clear wake-up flag*/
#define PWR_WAKEUP_WKUPC                     PWR_WKUPCR1_WKUPC


/**
  * @}
  */


/** @defgroup PWR_Exported_Constants_Group3 PWREx Periph List
  * @{
  */
#define PWR_PVM_VDDIO1              0U
#define PWR_PVM_VDDIO2              1U
#define PWR_PVM_VDDIO3              2U
#define PWR_PVM_VDDIO4              3U
#define PWR_PVM_USB33               4U
#define PWR_PVM_UCPD                5U
#define PWR_PVM_A                   6U

#define PWR_PVM_MAX_PERIPH          7U


/**
  * @}
  */


/** @defgroup PWR_Exported_Constants_Group5 PWREx PVM Mode
  * @{
  */
#define PWR_PVM_MODE_NORMAL                              PWR_EXTI_MODE_NORMAL
#define PWR_PVM_MODE_IT_RISING                           PWR_EXTI_MODE_IT_RISING
#define PWR_PVM_MODE_IT_FALLING                          PWR_EXTI_MODE_IT_FALLING
#define PWR_PVM_MODE_IT_RISING_FALLING                   PWR_EXTI_MODE_IT_RISING_FALLING


/**
  * @}
  */

/** @defgroup PWR_Exported_Constants_Group6 PWREx VDDcpu detection level
  * @{
  */
#if defined (PWR_CR6_VCPUMONEN)
#define PWR_VDDCPUDLEVEL_0  (0U<<PWR_CR6_VCPULLS_Pos)
#define PWR_VDDCPUDLEVEL_1  (1U<<PWR_CR6_VCPULLS_Pos)
#endif /* PWR_CR6_VCPUMONEN */
/**
  * @}
  */

/** @defgroup PWR_Exported_Constants_Group7 PWREx VDDcpu/VDDcore Mode
  * @{
  */
#define PWREx_VBAT_TEMP_TAMPER_EVENT                         RTC_INT_TAMPER_2


#define PWR_VDDCPUD_MODE_NORMAL                              PWR_EXTI_MODE_NORMAL
#define PWR_VDDCPUD_MODE_IT_RISING                           PWR_EXTI_MODE_IT_RISING
#define PWR_VDDCPUD_MODE_IT_FALLING                          PWR_EXTI_MODE_IT_FALLING
#define PWR_VDDCPUD_MODE_IT_RISING_FALLING                   PWR_EXTI_MODE_IT_RISING_FALLING

#define PWR_VDDCORED_MODE_NORMAL                              PWR_EXTI_MODE_NORMAL
#define PWR_VDDCORED_MODE_IT_RISING                           PWR_EXTI_MODE_IT_RISING
#define PWR_VDDCORED_MODE_IT_FALLING                          PWR_EXTI_MODE_IT_FALLING
#define PWR_VDDCORED_MODE_IT_RISING_FALLING                   PWR_EXTI_MODE_IT_RISING_FALLING
/**
  * @}
  */


#ifdef CORE_CM33
/*both EXTI1 and EXTI2 interruptions are connected to M33 NVIC*/
#define EXTI_CONNECTOR1  EXTI1_C2
#define EXTI_CONNECTOR2  EXTI2_C2
#elif defined (CORE_CA35)
/*both EXTI1 and EXTI2 interruptions are connected to A35 GIC*/
#define EXTI_CONNECTOR1  EXTI1_C1
#define EXTI_CONNECTOR2  EXTI2_C1
#elif defined (CORE_CM0PLUS)
/*only  EXTI2 interruptions are connected to M0+ NVIC*/
#define EXTI_CONNECTOR2  EXTI2_C3
#endif /* CORE_CM33 */

/**
  * @brief  indicate voltage range where VDDGPU is
  * @retval None
  */
#define PWR_VDDGPU_BELOW_LOW_THRESHOLD                0U
#define PWR_VDDGPU_BELOW_HIGH_THRESHOLD               1U
#define PWR_VDDGPU_ABOVE_EQUAL_LOW_THRESHOLD          2U
#define PWR_VDDGPU_ABOVE_EQUAL_HIGH_THRESHOLD         3U
#define PWR_NO_VDDGPU_MEASUREMENT_AVAILABLE          15U

/**
  * @brief  indicate voltage range where VDDCPU is
  * @retval None
  */
#define PWR_VDDCPU_BETWEEN_HIGH_LOW_THRESHOLD  0U
#define PWR_VDDCPU_BELOW_LOW_THRESHOLD         1U
#define PWR_VDDCPU_ABOVE_HIGH_THRESHOLD        2U
#define PWR_NO_VDDCPU_MEASUREMENT_AVAILABLE    15U

/**
  * @brief  indicates voltage range where VDDCore is
  * @retval None
  */
#define PWR_VDDCORE_BETWEEN_HIGH_LOW_THRESHOLD  0U
#define PWR_VDDCORE_BELOW_LOW_THRESHOLD         1U
#define PWR_VDDCORE_ABOVE_HIGH_THRESHOLD        2U
#define PWR_NO_VDDCORE_MEASUREMENT_AVAILABLE    15U

/** @defgroup PWREx_Exported_Constants_Group7 PWREx VBAT Thresholds
  * @{
  */
#define PWR_VBAT_BETWEEN_HIGH_LOW_THRESHOLD  0U
#define PWR_VBAT_BELOW_LOW_THRESHOLD         1U  /*!< Vsw low threshold is ~1.35V */
#define PWR_VBAT_ABOVE_HIGH_THRESHOLD        2U  /*!< Vsw high threshold is ~3.6V */
#define PWR_NO_VBAT_MEASUREMENT_AVAILABLE    15U
/**
  * @}
  */

/** @defgroup PWR_Exported_Constants_Group8 PWREx Temperature Thresholds
  * @{
  */
#define PWR_TEMP_BETWEEN_HIGH_LOW_THRESHOLD  0U
#define PWR_TEMP_BELOW_LOW_THRESHOLD         1U
#define PWR_TEMP_ABOVE_HIGH_THRESHOLD        2U
#define PWR_NO_TEMP_MEASUREMENT_AVAILABLE    15U
/**
  * @}
  */

/** @defgroup PWR_Exported_Constants_Group9 PWREx Retention RAM supply state
  * @{
  */
#define PWR_RETENTION_RAM_SUPPLY_OFF             (0U << (uint32_t)PWR_CR10_RETRBSEN_Pos)  /*!< no Backup supply powering for retentionRAM*/
#define PWR_RETENTION_RAM_SUPPLY_ON_STDBY_VBAT   (1U << (uint32_t)PWR_CR10_RETRBSEN_Pos)  /*!< Backup supply powering for retentionRAM in both VBAT and STANDBY*/
#define PWR_RETENTION_RAM_SUPPLY_ON_STDBYONLY    (2U << (uint32_t)PWR_CR10_RETRBSEN_Pos)  /*!< Backup supply powering for retentionRAM in STANDBY only*/


#define IS_PWR_RETENTION_RAM_SUPPLY(__MODE__)          (((__MODE__) == PWR_RETENTION_RAM_SUPPLY_OFF) || \
                                                        ((__MODE__) == PWR_RETENTION_RAM_SUPPLY_ON_STDBY_VBAT)  || \
                                                        ((__MODE__) == PWR_RETENTION_RAM_SUPPLY_ON_STDBYONLY) )

/**
  * @}
  */

/**
  * @}
  */

/* Exported macro ------------------------------------------------------------*/
/** @defgroup PWREx_Exported_Macro PWREx Exported Macro
  *  @{
  */

/**
  * @brief Generic macros to manage EXTI event whatever instance of EXTI is and whatever connected CPU is
  * @param _LINE_: Specifies  on which EXTI line event is connected
  * @param INSTANCE: Specifies either EXTI instance or in case of interruption management macro,EXTI_connector instance
  * @retval None.
  */

#define __HAL_PWR_EXTI_ENABLE_IT(INSTANCE, _LINE_)   ((_LINE_ < 32U) ? SET_BIT(INSTANCE->IMR1, _LINE_)  :\
                                                      ((_LINE_ < 64U) ? SET_BIT(INSTANCE->IMR2, _LINE_) :\
                                                       SET_BIT(INSTANCE->IMR3, _LINE_)))

#define __HAL_PWR_EXTI_DISABLE_IT(INSTANCE, _LINE_)  ((_LINE_ < 32U) ? CLEAR_BIT(INSTANCE->IMR1, _LINE_)  :\
                                                      ((_LINE_ < 64U) ? CLEAR_BIT(INSTANCE->IMR2, _LINE_) :\
                                                       CLEAR_BIT(INSTANCE->IMR3, _LINE_)))

#define __HAL_PWR_EXTI_ENABLE_RISING_EDGE(INSTANCE, _LINE_)   ((_LINE_ < 32U) ? SET_BIT(INSTANCE->RTSR1, _LINE_)   :\
                                                               ((_LINE_ < 64U) ? SET_BIT(INSTANCE->RTSR2, _LINE_)  :\
                                                                SET_BIT(INSTANCE->RTSR3, _LINE_)))

#define __HAL_PWR_EXTI_DISABLE_RISING_EDGE(INSTANCE, _LINE_)  ((_LINE_ < 32U) ? CLEAR_BIT(INSTANCE->RTSR1, _LINE_)  :\
                                                               ((_LINE_ < 64U) ? CLEAR_BIT(INSTANCE->RTSR2, _LINE_) :\
                                                                CLEAR_BIT(INSTANCE->RTSR3, _LINE_)))

#define __HAL_PWR_EXTI_ENABLE_FALLING_EDGE(INSTANCE, _LINE_)  ((_LINE_ < 32U) ? SET_BIT(INSTANCE->FTSR1, _LINE_)   :\
                                                               ((_LINE_ < 64U) ? SET_BIT(INSTANCE->FTSR2, _LINE_)  :\
                                                                SET_BIT(INSTANCE->FTSR3, _LINE_)))

#define __HAL_PWR_EXTI_DISABLE_FALLING_EDGE(INSTANCE, _LINE_)   ((_LINE_ < 32U) ? CLEAR_BIT(INSTANCE->FTSR1, _LINE_)  :\
                                                                 ((_LINE_ < 64U) ? CLEAR_BIT(INSTANCE->FTSR2, _LINE_) :\
                                                                  CLEAR_BIT(INSTANCE->FTSR3, _LINE_)))

#define __HAL_PWR_EXTI_GENERATE_SWIT(INSTANCE, _LINE_)  ((_LINE_ < 32U) ? SET_BIT(INSTANCE->SWIER1, _LINE_)  :\
                                                         ((_LINE_ < 64U) ? SET_BIT(INSTANCE->SWIER2, _LINE_) :\
                                                          SET_BIT(INSTANCE->SWIER3, _LINE_))

#define __HAL_PWR_EXTI_GET_FLAG(INSTANCE, _LINE_)     ((_LINE_ < 32U) ? (((INSTANCE->RPR1 & _LINE_) == _LINE_) || \
                                                                         (( INSTANCE->FPR1 & _LINE_) == _LINE_)) : \
                                                       ((_LINE_ < 64U) ? (((INSTANCE->RPR2 & _LINE_) == _LINE_) || \
                                                                          (( INSTANCE->FPR2 & _LINE_) == _LINE_)) : \
                                                        (((INSTANCE->RPR3 & _LINE_) == _LINE_) || \
                                                         (( INSTANCE->FPR3 & _LINE_) == _LINE_))))

#define __HAL_PWR_EXTI_CLEAR_RFLAG(INSTANCE, _LINE_)    ((_LINE_ < 32U) ? SET_BIT(INSTANCE->RPR1, _LINE_)  : \
                                                         ((_LINE_ < 64U) ? SET_BIT(INSTANCE->RPR2, _LINE_) : \
                                                          SET_BIT(INSTANCE->RPR3, _LINE_)))

#define __HAL_PWR_EXTI_CLEAR_FFLAG(INSTANCE, _LINE_)     ((_LINE_ < 32U) ? SET_BIT(INSTANCE->FPR1, _LINE_)  : \
                                                          ((_LINE_ < 64U) ? SET_BIT(INSTANCE->FPR2, _LINE_) : \
                                                           SET_BIT(INSTANCE->FPR3, _LINE_)))


#define __HAL_PWR_EXTI_CLEAR_FLAG(INSTANCE, _LINE_)           \
  do {\
    __HAL_PWR_EXTI_CLEAR_FFLAG(INSTANCE, _LINE_);  \
    __HAL_PWR_EXTI_CLEAR_RFLAG(INSTANCE, _LINE_);  \
  }while(0);

#define __HAL_PWR_EXTI_ENABLE_RISING_FALLING_EDGE(INSTANCE, _LINE_) \
  do { \
    __HAL_PWR_EXTI_ENABLE_RISING_EDGE(INSTANCE, _LINE_); \
    __HAL_PWR_EXTI_ENABLE_FALLING_EDGE(INSTANCE, _LINE_); \
  } while(0);

#define __HAL_PWR_EXTI_DISABLE_RISING_FALLING_EDGE(INSTANCE, _LINE_) \
  do { \
    __HAL_PWR_EXTI_DISABLE_RISING_EDGE(INSTANCE, _LINE_); \
    __HAL_PWR_EXTI_DISABLE_FALLING_EDGE(INSTANCE, _LINE_); \
  } while(0);


/**
  * @brief Enable the PVM  Exti Line.
  * @ note Exti Line is connected to Instance 1 of EXTI IP.
  * @note EXTI1 event are connected to A35_GIC and M33_NVIC but not to M0+_NVIC
  * @retval None.
  */
#if !defined(CORE_CM0PLUS)
#define __HAL_PWR_PVM_EXTI_ENABLE_IT()  SET_BIT(EXTI_CONNECTOR1->IMR1, PWR_EXTI_LINE_PVM)
#endif /* CORE_CM0PLUS */

/**
  * @brief Disable the PVM  EXTI Line.
  * @ note Exti Line is connected to Instance 1 of EXTI IP.
  * @note EXTI1 event are connected to A35_GIC and M33_NVIC but not to M0+_NVIC
  * @retval None.
  */
#if !defined(CORE_CM0PLUS)
#define __HAL_PWR_PVM_EXTI_DISABLE_IT() CLEAR_BIT(EXTI_CONNECTOR1->IMR1, PWR_EXTI_LINE_PVM)
#endif /* CORE_CM0PLUS */

/**
  * @brief Enable the PVM  Extended Interrupt Rising Trigger.
  * @retval None.
  */
#if !defined(CORE_CM0PLUS)
#define __HAL_PWR_PVM_EXTI_ENABLE_RISING_EDGE()  SET_BIT(EXTI1->RTSR1, PWR_EXTI_LINE_PVM)
#endif /* CORE_CM0PLUS */

/**
  * @brief Disable the PVM  Extended Interrupt Rising Trigger.
  * @retval None.
  */
#if !defined(CORE_CM0PLUS)
#define __HAL_PWR_PVM_EXTI_DISABLE_RISING_EDGE()  CLEAR_BIT(EXTI1->RTSR1, PWR_EXTI_LINE_PVM)
#endif /* CORE_CM0PLUS */


/**
  * @brief Enable the PVM Extended Interrupt Falling Trigger.
  * @retval None.
  */
#if !defined(CORE_CM0PLUS)
#define __HAL_PWR_PVM_EXTI_ENABLE_FALLING_EDGE()  SET_BIT(EXTI1->FTSR1, PWR_EXTI_LINE_PVM)
#endif /* CORE_CM0PLUS */

/**
  * @brief Disable the PVM  Extended Interrupt Falling Trigger.
  * @retval None.
  */
#if !defined(CORE_CM0PLUS)
#define __HAL_PWR_PVM_EXTI_DISABLE_FALLING_EDGE()  CLEAR_BIT(EXTI1->FTSR1, PWR_EXTI_LINE_PVM)
#endif /* CORE_CM0PLUS */

/**
  * @brief  PVM EXTI line configuration: set rising & falling edge trigger.
  * @retval None.
  */
#if !defined(CORE_CM0PLUS)
#define __HAL_PWR_PVM_EXTI_ENABLE_RISING_FALLING_EDGE() \
  do { \
    __HAL_PWR_PVM_EXTI_ENABLE_RISING_EDGE(); \
    __HAL_PWR_PVM_EXTI_ENABLE_FALLING_EDGE(); \
  } while(0);
#endif /* CORE_CM0PLUS */


/**
  * @brief Disable the PVM Extended Interrupt Rising & Falling Trigger.
  * @retval None.
  */
#if !defined(CORE_CM0PLUS)
#define __HAL_PWR_PVM_EXTI_DISABLE_RISING_FALLING_EDGE() \
  do { \
    __HAL_PWR_PVM_EXTI_DISABLE_RISING_EDGE(); \
    __HAL_PWR_PVM_EXTI_DISABLE_FALLING_EDGE(); \
  } while(0);
#endif /* CORE_CM0PLUS */


/**
  * @brief Check whether the specified PVM EXTI interrupt flag is set or not.
  * @retval EXTI PVM Line Status.
  */
#define __HAL_PWR_PVM_EXTI_GET_FLAG() \
  (((EXTI1->RPR1 & PWR_EXTI_LINE_PVM) == PWR_EXTI_LINE_PVM) || \
   ((EXTI1->FPR1 & PWR_EXTI_LINE_PVM) == PWR_EXTI_LINE_PVM))


/**
  * @brief Clear the PVM Exti flag.
  * @retval None.
  */
#define __HAL_PWR_PVM_EXTI_CLEAR_FLAG() \
  do { \
    SET_BIT(EXTI1->RPR1, PWR_EXTI_LINE_PVM); \
    SET_BIT(EXTI1->FPR1, PWR_EXTI_LINE_PVM); \
  } while(0);


/**
  * @brief  Generates a Software interrupt on PVM EXTI line
  * @retval None
  */
/*PVM Event in Bank1 */
#define __HAL_PWR_PVM_EXTI_GENERATE_SWIT() SET_BIT(EXTI1->SWIER1, PWR_EXTI_LINE_PVM )


/**
  * @brief Enable/Disable  VDDgpuD  Extended interruption from EXTI1 to current CPU (VDDgpuD line connected to EXTI1)
  * @retval None.
  */
#define __HAL_PWR_VDDGPUD_EXTI_ENABLE_IT()  __HAL_PWR_EXTI_ENABLE_IT(EXTI_CONNECTOR1,PWR_EXTI_LINE_VDDGPUD)
#define __HAL_PWR_VDDGPUD_EXTI_DISABLE_IT()  __HAL_PWR_EXTI_DISABLE_IT(EXTI_CONNECTOR1,PWR_EXTI_LINE_VDDGPUD)


/**
  * @brief Enable/Disable the VDDgpuD  Extended Interrupt Rising Trigger from EXTI1 (VDDgpuD line connected to EXTI1)
  * @retval None.
  */
#define __HAL_PWR_VDDGPUD_EXTI_ENABLE_RISING_EDGE()  __HAL_PWR_EXTI_ENABLE_RISING_EDGE(EXTI1, PWR_EXTI_LINE_VDDGPUD)
#define __HAL_PWR_VDDGPUD_EXTI_DISABLE_RISING_EDGE()  __HAL_PWR_EXTI_DISABLE_RISING_EDGE(EXTI1, PWR_EXTI_LINE_VDDGPUD)

/**
  * @brief Enable/Disable the VDDgpuD  Extended Interrupt Falling Trigger from EXTI1 (VDDgpuD line connected to EXTI1)
  * @retval None.
  */
#define __HAL_PWR_VDDGPUD_EXTI_ENABLE_FALLING_EDGE()  __HAL_PWR_EXTI_ENABLE_FALLING_EDGE(EXTI1, PWR_EXTI_LINE_VDDGPUD)
#define __HAL_PWR_VDDGPUD_EXTI_DISABLE_FALLING_EDGE()  __HAL_PWR_EXTI_DISABLE_FALLING_EDGE(EXTI1, PWR_EXTI_LINE_VDDGPUD)

/**
  * @brief Enable/Disable the VDDgpuD  Extended Interrupt Falling and Rising Trigger from EXTI1
  *        (VDDgpuD line connected to EXTI1)
  * @retval None.
  */
#define __HAL_PWR_VDDGPUD_EXTI_ENABLE_RISING_FALLING_EDGE()  __HAL_PWR_EXTI_ENABLE_RISING_FALLING_EDGE(EXTI1, \
    PWR_EXTI_LINE_VDDGPUD)
#define __HAL_PWR_VDDGPUD_EXTI_DISABLE_RISING_FALLING_EDGE()  __HAL_PWR_EXTI_DISABLE_RISING_FALLING_EDGE(EXTI1, \
    PWR_EXTI_LINE_VDDGPUD)

/**
  * @brief Check whether the specified VDDgpuD EXTI interrupt flag is set or not from EXTI1
  *        (VDDgpuD line connected to EXTI1)
  * @retval EXTI VDDgpuD Line Status.
  */
#define __HAL_PWR_VDDGPUD_EXTI_GET_FLAG()  __HAL_PWR_EXTI_GET_FLAG(EXTI1, PWR_EXTI_LINE_VDDGPUD)

/**
  * @brief Clear the VDDgpuD Exti flag on EXTI1 (VDDgpuD line connected to EXTI1)
  * @retval None.
  */
#define __HAL_PWR_VDDGPUD_EXTI_CLEAR_FLAG()  __HAL_PWR_EXTI_CLEAR_FLAG(EXTI1, PWR_EXTI_LINE_VDDGPUD)

/**
  * @brief  Generates VDDgpuD Software interrupt  on EXTI1 (VDDgpuD line connected to EXTI1)
  * @retval None
  */
#define __HAL_PWR_VDDGPUD_EXTI_GENERATE_SWIT() __HAL_PWR_EXTI_GENERATE_SWIT(EXTI1, PWR_EXTI_LINE_VDDGPUD)


/**
  * @brief Enable/Disable  VDDcpuD  Extended interruption from EXTI2 to current CPU (VDDcpuD line connected to EXTI2)
  * @retval None.
  */
#define __HAL_PWR_VDDCPUD_EXTI_ENABLE_IT()  __HAL_PWR_EXTI_ENABLE_IT(EXTI_CONNECTOR2,PWR_EXTI_LINE_VDDCPUD)
#define __HAL_PWR_VDDCPUD_EXTI_DISABLE_IT()  (__HAL_PWR_EXTI_DISABLE_IT(EXTI_CONNECTOR2,PWR_EXTI_LINE_VDDCPUD))


/**
  * @brief Enable/Disable the VDDcpuD  Extended Interrupt Rising Trigger from EXTI2 (VDDcpuD line connected to EXTI2)
  * @retval None.
  */
#define __HAL_PWR_VDDCPUD_EXTI_ENABLE_RISING_EDGE()  __HAL_PWR_EXTI_ENABLE_RISING_EDGE(EXTI2, PWR_EXTI_LINE_VDDCPUD)
#define __HAL_PWR_VDDCPUD_EXTI_DISABLE_RISING_EDGE()  __HAL_PWR_EXTI_DISABLE_RISING_EDGE(EXTI2, PWR_EXTI_LINE_VDDCPUD)

/**
  * @brief Enable/Disable the VDDcpuD  Extended Interrupt Falling Trigger from EXTI2 (VDDcpuD line connected to EXTI2)
  * @retval None.
  */
#define __HAL_PWR_VDDCPUD_EXTI_ENABLE_FALLING_EDGE()  __HAL_PWR_EXTI_ENABLE_FALLING_EDGE(EXTI2, PWR_EXTI_LINE_VDDCPUD)
#define __HAL_PWR_VDDCPUD_EXTI_DISABLE_FALLING_EDGE()  __HAL_PWR_EXTI_DISABLE_FALLING_EDGE(EXTI2, PWR_EXTI_LINE_VDDCPUD)

/**
  * @brief Enable/Disable the VDDcpuD  Extended Interrupt Falling and Rising Trigger from EXTI2
  *        (VDDcpuD line connected to EXTI2)
  * @retval None.
  */
#define __HAL_PWR_VDDCPUD_EXTI_ENABLE_RISING_FALLING_EDGE()  __HAL_PWR_EXTI_ENABLE_RISING_FALLING_EDGE(EXTI2, \
    PWR_EXTI_LINE_VDDCPUD)
#define __HAL_PWR_VDDCPUD_EXTI_DISABLE_RISING_FALLING_EDGE()  __HAL_PWR_EXTI_DISABLE_RISING_FALLING_EDGE(EXTI2, \
    PWR_EXTI_LINE_VDDCPUD)

/**
  * @brief Check whether the specified VDDcpuD EXTI interrupt flag is set or not from EXTI2
  *        (VDDcpuD line connected to EXTI2)
  * @retval EXTI VDDcpuD Line Status.
  */
#define __HAL_PWR_VDDCPUD_EXTI_GET_FLAG()  __HAL_PWR_EXTI_GET_FLAG(EXTI2, PWR_EXTI_LINE_VDDCPUD)

/**
  * @brief Clear the VDDcpuD Exti flag on EXTI2 (VDDcpuD line connected to EXTI2)
  * @retval None.
  */
#define __HAL_PWR_VDDCPUD_EXTI_CLEAR_FLAG()  __HAL_PWR_EXTI_CLEAR_FLAG(EXTI2, PWR_EXTI_LINE_VDDCPUD)

/**
  * @brief  Generates VDDcpuD Software interrupt  on EXTI2 (VDDcpuD line connected to EXTI2)
  * @retval None
  */
#define __HAL_PWR_VDDCPUD_EXTI_GENERATE_SWIT() __HAL_PWR_EXTI_GENERATE_SWIT(EXTI2, PWR_EXTI_LINE_VDDCPUD)

/**
  * @brief Enable/Disable  VDDcoreD Extended interruption from EXTI2 to current CPU (VDDcoreD line connected to EXTI2)
  * @retval None.
  */
#define __HAL_PWR_VDDCORED_EXTI_ENABLE_IT()  __HAL_PWR_EXTI_ENABLE_IT(EXTI_CONNECTOR2,PWR_EXTI_LINE_VDDCORED)
#define __HAL_PWR_VDDCORED_EXTI_DISABLE_IT()  __HAL_PWR_EXTI_DISABLE_IT(EXTI_CONNECTOR2,PWR_EXTI_LINE_VDDCORED)


/**
  * @brief Enable/Disable the VDDcoreD  Extended Interrupt Rising Trigger on EXTI2 (VDDcoreD line connected to EXTI2)
  * @retval None.
  */
#define __HAL_PWR_VDDCORED_EXTI_ENABLE_RISING_EDGE()  __HAL_PWR_EXTI_ENABLE_RISING_EDGE(EXTI2, PWR_EXTI_LINE_VDDCORED)
#define __HAL_PWR_VDDCORED_EXTI_DISABLE_RISING_EDGE()  __HAL_PWR_EXTI_DISABLE_RISING_EDGE(EXTI2, PWR_EXTI_LINE_VDDCORED)

/**
  * @brief Enable/Disable the VDDcoreD  Extended Interrupt Falling Trigger on EXTI2 (VDDcoreD line connected to EXTI2)
  * @retval None.
  */
#define __HAL_PWR_VDDCORED_EXTI_ENABLE_FALLING_EDGE()   __HAL_PWR_EXTI_ENABLE_FALLING_EDGE(EXTI2, \
    PWR_EXTI_LINE_VDDCORED)
#define __HAL_PWR_VDDCORED_EXTI_DISABLE_FALLING_EDGE()  __HAL_PWR_EXTI_DISABLE_FALLING_EDGE(EXTI2, \
    PWR_EXTI_LINE_VDDCORED)

/**
  * @brief Enable/Disable the VDDcoreD  Extended Interrupt Falling and Rising Trigger on EXTI2
  *        (VDDcoreD line connected to EXTI2)
  * @retval None.
  */
#define __HAL_PWR_VDDCORED_EXTI_ENABLE_RISING_FALLING_EDGE()   __HAL_PWR_EXTI_ENABLE_RISING_FALLING_EDGE(EXTI2, \
    PWR_EXTI_LINE_VDDCORED)
#define __HAL_PWR_VDDCORED_EXTI_DISABLE_RISING_FALLING_EDGE()  __HAL_PWR_EXTI_DISABLE_RISING_FALLING_EDGE(EXTI2, \
    PWR_EXTI_LINE_VDDCORED)

/**
  * @brief Check whether the specified VDDcoreD EXTI interrupt flag is set or not on EXTI2
  *        (VDDcoreD line connected to EXTI2)
  * @retval EXTI VDDcoreD Line Status.
  */
#define __HAL_PWR_VDDCORED_EXTI_GET_FLAG()  __HAL_PWR_EXTI_GET_FLAG(EXTI2, PWR_EXTI_LINE_VDDCORED)

/**
  * @brief Clear the VDDcoreD Exti flag on EXTI2 (VDDcoreD line connected to EXTI2)
  * @retval None.
  */
#define __HAL_PWR_VDDCORED_EXTI_CLEAR_FLAG()  __HAL_PWR_EXTI_CLEAR_FLAG(EXTI2, PWR_EXTI_LINE_VDDCORED)

/**
  * @brief  Generates VDDcoreD Software interrupt  on EXTI2 (VDDcoreD line connected to EXTI2)
  * @retval None
  */
#define __HAL_PWR_VDDCORED_EXTI_GENERATE_SWIT() __HAL_PWR_EXTI_GENERATE_SWIT(EXTI2, PWR_EXTI_LINE_VDDCORED)


/**
  * @brief Enable/Disable  NS TAMPER Extended interruption from EXTI2 to current CPU (TAMPER line connected to EXTI2)
  * @retval None.
  */
#define __HAL_PWR_NS_TAMPER_EXTI_ENABLE_IT()   __HAL_PWR_EXTI_ENABLE_IT (EXTI_CONNECTOR2,PWR_EXTI_LINE_NS_TAMPER)
#define __HAL_PWR_NS_TAMPER_EXTI_DISABLE_IT()  __HAL_PWR_EXTI_DISABLE_IT(EXTI_CONNECTOR2,PWR_EXTI_LINE_NS_TAMPER)

/**
  * @}
  */

/* Exported functions --------------------------------------------------------*/
/** @defgroup PWREx_Exported_Functions PWREx Exported Functions
  * @{
  */

/** @defgroup PWREx_Exported_Functions_Group1 Low power control functions
  * @{
  */
/* Power Wakeup PIN IRQ Handler */
#if !defined(CORE_CM0PLUS)
void HAL_PWREx_WAKEUP_PIN_IRQHandler(void);
#endif /* CORE_CM0PLUS */

/**
  * @}
  */

/** @defgroup PWREx_Exported_Functions_Group2 Peripherals control functions
  * @{
  */
/* Backup regulator control functions for backupRAM*/
void HAL_PWREx_EnableBkUpRamContentStandbyRetention(void);
void HAL_PWREx_DisableBkUpRamContentStandbyRetention(void);

/* Backup regulator control functions  for retentionRAM*/
void HAL_PWREx_EnableRetRamContentStandbyRetention(uint32_t RetentionRamPowerSupplyMode);
void HAL_PWREx_DisableRetRamContentStandbyRetention(void);

#if defined(PWR_CR9_LPR1BSEN)
/* Backup regulator control functions for CPU3 LPSRAM */
void HAL_PWREx_EnableLpsram1ContentStandby2Retention(void);
void HAL_PWREx_DisableLpsram1ContentStandby2Retention(void);
#endif /* defined(PWR_CR9_LPR1BSEN) */

/**
  * @}
  */

/** @defgroup PWREx_Exported_Functions_Group3 Power Monitoring functions
  * @{
  */
/* Power VBAT/Temperature monitoring functions */
#if defined(CORE_CM33)||defined(CORE_CA35)
void HAL_PWREx_EnableVbatTempMonitoring(void);
void HAL_PWREx_DisableVbatTempMonitoring(void);
#endif /* defined(CORE_CM33)||defined(CORE_CA35)) */
uint32_t HAL_PWREx_GetTemperatureLevel(void);
uint32_t HAL_PWREx_GetVbatLevel(void);
void HAL_PWREx_TEMP_VBAT_IRQHandler(void);
void HAL_PWREx_TEMP_HIGHERCallback(void);
void HAL_PWREx_TEMP_LowerCallback(void);
void HAL_PWREx_TEMP_INRANGECallback(void);
void HAL_PWREx_VBAT_HIGHERCallback(void);
void HAL_PWREx_VBAT_LowerCallback(void);
void HAL_PWREx_VBAT_INRANGECallback(void);

#if defined(PWR_CR12_VDDGPURDY)
/* GPU supply functions */
#if defined(CORE_CM33)||defined(CORE_CA35)
HAL_StatusTypeDef HAL_PWREx_EnableGPUSupply(void);
void HAL_PWREx_DisableGPUSupply(void);
HAL_StatusTypeDef HAL_PWREx_EnableGPUSupplyMonitoring(void);
void HAL_PWREx_DisableGPUSupplyMonitoring(void);
HAL_StatusTypeDef HAL_PWREx_EnableGPULowThreshold(void);
void HAL_PWREx_DisableGPULowThreshold(void);
uint32_t HAL_PWREx_GetVDDgpuRange(void);
void HAL_PWREx_GPU_IRQHandler(void);
void HAL_PWREx_GPU_EqualHigherCallback(void);
void HAL_PWREx_GPU_LowerCallback(void);
#endif /* defined(CORE_CM33)||defined(CORE_CA35) */
#endif /* defined(PWR_CR12_VDDGPURDY) */

/* Power PVM configuration functions */
#if defined(CORE_CM33)||defined(CORE_CA35)
void HAL_PWREx_Set_IO_Voltage(uint32_t periph, uint32_t setLow, uint32_t setLowStandby);
void HAL_PWREx_Get_IO_Voltage(uint32_t periph, uint32_t *isLow, uint32_t *isLowStandby);
void HAL_PWREx_ConfigurePVM(uint32_t mode);
HAL_StatusTypeDef HAL_PWREx_EnableSupply(uint32_t periph);
void HAL_PWREx_DisableSupply(uint32_t periph);
void HAL_PWREx_EnableSupplyMonitoring(uint32_t periph);
void HAL_PWREx_DisableSupplyMonitoring(uint32_t periph);
uint32_t HAL_PWREx_PVM_IsBelowThreshold(uint32_t periph);
void HAL_PWREx_PVM_IRQHandler(void);
void HAL_PWREx_PVM_EqualHigherCallback(void);
void HAL_PWREx_PVM_LowerCallback(void);
#endif /*defined(CORE_CM33)||defined(CORE_CA35)*/

#if defined (PWR_CR6_VCPUMONEN)
/* Power VDDcpu detection functions */
#if defined(CORE_CM33)||defined(CORE_CA35)
void HAL_PWREx_ConfigVDDcpuD(const PWREx_DetectionTypeDef *sConfigVDDcpuD);
void HAL_PWREx_EnableVDDcpuD(void);
void HAL_PWREx_DisableVDDcpuD(void);
#endif /* defined(CORE_CM33)||defined(CORE_CA35) */
uint32_t HAL_PWREx_GetVDDcpuRange(void);
void HAL_PWREx_VDDcpuD_IRQHandler(void);
void HAL_PWREx_VDDcpuD_HIGHERCallback(void);
void HAL_PWREx_VDDcpuD_LowerCallback(void);
void HAL_PWREx_VDDcpuD_INRANGECallback(void);
#endif /* PWR_CR6_VCPUMONEN */

#if defined (PWR_CR5_VCOREMONEN)
/* Power VDDcore detection functions */
#if defined(CORE_CM33)||defined(CORE_CA35)
void HAL_PWREx_ConfigVDDcoreD(const PWREx_DetectionTypeDef *sConfigVDDcoreD);
void HAL_PWREx_EnableVDDcoreD(void);
void HAL_PWREx_DisableVDDcoreD(void);
#endif /* defined(CORE_CM33)||defined(CORE_CA35) */
uint32_t HAL_PWREx_GetVDDcoreRange(void);
void HAL_PWREx_VDDcoreD_IRQHandler(void);
void HAL_PWREx_VDDcoreD_HIGHERCallback(void);
void HAL_PWREx_VDDcoreD_LowerCallback(void);
void HAL_PWREx_VDDcoreD_INRANGECallback(void);
#endif /* PWR_CR5_VCOREMONEN */

/*new API for system pwr state (STM32MP2 specific)*/
void HAL_PWREx_EnterCSTOPAllowSTOP(uint32_t Regulator, uint8_t STOPEntry);
#if defined(CORE_CM33)||defined(CORE_CA35)
void HAL_PWREx_EnterCSTOPAllowSTANDBY(uint8_t  STANDBYType);
#endif /* defined(CORE_CM33)||defined(CORE_CA35) */

void HAL_PWREx_ClearStatusFlag(void);

#if defined(CORE_CM33)||defined(CORE_CA35)
void HAL_PWREx_WKUP_Callback(__attribute__((unused))uint16_t line);
#endif /*defined(CORE_CM33)||defined(CORE_CA35)*/
/**
  * @}
  */

/**
  * @}
  */


/* Private types -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/** @defgroup PWREx_Private_Macros PWREx Private Macros
  * @{
  */

/** @defgroup PWREx_IS_PWR_Definitions PWREx Private macros to check input parameters
  * @{
  */

#define IS_PWR_CONFIGURABLE_IO(__PERIPH__)         (((__PERIPH__)==(PWR_PVM_VDDIO1))||((__PERIPH__)==(PWR_PVM_VDDIO2)))


#define IS_PWR_PVM_PERIPH(__PERIPH__)         ((__PERIPH__)<(PWR_PVM_MAX_PERIPH))

#define IS_PWR_PVM_MODE(MODE) IS_PWR_EXTI_MODE(MODE)
#define IS_AN_INTERRUPT_PWR_PVM_MODE(MODE)  IS_AN_INTERRUPT_PWR_EXTI_MODE(MODE)

#if defined (PWR_CR6_VCPUMONEN)
#define IS_PWR_VDDCPUD_LEVEL(LEVEL)  (((LEVEL) == PWR_VDDCPUDLEVEL_0) || ((LEVEL) == PWR_VDDCPUDLEVEL_1))
#endif /* PWR_CR6_VCPUMONEN */
#define IS_PWR_VDDCPUD_MODE(MODE) IS_PWR_EXTI_MODE(MODE)
#define IS_AN_INTERRUPT_PWR_VDDCPUD_MODE(MODE)  IS_AN_INTERRUPT_PWR_EXTI_MODE(MODE)


#define IS_PWR_VDDCORED_MODE(MODE) IS_PWR_EXTI_MODE(MODE)
#define IS_AN_INTERRUPT_PWR_VDDCORED_MODE(MODE)  IS_AN_INTERRUPT_PWR_EXTI_MODE(MODE)
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


#endif /* __STM32MP2xx_HAL_PWR_EX_H */
