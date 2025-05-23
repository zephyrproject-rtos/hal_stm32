/**
  ******************************************************************************
  * @file    stm32mp2xx_hal_pcd.c
  * @author  MCD Application Team
  * @brief   PCD HAL module driver.
  *          This file provides firmware functions to manage the following
  *          functionalities of the USB Peripheral Controller:
  *           + Initialization and de-initialization functions
  *           + IO operation functions
  *           + Peripheral Control functions
  *           + Peripheral State functions
  *
  @verbatim
  ==============================================================================
                    ##### How to use this driver #####
  ==============================================================================
    [..]
      The PCD HAL driver can be used as follows:

     (#) Declare a PCD_HandleTypeDef handle structure, for example:
         PCD_HandleTypeDef  hpcd;

     (#) Fill parameters of Init structure in HCD handle

     (#) Call HAL_PCD_Init() API to initialize the PCD peripheral (Core, Device core, ...)

     (#) Initialize the PCD low level resources through the HAL_PCD_MspInit() API:
         (##) Enable the PCD/USB Low Level interface clock
         (##) Initialize the related GPIO clocks
         (##) Configure PCD pin-out
         (##) Configure PCD NVIC interrupt

     (#)Associate the Upper USB device stack to the HAL PCD Driver:
         (##) hpcd.pData = pdev;

     (#)Enable PCD transmission and reception:
         (##) HAL_PCD_Start();

  @endverbatim
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include <string.h>
#include <stdio.h>
#include "stm32mp2xx_hal.h"

#define PCD_DBGLOG(...) (void)printf("PCD_DEBUG : " __VA_ARGS__);
#if (PCD_DEBUG_LEVEL > 0)
#define PCD_DBGLOG1(...)  (void)printf("PCD_DEBUG : " __VA_ARGS__);
#else
#define PCD_DBGLOG1(...)
#endif /*PCD_DEBUG_LEVEL 1*/
#if (PCD_DEBUG_LEVEL > 1)
#define PCD_DBGLOG2(...)  (void)printf("PCD_DEBUG : " __VA_ARGS__);
#else
#define PCD_DBGLOG2(...)
#endif /*PCD_DEBUG_LEVEL 2*/
#if (PCD_DEBUG_LEVEL > 2)
#define PCD_DBGLOG3(...)  (void)printf("PCD_DEBUG : " __VA_ARGS__);
#else
#define PCD_DBGLOG3(...)
#endif /*PCD_DEBUG_LEVEL 3*/

/** @addtogroup STM32MP2xx_HAL_Driver
  * @{
  */

/** @defgroup PCD PCD
  * @brief PCD HAL module driver
  * @{
  */

#ifdef HAL_PCD_MODULE_ENABLED

/* Private types -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
#define PCD_DEV_EVENTS_INTR 0 /* Interrupt to use for device events */

/** @defgroup PCD_Private_Macros PCD Private Macros
  * @{
  */
#define IS_MULTIPLE(x, a)   (((x) % (a)) == 0U)
#define ALIGN_MULTIPLE(x, a)  ((a) * (((x) / (a)) + ((((x) % (a)) != 0U) ? 1U : 0U)))

#define IS_ALIGNED(x, a)    (((x) & ((typeof(x))(a) - 1)) == 0)

/**
  * @}
  */

/* Private functions prototypes ----------------------------------------------*/
/** @defgroup PCD_Private_Functions PCD Private Functions
  * @{
  */

static PCD_DmaAddrDef PCD_MapDmaAddr(const uint8_t buf[], uint32_t size, uint8_t to_device)
{
  UNUSED(size);
  UNUSED(to_device);
  return (PCD_DmaAddrDef)buf;
}

static void PCD_UnMapDmaAddr(PCD_DmaAddrDef dma_addr, uint32_t size, uint8_t to_device)
{
  UNUSED(dma_addr);
  UNUSED(size);
  UNUSED(to_device);
  return;
}

static PCD_DmaAddrDef PCD_GetDmaAddr(const uint8_t buf[], uint32_t size, uint8_t to_device)
{
  UNUSED(size);
  UNUSED(to_device);
  return (PCD_DmaAddrDef)buf;
}

static void PCD_PutDmaAddr(PCD_DmaAddrDef dma_addr, uint32_t size, uint8_t to_device)
{
  UNUSED(dma_addr);
  UNUSED(size);
  UNUSED(to_device);
  return;
}

static void *PCD_MapCoherentAddr(void *addr, uint32_t size)
{
  UNUSED(addr);
  UNUSED(size);
  return addr;
}

static void PCD_UnMapCoherentAddr(const void *addr)
{
  UNUSED(addr);
  return;
}

static void *PCD_MapIOAddr(uint32_t addr, uint32_t size)
{
  UNUSED(addr);
  UNUSED(size);
  return (uint32_t *)addr;
}

static void PCD_UnMapIOAddr(const void *addr)
{
  UNUSED(addr);
  return;
}

static int32_t PCD_IRQRegister(void (*irq_handler)(PCD_HandleTypeDef *hpcd), const PCD_HandleTypeDef *hpcd)
{
  UNUSED(irq_handler);
  UNUSED(hpcd);
  return (int32_t)HAL_OK;
}

static void PCD_IRQUnRegister(const PCD_HandleTypeDef *hpcd)
{
  UNUSED(hpcd);
  return;
}

static void PCD_Memcpy(void *dest, const void *src, uint32_t num)
{
#ifdef AVOID_COMPILER_MEMCPY
  uint8_t *pcDst = (uint8_t *) dest;
  uint8_t const *pcSrc = (uint8_t const *) src;

  while (num--)
  {
    *pcDst++ = *pcSrc++;
  }
#else
  (void)memcpy(dest, src, num);
#endif /*AVOID_COMPILER_MEMCPY*/

  return;
}

