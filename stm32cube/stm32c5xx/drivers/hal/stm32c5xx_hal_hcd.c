/**
  ******************************************************************************
  * @file    stm32c5xx_hal_hcd.c
  * @brief   HCD HAL module driver.
  *          This file provides firmware functions to manage the following
  *          features of the USB Peripheral Controller:
  *           + Initialization and deinitialization functions
  *           + I/O operation functions
  *           + Peripheral Control functions
  *           + Peripheral State functions
  *
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

/* Includes ------------------------------------------------------------------*/
#include "stm32_hal.h"

/** @addtogroup STM32C5xx_HAL_Driver
  * @{
  */
#if defined (USB_DRD_FS)
#if defined (USE_HAL_HCD_MODULE) && (USE_HAL_HCD_MODULE == 1)

/** @addtogroup HCD
  * @brief Host Controller Driver, including the functions that allow the USB to be used in host mode.
  * @{
  */
/** @defgroup HCD_Introduction Introduction
  * @{

  USB Host Controller Driver (HCD) hardware abstraction layer provides all required APIs to interface with the
  USB peripheral in host mode. It simplifies the initialization, configuration, and management of the USB depending
  on the user's required host function.

  This abstraction layer ensures portability and ease of use across different STM32 series.
  The HCD HAL abstracts different USB hardware instances that can be present (depending on the STM32 MCU):
  * USB OTG FS (On-The-GO Full Speed)
  * USB OTG HS (On-The-GO High Speed)
  * USB DRD FS (Dual Role Device Full Speed)

  */
/**
  * @}
  */

/** @defgroup HCD_How_To_Use How To Use
  * @{
  # How to use the HAL USB HCD module driver

  ## Use the USB Host Controller Driver (HCD) HAL driver as follows:

  1. Declare a hal_hcd_handle_t handle structure, for example:
      hal_hcd_handle_t gh_hcd_usb_drd_fs;

  2. Initialize the USB HCD low-level resources:
    - USB HCD interface clock configuration:
      - Enable USB peripheral clock.

    - USB HCD interface Power configuration:
      - Enable USB peripheral VddUSB power supply if applicable.

    - USB host pins configuration:
      USB data pins are automatically configured by the hardware during USB peripheral initialization;
      no additional user action is required.

    - NVIC configuration for interrupt handling with HAL_HCD_IRQHandler():
      - Set the USB HCD interrupt priority.
      - Enable the USB IRQ channel in the NVIC.

  3. Initialize the USB HCD driver with HAL_HCD_Init() by selecting an instance, for example:

     - HAL_HCD_Init(&gh_hcd_usb_drd_fs, HAL_HCD_DRD_FS);

  - Declare a hal_hcd_config_t structure, for example:
     - hal_hcd_config_t config_hcd_usb_drd_fs;

  - In the configuration structure,
    program the PHY interface, core speed, and other parameters as required.

  - Apply the configuration with:
     - HAL_HCD_SetConfig(&gh_hcd_usb_drd_fs, &config_hcd_usb_drd_fs);

  ## USB HCD callback definitions:
  By default, all callbacks are initialized to their corresponding default weak functions.
  When the compilation define USE_HAL_HCD_REGISTER_CALLBACKS is set to 1U, configure the
  driver callbacks dynamically using the callback registration functions:

  | Default callback weak function                   | Callback registration function
  |--------------------------------------------------|------------------------------------------------------------------
  | HAL_HCD_SofCallback()                            | HAL_HCD_RegisterSofCallback()
  | HAL_HCD_PortConnectCallback()                    | HAL_HCD_RegisterPortConnectCallback()
  | HAL_HCD_PortDisconnectCallback()                 | HAL_HCD_RegisterPortDisconnectCallback()
  | HAL_HCD_PortEnabledCallback()                    | HAL_HCD_RegisterPortEnabledCallback()
  | HAL_HCD_PortDisabledCallback()                   | HAL_HCD_RegisterPortDisabledCallback()
  | HAL_HCD_PortSuspendCallback()                    | HAL_HCD_RegisterPortSuspendCallback()
  | HAL_HCD_PortResumeCallback()                     | HAL_HCD_RegisterPortResumeCallback()
  | HAL_HCD_ChannelNotifyURBChangeCallback()         | HAL_HCD_RegisterChannelNotifyURBChangeCallback()
  | HAL_HCD_ErrorCallback()                          | HAL_HCD_RegisterErrorCallback()
  */

/**
  * @}
  */

/** @defgroup HCD_Configuration_Table Configuration Table
  * @{
  ## Configuration inside the USB HCD driver:

  | Config defines                 | Description     | Default value | Note
  |--------------------------------|-----------------|---------------|--------------------------------------------------
  | USE_ASSERT_DBG_PARAM           | from IDE        |       NA      | Enable the parameter assert.
  | USE_ASSERT_DBG_STATE           | from IDE        |       NA      | Enable the state assert.
  | USE_HAL_HCD_MODULE             | from hal_conf.h |        1      | Enable the HAL USB HCD module.
  | USE_HAL_HCD_REGISTER_CALLBACKS | from hal_conf.h |        0      | Enable the register callbacks.
  | USE_HAL_HCD_MAX_CHANNEL_NB     | from hal_conf.h |       16      | Maximum number of USB HCD channels.
  | USE_HAL_HCD_USB_EP_TYPE_ISOC   | from hal_conf.h |        1      | Enable support for isochronous endpoints.
  | USE_HAL_HCD_USB_DOUBLE_BUFFER  | from hal_conf.h |        1      | Enable double-buffering for USB transfers.
  | USE_HAL_HCD_USER_DATA          | from hal_conf.h |        0      | Add user data to the HAL USB HCD handle.
  | USE_HAL_HCD_GET_LAST_ERRORS    | from hal_conf.h |        0      | Add an error value to the HAL USB HCD handle.
  | USE_HAL_CHECK_PARAM            | from hal_conf.h |        0      | Enable checking of HCD API parameters at runtime.
  */

/**
  * @}
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/** @defgroup HCD_Private_Macros Private Macros
  * @{
  */
/*! Macro to check ep_type */
#define HAL_HCD_CHECK_EP_TYPE(ep_type) ((((ep_type) == HAL_HCD_EP_TYPE_CTRL) \
                                         || ((ep_type) == HAL_HCD_EP_TYPE_BULK) \
                                         || ((ep_type) == HAL_HCD_EP_TYPE_INTR) \
                                         || ((ep_type) == HAL_HCD_EP_TYPE_ISOC)) ? 1U : 0U)

/**
  * @}
  */

/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/** @defgroup HCD_Private_Functions Private Functions
  * @{
  */

static void HCD_DRD_CHANNEL_IN_IRQHandler(hal_hcd_handle_t *hhcd, usb_core_phy_chep_t phy_ch_num);
static void HCD_DRD_CHANNEL_OUT_IRQHandler(hal_hcd_handle_t *hhcd, usb_core_phy_chep_t phy_ch_num);
static void HCD_DRD_Port_IRQHandler(hal_hcd_handle_t *hhcd);

#if defined (USE_HAL_HCD_USB_DOUBLE_BUFFER) && (USE_HAL_HCD_USB_DOUBLE_BUFFER == 1)
static void HCD_DRD_CHANNEL_IN_BulkDb(hal_hcd_handle_t *hhcd, usb_core_channel_t ch_num,
                                      usb_core_phy_chep_t phy_ch_num, uint32_t reg_value);

static void HCD_DRD_CHANNEL_OUT_BulkDb(hal_hcd_handle_t *hhcd, usb_core_channel_t ch_num,
                                       usb_core_phy_chep_t phy_ch_num, uint32_t reg_value);

#endif /* defined (USE_HAL_HCD_USB_DOUBLE_BUFFER) && (USE_HAL_HCD_USB_DOUBLE_BUFFER == 1) */
#if defined (USE_HAL_HCD_USB_EP_TYPE_ISOC) && (USE_HAL_HCD_USB_EP_TYPE_ISOC == 1)
static void HCD_DRD_CHANNEL_IN_IsocDb(hal_hcd_handle_t *hhcd, usb_core_channel_t ch_num,
                                      usb_core_phy_chep_t phy_ch_num, uint32_t reg_value);
#endif /* defined (USE_HAL_HCD_USB_EP_TYPE_ISOC) && (USE_HAL_HCD_USB_EP_TYPE_ISOC == 1) */

/**
  * @}
  */

/* Exported functions --------------------------------------------------------*/
/** @addtogroup HCD_Exported_Functions Exported Functions
  * @{
  */

/** @addtogroup HCD_Exported_Functions_Group1 Initialization and deinitialization functions
  *
  * @{
  This subsection provides a set of functions allowing to initialize and deinitialize the HCD.
  - Call the function HAL_HCD_Init() to initialize the selected HCD handle and associate an instance.
  - Call the function HAL_HCD_DeInit() to de-initialize the given HAL HCD instance by resetting the state machine.
  */

/**
  * @brief  Initialize the host driver.
  * @param  hhcd HCD handle
  * @param  instance HCD instance
  * @retval HAL status
  */
hal_status_t HAL_HCD_Init(hal_hcd_handle_t *hhcd, hal_hcd_t instance)
{
  /* Check hhcd handler */
  ASSERT_DBG_PARAM((hhcd != NULL));

  /* Check USB instance */
  ASSERT_DBG_PARAM(IS_HCD_ALL_INSTANCE((usb_drd_global_t *)((uint32_t)instance)));

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1U)
  if (hhcd == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  hhcd->instance = instance;

  switch (instance)
  {

#if defined (USB_DRD_FS)
    case HAL_HCD_DRD_FS:

      /* Register USB core instance operational functions */
      (void)USB_DRD_HCD_InitDriver(&hhcd->driver);

      hhcd->p_irq_handler = HAL_HCD_DRD_IRQHandler;

      /* Get the host channels number */
      hhcd->host_channels_nbr = (uint8_t)(USB_DRD_FS_CH_NBR);
      break;
#endif /* defined (USB_DRD_FS) */

    default:
      return HAL_ERROR;
      break;
  }

#if defined (USE_HAL_HCD_GET_LAST_ERRORS) && (USE_HAL_HCD_GET_LAST_ERRORS == 1)
  hhcd->last_error_codes = HAL_HCD_ERROR_NONE;
#endif /* USE_HAL_HCD_GET_LAST_ERRORS */

#if defined (USE_HAL_HCD_REGISTER_CALLBACKS) && (USE_HAL_HCD_REGISTER_CALLBACKS == 1U)
  hhcd->p_sof_cb = HAL_HCD_SofCallback;
  hhcd->p_port_connect_cb = HAL_HCD_PortConnectCallback;
  hhcd->p_port_disconnect_cb = HAL_HCD_PortDisconnectCallback;
  hhcd->p_port_enable_cb = HAL_HCD_PortEnabledCallback;
  hhcd->p_port_disable_cb = HAL_HCD_PortDisabledCallback;
  hhcd->p_port_suspend_cb = HAL_HCD_PortSuspendCallback;
  hhcd->p_port_resume_cb = HAL_HCD_PortResumeCallback;
  hhcd->p_ch_notify_urb_change_cb = HAL_HCD_ChannelNotifyURBChangeCallback;
  hhcd->p_error_cb = HAL_HCD_ErrorCallback;
#endif /* (USE_HAL_HCD_REGISTER_CALLBACKS) */

#if defined (USE_HAL_HCD_USER_DATA) && (USE_HAL_HCD_USER_DATA == 1U)
  hhcd->p_user_data = (void *)NULL;
#endif /* USE_HAL_HCD_USER_DATA */

  hhcd->global_state = HAL_HCD_STATE_INIT;

  return HAL_OK;
}

/**
  * @brief  DeInitialize the host driver.
  * @param  hhcd HCD handle
  */
void HAL_HCD_DeInit(hal_hcd_handle_t *hhcd)
{
  /* Check hhcd handler */
  ASSERT_DBG_PARAM((hhcd != NULL));

  /* Check USB instance */
  ASSERT_DBG_PARAM(IS_HCD_ALL_INSTANCE((usb_drd_global_t *)((uint32_t)hhcd->instance)));

  hhcd->driver.core_deinit((uint32_t)hhcd->instance);

  /* Update Host Port State */
  hhcd->port_state = HAL_HCD_PORT_STATE_DEV_DISCONNECT;

  /* Disable global interrupt */
  (void)hhcd->driver.core_disable_interrupts((uint32_t)hhcd->instance);

#if defined (USE_HAL_HCD_USER_DATA) && (USE_HAL_HCD_USER_DATA == 1U)
  /* Reset the user data pointer to NULL */
  hhcd->p_user_data = (void *) NULL;
#endif /* USE_HAL_HCD_USER_DATA */

#if defined (USE_HAL_HCD_GET_LAST_ERRORS) && (USE_HAL_HCD_GET_LAST_ERRORS == 1)
  hhcd->last_error_codes = HAL_HCD_ERROR_NONE;
#endif /* USE_HAL_HCD_GET_LAST_ERRORS */

  hhcd->global_state = HAL_HCD_STATE_RESET;
}
/**
  * @}
  */

