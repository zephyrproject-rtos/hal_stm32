
/**
  ******************************************************************************
  * @file    stm32mp13xx_hal_bsec.h
  * @author  MCD Application Team
  * @brief   Header file of BSEC HAL module.
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
#ifndef STM32MP13xx_HAL_BSEC_H
#define STM32MP13xx_HAL_BSEC_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32mp13xx_hal_def.h"
#include "stm32mp13xx_ll_bsec.h"

/** @addtogroup STM32MP13xx_HAL_Driver
  * @{
  */

/** @addtogroup BSEC
  * @{
  */

/* Exported types ------------------------------------------------------------*/
/** @defgroup BSEC_Exported_Types BSEC Exported Types
  * @{
  */
#define HAL_BSEC_OTP_WORD_INDEX_MAX 95
#define HAL_BSEC_OTP_NB_WORDS 96
/**
  * @brief  Definition of BSEC register index max within the same type
  * Example : BSEC_REG_TYPE_DISTURBED have BSEC_REG_TYPE_DISTURBED0..2, so index max is 2.
  */
#define BSEC_REG_INDEX_MAX                   ((uint32_t)2)

/**
  * @brief  BSEC SAFMEM Maximum number of OTP words
  */

/*!<  OTP_DATA0..95 only implemented in MPU AP v1 : Wildcat */
#define BSEC_OTP_WORD_INDEX_MAX              ((uint32_t)95)

/** Feature disabling definitions **/


typedef enum
{
  HAL_BSEC_FEATURE_CRYPTO_DISABLE           = 0,  /*!< Crypto disable (export licence)*/
  HAL_BSEC_FEATURE_FDCAN1AND2_DISABLE       = 3,  /*!< FDCAN1&2 disable               */
  HAL_BSEC_FEATURE_LTDC_DCMIPP_DISABLE      = 6,  /*!< LTDC and DCMIPP disable        */
  HAL_BSEC_FEATURE_TSC_DISABLE              = 7,  /*!< TSC disable                    */
  HAL_BSEC_FEATURE_FDCAN2_DISABLE           = 8,  /*!< FDCAN2 disable                 */
  HAL_BSEC_FEATURE_ETH1_DISABLE             = 9,  /*!< ETH1 disable                   */
  HAL_BSEC_FEATURE_ADC1_DISABLE             = 10, /*!< ADC1 disable                   */
  HAL_BSEC_FEATURE_TRANSPORT_KEY_DISABLE    = 15, /*!< Transport Key disable          */
} BSEC_FeatureEnDisTypeDef;


#define BSEC_FEAT_MAX (HAL_BSEC_FEATURE_TRANSPORT_KEY_DISABLE)


/* Value of BSEC Timeout : in number of clocks cycles : for gentimer clock running on 'ck_hsi' */
/* this is a number of Tck_hsi cycles                                                          */
/* Current estimations on SAFMEM operations are : */
/*
 * ## Read from SAFMEM timing : ie read operation :
 *    best case @ f(SAFMEM_ck) = 67 MHz with BSEC_OTP_CONTROL.FRC[1:0]=11'
 *    (SAFMEM_ck between 45 MHz and 67 MHz) => 630 ns for a word read (32 bits).
 *
 * ## Write to SAFMEM : ie programming operation :
 * @ f(SAFMEM_ck) = 67 MHz with BSEC_OTP_CONTROL.FRC[1:0]=11' (SAFMEM_ck between 45 MHz and 67 MHz) =>
 * Depends on the number of bit @ 1b1' in the word to be programmed.
 * mean duration for 1 bit = 54 us per bit => 54 us * 38 bits = 2.052 ms.
 * The current duration of timeout 1.56 ms can be too short to allow a
 * special word programming with many bits set to 1'.
 *
 * conclusion :
 * Set timeout waiting for BUSY bit return to value 1b0' to (1000000 * Tck_hsi) = 15.62 ms.
 *
 */
#define BSEC_TIMEOUT_VAL                       1000000 /* f(SAFMEM_clk) = f(ck_hsi) = 64 MHz => Tck_hsi = 15.62 ns */
/* (1000000 * Tck_hsi) = 15.62 ms                           */

