/**
  ******************************************************************************
  * @file    bleplat.h
  * @author  GPM WBL Application team
  * @brief   This file contains the interface of the Bluetooth LE platform layer
  *          (lower interface of the Bluetooth LE stack library).
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

#ifndef BLEPLAT_H__
#define BLEPLAT_H__

#include <stdint.h>
#include "bleplat_cntr.h"

#define RSSI_INVALID                    127

/* Enumerated values used for the return of the functions: */

typedef enum
{
  BLEPLAT_OK    =  0,
  BLEPLAT_FULL  = -1,
  BLEPLAT_BUSY  = -2,
  BLEPLAT_EOF   = -3
} BLEPLAT_NvmStatusTypeDef;


/* Enumerated values used for the 'type' of NVM functions: */

typedef enum
{
  BLEPLAT_NVM_REC_SEC        =  0,
  BLEPLAT_NVM_REC_GATT       =  1,
  BLEPLAT_NVM_REC_DEVICE_ID  =  2,
} BLEPLAT_NvmRecordTypeDef;


/* Enumerated values used for the 'mode' of NVM functions: */

typedef enum
{
  BLEPLAT_NVM_FIRST    =  0,
  BLEPLAT_NVM_NEXT     =  1,
  BLEPLAT_NVM_CURRENT  =  2,
  BLEPLAT_NVM_ALL      =  3
} BLEPLAT_NvmSeekModeTypeDef;

typedef enum
{
  BLEPLAT_PKA_SUCCESS     =  0,
  BLEPLAT_PKA_ERROR       = -1,
  BLEPLAT_PKA_ERR_BUSY    = -2,
  BLEPLAT_PKA_ERR_PARAM   = -3,
  BLEPLAT_PKA_ERR_PROCESS = -4
} BLEPLAT_PkaStatusTypeDef;

typedef void (*BLEPLAT_PkaFuncCb)(BLEPLAT_PkaStatusTypeDef errorCode, void *args);

typedef enum {
  BLEPLAT_AES_FLAGS_DEFAULT = (uint32_t) (0x00000000), /*!< User Flag: No flag specified. This is the default value that should be set to this flag  */
  BLEPLAT_AES_FLAGS_DONT_PERFORM_KEY_SCHEDULE = (uint32_t) (0x00000001), /*!< User Flag: Used to force the init to not reperform key schedule.\n
                                                                 The classic example is where the same key is used on a new message, in this case to redo key scheduling is
                                                                 a useless waste of computation, could be particularly useful on GCM, where key schedule is very complicated. */
  BLEPLAT_AES_FLAGS_FINAL_APPEND = (uint32_t) (0x00000020),   /*!< User Flag: Must be set in CMAC mode before the final Append call occurs. */
  BLEPLAT_AES_FLAGS_OPERATION_COMPLETED  = (uint32_t) (0x00000002),   /*!< Internal Flag (not to be set/read by user): used to check that the Finish function has been already called */
  BLEPLAT_AES_FLAGS_NO_MORE_APPEND_ALLOWED = (uint32_t) (0x00000004), /*!< Internal Flag (not to be set/read by user): it is set when the last append has been called. Used where the append is called with an InputSize not
                                                                    multiple of the block size, which means that is the last input.*/
  BLEPLAT_AES_FLAGS_NO_MORE_HEADER_APPEND_ALLOWED = (uint32_t) (0x00000010),   /*!< Internal Flag (not to be set/read by user): only for authenticated encryption modes. \n
                                                                      It is set when the last header append has been called. Used where the header append is called with an InputSize not
                                                                      multiple of the block size, which means that is the last input.*/
  BLEPLAT_AES_FLAGS_APPEND_DONE = (uint32_t) (0x00000040),   /*!< Internal Flag (not to be set/read by user): only for CMAC.It is set when the first append has been called */
  BLEPLAT_AES_FLAGS_SET_COUNTER = (uint32_t)(0x00000080),    /*!< User Flag: With ChaCha20 this is used to indicate a value for the counter, used to process non contiguous blocks (i.e. jump ahead)*/

} AESflagsTypeDef; /*!< Type definitation for Symmetric Key Flags */

#define BLEPLAT_AES_MAX_EXPKEY_SIZE   44  /*!< The max size of the AES expanded key (in uint32_t) */
#define BLEPLAT_AES128_KEY_SIZE       16 /*!< Number of bytes (uint8_t) necessary to store an AES key of 128 bits. */