/** @addtogroup HCD_Exported_Functions_Group2 Global Configuration functions
  * @{
  This subsection provides functions allowing to configure the USB in Host mode:
  - Call HAL_HCD_SetConfig() to configure the initialized instance with a set of parameters containing:
     * phy_interface
     * channels_nbr
     * core_speed
     * bulk_db_state
     * iso_db_state
  */

/**
  * @brief  Configure the HCD according to the specified
  *         parameters in the hal_hcd_handle_t and initialize the associated handle.
  * @param  hhcd HCD handle
  * @param  p_config pointer to the peripheral configuration structure
  * @retval HAL status
  */
hal_status_t HAL_HCD_SetConfig(hal_hcd_handle_t *hhcd, const hal_hcd_config_t *p_config)
{
  hal_status_t ret = HAL_OK;
  usb_core_config_params_t usb_core_config = {0U};

  /* Check hhcd handler and configuration parameter */
  ASSERT_DBG_PARAM((hhcd != NULL));
  ASSERT_DBG_PARAM((p_config != NULL));

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1U)
  if ((hhcd == NULL) || (p_config == NULL))
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  /* Check the global state */
  ASSERT_DBG_STATE(hhcd->global_state, HAL_HCD_STATE_INIT);

  switch (hhcd->instance)
  {
#if defined (USB_DRD_FS)
    case HAL_HCD_DRD_FS:

      usb_core_config.phy_interface = (usb_core_phy_module_t)p_config->phy_interface;
      usb_core_config.channels_nbr = hhcd->host_channels_nbr;
      usb_core_config.core_speed = (usb_core_speed_t)p_config->hcd_speed;
      usb_core_config.bulk_db_state = (usb_core_config_status_t)p_config->bulk_doublebuffer_enable;
#if defined (USE_HAL_HCD_USB_EP_TYPE_ISOC) && (USE_HAL_HCD_USB_EP_TYPE_ISOC == 1)
      usb_core_config.iso_db_state = (usb_core_config_status_t)p_config->iso_doublebuffer_enable;
#endif /* defined (USE_HAL_HCD_USB_EP_TYPE_ISOC) && (USE_HAL_HCD_USB_EP_TYPE_ISOC == 1) */
      break;
#endif /* defined (USB_DRD_FS) */

    default:
      return HAL_ERROR;
      break;
  }

  /* Disable the Interrupts */
  (void)hhcd->driver.core_disable_interrupts((uint32_t)hhcd->instance);

  /* Init the Core (common init.) */
  if (hhcd->driver.core_init((uint32_t)hhcd->instance, &usb_core_config) != USB_CORE_OK)
  {
    hhcd->global_state = HAL_HCD_STATE_FAULT;
    return HAL_ERROR;
  }

  /* Force Host Mode */
  if (hhcd->driver.core_set_mode((uint32_t)hhcd->instance, USB_CORE_HOST_MODE) != USB_CORE_OK)
  {
    hhcd->global_state = HAL_HCD_STATE_FAULT;
    ret = HAL_ERROR;
  }

  /* Init Host */
  if (hhcd->driver.host_init((uint32_t)hhcd->instance, &usb_core_config) != USB_CORE_OK)
  {
    hhcd->global_state = HAL_HCD_STATE_FAULT;
    ret = HAL_ERROR;
  }

  /* Host Port State */
  hhcd->port_state = HAL_HCD_PORT_STATE_DEV_DISCONNECT;

  if (ret != HAL_ERROR)
  {
    /* Set HCD Global state to IDLE */
    hhcd->global_state = HAL_HCD_STATE_IDLE;
  }

  return ret;
}

/**
  * @}
  */

/** @addtogroup HCD_Exported_Functions_Group3 User Data functions
  * @{
  */
#if defined (USE_HAL_HCD_GET_LAST_ERRORS) && (USE_HAL_HCD_GET_LAST_ERRORS == 1)
/**
  * @brief Get Last Error codes.
  * @param hhcd Pointer to a hal_hcd_handle_t
  * @retval last error code.
  */
uint32_t HAL_HCD_GetLastErrorCodes(const hal_hcd_handle_t *hhcd)
{
  /* Check hhcd handler */
  ASSERT_DBG_PARAM((hhcd != NULL));

  return (hhcd->last_error_codes);
}
#endif /* USE_HAL_HCD_GET_LAST_ERRORS */

#if defined (USE_HAL_HCD_USER_DATA) && (USE_HAL_HCD_USER_DATA == 1)

/**
  * @brief Set the user data pointer into the handle.
  * @param hhcd Pointer to a hal_hcd_handle_t
  * @param p_user_data Pointer to the user data.
  */
void HAL_HCD_SetUserData(hal_hcd_handle_t *hhcd, const void *p_user_data)
{
  /* Check hhcd handler */
  ASSERT_DBG_PARAM((hhcd != NULL));

  hhcd->p_user_data = p_user_data;
  return;
}

/**
  * @brief Get the user data pointer from the handle.
  * @param hhcd Pointer to a hal_hcd_handle_t
  * @retval Pointer to the user data.
  */
const void *HAL_HCD_GetUserData(const hal_hcd_handle_t *hhcd)
{
  /* Check hhcd handler */
  ASSERT_DBG_PARAM((hhcd != NULL));

  return (hhcd->p_user_data);
}

#endif /* USE_HAL_HCD_USER_DATA */
/**
  * @}
  */

/** @defgroup HCD_Exported_Functions_Group4 Peripheral Control functions
  * @{
  */
/**
  * @brief  Start the host driver.
  * @param  hhcd HCD handle
  * @retval HAL status
  */
hal_status_t HAL_HCD_Start(hal_hcd_handle_t *hhcd)
{
  /* Check hhcd handler */
  ASSERT_DBG_PARAM((hhcd != NULL));

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1U)
  if (hhcd == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  /* Check the global state */
  ASSERT_DBG_STATE(hhcd->global_state, HAL_HCD_STATE_IDLE);

  /* start host */
  (void)hhcd->driver.host_start((uint32_t)hhcd->instance);

  hhcd->global_state = HAL_HCD_STATE_ACTIVE;

  return HAL_OK;
}

/**
  * @brief  Stop the host driver.
  * @param  hhcd HCD handle
  * @retval HAL status
  */
hal_status_t HAL_HCD_Stop(hal_hcd_handle_t *hhcd)
{
  /* Check hhcd handler */
  ASSERT_DBG_PARAM((hhcd != NULL));

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1U)
  if (hhcd == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  /* Check the global state */
  ASSERT_DBG_STATE(hhcd->global_state, HAL_HCD_STATE_ACTIVE);

  (void)hhcd->driver.host_stop((uint32_t)hhcd->instance);

  hhcd->global_state = HAL_HCD_STATE_IDLE;

  return HAL_OK;
}

/**
  * @brief  Reset the host port.
  * @param  hhcd HCD handle
  * @retval HAL status
  */
hal_status_t HAL_HCD_ResetPort(hal_hcd_handle_t *hhcd)
{
  uint32_t wait_start;

  /* Check hhcd handler */
  ASSERT_DBG_PARAM((hhcd != NULL));

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1U)
  if (hhcd == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  /* Reset the USB Port by inserting an SE0 on the bus */
  (void)hhcd->driver.host_port_reset((uint32_t)hhcd->instance, USB_CORE_PORT_RESET_STS_SET);

  /* Wait for USB reset duration */
  wait_start = HAL_GetTick();
  while ((HAL_GetTick() - wait_start) < 100U)
  {
    /* Busy-wait */
  }

  (void)hhcd->driver.host_port_reset((uint32_t)hhcd->instance, USB_CORE_PORT_RESET_STS_CLEAR);

  /* Wait for reset recovery time */
  wait_start = HAL_GetTick();
  while ((HAL_GetTick() - wait_start) < 30U)
  {
    /* Busy-wait */
  }

  if (hhcd->port_state == HAL_HCD_PORT_STATE_DEV_CONNECT)
  {
    hhcd->port_state = HAL_HCD_PORT_STATE_DEV_RESET;
  }

  return HAL_OK;
}

/**
  * @brief  Put the Device in suspend mode.
  * @param  hhcd HCD handle
  * @retval HAL status
  */
hal_status_t HAL_HCD_SuspendPort(hal_hcd_handle_t *hhcd)
{
  hal_status_t ret = HAL_OK;

  /* Check hhcd handler */
  ASSERT_DBG_PARAM((hhcd != NULL));

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1U)
  if (hhcd == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  if (hhcd->driver.host_port_suspend((uint32_t)hhcd->instance) != USB_CORE_OK)
  {
    ret = HAL_ERROR;
  }

  if (ret != HAL_ERROR)
  {
    hhcd->port_state = HAL_HCD_PORT_STATE_DEV_SUSPEND;
  }

  return ret;
}

/**
  * @brief  Resume the host port.
  * @param  hhcd HCD handle
  * @retval HAL status
  */
hal_status_t HAL_HCD_ResumePort(hal_hcd_handle_t *hhcd)
{
  uint32_t wait_start;

  /* Check hhcd handler */
  ASSERT_DBG_PARAM((hhcd != NULL));

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1U)
  if (hhcd == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  (void)hhcd->driver.host_port_resume((uint32_t)hhcd->instance, USB_CORE_PORT_RESUME_STS_SET);

  /* Wait for resume signaling duration */
  wait_start = HAL_GetTick();
  while ((HAL_GetTick() - wait_start) < 30U)
  {
    /* Busy-wait */
  }

  (void)hhcd->driver.host_port_resume((uint32_t)hhcd->instance, USB_CORE_PORT_RESUME_STS_CLEAR);

  hhcd->port_state = HAL_HCD_PORT_STATE_DEV_RESUME;

  return HAL_OK;
}

/**
  * @brief  Return the current Host frame number.
  * @param  hhcd HCD handle
  * @retval Current Host frame number
  */
uint32_t HAL_HCD_GetCurrentFrame(const hal_hcd_handle_t *hhcd)
{
  /* Check hhcd handler */
  ASSERT_DBG_PARAM((hhcd != NULL));

  return (hhcd->driver.host_get_current_frame((uint32_t)hhcd->instance));
}

/**
  * @brief  Return the Host enumeration speed.
  * @param  hhcd HCD handle
  * @retval Enumeration speed
  */
hal_hcd_port_speed_t HAL_HCD_GetPortSpeed(const hal_hcd_handle_t *hhcd)
{
  /* Check hhcd handler */
  ASSERT_DBG_PARAM((hhcd != NULL));

  return (hal_hcd_port_speed_t)hhcd->driver.host_get_port_speed((uint32_t)hhcd->instance);
}

/**
  * @brief  Return the HCD DMA status enabled or disabled.
  * @param  hhcd HCD handle
  * @retval state
  */
hal_hcd_dma_status_t HAL_HCD_IsEnabledDMA(const hal_hcd_handle_t *hhcd)
{
  /* Check hhcd handler */
  ASSERT_DBG_PARAM((hhcd != NULL));

  return (hal_hcd_dma_status_t)(hhcd->driver.core_get_dma_status((uint32_t)hhcd->instance));
}

/**
  * @brief  Return the last host transfer size.
  * @param  hhcd HCD handle
  * @param  ch_num Channel number.
  *         This parameter can be a value from 1 to 15
  * @retval last transfer size in byte
  */
uint32_t HAL_HCD_GetChannelTransferCount(const hal_hcd_handle_t *hhcd, hal_hcd_channel_t ch_num)
{
  /* Check hhcd handler */
  ASSERT_DBG_PARAM((hhcd != NULL));
  /* Check channel number */
  ASSERT_DBG_PARAM(((uint8_t)ch_num < USE_HAL_HCD_MAX_CHANNEL_NB));

  return hhcd->channel[ch_num].core_ch.xfer_count;
}

/**
  * @brief  Halt a host channel.
  * @param  hhcd HCD handle
  * @param  ch_num Channel number.
  *         This parameter can be a value from 1 to 15
  * @retval HAL status
  */
