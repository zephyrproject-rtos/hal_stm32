/**
  ******************************************************************************
  * @file    ble_evt.c
  * @author  GPM WBL Application Team
  * @brief   BLE Event Dispatcher
  *****************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  *****************************************************************************
  */


/* Includes ------------------------------------------------------------------*/
#include "ble.h"
#include "ble_evt.h"

#ifndef BLE_CFG_MAX_NBR_GATT_EVT_HANDLERS
#define BLE_CFG_MAX_NBR_GATT_EVT_HANDLERS   0
#endif

#ifndef BLE_CFG_MAX_NBR_EVT_HANDLERS
#define BLE_CFG_MAX_NBR_EVT_HANDLERS        0
#endif

/* Private typedef -----------------------------------------------------------*/
typedef struct
{
#if (BLE_CFG_MAX_NBR_GATT_EVT_HANDLERS > 0)
BLEEVT_GattEvtHandlerFunc_t BLEEVT_SvcHandlerTab[BLE_CFG_MAX_NBR_GATT_EVT_HANDLERS];
#endif
uint8_t NbrOfRegisteredHandlers;
} BLEEVT_GattEvtHandler_t;

typedef struct
{
#if (BLE_CFG_MAX_NBR_EVT_HANDLERS > 0)
BLEEVT_HciPcktHandlerFunc_t BLEEVT_GenericHandlerTable[BLE_CFG_MAX_NBR_EVT_HANDLERS];
#endif
uint8_t NbrOfRegisteredHandlers;
} BLEEVT_GenericHandler_t;

/* Private defines -----------------------------------------------------------*/
#define BLEEVT_EGID_EVT_MASK   0xFC00
#define BLEEVT_GATT_EVT_TYPE   (3<<10)

/* Private macros ------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
BLEEVT_GattEvtHandler_t BLEEVT_GattEvtHandler;
BLEEVT_GenericHandler_t BLEEVT_GenericHandler;

/* Private functions ---------------------------------------------------------*/
/* Weak functions ------------------------------------------------------------*/

/* Functions Definition ------------------------------------------------------*/

void BLEEVT_Init(void)
{

  /**
   * Initialize the number of registered Handler
   */
  BLEEVT_GattEvtHandler.NbrOfRegisteredHandlers = 0;
  BLEEVT_GenericHandler.NbrOfRegisteredHandlers = 0;

  return;
}

int BLEEVT_RegisterGattEvtHandler(BLEEVT_GattEvtHandlerFunc_t EvtHandlerFunc)
{
  if(BLEEVT_GattEvtHandler.NbrOfRegisteredHandlers == BLE_CFG_MAX_NBR_GATT_EVT_HANDLERS)
  {
    return -1;
  }
#if (BLE_CFG_MAX_NBR_GATT_EVT_HANDLERS > 0)
  BLEEVT_GattEvtHandler.BLEEVT_SvcHandlerTab[BLEEVT_GattEvtHandler.NbrOfRegisteredHandlers] = EvtHandlerFunc;
  BLEEVT_GattEvtHandler.NbrOfRegisteredHandlers++;
#else
  (void)(EvtHandlerFunc);
#endif

  return 0;
}

int BLEEVT_RegisterHandler(BLEEVT_HciPcktHandlerFunc_t EvtHandlerFunc)
{
  if(BLEEVT_GenericHandler.NbrOfRegisteredHandlers == BLE_CFG_MAX_NBR_EVT_HANDLERS)
  {
    return -1;
  }
#if (BLE_CFG_MAX_NBR_EVT_HANDLERS > 0)
  BLEEVT_GenericHandler.BLEEVT_GenericHandlerTable[BLEEVT_GenericHandler.NbrOfRegisteredHandlers] = EvtHandlerFunc;
  BLEEVT_GenericHandler.NbrOfRegisteredHandlers++;
#else
  (void)(EvtHandlerFunc);
#endif

  return 0;
}

void BLE_STACK_Event(hci_pckt *hci_pckt, uint16_t length)
{
  BLEEVT_EvtAckStatus_t event_notification_status = BLEEVT_NoAck;
  
  if(hci_pckt->type == HCI_EVENT_PKT_TYPE || hci_pckt->type == HCI_EVENT_EXT_PKT_TYPE)
  {
    void *data;
    hci_event_pckt *event_pckt = (hci_event_pckt*)hci_pckt->data;
    
    if(hci_pckt->type == HCI_EVENT_PKT_TYPE){
      data = event_pckt->data;
    }
    else { /* hci_pckt->type == HCI_EVENT_EXT_PKT_TYPE */
      hci_event_ext_pckt *event_pckt = (hci_event_ext_pckt*)hci_pckt->data;
      data = event_pckt->data;
    }
    
    if(event_pckt->evt == HCI_VENDOR_EVT_CODE) /* evt fields is at same offset in hci_event_pckt and hci_event_ext_pckt */
    {
      aci_blecore_event * blecore_evt = (aci_blecore_event*) data;
      
      if((blecore_evt->ecode & BLEEVT_EGID_EVT_MASK) == BLEEVT_GATT_EVT_TYPE)
      {
        /* GATT events */
        
#if (BLE_CFG_MAX_NBR_GATT_EVT_HANDLERS > 0)
        /* For GATT event handler */
        for (uint8_t index = 0; index < BLEEVT_GattEvtHandler.NbrOfRegisteredHandlers; index++)
        {
          event_notification_status = BLEEVT_GattEvtHandler.BLEEVT_SvcHandlerTab[index](blecore_evt);
          /**
          * When a GATT event has been acknowledged by application, do not call other registered handler.
          * a GATT event may be relevant for only one Service
          */
          if (event_notification_status == BLEEVT_Ack)
          {
            /**
            *  The event has been managed. The Event processing should be stopped
            */
            break;
          }
        }
#endif
      }
      else
      {
        /* Proprietary non-GATT events */
        
#if (BLE_CFG_MAX_NBR_EVT_HANDLERS > 0)
        /* For generic event handler */
        for(uint8_t index = 0; index <BLEEVT_GenericHandler.NbrOfRegisteredHandlers; index++)
        {
          event_notification_status = BLEEVT_GenericHandler.BLEEVT_GenericHandlerTable[index](hci_pckt);
          /**
          * When an event has been acknowledged by application, do not call the other registered handler.
          */
          if (event_notification_status == BLEEVT_Ack)
          {
            /**
            *  The event has been managed. The Event processing should be stopped
            */
            break;
          }
        }
#endif
      }
    }
    else
    {
      /* Standard events */
      
#if (BLE_CFG_MAX_NBR_EVT_HANDLERS > 0)
      /* For generic event handler () */
      for(uint8_t index = 0; index <BLEEVT_GenericHandler.NbrOfRegisteredHandlers; index++)
      {
        event_notification_status = BLEEVT_GenericHandler.BLEEVT_GenericHandlerTable[index](hci_pckt);
      }
#endif
    }
  }
  
  /**
   * When no registered handlers has acknowledged the event, it is reported to the application.
   */
  
  if(event_notification_status == BLEEVT_NoAck)
  {
    BLEEVT_App_Notification(hci_pckt);
  }
}

