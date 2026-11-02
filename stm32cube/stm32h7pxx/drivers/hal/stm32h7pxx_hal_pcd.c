/**
  ******************************************************************************
  * @file    stm32h7pxx_hal_pcd.c
  * @brief   PCD HAL module driver.
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

/** @addtogroup STM32H7Pxx_HAL_Driver
  * @{
  */
#if defined (USB_OTG_FS)
#if defined (USE_HAL_PCD_MODULE) && (USE_HAL_PCD_MODULE == 1)

/** @addtogroup PCD
  * @brief Peripheral Controller Driver, including the functions that allow the USB to be used in device mode.
  * @{
  */
/** @defgroup PCD_Introduction Introduction
  * @{

  USB Peripheral Controller Driver (PCD) hardware abstraction layer provides all required APIs to interface with the
  USB instance in device mode.
  It simplifies the initialization, configuration, and management of the USB depending on the user's required device
  function.

  This abstraction layer ensures portability and ease of use across different STM32 series. The PCD HAL abstracts
  different USB hardware instances that can be (depending on the STM32 MCU):
  * USB OTG FS (On-The-GO Full Speed)
  * USB OTG HS (On-The-GO High Speed)
  * USB DRD FS (Dual Role Device Full Speed)

  */
/**
  * @}
  */

/** @defgroup PCD_How_To_Use HAL How To Use
  * @{

  # How to use the HAL USB PCD module driver

  ## Use the USB Peripheral Controller Driver (PCD) HAL driver as follows:

  1. Declare a hal_pcd_handle_t handle structure, for example:
      hal_pcd_handle_t gh_pcd_usb_otg_fs;

  2. Initialize the USB PCD low-level resources:
    - USB PCD interface clock configuration:
      - Enable USB peripheral clock.

    - USB PCD interface power configuration:
      - Enable USB peripheral VddUSB power supply if applicable.

    - USB device pins configuration:
      USB data pins are automatically configured by the hardware during USB peripheral initialization;
      no additional user action is required.

    - NVIC configuration for interrupt handling with HAL_PCD_IRQHandler():
      - Set the USB PCD interrupt priority.
      - Enable the USB IRQ channel in the NVIC.

  3. Initialize the USB PCD driver with HAL_PCD_Init() by selecting an instance, for example:

     - HAL_PCD_Init(&gh_pcd_usb_otg_fs, HAL_PCD_OTG_FS);

  - Declare a hal_pcd_config_t structure, for example:
     - hal_pcd_config_t config_pcd_usb_otg_fs;

  - In the configuration structure,
    program the PHY interface, core speed, and other parameters as required.

  - Apply the configuration with:
     - HAL_PCD_SetConfig(&gh_pcd_usb_otg_fs, &config_pcd_usb_otg_fs);

  - Configure required USB device endpoints.

  ## USB PCD callback definitions:
  By default, all callbacks are initialized to their corresponding default weak functions.
  When the compilation define USE_HAL_PCD_REGISTER_CALLBACKS is set to 1U, configure the
  driver callbacks dynamically using the callback registration functions:

  | Default callback weak function                   | Callback registration function
  |--------------------------------------------------|------------------------------------------------------------------
  | HAL_PCD_SofCallback()                            | HAL_PCD_RegisterSofCallback()
  | HAL_PCD_SetupStageCallback()                     | HAL_PCD_RegisterSetupCallback()
  | HAL_PCD_ResetCallback()                          | HAL_PCD_RegisterResetCallback()
  | HAL_PCD_SuspendCallback()                        | HAL_PCD_RegisterSuspendCallback()
  | HAL_PCD_ResumeCallback()                         | HAL_PCD_RegisterResumeCallback()
  | HAL_PCD_ConnectCallback()                        | HAL_PCD_RegisterConnectCallback()
  | HAL_PCD_DisconnectCallback()                     | HAL_PCD_RegisterDisconnectCallback()
  | HAL_PCD_DataOutStageCallback()                   | HAL_PCD_RegisterDataOutStageCallback()
  | HAL_PCD_DataInStageCallback()                    | HAL_PCD_RegisterDataInStageCallback()
  | HAL_PCD_ISOOUTIncompleteCallback()               | HAL_PCD_RegisterIsoOutIncpltCallback()
  | HAL_PCD_ISOINIncompleteCallback()                | HAL_PCD_RegisterIsoInIncpltCallback()
  | HAL_PCD_ErrorCallback()                          | HAL_PCD_RegisterErrorCallback()
  | HAL_PCD_EndpointAbortTransferCallback()          | HAL_PCD_RegisterEndpointAbortTransferCallback()
  | HAL_PCD_BcdCallback()                            | HAL_PCD_RegisterBcdCallback()
  | HAL_PCD_LpmCallback()                            | HAL_PCD_RegisterLpmCallback()
  */

/**
  * @}
  */

/** @defgroup PCD_Configuration_Table Configuration Table
  * @{
  ## Configuration inside the USB PCD driver:

  | Config defines                 | Description     | Default value | Note
  |--------------------------------|-----------------|---------------|--------------------------------------------------
  | USE_ASSERT_DBG_PARAM           | from IDE        |       NA      | Enable the parameter assert.
  | USE_ASSERT_DBG_STATE           | from IDE        |       NA      | Enable the state assert.
  | USE_HAL_PCD_MODULE             | from hal_conf.h |        1      | Enable the HAL USB PCD module.
  | USE_HAL_PCD_REGISTER_CALLBACKS | from hal_conf.h |        0      | Enable the register callbacks.
  | USE_HAL_PCD_USB_EP_TYPE_ISOC   | from hal_conf.h |        1      | Enable support for isochronous endpoints.
  | USE_HAL_PCD_USB_BCD            | from hal_conf.h |        0      | Enable USB Battery Charging Detection support.
  | USE_HAL_PCD_USB_LPM            | from hal_conf.h |        0      | Enable USB Link Power Management support.
  | USE_HAL_PCD_MAX_ENDPOINT_NB    | from hal_conf.h |       16      | Maximum number of USB PCD endpoints.
  | USE_HAL_PCD_USER_DATA          | from hal_conf.h |        0      | Add user data to the HAL USB PCD handle.
  | USE_HAL_PCD_GET_LAST_ERRORS    | from hal_conf.h |        0      | Add an error value to the HAL USB PCD handle.
  | USE_HAL_CHECK_PARAM            | from hal_conf.h |        0      | Enable checking of PCD API parameters at runtime.
  */

/**
  * @}
  */

/* Private types -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/** @defgroup PCD_Private_Macros Private Macros
  * @{
  */

/*! Macro to check ep_type */
#define HAL_PCD_CHECK_EP_TYPE(ep_type) ((((ep_type) == HAL_PCD_EP_TYPE_CTRL) \
                                         || ((ep_type) == HAL_PCD_EP_TYPE_BULK) \
                                         || ((ep_type) == HAL_PCD_EP_TYPE_INTR) \
                                         || ((ep_type) == HAL_PCD_EP_TYPE_ISOC)) ? 1U : 0U)

/**
  * @}
  */

/* Private functions prototypes ----------------------------------------------*/
/** @defgroup PCD_Private_Functions Private Functions
  * @{
  */
#if defined (USB_OTG_FS)
static hal_status_t PCD_WriteEmptyTxFifo(hal_pcd_handle_t *hpcd, uint32_t ep_num);
static hal_status_t PCD_EP_OutXfrComplete_int(hal_pcd_handle_t *hpcd, uint32_t ep_num);
static hal_status_t PCD_EP_OutSetupPacket_int(hal_pcd_handle_t *hpcd, uint32_t ep_num);
#endif /* defined (USB_OTG_FS) */
/**
  * @}
  */

/* Exported functions --------------------------------------------------------*/
/** @addtogroup PCD_Exported_Functions Exported Functions
  * @{
  */

/** @addtogroup PCD_Exported_Functions_Group1 Initialization and deinitialization functions
  *
  * @{
  This subsection provides a set of functions allowing to initialize and deinitialize the PCD.
  - Call the function HAL_PCD_Init() to initialize the selected PCD handle and associate an instance.
  - Call the function HAL_PCD_DeInit() to de-initialize the given HAL PCD instance by resetting the state machine.
  */

/**
  * @brief  Initializes the PCD according to the specified
  *         parameters in the hal_pcd_handle_t and initialize the associated instance.
  * @param  hpcd PCD handler
  * @param  instance PCD instance
  * @retval HAL status
  */
hal_status_t HAL_PCD_Init(hal_pcd_handle_t *hpcd, hal_pcd_t instance)
{
  ASSERT_DBG_PARAM((hpcd != NULL));

  ASSERT_DBG_PARAM(IS_PCD_ALL_INSTANCE((usb_otg_global_t *)((uint32_t)instance)));

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1U)
  if (hpcd == NULL)
  {
    return HAL_INVALID_PARAM;
  }

  if (!IS_PCD_ALL_INSTANCE((usb_otg_global_t *)((uint32_t)instance)))
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  hpcd->instance = instance;

  switch (instance)
  {
    case HAL_PCD_OTG_FS:

      /* Register USB core instance operational functions */
      (void)USB_OTG_PCD_InitDriver(&hpcd->driver);

      hpcd->p_irq_handler = HAL_PCD_OTG_IRQHandler;

      /* Get the device endpoints number */
      hpcd->endpoints_nbr = (uint8_t)(USB_OTG_FS_EP_NBR);

      break;

    default:
      break;
  }

#if defined (USE_HAL_PCD_GET_LAST_ERRORS) && (USE_HAL_PCD_GET_LAST_ERRORS == 1)
  hpcd->last_error_codes = HAL_PCD_ERROR_NONE;
#endif /* USE_HAL_PCD_GET_LAST_ERRORS */

#if defined (USE_HAL_PCD_REGISTER_CALLBACKS) && (USE_HAL_PCD_REGISTER_CALLBACKS == 1U)
  hpcd->p_sof_cb = HAL_PCD_SofCallback;
  hpcd->p_setup_stage_cb = HAL_PCD_SetupStageCallback;
  hpcd->p_reset_cb = HAL_PCD_ResetCallback;
  hpcd->p_suspend_cb = HAL_PCD_SuspendCallback;
  hpcd->p_resume_cb = HAL_PCD_ResumeCallback;
  hpcd->p_connect_cb = HAL_PCD_ConnectCallback;
  hpcd->p_disconnect_cb = HAL_PCD_DisconnectCallback;
  hpcd->p_data_out_stage_cb = HAL_PCD_DataOutStageCallback;
  hpcd->p_data_in_stage_cb = HAL_PCD_DataInStageCallback;
  hpcd->p_iso_out_incomplete_cb = HAL_PCD_ISOOUTIncompleteCallback;
  hpcd->p_iso_in_incomplete_cb = HAL_PCD_ISOINIncompleteCallback;
  hpcd->p_error_cb = HAL_PCD_ErrorCallback;
  hpcd->p_ep_abort_transfer_cb = HAL_PCD_EndpointAbortTransferCallback;
  hpcd->p_low_power_management_cb = HAL_PCD_LpmCallback;
  hpcd->p_battery_charging_cb = HAL_PCD_BcdCallback;
#endif /* (USE_HAL_PCD_REGISTER_CALLBACKS) */

  /* Reset device address */
  hpcd->usb_address = 0U;

#if defined (USE_HAL_PCD_USER_DATA) && (USE_HAL_PCD_USER_DATA == 1U)
  hpcd->p_user_data = (void *) NULL;
#endif /* USE_HAL_PCD_USER_DATA */

  hpcd->device_state = HAL_PCD_PORT_STATE_DEV_DISCONNECT;
  hpcd->global_state = HAL_PCD_STATE_INIT;

  return HAL_OK;
}

/**
  * @brief  DeInitializes the PCD peripheral.
  * @param  hpcd PCD handler
  */
void HAL_PCD_DeInit(hal_pcd_handle_t *hpcd)
{
  ASSERT_DBG_PARAM((hpcd != NULL));

  ASSERT_DBG_PARAM(IS_PCD_ALL_INSTANCE((usb_otg_global_t *)((uint32_t)hpcd->instance)));

  /* Stop device operation before de-initializing */
  (void)hpcd->driver.device_stop((uint32_t)hpcd->instance);

#if defined (USE_HAL_PCD_USER_DATA) && (USE_HAL_PCD_USER_DATA == 1U)
  hpcd->p_user_data = (void *) NULL;
#endif /* USE_HAL_PCD_USER_DATA */

#if defined (USE_HAL_PCD_GET_LAST_ERRORS) && (USE_HAL_PCD_GET_LAST_ERRORS == 1)
  hpcd->last_error_codes = HAL_PCD_ERROR_NONE;
#endif /* USE_HAL_PCD_GET_LAST_ERRORS */
  hpcd->device_state = HAL_PCD_PORT_STATE_DEV_DISCONNECT;
  hpcd->global_state = HAL_PCD_STATE_RESET;
}

/**
  * @}
  */

