/**
  ******************************************************************************
  * @file    stm32mp2xx_hal_pwr.h
  * @author  MCD Application Team
  * @brief   Header file of PWR HAL module.
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

#ifndef __STM32MP2xx_HAL_PWR_H
#define __STM32MP2xx_HAL_PWR_H


#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32mp2xx_hal_def.h"

/** @addtogroup STM32MP2xx_HAL_Driver
  * @{
  */

/** @addtogroup PWR
  * @{
  */


/* Exported types ------------------------------------------------------------*/
/** @defgroup PWR_Exported_Types PWR Exported Types
  * @{
  */

/**
  * @brief  PWR PVD configuration structure definition
  */
typedef struct
{
  uint32_t Mode;      /*!< Mode: Specifies the operating mode for the selected pins.
                           This parameter can be a value of @ref PWR_EXTI_Mode */
} PWR_PVDTypeDef;
/**
  * @}
  */

/* Exported constants --------------------------------------------------------*/

/** @defgroup PWR_Exported_Constants PWR Exported Constants
  * @{
  */

/** @defgroup PWR_WAKEUP_PIN_ID PWR PWR WAKEUP PIN ID
  * @{
  */
#define PWR_WAKEUP_PIN_ID1              0U    /*!< Wakeup event on pin WKUP1 */
#define PWR_WAKEUP_PIN_ID2              1U    /*!< Wakeup event on pin WKUP2 */
#define PWR_WAKEUP_PIN_ID3              2U    /*!< Wakeup event on pin WKUP3 */
#define PWR_WAKEUP_PIN_ID4              3U    /*!< Wakeup event on pin WKUP4 */
#define PWR_WAKEUP_PIN_ID5              4U    /*!< Wakeup event on pin WKUP5 */
#define PWR_WAKEUP_PIN_ID6              5U    /*!< Wakeup event on pin WKUP6 */
#define PWR_WAKEUP_PIN_ID_POS           0U
#define PWR_WAKEUP_PIN_ID_SIZE          6U
#define PWR_WAKEUP_PIN_ID_MASK          (0x3FU << PWR_WAKEUP_PIN_ID_POS)

#define PWR_WAKEUP_HIGH                 0U    /* detection on rising edge */
#define PWR_WAKEUP_LOW                  1U    /* detection on falling edge */
#define PWR_WAKEUP_EDGE_POS             (PWR_WAKEUP_PIN_ID_POS + PWR_WAKEUP_PIN_ID_SIZE)
#define PWR_WAKEUP_EDGE_SIZE            1U
#define PWR_WAKEUP_EDGE_MASK            (1U << PWR_WAKEUP_EDGE_POS)


#define PWR_WAKEUP_NOPULL               0U    /* no pull setting */
#define PWR_WAKEUP_PULLUP               1U    /* pull up setting */
#define PWR_WAKEUP_PULLDOWN             2U    /* pull down setting */
#define PWR_WAKEUP_PULL_POS             (PWR_WAKEUP_EDGE_POS + PWR_WAKEUP_EDGE_SIZE)
#define PWR_WAKEUP_PULL_MASK            (3U << PWR_WAKEUP_PULL_POS)


/*legacy heritage*/
#define PWR_WAKEUP_PIN6_HIGH                 \
  (PWR_WAKEUP_PIN_ID6 << PWR_WAKEUP_PIN_ID_POS) | (PWR_WAKEUP_HIGH << PWR_WAKEUP_EDGE_POS) | \
  (PWR_WAKEUP_NOPULL << PWR_WAKEUP_PULL_POS)
#define PWR_WAKEUP_PIN5_HIGH                 \
  (PWR_WAKEUP_PIN_ID5 << PWR_WAKEUP_PIN_ID_POS) | (PWR_WAKEUP_HIGH << PWR_WAKEUP_EDGE_POS) | \
  (PWR_WAKEUP_NOPULL << PWR_WAKEUP_PULL_POS)
#define PWR_WAKEUP_PIN4_HIGH                 \
  (PWR_WAKEUP_PIN_ID4 << PWR_WAKEUP_PIN_ID_POS) | (PWR_WAKEUP_HIGH << PWR_WAKEUP_EDGE_POS) | \
  (PWR_WAKEUP_NOPULL << PWR_WAKEUP_PULL_POS)
#define PWR_WAKEUP_PIN3_HIGH                 \
  (PWR_WAKEUP_PIN_ID3 << PWR_WAKEUP_PIN_ID_POS) | (PWR_WAKEUP_HIGH << PWR_WAKEUP_EDGE_POS) | \
  (PWR_WAKEUP_NOPULL << PWR_WAKEUP_PULL_POS)
#define PWR_WAKEUP_PIN2_HIGH                 \
  (PWR_WAKEUP_PIN_ID2 << PWR_WAKEUP_PIN_ID_POS) | (PWR_WAKEUP_HIGH << PWR_WAKEUP_EDGE_POS) | \
  (PWR_WAKEUP_NOPULL << PWR_WAKEUP_PULL_POS)
#define PWR_WAKEUP_PIN1_HIGH                 \
  (PWR_WAKEUP_PIN_ID1 << PWR_WAKEUP_PIN_ID_POS) | (PWR_WAKEUP_HIGH << PWR_WAKEUP_EDGE_POS) | \
  (PWR_WAKEUP_NOPULL << PWR_WAKEUP_PULL_POS)

#define PWR_WAKEUP_PIN6_LOW                 \
  (PWR_WAKEUP_PIN_ID6 << PWR_WAKEUP_PIN_ID_POS) | (PWR_WAKEUP_LOW << PWR_WAKEUP_EDGE_POS) | \
  (PWR_WAKEUP_NOPULL << PWR_WAKEUP_PULL_POS)
#define PWR_WAKEUP_PIN5_LOW                 \
  (PWR_WAKEUP_PIN_ID5 << PWR_WAKEUP_PIN_ID_POS) | (PWR_WAKEUP_LOW << PWR_WAKEUP_EDGE_POS) | \
  (PWR_WAKEUP_NOPULL << PWR_WAKEUP_PULL_POS)
#define PWR_WAKEUP_PIN4_LOW                 \
  (PWR_WAKEUP_PIN_ID4 << PWR_WAKEUP_PIN_ID_POS) | (PWR_WAKEUP_LOW << PWR_WAKEUP_EDGE_POS) | \
  (PWR_WAKEUP_NOPULL << PWR_WAKEUP_PULL_POS)
#define PWR_WAKEUP_PIN3_LOW                 \
  (PWR_WAKEUP_PIN_ID3 << PWR_WAKEUP_PIN_ID_POS) | (PWR_WAKEUP_LOW << PWR_WAKEUP_EDGE_POS) | \
  (PWR_WAKEUP_NOPULL << PWR_WAKEUP_PULL_POS)
#define PWR_WAKEUP_PIN2_LOW                 \
  (PWR_WAKEUP_PIN_ID2 << PWR_WAKEUP_PIN_ID_POS) | (PWR_WAKEUP_LOW << PWR_WAKEUP_EDGE_POS) | \
  (PWR_WAKEUP_NOPULL << PWR_WAKEUP_PULL_POS)
#define PWR_WAKEUP_PIN1_LOW                 \
  (PWR_WAKEUP_PIN_ID1 << PWR_WAKEUP_PIN_ID_POS) | (PWR_WAKEUP_LOW << ) | \
  (PWR_WAKEUP_NOPULL << PWR_WAKEUP_PULL_POS)

#define PWR_WAKEUP_PIN6               PWR_WAKEUP_PIN6_HIGH
#define PWR_WAKEUP_PIN5               PWR_WAKEUP_PIN5_HIGH
#define PWR_WAKEUP_PIN4               PWR_WAKEUP_PIN4_HIGH
#define PWR_WAKEUP_PIN3               PWR_WAKEUP_PIN3_HIGH
#define PWR_WAKEUP_PIN2               PWR_WAKEUP_PIN2_HIGH
#define PWR_WAKEUP_PIN1               PWR_WAKEUP_PIN1_HIGH