hal_status_t HAL_HCD_HaltChannel(const hal_hcd_handle_t *hhcd, hal_hcd_channel_t ch_num)
{
  hal_status_t status = HAL_OK;

  /* Check hhcd handler */
  ASSERT_DBG_PARAM((hhcd != NULL));

  /* Check channel number */
  ASSERT_DBG_PARAM(((uint8_t)ch_num < USE_HAL_HCD_MAX_CHANNEL_NB));

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1U)
  if ((hhcd == NULL) || ((uint8_t)ch_num >= USE_HAL_HCD_MAX_CHANNEL_NB))
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  hhcd->driver.host_channel_halt((uint32_t)hhcd->instance, &hhcd->channel[ch_num].core_ch);

  return status;
}

/**
  * @brief  Initialize a host channel.
  * @param  hhcd HCD handle
  * @param  ch_num Channel number.
  *         This parameter can be a value from 1 to 15
  * @param  p_channel_config channel config structure
  * @retval HAL status
  */
hal_status_t HAL_HCD_SetConfigChannel(hal_hcd_handle_t *hhcd, hal_hcd_channel_t ch_num,
                                      const hal_hcd_channel_config_t *p_channel_config)
{
  uint8_t ep_num;

  /* Check hhcd handler */
  ASSERT_DBG_PARAM((hhcd != NULL));
  /* Check channel config */
  ASSERT_DBG_PARAM((p_channel_config != NULL));
  /* Check channel number */
  ASSERT_DBG_PARAM(((uint8_t)ch_num < USE_HAL_HCD_MAX_CHANNEL_NB));
  /* Check EP Type */
  ASSERT_DBG_PARAM((HAL_HCD_CHECK_EP_TYPE(p_channel_config->ep_type) != 0U));

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1U)
  if ((hhcd == NULL) || (p_channel_config == NULL)
      || ((uint8_t)ch_num >= USE_HAL_HCD_MAX_CHANNEL_NB)
      || (HAL_HCD_CHECK_EP_TYPE(p_channel_config->ep_type) == 0U))
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  ep_num = p_channel_config->ep_address & 0xFU;

  hhcd->channel[ch_num].core_ch.do_ping = 0U;
  hhcd->channel[ch_num].core_ch.dev_addr = p_channel_config->device_address;
  hhcd->channel[ch_num].core_ch.ch_num = (usb_core_channel_t)ch_num;
  hhcd->channel[ch_num].core_ch.ep_type = (usb_core_ep_type_t)p_channel_config->ep_type;
  hhcd->channel[ch_num].core_ch.ep_num = (usb_core_endpoint_t)ep_num;

  (void)HAL_HCD_ClearChannelHubInfo(hhcd, ch_num);

  if ((p_channel_config->ep_address & USB_CORE_IN_EP_DIR_MSK) == USB_CORE_IN_EP_DIR_MSK)
  {
    hhcd->channel[ch_num].core_ch.ch_dir = USB_CORE_CH_IN_DIR;
  }
  else
  {
    hhcd->channel[ch_num].core_ch.ch_dir = USB_CORE_CH_OUT_DIR;
  }

  hhcd->channel[ch_num].core_ch.speed = (usb_core_device_speed_t)p_channel_config->device_speed;
  hhcd->channel[ch_num].core_ch.max_packet = p_channel_config->ep_mps;

  if (hhcd->driver.host_channel_init((uint32_t)hhcd->instance, &hhcd->channel[ch_num].core_ch) != USB_CORE_OK)
  {
    return HAL_ERROR;
  }

  return HAL_OK;
}

/**
  * @brief  Submit a new URB transfer request for processing.
  * @param  hhcd HCD handle
  * @param  ch_num Channel number.
  *         This parameter can be a value from 1 to 15
  * @param  p_channel_transfer_req Channel transfer request.
  * @retval HAL status
  */
hal_status_t HAL_HCD_RequestChannelTransfer(hal_hcd_handle_t *hhcd, hal_hcd_channel_t ch_num,
                                            const hal_hcd_channel_transfer_req_t *p_channel_transfer_req)
{
  hal_status_t ret = HAL_OK;

  /* Check hhcd handler */
  ASSERT_DBG_PARAM((hhcd != NULL));
  /* Check channel number */
  ASSERT_DBG_PARAM(((uint8_t)ch_num < USE_HAL_HCD_MAX_CHANNEL_NB));

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1U)
  if ((hhcd == NULL) || ((uint8_t)ch_num >= USE_HAL_HCD_MAX_CHANNEL_NB))
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  if (p_channel_transfer_req->token_type == 0U)
  {
    hhcd->channel[ch_num].core_ch.data_pid = USB_CORE_CH_PID_SETUP;
    hhcd->channel[ch_num].core_ch.do_ping = p_channel_transfer_req->do_ping;
  }
  else
  {
    hhcd->channel[ch_num].core_ch.data_pid = USB_CORE_CH_PID_DATA1;
  }

  /* Manage Data Toggle */
  switch (p_channel_transfer_req->ep_type)
  {
    case HAL_HCD_EP_TYPE_CTRL:
      if (p_channel_transfer_req->token_type == 1U) /* send data */
      {
        if (p_channel_transfer_req->ch_dir == HAL_HCD_CH_OUT_DIR)
        {
          if (p_channel_transfer_req->transfer_length == 0U)
          {
            /* For Status OUT stage, Length == 0U, Status Out PID = 1 */
            hhcd->channel[ch_num].toggle_out = 1U;
          }

          /* Set the Data Toggle bit as per the Flag */
          if (hhcd->channel[ch_num].toggle_out == 0U)
          {
            /* Put the PID 0 */
            hhcd->channel[ch_num].core_ch.data_pid = USB_CORE_CH_PID_DATA0;
          }
          else
          {
            /* Put the PID 1 */
            hhcd->channel[ch_num].core_ch.data_pid = USB_CORE_CH_PID_DATA1;
          }
        }
      }
      break;

    case HAL_HCD_EP_TYPE_BULK:
      if (p_channel_transfer_req->ch_dir == HAL_HCD_CH_OUT_DIR)
      {
        /* Set the Data Toggle bit as per the Flag */
        if (hhcd->channel[ch_num].toggle_out == 0U)
        {
          /* Put the PID 0 */
          hhcd->channel[ch_num].core_ch.data_pid = USB_CORE_CH_PID_DATA0;
        }
        else
        {
          /* Put the PID 1 */
          hhcd->channel[ch_num].core_ch.data_pid = USB_CORE_CH_PID_DATA1;
        }
      }
      else
      {
        if (hhcd->channel[ch_num].toggle_in == 0U)
        {
          hhcd->channel[ch_num].core_ch.data_pid = USB_CORE_CH_PID_DATA0;
        }
        else
        {
          hhcd->channel[ch_num].core_ch.data_pid = USB_CORE_CH_PID_DATA1;
        }
      }

      break;
    case HAL_HCD_EP_TYPE_INTR:
      if (p_channel_transfer_req->ch_dir == HAL_HCD_CH_OUT_DIR)
      {
        /* Set the Data Toggle bit as per the Flag */
        if (hhcd->channel[ch_num].toggle_out == 0U)
        {
          /* Put the PID 0 */
          hhcd->channel[ch_num].core_ch.data_pid = USB_CORE_CH_PID_DATA0;
        }
        else
        {
          /* Put the PID 1 */
          hhcd->channel[ch_num].core_ch.data_pid = USB_CORE_CH_PID_DATA1;
        }
      }
      else
      {
        if (hhcd->channel[ch_num].toggle_in == 0U)
        {
          hhcd->channel[ch_num].core_ch.data_pid = USB_CORE_CH_PID_DATA0;
        }
        else
        {
          hhcd->channel[ch_num].core_ch.data_pid = USB_CORE_CH_PID_DATA1;
        }
      }
      break;
#if defined (USE_HAL_HCD_USB_EP_TYPE_ISOC) && (USE_HAL_HCD_USB_EP_TYPE_ISOC == 1)
    case HAL_HCD_EP_TYPE_ISOC:
      hhcd->channel[ch_num].core_ch.data_pid = USB_CORE_CH_PID_DATA0;
      break;
#endif /* defined (USE_HAL_HCD_USB_EP_TYPE_ISOC) && (USE_HAL_HCD_USB_EP_TYPE_ISOC == 1) */
    default:
      return HAL_ERROR;
      break;
  }

  hhcd->channel[ch_num].urb_state = HAL_HCD_CHANNEL_URB_STATE_IDLE;
  hhcd->channel[ch_num].core_ch.p_xfer_buffer = p_channel_transfer_req->p_buffer;
  hhcd->channel[ch_num].core_ch.xfer_length = p_channel_transfer_req->transfer_length;
  hhcd->channel[ch_num].core_ch.xfer_size = p_channel_transfer_req->transfer_length;
  hhcd->channel[ch_num].core_ch.ch_dir = (usb_core_ch_direction_t)p_channel_transfer_req->ch_dir;
  hhcd->channel[ch_num].core_ch.ep_type = (usb_core_ep_type_t)p_channel_transfer_req->ep_type;
  hhcd->channel[ch_num].core_ch.xfer_count = 0U;
  hhcd->channel[ch_num].core_ch.ch_num = (usb_core_channel_t)ch_num;
  hhcd->channel[ch_num].state = HAL_HCD_CHANNEL_STATE_IDLE;

  (void)hhcd->driver.host_channel_start((uint32_t)hhcd->instance, &hhcd->channel[ch_num].core_ch);

  return ret;
}

/**
  * @brief  Set host channel hub information.
  * @param  hhcd HCD handle
  * @param  ch_num Channel number.
  *         This parameter can be a value from 1 to 8
  * @param  hub_addr Hub address
  * @param  port_nbr Hub port number
  * @retval HAL status
  */
hal_status_t HAL_HCD_SetChannelHubInfo(hal_hcd_handle_t *hhcd, hal_hcd_channel_t ch_num,
                                       uint8_t hub_addr, uint8_t port_nbr)
{
  /* Check hhcd handler */
  ASSERT_DBG_PARAM((hhcd != NULL));

  /* Check channel number */
  ASSERT_DBG_PARAM(((uint8_t)ch_num < USE_HAL_HCD_MAX_CHANNEL_NB));

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1U)
  if ((hhcd == NULL) || ((uint8_t)ch_num >= USE_HAL_HCD_MAX_CHANNEL_NB))
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */


  hhcd->channel[ch_num].core_ch.hub_addr = hub_addr;
  hhcd->channel[ch_num].core_ch.hub_port_nbr = port_nbr;

  return HAL_OK;
}

/**
  * @brief  Clear host channel hub information.
  * @param  hhcd HCD handle
  * @param  ch_num Channel number.
  *         This parameter can be a value from 1 to 8
  * @retval HAL status
  */
hal_status_t HAL_HCD_ClearChannelHubInfo(hal_hcd_handle_t *hhcd, hal_hcd_channel_t ch_num)
{
  /* Check hhcd handler */
  ASSERT_DBG_PARAM((hhcd != NULL));

  /* Check channel number */
  ASSERT_DBG_PARAM(((uint8_t)ch_num < USE_HAL_HCD_MAX_CHANNEL_NB));

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1U)
  if ((hhcd == NULL) || ((uint8_t)ch_num >= USE_HAL_HCD_MAX_CHANNEL_NB))
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  hhcd->channel[ch_num].core_ch.hub_addr = 0U;
  hhcd->channel[ch_num].core_ch.hub_port_nbr = 0U;

  return HAL_OK;
}

#if defined (USB_DRD_FS)
/**
  * @brief  Close host channel.
  * @param  hhcd HCD handle
  * @param  ch_num Channel number.
  *         This parameter can be a value from 1 to 15
  * @retval HAL status
  */
hal_status_t HAL_HCD_CloseChannel(hal_hcd_handle_t *hhcd, hal_hcd_channel_t ch_num)
{
  /* Check hhcd handler */
  ASSERT_DBG_PARAM((hhcd != NULL));

  /* Check channel number */
  ASSERT_DBG_PARAM(((uint8_t)ch_num < USE_HAL_HCD_MAX_CHANNEL_NB));

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1U)
  if ((hhcd == NULL) || ((uint8_t)ch_num >= USE_HAL_HCD_MAX_CHANNEL_NB))
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  if (hhcd->driver.host_channel_close((uint32_t)hhcd->instance, &hhcd->channel[ch_num].core_ch) != USB_CORE_OK)
  {
    return HAL_ERROR;
  }

  hhcd->channel[ch_num].state = HAL_HCD_CHANNEL_STATE_HALTED;

  return HAL_OK;
}
#endif /* defined (USB_DRD_FS) */