/** @addtogroup PCD_Exported_Functions_Group2 Global Configuration functions
  * @{
  This subsection provides functions allowing to configure the USB in Device mode:
  - Call HAL_PCD_SetConfig() to configure the initialized instance with a set of parameters containing:
     * phy_interface
     * endpoints_nbr
     * core_speed
  */

/**
  * @brief  Configure the PCD according to the specified
  *         parameters in the hal_pcd_handle_t and initialize the associated handle.
  * @param  hpcd PCD handler
  * @param  p_config pointer to the peripheral configuration structure
  * @retval HAL status
  */
hal_status_t HAL_PCD_SetConfig(hal_pcd_handle_t *hpcd, const hal_pcd_config_t *p_config)
{
  hal_status_t ret = HAL_OK;
  uint8_t ep_idx;
  usb_core_config_params_t usb_core_config = {0U};

  ASSERT_DBG_PARAM((hpcd != NULL));
  ASSERT_DBG_PARAM((p_config != NULL));

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1U)
  if ((hpcd == NULL) || (p_config == NULL))
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  ASSERT_DBG_STATE(hpcd->global_state, HAL_PCD_STATE_INIT);

  switch (hpcd->instance)
  {
    case HAL_PCD_OTG_FS:

      usb_core_config.phy_interface = (usb_core_phy_module_t)p_config->phy_interface;
      usb_core_config.endpoints_nbr = hpcd->endpoints_nbr;
      usb_core_config.core_speed = (usb_core_speed_t)p_config->pcd_speed;
      usb_core_config.vbus_sense_state = (usb_core_config_status_t)p_config->vbus_sensing_enable;
      usb_core_config.sof_state = (usb_core_config_status_t)p_config->sof_enable;
      usb_core_config.bcd_state = (usb_core_config_status_t)p_config->battery_charging_enable;
      break;

    default:
      break;
  }

  /* Prevent interrupts during USB device configuration */
  (void)hpcd->driver.core_disable_interrupts((uint32_t)hpcd->instance);

  /* Initialize the USB core */
  if (hpcd->driver.core_init((uint32_t)hpcd->instance, &usb_core_config) != USB_CORE_OK)
  {
    hpcd->global_state = HAL_PCD_STATE_FAULT;
    return HAL_ERROR;
  }

  /* Switch the USB core to device mode */
  if (hpcd->driver.core_set_mode((uint32_t)hpcd->instance, USB_CORE_DEVICE_MODE) != USB_CORE_OK)
  {
    hpcd->global_state = HAL_PCD_STATE_FAULT;
    ret = HAL_ERROR;
  }

  /* Init endpoints structures */
  for (ep_idx = 0U; ep_idx < USE_HAL_PCD_MAX_ENDPOINT_NB; ep_idx++)
  {
    /* Init ep structure */
    hpcd->in_ep[ep_idx].dir = HAL_PCD_EP_IN_DIR;
    hpcd->in_ep[ep_idx].num = (usb_core_endpoint_t)ep_idx;

    /* Control until ep is activated */
    hpcd->in_ep[ep_idx].type = USB_CORE_EP_TYPE_CTRL;
    hpcd->in_ep[ep_idx].max_packet = 0U;
    hpcd->in_ep[ep_idx].p_xfer_buffer = 0U;
    hpcd->in_ep[ep_idx].xfer_length = 0U;
  }

  for (ep_idx = 0U; ep_idx < USE_HAL_PCD_MAX_ENDPOINT_NB; ep_idx++)
  {
    hpcd->out_ep[ep_idx].dir = HAL_PCD_EP_OUT_DIR;
    hpcd->out_ep[ep_idx].num = (usb_core_endpoint_t)ep_idx;

    /* Control until ep is activated */
    hpcd->out_ep[ep_idx].type = USB_CORE_EP_TYPE_CTRL;
    hpcd->out_ep[ep_idx].max_packet = 0U;
    hpcd->out_ep[ep_idx].p_xfer_buffer = 0U;
    hpcd->out_ep[ep_idx].xfer_length = 0U;
  }

  /* Initialize device-specific registers and configuration */
  if (hpcd->driver.device_init((uint32_t)hpcd->instance, &usb_core_config) != USB_CORE_OK)
  {
    hpcd->global_state = HAL_PCD_STATE_FAULT;
    ret = HAL_ERROR;
  }

#if defined (USE_HAL_PCD_USB_LPM) && (USE_HAL_PCD_USB_LPM == 1)
  if (p_config->lpm_enable == HAL_PCD_LPM_ENABLED)
  {
    hpcd->driver.lpm_activate((uint32_t)hpcd->instance);
  }
#endif /* defined (USE_HAL_PCD_USB_LPM) && (USE_HAL_PCD_USB_LPM == 1) */

#if defined (USE_HAL_PCD_USB_BCD) && (USE_HAL_PCD_USB_BCD == 1)
  if (p_config->battery_charging_enable == HAL_PCD_BCD_ENABLED)
  {
    hpcd->driver.bcd_activate((uint32_t)hpcd->instance);
  }
#endif /* defined (USE_HAL_PCD_USB_BCD) && (USE_HAL_PCD_USB_BCD == 1) */

  hpcd->driver.device_disconnect((uint32_t)hpcd->instance);

  if (ret != HAL_ERROR)
  {
    hpcd->global_state = HAL_PCD_STATE_IDLE;
  }

  return ret;
}

/**
  * @}
  */

/** @addtogroup PCD_Exported_Functions_Group3 User Data functions
  * @{
 A set of functions allowing to manage a user data pointer stored to the PCD handle:
 - HAL_PCD_SetUserData() Set the user data into the handle
 - HAL_PCD_GetUserData() Get the user data from the handle
  */
#if defined (USE_HAL_PCD_USER_DATA) && (USE_HAL_PCD_USER_DATA == 1)
/**
  * @brief Set the user data pointer into the handle.
  * @param hpcd Pointer to a hal_pcd_handle_t
  * @param p_user_data Pointer to the user data.
  */
void HAL_PCD_SetUserData(hal_pcd_handle_t *hpcd, const void *p_user_data)
{
  ASSERT_DBG_PARAM((hpcd != NULL));

  hpcd->p_user_data = p_user_data;
}

/**
  * @brief Get the user data pointer from the handle.
  * @param hpcd Pointer to a hal_pcd_handle_t
  * @retval Pointer to the user data.
  */
const void *HAL_PCD_GetUserData(const hal_pcd_handle_t *hpcd)
{
  ASSERT_DBG_PARAM((hpcd != NULL));

  return (hpcd->p_user_data);
}
#endif /* USE_HAL_PCD_USER_DATA */

#if defined (USE_HAL_PCD_GET_LAST_ERRORS) && (USE_HAL_PCD_GET_LAST_ERRORS == 1)
/**
  * @brief Get Last Error codes.
  * @param hpcd Pointer to a hal_pcd_handle_t
  * @retval last error code.
  */
uint32_t HAL_PCD_GetLastErrorCodes(const hal_pcd_handle_t *hpcd)
{
  ASSERT_DBG_PARAM((hpcd != NULL));

  return (hpcd->last_error_codes);
}
#endif /* USE_HAL_PCD_GET_LAST_ERRORS */
/**
  * @}
  */

/** @addtogroup PCD_Exported_Functions_Group4 Peripheral Control functions
  * @{
  */
/**
  * @brief  Start the USB device.
  * @param  hpcd PCD handle
  * @retval HAL status
  */
hal_status_t HAL_PCD_Start(hal_pcd_handle_t *hpcd)
{
  ASSERT_DBG_PARAM((hpcd != NULL));

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1U)
  if (hpcd == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  ASSERT_DBG_STATE(hpcd->global_state, HAL_PCD_STATE_IDLE);
  HAL_CHECK_UPDATE_STATE(hpcd, global_state, HAL_PCD_STATE_IDLE, HAL_PCD_STATE_ACTIVE);

  hpcd->driver.device_start((uint32_t)hpcd->instance);

  return HAL_OK;
}

/**
  * @brief  Stop the USB device.
  * @param  hpcd PCD handle
  * @retval HAL status
  */
hal_status_t HAL_PCD_Stop(hal_pcd_handle_t *hpcd)
{
  ASSERT_DBG_PARAM((hpcd != NULL));

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1U)
  if (hpcd == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  ASSERT_DBG_STATE(hpcd->global_state, ((uint32_t)HAL_PCD_STATE_IDLE)
                   | ((uint32_t)HAL_PCD_STATE_ACTIVE));

  (void)hpcd->driver.core_disable_interrupts((uint32_t)hpcd->instance);
  (void)hpcd->driver.device_disconnect((uint32_t)hpcd->instance);
  (void)hpcd->driver.device_stop((uint32_t)hpcd->instance);

  hpcd->device_state = HAL_PCD_PORT_STATE_DEV_DISCONNECT;
  hpcd->global_state = HAL_PCD_STATE_IDLE;

  return HAL_OK;
}


#if defined (USE_HAL_PCD_USB_LPM) && (USE_HAL_PCD_USB_LPM == 1)
/**
  * @brief  Start LPM (low Power Management) feature.
  * @param  hpcd PCD handle
  * @retval HAL status
  */
hal_status_t HAL_PCD_LPM_Start(hal_pcd_handle_t *hpcd)
{
  ASSERT_DBG_PARAM((hpcd != NULL));

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1U)
  if (hpcd == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  ASSERT_DBG_STATE(hpcd->global_state, ((uint32_t)HAL_PCD_STATE_IDLE)
                   | ((uint32_t)HAL_PCD_STATE_ACTIVE));

  hpcd->driver.lpm_activate((uint32_t)hpcd->instance);
  hpcd->lpm_active = HAL_PCD_LPM_ENABLED;
  hpcd->lpm_state = HAL_PCD_LPM_STATE_L0;

  return HAL_OK;
}

/**
  * @brief  Stop LPM (low Power Management) feature.
  * @param  hpcd PCD handle
  * @retval HAL status
  */
hal_status_t HAL_PCD_LPM_Stop(hal_pcd_handle_t *hpcd)
{
  ASSERT_DBG_PARAM((hpcd != NULL));

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1U)
  if (hpcd == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  ASSERT_DBG_STATE(hpcd->global_state, ((uint32_t)HAL_PCD_STATE_IDLE)
                   | ((uint32_t)HAL_PCD_STATE_ACTIVE));

  hpcd->driver.lpm_deactivate((uint32_t)hpcd->instance);
  hpcd->lpm_active = HAL_PCD_LPM_DISABLED;

  return HAL_OK;
}
#endif /* defined (USE_HAL_PCD_USB_LPM) && (USE_HAL_PCD_USB_LPM == 1) */


#if defined (USE_HAL_PCD_USB_BCD) && (USE_HAL_PCD_USB_BCD == 1)

/**
  * @brief  Start Battery Charging feature.
  * @param  hpcd PCD handle
  * @retval HAL status
  */
hal_status_t HAL_PCD_BCD_Start(hal_pcd_handle_t *hpcd)
{
  ASSERT_DBG_PARAM((hpcd != NULL));

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1U)
  if (hpcd == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  ASSERT_DBG_STATE(hpcd->global_state, HAL_PCD_STATE_IDLE);

  hpcd->driver.bcd_activate((uint32_t)hpcd->instance);
  hpcd->battery_charging_active = HAL_PCD_BCD_ENABLED;

  return HAL_OK;
}

/**
  * @brief  Stop Battery Charging feature.
  * @param  hpcd PCD handle
  * @retval HAL status
  */
hal_status_t HAL_PCD_BCD_Stop(hal_pcd_handle_t *hpcd)
{
  ASSERT_DBG_PARAM((hpcd != NULL));

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1U)
  if (hpcd == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  ASSERT_DBG_STATE(hpcd->global_state, HAL_PCD_STATE_IDLE);

  hpcd->driver.bcd_deactivate((uint32_t)hpcd->instance);
  hpcd->battery_charging_active = HAL_PCD_BCD_DISABLED;

  return HAL_OK;
}

/**
  * @brief  Port Type Detection Process.
  * @param  hpcd PCD handle
  * @retval HAL status
  */