static void PCD_Handle_EP_Event(PCD_HandleTypeDef *hpcd, uint32_t event)
{
  uint8_t type = USB_ReadEndpointEventType(event);
  uint8_t phy_epnum = USB_ReadEndpointEventEpNum(event);
  uint8_t status = USB_ReadEndpointEventStatus(event);
  uint8_t ep_addr;
  uint8_t ep_num;
  USB_DWC3_EPTypeDef *ep;
  HAL_StatusTypeDef ret;

  ep_addr = __HAL_PCD_PHYEPNUM_TO_EPADDR(phy_epnum);
  ep_num = ep_addr & 0x7FU;

  if ((ep_addr & 0x80U) == 0x80U)
  {
    ep = &hpcd->IN_ep[ep_num];
  }
  else
  {
    ep = &hpcd->OUT_ep[ep_num];
  }

  switch (type)
  {
    case USB_DWC3_DEPEVT_XFERCOMPLETE:
      PCD_DBGLOG3("EP%d%s: Transfer Complete Event=%lx\n", ep_num, ep->is_in ? "IN" : "OUT", event);

      if (ep->type == EP_TYPE_ISOC)
      {
        PCD_DBGLOG1("EP%d%s is an Isochronous endpoint\n", ep_num, ep->is_in ? "IN" : "OUT");
        break;
      }

      /* Just for Log, since ctrl expects sw to follow the whole control
      programming sequence, as also mentioned in Linux driver */
      if ((USB_GetTRBStatusEP(ep) == USB_DWC3_TRBSTS_SETUP_PENDING) && (ep_num == 0U))
      {
        PCD_DBGLOG3("EP%d%s Setup Pending received\n", ep_num, ep->is_in ? "IN" : "OUT");
      }

      PCD_DBGLOG2("EP%d%s: Transfer Complete trb %08lx:%08lx:%08lx:%08lx:%08lx TRB-Status %d\n", ep_num,
                  ep->is_in ? "IN" : "OUT",
                  (uint32_t)ep->trb_addr, (uint32_t)ep->trb_addr->bph,
                  (uint32_t)ep->trb_addr->bpl, (uint32_t)ep->trb_addr->size,
                  (uint32_t)ep->trb_addr->ctrl, USB_GetTRBStatusEP(ep));

      if ((ep_addr & 0x80U) == 0x80U)   /* IN EP */
      {
        ep->xfer_count = ep->xfer_len - USB_GetTRBLengthEP(ep);

        ep->flags &= ~USB_DWC3_EP_REQ_QUEUED;

        if (ep->xfer_buff != 0U)
        {
          PCD_UnMapDmaAddr(ep->dma_addr, ep->xfer_len, 1);
        }

        /* For EP0IN, if packet is not sent completely, then error, as done in Linux driver */
        if ((ep_num == 0U) && (ep->xfer_len != ep->xfer_count))
        {
          ret = HAL_PCD_EP_SetStall(hpcd, ep_num); /*OUT EP0*/
          if (ret != HAL_OK)
          {
            PCD_DBGLOG1("Error : %s: %d\n", __func__, __LINE__);
          }
        }

        /* if 3-stage then wait for XFERNOTREADY(control-status) before sending data to upper layer*/
        if ((ep_num != 0U) || (ep->xfer_len == 0U))
        {
          HAL_PCD_DataInStageCallback(hpcd, ep_num);
        }

        /* For EP0, this is ZLP, so prepare EP0 for next setup */
        if ((ep_num == 0U) && (ep->xfer_len == 0U))
        {
          /* prepare to rx more setup packets */
          hpcd->EP0_State = HAL_PCD_EP0_SETUP_QUEUED;

          ret = USB_EP0_OutStart(hpcd->Instance, &hpcd->OUT_ep[0], hpcd->Setup_dma_addr);
          if (ret != HAL_OK)
          {
            PCD_DBGLOG1("Error : %s: %d\n", __func__, __LINE__);
            return;
          }
        }
      }
      else
      {
        ep->xfer_count = ep->xfer_len - USB_GetTRBLengthEP(ep);

        ep->flags &= ~USB_DWC3_EP_REQ_QUEUED;

        /* For EP0OUT */
        if ((ep_addr == 0U) && (hpcd->EP0_State == HAL_PCD_EP0_SETUP_QUEUED))
        {

          hpcd->EP0_State = HAL_PCD_EP0_SETUP_COMPLETED;
          ep->is_stall = false;
          PCD_DBGLOG2("EP%d%s: SetupData %02x%02x%02x%02x:%02x%02x%02x%02x\n", ep_num, ep->is_in ? "IN" : "OUT",
                      hpcd->Setup_addr[0], hpcd->Setup_addr[1], hpcd->Setup_addr[2], hpcd->Setup_addr[3],
                      hpcd->Setup_addr[4], hpcd->Setup_addr[5], hpcd->Setup_addr[6], hpcd->Setup_addr[7]);

          /* if 2-stage then wait for the XFERNOTREADY(control-status) */
          if (__HAL_PCD_SETUP_REQ_LEN(hpcd->Setup_addr) != 0U)
          {
            HAL_PCD_SetupStageCallback(hpcd);
          }
        }
        else
        {

          if (ep->xfer_buff != 0U)
          {
            PCD_UnMapDmaAddr(ep->dma_addr, ep->xfer_len, 0);
          }

          if (ep->xfer_buff == ep->bounce_buf)
          {
            PCD_Memcpy(ep->xfer_dest_buff, ep->xfer_buff, ep->xfer_count);
          }

          /* if 3-stage then wait for XFERNOTREADY(control-status) before sending data to upper layer */
          if ((ep_num != 0U) || (ep->xfer_len == 0U))
          {
            HAL_PCD_DataOutStageCallback(hpcd, ep_num);
          }

          /* For EP0, this is ZLP, so prepare EP0 for next setup */
          if ((ep_num == 0U) && (ep->xfer_len == 0U))
          {
            /* prepare to rx more setup packets */
            hpcd->EP0_State = HAL_PCD_EP0_SETUP_QUEUED;

            ret = USB_EP0_OutStart(hpcd->Instance, &hpcd->OUT_ep[0], hpcd->Setup_dma_addr);
            if (ret != HAL_OK)
            {
              PCD_DBGLOG1("Error : %s: %d\n", __func__, __LINE__);
              return;
            }
          }
        }
      }

      break;

    case USB_DWC3_DEPEVT_XFERINPROGRESS:
      PCD_DBGLOG1("EP%d%s: Transfer In-Progress %ld Event=%lx\n", ep_num, ep->is_in ? "IN" : "OUT",
                  hpcd->IntBuffers.EvtBufferPos[0], event);

      if (ep_num == 0U)
      {
        break;
      }

      if (ep->type != EP_TYPE_ISOC)
      {
        break;
      }

      PCD_DBGLOG2("EP%d%s: Transfer Complete trb %08lx:%08lx:%08lx:%08lx:%08lx TRB-Status %d\n", ep_num,
                  ep->is_in ? "IN" : "OUT",
                  (uint32_t)ep->trb_addr, (uint32_t)ep->trb_addr->bph,
                  (uint32_t)ep->trb_addr->bpl, (uint32_t)ep->trb_addr->size,
                  (uint32_t)ep->trb_addr->ctrl, USB_GetTRBStatusEP(ep));

      if (USB_GetTRBStatusEP(ep) == USB_DWC3_TRBSTS_MISSED_ISOC)
      {
        PCD_DBGLOG("EP%d%s Missed Isoc Interval received\n", ep_num, ep->is_in ? "IN" : "OUT");
        (void)USB_EPStopXfer(hpcd->Instance, ep);
      }
      if ((ep_addr & 0x80U) == 0x80U)   /* IN EP */
      {
        /* length valid only if TRB-Status is normal */
        if (USB_GetTRBStatusEP(ep) != USB_DWC3_TRBSTS_MISSED_ISOC)
        {
          ep->xfer_count = ep->xfer_len - USB_GetTRBLengthEP(ep);
        }

        ep->flags &= ~USB_DWC3_EP_REQ_QUEUED;

        if (ep->xfer_buff != 0)
        {
          PCD_UnMapDmaAddr(ep->dma_addr, ep->xfer_len, 1);
        }

        HAL_PCD_DataInStageCallback(hpcd, ep_num);
      }
      else
      {
        /*length valid only if TRB-Status is normal*/
        if (USB_GetTRBStatusEP(ep) != USB_DWC3_TRBSTS_MISSED_ISOC)
        {
          ep->xfer_count = ep->xfer_len - USB_GetTRBLengthEP(ep);
        }

        ep->flags &= ~USB_DWC3_EP_REQ_QUEUED;

        if (ep->xfer_buff != 0)
        {
          PCD_UnMapDmaAddr(ep->dma_addr, ep->xfer_len, 0);
        }

        if (ep->xfer_buff == ep->bounce_buf)
        {
          PCD_Memcpy(ep->xfer_dest_buff, ep->xfer_buff, ep->xfer_count);
        }

        HAL_PCD_DataOutStageCallback(hpcd, ep_num);
      }

      break;

    case USB_DWC3_DEPEVT_XFERNOTREADY:
      PCD_DBGLOG3("EP%d%s: Transfer Not Ready Event=%lx\n", ep_num, ep->is_in ? "IN" : "OUT", event);
      /* For EP0IN or EP0OUT, xfernotready interrupt not used */

      if (ep_num == 0U)
      {
        if (hpcd->EP0_State == HAL_PCD_EP0_SETUP_QUEUED)
        {
          ret = HAL_PCD_EP_SetStall(hpcd, ep_num);  /*OUT EP0*/
          if (ret != HAL_OK)
          {
            PCD_DBGLOG1("Error : %s: %d\n", __func__, __LINE__);
            return;
          }
        }
        else
        {
          if (__HAL_PCD_SETUP_REQ_LEN(hpcd->Setup_addr) == 0U)
          {
            switch (status)
            {
              case USB_DWC3_DEPEVT_XFERNOTREADY_STATUS_CTRL_STATUS:
                HAL_PCD_SetupStageCallback(hpcd);
                break;
              case USB_DWC3_DEPEVT_XFERNOTREADY_STATUS_CTRL_DATA:
                ret = HAL_PCD_EP_SetStall(hpcd, ep_num); /*OUT EP0*/
                if (ret != HAL_OK)
                {
                  PCD_DBGLOG1("Error : %s: %d\n", __func__, __LINE__);
                }
                break;
              default:
                PCD_DBGLOG1("Error : %s: %d\n", __func__, __LINE__);
                break;
            }
          }
          else
          {
            switch (status)
            {
              case USB_DWC3_DEPEVT_XFERNOTREADY_STATUS_CTRL_STATUS:
                if ((ep_addr & 0x80U) == 0x80U)
                {
                  HAL_PCD_DataOutStageCallback(hpcd, ep_num);
                }
                else
                {
                  HAL_PCD_DataInStageCallback(hpcd, ep_num);
                }
                break;
              case USB_DWC3_DEPEVT_XFERNOTREADY_STATUS_CTRL_DATA:
                if ((ep_addr & 0x80U) == 0x80U)
                {
                  /* if wrong direction */
                  if (__HAL_PCD_SETUP_REQ_DATA_DIR_IN(hpcd->Setup_addr) == 0U)
                  {
                    ret = USB_EPStopXfer(hpcd->Instance, &hpcd->OUT_ep[0]);
                    if (ret != HAL_OK)
                    {
                      PCD_DBGLOG1("Error : %s: %d\n", __func__, __LINE__);
                    }
                    ret = HAL_PCD_EP_SetStall(hpcd, ep_num); /*OUT EP0*/
                    if (ret != HAL_OK)
                    {
                      PCD_DBGLOG1("Error : %s: %d\n", __func__, __LINE__);
                    }
                  }
                  /* last packet is MPS multiple, so send ZLP packet, handled by USBD_core.c */
                }
                else
                {
                  /* if wrong direction */
                  if (__HAL_PCD_SETUP_REQ_DATA_DIR_IN(hpcd->Setup_addr) != 0U)
                  {
                    ret = USB_EPStopXfer(hpcd->Instance, &hpcd->IN_ep[0]);
                    if (ret != HAL_OK)
                    {
                      PCD_DBGLOG1("Error : %s: %d\n", __func__, __LINE__);
                    }
                    ret = HAL_PCD_EP_SetStall(hpcd, ep_num); /*OUT EP0*/
                    if (ret != HAL_OK)
                    {
                      PCD_DBGLOG1("Error : %s: %d\n", __func__, __LINE__);
                    }
                  }
                }
                break;
              default:
                PCD_DBGLOG1("Error : %s: %d\n", __func__, __LINE__);
                break;
            }
          }
        }
      }

      /* HAL doesn't provide request queue to support On-demand transfers for non-isoc EP,
      it only supports preset transfers so this event will not be used, Section 9.2.4
      "Transfer Setup Recommendations" */

      /* But for isoc transfers we need to issue the request from here using the micro-frame number */
      if (ep->type != EP_TYPE_ISOC)
      {
        break;
      }

      /* if pending isoc transfer then issue it now using the uframe number */
      ep->uframe = USB_ReadEndpointEventParam(event) & ~((1U << (ep->bInterval - 1U)) - 1U);
      PCD_DBGLOG1("EP%d%s: ISOC Transfer Not Ready %lx\n", ep_num, ep->is_in ? "IN" : "OUT", (uint32_t)ep->uframe);

      if ((ep->flags & USB_DWC3_EP_ISOC_START_PENDING) != 0U)
      {
        ret = USB_EPStartXfer(hpcd->Instance, ep);
        if (ret != HAL_OK)
        {
          PCD_DBGLOG1("Error : %s: %d\n", __func__, __LINE__);
          return;
        }
      }
      break;

    case USB_DWC3_DEPEVT_STREAMEVT: /* Stream event, Not used */
      break;
    case USB_DWC3_DEPEVT_RXTXFIFOEVT: /* FIFO Overrun */
      break;
    case USB_DWC3_DEPEVT_EPCMDCMPLT: /* Endpoint Command Complete */
      PCD_DBGLOG1("EP%d%s: Endpoint Command Complete Event=%lx\n", ep_num, ep->is_in ? "IN" : "OUT", event);
      break;
    default:
      break;
  }
}