typedef struct
{
  uint32_t mContextId; /*!< Unique ID of this context. \b Not \b used in current implementation. */
  AESflagsTypeDef mFlags; /*!< 32 bit mFlags, used to perform keyschedule and future use */
  const uint8_t *pmKey; /*!< Pointer to original Key buffer */
  const uint8_t *pmIv; /*!< Pointer to original Initialization Vector buffer */
  int32_t   mIvSize; /*!< Size of the Initialization Vector in bytes */
  uint32_t   amIv[4]; /*!< Temporary result/IV */
  int32_t   mKeySize;   /*!< Key length in bytes */
  uint32_t   amExpKey[BLEPLAT_AES_MAX_EXPKEY_SIZE];   /*!< Expanded AES key */
  const uint8_t *pmTag;   /*!< Pointer to Authentication TAG. This value must be set in decryption, and this TAG will be verified */
  int32_t mTagSize; /*!< Size of the Tag to return. This must be set by the caller prior to calling Init */
} BLEPLAT_AESCMACctxTypeDef; /*<! AES context structure for CMAC mode */

typedef struct BLEPLAT_TimerHandleS {
	uint64_t ExpiryTime; /*!< Managed internally when the timer is started */
	void (*Callback)(void *); /*!< Pointer to the user callback */
	uint8_t active; /*!< Managed internally when the timer is started */
	struct BLEPLAT_TimerHandleS *next; /*!< Managed internally when the timer is started */
	void *userData; /*!< Pointer to user data */
} BLEPLAT_TimerHandleTypeDef;


void BLEPLAT_MemCpy(void *Dest, const void *Src, unsigned int Size);
void BLEPLAT_MemSet(void *Ptr, int Value, unsigned int Size);
int BLEPLAT_MemCmp(void *S1, void *S2, unsigned int Size);


/**
 * @brief Get Device ID, Version and Revision numbers
 *
 * This function returns the device ID, version and revision numbers.
 * To be called by the BLE Stack for ensuring platform independence.
 *
 * @param[out] device_id Device ID (6 = STM32WB09)
 * @param[out] major_cut Device cut version/major number
 * @param[out] minor_cut Device cut revision/minor number
 *
 * @retval None
 */
void BLEPLAT_GetPartInfo(uint8_t *pDeviceId, uint8_t *pMajorCut, uint8_t *pMinorCut);


/* Non Volatile Memory (NVM) interface:
 *
 * This interface is only called from BLE stack Tick/Commands context
 */

BLEPLAT_NvmStatusTypeDef BLEPLAT_NvmAdd(BLEPLAT_NvmRecordTypeDef Type,
                                        const uint8_t* pData,
                                        uint16_t Size,
                                        const uint8_t* pExtraData,
                                        uint16_t ExtraSize);

BLEPLAT_NvmStatusTypeDef BLEPLAT_NvmGet(BLEPLAT_NvmSeekModeTypeDef Mode,
                                        BLEPLAT_NvmRecordTypeDef Type,
                                        uint16_t Offset,
                                        uint8_t* pData,
                                        uint16_t Size);

int BLEPLAT_NvmCompare(uint16_t Offset, const uint8_t* pData, uint16_t Size);

void BLEPLAT_NvmDiscard(BLEPLAT_NvmSeekModeTypeDef Mode);


/* Public Key Algorithms (PKA) interface:
 *
 * This interface is only called from BLE stack Tick/Commands context
 */

BLEPLAT_PkaStatusTypeDef BLEPLAT_PkaStartP256Key(const uint32_t *PrivateKey, BLEPLAT_PkaFuncCb FuncCb);

BLEPLAT_PkaStatusTypeDef BLEPLAT_PkaStartDHkey(uint32_t* PrivateKey,
                                         uint32_t* PublicKey,
                                         BLEPLAT_PkaFuncCb FuncCb);

/* Advanced Encryption Standard (AES) interface:
 *
 * This interface is only called from BLE stack Tick/Commands context
 */

void BLEPLAT_AesEcbEncrypt(const uint32_t *plainTextData,
                           const uint32_t *key,
                           uint32_t *encryptedData);

int32_t BLEPLAT_AesCMACEncryptInit(BLEPLAT_AESCMACctxTypeDef *pAESCMACctx);

int32_t BLEPLAT_AesCMACEncryptAppend(BLEPLAT_AESCMACctxTypeDef *pAESCMACctx,
                                     const uint8_t  *pInputBuffer,
                                     int32_t InputSize);

int32_t BLEPLAT_AesCMACEncryptFinish(BLEPLAT_AESCMACctxTypeDef *pAESCMACctx,
                                     uint8_t *pOutputBuffer,
                                     int32_t *pOutputSize);

/* Random Number Generation (RNG) interface:
 *
 * This interface is called from both BLE stack contexts: ISR and Tick/Commands
 */

