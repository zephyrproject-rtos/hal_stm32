/**
  ******************************************************************************
  * @file    stm32c5xx_usb_core_def.h
  * @brief   Header file for the USB CORE driver module.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef STM32C5xx_USB_CORE_DEF_H
#define STM32C5xx_USB_CORE_DEF_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Exported functions --------------------------------------------------------*/
__STATIC_INLINE uint32_t USB_CORE_MIN_U32(uint32_t value1, uint32_t value2)
{
  return (value1 < value2) ? value1 : value2;
}

__STATIC_INLINE uint32_t USB_CORE_MAX_U32(uint32_t value1, uint32_t value2)
{
  return (value1 > value2) ? value1 : value2;
}

/* Private constants ---------------------------------------------------------*/
#ifndef USB_CORE_CURRENT_MODE_MAX_DELAY_CYCLES
#define USB_CORE_CURRENT_MODE_MAX_DELAY_CYCLES        (200U * (SystemCoreClock / 1000U))
#endif /* USB_CORE_CURRENT_MODE_MAX_DELAY_CYCLES */

#define USB_CORE_IN_EP_DIR_MSK                (0x80U)    /*!< IN Endpoint Direction Mask */

/**
  * @brief  USB CORE Status structures definition
  */
typedef enum
{
  USB_CORE_OK    = 0x00000000U,   /*!< USB CORE operation completed successfully */
  USB_CORE_ERROR = 0xFFFFFFFFU,   /*!< USB CORE operation completed with error   */
} usb_core_status_t;


/**
  * @brief  USB CORE configuration state definition
  */
typedef enum
{
  USB_CORE_CONFIG_DISABLED = 0x0U,               /*!< USB CORE config state disabled: 0 */
  USB_CORE_CONFIG_ENABLED  = 0x1U,               /*!< USB CORE config state enabled:  1 */
} usb_core_config_status_t;


/**
  * @brief  USB CORE mode definition
  */
typedef enum
{
  USB_CORE_DEVICE_MODE = 0x00U,                  /*!< USB CORE Device Mode */
  USB_CORE_HOST_MODE   = 0x01U,                  /*!< USB CORE Host Mode   */
} usb_core_mode_t;

/**
  * @brief  USB CORE Speed definition
  */
typedef enum
{
  USB_CORE_SPEED_FS = 0x01U,                     /*!< USB CORE SPEED FULL         */
} usb_core_speed_t;


/**
  * @brief  USB CORE Device Speed definition
  */
typedef enum
{
  USB_CORE_DEVICE_SPEED_LS = 0x00U,              /*!< USB CORE DEVICE SPEED LOW   */
  USB_CORE_DEVICE_SPEED_FS = 0x01U,              /*!< USB CORE DEVICE SPEED FULL  */
  USB_CORE_DEVICE_SPEED_HS = 0x02U,              /*!< USB CORE DEVICE SPEED HIGH  */
  USB_CORE_DEVICE_SPEED_ERROR = 0xFFU,           /*!< USB CORE DEVICE SPEED ERROR */
} usb_core_device_speed_t;


/**
  * @brief  USB CORE Host Port Speed definition
  */
typedef enum
{
  USB_CORE_PORT_SPEED_HS = 0x00U,                /*!< USB CORE Host Port SPEED HIGH */
  USB_CORE_PORT_SPEED_FS = 0x01U,                /*!< USB CORE Host Port SPEED FULL */
  USB_CORE_PORT_SPEED_LS = 0x02U,                /*!< USB CORE Host Port SPEED LOW  */
} usb_core_port_speed_t;


/**
  * @brief  USB CORE PHY Module definition
  */
typedef enum
{
  USB_CORE_PHY_EXTERNAL_ULPI = 0x1U,             /*!< PCD PHY ULPI     */
  USB_CORE_PHY_EMBEDDED_FS   = 0x2U,             /*!< PCD PHY EMBEDDED */
  USB_CORE_PHY_EMBEDDED_HS   = 0x3U,             /*!< PCD PHY UTMI     */
} usb_core_phy_module_t;