/* Value of BSEC Timeout waiting for SAFMEM to be powered up and stable */
/* in number of clocks cycles : for gentimer clock running on ck_hsi    */
/* this is a number of Tck_hsi cycles                                   */
#define BSEC_TIMEOUT_SAFMEM_PWRUP_VAL          1000000 /* f(SAFMEM_clk) = f(ck_hsi) = 64 MHz => Tck_hsi = 15.62 ns */
/* (1000000 * Tck_hsi) = 15.6 ms                            */

/* Exported types ------------------------------------------------------------*/

/**
  * @brief  BSEC state definitions
  */
typedef enum
{
  /*!< BSEC is Idle : not initialized BSEC handle and globals and SAFMEM is not powered up       */
  BSEC_STATE_IDLE         = 0x00,
  /*!< BSEC driver initialized (globals) and ready, but SAFMEM is not powered up : so no read and programming */
  /* operations are possible */
  BSEC_STATE_READY        = 0x01,
  /*!< SAFMEM is powered up,  */
  BSEC_STATE_SAFMEM_PWRUP = 0x02

} BSEC_StateTypeDef;

/**
  * @brief  BSEC Errors definitions that goes in
  * BSEC_HandleTypeDef->Error field to help diagnose eventual error.
  * Note : Error definitions are a mask, so that error bits can be combined together.
  */
typedef enum
{
  BSEC_ERROR_NONE                    = 0x00,    /*!< No error */
  BSEC_ERROR_INVALID_PARAMETER       = 0x01,    /*!< Invalid BSEC Driver API function parameter */
  BSEC_ERROR_INVALID_OTP_WORD        = 0x02,    /*!< Out of range OTP Word invoked   */
  BSEC_ERROR_TIMEOUT                 = 0x04,    /*!< Timeout while reading from OTP or programming/locking operation on OTP Word */
  BSEC_ERROR_LOCK_READ               = 0x08,    /*!< Error the register or OTP word is read locked */
  BSEC_ERROR_PERM_LOCK_PROG          = 0x10,    /*!< Error the OTP word is programming locked */
  BSEC_ERROR_STICKY_LOCK_PROG        = 0x20,    /*!< Error the OTP word is programming locked */
  BSEC_ERROR_LOCK_WRITE              = 0x40,    /*!< Error the OTP shadow word is programming write locked  */
  BSEC_ERROR_SAFMEM_PWRDOWN          = 0x80,    /*!< Error the SAFMEM is powered down and hence inaccessible */
  BSEC_ERROR_DISTURBED               = 0x100,   /*!< Error Read process of OTP word have been disturbed (tamper attack) */
  BSEC_ERROR_ECC_REDUNDANCY          = 0x200,   /*!< Error Read process the ECC or redundancy did not allow error correction */
  BSEC_ERROR_PROG_FAIL               = 0x400,   /*!< Error the last OTP programming (write or lock) attempt failed */
  BSEC_ERROR_SOFT_DRIVER             = 0x800,   /*!< Error BSEC undefined driver software error */
  BSEC_ERROR_ALREADY_LOCKED          = 0x1000,  /*!< Error BSEC already locked OTP word / function */
  BSEC_ERROR_PROG_VALUE_NOT_POSSIBLE = 0x2000,  /*!< Error requested value to program in SAFMEM is not feasible due to techno */
  BSEC_ERROR_DRIVER_NOT_READY        = 0x4000,  /*!< Error the BSEC driver is not Ready (handle not initialized) */

} BSEC_ErrorTypeDefEnum;

typedef uint32_t BSEC_ErrorTypeDef;
/**
  * @brief  BSEC Feature Disable definitions
  * - A level 1b1' is coding a disabling.
  * - A level 1b0' is coding a no disabling (hence enabled).
  */
typedef enum
{
  BSEC_FEATURE_NOT_DISABLED  = 0x00,    /*!< BSEC Feature is not Disabled */
  BSEC_FEATURE_DISABLED      = 0x01     /*!< BSEC Feature is Disabled     */

} BSEC_FeatureDisableTypeDef;

