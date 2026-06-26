/**
  ******************************************************************************
  * @file    stm32g5xx_ll_posenc.h
  * @brief   Header file of POSENC LL module.

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
#ifndef STM32G5xx_LL_POSENC_H
#define STM32G5xx_LL_POSENC_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Includes ------------------------------------------------------------------*/
#include "stm32g5xx.h"

/** @addtogroup STM32G5xx_LL_Driver
  * @{
  */

#if defined (POSENC1) || defined (POSENC2)

/** @defgroup POSENC_LL POSENC
  * @{
  */

/* Private macros ------------------------------------------------------------*/
/** @defgroup POSENC_LL_Private_Macros POSENC Private Macros
  * @{
  */

/**
  * @brief  Driver macro reserved for internal use: set a pointer to
  *         a register from a register basis from which an offset
  *         is applied.
  * @param  reg Register basis from which the offset is applied.
  * @param  reg_offset Offset to be applied (unit: number of registers).
  * @return Pointer to register address
  */
#define LL_POSENC_PTR_REG_OFFSET(reg, reg_offset) \
  ((__IO uint32_t *)((uint32_t) ((uint32_t)(&(reg)) + ((reg_offset) << 2UL))))

/**
  * @brief  Driver macro reserved for internal use: return a pointer to
  *         POSENC_ED3_TypeDef instance corresponding to the POSENC instance
  *         passed as parameter.
  * @param  instance POSENC instance.
  * @return Pointer to the ENDAT3 register structure.
  */
#define LL_POSENC_GET_ENDAT3_INSTANCE(instance) \
  (((instance) == POSENC1) ? (POSENC_ED3_TypeDef*)POSENC1_ED3 : (POSENC_ED3_TypeDef*)POSENC2_ED3)

/**
  * @brief  Driver macro reserved for internal use: return a pointer to
  *         POSENC_HD_TypeDef instance corresponding to the POSENC instance
  *         passed as parameter.
  * @param  instance POSENC instance.
  * @return Pointer to the HIPERFACE-DSL register structure.
  */
#define LL_POSENC_GET_HIPERFACEDSL_INSTANCE(instance) \
  (((instance) == POSENC1) ? (POSENC_HD_TypeDef*)POSENC1_HD : (POSENC_HD_TypeDef*)POSENC2_HD)


/**
  * @}
  */


/* Exported macros ------------------------------------------------------------*/
/** @defgroup POSENC_LL_Exported_Macros POSENC Exported Macros
  * @{
  */

/**
  * @brief  Register access macro to read a register of POSENC EnDat3 submodule.
  * @param  instance POSENC instance.
  * @param  reg Register to be read.
  * @return Register value.
  */
#define LL_POSENC_ED3_READ_REG(instance, reg) \
  STM32_READ_REG(LL_POSENC_GET_ENDAT3_INSTANCE(instance)->reg)

/**
  * @brief  Register access macro to write a register of POSENC EnDat3 submodule.
  * @param  instance POSENC instance.
  * @param  reg Register to be written.
  * @param  value Value to be written in register.
  * @return None
  */
#define LL_POSENC_ED3_WRITE_REG(instance, reg, value) \
  STM32_WRITE_REG(LL_POSENC_GET_ENDAT3_INSTANCE(instance)->reg, value)

/**
  * @brief  Register access macro to clear and set one or several bits of POSENC EnDat3 submodule.
  * @param  instance POSENC instance.
  * @param  reg Register to be modified.
  * @param  clear_mask Mask of bits to be cleared.
  * @param  set_mask Mask of bits to be set.
  * @return None
  */
#define LL_POSENC_ED3_MODIFY_REG(instance, reg, clear_mask, set_mask) \
  STM32_MODIFY_REG(LL_POSENC_GET_ENDAT3_INSTANCE(instance)->reg, clear_mask, set_mask)

/**
  * @brief  Register access macro to write a register of POSENC Hiperface-DSL submodule.
  * @param  instance POSENC instance.
  * @param  reg Register to be written.
  * @param  value Value to be written in register.
  * @return None
  */
#define LL_POSENC_HD_WRITE_REG(instance, reg, value) \
  STM32_WRITE_REG(LL_POSENC_GET_HIPERFACEDSL_INSTANCE(instance)->reg, value)

/**
  * @}
  */

/* Exported constants --------------------------------------------------------*/
/** @defgroup POSENC_LL_Exported_Constants LL POSENC Constants
  * @{
  */

/** @defgroup POSENC_LL_EC_ENCSEL   Encoder selection
  * @{
  */
#define LL_POSENC_ENCSEL_ENDAT3               (0x00000000UL)         /*!< EnDat3 */
#define LL_POSENC_ENCSEL_HIPERFACEDSL         (POSENC_CR1_ENCSEL_2)  /*!< Hiperface-DSL */
#define LL_POSENC_ENCSEL_NO_PROTOCOL_SELECTED (POSENC_CR1_ENCSEL)    /*!< No protocol selected */
/**
  * @}
  */

/** @defgroup POSENC_LL_EC_STROBE_RESYNC   Strobe re-synchronization
  * @{
  */
#define LL_POSENC_STROBE_RESYNC_ENABLED  (0x00000000UL)           /*!< Strobe re-synchronization enabled */
#define LL_POSENC_STROBE_RESYNC_DISABLED (POSENC_CR1_NSTRBRSYNC)  /*!< Strobe re-synchronization disabled */
/**
  * @}
  */

/** @defgroup POSENC_LL_EC_STRBSEL   Strobe selection
  * @{
  */
#define LL_POSENC_STROBE_TIM1_TRGO          (0x00000000UL)               /*!< POSENC external strobe source: TIM1 TRGO
                                                                              event */
#define LL_POSENC_STROBE_TIM1_TRGO2         (POSENC_CR1_STRBSEL_0)       /*!< POSENC external strobe source: TIM1 TRGO2
                                                                              event */
#define LL_POSENC_STROBE_TIM8_TRGO          (POSENC_CR1_STRBSEL_1)       /*!< POSENC external strobe source: TIM8 TRGO
                                                                              event */
#define LL_POSENC_STROBE_TIM8_TRGO2         (POSENC_CR1_STRBSEL_1    \
                                             | POSENC_CR1_STRBSEL_0)     /*!< POSENC external strobe source: TIM8 TRGO2
                                                                             event */
#define LL_POSENC_STROBE_TIM9_TRGO          (POSENC_CR1_STRBSEL_2 )      /*!< POSENC external strobe source: TIM9 TRGO
                                                                              event */
#define LL_POSENC_STROBE_TIM12_TRGO         (POSENC_CR1_STRBSEL_2    \
                                             | POSENC_CR1_STRBSEL_0)     /*!< POSENC external strobe source: TIM12 TRGO
                                                                              event */
#define LL_POSENC_STROBE_TIM20_TRGO         (POSENC_CR1_STRBSEL_2    \
                                             | POSENC_CR1_STRBSEL_1)     /*!< POSENC external strobe source: TIM20 TRGO
                                                                              event */
#define LL_POSENC_STROBE_TIM20_TRGO2        (POSENC_CR1_STRBSEL_2    \
                                             | POSENC_CR1_STRBSEL_1  \
                                             | POSENC_CR1_STRBSEL_0)     /*!< POSENC external strobe source: TIM20 TRGO2
                                                                              event */
#define LL_POSENC_STROBE_TIM26_TRGO         (POSENC_CR1_STRBSEL_3    \
                                             | POSENC_CR1_STRBSEL_1)     /*!< POSENC external strobe source: TIM26 TRGO
                                                                              event */
#define LL_POSENC_STROBE_TIM27_TRGO         (POSENC_CR1_STRBSEL_3    \
                                             | POSENC_CR1_STRBSEL_1  \
                                             | POSENC_CR1_STRBSEL_0)     /*!< POSENC external strobe source: TIM27 TRGO
                                                                              event */
#define LL_POSENC_STROBE_HRTIM1_ADC_TRIG1   (POSENC_CR1_STRBSEL_3    \
                                             | POSENC_CR1_STRBSEL_2)     /*!< POSENC external strobe source: HRTIM ADC
                                                                              TRIG1 event */
#define LL_POSENC_STROBE_HRTIM1_ADC_TRIG3   (POSENC_CR1_STRBSEL_3    \
                                             | POSENC_CR1_STRBSEL_2  \
                                             | POSENC_CR1_STRBSEL_0)     /*!< POSENC external strobe source: HRTIM ADC
                                                                              TRIG3 event */
#define LL_POSENC_STROBE_EXTI10             (POSENC_CR1_STRBSEL_4)       /*!< POSENC external strobe source: external
                                                                              interrupt line 10 event
                                                                              (Specific to POSENC1) */
#define LL_POSENC_STROBE_PLAY1_OUT7         (POSENC_CR1_STRBSEL_4    \
                                             | POSENC_CR1_STRBSEL_0)     /*!< POSENC external strobe source: PLAY1 OUT7
                                                                              event (Specific to POSENC1) */
#define LL_POSENC_STROBE_EXTI12             (POSENC_CR1_STRBSEL_4)       /*!< POSENC external strobe source: external
                                                                              interrupt line 12 event
                                                                              (Specific to POSENC2) */
#define LL_POSENC_STROBE_PLAY1_OUT10         (POSENC_CR1_STRBSEL_4    \
                                              | POSENC_CR1_STRBSEL_0)    /*!< POSENC external strobe source: PLAY1 OUT10
                                                                              event (Specific to POSENC2) */
/**
  * @}
  */

/** @defgroup POSENC_LL_EC_HD_POS   Hiperface-DSL fast position event-driven accesses
  * @{
  */
#define LL_POSENC_HD_EVTDRV_FASTPOSITION_DISABLED (0x00000000UL)        /*!< No event driven position read access */
#define LL_POSENC_HD_EVTDRV_FASTPOSITION_24BIT    (POSENC_CR2_HDPOS_0)  /*!< Event driven read transfer position data
                                                                              from register POS0, POS1 and POS2 to
                                                                              HD_POS30R */
#define LL_POSENC_HD_EVTDRV_FASTPOSITION_32BIT    (POSENC_CR2_HDPOS_1)  /*!< Event driven read transfer position data
                                                                              from register POS0, POS1, POS2 and POS3
                                                                              to HD_POS30R */
#define LL_POSENC_HD_EVTDRV_FASTPOSITION_40BIT    (POSENC_CR2_HDPOS)    /*!< Event driven read transfer position data
                                                                              from register POS0, POS1, POS2, POS3 to
                                                                              HD_POS30R
                                                                              and data from POS4 to HD_POS4R */
/**
  * @}
  */

/** @defgroup POSENC_LL_EC_HD_VPOS   Hiperface-DSL fast position event-driven accesses
  * @{
  */
#define LL_POSENC_HD_EVTDRV_SAFE_POSITION_1_DISABLED (0x00000000UL)      /*!< No event driven safe position 1 read
                                                                              access */
#define LL_POSENC_HD_EVTDRV_SAFE_POSITION_1_24BIT (POSENC_CR2_HDVPOS_0) /*!< Event driven read transfer safe position 1
                                                                              data from register VPOS0, VPOS1 and VPOS2
                                                                              to HD_VPOS30R */
#define LL_POSENC_HD_EVTDRV_SAFE_POSITION_1_32BIT (POSENC_CR2_HDVPOS_1) /*!< Event driven read transfer safe position 1
                                                                              data from register VPOS0, VPOS1, VPOS2 and
                                                                              VPOS3 to HD_VPOS30R */