/**
  * @brief  USB  EP Type structure definition
  */
typedef enum
{
  USB_CORE_EP_TYPE_CTRL = 0x00U,
  USB_CORE_EP_TYPE_ISOC = 0x01U,
  USB_CORE_EP_TYPE_BULK = 0x02U,
  USB_CORE_EP_TYPE_INTR = 0x03U,
} usb_core_ep_type_t;


/**
  * @brief  USB CORE Endpoint Direction definition
  */
typedef enum
{
  USB_CORE_EP_OUT_DIR = 0x00U,                   /*!< USB CORE Endpoint OUT DIR: 0 */
  USB_CORE_EP_IN_DIR  = 0x01U,                   /*!< USB CORE Endpoint IN DIR:  1 */
} usb_core_ep_direction_t;


/**
  * @brief  USB CORE BCD Detection structure definition
  */
typedef enum
{
  USB_CORE_BCD_PRIMARY_DETECTION   = 0x01U,
  USB_CORE_BCD_SECONDARY_DETECTION = 0x02U,
} usb_core_bcd_detection_t;


/**
  * @brief  USB CORE BCD port status structure definition
  */
typedef enum
{
  USB_CORE_BCD_PORT_STATUS_DEFAULT             = 0x00U,     /*!< USB CORE BCD Default BCD Status Port  */
  USB_CORE_BCD_PORT_STATUS_NOT_STD_DOWNSTREAM  = 0x01U,     /*!< USB CORE BCD NOT STD Downstream Port  */
  USB_CORE_BCD_PORT_STATUS_STD_DOWNSTREAM      = 0x02U,     /*!< USB CORE BCD STD Downstream Port      */
  USB_CORE_BCD_PORT_STATUS_DEDICATED_CHARGING  = 0x03U,     /*!< USB CORE BCD Dedicated Charging Port  */
  USB_CORE_BCD_PORT_STATUS_CHARGING_DOWNSTREAM = 0x04U,     /*!< USB CORE BCD Charging Downstream Port */
} usb_core_bcd_port_status_t;


/**
  * @brief  USB CORE BCD mode structure definition
  */
typedef enum
{
  USB_CORE_BCD_CONFIG_DCD = 0x00U,    /*!< USB CORE BCD Data Contact Detection */
  USB_CORE_BCD_CONFIG_PD = 0x01U,     /*!< USB CORE BCD Primary Detection      */
  USB_CORE_BCD_CONFIG_SD = 0x02U,     /*!< USB CORE BCD Secondary Detection    */
} usb_core_bcd_config_t;


/**
  * @brief  USB CORE BCD status structure definition
  */
typedef enum
{
  USB_CORE_BCD_CONFIG_STS_CLEAR = 0x00U,   /*!< USB CORE BCD mode cleared */
  USB_CORE_BCD_CONFIG_STS_SET = 0x01U,     /*!< USB CORE BCD mode set     */
} usb_core_bcd_config_sts_t;


/**
  * @brief USB CORE Endpoint identifier definition
  */