#define IS_PWR_WAKEUP_PIN_EDGE(__EDGE__)  (((__EDGE__)  == PWR_WAKEUP_HIGH)        || \
                                           ((__EDGE__)  == PWR_WAKEUP_LOW)            )

#define IS_PWR_WAKEUP_PIN_CONFIG(__CFG__)  (((__CFG__) == PWR_WAKEUP_NOPULL)       || \
                                            ((__CFG__) == PWR_WAKEUP_PULLUP)       || \
                                            ((__CFG__) == PWR_WAKEUP_PULLDOWN)        )


#define IS_PWR_WAKEUP_PIN_ID(__VALUE__)            (((__VALUE__)  == PWR_WAKEUP_PIN_ID1)        || \
                                                    ((__VALUE__)  == PWR_WAKEUP_PIN_ID2)        || \
                                                    ((__VALUE__)  == PWR_WAKEUP_PIN_ID3)        || \
                                                    ((__VALUE__)  == PWR_WAKEUP_PIN_ID4)        || \
                                                    ((__VALUE__)  == PWR_WAKEUP_PIN_ID5)        || \
                                                    ((__VALUE__)  == PWR_WAKEUP_PIN_ID6)           )

/**
  * @}
  */

/** @defgroup PWR_EXTI_Mode PWR EXTI Mode
  * @{
  */
#define PWR_EXTI_MODE_NORMAL               ((uint32_t)0x00000000U)  /*!< Basic mode used, no interruption                                   */
#define PWR_EXTI_MODE_IT_RISING            ((uint32_t)0x00010001U)  /*!< External Interrupt Mode with Rising edge trigger detection         */
#define PWR_EXTI_MODE_IT_FALLING           ((uint32_t)0x00010002U)  /*!< External Interrupt Mode with Falling edge trigger detection        */
#define PWR_EXTI_MODE_IT_RISING_FALLING    ((uint32_t)0x00010003U)  /*!< External Interrupt Mode with Rising/Falling edge trigger detection */


#define IS_PWR_EXTI_MODE(MODE) (((MODE) == PWR_EXTI_MODE_IT_RISING)         || ((MODE) == PWR_EXTI_MODE_IT_FALLING) || \
                                ((MODE) == PWR_EXTI_MODE_IT_RISING_FALLING) || ((MODE) == PWR_EXTI_MODE_NORMAL) )

#define IS_AN_INTERRUPT_PWR_EXTI_MODE(MODE) (((MODE) == PWR_EXTI_MODE_IT_RISING)   || \
                                             ((MODE) == PWR_EXTI_MODE_IT_FALLING)  || \
                                             ((MODE) == PWR_EXTI_MODE_IT_RISING_FALLING)  )

#define PWR_PVD_MODE_NORMAL                              PWR_EXTI_MODE_NORMAL
#define PWR_PVD_MODE_IT_RISING                           PWR_EXTI_MODE_IT_RISING
#define PWR_PVD_MODE_IT_FALLING                          PWR_EXTI_MODE_IT_FALLING
#define PWR_PVD_MODE_IT_RISING_FALLING                   PWR_EXTI_MODE_IT_RISING_FALLING


#define IS_PWR_PVD_MODE(MODE) IS_PWR_EXTI_MODE(MODE)
#define IS_AN_INTERRUPT_PWR_PVD_MODE(MODE)  IS_AN_INTERRUPT_PWR_EXTI_MODE(MODE)
/**
  * @}
  */

/**
  * @brief  indicate voltage range where VDD is
  * @retval None
  */
#define PWR_VDD_BELOW_THRESHOLD                 1U
#define PWR_VDD_ABOVE_OR_EQUAL_THRESHOLD        2U
#define PWR_NO_VDD_MEASUREMENT_AVAILABLE        15U

/** @defgroup PWR_Access_filtering PWR Access filtering (non shareable then wio resource)
  * @{
  */
#define NS_RESOURCE_POS              0U

#define NON_SHAREABLE_RESSOURCE_0    (1U << (0U + NS_RESOURCE_POS))   /*!< non shareable Resource1 access control  */
#define NON_SHAREABLE_RESSOURCE_1    (1U << (1U + NS_RESOURCE_POS))   /*!< non shareable Resource2 access control  */
#define NON_SHAREABLE_RESSOURCE_2    (1U << (2U + NS_RESOURCE_POS))   /*!< non shareable Resource3 access control  */
#define NON_SHAREABLE_RESSOURCE_3    (1U << (3U + NS_RESOURCE_POS))   /*!< non shareable Resource4 access control  */
#define NON_SHAREABLE_RESSOURCE_4    (1U << (4U + NS_RESOURCE_POS))   /*!< non shareable Resource5 access control  */
#define NON_SHAREABLE_RESSOURCE_5    (1U << (5U + NS_RESOURCE_POS))   /*!< non shareable Resource5 access control  */
#define NON_SHAREABLE_RESSOURCE_6    (1U << (6U + NS_RESOURCE_POS))   /*!< non shareable Resource5 access control  */

#define NON_SHAREABLE_RESOURCE_NB    7U


#define NS_RESOURCE_ATTR_PRIV_SELECT          0x01000000U
#define NS_RESOURCE_ATTR_SEC_SELECT           0x02000000U
#define NS_RESOURCE_ATTR_CID_STATIC_SELECT    0x20000000U
#define NS_RESOURCE_CID_DISABLE               0x80000000U

#define NS_RESOURCE_PRIV_VAL_POS             0
#define NS_RESOURCE_PRIV                     (NS_RESOURCE_ATTR_PRIV_SELECT | (1U<<NS_RESOURCE_PRIV_VAL_POS)) /*!< Resource is privileged   */
#define NS_RESOURCE_NPRIV                    (NS_RESOURCE_ATTR_PRIV_SELECT)                                  /*!< Resource is unprivileged */

#if defined (CORTEX_IN_SECURE_STATE)
#define NS_RESOURCE_SEC_VAL_POS              1
#define NS_RESOURCE_SEC                      (NS_RESOURCE_ATTR_SEC_SELECT | (1U<<NS_RESOURCE_SEC_VAL_POS)) /*!< Resource is secure       */
#define NS_RESOURCE_NSEC                     (NS_RESOURCE_ATTR_SEC_SELECT)                                 /*!< Resource is non-secure   */
#endif /* __ARM_SECURE_STATE */

#define NS_RESOURCE_CID_STATIC_0     (NS_RESOURCE_ATTR_CID_STATIC_SELECT | (0<<PWR_R0CIDCFGR_SCID_Pos))   /*!< Enable CID filtering (static mode) and give pin control  to CID0 */
#define NS_RESOURCE_CID_STATIC_1     (NS_RESOURCE_ATTR_CID_STATIC_SELECT | (1<<PWR_R0CIDCFGR_SCID_Pos))   /*!< Enable CID filtering (static mode) and give pin control  to CID1 */
#define NS_RESOURCE_CID_STATIC_2     (NS_RESOURCE_ATTR_CID_STATIC_SELECT | (2<<PWR_R0CIDCFGR_SCID_Pos))   /*!< Enable CID filtering (static mode) and give pin control  to CID2 */
#define NS_RESOURCE_CID_STATIC_3     (NS_RESOURCE_ATTR_CID_STATIC_SELECT | (3<<PWR_R0CIDCFGR_SCID_Pos))   /*!< Enable CID filtering (static mode) and give pin control  to CID3 */
#define NS_RESOURCE_CID_STATIC_4     (NS_RESOURCE_ATTR_CID_STATIC_SELECT | (4<<PWR_R0CIDCFGR_SCID_Pos))   /*!< Enable CID filtering (static mode) and give pin control  to CID4 */
#define NS_RESOURCE_CID_STATIC_5     (NS_RESOURCE_ATTR_CID_STATIC_SELECT | (5<<PWR_R0CIDCFGR_SCID_Pos))   /*!< Enable CID filtering (static mode) and give pin control  to CID5 */
#define NS_RESOURCE_CID_STATIC_6     (NS_RESOURCE_ATTR_CID_STATIC_SELECT | (6<<PWR_R0CIDCFGR_SCID_Pos))   /*!< Enable CID filtering (static mode) and give pin control  to CID6 */
#define NS_RESOURCE_CID_STATIC_7     (NS_RESOURCE_ATTR_CID_STATIC_SELECT | (7<<PWR_R0CIDCFGR_SCID_Pos))   /*!< Enable CID filtering (static mode) and give pin control  to CID7 */


