/*****************************************************************************
 * @file    bleplat.h
 *
 * @brief   This file contains the interface of the BLE platform layer
 *          (lower interface of the BLE stack library).
 *          It is included by the STM32WBX BLE stack library.
 *****************************************************************************
 * @attention
 *
 * Copyright (c) 2018-2025 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 *****************************************************************************
 */

#ifndef BLEPLAT_H__
#define BLEPLAT_H__


#include <stdint.h>

/* Enumerated values used for the return of the functions:
 */
enum
{
  BLEPLAT_OK    =  0, /* The function did the job and returns an OK status */
  BLEPLAT_FULL  = -1, /* The function exits because the HW resource is full */
  BLEPLAT_BUSY  = -2, /* The function is busy and is not available for the
                         requested operation */
  BLEPLAT_EOF   = -3, /* The function exits and notifies the HW resource
                         (memory for example) reached the end */
  BLEPLAT_WARN  = -4, /* The function runs the asked operation and notifies
                         that the HW resource is near to be full */
  BLEPLAT_ERROR = -5  /* The function exits due to some issue (memory
                         corruption or buffer overflow for example) */
};

/* Enumerated values used for the 'type' of NVM functions:
 */
enum
{
  BLEPLAT_NVM_TYPE_SEC  =  0,
  BLEPLAT_NVM_TYPE_GATT =  1,
};

/* Enumerated values used for the 'mode' of NVM functions:
 */
enum
{
  BLEPLAT_NVM_FIRST    =  0,
  BLEPLAT_NVM_NEXT     =  1,
  BLEPLAT_NVM_CURRENT  =  2,
  BLEPLAT_NVM_ALL      =  3
};

/* General functions:
 */

/**
 * @brief  This function is called by the Bluetooth LE stack when it is
 *         initialized or reset (via hci_reset). The user shall call here the
 *         functions to reset the Timer, AES, PKA, NVM and RNG needed for the
 *         Bluetooth LE stack.
 * @param  None
 * @retval None
 */
extern void BLEPLAT_Init( void );

/* Non Volatile Memory (NVM) interface:
 */

/**
 * @brief  Store data in the NVM
 * @param  type: The type of data to be stored either security data
 *         (BLEPLAT_NVM_TYPE_SEC) or GATT data (BLEPLAT_NVM_TYPE_GATT)
 * @param  data: The data buffer to be stored
 * @param  size: The size of data to be stored
 * @param  extra_data: If there is extra data to be stored too. If not, this
 *         parameter shall be passed with "NULL" value
 * @param  extra_size: The size of extra data
 * @retval status (BLEPLAT_XX)
 */
extern int BLEPLAT_NvmAdd( uint8_t type,
                           const uint8_t* data,
                           uint16_t size,
                           const uint8_t* extra_data,
                           uint16_t extra_size );

/**
 * @brief  Read data from the NVM
 * @param  mode: The mode of NVM reading:
 *         - BLEPLAT_NVM_FIRST
 *           used to read the first record of NVM
 *         - BLEPLAT_NVM_NEXT
 *           used to read the next record (after a previous call to
 *           BLEPLAT_NvmGet)
 *         - BLEPLAT_NVM_CURRENT
 *           used to read the same record again (after a previous call to
 *           BLEPLAT_NvmGet)
 * @param  type: The type of data to be read, either security data
 *         (BLEPLAT_NVM_TYPE_SEC) or GATT data (BLEPLAT_NVM_TYPE_GATT)
 * @param  offset: The offset from which the NVM starts the read an operation.
 * @param  data: The pointer to data read by the function
 * @param  size: The size of data to be read
 * @retval - if positive or zero, it is the number of copied bytes
 *         - if negative, it is an error status (BLEPLAT_XX)
 */
extern int BLEPLAT_NvmGet( uint8_t mode,
                           uint8_t type,
                           uint16_t offset,
                           uint8_t* data,
                           uint16_t size );

/**
 * @brief  Compare passed data as parameter with data stored in the NVM
 * @param  offset: The offset from which the NVM starts the comparison
 * @param  data: The data to be compared with stored data in the NVM
 * @param  size: The size of data to be compared
 * @retval - if zero, the comparison was successful (BLEPLAT_OK)
 *         - if positive, the comparison failed
 *         - if negative, it is an error status (BLEPLAT_XX)
 */
extern int BLEPLAT_NvmCompare( uint16_t offset,
                               const uint8_t* data,
                               uint16_t size );

/**
 * @brief  Clear a block from the NVM or the whole NVM, storing the security
 *         database (security and GATT records)
 * @param  mode: Mode of deleting data from the NVM, either clear all the
 *         security database (BLEPLAT_NVM_ALL) or the current read NVM block
 *         (BLEPLAT_NVM_CURRENT)
 * @retval None
 */
extern void BLEPLAT_NvmDiscard( uint8_t mode );

/* Public Key Algorithms (PKA) interface:
 */

/**
 * @brief  Start P-256 public key generation
 * @param  local_private_key: table of 8 x 32-bit words that contains the
 *         P-256 private key (Little Endian format)
 * @retval status (BLEPLAT_XX)
 */