typedef enum
{
  USB_CORE_ENDPOINT_0  = 0U,     /*!< USB CORE ENDPOINT 0  */
  USB_CORE_ENDPOINT_1  = 1U,     /*!< USB CORE ENDPOINT 1  */
  USB_CORE_ENDPOINT_2  = 2U,     /*!< USB CORE ENDPOINT 2  */
  USB_CORE_ENDPOINT_3  = 3U,     /*!< USB CORE ENDPOINT 3  */
  USB_CORE_ENDPOINT_4  = 4U,     /*!< USB CORE ENDPOINT 4  */
  USB_CORE_ENDPOINT_5  = 5U,     /*!< USB CORE ENDPOINT 5  */
  USB_CORE_ENDPOINT_6  = 6U,     /*!< USB CORE ENDPOINT 6  */
  USB_CORE_ENDPOINT_7  = 7U,     /*!< USB CORE ENDPOINT 7  */
  USB_CORE_ENDPOINT_8  = 8U,     /*!< USB CORE ENDPOINT 8  */
  USB_CORE_ENDPOINT_9  = 9U,     /*!< USB CORE ENDPOINT 9  */
  USB_CORE_ENDPOINT_10 = 10U,    /*!< USB CORE ENDPOINT 10 */
  USB_CORE_ENDPOINT_11 = 11U,    /*!< USB CORE ENDPOINT 11 */
  USB_CORE_ENDPOINT_12 = 12U,    /*!< USB CORE ENDPOINT 12 */
  USB_CORE_ENDPOINT_13 = 13U,    /*!< USB CORE ENDPOINT 13 */
  USB_CORE_ENDPOINT_14 = 14U,    /*!< USB CORE ENDPOINT 14 */
  USB_CORE_ENDPOINT_15 = 15U,    /*!< USB CORE ENDPOINT 15 */
  USB_CORE_ENDPOINT_FF = 0xFFU,  /*!< USB CORE ENDPOINT FF */
} usb_core_endpoint_t;


/**
  * @brief USB CORE CHEP identifier definition
  */
typedef enum
{
  USB_CORE_PHY_CHEP_0  = 0U,      /*!< USB CORE PHYSICAL CHANNEL/ENDPOINT 0  */
  USB_CORE_PHY_CHEP_1  = 1U,      /*!< USB CORE PHYSICAL CHANNEL/ENDPOINT 1  */
  USB_CORE_PHY_CHEP_2  = 2U,      /*!< USB CORE PHYSICAL CHANNEL/ENDPOINT 2  */
  USB_CORE_PHY_CHEP_3  = 3U,      /*!< USB CORE PHYSICAL CHANNEL/ENDPOINT 3  */
  USB_CORE_PHY_CHEP_4  = 4U,      /*!< USB CORE PHYSICAL CHANNEL/ENDPOINT 4  */
  USB_CORE_PHY_CHEP_5  = 5U,      /*!< USB CORE PHYSICAL CHANNEL/ENDPOINT 5  */
  USB_CORE_PHY_CHEP_6  = 6U,      /*!< USB CORE PHYSICAL CHANNEL/ENDPOINT 6  */
  USB_CORE_PHY_CHEP_7  = 7U,      /*!< USB CORE PHYSICAL CHANNEL/ENDPOINT 7  */
  USB_CORE_PHY_CHEP_FF = 0xFFU,   /*!< USB CORE ERROR FF                     */
} usb_core_phy_chep_t;

typedef usb_core_phy_chep_t usb_core_phy_ch_t;
typedef usb_core_phy_chep_t usb_core_phy_ep_t;


/**
  * @brief  USB CORE Host Port reset definition
  */
typedef enum
{
  USB_CORE_PORT_RESET_STS_CLEAR = 0U,    /*!< USB CORE Clear Port Reset */
  USB_CORE_PORT_RESET_STS_SET  = 1U,     /*!< USB CORE Set Port Reset   */
} usb_core_port_reset_sts_t;


/**
  * @brief  USB CORE Port Resume status definition
  */
typedef enum
{
  USB_CORE_PORT_RESUME_STS_CLEAR = 0x00U,   /*!< USB CORE Port Resume status cleared */
  USB_CORE_PORT_RESUME_STS_SET = 0x01U,     /*!< USB CORE Port Resume status set     */
} usb_core_port_resume_sts_t;

/**
  * @brief  USB CORE Channel PID Type definition
  */
typedef enum
{
  USB_CORE_CH_PID_DATA0 = 0x00U,     /*!< USB CORE HC PID DATA0    */
  USB_CORE_CH_PID_DATA2 = 0x01U,     /*!< USB CORE HC PID DATA2    */
  USB_CORE_CH_PID_DATA1 = 0x02U,     /*!< USB CORE HC PID DATA1    */
  USB_CORE_CH_PID_SETUP = 0x03U,     /*!< USB CORE HC PID SETUP    */
} usb_core_ch_pid_type_t;