/**
  * @brief  BSEC Shadow register reloading post OTP Read action
  * Enable/Disable definitions
  */
typedef enum
{
  /*!< Shadow reloading post OTP Read is Disabled */
  BSEC_SHADOW_RELOAD_DISABLED  = 0x00,
  /*!< Shadow reloading post OTP Read is Enabled  */
  BSEC_SHADOW_RELOAD_ENABLED   = 0x01

} BSEC_ShadowReloadTypeDef;

/**
  * @brief  BSEC Read Mode definitions
  * Defines how the read should be handled either
  * - Normal read from OTP shadow registers Or
  * - Force a read from SAFMEM (going through the update of shadow registers).
  */
typedef enum
{
  /*!< Read from OTP shadow registers  */
  BSEC_READ_FROM_SHADOW  = 0x00,
  /*!< Force read from SAFMEM : this is a force reload shadows from SAFMEM */
  BSEC_READ_FROM_SAFMEM  = 0x01

} BSEC_ReadModeTypeDef;

/**
  * @brief  BSEC Locking in the general meaning definitions
  */
typedef enum
{
  /*!< BSEC word/function is not read/prog/write locked */
  BSEC_NOTLOCKED  = 0x00,
  /*!< BSEC word/function is either read/prog/write locked */
  BSEC_LOCKED     = 0x01

} BSEC_LockTypeDef;

/**
  * @brief  SAFMEM power status definitions
  * Note : by default after Power Up Reset, the SAFMEM is powered down.
  * It should be powered up before any operation with SAFMEM : that is
  * - read from SAFMEM
  * - programming of OTP words in SAFMEM.
  */
typedef enum
{
  /*!< OTP SAFMEM Powered Off  */
  BSEC_SAFMEM_OFF = 0x00,
  /*!< OTP SAFMEM Powered On   */
  BSEC_SAFMEM_ON  = 0x01

} BSEC_SafMemPwrStatusTypeDef;

/**
  * @brief  BSEC Chip sample security definitions as read from register BSEC_OTP_STATUS.
  */
typedef enum
{
  BSEC_INVALID_STATE         = 0x00,    /*!< Invalid secure sample             */
  /* Upper Secrets not copied in shadows */
  /* OTP status on a tampered sample : ROM code should block further boot */
  BSEC_SECURED_OPEN_STATE    = 0x01,    /*!< Upper Secrets not copied in shadows : */
  /* EWS only mode, not possible at customer */
  /* ROM code doing nothing in this state    */
  BSEC_SECURED_CLOSE_STATE   = 0x02,    /*!< Normal secure sample : state at end of EWS */
  /* Normal state for samples in Final Test (ST or OEM sub-contractor) */
  /* BSEC OTP Status for samples 'Open_Device', 'Final_Closed' */
  /* 'RMA', 'RMA_Relocked' : all OTP upper are copied in shadows */
} BSEC_ChipSecurityTypeDef;

/**
  * @brief  BSEC functional sticky lock capabilities definitions
  * - OTP Upper OTP Read : shadow sticky load read for upper part OTP words : OTP[32..95] : those
  *   containing ST or OEM secrets.
  * - Debug Enable Write : for debug (CoreSight) access control (global, for non invasive or invasive access in
  *   either non secure or secure privileged modes) : allows to disable or re-enable a debug access.
  * - ROMLOCK : allows to unmap the upper 8 kBytes of ROM and sticky lock this unmap : this can be done
  *   by Sw only when the sample is SEC_OPEN.
  *   In all others states of the life cycle (OPEN1/OPEN2/SEC_FINAL/OTP_INVALID),
  *   the unmap of upper 8 kBytes of ROM is handled by Hw and cannot be overridden by Sw.
  * - PROG_GLOBAL_OTP : Sticky lock programming of all OTPs until next system reset
  *
  *   The enumeration values are matching the mapping of fields of register BSEC_OTP_LOCK and can be
  *   ORed to create a mask of functionalities to sticky lock.
  */