/**
  * @}
  */

/** @defgroup HCD_Exported_Functions_Group5 Peripheral State functions
  * @{
  */

/**
  * @brief  Return the HCD handle state.
  * @param  hhcd HCD handle
  * @retval HAL state
  */
hal_hcd_state_t HAL_HCD_GetState(const hal_hcd_handle_t *hhcd)
{
  /* Check hhcd handler */
  ASSERT_DBG_PARAM((hhcd != NULL));

  return hhcd->global_state;
}

/**
  * @brief  Return  URB state for a channel.
  * @param  hhcd HCD handle
  * @param  ch_num Channel number.
  *         This parameter can be a value from 1 to 15
  * @retval URB state.
  *          This parameter can be one of these values:
  *            HAL_HCD_CHANNEL_URB_STATE_IDLE/
  *            HAL_HCD_CHANNEL_URB_STATE_DONE/
  *            HAL_HCD_CHANNEL_URB_STATE_NOTREADY/
  *            HAL_HCD_CHANNEL_URB_STATE_ERROR/
  *            HAL_HCD_CHANNEL_URB_STATE_STALL
  */
hal_hcd_channel_urb_state_t HAL_HCD_GetChannelURBState(const hal_hcd_handle_t *hhcd, hal_hcd_channel_t ch_num)
{
  /* Check hhcd handler */
  ASSERT_DBG_PARAM((hhcd != NULL));
  /* Check channel number */
  ASSERT_DBG_PARAM(((uint8_t)ch_num < USE_HAL_HCD_MAX_CHANNEL_NB));

  return hhcd->channel[ch_num].urb_state;
}

/**
  * @brief  Return the Host Channel state.
  * @param  hhcd HCD handle
  * @param  ch_num Channel number.
  *         This parameter can be a value from 0 to 15
  * @retval Host channel state
  *          This parameter can be one of these values:
  *            HAL_HCD_CHANNEL_STATE_RESET
  *            HAL_HCD_CHANNEL_STATE_IDLE
  *            HAL_HCD_CHANNEL_STATE_XFRC
  *            HAL_HCD_CHANNEL_STATE_HALTED
  *            HAL_HCD_CHANNEL_STATE_NYET
  *            HAL_HCD_CHANNEL_STATE_NAK
  *            HAL_HCD_CHANNEL_STATE_STALL
  *            HAL_HCD_CHANNEL_STATE_XACTERR
  *            HAL_HCD_CHANNEL_STATE_BBLERR
  *            HAL_HCD_CHANNEL_STATE_DATATGLERR
  */
hal_hcd_channel_state_t HAL_HCD_GetChannelState(const hal_hcd_handle_t *hhcd, hal_hcd_channel_t ch_num)
{
  /* Check hhcd handler */
  ASSERT_DBG_PARAM((hhcd != NULL));
  /* Check channel number */
  ASSERT_DBG_PARAM(((uint8_t)ch_num < USE_HAL_HCD_MAX_CHANNEL_NB));

  return hhcd->channel[ch_num].state;
}

/**
  * @}
  */

/** @defgroup HCD_Exported_Functions_Group6 IRQ handling functions
  * @{
  */
/**
  * @brief  Handles HCD interrupt request.
  * @param  hhcd HCD handle
  */
void HAL_HCD_IRQHandler(hal_hcd_handle_t *hhcd)
{
  /* Check hhcd handler */
  ASSERT_DBG_PARAM((hhcd != NULL));
  ASSERT_DBG_PARAM((hhcd->p_irq_handler != NULL));

  hhcd->current_mode = hhcd->driver.core_get_mode((uint32_t)hhcd->instance);

  hhcd->p_irq_handler(hhcd);

  return;
}

#if defined (USB_DRD_FS)

/**
  * @brief  Handle HCD interrupt request.
  * @param  hhcd HCD handle
  */
void HAL_HCD_DRD_IRQHandler(hal_hcd_handle_t *hhcd)
{
  usb_drd_global_t *p_usb;
  uint32_t istr_reg;
  uint32_t ch_dir;
  uint32_t phy_ch_num;

  /* Check hhcd handler */
  ASSERT_DBG_PARAM((hhcd != NULL));

  istr_reg = USB_DRD_ReadInterrupts((uint32_t)hhcd->instance);
  p_usb = USB_DRD_GET_INSTANCE((uint32_t)hhcd->instance);

  /* Port Change Detected (Connection/Disconnection) */
  if ((istr_reg & USB_ISTR_DCON) == USB_ISTR_DCON)
  {
    /* Clear Flag */
    USB_DRD_ClearInterrupts((uint32_t)hhcd->instance, USB_ISTR_DCON);

    /* Call Port IRQHandler */
    HCD_DRD_Port_IRQHandler(hhcd);

    return;
  }

  /* Correct Transaction Detected -------*/
  if ((istr_reg & USB_ISTR_CTR) == USB_ISTR_CTR)
  {
    /* Get Physical channel */
    phy_ch_num = (USB_DRD_GET_CHNUM(p_usb) & 0x7U);

    /* Get channel direction */
    ch_dir = USB_DRD_GET_CHDIR(p_usb);

    if (ch_dir == (uint32_t)USB_CORE_CH_OUT_DIR)
    {
      /* Call Channel_OUT_IRQ() */
      HCD_DRD_CHANNEL_OUT_IRQHandler(hhcd, (usb_core_phy_chep_t)phy_ch_num);
    }
    else
    {
      /* Call Channel_IN_IRQ() */
      HCD_DRD_CHANNEL_IN_IRQHandler(hhcd, (usb_core_phy_chep_t)phy_ch_num);
    }

    return;
  }

  /* Wakeup Flag Detected */
  if ((istr_reg & USB_ISTR_WKUP) == USB_ISTR_WKUP)
  {
    if (hhcd->port_state == HAL_HCD_PORT_STATE_DEV_SUSPEND)
    {
      /* Set The L2Resume bit */
      p_usb->CNTR |= USB_CNTR_L2RES;

      /* Clear the wake-up flag */
      USB_DRD_ClearInterrupts((uint32_t)hhcd->instance, USB_ISTR_WKUP);

      /* Update the USB Software state machine */
#if defined (USE_HAL_HCD_REGISTER_CALLBACKS) && (USE_HAL_HCD_REGISTER_CALLBACKS == 1U)
      hhcd->p_port_resume_cb(hhcd);
#else
      HAL_HCD_PortResumeCallback(hhcd);
#endif /* USE_HAL_HCD_REGISTER_CALLBACKS */
      hhcd->port_state = HAL_HCD_PORT_STATE_DEV_RESUME;
    }
    else
    {
      /* Clear the wake-up flag */
      USB_DRD_ClearInterrupts((uint32_t)hhcd->instance, USB_ISTR_WKUP);
    }

    return;
  }

  /* Global Error Flag Detected */
  if ((istr_reg & USB_ISTR_ERR) == USB_ISTR_ERR)
  {
    USB_DRD_ClearInterrupts((uint32_t)hhcd->instance, USB_ISTR_ERR);

#if defined (USE_HAL_HCD_REGISTER_CALLBACKS) && (USE_HAL_HCD_REGISTER_CALLBACKS == 1U)
    hhcd->p_error_cb(hhcd);
#else
    HAL_HCD_ErrorCallback(hhcd);
#endif /* USE_HAL_HCD_REGISTER_CALLBACKS */

    return;
  }

  /* PMA Overrun detected */
  if ((istr_reg & USB_ISTR_PMAOVR) == USB_ISTR_PMAOVR)
  {
    USB_DRD_ClearInterrupts((uint32_t)hhcd->instance, USB_ISTR_PMAOVR);

#if defined (USE_HAL_HCD_REGISTER_CALLBACKS) && (USE_HAL_HCD_REGISTER_CALLBACKS == 1U)
    hhcd->p_error_cb(hhcd);
#else
    HAL_HCD_ErrorCallback(hhcd);
#endif /* USE_HAL_HCD_REGISTER_CALLBACKS */

    return;
  }

  /* Suspend Detected */
  if ((istr_reg & USB_ISTR_SUSP) == USB_ISTR_SUSP)
  {
    /* Set HAL Port State to Suspend */
    hhcd->port_state = HAL_HCD_PORT_STATE_DEV_SUSPEND;

    /* Force low-power mode in the macrocell */
    p_usb->CNTR |= USB_CNTR_SUSPEN;

    /* Clear the ISTR bit after setting CNTR_FSUSP */
    USB_DRD_ClearInterrupts((uint32_t)hhcd->instance, USB_ISTR_SUSP);

    /* Call suspend Callback */
#if defined (USE_HAL_HCD_REGISTER_CALLBACKS) && (USE_HAL_HCD_REGISTER_CALLBACKS == 1U)
    hhcd->p_port_suspend_cb(hhcd);
#else
    HAL_HCD_PortSuspendCallback(hhcd);
#endif /* USE_HAL_HCD_REGISTER_CALLBACKS */

    return;
  }

  /* Start Of Frame Detected */
  if ((istr_reg & USB_ISTR_SOF) == USB_ISTR_SOF)
  {
#if defined (USE_HAL_HCD_REGISTER_CALLBACKS) && (USE_HAL_HCD_REGISTER_CALLBACKS == 1U)
    hhcd->p_sof_cb(hhcd);
#else
    HAL_HCD_SofCallback(hhcd);
#endif /* USE_HAL_HCD_REGISTER_CALLBACKS */

    USB_DRD_ClearInterrupts((uint32_t)hhcd->instance, USB_ISTR_SOF);

    /* First SOF detected after USB_RESET, set port state to run */
    if (hhcd->port_state == HAL_HCD_PORT_STATE_DEV_RESET)
    {
      /* HAL State */
      hhcd->port_state = HAL_HCD_PORT_STATE_DEV_RUN;

#if defined (USE_HAL_HCD_REGISTER_CALLBACKS) && (USE_HAL_HCD_REGISTER_CALLBACKS == 1U)
      hhcd->p_port_enable_cb(hhcd);
#else
      HAL_HCD_PortEnabledCallback(hhcd);
#endif /* USE_HAL_HCD_REGISTER_CALLBACKS */
    }

    return;
  }
}
#endif /* defined (USB_DRD_FS) */

/**
  * @}
  */

/** @defgroup HCD_Exported_Functions_Group7 Default Callbacks functions
  * @{
  */

/**
  * @brief  SOF callback.
  * @param  hhcd HCD handle
  */
__WEAK void HAL_HCD_SofCallback(hal_hcd_handle_t *hhcd)
{
  /* Prevent unused argument(s) compilation warning */
  STM32_UNUSED(hhcd);

  /* WARNING : This function could not be modified, when the callback is needed,
            the HAL_HCD_SofCallback could be implemented in the user file
   */
}

/**
  * @brief Connection Event callback.
  * @param  hhcd HCD handle
  */
__WEAK void HAL_HCD_PortConnectCallback(hal_hcd_handle_t *hhcd)
{
  /* Prevent unused argument(s) compilation warning */
  STM32_UNUSED(hhcd);

  /* WARNING : This function could not be modified, when the callback is needed,
            the HAL_HCD_PortConnectCallback could be implemented in the user file
   */
}

/**
  * @brief  Disconnection Event callback.
  * @param  hhcd HCD handle
  */
__WEAK void HAL_HCD_PortDisconnectCallback(hal_hcd_handle_t *hhcd)
{
  /* Prevent unused argument(s) compilation warning */
  STM32_UNUSED(hhcd);

  /* WARNING : This function could not be modified, when the callback is needed,
            the HAL_HCD_PortDisconnectCallback could be implemented in the user file
   */
}

/**
  * @brief  Port Enabled  Event callback.
  * @param  hhcd HCD handle
  */
__WEAK void HAL_HCD_PortEnabledCallback(hal_hcd_handle_t *hhcd)
{
  /* Prevent unused argument(s) compilation warning */
  STM32_UNUSED(hhcd);

  /* WARNING : This function could not be modified, when the callback is needed,
            the HAL_HCD_PortEnabledCallback could be implemented in the user file
   */
}

/**
  * @brief  Port Disabled  Event callback.
  * @param  hhcd HCD handle
  */
__WEAK void HAL_HCD_PortDisabledCallback(hal_hcd_handle_t *hhcd)
{
  /* Prevent unused argument(s) compilation warning */
  STM32_UNUSED(hhcd);

  /* WARNING : This function could not be modified, when the callback is needed,
            the HAL_HCD_PortDisabledCallback could be implemented in the user file
   */
}

