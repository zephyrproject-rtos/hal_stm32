/*****************************************************************************
 * @file    blestack.h
 *
 * @brief   Header file for STM32WBA BLE stack
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

#ifndef BLESTACK_H__
#define BLESTACK_H__


#include "auto/ble_types.h"
#include "ble_bufsize.h"


/*
 * Definitions for return value of BleStack_Process( )
 */
enum
{
  BLE_SLEEPMODE_RUNNING   = 0,
  BLE_SLEEPMODE_CPU_HALT  = 1,
  BLE_SLEEPMODE_WAKETIMER = 2,
  BLE_SLEEPMODE_NOTIMER   = 3,
};

/*
 * Definitions for 'options' parameter
 */
enum
{
  BLE_OPTIONS_LL_ONLY             = 0x0001U,
  BLE_OPTIONS_NO_SVC_CHANGE_DESC  = 0x0002U,
  BLE_OPTIONS_DEV_NAME_READ_ONLY  = 0x0004U,
  BLE_OPTIONS_EXTENDED_ADV        = 0x0008U,
  BLE_OPTIONS_REDUCED_DB_IN_NVM   = 0x0020U,
  BLE_OPTIONS_GATT_CACHING        = 0x0040U,
  BLE_OPTIONS_POWER_CLASS_1       = 0x0080U,
  BLE_OPTIONS_APPEARANCE_WRITABLE = 0x0100U,
  BLE_OPTIONS_ENHANCED_ATT        = 0x0200U,
};

/*
 * Definitions for 'debug' parameter
 */
enum
{
  BLE_DEBUG_RAND_ADDR_INIT  = 0x00000010UL,
};

/*
 * This structure contains memory and low level hardware configuration data
 * for the device
*/
typedef struct
{
  /* Start address of the RAM buffer allocated for BLE stack library.
   * It must be a 32bit aligned RAM area.
   */
  uint8_t* bleStartRamAddress;

  /* Size of the RAM buffer allocated for BLE stack library.
   * (could be filled with BLE_TOTAL_BUFFER_SIZE return value)
   */
  uint32_t total_buffer_size;

  /* Start address of the RAM buffer allocated for GATT database.
   * It must be a 32bit aligned RAM area.
   */
  uint8_t* bleStartRamAddress_GATT;

  /* Size of the RAM buffer allocated for GATT database.
   * (could be filled with BLE_TOTAL_BUFFER_SIZE_GATT return value)
   */
  uint32_t total_buffer_size_GATT;

  /* Maximum number of Attributes (i.e. the number of characteristic + the
   * number of characteristic values + the number of descriptors, excluding the
   * services) that can be stored in the GATT database.
   * Note that certain characteristics and relative descriptors are added
   * automatically during device initialization so this parameters should be 9
   * (or 6 w.r.t. options) plus the number of user Attributes (NUM_GATT_
   * ATTRIBUTES used in the calculation of BLE TOTAL_BUFFER_SIZE_GATT)
   */
  uint16_t numAttrRecord;

  /* Maximum number of Services that can be stored in the GATT database.
   * Note that the GAP and GATT services are automatically added so this
   * parameter should be 2 plus the number of user services (NUM_GATT_SERVICES
   * used in the calculation of BLE_TOTAL_BUFFER_SIZE_GATT)
   */
  uint16_t numAttrServ;

  /* Size of the storage area for Attribute values (ATT_VALUE_ARRAY_SIZE used
   * in the calculation of BLE_TOTAL_BUFFER_SIZE_GATT)
   * This value depends on the number of attributes used by application. In
   * particular the sum of the following quantities (in octets) should be made
   * for each attribute:
   * - attribute value length
   * - 5, if UUID is 16 bit; 19, if UUID is 128 bit
   * - 2, if server configuration descriptor is used
   * - 2*numOfLinks, if client configuration descriptor is used
   * - 2, if extended properties is used
   * The total amount of memory needed is the sum of the above quantities for
   * each attribute.
   */
  uint16_t attrValueArrSize;

  /* Maximum number of simultaneous connections that the device will support.
   * Valid values are from 1 to 8 (NUM_LINKS used in the calculation of
   * BLE_TOTAL_BUFFER_SIZE).
   */
  uint8_t numOfLinks;

  /* Prepare Write List size in terms of number of packet with ATT_MTU=23 bytes
   */
  uint8_t prWriteListSize;

  /* Number of allocated memory blocks
   */
  uint16_t mblockCount;

  /* Maximum supported ATT_MTU size
   */
  uint16_t attMtu;

  /* Maximum value of the connection-oriented channel Maximum Payload Size
   * Range: 23 .. (BLE_EVT_MAX_PARAM_LEN - 7)
   */
  uint16_t max_coc_mps;

  /* Maximum number of connection-oriented channels.
   * Range: 0 .. 64
   */
  uint8_t max_coc_nbr;

  /* Maximum number of connection-oriented channels in initiator mode.
   * Range: 0 .. max_coc_nbr
   */
  uint8_t max_coc_initiator_nbr;

  /* Options flags
   * Bitmap of the "BLE_OPTIONS_..." definitions (see above).
   * - bit 0:   1: LL only                   0: LL + host
   * - bit 1:   1: no service change desc.   0: with service change desc.
   * - bit 2:   1: device name Read-Only     0: device name R/W
   * - bit 3:   1: extended adv supported    0: extended adv not supported
   * - bit 5:   1: Reduced GATT db in NVM    0: Full GATT db in NVM
   * - bit 6:   1: GATT caching is used      0: GATT caching is not used
   * - bit 7:   1: LE Power Class 1          0: Other LE Power Classes
   * - bit 8:   1: appearance Writable       0: appearance Read-Only
   * - bit 9:   1: Enhanced ATT supported    0: Enhanced ATT not supported
   * - other bits: reserved
   */
  uint16_t options;

  /* Debug flags
   * Bitmap of the "BLE_DEBUG_..." definitions (see above).
   */
  uint32_t debug;

} BleStack_init_t;