#define LL_POSENC_HD_EVTDRV_SAFE_POSITION_1_40BIT (POSENC_CR2_HDVPOS)   /*!< Event driven read transfer safe position 1
                                                                              data from register VPOS0, VPOS1, VPOS2,
                                                                              VPOS3 to HD_VPOS30R
                                                                              and data from VPOS4 to HD_VPOS4R */
/**
  * @}
  */

/** @defgroup POSENC_LL_EC_IT POSENC interrupts for configuration (interrupt enable or disable)
  *           and flag management
  * @brief    IT defines which can be used with LL_POSENC_IsEnabledIT _ReadReg and LL_POSENC_EnableIT functions.
  * @{
  */
#define LL_POSENC_IT_GTC         (POSENC_IER_GTCIE)                      /*!< POSENC interrupt Global Transfer
                                                                              Complete */
#define LL_POSENC_IT_WRTC        (POSENC_IER_WRTCIE)                     /*!< POSENC interrupt Write Transfer
                                                                              Complete */
#define LL_POSENC_IT_D0RTC       (POSENC_IER_D0RTCIE)                    /*!< POSENC interrupt Read Data 0 Transfer
                                                                              Complete */
#define LL_POSENC_IT_D1RTC       (POSENC_IER_D1RTCIE)                    /*!< POSENC interrupt Read Data 1 Transfer
                                                                              Complete */
#define LL_POSENC_IT_HDVPOSCRCTC (POSENC_IER_HDVPOSCRCTCIE)              /*!< POSENC interrupt Hiperface-DSL Safe
                                                                              Position 1 CRC Transfer Complete */
#define LL_POSENC_IT_HDVPOSTC    (POSENC_IER_HDVPOSTCIE)                 /*!< POSENC interrupt Hiperface-DSL Safe
                                                                              Position 1 Transfer Complete */
#define LL_POSENC_IT_HDVELTC     (POSENC_IER_HDVELTCIE)                  /*!< POSENC interrupt Hiperface-DSL Velocity
                                                                              Transfer Complete */
#define LL_POSENC_IT_HDFPOSTC    (POSENC_IER_HDFPOSTCIE)                 /*!< POSENC interrupt Hiperface-DSL Fast
                                                                              Position Transfer Complete */
#define LL_POSENC_IT_HDFPOS      (POSENC_IER_HDFPOSIE)                   /*!< POSENC interrupt Hiperface-DSL Fast
                                                                              Position */
#define LL_POSENC_IT_HDVPOS1     (POSENC_IER_HDVPOS1IE)                  /*!< POSENC interrupt Hiperface-DSL Safe
                                                                              Position 1 */
#define LL_POSENC_IT_HDVPOS2     (POSENC_IER_HDVPOS2IE)                  /*!< POSENC interrupt Hiperface-DSL Safe
                                                                              Position 2 */
#define LL_POSENC_IT_HDFREL      (POSENC_IER_HDFRELIE)                   /*!< POSENC interrupt Hiperface-DSL Long
                                                                              message */
#define LL_POSENC_IT_HDFRES      (POSENC_IER_HDFRESIE)                   /*!< POSENC interrupt Hiperface-DSL Short
                                                                              message */
#define LL_POSENC_IT_ALL         (LL_POSENC_IT_GTC     | LL_POSENC_IT_WRTC            \
                                  | LL_POSENC_IT_D0RTC | LL_POSENC_IT_D1RTC           \
                                  | LL_POSENC_IT_HDVPOSCRCTC | LL_POSENC_IT_HDVPOSTC  \
                                  | LL_POSENC_IT_HDVELTC     | LL_POSENC_IT_HDFPOSTC  \
                                  | LL_POSENC_IT_HDFPOS                               \
                                  | LL_POSENC_IT_HDVPOS1 | LL_POSENC_IT_HDVPOS2       \
                                  | LL_POSENC_IT_HDFREL  | LL_POSENC_IT_HDFRES) /*!< POSENC all interrupts */
/**
  * @}
  */


/** @defgroup POSENC_LL_EC_STATUS POSENC flag indicating current status
  * @brief    These defines can be used with LL_POSENC_GetStatus function.
  * @{
  */
#define LL_POSENC_STATUS_GLOBAL_BUSY  (POSENC_SR1_GBSY)                  /*!< POSENC Hiperface-DSL read or write
                                                                              transaction busy status */
#define LL_POSENC_STATUS_WRITE_BUSY   (POSENC_SR1_WRBSY)                 /*!< POSENC Hiperface-DSL write transaction
                                                                              busy status */
#define LL_POSENC_STATUS_DATA_0_BUSY  (POSENC_SR1_D0RDBSY)               /*!< POSENC Data 0 Busy status */
#define LL_POSENC_STATUS_DATA_1_BUSY  (POSENC_SR1_D1RDBSY)               /*!< POSENC Data 1 Busy status */
#define LL_POSENC_STATUS_HD_IT        (POSENC_SR1_HDINT)                 /*!< POSENC Hiperface-DSL Long message */
#define LL_POSENC_STATUS_HD_IT_S      (POSENC_SR1_HDINTS)                /*!< POSENC Hiperface-DSL Short message */
#define LL_POSENC_STATUS_ALL          (LL_POSENC_STATUS_GLOBAL_BUSY     \
                                       | LL_POSENC_STATUS_WRITE_BUSY    \
                                       | LL_POSENC_STATUS_DATA_0_BUSY   \
                                       | LL_POSENC_STATUS_DATA_1_BUSY   \
                                       | LL_POSENC_STATUS_HD_IT         \
                                       | LL_POSENC_STATUS_HD_IT_S)       /*!< POSENC all status flags */
/**
  * @}
  */

/** @defgroup POSENC_LL_EC_HD_REGISTER Hiperface-DSL register address translation
  * @brief These defines can be used with LL_POSENC_RequestReadData0 and LL_POSENC_RequestReadData1 functions.
  * @note The Hiperface-DSL IP core native interface is 8-bit wide. POSENC provides an address translation logic, a
  *       posted write mechanism and indirect read requests to avoid APB bus stalls during Hiperface-DSL accesses.
  * @{
  */
#define LL_POSENC_HD_CTRLR          (0x00UL)     /* POSENC address for Hiperface-DSL registers SYNC_CTRL and SYS_CTRL */
#define LL_POSENC_HD_MASTER_QMR     (0x04UL)     /* POSENC address for Hiperface-DSL register MASTER_QM               */
#define LL_POSENC_HD_EVENTR         (0x08UL)     /* POSENC address for Hiperface-DSL registers EVENT_H, EVENT_L       */
#define LL_POSENC_HD_MASKR          (0x0CUL)     /* POSENC address for Hiperface-DSL registers MASK_SUM, MASK_H,
                                                    MASK_L */
#define LL_POSENC_HD_EDGESR         (0x10UL)     /* POSENC address for Hiperface-DSL register EDGES                   */
#define LL_POSENC_HD_DELAYR         (0x14UL)     /* POSENC address for Hiperface-DSL register DELAY                   */
#define LL_POSENC_HD_VRS_RELR       (0x18UL)     /* POSENC address for Hiperface-DSL registers RELEASE data FIFO
                                                    VERSION */
#define LL_POSENC_HD_ENC_IDR        (0x1CUL)     /* POSENC address for Hiperface-DSL registers ENC_ID2, ENC_ID1,
                                                    ENC_ID2 */
#define LL_POSENC_HD_FPOSSTR        (0x20UL)     /* POSENC address for Hiperface-DSL registers POS2, POS1, POS0       */
#define LL_POSENC_HD_FPOSMT1        (0x24UL)     /* POSENC address for Hiperface-DSL registers POS3, POS2, POS1, POS0 */
#define LL_POSENC_HD_FPOSMT2        (0x28UL)     /* POSENC address for Hiperface-DSL register POS4                    */
#define LL_POSENC_HD_VELR           (0x2CUL)     /* POSENC address for Hiperface-DSL registers VEL2, VEL1, VEL0       */
#define LL_POSENC_HD_VPOSST         (0x34UL)     /* POSENC address for Hiperface-DSL registers VPOS2, VPOS1, VPOS0    */
#define LL_POSENC_HD_VPOSMT1        (0x38UL)     /* POSENC address for Hiperface-DSL registers VPOS3, VPOS2, VPOS1,
                                                    VPOS0 */
#define LL_POSENC_HD_VPOSMT2        (0x3CUL)     /* POSENC address for Hiperface-DSL register VPOS4                   */
#define LL_POSENC_HD_VPOSCRC        (0x40UL)     /* POSENC address for Hiperface-DSL registers VPOS_CRC_H, VPOS_CRC_L */
#define LL_POSENC_HD_PCBUFA         (0x44UL)     /* POSENC address for Hiperface-DSL registers PC_BUFFER1, PC_BUFFER0 */
#define LL_POSENC_HD_PCBUFB         (0x48UL)     /* POSENC address for Hiperface-DSL registers PC_BUFFER3, PC_BUFFER2,
                                                    PC_BUFFER1, PC_BUFFER0 */
#define LL_POSENC_HD_PCBUFC         (0x4CUL)     /* POSENC address for Hiperface-DSL registers PC_BUFFER7, PC_BUFFER6,
                                                    PC_BUFFER5, PC_BUFFER4 */
#define LL_POSENC_HD_LOFFR          (0x50UL)     /* POSENC address for Hiperface-DSL register PC_ADD_H                */
#define LL_POSENC_HD_PC_ADDR        (0x54UL)     /* POSENC address for Hiperface-DSL registers PC_ADD_H, PC_ADD_L     */
#define LL_POSENC_HD_PC_OFFR        (0x58UL)     /* POSENC address for Hiperface-DSL registers PC_OFF_H, PC_OFF_L     */
#define LL_POSENC_HD_PC_ADDOFFR     (0x5CUL)     /* POSENC address for Hiperface-DSL registers PC_OFF_H, PC_OFF_L,
                                                    PC_ADD_H, PC_ADD_L */