#define WIO_RESOURCE_POS   NON_SHAREABLE_RESOURCE_NB

#define WIO_RESOURCE_0     (1U << (0U + WIO_RESOURCE_POS))   /*!< shareable wake-up IO  Resource1 access control  */
#define WIO_RESOURCE_1     (1U << (1U + WIO_RESOURCE_POS))   /*!< shareable wake-up IO  Resource2 access control  */
#define WIO_RESOURCE_2     (1U << (2U + WIO_RESOURCE_POS))   /*!< shareable wake-up IO  Resource3 access control  */
#define WIO_RESOURCE_3     (1U << (3U + WIO_RESOURCE_POS))   /*!< shareable wake-up IO  Resource4 access control  */
#define WIO_RESOURCE_4     (1U << (4U + WIO_RESOURCE_POS))   /*!< shareable wake-up IO  Resource5 access control  */
#define WIO_RESOURCE_5     (1U << (5U + WIO_RESOURCE_POS))   /*!< shareable wake-up IO  Resource5 access control  */


#define WIO_PIN_ATTR_PRIV_SELECT          0x01000000U
#define WIO_PIN_ATTR_SEC_SELECT           0x02000000U
#define WIO_PIN_ATTR_CID_SHARED_MASK      (PWR_WIO1CIDCFGR_SEMWLC0 | PWR_WIO1CIDCFGR_SEMWLC1 | \
                                           PWR_WIO1CIDCFGR_SEMWLC2 | PWR_WIO1CIDCFGR_SEMWLC3 | \
                                           PWR_WIO1CIDCFGR_SEMWLC4 | PWR_WIO1CIDCFGR_SEMWLC5 | \
                                           PWR_WIO1CIDCFGR_SEMWLC6 | PWR_WIO1CIDCFGR_SEMWLC7 )
#define WIO_PIN_ATTR_CID_SHARED_SELECT    0x10000000U
#define WIO_PIN_ATTR_CID_STATIC_SELECT    0x20000000U
#define WIO_PIN_CID_DISABLE               0x80000000U

#define WIO_PIN_PRIV_VAL_POS             0
#define WIO_PIN_PRIV                     (WIO_PIN_ATTR_PRIV_SELECT | (1U<<WIO_PIN_PRIV_VAL_POS))     /*!< Pin is privileged             */
#define WIO_PIN_NPRIV                    (WIO_PIN_ATTR_PRIV_SELECT)                                  /*!< Pin is unprivileged           */

#if defined (CORTEX_IN_SECURE_STATE)
#define WIO_PIN_SEC_VAL_POS              1
#define WIO_PIN_SEC                      (WIO_PIN_ATTR_SEC_SELECT | (1U<<WIO_PIN_SEC_VAL_POS))      /*!< Pin is secure                 */
#define WIO_PIN_NSEC                     (WIO_PIN_ATTR_SEC_SELECT)              /*!< Pin is non-secure             */
#endif /* __ARM_SECURE_STATE */

#define WIO_PIN_CID_STATIC_0        (WIO_PIN_ATTR_CID_STATIC_SELECT | (0<<PWR_WIO1CIDCFGR_SCID_Pos))   /*!< Enable CID filtering (static mode) and give pin control  to CID0 */
#define WIO_PIN_CID_STATIC_1        (WIO_PIN_ATTR_CID_STATIC_SELECT | (1<<PWR_WIO1CIDCFGR_SCID_Pos))   /*!< Enable CID filtering (static mode) and give pin control  to CID1 */
#define WIO_PIN_CID_STATIC_2        (WIO_PIN_ATTR_CID_STATIC_SELECT | (2<<PWR_WIO1CIDCFGR_SCID_Pos))   /*!< Enable CID filtering (static mode) and give pin control  to CID2 */
#define WIO_PIN_CID_STATIC_3        (WIO_PIN_ATTR_CID_STATIC_SELECT | (3<<PWR_WIO1CIDCFGR_SCID_Pos))   /*!< Enable CID filtering (static mode) and give pin control  to CID3 */
#define WIO_PIN_CID_STATIC_4        (WIO_PIN_ATTR_CID_STATIC_SELECT | (4<<PWR_WIO1CIDCFGR_SCID_Pos))   /*!< Enable CID filtering (static mode) and give pin control  to CID4 */
#define WIO_PIN_CID_STATIC_5        (WIO_PIN_ATTR_CID_STATIC_SELECT | (5<<PWR_WIO1CIDCFGR_SCID_Pos))   /*!< Enable CID filtering (static mode) and give pin control  to CID5 */
#define WIO_PIN_CID_STATIC_6        (WIO_PIN_ATTR_CID_STATIC_SELECT | (6<<PWR_WIO1CIDCFGR_SCID_Pos))   /*!< Enable CID filtering (static mode) and give pin control  to CID6 */
#define WIO_PIN_CID_STATIC_7        (WIO_PIN_ATTR_CID_STATIC_SELECT | (7<<PWR_WIO1CIDCFGR_SCID_Pos))   /*!< Enable CID filtering (static mode) and give pin control  to CID7 */

#define WIO_PIN_CID_SHARED_0        (WIO_PIN_ATTR_CID_SHARED_SELECT | PWR_WIO1CIDCFGR_SEMWLC0)      /*!< Enable CID filtering (shared mode) and give pin control  to CID0 */
#define WIO_PIN_CID_SHARED_1        (WIO_PIN_ATTR_CID_SHARED_SELECT | PWR_WIO1CIDCFGR_SEMWLC1)      /*!< Enable CID filtering (shared mode) and give pin control  to CID1 */
#define WIO_PIN_CID_SHARED_2        (WIO_PIN_ATTR_CID_SHARED_SELECT | PWR_WIO1CIDCFGR_SEMWLC2)      /*!< Enable CID filtering (shared mode) and give pin control  to CID2 */
#define WIO_PIN_CID_SHARED_3        (WIO_PIN_ATTR_CID_SHARED_SELECT | PWR_WIO1CIDCFGR_SEMWLC3)      /*!< Enable CID filtering (shared mode) and give pin control  to CID3 */
#define WIO_PIN_CID_SHARED_4        (WIO_PIN_ATTR_CID_SHARED_SELECT | PWR_WIO1CIDCFGR_SEMWLC4)      /*!< Enable CID filtering (shared mode) and give pin control  to CID4 */
#define WIO_PIN_CID_SHARED_5        (WIO_PIN_ATTR_CID_SHARED_SELECT | PWR_WIO1CIDCFGR_SEMWLC5)      /*!< Enable CID filtering (shared mode) and give pin control  to CID5 */
#define WIO_PIN_CID_SHARED_6        (WIO_PIN_ATTR_CID_SHARED_SELECT | PWR_WIO1CIDCFGR_SEMWLC6)      /*!< Enable CID filtering (shared mode) and give pin control  to CID6 */
#define WIO_PIN_CID_SHARED_7        (WIO_PIN_ATTR_CID_SHARED_SELECT | PWR_WIO1CIDCFGR_SEMWLC7)      /*!< Enable CID filtering (shared mode) and give pin control  to CID7 */

#define SHAREABLE_RESOURCE_NB        6U
/**
  * @}
  */


/** @defgroup PWR_Regulator_state_in_STOP_mode PWR Regulator state in STOP_mode
  * @{
  */
#define PWR_REGULATOR_LP_OFF                        0U
#define PWR_REGULATOR_LP_ON_LV_OFF                  1U
#define PWR_REGULATOR_LP_ON_LV_ON                   3U

#define IS_PWR_STOP_MODE_REGULATOR(__REGULATOR__)     (((__REGULATOR__) == PWR_REGULATOR_LP_OFF)  || \
                                                       ((__REGULATOR__) == PWR_REGULATOR_LP_ON_LV_OFF) || \
                                                       ((__REGULATOR__) == PWR_REGULATOR_LP_ON_LV_ON))