/**
  * @brief  Suspend Event callback.
  * @param  hhcd HCD handle
  */
__WEAK void HAL_HCD_PortSuspendCallback(hal_hcd_handle_t *hhcd)
{
  /* Prevent unused argument(s) compilation warning */
  STM32_UNUSED(hhcd);

  /* WARNING : This function could not be modified, when the callback is needed,
            the HAL_HCD_PortSuspendCallback could be implemented in the user file
  */

}

/**
  * @brief  Resume Event callback.
  * @param  hhcd HCD handle
  */
__WEAK void HAL_HCD_PortResumeCallback(hal_hcd_handle_t *hhcd)
{
  /* Prevent unused argument(s) compilation warning */
  STM32_UNUSED(hhcd);

  /* WARNING : This function could not be modified, when the callback is needed,
            the HAL_HCD_PortResumeCallback could be implemented in the user file
  */
}

/**
  * @brief  Notify URB state change callback.
  * @param  hhcd HCD handle
  * @param  ch_num Channel number.
  *         This parameter can be a value from 1 to 15
  * @param  urb_state:
  *          This parameter can be one of these values:
  *            HAL_HCD_CHANNEL_URB_STATE_IDLE/
  *            HAL_HCD_CHANNEL_URB_STATE_DONE/
  *            HAL_HCD_CHANNEL_URB_STATE_NOTREADY/
  *            HAL_HCD_CHANNEL_URB_STATE_ERROR/
  *            HAL_HCD_CHANNEL_URB_STATE_STALL/
  */
__WEAK void HAL_HCD_ChannelNotifyURBChangeCallback(hal_hcd_handle_t *hhcd, hal_hcd_channel_t ch_num,
                                                   hal_hcd_channel_urb_state_t urb_state)
{
  /* Prevent unused argument(s) compilation warning */
  STM32_UNUSED(hhcd);
  STM32_UNUSED(ch_num);
  STM32_UNUSED(urb_state);

  /* WARNING : This function could not be modified, when the callback is needed,
            the HAL_HCD_ChannelNotifyURBChangeCallback could be implemented in the user file
   */
}

/**
  * @brief  HCD Error callback.
  * @param  hhcd HCD handle
  */
__WEAK void HAL_HCD_ErrorCallback(hal_hcd_handle_t *hhcd)
{
  /* Prevent unused argument(s) compilation warning */
  STM32_UNUSED(hhcd);

  /* WARNING : This function could not be modified, when the callback is needed,
            the HAL_HCD_ErrorCallback could be implemented in the user file
   */
}

/**
  * @}
  */

/** @defgroup HCD_Exported_Functions_Group8 Register Callbacks functions
  * @{
  */
#if defined (USE_HAL_HCD_REGISTER_CALLBACKS) && (USE_HAL_HCD_REGISTER_CALLBACKS == 1U)
/**
  * @brief  Register User SOF Callback
  *         To be used instead of the weak predefined callback.
  * @param  hhcd USB HCD handle
  * @param  p_callback pointer to the Callback function
  * @retval HAL status
  */
hal_status_t HAL_HCD_RegisterSofCallback(hal_hcd_handle_t *hhcd, hal_hcd_cb_t p_callback)
{
  /* Check hhcd handler */
  ASSERT_DBG_PARAM((hhcd != NULL));
  ASSERT_DBG_PARAM((p_callback != NULL));

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1U)
  if ((hhcd == NULL) || (p_callback == NULL))
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  hhcd->p_sof_cb = p_callback;

  return HAL_OK;
}

/**
  * @brief  Register a USB HCD Connect Callback
  *         To be used instead of the weak predefined callback.
  * @param  hhcd USB HCD handle
  * @param  p_callback pointer to the Callback function
  * @retval HAL status
  */
hal_status_t HAL_HCD_RegisterPortConnectCallback(hal_hcd_handle_t *hhcd, hal_hcd_cb_t p_callback)
{
  /* Check hhcd handler */
  ASSERT_DBG_PARAM((hhcd != NULL));
  ASSERT_DBG_PARAM((p_callback != NULL));

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1U)
  if ((hhcd == NULL) || (p_callback == NULL))
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  hhcd->p_port_connect_cb = p_callback;

  return HAL_OK;
}

/**
  * @brief  Register a USB HCD Disconnect Callback
  *         To be used instead of the weak predefined callback.
  * @param  hhcd USB HCD handle
  * @param  p_callback pointer to the Callback function
  * @retval HAL status
  */
hal_status_t HAL_HCD_RegisterPortDisconnectCallback(hal_hcd_handle_t *hhcd, hal_hcd_cb_t p_callback)
{
  /* Check hhcd handler */
  ASSERT_DBG_PARAM((hhcd != NULL));
  ASSERT_DBG_PARAM((p_callback != NULL));

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1U)
  if ((hhcd == NULL) || (p_callback == NULL))
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  hhcd->p_port_disconnect_cb = p_callback;

  return HAL_OK;
}

/**
  * @brief  Register a USB HCD Port Enabled Callback
  *         To be used instead of the weak predefined callback.
  * @param  hhcd USB HCD handle
  * @param  p_callback pointer to the Callback function
  * @retval HAL status
  */
hal_status_t HAL_HCD_RegisterPortEnabledCallback(hal_hcd_handle_t *hhcd, hal_hcd_cb_t p_callback)
{
  /* Check hhcd handler */
  ASSERT_DBG_PARAM((hhcd != NULL));
  ASSERT_DBG_PARAM((p_callback != NULL));

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1U)
  if ((hhcd == NULL) || (p_callback == NULL))
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  hhcd->p_port_enable_cb = p_callback;

  return HAL_OK;
}

/**
  * @brief  Register a USB HCD Port Disabled Callback
  *         To be used instead of the weak predefined callback.
  * @param  hhcd USB HCD handle
  * @param  p_callback pointer to the Callback function
  * @retval HAL status
  */
hal_status_t HAL_HCD_RegisterPortDisabledCallback(hal_hcd_handle_t *hhcd, hal_hcd_cb_t p_callback)
{
  /* Check hhcd handler */
  ASSERT_DBG_PARAM((hhcd != NULL));
  ASSERT_DBG_PARAM((p_callback != NULL));

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1U)
  if ((hhcd == NULL) || (p_callback == NULL))
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  hhcd->p_port_disable_cb = p_callback;

  return HAL_OK;
}

/**
  * @brief  Register a USB HCD Suspend Callback
  *         To be used instead of the weak predefined callback.
  * @param  hhcd USB HCD handle
  * @param  p_callback pointer to the Callback function
  * @retval HAL status
  */
hal_status_t HAL_HCD_RegisterPortSuspendCallback(hal_hcd_handle_t *hhcd, hal_hcd_cb_t p_callback)
{
  /* Check hhcd handler */
  ASSERT_DBG_PARAM((hhcd != NULL));
  ASSERT_DBG_PARAM((p_callback != NULL));

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1U)
  if ((hhcd == NULL) || (p_callback == NULL))
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  hhcd->p_port_suspend_cb = p_callback;

  return HAL_OK;
}

/**
  * @brief  Register a USB HCD Resume Callback
  *         To be used instead of the weak predefined callback.
  * @param  hhcd USB HCD handle
  * @param  p_callback pointer to the Callback function
  * @retval HAL status
  */
hal_status_t HAL_HCD_RegisterPortResumeCallback(hal_hcd_handle_t *hhcd, hal_hcd_cb_t p_callback)
{
  /* Check hhcd handler */
  ASSERT_DBG_PARAM((hhcd != NULL));
  ASSERT_DBG_PARAM((p_callback != NULL));

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1U)
  if ((hhcd == NULL) || (p_callback == NULL))
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  hhcd->p_port_resume_cb = p_callback;

  return HAL_OK;
}


/**
  * @brief  Register USB HCD Host Channel Notify URB Change Callback
  *         To be used instead of the weak HAL_HCD_ChannelNotifyURBChangeCallback() predefined callback.
  * @param  hhcd HCD handle
  * @param  p_callback pointer to the USB HCD Host Channel Notify URB Change Callback function
  * @retval HAL status
  */
hal_status_t HAL_HCD_RegisterChannelNotifyURBChangeCallback(hal_hcd_handle_t *hhcd,
                                                            hal_hcd_ch_notify_urb_change_cb_t p_callback)
{
  /* Check hhcd handler */
  ASSERT_DBG_PARAM((hhcd != NULL));
  ASSERT_DBG_PARAM((p_callback != NULL));

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1U)
  if ((hhcd == NULL) || (p_callback == NULL))
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  hhcd->p_ch_notify_urb_change_cb = p_callback;

  return HAL_OK;
}

/**
  * @brief  Register USB HCD Error Callback
  *         To be used instead of the weak HAL_HCD_ErrorCallback() predefined callback.
  * @param  hhcd HCD handle
  * @param  p_callback pointer to the USB HCD Error Callback function
  * @retval HAL status
  */
hal_status_t HAL_HCD_RegisterErrorCallback(hal_hcd_handle_t *hhcd, hal_hcd_cb_t p_callback)
{
  /* Check hhcd handler */
  ASSERT_DBG_PARAM((hhcd != NULL));
  ASSERT_DBG_PARAM((p_callback != NULL));

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1U)
  if ((hhcd == NULL) || (p_callback == NULL))
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  hhcd->p_error_cb = p_callback;

  return HAL_OK;
}

#endif /* USE_HAL_HCD_REGISTER_CALLBACKS */

/**
  * @}
  */

/**
  * @}
  */
/* Private functions  -----------------------------------------------*/
/** @addtogroup HCD_Private_Functions
  * @{
  */

#if defined (USE_HAL_HCD_USB_DOUBLE_BUFFER) && (USE_HAL_HCD_USB_DOUBLE_BUFFER == 1)
/**
  * @brief  Handle Host Channel OUT Double Buffer Bulk requests.
  * @param  hhcd HCD handle
  * @param  ch_num Channel number This parameter can be a value from 1 to 15
  * @param  phy_ch_num Physical Channel number [0..7]
  * @param  reg_value contain Snapshot of the EPCHn register when ISR is detected
  */