hal_status_t HAL_PCD_BCD_PortTypeDetection(hal_pcd_handle_t *hpcd)
{
  uint32_t tickstart = HAL_GetTick();
  uint32_t wait_start;
  hal_pcd_bcd_port_status_t port_type;

  ASSERT_DBG_PARAM((hpcd != NULL));

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1U)
  if (hpcd == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  ASSERT_DBG_STATE(hpcd->global_state, HAL_PCD_STATE_IDLE);

  /* Wait for Min DCD Timeout (T_DCD_TIMEOUT >= 300ms per USB BCD spec 1.2) */
  wait_start = HAL_GetTick();
  while ((HAL_GetTick() - wait_start) < 350U)
  {
    /* Busy-wait */
  }

  hpcd->driver.bcd_set_mode((uint32_t)hpcd->instance, USB_CORE_BCD_CONFIG_PD, USB_CORE_BCD_CONFIG_STS_SET);

  /* Wait for primary detection result to stabilize */
  wait_start = HAL_GetTick();
  while ((HAL_GetTick() - wait_start) < 50U)
  {
    /* Busy-wait */
  }

  /* Determine the detected BCD port type */
  port_type = (hal_pcd_bcd_port_status_t)hpcd->driver.bcd_detect_port_type((uint32_t)hpcd->instance,
                                                                           USB_CORE_BCD_PRIMARY_DETECTION);

  if (port_type == HAL_PCD_BCD_PORT_STATUS_STD_DOWNSTREAM)
  {
    /* Standard Downstream Port */
#if defined (USE_HAL_PCD_REGISTER_CALLBACKS) && (USE_HAL_PCD_REGISTER_CALLBACKS == 1U)
    hpcd->p_battery_charging_cb(hpcd, HAL_PCD_BCD_STD_DOWNSTREAM_PORT);
#else
    HAL_PCD_BcdCallback(hpcd, HAL_PCD_BCD_STD_DOWNSTREAM_PORT);
#endif /* USE_HAL_PCD_REGISTER_CALLBACKS */
  }
  else
  {
    /* Start BCD Secondary detection */
    hpcd->driver.bcd_set_mode((uint32_t)hpcd->instance, USB_CORE_BCD_CONFIG_PD, USB_CORE_BCD_CONFIG_STS_CLEAR);

    /* Wait for T_VDM_SRC_ON >= 40ms */
    wait_start = HAL_GetTick();
    while ((HAL_GetTick() - wait_start) < 50U)
    {
      /* Busy-wait */
    }

    hpcd->driver.bcd_set_mode((uint32_t)hpcd->instance, USB_CORE_BCD_CONFIG_SD, USB_CORE_BCD_CONFIG_STS_SET);

    /* Wait for secondary detection result to stabilize */
    wait_start = HAL_GetTick();
    while ((HAL_GetTick() - wait_start) < 50U)
    {
      /* Busy-wait */
    }

    /* Determine the detected BCD port type */
    port_type = (hal_pcd_bcd_port_status_t)hpcd->driver.bcd_detect_port_type((uint32_t)hpcd->instance,
                                                                             USB_CORE_BCD_SECONDARY_DETECTION);


    if (port_type == HAL_PCD_BCD_PORT_STATUS_DEDICATED_CHARGING)
    {
      /* Case Dedicated Charging Port  */
#if defined (USE_HAL_PCD_REGISTER_CALLBACKS) && (USE_HAL_PCD_REGISTER_CALLBACKS == 1U)
      hpcd->p_battery_charging_cb(hpcd, HAL_PCD_BCD_DEDICATED_CHARGING_PORT);
#else
      HAL_PCD_BcdCallback(hpcd, HAL_PCD_BCD_DEDICATED_CHARGING_PORT);
#endif /* USE_HAL_PCD_REGISTER_CALLBACKS */
    }
    else
    {
      /* Case Charging Downstream Port */
#if defined (USE_HAL_PCD_REGISTER_CALLBACKS) && (USE_HAL_PCD_REGISTER_CALLBACKS == 1U)
      hpcd->p_battery_charging_cb(hpcd, HAL_PCD_BCD_CHARGING_DOWNSTREAM_PORT);
#else
      HAL_PCD_BcdCallback(hpcd, HAL_PCD_BCD_CHARGING_DOWNSTREAM_PORT);
#endif /* USE_HAL_PCD_REGISTER_CALLBACKS */
    }
  }

  /* Battery Charging capability discovery finished */
  hpcd->driver.bcd_deactivate((uint32_t)hpcd->instance);
  hpcd->battery_charging_active = HAL_PCD_BCD_DISABLED;

  /* Check for the Timeout, else start USB Device */
  if ((HAL_GetTick() - tickstart) > 1000U)
  {
#if defined (USE_HAL_PCD_REGISTER_CALLBACKS) && (USE_HAL_PCD_REGISTER_CALLBACKS == 1U)
    hpcd->p_battery_charging_cb(hpcd, HAL_PCD_BCD_ERROR);
#else
    HAL_PCD_BcdCallback(hpcd, HAL_PCD_BCD_ERROR);
#endif /* USE_HAL_PCD_REGISTER_CALLBACKS */
  }
  else
  {
#if defined (USE_HAL_PCD_REGISTER_CALLBACKS) && (USE_HAL_PCD_REGISTER_CALLBACKS == 1U)
    hpcd->p_battery_charging_cb(hpcd, HAL_PCD_BCD_DISCOVERY_COMPLETED);
#else
    HAL_PCD_BcdCallback(hpcd, HAL_PCD_BCD_DISCOVERY_COMPLETED);
#endif /* USE_HAL_PCD_REGISTER_CALLBACKS */
  }

  return HAL_OK;
}
#endif /* defined (USE_HAL_PCD_USB_BCD) && (USE_HAL_PCD_USB_BCD == 1) */


/**
  * @brief  Connect the USB device.
  * @param  hpcd PCD handle
  * @retval HAL status
  */
hal_status_t HAL_PCD_DeviceConnect(const hal_pcd_handle_t *hpcd)
{
  ASSERT_DBG_PARAM((hpcd != NULL));

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1U)
  if (hpcd == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  ASSERT_DBG_STATE(hpcd->global_state, ((uint32_t)HAL_PCD_STATE_IDLE)
                   | ((uint32_t)HAL_PCD_STATE_ACTIVE));

  hpcd->driver.device_connect((uint32_t)hpcd->instance);

  return HAL_OK;
}

/**
  * @brief  Disconnect the USB device.
  * @param  hpcd PCD handle
  * @retval HAL status
  */
hal_status_t HAL_PCD_DeviceDisconnect(const hal_pcd_handle_t *hpcd)
{
  ASSERT_DBG_PARAM((hpcd != NULL));

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1U)
  if (hpcd == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  ASSERT_DBG_STATE(hpcd->global_state, ((uint32_t)HAL_PCD_STATE_IDLE)
                   | ((uint32_t)HAL_PCD_STATE_ACTIVE));

  (void)hpcd->driver.device_disconnect((uint32_t)hpcd->instance);

  return HAL_OK;
}

/**
  * @brief  Set the USB Device address.
  * @param  hpcd PCD handle
  * @param  address new device address
  * @retval HAL status
  */
hal_status_t HAL_PCD_SetDeviceAddress(hal_pcd_handle_t *hpcd, uint8_t address)
{
  ASSERT_DBG_PARAM((hpcd != NULL));

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1U)
  if (hpcd == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  ASSERT_DBG_STATE(hpcd->global_state, HAL_PCD_STATE_ACTIVE);
  ASSERT_DBG_STATE(hpcd->device_state, HAL_PCD_PORT_STATE_DEV_RUN);

  hpcd->usb_address = address;
  (void)hpcd->driver.device_set_address((uint32_t)hpcd->instance, address);

  return HAL_OK;
}

/**
  * @brief  Get the USB Device speed.
  * @param  hpcd PCD handle
  * @retval HAL status
  */
hal_pcd_device_speed_t HAL_PCD_GetDeviceSpeed(const hal_pcd_handle_t *hpcd)
{
  ASSERT_DBG_PARAM((hpcd != NULL));
  ASSERT_DBG_STATE(hpcd->global_state, HAL_PCD_STATE_ACTIVE);
  ASSERT_DBG_STATE(hpcd->device_state, HAL_PCD_PORT_STATE_DEV_RUN);

  return (hal_pcd_device_speed_t)hpcd->driver.device_get_speed((uint32_t)hpcd->instance);
}

/**
  * @brief  Open and configure an endpoint.
  * @param  hpcd PCD handle
  * @param  ep_addr endpoint address
  * @param  ep_mps endpoint max packet size
  * @param  ep_type endpoint type
  * @retval HAL status
  */
hal_status_t HAL_PCD_OpenEndpoint(hal_pcd_handle_t *hpcd, uint8_t ep_addr, uint16_t ep_mps, hal_pcd_ep_type_t ep_type)
{
  hal_pcd_ep_t *p_ep;
  uint8_t ep_num = ep_addr & HAL_PCD_EP_ADDR_MSK;

  ASSERT_DBG_PARAM((hpcd != NULL));
  ASSERT_DBG_PARAM((ep_num < (uint8_t)USE_HAL_PCD_MAX_ENDPOINT_NB));
  ASSERT_DBG_PARAM((HAL_PCD_CHECK_EP_TYPE(ep_type) != 0U));

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1U)
  if ((hpcd == NULL)
      || (ep_num >= ((uint8_t)USE_HAL_PCD_MAX_ENDPOINT_NB))
      || (HAL_PCD_CHECK_EP_TYPE(ep_type) == 0U))
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  ASSERT_DBG_STATE(hpcd->global_state, ((uint32_t)HAL_PCD_STATE_IDLE)
                   | ((uint32_t)HAL_PCD_STATE_ACTIVE));

  if ((ep_addr & USB_CORE_IN_EP_DIR_MSK) == USB_CORE_IN_EP_DIR_MSK)
  {
    hpcd->in_ep[ep_num].dir = HAL_PCD_EP_IN_DIR;
    p_ep = &hpcd->in_ep[ep_num];
  }
  else
  {
    hpcd->out_ep[ep_num].dir = HAL_PCD_EP_OUT_DIR;
    p_ep = &hpcd->out_ep[ep_num];
  }

  p_ep->num = (usb_core_endpoint_t)ep_num;
  p_ep->max_packet = (uint32_t)ep_mps & 0x7FFU;
  p_ep->type = (usb_core_ep_type_t)ep_type;

  (void)hpcd->driver.ep_activate((uint32_t)hpcd->instance, p_ep);

  return HAL_OK;
}

/**
  * @brief  Deactivate an endpoint.
  * @param  hpcd PCD handle
  * @param  ep_addr endpoint address
  * @retval HAL status
  */
hal_status_t HAL_PCD_CloseEndpoint(hal_pcd_handle_t *hpcd, uint8_t ep_addr)
{
  hal_pcd_ep_t *p_ep;
  uint8_t ep_num = ep_addr & HAL_PCD_EP_ADDR_MSK;

  ASSERT_DBG_PARAM((hpcd != NULL));
  ASSERT_DBG_PARAM((ep_num < (uint8_t)USE_HAL_PCD_MAX_ENDPOINT_NB));

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1U)
  if ((hpcd == NULL) || (ep_num >= ((uint8_t)USE_HAL_PCD_MAX_ENDPOINT_NB)))
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  ASSERT_DBG_STATE(hpcd->global_state, ((uint32_t)HAL_PCD_STATE_IDLE)
                   | ((uint32_t)HAL_PCD_STATE_ACTIVE));

  if ((ep_addr & USB_CORE_IN_EP_DIR_MSK) == USB_CORE_IN_EP_DIR_MSK)
  {
    hpcd->in_ep[ep_num].dir = HAL_PCD_EP_IN_DIR;
    p_ep = &hpcd->in_ep[ep_num];
  }
  else
  {
    hpcd->out_ep[ep_num].dir = HAL_PCD_EP_OUT_DIR;
    p_ep = &hpcd->out_ep[ep_num];
  }

  p_ep->num = (usb_core_endpoint_t)ep_num;

  (void)hpcd->driver.ep_deactivate((uint32_t)hpcd->instance, p_ep);

  return HAL_OK;
}


/**
  * @brief  Receive an amount of data.
  * @param  hpcd PCD handle
  * @param  ep_addr endpoint address
  * @param  p_buffer pointer to the reception buffer
  * @param  size_byte amount of data to be received
  * @retval HAL status
  */
hal_status_t HAL_PCD_SetEndpointReceive(hal_pcd_handle_t *hpcd, uint8_t ep_addr, uint8_t *p_buffer, uint32_t size_byte)
{
  hal_pcd_ep_t *p_ep;
  uint8_t ep_num = ep_addr & HAL_PCD_EP_ADDR_MSK;

  ASSERT_DBG_PARAM((hpcd != NULL));
  ASSERT_DBG_PARAM((ep_num < (uint8_t)USE_HAL_PCD_MAX_ENDPOINT_NB));

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1U)
  if ((hpcd == NULL) || (ep_num >= ((uint8_t)USE_HAL_PCD_MAX_ENDPOINT_NB)))
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  ASSERT_DBG_STATE(hpcd->global_state, ((uint32_t)HAL_PCD_STATE_IDLE)
                   | ((uint32_t)HAL_PCD_STATE_ACTIVE));

  hpcd->out_ep[ep_num].dir = HAL_PCD_EP_OUT_DIR;

  /* Get Endpoint OUT object address */
  p_ep = &hpcd->out_ep[ep_num];

  /* Configure the endpoint buffer and initiate the transfer */
  p_ep->p_xfer_buffer = p_buffer;
  p_ep->xfer_length = size_byte;
  p_ep->xfer_count = 0U;
  p_ep->num = (usb_core_endpoint_t)ep_num;

  p_ep = &hpcd->out_ep[ep_num];

  (void)hpcd->driver.ep_start_transfer((uint32_t)hpcd->instance, p_ep);

  return HAL_OK;
}

/**
  * @brief  Get Received Data Size.
  * @param  hpcd PCD handle
  * @param  ep_addr endpoint address
  * @retval Data Size
  */