/**
  * @}
  */


/** @defgroup PWR_CPU_state PWR CPU state
  * @{
  */
#define PWR_CPU_CRUN                    1U
#define PWR_CPU_CSLEEP                  2U
#define PWR_CPU_CSTOP                   3U
#define PWR_CPU_CRESET                  0U
/**
  * @}
  */

/** @defgroup PWR_D1_state PWR D1 state
  * @{
  */
/* CPU1 is in CRUN or CSLEEP */
#define PWR_D1_DRUN                    0U
/* CPU1 is in CSTOP (D1 clock stalled) with no additional power saving request set */
#define PWR_D1_DSTOP1                  1U
/* CPU1 is in CSTOP (D1 clock stalled) with LPwr power saving request set */
#define PWR_D1_DSTOP2                  2U
/* CPU1 is in CSTOP (D1 clock stalled) with LPwr/LVoltage power saving request set*/
#define PWR_D1_DSTOP3                  3U
/* D1 is not powered */
#define PWR_D1_DSTANDBY                4U
/**
  * @}
  */

/** @defgroup PWR_D2_state PWR D2 state
  * @{
  */
/* CPU2 is CRUN or CSLEEP */
#define PWR_D2_RUN                     0U
/* CPU1/CPU2 are in CSTOP (D1/D2 clock stalled) with no additional power saving request set*/
#define PWR_D2_STOP                    1U
/* CPU1/CPU2 are in CSTOP (D1/D2 clock stalled) with no LPwr power saving request set*/
#define PWR_D2_LP_STOP                 2U
/* D1 not powered, CPU2 is in CSTOP (D2 clock stalled) with LPwr/LVotage power saving request set*/
#define PWR_D2_LPLVSTOP2               3U
/* D2/D1 not powered (D3 may be powered or not according to CPU3 activity)*/
#define PWR_D2_STANDBY                 4U
/* system is on VBAT */
#define PWR_D2_VBAT                    5U
/**
  * @}
  */

/** @defgroup PWR_D3_state PWR D3 state
  * @{
  */
#define PWR_D3_SRUN1                   0U   /* all CPUS are in CRUN or CSLEEP*/
#define PWR_D3_SRUN2                   1U   /* CPU3 is in CRUN or CSLEEP, D2 is in STOP  */
#define PWR_D3_SRUN3                   2U   /* CPU3 is in CRUN or CSLEEP, D2 is in STOP-LP or STOP-VP or standby*/
#define PWR_D3_SSTOP1                  3U   /* CPU3 is in CSTOP, D2 is in STOP  */
#define PWR_D3_SSTOP2                  4U   /* CPU3 is in CSTOP, D2 is in STOP-LP or STOP-LV or standby */
#define PWR_D3_SSTANDBY                5U   /* D3/D2/D1 domain are not powered */
/**
  * @}
  */


/** @defgroup PWR_SLEEP_mode_entry PWR SLEEP mode entry
  * @{
  */

#define PWR_SLEEPENTRY_WFI              ((uint8_t)0x01)
#define PWR_SLEEPENTRY_WFE              ((uint8_t)0x02)
#define IS_PWR_SLEEP_ENTRY(__ENTRY__)   (((__ENTRY__) == PWR_SLEEPENTRY_WFI) || ((__ENTRY__) == PWR_SLEEPENTRY_WFE))
/**
  * @}
  */


/** @defgroup PWR_STOP_mode_entry PWR STOP mode entry
  * @{
  */
#define PWR_STOPENTRY_WFI               ((uint8_t)0x01)
#define PWR_STOPENTRY_WFE               ((uint8_t)0x02)

#define IS_PWR_STOP_ENTRY(__ENTRY__)    (((__ENTRY__) == PWR_STOPENTRY_WFI) || ((__ENTRY__) == PWR_STOPENTRY_WFE))
/**
  * @}
  */

/** @defgroup PWR_STANDBYType PWR STANDBYType
  * @{
  */
#define PWR_STANDBY_1               ((uint8_t)0x01)
#define PWR_STANDBY_2               ((uint8_t)0x02)

#define IS_PWR_STANDBY_TYPE(__TYPE__)    (((__TYPE__) == PWR_STANDBY_1) || ((__TYPE__) == PWR_STANDBY_2))

/**
  * @}
  */

/** @defgroup PWR_SYSTEM_STANDBY_REQUEST  PWR SYSTEM STANDBY REQUEST
  * @{
  */

#ifdef CORE_CM0PLUS
#define  SYSTEM_STANDBY_FLAG                            PWR_CPU3CR_SBF_D3
#define  SYSTEM_STANDBY_REQUEST                         PWR_D3CR_PDDS_D3
#define  SYSTEM_STANDBY_FLAGS_CLEAR                     PWR_CPU3CR_CSSF
#endif /* CORE_CM0PLUS */
#ifdef CORE_CM33
#define  SYSTEM_STANDBY_FLAG                            PWR_CPU2CR_SBF
#define  SYSTEM_STANDBY_REQUEST                         PWR_CPU2CR_PDDS_D2
#define  SYSTEM_STANDBY_FLAGS_CLEAR                     PWR_CPU2CR_CSSF
#endif /* CORE_CM33 */
#ifdef CORE_CA35
#define  SYSTEM_STANDBY_FLAG                            PWR_CPU1CR_SBF
#define  SYSTEM_STANDBY_REQUEST                         PWR_CPU1CR_PDDS_D1
#define  DOMAIN2_STANDBY_REQUEST                        PWR_CPU1CR_PDDS_D2
#define  SYSTEM_STANDBY_FLAGS_CLEAR                     PWR_CPU1CR_CSSF
#endif /* CORE_CA35 */

/**
  * @}
  */


/** @defgroup PWR_Flag PWR Flag
  * @{
  */
#define PWR_FLAG_VDDGPURDY         (0x00U)   /* to check readiness of GPU power domain       */
#define PWR_FLAG_D3RDY             (0x01U)   /* to check readiness of D3 domain supply       */
#define PWR_FLAG_PVDO              (0x03U)   /* to check if VDD  is lower than PVD threshold */
#define PWR_FLAG_VBATL             (0x04U)   /* to check if VBAT is equal or lower  than VBAT low  threshold */
#define PWR_FLAG_VBATH             (0x05U)   /* to check if VBAT is equal or higher than VBAT high threshold */
#define PWR_FLAG_TEMPL             (0x06U)   /* to check if TEMP is equal or lower  than TEMP low  threshold */
#define PWR_FLAG_TEMPH             (0x07U)   /* to check if TEMP is equal or higher than TEMP high threshold */
#define PWR_FLAG_USB               (0x08U)   /* to check readiness of  USB supply */
#define PWR_FLAG_VDDCOREL          (0x09U)   /* to check if VDDcore is equal or lower than VDDcore low threshold */
#define PWR_FLAG_VDDCOREH          (0x0AU)   /* to check if VDDcore is equal or higher than VDDcore high threshold */
#define PWR_FLAG_VDDCPUL           (0x0BU)   /* to check if VDDcpu is equal or lower than VDDcpu low threshold */
#define PWR_FLAG_VDDCPUH           (0x0CU)   /* to check if VDDcpu is equal or higher than VDDcpu high threshold */
#define PWR_FLAG_VB                (0x0DU)   /* to check if system has been in VBAT mode */
#define PWR_FLAG_SB_D3             (0x0EU)   /* to check if D3 domain  has been in standby */
#define PWR_FLAG_SB_D2             (0x10U)   /* to check if D2domain  has been in standby */
#define PWR_FLAG_SB_D1             (0x11U)   /* to check if D1 domain  has been in standby */
#if !defined (CORE_CM0PLUS)
#define PWR_FLAG_SB                (0x15U)   /* to check if system  has been in standby */
#define PWR_FLAG_STOP              (0x16U)   /* to check if system  has been in stop */
#endif /* CORE_CM0PLUS */

/**
  * @}
  */
/**
  * @}
  */

/* Exported macro ------------------------------------------------------------*/