typedef enum
{
  /*!< Sticky lock read OTP shadow registers of upper part (secrets OTP[32..95]) = hide all secrets */
  BSEC_FUNC_STICKY_LOCK_OTP_UPPER_READ    = BSEC_OTP_LOCK_OTP,
  /*!< Sticky lock write of BSEC register debug enable */
  BSEC_FUNC_STICKY_LOCK_DENABLE_WRITE     = BSEC_OTP_LOCK_DENREG,
  /*!< Set and Sticky lock write of ROMLOCK signal : always already done by Hw when sample is not SEC_OPEN */
  BSEC_FUNC_STICKY_LOCK_ROMLOCK           = BSEC_OTP_LOCK_OTP,
  /*!< Sticky lock programming of whole OTP (ie SAFMEM) */
  BSEC_FUNC_STICKY_LOCK_PROG_GLOBAL_OTP   = BSEC_OTP_LOCK_GPLOCK

} BSEC_FuncStickyLockTypeDef;

/**
  * @brief  BSEC sticky lock by OTP word capabilities definitions
  * The enumerate is made so that all commands can be combined to have several sticky lock operation
  * on the same OTP index or shadow index done at the same time or reported at the same time (status).
  * - sticky lock OTP word programming operation (until next Power On Reset)
  * - sticky lock OTP word shadow register write (until next Power On Reset)
  * - sticky lock OTP word shadow register read (until next Power On Reset)
  */
typedef enum
{
  /*!< Sticky lock programming of a given OTP word  */
  /* no programming allowed until next System Reset */
  BSEC_OTP_STICKY_LOCK_PROG_FUSE       = 0x01,
  /*!< Sticky lock write of a given OTP shadow register */
  BSEC_OTP_STICKY_LOCK_WRITE_SHADOW    = 0x02,
  /*!< Sticky lock read of a given OTP shadow register       */
  /* hence : update of shadow by read operation is forbidden */
  BSEC_OTP_STICKY_LOCK_UPDATE_SHADOW   = 0x04
} BSEC_OtpStickyLockTypeDef;

/**
  * @brief  BSEC Feature possibly disabled by OTP programming (OTP_DATA1 word) definitions
  * On a secure SoC sample only (no effect on non secured sample) it is possible to re-enable
  * some features that have been disabled by OTP_DATA1 word programming (feature disabling by OTP) by
  * programming the BSEC register BSEC_FENABLE.
  * - Cryptographic hardware accelerators (large meaning) access allowed / disallowed
  * - Access allowed to single (CA7 CPU-0 only) or dual CPU (CA7 CPU-0 & 1)
  * - Access to GPU
  *
  * Note : the enum value is matching OTP_DATA1 and register BSEC_FENABLE bits mapping in the sense that
  *
  * OTP_DATA1[2:0]  == otp_feat_dis[2:0]
  * otp_feat_dis[i] = 1b0' => feature corresponding to 'i' is not disabled by OTP (hence is available for use in Hw)
  * otp_feat_dis[i] = 1b1' => feature corresponding to 'i' is disabled by OTP (hence is not available for use in Hw)
  *                           But could be re-enabled on a secure sample by BSEC_FENABLE[i] programming to 1b1'.
  *
  * BSEC_FENABLE[2:0]  == bsec_frenable[2:0]
  * bsec_frenable[i] = 1b0' => No effect at all
  * bsec_frenable[i] = 1b1' => Attempt to re-enable the feature, which will be effective only on secure sample.
  */
/**
  * @brief  BSEC debug enabled related definitions for mask signals definitions
  * Explanations on signals : For CoreSight signals Please refer bootROM team document "CoreSight overview"
  * DFTEN : allow/disallow DFT access
  * DBGEN : CoreSight signal : allow/disallow DAP AHB-AP port main access (hence AHB part of debug).
  * NIDEN : CoreSight signal : allow/disallow Non Invasive Non Secure debug access.
  * DEVICEEN : CoreSight signal : allow/disallow access to DAP APB-AP by
  *                               external tool connection (hence APB part of debug).
  * HDPEN : Allow/disallow output of Hardware Debug Port SoC signals for monitoring on logic analyzer/scope.
  * SPIDEN : CoreSight signal : Allow/disallow Secure Privileged Invasive debug using the DAP AHB-AP port
  * SPNIDEN : CoreSight signal : Allow/disallow Secure Privileged Non Invasive debug using the DAP AHB-AP port
  * CP15SDISABLE0 : signal influenced by BSEC programming and going to CA7 MPCore cluster core 0
  *                 to allow/disallow programming of CP15 secure registers on core 0.
  * CP15SDISABLE1 : signal influenced by BSEC programming and going to CA7 MPCore cluster core 1
  *                 to allow/disallow programming of CP15 secure registers on core 1.
  * CFGSDISABLE : signal influenced by BSEC programming and going to CA7 MPCore cluster to
                  allow/disallow access to GIC Secure registers.
  * DBGSWENABLE : CoreSight signal : enable/disable input signal of the CoreSight components (top level debug allow).
  */