static void PCD_Handle_DEV_Event(PCD_HandleTypeDef *hpcd, uint32_t event)
{
  uint8_t type = USB_ReadDeviceEventType(event);
  uint8_t i;
  USB_DWC3_EPTypeDef *ep;
  HAL_StatusTypeDef ret;

  switch (type)
  {
    case USB_DWC3_DEVICE_EVENT_DISCONNECT:
      PCD_DBGLOG1("Event: Device Disconnect\n");
      /* For SuperSpeed, set DCTL[8:5] to 5*/

      HAL_PCD_DisconnectCallback(hpcd);
      break;

    case USB_DWC3_DEVICE_EVENT_RESET:
      PCD_DBGLOG1("Event: Device Reset\n");

      if (hpcd->EP0_State != HAL_PCD_EP0_SETUP_QUEUED)
      {
        ret = USB_EPStopXfer(hpcd->Instance, &hpcd->OUT_ep[0]);
        if (ret != HAL_OK)
        {
          PCD_DBGLOG1("Error : %s: %d\n", __func__, __LINE__);
        }
        ret = HAL_PCD_EP_SetStall(hpcd, 0); /*OUT EP0*/
        if (ret != HAL_OK)
        {
          PCD_DBGLOG1("Error : %s: %d\n", __func__, __LINE__);
        }
      }

      /* Stop transfers for all(USB_DWC3_NUM_IN_EPS) EP except EP0IN k = USB_DWC3_NUM_IN_EP */
      for (i = 0; i < USB_DWC3_NUM_IN_EP; i++)
      {
        if (USB_EPStopXfer(hpcd->Instance, &hpcd->IN_ep[i]) == HAL_OK)
        {
          /* Nothing to Do*/
        }
      }

      /* Stop transfers for all EP except EP0OUT k = USB_DWC3_NUM_OUT_EP */
      for (i = 1; i < USB_DWC3_NUM_OUT_EP; i++)
      {
        if (USB_EPStopXfer(hpcd->Instance, &hpcd->OUT_ep[i]) == HAL_OK)
        {
          /* Nothing to Do*/
        }
      }

      /* Clear Stall for all EP except EP0IN k = USB_DWC3_NUM_IN_EP */
      for (i = 1; i < USB_DWC3_NUM_IN_EP; i++)
      {
        ep = &hpcd->IN_ep[i];

        if (!ep->is_stall)
        {
          continue;
        }

        ep->is_stall = false;

        ret = USB_EPClearStall(hpcd->Instance, ep);
        if (ret != HAL_OK)
        {
          PCD_DBGLOG1("Error : %s: %d\n", __func__, __LINE__);
          return;
        }
      }

      /* Clear Stall for all EP except EP0OUT k = USB_DWC3_NUM_OUT_EP */
      for (i = 1; i < USB_DWC3_NUM_OUT_EP; i++)
      {
        ep = &hpcd->OUT_ep[i];

        if (!ep->is_stall)
        {
          continue;
        }

        ep->is_stall = false;

        ret = USB_EPClearStall(hpcd->Instance, ep);
        if (ret != HAL_OK)
        {
          PCD_DBGLOG1("Error : %s: %d\n", __func__, __LINE__);
          return;
        }

      }

      /* Reset device address to zero */
      ret = USB_SetDevAddress(hpcd->Instance, 0);
      if (ret != HAL_OK)
      {
        PCD_DBGLOG1("Error : %s: %d\n", __func__, __LINE__);
        return;
      }

      break;

    case USB_DWC3_DEVICE_EVENT_CONNECT_DONE:
      PCD_DBGLOG1("Event: Device Connection Done\n");

      /*hpcd->Init.ep0_mps = MaxPacketSize to 512 (SuperSpeed), 64 (High-Speed), 8/16/32/64 (Full-Speed),/
       or 8 (Low-Speed).*/
      hpcd->Init.speed = USB_GetDevSpeed(hpcd->Instance);
      switch (hpcd->Init.speed)
      {
        case USB_DWC3_SPEED_SUPER:
          hpcd->Init.ep0_mps = PCD_SPEED_SUPER_MAXPACKETSIZE;
          break;
        case USB_DWC3_SPEED_HIGH:
          hpcd->Init.ep0_mps = PCD_SPEED_HIGH_MAXPACKETSIZE;
          break;
        case USB_DWC3_SPEED_FULL_48:
        case USB_DWC3_SPEED_FULL:
          hpcd->Init.ep0_mps = PCD_SPEED_FULL_MAXPACKETSIZE;
          break;
        case USB_DWC3_SPEED_LOW:
          hpcd->Init.ep0_mps = PCD_SPEED_LOW_MAXPACKETSIZE;
          break;
        default:
          PCD_DBGLOG1("Error : %s: %d\n", __func__, __LINE__);
          break;
      }


      HAL_PCD_ResetCallback(hpcd);

      /* Update DWC3_GCTL_RAMCLKSEL, but only for Superspeed */

      /* Modify max packet size for EP 0 & 1 */
      ret = USB_ConfigureEP(hpcd->Instance, 0, false, EP_TYPE_CTRL, hpcd->Init.ep0_mps, 0, 0, 0,
                            hpcd->OUT_ep[0].intr_num, USB_DWC3_DEPCFG_ACTION_MODIFY);
      if (ret != HAL_OK)
      {
        PCD_DBGLOG1("Error : %s: %d\n", __func__, __LINE__);
        return;
      }
      ret = USB_ConfigureEP(hpcd->Instance, 0, true, EP_TYPE_CTRL, hpcd->Init.ep0_mps, 0, 0, 1,
                            hpcd->IN_ep[0].intr_num, USB_DWC3_DEPCFG_ACTION_MODIFY);
      if (ret != HAL_OK)
      {
        PCD_DBGLOG1("Error : %s: %d\n", __func__, __LINE__);
        return;
      }

      hpcd->OUT_ep[0].maxpacket = hpcd->Init.ep0_mps;
      hpcd->IN_ep[0].maxpacket = hpcd->Init.ep0_mps;

      /* Depending on the connected speed, write to the other PHY's control register to suspend it. */

      /* Use default values for GTXFIFOSIZn and GRXFIFOSIZ0 */
      break;

    case USB_DWC3_DEVICE_EVENT_LINK_STATUS_CHANGE:
      PCD_DBGLOG1("Event: Link Status Change : %s(%d)\n",
                  USB_GetLinkStateString(USB_ReadDeviceEventLinkState(event)),
                  USB_ReadDeviceEventLinkState(event));
      /* Handle link state changes, U0,U1,U2,U3 with suspend/resume functions */
      break;

    case USB_DWC3_DEVICE_EVENT_WAKEUP:
      PCD_DBGLOG1("Event: Wake-UP\n");
      /* resume function */
      HAL_PCD_ResumeCallback(hpcd);
      break;

    case USB_DWC3_DEVICE_EVENT_HIBER_REQ:
      PCD_DBGLOG1("Event: Hibernation Request\n");
      /* hibernation function */
      break;

    case USB_DWC3_DEVICE_EVENT_EOPF: /* End of Periodic Frame */
      PCD_DBGLOG1("Event: Suspend\n");
      HAL_PCD_SuspendCallback(hpcd);
      break;

    case USB_DWC3_DEVICE_EVENT_SOF: /* Start of Periodic Frame */
      PCD_DBGLOG1("Event: Start of Periodic Frame\n");
      break;

    case USB_DWC3_DEVICE_EVENT_L1SUSPEND:
      PCD_DBGLOG1("Event: L1 Suspend\n");
      HAL_PCD_SuspendCallback(hpcd);
      break;

    case USB_DWC3_DEVICE_EVENT_ERRATIC_ERROR: /* Erratic Error */
      PCD_DBGLOG1("Event: Erratic Error\n");
      break;

    case USB_DWC3_DEVICE_EVENT_CMD_CMPL: /* Command Complete */
      PCD_DBGLOG1("Event: Command Complete\n");
      break;

    case USB_DWC3_DEVICE_EVENT_OVERFLOW: /* Overflow */
      PCD_DBGLOG1("Event: Overflow\n");
      break;

    case USB_DWC3_DEVICE_EVENT_L1WAKEUP:
      PCD_DBGLOG("Event: L1 Wake-UP\n");
      /* resume function */
      HAL_PCD_ResumeCallback(hpcd);
      break;

    default:  /* UNKNOWN IRQ type */
      break;
  }
}
/**
  * @}
  */