uint32_t HAL_PCD_EP_GetRxCount(const hal_pcd_handle_t *hpcd, uint8_t ep_addr)
{
  uint16_t ep_num = (uint16_t)ep_addr & HAL_PCD_EP_ADDR_MSK;

  ASSERT_DBG_PARAM((hpcd != NULL));
  ASSERT_DBG_PARAM((ep_addr & USB_CORE_IN_EP_DIR_MSK) == 0x0U);
  ASSERT_DBG_PARAM((ep_num < (uint8_t)USE_HAL_PCD_MAX_ENDPOINT_NB));

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1U)
  if ((hpcd == NULL) || (ep_num >= ((uint8_t)USE_HAL_PCD_MAX_ENDPOINT_NB)))
  {
    return 0U;
  }
#endif /* USE_HAL_CHECK_PARAM */

  ASSERT_DBG_STATE(hpcd->global_state, HAL_PCD_STATE_ACTIVE);

  return hpcd->out_ep[ep_num].xfer_count;
}

/**
  * @brief  Get the current frame number cached on the last SOF interrupt.
  * @param  hpcd PCD handle
  * @retval Current frame number
  */
uint32_t HAL_PCD_GetCurrentFrame(const hal_pcd_handle_t *hpcd)
{
  ASSERT_DBG_PARAM((hpcd != NULL));

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1U)
  if (hpcd == NULL)
  {
    return 0U;
  }
#endif /* USE_HAL_CHECK_PARAM */

  return hpcd->frame_number;
}

/**
  * @brief  Send an amount of data.
  * @param  hpcd PCD handle
  * @param  ep_addr endpoint address
  * @param  p_buffer pointer to the transmission buffer
  * @param  size_byte amount of data to be sent
  * @retval HAL status
  */
hal_status_t HAL_PCD_SetEndpointTransmit(hal_pcd_handle_t *hpcd, uint8_t ep_addr, uint8_t *p_buffer, uint32_t size_byte)
{
  hal_pcd_ep_t *p_ep;
  uint8_t ep_num = ep_addr & HAL_PCD_EP_ADDR_MSK;

  ASSERT_DBG_PARAM((hpcd != NULL));
  ASSERT_DBG_PARAM((ep_num < (uint8_t)USE_HAL_PCD_MAX_ENDPOINT_NB));

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1U)
  if ((hpcd == NULL) || (ep_num >= ((uint8_t)USE_HAL_PCD_MAX_ENDPOINT_NB)))
  {
    return HAL_INVALID_PARAM;
  }

  if ((p_buffer == NULL) && (size_byte != 0U))
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  ASSERT_DBG_STATE(hpcd->global_state, ((uint32_t)HAL_PCD_STATE_IDLE)
                   | ((uint32_t)HAL_PCD_STATE_ACTIVE));

  hpcd->in_ep[ep_num].dir = HAL_PCD_EP_IN_DIR;

  p_ep = &hpcd->in_ep[ep_num];

  /* Configure the endpoint buffer and initiate the transfer */
  p_ep->p_xfer_buffer = p_buffer;
  p_ep->xfer_length = size_byte;
  p_ep->xfer_size = size_byte;
  p_ep->xfer_count = 0U;
  p_ep->num = (usb_core_endpoint_t)ep_num;

  (void)hpcd->driver.ep_start_transfer((uint32_t)hpcd->instance, p_ep);

  return HAL_OK;
}

/**
  * @brief  Set a STALL condition over an endpoint.
  * @param  hpcd PCD handle
  * @param  ep_addr endpoint address
  * @retval HAL status
  */
hal_status_t HAL_PCD_SetEndpointStall(hal_pcd_handle_t *hpcd, uint8_t ep_addr)
{
  hal_pcd_ep_t *p_ep;
  uint8_t ep_num = ep_addr & HAL_PCD_EP_ADDR_MSK;

  ASSERT_DBG_PARAM((hpcd != NULL));
  ASSERT_DBG_PARAM((ep_num < (uint8_t)USE_HAL_PCD_MAX_ENDPOINT_NB));

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1U)
  if ((hpcd == NULL) || (ep_num >= ((uint8_t)USE_HAL_PCD_MAX_ENDPOINT_NB)))
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  ASSERT_DBG_STATE(hpcd->global_state, ((uint32_t)HAL_PCD_STATE_IDLE)
                   | ((uint32_t)HAL_PCD_STATE_ACTIVE));

  if ((ep_addr & USB_CORE_IN_EP_DIR_MSK) == USB_CORE_IN_EP_DIR_MSK)
  {
    hpcd->in_ep[ep_num].dir = HAL_PCD_EP_IN_DIR;
    p_ep = &hpcd->in_ep[ep_num];
  }
  else
  {
    hpcd->out_ep[ep_num].dir = HAL_PCD_EP_OUT_DIR;
    p_ep = &hpcd->out_ep[ep_num];
  }

  p_ep->num = (usb_core_endpoint_t)ep_num;

  (void)hpcd->driver.ep_set_stall((uint32_t)hpcd->instance, p_ep);

  if (hpcd->driver.ep0_out_start != NULL)
  {
    if (ep_num == 0U)
    {
      (void)hpcd->driver.ep0_out_start((uint32_t)hpcd->instance, (uint8_t *)hpcd->setup);
    }
  }

  return HAL_OK;
}

/**
  * @brief  Clear a STALL condition over an endpoint.
  * @param  hpcd PCD handle
  * @param  ep_addr endpoint address
  * @retval HAL status
  */
hal_status_t HAL_PCD_ClearEndpointStall(hal_pcd_handle_t *hpcd, uint8_t ep_addr)
{
  hal_pcd_ep_t *p_ep;
  uint8_t ep_num = ep_addr & HAL_PCD_EP_ADDR_MSK;

  ASSERT_DBG_PARAM((hpcd != NULL));
  ASSERT_DBG_PARAM((ep_num < (uint8_t)USE_HAL_PCD_MAX_ENDPOINT_NB));

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1U)
  if ((hpcd == NULL) || (ep_num >= ((uint8_t)USE_HAL_PCD_MAX_ENDPOINT_NB)))
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  ASSERT_DBG_STATE(hpcd->global_state, ((uint32_t)HAL_PCD_STATE_IDLE)
                   | ((uint32_t)HAL_PCD_STATE_ACTIVE));

  if ((ep_addr & USB_CORE_IN_EP_DIR_MSK) == USB_CORE_IN_EP_DIR_MSK)
  {
    hpcd->in_ep[ep_num].dir = HAL_PCD_EP_IN_DIR;
    p_ep = &hpcd->in_ep[ep_num];
  }
  else
  {
    hpcd->out_ep[ep_num].dir = HAL_PCD_EP_OUT_DIR;
    p_ep = &hpcd->out_ep[ep_num];
  }

  p_ep->num = (usb_core_endpoint_t)ep_num;

  (void)hpcd->driver.ep_clear_stall((uint32_t)hpcd->instance, p_ep);

  return HAL_OK;
}

/**
   * @brief  Abort an USB endpoint transaction.
   * @param  hpcd PCD handle
   * @param  ep_addr endpoint address
   * @retval HAL status
   */
hal_status_t HAL_PCD_AbortEndpointTransfer(hal_pcd_handle_t *hpcd, uint8_t ep_addr)
{
  const hal_pcd_ep_t *p_ep;
  uint8_t ep_num = ep_addr & HAL_PCD_EP_ADDR_MSK;

  ASSERT_DBG_PARAM((hpcd != NULL));
  ASSERT_DBG_PARAM((ep_num < (uint8_t)USE_HAL_PCD_MAX_ENDPOINT_NB));

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1U)
  if ((hpcd == NULL) || (ep_num >= ((uint8_t)USE_HAL_PCD_MAX_ENDPOINT_NB)))
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  ASSERT_DBG_STATE(hpcd->global_state, ((uint32_t)HAL_PCD_STATE_IDLE)
                   | ((uint32_t)HAL_PCD_STATE_ACTIVE));

  if ((ep_addr & USB_CORE_IN_EP_DIR_MSK) == USB_CORE_IN_EP_DIR_MSK)
  {
    p_ep = &hpcd->in_ep[ep_num];
  }
  else
  {
    p_ep = &hpcd->out_ep[ep_num];
  }

  /* Abort any ongoing transfer on this endpoint */
  if (hpcd->driver.ep_stop_transfer((uint32_t)hpcd->instance, p_ep) != USB_CORE_OK)
  {
    return HAL_ERROR;
  }

#if defined (USE_HAL_PCD_REGISTER_CALLBACKS) && (USE_HAL_PCD_REGISTER_CALLBACKS == 1U)
  hpcd->p_ep_abort_transfer_cb(hpcd, ep_num);
#else
  HAL_PCD_EndpointAbortTransferCallback(hpcd, ep_num);
#endif /* USE_HAL_PCD_REGISTER_CALLBACKS */

  return HAL_OK;
}

/**
  * @brief  Flush an endpoint.
  * @param  hpcd PCD handle
  * @param  ep_addr endpoint address
  * @retval HAL status
  */
hal_status_t HAL_PCD_FlushEndpoint(const hal_pcd_handle_t *hpcd, uint8_t ep_addr)
{
  uint8_t ep_num = ep_addr & HAL_PCD_EP_ADDR_MSK;

  ASSERT_DBG_PARAM((hpcd != NULL));
  ASSERT_DBG_PARAM((ep_num < (uint8_t)USE_HAL_PCD_MAX_ENDPOINT_NB));

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1U)
  if ((hpcd == NULL) || (ep_num >= ((uint8_t)USE_HAL_PCD_MAX_ENDPOINT_NB)))
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  if ((ep_addr & USB_CORE_IN_EP_DIR_MSK) == USB_CORE_IN_EP_DIR_MSK)
  {
    if (hpcd->driver.flush_tx_fifo != NULL)
    {
      if (hpcd->driver.flush_tx_fifo((uint32_t)hpcd->instance, (uint32_t)ep_num) != USB_CORE_OK)
      {
        return HAL_ERROR;
      }
    }
  }
  else
  {
    if (hpcd->driver.flush_rx_fifo != NULL)
    {
      if (hpcd->driver.flush_rx_fifo((uint32_t)hpcd->instance) != USB_CORE_OK)
      {
        return HAL_ERROR;
      }
    }
  }

  return HAL_OK;
}

/**
  * @brief  Start remote wakeup signalling.
  * @param  hpcd PCD handle
  * @retval HAL status
  */
hal_status_t HAL_PCD_RemoteWakeup_Start(const hal_pcd_handle_t *hpcd)
{
  ASSERT_DBG_PARAM(hpcd != NULL);

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1U)
  if (hpcd == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  ASSERT_DBG_STATE(hpcd->global_state, ((uint32_t)HAL_PCD_STATE_IDLE)
                   | ((uint32_t)HAL_PCD_STATE_ACTIVE));

  (void)hpcd->driver.remote_wakeup_activate((uint32_t)hpcd->instance);

  return HAL_OK;
}

/**
  * @brief  Stop remote wakeup signalling.
  * @param  hpcd PCD handle
  * @retval HAL status
  */
hal_status_t HAL_PCD_RemoteWakeup_Stop(const hal_pcd_handle_t *hpcd)
{
  ASSERT_DBG_PARAM(hpcd != NULL);

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1U)
  if (hpcd == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  ASSERT_DBG_STATE(hpcd->global_state, ((uint32_t)HAL_PCD_STATE_IDLE)
                   | ((uint32_t)HAL_PCD_STATE_ACTIVE));

  (void)hpcd->driver.remote_wakeup_deactivate((uint32_t)hpcd->instance);

  return HAL_OK;
}

#if defined (USB_OTG_FS)
/**
  * @brief  Set Tx FIFO Size.
  * @param  hpcd PCD handle
  * @param  fifo number of Tx fifo
  * @param  size_words FIFO size in words
  * @retval HAL status
  */
hal_status_t HAL_PCD_SetTxFiFoSize(const hal_pcd_handle_t *hpcd, uint8_t fifo, uint16_t size_words)
{
  ASSERT_DBG_PARAM(hpcd != NULL);

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1U)
  if (hpcd == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  ASSERT_DBG_STATE(hpcd->global_state, ((uint32_t)HAL_PCD_STATE_IDLE)
                   | ((uint32_t)HAL_PCD_STATE_ACTIVE));

  hpcd->driver.set_tx_fifo((uint32_t)hpcd->instance, fifo, size_words);

  return HAL_OK;
}

/**
  * @brief  Set Rx FIFO Size.
  * @param  hpcd PCD handle
  * @param  size_words Size of Rx FIFO in words
  * @retval HAL status
  */
hal_status_t HAL_PCD_SetRxFiFoSize(const hal_pcd_handle_t *hpcd, uint16_t size_words)
{
  ASSERT_DBG_PARAM(hpcd != NULL);

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1U)
  if (hpcd == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  ASSERT_DBG_STATE(hpcd->global_state, ((uint32_t)HAL_PCD_STATE_IDLE)
                   | ((uint32_t)HAL_PCD_STATE_ACTIVE));

  hpcd->driver.set_rx_fifo((uint32_t)hpcd->instance, size_words);

  return HAL_OK;
}
#endif /* defined (USB_OTG_FS) */
/**
  * @}
  */