typedef enum
{
  BSEC_DEBUG_ENABLE_DFTEN         = BSEC_DENABLE_DFTEN_Pos,         /*!< DFTEN debug signal */
  BSEC_DEBUG_ENABLE_DBGEN         = BSEC_DENABLE_DBGEN_Pos,         /*!< DBGEN debug signal : CoreSight signal */
  BSEC_DEBUG_ENABLE_NIDEN         = BSEC_DENABLE_NIDEN_Pos,         /*!< NIDEN debug signal : CoreSight signal */
  BSEC_DEBUG_ENABLE_DEVICEEN      = BSEC_DENABLE_DEVICEEN_Pos,      /*!< DEVICEEN debug signal : CoreSight signal */
  BSEC_DEBUG_ENABLE_HDPEN         = BSEC_DENABLE_HDPEN_Pos,         /*!< HDPEN debug signal */
  BSEC_DEBUG_ENABLE_SPIDEN        = BSEC_DENABLE_SPIDEN_Pos,        /*!< SPIDEN debug signal : CoreSight signal */
  BSEC_DEBUG_ENABLE_SPNIDEN       = BSEC_DENABLE_SPNIDEN_Pos,       /*!< SPNIDEN debug signal : CoreSight signal */
  BSEC_DEBUG_ENABLE_CP15SDISABLE0 = BSEC_DENABLE_CP15SDISABLE_Pos, /*!< CP15SDISABLE signal to CA7-0 core */
  BSEC_DEBUG_ENABLE_CP15SDISABLE1 = (BSEC_DENABLE_CP15SDISABLE_Pos + 1), /*!< CP15SDISABLE signal to CA7-1 core */
  BSEC_DEBUG_ENABLE_CFGSDISABLE   = BSEC_DENABLE_CFGSDISABLE_Pos,   /*!< CFGSDISABLE signal to CA7 MPCore cluster */
  BSEC_DEBUG_ENABLE_DBGSWENABLE   = BSEC_DENABLE_DBGSWENABLE_Pos,   /*!< DBGSWENABLE debug signal : CoreSight signal */
  BSEC_DEBUG_ENABLE_MAX           = BSEC_DEBUG_ENABLE_DBGSWENABLE

} BSEC_DebugEnabledTypeDef;






/**
  * @brief  BSEC SAFMEM clock range (FRC) definitions
  * SAFMEM operation requires safmem_clk <= 67 MHz
  * f(safmem_clk) = 64 MHz = f(ck_hsi) is beset suited for use of SAFMEM read and programming
  * operations.
  */
typedef enum
{
  BSEC_SAFMEM_CLK_RANGE_10MHZ_20MHZ    = 0x0, /*!< FRC between 10 MHz and 20 MHz */
  BSEC_SAFMEM_CLK_RANGE_20MHZ_30MHZ    = 0x1, /*!< FRC between 20 MHz and 30 MHz */
  BSEC_SAFMEM_CLK_RANGE_30MHZ_45MHZ    = 0x2, /*!< FRC between 30 MHz and 45 MHz */
  BSEC_SAFMEM_CLK_RANGE_45MHZ_67MHZ    = 0x3, /*!< FRC between 45 MHz and 67 MHz */
  BSEC_SAFMEM_CLK_RANGE_MAX            = BSEC_SAFMEM_CLK_RANGE_45MHZ_67MHZ

} BSEC_SafMemClkRangeTypeDef;