#define LL_POSENC_HD_PC_CTRLR       (0x60UL)     /* POSENC address for Hiperface-DSL register PC_CTRL                 */
#define LL_POSENC_HD_PIPE_SR        (0x64UL)     /* POSENC address for Hiperface-DSL register PIPE_SR                 */
#define LL_POSENC_HD_PIPE_D         (0x68UL)     /* POSENC address for Hiperface-DSL register PIPE_D                  */
#define LL_POSENC_HD_SAFE_CTRL      (0x70UL)     /* POSENC address for Hiperface-DSL register SAFE_CTRL               */
#define LL_POSENC_HD_SAFE_SUM       (0x74UL)     /* POSENC address for Hiperface-DSL register SAFE_SUM                */
#define LL_POSENC_HD_S_PC_DATA      (0x78UL)     /* POSENC address for Hiperface-DSL register S_PC_DATA               */
#define LL_POSENC_HD_ACC_EE_CNT     (0x7CUL)     /* POSENC address for Hiperface-DSL register ACC_EE_CNT              */
#define LL_POSENC_HD_MAXACC         (0x80UL)     /* POSENC address for Hiperface-DSL register MAXACC                  */
#define LL_POSENC_HD_MAXDEV         (0x84UL)     /* POSENC address for Hiperface-DSL registers MAXDEV_H, MAXDEV_L     */
#define LL_POSENC_HD_EVENT_S        (0x88UL)     /* POSENC address for Hiperface-DSL register EVENT_S                 */
#define LL_POSENC_HD_MASK_S         (0x8CUL)     /* POSENC address for Hiperface-DSL register MASK_S                  */
#define LL_POSENC_HD_DUMMY          (0x90UL)     /* POSENC address for Hiperface-DSL register DUMMY                   */
#define LL_POSENC_HD_ST0            (0x94UL)     /* POSENC address for Hiperface-DSL register ENC_ST0                 */
#define LL_POSENC_HD_ST1            (0x98UL)     /* POSENC address for Hiperface-DSL register ENC_ST1                 */
#define LL_POSENC_HD_ST2            (0x9CUL)     /* POSENC address for Hiperface-DSL register ENC_ST2                 */
#define LL_POSENC_HD_ST3            (0xA0UL)     /* POSENC address for Hiperface-DSL register ENC_ST3                 */
#define LL_POSENC_HD_ST4            (0xA4UL)     /* POSENC address for Hiperface-DSL register ENC_ST4                 */
#define LL_POSENC_HD_ST5            (0xA8UL)     /* POSENC address for Hiperface-DSL register ENC_ST5                 */
#define LL_POSENC_HD_ST6            (0xACUL)     /* POSENC address for Hiperface-DSL register ENC_ST6                 */
#define LL_POSENC_HD_ST7            (0xB0UL)     /* POSENC address for Hiperface-DSL register ENC_ST7                 */
#define LL_POSENC_HD_SRSSI          (0xB4UL)     /* POSENC address for Hiperface-DSL register SRSSI                   */
#define LL_POSENC_HD_MAIL           (0xB8UL)     /* POSENC address for Hiperface-DSL register MAIL                    */
#define LL_POSENC_HD_PING           (0xBCUL)     /* POSENC address for Hiperface-DSL register PING                    */
/**
  * @}
  */

/** @defgroup POSENC_LL_EC_ED3 EnDat3 FID memory address (64-bit) organization
  * @brief EnDat3 memory address helpers.
  * @note EnDat3 cycle-based, safety and FID-based memories are 64-bit wide. Access one entry with two 32-bit accesses
  *       from a 64-bit aligned frame address using LL_POSENC_ED3_MEM_LOW and LL_POSENC_ED3_MEM_HIGH.
  * @{
  */

#define LL_POSENC_ED3_MEM_LOW     (0x0UL)                                /* POSENC selection of LSB word in 64-bit
                                                                            EnDat3 memory */
#define LL_POSENC_ED3_MEM_HIGH    (0x4UL)                                /* POSENC selection of MSB word in 64-bit
                                                                            EnDat3 memory */

#define LL_POSENC_ED3_MEM_BASE    (0x1000UL)                             /* POSENC base address for EnDat3 Cycle-based
                                                                            memory for HPF data and LPF data  */
#define LL_POSENC_ED3_MEM_HPF     (LL_POSENC_ED3_MEM_BASE + 0x0000UL)    /* POSENC address for EnDat3 memory HPF   */
#define LL_POSENC_ED3_MEM_LPF0    (LL_POSENC_ED3_MEM_BASE + 0x0008UL)    /* POSENC address for EnDat3 memory LPF0  */
#define LL_POSENC_ED3_MEM_LPF1    (LL_POSENC_ED3_MEM_BASE + 0x0010UL)    /* POSENC address for EnDat3 memory LPF1  */
#define LL_POSENC_ED3_MEM_LPF2    (LL_POSENC_ED3_MEM_BASE + 0x0018UL)    /* POSENC address for EnDat3 memory LPF2  */
#define LL_POSENC_ED3_MEM_LPF3    (LL_POSENC_ED3_MEM_BASE + 0x0020UL)    /* POSENC address for EnDat3 memory LPF3  */
#define LL_POSENC_ED3_MEM_LPF4    (LL_POSENC_ED3_MEM_BASE + 0x0028UL)    /* POSENC address for EnDat3 memory LPF4  */
#define LL_POSENC_ED3_MEM_LPF5    (LL_POSENC_ED3_MEM_BASE + 0x0030UL)    /* POSENC address for EnDat3 memory LPF5  */
#define LL_POSENC_ED3_MEM_LPF6    (LL_POSENC_ED3_MEM_BASE + 0x0038UL)    /* POSENC address for EnDat3 memory LPF6  */
#define LL_POSENC_ED3_MEM_LPF7    (LL_POSENC_ED3_MEM_BASE + 0x0040UL)    /* POSENC address for EnDat3 memory LPF7  */
#define LL_POSENC_ED3_MEM_LPF8    (LL_POSENC_ED3_MEM_BASE + 0x0048UL)    /* POSENC address for EnDat3 memory LPF8  */
#define LL_POSENC_ED3_MEM_LPF9    (LL_POSENC_ED3_MEM_BASE + 0x0050UL)    /* POSENC address for EnDat3 memory LPF9  */
#define LL_POSENC_ED3_MEM_LPF10   (LL_POSENC_ED3_MEM_BASE + 0x0058UL)    /* POSENC address for EnDat3 memory LPF10 */
#define LL_POSENC_ED3_MEM_LPF11   (LL_POSENC_ED3_MEM_BASE + 0x0060UL)    /* POSENC address for EnDat3 memory LPF11 */
#define LL_POSENC_ED3_MEM_LPF12   (LL_POSENC_ED3_MEM_BASE + 0x0068UL)    /* POSENC address for EnDat3 memory LPF12 */
#define LL_POSENC_ED3_MEM_LPF13   (LL_POSENC_ED3_MEM_BASE + 0x0070UL)    /* POSENC address for EnDat3 memory LPF13 */
#define LL_POSENC_ED3_MEM_LPF14   (LL_POSENC_ED3_MEM_BASE + 0x0078UL)    /* POSENC address for EnDat3 memory LPF14 */

#define LL_POSENC_ED3_MEM_LPH     (0x1400UL)                             /* POSENC base address for EnDat3 cycle-based
                                                                            memory for LPH data */

#define LL_POSENC_ED3_MEM_SAFETY_COLLECTOR_BASE  (0x1500UL)              /* POSENC base address for memory for safety
                                                                            information */
#define LL_POSENC_ED3_MEM_SAFETY_DATA_1 (LL_POSENC_ED3_MEM_SAFETY_COLLECTOR_BASE + 0x0000UL) /* POSENC address for
                                                                                                EnDat3 safety data 1 */
#define LL_POSENC_ED3_MEM_SAFETY_DATA_2 (LL_POSENC_ED3_MEM_SAFETY_COLLECTOR_BASE + 0x0008UL) /* POSENC address for
                                                                                                EnDat3 safety data 2 */
#define LL_POSENC_ED3_MEM_SAFETY_PACKET (LL_POSENC_ED3_MEM_SAFETY_COLLECTOR_BASE + 0x0010UL) /* POSENC address for
                                                                                                EnDat3 safety packet */

#define LL_POSENC_ED3_MEM_FID_BASE (0x1700)                              /* POSENC base address for FID-based memory
                                                                            for LPF data */

/**
  * @}
  */

/**
  * @}
  */

/* Exported functions --------------------------------------------------------*/
/** @defgroup POSENC_LL_Exported_Functions LL POSENC Functions
  * @{
  */

/**
  * @brief Configures the position encoder operation.
  * @rmtoll
  *  CR1         ENCSEL         LL_POSENC_ConfigEncoder \n
  *  CR1         NSTRBRSYNC     LL_POSENC_ConfigEncoder \n
  *  CR1         STRBSEL        LL_POSENC_ConfigEncoder
  * @param  p_posenc POSENC instance.
  * @param  resync This parameter can be one of the following values:
  *         @arg @ref LL_POSENC_STROBE_RESYNC_ENABLED
  *         @arg @ref LL_POSENC_STROBE_RESYNC_DISABLED
  * @param  encoder This parameter can be one of the following values:
  *         @arg @ref LL_POSENC_ENCSEL_ENDAT3
  *         @arg @ref LL_POSENC_ENCSEL_HIPERFACEDSL
  *         @arg @ref LL_POSENC_ENCSEL_NO_PROTOCOL_SELECTED
  * @param  strobe Strobe signal for the encoder.
  *         @arg @ref LL_POSENC_STROBE_TIM1_TRGO
  *         @arg @ref LL_POSENC_STROBE_TIM1_TRGO2
  *         @arg @ref LL_POSENC_STROBE_TIM8_TRGO
  *         @arg @ref LL_POSENC_STROBE_TIM8_TRGO2
  *         @arg @ref LL_POSENC_STROBE_TIM9_TRGO
  *         @arg @ref LL_POSENC_STROBE_TIM12_TRGO
  *         @arg @ref LL_POSENC_STROBE_TIM20_TRGO
  *         @arg @ref LL_POSENC_STROBE_TIM20_TRGO2
  *         @arg @ref LL_POSENC_STROBE_TIM26_TRGO
  *         @arg @ref LL_POSENC_STROBE_TIM27_TRGO
  *         @arg @ref LL_POSENC_STROBE_HRTIM1_ADC_TRIG1
  *         @arg @ref LL_POSENC_STROBE_HRTIM1_ADC_TRIG3
  *         @arg @ref LL_POSENC_STROBE_EXTI10
  *         @arg @ref LL_POSENC_STROBE_PLAY1_OUT7
  *         @arg @ref LL_POSENC_STROBE_EXTI12
  *         @arg @ref LL_POSENC_STROBE_PLAY1_OUT10
  * @note  Program protocol selection before any other POSENC register access. Once ENCSEL[3:0] is different from
  *        LL_POSENC_ENCSEL_NO_PROTOCOL_SELECTED, POSENC_CR1 protocol and strobe fields are locked by hardware.
  */
__STATIC_INLINE void LL_POSENC_ConfigEncoder(POSENC_TypeDef *p_posenc,
                                             uint32_t resync,
                                             uint32_t encoder,
                                             uint32_t strobe)
{
  STM32_MODIFY_REG(p_posenc->CR1,
                   POSENC_CR1_ENCSEL | POSENC_CR1_NSTRBRSYNC | POSENC_CR1_STRBSEL,
                   encoder | resync | strobe);
}

/**
  * @brief  Set encoder protocol.
  * @rmtoll
  *  CR1         ENCSEL         LL_POSENC_SetEncoder
  * @param  p_posenc POSENC instance.
  * @param  encoder This parameter can be one of the following values:
  *         @arg @ref LL_POSENC_ENCSEL_ENDAT3
  *         @arg @ref LL_POSENC_ENCSEL_HIPERFACEDSL
  *         @arg @ref LL_POSENC_ENCSEL_NO_PROTOCOL_SELECTED
  * @note  Program the final protocol selection only after the required strobe source and re-synchronization fields are
  *        configured, because POSENC_CR1 is locked once ENCSEL[3:0] selects a protocol.
  */
__STATIC_INLINE void LL_POSENC_SetEncoder(POSENC_TypeDef *p_posenc, uint32_t encoder)
{
  STM32_MODIFY_REG(p_posenc->CR1, POSENC_CR1_ENCSEL, encoder);
}

/**
  * @brief  Get encoder protocol.
  * @rmtoll
  *  CR1         ENCSEL         LL_POSENC_GetEncoder
  * @param  p_posenc POSENC instance.
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_POSENC_ENCSEL_ENDAT3
  *         @arg @ref LL_POSENC_ENCSEL_HIPERFACEDSL
  *         @arg @ref LL_POSENC_ENCSEL_NO_PROTOCOL_SELECTED
  */