/** @addtogroup PCD_Exported_Functions_Group5 Peripheral State functions
  * @{
  */

/**
  * @brief  Return the PCD handle state.
  * @param  hpcd PCD handle
  * @retval HAL state
  */
hal_pcd_state_t HAL_PCD_GetState(const hal_pcd_handle_t *hpcd)
{
  ASSERT_DBG_PARAM((hpcd != NULL));

  return hpcd->global_state;
}

/**
  * @}
  */

/** @addtogroup PCD_Exported_Functions_Group6 IRQ handling functions
  * @{
  */
/**
  * @brief  Dispatch the PCD interrupt request.
  * @param  hpcd PCD handle
  */
void HAL_PCD_IRQHandler(hal_pcd_handle_t *hpcd)
{
  ASSERT_DBG_PARAM((hpcd != NULL));
  ASSERT_DBG_PARAM((hpcd->p_irq_handler != NULL));

  hpcd->current_mode = hpcd->driver.core_get_mode((uint32_t)hpcd->instance);

  hpcd->p_irq_handler(hpcd);
}


/**
  * @brief  Handles PCD interrupt request.
  * @param  hpcd PCD handle
  */
void HAL_PCD_OTG_IRQHandler(hal_pcd_handle_t *hpcd)
{
  usb_otg_global_t *p_usb;
  hal_pcd_ep_t *p_ep;
  uint32_t ep_idx;
  uint32_t ep_all_int;
  uint32_t ep_int;
  uint32_t ep_num;
  uint32_t fifo_empty_msk;
  uint32_t reg_value;
  uint32_t grxstsp_bcnt;
#if defined (USE_HAL_PCD_USB_EP_TYPE_ISOC) && (USE_HAL_PCD_USB_EP_TYPE_ISOC == 1)
  uint32_t frame_number;
#endif /* defined (USE_HAL_PCD_USB_EP_TYPE_ISOC) && (USE_HAL_PCD_USB_EP_TYPE_ISOC == 1) */

  ASSERT_DBG_PARAM((hpcd != NULL));

  p_usb = USB_OTG_GET_INSTANCE((uint32_t)hpcd->instance);

  /* Ensure that we are in device mode */
  if (hpcd->current_mode == USB_CORE_DEVICE_MODE)
  {
    /* Avoid spurious interrupt */
    if (USB_OTG_ReadInterrupts((uint32_t)p_usb) == 0U)
    {
      return;
    }

    if ((USB_OTG_ReadInterrupts((uint32_t)p_usb) & USB_OTG_GINTSTS_MMIS) == USB_OTG_GINTSTS_MMIS)
    {
      /* Incorrect mode, acknowledge the interrupt */
      USB_OTG_ClearInterrupts((uint32_t)p_usb, USB_OTG_GINTSTS_MMIS);
    }

    /* Handle RxQLevel Interrupt */
    if ((USB_OTG_ReadInterrupts((uint32_t)p_usb) & USB_OTG_GINTSTS_RXFLVL) == USB_OTG_GINTSTS_RXFLVL)
    {
      USB_OTG_MASK_IT(p_usb, USB_OTG_GINTSTS_RXFLVL);

      reg_value = p_usb->GRXSTSP;
      ep_num = (reg_value & USB_OTG_GRXSTSP_EPNUM);

      if (ep_num >= USE_HAL_PCD_MAX_ENDPOINT_NB)
      {
        USB_OTG_UNMASK_IT(p_usb, USB_OTG_GINTSTS_RXFLVL);
        return;
      }

      p_ep = &hpcd->out_ep[ep_num];

      if (((reg_value & USB_OTG_GRXSTSP_PKTSTS) >> 17) == (uint32_t)USB_OTG_STS_DATA_UPDT)
      {
        if ((reg_value & USB_OTG_GRXSTSP_BCNT) != 0U)
        {
          grxstsp_bcnt = (reg_value & USB_OTG_GRXSTSP_BCNT) >> 4;

          if (grxstsp_bcnt <= (p_ep->xfer_length - p_ep->xfer_count))
          {
            hpcd->driver.read_packet((uint32_t)p_usb, p_ep->p_xfer_buffer, p_ep->num, (uint16_t)grxstsp_bcnt);

            p_ep->p_xfer_buffer += grxstsp_bcnt;
            p_ep->xfer_count += grxstsp_bcnt;
          }
          else
          {
            /* Flush this packet and stall the EP */
            (void)USB_OTG_FlushRxFifo((uint32_t)p_usb);
            (void)hpcd->driver.ep_set_stall((uint32_t)hpcd->instance, p_ep);
          }
        }
      }
      else if (((reg_value & USB_OTG_GRXSTSP_PKTSTS) >> 17) == (uint32_t)USB_OTG_STS_SETUP_UPDT)
      {
        grxstsp_bcnt = (reg_value & USB_OTG_GRXSTSP_BCNT) >> 4;
        hpcd->driver.read_packet((uint32_t)p_usb, (uint8_t *)hpcd->setup, p_ep->num, 8U);
        p_ep->xfer_count += grxstsp_bcnt;
      }
      else
      {
        /* ... */
      }

      USB_OTG_UNMASK_IT(p_usb, USB_OTG_GINTSTS_RXFLVL);
    }

    if ((USB_OTG_ReadInterrupts((uint32_t)p_usb) & USB_OTG_GINTSTS_OEPINT) == USB_OTG_GINTSTS_OEPINT)
    {
      ep_num = 0U;

      /* Read in the device interrupt bits */
      ep_all_int = USB_OTG_ReadDevAllOutEpInterrupt((uint32_t)p_usb);

      while (ep_all_int != 0U)
      {
        if ((((ep_all_int & 0x1U) != 0U)) && (ep_num < USE_HAL_PCD_MAX_ENDPOINT_NB))
        {
          ep_int = USB_OTG_ReadDevOutEPInterrupt((uint32_t)p_usb, (uint8_t)ep_num);

          if ((ep_int & USB_OTG_DOEPINT_XFRC) == USB_OTG_DOEPINT_XFRC)
          {
            USB_OTG_OUT_EP_CLEAR_IT((uint32_t)hpcd->instance, ep_num, USB_OTG_DOEPINT_XFRC);
            (void)PCD_EP_OutXfrComplete_int(hpcd, ep_num);
          }

          if ((ep_int & USB_OTG_DOEPINT_STUP) == USB_OTG_DOEPINT_STUP)
          {
            USB_OTG_OUT_EP_CLEAR_IT((uint32_t)hpcd->instance, ep_num, USB_OTG_DOEPINT_STUP);
            /* Class B setup phase done for previous decoded setup */
            (void)PCD_EP_OutSetupPacket_int(hpcd, ep_num);
          }

          if ((ep_int & USB_OTG_DOEPINT_OTEPDIS) == USB_OTG_DOEPINT_OTEPDIS)
          {
            USB_OTG_OUT_EP_CLEAR_IT((uint32_t)hpcd->instance, ep_num, USB_OTG_DOEPINT_OTEPDIS);
          }

          /* Clear OUT Endpoint disable interrupt */
          if ((ep_int & USB_OTG_DOEPINT_EPDISD) == USB_OTG_DOEPINT_EPDISD)
          {
            if ((p_usb->GINTSTS & USB_OTG_GINTSTS_GONAKEFF) == USB_OTG_GINTSTS_GONAKEFF)
            {
              USB_OTG_DEVICE((uint32_t)hpcd->instance)->DCTL |= USB_OTG_DCTL_CGONAK;
            }

#if defined (USE_HAL_PCD_USB_EP_TYPE_ISOC) && (USE_HAL_PCD_USB_EP_TYPE_ISOC == 1)
            p_ep = &hpcd->out_ep[ep_num];

            if (p_ep->is_iso_incomplete == 1U)
            {
              p_ep->is_iso_incomplete = 0U;

#if defined (USE_HAL_PCD_REGISTER_CALLBACKS) && (USE_HAL_PCD_REGISTER_CALLBACKS == 1U)
              hpcd->p_iso_out_incomplete_cb(hpcd, (uint8_t)ep_num);
#else
              HAL_PCD_ISOOUTIncompleteCallback(hpcd, (uint8_t)ep_num);
#endif /* USE_HAL_PCD_REGISTER_CALLBACKS */
            }
#endif /* defined (USE_HAL_PCD_USB_EP_TYPE_ISOC) && (USE_HAL_PCD_USB_EP_TYPE_ISOC == 1) */

            USB_OTG_OUT_EP_CLEAR_IT((uint32_t)hpcd->instance, ep_num, USB_OTG_DOEPINT_EPDISD);
          }

          /* Clear Status Phase Received interrupt */
          if ((ep_int & USB_OTG_DOEPINT_STSPHSRX) == USB_OTG_DOEPINT_STSPHSRX)
          {
            USB_OTG_OUT_EP_CLEAR_IT((uint32_t)hpcd->instance, ep_num, USB_OTG_DOEPINT_STSPHSRX);
          }

          /* Clear OUT NAK interrupt */
          if ((ep_int & USB_OTG_DOEPINT_NAK) == USB_OTG_DOEPINT_NAK)
          {
            USB_OTG_OUT_EP_CLEAR_IT((uint32_t)hpcd->instance, ep_num, USB_OTG_DOEPINT_NAK);
          }
        }
        ep_num++;
        ep_all_int >>= 1U;
      }
    }

    if ((USB_OTG_ReadInterrupts((uint32_t)p_usb) & USB_OTG_GINTSTS_IEPINT) == USB_OTG_GINTSTS_IEPINT)
    {
      /* Read in the device interrupt bits */
      ep_all_int = USB_OTG_ReadDevAllInEpInterrupt((uint32_t)p_usb);

      ep_num = 0U;

      while (ep_all_int != 0U)
      {
        if ((((ep_all_int & 0x1U) != 0U)) && (ep_num < USE_HAL_PCD_MAX_ENDPOINT_NB)) /* In ITR */
        {
          ep_int = USB_OTG_ReadDevInEPInterrupt((uint32_t)p_usb, (uint8_t)ep_num);

          if ((ep_int & USB_OTG_DIEPINT_XFRC) == USB_OTG_DIEPINT_XFRC)
          {
            fifo_empty_msk = (uint32_t)(0x1UL << (ep_num & HAL_PCD_EP_ADDR_MSK));
            USB_OTG_DEVICE((uint32_t)hpcd->instance)->DIEPEMPMSK &= ~fifo_empty_msk;

            USB_OTG_IN_EP_CLEAR_IT((uint32_t)hpcd->instance, ep_num, USB_OTG_DIEPINT_XFRC);

#if defined (USE_HAL_PCD_REGISTER_CALLBACKS) && (USE_HAL_PCD_REGISTER_CALLBACKS == 1U)
            hpcd->p_data_in_stage_cb(hpcd, (uint8_t)ep_num);
#else
            HAL_PCD_DataInStageCallback(hpcd, (uint8_t)ep_num);
#endif /* USE_HAL_PCD_REGISTER_CALLBACKS */
          }
          if ((ep_int & USB_OTG_DIEPINT_TOC) == USB_OTG_DIEPINT_TOC)
          {
            USB_OTG_IN_EP_CLEAR_IT((uint32_t)hpcd->instance, ep_num, USB_OTG_DIEPINT_TOC);
          }
          if ((ep_int & USB_OTG_DIEPINT_ITTXFE) == USB_OTG_DIEPINT_ITTXFE)
          {
            USB_OTG_IN_EP_CLEAR_IT((uint32_t)hpcd->instance, ep_num, USB_OTG_DIEPINT_ITTXFE);
          }
          if ((ep_int & USB_OTG_DIEPINT_INEPNE) == USB_OTG_DIEPINT_INEPNE)
          {
            USB_OTG_IN_EP_CLEAR_IT((uint32_t)hpcd->instance, ep_num, USB_OTG_DIEPINT_INEPNE);
          }
          if ((ep_int & USB_OTG_DIEPINT_EPDISD) == USB_OTG_DIEPINT_EPDISD)
          {
            (void)USB_OTG_FlushTxFifo((uint32_t)p_usb, ep_num);

#if defined (USE_HAL_PCD_USB_EP_TYPE_ISOC) && (USE_HAL_PCD_USB_EP_TYPE_ISOC == 1)
            p_ep = &hpcd->in_ep[ep_num];

            if (p_ep->is_iso_incomplete == 1U)
            {
              p_ep->is_iso_incomplete = 0U;

#if defined (USE_HAL_PCD_REGISTER_CALLBACKS) && (USE_HAL_PCD_REGISTER_CALLBACKS == 1U)
              hpcd->p_iso_in_incomplete_cb(hpcd, (uint8_t)ep_num);
#else
              HAL_PCD_ISOINIncompleteCallback(hpcd, (uint8_t)ep_num);
#endif /* USE_HAL_PCD_REGISTER_CALLBACKS */
            }
#endif /* defined (USE_HAL_PCD_USB_EP_TYPE_ISOC) && (USE_HAL_PCD_USB_EP_TYPE_ISOC == 1) */

            USB_OTG_IN_EP_CLEAR_IT((uint32_t)hpcd->instance, ep_num, USB_OTG_DIEPINT_EPDISD);
          }
          if ((ep_int & USB_OTG_DIEPINT_TXFE) == USB_OTG_DIEPINT_TXFE)
          {
            (void)PCD_WriteEmptyTxFifo(hpcd, ep_num);
          }
        }
        ep_num++;
        ep_all_int >>= 1U;
      }
    }

    /* Handle Resume Interrupt */
    if ((USB_OTG_ReadInterrupts((uint32_t)p_usb) & USB_OTG_GINTSTS_WKUPINT) == USB_OTG_GINTSTS_WKUPINT)
    {
      /* Clear the Remote Wake-up Signaling */
      USB_OTG_DEVICE((uint32_t)hpcd->instance)->DCTL &= ~USB_OTG_DCTL_RWUSIG;

      hpcd->device_state = HAL_PCD_PORT_STATE_DEV_RUN;

#if defined (USE_HAL_PCD_USB_LPM) && (USE_HAL_PCD_USB_LPM == 1)
      if (hpcd->lpm_state == HAL_PCD_LPM_STATE_L1)
      {
        hpcd->lpm_state = HAL_PCD_LPM_STATE_L0;

#if defined (USE_HAL_PCD_REGISTER_CALLBACKS) && (USE_HAL_PCD_REGISTER_CALLBACKS == 1U)
        hpcd->p_low_power_management_cb(hpcd, HAL_PCD_LPM_L0_ACTIVE);
#else
        HAL_PCD_LpmCallback(hpcd, HAL_PCD_LPM_L0_ACTIVE);
#endif /* USE_HAL_PCD_REGISTER_CALLBACKS */
      }
      else
#endif /* defined (USE_HAL_PCD_USB_LPM) && (USE_HAL_PCD_USB_LPM == 1) */
      {
#if defined (USE_HAL_PCD_REGISTER_CALLBACKS) && (USE_HAL_PCD_REGISTER_CALLBACKS == 1U)
        hpcd->p_resume_cb(hpcd);
#else
        HAL_PCD_ResumeCallback(hpcd);
#endif /* USE_HAL_PCD_REGISTER_CALLBACKS */
      }

      USB_OTG_ClearInterrupts((uint32_t)p_usb, USB_OTG_GINTSTS_WKUPINT);
    }

    /* Handle Suspend Interrupt */
    if ((USB_OTG_ReadInterrupts((uint32_t)p_usb) & USB_OTG_GINTSTS_USBSUSP) == USB_OTG_GINTSTS_USBSUSP)
    {
      if ((USB_OTG_DEVICE((uint32_t)hpcd->instance)->DSTS & USB_OTG_DSTS_SUSPSTS) == USB_OTG_DSTS_SUSPSTS)
      {
        hpcd->device_state = HAL_PCD_PORT_STATE_DEV_SUSPEND;

#if defined (USE_HAL_PCD_REGISTER_CALLBACKS) && (USE_HAL_PCD_REGISTER_CALLBACKS == 1U)
        hpcd->p_suspend_cb(hpcd);
#else
        HAL_PCD_SuspendCallback(hpcd);
#endif /* USE_HAL_PCD_REGISTER_CALLBACKS */
      }
      USB_OTG_ClearInterrupts((uint32_t)p_usb, USB_OTG_GINTSTS_USBSUSP);
    }

#if defined (USE_HAL_PCD_USB_LPM) && (USE_HAL_PCD_USB_LPM == 1)
    /* Handle LPM (low Power Management) Interrupt */
    if ((USB_OTG_ReadInterrupts((uint32_t)p_usb) & USB_OTG_GINTSTS_LPMINT) == USB_OTG_GINTSTS_LPMINT)
    {
      USB_OTG_ClearInterrupts((uint32_t)p_usb, USB_OTG_GINTSTS_LPMINT);

      if (hpcd->lpm_state == HAL_PCD_LPM_STATE_L0)
      {
        hpcd->lpm_state = HAL_PCD_LPM_STATE_L1;
        hpcd->lpm_besl = (p_usb->GLPMCFG & USB_OTG_GLPMCFG_BESL) >> 2U;

#if defined (USE_HAL_PCD_REGISTER_CALLBACKS) && (USE_HAL_PCD_REGISTER_CALLBACKS == 1U)
        hpcd->p_low_power_management_cb(hpcd, HAL_PCD_LPM_L1_ACTIVE);
#else
        HAL_PCD_LpmCallback(hpcd, HAL_PCD_LPM_L1_ACTIVE);
#endif /* USE_HAL_PCD_REGISTER_CALLBACKS */
      }
      else
      {
#if defined (USE_HAL_PCD_REGISTER_CALLBACKS) && (USE_HAL_PCD_REGISTER_CALLBACKS == 1U)
        hpcd->p_suspend_cb(hpcd);
#else
        HAL_PCD_SuspendCallback(hpcd);
#endif /* USE_HAL_PCD_REGISTER_CALLBACKS */
      }
    }
#endif /* defined (USE_HAL_PCD_USB_LPM) && (USE_HAL_PCD_USB_LPM == 1) */

    /* Handle Reset Interrupt */
    if ((USB_OTG_ReadInterrupts((uint32_t)p_usb) & USB_OTG_GINTSTS_USBRST) == USB_OTG_GINTSTS_USBRST)
    {
      USB_OTG_DEVICE((uint32_t)hpcd->instance)->DCTL &= ~USB_OTG_DCTL_RWUSIG;
      (void)USB_OTG_FlushTxFifo((uint32_t)p_usb, 0x10U);

      for (ep_idx = 0U; ep_idx < hpcd->endpoints_nbr; ep_idx++)
      {
        USB_OTG_IN_EP((uint32_t)hpcd->instance, ep_idx)->DIEPINT = 0xFB7FU;
        USB_OTG_IN_EP((uint32_t)hpcd->instance, ep_idx)->DIEPCTL &= ~USB_OTG_DIEPCTL_STALL;
        USB_OTG_OUT_EP((uint32_t)hpcd->instance, ep_idx)->DOEPINT = 0xFB7FU;
        USB_OTG_OUT_EP((uint32_t)hpcd->instance, ep_idx)->DOEPCTL &= ~USB_OTG_DOEPCTL_STALL;
        USB_OTG_OUT_EP((uint32_t)hpcd->instance, ep_idx)->DOEPCTL |= USB_OTG_DOEPCTL_SNAK;
      }

      USB_OTG_DEVICE((uint32_t)hpcd->instance)->DAINTMSK |= 0x10001U;

      USB_OTG_DEVICE((uint32_t)hpcd->instance)->DOEPMSK |= USB_OTG_DOEPMSK_STUPM
                                                           | USB_OTG_DOEPMSK_XFRCM
                                                           | USB_OTG_DOEPMSK_EPDM
                                                           | USB_OTG_DOEPMSK_STSPHSRXM
                                                           | USB_OTG_DOEPMSK_NAKM;

      USB_OTG_DEVICE((uint32_t)hpcd->instance)->DIEPMSK |= USB_OTG_DIEPMSK_TOM
                                                           | USB_OTG_DIEPMSK_XFRCM
                                                           | USB_OTG_DIEPMSK_EPDM;

      /* Set Default Address to 0 */
      USB_OTG_DEVICE((uint32_t)hpcd->instance)->DCFG &= ~USB_OTG_DCFG_DAD;

      /* Setup EP0 to receive SETUP packets */
      (void)USB_OTG_StartOutEP0((uint32_t)p_usb, (uint8_t *)hpcd->setup);

      hpcd->device_state = HAL_PCD_PORT_STATE_DEV_RESET;

      USB_OTG_ClearInterrupts((uint32_t)p_usb, USB_OTG_GINTSTS_USBRST);
    }

    /* Handle Enumeration done Interrupt */
    if ((USB_OTG_ReadInterrupts((uint32_t)p_usb) & USB_OTG_GINTSTS_ENUMDNE) == USB_OTG_GINTSTS_ENUMDNE)
    {
      hpcd->device_state = HAL_PCD_PORT_STATE_DEV_RUN;
      (void) USB_OTG_ActivateSetup((uint32_t)p_usb);

      /* Set USB Turnaround time */
      (void)USB_OTG_SetTurnaroundTime((uint32_t)p_usb, HAL_RCC_GetHCLKFreq(),
                                      USB_OTG_GetDeviceSpeed((uint32_t)p_usb));

#if defined (USE_HAL_PCD_REGISTER_CALLBACKS) && (USE_HAL_PCD_REGISTER_CALLBACKS == 1U)
      hpcd->p_reset_cb(hpcd);
#else
      HAL_PCD_ResetCallback(hpcd);
#endif /* USE_HAL_PCD_REGISTER_CALLBACKS */

      USB_OTG_ClearInterrupts((uint32_t)p_usb, USB_OTG_GINTSTS_ENUMDNE);
    }

    /* Handle SOF Interrupt */
    if ((USB_OTG_ReadInterrupts((uint32_t)p_usb) & USB_OTG_GINTSTS_SOF) == USB_OTG_GINTSTS_SOF)
    {
      /* Store current frame number */
      hpcd->frame_number = USB_OTG_GetDeviceCurrentFrame((uint32_t)hpcd->instance);

#if defined (USE_HAL_PCD_REGISTER_CALLBACKS) && (USE_HAL_PCD_REGISTER_CALLBACKS == 1U)
      hpcd->p_sof_cb(hpcd);
#else
      HAL_PCD_SofCallback(hpcd);
#endif /* USE_HAL_PCD_REGISTER_CALLBACKS */

      USB_OTG_ClearInterrupts((uint32_t)p_usb, USB_OTG_GINTSTS_SOF);
    }

    /* Handle Global OUT NAK effective Interrupt */
    if ((USB_OTG_ReadInterrupts((uint32_t)p_usb) & USB_OTG_GINTSTS_GONAKEFF) == USB_OTG_GINTSTS_GONAKEFF)
    {
      p_usb->GINTMSK &= ~USB_OTG_GINTMSK_GONAKEFFM;

#if defined (USE_HAL_PCD_USB_EP_TYPE_ISOC) && (USE_HAL_PCD_USB_EP_TYPE_ISOC == 1)
      for (ep_idx = 1U; ep_idx < USE_HAL_PCD_MAX_ENDPOINT_NB; ep_idx++)
      {
        if (hpcd->out_ep[ep_idx].is_iso_incomplete == 1U)
        {
          /* Disable the endpoint */
          USB_OTG_OUT_EP((uint32_t)hpcd->instance, ep_idx)->DOEPCTL |= (USB_OTG_DOEPCTL_SNAK);
          USB_OTG_OUT_EP((uint32_t)hpcd->instance, ep_idx)->DOEPCTL |= (USB_OTG_DOEPCTL_EPDIS);
        }
      }
#endif /* defined (USE_HAL_PCD_USB_EP_TYPE_ISOC) && (USE_HAL_PCD_USB_EP_TYPE_ISOC == 1) */
    }

#if defined (USE_HAL_PCD_USB_EP_TYPE_ISOC) && (USE_HAL_PCD_USB_EP_TYPE_ISOC == 1)
    /* Handle Incomplete ISO IN Interrupt */
    if ((USB_OTG_ReadInterrupts((uint32_t)p_usb) & USB_OTG_GINTSTS_IISOIXFR) == USB_OTG_GINTSTS_IISOIXFR)
    {
      for (ep_idx = 1U; ep_idx < PCD_MIN(hpcd->endpoints_nbr, (uint8_t)USE_HAL_PCD_MAX_ENDPOINT_NB); ep_idx++)
      {
        reg_value = USB_OTG_IN_EP((uint32_t)hpcd->instance, ep_idx)->DIEPCTL;

        if ((hpcd->in_ep[ep_idx].type == USB_CORE_EP_TYPE_ISOC)
            && ((reg_value & USB_OTG_DIEPCTL_EPENA) == USB_OTG_DIEPCTL_EPENA))
        {
          hpcd->in_ep[ep_idx].is_iso_incomplete = 1U;

          /* Abort current transaction and disable the endpoint */
          (void)hpcd->driver.ep_stop_transfer((uint32_t)hpcd->instance, &hpcd->in_ep[ep_idx]);
        }
      }

      USB_OTG_ClearInterrupts((uint32_t)p_usb, USB_OTG_GINTSTS_IISOIXFR);
    }

    /* Handle Incomplete ISO OUT Interrupt */
    if ((USB_OTG_ReadInterrupts((uint32_t)p_usb) & USB_OTG_GINTSTS_INCOMPISOOUT) == USB_OTG_GINTSTS_INCOMPISOOUT)
    {
      /* Store current frame number */
      frame_number = (USB_OTG_DEVICE(hpcd->instance)->DSTS & USB_OTG_DSTS_FNSOF_Msk) >> USB_OTG_DSTS_FNSOF_Pos;

      for (ep_idx = 1U; ep_idx < PCD_MIN(hpcd->endpoints_nbr, (uint8_t)USE_HAL_PCD_MAX_ENDPOINT_NB); ep_idx++)
      {
        reg_value = USB_OTG_OUT_EP(hpcd->instance, ep_idx)->DOEPCTL;

        if ((hpcd->out_ep[ep_idx].type == USB_CORE_EP_TYPE_ISOC)
            && ((reg_value & USB_OTG_DOEPCTL_EPENA) == USB_OTG_DOEPCTL_EPENA)
            && (((reg_value & (0x1UL << 16)) >> 16U) == (frame_number & 0x1U)))
        {
          hpcd->out_ep[ep_idx].is_iso_incomplete = 1U;

          p_usb->GINTMSK |= USB_OTG_GINTMSK_GONAKEFFM;

          if ((p_usb->GINTSTS & USB_OTG_GINTSTS_GONAKEFF) == 0U)
          {
            USB_OTG_DEVICE((uint32_t)hpcd->instance)->DCTL |= USB_OTG_DCTL_SGONAK;
            break;
          }
        }
      }

      USB_OTG_ClearInterrupts((uint32_t)p_usb, USB_OTG_GINTSTS_INCOMPISOOUT);
    }
#endif /* defined (USE_HAL_PCD_USB_EP_TYPE_ISOC) && (USE_HAL_PCD_USB_EP_TYPE_ISOC == 1) */

    /* Handle Connection event Interrupt */
    if ((USB_OTG_ReadInterrupts((uint32_t)p_usb) & USB_OTG_GINTSTS_SRQINT) == USB_OTG_GINTSTS_SRQINT)
    {
      hpcd->device_state = HAL_PCD_PORT_STATE_DEV_CONNECT;

#if defined (USE_HAL_PCD_REGISTER_CALLBACKS) && (USE_HAL_PCD_REGISTER_CALLBACKS == 1U)
      hpcd->p_connect_cb(hpcd);
#else
      HAL_PCD_ConnectCallback(hpcd);
#endif /* USE_HAL_PCD_REGISTER_CALLBACKS */

      USB_OTG_ClearInterrupts((uint32_t)p_usb, USB_OTG_GINTSTS_SRQINT);
    }

    /* Handle Disconnection event Interrupt */
    if ((USB_OTG_ReadInterrupts((uint32_t)p_usb) & USB_OTG_GINTSTS_OTGINT) == USB_OTG_GINTSTS_OTGINT)
    {
      reg_value = p_usb->GOTGINT;

      if ((reg_value & USB_OTG_GOTGINT_SEDET) == USB_OTG_GOTGINT_SEDET)
      {
        hpcd->device_state = HAL_PCD_PORT_STATE_DEV_DISCONNECT;

#if defined (USE_HAL_PCD_REGISTER_CALLBACKS) && (USE_HAL_PCD_REGISTER_CALLBACKS == 1U)
        hpcd->p_disconnect_cb(hpcd);
#else
        HAL_PCD_DisconnectCallback(hpcd);
#endif /* USE_HAL_PCD_REGISTER_CALLBACKS */
      }
      p_usb->GOTGINT |= reg_value;
    }
  }
}