/* Exported functions --------------------------------------------------------*/
/** @defgroup PCD_Exported_Functions PCD Exported Functions
  * @{
  */

/** @defgroup PCD_Exported_Functions_Group1 Initialization and de-initialization functions
  *  @brief    Initialization and Configuration functions
  *
@verbatim
 ===============================================================================
            ##### Initialization and de-initialization functions #####
 ===============================================================================
    [..]  This section provides functions allowing to:

@endverbatim
  * @{
  */

/**
  * @brief  Initializes the PCD according to the specified
  *         parameters in the PCD_InitTypeDef and initialize the associated handle.
  * @param  hpcd PCD handle
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_PCD_Init(PCD_HandleTypeDef *hpcd)
{
  uint8_t i;
  HAL_StatusTypeDef ret;

  hpcd->Instance = (PCD_TypeDef *) PCD_MapIOAddr((uint32_t)hpcd->Instance, 0xCD00); /********/

  /* Check the PCD handle allocation */
  if (hpcd == NULL)
  {
    return HAL_ERROR;
  }

  /* Check the parameters */
  assert_param(IS_PCD_ALL_INSTANCE(hpcd->Instance));

  /* Check hpcd->State is HAL_PCD_STATE_RESET, otherwise error */
  assert_param(hpcd->State == HAL_PCD_STATE_RESET);

  hpcd->State = HAL_PCD_STATE_BUSY;

  /* Init the low level hardware : GPIO, CLOCK, NVIC... */
  HAL_PCD_MspInit(hpcd);

  /* Disable the Interrupts */
  for (i = 0; i < USB_DWC3_INT_INUSE; i++)
  {
    __HAL_PCD_DISABLE_INTR(hpcd, i);
  }

  /* Init the Core (common init.) */
  ret = USB_CoreInit(hpcd->Instance, hpcd->Init);
  if (ret != HAL_OK)
  {
    PCD_DBGLOG1("Error : %s: %d\n", __func__, __LINE__);
    return ret;
  }

  /* Init endpoints structures */
  for (i = 0; i < USB_DWC3_NUM_IN_EP ; i++)
  {
    /* Init ep structure */
    hpcd->IN_ep[i].is_in = true;
    hpcd->IN_ep[i].num = i;
    hpcd->IN_ep[i].tx_fifo_num = i;
    /* Control until ep is activated */
    hpcd->IN_ep[i].type = EP_TYPE_CTRL;

    /*
     * We are doing 1:1 alternate mapping for endpoints, meaning
     * IN Endpoint X maps to Physical Endpoint 2*X +1 and
     * OUT Endpoint X maps to Physical Endpoint 2*X.
     * So USB endpoint 0x81 is 0x03.
     */
    hpcd->IN_ep[i].phy_epnum = __HAL_PCD_EPADDR_TO_PHYEPNUM(i | 0x80U);

  }

  for (i = 0; i < USB_DWC3_NUM_OUT_EP ; i++)
  {
    /* Init ep structure */
    hpcd->OUT_ep[i].is_in = false;
    hpcd->OUT_ep[i].num = i;
    hpcd->OUT_ep[i].tx_fifo_num = i;
    /* Control until ep is activated */
    hpcd->OUT_ep[i].type = EP_TYPE_CTRL;

    /*
     * We are doing 1:1 alternate mapping for endpoints, meaning
     * IN Endpoint X maps to Physical Endpoint 2*X +1 and
     * OUT Endpoint X maps to Physical Endpoint 2*X.
     * So USB endpoint 0x81 is 0x03.
     */
    hpcd->OUT_ep[i].phy_epnum = __HAL_PCD_EPADDR_TO_PHYEPNUM(i);

  }

  hpcd->Setup_dma_addr = (PCD_DmaAddrDef)PCD_GetDmaAddr((void *)hpcd->Setup, sizeof(hpcd->Setup), 1);
  if (hpcd->Setup_dma_addr == 0U)
  {
    return HAL_ERROR;
  }

  hpcd->Setup_addr = PCD_MapCoherentAddr((void *)hpcd->Setup, sizeof(hpcd->Setup));
  if (hpcd->Setup_addr == 0U)
  {
    return HAL_ERROR;
  }

  /* Map DMA and Coherent address for event buffers k = USB_DWC3_INT_INUSE */
  for (i = 0; i < USB_DWC3_INT_INUSE; i++)
  {
    hpcd->IntBuffers.EvtBuffer_dma_addr[i] = PCD_GetDmaAddr((void *)hpcd->IntBuffers.EvtBuffer[i].EvtBufferArea,
                                                            sizeof(hpcd->IntBuffers.EvtBuffer[i].EvtBufferArea), 1);
    if (hpcd->IntBuffers.EvtBuffer_dma_addr[i] == 0U)
    {
      return HAL_ERROR;
    }

    hpcd->IntBuffers.EvtBuffer_addr[i] = PCD_MapCoherentAddr((void *)hpcd->IntBuffers.EvtBuffer[i].EvtBufferArea,
                                                             sizeof(hpcd->IntBuffers.EvtBuffer[i].EvtBufferArea));
    if (hpcd->IntBuffers.EvtBuffer_addr[i] == 0U)
    {
      return HAL_ERROR;
    }

    hpcd->IntBuffers.EvtBufferPos[i] = 0;

    PCD_DBGLOG3("EventBuffer%d: BuffArea=%08lx DmaAddr=%08lx CoherentMapAddr=%08lx\n", i,
                (uint32_t)hpcd->IntBuffers.EvtBuffer[i].EvtBufferArea, (uint32_t)hpcd->IntBuffers.EvtBuffer_dma_addr[i],
                (uint32_t)hpcd->IntBuffers.EvtBuffer_addr[i]);
  }

  /* MAP TRB Coherent and DMA address for EP0IN and EP0OUT */
  hpcd->IN_ep[0].trb_dma_addr = (uint32_t)PCD_GetDmaAddr((void *)&hpcd->IN_ep[0].trb, sizeof(hpcd->IN_ep[0].trb), 1);
  if (hpcd->IN_ep[0].trb_dma_addr == 0U)
  {
    return HAL_ERROR;
  }

  hpcd->IN_ep[0].trb_addr = (USB_DWC3_Trb *)PCD_MapCoherentAddr((void *)&hpcd->IN_ep[0].trb,
                                                                sizeof(hpcd->IN_ep[0].trb));
  if (hpcd->IN_ep[0].trb_addr == 0U)
  {
    return HAL_ERROR;
  }

  hpcd->OUT_ep[0].trb_dma_addr = (uint32_t)PCD_GetDmaAddr((void *)&hpcd->OUT_ep[0].trb, sizeof(hpcd->OUT_ep[0].trb), 1);
  if (hpcd->OUT_ep[0].trb_dma_addr == 0U)
  {
    return HAL_ERROR;
  }

  hpcd->OUT_ep[0].trb_addr = (USB_DWC3_Trb *)PCD_MapCoherentAddr((void *)&hpcd->OUT_ep[0].trb,
                                                                 sizeof(hpcd->OUT_ep[0].trb));
  if (hpcd->OUT_ep[0].trb_addr == 0U)
  {
    return HAL_ERROR;
  }

  if (PCD_IRQRegister(HAL_PCD_IRQHandler, hpcd) != 0)
  {
    return HAL_ERROR;
  }

  /* Init Device */
  hpcd->EP0_State = HAL_PCD_EP0_SETUP_QUEUED;
  ret = USB_DevInit(hpcd->Instance, hpcd->Init, hpcd->IntBuffers.EvtBuffer_dma_addr, &hpcd->OUT_ep[0],
                    hpcd->Setup_dma_addr, PCD_DEV_EVENTS_INTR);
  if (ret != HAL_OK)
  {
    PCD_DBGLOG1("Error : %s: %d\n", __func__, __LINE__);
    return ret;
  }

  hpcd->State = HAL_PCD_STATE_READY;


  return HAL_OK;
}