__STATIC_INLINE uint32_t LL_POSENC_GetEncoder(const POSENC_TypeDef *p_posenc)
{
  return (STM32_READ_BIT(p_posenc->CR1, POSENC_CR1_ENCSEL));
}
/**
  * @brief  Enable Strobe re-synchronization.
  * @rmtoll
  *  CR1         NSTRBRSYNC         LL_POSENC_EnableStrobeResync
  * @param  p_posenc POSENC instance.
  * @note  Strobe re-synchronization must only be disabled when the selected trigger source and POSENC are synchronous.
  *        This field is locked by hardware once ENCSEL[3:0] selects a protocol.
  */
__STATIC_INLINE void LL_POSENC_EnableStrobeResync(POSENC_TypeDef *p_posenc)
{
  STM32_CLEAR_BIT(p_posenc->CR1, POSENC_CR1_NSTRBRSYNC);
}

/**
  * @brief  Disable Strobe re-synchronization.
  * @rmtoll
  *  CR1         NSTRBRSYNC         LL_POSENC_DisableStrobeResync
  * @param  p_posenc POSENC instance.
  * @note  Strobe re-synchronization must only be disabled when the selected trigger source and POSENC are synchronous.
  *        This field is locked by hardware once ENCSEL[3:0] selects a protocol.
  */
__STATIC_INLINE void LL_POSENC_DisableStrobeResync(POSENC_TypeDef *p_posenc)
{
  STM32_SET_BIT(p_posenc->CR1, POSENC_CR1_NSTRBRSYNC);
}

/**
  * @brief  Get Strobe re-synchronization state.
  * @rmtoll
  *  CR1         NSTRBRSYNC         LL_POSENC_IsEnabledStrobeResync
  * @param p_posenc Position encoder instance.
  * @retval State of Strobe re-synchronization (1 or 0).
  */
__STATIC_INLINE uint32_t LL_POSENC_IsEnabledStrobeResync(const POSENC_TypeDef *p_posenc)
{
  return ((STM32_READ_BIT(p_posenc->CR1, POSENC_CR1_NSTRBRSYNC) == 0UL) ? 1UL : 0UL);
}

/**
  * @brief  Set strobe source selection.
  * @rmtoll
  *  CR1         STRBSEL         LL_POSENC_SetStrobeSource
  * @param  p_posenc POSENC instance.
  * @param  strobe This parameter can be one of the following values:
  *         @arg @ref LL_POSENC_STROBE_TIM1_TRGO
  *         @arg @ref LL_POSENC_STROBE_TIM1_TRGO2
  *         @arg @ref LL_POSENC_STROBE_TIM8_TRGO
  *         @arg @ref LL_POSENC_STROBE_TIM8_TRGO2
  *         @arg @ref LL_POSENC_STROBE_TIM9_TRGO
  *         @arg @ref LL_POSENC_STROBE_TIM12_TRGO
  *         @arg @ref LL_POSENC_STROBE_TIM20_TRGO
  *         @arg @ref LL_POSENC_STROBE_TIM20_TRGO2
  *         @arg @ref LL_POSENC_STROBE_TIM26_TRGO
  *         @arg @ref LL_POSENC_STROBE_TIM27_TRGO
  *         @arg @ref LL_POSENC_STROBE_HRTIM1_ADC_TRIG1
  *         @arg @ref LL_POSENC_STROBE_HRTIM1_ADC_TRIG3
  *         @arg @ref LL_POSENC_STROBE_EXTI10
  *         @arg @ref LL_POSENC_STROBE_PLAY1_OUT7
  *         @arg @ref LL_POSENC_STROBE_EXTI12
  *         @arg @ref LL_POSENC_STROBE_PLAY1_OUT10
  * @note  This field is locked by hardware once ENCSEL[3:0] selects a protocol.
  */
__STATIC_INLINE void LL_POSENC_SetStrobeSource(POSENC_TypeDef *p_posenc, uint32_t strobe)
{
  STM32_MODIFY_REG(p_posenc->CR1, POSENC_CR1_STRBSEL, strobe);
}

/**
  * @brief  Get strobe selection.
  * @rmtoll
  *  CR1         STRBSEL         LL_POSENC_GetStrobeSource
  * @param  p_posenc POSENC instance.
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_POSENC_STROBE_TIM1_TRGO
  *         @arg @ref LL_POSENC_STROBE_TIM1_TRGO2
  *         @arg @ref LL_POSENC_STROBE_TIM8_TRGO
  *         @arg @ref LL_POSENC_STROBE_TIM8_TRGO2
  *         @arg @ref LL_POSENC_STROBE_TIM9_TRGO
  *         @arg @ref LL_POSENC_STROBE_TIM12_TRGO
  *         @arg @ref LL_POSENC_STROBE_TIM20_TRGO
  *         @arg @ref LL_POSENC_STROBE_TIM20_TRGO2
  *         @arg @ref LL_POSENC_STROBE_TIM26_TRGO
  *         @arg @ref LL_POSENC_STROBE_TIM27_TRGO
  *         @arg @ref LL_POSENC_STROBE_HRTIM1_ADC_TRIG1
  *         @arg @ref LL_POSENC_STROBE_HRTIM1_ADC_TRIG3
  *         @arg @ref LL_POSENC_STROBE_EXTI10
  *         @arg @ref LL_POSENC_STROBE_PLAY1_OUT7
  *         @arg @ref LL_POSENC_STROBE_EXTI12
  *         @arg @ref LL_POSENC_STROBE_PLAY1_OUT10
  */
__STATIC_INLINE uint32_t LL_POSENC_GetStrobeSource(const POSENC_TypeDef *p_posenc)
{
  return (STM32_READ_BIT(p_posenc->CR1, POSENC_CR1_STRBSEL));
}

/**
  * @brief  Set Hiperface-DSL fast position event-driven accesses.
  * @rmtoll
  *  CR2         HDPOS         LL_POSENC_HD_SetEventDrivenFastPosition
  * @param  p_posenc POSENC instance.
  * @param  position_mode This parameter can be one of the following values:
  *         @arg @ref LL_POSENC_HD_EVTDRV_FASTPOSITION_DISABLED
  *         @arg @ref LL_POSENC_HD_EVTDRV_FASTPOSITION_24BIT
  *         @arg @ref LL_POSENC_HD_EVTDRV_FASTPOSITION_32BIT
  *         @arg @ref LL_POSENC_HD_EVTDRV_FASTPOSITION_40BIT
  * @note  Configure this field before Hiperface-DSL reception starts.
  */
__STATIC_INLINE void LL_POSENC_HD_SetEventDrivenFastPosition(POSENC_TypeDef *p_posenc, uint32_t position_mode)
{
  STM32_MODIFY_REG(p_posenc->CR2, POSENC_CR2_HDPOS, position_mode);
}

/**
  * @brief  Get Hiperface-DSL fast position event-driven accesses.
  * @rmtoll
  *  CR2         HDPOS         LL_POSENC_HD_GetEventDrivenFastPosition
  * @param  p_posenc POSENC instance.
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_POSENC_HD_EVTDRV_FASTPOSITION_DISABLED
  *         @arg @ref LL_POSENC_HD_EVTDRV_FASTPOSITION_24BIT
  *         @arg @ref LL_POSENC_HD_EVTDRV_FASTPOSITION_32BIT
  *         @arg @ref LL_POSENC_HD_EVTDRV_FASTPOSITION_40BIT
  */
__STATIC_INLINE uint32_t LL_POSENC_HD_GetEventDrivenFastPosition(const POSENC_TypeDef *p_posenc)
{
  return (STM32_READ_BIT(p_posenc->CR2, POSENC_CR2_HDPOS));
}

/**
  * @brief  Enable Hiperface-DSL velocity event-driven accesses.
  * @rmtoll
  *  CR2         HDVEL         LL_POSENC_HD_EnableEventDrivenVelocity
  * @param  p_posenc POSENC instance.
  */
__STATIC_INLINE void LL_POSENC_HD_EnableEventDrivenVelocity(POSENC_TypeDef *p_posenc)
{
  STM32_SET_BIT(p_posenc->CR2, POSENC_CR2_HDVEL);
}

/**
  * @brief  Disable Hiperface-DSL velocity event-driven accesses.
  * @rmtoll
  *  CR2         HDVEL         LL_POSENC_HD_DisableEventDrivenVelocity
  * @param  p_posenc POSENC instance.
  */
__STATIC_INLINE void LL_POSENC_HD_DisableEventDrivenVelocity(POSENC_TypeDef *p_posenc)
{
  STM32_CLEAR_BIT(p_posenc->CR2, POSENC_CR2_HDVEL);
}

/**
  * @brief  Check whether Hiperface-DSL velocity event-driven accesses are enabled.
  * @rmtoll
  *  CR2         HDVEL         LL_POSENC_HD_IsEnabledEventDrivenVelocity
  * @param  p_posenc POSENC instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_POSENC_HD_IsEnabledEventDrivenVelocity(const POSENC_TypeDef *p_posenc)
{
  return ((STM32_READ_BIT(p_posenc->CR2, POSENC_CR2_HDVEL) == POSENC_CR2_HDVEL) ? 1UL : 0UL);
}

/**
  * @brief  Set Hiperface-DSL safe position 1 event-driven accesses.
  * @rmtoll
  *  CR2         HDVPOS         LL_POSENC_HD_SetEventDrivenSafePosition_1
  * @param  p_posenc POSENC instance.
  * @param  event_position_mode This parameter can be one of the following values:
  *         @arg @ref LL_POSENC_HD_EVTDRV_SAFE_POSITION_1_DISABLED
  *         @arg @ref LL_POSENC_HD_EVTDRV_SAFE_POSITION_1_24BIT
  *         @arg @ref LL_POSENC_HD_EVTDRV_SAFE_POSITION_1_32BIT
  *         @arg @ref LL_POSENC_HD_EVTDRV_SAFE_POSITION_1_40BIT
  * @note  Configure this field before Hiperface-DSL reception starts.
  */
__STATIC_INLINE void LL_POSENC_HD_SetEventDrivenSafePosition_1(POSENC_TypeDef *p_posenc, uint32_t event_position_mode)
{
  STM32_MODIFY_REG(p_posenc->CR2, POSENC_CR2_HDVPOS, event_position_mode);
}

/**
  * @brief  Get Hiperface-DSL safe position 1 event-driven accesses.
  * @rmtoll
  *  CR2         HDVPOS         LL_POSENC_HD_GetEventDrivenSafePosition_1
  * @param  p_posenc POSENC instance.
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_POSENC_HD_EVTDRV_SAFE_POSITION_1_DISABLED
  *         @arg @ref LL_POSENC_HD_EVTDRV_SAFE_POSITION_1_24BIT
  *         @arg @ref LL_POSENC_HD_EVTDRV_SAFE_POSITION_1_32BIT
  *         @arg @ref LL_POSENC_HD_EVTDRV_SAFE_POSITION_1_40BIT
  */
__STATIC_INLINE uint32_t LL_POSENC_HD_GetEventDrivenSafePosition_1(const POSENC_TypeDef *p_posenc)
{
  return (STM32_READ_BIT(p_posenc->CR2, POSENC_CR2_HDVPOS));
}

/**
  * @brief  Enable Hiperface-DSL safe position 1 CRC event-driven accesses.
  * @rmtoll
  *  CR2         HDVPOSCRC         LL_POSENC_HD_EnableEventDrivenSafePosition_1_CRC
  * @param  p_posenc POSENC instance.
  */