void BLEPLAT_RngGetRandom16(uint16_t* Num);

void BLEPLAT_RngGetRandom32(uint32_t* Num);

/**
  * @brief  Convert TX output power in dBm to the related Power Amplifier level
  * @param  TX_dBm Desired TX output power.
  *
  * @retval PA level that has to be set in the radio register to have a TX
  *         output power lower than or equal to the desired output power
  */
uint8_t BLEPLAT_DBmToPALevel(int8_t TxDBm);

/**
  * @brief  Convert TX output power in dBm to the related Power Amplifier level
  * @param  TX_dBm Desired TX output power.
  *
  * @retval PA level that has to be set in the radio register to have a TX
  *         output power greater than or equal to the desired output power
  */
uint8_t BLEPLAT_DBmToPALevelGe(int8_t TxDBm);

/**
  * @brief  Convert Power Amplifier level to TX output power in dBm
  * @param  PA_Level Level setting for the Power Amplifier
  *
  * @retval Output power in dBm, corresponding to the given PA level. If PA
  *         level is invalid, returned value is 127.
  */
int8_t BLEPLAT_PALevelToDBm(uint8_t PaLevel);

/**
  * @brief  Return minimum and maximum supported TX power.
  * @param[out]  Min_Tx_Power Minimum supported TX power in dBm.
  * @param[out]  Max_Tx_Power Maximum supported TX power in dBm.
  *
  * @retval None
  */
void BLEPLAT_ReadTransmitPower(int8_t *MinTxPower, int8_t *MaxTxPower);

/**
  * @brief  Configure the radio in order to increase output power level.
  * @note   This function should be called only by the BLE stack.
  * @param  enable Enable or disable the ability to reach maximum TX power.
  *                Set to 1 to enable high power mode. Set ot 0 to disable.
  * @retval None
  */
void BLEPLAT_SetHighPower(uint8_t Enable);

/**
  * @brief  Return the current RSSI measured for the last received packet
            as a signed value in dBm.
  * @retval Current RSSI value
  */
int8_t BLEPLAT_CalculateRSSI(void);

/**
  * @brief  Return the next value of the average of RSSI values
  *         given the current RSSI average value and the next RSSI value.
  *         All values are signed and expressed in dBm.
  *         An Exponential Moving Average algorithm is applied.
  * @param  avg_rssi          Current RSSI average value.
  *                           Set to 127 to return the 'rssi' value.
  * @param  rssi              Next RSSI value
  * @param  rssi_filter_coeff Coefficient used for the filtering of
  *                           the RSSI samples and the calculation of
  *                           the average RSSI.
  * @retval Next RSSI average value
  */
int8_t BLEPLAT_UpdateAvgRSSI(int8_t AvgRssi, int8_t Rssi, uint8_t RssiFilterCoeff);

/**
  * @brief  Return the Coding Indicator field of the received packet (valid for
  *         Coded PHY only)
  * @retval 0: Coded S8; 1: Coded S2.
  */
uint8_t BLEPLAT_GetDemodCI(void);


/**
  * @brief  Return the maximum Power Amplifier level available for the device.
  * @return Maximum PA level
  */
uint8_t BLEPLAT_GetMaxPALevel(void);

/**
  * @brief  Return the default level to be set for the Power Amplifier.
  * @return Default PA level
  */
uint8_t BLEPLAT_GetDefaultPALevel(void);

void BLEPLAT_InitCTE(uint8_t smNo);

void BLEPLAT_DeinitCTE(void);

void BLEPLAT_CalibrateCTE(uint8_t smNo);

void BLEPLAT_AntIdxRemap(uint8_t antPattLen, uint8_t *pAntRamTable, const uint8_t* pAntPatt);

uint64_t BLEPLAT_GetCurrentSysTime(void);

uint64_t BLEPLAT_GetFutureSysTime64(uint32_t SysTime);

int BLEPLAT_StartTimer(BLEPLAT_TimerHandleTypeDef *TimerHandle, uint64_t Time);

void BLEPLAT_StopTimer(BLEPLAT_TimerHandleTypeDef *TimerHandle);

uint8_t BLEPLAT_SetRadioTimerValue(uint32_t Time, uint8_t EventType, uint8_t CalReq);

uint8_t BLEPLAT_ClearRadioTimerValue(void);

uint64_t BLEPLAT_GetAnchorPoint(uint64_t *current_system_time);

void BLEPLAT_SetRadioCloseTimeout(void);

uint8_t BLEPLAT_SetRadioTimerRelativeUsValue(uint32_t RelTimeoutUs, uint8_t Tx, uint8_t PLLCal);

#endif /* ! BLEPLAT_H__ */