/**
  * @brief  DeInitializes the PCD peripheral.
  * @param  hpcd PCD handle
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_PCD_DeInit(PCD_HandleTypeDef *hpcd)
{
  uint32_t i;
  HAL_StatusTypeDef ret;

  /* Check the PCD handle allocation */
  if (hpcd == NULL)
  {
    return HAL_ERROR;
  }

  /* Check hpcd->State is HAL_PCD_STATE_RESET, otherwise error */
  assert_param(hpcd->State == HAL_PCD_STATE_RESET);

  hpcd->State = HAL_PCD_STATE_BUSY;

  /* Stop Device */

  PCD_IRQUnRegister(hpcd);

  /* UnInit the Core (common init.) */
  ret = USB_CoreUnInit(hpcd->Instance);
  if (ret != HAL_OK)
  {
    PCD_DBGLOG1("Error : %s: %d\n", __func__, __LINE__);
    return ret;
  }

  for (i = 0; i < USB_DWC3_INT_INUSE; i++)
  {
    PCD_UnMapCoherentAddr(hpcd->IntBuffers.EvtBuffer_addr[i]);

    PCD_PutDmaAddr(hpcd->IntBuffers.EvtBuffer_dma_addr[i], sizeof(hpcd->IntBuffers.EvtBuffer[i].EvtBufferArea), 1);
  }

  PCD_UnMapCoherentAddr(hpcd->Setup_addr);

  PCD_PutDmaAddr(hpcd->Setup_dma_addr, sizeof(hpcd->Setup), 1);

  /* DeInit the low level hardware */
  HAL_PCD_MspDeInit(hpcd);

  PCD_UnMapIOAddr(hpcd->Instance); /********/

  hpcd->State = HAL_PCD_STATE_RESET;

  return HAL_OK;
}

/**
  * @brief  Initializes the PCD MSP.
  * @param  hpcd PCD handle
  * @retval None
  */
__weak void HAL_PCD_MspInit(PCD_HandleTypeDef *hpcd)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hpcd);

  /* NOTE : This function Should not be modified, when the callback is needed,
            the HAL_PCD_MspInit could be implemented in the user file
   */
}

/**
  * @brief  DeInitializes PCD MSP.
  * @param  hpcd PCD handle
  * @retval None
  */
__weak void HAL_PCD_MspDeInit(PCD_HandleTypeDef *hpcd)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hpcd);

  /* NOTE : This function Should not be modified, when the callback is needed,
            the HAL_PCD_MspDeInit could be implemented in the user file
   */
}

/**
  * @}
  */

/** @defgroup PCD_Exported_Functions_Group2 Input and Output operation functions
  *  @brief   Data transfers functions
  *
@verbatim
 ===============================================================================
                      ##### IO operation functions #####
 ===============================================================================
    [..]
    This subsection provides a set of functions allowing to manage the PCD data
    transfers.

@endverbatim
  * @{
  */