__STATIC_INLINE void LL_POSENC_HD_EnableEventDrivenSafePosition_1_CRC(POSENC_TypeDef *p_posenc)
{
  STM32_SET_BIT(p_posenc->CR2, POSENC_CR2_HDVPOSCRC);
}

/**
  * @brief  Disable Hiperface-DSL safe position 1 CRC event-driven accesses.
  * @rmtoll
  *  CR2         HDVPOSCRC         LL_POSENC_HD_DisableEventDrivenSafePosition_1_CRC
  * @param  p_posenc POSENC instance.
  */
__STATIC_INLINE void LL_POSENC_HD_DisableEventDrivenSafePosition_1_CRC(POSENC_TypeDef *p_posenc)
{
  STM32_CLEAR_BIT(p_posenc->CR2, POSENC_CR2_HDVPOSCRC);
}

/**
  * @brief  Check whether Hiperface-DSL safe position 1 CRC event-driven accesses are enabled.
  * @rmtoll
  *  CR2         HDVPOSCRC         LL_POSENC_HD_IsEnabledEventDrivenSafePosition_1_CRC
  * @param  p_posenc POSENC instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_POSENC_HD_IsEnabledEventDrivenSafePosition_1_CRC(const POSENC_TypeDef *p_posenc)
{
  return ((STM32_READ_BIT(p_posenc->CR2, POSENC_CR2_HDVPOSCRC) == POSENC_CR2_HDVPOSCRC) ? 1UL : 0UL);
}

/**
  * @brief Freeze Hiperface-DSL registers.
  * @rmtoll
  *  CR2         HDFRZ         LL_POSENC_HD_FreezeRegister
  * @param  p_posenc POSENC instance.
  * @note Freeze mechanism is used to prevent the Hiperface-DSL registers from
  *       being updated. This must be used to guarantee the coherency of the
  *       data between two consecutive accesses.
  *       Please refer to Reference Manual for read access procedure.
  */
__STATIC_INLINE void LL_POSENC_HD_FreezeRegister(POSENC_TypeDef *p_posenc)
{
  STM32_SET_BIT(p_posenc->CR2, POSENC_CR2_HDFRZ);
}

/**
  * @brief  Un-freeze Hiperface-DSL registers.
  * @rmtoll
  *  CR2         HDFRZ         LL_POSENC_HD_UnFreezeRegister
  * @param p_posenc Position encoder instance.
  */
__STATIC_INLINE void LL_POSENC_HD_UnFreezeRegister(POSENC_TypeDef *p_posenc)
{
  STM32_CLEAR_BIT(p_posenc->CR2, POSENC_CR2_HDFRZ);
}

/**
  * @brief Get Hiperface-DSL freeze state.
  * @rmtoll
  *  CR2         HDFRZ         LL_POSENC_HD_IsRegisterFrozen
  * @param p_posenc Position encoder instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_POSENC_HD_IsRegisterFrozen(const POSENC_TypeDef *p_posenc)
{
  return ((STM32_READ_BIT(p_posenc->CR2, POSENC_CR2_HDFRZ) == POSENC_CR2_HDFRZ) ? 1UL : 0UL);
}

/**
  * @brief  Get state of POSENC interrupt.
  * @rmtoll
  *  IER      GTC              LL_POSENC_IsEnabledIT \n
  *  IER      WRTC             LL_POSENC_IsEnabledIT \n
  *  IER      D0RTC            LL_POSENC_IsEnabledIT \n
  *  IER      D1RTC            LL_POSENC_IsEnabledIT \n
  *  IER      HDVPOSCRCTC      LL_POSENC_IsEnabledIT \n
  *  IER      HDVPOSTC         LL_POSENC_IsEnabledIT \n
  *  IER      HDVELTC          LL_POSENC_IsEnabledIT \n
  *  IER      HDFPOSTC         LL_POSENC_IsEnabledIT \n
  *  IER      HDFPOS           LL_POSENC_IsEnabledIT \n
  *  IER      HDVPOS1          LL_POSENC_IsEnabledIT \n
  *  IER      HDVPOS2          LL_POSENC_IsEnabledIT \n
  *  IER      HDFREL           LL_POSENC_IsEnabledIT \n
  *  IER      HDFRES           LL_POSENC_IsEnabledIT
  * @param  p_posenc POSENC instance.
  * @param  it   This parameter can be one of the following values:
  *         @arg @ref LL_POSENC_IT_GTC
  *         @arg @ref LL_POSENC_IT_WRTC
  *         @arg @ref LL_POSENC_IT_D0RTC
  *         @arg @ref LL_POSENC_IT_D1RTC
  *         @arg @ref LL_POSENC_IT_HDVPOSCRCTC
  *         @arg @ref LL_POSENC_IT_HDVPOSTC
  *         @arg @ref LL_POSENC_IT_HDVELTC
  *         @arg @ref LL_POSENC_IT_HDFPOSTC
  *         @arg @ref LL_POSENC_IT_HDFPOS
  *         @arg @ref LL_POSENC_IT_HDVPOS1
  *         @arg @ref LL_POSENC_IT_HDVPOS2
  *         @arg @ref LL_POSENC_IT_HDFREL
  *         @arg @ref LL_POSENC_IT_HDFRES
  *         @arg @ref LL_POSENC_IT_ALL
  * @note   Generic function with interrupt selected as parameter.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_POSENC_IsEnabledIT(const POSENC_TypeDef *p_posenc, uint32_t it)
{
  return ((STM32_READ_BIT(p_posenc->IER, it) == (it)) ? 1UL : 0UL);
}

/**
  * @brief  Disable POSENC interrupt.
  * @rmtoll
  *  IER       GTC           LL_POSENC_DisableIT \n
  *  IER       WRTC          LL_POSENC_DisableIT \n
  *  IER       D0RTC         LL_POSENC_DisableIT \n
  *  IER       D1RTC         LL_POSENC_DisableIT \n
  *  IER       HDVPOSCRCTC   LL_POSENC_DisableIT \n
  *  IER       HDVPOSTC      LL_POSENC_DisableIT \n
  *  IER       HDVELTC       LL_POSENC_DisableIT \n
  *  IER       HDFPOSTC      LL_POSENC_DisableIT \n
  *  IER       HDFPOS        LL_POSENC_DisableIT \n
  *  IER       HDVPOS1       LL_POSENC_DisableIT \n
  *  IER       HDVPOS2       LL_POSENC_DisableIT \n
  *  IER       HDFREL        LL_POSENC_DisableIT \n
  *  IER       HDFRES        LL_POSENC_DisableIT
  * @param  p_posenc POSENC instance.
  * @param  it   This parameter can be a combination of the following values:
  *         @arg @ref LL_POSENC_IT_GTC
  *         @arg @ref LL_POSENC_IT_WRTC
  *         @arg @ref LL_POSENC_IT_D0RTC
  *         @arg @ref LL_POSENC_IT_D1RTC
  *         @arg @ref LL_POSENC_IT_HDVPOSCRCTC
  *         @arg @ref LL_POSENC_IT_HDVPOSTC
  *         @arg @ref LL_POSENC_IT_HDVELTC
  *         @arg @ref LL_POSENC_IT_HDFPOSTC
  *         @arg @ref LL_POSENC_IT_HDFPOS
  *         @arg @ref LL_POSENC_IT_HDVPOS1
  *         @arg @ref LL_POSENC_IT_HDVPOS2
  *         @arg @ref LL_POSENC_IT_HDFREL
  *         @arg @ref LL_POSENC_IT_HDFRES
  *         @arg @ref LL_POSENC_IT_ALL
  * @note   Generic function with interrupt selected as parameter.
  *         Optimized functions for each flag are also available.
  */
__STATIC_INLINE void LL_POSENC_DisableIT(POSENC_TypeDef *p_posenc, uint32_t it)
{
  STM32_CLEAR_BIT(p_posenc->IER, it);
}

/**
  * @brief  Enable POSENC interrupt.
  * @rmtoll
  *  IER       GTC           LL_POSENC_EnableIT \n
  *  IER       WRTC          LL_POSENC_EnableIT \n
  *  IER       D0RTC         LL_POSENC_EnableIT \n
  *  IER       D1RTC         LL_POSENC_EnableIT \n
  *  IER       HDVPOSCRCTC   LL_POSENC_EnableIT \n
  *  IER       HDVPOSTC      LL_POSENC_EnableIT \n
  *  IER       HDVELTC       LL_POSENC_EnableIT \n
  *  IER       HDFPOSTC      LL_POSENC_EnableIT \n
  *  IER       HDFPOS        LL_POSENC_EnableIT \n
  *  IER       HDVPOS1       LL_POSENC_EnableIT \n
  *  IER       HDVPOS2       LL_POSENC_EnableIT \n
  *  IER       HDFREL        LL_POSENC_EnableIT \n
  *  IER       HDFRES        LL_POSENC_EnableIT
  * @param  p_posenc POSENC instance.
  * @param  it   This parameter can be a combination of the following values:
  *         @arg @ref LL_POSENC_IT_GTC
  *         @arg @ref LL_POSENC_IT_WRTC
  *         @arg @ref LL_POSENC_IT_D0RTC
  *         @arg @ref LL_POSENC_IT_D1RTC
  *         @arg @ref LL_POSENC_IT_HDVPOSCRCTC
  *         @arg @ref LL_POSENC_IT_HDVPOSTC
  *         @arg @ref LL_POSENC_IT_HDVELTC
  *         @arg @ref LL_POSENC_IT_HDFPOSTC
  *         @arg @ref LL_POSENC_IT_HDFPOS
  *         @arg @ref LL_POSENC_IT_HDVPOS1
  *         @arg @ref LL_POSENC_IT_HDVPOS2
  *         @arg @ref LL_POSENC_IT_HDFREL
  *         @arg @ref LL_POSENC_IT_HDFRES
  *         @arg @ref LL_POSENC_IT_ALL
  * @note   Generic function with interrupt selected as parameter.
  */
__STATIC_INLINE void LL_POSENC_EnableIT(POSENC_TypeDef *p_posenc, uint32_t it)
{
  STM32_SET_BIT(p_posenc->IER, it);
}

/**
  * @brief  Clear POSENC interrupt flag.
  * @rmtoll
  *  ICR       GTC           LL_POSENC_ClearFlag \n
  *  ICR       WRTC          LL_POSENC_ClearFlag \n
  *  ICR       D0RTC         LL_POSENC_ClearFlag \n
  *  ICR       D1RTC         LL_POSENC_ClearFlag \n
  *  ICR       HDVPOSCRCTC   LL_POSENC_ClearFlag \n
  *  ICR       HDVPOSTC      LL_POSENC_ClearFlag \n
  *  ICR       HDVELTC       LL_POSENC_ClearFlag \n
  *  ICR       HDFPOSTC      LL_POSENC_ClearFlag \n
  *  ICR       HDFPOS        LL_POSENC_ClearFlag \n
  *  ICR       HDVPOS1       LL_POSENC_ClearFlag \n
  *  ICR       HDVPOS2       LL_POSENC_ClearFlag \n
  *  ICR       HDFREL        LL_POSENC_ClearFlag \n
  *  ICR       HDFRES        LL_POSENC_ClearFlag
  * @param  p_posenc POSENC instance.
  * @param  flag This parameter can be a combination of the following values:
  *         @arg @ref LL_POSENC_IT_GTC
  *         @arg @ref LL_POSENC_IT_WRTC
  *         @arg @ref LL_POSENC_IT_D0RTC
  *         @arg @ref LL_POSENC_IT_D1RTC
  *         @arg @ref LL_POSENC_IT_HDVPOSCRCTC
  *         @arg @ref LL_POSENC_IT_HDVPOSTC
  *         @arg @ref LL_POSENC_IT_HDVELTC
  *         @arg @ref LL_POSENC_IT_HDFPOSTC
  *         @arg @ref LL_POSENC_IT_HDFPOS
  *         @arg @ref LL_POSENC_IT_HDVPOS1
  *         @arg @ref LL_POSENC_IT_HDVPOS2
  *         @arg @ref LL_POSENC_IT_HDFREL
  *         @arg @ref LL_POSENC_IT_HDFRES
  *         @arg @ref LL_POSENC_IT_ALL
  * @note   Generic function with flag selected as parameter.
  */