/**
  * @brief  USB CORE Host Channel Direction definition
  */
typedef enum
{
  USB_CORE_CH_OUT_DIR = USB_CORE_EP_OUT_DIR,      /*!< USB CORE CH OUT DIR: 0 */
  USB_CORE_CH_IN_DIR  = USB_CORE_EP_IN_DIR,       /*!< USB CORE CH IN DIR:  1 */
} usb_core_ch_direction_t;


/**
  * @brief USB CORE CHANNEL identifier definition
  */
typedef enum
{
  USB_CORE_CHANNEL_0  = 0U,    /*!< USB CORE CHANNEL 0  */
  USB_CORE_CHANNEL_1  = 1U,    /*!< USB CORE CHANNEL 1  */
  USB_CORE_CHANNEL_2  = 2U,    /*!< USB CORE CHANNEL 2  */
  USB_CORE_CHANNEL_3  = 3U,    /*!< USB CORE CHANNEL 3  */
  USB_CORE_CHANNEL_4  = 4U,    /*!< USB CORE CHANNEL 4  */
  USB_CORE_CHANNEL_5  = 5U,    /*!< USB CORE CHANNEL 5  */
  USB_CORE_CHANNEL_6  = 6U,    /*!< USB CORE CHANNEL 6  */
  USB_CORE_CHANNEL_7  = 7U,    /*!< USB CORE CHANNEL 7  */
  USB_CORE_CHANNEL_8  = 8U,    /*!< USB CORE CHANNEL 8  */
  USB_CORE_CHANNEL_9  = 9U,    /*!< USB CORE CHANNEL 9  */
  USB_CORE_CHANNEL_10 = 10U,   /*!< USB CORE CHANNEL 10 */
  USB_CORE_CHANNEL_11 = 11U,   /*!< USB CORE CHANNEL 11 */
  USB_CORE_CHANNEL_12 = 12U,   /*!< USB CORE CHANNEL 12 */
  USB_CORE_CHANNEL_13 = 13U,   /*!< USB CORE CHANNEL 13 */
  USB_CORE_CHANNEL_14 = 14U,   /*!< USB CORE CHANNEL 14 */
  USB_CORE_CHANNEL_15 = 15U,   /*!< USB CORE CHANNEL 15 */
  USB_CORE_CHANNEL_FF = 0xFFU, /*!< USB CORE CHANNEL FF */
} usb_core_channel_t;


/**
  * @brief USB CORE Config Params definition
  */
typedef struct
{
  uint8_t endpoints_nbr;
  uint8_t channels_nbr;
  usb_core_phy_module_t phy_interface;
  usb_core_speed_t core_speed;
  usb_core_config_status_t dma_state;
  usb_core_config_status_t sof_state;
  usb_core_config_status_t bcd_state;
  usb_core_config_status_t vbus_sense_state;
  usb_core_config_status_t iso_db_state;
  usb_core_config_status_t bulk_db_state;
} usb_core_config_params_t;


/**
  * @brief  PCD Endpoint Structure definition
  */