static void HCD_DRD_CHANNEL_OUT_BulkDb(hal_hcd_handle_t *hhcd, usb_core_channel_t ch_num,
                                       usb_core_phy_chep_t phy_ch_num, uint32_t reg_value)
{
  uint16_t data_xfr;
  uint16_t len;

  /* Check hhcd handler */
  ASSERT_DBG_PARAM((hhcd != NULL));
  /* Check channel number */
  ASSERT_DBG_PARAM(((uint8_t)ch_num < USE_HAL_HCD_MAX_CHANNEL_NB));

  /* Send Buffer0 */
  if ((reg_value & USB_CH_DTOG_TX) != 0U)
  {
    data_xfr = (uint16_t)(((USB_DRD_PMA_BUFF + (uint32_t)phy_ch_num)->TXBD & 0x03FF0000U) >> 16U);

    if (hhcd->channel[ch_num].core_ch.xfer_length >= data_xfr)
    {
      hhcd->channel[ch_num].core_ch.xfer_length -= data_xfr;
    }
    else
    {
      hhcd->channel[ch_num].core_ch.xfer_length = 0U;
    }

    /* Transfer still in progress: the device ACKed one max-packet-size (MPS) packet, but more data remains. */
    if (hhcd->channel[ch_num].core_ch.xfer_length != 0U)
    {
      /* Manage multiple Xfer */
      hhcd->channel[ch_num].core_ch.xfer_count += data_xfr;

      /* Check if we need to free user buffer */
      if ((reg_value & USB_CH_DTOG_RX) != 0U)
      {
        /* Toggle SwBuff */
        USB_DRD_HCD_CLEAR_TX_DTOG((uint32_t)hhcd->instance, phy_ch_num);
        USB_DRD_HCD_CLEAR_RX_DTOG((uint32_t)hhcd->instance, phy_ch_num);
        USB_DRD_HCD_TX_DTOG((uint32_t)hhcd->instance, phy_ch_num);
      }

      if (hhcd->channel[ch_num].core_ch.xfer_size > 0U) /* Still data to fill in the buffer */
      {
        hhcd->channel[ch_num].core_ch.p_xfer_buffer += data_xfr;

        /* Calculate Length of new buffer to fill */
        if (hhcd->channel[ch_num].core_ch.xfer_size > hhcd->channel[ch_num].core_ch.max_packet)
        {
          len = (uint16_t)hhcd->channel[ch_num].core_ch.max_packet;
          hhcd->channel[ch_num].core_ch.xfer_size -= len;
        }
        else
        {
          len = (uint16_t)hhcd->channel[ch_num].core_ch.xfer_size;
          hhcd->channel[ch_num].core_ch.xfer_size = 0U; /* end of fill buffer */
        }

        /* Write remaining data to Buffer0 */
        USB_DRD_HCD_SET_CH_DBUF0_CNT((uint32_t)hhcd->instance, phy_ch_num, USB_CORE_EP_IN_DIR, (uint16_t)len);
        USB_DRD_WritePMA((uint32_t)hhcd->instance, hhcd->channel[ch_num].core_ch.p_xfer_buffer,
                         hhcd->channel[ch_num].core_ch.pma_addr0, (uint16_t)len);
      }
      /* Start a new transfer */
      USB_DRD_HCD_SET_CH_TX_STATUS((uint32_t)hhcd->instance, phy_ch_num, USB_CH_TX_VALID);
    }
    else
    {
      /* Transfer complete state */
      hhcd->channel[ch_num].core_ch.xfer_count += data_xfr;
      hhcd->channel[ch_num].state = HAL_HCD_CHANNEL_STATE_XFRC;
      hhcd->channel[ch_num].urb_state  = HAL_HCD_CHANNEL_URB_STATE_DONE;
      hhcd->channel[ch_num].toggle_out ^= 1U;
      /* Close the Channel */
      USB_DRD_HCD_SET_CH_TX_STATUS((uint32_t)hhcd->instance, phy_ch_num, USB_CH_TX_DIS);
    }
  }
  else
  {
    /* Send Buffer1 */
    data_xfr = (uint16_t)(((USB_DRD_PMA_BUFF + (uint32_t)phy_ch_num)->RXBD & 0x03FF0000U) >> 16U);

    if (hhcd->channel[ch_num].core_ch.xfer_length >= data_xfr) /* updated */
    {
      hhcd->channel[ch_num].core_ch.xfer_length -= data_xfr;
    }

    /* Transfer not yet finished only one packet of mps is transferred and ACKed from device */
    if (hhcd->channel[ch_num].core_ch.xfer_length != 0U)
    {
      /* Manage multiple Xfer */
      hhcd->channel[ch_num].core_ch.xfer_count += data_xfr;

      /* Check if we need to free user buffer */
      if ((reg_value & USB_CH_DTOG_RX) == 0U)
      {
        /* Toggle SwBuff */
        USB_DRD_HCD_CLEAR_TX_DTOG((uint32_t)hhcd->instance, phy_ch_num);
        USB_DRD_HCD_CLEAR_RX_DTOG((uint32_t)hhcd->instance, phy_ch_num);
        USB_DRD_HCD_RX_DTOG((uint32_t)hhcd->instance, phy_ch_num);
      }

      if (hhcd->channel[ch_num].core_ch.xfer_size > 0U) /* Still data to fill in the buffer */
      {
        hhcd->channel[ch_num].core_ch.p_xfer_buffer += data_xfr;

        /* Calculate length of new buffer to fill */
        if (hhcd->channel[ch_num].core_ch.xfer_size > hhcd->channel[ch_num].core_ch.max_packet)
        {
          len = hhcd->channel[ch_num].core_ch.max_packet;
          hhcd->channel[ch_num].core_ch.xfer_size -= len;
        }
        else
        {
          len = (uint16_t)hhcd->channel[ch_num].core_ch.xfer_size;
          hhcd->channel[ch_num].core_ch.xfer_size = 0U; /* end of fill buffer */
        }

        /* Write remaining data to Buffer0 */
        USB_DRD_HCD_SET_CH_DBUF1_CNT((uint32_t)hhcd->instance, phy_ch_num, USB_CORE_EP_IN_DIR, (uint16_t)len);

        USB_DRD_WritePMA((uint32_t)hhcd->instance, hhcd->channel[ch_num].core_ch.p_xfer_buffer,
                         hhcd->channel[ch_num].core_ch.pma_addr1, (uint16_t)len);
      }

      /* Start a new transfer */
      USB_DRD_HCD_SET_CH_TX_STATUS((uint32_t)hhcd->instance, phy_ch_num, USB_CH_TX_VALID);
    }
    else
    {
      /* Transfer complete state */
      hhcd->channel[ch_num].core_ch.xfer_count += data_xfr;
      hhcd->channel[ch_num].state = HAL_HCD_CHANNEL_STATE_XFRC;
      hhcd->channel[ch_num].urb_state  = HAL_HCD_CHANNEL_URB_STATE_DONE;
      hhcd->channel[ch_num].toggle_out ^= 1U;

      /* Close the channel */
      USB_DRD_HCD_SET_CH_TX_STATUS((uint32_t)hhcd->instance, phy_ch_num, USB_CH_TX_DIS);
    }
  }
}


/**
  * @brief  Handle Host Channel IN Double Buffer Bulk requests.
  * @param  hhcd HCD handle
  * @param  ch_num Channel number: This parameter can be a value from 1 to 15
  * @param  phy_ch_num Physical Channel number [0..7]
  * @param  reg_value contain Snapshot of the EPCHn register when ISR is detected
  */
static void HCD_DRD_CHANNEL_IN_BulkDb(hal_hcd_handle_t *hhcd, usb_core_channel_t ch_num,
                                      usb_core_phy_chep_t phy_ch_num, uint32_t reg_value)
{
  uint16_t received_bytes;

  /* Check hhcd handler */
  ASSERT_DBG_PARAM((hhcd != NULL));

  /* Check channel number */
  ASSERT_DBG_PARAM(((uint8_t)ch_num < USE_HAL_HCD_MAX_CHANNEL_NB));

  /* Read from Buffer 0 */
  if ((reg_value & USB_CH_DTOG_RX) != 0U)
  {
    received_bytes = (uint16_t)USB_DRD_HCD_GET_CH_DBUF0_CNT((uint32_t)hhcd->instance, phy_ch_num);

    if (hhcd->channel[ch_num].core_ch.xfer_length <= received_bytes)
    {
      hhcd->channel[ch_num].core_ch.xfer_length = 0U;
    }
    else
    {
      hhcd->channel[ch_num].core_ch.xfer_length -= received_bytes;
    }

    /* Check if we Need to free the other buffer for the IP */
    if ((hhcd->channel[ch_num].core_ch.xfer_length != 0U) && ((reg_value & USB_CH_DTOG_TX) != 0U))
    {
      /* Toggle SwBuff */
      USB_DRD_TX_DTOG((uint32_t)hhcd->instance, phy_ch_num);
    }

    /* Read the byte from PMA to user Buffer(System Memory) */
    USB_DRD_ReadPMA((uint32_t)hhcd->instance, hhcd->channel[ch_num].core_ch.p_xfer_buffer,
                    hhcd->channel[ch_num].core_ch.pma_addr0, (uint16_t)received_bytes);
  }
  else
  {
    /* Read from Buffer 1 */
    received_bytes = (uint16_t) USB_DRD_HCD_GET_CH_DBUF1_CNT((uint32_t)hhcd->instance, phy_ch_num);

    if (hhcd->channel[ch_num].core_ch.xfer_length <= received_bytes)
    {
      hhcd->channel[ch_num].core_ch.xfer_length = 0U;
    }
    else
    {
      hhcd->channel[ch_num].core_ch.xfer_length -= received_bytes;
    }

    /* Check if we Need to free the other buffer for the IP */
    if ((hhcd->channel[ch_num].core_ch.xfer_length != 0U) && ((reg_value & USB_CH_DTOG_TX) == 0U))
    {
      /* Toggle SwBuff */
      USB_DRD_TX_DTOG((uint32_t)hhcd->instance, phy_ch_num);
    }

    /* Read the byte from PMA to user Buffer(System Memory) */
    USB_DRD_ReadPMA((uint32_t)hhcd->instance, hhcd->channel[ch_num].core_ch.p_xfer_buffer,
                    hhcd->channel[ch_num].core_ch.pma_addr1, (uint16_t)received_bytes);
  }

  /* Update the global number of all received bytes */
  hhcd->channel[ch_num].core_ch.xfer_count += received_bytes;

  /* Transfer complete state */
  hhcd->channel[ch_num].state = HAL_HCD_CHANNEL_STATE_ACK;
  hhcd->channel[ch_num].err_cnt = 0U;

  if ((hhcd->channel[ch_num].core_ch.xfer_length == 0U)
      || ((received_bytes < hhcd->channel[ch_num].core_ch.max_packet)))
  {
    hhcd->channel[ch_num].urb_state = HAL_HCD_CHANNEL_URB_STATE_DONE;
    hhcd->channel[ch_num].state  = HAL_HCD_CHANNEL_STATE_XFRC;

    /* disable channel */
    USB_DRD_HCD_SET_CH_RX_STATUS((uint32_t)hhcd->instance, phy_ch_num, USB_CH_RX_DIS);
  }
  else
  {
    hhcd->channel[ch_num].core_ch.p_xfer_buffer += received_bytes;

    /* Reactivate the Channel Submit an other URB since the Transfer is not yet completed */
    USB_DRD_HCD_SET_CH_RX_STATUS((uint32_t)hhcd->instance, phy_ch_num, USB_CH_RX_STRX);
  }
}
#endif /* defined (USE_HAL_HCD_USB_DOUBLE_BUFFER) && (USE_HAL_HCD_USB_DOUBLE_BUFFER == 1) */

#if defined (USE_HAL_HCD_USB_EP_TYPE_ISOC) && (USE_HAL_HCD_USB_EP_TYPE_ISOC == 1)
/**
  * @brief  Handle Host Channel IN Isochronous Transaction.
  * @param  hhcd HCD handle
  * @param  ch_num Channel number: This parameter can be a value from 1 to 15
  * @param  phy_ch_num Physical Channel number [0..7]
  * @param  reg_value contain Snapshot of the EPCHn register when ISR is detected
  */
static void HCD_DRD_CHANNEL_IN_IsocDb(hal_hcd_handle_t *hhcd, usb_core_channel_t ch_num,
                                      usb_core_phy_chep_t phy_ch_num, uint32_t reg_value)
{
  /* Check hhcd handler */
  ASSERT_DBG_PARAM((hhcd != NULL));

  /* Check channel number */
  ASSERT_DBG_PARAM(((uint8_t)ch_num < USE_HAL_HCD_MAX_CHANNEL_NB));

  /* Check if Double buffer isochronous */
  if ((reg_value & USB_CH_KIND) != 0U)
  {
    /* Get Data IN Packet */
    hhcd->channel[ch_num].core_ch.xfer_count = USB_DRD_HCD_GET_CH_RX_CNT((uint32_t)hhcd->instance, phy_ch_num);

    if (hhcd->channel[ch_num].core_ch.xfer_count != 0U)
    {
      USB_DRD_ReadPMA((uint32_t)hhcd->instance, hhcd->channel[ch_num].core_ch.p_xfer_buffer,
                      hhcd->channel[ch_num].core_ch.pma_address,
                      (uint16_t)hhcd->channel[ch_num].core_ch.xfer_count);

      hhcd->channel[ch_num].urb_state = HAL_HCD_CHANNEL_URB_STATE_DONE;
    }
  }
#if defined (USE_HAL_HCD_USB_DOUBLE_BUFFER) && (USE_HAL_HCD_USB_DOUBLE_BUFFER == 1)
  else  /* double buffer isochronous */
  {
    /* Read from Buffer0 */
    if ((reg_value & USB_CH_DTOG_RX) != 0U)
    {
      /* Get number of Received byte in buffer0 */
      hhcd->channel[ch_num].core_ch.xfer_count = USB_DRD_HCD_GET_CH_DBUF0_CNT((uint32_t)hhcd->instance, phy_ch_num);

      if (hhcd->channel[ch_num].core_ch.xfer_count != 0U)
      {
        /* Read from Buffer0 */
        USB_DRD_ReadPMA((uint32_t)hhcd->instance, hhcd->channel[ch_num].core_ch.p_xfer_buffer,
                        hhcd->channel[ch_num].core_ch.pma_addr0,
                        (uint16_t)hhcd->channel[ch_num].core_ch.xfer_count);

        hhcd->channel[ch_num].urb_state = HAL_HCD_CHANNEL_URB_STATE_DONE;
      }
    }
    else
    {
      /* Get number of Received byte in buffer1 */
      hhcd->channel[ch_num].core_ch.xfer_count = USB_DRD_HCD_GET_CH_DBUF1_CNT((uint32_t)hhcd->instance, phy_ch_num);

      if (hhcd->channel[ch_num].core_ch.xfer_count != 0U)
      {
        /* Read from Buffer1 */
        USB_DRD_ReadPMA((uint32_t)hhcd->instance, hhcd->channel[ch_num].core_ch.p_xfer_buffer,
                        hhcd->channel[ch_num].core_ch.pma_addr1,
                        (uint16_t)hhcd->channel[ch_num].core_ch.xfer_count);

        hhcd->channel[ch_num].urb_state = HAL_HCD_CHANNEL_URB_STATE_DONE;
      }
    }
  }
#endif /* defined (USE_HAL_HCD_USB_DOUBLE_BUFFER) && (USE_HAL_HCD_USB_DOUBLE_BUFFER == 1) */

  /* Transfer complete state */
  hhcd->channel[ch_num].state = HAL_HCD_CHANNEL_STATE_XFRC;

  /* Clear VTRX */
  USB_DRD_HCD_CLEAR_RX_CH_CTR((uint32_t)hhcd->instance, phy_ch_num);
}
#endif /* defined (USE_HAL_HCD_USB_EP_TYPE_ISOC) && (USE_HAL_HCD_USB_EP_TYPE_ISOC == 1) */