/**
  * @}
  */

/** @addtogroup PCD_Exported_Functions_Group7 Default Callbacks functions
  * @{
  */
/**
  * @brief  Send LPM (low Power Management) active status to user layer callback.
  * @param  hpcd PCD handle
  * @param  lpm_status LPM active status
  */
__WEAK void HAL_PCD_LpmCallback(hal_pcd_handle_t *hpcd, hal_pcd_lpm_active_status_t lpm_status)
{
  /* Prevent unused argument(s) compilation warning */
  STM32_UNUSED(hpcd);
  STM32_UNUSED(lpm_status);

  /* WARNING : This function must not be modified, when the callback is needed,
            the HAL_PCD_LpmCallback could be implemented in the user file
   */
}

/**
  * @brief  Send BatteryCharging port type to user layer callback.
  * @param  hpcd PCD handle
  * @param  port_type port type
  */
__WEAK void HAL_PCD_BcdCallback(hal_pcd_handle_t *hpcd, hal_pcd_bcd_port_type_t port_type)
{
  /* Prevent unused argument(s) compilation warning */
  STM32_UNUSED(hpcd);
  STM32_UNUSED(port_type);

  /* WARNING : This function must not be modified, when the callback is needed,
            the HAL_PCD_BcdCallback could be implemented in the user file
   */
}