/**
  * @brief  BSEC Registers type definitions for operations (= read/write actions)
  */
typedef enum
{
  BSEC_REG_TYPE_DISTURBED    = 0x00,    /*!< Operation on register BSEC_OTP_DISTURBEDx */
  BSEC_REG_TYPE_ERROR        = 0x01,    /*!< Operation on register BSEC_OTP_ERRORx */
  BSEC_REG_TYPE_WRLOCK       = 0x02,    /*!< Operation on register BSEC_OTP_WRLOCKx */
  BSEC_REG_TYPE_SPLOCK       = 0x03,    /*!< Operation on register BSEC_OTP_SPLOCKx */
  BSEC_REG_TYPE_SWLOCK       = 0x04,    /*!< Operation on register BSEC_OTP_SWLOCKx */
  BSEC_REG_TYPE_SRLOCK       = 0x05     /*!< Operation on register BSEC_OTP_SRLOCKx */

} BSEC_RegTypeTypeDef;

/**
  * @brief  BSEC handle Structure definition
  */
typedef struct
{
  BSEC_TypeDef       *Instance; /*!< BSEC Registers base address */
  BSEC_StateTypeDef   State;    /*!< BSEC driver current state of type @ref BSEC_StateTypeDef */
  BSEC_ErrorTypeDef   Error;    /*!< BSEC driver eventual error of type @ref BSEC_ErrorTypeDef */

} BSEC_HandleTypeDef;

/**
  * @}
  */

/* Exported constants --------------------------------------------------------*/
/** @defgroup BSEC_Exported_Constants BSEC Exported Constants
  * @{
  */

/**
  * @}
  */

/* Exported macros -----------------------------------------------------------*/
/** @defgroup BSEC_Exported_Macros BSEC Exported Macros
  * @{
  */

/** @brief Reset BSEC handle state.
  * @param  __HANDLE__ BSEC handle.
  * @retval None
  */
/* #define __HAL_BSEC_RESET_HANDLE_STATE(__HANDLE__) ((__HANDLE__)->State = HAL_BSEC_STATE_RESET) */

/**
  * @}
  */


/* Private macros --------------------------------------------------------*/
/** @defgroup  BSEC_Private_Macros BSEC Private Macros
  * @{
  */



/**
  * @}
  */



/* Exported functions --------------------------------------------------------*/
/** @defgroup BSEC_Exported_Functions BSEC Exported Functions
  * @{
  */

/* Exported functions --------------------------------------------------------*/
void              HAL_BSEC_Init(BSEC_HandleTypeDef *hBsec);
HAL_StatusTypeDef HAL_BSEC_SafMemPwrUp(BSEC_HandleTypeDef          *hBsec,
                                       BSEC_SafMemClkRangeTypeDef   safMemClkFreqRange);
void              HAL_BSEC_SafMemPwrDown(BSEC_HandleTypeDef   *hBsec);
void              HAL_BSEC_DeInit(BSEC_HandleTypeDef *hBsec);
HAL_StatusTypeDef HAL_BSEC_UtilReadRegisterBit(BSEC_HandleTypeDef *hBsec, BSEC_RegTypeTypeDef regType, uint32_t regIdx,
                                               uint32_t regBit, uint32_t *pBitValue);
HAL_StatusTypeDef HAL_BSEC_ReadRegisterBit(BSEC_HandleTypeDef *hBsec, BSEC_RegTypeTypeDef regType, uint32_t otpWordIdx,
                                           uint32_t *pBitValue);