/**
  * @brief  Handle Host Channel IN interrupt requests.
  * @param  hhcd HCD handle
  * @param  phy_ch_num Channel number
  *         This parameter can be a value from 1 to 8
  */
static void HCD_DRD_CHANNEL_IN_IRQHandler(hal_hcd_handle_t *hhcd, usb_core_phy_chep_t phy_ch_num)
{
  uint16_t received_bytes;
  usb_core_channel_t ch_num = USB_DRD_GetLogicalChannel(phy_ch_num, USB_CORE_CH_IN_DIR);

  /* Check hhcd handler */
  ASSERT_DBG_PARAM((hhcd != NULL));

  /* Check channel number */
  ASSERT_DBG_PARAM(((uint8_t)ch_num < USE_HAL_HCD_MAX_CHANNEL_NB));

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1U)
  if ((uint8_t)ch_num >= USE_HAL_HCD_MAX_CHANNEL_NB)
  {
    return;
  }
#endif /* USE_HAL_CHECK_PARAM */

  /* Take a Flag snapshot from the CHEP register, due to STRX bits are used for both control and status */
  uint32_t ch_reg = USB_DRD_HCD_GET_CHANNEL((uint32_t)hhcd->instance, phy_ch_num);

  /* Manage Correct Transaction */
  if ((ch_reg & USB_CH_ERRRX) == 0U)
  {
    /* Manage all Non Isochronous Transaction */
    if ((ch_reg & USB_CH_UTYPE) != USB_EP_ISOCHRONOUS)
    {
      /* manage ACK response single buffer */
      if (((ch_reg) & USB_CH_RX_STRX) == USB_CH_RX_ACK_SBUF)
      {
        /* Get Control Data OUT Packet */
        received_bytes = (uint16_t)USB_DRD_HCD_GET_CH_RX_CNT((uint32_t)hhcd->instance, phy_ch_num);

        /* Read the byte from PMA to user Buffer(System Memory) */
        USB_DRD_ReadPMA((uint32_t)hhcd->instance, hhcd->channel[ch_num].core_ch.p_xfer_buffer,
                        hhcd->channel[ch_num].core_ch.pma_address, (uint16_t)received_bytes);

        /* update the global number of all received bytes */
        hhcd->channel[ch_num].core_ch.xfer_count += received_bytes;

        /* Transfer complete state */
        hhcd->channel[ch_num].state = HAL_HCD_CHANNEL_STATE_ACK;
        hhcd->channel[ch_num].err_cnt = 0U;

        if (hhcd->channel[ch_num].core_ch.xfer_length <= received_bytes)
        {
          hhcd->channel[ch_num].core_ch.xfer_length = 0U;
        }
        else
        {
          hhcd->channel[ch_num].core_ch.xfer_length -= received_bytes;
        }

        if ((hhcd->channel[ch_num].core_ch.xfer_length == 0U)
            || ((received_bytes < hhcd->channel[ch_num].core_ch.max_packet)))
        {
          hhcd->channel[ch_num].urb_state  = HAL_HCD_CHANNEL_URB_STATE_DONE;
          hhcd->channel[ch_num].state = HAL_HCD_CHANNEL_STATE_XFRC;
        }
        else
        {
          hhcd->channel[ch_num].core_ch.p_xfer_buffer += received_bytes;

          /* Reactivate the Channel to Submit another URB since the Transfer is not yet completed */
          USB_DRD_HCD_SET_CH_RX_STATUS((uint32_t)hhcd->instance, phy_ch_num, USB_CH_RX_STRX);
        }

        if ((hhcd->channel[ch_num].core_ch.ep_type == USB_CORE_EP_TYPE_BULK)
            || (hhcd->channel[ch_num].core_ch.ep_type == USB_CORE_EP_TYPE_INTR))
        {
          hhcd->channel[ch_num].toggle_in ^= 1U;
        }
      }
      /* Manage NACK Response */
      else if (((ch_reg & USB_CH_RX_STRX) == USB_CH_RX_NAK)
               && (hhcd->channel[ch_num].urb_state != HAL_HCD_CHANNEL_URB_STATE_DONE))
      {
        hhcd->channel[ch_num].urb_state = HAL_HCD_CHANNEL_URB_STATE_NOTREADY;
        hhcd->channel[ch_num].err_cnt = 0U;
        hhcd->channel[ch_num].state = HAL_HCD_CHANNEL_STATE_NAK;

        if (hhcd->channel[ch_num].core_ch.ep_type == USB_CORE_EP_TYPE_INTR)
        {
          /* Close the channel */
          USB_DRD_HCD_SET_CH_RX_STATUS((uint32_t)hhcd->instance, phy_ch_num, USB_CH_RX_DIS);
        }
      }
      /* Manage STALL Response */
      else if ((ch_reg & USB_CH_RX_STRX) == USB_CH_RX_STALL)
      {
        (void)HAL_HCD_HaltChannel(hhcd, (hal_hcd_channel_t)ch_num);
        hhcd->channel[ch_num].state = HAL_HCD_CHANNEL_STATE_STALL;
        hhcd->channel[ch_num].urb_state = HAL_HCD_CHANNEL_URB_STATE_STALL;

        /* Close the channel */
        USB_DRD_HCD_SET_CH_RX_STATUS((uint32_t)hhcd->instance, phy_ch_num, USB_CH_RX_DIS);
      }
#if defined (USE_HAL_HCD_USB_DOUBLE_BUFFER) && (USE_HAL_HCD_USB_DOUBLE_BUFFER == 1)
      /* Double Buffer Management in case of Bulk Transaction */
      else  if (((ch_reg & USB_CH_RX_STRX) == USB_CH_RX_ACK_DBUF) && ((ch_reg & USB_CH_KIND) != 0U))
      {
        /* Bulk IN Double Buffer ISR */
        HCD_DRD_CHANNEL_IN_BulkDb(hhcd, ch_num, phy_ch_num, ch_reg);
      }
#endif /* defined (USE_HAL_HCD_USB_DOUBLE_BUFFER) && (USE_HAL_HCD_USB_DOUBLE_BUFFER == 1) */
      else
      {
        /*....*/
        /* Not defined state: STRX=11 in single buffer no iso is not defined */
      }

#if defined (USE_HAL_HCD_REGISTER_CALLBACKS) && (USE_HAL_HCD_REGISTER_CALLBACKS == 1U)
      hhcd->p_ch_notify_urb_change_cb(hhcd, (hal_hcd_channel_t)ch_num, hhcd->channel[ch_num].urb_state);
#else
      HAL_HCD_ChannelNotifyURBChangeCallback(hhcd, (hal_hcd_channel_t)ch_num, hhcd->channel[ch_num].urb_state);
#endif /* USE_HAL_HCD_REGISTER_CALLBACKS */

      /* Clear VTRX */
      USB_DRD_HCD_CLEAR_RX_CH_CTR((uint32_t)hhcd->instance, phy_ch_num);
    }
#if defined (USE_HAL_HCD_USB_EP_TYPE_ISOC) && (USE_HAL_HCD_USB_EP_TYPE_ISOC == 1)
    /* Isochronous Channel */
    else
    {
      HCD_DRD_CHANNEL_IN_IsocDb(hhcd, ch_num, phy_ch_num, ch_reg);
    }
#endif /* defined (USE_HAL_HCD_USB_EP_TYPE_ISOC) && (USE_HAL_HCD_USB_EP_TYPE_ISOC == 1) */
  }
  else /* Error detected during last transaction */
  {
    /* Set URB Error State */
    hhcd->channel[ch_num].urb_state = HAL_HCD_CHANNEL_URB_STATE_NOTREADY;
    hhcd->channel[ch_num].err_cnt++;
    hhcd->channel[ch_num].state = HAL_HCD_CHANNEL_STATE_XACTERR;

    /* Clear VTTRX & ERR_RX */
    USB_DRD_HCD_CLEAR_RX_CH_ERR((uint32_t)hhcd->instance, phy_ch_num);

    /* Check Error number */
    if (hhcd->channel[ch_num].err_cnt > 3U)
    {
      hhcd->channel[ch_num].urb_state = HAL_HCD_CHANNEL_URB_STATE_ERROR;
      USB_DRD_HCD_SET_CH_RX_STATUS((uint32_t)hhcd->instance, phy_ch_num, USB_CH_RX_DIS);

      /* Clear pending err_tx */
      USB_DRD_HCD_CLEAR_RX_CH_ERR((uint32_t)hhcd->instance, phy_ch_num);
    }

#if defined (USE_HAL_HCD_REGISTER_CALLBACKS) && (USE_HAL_HCD_REGISTER_CALLBACKS == 1U)
    hhcd->p_ch_notify_urb_change_cb(hhcd, (hal_hcd_channel_t)ch_num, hhcd->channel[ch_num].urb_state);
#else
    HAL_HCD_ChannelNotifyURBChangeCallback(hhcd, (hal_hcd_channel_t)ch_num, hhcd->channel[ch_num].urb_state);
#endif /* USE_HAL_HCD_REGISTER_CALLBACKS */
  }
}

/**
  * @brief  Handle Host Channel OUT interrupt requests.
  * @param  hhcd  HCD handle
  * @param  phy_ch_num Channel number
  *         This parameter can be a value from 1 to 8
  */