/**
  * @brief  Start The USB OTG Device.
  * @param  hpcd PCD handle
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_PCD_Start(PCD_HandleTypeDef *hpcd)
{
  uint8_t i;

  /* Enable the USB Interrupts */
  for (i = 0; i < USB_DWC3_INT_INUSE; i++)
  {
    __HAL_PCD_ENABLE_INTR(hpcd, i);
  }

  /* Enable Pullups */
  return USB_DevConnect(hpcd->Instance);
}

/**
  * @brief  Stop The USB OTG Device.
  * @param  hpcd PCD handle
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_PCD_Stop(PCD_HandleTypeDef *hpcd)
{
  uint8_t i;

  /* FIFOs are flushed inside Stop Transfer command */
  /* Stop transfers for all(USB_DWC3_NUM_IN_EPS) EP except EP0IN k = USB_DWC3_NUM_IN_EP */
  for (i = 0; i < USB_DWC3_NUM_IN_EP; i++)
  {
    if (USB_EPStopXfer(hpcd->Instance, &hpcd->IN_ep[i]) == HAL_OK)
    {
      HAL_PCD_DataInStageCallback(hpcd, i);
    }
  }

  /* Stop transfers for all EP except EP0OUT k = USB_DWC3_NUM_OUT_EP */
  for (i = 0; i < USB_DWC3_NUM_OUT_EP; i++)
  {
    if (USB_EPStopXfer(hpcd->Instance, &hpcd->OUT_ep[i]) == HAL_OK)
    {
      HAL_PCD_DataOutStageCallback(hpcd, i);
    }
  }

  /* Disable the USB Interrupts */
  for (i = 0; i < USB_DWC3_INT_INUSE; i++)
  {
    __HAL_PCD_DISABLE_INTR(hpcd, i);
  }

  /* Disable Pullups */
  return USB_DevDisconnect(hpcd->Instance);
}

/**
  * @brief  Handle PCD interrupt request.
  * @param  hpcd PCD handle
  * @retval HAL status
  */
void HAL_PCD_IRQHandler(PCD_HandleTypeDef *hpcd)
{
  uint32_t evtcnt;
  uint32_t evt;
  uint8_t i;

  /* Use same handler for all the Evt-Buf IRQs */

  /* Check for all Event Buffer interrupt k = USB_DWC3_INT_INUSE */
  for (i = 0; i < USB_DWC3_INT_INUSE; i++)
  {
    evtcnt = USB_ReadInterruptCount(hpcd->Instance, i);

    for (evt = 0; evt < evtcnt; evt += USB_DWC3_EVENT_SIZE)
    {
      if (USB_IsEndpointEvent(__HAL_PCD_READ_EVENT(hpcd, i)))   /* EP event */
      {
        PCD_Handle_EP_Event(hpcd, __HAL_PCD_READ_EVENT(hpcd, i));
      }
      else      /* NON-EP event */
      {
        if (USB_IsDeviceEvent(__HAL_PCD_READ_EVENT(hpcd, i)))   /* Device specific event */
        {
          PCD_Handle_DEV_Event(hpcd, __HAL_PCD_READ_EVENT(hpcd, i));
        }
        else
        {
          /* Error, non supported events */
        }
      }

      __HAL_PCD_INCR_EVENT_POS(hpcd, i, USB_DWC3_EVENT_SIZE);

      USB_AckEventCount(hpcd->Instance, i, USB_DWC3_EVENT_SIZE);
    }
  }
}

/**
  * @brief  Data OUT stage callback.
  * @param  hpcd PCD handle
  * @param  epnum endpoint number
  * @retval None
  */
__weak void HAL_PCD_DataOutStageCallback(PCD_HandleTypeDef *hpcd, uint8_t epnum)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hpcd);
  UNUSED(epnum);
  /* NOTE : This function Should not be modified, when the callback is needed,
            the HAL_PCD_DataOutStageCallback could be implemented in the user file
   */
}

/**
  * @brief  Data IN stage callback.
  * @param  hpcd PCD handle
  * @param  epnum endpoint number
  * @retval None
  */
__weak void HAL_PCD_DataInStageCallback(PCD_HandleTypeDef *hpcd, uint8_t epnum)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hpcd);
  UNUSED(epnum);
  /* NOTE : This function Should not be modified, when the callback is needed,
            the HAL_PCD_DataInStageCallback could be implemented in the user file
   */
}
/**
  * @brief  Setup stage callback.
  * @param  hpcd PCD handle
  * @retval None
  */
__weak void HAL_PCD_SetupStageCallback(PCD_HandleTypeDef *hpcd)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hpcd);

  /* NOTE : This function Should not be modified, when the callback is needed,
            the HAL_PCD_SetupStageCallback could be implemented in the user file
   */
}

/**
  * @brief  USB Start Of Frame callback.
  * @param  hpcd PCD handle
  * @retval None
  */
__weak void HAL_PCD_SOFCallback(PCD_HandleTypeDef *hpcd)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hpcd);

  /* NOTE : This function Should not be modified, when the callback is needed,
            the HAL_PCD_SOFCallback could be implemented in the user file
   */
}

/**
  * @brief  USB Reset callback.
  * @param  hpcd PCD handle
  * @retval None
  */
__weak void HAL_PCD_ResetCallback(PCD_HandleTypeDef *hpcd)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hpcd);

  /* NOTE : This function Should not be modified, when the callback is needed,
            the HAL_PCD_ResetCallback could be implemented in the user file
   */
}

/**
  * @brief  Suspend event callback.
  * @param  hpcd PCD handle
  * @retval None
  */
__weak void HAL_PCD_SuspendCallback(PCD_HandleTypeDef *hpcd)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hpcd);

  /* NOTE : This function Should not be modified, when the callback is needed,
            the HAL_PCD_SuspendCallback could be implemented in the user file
   */
}

/**
  * @brief  Resume event callback.
  * @param  hpcd PCD handle
  * @retval None
  */
__weak void HAL_PCD_ResumeCallback(PCD_HandleTypeDef *hpcd)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hpcd);

  /* NOTE : This function Should not be modified, when the callback is needed,
            the HAL_PCD_ResumeCallback could be implemented in the user file
   */
}

/**
  * @brief  Incomplete ISO OUT callback.
  * @param  hpcd PCD handle
  * @param  epnum endpoint number
  * @retval None
  */
__weak void HAL_PCD_ISOOUTIncompleteCallback(PCD_HandleTypeDef *hpcd, uint8_t epnum)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hpcd);
  UNUSED(epnum);
  /* NOTE : This function Should not be modified, when the callback is needed,
            the HAL_PCD_ISOOUTIncompleteCallback could be implemented in the user file
   */
}

/**
  * @brief  Incomplete ISO IN  callback.
  * @param  hpcd PCD handle
  * @param  epnum endpoint number
  * @retval None
  */
__weak void HAL_PCD_ISOINIncompleteCallback(PCD_HandleTypeDef *hpcd, uint8_t epnum)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hpcd);
  UNUSED(epnum);
  /* NOTE : This function Should not be modified, when the callback is needed,
            the HAL_PCD_ISOINIncompleteCallback could be implemented in the user file
   */
}

/**
  * @brief  Connection event callback.
  * @param  hpcd PCD handle
  * @retval None
  */
__weak void HAL_PCD_ConnectCallback(PCD_HandleTypeDef *hpcd)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hpcd);

  /* NOTE : This function Should not be modified, when the callback is needed,
            the HAL_PCD_ConnectCallback could be implemented in the user file
   */
}

/**
  * @brief  Disconnection event callback.
  * @param  hpcd PCD handle
  * @retval None
  */
__weak void HAL_PCD_DisconnectCallback(PCD_HandleTypeDef *hpcd)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hpcd);

  /* NOTE : This function Should not be modified, when the callback is needed,
            the HAL_PCD_DisconnectCallback could be implemented in the user file
   */
}