extern int BLEPLAT_PkaStartP256Key( const uint32_t* local_private_key );

/**
 * @brief  Get result of P-256 public key generation
 * @param  local_public_key: table of 32 x 32-bit words that is filled by the
 *         function with the generated P-256 public key (Little Endian format)
 * @retval status (BLEPLAT_XX)
 */
extern void BLEPLAT_PkaReadP256Key( uint32_t* local_public_key );

/**
 * @brief  Start DH key computation
 * @param  local_private_key: table of 8 x 32-bit words that contains the
 *         local P-256 private key (Little Endian format)
 * @param  remote_public_key: table of 32 x 32-bit words that contains the
 *         remote P-256 public key (Little Endian format)
 * @retval status (BLEPLAT_XX)
 */
extern int BLEPLAT_PkaStartDhKey( const uint32_t* local_private_key,
                                  const uint32_t* remote_public_key );
/**
 * @brief  Get result of DH key computation
 * @param  dh_key: table of 8 x 32-bit words that is filled by the function
 *         with the generated DH key (Little Endian format)
 * @retval status (BLEPLAT_XX)
 */
extern int BLEPLAT_PkaReadDhKey( uint32_t* dh_key );

/**
 * @brief  Callback function implemented by the Bluetooth LE stack that must
 *         be called by the user to inform the Bluetooth LE stack about
 *         completion of P-256 public key generation or DH key computation
 * @param  None
 * @retval status (BLEPLAT_XX)
 */
extern void BLEPLATCB_PkaComplete( void );

/* Advanced Encryption Standard (AES) interface:
 */

/**
  * @brief  Encrypt a single 128-bit block with a 128-bit key.
  * @param  key: table of 16 bytes that contains the key to use
  *         (Little Endian format)
  * @param  input: table of 16 bytes that contains the block to encrypt
  * @param  output: table of 16 bytes that is filled by the function with the
  *         encrypted block
  * @retval None
  */
extern void BLEPLAT_AesEcbEncrypt( const uint8_t* key,
                                   const uint8_t* input,
                                   uint8_t* output );

/**
  * @brief  Set the 128-bit key to be used for CMAC computation.
  * @param  key: table of 16 bytes that contains the key to use
  *         (Little Endian format)
  * @retval None
  */
extern void BLEPLAT_AesCmacSetKey( const uint8_t* key );

/**
  * @brief  CMAC computation: the function can be called several times with
  *         output_tag set to 0 to append data to the computation. It must be
  *         called once at the end with output_tag not set at 0 to complete
  *         the CMAC computation.
  * @param  input: table of "input_length" bytes that contains the data to
  *         append for the CMAC computation
  * @param  input_length: number of bytes in "input".
  * @param  output_tag: must be set to 0 for append.
  *         Otherwise: table of 16 bytes that is filled by the function with
  *         the computed CMAC tag.
  * @retval None
  */
extern void BLEPLAT_AesCmacCompute( const uint8_t* input,
                                    uint32_t input_length,
                                    uint8_t* output_tag );

/**
  * @brief  CCM computation
  *
  * @param  mode: CCM mode (0=encryption, 1=decryption)
  * @param  key: AES encryption key (16 bytes)
  * @param  iv_length: IV length (in bytes)
  * @param  iv: IV data
  * @param  add_length: add length (in bytes)
  * @param  add: add data
  * @param  input_length: input data length (in bytes)
  * @param  input: original data (to be encrypted or decrypted)
  * @param  tag_length: CCM tag length (in bytes)
  * @param  tag: CCM tag
  * @param  output: result data (encrypted or decrypted)
  * @retval status (BLEPLAT_XX)
  */
extern int BLEPLAT_AesCcmCrypt( uint8_t mode,
                                const uint8_t* key,
                                uint8_t iv_length,
                                const uint8_t* iv,
                                uint16_t add_length,
                                const uint8_t* add,
                                uint32_t input_length,
                                const uint8_t* input,
                                uint8_t tag_length,
                                uint8_t* tag,
                                uint8_t* output );

/* Random Number Generation (RNG) interface:
 */

/**
  * @brief  Get random values.
  * @param  n: number of 32-bit words to read.
  * @param  val: pointer to a 32-bit table of size"n" that are filled with
  *         random values by the function.
  * @retval None
  */
extern void BLEPLAT_RngGet( uint8_t n,
                            uint32_t* val );

/* Timer interface:
 */

/**
  * @brief  Start the Timer.
  * @param  id: The timer ID to be started
  * @param  timeout: The timeout needed to stop the timer (in ms)
  * @retval status (BLEPLAT_XX)
  */
extern uint8_t BLEPLAT_TimerStart( uint16_t id,
                                   uint32_t timeout );

/**
  * @brief  Stop the Timer
  * @param  id: The timer ID to be stopped
  * @retval None
  */
extern void BLEPLAT_TimerStop( uint16_t id );

/**
  * @brief  The timer callback function called when the timeout of a given
  *         timer has elapsed
  * @param  id: The timer ID
  * @retval None
  */
extern void BLEPLATCB_TimerExpiry( uint16_t id );


#endif /* BLEPLAT_H__ */