/**
  * @brief  Data OUT stage callback.
  * @param  hpcd PCD handle
  * @param  ep_num endpoint number
  */
__WEAK void HAL_PCD_DataOutStageCallback(hal_pcd_handle_t *hpcd, uint8_t ep_num)
{
  /* Prevent unused argument(s) compilation warning */
  STM32_UNUSED(hpcd);
  STM32_UNUSED(ep_num);

  /* WARNING : This function must not be modified, when the callback is needed,
            the HAL_PCD_DataOutStageCallback could be implemented in the user file
   */
}

/**
  * @brief  Data IN stage callback.
  * @param  hpcd PCD handle
  * @param  ep_num endpoint number
  */
__WEAK void HAL_PCD_DataInStageCallback(hal_pcd_handle_t *hpcd, uint8_t ep_num)
{
  /* Prevent unused argument(s) compilation warning */
  STM32_UNUSED(hpcd);
  STM32_UNUSED(ep_num);

  /* WARNING : This function must not be modified, when the callback is needed,
            the HAL_PCD_DataInStageCallback could be implemented in the user file
   */
}
/**
  * @brief  Setup stage callback.
  * @param  hpcd PCD handle
  */
__WEAK void HAL_PCD_SetupStageCallback(hal_pcd_handle_t *hpcd)
{
  /* Prevent unused argument(s) compilation warning */
  STM32_UNUSED(hpcd);

  /* WARNING : This function must not be modified, when the callback is needed,
            the HAL_PCD_SetupStageCallback could be implemented in the user file
   */
}

/**
  * @brief  USB Start Of Frame callback.
  * @param  hpcd PCD handle
  */
__WEAK void HAL_PCD_SofCallback(hal_pcd_handle_t *hpcd)
{
  /* Prevent unused argument(s) compilation warning */
  STM32_UNUSED(hpcd);

  /* WARNING : This function must not be modified, when the callback is needed,
            the HAL_PCD_SofCallback could be implemented in the user file
   */
}

/**
  * @brief  USB Reset callback.
  * @param  hpcd PCD handle
  */
__WEAK void HAL_PCD_ResetCallback(hal_pcd_handle_t *hpcd)
{
  /* Prevent unused argument(s) compilation warning */
  STM32_UNUSED(hpcd);

  /* WARNING : This function must not be modified, when the callback is needed,
            the HAL_PCD_ResetCallback could be implemented in the user file
   */
}

/**
  * @brief  Suspend event callback.
  * @param  hpcd PCD handle
  */
__WEAK void HAL_PCD_SuspendCallback(hal_pcd_handle_t *hpcd)
{
  /* Prevent unused argument(s) compilation warning */
  STM32_UNUSED(hpcd);

  /* WARNING : This function must not be modified, when the callback is needed,
            the HAL_PCD_SuspendCallback could be implemented in the user file
   */
}

/**
  * @brief  Resume event callback.
  * @param  hpcd PCD handle
  */
__WEAK void HAL_PCD_ResumeCallback(hal_pcd_handle_t *hpcd)
{
  /* Prevent unused argument(s) compilation warning */
  STM32_UNUSED(hpcd);

  /* WARNING : This function must not be modified, when the callback is needed,
            the HAL_PCD_ResumeCallback could be implemented in the user file
   */
}

/**
  * @brief  Incomplete ISO OUT callback.
  * @param  hpcd PCD handle
  * @param  ep_num endpoint number
  */
__WEAK void HAL_PCD_ISOOUTIncompleteCallback(hal_pcd_handle_t *hpcd, uint8_t ep_num)
{
  /* Prevent unused argument(s) compilation warning */
  STM32_UNUSED(hpcd);
  STM32_UNUSED(ep_num);

  /* WARNING : This function must not be modified, when the callback is needed,
            the HAL_PCD_ISOOUTIncompleteCallback could be implemented in the user file
   */
}

/**
  * @brief  Incomplete ISO IN callback.
  * @param  hpcd PCD handle
  * @param  ep_num endpoint number
  */
__WEAK void HAL_PCD_ISOINIncompleteCallback(hal_pcd_handle_t *hpcd, uint8_t ep_num)
{
  /* Prevent unused argument(s) compilation warning */
  STM32_UNUSED(hpcd);
  STM32_UNUSED(ep_num);

  /* WARNING : This function must not be modified, when the callback is needed,
            the HAL_PCD_ISOINIncompleteCallback could be implemented in the user file
   */
}

/**
  * @brief  Connection event callback.
  * @param  hpcd PCD handle
  */
__WEAK void HAL_PCD_ConnectCallback(hal_pcd_handle_t *hpcd)
{
  /* Prevent unused argument(s) compilation warning */
  STM32_UNUSED(hpcd);

  /* WARNING : This function must not be modified, when the callback is needed,
            the HAL_PCD_ConnectCallback could be implemented in the user file
   */
}

/**
  * @brief  Disconnection event callback.
  * @param  hpcd PCD handle
  */
__WEAK void HAL_PCD_DisconnectCallback(hal_pcd_handle_t *hpcd)
{
  /* Prevent unused argument(s) compilation warning */
  STM32_UNUSED(hpcd);

  /* WARNING : This function must not be modified, when the callback is needed,
            the HAL_PCD_DisconnectCallback could be implemented in the user file
   */
}

/**
  * @brief  PCD Error callback.
  * @param  hpcd PCD handle
  */
__WEAK void HAL_PCD_ErrorCallback(hal_pcd_handle_t *hpcd)
{
  /* Prevent unused argument(s) compilation warning */
  STM32_UNUSED(hpcd);

  /* WARNING : This function must not be modified, when the callback is needed,
            the HAL_PCD_ErrorCallback could be implemented in the user file
   */
}

/**
  * @brief  PCD Endpoint Abort Transfer callback.
  * @param  hpcd PCD handle
  * @param  ep_num endpoint number
  */
__WEAK void HAL_PCD_EndpointAbortTransferCallback(hal_pcd_handle_t *hpcd, uint8_t ep_num)
{
  /* Prevent unused argument(s) compilation warning */
  STM32_UNUSED(hpcd);
  STM32_UNUSED(ep_num);

  /* WARNING : This function must not be modified, when the callback is needed,
            the HAL_PCD_EndpointAbortTransferCallback could be implemented in the user file
   */
}

/**
  * @}
  */

/** @addtogroup PCD_Exported_Functions_Group8 Register Callbacks functions
  * @{
  */
#if defined (USE_HAL_PCD_REGISTER_CALLBACKS) && (USE_HAL_PCD_REGISTER_CALLBACKS == 1U)
/**
  * @brief  Register USB PCD SOF callback
  *         To be used instead of the weak predefined callback.
  * @param  hpcd USB PCD handle
  * @param  p_callback pointer to the SOF callback function
  * @retval HAL status
  */
hal_status_t HAL_PCD_RegisterSofCallback(hal_pcd_handle_t *hpcd, hal_pcd_cb_t p_callback)
{
  ASSERT_DBG_PARAM((hpcd != NULL));
  ASSERT_DBG_PARAM((p_callback != NULL));

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1U)
  if ((hpcd == NULL) || (p_callback == NULL))
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  hpcd->p_sof_cb = p_callback;

  return HAL_OK;
}

/**
  * @brief  Register a USB PCD Setup callback
  *         To be used instead of the weak predefined callback.
  * @param  hpcd USB PCD handle
  * @param  p_callback pointer to the Setup callback function
  * @retval HAL status
  */
hal_status_t HAL_PCD_RegisterSetupCallback(hal_pcd_handle_t *hpcd, hal_pcd_cb_t p_callback)
{
  ASSERT_DBG_PARAM((hpcd != NULL));
  ASSERT_DBG_PARAM((p_callback != NULL));

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1U)
  if ((hpcd == NULL) || (p_callback == NULL))
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  hpcd->p_setup_stage_cb = p_callback;

  return HAL_OK;
}

/**
  * @brief  Register a USB PCD Reset callback
  *         To be used instead of the weak predefined callback.
  * @param  hpcd USB PCD handle
  * @param  p_callback pointer to the Reset callback function
  * @retval HAL status
  */
hal_status_t HAL_PCD_RegisterResetCallback(hal_pcd_handle_t *hpcd, hal_pcd_cb_t p_callback)
{
  ASSERT_DBG_PARAM((hpcd != NULL));
  ASSERT_DBG_PARAM((p_callback != NULL));

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1U)
  if ((hpcd == NULL) || (p_callback == NULL))
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  hpcd->p_reset_cb = p_callback;

  return HAL_OK;
}

/**
  * @brief  Register a USB PCD Suspend callback
  *         To be used instead of the weak predefined callback.
  * @param  hpcd USB PCD handle
  * @param  p_callback pointer to the Suspend callback function
  * @retval HAL status
  */