__STATIC_INLINE void LL_POSENC_ClearFlag(POSENC_TypeDef *p_posenc, uint32_t flag)
{
  STM32_SET_BIT(p_posenc->ICR, flag);
}

/**
  * @brief  Get POSENC interrupt flag.
  * @rmtoll
  *  ISR       GTC           LL_POSENC_GetFlag \n
  *  ISR       WRTC          LL_POSENC_GetFlag \n
  *  ISR       D0RTC         LL_POSENC_GetFlag \n
  *  ISR       D1RTC         LL_POSENC_GetFlag \n
  *  ISR       HDVPOSCRCTC   LL_POSENC_GetFlag \n
  *  ISR       HDVPOSTC      LL_POSENC_GetFlag \n
  *  ISR       HDVELTC       LL_POSENC_GetFlag \n
  *  ISR       HDFPOSTC      LL_POSENC_GetFlag \n
  *  ISR       HDFPOS        LL_POSENC_GetFlag \n
  *  ISR       HDVPOS1       LL_POSENC_GetFlag \n
  *  ISR       HDVPOS2       LL_POSENC_GetFlag \n
  *  ISR       HDFREL        LL_POSENC_GetFlag \n
  *  ISR       HDFRES        LL_POSENC_GetFlag
  * @param  p_posenc POSENC instance.
  * @param  flag This parameter can be a combination of the following values:
  *         @arg @ref LL_POSENC_IT_GTC
  *         @arg @ref LL_POSENC_IT_WRTC
  *         @arg @ref LL_POSENC_IT_D0RTC
  *         @arg @ref LL_POSENC_IT_D1RTC
  *         @arg @ref LL_POSENC_IT_HDVPOSCRCTC
  *         @arg @ref LL_POSENC_IT_HDVPOSTC
  *         @arg @ref LL_POSENC_IT_HDVELTC
  *         @arg @ref LL_POSENC_IT_HDFPOSTC
  *         @arg @ref LL_POSENC_IT_HDFPOS
  *         @arg @ref LL_POSENC_IT_HDVPOS1
  *         @arg @ref LL_POSENC_IT_HDVPOS2
  *         @arg @ref LL_POSENC_IT_HDFREL
  *         @arg @ref LL_POSENC_IT_HDFRES
  *         @arg @ref LL_POSENC_IT_ALL
  * @note   Generic function with flag selected as parameter.
  */
__STATIC_INLINE uint32_t LL_POSENC_GetFlag(const POSENC_TypeDef *p_posenc, uint32_t flag)
{
  return ((STM32_READ_BIT(p_posenc->ISR, flag) == flag) ? 1UL : 0UL);
}

/**
  * @brief  Get state of masked POSENC interrupt flag.
  * @rmtoll
  *  MISR       GTC           LL_POSENC_IsMaskedITFlag \n
  *  MISR       WRTC          LL_POSENC_IsMaskedITFlag \n
  *  MISR       D0RTC         LL_POSENC_IsMaskedITFlag \n
  *  MISR       D1RTC         LL_POSENC_IsMaskedITFlag \n
  *  MISR       HDVPOSCRCTC   LL_POSENC_IsMaskedITFlag \n
  *  MISR       HDVPOSTC      LL_POSENC_IsMaskedITFlag \n
  *  MISR       HDVELTC       LL_POSENC_IsMaskedITFlag \n
  *  MISR       HDFPOSTC      LL_POSENC_IsMaskedITFlag \n
  *  MISR       HDFPOS        LL_POSENC_IsMaskedITFlag \n
  *  MISR       HDVPOS1       LL_POSENC_IsMaskedITFlag \n
  *  MISR       HDVPOS2       LL_POSENC_IsMaskedITFlag \n
  *  MISR       HDFREL        LL_POSENC_IsMaskedITFlag \n
  *  MISR       HDFRES        LL_POSENC_IsMaskedITFlag
  * @param  p_posenc POSENC instance.
  * @param  flag This parameter can be a combination of the following values:
  *         @arg @ref LL_POSENC_IT_GTC
  *         @arg @ref LL_POSENC_IT_WRTC
  *         @arg @ref LL_POSENC_IT_D0RTC
  *         @arg @ref LL_POSENC_IT_D1RTC
  *         @arg @ref LL_POSENC_IT_HDVPOSCRCTC
  *         @arg @ref LL_POSENC_IT_HDVPOSTC
  *         @arg @ref LL_POSENC_IT_HDVELTC
  *         @arg @ref LL_POSENC_IT_HDFPOSTC
  *         @arg @ref LL_POSENC_IT_HDFPOS
  *         @arg @ref LL_POSENC_IT_HDVPOS1
  *         @arg @ref LL_POSENC_IT_HDVPOS2
  *         @arg @ref LL_POSENC_IT_HDFREL
  *         @arg @ref LL_POSENC_IT_HDFRES
  *         @arg @ref LL_POSENC_IT_ALL
  * @note   Generic function with flag selected as parameter.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_POSENC_IsMaskedITFlag(const POSENC_TypeDef *p_posenc, uint32_t flag)
{
  return ((STM32_READ_BIT(p_posenc->MISR, flag) == flag) ? 1UL : 0UL);
}

/**
  * @brief  Get POSENC status flag.
  * @rmtoll
  *  SR1       HDINTS         LL_POSENC_GetStatus \n
  *  SR1       HDINT          LL_POSENC_GetStatus \n
  *  SR1       D1RDBSY        LL_POSENC_GetStatus \n
  *  SR1       D0RDBSY        LL_POSENC_GetStatus \n
  *  SR1       WRBSY          LL_POSENC_GetStatus \n
  *  SR1       GBSY           LL_POSENC_GetStatus
  * @param  p_posenc POSENC instance.
  * @param  status This parameter can be a combination of the following values:
  *         @arg @ref LL_POSENC_STATUS_GLOBAL_BUSY
  *         @arg @ref LL_POSENC_STATUS_WRITE_BUSY
  *         @arg @ref LL_POSENC_STATUS_DATA_0_BUSY
  *         @arg @ref LL_POSENC_STATUS_DATA_1_BUSY
  *         @arg @ref LL_POSENC_STATUS_HD_IT
  *         @arg @ref LL_POSENC_STATUS_HD_IT_S
  *         @arg @ref LL_POSENC_STATUS_ALL
  * @note   Generic function with status selected as parameter.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_POSENC_GetStatus(const POSENC_TypeDef *p_posenc, uint32_t status)
{
  return ((STM32_READ_BIT(p_posenc->SR1, status) == status) ? 1UL : 0UL);
}

/**
  * @brief  Get Online status D interface.
  * @rmtoll
  *  SR2         ONLINESTATUSD         LL_POSENC_GetOnlineStatusD
  * @param  p_posenc POSENC instance.
  * @return HiperfaceDSL Online Status D
  */
__STATIC_INLINE uint32_t LL_POSENC_GetOnlineStatusD(const POSENC_TypeDef *p_posenc)
{
  return (STM32_READ_BIT(p_posenc->SR2, POSENC_SR2_ONLINESTATUSD));
}

/**
  * @brief  Get Online status safe 1 interface.
  * @rmtoll
  *  SR2         ONLINESTATUS1         LL_POSENC_GetOnlineStatus1
  * @param  p_posenc POSENC instance.
  * @return HiperfaceDSL Online Status 1
  */
__STATIC_INLINE uint32_t LL_POSENC_GetOnlineStatus1(const POSENC_TypeDef *p_posenc)
{
  return (STM32_READ_BIT(p_posenc->SR2, POSENC_SR2_ONLINESTATUS1)) >> POSENC_SR2_ONLINESTATUS1_Pos;
}

/**
  * @brief  Get Online status safe 2 interface.
  * @rmtoll
  *  SR3         ONLINESTATUS2         LL_POSENC_GetOnlineStatus2
  * @param  p_posenc POSENC instance.
  * @return  HiperfaceDSL Online Status 2
  */
__STATIC_INLINE uint32_t LL_POSENC_GetOnlineStatus2(const POSENC_TypeDef *p_posenc)
{
  return (STM32_READ_BIT(p_posenc->SR3, POSENC_SR3_ONLINESTATUS2));
}

/**
  * @brief  Set data 0 read address and start read transaction.
  * @rmtoll
  *  D0AR         D0ADD         LL_POSENC_RequestReadData0
  * @param  p_posenc POSENC instance.
  * @param  address This parameter can be a combination of the following values:
  *         @arg @ref LL_POSENC_HD_CTRLR
  *         @arg @ref LL_POSENC_HD_MASTER_QMR
  *         @arg @ref LL_POSENC_HD_EVENTR
  *         @arg @ref LL_POSENC_HD_MASKR
  *         @arg @ref LL_POSENC_HD_EDGESR
  *         @arg @ref LL_POSENC_HD_DELAYR
  *         @arg @ref LL_POSENC_HD_VRS_RELR
  *         @arg @ref LL_POSENC_HD_ENC_IDR
  *         @arg @ref LL_POSENC_HD_FPOSSTR
  *         @arg @ref LL_POSENC_HD_FPOSMT1
  *         @arg @ref LL_POSENC_HD_FPOSMT2
  *         @arg @ref LL_POSENC_HD_VELR
  *         @arg @ref LL_POSENC_HD_VPOSST
  *         @arg @ref LL_POSENC_HD_VPOSMT1
  *         @arg @ref LL_POSENC_HD_VPOSMT2
  *         @arg @ref LL_POSENC_HD_VPOSCRC
  *         @arg @ref LL_POSENC_HD_PCBUFA
  *         @arg @ref LL_POSENC_HD_PCBUFB
  *         @arg @ref LL_POSENC_HD_PCBUFC
  *         @arg @ref LL_POSENC_HD_LOFFR
  *         @arg @ref LL_POSENC_HD_PC_ADDR
  *         @arg @ref LL_POSENC_HD_PC_OFFR
  *         @arg @ref LL_POSENC_HD_PC_ADDOFFR
  *         @arg @ref LL_POSENC_HD_PC_CTRLR
  *         @arg @ref LL_POSENC_HD_PIPE_SR
  *         @arg @ref LL_POSENC_HD_PIPE_D
  *         @arg @ref LL_POSENC_HD_SAFE_CTRL
  *         @arg @ref LL_POSENC_HD_SAFE_SUM
  *         @arg @ref LL_POSENC_HD_S_PC_DATA
  *         @arg @ref LL_POSENC_HD_ACC_EE_CNT
  *         @arg @ref LL_POSENC_HD_MAXACC
  *         @arg @ref LL_POSENC_HD_MAXDEV
  *         @arg @ref LL_POSENC_HD_EVENT_S
  *         @arg @ref LL_POSENC_HD_MASK_S
  *         @arg @ref LL_POSENC_HD_DUMMY
  *         @arg @ref LL_POSENC_HD_ST0
  *         @arg @ref LL_POSENC_HD_ST1
  *         @arg @ref LL_POSENC_HD_ST2
  *         @arg @ref LL_POSENC_HD_ST3
  *         @arg @ref LL_POSENC_HD_ST4
  *         @arg @ref LL_POSENC_HD_ST5
  *         @arg @ref LL_POSENC_HD_ST6
  *         @arg @ref LL_POSENC_HD_ST7
  *         @arg @ref LL_POSENC_HD_SRSSI
  *         @arg @ref LL_POSENC_HD_MAIL
  *         @arg @ref LL_POSENC_HD_PING
  * @note   Before issuing a new Data 0 software-driven read request, make sure that LL_POSENC_STATUS_DATA_0_BUSY is
  *         reset.
  */