typedef struct
{
  usb_core_endpoint_t num;           /*!< Endpoint number
                                          This parameter must be a number between Min_Data = 0 and Max_Data = 15      */

  usb_core_ep_direction_t dir;       /*!< Endpoint direction
                                          This parameter store the physical channel direction IN/OUT                  */

  usb_core_ep_type_t type;           /*!< Endpoint type
                                          This parameter can be any value of @ref usb_core_ep_type_t                  */

  uint32_t max_packet;               /*!< Endpoint Max packet size                                                    */

  uint32_t xfer_length;              /*!< Current transfer length                                                     */

  uint32_t xfer_count;               /*!< Partial transfer length in case of multi packet transfer                    */

  uint8_t *p_xfer_buffer;            /*!< Pointer to transfer buffer                                                  */

  uint32_t xfer_size;                /*!< Requested transfer size                                                     */

  uint16_t pma_address;              /*!< PMA Address
                                          This parameter can be any value between Min_addr = 0 and Max_addr = 1K      */

  uint16_t pma_addr0;                /*!< PMA Address0
                                          This parameter can be any value between Min_addr = 0 and Max_addr = 1K      */

  uint16_t pma_addr1;                /*!< PMA Address1
                                          This parameter can be any value between Min_addr = 0 and Max_addr = 1K      */

  uint8_t double_buffer_en;          /*!< Double buffer enable
                                          This parameter can be 0 or 1                                                */

  uint8_t xfer_fill_db;              /*!< double buffer Need to Fill new buffer  used with bulk_in                    */
} usb_core_ep_t;


/**
  * @brief  USB Instance Host Channel Structure definition
  */
typedef struct
{
  usb_core_phy_ch_t phy_ch_num;       /*!< Host physical channel number
                                           This parameter must be a number between Min_Data = 0 and Max_Data = 15     */

  usb_core_channel_t ch_num;          /*!< Host channel number
                                           This parameter must be a number between Min_Data = 0 and Max_Data = 15     */

  usb_core_ch_direction_t ch_dir;     /*!< Channel direction
                                           This parameter store the physical channel direction IN/OUT                 */

  usb_core_device_speed_t speed;      /*!< USB Host Channel device speed
                                           This parameter can be any value of @ref usb_core_device_speed_t
                                                                                   (USB_CORE_DEVICE_SPEED_xxx)        */

  usb_core_ch_pid_type_t data_pid;    /*!< Initial data PID
                                           This parameter must be a number between Min_Data = 0 and Max_Data = 1      */

  usb_core_ep_type_t ep_type;         /*!< Endpoint Type
                                           This parameter can be any value of @ref usb_core_ep_type_t                 */

  usb_core_endpoint_t ep_num;         /*!< Endpoint number
                                           This parameter must be a number between Min_Data = 0 and Max_Data = 15     */

  uint8_t dev_addr;                   /*!< USB device address
                                           This parameter must be a number between Min_Data = 1 and Max_Data = 255    */

  uint16_t max_packet;                /*!< Endpoint Max packet size                                                   */

  uint8_t do_ping;                    /*!< Enable or disable the use of the PING protocol for HS mode.                */
  uint8_t do_ssplit;                  /*!< Enable start split transaction in HS mode.                                 */
  uint8_t do_csplit;                  /*!< Enable complete split transaction in HS mode.                              */
  uint8_t iso_split_xact_pos;         /*!< iso split transfer transaction position.                                   */
  uint8_t hub_port_nbr;               /*!< USB HUB port number                                                        */
  uint8_t hub_addr;                   /*!< USB HUB address                                                            */

  uint8_t *p_xfer_buffer;             /*!< Pointer to transfer buffer                                                 */
  uint32_t xfer_count;                /*!< Partial transfer length in case of multi packet transfer                   */
  uint32_t xfer_length;               /*!< Current transfer length                                                    */
  uint32_t xfer_size;                 /*!< Host Channel transfer size                                                 */

  uint32_t err_cnt;                   /*!< Host channel error count                                                   */

  uint16_t pma_address;               /*!< PMA Address
                                           This parameter can be any value between Min_addr = 0 and Max_addr = 1K     */

  uint16_t pma_addr0;                 /*!< PMA Address0
                                           This parameter can be any value between Min_addr = 0 and Max_addr = 1K     */

  uint16_t pma_addr1;                 /*!< PMA Address1
                                           This parameter can be any value between Min_addr = 0 and Max_addr = 1K     */

  uint8_t double_buffer_en;           /*!< Double buffer enable
                                           This parameter can be 0 or 1                                               */
} usb_core_ch_t;