HAL_StatusTypeDef HAL_BSEC_OtpShadowRead(BSEC_HandleTypeDef *hBsec, uint32_t otpWordIdx, uint32_t *pOtpShadowVal);
HAL_StatusTypeDef HAL_BSEC_OtpRead(BSEC_HandleTypeDef *hBsec, uint32_t otpWordIdx, uint32_t *pOtpShadowVal);
HAL_StatusTypeDef HAL_BSEC_GetSecurityStatus(BSEC_HandleTypeDef *hBsec, BSEC_ChipSecurityTypeDef *pSecStatus);
HAL_StatusTypeDef HAL_BSEC_OtpShadowWrite(BSEC_HandleTypeDef *hBsec, uint32_t otpWordIdx, uint32_t otpVal);
HAL_StatusTypeDef HAL_BSEC_OtpProgram(BSEC_HandleTypeDef *hBsec, uint32_t otpWordIdx, uint32_t otpWordValReq);
HAL_StatusTypeDef HAL_BSEC_ReadScratch(BSEC_HandleTypeDef *hBsec, uint32_t *pScratchReadVal);
HAL_StatusTypeDef HAL_BSEC_WriteScratch(BSEC_HandleTypeDef *hBsec, uint32_t scratchWriteVal);
HAL_StatusTypeDef HAL_BSEC_JtagInRead(BSEC_HandleTypeDef *hBsec, uint16_t *pJtagReadVal);
HAL_StatusTypeDef HAL_BSEC_JtagOutWrite(BSEC_HandleTypeDef *hBsec, uint16_t jtagWriteVal);
HAL_StatusTypeDef HAL_BSEC_FunctionSetLock(BSEC_HandleTypeDef *hBsec, uint32_t setFunctionLockMask);
HAL_StatusTypeDef HAL_BSEC_FunctionGetLock(BSEC_HandleTypeDef *hBsec, uint32_t *pFunctionLockMaskRead);
HAL_StatusTypeDef HAL_BSEC_SetOtpPermanentProgLock(BSEC_HandleTypeDef *hBsec, uint32_t otpWordIdx);
HAL_StatusTypeDef HAL_BSEC_GetOtpPermanentProgLockStatus(BSEC_HandleTypeDef *hBsec, uint32_t otpWordIdx,
                                                         uint32_t *pLockStatus);
HAL_StatusTypeDef HAL_BSEC_SetOtpStickyLock(BSEC_HandleTypeDef *hBsec, uint32_t otpWordIdx, uint32_t stickyLockCmd);
HAL_StatusTypeDef HAL_BSEC_GetOtpStickyLockStatus(BSEC_HandleTypeDef *hBsec, uint32_t otpWordIdx,
                                                  uint32_t *pStickyLockStatus);
HAL_StatusTypeDef HAL_BSEC_GetOtpErrorStatus(BSEC_HandleTypeDef *hBsec, uint32_t otpWordIdx, uint32_t *pErrorStatus);
HAL_StatusTypeDef HAL_BSEC_GetOtpDisturbStatus(BSEC_HandleTypeDef *hBsec, uint32_t otpWordIdx,
                                               uint32_t *pDisturbStatus);
HAL_StatusTypeDef HAL_BSEC_GetFeatureDisabled(BSEC_HandleTypeDef *hBsec, uint32_t *pMaskFeatDisabled);
HAL_StatusTypeDef HAL_BSEC_GetFdisTkValue(BSEC_HandleTypeDef *hBsec, uint32_t *pFdisTkValue);
HAL_StatusTypeDef HAL_BSEC_GetTk(BSEC_HandleTypeDef *hBsec, uint32_t *tkValue);


HAL_StatusTypeDef HAL_BSEC_GetDebugEnabled(BSEC_HandleTypeDef *hBsec, uint32_t *pDebugMaskEnabled);
HAL_StatusTypeDef HAL_BSEC_SetDebugEnabled(BSEC_HandleTypeDef *hBsec, uint32_t debugMaskEnabled);

HAL_StatusTypeDef HAL_BSEC_GetPKH(BSEC_HandleTypeDef *hBsec,
                                  BSEC_ReadModeTypeDef readMode,
                                  uint32_t             pkhOtpFirstWordIdx,
                                  uint8_t       *pPKH);

void              HAL_BSEC_Div(uint32_t A, uint32_t B, uint32_t *pQ, uint32_t *pR);
void              HAL_BSEC_TraceOnError(BSEC_HandleTypeDef *hBsec);
uint32_t          HAL_BSEC_WaitBusyClearWithTimeout(const BSEC_HandleTypeDef *hBsec);


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

#endif /* STM32MP13xx_HAL_BSEC_H */