/** @defgroup PWR_Exported_Macro PWR Exported Macro
  * @{
  */
/* Check the parameters */
#define IS_NS_RESOURCE(__RESOURCE__)       (                                                 \
    ((__RESOURCE__) == NON_SHAREABLE_RESSOURCE_0) || ((__RESOURCE__) == NON_SHAREABLE_RESSOURCE_1)|| \
    ((__RESOURCE__) == NON_SHAREABLE_RESSOURCE_2) || ((__RESOURCE__) == NON_SHAREABLE_RESSOURCE_3)|| \
    ((__RESOURCE__) == NON_SHAREABLE_RESSOURCE_4) || ((__RESOURCE__) == NON_SHAREABLE_RESSOURCE_5)|| \
    ((__RESOURCE__) == NON_SHAREABLE_RESSOURCE_6))

#if defined (CORTEX_IN_SECURE_STATE)
#define IS_NS_RESOURCE_ATTRIBUTES(__ATTRIBUTES__)   (\
                                                     (((__ATTRIBUTES__) & NS_RESOURCE_ATTR_CID_STATIC_SELECT ) == \
                                                      NS_RESOURCE_ATTR_CID_STATIC_SELECT)    ||\
                                                     (((__ATTRIBUTES__) & NS_RESOURCE_CID_DISABLE            ) == \
                                                      NS_RESOURCE_CID_DISABLE)               ||\
                                                     (((__ATTRIBUTES__) & NS_RESOURCE_ATTR_SEC_SELECT )        == \
                                                      NS_RESOURCE_ATTR_SEC_SELECT)           ||\
                                                     (((__ATTRIBUTES__) & NS_RESOURCE_ATTR_PRIV_SELECT)        == \
                                                      NS_RESOURCE_ATTR_PRIV_SELECT)            )
#else
#define IS_NS_RESOURCE_ATTRIBUTES(__ATTRIBUTES__)   (\
                                                     (((__ATTRIBUTES__) & NS_RESOURCE_ATTR_CID_STATIC_SELECT ) == \
                                                      NS_RESOURCE_ATTR_CID_STATIC_SELECT)    ||\
                                                     (((__ATTRIBUTES__) & NS_RESOURCE_CID_DISABLE            ) == \
                                                      NS_RESOURCE_CID_DISABLE)               ||\
                                                     (((__ATTRIBUTES__) & NS_RESOURCE_ATTR_PRIV_SELECT)        == \
                                                      NS_RESOURCE_ATTR_PRIV_SELECT)            )
#endif /* CORTEX_IN_SECURE_STATE */

#define IS_WIO_RESOURCE(__RESOURCE__)          (                                   \
    ((__RESOURCE__) == WIO_RESOURCE_0) || ((__RESOURCE__) == WIO_RESOURCE_1)|| \
    ((__RESOURCE__) == WIO_RESOURCE_2) || ((__RESOURCE__) == WIO_RESOURCE_3)|| \
    ((__RESOURCE__) == WIO_RESOURCE_4) || ((__RESOURCE__) == WIO_RESOURCE_5)   )

#if defined (CORTEX_IN_SECURE_STATE)
#define IS_WIO_PIN_ATTRIBUTES(__ATTRIBUTES__)   ((((__ATTRIBUTES__) & WIO_PIN_ATTR_CID_SHARED_SELECT ) == \
                                                  WIO_PIN_ATTR_CID_SHARED_SELECT)    ||\
                                                 (((__ATTRIBUTES__) & WIO_PIN_ATTR_CID_STATIC_SELECT ) == \
                                                  WIO_PIN_ATTR_CID_STATIC_SELECT)    ||\
                                                 (((__ATTRIBUTES__) & WIO_PIN_CID_DISABLE            ) == \
                                                  WIO_PIN_CID_DISABLE)               ||\
                                                 (((__ATTRIBUTES__) & WIO_PIN_ATTR_SEC_SELECT )        == \
                                                  WIO_PIN_ATTR_SEC_SELECT)           ||\
                                                 (((__ATTRIBUTES__) & WIO_PIN_ATTR_PRIV_SELECT)        == \
                                                  WIO_PIN_ATTR_PRIV_SELECT)            )
#else
#define IS_WIO_PIN_ATTRIBUTES(__ATTRIBUTES__)   ((((__ATTRIBUTES__) & WIO_PIN_ATTR_CID_SHARED_SELECT ) == \
                                                  WIO_PIN_ATTR_CID_SHARED_SELECT)    ||\
                                                 (((__ATTRIBUTES__) & WIO_PIN_ATTR_CID_STATIC_SELECT ) == \
                                                  WIO_PIN_ATTR_CID_STATIC_SELECT)    ||\
                                                 (((__ATTRIBUTES__) & WIO_PIN_CID_DISABLE            ) == \
                                                  WIO_PIN_CID_DISABLE)               ||\
                                                 (((__ATTRIBUTES__) & WIO_PIN_ATTR_PRIV_SELECT)        == \
                                                  WIO_PIN_ATTR_PRIV_SELECT)            )
#endif /* CORTEX_IN_SECURE_STATE */


#define IS_PWR_ITEMS(__ITEM__)           (IS_WIO_RESOURCE(__ITEM__) || IS_NS_RESOURCE(__ITEM__))


#if defined(PWR_D3CR_D3RDY)
#define __HAL_PWR_GET_COMMON_FLAG(__FLAG__) ( \
                                              ((__FLAG__) == PWR_FLAG_VDDGPURDY)?((PWR->CR12 & PWR_CR12_VDDGPURDY) \
                                                  == PWR_CR12_VDDGPURDY) :   \
                                              ((__FLAG__) == PWR_FLAG_PVDO)     ?((PWR->CR3  & PWR_CR3_PVDO) \
                                                  == PWR_CR3_PVDO)      :    \
                                              ((__FLAG__) == PWR_FLAG_VBATL)    ?((PWR->CR2  & PWR_CR2_VBATL) \
                                                  == PWR_CR2_VBATL)     :    \
                                              ((__FLAG__) == PWR_FLAG_VBATH)    ?((PWR->CR2  & PWR_CR2_VBATH) \
                                                  == PWR_CR2_VBATH)     :    \
                                              ((__FLAG__) == PWR_FLAG_TEMPL)    ?((PWR->CR2  & PWR_CR2_TEMPL)    \
                                                  == PWR_CR2_TEMPL)     :    \
                                              ((__FLAG__) == PWR_FLAG_TEMPH)    ?((PWR->CR2  & PWR_CR2_TEMPH)  \
                                                  == PWR_CR2_TEMPH)     :    \
                                              ((__FLAG__) == PWR_FLAG_VDDCOREL) ?((PWR->CR5  & PWR_CR5_VCOREL)  \
                                                  == PWR_CR5_VCOREL)    :    \
                                              ((__FLAG__) == PWR_FLAG_VDDCOREH) ?((PWR->CR5  & PWR_CR5_VCOREH)   \
                                                  == PWR_CR5_VCOREH)    :    \
                                              ((__FLAG__) == PWR_FLAG_VDDCPUL)  ?((PWR->CR6  & PWR_CR6_VCPUL) \
                                                  == PWR_CR6_VCPUL)     :    \
                                              ((__FLAG__) == PWR_FLAG_VDDCPUH)  ?((PWR->CR6  & PWR_CR6_VCPUH)   \
                                                  == PWR_CR6_VCPUH)     :    \
                                              ((PWR->D3CR & PWR_D3CR_D3RDY)     == PWR_D3CR_D3RDY))
#else
#define __HAL_PWR_GET_COMMON_FLAG(__FLAG__) ( \
                                              ((__FLAG__) == PWR_FLAG_PVDO)    ?((PWR->CR3  & PWR_CR3_PVDO)  \
                                                  == PWR_CR3_PVDO)      :    \
                                              ((__FLAG__) == PWR_FLAG_VBATL)   ?((PWR->CR2  & PWR_CR2_VBATL) \
                                                  == PWR_CR2_VBATL)     :    \
                                              ((__FLAG__) == PWR_FLAG_VBATH)   ?((PWR->CR2  & PWR_CR2_VBATH) \
                                                  == PWR_CR2_VBATH)     :    \
                                              ((__FLAG__) == PWR_FLAG_TEMPL)   ?((PWR->CR2  & PWR_CR2_TEMPL) \
                                                  == PWR_CR2_TEMPL)     :    \
                                              ((__FLAG__) == PWR_FLAG_TEMPH)   ?((PWR->CR2  & PWR_CR2_TEMPH) \
                                                  == PWR_CR2_TEMPH)     : 0U )