hal_status_t HAL_PCD_RegisterSuspendCallback(hal_pcd_handle_t *hpcd, hal_pcd_cb_t p_callback)
{
  ASSERT_DBG_PARAM((hpcd != NULL));
  ASSERT_DBG_PARAM((p_callback != NULL));

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1U)
  if ((hpcd == NULL) || (p_callback == NULL))
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  hpcd->p_suspend_cb = p_callback;

  return HAL_OK;
}

/**
  * @brief  Register a USB PCD Resume callback
  *         To be used instead of the weak predefined callback.
  * @param  hpcd USB PCD handle
  * @param  p_callback pointer to the Resume callback function
  * @retval HAL status
  */
hal_status_t HAL_PCD_RegisterResumeCallback(hal_pcd_handle_t *hpcd, hal_pcd_cb_t p_callback)
{
  ASSERT_DBG_PARAM((hpcd != NULL));
  ASSERT_DBG_PARAM((p_callback != NULL));

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1U)
  if ((hpcd == NULL) || (p_callback == NULL))
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  hpcd->p_resume_cb = p_callback;

  return HAL_OK;
}

/**
  * @brief  Register a USB PCD Connect callback
  *         To be used instead of the weak predefined callback.
  * @param  hpcd USB PCD handle
  * @param  p_callback pointer to the Connect callback function
  * @retval HAL status
  */
hal_status_t HAL_PCD_RegisterConnectCallback(hal_pcd_handle_t *hpcd, hal_pcd_cb_t p_callback)
{
  ASSERT_DBG_PARAM((hpcd != NULL));
  ASSERT_DBG_PARAM((p_callback != NULL));

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1U)
  if ((hpcd == NULL) || (p_callback == NULL))
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  hpcd->p_connect_cb = p_callback;

  return HAL_OK;
}

/**
  * @brief  Register a USB PCD Disconnect callback
  *         To be used instead of the weak predefined callback.
  * @param  hpcd USB PCD handle
  * @param  p_callback pointer to the Disconnect callback function
  * @retval HAL status
  */
hal_status_t HAL_PCD_RegisterDisconnectCallback(hal_pcd_handle_t *hpcd, hal_pcd_cb_t p_callback)
{
  ASSERT_DBG_PARAM((hpcd != NULL));
  ASSERT_DBG_PARAM((p_callback != NULL));

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1U)
  if ((hpcd == NULL) || (p_callback == NULL))
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  hpcd->p_disconnect_cb = p_callback;

  return HAL_OK;
}

/**
  * @brief  Register USB PCD Data OUT Stage callback
  *         To be used instead of the weak HAL_PCD_DataOutStageCallback() predefined callback.
  * @param  hpcd PCD handle
  * @param  p_callback pointer to the USB PCD Data OUT Stage callback function
  * @retval HAL status
  */
hal_status_t HAL_PCD_RegisterDataOutStageCallback(hal_pcd_handle_t *hpcd, hal_pcd_data_cb_t p_callback)
{
  ASSERT_DBG_PARAM((hpcd != NULL));
  ASSERT_DBG_PARAM((p_callback != NULL));

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1U)
  if ((hpcd == NULL) || (p_callback == NULL))
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  hpcd->p_data_out_stage_cb = p_callback;

  return HAL_OK;
}

/**
  * @brief  Register USB PCD Data IN Stage callback
  *         To be used instead of the weak HAL_PCD_DataInStageCallback() predefined callback.
  * @param  hpcd PCD handle
  * @param  p_callback pointer to the USB PCD Data IN Stage callback function
  * @retval HAL status
  */
hal_status_t HAL_PCD_RegisterDataInStageCallback(hal_pcd_handle_t *hpcd, hal_pcd_data_cb_t p_callback)
{
  ASSERT_DBG_PARAM((hpcd != NULL));
  ASSERT_DBG_PARAM((p_callback != NULL));

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1U)
  if ((hpcd == NULL) || (p_callback == NULL))
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  hpcd->p_data_in_stage_cb = p_callback;

  return HAL_OK;
}

/**
  * @brief  Register USB PCD Iso OUT incomplete callback
  *         To be used instead of the weak HAL_PCD_ISOOUTIncompleteCallback() predefined callback.
  * @param  hpcd PCD handle
  * @param  p_callback pointer to the USB PCD Iso OUT incomplete callback function
  * @retval HAL status
  */
hal_status_t HAL_PCD_RegisterIsoOutIncpltCallback(hal_pcd_handle_t *hpcd, hal_pcd_iso_cb_t p_callback)
{
  ASSERT_DBG_PARAM((hpcd != NULL));
  ASSERT_DBG_PARAM((p_callback != NULL));

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1U)
  if ((hpcd == NULL) || (p_callback == NULL))
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  hpcd->p_iso_out_incomplete_cb = p_callback;

  return HAL_OK;
}

/**
  * @brief  Register USB PCD Iso IN incomplete callback
  *         To be used instead of the weak HAL_PCD_ISOINIncompleteCallback() predefined callback.
  * @param  hpcd PCD handle
  * @param  p_callback pointer to the USB PCD Iso IN incomplete callback function
  * @retval HAL status
  */
hal_status_t HAL_PCD_RegisterIsoInIncpltCallback(hal_pcd_handle_t *hpcd, hal_pcd_iso_cb_t p_callback)
{
  ASSERT_DBG_PARAM((hpcd != NULL));
  ASSERT_DBG_PARAM((p_callback != NULL));

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1U)
  if ((hpcd == NULL) || (p_callback == NULL))
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  hpcd->p_iso_in_incomplete_cb = p_callback;

  return HAL_OK;
}

/**
  * @brief  Register USB PCD Error callback
  *         To be used instead of the weak HAL_PCD_ErrorCallback() predefined callback.
  * @param  hpcd PCD handle
  * @param  p_callback pointer to the USB PCD Error callback function
  * @retval HAL status
  */
hal_status_t HAL_PCD_RegisterErrorCallback(hal_pcd_handle_t *hpcd, hal_pcd_cb_t p_callback)
{
  ASSERT_DBG_PARAM((hpcd != NULL));
  ASSERT_DBG_PARAM((p_callback != NULL));

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1U)
  if ((hpcd == NULL) || (p_callback == NULL))
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  hpcd->p_error_cb = p_callback;

  return HAL_OK;
}

/**
  * @brief  Register USB PCD Endpoint Abort Transfer callback
  *         To be used instead of the weak HAL_PCD_EndpointAbortTransferCallback() predefined callback.
  * @param  hpcd PCD handle
  * @param  p_callback pointer to the USB PCD Endpoint Abort Transfer callback function
  * @retval HAL status
  */
hal_status_t HAL_PCD_RegisterEndpointAbortTransferCallback(hal_pcd_handle_t *hpcd, hal_pcd_data_cb_t p_callback)
{
  ASSERT_DBG_PARAM((hpcd != NULL));
  ASSERT_DBG_PARAM((p_callback != NULL));

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1U)
  if ((hpcd == NULL) || (p_callback == NULL))
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  hpcd->p_ep_abort_transfer_cb = p_callback;

  return HAL_OK;
}

/**
  * @brief  Register USB PCD BCD callback
  *         To be used instead of the weak HAL_PCD_BcdCallback() predefined callback.
  * @param  hpcd PCD handle
  * @param  p_callback pointer to the USB PCD BCD callback function
  * @retval HAL status
  */
hal_status_t HAL_PCD_RegisterBcdCallback(hal_pcd_handle_t *hpcd, hal_pcd_bcd_cb_t p_callback)
{
  ASSERT_DBG_PARAM((hpcd != NULL));
  ASSERT_DBG_PARAM((p_callback != NULL));

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1U)
  if ((hpcd == NULL) || (p_callback == NULL))
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  hpcd->p_battery_charging_cb = p_callback;

  return HAL_OK;
}

/**
  * @brief  Register USB PCD LPM callback
  *         To be used instead of the weak HAL_PCD_LpmCallback() predefined callback.
  * @param  hpcd PCD handle
  * @param  p_callback pointer to the USB PCD LPM callback function
  * @retval HAL status
  */
hal_status_t HAL_PCD_RegisterLpmCallback(hal_pcd_handle_t *hpcd, hal_pcd_lpm_cb_t p_callback)
{
  ASSERT_DBG_PARAM((hpcd != NULL));
  ASSERT_DBG_PARAM((p_callback != NULL));

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1U)
  if ((hpcd == NULL) || (p_callback == NULL))
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  hpcd->p_low_power_management_cb = p_callback;

  return HAL_OK;
}
#endif /* USE_HAL_PCD_REGISTER_CALLBACKS */

/**
  * @}
  */

/**
  * @}
  */

/* Private functions ---------------------------------------------------------*/
/** @addtogroup PCD_Private_Functions
  * @{
  */
#if defined (USB_OTG_FS)
/**
  * @brief  Check FIFO for the next packet to be loaded.
  * @param  hpcd PCD handle
  * @param  ep_num endpoint number
  * @retval HAL status
  */
static hal_status_t PCD_WriteEmptyTxFifo(hal_pcd_handle_t *hpcd, uint32_t ep_num)
{
  const usb_otg_global_t *p_usb;
  hal_pcd_ep_t *p_ep;
  uint32_t length;
  uint32_t len32b;
  uint32_t fifoemptymsk;

  p_ep = &hpcd->in_ep[ep_num];

  p_usb = USB_OTG_GET_INSTANCE((uint32_t)hpcd->instance);

  if (p_ep->xfer_count > p_ep->xfer_length)
  {
    return HAL_ERROR;
  }

  length = p_ep->xfer_length - p_ep->xfer_count;

  if (length > p_ep->max_packet)
  {
    length = p_ep->max_packet;
  }

  len32b = (length + 3U) / 4U;

  while (((USB_OTG_IN_EP((uint32_t)hpcd->instance, ep_num)->DTXFSTS & USB_OTG_DTXFSTS_INEPTFSAV) >= len32b)
         && (p_ep->xfer_count < p_ep->xfer_length) && (p_ep->xfer_length != 0U))
  {
    /* Write the FIFO */
    length = p_ep->xfer_length - p_ep->xfer_count;

    if (length > p_ep->max_packet)
    {
      length = p_ep->max_packet;
    }

    len32b = (length + 3U) / 4U;

    (void)hpcd->driver.write_packet((uint32_t)p_usb, p_ep->p_xfer_buffer, (uint8_t)ep_num, length);

    p_ep->p_xfer_buffer  += length;
    p_ep->xfer_count += length;
  }

  if (p_ep->xfer_length <= p_ep->xfer_count)
  {
    fifoemptymsk = (uint32_t)(0x1UL << (ep_num & HAL_PCD_EP_ADDR_MSK));
    USB_OTG_DEVICE((uint32_t)hpcd->instance)->DIEPEMPMSK &= ~fifoemptymsk;
  }

  return HAL_OK;
}


/**
  * @brief  process endpoint OUT transfer complete interrupt.
  * @param  hpcd PCD handle
  * @param  ep_num endpoint number
  * @retval HAL status
  */
static hal_status_t PCD_EP_OutXfrComplete_int(hal_pcd_handle_t *hpcd, uint32_t ep_num)
{
#if defined (USE_HAL_PCD_REGISTER_CALLBACKS) && (USE_HAL_PCD_REGISTER_CALLBACKS == 1U)
  hpcd->p_data_out_stage_cb(hpcd, (uint8_t)ep_num);
#else
  HAL_PCD_DataOutStageCallback(hpcd, (uint8_t)ep_num);
#endif /* USE_HAL_PCD_REGISTER_CALLBACKS */

  return HAL_OK;
}


/**
  * @brief  process endpoint OUT setup packet received interrupt.
  * @param  hpcd PCD handle
  * @param  ep_num endpoint number
  * @retval HAL status
  */
static hal_status_t PCD_EP_OutSetupPacket_int(hal_pcd_handle_t *hpcd, uint32_t ep_num)
{
  uint32_t doepint_reg;

  doepint_reg = USB_OTG_OUT_EP((uint32_t)hpcd->instance, ep_num)->DOEPINT;

  if ((doepint_reg & USB_OTG_DOEPINT_STPKTRX) == USB_OTG_DOEPINT_STPKTRX)
  {
    USB_OTG_OUT_EP_CLEAR_IT((uint32_t)hpcd->instance, ep_num, USB_OTG_DOEPINT_STPKTRX);
  }

  /* Inform the upper layer that a setup packet is available */
#if defined (USE_HAL_PCD_REGISTER_CALLBACKS) && (USE_HAL_PCD_REGISTER_CALLBACKS == 1U)
  hpcd->p_setup_stage_cb(hpcd);
#else
  HAL_PCD_SetupStageCallback(hpcd);
#endif /* USE_HAL_PCD_REGISTER_CALLBACKS */


  return HAL_OK;
}
#endif /* defined (USB_OTG_FS) */


/**
  * @}
  */

/**
  * @}
  */

#endif /* defined (USE_HAL_PCD_MODULE) && (USE_HAL_PCD_MODULE == 1) */
#endif /* defined (USB_OTG_FS) */

/**
  * @}
  */
