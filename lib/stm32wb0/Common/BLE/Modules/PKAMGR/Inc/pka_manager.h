/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    pka_manager.h
  * @author  GPM WBL Application Team
  * @brief   This file contains all the functions prototypes for the PKA Manager.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef PKAMGR_H
#define PKAMGR_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stdint.h"

/** @addtogroup PKA_Manager_Peripheral  PKA Manager
 * @{
 */

/** @defgroup PKA_Manager_Exported_Types Exported Types
 * @{
 */
/* Enumerated values used to report the PKA result status after a process */
typedef enum
{
  PKAMGR_SUCCESS     =  0,
  PKAMGR_ERROR       = -1,
  PKAMGR_ERR_BUSY    = -2,
  PKAMGR_ERR_PARAM   = -3,
  PKAMGR_ERR_PROCESS = -4
} PKAMGR_ResultStatus;
/**
 * @}
 */

/** @defgroup PKA_Manager_Public_Variables Public Variables
* @{
*/
static const uint32_t PKAStartPoint[16] = { 0xd898c296U, 0xf4a13945U, 0x2deb33a0U, 0x77037d81U,
                                       0x63a440f2U, 0xf8bce6e5U, 0xe12c4247U, 0x6b17d1f2U,
                                       0x37bf51f5U, 0xcbb64068U, 0x6b315eceU, 0x2bce3357U,
                                       0x7c0f9e16U, 0x8ee7eb4aU, 0xfe1a7f9bU, 0x4fe342e2U};

/**
* @}
*/

/** @defgroup PKA_Manager_Exported_Functions        Exported Functions
 * @{
 */

/**
  * @brief  PKA Callback pointer definition
  *
  * @param  errorCode - indicates the status of the PKA operation just completed.
  *
  * @param  args - reference to a copy of the output/result of the PKA operation.
  *         It may be either:
  *         a) an array of 3x32 octets long, containing the Local Public Key, in case of P256 Public Key generation,
  *            formatted as follows:
  *            | Secret Key  | Public Key X-coord | Public Key Y-coord |
  *            | (32 octets) | (32 octets)        | (32 octets)        |
  *         b) an array of 32 octets long, containing the DHKey-check result, in case of DHKey check operation,
  *            formatted as follows:
  *            | DHKey check |
  *            | (32 octets) |
  *            | N.A.        | DHKey check        | N.A.               |
  *            | (32 octets) | (32 octets)        | (32 octets)        |
  *         The PKA processing output/result is reported as a linear array of octets,
  *         without any indication of the data length.
  *         The caller of the PKA operations shall read/decode the result, including the data length,
  *         based on the last operation requested.
  *
  *
  * @note 1 - ERROR_PARAMETERS should not be reported to the callback,
  *           assuming that the input parameters (passed for DHKey computation)
  *           are checked when calling HW_PKA_StartP256DHkeyGeneration.
  *
  * @note 2 This model is based on a unique and generic callback function, that reports the PKA output/result
  *         without enforcing a specific function argument typing (preferred option).
  *         Otherwise, 2 specific function callbacks may be defined, each one with specific function arguments
  *         depending on the specific operation requested.
  */
typedef void (*PKAMGR_funcCB)(PKAMGR_ResultStatus errorCode, void *args);  /*!< Pointer to a PKA callback function */

PKAMGR_ResultStatus PKAMGR_Init(void);

PKAMGR_ResultStatus PKAMGR_Deinit(void);

PKAMGR_ResultStatus PKAMGR_SleepCheck(void);

uint8_t PKAMGR_PowerSaveLevelCheck(uint8_t x);

PKAMGR_ResultStatus PKAMGR_Lock(void);

PKAMGR_ResultStatus PKAMGR_Unlock(void);

void PKAMGR_IRQCallback(void);

/**
 * @name   PKAMGR_StartP256PublicKeyGeneration.
 *
 * @brief  Function used to request the generation of a new ECC Public Key.
 *
 * @param[in] privateKey The private key used to generate the public key.
 *
 * @param   funcCB - callback function that BLEPS Library makes available to BLEPLAT HAL,
 *          that is called when the PKA operation requested has been completed (either successfully or not).
 *
 * @return Status of the PKA peripheral w.r.t. the requested operation
 *         - SUCCESS in case the PKA peripheral is available and ready to execute the operation.
 *         - ERROR_BUSY in case the PKA peripheral is BUSY with another operation that could
 *         have been requested by the BLEPS Library or by the End-User Application.
 *
 * @note   Called by BLEPS Library function: <c>hci_le_read_local_p256_publicKey<\c>.
 *
 */
PKAMGR_ResultStatus PKAMGR_StartP256PublicKeyGeneration(const uint32_t *privateKey, PKAMGR_funcCB funcCB);

/**
 * @name    pka_manager_Start_ECDH_P256_DHKey_Generation
 *
 * @brief   Function which configures the PKA to perform the computation of DHKey check value.
 *
 * @param   secretKey - the Secret Key of the Local device (LE format).
 * @param   publicKey - the Public Key of the peer remote device for which the DHKey will be computed (LE format).
 * @param   funcCB - callback function that BLEPS Library makes available to BLEPLAT HAL,
 *          that is called when the PKA operation requested has been completed (either successfully or not).
 *
 * @return  Status of the preliminary checks performed on input parameters and PKA peripheral status
 *          made beofre to configure the PKA for DHKey computation.
 *         - SUCCESS in case the PKA peripheral is available and ready to execute the operation
 *           and the input parameters are correct!
 *         - ERROR_BUSY in case the PKA peripheral is BUSY with another operation that could
 *           have been requested by the BLEPS Library or by the End-User Application.
 *         - ERROR_PARAMETERS in case the input parameters are invalid; either the Secret key or the
 *           remote P256 public key may be wrong (when the peer remote public key is not a valid ECC point)
 *
 */
PKAMGR_ResultStatus HW_PKA_StartP256DHkeyGeneration(const uint32_t *secretKey,
                                                    const uint32_t *publicKey,
                                                    PKAMGR_funcCB funcCB);

/**
 * @}
 */

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* PKAMGR_H */