/**
  * @brief  USB CORE pcd driver Structure definition
  */
typedef struct
{
  usb_core_status_t (* core_init)(uint32_t instance,
                                  const usb_core_config_params_t *p_core_config);    /*!< USB Core initialize         */

  usb_core_status_t (* core_deinit)(uint32_t instance);                              /*!< USB Core de-initialize      */

  usb_core_status_t (* core_set_mode)(uint32_t instance, usb_core_mode_t core_mode); /*!< USB Core set mode           */
  usb_core_mode_t (* core_get_mode)(uint32_t instance);                              /*!< USB Core get mode           */
  usb_core_status_t (* core_enable_interrupts)(uint32_t instance);                   /*!< USB Core enable interrupts  */
  usb_core_status_t (* core_disable_interrupts)(uint32_t instance);                  /*!< USB Core disable interrupts */

  usb_core_status_t (* device_init)(uint32_t instance,
                                    const usb_core_config_params_t *p_core_config);  /*!< Initialize the Device       */

  usb_core_status_t (* device_start)(uint32_t instance);                             /*!< DeInitialize the Device     */
  usb_core_status_t (* device_stop)(uint32_t instance);                              /*!< Stop the Device             */
  usb_core_status_t (* device_connect)(uint32_t instance);                           /*!< Connect the Device          */
  usb_core_status_t (* device_disconnect)(uint32_t instance);                        /*!< Disconnect the Device       */
  usb_core_status_t (* device_set_address)(uint32_t instance, uint8_t address);      /*!< Sets the Device Address     */

  usb_core_device_speed_t (* device_get_speed)(uint32_t instance);                   /*!< Gets the Device Speed       */

  usb_core_status_t (* ep_activate)(uint32_t instance, usb_core_ep_t *p_ep);         /*!< Activate the Endpoint       */

  usb_core_status_t (* ep_deactivate)(uint32_t instance,
                                      const usb_core_ep_t *p_ep);                    /*!< Deactivate the Endpoint     */

  usb_core_status_t (* ep_start_transfer)(uint32_t instance, usb_core_ep_t *p_ep);   /*!< Start the endpoint transfer */

  usb_core_status_t (* ep_stop_transfer)(uint32_t instance,
                                         const usb_core_ep_t *p_ep);                 /*!< Stop the endpoint transfer  */

  usb_core_status_t (* ep_set_stall)(uint32_t instance,
                                     const usb_core_ep_t *p_ep);                     /*!< Endpoint set stall          */

  usb_core_status_t (* ep_clear_stall)(uint32_t instance,
                                       const usb_core_ep_t *p_ep);                   /*!< Endpoint clear stall        */

  usb_core_status_t (* ep0_out_start)(uint32_t instance,
                                      const uint8_t *p_setup);                       /*!< Endpoint0 out start         */

  usb_core_status_t (* set_tx_fifo)(uint32_t instance, uint8_t fifo,
                                    uint16_t size_words);                            /*!< Set Tx FIFO                 */

  usb_core_status_t (* set_rx_fifo)(uint32_t instance, uint16_t size_words);         /*!< Set Rx FIFO                 */

  usb_core_status_t (* flush_tx_fifo)(uint32_t instance, uint32_t tx_fifo);          /*!< Flush Tx FIFO               */
  usb_core_status_t (* flush_rx_fifo)(uint32_t instance);                            /*!< Flush Rx FIFO               */

  void *(* read_packet)(uint32_t instance, uint8_t *p_dest,
                        uint8_t ep_num, uint32_t size_byte);                         /*!< Read Packet                 */

  usb_core_status_t (* write_packet)(uint32_t instance, const uint8_t *p_src,
                                     uint8_t ep_num, uint32_t size_byte);            /*!< Write Packet                */

  usb_core_status_t (* remote_wakeup_activate)(uint32_t instance);                   /*!< Activate Remote wake up     */
  usb_core_status_t (* remote_wakeup_deactivate)(uint32_t instance);                 /*!< Deactivate Remote wake up   */

  usb_core_status_t (* lpm_activate)(uint32_t instance);                             /*!< Activate LPM                */
  usb_core_status_t (* lpm_deactivate)(uint32_t instance);                           /*!< Deactivate LPM              */

  usb_core_status_t (* bcd_activate)(uint32_t instance);                             /*!< Activate BCD                */
  usb_core_status_t (* bcd_deactivate)(uint32_t instance);                           /*!< Deactivate BCD              */
  usb_core_status_t (* bcd_set_mode)(uint32_t instance,
                                     usb_core_bcd_config_t bcd_config,
                                     usb_core_bcd_config_sts_t bcd_sts);             /*!< Set BCD mode                */

  usb_core_bcd_port_status_t (* bcd_detect_port_type)(uint32_t instance,
                                                      usb_core_bcd_detection_t detection); /*!< Set BCD detection     */
} usb_core_pcd_driver_t;