__STATIC_INLINE void LL_POSENC_RequestReadData0(POSENC_TypeDef *p_posenc, uint32_t address)
{
  STM32_MODIFY_REG(p_posenc->D0AR, POSENC_D0AR_D0ADD, address);
}

/**
  * @brief  Get data 0 read address.
  * @rmtoll
  *  D0AR         D0ADD         LL_POSENC_GetReadData0RequestAddress
  * @param  p_posenc POSENC instance.
  * @return Requested address in the Hiperface DSL (32-bit translated address)
  */
__STATIC_INLINE uint32_t LL_POSENC_GetReadData0RequestAddress(const POSENC_TypeDef *p_posenc)
{
  return (STM32_READ_BIT(p_posenc->D0AR, POSENC_D0AR_D0ADD));
}

/**
  * @brief  Set data 1 read address and start read transaction.
  * @rmtoll
  *  D1AR         D1ADD         LL_POSENC_RequestReadData1
  * @param  p_posenc POSENC instance.
  * @param  address This parameter can be a combination of the following values:
  *         @arg @ref LL_POSENC_HD_CTRLR
  *         @arg @ref LL_POSENC_HD_MASTER_QMR
  *         @arg @ref LL_POSENC_HD_EVENTR
  *         @arg @ref LL_POSENC_HD_MASKR
  *         @arg @ref LL_POSENC_HD_EDGESR
  *         @arg @ref LL_POSENC_HD_DELAYR
  *         @arg @ref LL_POSENC_HD_VRS_RELR
  *         @arg @ref LL_POSENC_HD_ENC_IDR
  *         @arg @ref LL_POSENC_HD_FPOSSTR
  *         @arg @ref LL_POSENC_HD_FPOSMT1
  *         @arg @ref LL_POSENC_HD_FPOSMT2
  *         @arg @ref LL_POSENC_HD_VELR
  *         @arg @ref LL_POSENC_HD_VPOSST
  *         @arg @ref LL_POSENC_HD_VPOSMT1
  *         @arg @ref LL_POSENC_HD_VPOSMT2
  *         @arg @ref LL_POSENC_HD_VPOSCRC
  *         @arg @ref LL_POSENC_HD_PCBUFA
  *         @arg @ref LL_POSENC_HD_PCBUFB
  *         @arg @ref LL_POSENC_HD_PCBUFC
  *         @arg @ref LL_POSENC_HD_LOFFR
  *         @arg @ref LL_POSENC_HD_PC_ADDR
  *         @arg @ref LL_POSENC_HD_PC_OFFR
  *         @arg @ref LL_POSENC_HD_PC_ADDOFFR
  *         @arg @ref LL_POSENC_HD_PC_CTRLR
  *         @arg @ref LL_POSENC_HD_PIPE_SR
  *         @arg @ref LL_POSENC_HD_PIPE_D
  *         @arg @ref LL_POSENC_HD_SAFE_CTRL
  *         @arg @ref LL_POSENC_HD_SAFE_SUM
  *         @arg @ref LL_POSENC_HD_S_PC_DATA
  *         @arg @ref LL_POSENC_HD_ACC_EE_CNT
  *         @arg @ref LL_POSENC_HD_MAXACC
  *         @arg @ref LL_POSENC_HD_MAXDEV
  *         @arg @ref LL_POSENC_HD_EVENT_S
  *         @arg @ref LL_POSENC_HD_MASK_S
  *         @arg @ref LL_POSENC_HD_DUMMY
  *         @arg @ref LL_POSENC_HD_ST0
  *         @arg @ref LL_POSENC_HD_ST1
  *         @arg @ref LL_POSENC_HD_ST2
  *         @arg @ref LL_POSENC_HD_ST3
  *         @arg @ref LL_POSENC_HD_ST4
  *         @arg @ref LL_POSENC_HD_ST5
  *         @arg @ref LL_POSENC_HD_ST6
  *         @arg @ref LL_POSENC_HD_ST7
  *         @arg @ref LL_POSENC_HD_SRSSI
  *         @arg @ref LL_POSENC_HD_MAIL
  *         @arg @ref LL_POSENC_HD_PING
  * @note   Before issuing a new Data 1 software-driven read request, make sure that LL_POSENC_STATUS_DATA_1_BUSY is
  *         reset.
  */
__STATIC_INLINE void LL_POSENC_RequestReadData1(POSENC_TypeDef *p_posenc, uint32_t address)
{
  STM32_MODIFY_REG(p_posenc->D1AR, POSENC_D1AR_D1ADD, address);
}

/**
  * @brief  Get data 1 read address.
  * @rmtoll
  *  D1AR         D1ADD         LL_POSENC_GetReadData1RequestAddress
  * @param  p_posenc POSENC instance.
  * @return Requested address in the Hiperface DSL (32-bit translated address)
  */
__STATIC_INLINE uint32_t LL_POSENC_GetReadData1RequestAddress(const POSENC_TypeDef *p_posenc)
{
  return (STM32_READ_BIT(p_posenc->D1AR, POSENC_D1AR_D1ADD));
}

/**
  * @brief Read Requested register value (Software-driven read access).
  * @rmtoll
  *  D0R         D0         LL_POSENC_ReadRequestedData0
  * @param  p_posenc POSENC instance.
  * @note  This function returns a 32--bit value from the requested register.
  *        Refer to the reference manual for data management.
  *        (table "Hiperface-DSL Address conversion table")
  *        Data is valid once the D0RTC flag is set.
  * @return Requested data0 register value
  */
__STATIC_INLINE uint32_t LL_POSENC_ReadRequestedData0(const POSENC_TypeDef *p_posenc)
{
  return (STM32_READ_BIT(p_posenc->D0R, POSENC_D0R_D0));
}

/**
  * @brief Read Requested register value (Software-driven read access).
  * @rmtoll
  *  D1R         D1         LL_POSENC_ReadRequestedData1
  * @param  p_posenc POSENC instance.
  * @note  This function returns a 32--bit value from the requested register.
  *        Refer to the reference manual for data management.
  *        (table "Hiperface-DSL Address conversion table")
  *        Data is valid once the D1RTC flag is set.
  * @return Requested data1 register value
  */
__STATIC_INLINE uint32_t LL_POSENC_ReadRequestedData1(const POSENC_TypeDef *p_posenc)
{
  return (STM32_READ_BIT(p_posenc->D1R, POSENC_D1R_D1));
}

/**
  * @brief  Get Hiperface-DSL safe position 1 CRC value.
  * @rmtoll
  *  HD_VPOSCRCR         VPOSCRCH         LL_POSENC_HD_GetSafePosition1CRC\n
  *  HD_VPOSCRCR         VPOSCRCL         LL_POSENC_HD_GetSafePosition1CRC
  * @param  p_posenc POSENC instance.
  * @return Safe position 1 CRC value
  */
__STATIC_INLINE uint32_t LL_POSENC_HD_GetSafePosition1CRC(const POSENC_TypeDef *p_posenc)
{
  return (STM32_READ_BIT(p_posenc->HD_VPOSCRCR, POSENC_HD_VPOSCRCR_VPOSCRCL | POSENC_HD_VPOSCRCR_VPOSCRCH));
}

/**
  * @brief  Get Hiperface-DSL safe position 1: VPOS4 value.
  * @rmtoll
  *  HD_VPOS4R         VPOS4         LL_POSENC_HD_GetSafePosition1_MSB
  * @param  p_posenc POSENC instance.
  * @return Safe position 1 VPOS4 (MSB) value
  */
__STATIC_INLINE uint32_t LL_POSENC_HD_GetSafePosition1_MSB(const POSENC_TypeDef *p_posenc)
{
  return (STM32_READ_BIT(p_posenc->HD_VPOS4R, POSENC_HD_VPOS4R_VPOS4));
}

/**
  * @brief  Get Hiperface-DSL safe position 1: VPOS0 to VPOS3 value.
  * @rmtoll
  *  HD_VPOS30R         VPOS0         LL_POSENC_HD_GetSafePosition1_LSB\n
  *  HD_VPOS30R         VPOS1         LL_POSENC_HD_GetSafePosition1_LSB\n
  *  HD_VPOS30R         VPOS2         LL_POSENC_HD_GetSafePosition1_LSB\n
  *  HD_VPOS30R         VPOS3         LL_POSENC_HD_GetSafePosition1_LSB
  * @param  p_posenc POSENC instance.
  * @return Safe position 1 VPOS3 to VPOS0 (LSB) value
  */
__STATIC_INLINE uint32_t LL_POSENC_HD_GetSafePosition1_LSB(const POSENC_TypeDef *p_posenc)
{
  return (STM32_READ_BIT(p_posenc->HD_VPOS30R, (POSENC_HD_VPOS30R_VPOS0 | POSENC_HD_VPOS30R_VPOS1
                                                | POSENC_HD_VPOS30R_VPOS2 | POSENC_HD_VPOS30R_VPOS3)));
}

/**
  * @brief  Get Hiperface-DSL velocity value.
  * @rmtoll
  *  HD_VEL20R         VEL0         LL_POSENC_HD_GetVelocity
  * @param  p_posenc POSENC instance.
  * @return Velocity value (VEL2 to VEL0)
  */
__STATIC_INLINE uint32_t LL_POSENC_HD_GetVelocity(const POSENC_TypeDef *p_posenc)
{
  return (STM32_READ_BIT(p_posenc->HD_VEL20R, (POSENC_HD_VEL20R_VEL2 | POSENC_HD_VEL20R_VEL1 | POSENC_HD_VEL20R_VEL0)));
}

/**
  * @brief  Get Hiperface-DSL fast position: POS4 value.
  * @rmtoll
  *  HD_POS4R         POS4         LL_POSENC_HD_GetPosition_MSB
  * @param  p_posenc POSENC instance.
  * @return Fast position POS4 (MSB) value
  */
__STATIC_INLINE uint32_t LL_POSENC_HD_GetPosition_MSB(const POSENC_TypeDef *p_posenc)
{
  return (STM32_READ_BIT(p_posenc->HD_POS4R, POSENC_HD_POS4R_POS4));
}

/**
  * @brief  Get Hiperface-DSL fast position: POS3 to POS0 value.
  * @rmtoll
  *  HD_POS30R         POS3         LL_POSENC_HD_GetPosition_LSB \n
  *  HD_POS30R         POS2         LL_POSENC_HD_GetPosition_LSB \n
  *  HD_POS30R         POS1         LL_POSENC_HD_GetPosition_LSB \n
  *  HD_POS30R         POS0         LL_POSENC_HD_GetPosition_LSB
  * @param  p_posenc POSENC instance.
  * @return Fast position POS3 to POS0 (LSB) value
  */