#endif /* defined(PWR_D3CR_D3RDY) */

#if defined(PWR_CPU3CR_VBF)
#if defined (CORE_CA35)
#define __HAL_PWR_GET_FLAG(__FLAG__) ( \
                                       ((__FLAG__) == PWR_FLAG_VB)        ?((PWR->CPU1CR & PWR_CPU1CR_VBF)    \
                                                                            == PWR_CPU1CR_VBF)    :        \
                                       ((__FLAG__) == PWR_FLAG_SB_D3)     ?((PWR->CPU1CR & PWR_CPU1CR_SBF_D3)  \
                                                                            == PWR_CPU1CR_SBF_D3) :        \
                                       ((__FLAG__) == PWR_FLAG_SB_D1)     ?((PWR->CPU1CR & PWR_CPU1CR_SBF_D1)  \
                                                                            == PWR_CPU1CR_SBF_D1) :        \
                                       ((__FLAG__) == PWR_FLAG_SB)        ?((PWR->CPU1CR & PWR_CPU1CR_SBF)  \
                                                                            == PWR_CPU1CR_SBF)    :        \
                                       ((__FLAG__) == PWR_FLAG_STOP)      ?((PWR->CPU1CR & PWR_CPU1CR_STOPF)  \
                                                                            == PWR_CPU1CR_STOPF)  :        \
                                       (__HAL_PWR_GET_COMMON_FLAG(__FLAG__)))
#elif defined (CORE_CM33)
#define __HAL_PWR_GET_FLAG(__FLAG__) ( \
                                       ((__FLAG__) == PWR_FLAG_VB)        ?((PWR->CPU2CR & PWR_CPU2CR_VBF)    \
                                                                            == PWR_CPU2CR_VBF)    :        \
                                       ((__FLAG__) == PWR_FLAG_SB_D3)     ?((PWR->CPU2CR & PWR_CPU2CR_SBF_D3)  \
                                                                            == PWR_CPU2CR_SBF_D3) :        \
                                       ((__FLAG__) == PWR_FLAG_SB_D2)     ?((PWR->CPU2CR & PWR_CPU2CR_SBF_D2)  \
                                                                            == PWR_CPU2CR_SBF_D2) :        \
                                       ((__FLAG__) == PWR_FLAG_SB)        ?((PWR->CPU2CR & PWR_CPU2CR_SBF)      \
                                                                            == PWR_CPU2CR_SBF)    :        \
                                       ((__FLAG__) == PWR_FLAG_STOP)      ?((PWR->CPU2CR & PWR_CPU2CR_STOPF)    \
                                                                            == PWR_CPU2CR_STOPF)  :        \
                                       (__HAL_PWR_GET_COMMON_FLAG(__FLAG__)))
#elif defined (CORE_CM0PLUS)
#define __HAL_PWR_GET_FLAG(__FLAG__) ( \
                                       ((__FLAG__) == PWR_FLAG_VB)        ?((PWR->CPU3CR & PWR_CPU3CR_VBF)    \
                                                                            == PWR_CPU3CR_VBF)    :        \
                                       ((__FLAG__) == PWR_FLAG_SB_D3)     ?((PWR->CPU3CR & PWR_CPU3CR_SBF_D3)  \
                                                                            == PWR_CPU3CR_SBF_D3) :        \
                                       (__HAL_PWR_GET_COMMON_FLAG(__FLAG__)))
#endif /* CORE_CA35 */
#else
#if defined (CORE_CA35)
#define __HAL_PWR_GET_FLAG(__FLAG__) ( \
                                       ((__FLAG__) == PWR_FLAG_VB)        ?((PWR->CPU1CR & PWR_CPU1CR_VBF)    \
                                                                            == PWR_CPU1CR_VBF)    :        \
                                       ((__FLAG__) == PWR_FLAG_SB_D1)     ?((PWR->CPU1CR & PWR_CPU1CR_SBF_D1)  \
                                                                            == PWR_CPU1CR_SBF_D1) :        \
                                       ((__FLAG__) == PWR_FLAG_SB)        ?((PWR->CPU1CR & PWR_CPU1CR_SBF) \
                                                                            == PWR_CPU1CR_SBF)    :        \
                                       ((__FLAG__) == PWR_FLAG_STOP)      ?((PWR->CPU1CR & PWR_CPU1CR_STOPF) \
                                                                            == PWR_CPU1CR_STOPF)  :        \
                                       (__HAL_PWR_GET_COMMON_FLAG(__FLAG__)))
#elif defined (CORE_CM33)
#define __HAL_PWR_GET_FLAG(__FLAG__) ( \
                                       ((__FLAG__) == PWR_FLAG_VB)        ?((PWR->CPU2CR & PWR_CPU2CR_VBF)           \
                                                                            == PWR_CPU2CR_VBF)    :        \
                                       ((__FLAG__) == PWR_FLAG_SB_D2)     ?((PWR->CPU2CR & PWR_CPU2CR_SBF_D2)        \
                                                                            == PWR_CPU2CR_SBF_D2) :        \
                                       ((__FLAG__) == PWR_FLAG_SB)        ?((PWR->CPU2CR & PWR_CPU2CR_SBF)           \
                                                                            == PWR_CPU2CR_SBF)    :        \
                                       ((__FLAG__) == PWR_FLAG_STOP)      ?((PWR->CPU2CR & PWR_CPU2CR_STOPF)         \
                                                                            == PWR_CPU2CR_STOPF)  :        \
                                       (__HAL_PWR_GET_COMMON_FLAG(__FLAG__)))
#endif /* CORE_CA35 */
#endif /* defined(PWR_CPU3CR_VBF) */


/** @brief  Clear  all historic  PWR state flags (e.g. system has been in standby)
  *         on current CPU control register
  * @retval None.
  */
#if defined (CORE_CA35)
#define __HAL_PWR_CLEAR_FLAG(__FLAG__)  SET_BIT(PWR->CPU1CR, PWR_CPU1CR_CSSF)
#elif defined (CORE_CM33)
#define __HAL_PWR_CLEAR_FLAG(__FLAG__)  SET_BIT(PWR->CPU2CR, PWR_CPU2CR_CSSF)
#elif defined (CORE_CM0PLUS)
#define __HAL_PWR_CLEAR_FLAG(__FLAG__)  SET_BIT(PWR->CPU3CR, PWR_CPU3CR_CSSF)
#endif /* CORE_CA35 */

/** @brief  Clear PWR WKUP line status flags
  * @retval None.
  */
#define __HAL_PWR_WKUP_CLEAR_FLAG(__LINE__) \
  SET_BIT(*(&PWR->WKUPCR1 + (__LINE__)*(0x01u)), PWR_WKUPCR1_WKUPC)


/**
  * @brief Enable the PVD  Exti Line.
  * @note Line is connected to Instance 1 of EXTI IP.
  * @note EXT1 event are  connected to M33_NVIC and A35_GIC  but not to M0+_NVIC
  * @retval None.
  */
#if defined(CORE_CM33)
#define __HAL_PWR_PVD_EXTI_ENABLE_IT()  SET_BIT(EXTI1_C2->IMR1, PWR_EXTI_LINE_PVD)
#elif defined (CORE_CA35)
#define __HAL_PWR_PVD_EXTI_ENABLE_IT()  SET_BIT(EXTI1_C1->IMR1, PWR_EXTI_LINE_PVD)
#endif /* CORE_CM33 */


/**
  * @brief Disable the PVD  EXTI Line.
  * @note Line is connected to Instance 1 of EXTI IP.
  * @note EXT1 event are  connected to M33_NVIC and A35_GIC  but not to M0+_NVIC
  * @retval None.
  */