/*
 * BleStack_Init
 *
 * @brief The BLE Stack initialization routine
 *
 * @param[in]  Init_params_p      pointer to the const structure containing
 *                                memory and low level  hardware configuration
 *                                data for the device
 *
 * @return Value indicating success or error code.
 */
extern tBleStatus BleStack_Init( const BleStack_init_t* init_params_p );

/*
 * BleStack_Process
 *
 * @brief This function executes the processing of all Host Stack layers.
 * It has to be executed regularly to process incoming Link Layer packets and
 * to process Host Layers procedures. All stack callbacks are called by this
 * function.
 *
 * No BLE stack function must be called while the BleStack_Process is running.
 * For example, if a BLE stack function may be called inside an
 * interrupt routine, that interrupt must be disabled during the execution of
 * BleStack_Process().
 *
 * @return
 *  BLE_SLEEPMODE_RUNNING   (0) -> BLE Stack Process has to be executed,
 *  BLE_SLEEPMODE_CPU_HALT  (1) -> BLE Stack Process does not have to be
 *                                 executed,
 */
extern uint8_t BleStack_Process( void );

/*
 * BleStack_Request
 *
 * @brief This function gives a request from application to the BLE stack.
 * The input parameter is a buffer of bytes in the BLE standard format:
 * HCI/ACI command packet or ACL data packet.
 * The response packet is returned in the same buffer and the size (in bytes)
 * of the response is given by the function return value.
 */
extern uint16_t BleStack_Request( uint8_t* buffer );

/*
 * BLECB_Indication
 *
 * @brief Callback called by the BLE stack (from BleStack_Process() context)
 * to send an indication to the application. The indication is a BLE standard
 * packet that can be either an ACI/HCI event or an ACL data.
 */
extern uint8_t BLECB_Indication( const uint8_t* data,
                                 uint16_t length,
                                 const uint8_t* ext_data,
                                 uint16_t ext_length );


#endif /* BLESTACK_H__ */