/**
  * @}
  */

/** @defgroup PCD_Exported_Functions_Group3 Peripheral Control functions
  *  @brief   management functions
  *
@verbatim
 ===============================================================================
                      ##### Peripheral Control functions #####
 ===============================================================================
    [..]
    This subsection provides a set of functions allowing to control the PCD data
    transfers.

@endverbatim
  * @{
  */

/**
  * @brief  Set the USB Device address.
  * @param  hpcd PCD handle
  * @param  address new device address
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_PCD_SetAddress(PCD_HandleTypeDef *hpcd, uint8_t address)
{
  return USB_SetDevAddress(hpcd->Instance, address);
}

/**
  * @brief  Set the USB Device address.
  * @param  hpcd PCD handle
  * @param  test_mode USB Device Test Mode
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_PCD_SetTestMode(PCD_HandleTypeDef *hpcd, uint8_t test_mode)
{
  return USB_SetTestMode(hpcd->Instance, test_mode);
}

/**
  * @brief  Open and configure an endpoint.
  * @param  hpcd PCD handle
  * @param  ep_addr endpoint address
  * @param  ep_mps endpoint max packet size
  * @param  ep_type endpoint type
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_PCD_EP_Open(PCD_HandleTypeDef *hpcd, uint8_t ep_addr, uint16_t ep_mps, uint8_t ep_type)
{
  USB_DWC3_EPTypeDef *ep;

  if ((ep_addr & 0x80U) == 0x80U)
  {
    ep = &hpcd->IN_ep[ep_addr & 0x7FU];
  }
  else
  {
    ep = &hpcd->OUT_ep[ep_addr & 0x7FU];
  }

  ep->num = ep_addr & 0x7FU;

  if (ep->num == 0U) /*Do not let the USB-MW control EP0 & EP1*/
  {
    return HAL_ERROR;
  }

  ep->is_in = ((ep_addr & 0x80U) == 0x80U);
  ep->maxpacket = ep_mps;
  ep->type = ep_type;

  ep->trb_dma_addr = (uint32_t)PCD_GetDmaAddr((void *)ep->trb, sizeof(ep->trb), 1);
  if (ep->trb_dma_addr == 0U)
  {
    return HAL_ERROR;
  }

  ep->trb_addr = (USB_DWC3_Trb *)PCD_MapCoherentAddr((void *)ep->trb, sizeof(ep->trb));
  if (ep->trb_addr == 0U)
  {
    return HAL_ERROR;
  }

  /* Set to 0, to ignore for FS (bInterval_m1 should be 0) and also non-periodic EP */
  ep->bInterval = 0;

  if (USB_IsEndpointEnabled(hpcd->Instance, ep->phy_epnum))
  {
    return HAL_ERROR;
  }

  return USB_ActivateEndpoint(hpcd->Instance, ep);
}

/**
  * @brief  Open and configure an endpoint.
  * @param  hpcd PCD handle
  * @param  ep_addr endpoint address
  * @param  ep_mps endpoint max packet size
  * @param  ep_type endpoint type
  * @param  ep_bInterval  endpoint open interval
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_PCD_EP_Open_Periodic(PCD_HandleTypeDef *hpcd, uint8_t ep_addr, uint16_t ep_mps, uint8_t ep_type,
                                           uint8_t ep_bInterval)
{
  USB_DWC3_EPTypeDef *ep;
  HAL_StatusTypeDef ret;

  if ((ep_addr & 0x80U) == 0x80U)
  {
    ep = &hpcd->IN_ep[ep_addr & 0x7FU];
  }
  else
  {
    ep = &hpcd->OUT_ep[ep_addr & 0x7FU];
  }

  ep->num = ep_addr & 0x7FU;

  if (ep->num == 0U) /*Do not let the USB-MW control EP0 & EP1*/
  {
    return HAL_ERROR;
  }

  ep->is_in = ((ep_addr & 0x80U) == 0x80U);
  ep->maxpacket = ep_mps;
  ep->type = ep_type;

  ep->trb_dma_addr = (uint32_t)PCD_GetDmaAddr((void *)ep->trb, sizeof(ep->trb), 1);
  if (ep->trb_dma_addr == 0U)
  {
    return HAL_ERROR;
  }

  ep->trb_addr = (USB_DWC3_Trb *)PCD_MapCoherentAddr((void *)ep->trb, sizeof(ep->trb));
  if (ep->trb_addr == 0)
  {
    return HAL_ERROR;
  }

  ep->bInterval = ep_bInterval;

  if (USB_IsEndpointEnabled(hpcd->Instance, ep->phy_epnum))
  {
    return HAL_ERROR;
  }

  ret = USB_ActivateEndpoint(hpcd->Instance, ep);

  return ret;
}

/**
  * @brief  Deactivate an endpoint.
  * @param  hpcd PCD handle
  * @param  ep_addr endpoint address
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_PCD_EP_Close(PCD_HandleTypeDef *hpcd, uint8_t ep_addr)
{
  USB_DWC3_EPTypeDef *ep;
  HAL_StatusTypeDef ret;
  bool stopped = false;

  if ((ep_addr & 0x80U) == 0x80U)
  {
    ep = &hpcd->IN_ep[ep_addr & 0x7FU];
  }
  else
  {
    ep = &hpcd->OUT_ep[ep_addr & 0x7FU];
  }

  if (!USB_IsEndpointEnabled(hpcd->Instance, ep->phy_epnum))
  {
    return HAL_ERROR;
  }

  /* Stop Transfer on this EP */
  if (USB_EPStopXfer(hpcd->Instance, ep) == HAL_OK)
  {
    stopped = true;
  }

  ret = USB_DeactivateEndpoint(hpcd->Instance, ep);

  if (stopped)
  {
    if (ep->is_in)
    {
      HAL_PCD_DataInStageCallback(hpcd, ep_addr);
    }
    else
    {
      HAL_PCD_DataOutStageCallback(hpcd, ep_addr);
    }
  }

  PCD_UnMapCoherentAddr(ep->trb_addr);

  PCD_PutDmaAddr(ep->trb_dma_addr, sizeof(ep->trb), 1);

  return ret;
}

/**
  * @brief  Receive an amount of data.
  * @param  hpcd PCD handle
  * @param  ep_addr endpoint address
  * @param  pBuf pointer to the reception buffer
  * @param  len amount of data to be received
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_PCD_EP_Receive(PCD_HandleTypeDef *hpcd, uint8_t ep_addr, uint8_t *pBuf, uint32_t len)
{
  USB_DWC3_EPTypeDef *ep;

  ep = &hpcd->OUT_ep[ep_addr & 0x7FU];

  if (!USB_IsEndpointEnabled(hpcd->Instance, ep->phy_epnum))
  {
    return HAL_ERROR;
  }

  if ((len > ep->maxpacket) && !IS_MULTIPLE(len, ep->maxpacket))
  {
    PCD_DBGLOG("WARNING:PacketSize>Max_packet but non-multiple,buffer should be of at least Max_packetsize multiple\n");
  }

  /*setup and start the Xfer */
  if ((len != 0U) && (len < ep->maxpacket))
  {
    ep->xfer_buff = ep->bounce_buf;
    ep->xfer_len = ep->maxpacket;
    ep->xfer_dest_buff = pBuf;
    ep->xfer_dest_len = len;
  }
  else
  {
    ep->xfer_buff = pBuf;
    ep->xfer_len = ALIGN_MULTIPLE(len, ep->maxpacket);
  }

  ep->xfer_count = 0;
  ep->is_in = false;
  ep->num = ep_addr & 0x7FU;

  ep->dma_addr = ((ep->xfer_buff != 0) ? PCD_MapDmaAddr(ep->xfer_buff, ep->xfer_len, 0) : 0x0U);

  if ((ep_addr & 0x7FU) == 0U)
  {
    /* For Status ZLP packet */
    if (len == 0U)
    {
      /* 2-stage/3-stage control transfer */
      if (__HAL_PCD_SETUP_REQ_LEN(hpcd->Setup_addr) == 0U)
      {
        ep->trb_flag = USB_DWC3_TRBCTL_CONTROL_STATUS2;
      }
      else
      {
        ep->trb_flag = USB_DWC3_TRBCTL_CONTROL_STATUS3;
      }
    }
    else
    {
      ep->trb_flag = USB_DWC3_TRBCTL_CONTROL_DATA;
    }
  }
  else
  {
    if ((ep->type == EP_TYPE_INTR) || (ep->type == EP_TYPE_BULK))
    {
      ep->trb_flag = USB_DWC3_TRBCTL_NORMAL;
    }
    else
    {
      ep->trb_flag = USB_DWC3_TRBCTL_ISOCHRONOUS_FIRST;
    }
  }

  return USB_EPStartXfer(hpcd->Instance, ep);
}