#if defined(CORE_CM33)
#define __HAL_PWR_PVD_EXTI_DISABLE_IT() CLEAR_BIT(EXTI1_C2->IMR1, PWR_EXTI_LINE_PVD)
#elif defined (CORE_CA35)
#define __HAL_PWR_PVD_EXTI_DISABLE_IT() CLEAR_BIT(EXTI1_C1->IMR1, PWR_EXTI_LINE_PVD)
#endif /* CORE_CM33 */

#if defined(CORE_CM33)||defined(CORE_CA35)
/**
  * @brief Enable the PVD  Extended Interrupt Rising Trigger.
  * @retval None.
  */
#define __HAL_PWR_PVD_EXTI_ENABLE_RISING_EDGE()  SET_BIT(EXTI1->RTSR1, PWR_EXTI_LINE_PVD)

/**
  * @brief Disable the PVD  Extended Interrupt Rising Trigger.
  * @retval None.
  */
#define __HAL_PWR_PVD_EXTI_DISABLE_RISING_EDGE()  CLEAR_BIT(EXTI1->RTSR1, PWR_EXTI_LINE_PVD)


/**
  * @brief Enable the PVD Extended Interrupt Falling Trigger.
  * @retval None.
  */
#define __HAL_PWR_PVD_EXTI_ENABLE_FALLING_EDGE()  SET_BIT(EXTI1->FTSR1, PWR_EXTI_LINE_PVD)

/**
  * @brief Disable the PVD Extended Interrupt Falling Trigger.
  * @retval None.
  */
#define __HAL_PWR_PVD_EXTI_DISABLE_FALLING_EDGE()  CLEAR_BIT(EXTI1->FTSR1, PWR_EXTI_LINE_PVD)


/**
  * @brief  PVD EXTI line configuration: set rising & falling edge trigger.
  * @retval None.
  */
#define __HAL_PWR_PVD_EXTI_ENABLE_RISING_FALLING_EDGE() \
  do { \
    __HAL_PWR_PVD_EXTI_ENABLE_RISING_EDGE(); \
    __HAL_PWR_PVD_EXTI_ENABLE_FALLING_EDGE(); \
  } while(0);

/**
  * @brief Disable the PVD Extended Interrupt Rising & Falling Trigger.
  * @retval None.
  */
#define __HAL_PWR_PVD_EXTI_DISABLE_RISING_FALLING_EDGE() \
  do { \
    __HAL_PWR_PVD_EXTI_DISABLE_RISING_EDGE(); \
    __HAL_PWR_PVD_EXTI_DISABLE_FALLING_EDGE(); \
  } while(0);

/**
  * @brief Check whether the specified PVD EXTI interrupt flag is set or not.
  * @retval EXTI PVD Line Status.
  */
#define __HAL_PWR_PVD_EXTI_GET_FLAG() \
  (((EXTI1->RPR1 & PWR_EXTI_LINE_PVD) == PWR_EXTI_LINE_PVD) || \
   ((EXTI1->FPR1 & PWR_EXTI_LINE_PVD) == PWR_EXTI_LINE_PVD))

/**
  * @brief Clear the PVD Exti flag.
  * @retval None.
  */
#define __HAL_PWR_PVD_EXTI_CLEAR_FLAG() \
  do { \
    SET_BIT(EXTI1->RPR1, PWR_EXTI_LINE_PVD); \
    SET_BIT(EXTI1->FPR1, PWR_EXTI_LINE_PVD); \
  } while(0);

/**
  * @brief  Generates a Software interrupt on selected EXTI line.
  * @retval None
  */
/* PVD  Event in Bank1 */
#define __HAL_PWR_PVD_EXTI_GENERATE_SWIT() SET_BIT(EXTI1->SWIER1, PWR_EXTI_LINE_PVD )

#endif /*defined(CORE_CM33)||defined(CORE_CA35)*/

/* Include PWR HAL Extension module */
#include "stm32mp2xx_hal_pwr_ex.h"


#if defined(CORE_CM33)||defined(CORE_CA35)
/**
  * @brief EXTI line  '52+k' mask is '1 << exti_line#(52+k)_pos' where k in range
  *        from 0 (PWR wakeup line #0)  to 5 (PWR wakeup line #5)
  * @note    for wake-up line 0 mask is '1<<20'  as EXTI line for wake-up line 0 is line 52
  * @note    which position is 20 in EXTI_IMR2
  * @note    for wake-up line 5 mask is '1<<25'  as EXTI line for wake-up line 5 is line 57
  * @note    which position is 25 in EXTI_IMR2
  **/

#define __HAL_WKUP_LINE0_EXTI_MSK                          EXTI1_IMR2_IM52
#define __HAL_WKUP_LINE1_EXTI_MSK                          EXTI1_IMR2_IM53
#define __HAL_WKUP_LINE2_EXTI_MSK                          EXTI1_IMR2_IM54
#define __HAL_WKUP_LINE3_EXTI_MSK                          EXTI1_IMR2_IM55
#define __HAL_WKUP_LINE4_EXTI_MSK                          EXTI1_IMR2_IM56
#define __HAL_WKUP_LINE5_EXTI_MSK                          EXTI1_IMR2_IM57
#endif /*defined(CORE_CM33)||defined(CORE_CA35)*/


/**
  * @brief  Enable generation of EXTI interruption from a PWR wake-up line (case M33/A35)
  * @param  __EXTI_MSK__: specifies mask of the EXTI line which associated interruption shall be enable
  *         For M33 or A35 core, this parameter can be one of the following values
  *            @arg __HAL_WKUP_LINE0_EXTI_MSK
  *            @arg __HAL_WKUP_LINE1_EXTI_MSK
  *            @arg __HAL_WKUP_LINE2_EXTI_MSK
  *            @arg __HAL_WKUP_LINE3_EXTI_MSK
  *            @arg __HAL_WKUP_LINE4_EXTI_MSK
  *            @arg __HAL_WKUP_LINE5_EXTI_MSK
  * @retval None
  */
#ifdef CORE_CM33
#define __HAL_WKUP_EXTI_ENABLE_IT(__EXTI_MSK__)          (EXTI1_C2->IMR2 |= (__EXTI_MSK__))
#elif defined(CORE_CA35)
#define __HAL_WKUP_EXTI_ENABLE_IT(__EXTI_MSK__)          (EXTI1_C1->IMR2 |= (__EXTI_MSK__))
#endif /* CORE_CM33 */

/**
  * @brief  Disable generation of EXTI interruption from a PWR wake-up line (case M33/A35)
  * @param  __EXTI_MSK__: specifies mask of the EXTI line which associated interruption shall be disable
  *         For M33 or A35 core, this parameter can be one of the following values
  *            @arg __HAL_WKUP_LINE0_EXTI_MSK
  *            @arg __HAL_WKUP_LINE1_EXTI_MSK
  *            @arg __HAL_WKUP_LINE2_EXTI_MSK
  *            @arg __HAL_WKUP_LINE3_EXTI_MSK
  *            @arg __HAL_WKUP_LINE4_EXTI_MSK
  *            @arg __HAL_WKUP_LINE5_EXTI_MSK
  * @retval None
  */
#ifdef CORE_CM33
#define __HAL_WKUP_EXTI_DISABLE_IT(__EXTI_MSK__)          CLEAR_BIT(EXTI1_C2->IMR2, __EXTI_MSK__)
#elif defined(CORE_CA35)
#define __HAL_WKUP_EXTI_DISABLE_IT(__EXTI_MSK__)          CLEAR_BIT(EXTI1_C1->IMR2, __EXTI_MSK__)
#endif /* CORE_CM33 */


/**
  * @brief  Return interruption state of  EXTI interruption from a PWR wake-up line (case M33/A35)
  * @param  __EXTI_MSK__: specifies mask of the EXTI line which associated interruption shall be disable
  *                            see __HAL_WKUP_XX_EXTI_MSK where XX LINE0 ..LINE5 for M33/A35
  * @retval EXTI interrupt register ANDed with wake-up mask
  */