__STATIC_INLINE uint32_t LL_POSENC_HD_GetPosition_LSB(const POSENC_TypeDef *p_posenc)
{
  return (STM32_READ_BIT(p_posenc->HD_POS30R, (POSENC_HD_POS30R_POS3 | POSENC_HD_POS30R_POS2
                                               | POSENC_HD_POS30R_POS1 | POSENC_HD_POS30R_POS0)));
}


/**
  * @brief Read data from EnDat3 cycle based memory.
  * @rmtoll
  *  VERSION_INFO         XXXX         LL_POSENC_ED3_ReadCycleBasedMemory
  * @param p_posenc POSENC instance.
  * @param frame Can be one of the following values:
  *              @arg @ref LL_POSENC_ED3_MEM_BASE
  *              @arg @ref LL_POSENC_ED3_MEM_HPF
  *              @arg @ref LL_POSENC_ED3_MEM_LPF0
  *              @arg @ref LL_POSENC_ED3_MEM_LPF1
  *              @arg @ref LL_POSENC_ED3_MEM_LPF2
  *              @arg @ref LL_POSENC_ED3_MEM_LPF3
  *              @arg @ref LL_POSENC_ED3_MEM_LPF4
  *              @arg @ref LL_POSENC_ED3_MEM_LPF5
  *              @arg @ref LL_POSENC_ED3_MEM_LPF6
  *              @arg @ref LL_POSENC_ED3_MEM_LPF7
  *              @arg @ref LL_POSENC_ED3_MEM_LPF8
  *              @arg @ref LL_POSENC_ED3_MEM_LPF9
  *              @arg @ref LL_POSENC_ED3_MEM_LPF10
  *              @arg @ref LL_POSENC_ED3_MEM_LPF11
  *              @arg @ref LL_POSENC_ED3_MEM_LPF12
  *              @arg @ref LL_POSENC_ED3_MEM_LPF13
  *              @arg @ref LL_POSENC_ED3_MEM_LPF14
  * @param low_high HIGH or LOW word of double word data
  *              @arg @ref LL_POSENC_ED3_MEM_LOW
  *              @arg @ref LL_POSENC_ED3_MEM_HIGH
  * @note  Memory address use a remapping. Refer to reference manual.
  * @return 32-bit data from the cycle based memory
  */
__STATIC_INLINE uint32_t LL_POSENC_ED3_ReadCycleBasedMemory(const POSENC_TypeDef *p_posenc,
                                                            uint32_t frame,
                                                            uint32_t low_high)
{
  const POSENC_ED3_TypeDef *p_posenc_ed3 = LL_POSENC_GET_ENDAT3_INSTANCE(p_posenc);
  const volatile uint32_t *p_tmp_mem;
  uint32_t mem_address;

  mem_address = (uint32_t)(&(p_posenc_ed3->VERSION_INFO)) + frame + low_high;
  p_tmp_mem = (const volatile uint32_t *)mem_address;

  return (uint32_t)(*p_tmp_mem);
}

/**
  * @brief Write data to EnDat3 cycle based memory.
  * @rmtoll
  *  VERSION_INFO         XXXX         LL_POSENC_ED3_WriteCycleBasedMemory
  * @param p_posenc POSENC instance.
  * @param frame Can be one of the following values:
  *              @arg @ref LL_POSENC_ED3_MEM_BASE
  *              @arg @ref LL_POSENC_ED3_MEM_HPF
  *              @arg @ref LL_POSENC_ED3_MEM_LPF0
  *              @arg @ref LL_POSENC_ED3_MEM_LPF1
  *              @arg @ref LL_POSENC_ED3_MEM_LPF2
  *              @arg @ref LL_POSENC_ED3_MEM_LPF3
  *              @arg @ref LL_POSENC_ED3_MEM_LPF4
  *              @arg @ref LL_POSENC_ED3_MEM_LPF5
  *              @arg @ref LL_POSENC_ED3_MEM_LPF6
  *              @arg @ref LL_POSENC_ED3_MEM_LPF7
  *              @arg @ref LL_POSENC_ED3_MEM_LPF8
  *              @arg @ref LL_POSENC_ED3_MEM_LPF9
  *              @arg @ref LL_POSENC_ED3_MEM_LPF10
  *              @arg @ref LL_POSENC_ED3_MEM_LPF11
  *              @arg @ref LL_POSENC_ED3_MEM_LPF12
  *              @arg @ref LL_POSENC_ED3_MEM_LPF13
  *              @arg @ref LL_POSENC_ED3_MEM_LPF14
  * @param low_high HIGH or LOW word of double word data
  *              @arg @ref LL_POSENC_ED3_MEM_LOW
  *              @arg @ref LL_POSENC_ED3_MEM_HIGH
  * @param data Data to be written (32-bit)
  * @note  Memory address use a remapping. Refer to reference manual.
  */
__STATIC_INLINE void LL_POSENC_ED3_WriteCycleBasedMemory(POSENC_TypeDef *p_posenc,
                                                         uint32_t frame,
                                                         uint32_t low_high,
                                                         uint32_t data)
{
  POSENC_ED3_TypeDef *p_posenc_ed3 = LL_POSENC_GET_ENDAT3_INSTANCE(p_posenc);
  volatile uint32_t *p_tmp_mem;
  uint32_t mem_address;

  mem_address = (uint32_t)(&(p_posenc_ed3->VERSION_INFO)) + frame + low_high;
  p_tmp_mem = (volatile uint32_t *)mem_address;

  *p_tmp_mem = (uint32_t)(data);
}

/**
  * @brief Read data from EnDat3 safety collector memory.
  * @rmtoll
  *  VERSION_INFO         XXXX         LL_POSENC_ED3_ReadSafetyMemory
  * @param p_posenc POSENC instance.
  * @param frame Can be one of the following values:
  *              @arg @ref LL_POSENC_ED3_MEM_SAFETY_DATA_1
  *              @arg @ref LL_POSENC_ED3_MEM_SAFETY_DATA_2
  *              @arg @ref LL_POSENC_ED3_MEM_SAFETY_PACKET
  * @param low_high HIGH or LOW word of double word data
  *              @arg @ref LL_POSENC_ED3_MEM_LOW
  *              @arg @ref LL_POSENC_ED3_MEM_HIGH
  * @note  Memory address use a remapping. Refer to reference manual.
  * @return 32-bit data from the safety collector memory
  */
__STATIC_INLINE uint32_t LL_POSENC_ED3_ReadSafetyMemory(const POSENC_TypeDef *p_posenc,
                                                        uint32_t frame,
                                                        uint32_t low_high)
{
  const POSENC_ED3_TypeDef *p_posenc_ed3 = LL_POSENC_GET_ENDAT3_INSTANCE(p_posenc);
  const volatile uint32_t *p_tmp_mem;
  uint32_t mem_address;

  mem_address = (uint32_t)(&(p_posenc_ed3->VERSION_INFO)) + frame + low_high;
  p_tmp_mem = (const volatile uint32_t *)mem_address;

  return (uint32_t)(*p_tmp_mem);
}

/**
  * @brief Write data to EnDat3 safety collector memory.
  * @rmtoll
  *  VERSION_INFO         XXXX         LL_POSENC_ED3_WriteSafetyMemory
  * @param p_posenc POSENC instance.
  * @param frame Can be one of the following values:
  *              @arg @ref LL_POSENC_ED3_MEM_SAFETY_DATA_1
  *              @arg @ref LL_POSENC_ED3_MEM_SAFETY_DATA_2
  *              @arg @ref LL_POSENC_ED3_MEM_SAFETY_PACKET
  * @param low_high HIGH or LOW word of double word data
  *              @arg @ref LL_POSENC_ED3_MEM_LOW
  *              @arg @ref LL_POSENC_ED3_MEM_HIGH
  * @param data Data to be written (32-bit)
  * @note  Memory address use a remapping. Refer to reference manual.
  */
__STATIC_INLINE void LL_POSENC_ED3_WriteSafetyMemory(POSENC_TypeDef *p_posenc,
                                                     uint32_t frame,
                                                     uint32_t low_high,
                                                     uint32_t data)
{
  POSENC_ED3_TypeDef *p_posenc_ed3 = LL_POSENC_GET_ENDAT3_INSTANCE(p_posenc);
  volatile uint32_t *p_tmp_mem;
  uint32_t mem_address;

  mem_address = (uint32_t)(&(p_posenc_ed3->VERSION_INFO)) + frame + low_high;
  p_tmp_mem = (volatile uint32_t *)mem_address;

  *p_tmp_mem = (uint32_t)(data);
}

/**
  * @brief Read data from EnDat3 FID based memory.
  * @rmtoll
  *  VERSION_INFO         XXXX         LL_POSENC_ED3_ReadFIDBasedMemory
  * @param p_posenc POSENC instance.
  * @param fid Frame identifier value (7-bit). Please refer to
  *            EnDat3 documentation for information about available FIDs.
  * @param low_high HIGH or LOW word of double word data
  *              @arg @ref LL_POSENC_ED3_MEM_LOW
  *              @arg @ref LL_POSENC_ED3_MEM_HIGH
  * @note  Memory address use a remapping. Refer to reference manual.
  * @return 32-bit data from the FID based memory
  */
__STATIC_INLINE uint32_t LL_POSENC_ED3_ReadFIDBasedMemory(const POSENC_TypeDef *p_posenc,
                                                          uint32_t fid,
                                                          uint32_t low_high)
{
  const POSENC_ED3_TypeDef *p_posenc_ed3 = LL_POSENC_GET_ENDAT3_INSTANCE(p_posenc);
  const volatile uint32_t *p_tmp_mem;
  uint32_t mem_address;

  mem_address = (uint32_t)(&(p_posenc_ed3->VERSION_INFO)) + LL_POSENC_ED3_MEM_FID_BASE
                + (fid * 0x8UL) + low_high;
  p_tmp_mem = (const volatile uint32_t *)mem_address;

  return (uint32_t)(*p_tmp_mem);
}

/**
  * @brief Write data to EnDat3 FID based memory.
  * @rmtoll
  *  VERSION_INFO         XXXX         LL_POSENC_ED3_WriteFIDBasedMemory
  * @param p_posenc POSENC instance.
  * @param fid Frame identifier value (7-bit). Please refer to
  *            EnDat3 documentation for information about available FIDs.
  * @param low_high HIGH or LOW word of double word data
  *              @arg @ref LL_POSENC_ED3_MEM_LOW
  *              @arg @ref LL_POSENC_ED3_MEM_HIGH
  * @param data Data to be written (32-bit)
  * @note  Memory address use a remapping. Refer to reference manual.
  */
__STATIC_INLINE void LL_POSENC_ED3_WriteFIDBasedMemory(POSENC_TypeDef *p_posenc,
                                                       uint32_t fid,
                                                       uint32_t low_high,
                                                       uint32_t data)
{
  POSENC_ED3_TypeDef *p_posenc_ed3 = LL_POSENC_GET_ENDAT3_INSTANCE(p_posenc);
  volatile uint32_t *p_tmp_mem;
  uint32_t mem_address;

  mem_address = (uint32_t)(&(p_posenc_ed3->VERSION_INFO)) + LL_POSENC_ED3_MEM_FID_BASE
                + (fid * 0x8UL) + low_high;
  p_tmp_mem = (volatile uint32_t *)mem_address;

  *p_tmp_mem = (uint32_t)(data);
}


/**
  * @}
  */

/**
  * @}
  */

#endif /* POSENC1 || POSENC2 */
/**
  * @}
  */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* STM32G5xx_LL_POSENC_H */
