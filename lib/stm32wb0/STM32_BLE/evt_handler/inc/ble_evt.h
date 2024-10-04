/**
  ******************************************************************************
  * @file    ble_evt.h
  * @author  GPM WBL Application Team
  * @brief   Header for BLE Event Dispatcher module
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


/**
 * The BLE Controller supports the application to handle services and clients.
 * It provides an API to initialize the BLE core Device and a handler mechanism to rout the GATT/GAP events to the
 * application. When the ble_controller is used (recommended), the application shall register a callback for each
 * Service and each Client implemented. This is already done with the Services and Clients provided in that delivery.
 *  + A GATT event is relevant to only one Service and/or one Client. When a GATT event is received, it is notified to
 *    the registered handlers to the BLE controller. When no registered handler acknowledges positively the GATT event,
 *    it is reported to the application.
 *  + A GAP event is not relevant to either a Service or a Client. It is sent to the application
 *  + In case the application does not want to take benefit from the ble_controller, it could bypass it. In that case,
 *  the application shall:
 *    - call  SVCCTL_Init() to initialize the BLE core device (or implement on its own what is inside that function
 *    - implement TLHCI_UserEvtRx() which is the notification from the HCI layer to report all events (GATT/GAP).
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef BLE_EVT_H
#define BLE_EVT_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "ble_events.h"
/* Exported types ------------------------------------------------------------*/


typedef enum
{
  BLEEVT_NoAck,
  BLEEVT_Ack,
} BLEEVT_EvtAckStatus_t;

typedef BLEEVT_EvtAckStatus_t (*BLEEVT_HciPcktHandlerFunc_t)(hci_pckt *hci_pckt_p);
typedef BLEEVT_EvtAckStatus_t (*BLEEVT_GattEvtHandlerFunc_t)(aci_blecore_event *evt_p);


  /* Exported constants --------------------------------------------------------*/
  /* External variables --------------------------------------------------------*/
  /* Exported macros -----------------------------------------------------------*/

  /* Exported functions ------------------------------------------------------- */
/**
* @brief  It initializes the BLE Event Handler library.
*
* @param  None
* @retval None
*/
void BLEEVT_Init(void);

/**
 * @brief  This API registers a handler to be called when a GATT user event is received from the BLE core device. When
 *         a Service is created, it shall register a callback to be notified when a GATT event is received from the
 *         BLE core device. When a GATT event is received, it shall be checked in the handler if the GATT events belongs
 *         to the Service or not. As soon as one Service handler acknowledges positively the GATT event, no other registered
 *         Service handlers will be called.
 *         The maximum number of registered handlers is controlled by BLE_CFG_MAX_NBR_GATT_EVT_HANDLERS macros.
 *         This handler is called from BLEStack_Process() context.
 *
 * @param  EvtHandlerFunc This is the Service handler that is called to report a GATT event.
 *         If the GATT event exclusively belongs to that Service, the callback should return positively with
 *         BLEEVT_Ack.
 * @retval 0  Success
 * @retval -1 Not able to register the handler. Increase number of supported event handlers with BLE_CFG_MAX_NBR_GATT_EVT_HANDLERS.
 */
int BLEEVT_RegisterGattEvtHandler(BLEEVT_GattEvtHandlerFunc_t EvtHandlerFunc);

/**
 * @brief  This API registers a handler to be called when a generic non-GATT event is received from the BLE core stack.
 *         A Bluetooth profile may use this function to be notified when an event is received.
 *         The maximum number of registered handlers is controlled by BLE_CFG_MAX_NBR_EVT_HANDLERS macros.
 *         If the handler returns BLEEVT_Ack, no other registered handlers will be called.
 *         This handler is called from BLEStack_Process() context.
 *
 * @param  EvtHandlerFunc This is the Service handler that is called to report a non-GATT event.
 * @retval 0  Success
 * @retval -1 Not able to register the handler. Increase number of supported event handlers with BLE_CFG_MAX_NBR_EVT_HANDLERS.
 */
int BLEEVT_RegisterHandler(BLEEVT_HciPcktHandlerFunc_t EvtHandlerFunc);

/**
 * @brief This callback is triggered when either
 *          + a standard HCI event is received from the BLE core device.
 *          + a proprietary event not positively acknowledged by the registered handler is received from the
 *            BLE core device. 
 *        This callback is triggered in the BLEStack_Process() context.
 *
 * @param  hci_pckt: The user event received from the BLE core device
 * @retval None
 */
void BLEEVT_App_Notification(const hci_pckt *hci_pckt);

#ifdef __cplusplus
}
#endif

#endif /*BLE_EVT_H */