static void HCD_DRD_CHANNEL_OUT_IRQHandler(hal_hcd_handle_t *hhcd, usb_core_phy_chep_t phy_ch_num)
{
  const usb_drd_global_t *p_usb;
  __IO uint32_t get_ch_reg;
  uint16_t data_xfr;
  usb_core_channel_t ch_num = USB_DRD_GetLogicalChannel(phy_ch_num, USB_CORE_CH_OUT_DIR);

  /* Check hhcd handler */
  ASSERT_DBG_PARAM((hhcd != NULL));

  /* Check channel number */
  ASSERT_DBG_PARAM(((uint8_t)ch_num < USE_HAL_HCD_MAX_CHANNEL_NB));

  if ((uint8_t)ch_num >= USE_HAL_HCD_MAX_CHANNEL_NB)
  {
    return;
  }

  p_usb = USB_DRD_GET_INSTANCE((uint32_t)hhcd->instance);

  /* Take a Flag snapshot from the CHEP register, due to STRX bits are used for both control & status */
  uint32_t ch_reg = *(__IO uint32_t *)((__IO uint32_t)(&(p_usb->CHEP0R) + (uint32_t)phy_ch_num));

  /*------ Manage Correct Transaction ------*/
  if ((ch_reg & USB_CH_ERRTX) == 0U)
  {
    /* Manage all Non Isochronous Transaction */
    if ((ch_reg & USB_CH_UTYPE) != USB_EP_ISOCHRONOUS)
    {
      /* Check ACK response */
      if ((ch_reg & USB_CH_TX_STTX) == USB_CH_TX_ACK_SBUF)
      {
        data_xfr = (uint16_t)(((USB_DRD_PMA_BUFF + (uint32_t)phy_ch_num)->TXBD & 0x03FF0000U) >> 16U);

        if (hhcd->channel[ch_num].core_ch.xfer_length >= data_xfr)
        {
          hhcd->channel[ch_num].core_ch.xfer_length -= data_xfr;
        }
        else
        {
          hhcd->channel[ch_num].core_ch.xfer_length = 0U;
        }

        if ((hhcd->channel[ch_num].core_ch.ep_type == USB_CORE_EP_TYPE_BULK)
            || (hhcd->channel[ch_num].core_ch.ep_type == USB_CORE_EP_TYPE_INTR))
        {
          hhcd->channel[ch_num].toggle_out ^= 1U;
        }

        /* Transfer no yet finished only one packet of mps is transferred and ACKed from device */
        if (hhcd->channel[ch_num].core_ch.xfer_length != 0U)
        {
          /* Manage multiple Xfer */
          hhcd->channel[ch_num].core_ch.p_xfer_buffer += data_xfr;
          hhcd->channel[ch_num].core_ch.xfer_count += data_xfr;

          /* Start a new transfer */
          (void)hhcd->driver.host_channel_start((uint32_t)hhcd->instance, &hhcd->channel[ch_num].core_ch);
        }
        else
        {
          /* Transfer complete */
          hhcd->channel[ch_num].core_ch.xfer_count += data_xfr;
          hhcd->channel[ch_num].state = HAL_HCD_CHANNEL_STATE_XFRC;
          hhcd->channel[ch_num].urb_state = HAL_HCD_CHANNEL_URB_STATE_DONE;
        }
      }
      /* Check NACK Response */
      else if (((ch_reg & USB_CHEP_NAK) == USB_CHEP_NAK) || ((ch_reg & USB_CH_TX_STTX) == USB_CH_TX_NAK))
      {
        /* Update Channel status */
        hhcd->channel[ch_num].state = HAL_HCD_CHANNEL_STATE_NAK;
        hhcd->channel[ch_num].urb_state = HAL_HCD_CHANNEL_URB_STATE_NOTREADY;
        hhcd->channel[ch_num].err_cnt = 0U;

        /* Get Channel register value */
        get_ch_reg = *(__IO uint32_t *)((__IO uint32_t)(&(p_usb->CHEP0R) + (uint32_t)phy_ch_num));

        /* Clear NAK status */
        get_ch_reg &= ~USB_CHEP_NAK & USB_CHEP_REG_MASK;

        /* Update channel register Value */
        USB_DRD_HCD_SET_CHANNEL((uint32_t)hhcd->instance, phy_ch_num, get_ch_reg);

        if (hhcd->channel[ch_num].core_ch.double_buffer_en == 0U)
        {
#if defined (USE_HAL_HCD_REGISTER_CALLBACKS) && (USE_HAL_HCD_REGISTER_CALLBACKS == 1U)
          hhcd->p_ch_notify_urb_change_cb(hhcd, (hal_hcd_channel_t)ch_num, hhcd->channel[ch_num].urb_state);
#else
          HAL_HCD_ChannelNotifyURBChangeCallback(hhcd, (hal_hcd_channel_t)ch_num, hhcd->channel[ch_num].urb_state);
#endif /* USE_HAL_HCD_REGISTER_CALLBACKS */
        }
      }
      /* Check STALL Response */
      else if ((ch_reg & USB_CH_TX_STTX) == USB_CH_TX_STALL)
      {
        (void) HAL_HCD_HaltChannel(hhcd, (hal_hcd_channel_t)ch_num);
        hhcd->channel[ch_num].state = HAL_HCD_CHANNEL_STATE_STALL;
        hhcd->channel[ch_num].urb_state = HAL_HCD_CHANNEL_URB_STATE_STALL;
      }
#if defined (USE_HAL_HCD_USB_DOUBLE_BUFFER) && (USE_HAL_HCD_USB_DOUBLE_BUFFER == 1)
      /* Check double buffer ACK in case of bulk transaction */
      else if ((ch_reg & USB_CH_TX_STTX) == USB_CH_TX_ACK_DBUF)
      {
        /* Double buffer management Bulk Out */
        (void)HCD_DRD_CHANNEL_OUT_BulkDb(hhcd, ch_num, phy_ch_num, ch_reg);
      }
#endif /* defined (USE_HAL_HCD_USB_DOUBLE_BUFFER) && (USE_HAL_HCD_USB_DOUBLE_BUFFER == 1) */
      else
      {
        /*...*/
      }

      if ((ch_reg & USB_CH_TX_STTX) != USB_CH_TX_NAK)
      {
#if defined (USE_HAL_HCD_REGISTER_CALLBACKS) && (USE_HAL_HCD_REGISTER_CALLBACKS == 1U)
        hhcd->p_ch_notify_urb_change_cb(hhcd, (hal_hcd_channel_t)ch_num, hhcd->channel[ch_num].urb_state);
#else
        HAL_HCD_ChannelNotifyURBChangeCallback(hhcd, (hal_hcd_channel_t)ch_num, hhcd->channel[ch_num].urb_state);
#endif /* USE_HAL_HCD_REGISTER_CALLBACKS */
      }

      USB_DRD_HCD_CLEAR_TX_CH_CTR((uint32_t)hhcd->instance, phy_ch_num);
    }
#if defined (USE_HAL_HCD_USB_EP_TYPE_ISOC) && (USE_HAL_HCD_USB_EP_TYPE_ISOC == 1)
    /* Handle Isochronous channel */
    else
    {
      /* Correct transaction */
      if ((p_usb->ISTR & USB_ISTR_ERR) == 0U)
      {
        /* Double buffer isochronous out */
        if ((ch_reg & USB_CH_KIND) != 0U)
        {
          USB_DRD_HCD_SET_CH_TX_CNT((uint32_t)hhcd->instance, phy_ch_num, 0U);
        }
#if defined (USE_HAL_HCD_USB_DOUBLE_BUFFER) && (USE_HAL_HCD_USB_DOUBLE_BUFFER == 1)
        else /* Double buffer isochronous out */
        {
          /* Odd Transaction */
          if ((ch_reg & USB_CH_DTOG_TX) != 0U)
          {
            USB_DRD_HCD_SET_CH_TX_CNT((uint32_t)hhcd->instance, phy_ch_num, 0U);
          }
          /* Even Transaction */
          else
          {
            USB_DRD_HCD_SET_CH_RX_CNT((uint32_t)hhcd->instance, phy_ch_num, 0U);
          }

          USB_DRD_SET_CHEP_TX_STATUS((uint32_t)hhcd->instance, phy_ch_num, USB_CH_TX_DIS);
        }
#endif /* defined (USE_HAL_HCD_USB_DOUBLE_BUFFER) && (USE_HAL_HCD_USB_DOUBLE_BUFFER == 1) */

        /* Transfer complete state */
        hhcd->channel[ch_num].state = HAL_HCD_CHANNEL_STATE_XFRC;
        hhcd->channel[ch_num].urb_state = HAL_HCD_CHANNEL_URB_STATE_DONE;
      }

      /* Clear Correct Transfer */
      USB_DRD_HCD_CLEAR_TX_CH_CTR((uint32_t)hhcd->instance, phy_ch_num);

      /* TX COMPLETE */
#if defined (USE_HAL_HCD_REGISTER_CALLBACKS) && (USE_HAL_HCD_REGISTER_CALLBACKS == 1U)
      hhcd->p_ch_notify_urb_change_cb(hhcd, (hal_hcd_channel_t)ch_num, hhcd->channel[ch_num].urb_state);
#else
      HAL_HCD_ChannelNotifyURBChangeCallback(hhcd, (hal_hcd_channel_t)ch_num, hhcd->channel[ch_num].urb_state);
#endif /* USE_HAL_HCD_REGISTER_CALLBACKS */

    }
#endif /* defined (USE_HAL_HCD_USB_EP_TYPE_ISOC) && (USE_HAL_HCD_USB_EP_TYPE_ISOC == 1) */
  }
  /*------ Manage Transaction Error------*/
  else
  {
    hhcd->channel[ch_num].err_cnt++;
    if (hhcd->channel[ch_num].err_cnt > 3U)
    {
      USB_DRD_HCD_SET_CH_TX_STATUS((uint32_t)hhcd->instance, phy_ch_num, USB_CH_TX_DIS);
      hhcd->channel[ch_num].urb_state = HAL_HCD_CHANNEL_URB_STATE_ERROR;
    }
    else
    {
      hhcd->channel[ch_num].urb_state = HAL_HCD_CHANNEL_URB_STATE_NOTREADY;
    }

    hhcd->channel[ch_num].state = HAL_HCD_CHANNEL_STATE_XACTERR;

    /* Clear ERR_TX */
    USB_DRD_HCD_CLEAR_TX_CH_ERR((uint32_t)hhcd->instance, phy_ch_num);

#if defined (USE_HAL_HCD_REGISTER_CALLBACKS) && (USE_HAL_HCD_REGISTER_CALLBACKS == 1U)
    hhcd->p_ch_notify_urb_change_cb(hhcd, (hal_hcd_channel_t)ch_num, hhcd->channel[ch_num].urb_state);
#else
    HAL_HCD_ChannelNotifyURBChangeCallback(hhcd, (hal_hcd_channel_t)ch_num, hhcd->channel[ch_num].urb_state);
#endif /* USE_HAL_HCD_REGISTER_CALLBACKS */
  }
}


/**
  * @brief  Handle Host Port interrupt requests.
  * @param  hhcd  HCD handle
  */
static void HCD_DRD_Port_IRQHandler(hal_hcd_handle_t *hhcd)
{
  const usb_drd_global_t *p_usb;
  uint32_t fnr_reg;
  uint32_t istr_reg;

  /* Check hhcd handler */
  ASSERT_DBG_PARAM((hhcd != NULL));

  p_usb = USB_DRD_GET_INSTANCE((uint32_t)hhcd->instance);
  fnr_reg = p_usb->FNR;
  istr_reg = p_usb->ISTR;

  /* SE0 detected USB Disconnected state */
  if ((fnr_reg & (USB_FNR_RXDP | USB_FNR_RXDM)) == 0U)
  {
    /* Host Port State */
    hhcd->port_state = HAL_HCD_PORT_STATE_DEV_DISCONNECT;

    /* Clear all allocated virtual channel */
    (void)USB_DRD_ClearPhysicalChannels();

    /* Reset the PMA current pointer */
    (void)USB_DRD_PMAReset();

    /* Disconnection Callback */
#if defined (USE_HAL_HCD_REGISTER_CALLBACKS) && (USE_HAL_HCD_REGISTER_CALLBACKS == 1U)
    hhcd->p_port_disconnect_cb(hhcd);
#else
    HAL_HCD_PortDisconnectCallback(hhcd);
#endif /* USE_HAL_HCD_REGISTER_CALLBACKS */

    return;
  }

  if ((hhcd->port_state == HAL_HCD_PORT_STATE_DEV_DISCONNECT) != 0U)
  {
    /* J-state or K-state detected & LastState=Disconnected */
    if (((fnr_reg & USB_FNR_RXDP) != 0U) || ((istr_reg & USB_ISTR_LS_DCONN) != 0U))
    {
      hhcd->port_state = HAL_HCD_PORT_STATE_DEV_CONNECT;

#if defined (USE_HAL_HCD_REGISTER_CALLBACKS) && (USE_HAL_HCD_REGISTER_CALLBACKS == 1U)
      hhcd->p_port_connect_cb(hhcd);
#else
      HAL_HCD_PortConnectCallback(hhcd);
#endif /* USE_HAL_HCD_REGISTER_CALLBACKS */
    }
  }
  else
  {
    /* J-state or K-state detected & lastState=Connected: a Missed disconnection is detected */
    if (((fnr_reg & USB_FNR_RXDP) != 0U) || ((istr_reg & USB_ISTR_LS_DCONN) != 0U))
    {
      /* Host Port State */
      hhcd->port_state = HAL_HCD_PORT_STATE_DEV_DISCONNECT;

      /* Clear all allocated virtual channel */
      (void)USB_DRD_ClearPhysicalChannels();

      /* Reset the PMA current pointer */
      (void)USB_DRD_PMAReset();

      /* Disconnection Callback */
#if defined (USE_HAL_HCD_REGISTER_CALLBACKS) && (USE_HAL_HCD_REGISTER_CALLBACKS == 1U)
      hhcd->p_port_disconnect_cb(hhcd);
#else
      HAL_HCD_PortDisconnectCallback(hhcd);
#endif /* USE_HAL_HCD_REGISTER_CALLBACKS */
    }
  }
}

/**
  * @}
  */

/**
  * @}
  */
#endif /* defined (USE_HAL_HCD_MODULE) && (USE_HAL_HCD_MODULE == 1) */
#endif /* defined (USB_DRD_FS) */

/**
  * @}
  */