/**
  * @brief  Get Received Data Size.
  * @param  hpcd PCD handle
  * @param  ep_addr endpoint address
  * @retval Data Size
  */
uint16_t HAL_PCD_EP_GetRxCount(const PCD_HandleTypeDef *hpcd, uint8_t ep_addr)
{
  return (uint16_t)hpcd->OUT_ep[ep_addr & 0xFU].xfer_count;
}

/**
  * @brief  Send an amount of data.
  * @param  hpcd PCD handle
  * @param  ep_addr endpoint address
  * @param  pBuf pointer to the transmission buffer
  * @param  len amount of data to be sent
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_PCD_EP_Transmit(PCD_HandleTypeDef *hpcd, uint8_t ep_addr, uint8_t *pBuf, uint32_t len)
{
  USB_DWC3_EPTypeDef *ep;

  ep = &hpcd->IN_ep[ep_addr & 0x7FU];

  if (!USB_IsEndpointEnabled(hpcd->Instance, ep->phy_epnum))
  {
    return HAL_ERROR;
  }

  /*setup and start the Xfer */
  ep->xfer_buff = pBuf;
  ep->xfer_len = len;
  ep->xfer_count = 0;
  ep->is_in = true;
  ep->num = ep_addr & 0x7FU;

  ep->dma_addr = ((ep->xfer_buff != 0) ? PCD_MapDmaAddr(ep->xfer_buff, ep->xfer_len, 1) : 0x0U);

  if ((ep_addr & 0x7FU) == 0U)
  {
    /* For Status ZLP packet */
    if (len == 0U)
    {
      /* 2-stage/3-stage control transfer */
      if (__HAL_PCD_SETUP_REQ_LEN(hpcd->Setup_addr) == 0U)
      {
        ep->trb_flag = USB_DWC3_TRBCTL_CONTROL_STATUS2;
      }
      else
      {
        ep->trb_flag = USB_DWC3_TRBCTL_CONTROL_STATUS3;
      }
    }
    else
    {
      ep->trb_flag = USB_DWC3_TRBCTL_CONTROL_DATA;
    }
  }
  else
  {
    if ((ep->type == EP_TYPE_INTR) || (ep->type == EP_TYPE_BULK))
    {
      ep->trb_flag = USB_DWC3_TRBCTL_NORMAL;
    }
    else
    {
      ep->trb_flag = USB_DWC3_TRBCTL_ISOCHRONOUS_FIRST;
    }
  }

  return USB_EPStartXfer(hpcd->Instance, ep);
}

/**
  * @brief  Set a STALL condition over an endpoint.
  * @param  hpcd PCD handle
  * @param  ep_addr endpoint address
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_PCD_EP_SetStall(PCD_HandleTypeDef *hpcd, uint8_t ep_addr)
{
  USB_DWC3_EPTypeDef *ep;
  HAL_StatusTypeDef ret;

  if ((0x80U & ep_addr) == 0x80U)
  {
    ep = &hpcd->IN_ep[ep_addr & 0x7FU];
  }
  else
  {
    ep = &hpcd->OUT_ep[ep_addr];
  }

  /* For control endpoints, the application issues only the Set Stall command, and only on the
  OUT direction of the control endpoint. The controller automatically clears the STALL when it
  receives a SETUP token for the endpoint. The application must not issue the Clear Stall command
  on a control endpoint*/
  if (ep_addr == 0x80U)
  {
    return HAL_OK;
  }

  if (ep->is_stall)
  {
    return HAL_OK;
  }

  ep->is_stall = true;
  ep->num   = ep_addr & 0x7FU;
  ep->is_in = ((ep_addr & 0x80U) == 0x80U);

  ret = USB_EPSetStall(hpcd->Instance, ep);
  if (ret != HAL_OK)
  {
    return ret;
  }

  if ((ep_addr & 0x7FU) == 0U)
  {
    hpcd->EP0_State = HAL_PCD_EP0_SETUP_QUEUED;
    ret = USB_EP0_OutStart(hpcd->Instance, &hpcd->OUT_ep[0], hpcd->Setup_dma_addr);
  }

  return ret;
}

/**
  * @brief  Clear a STALL condition over in an endpoint.
  * @param  hpcd PCD handle
  * @param  ep_addr endpoint address
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_PCD_EP_ClrStall(PCD_HandleTypeDef *hpcd, uint8_t ep_addr)
{
  USB_DWC3_EPTypeDef *ep;

  if ((0x80U & ep_addr) == 0x80U)
  {
    ep = &hpcd->IN_ep[ep_addr & 0x7FU];
  }
  else
  {
    ep = &hpcd->OUT_ep[ep_addr];
  }

  if (!(ep->is_stall))
  {
    return HAL_OK;
  }

  ep->is_stall = false;
  ep->num   = ep_addr & 0x7FU;
  ep->is_in = ((ep_addr & 0x80U) == 0x80U);

  return USB_EPClearStall(hpcd->Instance, ep);
}

/**
  * @brief  Flush an endpoint.
  * @param  hpcd PCD handle
  * @param  ep_addr endpoint address
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_PCD_EP_Flush(const PCD_HandleTypeDef *hpcd, uint8_t ep_addr)
{
  /* To be Replaced by dummy function, since dma (descriptor) use is non-avoidable.
  There is no method to flush TxFifo/RxFifo */

  UNUSED(hpcd);
  UNUSED(ep_addr);
  return HAL_OK;
}

/**
  * @brief  Activate remote wakeup signalling.
  * @param  hpcd PCD handle
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_PCD_ActivateRemoteWakeup(PCD_HandleTypeDef *hpcd)
{
  return USB_ActivateRemoteWakeup(hpcd->Instance);
}

/**
  * @brief  De-activate remote wakeup signalling.
  * @param  hpcd PCD handle
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_PCD_DeActivateRemoteWakeup(PCD_HandleTypeDef *hpcd)
{
  /* Nothing to be done since HAL_PCD_ActivateRemoteWakeup handles both activation and deactivation */

  return HAL_PCD_ActivateRemoteWakeup(hpcd);
}

/**
  * @}
  */

/** @defgroup PCD_Exported_Functions_Group4 Peripheral State functions
  *  @brief   Peripheral State functions
  *
@verbatim
 ===============================================================================
                      ##### Peripheral State functions #####
 ===============================================================================
    [..]
    This subsection permits to get in run-time the status of the peripheral
    and the data flow.

@endverbatim
  * @{
  */

/**
  * @brief  Return the PCD handle state.
  * @param  hpcd PCD handle
  * @retval HAL state
  */
PCD_StateTypeDef HAL_PCD_GetState(const PCD_HandleTypeDef *hpcd)
{
  return hpcd->State;
}

/**
  * @}
  */

/**
  * @}
  */
#endif /* HAL_PCD_MODULE_ENABLED */
/**
  * @}
  */

/**
  * @}
  */