/**
  * @brief  USB CORE hcd driver Structure definition
  */
typedef struct
{
  usb_core_status_t (* core_init)(uint32_t instance,
                                  const usb_core_config_params_t *p_core_config);    /*!< USB Core initialize         */

  usb_core_status_t (* core_deinit)(uint32_t instance);                              /*!< USB Core de-initialize      */

  usb_core_status_t (* core_set_mode)(uint32_t instance, usb_core_mode_t core_mode); /*!< USB Core set mode           */
  usb_core_mode_t (* core_get_mode)(uint32_t instance);                              /*!< USB Core get mode           */
  usb_core_status_t (* core_enable_interrupts)(uint32_t instance);                   /*!< USB Core enable interrupts  */
  usb_core_status_t (* core_disable_interrupts)(uint32_t instance);                  /*!< USB Core disable interrupts */

  usb_core_status_t (* host_init)(uint32_t instance,
                                  const usb_core_config_params_t *p_core_config);    /*!< USB Host initialize         */

  usb_core_status_t (* host_start)(uint32_t instance);                               /*!< USB Host start              */
  usb_core_status_t (* host_stop)(uint32_t instance);                                /*!< USB Host stop               */
  usb_core_status_t (* host_channel_init)(uint32_t instance, usb_core_ch_t *p_ch);   /*!< USB Host channel init       */
  usb_core_status_t (* host_channel_start)(uint32_t instance, usb_core_ch_t *p_ch);  /*!< USB Host channel de-init    */
  usb_core_status_t (* host_channel_stop)(uint32_t instance, usb_core_ch_t *p_ch);   /*!< USB Host channel stop       */
  usb_core_status_t (* host_channel_halt)(uint32_t instance,
                                          const usb_core_ch_t *p_ch);                /*!< USB Host channel halt       */

  usb_core_status_t (* host_channel_close)(uint32_t instance, usb_core_ch_t *p_ch);  /*!< USB Host channel close      */
  usb_core_status_t (* host_port_power)(uint32_t instance, uint8_t state);           /*!< USB Host port power         */
  usb_core_status_t (* host_port_reset)(uint32_t instance,
                                        usb_core_port_reset_sts_t reset_status);     /*!< USB Host port reset         */
  usb_core_status_t (* host_port_suspend)(uint32_t instance);                        /*!< USB Host port suspend       */
  usb_core_status_t (* host_port_resume)(uint32_t instance,
                                         usb_core_port_resume_sts_t resume_status);  /*!< USB Host port resume        */

  uint32_t (* host_get_current_frame)(uint32_t instance);                            /*!< USB Host get current frame  */
  usb_core_port_speed_t (* host_get_port_speed)(uint32_t instance);                  /*!< USB Host get port speed     */
  uint32_t (* core_get_dma_status)(uint32_t instance);                               /*!< USB Core get DMA status     */
} usb_core_hcd_driver_t;

#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif /* STM32C5xx_USB_DRD_CORE_H */