#ifdef CORE_CM33
#define __HAL_WKUP_EXTI_BIT_IT(__EXTI_MSK__)          READ_BIT(EXTI1_C2->IMR2, __EXTI_MSK__)
#elif defined(CORE_CA35)
#define __HAL_WKUP_EXTI_BIT_IT(__EXTI_MSK__)          READ_BIT(EXTI1_C1->IMR2, __EXTI_MSK__)
#endif /* CORE_CM33 */

/**
  * @}
  */


/* Exported functions --------------------------------------------------------*/
/** @defgroup PWR_Exported_Functions PWR Exported Functions
  * @{
  */

/** @defgroup PWR_Exported_Functions_Group1 Initialization and de-initialization functions
  * @{
  */
/* Initialization and de-initialization functions *****************************/
#if !defined(CORE_CM0PLUS)
#if defined(PWR_BDCR1_DBD3P)
void HAL_PWR_EnableBkUpD3Access(void);
void HAL_PWR_DisableBkUpD3Access(void);
#else
void HAL_PWR_EnableBkUpAccess(void);
void HAL_PWR_DisableBkUpAccess(void);
#endif /* defined(PWR_BDCR1_DBD3P) */
#else
void HAL_PWR_EnableBkUpAccess(void);
void HAL_PWR_DisableBkUpAccess(void);
#endif /*!defined(CORE_CM0PLUS)*/
/**
  * @}
  */

/* Peripheral Control functions  **********************************************/
/** @defgroup PWR_Exported_Functions_Group2 Peripheral Control functions
  * @{
  */
/* PVD configuration */
void HAL_PWR_ConfigPVD(const PWR_PVDTypeDef *sConfigPVD);
void HAL_PWR_EnablePVD(void);
void HAL_PWR_DisablePVD(void);
uint32_t HAL_PWR_GetPVDRange(void);
void HAL_PWR_PVD_IRQHandler(void);
void HAL_PWR_PVD_EqualHigherCallback(void);
void HAL_PWR_PVD_LowerCallback(void);


/* WakeUp pins configuration */
#if !defined(CORE_CM0PLUS)
void HAL_PWR_EnableWakeUpPin(uint32_t WakeUpPinPolarity);
void HAL_PWR_DisableWakeUpPin(uint32_t WakeUpPinx);
uint32_t HAL_PWR_IsWakeUpCapable(uint32_t WakeUpPinx);
#endif /* CORE_CM0PLUS */


/* EXTI IT functions associated to  WakeUp pin */
#if !defined(CORE_CM0PLUS)
void HAL_PWR_EnableWakeUpExtiIT(uint32_t WakeUpPinx);
void HAL_PWR_DisableWakeUpExtiIT(uint32_t WakeUpPinx);
uint32_t HAL_PWR_IsWakeUpExtiCapable(uint32_t WakeUpPinx);
#endif /* CORE_CM0PLUS */

/* PWR  configuration for D3 wake-up from non-secure TAMPER when system is in VBAT*/
#if ! defined(CORE_CM0PLUS)
void HAL_PWR_EnableD3WakeUpTamper(void);
void HAL_PWR_DisableD3WakeUpTamper(void);
uint32_t HAL_PWR_IsTamperD3WakeUpCapable(void);
#endif /* CORE_CM0PLUS */


/* power state queries */
uint32_t HAL_PWR_CPU1State(void);
uint32_t HAL_PWR_CPU2State(void);
uint32_t HAL_PWR_CPU3State(void);

uint32_t HAL_PWR_D1State(void);
uint32_t HAL_PWR_D2State(void);
uint32_t HAL_PWR_D3State(void);

uint32_t HAL_PWR_HasD1BeenInStandby(void);
uint32_t HAL_PWR_HasD2BeenInStandby(void);
uint32_t HAL_PWR_HasD3BeenInStandby(void);

uint32_t HAL_PWR_HasSystemBeenInStandby(void);
uint32_t HAL_PWR_HasSystemBeenInVBAT(void);
#if defined(CORE_CM33)||defined(CORE_CA35)
uint32_t HAL_PWR_HasSystemBeenInStop(void);
#endif /* defined(CORE_CM33)||defined(CORE_CA35) */

/* Low Power modes entry */
void HAL_PWR_EnterSTOPMode(uint32_t Regulator, uint8_t STOPEntry);
void HAL_PWR_EnterSLEEPMode(__attribute__((unused))uint32_t Regulator, uint8_t SLEEPEntry);
#if defined(CORE_CM33)||defined(CORE_CA35)
void HAL_PWR_EnterSTANDBYMode(uint8_t STANDBYType);
#endif /* defined(CORE_CM33)||defined(CORE_CA35) */


/**
  * @}
  */

/* Cortex System Control functions  *******************************************/
/** @defgroup PWR_Exported_Functions_Group3 Cortex System Control functions
  * @{
  */
#if defined(CORE_CM33)||defined(CORE_CM0PLUS)
void HAL_PWR_EnableSleepOnExit(void);
void HAL_PWR_DisableSleepOnExit(void);
void HAL_PWR_EnableStopOnExit(uint32_t Regulator);
void HAL_PWR_DisableStopOnExit(void);
void HAL_PWR_EnableSEVOnPend(void);
void HAL_PWR_DisableSEVOnPend(void);
#endif /* defined(CORE_CM33)||defined(CORE_CA35) */
/**
  * @}
  */

/* Register Access control  functions  *******************************************/
/** @defgroup PWR_Exported_Functions_Group4 Register Access control functions
  * @{
  */
void HAL_PWR_ConfigResourceAttributes(uint16_t Item, uint32_t Attributes);
HAL_StatusTypeDef HAL_PWR_GetConfigResourceAttributes(uint16_t Item, uint32_t *pAttributes);
HAL_StatusTypeDef HAL_PWR_TakeResourceSemaphore(uint16_t Item);
HAL_StatusTypeDef HAL_PWR_ReleaseResourceSemaphore(uint16_t Item);


/**
  * @}
  */

/**
  * @}
  */


/* Private constants ---------------------------------------------------------*/

/** @defgroup PWR_Private_Constants PWR Private Constants
  * @{
  */

/** @defgroup  EXTI Lines
  * @{
  */
#define PWR_EXTI_LINE_PVD        EXTI1_IMR1_IM16         /*PVD signal connected on line16 of EXTI*/
#define PWR_EXTI_LINE_PVM        EXTI1_IMR1_IM17         /*PVM signal connected on line17 of EXTI*/
#define PWR_EXTI_LINE_VDDCORED   EXTI2_IMR3_IM65         /*VDD core detection signal connected on line65 of EXTI*/
#define PWR_EXTI_LINE_VDDCPUD    EXTI2_IMR3_IM64         /*VDD cpu  detection signal connected on line64 of EXTI*/
#define PWR_EXTI_LINE_VDDGPUD    EXTI1_IMR1_IM18         /*VDD gpu  detection signal connected on line18 of EXTI*/
#if defined(CORE_CM0PLUS)
#define PWR_EXTI_LINE_NS_TAMPER     EXTI2_IMR1_IM20  /*non secure TAMPER  signal for M0+  connected on line20 of EXTI*/
#endif /* CORE_CM0PLUS */
#if defined(CORE_CM33)
#define PWR_EXTI_LINE_NS_TAMPER     EXTI2_IMR1_IM18  /*non secure TAMPER  signal for M33  connected on line18 of EXTI*/
#define PWR_EXTI_LINE_S_TAMPER      EXTI2_IMR1_IM23  /*    secure TAMPER  signal for M33  connected on line23 of EXTI*/
#endif /* CORE_CM33 */
#if defined(CORE_CA35)
#define PWR_EXTI_LINE_NS_TAMPER     EXTI2_IMR1_IM16  /*non secure TAMPER  signal for A35  connected on line16 of EXTI*/
#define PWR_EXTI_LINE_S_TAMPER      EXTI2_IMR1_IM21  /*secure TAMPER  signal for M33  connected on line21 of EXTI*/
#endif /* CORE_CA35 */

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

#endif /* __STM32MP2xx_HAL_PWR_H */
