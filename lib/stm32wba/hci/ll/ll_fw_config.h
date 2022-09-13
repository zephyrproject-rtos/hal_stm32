/*$Id: //dwh/bluetooth/DWC_ble154combo/firmware/rel/1.30a-SOW05PatchV6/firmware/public_inc/ll_fw_config.h#1 $*/
/**
 ********************************************************************************
 * @file    ll_fw_config.h
 * @brief   This file contains the major configurations to the BLE controller.
 ******************************************************************************
  * @copy
 * This Synopsys DWC Bluetooth Low Energy Combo Link Layer/MAC software and
 * associated documentation ( hereinafter the "Software") is an unsupported
 * proprietary work of Synopsys, Inc. unless otherwise expressly agreed to in
 * writing between Synopsys and you. The Software IS NOT an item of Licensed
 * Software or a Licensed Product under any End User Software License Agreement
 * or Agreement for Licensed Products with Synopsys or any supplement thereto.
 * Synopsys is a registered trademark of Synopsys, Inc. Other names included in
 * the SOFTWARE may be the trademarks of their respective owners.
 *
 * Synopsys MIT License:
 * Copyright (c) 2020-Present Synopsys, Inc
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * the Software), to deal in the Software without restriction, including without
 * limitation the rights to use, copy, modify, merge, publish, distribute,
 * sublicense, and/or sell copies of the Software, and to permit persons to whom
 * the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THIS SOFTWARE IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING, BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE, AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT, OR OTHERWISE ARISING FROM,
 * OUT OF, OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * */
#ifndef INCLUDE_LL_FW_CONFIG_H
#define INCLUDE_LL_FW_CONFIG_H


/*************************** BLE Configuration *************************************/
/*Configurations of BLE will apply only when BLE is enabled*/
/* Roles configurations */
#define SUPPORT_EXPLCT_OBSERVER_ROLE				1 /* Enable\Disable Explicit observer role. Enable:1 - Disable:0 */
#define SUPPORT_EXPLCT_BROADCASTER_ROLE				1 /* Enable\Disable Explicit broadcaster role. Enable:1 - Disable:0 */
#define SUPPORT_MASTER_CONNECTION					1 /* Enable\Disable Master connection role. Enable:1 - Disable:0 */
#define SUPPORT_SLAVE_CONNECTION					1 /* Enable\Disable Slave connection role. Enable:1 - Disable:0 */

/* Standard features configurations */
#define SUPPORT_LE_ENCRYPTION						1 /* Enable\Disable Encryption feature. Enable:1 - Disable:0 */
#define SUPPORT_PRIVACY								1 /* Enable\Disable Privacy feature. Enable:1 - Disable:0 */

/* Capabilities configurations */
#define MAX_NUM_CNCRT_STAT_MCHNS					8 /* Set maximum number of states the controller can support */
#define USE_NON_ACCURATE_32K_SLEEP_CLK				1 /* Allow to drive the sleep clock by sources other than the default crystal oscillator source.*/
													   /*LL can use crystal oscillator or RTC or RCO to drive the sleep clock.This selection is done via "DEFAULT_SLEEP_CLOCK_SOURCE" macro. */
#define SUPPORT_LE_EXTENDED_ADVERTISING				1 /* Enable\Disable Extended advertising feature. Enable:1 - Disable:0 */
#define SUPPORT_LE_PERIODIC_ADVERTISING				1 /* Enable\Disable Periodic advertising feature. Enable:1 - Disable:0 */
#define SUPPORT_LE_POWER_CLASS_1					0 /* Enable\Disable Low power class 1 feature. Enable:1 - Disable:0 */
#define SUPPORT_AOA_AOD								1 /* Enable\Disable AOA_AOD feature. Enable:1 - Disable:0 */
#define SUPPORT_PERIODIC_SYNC_TRANSFER				1 /* Enable\Disable PAST feature. Enable:1 - Disable:0 */
#define SUPPORT_SLEEP_CLOCK_ACCURCY_UPDATES         1 /* Enable\Disable Sleep Clock Accuracy Updates Feature. Enable:1 - Disable:0 */
#define SUPPORT_CONNECTED_ISOCHRONOUS               1 /* Enable\Disable Connected Isochronous Channel Feature. Enable:1 - Disable:0 */
#define SUPPORT_BRD_ISOCHRONOUS               		1 /* Enable\Disable Broadcast Isochronous Channel Feature. Enable:1 - Disable:0 */
#define SUPPORT_SYNC_ISOCHRONOUS               		1 /* Enable\Disable Broadcast Isochronous Synchronizer Channel Feature. Enable:1 - Disable:0 */
#define SUPPORT_LE_POWER_CONTROL					1 /* Enable\Disable LE Power Control Feature. Enable:1 - Disable:0 */

/* 5.3 features */
#define SUPPORT_CHANNEL_CLASSIFICATION    0
#define SUPPORT_LE_ENHANCED_CONN_UPDATE    0

/* Capabilities configurations */
#define MAX_NUM_CNCRT_STAT_MCHNS					8 /* Set maximum number of states the controller can support */
#define USE_NON_ACCURATE_32K_SLEEP_CLK				1 /* Allow to drive the sleep clock by sources other than the default crystal oscillator source.*/
													   /*LL can use crystal oscillator or RTC or RCO to drive the sleep clock.This selection is done via "DEFAULT_SLEEP_CLOCK_SOURCE" macro. */

/* Non-standard features configurations */
#define NUM_OF_CTSM_EMNGR_HNDLS						1 /* Number of custom handles in event manager to be used for app specific needs */
#define SUPPORT_AUGMENTED_BLE_MODE					1 /* Enable\Disable Augmented BLE Support. Enable:1 - Disable:0 */
#define SUPPORT_PTA									0 /* Enable\Disable PTA Feature. Enable:1 - Disable:0 */

#define SUPPORT_AUTONOMOUS_POWER_CONTROL_REQ                      (1)
#define LL_BASIC  0

/*************************** MAC Configuration *************************************/
/*Configurations of MAC will apply only when MAC is enabled*/
#define FFD_DEVICE_CONFIG							0 /* Enable\Disable FFD:1 - RFD:0 */
#ifdef SUPPORT_AUG_MAC_HCI_UART
#define RAL_NUMBER_OF_INSTANCE						0 /* The Number of RAL instances supported */
#else
#define RAL_NUMBER_OF_INSTANCE						0 /* The Number of RAL instances supported */
#endif
#define MAX_NUMBER_OF_INDIRECT_DATA 				0 /* The maximum number of supported indirect data buffers */
#define SUPPORT_OPENTHREAD_1_2                  	0 /* Enable / disable FW parts related to new features introduced in openthread 1.2*/
#define SUPPORT_SEC 								0 /* The MAC Security Supported : 1 - Not Supported:0 */
#define RADIO_CSMA									0 /* Enable\Disable CSMA Algorithm in Radio Layer, Must be Enabled if MAC_LAYER_BUILD */
#define SUPPORT_A_MAC								0
#define SMPL_PRTCL_TEST_ENABLE 						0

#endif /* INCLUDE_LL_FW_CONFIG_H */
