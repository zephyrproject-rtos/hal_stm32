/*$Id: //dwh/bluetooth/DWC_ble154combo/firmware/rel/1.30a-SOW05PatchV6/firmware/public_inc/ll_intf.h#1 $*/
/**
 ********************************************************************************
 * @file    ll_intf_cmds.h
 * @brief   This file contains all the functions prototypes for the LL interface component.
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

#ifndef INCLUDE_LL_INTF_CMDS_H
#define INCLUDE_LL_INTF_CMDS_H

#include <stdint.h>
#include "common_types.h"
#if SUPPORT_PTA
#include "pta.h"
#endif /* SUPPORT_PTA */
/**
 * @brief Global error definition across different components.
 * refer the error codes defined in @ref  ll_error.h for more  information about  the values that this type should set
 */
typedef uint32_t ble_stat_t;

#ifndef ADDRESS_SIZE
#define ADDRESS_SIZE			6
#endif /* ADDRESS_SIZE */

#define LE_FEATURES_BYTES_NO 	8
#define ISO_CODEC_ID_SIZE 		5

/*!
 * The link layer will write the received packets RX_DATA_OFFSET
 * bytes after the start of the allocated shared memory. This may
 * be used to meet the requirements of the host or application in
 * case that some free space has to lead the received packets.
 */
#define RX_DATA_OFFSET				0

/**
 *  This defined value is used on Link Status custom command as 
 * 	the maximum number of states as follows:
 * 		8 (max num of state machines)
 *  
 *  in addition to:
 *  	2 (Broadcaster and Observer) 
 */
#define LINK_STATUS_SIZE				(MAX_NUM_CNCRT_STAT_MCHNS+2)
/**
 *  This defined value is used on Link Status custom command to indicate 
 * 	that the given state machine on a state other that a connection state 
 */
#define LINK_STATUS_DEFAULT_HANDLE		0xFFFF


/**
 *  This defined values are used to check for the range of values that the
 * 	channel classification parameters take (both min_spacing and max_delay)
 */
#define CHANNEL_CLASSIFICATION_REPORTING_TIMING_PARAM_MIN		5
#define CHANNEL_CLASSIFICATION_REPORTING_TIMING_PARAM_MAX		150

extern const struct hci_dispatch_tbl* p_dis_tbl;
/*================================= Enumerations =====================================*/

/**
 * @brief BLE  role enumeration
 */
typedef enum _ble_conn_role_e {
	BLE_ROLE_MASTER = 0 ,
	BLE_ROLE_SLAVE  = 1
}ble_conn_role_e;

/**
 * @brief Advertising event type enumeration
 */
typedef enum _ble_adv_event_type_e {
	ADV_IND_EVENT,
	ADV_DIRECT_IND_EVENT,
	ADV_SCAN_IND_EVENT,
	ADV_NONCONN_IND_EVENT,
	SCAN_RSP_EVENT,
} ble_adv_event_type_e;

/**
 * @brief Enum device address type.
 */
typedef enum dev_addr_type {
	PUBLIC, RANDOM, PUBLIC_ID, RANDOM_STATIC_ID, INVALID_TYPE,
	ANNONYMOUS = 0xFF
} dev_addr_type_e;

/**
 * @brief Enum device address type.
 */
typedef enum _rec_adv_stat_e {
	ADV_EXT_STAT,
	AUX_ADV_STAT,
	AUX_CHAIN_STAT,
} rec_adv_stat_e;

#if (SUPPORT_AOA_AOD)
/**
 * @brief Enum CTE_Type.
 */
typedef enum _cte_type_e {
	AOA_CTE,
	AOD_CTE_1_US_SLOTS,
	AOD_CTE_2_US_SLOTS
} cte_type_e;

/**
 * @brief Enum CTE_Category (connection CTE or connectionless CTE).
 */
typedef enum _cte_category_e {
	CONNECTION_CTE,
	CONNECTIONLESS_CTE
} cte_category_e;

/**
 * @brief Enum CTE Slot Durations.
 */
typedef enum _cte_slot_durtn_e {
	SLOT_DURTN_1_US = 0x01,
	SLOT_DURTN_2_US
} cte_slot_durtn_e;
#endif /* SUPPORT_AOA_AOD */

/*
 * @brief Privacy Modes
 */
typedef enum _ble_prvcy_mod_e {
	NETWORK_MODE,
	DEVICE_MODE
} ble_prvcy_mod_e;

/**
 * @brief State machine status for Get Link Status Command, it holds the
 *  values for different state machines based on its running event type
 */
enum _sm_status_e {
	SM_STATUS_IDLE 			= 0,
	SM_STATUS_ADV_EXTADV 	= 1,
	SM_STATUS_PERI_CONN 	= 2,
	SM_STATUS_SCN_EXTSCN 	= 3,
	SM_STATUS_CENT_CONN 	= 5,
	SM_STATUS_DTM_TX 		= 6,
	SM_STATUS_DTM_RX 		= 7,
	SM_STATUS_PRDC_ADV	 	= 9,
	SM_STATUS_PRDC_SYNC	 	= 10,
	SM_STATUS_BIG_ADV	 	= 11,
	SM_STATUS_BIG_SYNC	 	= 12,
	SM_STATUS_PERI_CIG	 	= 13,
	SM_STATUS_CENT_CIG	 	= 14,
};

/*================================= Structures =====================================*/

/**
 * @brief The data in one advertising report from the non-connection manager to the LL interface
 *
 * This structure contains the parameters should be sent from the link layer to the host per report.
 */
typedef struct _ble_intf_adv_report_data_st {
	uint8_t adv_addr[ADDRESS_SIZE + 2];
	ble_buff_hdr_t adv_rprt_data;
	int8_t rssi;
	ble_adv_event_type_e evnt_type;
	dev_addr_type_e adv_addr_type;
} ble_intf_adv_report_data_st;

/**
 * @brief Structure containing the advertising report data to be reported to host
 */
typedef struct _ble_intf_extended_adv_rprt_data_st {
	rec_adv_stat_e adv_stat;
	uint16_t event_type;
	uint8_t address_type;
	uint8_t *ptr_address;
	uint8_t primary_phy;
	uint8_t secondary_phy;
	uint8_t advertising_sid;
	uint16_t adv_data_id;
	uint8_t TX_power;
	int8_t rssi;
	uint16_t periodic_advertisng_interval;
	uint8_t direct_addresses_type;
	uint8_t *ptr_direct_address;
	uint8_t data_length;
	ble_buff_hdr_t *ptr_data;
	uint8_t rmv_adv_rprt;
	uint8_t address [ADDRESS_SIZE];
} ble_intf_extended_adv_rprt_data_st;

#if (SUPPORT_PERIODIC_SYNC_TRANSFER)
/**
 * @brief Structure containing the advertising sync transfer report to be reported to the host
 */
typedef struct _ble_intf_prdc_adv_sync_transfer_report_st {
	uint8_t status;                    /* Periodic advertising sync successful/failed */
	uint16_t conn_handle;			   /* Used to identify connection */
	uint16_t service_data;			   /* A value provided by the peer device */
	uint16_t sync_handle;			   /* Used to identify the periodic advertiser */
	uint8_t advertising_sid;           /* Value of the Advertising SID subfield in the ADI field of the PDU */
	uint8_t advertiser_address_type;   /* Advertiser address type */
	uint8_t* ptr_advertiser_address;   /* Pointer to advertiser address */
	uint8_t advertiser_phy;            /* Advertiser PHY */
	uint16_t periodic_advertising_interval; /* Periodic advertising interval */
	uint8_t advertiser_clock_accuracy; /* Clock accuracy used by advertise */
} ble_intf_prdc_adv_sync_transfer_report_st ;
#endif /* SUPPORT_PERIODIC_SYNC_TRANSFER */

/**
 * @brief The data in one direct advertising report from the non-connection manager to the LL interface
 *
 * This structure contains the parameters should be sent from the link layer to the host per direct advertising report.
 */
typedef struct _ble_intf_dir_adv_report_data_st {
	uint8_t addr[ADDRESS_SIZE + 2];
	uint8_t dir_addr[ADDRESS_SIZE + 2];
	int8_t rssi;
	ble_adv_event_type_e evnt_type;
	dev_addr_type_e addr_type;
	dev_addr_type_e dir_addr_type;
} ble_intf_dir_adv_report_data_st;

/**
 * @brief Data contained in extended advertising enable command for each advertising handle.
 *
 * This structure contains the parameters that are passed by the Host in extended advertising enable command for each advertising handle .
 * we divided the duration into two octets to avoid the structure padding
 */
typedef struct {
	uint8_t advertising_handle; /* Advertising handle that identify the advertising sets.*/
	uint8_t duration_LSB; /* The Least Significant Octet of the  Duration of the advertising  */
	uint8_t duration_MSB; /* The Most Significant Octet of the  Duration of the advertising  */
	uint8_t max_extended_advertising_events; /* Max number of events of the advertising of each advertising handle */
} st_ble_intf_ext_adv_enable_params;

/**
 * @brief Data contained in extended create connection command for each PHY.
 *
 * This structure contains the parameters that are passed by the Host in set extended scan parameters command for each PHY.
 */
typedef struct {
	uint8_t scan_type;
	uint16_t scan_interval;
	uint16_t scan_window;
} st_ble_intf_ext_scn_params;

#if (SUPPORT_CONNECTED_ISOCHRONOUS &&( SUPPORT_MASTER_CONNECTION || SUPPORT_SLAVE_CONNECTION))
/**
 * @brief Data contained in CIS established event
 *
 * This structure contains the parameters that are passed to the Host in different scenarios of CIS (eg: create_cis).
 */
typedef struct _ble_intf_cis_estblshd_evnt_st{
	uint32_t cig_sync_delay;		/* The maximum time, in us, for transmission all CISes */
	uint32_t cis_sync_delay;		/* The maximum time, in us, for transmission of PDUs of a CIS */
	uint32_t trsnprt_ltncy_m_to_s;	/* The maximum time, in us, for transmission of SDUs of all CISes */
	uint32_t trsnprt_ltncy_s_to_m;
	uint16_t conn_hndl;				/* Connection handle of the CIS */
	uint16_t max_pdu_m_to_s;			/* max pdu size */
	uint16_t max_pdu_s_to_m;
	uint16_t iso_interval;
	uint8_t status;					/* Status of the establishment */
	uint8_t phy_m_to_s;				/* Used PHY from Master to Slave */
	uint8_t phy_s_to_m;				/* Used PHY from Slave to Master */
	uint8_t nse;					/* number of sub-event*/
	uint8_t bn_m_to_s;				/* number of payloads */
	uint8_t bn_s_to_m;
	uint8_t ft_m_to_s;				/* flush timeout */
	uint8_t ft_s_to_m;
} ble_intf_cis_estblshd_evnt_st;

/**
 * @brief Data contained in CIS Request event
 *
 * This structure contains the parameters passed from the master to the host of the slave in CIS creation procedure.
 */
typedef struct _ble_intf_cis_req_evnt_st{
	uint16_t acl_conn_hndl;	/* ACL connection handle*/
	uint16_t cis_conn_hndl;	/* CIS connection handle */
	uint8_t cis_id;		/* CIS Identifier */
	uint8_t cig_id;		/* CIG Identifier */
} ble_intf_cis_req_evnt_st;

#endif/* SUPPORT_CONNECTED_ISOCHRONOUS &&( SUPPORT_MASTER_CONNECTION || SUPPORT_SLAVE_CONNECTION) */

#if ((SUPPORT_CONNECTED_ISOCHRONOUS &&( SUPPORT_MASTER_CONNECTION || SUPPORT_SLAVE_CONNECTION)) || (SUPPORT_BRD_ISOCHRONOUS || SUPPORT_SYNC_ISOCHRONOUS))
/**
 * @brief Structure containing the ISO sync event info to be reported to host
 */
typedef struct _ble_intf_sync_evnt_st{
	uint8_t group_id;	/* identifier of the CIG or BIG*/
	uint32_t next_anchor_point;	/* the time stamp in microseconds at the Controller clock of the next expected CIG or BIG anchor point */
	uint32_t time_stamp; /* the time stamp in microseconds at the Controller clock, this represent the time at which the Trigger is generated */
	uint32_t nxt_sdu_delivery_timeout;
} ble_intf_sync_evnt_st;
#endif /* (SUPPORT_CONNECTED_ISOCHRONOUS &&( SUPPORT_MASTER_CONNECTION || SUPPORT_SLAVE_CONNECTION)) || (SUPPORT_BRD_ISOCHRONOUS || SUPPORT_SYNC_ISOCHRONOUS) */

#if (SUPPORT_BRD_ISOCHRONOUS || SUPPORT_SYNC_ISOCHRONOUS)
/**
 * @brief Structure containing the Create BIG Test command parameters
 */
typedef struct _ble_intf_create_big_test_cmd_st
{
	uint16_t iso_intrv;  /* contains the time duration between two consecutive BIG anchor points*/
	uint16_t max_pdu;    /* contains the maximum size of every BIS Data PDU for every BIS in the BIG*/
	uint8_t nse;         /* Number of SubEvents */
	uint8_t bn;       	 /* (Burst Number) the number of new payloads for each BIS in an isochronous interval*/
	uint8_t irc;      	 /*(Immediate Repetition Count) the number of times the  data packet is transmitted */
	uint8_t pto;    	 /* (Pre_Transmission_Offset) the offset in number of ISO_Intervals for pre-transmissions of data packets */
} ble_intf_create_big_test_cmd_st;

/**
 * @brief Structure containing the Create BIG SYNC command parameters
 */
typedef struct _ble_intf_big_common_sync_bc_cmd_st{
	uint8_t num_bis;  		   /* Total number of BISes to synchronize*/
	uint32_t bcast_code[4];	   /* used for deriving the session key for decrypting payloads of encrypted BISes.*/
	uint8_t big_hndle;   	   /* the identifier of the BIG */
	uint8_t encrptn;  		   /* identifies the encryption mode of the BISes */
}ble_intf_big_common_sync_bc_cmd_st;

/**
 * @brief structure of common parameters between create_big and create_big_test
 */
typedef struct _ble_intf_create_big_common_param_cmd_st{
	uint32_t sdu_intrv;    /* contains the time interval of the periodic SDUs */
	uint16_t max_sdu;    /* contains the maximum size of an SDU*/
	uint8_t adv_hndle;   /* identifies the associated periodic advertising train of the BIG */
	uint8_t pack;           /* the preferred method of arranging subevents of multiple BISes*/
	uint8_t framing;    /* indicates the format for sending BIS Data PDUs (framed or unframed)*/
	tx_rx_phy_e phy;             /* the PHY used for transmission of PDUs of BISes in the BIG */
	ble_intf_big_common_sync_bc_cmd_st big_common_sync_bc; /* common parameters between the synchronizer and broadcaster */
}ble_intf_create_big_common_param_cmd_st;

#if(SUPPORT_BRD_ISOCHRONOUS)
/**
 * @brief Data contained in big complete event
 *
 * This structure contains parameters that are passed to the Host while ig creation.
 */
typedef struct _ble_intf_big_cmplt_evnt_st{
	uint16_t *conn_hndle; 		/* the list of connection handles of all BISes in the BIG*/
	uint32_t big_sync_delay; 	/* the maximum time, in microseconds, for transmission of PDUs of all BISes in a BIG in an isochronous interval */
	uint32_t trnsprt_ltncy_big; /* the maximum time, in microseconds, for transmission of SDUs of all BISes in a BIG */
	uint16_t max_pdu;	/*Maximum size, in octets, of the payload*/
	uint16_t iso_intrv;	/* iso interval */
	uint8_t status; 	/*Create BIG  successful/failed*/
	uint8_t big_hndle; 	/* the identifier of the BIG */
	uint8_t phy;	 	/* the PHY used to create the BIG*/
	uint8_t num_bis; 	/* the total number of BISes in the BIG*/
	uint8_t nse; 		/*The number of subevents in each BIS event in the BIG*/
	uint8_t bn;			/*The number of new payloads in each BIS event*/
	uint8_t pto;	 	/*Offset used for pre-transmissions*/
	uint8_t irc; 		/*The number of times a payload is transmitted in a BIS event*/
} ble_intf_big_cmplt_evnt_st;
#endif /* SUPPORT_BRD_ISOCHRONOUS */

#if(SUPPORT_SYNC_ISOCHRONOUS)
/**
 * @brief Data contained in big sync established event
 */
typedef struct _ble_intf_big_sync_estblshd_evnt_st{
	uint32_t trnsprt_ltncy_big; /* the maximum time, in microseconds, for reception of SDUs of all BISes in aBIG */
	uint16_t *conn_hndle; /* The list of connection handles of all BISes in the BIG*/
	uint16_t max_pdu;	  /* Maximum size, in octets, of the payload*/
	uint16_t iso_intrvl;  /* IsoInterval */
	uint8_t status; 	  /* BIG sync establish successful/failed  */
	uint8_t big_hndle; 	  /* the identifier of the BIG */
	uint8_t num_bis;  	  /* the total number of BISes in the BIG*/
	uint8_t nse; 		  /*The number of subevents in each BIS event in the BIG*/
	uint8_t bn;			  /*The number of new payloads in each BIS event*/
	uint8_t pto;	 	  /*Offset used for pre-transmissions*/
	uint8_t irc; 		  /*The number of times a payload is transmitted in a BIS event*/
} ble_intf_big_sync_estblshd_evnt_st;

/**
 * @brief Data contained in BIGInfo report event
 */
typedef struct _ble_intf_biginfo_rprt_evnt_st{
	ble_intf_create_big_test_cmd_st test_param_st;
	ble_intf_create_big_common_param_cmd_st non_test_param;
	uint16_t sync_hndl;
} ble_intf_biginfo_rprt_evnt_st;

#endif /* SUPPORT_SYNC_ISOCHRONOUS */
#endif/* SUPPORT_BRD_ISOCHRONOUS || SUPPORT_SYNC_ISOCHRONOUS */

#if (SUPPORT_AOA_AOD)
#if (SUPPORT_EXPLCT_OBSERVER_ROLE || SUPPORT_MASTER_CONNECTION || SUPPORT_SYNC_ISOCHRONOUS)
/**
 * @brief This structure contains the parameters that should be sent from the link layer to the host through the LE_Connectionless_IQ_Report_Event.
 */
typedef struct _le_connless_iq_report_evnt_st {
	ble_buff_hdr_t  *ptr_iq_samples; 	/* Pointer to the IQ samples buffer received in AUX_SYNC_IND PDU */
	uint16_t sync_handle;
	int16_t rssi;				/* RSSI of the packet (excluding the Constant Tone Extension) */
	uint16_t pa_event_counter;
	uint8_t  rssi_antenna_id;		/* ID of the antenna on which the RSSI was measured */
	uint8_t  channel_index; 		/* Index of the channel on which the AUX_SYNC_IND PDU was received */
	uint8_t  pckt_status; 			/* Indicate whether the received packet had a valid CRC */
	uint8_t  sample_count; 			/* Total number of IQ sample pairs */
	cte_type_e  cte_type; 			/* CTE field type */
	cte_slot_durtn_e  slot_durations;	/* CTE switching and sampling slot durations */
} le_connless_iq_report_evnt_st;
#endif /* SUPPORT_EXPLCT_OBSERVER_ROLE || SUPPORT_MASTER_CONNECTION || SUPPORT_SYNC_ISOCHRONOUS*/

#if (SUPPORT_MASTER_CONNECTION || SUPPORT_SLAVE_CONNECTION)
/**
 * @brief This structure contains the parameters that should be sent from the link layer to the host through the LE_Connection_IQ_Report_Event.
 */
typedef struct _ble_intf_conn_iq_report_st {
	ble_buff_hdr_t  *ptr_iq_samples; 	/* Pointer to the IQ samples buffer received during the connection event */
	uint16_t conn_handle;
	int16_t rssi; 				/* RSSI value of the received data packet */
	uint16_t conn_event_counter;
	uint8_t rx_phy;				/* Receiver PHY for the connection. 0x01: LE 1M PHY, 0x02: LE 2M PHY */
	uint8_t data_channel_index; 		/* Index of the data channel on which the Data Channel PDU was received */
	uint8_t rssi_antenna_id; 		/* ID of the antenna on which the RSSI was measured */
	uint8_t pckt_status; 			/* Indicate whether the received packet had a valid CRC */
	uint8_t sample_count; 			/* Total number of IQ sample pairs */
	cte_type_e  cte_type; 			/* CTE field type */
	cte_slot_durtn_e  slot_durations;	/* CTE switching and sampling slot durations */
} ble_intf_conn_iq_report_st;
#endif /* (SUPPORT_MASTER_CONNECTION || SUPPORT_SLAVE_CONNECTION) */
#endif /* SUPPORT_AOA_AOD */

#if (SUPPORT_LE_POWER_CONTROL)
/**
 * @brief This structure contains the parameters that should be sent from the link layer to the host through the LE_Transmit_Power_Reporting_Event.
 */
typedef struct _le_tx_power_report_st {
	uint16_t conn_handle_id;	/* Connection handle for which the TX_Power level is reported to Host */
	uint8_t status;				/* Status of the "HCI_LE_Read_Remote_Transmit_Power_Level" command */
	uint8_t reason;				/* Indicates why the event was sent and the device whose TX_Power level is being reported:
									0x00: Local transmit power changed
									0x01: Remote transmit power changed
									0x02: HCI_LE_Read_Remote_Transmit_Power_Level command completed */
	uint8_t phy;				/* Indicate the PHY involved (which might not be the current TX PHY for the relevant device) */
	uint8_t tx_power_level_flag;/* Indicate whether the TX_Power level that is being reported has reached its minimum and/or maximum level */
	int8_t tx_power_level;		/* Indicate the TX_Power level for the PHY (unit: dBm) */
	int8_t delta;				/* Set to the change in power level for the transmitter being reported (unit: dB) */
} le_tx_power_report_st;

/**
 * @brief This structure contains the parameters that should be sent from the link layer to the host through the LE_Path_Loss_Threshold_Event.
 */
typedef struct _le_path_loss_threshold_evnt_st {
	uint16_t conn_handle_id;	/* Connection handle for which a path loss threshold crossing is reported to Host */
	uint8_t current_path_loss;	/* The current path loss value as calculated by the Controller. (unit: dB) */
	uint8_t zone_entered;		/* Indicates which zone was entered:
									0x00: Entered low zone
									0x01: Entered middle zone
									0x02: Entered high zone */
} le_path_loss_threshold_evnt_st;
#endif /* SUPPORT_LE_POWER_CONTROL */

#if SUPPORT_LE_ENHANCED_CONN_UPDATE
/* struct holding the subrate parameters used in posting subrate change event to the host */
typedef struct _le_subrate_change_evnt_st{
		uint16_t conn_handle_id;
		uint16_t subrate_factor;
		uint16_t peripheral_latency;
		uint16_t continuation_num;
		uint16_t supervisionTo;
		uint8_t status;
}le_subrate_change_evnt_st;
#endif /* SUPPORT_LE_ENHANCED_CONN_UPDATE */
/**
 * @brief Data contained in extended create connection command for each PHY.
 *
 * This structure contains the parameters that are passed by the Host in extended create connection command for each PHY.
 */
typedef struct _ble_intf_ext_create_conn_st {
	uint16_t scan_interval; /* scanning intervals for each PHY. */
	uint16_t scan_window; /* scanning windows for each PHY. */
	uint16_t conn_interval_min; /* minimum connection interval for each PHY. */
	uint16_t conn_interval_max; /* maximum connection interval for each PHY. */
	uint16_t conn_latency; /* connection latencies for each PHY. */
	uint16_t supervision_timeout; /* supervision timeout for each PHY. */
	uint16_t minimum_ce_length; /* minimum connection event length for each PHY. */
	uint16_t maximum_ce_length;
} st_ble_intf_ext_create_conn;

/* HCI Commands Parameters Structures */
#if (SUPPORT_AOA_AOD)
#if (SUPPORT_EXPLCT_BROADCASTER_ROLE)
/**
 * @brief LE Set Connectionless CTE Transmit Parameters Command
 */
typedef struct _le_set_connless_cte_tx_params_cmd_st
{
	uint8_t adv_handle;
	uint8_t cte_len;		/* Length of the Constant Tone Extension in 8 us units. Range:[0x02 – 0x14]
	 	 	 	 	   0x00: means Do not transmit a Constant Tone Extension */
	uint8_t cte_type;		/* 0x00: AoA CTE
					   0x01: AoD CTE with 1 us slots
					   0x02: AoD CTE with 2 us slots */
	uint8_t cte_count;		/* Number of CTEs to transmit in each periodic advertising interval*/
	uint8_t switching_pattern_len;	/* The number of Antenna IDs in the switching pattern */
	uint8_t	*ptr_antenna_ids;	/* List of Antenna IDs in the pattern */
}le_set_connless_cte_tx_params_cmd_st;

/**
 * @brief LE Set Connectionless CTE Transmit Enable Command
 */
typedef struct _le_set_connless_cte_tx_enable_cmd_st
{
	uint8_t adv_handle;
	uint8_t connless_cte_enable;	/* Enable/Disable Connectionless CTE transmission. Enable:1 - Disable:0 */

}le_set_connless_cte_tx_enable_cmd_st;
#endif /* (SUPPORT_EXPLCT_BROADCASTER_ROLE) */

#if (SUPPORT_EXPLCT_OBSERVER_ROLE ||  SUPPORT_MASTER_CONNECTION || SUPPORT_SYNC_ISOCHRONOUS)
/**
 * @brief LE Set Connectionless IQ Sampling Enable Command
 */
typedef struct _le_set_connless_iq_sampling_enable_cmd_st
{
	uint16_t sync_handle;
	uint8_t  iq_sampling_enable;	/* Enable/Disable Connectionless IQ samples capturing. Enable:1 - Disable:0 */
	uint8_t  slot_durations;	/* Switching and sampling slots' duration */
	uint8_t  max_sampled_ctes;	/* maximum number of CTEs to sample and report in each periodic advertising interval */
	uint8_t  switching_pattern_len; /* The number of Antenna IDs in the switching pattern */
	uint8_t	 *ptr_antenna_ids;	/* List of Antenna IDs in the pattern */
}le_set_connless_iq_sampling_enable_cmd_st;
#endif /* (SUPPORT_EXPLCT_OBSERVER_ROLE || SUPPORT_MASTER_CONNECTION || SUPPORT_SYNC_ISOCHRONOUS) */

#if ((SUPPORT_MASTER_CONNECTION) || (SUPPORT_SLAVE_CONNECTION))
/**
 * @brief LE Set Connection CTE Receive Parameters Command
 */
typedef struct _le_set_conn_cte_rx_params_cmd_st
{
	uint16_t conn_handle_id;
	uint8_t  cte_sampling_enable;	/* Enable/Disable sampling the received CTE fields on this connection handle. Enable:1 - Disable:0 */
	uint8_t  slot_durations;	/* Switching and sampling slots' duration */
	uint8_t  switching_pattern_len;	/* The number of Antenna IDs in the switching pattern */
	uint8_t	 *ptr_antenna_ids;	/* List of Antenna IDs in the pattern */
}le_set_conn_cte_rx_params_cmd_st;

/**
 * @brief LE Set Connection CTE Transmit Parameters Command
 */
typedef struct _le_set_conn_cte_tx_params_cmd_st
{
	uint16_t conn_handle_id;
	uint8_t  cte_types;		/* 0x00: AoA CTE
					   0x01: AoD CTE with 1 us slots
					   0x02: AoD CTE with 2 us slots */
	uint8_t  switching_pattern_len;	/* The number of Antenna IDs in the switching pattern */
	uint8_t	 *ptr_antenna_ids;	/* List of Antenna IDs in the pattern */
}le_set_conn_cte_tx_params_cmd_st;

/**
 * @brief LE Connection CTE Request Enable Command
 */
typedef struct _le_set_conn_cte_req_enable_cmd_st
{
	uint16_t conn_handle_id;
	uint16_t  cte_req_intrvl;	/* 0x00				: Send LL_CTE_REQ once, at the earliest practical opportunity
 				       	   	   	   0x0001 - 0xFFFF	: Requested interval for sending LL_CTE_REQ PDUs in number of connection events. */
	uint8_t  cte_req_enable;	/* Enable/Disable CTE Request transmission for the connection. Enable:1 - Disable:0 */
	uint8_t	  requested_cte_len;	/* Minimum length of the Constant Tone Extension being requested in 8 us units */
	uint8_t	  requested_cte_type;	/* Indicates the type of CTE that the Controller shall request from the remote device, its values:
					   	   0x00		: AoA Constant Tone Extension
 				       	   0x01		: AoD Constant Tone Extension with 1 us slots
				           0x02		: AoD Constant Tone Extension with 2 us slots */
}le_set_conn_cte_req_enable_cmd_st;

/**
 * @brief LE Connection CTE Response Enable Command
 */
typedef struct _le_set_conn_cte_rsp_enable_cmd_st
{
	uint16_t conn_handle_id;
	uint8_t  cte_rsp_enable;	/* Enable/Disable CTE Response transmission for the connection. Enable:1 - Disable:0 */
}le_set_conn_cte_rsp_enable_cmd_st;
#endif /* (SUPPORT_MASTER_CONNECTION) || (SUPPORT_SLAVE_CONNECTION) */
#endif /* SUPPORT_AOA_AOD */

#if (SUPPORT_AOA_AOD)
/**
 * @brief LE Receiver Test command [v3]
 */
typedef struct
{
	uint8_t rx_channel;		/* specify the RF channel to be used by the receiver */
	uint8_t phy; 			/* specify the PHY to be used by the receiver */
	uint8_t modulation_index; 	/* specify whether or not the Controller should assume the receiver has a stable modulation index */
	uint8_t expected_cte_length;	/* specify the expected length of the Constant Tone Extension in received test reference packets */
	uint8_t expected_cte_type;	/* specify the expected type of the Constant Tone Extension in expected test reference packets */
	uint8_t switching_pattern_len;	/* specify the length of the antenna switching pattern used when receiving an AoA CTE */
	uint8_t *ptr_antenna_ids;	/* specify the antenna switching pattern used when receiving an AoA CTE */
	cte_slot_durtn_e slot_durations;		/* specify the CTE sampling slots durations */
}le_rx_test_v3_cmd_st;

/**
 * @brief LE Transmitter Test command [v3]
 */
typedef struct _le_tx_test_v3_cmd_st
{
	uint8_t tx_channel;		/* specify the RF channel to be used by the transmitter */
	uint8_t length_of_test_data; 	/* specify the length of the Payload of the test reference packets */
	uint8_t packet_payload;		/* specify the con_le_rx_test_v3_cmd_sttents of the Payload of the test reference packets */
	uint8_t phy; 			/* specify the PHY to be used by the transmitter */
	uint8_t cte_length;		/* specify the length of the Constant Tone Extension in the test reference packets */
	uint8_t cte_type;		/* specify the type of the Constant Tone Extension in the test reference packets */
	uint8_t switching_pattern_len;	/* specify the length of the antenna switching pattern used when transmitting an AoD CTE */
	uint8_t *ptr_antenna_ids;	/* specify the antenna switching pattern used when transmitting an AoD CTE */
}le_tx_test_v3_cmd_st;
#endif /* SUPPORT_AOA_AOD */

/**
 * @brief LE Set Connection Transmit Power Level command
 */
#if (SUPPORT_MASTER_CONNECTION || SUPPORT_SLAVE_CONNECTION)
typedef struct _le_set_conn_tx_pwr_lvl_cmd_st{
	uint16_t conn_handle_id;	/* Connection handle for which the TX_Power level used by the local controller is updated */
	uint8_t phy;				/* PHY for which the TX_Power level used by the local controller is updated */
	int8_t tx_power;			/* specify the change in the local TX_Power level, if any,for the PHY(s) specified */
}le_set_conn_tx_pwr_lvl_cmd_st;
#endif /* SUPPORT_MASTER_CONNECTION || SUPPORT_SLAVE_CONNECTION */

#if (SUPPORT_LE_POWER_CONTROL)
/**
 * @brief LE Enhanced Read Transmit Power Level command
 */
typedef struct _le_enhanced_read_tx_pwr_lvl_cmd_st{
	uint16_t conn_handle_id;	/* Connection handle for which the current and maximum TX_Power levels are reported */
	uint8_t phy;				/* PHY for which the current and maximum TX_Power levels are reported */
}le_enhanced_read_tx_pwr_lvl_cmd_st;

/**
 * @brief LE Read Remote Transmit Power Level command
 */
typedef struct _le_read_remote_tx_pwr_lvl_cmd_st{
	uint16_t conn_handle_id;	/* Connection handle for which the TX_Power level used by the remote controller is reported */
	uint8_t phy;				/* PHY for which the TX_Power level used by the remote controller is reported */
}le_read_remote_tx_pwr_lvl_cmd_st;

/**
 * @brief LE Set Path Loss Reporting Parameters command
 */
typedef struct _le_set_path_loss_reporting_params_cmd_st{
	uint16_t conn_handle_id;	/* Connection handle for which path loss threshold reporting parameters are set */
	uint16_t min_time_spent;	/* Minimum time in number of connection events to be observed once the path crosses the threshold before an event is generated to Host */
	uint8_t high_threshold;		/* High threshold for the path loss (unit: dB) */
	uint8_t high_hysteresis;	/* Hysteresis value for the high threshold (unit: dB) */
	uint8_t low_threshold;		/* Low threshold for the path loss (unit: dB) */
	uint8_t low_hysteresis;		/* Hysteresis value for the low threshold (unit: dB) */
}le_set_path_loss_reporting_params_cmd_st;

/**
 * @brief LE Set Path Loss Reporting Enable command
 */
typedef struct _le_set_path_loss_reporting_enable_cmd_st{
	uint16_t conn_handle_id;	/* Connection handle for which path loss reporting to Host is enabled or disabled */
	uint8_t enable;				/* Enable or Disabled the path loss reporting to Host. 0x00: Reporting disabled. 0x01: Reporting enabled */
}le_set_path_loss_reporting_enable_cmd_st;

/**
 * @brief LE Set Transmit Power Reporting Enable command
 */
typedef struct _le_set_tx_pwr_reporting_enable_cmd_st{
	uint16_t conn_handle_id;	/* Connection handle for which reporting to the local Host of TX_Power level changes in the local and remote Controllers is enabled or disabled */
	uint8_t local_enable;		/* 0x00: Disable local transmit power reports
								   0x01: Enable local transmit power reports */
	uint8_t remote_enable;		/* 0x00: Disable remote transmit power reports
	 	 	 	 	 	 		   0x01 Enable remote transmit power reports */
}le_set_tx_pwr_reporting_enable_cmd_st;

/**
 * @brief LE Transmitter Test command [v4]
 */
typedef struct _le_tx_test_v4_cmd_st
{
	uint8_t tx_channel;		/* specify the RF channel to be used by the transmitter */
	uint8_t length_of_test_data; 	/* specify the length of the Payload of the test reference packets */
	uint8_t packet_payload;		/* specify the con_le_rx_test_v3_cmd_sttents of the Payload of the test reference packets */
	uint8_t phy; 			/* specify the PHY to be used by the transmitter */
	uint8_t cte_length;		/* specify the length of the Constant Tone Extension in the test reference packets */
	uint8_t cte_type;		/* specify the type of the Constant Tone Extension in the test reference packets */
	uint8_t switching_pattern_len;	/* specify the length of the antenna switching pattern used when transmitting an AoD CTE */
	uint8_t *ptr_antenna_ids;	/* specify the antenna switching pattern used when transmitting an AoD CTE */
	int8_t tx_power_level;	/* specify the TX_Power level to be used by the transmitter. (Unit: dBm)
	 	 	 	 	 	 	 0x7E: Set transmitter to minimum TX_Power.
	 	 	 	 	 	 	 0x7F: Set transmitter to maximum TX_Power.
	 	 	 	 	 	 	 otherwise, Set transmitter to the specified or the nearest TX_Power level. */
}le_tx_test_v4_cmd_st;
#endif /* SUPPORT_LE_POWER_CONTROL */

/**
 * @brief LE Set ADV parameters
 */
typedef struct _le_set_adv_params_cmd_st {
	uint16_t adv_intrv_min; /* Range: 0x0020 to 0x4000, Time = N * 0.625 msec, Time Range: 20 ms to 10.24 sec*/
	uint16_t adv_intrv_max; /* Range: 0x0020 to 0x4000, Time = N * 0.625 msec, Time Range: 20 ms to 10.24 sec*/
	uint8_t adv_type; 		/* Advertising type*/
	uint8_t own_addr_type; 	/* Address type of the source address */
	uint8_t peer_addr_type; /* peer address type */
	uint8_t peer_addr[ADDRESS_SIZE]; /* Public Device Address, Random Device Address,
	 	 	 	 	 	 	 	 	 	Public Identity Address, or Random (static)
	 	 	 	 	 	 	 	 	 	Identity Address of the device to be connected*/
	uint8_t adv_chnl_map; 			/* Advertising channel index used when transmitting advertising packets. */
	uint8_t adv_filter_policy; 	/* filter policy type. range 0:3 */
} le_set_adv_params_cmd_st;

/**
 * @brief LE Create Connection Command
 */
typedef struct _le_set_scn_params_cmd_st {
	uint8_t scn_type; /* Passive 0 or active 1 scanning*/
	uint16_t scn_interv; /* Range: 0x0020 to 0x4000, Time = N * 0.625 msec, Time Range: 20 ms to 10.24 sec*/
	uint16_t scn_wndw; /* Range: 0x0020 to 0x4000, Time = N * 0.625 msec, Time Range: 20 ms to 10.24 sec*/
	uint8_t own_addr_type; 	/* Address type of the source address */
	uint8_t scanning_filter_policy; /**<filter policy type saved for fw purposes. range 0:3 */
} le_set_scn_params_cmd_st;

/**
 * @brief LE Set Scan Command
 */
typedef struct _le_create_conn_cmd_st {
	uint16_t le_scan_intrv;
	uint16_t le_scan_wndw;
	uint8_t init_filter_policy ;
	uint8_t peer_addr_type;
	uint8_t peer_addr[ADDRESS_SIZE];
	uint8_t own_addr_type;
	uint16_t conn_interval_min;	/*Range: 0x0006 to 0x0C80, Time = N * 1.25 msec, Time Range: 7.5 msec to 4 seconds*/
	uint16_t conn_interval_max;	/*Range: 0x0006 to 0x0C80, Time = N * 1.25 msec, Time Range: 7.5 msec to 4 seconds*/
	uint16_t host_slave_latency;/*Range: 0x0000 to 0x01F3*/
	uint16_t sv_timeout;		/*Range: 0x000A to 0x0C80, Time = N * 10 msec, Time Range: 100 msec to 32 seconds*/
	uint16_t min_ce_length;		/*Range: 0x0000  0xFFFF, Time = N * 0.625 msec.*/
	uint16_t max_ce_length;		/*Range: 0x0000  0xFFFF, Time = N * 0.625 msec.*/
} le_create_conn_cmd_st;

/**
 * @brief LE Remote Connection Parameters REQ reply
 */
typedef struct _le_rmt_conn_param_req_rply_cmd_st {
	uint16_t conn_interval_min;	/*Range: 0x0006 to 0x0C80, Time = N * 1.25 msec, Time Range: 7.5 msec to 4 seconds*/
	uint16_t conn_interval_max;	/*Range: 0x0006 to 0x0C80, Time = N * 1.25 msec, Time Range: 7.5 msec to 4 seconds*/
	uint16_t slave_latency;		/*Range: 0x0000 to 0x01F3*/
	uint16_t sv_timeout;		/*Range: 0x000A to 0x0C80, Time = N * 10 msec, Time Range: 100 msec to 32 seconds*/
	uint16_t min_ce_length;		/*Range: 0x0000  0xFFFF, Time = N * 0.625 msec.*/
	uint16_t max_ce_length;		/*Range: 0x0000  0xFFFF, Time = N * 0.625 msec.*/
} le_rmt_conn_param_req_rply_cmd_st;

/**
 * @brief HCI Dispatch table containing callback event functions
 */
struct hci_dispatch_tbl {

	/*========================================================================================================*/
	/*================================================= APIs =================================================*/
	/*========================================================================================================*/

	/*##### Generic Events HCI Group #####*/

	/**
	 * @brief  Used to notify the Host that a hardware failure has occurred in the Controller
	 *
	 * @param  hw_code  : [in]  code values that indicate various hardware problems.
	 */
	void (*ll_intf_hw_error_evnt)(uint8_t hw_code);

	/*##### Connection Setup HCI Group #####*/

#if (SUPPORT_SLEEP_CLOCK_ACCURCY_UPDATES)
	/**
	 * @brief  The HCI_LE_Request_Peer_SCA_Complete event indicates that the HCI_LE_Request_Peer_SCA command has been completed.
	 *
	 * @param  status		: [in] whether the correct PDU is recieved by the controller.
	 * @param  conn_hndl	: [in] is the connection handle of the ACL connection in which the HCI_LE_Request_Peer_SCA command is issued.
	 * @param  sca			: [in] contains the sleep clock accuracy of the peer.
	 */
	void (*ll_intf_le_req_peer_sca_cpmlt_evnt)(uint8_t status, uint16_t conn_hndl, uint8_t sca);
#endif /* Sleep Clock Accuracy update*/

#if (SUPPORT_CONNECTED_ISOCHRONOUS &&( SUPPORT_MASTER_CONNECTION || SUPPORT_SLAVE_CONNECTION))
	/**
	 * @brief  The HCI_LE_CIS_Established event indicates that the CIS with the Connection_Handle is established.
	 *
	 * @param  ptr_st_cis_estblshd_evnt_params	: [in] pointer to ble_intf_cis_estblshd_evnt_st that carries all event parameters.
	 */
	void (*ll_intf_le_cis_estblshd_evnt)(ble_intf_cis_estblshd_evnt_st* ptr_st_cis_estblshd_evnt_params);

#if(SUPPORT_SLAVE_CONNECTION)
	/**
	 * @brief  The HCI_LE_CIS_Request event indicates that a Controller has received a request to establish a CIS.
	 *
	 * @param  ptr_st_cis_req_evnt_params	: [in] pointer to ble_intf_cis_req_evnt_st that carries all event parameters.
	 */
	void (*ll_intf_le_cis_req_evnt)(ble_intf_cis_req_evnt_st* ptr_st_cis_req_evnt_params);
#endif /* SUPPORT_SLAVE_CONNECTION */
#endif /* SUPPORT_CONNECTED_ISOCHRONOUS &&( SUPPORT_MASTER_CONNECTION || SUPPORT_SLAVE_CONNECTION) */

#if (SUPPORT_BRD_ISOCHRONOUS || SUPPORT_SYNC_ISOCHRONOUS)

#if(SUPPORT_BRD_ISOCHRONOUS)
	/**
	 * @brief  The HCI_LE_Create_BIG_Complete event indicates that the HCI_LE_Create_BIG command has completed.
	 *
	 * @param  ptr_st_big_cmplt_evnt	: [in] pointer to ble_intf_big_cmplt_evnt_st that carries all event parameters.
	 */
	void (*ll_intf_le_create_big_cmplt_evnt)(ble_intf_big_cmplt_evnt_st* ptr_st_big_cmplt_evnt);

	/**
	 * @brief  The HCI_LE_Terminate_BIG_Complete event indicates that the transmission of all the BISes in the BIG are terminated.
	 *
	 * @param  rsn			: [in] Reason for termination.
	 * @param  big_hndle	: [in] BIG identifier used to identify the BIG that is terminated.
	 */
	void (*ll_intf_le_terminate_big_cmplt_evntt)(uint8_t rsn, uint8_t big_hndle);
#endif /* SUPPORT_BRD_ISOCHRONOUS */

#if(SUPPORT_SYNC_ISOCHRONOUS)
	/**
	 * @brief  The HCI_LE_BIG_Sync_Established event indicates that the HCI_LE_BIG_Create_Sync command has completed.
	 *
	 * @param  ptr_st_big_sync_estblshd_evnt	: [in] pointer to ble_intf_big_sync_estblshd_evnt_st that carries all event parameters.
	 */
	void (*ll_intf_le_big_sync_estblshd_evnt)(ble_intf_big_sync_estblshd_evnt_st* ptr_st_big_sync_estblshd_evnt);

	/**
	 * @brief  The HCI_LE_BIG_Sync_Lost event indicates that the Controller has either not received any PDUs on a BIG within
	 * 		   the timeout period BIG_Sync_Timeout, or the BIG has been terminated by the remote device, or the local Host
	 * 		   has terminated synchronization using the HCI_LE_BIG_Terminate_Sync command
	 *
	 * @param  rsn			: [in] Reason for termination.
	 * @param  big_hndle	: [in] BIG identifier used to identify the BIG that is terminated.
	 */
	void (*ll_intf_le_big_sync_lost_evnt)(uint8_t big_hndle, uint8_t rsn);

	/**
	 * @brief  The HCI_LE_BIGInfo_Advertising_Report event indicates that the Controller
	 * 		   has received an Advertising PDU that contained a BIGInfo field. Whenever such a PDU is received
	 *         and the Controller generates a corresponding HCI_LE_Periodic_Advertising_Report event,
	 *         it shall generate this event immediately afterwards
	 *
	 * @param  ptr_st_biginfo_rprt_event			: [in] pointer to structure that contains returned report.
	 */
	void (*ll_intf_le_biginfo_rprt_evnt)(ble_intf_biginfo_rprt_evnt_st * ptr_st_biginfo_rprt_event);
#endif /* SUPPORT_SYNC_ISOCHRONOUS */
#endif /* SUPPORT_BRD_ISOCHRONOUS || SUPPORT_SYNC_ISOCHRONOUS */

#if (SUPPORT_MASTER_CONNECTION || SUPPORT_SLAVE_CONNECTION)

	/**
	 * @brief  Event generated when a connection is terminated.
	 *
	 * @param  status			: [in] indicate if the disconnection was successful or not.
	 * @param  conn_handle_id	: [in] connection handle of the connection which was disconnected.
	 * @param  reason       	: [in] indicate the reason for the disconnection if the disconnection was successful.
	 */
	void (*ll_intf_conn_disconnect_evnt)(ble_stat_t status,
		uint16_t conn_handle_id, uint8_t reason);


	/**
	 * @brief  Used to inform the host that a new connection has been created(if both the LE Enhanced Connection Complete event and
	 * 	   LE Connection Complete event are unmasked, only the LE Enhanced Connection Complete event is generated is sent when
	 * 	   a new connection has been completed).
	 *
	 * @param  status                        : [in] indicate if the connection was successfully completed or not.
	 * @param  conn_handle_id                : [in] connection handle of the connection which was created.
	 * @param  role                          : [in] indicate whether the connection is master or slave.
	 * @param  peer_addr_type                : [in] define the address type of the peer device.
	 * @param  peer_Addr                     : [in] address of the peer device.
	 * @param  local_resolvable_private_addr : [in] resolvable private address being used by the local device for this connection (in case the local device uses the resolvable private address).
	 * @param  peer_resolvable_private_addr  : [in] resolvable private address being used by the peer device for this connection (in case the peer device uses the resolvable private address)..
	 * @param  conn_interval                 : [in] connection interval value used on the connection created.
	 * @param  conn_latency                  : [in] slave latency value for the connection created, in number of connection events.
	 * @param  supervsn_timeout	         	 : [in] connection supervision timeout value for the connection created.
	 * @param  master_clock_accuracy         : [in] master clock accuracy value (only valid for a slave).
	 */
	void (*ll_intf_le_enhanced_conn_cmplt_evnt)(ble_stat_t status,
		uint16_t conn_handle_id, ble_conn_role_e role, uint8_t peer_addr_type,
		uint8_t peer_addr[ADDRESS_SIZE],
		uint8_t local_resolvable_private_addr[ADDRESS_SIZE],
		uint8_t peer_resolvable_private_addr[ADDRESS_SIZE],
		uint16_t conn_interval, uint16_t conn_latency,
		uint16_t supervsn_timeout, uint8_t master_clock_accuracy);

	/*===== Read Remote Version Information Complete Event =====*/
	/**
	 * @brief  used to indicate the completion of the process obtaining the version information of the remote Controller.
	 *
	 * @param  status            : [in] indicate whether the Read Remote Version Information command has successfully completed.
	 * @param  conn_handle_id    : [in] connection handle of the connection for which the Read Remote Version Information command is applied.
	 * @param  version           : [in] define the specification version of the LE Controller.
	 * @param  manufacturer_name : [in] indicate the manufacturer of the remote Controller.
	 * @param  subversion        : [in] Subversion of the LMP in the remote Controller(this value is controlled by the manufacturer and is implementation dependent).
	 */
	void (*ll_intf_read_remote_version_info_cmplt_evnt)(ble_stat_t status,
		uint16_t conn_handle_id, uint8_t version,
		uint16_t manufacturer_name, uint16_t subversion);

	/**
	 * @brief  used to indicate the completion of the process of the local Controller obtaining the used features of the remote device.
	 *
	 * @param  status         : [in] indicate whether the LE Read Remote Used Features command has successfully completed.
	 * @param  conn_handle_id : [in] connection handle of the connection for which the LE Read Remote Used Features command is applied.
	 * @param  le_features    : [in] Bit Mask List of used LE features.
	 */
	void (*ll_intf_le_read_remote_used_features_cmplt_evnt)(
		ble_stat_t status, uint16_t conn_handle_id,
		uint8_t le_features[LE_FEATURES_BYTES_NO]);

	/*##### Host Flow Control HCI Group #####*/

	/**
	 * @brief  used to indicate that the Controller’s data buffers have been overflowed. This can occur if the Host has sent more packets than allowed.
	 *
	 * @param  link_type : [in] indicate whether the overflow was caused by ACL or synchronous data (in case of BLE: only ACL is used).
	 */
	void (*ll_intf_data_buffer_overflow_evnt)(uint8_t link_type);

	/*##### Controller Flow Control HCI Group #####*/

	/*##### Received ACL Data #####*/

	/**
	 * @brief  used to send the received ACL data packets from controller to host.
	 *
	 * @param  conn_handle_id                  : [in] connection handle contained in the Number of Completed Packets event to be sent to the Host.
	 * @param  *received_acl_data_packets      : [in] Array of the received ACL data packet information.
	 */
	void (*ll_intf_send_data_to_host)(uint16_t conn_handle_id,
		ble_buff_hdr_t *received_acl_data_packet);
#endif /* SUPPORT_MASTER_CONNECTION || SUPPORT_SLAVE_CONNECTION */

#if ((SUPPORT_BRD_ISOCHRONOUS) || (SUPPORT_SLAVE_CONNECTION || SUPPORT_MASTER_CONNECTION))

	/*===== Number of Completed Packets event =====*/
	/**
	 * @brief  used to send the Number of Completed Packets event to the host.
	 *
	 * @param  conn_handle_id                  : [in] connection handle contained in the Number of Completed Packets event to be sent to the Host.
	 * @param  useful_pkt_transmitted          : [in] Number of ACL Data Packets that have been transmitted for this connection handle.
	 */
	void (*ll_intf_transmit_receive_status_evnt)(uint8_t num_of_handles,
		uint16_t* conn_handle_id, uint16_t* useful_pkt_transmitted);

#endif /* (SUPPORT_BRD_ISOCHRONOUS) || (SUPPORT_SLAVE_CONNECTION || SUPPORT_MASTER_CONNECTION) */
	/*##### Device Discovery HCI Group #####*/

#if (SUPPORT_MASTER_CONNECTION || SUPPORT_EXPLCT_OBSERVER_ROLE || SUPPORT_SYNC_ISOCHRONOUS)
	/*===== LE Advertising Report event =====*/
	/**
	 * @brief  Used to indicate to the host that a Bluetooth device or multiple Bluetooth devices have responded to an active scan or received some
	 *         information during a passive scan.
	 *
	 * @param ble_intf_tot_adv_report_st : This structure contains the whole report should be sent from the link layer to the host to be reported
	 * 					When receiving advertising or scanning response
	 */
	void (*ll_intf_le_adv_report_evnt)(
		ble_intf_adv_report_data_st* le_adv_report, uint8_t num_rprts);
#endif /* SUPPORT_MASTER_CONNECTION || SUPPORT_EXPLCT_OBSERVER_ROLE || SUPPORT_SYNC_ISOCHRONOUS */

#if (SUPPORT_MASTER_CONNECTION || SUPPORT_EXPLCT_OBSERVER_ROLE || SUPPORT_SYNC_ISOCHRONOUS) && SUPPORT_PRIVACY
	/*===== LE Direct Advertising Report event =====*/
	/**
	 * @brief  Used to indicate to the host that directed advertisements have been received by the controller, where the advertiser is using a resolvable private address.
	 *
	 * @param le_dir_adv_report : This structure contains the whole report should be sent from the link layer to the host to be reported
	 * 			      When receiving direct advertisement.
	 */
	void (*ll_intf_le_dir_adv_report_evnt)(
		ble_intf_dir_adv_report_data_st* le_dir_adv_report);
#endif /* (SUPPORT_MASTER_CONNECTION || SUPPORT_EXPLCT_OBSERVER_ROLE || SUPPORT_SYNC_ISOCHRONOUS) && SUPPORT_PRIVACY */

	/*##### Connection State HCI Commands' Group #####*/

	/**
	 * @brief  indicate the completion of the process of the Link Manager obtaining the version information of the remote device associated with the Connection_Handle event parameter.
	 *
	 * @param  status 		   : [in] Connection_Update command status.
	 * @param  conn_handle_id 	   : [in] Connection Handle Id to be used to identify a connection between two Bluetooth devices.
	 * @param  conn_interval 	   : [in] Connection interval used on this connection.
	 * @param  slave_latency 	   : [in] Slave latency for the connection in number of connection events.
	 * @param  supervsn_timeout : [in] Supervision timeout for this connection.
	 */
#if (SUPPORT_MASTER_CONNECTION || SUPPORT_SLAVE_CONNECTION)
	void (*ll_intf_le_conn_update_cmplt_event)(ble_stat_t status,
		uint16_t conn_handle_id, uint16_t conn_interval,
		uint16_t slave_latency, uint16_t supervsn_timeout);
#endif /* SUPPORT_MASTER_CONNECTION || SUPPORT_SLAVE_CONNECTION */

#if SUPPORT_MASTER_CONNECTION || SUPPORT_SLAVE_CONNECTION
	/**
	 * @brief  indicate the completion of the process of the Link Manager obtaining the version information of the remote device associated with the Connection_Handle event parameter.
	 *
	 * @param  conn_handle_id 	   : [in] Connection Handle Id to be used to identify a connection.
	 * @param  interval_min 	   : [in] Minimum value of the connection interval requested by the remote device.
	 * @param  interval_max 	   : [in] Maximum value of the connection interval requested by the remote device.
	 * @param  slave_latency 	   : [in] Maximum allowed slave latency for the connection specified as the number of connection events requested by the remote device.
	 * @param  supervsn_timeout 	   : [in] Supervision timeout for the connection requested by the remote device.
	 *
	 * @retval Status (0:SUCCESS, 0xXX:ERROR_CODE).
	 */
	ble_stat_t (*ll_intf_le_remote_conn_param_req_event)(
		uint16_t conn_handle_id, uint16_t interval_min,
		uint16_t interval_max, uint16_t slave_latency,
		uint16_t supervsn_timeout);
#endif /*SUPPORT_MASTER_CONNECTION || SUPPORT_SLAVE_CONNECTION*/

	/**
	 * @brief  is used to suggest maximum packet sizes to the Controller.
	 *
	 * @param  conn_handle_id 	: [in] Connection Handle Id to be used to identify a connection.
	 * @param  max_tx_octets	: [in] The maximum number of payload octets in a Link Layer Data Channel PDU that the local Controller will send on this connection.
	 * @param  max_tx_time		: [in] The maximum time that the local Controller will take to send a Link Layer Data Channel PDU on this connection.
	 * @param  max_rx_octets	: [in] The maximum number of payload octets in a Link Layer Data Channel PDU that the local controller expects to receive on this connection.
	 * @param  max_rx_time		: [in] The maximum time that the local Controller expects to take to receive a Link Layer Data Channel PDU on this connection.
	 */
	void (*ll_intf_le_data_length_chg_event)(uint16_t conn_handle_id,
		uint16_t max_tx_octets, uint16_t max_tx_time,
		uint16_t max_rx_octets, uint16_t max_rx_time);

#if (SUPPORT_MASTER_CONNECTION || SUPPORT_SLAVE_CONNECTION)
	/**
	 * @brief  The LE PHY Update Complete Event command is used to request a change to the transmitter PHY and receiver PHY for a connection.
	 *
	 * @param subevent_code	 : [in] Subevent code for LE PHY Update Complete Event (0x0c).
	 * @param status 	 : [in] 0:SUCCESS, 0xXX:ERROR_CODE.
	 * @param conn_handle_id : [in] Connection_Handle to be used to identify a connection.(Range:0x0000-0x0EFF)
	 * @param tx_phys  	 : [in] The used PHY in the Tx
	 * @param rx_phys  	 : [in] The used PHY in the Rx
	 */
	void (*ll_intf_le_phy_update_complete_event)(ble_stat_t status,
		uint16_t conn_handle_id, uint8_t tx_phy, uint8_t rx_phy);

#endif /* (SUPPORT_MASTER_CONNECTION || SUPPORT_SLAVE_CONNECTION) */

	/*##### Authentication and Encryption HCI Group #####*/

#if (SUPPORT_LE_ENCRYPTION)
	/*================  Encryption Change Event =====================*/
	/**
	 * @brief  Used to indicate that the change of the encryption mode has been completed.
	 *
	 * @param  status		: [in] indicate whether the encryption change has occurred or failed.
	 * 				       status = 0x00, if encryption change has occurred
	 * 				       status = 0x01 - 0xFF, if encryption change has failed
	 * @param  conn_handle_id	: [in] Connection_Handle for which the link layer encryption has been enabled/disabled.
	 * @param  encrpt_enbld	: [in] This parameter is:
	 * 				       0x00 when encryption is off, and
	 * 				       ox01 when encryption is on.
	 */
	void (*ll_intf_encrpt_chng_evnt)(ble_stat_t status,
		uint16_t conn_handle_id, uint8_t encrpt_enbld);

	/*================  Encryption Key Refresh Complete Event =====================*/
	/**
	 * @brief  Used to indicate to the Host that the encryption key was refreshed on the given Connection_Handle any time encryption
	 * 	    is paused and then resumed
	 *
	 * @param  status		: [in] indicate whether the encryption key refresh has completed successfully or failed.
	 * 				       status = 0x00, if encryption key refresh has completed successfully
	 * 				       status = 0x01 - 0xFF, if encryption key refresh has failed
	 * @param  conn_handle_id	: [in] Connection Handle for the ACL connection to have the encryption key refreshed on.
	 */
	void (*ll_intf_encrpt_key_rfrsh_cmplt_evnt)(ble_stat_t status,
		uint16_t conn_handle_id);

	/*================  Authenticated Payload Timeout Expired Event =====================*/
	/**
	 * @brief  Used to indicate that a packet containing a valid MIC on the Connection_Handle was not received
	 * 	    within the LE Authenticated Payload Timeout for the LE connection.
	 *
	 * @param  conn_handle_id	: [in] Connection_Handle of the connection where the packet with a valid MIC was not
	 * 				       received within the timeout.

	 */
	void (*ll_intf_authn_pyld_tout_exprd_evnt)(uint16_t conn_handle_id);

#if SUPPORT_SLAVE_CONNECTION
	/*================  LE Long term Key Request Event =====================*/
	/**
	 * @brief  Indicate that the master device is attempting to encrypt or re-encrypt the link and is requesting the Long
	 * 	    Term Key from the Host
	 *
	 * @param  conn_handle_id	: [in] Connection Handle to identify the connection handle for which the host is requesting the long term key.
	 * @param  ptr_rand_num	: [in] A pointer to 64-bit random number.
	 * @param  encrptd_divrsfier	: [in] 16-bit encrypted diversifier.
	 *
	 * @retval Status (0:SUCCESS, 0xXX:ERROR_CODE).
	 */
	ble_stat_t (*ll_intf_le_long_trm_key_rqst_evnt)(uint16_t conn_handle_id,
		uint8_t *ptr_rand_num, uint16_t encrpt_divrsfier);

#endif /* SUPPORT_SLAVE_CONNECTION */
#endif /* SUPPORT_LE_ENCRYPTION */

#if (SUPPORT_LE_EXTENDED_ADVERTISING)
#if (SUPPORT_EXPLCT_OBSERVER_ROLE || SUPPORT_MASTER_CONNECTION || SUPPORT_SYNC_ISOCHRONOUS)
	/*===== LE Extended Advertising Report Event =====*/
	/**
	 * @brief  indicates that one or more Bluetooth devices have responded to an active scan or have broadcast advertisements
	 *         that were received during a passive scan.
	 *
	 * @param  num_of_rprts			: [in] Number of separate reports in the event.
	 * @param  ptr_adv_rprt 		: [in] pointer to the advertising reports.
	 */
	void (*ll_intf_le_extended_adv_report)(uint8_t num_of_rprts,
		ble_intf_extended_adv_rprt_data_st *ptr_adv_rprt);

	/*===== LE Extended Truncated Advertising Report Event =====*/
	/**
	 * @brief  indicates that one or more Bluetooth devices have responded to an active scan or have broadcast advertisements
	 *         that were received during a passive scan but are truncated.
	 *
	 * @param  ptr_adv_rprt 		: [in] pointer to the truncated advertising reports.
	 */
	void (*ll_intf_le_trunc_extended_adv_report)(
		ble_intf_extended_adv_rprt_data_st *ptr_adv_rprt);

	/*===== LE Scan Timeout Event =====*/
	/**
	 * @brief  indicates that scanning has ended because the duration has expired.
	 */
	void (*ll_intf_le_scan_timeout)(void);
#endif /* SUPPORT_EXPLCT_OBSERVER_ROLE || SUPPORT_MASTER_CONNECTION || SUPPORT_SYNC_ISOCHRONOUS*/

#if (SUPPORT_EXPLCT_BROADCASTER_ROLE || SUPPORT_SLAVE_CONNECTION || SUPPORT_BRD_ISOCHRONOUS)
	/*===== LE Advertising Set Terminated Event =====*/
	/**
	 * @brief  indicates that the Controller has terminated advertising in the advertising sets specified by theadv_hndl parameter.
	 *
	 * @param  status	: [in] 0  : Advertising successfully ended with a connection being created.
	 *                         OW : Advertising ended for another reason.
	 * @param  adv_hndl  : [in] Advertising_Handle in which advertising has ended.
	 * @param  conn_hndl : [in] Connection_Handle of the connection whose creation ended the advertising.
	 * @param  num_of_cmpltd_extended_events : [in] Number of completed extended advertising events transmitted by the Controller.
	 */
	void (*ll_intf_le_adv_set_terminated)(uint8_t status, uint8_t adv_hndl,
		uint16_t conn_hndl, uint8_t num_of_cmpltd_extended_events);

	/*===== LE Scan Request Received Event =====*/
	/**
	 * @brief  indicates that a SCAN_REQ PDU or an AUX_SCAN_REQ PDU has been received by the advertiser.
	 *
	 * @param  adv_hndl 	       : [in] Used to identify an advertising set.
	 * @param  scanner_addrs_type  : [in] indicates the type of the address
	 * @param  ptr_scanner_addrs   : [in] pointer to the scanner address.
	 */
	void (*ll_intf_le_scan_req_received)(uint8_t adv_hndl,
		uint8_t scanner_addrs_type, uint8_t *ptr_scanner_addrs);
#endif /* SUPPORT_EXPLCT_BROADCASTER_ROLE || SUPPORT_SLAVE_CONNECTION || SUPPORT_BRD_ISOCHRONOUS */

#if SUPPORT_LE_PERIODIC_ADVERTISING
#if (SUPPORT_EXPLCT_OBSERVER_ROLE || SUPPORT_MASTER_CONNECTION || SUPPORT_SYNC_ISOCHRONOUS)
	/*===== LE Periodic Advertising Report Event =====*/
	/**
	 * @brief  indicates that the Controller has received a Periodic Advertising packet
	 *
	 * @param  sync_handle 	: [in] used to identify the periodic advertiser from which data has been received.
	 * @param  tx_power    	: [in] tx power from the extended adv report
	 * @param  rssi 	   	: [in] Advertiser address type.
	 * @param  cte_type 	: [in] indicates the type of CTE in the periodic advertising packets.
	 *								0x00: AoA_CTE
	 *								0x01: AoD_CTE_1us_Slot
	 *								0x02: AoD_CTE_2us_Slot
	 *								0xFF: No CTE
	 * @param  data_status 	: [in] 0x00 Data complete
	 *                             0x01 Data incomplete, more data to come
	 *                             0x02 Data incomplete, data truncated, no more to come
	 *                             All other values Reserved for future use.
	 * @param  data_length 	: [in] data length
	 * @param  ptr_data     : [in] Data received from a Periodic Advertising packet.
	 */
	void (*ll_intf_le_periodic_adv_report)(uint16_t sync_handle,
		uint8_t tx_power, int8_t rssi, uint8_t cte_type, uint8_t data_status,
		uint8_t data_length, ble_buff_hdr_t *ptr_data);

	/*===== LE Periodic Advertising Sync Established =====*/
	/**
	 * @brief  Indicates that the Controller has received the first periodic advertising packet from an advertiser after the LE_Periodic_Advertising_Create_Sync Command has been sent to the Controller.
	 *
	 * @param  status						: [in] Periodic advertising sync successful/failed.
	 * @param  sync_handle 					: [in] Used to identify the periodic advertiser.
	 * @param  advertising_sid 				: [in] Value of the Advertising SID subfield in the ADI field of the PDU.
	 * @param  advertiser_address_type 		: [in] Advertiser address type.
	 * @param  ptr_advertiser_address 		: [in] Pointer to advertiser address.
	 * @param  advertiser_phy 				: [in] Advertiser PHY.
	 * @param  periodic_advertising_interval: [in] Periodic advertising interval.
	 * @param  advertiser_clock_accuracy	: [in] Clock accuracy used by advertiser.
	 */
	void (*ll_intf_le_periodic_adv_sync_estblshd)(uint8_t status,
		uint16_t sync_handle, uint8_t advertising_sid,
		uint8_t advertiser_address_type,
		uint8_t* ptr_advertiser_address, uint8_t advertiser_phy,
		uint16_t periodic_advertising_interval,
		uint8_t advertiser_clock_accuracy);

	/*===== LE Periodic Advertising Sync Lost Event =====*/
	/**
	 * @brief  indicates that the Controller has received the first periodic advertising packet from an advertiser after the LE_Periodic_Advertising_Create_Sync Command has been sent to the Controller.
	 *
	 * @param  Sync_Handle			: [in] used to identify the periodic advertiser.
	 */
	void (*ll_intf_le_periodic_adv_sync_lost)(uint16_t sync_hndl);

#if (SUPPORT_PERIODIC_SYNC_TRANSFER)
	/*===== LE Periodic Advertising Sync Transfer Received  =====*/
	/**
	 * @brief  used by the Controller to report that it has received periodic advertising synchronization
	 *		   information from the device referred to by the Connection_Handle parameter and either successfully
 	 *		   synchronized to the periodic advertising events or timed out while attempting to synchronize
	 *
 	 * @param  ptr_prdc_sync_transfer_report	: [in] Pointer to periodic advertising sync transfer report
   	 */
	void (*ll_intf_periodic_adv_sync_transfer_recieved)(
		ble_intf_prdc_adv_sync_transfer_report_st * ptr_prdc_sync_transfer_report);
#endif /* SUPPORT_PERIODIC_SYNC_TRANSFER */

#endif /* SUPPORT_EXPLCT_OBSERVER_ROLE || SUPPORT_MASTER_CONNECTION || SUPPORT_SYNC_ISOCHRONOUS*/
#endif /* SUPPORT_LE_PERIODIC_ADVERTISING */
#endif /* SUPPORT_LE_EXTENDED_ADVERTISING */

	/*=======================================================================================================================*/
	/*===============================================    BLE_5.0    =========================================================*/
	/*=======================================================================================================================*/

#if (SUPPORT_MASTER_CONNECTION || SUPPORT_SLAVE_CONNECTION)
	/*=====================  LE Channel Selection Algorithm Event  =====================*/
	/**
	 * @brief  used to indicate which channel selection algorithm is used on a data channel connection.
	 *
	 * @param  conn_handle_id   : [in] connection handle of the connection for which the channel selection algorithm is determined.
	 * @param  chnl_sel_algo	: [in] 0x00 means LE Channel Selection Algorithm #1 is used, and
	 * 				       			   0x01 means LE Channel Selection Algorithm #2 is used.
	 */
	void (*ll_intf_le_chnl_sel_algo_evnt)(uint16_t conn_handle_id,
		uint8_t chnl_sel_algo);
#endif /* (SUPPORT_MASTER_CONNECTION || SUPPORT_SLAVE_CONNECTION) */

	/* AOA_AOD HCI Events */
	/*=====================  LE Connectionless IQ Report Event  =====================*/
#if (SUPPORT_AOA_AOD)
#if (SUPPORT_EXPLCT_OBSERVER_ROLE || SUPPORT_MASTER_CONNECTION || SUPPORT_SYNC_ISOCHRONOUS)
	/**
	 * @brief  Used by the Controller to report IQ information from the CTE field of a received advertising packet containing the AUX_SYNC_IND PDU.
	 *
	 * @param  ptr_connless_iq_rprt	: [in] Pointer to the connectionless IQ report params.
	 */
	void (*ll_intf_le_connless_iq_report_evnt)(le_connless_iq_report_evnt_st *ptr_connless_iq_rprt);
#endif /* SUPPORT_EXPLCT_OBSERVER_ROLE || SUPPORT_MASTER_CONNECTION  || SUPPORT_SYNC_ISOCHRONOUS*/

#if ((SUPPORT_MASTER_CONNECTION) || (SUPPORT_SLAVE_CONNECTION))
	/*=====================  LE Connection IQ Report Event  =====================*/
	/**
	 * @brief  Used by the Controller to report the IQ samples from the Constant Tone Extension field of a received data packet.
	 *
	 * @param  ptr_conn_iq_rprt	: [in] Pointer to the connection IQ report parameters
	 */
	void (*ll_intf_le_conn_iq_report_evnt) (ble_intf_conn_iq_report_st *ptr_conn_iq_rprt);

	/*=====================  LE CTE Request Failed Event  =====================*/
	/**
	 * @brief  Used by the Controller to report an issue following a request to a peer device to reply with an LL_CTE_RSP PDU containing a CTE field.
	 *
	 * @param  cte_prcdur_status	: [in] Identify whether the LL_CTE_RSP PDU was received successfully or the peer has rejected the request.
	 * @param  conn_handle_id	: [in] Identifying the connection handle.
	 */
	void (*ll_intf_le_cte_req_failed_evnt) (uint16_t conn_handle_id, uint8_t cte_prcdur_status);
#endif /* (SUPPORT_MASTER_CONNECTION) || (SUPPORT_SLAVE_CONNECTION) || SUPPORT_SYNC_ISOCHRONOUS*/
#endif /* SUPPORT_AOA_AOD */

/*##### Custom Events HCI Group #####*/
#if (SUPPORT_SLEEP_CLOCK_ACCURCY_UPDATES && (SUPPORT_MASTER_CONNECTION || SUPPORT_SLAVE_CONNECTION))
	/*===============  LE Update Sleep Clock Accuracy Complete Event ===============*/
	/**
	 * @brief notify the Host that Sleep clock accuracy update procedure completed.
	 *
	 * @param  status			: HCI_LE_Update_Sleep_Clock_Accuracy command successfully completed.
	 * @param  sca      		: Recommanded sleep clock accuracy.
	 */
	void (*ll_intf_le_update_slp_clk_acc_cmp_evnt) (uint8_t status , uint8_t sca);

#endif /* SUPPORT_SLEEP_CLOCK_ACCURCY_UPDATES && (SUPPORT_MASTER_CONNECTION || SUPPORT_SLAVE_CONNECTION)*/

#if (SUPPORT_CONNECTED_ISOCHRONOUS &&( SUPPORT_MASTER_CONNECTION || SUPPORT_SLAVE_CONNECTION) || (SUPPORT_BRD_ISOCHRONOUS) || (SUPPORT_SYNC_ISOCHRONOUS))
	/*===============  LE Sync Event ===============*/
	/**
	 * @brief generated after the execution of CIG or BIG is completed on hardware.
	 *
	 * @param  ptr_sync_evnt_params : pointer to sync event paramters.
	 */
	void (*ll_intf_le_sync_evnt) (ble_intf_sync_evnt_st * ptr_sync_evnt_params);
#endif /*  (SUPPORT_CONNECTED_ISOCHRONOUS &&( SUPPORT_MASTER_CONNECTION || SUPPORT_SLAVE_CONNECTION) || (SUPPORT_BRD_ISOCHRONOUS) || (SUPPORT_SYNC_ISOCHRONOUS)) */

#if (SUPPORT_LE_POWER_CONTROL)
	/* LE Power Control HCI Events */
	/*=====================  LE Path Loss Threshold Event  =====================*/
	/**
	 * @brief  Used by the Controller to report a path loss threshold crossing.
	 *
	 * @param  ptr_path_loss_threshold_evnt	: [in] Pointer to path loss threshold params.
	 */
	void (*ll_intf_le_path_loss_threshold_evnt) (le_path_loss_threshold_evnt_st *ptr_path_loss_threshold_evnt);

	/*=====================  LE Transmit Power Reporting Event  =====================*/
	/**
	 * @brief  Used used to report the transmit power level on the ACL connection.
	 *
	 * @param  ptr_tx_power_report: [in] Pointer to structure containing the Tx power report params.
	 */
	void (*ll_intf_le_tx_power_reporting_evnt) (le_tx_power_report_st *ptr_tx_power_report);
#endif /* SUPPORT_LE_POWER_CONTROL */

#if (SUPPORT_AUGMENTED_BLE_MODE)
	/*===============  LE Energy Detection Complete Event ===============*/
	/**
	 * @brief generated after the execution of Energy Detection on the host provided channel Map is completed on hardware.
	 *
	 * @param  ed_values : Array of Energy Detected Values.
	 * @param  num_of_chnl : Numer of energy detection channels.
	 */
	 void (*ll_intf_le_energy_dctn_cmplt_evnt)(uint16_t* ed_values, uint8_t num_of_chnl);
	#endif /* SUPPORT_AUGMENTED_BLE_MODE */

#if ((SUPPORT_CONNECTED_ISOCHRONOUS && (SUPPORT_MASTER_CONNECTION || SUPPORT_SLAVE_CONNECTION)) || (SUPPORT_SYNC_ISOCHRONOUS))
/**
 * @brief  Send the ISO data from the controller to host.
 *
 * @param  frst_sdu_ptr  	: [in] pointer to the first received sdu_buff_hdr
 * @param  iso_conn_hndl  	: [in] the iso conn_handle  for BIS /CIS in which the SDU is recieved
 *
 * @retval None
 */
	 void (*ll_intf_send_iso_data_from_cntrlr_to_host)(const iso_sdu_buf_hdr_p frst_sdu_ptr, const uint16_t iso_conn_hndl);
#endif /* (SUPPORT_CONNECTED_ISOCHRONOUS && (SUPPORT_MASTER_CONNECTION || SUPPORT_SLAVE_CONNECTION)) || (SUPPORT_SYNC_ISOCHRONOUS) */
#if SUPPORT_LE_ENHANCED_CONN_UPDATE
	 /**
	  * @brief  Send the subrate change event to the host.
	  *
	  * @param  ptr_le_subrate_change_evnt  	: [in] pointer to struct holding the changed subrate parameters to notify the host of it.
	  *
	  * @retval None
	  */
	 void (*ll_intf_le_subrate_change_event)(const le_subrate_change_evnt_st * ptr_le_subrate_change_evnt);
#endif /* SUPPORT_LE_ENHANCED_CONN_UPDATE */

#if END_OF_RADIO_ACTIVITY_REPORTING
/**
 * @brief  Send the end of radio activity event to host.
 *
 * @param  curr_state  	: [in] the state of the current event
 * @param  nxt_state  	: [in] the state of the next event
 *
 * @retval None
 */
	void (*ll_intf_end_of_activity_evnt)(uint16_t curr_state, uint16_t nxt_state);
#endif /* END_OF_RADIO_ACTIVITY_REPORTING */
};

#if (SUPPORT_CONNECTED_ISOCHRONOUS &&( SUPPORT_MASTER_CONNECTION || SUPPORT_SLAVE_CONNECTION))
/**
 * @brief ble_intf_cig_host_param_st structure is a container to CIG parameters passed from the host
 */
typedef struct _ble_intf_cig_host_param{
	uint32_t sdu_intrv_m_to_s;			/* The interval, in us, of periodic SDUs M-> S */
	uint32_t sdu_intrv_s_to_m;			/* The interval, in us, of periodic SDUs S->M */
	uint16_t iso_interval;  			/* Time duration of the isochronous interval */
	uint16_t max_trnsprt_ltncy_m_to_s;	/* Maximum time, in ms, for an SDU to be sent from the master to slave */
	uint16_t max_trnsprt_ltncy_s_to_m;	/* Maximum time, in ms, for an SDU to be sent from the   slave to master */
	uint8_t cig_id;						/* CIG Identifer */
	uint8_t sca;						/* The worst-case sleep clock accuracy of all the slaves */
	uint8_t pack;						/* the preferred method of arranging subevents of multiple CISes */
	uint8_t framing;					/* Framed or Unframed SDUs */
	uint8_t cis_cnt;					/* Total number of CISes in the CIG being added or modified */
	uint8_t ft_m_to_s; 					/* The flush timeout in multiples of ISO_Interval for each payload sent from the master to slave */
	uint8_t ft_s_to_m; 					/* The flush timeout in multiples of ISO_Interval for each payload sent from     the slave to master */
} ble_intf_cig_host_param_st;

/**
 * @brief ble_intf_cis_host_param_st structure is a container to CIS(es) parameters passed from the host
 */
typedef struct _ble_intf_cis_host_param{
	uint8_t cis_id;      					/* Maximum number of subevents in each isochronous interval of CIS*/
	uint8_t max_sdu_m_to_s_least;			/* max pdu size from master to slave Least OCTET*/
	uint8_t max_sdu_m_to_s_most;			/* max pdu size from master to slave Most OCTET */
	uint8_t max_sdu_s_to_m_least;			/* max pdu size from slave to master Least OCTET */
	uint8_t max_sdu_s_to_m_most;			/* max pdu size from slave to master Most OCTET */
	uint8_t phy_m_to_s;				/* The used PHY from master to slave */
	uint8_t phy_s_to_m;				/* The used PHY from slave to master */
	uint8_t rtn_m_to_s;				/* The recommendation retransmission effort from master to slave */
	uint8_t rtn_s_to_m;				/* The recommendation retransmission effort from slave to master */
} ble_intf_cis_host_param_st;

/**
 * @brief ble_intf_cis_host_param_test_st structure is a container to CIS(es) parameters passed from the host
 */
typedef struct _ble_intf_cis_host_param_test{
	uint8_t cis_id;      					/* Maximum number of subevents in each isochronous interval of CIS*/
	uint8_t nse;      					/* Maximum number of subevents in each isochronous interval of CIS*/
	uint8_t max_sdu_m_to_s_least;			/* Maximum size, in octets, of an SDU from the master Host Least OCTET */
	uint8_t max_sdu_m_to_s_most;			/* Maximum size, in octets, of an SDU from the master Host Most OCTET */
	uint8_t max_sdu_s_to_m_least;			/* Maximum size, in octets, of an SDU from the slave Host Least OCTET */
	uint8_t max_sdu_s_to_m_most;			/* Maximum size, in octets, of an SDU from the slave Host Most OCTET */
	uint8_t max_pdu_m_to_s_least;			/* max pdu size from master to slave Least OCTET */
	uint8_t max_pdu_m_to_s_most;			/* max pdu size from master to slave Most OCTET */
	uint8_t max_pdu_s_to_m_least;			/* max pdu size from slave to master Least OCTET */
	uint8_t max_pdu_s_to_m_most;			/* max pdu size from slave to master Most OCTET */
	uint8_t phy_m_to_s;				/* The used PHY from master to slave */
	uint8_t phy_s_to_m;				/* The used PHY from slave to master */
	uint8_t bn_m_to_s;					/* burst number from master to slave */
	uint8_t bn_s_to_m;					/* burst number from slave to master */
} ble_intf_cis_host_param_test_st;

/**
 * @brief ble_intf_set_cig_params_comman_cmd_st structure is a container to CIS(es)/CIG parameters passed from the host
 */
typedef struct _ble_intf_set_cig_params_common_cmd_st {
	
	ble_intf_cis_host_param_st* cis_host_params;
	ble_intf_cis_host_param_test_st* cis_host_params_test;
	ble_intf_cig_host_param_st cig_host_params;
	uint8_t slv_cis_id;
} ble_intf_set_cig_params_comman_cmd_st;

/**
 * @brief ble_intf_create_cis_cmd_st structure used to carry map between CISes and their corresponding ACL
 */
typedef struct _ble_intf_create_cis_cmd_hndl_st{
	uint16_t cis_conn_hndl;	/* CIS connection handles */
	uint16_t acl_conn_hndl;	/* ACL connection handles */
} ble_intf_create_cis_cmd_hndl_st;

/**
 * @brief ble_intf_create_cis_cmd_st structure used to create a CIS stream
 */
typedef struct _ble_intf_create_cis_cmd_st{
	ble_intf_create_cis_cmd_hndl_st* create_cis_hndls;	/* CIS to ACL connection handles */
	uint8_t cis_cnt;		/* The number of CISes to be created */
} ble_intf_create_cis_cmd_st;
#endif/* SUPPORT_CONNECTED_ISOCHRONOUS &&( SUPPORT_MASTER_CONNECTION || SUPPORT_SLAVE_CONNECTION */


#if (SUPPORT_BRD_ISOCHRONOUS || SUPPORT_SYNC_ISOCHRONOUS)
#if(SUPPORT_SYNC_ISOCHRONOUS)
/**
 * @brief ble_intf_big_create_sync_cmd_st structure used to create a BIG SYNC
 */
typedef struct _ble_intf_big_create_sync_cmd_st
{
	uint8_t *bis;  			   							   /* List of indices of BISes*/
	uint16_t big_sync_timeout; 							   /* Synchronization timeout for the BIG */
	uint16_t sync_hndle; 	   							   /* Used to identify the periodic advertising train*/
	uint8_t mse; 			   							  /* the maximum number of subevents that a Controller should use to receive data payloads in each interval for a BIS */
	ble_intf_big_common_sync_bc_cmd_st big_common_sync_bc; /* common parameters between the synchronizer and broadcaster */
} ble_intf_big_create_sync_cmd_st;
#endif/* SUPPORT_SYNC_ISOCHRONOUS */

/**
 * @brief ble_intf_create_big_cmd_st structure used to create a BIG
 */
typedef struct _ble_intf_create_big_cmd_st
{
	uint16_t max_trnsprt_ltncy;
	uint8_t rtn;   	  /* specifies the number of times every PDU should be retransmitted*/
} ble_intf_create_big_cmd_st;

/**
 * @brief ble_intf_create_big_cmd_un union governing the create BIG commands
 */
typedef union _ble_intf_create_big_cmd_un{
	ble_intf_create_big_test_cmd_st create_big_test_cmd_st;
	ble_intf_create_big_cmd_st create_big_cmd_st;
} ble_intf_create_big_cmd_un;

/**
 * @brief ble_intf_create_big_st Structure containing the Create BIG params
 */
typedef struct _ble_intf_create_big_st{
	/* Common parameters of create big and create big test */
	ble_intf_create_big_common_param_cmd_st create_big_common_param;
	/* choose between create_big and create_big_test */
	ble_intf_create_big_cmd_un	create_big_cmd_un;
} ble_intf_create_big_st;

#endif/* SUPPORT_BRD_ISOCHRONOUS || SUPPORT_SYNC_ISOCHRONOUS */

#if((SUPPORT_CONNECTED_ISOCHRONOUS && (SUPPORT_MASTER_CONNECTION || SUPPORT_SLAVE_CONNECTION)) || (SUPPORT_BRD_ISOCHRONOUS || SUPPORT_SYNC_ISOCHRONOUS))
/**
 * @brief ble_intf_read_iso_link_cmd_st is a container to the output parameters used in read_iso_link_quality cmd
 */
typedef struct _ble_intf_read_iso_link_cmd_st{
	uint32_t crc_error_pkt_cntr;		/*This counter is incremented when The Link Layer receives a packet with a CRC error.*/
	uint32_t rx_unreceived_pkt_cntr;    /*This counter is incremented when The Link Layer does not receive a specific payload by its flush point (on a CIS) or the end of the event it is associated with (on a BIS)*/
	uint32_t tx_unacked_pkt_cntr;       /*This counter is incremented when The Link Layer does not receive an acknowledgment for a CIS Data PDU that it transmitted at least once by its flush point*/
	uint32_t tx_flshed_pkt_cntr;        /*This counter is incremented when The Link Layer does not transmit a specific payload by its flush point.*/
	uint32_t retrans_pkt_cntr;          /*This counter is incremented when The Link Layer retransmits a CIS Data PDU.*/
	uint32_t duplicate_pkt_cntr;        /*This counter is incremented when The Link Layer receives a retransmission of a CIS Data PDU.*/
	uint32_t tx_last_se_pkt_cntr;       /*This counter is incremented when The Link Layer transmits a CIS Data PDU in the last subevent of a CIS event*/
} ble_intf_read_iso_link_cmd_st;

/**
 * @brief ble_intf_setup_iso_data_path is a structure containing the ISO Setup Data Path params
 */
typedef struct _ble_intf_setup_iso_data_path{
	uint8_t* codec_config;					/* Codec-specific configuration data */
	uint32_t controller_delay;				/* Controller delay in microseconds */
	uint8_t codec_id[ISO_CODEC_ID_SIZE];	/*  Octet 0 See Assigned Numbers for Coding Format
											 *  Octet 1 to 2 Company ID, see Assigned Numbers for Company Identifier. (Shall be ignored if octet 0 is not 0xFF.)
											 *  Octet 3 to 4 Vendor-defined codec ID. (Shall be ignored if octet 0 is not 0xFF.)
	 	 	 	 	 	 	 	 	 	 	 */
	uint8_t data_path_dir;					/* input or output from from controller respective */
	uint8_t data_path_id;					/* HCI or vendor specific */
	uint8_t codec_config_length;			/* Length of codec configuration */
} ble_intf_setup_iso_data_path;
#endif/* (SUPPORT_CONNECTED_ISOCHRONOUS || SUPPORT_BROADCAST_ISOCHRONOUS ) */

/**
 * @brief Union containing the set parameters commands
 */
typedef union _hci_cmds_params_un
{
#if (SUPPORT_AOA_AOD)
#if (SUPPORT_EXPLCT_BROADCASTER_ROLE)
	le_set_connless_cte_tx_params_cmd_st le_set_connless_cte_tx_params_cmd;
	le_set_connless_cte_tx_enable_cmd_st le_set_connless_cte_tx_enable_cmd;
#endif /* (SUPPORT_EXPLCT_BROADCASTER_ROLE) */
#if (SUPPORT_EXPLCT_OBSERVER_ROLE)
	le_set_connless_iq_sampling_enable_cmd_st le_set_connless_iq_sampling_enable_cmd;
#endif /* (SUPPORT_EXPLCT_OBSERVER_ROLE) */
#if ((SUPPORT_MASTER_CONNECTION) || (SUPPORT_SLAVE_CONNECTION))
	le_set_conn_cte_rx_params_cmd_st le_set_conn_cte_rx_params_cmd;
	le_set_conn_cte_req_enable_cmd_st le_set_conn_cte_req_enable_cmd;
	le_set_conn_cte_tx_params_cmd_st le_set_conn_cte_tx_params_cmd;
	le_set_conn_cte_rsp_enable_cmd_st le_set_conn_cte_rsp_enable_cmd;
#endif /* (SUPPORT_MASTER_CONNECTION) || (SUPPORT_SLAVE_CONNECTION) */
#endif /* SUPPORT_AOA_AOD */
#if (SUPPORT_AOA_AOD)
	le_rx_test_v3_cmd_st le_rx_test_v3_cmd;
	le_tx_test_v3_cmd_st le_tx_test_v3_cmd;
#endif /* SUPPORT_AOA_AOD */
	le_set_adv_params_cmd_st le_set_adv_params_cmd;
	le_create_conn_cmd_st le_create_conn_cmd;
	le_set_scn_params_cmd_st le_set_scn_params_cmd;
	le_rmt_conn_param_req_rply_cmd_st le_rmt_conn_param_req_rply_cmd;
	/* CONNECTION ISOCHRONOUS */
#if (SUPPORT_CONNECTED_ISOCHRONOUS &&( SUPPORT_MASTER_CONNECTION || SUPPORT_SLAVE_CONNECTION))
	ble_intf_set_cig_params_comman_cmd_st ble_intf_set_cig_params_common_cmd;
	ble_intf_create_cis_cmd_st ble_intf_create_cis_cmd;
//	ble_intf_set_cig_params_comman_cmd_st ble_intf_set_cig_params_test_cmd;
#endif	/* CONNECTION ISOCHRONOUS */
	/* BROADCAST ISOCHRONOUS */
#if (SUPPORT_BRD_ISOCHRONOUS || SUPPORT_SYNC_ISOCHRONOUS)
/* SCANNER OBSERVER ROLE */
#if(SUPPORT_SYNC_ISOCHRONOUS)
	ble_intf_big_create_sync_cmd_st ble_intf_big_create_sync_cmd;
#endif/* SCANNER OBSERVER ROLE */
/* ADVERTISER BC ROLE */
#if(SUPPORT_BRD_ISOCHRONOUS)
	ble_intf_create_big_st ble_intf_create_big_cmd;
#endif/* ADVERTISER BC ROLE */
#endif/* BROADCAST ISOCHRONOUS */
#if((SUPPORT_CONNECTED_ISOCHRONOUS && (SUPPORT_MASTER_CONNECTION || SUPPORT_SLAVE_CONNECTION))|| (SUPPORT_BRD_ISOCHRONOUS || SUPPORT_SYNC_ISOCHRONOUS))
	ble_intf_setup_iso_data_path ble_intf_setup_iso_data_path_cmd;
#endif /* (SUPPORT_CONNECTED_ISOCHRONOUS && (SUPPORT_MASTER_CONNECTION || SUPPORT_SLAVE_CONNECTION)) */
#if (SUPPORT_LE_POWER_CONTROL)
	le_enhanced_read_tx_pwr_lvl_cmd_st le_enhanced_read_tx_pwr_lvl_cmd;
	le_read_remote_tx_pwr_lvl_cmd_st le_read_remote_tx_pwr_lvl_cmd;
	le_set_path_loss_reporting_params_cmd_st le_set_path_loss_reporting_params_cmd;
	le_set_path_loss_reporting_enable_cmd_st le_set_path_loss_reporting_enable_cmd;
	le_set_tx_pwr_reporting_enable_cmd_st le_set_tx_pwr_reporting_enable_cmd;
	le_tx_test_v4_cmd_st le_tx_test_v4_cmd;
#endif /* SUPPORT_LE_POWER_CONTROL */
#if (SUPPORT_MASTER_CONNECTION || SUPPORT_SLAVE_CONNECTION)
	le_set_conn_tx_pwr_lvl_cmd_st le_set_conn_tx_pwr_lvl_cmd;
#endif /* SUPPORT_MASTER_CONNECTION || SUPPORT_SLAVE_CONNECTION */
} hci_cmds_params_un;




#if SUPPORT_LE_ENHANCED_CONN_UPDATE


/* struct holding the default subrate values requested by master's host also used to hold the values requested by the host from le_subrate_req */
typedef struct subrate_default_params_st{
  uint16_t subrate_min;     /*the minimum subrate factor allowed in requests by a Peripheral Range: 0x0001 to 0x01F4*/
  uint16_t subrate_max;     /*the maximum subrate factor allowed in requests by a Peripheral Range: 0x0001 to 0x01F4*/
  uint16_t max_latency;     /*the maximum slavePeripheral latency allowed in requests by a Peripheral,in units of subrated connection intervals Range: 0x0000 to 0x01F3*/
  uint16_t continuation_num;/*the minimum number of underlying connection events to remain active after a packet is sent or received in requests by a Peripheral Range: 0x0000 to 0x01F3*/
  uint16_t supervisionTO;   /*the maximum supervision timeout allowed in requests by a Peripheral Range: 0x000A to 0x0C80*/
}subrate_default_params_t;

#endif /* SUPPORT_LE_ENHANCED_CONN_UPDATE */

/* Exported  Definition ------------------------------------------------------*/
#if ((SUPPORT_CONNECTED_ISOCHRONOUS && (SUPPORT_MASTER_CONNECTION || SUPPORT_SLAVE_CONNECTION)) || (SUPPORT_SYNC_ISOCHRONOUS))
typedef void (*vendor_specific_from_cntrl_to_host_cbk)(const iso_sdu_buf_hdr_p, const uint16_t conn_hndl);
#endif /* ((SUPPORT_CONNECTED_ISOCHRONOUS && (SUPPORT_MASTER_CONNECTION || SUPPORT_SLAVE_CONNECTION)) || (SUPPORT_SYNC_ISOCHRONOUS)) */

#if SUPPORT_HCI_EVENT_ONLY
typedef uint8_t (*hst_cbk)(ble_buff_hdr_t *ptr_evnt_hdr);
typedef void (*hst_cbk_queue_full)(ble_buff_hdr_t *ptr_evnt_hdr);
#endif /* SUPPORT_HCI_EVENT_ONLY */

#if (SUPPORT_CONNECTED_ISOCHRONOUS && (SUPPORT_MASTER_CONNECTION || SUPPORT_SLAVE_CONNECTION))
/* missed cig events callback function type definition */
typedef void (*hst_cig_missed_evnt_cbk)(uint8_t cig_id, uint8_t missed_intrvs, uint32_t nxt_anchor_pnt);
#endif /* (SUPPORT_CONNECTED_ISOCHRONOUS && (SUPPORT_MASTER_CONNECTION || SUPPORT_SLAVE_CONNECTION)) */

#if (SUPPORT_BRD_ISOCHRONOUS || SUPPORT_SYNC_ISOCHRONOUS)
/* missed big events callback function type definition */
typedef void (*hst_big_missed_evnt_cbk)(uint8_t big_hndl, uint8_t missed_intrvs, uint32_t nxt_anchor_pnt);
#endif /* (SUPPORT_BRD_ISOCHRONOUS || SUPPORT_SYNC_ISOCHRONOUS) */

/*##### Device Setup HCI Commands' Group #####*/
/** @ingroup  device_setup
 *  @{
 */
/*========================================================================================================*/
/*=======================================  ll_intf Initialization ========================================*/
/*========================================================================================================*/
/**
 * @brief Initializes the LL stack
 *
 * @param p_dispatch_tbl : [in] Dispatch table for HCI events
 *
 * @retval ble_stat_t : Command status to be sent to the Host.
 */
ble_stat_t ll_intf_init(const struct hci_dispatch_tbl* p_dispatch_tbl);


/*========================================================================================================*/
/*============================  HCI Commands' Groups (Based on Functionality) ============================*/
/*========================================================================================================*/

/**
 * @brief  Reset the controller and the Link Layer on an LE controller .
 *
 * @retval ble_stat_t : Command status to be sent to the Host.
 */
ble_stat_t ll_intf_reset(void);

/** @}
*/

/*##### Controller Flow Control HCI Commands' Group #####*/
/** @ingroup  controller_info
 *  @{
 */
#if(SUPPORT_SLAVE_CONNECTION || SUPPORT_MASTER_CONNECTION)
/**
 * @brief  Read the maximum size of the data portion of HCI LE ACL Data Packets sent from the Host to the Controller .
 *
 * @param  le_acl_data_pkt_length     : [out] Max length (in octets) of the data portion of each HCI ACL Data Packet that the controller is able to accept .
 * @param  total_num_le_acl_data_pkts : [out] Total number of HCI ACL Data Packets that can be stored in the data buffers of the controller .
 *
 * @retval ble_stat_t : Command status to be sent to the Host.
 */
ble_stat_t ll_intf_le_read_buffer_size(uint16_t *le_acl_data_pkt_length,
	uint8_t *total_num_le_acl_data_pkts);
#endif /*(SUPPORT_SLAVE_CONNECTION || SUPPORT_MASTER_CONNECTION)*/
/*##### Controller Information HCI Commands' Group #####*/

/**
 * @brief  Read the values of the version information of the local controller .
 *
 * @param  hci_version    	 : [out] Defines the version information of the HCI layer .
 * @param  hci_revision	 : [out] Revision of the Current HCI in the BE/EDR Controller .
 * @param  lmp_version		 : [out] Version of the Current LMP or PAL in the Controller .
 * @param  manfacturer_name     : [out] Manufacturer Name of the BR/EDR Controller .
 * @param  lmp_subversion	 : [out] Subversion of the Current LMP or PAL in the Controller .
 *
 * @retval ble_stat_t : Command status to be sent to the Host.
 */
ble_stat_t ll_intf_read_local_ver_info(uint8_t *hci_version,
	uint8_t *hci_revision, uint8_t *lmp_version, uint8_t *manfacturer_name,
	uint8_t *lmp_subversion);

/**
 * @brief  Read the version information of the controller .
 *
 * @param  ptr_vrsn  : [out] Defines the controller version information.
 * @param  length     : [in] the length of the sent array to be written.
 *
 * @retval ble_stat_t : Command status to be sent to the Host.
 */
ble_stat_t ll_intf_read_cntrlr_ver_info(uint8_t *ptr_vrsn, uint8_t length);

/**
 * @brief  Read the list of HCI commands supported for the local controller
 * 		   (It is implied that if a command is listed as supported, the feature underlying that command is also supported) .
 *
 * @param  supported_cmds : [out] A bit mask for each HCI command, where:
 * 			     If the controller sets a bit to 1, then the controller supports the corresponding command and the features required for the comman, and
 * 			     If the controller sets a bit to 0, then this command is unsupported or undefined command .
 *
 * @retval ble_stat_t : Command status to be sent to the Host.
 */
ble_stat_t ll_intf_read_local_supported_cmds(uint8_t supported_cmds[64]);

/**
 * @brief  Read a list of the supported features for the local BR/EDR Controller including the LE Supported feature .
 *
 * @param  lmp_features : [out] Bit Mask List of LMP features .
 *
 * @retval ble_stat_t : Command status to be sent to the Host.
 */
ble_stat_t ll_intf_read_local_supported_features(uint8_t lmp_features[8]);

/**
 * @brief  Read the list of the supported LE features for the Controller .
 *
 * @param  le_features : [out] Bit Mask List of supported LE features .
 *
 * @retval ble_stat_t : Command status to be sent to the Host.
 */
ble_stat_t ll_intf_le_read_local_supported_features(
	uint8_t le_features[LE_FEATURES_BYTES_NO]);

/**
 * @brief  Read the Public Device Address of the LE controller .Reset the controller and the Link Layer on an LE controller .
 *
 * @param  bd_addr : [out] Public address of the LE controller .
 *
 * @retval ble_stat_t : Command status to be sent to the Host .
 */
ble_stat_t ll_intf_read_bd_addr(uint8_t bd_addr[6]);

/*===============  Write BD_ADDR Command ===============*/

/**
 * @brief  write the Public Device Address of the LE controller .
 *
 * @param  bd_addr : [in] Public address of the LE controller .
 *
 * @retval ble_stat_t : Command status to be sent to the Host .
 */
ble_stat_t ll_intf_write_bd_addr(uint8_t* bd_addr);

/**
 * @brief  Read the states and state combinations that the link layer supports .
 *
 * @param  le_states : [out] Bit Mask List of supported LE states and state combinations .
 *
 * @retval ble_stat_t : Command status to be sent to the Host.
 */
ble_stat_t ll_intf_le_read_supported_states(uint8_t le_states[8]);

#if(SUPPORT_SLAVE_CONNECTION || SUPPORT_MASTER_CONNECTION)
/**
 * @brief  Allow the Host to read the Controller maximum supported payload octets and packet duration times for transmission and reception .
 *
 * @param  supported_max_tx_octets : [out] Max number of payload octets that the local Controller supports for transmission of a single LL Data Channel PDU .
 * @param  supported_max_tx_time   : [out] Max time, in microseconds, that the local Controller supports for transmission of a single LL Data Channel PDU .
 * @param  supported_max_rx_octets : [out] Max number of payload octets that the local Controller supports for reception of a single LL Data Channel PDU .
 * @param  supported_max_rx_time   : [out] Max time, in microseconds, that the local Controller supports for reception of a single LL Data Channel PDU .
 *
 * @retval ble_stat_t : Command status to be sent to the Host.
 */
ble_stat_t ll_intf_le_read_max_data_length(uint8_t *supported_max_tx_octets,
	uint8_t *supported_max_tx_time, uint8_t *supported_max_rx_octets,
	uint8_t *supported_max_rx_time);
#endif /* SUPPORT_SLAVE_CONNECTION || SUPPORT_MASTER_CONNECTION */

/** @}
*/
/*##### Controller Configuration HCI Commands' Group #####*/
/** @ingroup  adv_cfg
 *  @{
 */
#if(SUPPORT_EXPLCT_BROADCASTER_ROLE || SUPPORT_SLAVE_CONNECTION || SUPPORT_BRD_ISOCHRONOUS)
/**
 * @brief  Set the advertising parameters, sent by the host, in the controller.
 *
 * @param  ptr_hst_adv_params 	: [in] Structure containing the host adv params.
 *
 * @retval ble_stat_t : Command status to be sent to the Host.
 */
ble_stat_t ll_intf_le_set_adv_params(le_set_adv_params_cmd_st *ptr_hst_adv_params);

/**
 * @brief  Set the data used in advertising packets that have a data field. This data is sent by the Host to the Controller.
 *
 * @param  adv_data_length 	: [in] Number of significant octets in the advertising data command parameter.
 * @param  adv_data			: [in] Advertising data sent by the host to be sent in the advertising packets.
 *
 * @retval ble_stat_t : Command status to be sent to the Host.
 */
ble_stat_t ll_intf_le_set_adv_data(uint8_t adv_data_length,
	uint8_t adv_data[31]);
#endif /* SUPPORT_EXPLCT_BROADCASTER_ROLE || SUPPORT_SLAVE_CONNECTION || SUPPORT_BRD_ISOCHRONOUS */

#if (SUPPORT_SLAVE_CONNECTION || SUPPORT_EXPLCT_BROADCASTER_ROLE)
/**
 * @brief  Set the data used in Scanning Packets that have a data field. This data is sent by the Host to the Controller.
 *
 * @param  scan_rsp_data_length : [in] Number of significant octets in the scan response data command parameter.
 * @param  scan_rsp_data		: [in] Scanning response data sent by the host to be sent in the scanning packets.
 *
 * @retval ble_stat_t : Command status to be sent to the Host.
 */
ble_stat_t ll_intf_le_set_scan_rsp_data(uint8_t scan_rsp_data_length,
	uint8_t scan_rsp_data[31]);
#endif /* SUPPORT_SLAVE_CONNECTION || SUPPORT_EXPLCT_BROADCASTER_ROLE */

#if(SUPPORT_EXPLCT_BROADCASTER_ROLE || SUPPORT_SLAVE_CONNECTION || SUPPORT_BRD_ISOCHRONOUS)
/**
 * @brief  Command the controller to start or stop advertising based on the Host's request.
 *
 * @param  adv_enable : [in] If 0x00, advertising is disabled.
 * 			     If 0x01, advertising is enabled.
 *
 * @retval ble_stat_t : Command status to be sent to the Host.
 */
ble_stat_t ll_intf_le_set_adv_enable(uint8_t adv_enable);
#endif /* SUPPORT_EXPLCT_BROADCASTER_ROLE || SUPPORT_SLAVE_CONNECTION || SUPPORT_BRD_ISOCHRONOUS */

/** @}
*/

/** @ingroup  controller_info
 *  @{
 */
/**
 * @brief  Set the LE Random Device Address in the Controller. This address is sent by the Host.
 *
 * @param  random_addr : [in] Random Device Address sent by the Host to the Controller.
 *
 * @retval ble_stat_t : Command status to be sent to the Host.
 */
ble_stat_t ll_intf_le_set_random_addr(uint8_t random_addr[6]);
/**@}
 */

#if (SUPPORT_PRIVACY)
/*##### Controller Configuration HCI Commands' Group #####*/
/** @ingroup  privacy_cfg
 *  @{
 */
/**
 * @brief  Set the length of time the controller uses a Resolvable Private Address before a new resolvable
 private address is generated and starts being used.
 *
 * @param  rpa_timeout : [in] Resolvable Private Address timeout measured in seconds.
 *
 * @retval ble_stat_t : Command status to be sent to the Host.
 */
/**@}
 */
ble_stat_t ll_intf_le_set_resolvable_private_addr_timeout(uint16_t rpa_timeout);

#endif /* SUPPORT_PRIVACY */

/*##### Device Discovery HCI Commands' Group #####*/
/** @ingroup  scn_cfg
 *  @{
 */
#if(SUPPORT_MASTER_CONNECTION || SUPPORT_EXPLCT_OBSERVER_ROLE)
/**
 * @brief  Set the scan parameters, sent by the Host,in the controller.
 *
 * @param  ptr_hst_scn_params : [in] Pointer to the set scan command parameters.
 *
 * @retval ble_stat_t : Command status to be sent to the Host.
 */
ble_stat_t ll_intf_le_set_scan_params(le_set_scn_params_cmd_st *ptr_hst_scn_params);

/**
 * @brief  Command the controller to start or stop scanning based on the Host's request.
 *
 * @param  scan_enable 		: [in] 	If 0x00, scanning is disabled,If 0x01, scanning is enabled.
 * @param  filter_duplicates 	: [in] 	control whether the LL should filter out duplicate advertising reports to the Host, or if the LL should generate advertising reports for each packet received.
 *
 * @retval ble_stat_t : Command status to be sent to the Host.
 */
ble_stat_t ll_intf_le_set_scan_enable(uint8_t scan_enable,
	uint8_t filter_duplicates);
/**@}
 */
#endif /* SUPPORT_MASTER_CONNECTION || SUPPORT_EXPLCT_OBSERVER_ROLE */

/*##### Connection Setup HCI Commands' Group #####*/
/** @ingroup  Conn_cfg Connection Commands
 *  @{
 */
#if(SUPPORT_MASTER_CONNECTION)
/**
 * @brief  Used to create a LL connection to a connectable advertiser.
 *
 * @param  ptr_hst_init_params	: [in] Pointer to the create connection command parameters.
 *
 * @retval ble_stat_t : Command status to be sent to the Host.
 */
ble_stat_t ll_intf_le_create_conn(le_create_conn_cmd_st *ptr_hst_init_params);

/**
 * @brief  Used to cancel the "LE_Create_Connection" Command.
 *
 * @retval ble_stat_t : Command status to be sent to the Host.
 */
ble_stat_t ll_intf_le_create_conn_cancel(void);
#endif /* SUPPORT_MASTER_CONNECTION */

#if(SUPPORT_MASTER_CONNECTION || SUPPORT_SLAVE_CONNECTION)
/**
 * @brief  Used to terminate an existing connection.
 *
 * @param  conn_handle_id	: [in] Connection_Handle for the connection being disconnected.
 * @param  reason      		: [in] indicate the reason for ending the connection.
 *
 * @retval ble_stat_t : Command status to be sent to the Host.
 */
ble_stat_t ll_intf_disconnect(uint16_t conn_handle_id, uint8_t reason);
#endif
/**  @}
*/
/*##### Physical Links HCI Commands' Group #####*/

#if SUPPORT_MASTER_CONNECTION	||																			\
 	(SUPPORT_SLAVE_CONNECTION && SUPPORT_CHANNEL_CLASSIFICATION)	||  									\
	(SUPPORT_LE_EXTENDED_ADVERTISING && (SUPPORT_SLAVE_CONNECTION || SUPPORT_EXPLCT_BROADCASTER_ROLE))
/** @ingroup  chnlmap_cfg  Channel Map Commands
 * @{
 */
/**
 * @brief  Used to allow the Host to specify a channel classification for data channels based on its "local information".
 *
 * @param  channel_map : [in] Bit Mask parameter to classify each LL channel index.
 * 			      If a bit is set to 0, then the corresponding  LL channel index is bad, and
 *			      If a bit is set to 1, then the corresponding  LL channel index is unknown.
 *
 * @retval ble_stat_t : Command status to be sent to the Host.
 */
ble_stat_t ll_intf_le_set_host_channel_classification(uint8_t channel_map[]);
/**@}
 */
#endif /* SUPPORT_MASTER_CONNECTION || (SUPPORT_SLAVE_CONNECTION && SUPPORT_CHANNEL_CLASSIFICATION) || (SUPPORT_EXPLCT_BROADCASTER_ROLE && SUPPORT_LE_EXTENDED_ADVERTISING) */

/*##### Host Flow Control  HCI Commands' Group #####*/
/** @ingroup  white_list_cfg White list Commands
 *  @{
 */
/**
 * @brief  Add a single device to the white list stored in the Controller.
 *
 * @param  addr_type	: [in] Address type of the device to be added to the white list of the controller.
 * @param  addr		: [in] Public Device Address or Random Device Address of the device to be added to the white list.
 *
 * @retval ble_stat_t : Command status to be sent to the Host.
 */
ble_stat_t ll_intf_le_add_device_white_list(uint8_t addr_type, uint8_t addr[6]);

/**
 * @brief  Remove a single device from the white list stored in the Controller.
 *
 * @param  addr_type 	 : [in] Address type of the device to be added to the white list of the controller.
 * @param  addr		 : [in] Public Device Address or Random Device Address of the device to be removed from the white list.
 *
 * @retval ble_stat_t : Command status to be sent to the Host.
 */
ble_stat_t ll_intf_le_remove_device_white_list(uint8_t addr_type,
	uint8_t addr[6]);

/**
 * @brief  Clear the white list stored in the Controller.
 *
 * @retval ble_stat_t : Command status to be sent to the Host.
 */
ble_stat_t ll_intf_le_clear_white_list(void);

/**
 * @brief  Read the total number of white list entries that can be stored in the Controller.
 *
 * @param  white_list_size : [out] Total number of white list entries that can be stored in the Controller.
 *
 * @retval ble_stat_t : Command status to be sent to the Host.
 */
ble_stat_t ll_intf_le_read_white_list_size(uint8_t *white_list_size);

/**  @}
*/

/** @ingroup  privacy_cfg
 *  @{
 */

#if (SUPPORT_PRIVACY &&(SUPPORT_EXPLCT_BROADCASTER_ROLE || SUPPORT_SLAVE_CONNECTION || SUPPORT_BRD_ISOCHRONOUS))
/**
 * @brief  Set the reasons that trigger generating RPA
 * bit0 : regenerate when adv data change
 * bit1 : regenerate when scan response data change
 *
 * @param[in]  handler		handler to the advertising set to assign its change_reason parameter
 * @param[in]  chng_resns   the new change_reason value bit 0 : Change the address whenever the advertising data changes bit 1 : Change the address whenever the scan response data changes
 *
 * @retval ble_stat_t : Command status to be sent to the Host.
 */
ble_stat_t ll_intf_le_set_data_related_address_changes_command(uint8_t handler, uint8_t chng_resns);
#endif /*SUPPORT_PRIVACY &&(SUPPORT_EXPLCT_BROADCASTER_ROLE || SUPPORT_SLAVE_CONNECTION || SUPPORT_BRD_ISOCHRONOUS)*/


#if (SUPPORT_PRIVACY)
/**
 * @brief  Used to add one device to the list of address translations used to resolve Resolvable Private
 * 	   Addresses in the Controller
 *
 * @param  peer_id_addr_type	: [in] Peer address type whether public or random (static).
 * @param  peer_id_addr		: [in] Public or Random (static) Identity address of the peer device.
 * @param  peer_irk		: [in] A pointer to the IRK of the peer device.
 * @param  lcl_irk		: [in] A pointer to the IRK of the local device.
 *
 * @retval ble_stat_t : Command status to be sent to the Host.
 */
ble_stat_t ll_intf_le_add_device_rsolv_list(uint8_t peer_id_addr_type,
	uint8_t peer_id_addr[ADDRESS_SIZE], uint8_t *peer_irk, uint8_t *lcl_irk);

/**
 * @brief  Used to remove one device from the list of address translations used to resolve Resolvable
 * 	   Private Addresses in the controller.
 *
 * @param  peer_id_addr_type 	 : [in] Address type of the device to be added to the resolving list of the controller.
 * @param  peer_id_addr		 : [in] Public Device Address or Random Device Address of the device to be removed from the resolving list.
 *
 * @retval ble_stat_t : Command status to be sent to the Host.
 */
ble_stat_t ll_intf_le_remove_device_rsolv_list(uint8_t peer_id_addr_type,
	uint8_t peer_id_addr[ADDRESS_SIZE]);

/**
 * @brief  used to remove all devices from the list of address translations used to resolve
 * 	   Resolvable Private Addresses in the Controller.
 *
 * @retval ble_stat_t : Command status to be sent to the Host.
 */
ble_stat_t ll_intf_le_clear_rsolv_list(void);

/**
 * @brief  Read the total number of white list entries that can be stored in the Controller.
 *
 * @param  rsolv_list_size : [out] Number of address translation entries in the resolving list.
 *
 * @retval ble_stat_t : Command status to be sent to the Host.
 */
ble_stat_t ll_intf_le_read_rsolv_list_size(uint8_t *rsolv_list_size);

/**
 * @brief  Used to get the current peer Resolvable Private Address being used for the corresponding
 * 	   peer Public and Random (static) Identity Address.
 *
 * @param  peer_id_addr_type 	: [in] Address type of the peer device to be read by the controller.
 * @param  peer_id_addr 	: [in] Public Device Address or Random Device Address of the peer device to be read by the controller.
 * @param  peer_rsolvabl_addr 	: [out] Peer resolvable address of the peer device.
 *
 * @retval ble_stat_t : Command status to be sent to the Host.
 */
ble_stat_t ll_intf_le_read_peer_rsolvabl_addr(uint8_t peer_id_addr_type,
	uint8_t peer_id_addr[ADDRESS_SIZE],
	uint8_t peer_rsolvabl_addr[ADDRESS_SIZE]);

/**
 * @brief  Used to get the current local Resolvable Private Address being used for the corresponding peer Identity Address.
 *
 * @param  peer_id_addr_type 	: [in] Address type of the peer device.
 * @param  peer_id_addr 		: [in] Public Device Address or Random Device Address of the peer device.
 * @param  lcl_rsolvabl_addr 	: [out] Resolvable address of the local device read by the controller.
 *
 * @retval ble_stat_t : Command status to be sent to the Host.
 */
ble_stat_t ll_intf_le_read_lcl_rsolvabl_addr(uint8_t peer_id_addr_type,
	uint8_t peer_id_addr[ADDRESS_SIZE],
	uint8_t lcl_rsolvabl_addr[ADDRESS_SIZE]);

/**
 * @brief  Used to enable resolution of Resolvable Private Addresses in the Controller.
 *
 * @param  addr_rsln_enble : [in] Parameter to enable or disable the address resolution in the controller.
 *
 * @retval ble_stat_t : Command status to be sent to the Host.
 */
ble_stat_t ll_intf_le_set_addr_rsln_enble(uint8_t addr_rsln_enble);

/*
 * @brief  Used to set the privacy mode for a specific peer in the Controller.
 *
 * @param  peer_id_addr_type 	: [in] Address type of the peer device.
 * @param  peer_id_addr 	: [in] Public Device Address or Random Device Address of the peer device.
 * @param  prvcy_mode	 	: [in] Privacy Mode of this peer (Network or Device).
 *
 * @retval ble_stat_t : Command status to be sent to the Host.
 */
ble_stat_t ll_intf_le_set_privacy_mode(uint8_t peer_id_addr_type,
	uint8_t peer_id_addr[ADDRESS_SIZE],
	ble_prvcy_mod_e prvcy_mode);
/**  @}
*/
#endif

/*##### Link Information HCI Commands' Group #####*/
/*##### Connection Setup HCI Commands' Group #####*/
/** @ingroup  Conn_cfg Connection Commands
 *  @{
 */
#if (SUPPORT_MASTER_CONNECTION || SUPPORT_SLAVE_CONNECTION)
/**
 * @brief  Read the value of the transmit power level of certain connection handle.
 *
 * @param  conn_handle_id		: [in]  Specify which Connection_Handle’s Transmit Power Level setting to read.
 * @param  type				: [in]  Type of the transmit power level to be read, whether current transmit power level or maximum transmit power level.
 * @param  transmit_power_level	: [out] Transmit power level value to be returned.
 *
 * @retval ble_stat_t : Command status to be sent to the Host.
 */
ble_stat_t ll_intf_read_transmit_power_level(uint16_t conn_handle_id,
	uint8_t type, int8_t *transmit_power_level);

/**
 * @brief  Read the RSSI value for a ceratin connection from the controller.
 *
 * @param  conn_handle_id 	: [in]  Handle for the connection for which the RSSI is to be read.
 * @param  rssi        	: [out] RSSI (Received Signal Strength Indication) value read from the controller.
 *
 * @retval ble_stat_t : Command status to be sent to the Host.
 */
ble_stat_t ll_intf_read_rssi(uint16_t conn_handle_id, int8_t *rssi);
#endif /* SUPPORT_MASTER_CONNECTION || SUPPORT_SLAVE_CONNECTION */
/**  @}
*/

#if(SUPPORT_SLAVE_CONNECTION || SUPPORT_EXPLCT_BROADCASTER_ROLE)
/** @ingroup  tx_pwr_cfg Tx Power Commands
 * @{
 */
/**
 * @brief  Read the transmit power level used for LE advertising channel packets from the controller.
 *
 * @param  transmit_power_level : [out] Transmit power level value for LE advertising channel packets read from the controller.
 *
 * @retval ble_stat_t : Command status to be sent to the Host.
 */
ble_stat_t ll_intf_le_read_adv_channel_tx_power(int8_t *transmit_power_level);
/**@}
 */
#endif /* SUPPORT_SLAVE_CONNECTION || SUPPORT_EXPLCT_BROADCASTER_ROLE */

#if (SUPPORT_MASTER_CONNECTION || SUPPORT_SLAVE_CONNECTION)
/** @ingroup  chnlmap_cfg  Channel Map Commands
 * @{
 */
/**
 * @brief  Read the current channel map of a certain connection from the controller.
 *
 * @param  conn_handle_id  	: [in]  Connection handle for the connection for which the channel map is to be read.
 * @param  channel_map  	: [out] The current channel map for the specified connection handle.
 *
 * @retval ble_stat_t : Command status to be sent to the Host.
 */
ble_stat_t ll_intf_le_read_channel_map(uint16_t conn_handle_id,
	uint8_t channel_map[5]);
/**@}
 */
#endif /* SUPPORT_MASTER_CONNECTION || SUPPORT_SLAVE_CONNECTION */

/*##### Authentication and Encryption HCI Commands' Group #####*/
/** @ingroup  enc_cfg  Authentication and Encryption Commands
 *  @{
 */
#if (SUPPORT_LE_ENCRYPTION)
/**
 * @brief Request the controller to encrypt the data provided with the given key.
 *
 * @param  ptr_key				: [in] A pointer to 128 bit key for the encryption of the data.
 * @param  ptr_plaintxt_data	: [in] A pointer to 128 bit data block that is requested to be encrypted.
 * @param  ptr_encrptd_data		: [out] A pointer to the encrypted data.
 *
 * @retval ble_stat_t : Command status to be sent to the Host.
 */
ble_stat_t ll_intf_le_encrypt(uint8_t *ptr_key, uint8_t *ptr_plaintxt_data,
	uint8_t *ptr_encrptd_data);
#endif /* SUPPORT_LE_ENCRYPTION */

#if (SUPPORT_LE_ENCRYPTION && SUPPORT_SLAVE_CONNECTION)
/**
 * @brief Used to reply to an LE Long Term Key Request event from the controller.
 *
 * @param  conn_handle_id	: [in] Connection_Handle to be used to identify the connection.
 * @param  ptr_long_trm_key	: [in] A pointer to 128 bit long term key provided by the Host.
 *
 * @retval ble_stat_t : Command status to be sent to the Host.
 */
ble_stat_t ll_intf_rcvd_long_trm_key(uint16_t conn_handle_id,
	uint8_t *ptr_long_trm_key);
#endif /* (SUPPORT_LE_ENCRYPTION && SUPPORT_SLAVE_CONNECTION) */

#if SUPPORT_LE_ENCRYPTION
/**
 * @brief  Request the Controller to generate 8 octets of random data to be sent to the Host.
 *
 * @param  ptr_rand_data	: [out] A pointer to the random number generated by the controller.
 *
 * @retval ble_stat_t : Command status to be sent to the Host.
 */
ble_stat_t ll_intf_le_rand_data(uint8_t *ptr_rand_data);
#endif /* SUPPORT_LE_ENCRYPTION */

#if (SUPPORT_LE_ENCRYPTION && SUPPORT_MASTER_CONNECTION)
/**
 * @brief Used to authenticate the given encryption key and to encrypt the connection.
 *
 * @param  conn_handle_id	: [in] Connection_Handle to be used to identify the connection.
 * @param  ptr_rand_num		: [in] A pointer to 64 bit random number to be used in encryption.
 * @param  encrptd_divrsfier	: [in] A pointer to 16 bit encrypted diversifier to be used in encryption.
 * @param  ptr_long_trm_key	: [in] A pointer to 128 bit long term key to be used in encryption.
 *
 * @retval ble_stat_t : Command status to be sent to the Host.
 */
ble_stat_t ll_intf_le_strt_encrpt(uint16_t conn_handle_id,
	uint8_t *ptr_rand_num, uint16_t encrptd_divrsfier,
	uint8_t * ptr_long_trm_key);
#endif /* SUPPORT_LE_ENCRYPTION && SUPPORT_MASTER_CONNECTION */
/**  @}
*/

/*##### DTM Commands' Group #####*/
/** @ingroup  dtm_cfg  DTM Commands
 *  @{
 */
/**
 * @brief run the LE receiver test.
 *
 * @param  rx_channel		: [in] rx channel value:
 *
 * @retval ble_stat_t 		: Command status to be sent to the Host.
 */
ble_stat_t ll_intf_le_receiver_test(uint8_t rx_channel);

/**
 * @brief run the LE transmitter test.
 *
 * @param  tx_channel		: [in] tx channel value.
 * @param  length_of_test_data	: [in] Length in bytes of payload data in each packet.
 * @param  packet_payload	: [in] Packet payload type in each packet as in (7.8.29).
 *
 * @retval ble_stat_t 		: Command status to be sent to the Host.
 */
ble_stat_t ll_intf_le_transmitter_test(uint8_t tx_channel,
	uint8_t length_of_test_data, uint8_t packet_payload);

/**
 * @brief end LE test.
 *
 * @param  number_of_packets	: Pointer to number of packets received.
 *
 * @retval ble_stat_t 		: Command status to be sent to the Host.
 */
ble_stat_t ll_intf_le_test_end(uint16_t* number_of_packets);

/**
 * @brief  The LE Set PHY command is used to request a change to the transmitter PHY and receiver PHY for a connection.
 *
 * @param rx_channel		: [in] Frequency Range 0x00 to 0x27
 * @param phy				: [in] Receiver set to 1M/2M/coded PHY
 * @param modulation_index	: [in] Modulation index type (standard/stable)
 *
 * @retval status        	: [out] 0:SUCCESS, 0xXX:ERROR_CODE.
 *
 */
ble_stat_t ll_intf_le_enhanced_receiver_test(uint8_t rx_channel,
	uint8_t phy, uint8_t modulation_index);

/**
 * @brief  The LE Set PHY command is used to request a change to the transmitter PHY and receiver PHY for a connection.
 *
 * @param tx_channel 		: [in] Frequency Range 0x00 to 0x27
 * @param length_of_test_data 	: [in] Length in bytes of payload data in each packet
 * @param packet_payload  	: [in] Sequence
 * @param phy				: [in] Transmitter set to 1M/2M/coded PHY
 *
 * @retval status        	: [out] 0:SUCCESS, 0xXX:ERROR_CODE.
 */
ble_stat_t ll_intf_le_enhanced_transmitter_test(uint8_t tx_channel,
	uint8_t length_of_test_data, uint8_t packet_payload, uint8_t phy);


#if (SUPPORT_AOA_AOD)
/*================  LE receiver Test [v3] Command =====================*/
/**
 * @brief  Used to start a test where the DUT receives test reference packets at a fixed interval. This command includes the Constant Tone Extension feature.
 *
 * @param  ptr_hci_cmd_params	: [in] Pointer to the HCI command parameters.
 *
 * @retval status        	: [out] 0:SUCCESS, 0xXX:ERROR_CODE.
 *
 */
ble_stat_t ll_intf_le_receiver_test_v3(le_rx_test_v3_cmd_st *ptr_hci_cmd_params);

/*================  LE transmitter Test [v3] Command =====================*/
/**
 * @brief  Used to start a test where the DUT generates test reference packets at a fixed interval and including the Constant Tone Extension feature.
 *
 * @param  ptr_hci_cmd_params	: [in] Pointer to the HCI command parameters.
 *
 * @retval status        	: [out] 0:SUCCESS, 0xXX:ERROR_CODE.
 *
 */
ble_stat_t ll_intf_le_transmitter_test_v3(le_tx_test_v3_cmd_st *ptr_hci_cmd_params);
#endif /* SUPPORT_AOA_AOD */


#if SUPPORT_CHANNEL_CLASSIFICATION
/**
 * @brief Read the current channel assessment mode of the controller
 *
 * @param  ptr_assessment_mode	: [out] A pointer to the channel assessment mode used by the controller
 *
 * @retval ble_stat_t : Command status to be sent to the Host.
 */
ble_stat_t ll_intf_read_afh_chnl_assessment_mode(uint8_t *ptr_assessment_mode);

/**
 * @brief Write channel assessment mode to be used by the controller
 *
 * @param  assessment_mode	: [in] channel assessment mode set by the host to be used by the controller
 *
 * @retval ble_stat_t : Command status to be sent to the Host.
 */
ble_stat_t ll_intf_write_afh_chnl_assessment_mode(uint8_t assessment_mode);
#endif /* SUPPORT_CHANNEL_CLASSIFICATION */


/**  @}
*/

/** @ingroup  enc_cfg  Authentication and Encryption Commands
 *  @{
 */
#if (SUPPORT_LE_ENCRYPTION && (SUPPORT_SLAVE_CONNECTION || SUPPORT_MASTER_CONNECTION))
/**
 * @brief Write the LE Authenticated Payload Timeout for the LE connection
 *
 * @param  conn_handle_id	: [in] Connection_Handle to be used to identify the connection.
 * @param  authn_pyld_tout	: [in] Maximum amount of time specified between packets authenticated by a valid MIC.
 *
 * @retval ble_stat_t : Command status to be sent to the Host.
 */
ble_stat_t ll_intf_wrte_authn_pyld_tout(uint16_t conn_handle_id,
	uint16_t authn_pyld_tout);

/**
 * @brief Read the LE Authenticated Payload Timeout for the LE connection.
 *
 * @param  conn_handle_id		: [in] Connection_Handle to be used to identify the connection.
 * @param  ptr_authn_pyld_tout	: [out] A pointer to the authenticated payload timeout, which is the maximum amount of time
 * 					specified between packets authenticated by a MIC.
 *
 * @retval ble_stat_t : Command status to be sent to the Host.
 */
ble_stat_t ll_intf_read_authn_pyld_tout(uint16_t conn_handle_id,
	uint16_t *ptr_authn_pyld_tout);
#endif /* SUPPORT_LE_ENCRYPTION && (SUPPORT_SLAVE_CONNECTION || SUPPORT_MASTER_CONNECTION) */
/**  @}
*/

/*##### Remote Information HCI Commands' Group #####*/

/** @ingroup  remote_info_cfg  Remote Information HCI Commands
 *  @{
 */
#if(SUPPORT_MASTER_CONNECTION || SUPPORT_SLAVE_CONNECTION)
/**
 * @brief  Read the values for the version information for the remote device associated with the Connection_Handle.
 *
 * @param  conn_handle_id : [in] Connection Handle Id version information to get.
 *
 * @retval ble_stat_t : Command status to be sent to the Host.
 */
ble_stat_t ll_intf_read_remote_version_info(uint16_t conn_handle_id);

/**
 * @brief  Read the used features of a LE remote device.
 *
 * @param  conn_handle_id : [in] Connection Handle Id to identify a connection.
 *
 * @retval ble_stat_t : Command status to be sent to the Host.
 */
ble_stat_t ll_intf_le_read_remote_used_features(uint16_t conn_handle_id);
/**@}
 */

/*##### Connection State HCI Commands' Group #####*/
/** @ingroup  conn_state_cmds  Connection State HCI Commands
 *  @{
 */
/**
 * @brief  Used to change the connection parameters of an existing connection.
 *
 * @param  conn_handle_id 	: [in] Connection Handle Id to identify a connection.
 * @param  conn_interval_min   	: [in] Minimum value for the connection event interval.
 * @param  conn_interval_max   	: [in] Maximum value for the connection event interval.
 * @param  slave_latency 	: [in] Slave latency for the connection in number of connection events.
 * @param  supervsn_timeout	: [in] Supervision timeout for the LE Link.
 * @param  min_ce_length 	: [in] Information parameter about the minimum length of connection event needed for this LE connection.
 * @param  max_ce_length 	: [in] Information parameter about the maximum length of connection event needed for this LE connection.
 *
 * @retval ble_stat_t : Command status to be sent to the Host.
 */
ble_stat_t ll_intf_le_conn_update(uint16_t conn_handle_id,
	uint16_t conn_interval_min, uint16_t conn_interval_max,
	uint16_t slave_latency, uint16_t supervsn_timeout,
	uint16_t min_ce_length, uint16_t max_ce_length);

/**
 * @brief  is used to accept the remote device’s request to change the connection parameters of the LE connection.
 *
 * @param  conn_handle_id 		: [in] Connection Handle Id to be used to identify a connection.
 * @param  ptr_new_conn_param 	: [in] Pointer to the new connection parameters.
 *
 * @retval ble_stat_t : Command status to be sent to the Host.
 */
ble_stat_t ll_intf_le_remote_conn_parm_req_reply(
	uint16_t conn_handle_id,
	le_rmt_conn_param_req_rply_cmd_st *ptr_new_conn_param);

/**
 * @brief  is used to reject the remote device’s request to change the connection parameters of the LE connection.
 *
 * @param  conn_handle_id 	   : [in] Connection Handle Id to be used to identify a connection.
 * @param  reason		   : [in] Reason that the connection parameter request was rejected.
 *
 * @retval ble_stat_t 		   : Command status to be sent to the Host.
 */
ble_stat_t ll_intf_le_remote_conn_parm_req_neg_reply(uint16_t conn_handle_id,
	uint8_t reason);

/**
 * @brief  is used to suggest maximum packet sizes to the Controller.
 *
 * @param  conn_handle_id 	   : [in] Connection Handle Id to be used to identify a connection.
 * @param  tx_octets		   : [in] Preferred maximum number of payload octets that the local Controller should include in a single Link Layer Data Channel PDU.
 * @param  tx_time		   : [in] Preferred maximum number of microseconds that the local Controller should use to transmit a single Link Layer Data Channel PDU.
 *
 * @retval ble_stat_t 		   : Command status to be sent to the Host.
 */
ble_stat_t ll_intf_le_set_data_length(uint16_t conn_handle_id,
	uint16_t tx_octets, uint16_t tx_time);

/**
 * @brief  allows the Host to read the initial MaxTxOctets and MaxTx-Time values for new connections it suggested to the Controller.
 *
 * @param  sug_max_tx_octets    : [out] used for new connections - connInitialMaxTxOctets.
 * @param  sug_max_tx_time	: [out] used for new connections - connInitialMaxTx-Time.
 *
 * @retval ble_stat_t 		: Command status to be sent to the Host.
 */
ble_stat_t ll_intf_le_read_sugg_default_data_length(uint16_t *sug_max_tx_octets,
	uint16_t *sug_max_tx_time);

/**
 * @brief  allows the Host to suggest initial MaxTxOctets and MaxTxTime values for new connections.
 *
 * @param  sug_max_tx_octets   	: [in] used for new connections - connInitialMaxTxOctets.
 * @param  sug_max_tx_time	: [in] used for new connections - connInitialMaxTx-Time.
 *
 * @retval ble_stat_t 		: Command status to be sent to the Host.
 */
ble_stat_t ll_intf_le_wrt_sugg_default_data_length(uint16_t sug_max_tx_octets,
	uint16_t sug_max_tx_time);

/**
 * @brief  received data packets from host to controller.
 *
 * @param  conn_handle_id  	: [in] Connection Handle ID.
 * @param  ptr_pkt 			: [in] Pointer to the data sent from host.
 *
 * @retval ble_stat_t	: Command status.
 */
ble_stat_t ll_intf_acl_data_from_host_to_cntrlr(uint16_t conn_handle_id,
	ble_buff_hdr_t *ptr_pkt);
#endif /* SUPPORT_MASTER_CONNECTION || SUPPORT_SLAVE_CONNECTION */
/**  @}
*/

#if SUPPORT_LE_EXTENDED_ADVERTISING
#if (SUPPORT_EXPLCT_BROADCASTER_ROLE || SUPPORT_SLAVE_CONNECTION || SUPPORT_BRD_ISOCHRONOUS)
/** @ingroup  adv_cfg
 *  @{
 */
/*================  The extended advertising =====================*/
/*================  LE Set Advertising Set Random Address Command =====================*/
/**
 * @brief  Set Advertising Set Random Address Command, sent by the host, in the controller.
 *
 * @param  adv_handle	        : [in] Advertising Handle used to identify an advertising set.
 * @param  ptr_random_adv_addrs	: [in] pointer to the Random Device Address, This address is used in the Controller
 *                                     for the advertiser's address contained in the advertising PDUs for the
 *                                     advertising set specified by the adv_handle parameter.
 *
 * @retval ble_stat_t : Command status to be sent to the Host.
 */
ble_stat_t ll_intf_le_set_adv_set_random_addrs(uint8_t adv_handle,
	uint8_t *ptr_random_adv_addrs);

/* ================  LE Set Extended Advertising Parameters Command =====================*/
/*
 * @brief  Set Extended Advertising Parameters Command , used by the Host to set the advertising parameters. .
 *
 * @param  adv_handle	        : [in] Advertising Handle used to identify an advertising set.
 * @param  adv_properties		: [in] describes the type of advertising event that is being configured and its basic properties.
 * @param  prim_adv_intrv_min	: [in] Minimum advertising interval for undirected and low duty cycle directed advertising.
 * @param  prim_adv_intrv_max	: [in] Maximum advertising interval for undirected and low duty cycle directed advertising.
 * @param  prim_adv_chnl_map	: [in] indicates the advertising channels that shall be used when transmitting advertising packets..
 * @param  own_addrs_type	: [in] specifies the type of address being used in the advertising packets.
 * @param  peer_addrs_type	: [in] specifies the type of the peer address being used in the advertising packets.
 * @param  ptr_peer_addrs	: [in] pointer to the Peer Device Address, This address is used in the Controller
 *                                     for the advertiser's address contained in the advertising PDUs for the
 *                                     advertising set specified by the adv_handle parameter.
 * @param adv_filter_policy	: [in] Advertising Filter Policy to be used for the advertising set specified by the adv_handle parameter.
 * @param  prim_adv_phy	    : [in] indicates the PHY on which the
 advertising packets are transmitted on the primary advertising channel.
 * @param  sec_adv_max_skip	: [in] the maximum number of advertising events that can be skipped before the AUX_ADV_IND can be sent.
 * @param  sec_adv_phy	    : [in] indicates the PHY on which the advertising packets are be transmitted on the
 *                                     secondary advertising channel.
 * @param  adv_sid	        : [in] specifies the value to be transmitted in the Advertising SID subfield of the ADI field of the
 *                                    Extended Header of those advertising channel PDUs that have an ADI field..
 * @param  scan_req_notfy	: [in] indicates whether the Controller shall send notifications upon the receipt of a scan request PDU that
 *                                     is in response to an advertisement from the specified advertising set that contains its device address and is
 *                                     from a scanner that is allowed by the advertising filter policy.
 * @param  *selected_tx_pwr	: [out] pointer to the selected TX power value to be set by link layer.
 *
 * @retval ble_stat_t : Command status to be sent to the Host.
 */
ble_stat_t ll_intf_le_set_extended_adv_params(uint8_t adv_handle,
	uint16_t adv_properties, uint32_t prim_adv_intrv_min,
	uint32_t prim_adv_intrv_max, uint8_t prim_adv_chnl_map,
	uint8_t own_addrs_type, uint8_t peer_addrs_type,
	uint8_t *ptr_peer_addrs, uint8_t adv_filter_policy, int8_t adv_tx_power,
	uint8_t prim_adv_phy, uint8_t sec_adv_max_skip, uint8_t sec_adv_phy,
	uint8_t adv_sid, uint8_t scan_req_notfy, int8_t *selected_tx_pwr);

/*================  LE Set Extended Advertising Data Command =====================*/
/**
 * @brief  Set Extended Advertising Data Command , used by the Host to set the advertising data. .
 *
 * @param  adv_handle	        : [in] Advertising Handle used to identify an advertising set.
 * @param  adv_data_operation	: [in] indicates if the data is intermediate fragment, first fragment , last fragment, or
 *                                     Complete extended advertising data, or unchanged data(just update the DID).
 * @param  fragmnt_preference	: [in] provides a hint to the Controller as to whether advertising data should be fragmented.
 * @param  adv_data_length		: [in] The number of octets in the Advertising Data parameter.
 * @param  ptr_adv_data	        : [in] pointer Advertising data formatted as defined in [Vol 3] Part C, Section 11 of the standard.
 *
 * @retval ble_stat_t : Command status to be sent to the Host.
 */
ble_stat_t ll_intf_le_set_extended_adv_data(uint8_t adv_handle,
	uint8_t adv_data_operation, uint8_t fragmnt_preference,
	uint8_t adv_data_length, uint8_t *ptr_adv_data);

/*================  LE Set Extended Scan Response Data Command =====================*/
/**
 * @brief  Set Extended Scan Response Data Command , used by the Host to set the Scan Responsedata. .
 *
 * @param  adv_handle	          : [in] Advertising Handle used to identify an advertising set.
 * @param  scn_rsp_data_operation : [in] indicates if the data is intermediate fragment, first fragment , last fragment, or
 *                                     Complete extended scan response data, or unchanged data(just update the DID).
 * @param  fragmnt_preference	: [in]  provides a hint to the Controller as to whether scan response data should be fragmented.
 * @param  scn_rsp_data_length	: [in] The number of octets in the scan response Data parameter.
 * @param  ptr_scn_rsp_data	    : [in] pointer scan response data formatted as defined in [Vol 3] Part C, Section 11 of the standard.
 *
 * @retval ble_stat_t : Command status to be sent to the Host.
 */
ble_stat_t ll_intf_le_set_extended_scn_rsp_data(uint8_t adv_handle,
	uint8_t scn_rsp_data_operation, uint8_t fragmnt_preference,
	uint8_t scn_rsp_data_length, uint8_t *ptr_scn_rsp_data);

/*================  LE Set Extended Advertising Enable Command =====================*/
/**
 * @brief  Set Extended Advertising Enable is used to request the
 *         Controller to enable or disable one or more advertising sets using the
 *         advertising sets identified by the Advertising handles .
 *
 * @param  adv_enbl	                   : [in] For disable the advertising set it to zero , for enable set it to one .
 * @param  num_of_sets	               : [in] the number of advertising sets contained in the parameter arrays.
 * @param  ptr_ext_adv_enable_params   : [in] Pointer represents array of advertising enable structure.
 *
 * @retval ble_stat_t : Command status to be sent to the Host.
 */
ble_stat_t ll_intf_le_set_extended_adv_enable(uint8_t adv_enbl,
	uint8_t num_of_sets,
	st_ble_intf_ext_adv_enable_params* ptr_ext_adv_enable_params);

/*================  LE Read Maximum Advertising Data Length Command =====================*/
/**
 * @brief   is used to read  the maximum length of data supported by the Controller for use as
 * advertisement data or scan response data in an advertising event or as periodic advertisement data.
 *
 * @param  ptr_max_adv_data_len  : [out] pointer to the maximum length of advertisement data or scan response data.
 *
 * @retval ble_stat_t : Command status to be sent to the Host.
 */
ble_stat_t ll_intf_le_read_max_adv_data_len(uint16_t *ptr_max_adv_data_len);

/*================  LE Read Maximum Advertising Data Length Command =====================*/
/**
 * @brief   is used to read the maximum number of advertising sets supported by the advertising Controller at the same time.
 *
 * @param ptr_max_num_of_adv_sets  : [out] pointer to the maximum number of advertising sets supported by the advertising
 *                                         Controller at the same time.
 *
 * @retval ble_stat_t : Command status to be sent to the Host.
 */
ble_stat_t ll_intf_le_read_max_num_of_adv_sets(uint8_t *ptr_max_num_of_adv_sets);

/*================  LE Remove Advertising Set Command =====================*/
/**
 * @brief  is used to remove an advertising set from the Controller.
 *
 * @param adv_hndl  : [in] Used to identify an advertising set.
 *
 * @retval ble_stat_t : Command status to be sent to the Host.
 */
ble_stat_t ll_intf_le_rmv_adv_set(uint8_t adv_hndl);

/*================  LE Clear Advertising Sets Command =====================*/
/**
 * @brief  is used to remove all existing advertising sets from the Controller.
 *
 * @retval ble_stat_t : Command status to be sent to the Host.
 */
ble_stat_t ll_intf_le_clear_adv_sets(void);

#if SUPPORT_LE_PERIODIC_ADVERTISING
/**
 * @brief  Set periodic advertising parameters.
 *
 * @param  advertising_handle  					: [in] Advertising handle referring to an advertising instant.
 * @param  periodic_advertising_interval_min  	: [in] Minimum value for periodic advertising interval.
 * @param  periodic_advertising_interval_max  	: [in] Maximum value for periodic advertising interval.
 * @param  periodic_advertising_properties  	: [in] Indicates which fields should be included in the advertising packet.
 *
 * @retval ble_stat_t	: Command status.
 */
ble_stat_t ll_intf_le_set_periodic_adv_params(uint8_t advertising_handle,
	uint16_t periodic_advertising_interval_min,
	uint16_t periodic_advertising_interval_max,
	uint16_t periodic_advertising_properties);
/**
 * @brief  Set periodic advertising data.
 *
 * @param  advertising_handle  		: [in] Advertising handle referring to an advertising instant.
 * @param  operation  				: [in] Information for Host fragmentation.
 * @param  advertising_data_length  : [in] Length of Host advertising data.
 * @param  ptr_periodic_adv_data  	: [in] Pointer to Host advertising data.
 *
 * @retval ble_stat_t	: Command status.
 */
ble_stat_t ll_intf_le_set_periodic_adv_data(uint8_t advertising_handle,
	uint8_t operation, uint8_t advertising_data_length,
	uint8_t *ptr_periodic_adv_data);

/**
 * @brief  Enable/Disable periodic advertising.
 *
 * @param  enable  				: [in] Enable/Disable advertising.
 * @param  advertising_handle  	: [in] Advertising handle referring to an advertising instant.
 *
 * @retval ble_stat_t	: Command status.
 */
ble_stat_t ll_intf_le_set_periodic_adv_enable(uint8_t enable,
	uint8_t advertising_handle);
#endif /* SUPPORT_LE_PERIODIC_ADVERTISING */
#endif /* (SUPPORT_EXPLCT_BROADCASTER_ROLE || SUPPORT_SLAVE_CONNECTION || SUPPORT_BRD_ISOCHRONOUS) */
/**@}
*/

/** @ingroup  scn_cfg
 *  @{
 */
#if (SUPPORT_MASTER_CONNECTION || SUPPORT_EXPLCT_OBSERVER_ROLE)
/**
 * @brief  Set extended scanning parameters.
 *
 * @param  own_address_type  		: [in] Own (scanner) address type.
 * @param  scanning_filter_policy  	: [in] Filter policy used in scanning state.
 * @param  scanning_phys		  	: [in] PHY(s) on which the advertising packets should be received on the primary advertising channel.
 * @param  ptr_ext_scn_params	  	: [in] Pointer represents extended scanning parameters each PHY.
 *
 * @retval ble_stat_t	: Command status.
 */
ble_stat_t ll_intf_le_set_extended_scan_params(uint8_t own_address_type,
	uint8_t scanning_filter_policy, uint8_t scanning_phys,
	st_ble_intf_ext_scn_params* ptr_ext_scn_params);

/**
 * @brief  Enable/Disable extended scanning.
 *
 * @param  scan_enable  	 : [in] Scanning enable/disable flag.
 * @param  filter_duplicates : [in] Filter out duplicate advertising reports flag.
 * @param  durtion			 : [in] Scanning duration.
 * @param  period			 : [in] scanning period.
 *
 * @retval ble_stat_t	: Command status.
 */
ble_stat_t ll_intf_le_set_extended_scan_enable(uint8_t scan_enable,
	uint8_t filter_duplicates, uint16_t durtion, uint16_t period);
#endif /* (SUPPORT_MASTER_CONNECTION || SUPPORT_EXPLCT_OBSERVER_ROLE) */
/**@}
*/

/** @ingroup  Conn_cfg Connection Commands
 *  @{
 */
#if (SUPPORT_MASTER_CONNECTION)
/**
 * @brief  Start initiating to create a connection.
 *
 * @param  initiator_filter_policy  : [in] Scanning enable/disable flag.
 * @param  own_addr_type		: [in] Filter policy used in initiating state.
 * @param  peer_addr_type		: [in] Peer address type.
 * @param  ptr_peer_address		: [in] Pionter to peer address.
 * @param  initiating_phys  	: [in] PHY(s) on which the advertising packets should be received on the primary advertising channel..
 * @param  ptr_ext_create_conn	: [in] Pointer represents extended create connection structure.
 *
 * @retval ble_stat_t	: Command status.
 */
ble_stat_t ll_intf_le_extended_create_conn(uint8_t initiator_filter_policy,
	uint8_t own_addr_type, uint8_t peer_addr_type,
	uint8_t* ptr_peer_address, uint8_t initiating_phys,
	st_ble_intf_ext_create_conn* ptr_ext_create_conn);
#endif /* (SUPPORT_MASTER_CONNECTION) */
/**@}
*/

#if (SUPPORT_MASTER_CONNECTION || SUPPORT_EXPLCT_OBSERVER_ROLE) && SUPPORT_LE_PERIODIC_ADVERTISING
/** @ingroup  prdc_sync_cmds Periodic Synchronization Commands
 *  @{
 */
/**
 * @brief  Set periodic advertising create sync.
 *
 * @param  options			  		: [in] Determine whether the Periodic Advertiser List is used.
 * @param  advertising_sid  		: [in] Advertiser set ID.
 * @param  advertising_address_type : [in] Advertiser address type.
 * @param  ptr_advertiser_address  	: [in] Pointer to advertiser address.
 * @param  skip			  	: [in] Number of consecutive periodic advertising packets that the receiver may skip after successfully receiving a periodic advertising packet.
 * @param  sync_timeout  	: [in] Maximum permitted time between successful receives.
 * @param  cte_type  		: [in] Specifies whether to only sync to periodic advertising with certain types of Constant Tone Extension.
 *
 * @retval ble_stat_t	: Command status.
 */
ble_stat_t ll_intf_le_set_periodic_adv_create_sync(uint8_t options,
	uint8_t advertising_sid, uint8_t advertising_address_type,
	uint8_t *ptr_advertiser_address, uint16_t skip, uint16_t sync_timeout,uint8_t cte_type);

/**
 * @brief  Cancel periodic advertising create sync cancel.
 *
 * @retval ble_stat_t	: Command status.
 */
ble_stat_t ll_intf_le_set_periodic_adv_create_sync_cancel(void);

/**
 * @brief  Cancel periodic advertising terminate sync.
 *
 * @param  sync_handle		: Used to identify the periodic advertiser.
 *
 * @retval ble_stat_t	: Command status.
 */
ble_stat_t ll_intf_le_set_periodic_adv_terminate_sync(uint16_t sync_handle);
/**@}
*/

/** @ingroup  prdc_list_cfg Periodic list Commands
 *  @{
 */
/**
 * @brief  Add device to periodic advertiser list.
 *
 * @param  advertiser_address_type	: [in] Advertiser address type.
 * @param  ptr_advertiser_address	: [in] Pointer to advertiser address.
 * @param  advertising_sid			: [in] Advertiser set ID.
 *
 * @retval ble_stat_t	: Command status.
 */
ble_stat_t ll_intf_le_add_dev_to_periodic_adv_lst(
	uint8_t advertiser_address_type, uint8_t* ptr_advertiser_address,
	uint8_t advertising_sid);

/**
 * @brief  Remove device from periodic advertiser list.
 *
 * @param  advertiser_address_type	: [in] Advertiser address type.
 * @param  ptr_advertiser_address	: [in] Pointer to advertiser address.
 * @param  advertising_sid			: [in] Advertiser set ID.
 *
 * @retval ble_stat_t	: Command status.
 */
ble_stat_t ll_intf_le_rmv_dev_from_periodic_adv_lst(
	uint8_t advertiser_address_type, uint8_t* ptr_advertiser_address,
	uint8_t advertising_sid);

/**
 * @brief  Clear periodic advertiser list.
 *
 * @retval ble_stat_t	: Command status.
 */
ble_stat_t ll_intf_le_clr_periodic_adv_lst(void);

/**
 * @brief  Read periodic advertiser list size.
 *
 * @param  ptr_periodic_advertiser_list_size	: [out] Pointer to advertiser list size.
 *
 * @retval ble_stat_t	: Command status.
 */
ble_stat_t ll_intf_le_read_periodic_adv_lst_size(
	uint8_t* ptr_periodic_advertiser_list_size);
/**@}
*/
#endif /* (SUPPORT_MASTER_CONNECTION || SUPPORT_EXPLCT_OBSERVER_ROLE) && SUPPORT_LE_PERIODIC_ADVERTISING*/
#endif /*SUPPORT_LE_EXTENDED_ADVERTISING*/

/** @ingroup  tx_pwr_cfg  Tx Power Commands
 * @{
 */
/**
 * @brief  Used to read the minimum and maximum transmit powers supported by the Controller.
 *
 * @param  ptr_min_tx_pwr	: [out] A pointer to the min TX power value to be set by the controller [Range: -127 dB to 20 dB]
 * @param  ptr_max_tx_pwr	: [out] A pointer to the max TX power compensation value to be set by the controller [Range: -127 dB to 20.0 dB]
 *
 * @retval ble_stat_t	: Command status.
 */
ble_stat_t ll_intf_le_read_tx_pwr(
	int8_t *ptr_min_tx_pwr, int8_t* ptr_max_tx_pwr);

/**
 * @brief  Used to read the RF Path Compensation Values parameter used in the Tx Power Level and RSSI calculation.
 *
 * @param  ptr_rf_tx_path_compnstn	: [out] A pointer to the RF TX path compensation value to be set by the controller [Range: -128.0 dB (0xFB00) -> 128.0 dB (0x0500)]
 * @param  ptr_rf_rx_path_compnstn	: [out] A pointer to the RF RX path compensation value to be set by the controller [Range: -128.0 dB (0xFB00) -> 128.0 dB (0x0500)]
 *
 * @retval ble_stat_t	: Command status.
 */
ble_stat_t ll_intf_le_read_rf_path_compensation(
	int16_t *ptr_rf_tx_path_compnstn, int16_t* ptr_rf_rx_path_compnstn);

/**
 * @brief  Used to indicate the RF path gain or loss between the RF transceiver and the antenna contributed by intermediate components.
 *
 * @param  ptr_rf_tx_path_compnstn	: [in] RF TX path compensation value sent by host [Range: -128.0 dB (0xFB00) -> 128.0 dB (0x0500)]
 * @param  ptr_rf_rx_path_compnstn	: [in] RF RX path compensation value sent by host [Range: -128.0 dB (0xFB00) -> 128.0 dB (0x0500)]
 *
 * @retval ble_stat_t	: Command status.
 */
ble_stat_t ll_intf_le_write_rf_path_compensation(
	int16_t ptr_rf_tx_path_compnstn, int16_t ptr_rf_rx_path_compnstn);
/**@}
 */

/** @ingroup  connless_cte_cfg Connectionless CTE Commands
 *  @{
 */
/*================	AoA / AoD	=====================*/
/*================	LE Set Connectionless CTE Transmit Parameters Command	=====================*/
/**
 * @brief  Used to set the type, length, and antenna switching pattern for the transmission of the Constant Tone Extension field
 * 	   		in any periodic advertising on the advertising set identified by the Advertising_Handle parameter.
 *
 * @param  ptr_hci_cmd_params	: [in] Pointer to the HCI command parameters.
 *
 * @retval ble_stat_t		 : Command status.
 */
#if (SUPPORT_AOA_AOD)
#if (SUPPORT_EXPLCT_BROADCASTER_ROLE && SUPPORT_LE_PERIODIC_ADVERTISING)
ble_stat_t ll_intf_le_set_connectionless_cte_tx_params(le_set_connless_cte_tx_params_cmd_st *ptr_hci_cmd_params);

/*================	LE Set Connectionless CTE Transmit Enable Command	=====================*/
/**
 * @brief  Used to request that the Controller enables or disables the use of Constant Tone Extensions in any periodic
 * 	   		advertising on the advertising set identified by Advertising_Handle.
 *
 * @param  ptr_hci_cmd_params	: [in] Pointer to the HCI command parameters.
 *
 * @retval ble_stat_t		: Command status.
 */
ble_stat_t ll_intf_le_set_connless_cte_tx_enable(le_set_connless_cte_tx_enable_cmd_st *ptr_hci_cmd_params);
#endif /* (SUPPORT_EXPLCT_BROADCASTER_ROLE && SUPPORT_LE_PERIODIC_ADVERTISING) */

#if (SUPPORT_EXPLCT_OBSERVER_ROLE)
/*================	LE Set Connectionless IQ Sampling Enable Command	=====================*/
/**
 * @brief  Used to request that the Controller enables or disables capturing IQ samples from
 * 	   		the Constant Tone Extension field of periodic advertising packets identified by the
 * 	   		Sync_Handle parameter.
 *
 * @param  ptr_hci_cmd_params	: [in] Pointer to the HCI command parameters.
 *
 * @retval ble_stat_t		: Command status.
 */
ble_stat_t ll_intf_le_set_connless_iq_sampling_enable(le_set_connless_iq_sampling_enable_cmd_st *ptr_hci_cmd_params);
#endif /* (SUPPORT_EXPLCT_OBSERVER_ROLE) */
/**@}
*/

/** @ingroup  conn_cte_cfg Connection CTE Commands
 *  @{
 */
/*================	LE Set Connection CTE Receive Parameters Command	=====================*/
/**
 * @brief  Used to set the antenna switching pattern and switching and sampling slot durations for
 * 			receiving the CTE field during connection.
 *
 * @param  ptr_hci_cmd_params	: [in] Pointer to the HCI command parameters.
 *
 * @retval ble_stat_t			: Command status.
 */
#if ((SUPPORT_MASTER_CONNECTION) || (SUPPORT_SLAVE_CONNECTION))
ble_stat_t ll_intf_le_set_conn_cte_rx_params(le_set_conn_cte_rx_params_cmd_st *ptr_hci_cmd_params);

/*================	LE Set Connection CTE Transmit Parameters Command	=====================*/
/**
 * @brief  Used to set the antenna switching pattern and permitted CTE types used for transmitting the CTE field requested by the peer
 * 			evice during connection.
 *
 * @param  ptr_hci_cmd_params	: [in] Pointer to the HCI command parameters.
 *
 * @retval ble_stat_t	: Command status.
 */
ble_stat_t ll_intf_le_set_conn_cte_tx_params(le_set_conn_cte_tx_params_cmd_st *ptr_hci_cmd_params);

/*================	LE Connection CTE Request Enable Command	=====================*/
/**
 * @brief  Used to request the Controller to start or stop sending one or more LL_CTE_REQ PDU(s) on a
 * 			connection identified by the Connection_Handle parameter.
 *
 * @param  ptr_hci_cmd_params	: [in] Pointer to the HCI command parameters.
 *
 * @retval ble_stat_t		: Command status.
 */
ble_stat_t ll_intf_le_set_conn_cte_req_enable(le_set_conn_cte_req_enable_cmd_st *ptr_hci_cmd_params);

/*================	LE Connection CTE Response Enable Command	=====================*/
/**
 * @brief  Used to request the Controller to respond to LL_CTE_REQ PDUs with LL_CTE_RSP PDUs on the specified connection.
 *
 * @param  ptr_hci_cmd_params	: [in] Pointer to the HCI command parameters.
 *
 * @retval ble_stat_t		: Command status.
 */
ble_stat_t ll_intf_le_set_conn_cte_rsp_enable(le_set_conn_cte_rsp_enable_cmd_st *ptr_hci_cmd_params);

#endif /* (SUPPORT_MASTER_CONNECTION) || (SUPPORT_SLAVE_CONNECTION) */
/**@}
*/

/** @ingroup  antenna_cfg Antenna Commands
*  @{
*/
/*================	LE Read Antenna Information Command	=====================*/
/**
 * @brief  Allow the Host to read the switching rates, the sampling rates, the number of antennae, and the maximum
 * 	   		length of the Constant Tone Extension supported by the Controller.
 *
 * @param  ptr_supprtd_switching_sampling_rates	: [out] Antenna Switching and IQ Sampling rates supported by the controller.
 * @param  ptr_antenna_num						: [out] The number of antennae supported by the Controller.
 * @param  ptr_switching_pattern_max_len		: [out] Maximum length of antenna switching pattern supported by the Controller.
 * @param  ptr_cte_max_len						: [out] Maximum length of Constant Tone Extension supported in 8 us units.
 *
 * @retval ble_stat_t	: Command status.
 */
ble_stat_t ll_intf_read_antenna_info(uint8_t *ptr_supprtd_switching_sampling_rates,
	uint8_t *ptr_antenna_num,
	uint8_t *ptr_switching_pattern_max_len,
	uint8_t *ptr_cte_max_len);
/**@}
*/

/** @ingroup  vendor_cfg Vendor Specific Commands
*  @{
*/
/*================	LE Set Default Antenna ID Command	=====================*/
/**
 * @brief  Allow the Host to set the default antenna ID to be used by the Controller.
 *
 * @param  default_antenna_id : [in] Antenna ID value for the default antenna to be used by the controller, in case no antenna switching is required.
 *
 * @retval ble_stat_t	: Command status.
 */
ble_stat_t ll_intf_set_default_antenna_id(uint8_t default_antenna_id);
/**@}
 */
#endif /* SUPPORT_AOA_AOD */

/** @ingroup  phy_cfg PHY Commands
 * @{
 */
#if (SUPPORT_MASTER_CONNECTION || SUPPORT_SLAVE_CONNECTION)
/**
 * @brief  The LE Read PHY command is sent by the host to read the current working PHY per connection.
 *
 * @param  conn_handle_id : [in]  Connection_Handle to be used to identify a connection.(Range:0x0000-0x0EFF)
 * @param tx_phy 	  : [out] The used PHY in the Tx
 * @param rx_phy	  : [out] The used PHY in the Rx
 *
 * @retval status 	  : [out] 0:SUCCESS, 0xXX:ERROR_CODE.
 */
ble_stat_t ll_intf_le_read_phy_cmd(uint16_t conn_handle_id, uint8_t *tx_phy,
	uint8_t *rx_phy);

/**
 * @brief  The LE Set Default PHY command is sent by the host to set the prefered working PHYs for Tx and Rx.
 *
 * @param all_phys : [in]  The Host preferences (use prefered shown in tx_phys and rx_phys / no_preference) for the used PHYs in the TX or RX
 * @param tx_phys  : [in]  The prefered used PHY in the Tx
 * @param rx_phys  : [in]  The prefered used PHY in the Rx
 *
 * @retval status  : [out] 0:SUCCESS, 0xXX:ERROR_CODE.
 *
 */
ble_stat_t ll_intf_le_set_default_phy_cmd(uint8_t all_phys, uint8_t tx_phys,
	uint8_t rx_phys);

/**
 * @brief  The LE Set PHY command is used to request a change to the transmitter PHY and receiver PHY for a connection.
 *
 * @param conn_handle_id : [in] Connection_Handle to be used to identify a connection.(Range:0x0000-0x0EFF)
 * @param all_phys 	 : [in] The Host preferences (use prefered shown in tx_phys and rx_phys / no_preference) for the used PHYs in the TX or RX
 * @param tx_phys  	 : [in] The prefered used PHY in the Tx
 * @param rx_phys  	 : [in] The prefered used PHY in the Rx
 *
 * @retval status        : [out] 0:SUCCESS, 0xXX:ERROR_CODE.
 */
ble_stat_t ll_intf_le_set_phy_cmd(uint16_t conn_handle_id, uint8_t all_phys,
	uint8_t tx_phys, uint8_t rx_phys, uint16_t phy_options);
#endif /* (SUPPORT_MASTER_CONNECTION || SUPPORT_SLAVE_CONNECTION) */
/**@}
 */

#if (SUPPORT_LE_PERIODIC_ADVERTISING)
/** @ingroup  scn_cfg
 *  @{
 */
#if (SUPPORT_EXPLCT_OBSERVER_ROLE || SUPPORT_MASTER_CONNECTION || SUPPORT_SYNC_ISOCHRONOUS)
/*=============== LE Set Periodic Advertising Receive Enable Command ===============*/
/**
 * @brief  used to enable or disable reports for the periodic advertising identified by the Sync Handle parameter.
 *
 * @param  sync_handle	: [in] Used to identify the periodic advertiser.
 * @param  enable	    : [in] Enable/Disable sending reports
 *
 * @retval ble_stat_t	: Command status.
 */
ble_stat_t  ll_intf_le_set_periodic_adv_receive_enable(uint16_t sync_handle , uint8_t enable);
#endif /* (SUPPORT_EXPLCT_OBSERVER_ROLE || SUPPORT_MASTER_CONNECTION || SUPPORT_SYNC_ISOCHRONOUS)*/
/**@}
 */

/** @ingroup  prdc_sync_transfer_cfg Periodic Sync Transfer Commands
 * @{
 */
#if (SUPPORT_PERIODIC_SYNC_TRANSFER)
/*=============== LE Periodic Advertising Sync Transfer Command ===============*/
/**
 * @brief  : used to instruct the Controller to send synchronization information about the periodic advertising
 *			identified by the Sync Handle parameter to a connected device.
 *
 * @param  conn_handle	: [in] Connection Handle Id to identify a connection.
 * @param  service_data : [in] A value provided by the Host
 * @param  sync_handle	: [in] Used to identify the periodic advertiser.
 *
 * @retval ble_stat_t	: Command status.
 */
ble_stat_t ll_intf_le_periodic_adv_sync_transfer(
    uint16_t conn_handle,
    uint16_t service_data,
    uint16_t sync_handle);

/*=============== LE Set Periodic Advertising Set Info Transfer Command ===============*/
/**
 * @brief  : used to instruct the Controller to send synchronization information about the periodic advertising
 *			in an advertising set to a connected device.
 *
 * @param  service_data : [in] A value provided by the Host.
 * @param  conn_handle	: [in] Connection Handle Id to identify a connection.
 * @param  adv_handle	: [in] Used to identify the periodic advertiser.
 *
 * @retval ble_stat_t	: Command status.
 */
ble_stat_t ll_intf_le_periodic_adv_set_info_transfer(
    uint16_t conn_handle,
    uint16_t service_data,
    uint8_t adv_handle);

/*=============== LE Set Periodic Advertising Sync Transfer Parameters Command ===============*/
/**
 * @brief  : used to specify how the Controller will process periodic advertising synchronization information
 *			received from the device identified by the Connection Handle parameter.
 *
 * @param  conn_handle 	: [in] Connection Handle Id to identify a connection.
 * @param  mode     	: [in] Specifies the action to be taken when periodic advertising synchronization information is received.
 * @param  skip 		: [in] Number of consecutive periodic advertising packets that the receiver may skip after successfully receiving a periodic advertising packet.
 * @param  sync_timeout	: [in] Maximum permitted time between successful receives.
 * @param  cte_type     : [in] Specifies whether to only synchronize to periodic advertising with certain types of Constant Tone Extension.
 *
 * @retval ble_stat_t	: Command status.
 */
ble_stat_t  ll_intf_le_set_periodic_adv_sync_transfer_paramters(
	uint16_t conn_handle,uint8_t mode , uint16_t skip , uint16_t sync_timeout,uint8_t cte_type);

/*=============== LE Set Default Periodic Advertising Sync Transfer Parameters Command ===============*/
/**
 * @brief  : used to specify the initial value for the mode, skip, timeout, and Constant Tone Extension type.
 *
 * @param  mode     	: [in] Specifies the action to be taken when periodic advertising synchronization information is received.
 * @param  skip 		: [in] Number of consecutive periodic advertising packets that the receiver may skip after successfully receiving a periodic advertising packet.
 * @param  sync_timeout	: [in] Maximum permitted time between successful receives.
 * @param  cte_type     : [in] Specifies whether to only synchronize to periodic advertising with certain types of Constant Tone Extension.
 *
 * @retval ble_stat_t	: Command status.
 */
ble_stat_t	ll_intf_le_set_default_periodic_adv_sync_transfer_paramters(
	uint8_t mode , uint16_t skip , uint16_t sync_timeout,uint8_t cte_type);

#endif /* SUPPORT_PERIODIC_SYNC_TRANSFER */
/**@}
 */
#endif /* SUPPORT_LE_PERIODIC_ADVERTISING */

#if (SUPPORT_MASTER_CONNECTION || SUPPORT_SLAVE_CONNECTION)
/** @ingroup  tx_pwr_cfg  Tx Power Commands
 * @{
 */
/*================	LE Set Connection Transmit Power Level Command	=====================*/
/**
 * @brief  Used to Set the TX_Power level used by the local Controller on an ACL connection for a certain PHY.
 *
 * @param  ptr_hci_cmd_params	: [in] Pointer to the HCI command parameters.
 * @param  ptr_tx_power			: [out] Used to report the new Tx_power after the change.
 *
 * @retval ble_stat_t	: Command status.
 */
ble_stat_t ll_intf_set_conn_tx_power_level(le_set_conn_tx_pwr_lvl_cmd_st *ptr_hci_cmd_params, int8_t *ptr_tx_power);
/**@}
 */
#endif /* SUPPORT_MASTER_CONNECTION || SUPPORT_SLAVE_CONNECTION */

/*================	LE Power Control	=====================*/
/*================	LE Enhanced Read Transmit Power Level Command	=====================*/
#if (SUPPORT_LE_POWER_CONTROL)
/** @ingroup  power_control_cfg Power Control Commands
 * @{
 */
/**
 * @brief  Used to read the current and maximum TX_Power levels of the local Controller on an ACL connection for a certain PHY.
 *
 * @param  ptr_hci_cmd_params	: [in] Pointer to the HCI command parameters.
 * @param  ptr_curr_tx_power	: [Out] Value of the local current TX_Power level to be set by the Controller.
 * @param  ptr_max_tx_power	: [Out] Value of the local maximum TX_Power level to be set by the Controller.
 *
 * @retval ble_stat_t	: Command status.
 */
ble_stat_t ll_intf_enhanced_read_tx_power_level(le_enhanced_read_tx_pwr_lvl_cmd_st *ptr_hci_cmd_params,
		uint8_t *ptr_curr_tx_power,
		uint8_t *ptr_max_tx_power);

/*================	LE Read Remote Transmit Power Level Command	=====================*/
/**
 * @brief  Used to read the TX_Power level used by the remote Controller on an ACL connection for a certain PHY.
 *
 * @param  ptr_hci_cmd_params	: [in] Pointer to the HCI command parameters.
 *
 * @retval ble_stat_t	: Command status.
 */
ble_stat_t ll_intf_read_remote_tx_power_level(le_read_remote_tx_pwr_lvl_cmd_st *ptr_hci_cmd_params);

/*================	LE Set Path Loss Reporting Parameters Command	=====================*/
/**
 * @brief  Used to set the path loss threshold reporting parameters for an ACL connection.
 *
 * @param  ptr_hci_cmd_params	: [in] Pointer to the HCI command parameters.
 *
 * @retval ble_stat_t	: Command status.
 */
ble_stat_t ll_intf_set_path_loss_reporting_params(le_set_path_loss_reporting_params_cmd_st *ptr_hci_cmd_params);

/*================	LE Set Path Loss Reporting Enable Command	=====================*/
/**
 * @brief  Used to enable or disable path loss reporting for an ACL connection.
 *
 * @param  ptr_hci_cmd_params	: [in] Pointer to the HCI command parameters.
 *
 * @retval ble_stat_t	: Command status.
 */
ble_stat_t ll_intf_set_path_loss_reporting_enable(le_set_path_loss_reporting_enable_cmd_st *ptr_hci_cmd_params);

/*================	LE Set Transmit Power Reporting Enable Command	=====================*/
/**
 * @brief  Used to enable or disable the reporting to the local Host of TX_Power level changes in the local and remote Controllers for an ACL connection.
 *
 * @param  ptr_hci_cmd_params	: [in] Pointer to the HCI command parameters.
 *
 * @retval ble_stat_t	: Command status.
 */
ble_stat_t ll_intf_set_tx_power_reporting_enable(le_set_tx_pwr_reporting_enable_cmd_st *ptr_hci_cmd_params);
/**@}
 */

/** @ingroup  dtm_cfg  DTM Commands
 * @{
 */
/*================  LE transmitter Test [v4] Command =====================*/
/**
 * @brief  Used to start a test where the DUT generates test reference packets at a fixed interval and including the LE Low Power feature.
 *
 * @param  ptr_hci_cmd_params	: [in] Pointer to the HCI command parameters.
 *
 * @retval status        	: [out] 0:SUCCESS, 0xXX:ERROR_CODE.
 */
ble_stat_t ll_intf_le_transmitter_test_v4(le_tx_test_v4_cmd_st *ptr_hci_cmd_params);
/**@}
 */
#endif /* SUPPORT_LE_POWER_CONTROL */

/*################# Vendor-Specific HCI Commands' Group  ################# */

/** @ingroup  vendor_cfg Vendor Specific Commands
 * @{
 */
/*===============  LE Write Transmit Power Command ===============*/
/**
 * @brief  Set the minimum and maximum TX Power values to be supported by the controller.
 *
 * @param  tx_pwr     : [in] transmit power sent by host to be used by the controller
 *
 * @retval ble_stat_t : Command status to be sent to the Host.
 */
ble_stat_t ll_intf_le_write_tx_pwr(int8_t tx_pwr);
/**@}
 */


#if (SUPPORT_SLEEP_CLOCK_ACCURCY_UPDATES)
/** @ingroup  modify_slpclk_cfg Sleep Clock Accuracy Commands
 * @{
 */
/*===============  LE modify Sleep Clock Accuracy ===============*/
/**
 * @brief  Modify Sleep Clock Accuracy. This should be used for testing purposes only.
 *
 * @param  action     : [in] specifies action more accurate or less accurate SCA
 *
 * @retval ble_stat_t : Command status to be sent to the Host.
 */
ble_stat_t ll_intf_le_modify_sleep_clock_accuracy(uint8_t action);
/**@}
 */
#endif /* SUPPORT_SLEEP_CLOCK_ACCURCY_UPDATES */

/** @ingroup  sleep_clk_acc_cfg Set Sleep Clock Accuracy Command
 * @{
 */
/*===============  LE Set Sleep Clock Accuracy ===============*/
/**
 * @brief  Set Sleep Clock Acuuracy.
 *
 * @param  slp_clk_acc    : [in] sleep clock accuracy
 *
 * @retval ble_stat_t : Command status to be sent to the Host.
 */
ble_stat_t ll_intf_le_set_sleep_clock_accuracy(uint8_t slp_clk_acc);
/**@}
 */

/** @ingroup  dpslp_cfg Deep Sleep Commands
 * @{
 */
/*===============  LE Set Deep Sleep Mode ===============*/
/**
 * @brief Used to configure linklayer to go to/back from deep sleep mode.
 *
 * @param  dp_slp_mode : [in] 1 enable deep sleep mode , 0 go back to sleep mode
 *
 * @retval Status.
 */
ble_stat_t ll_intf_le_set_dp_slp_mode(uint8_t dp_slp_mode);
/**@}
 */

/** @ingroup  vendor_cfg Vendor Specific Commands
 * @{
 */
/*===============  LE Set PHY Calibration Event Parameters ===============*/
/**
 * @brief Used to configure the PHY calibration event parameters.
 *
 * @param  phy_clbr_evnt_period : [in] Indicate the periodicity of the PHY calibration event. Periodicity = phy_clbr_evnt_period * 1s.
 * @param  phy_clbr_evnt_count 	: [in] Indicate the number of the PHY calibration events to be executed.
 */
void ll_intf_le_set_phy_clbr_params(uint32_t phy_clbr_evnt_period, uint32_t phy_clbr_evnt_count);

#if ((SUPPORT_BRD_ISOCHRONOUS || SUPPORT_SYNC_ISOCHRONOUS) || \
	 (SUPPORT_CONNECTED_ISOCHRONOUS && (SUPPORT_MASTER_CONNECTION || SUPPORT_SLAVE_CONNECTION)))
#if SUPPORT_HW_AUDIO_SYNC_SIGNAL
/**
 * @brief Enable the audio sync signal for specific Stream
 * @param conn_hndle		:	Connection handle for stream for which hw audio sync signal should be enabled
 * @retval Status
 */
ble_stat_t ll_intf_enable_audio_sync_signal(uint16_t conn_hndle);
#if (SUPPORT_SYNC_ISOCHRONOUS)
/**
 * @brief Force RTL to re-rx the first sub-event in the stream which is already enabled
 * @param conn_hndle		:	Connection handle for stream for which hw audio sync signal should be enabled
 * @param force_state		:	Switch control of force resync
 * 								(1: means that the force mechanism is enabled, and the HW Audio signal
 * 								    is generated at the first sub-event of the stream that is already HW Audio signal is enabled
 * 								 0: means that the force mechanism is disabled, and the HW Audio signal
 * 								 	is generated at the last
 * @retval Status
 */
ble_stat_t ll_intf_force_audio_sync_signal_resync(uint16_t conn_hndle, uint8_t force_state);
#endif /*SUPPORT_SYNC_ISOCHRONOUS*/
#endif /*SUPPORT_HW_AUDIO_SYNC_SIGNAL*/
#endif /*#if ((SUPPORT_BRD_ISOCHRONOUS || SUPPORT_SYNC_ISOCHRONOUS) || \
	 (SUPPORT_CONNECTED_ISOCHRONOUS && (SUPPORT_MASTER_CONNECTION || SUPPORT_SLAVE_CONNECTION))) */

/*===============  LE Set Get Remaining Time For Next Event ===============*/
/**
 * @brief Used to Get Remaining Time For Next Event.
 *
 * @param  remaing_time : [out] the value of remaining time  for the next event in us.
 *
 * @retval Status.
 */
ble_stat_t ll_intf_le_get_remaining_time_for_next_event(uint32_t* remaing_time);

/*===============  LE Set SETUP_TIME Time               ===============*/
/**
 * @brief Used to Set SETUP_TIME Time For Next Event.
 *
 * @param  setup_time : [in]  the value of setup time in us to be used be the link layer scheduler  .
 *
 * @retval Status.
 */
ble_stat_t ll_intf_le_set_scheduler_setup_time(uint32_t setup_time) ;

#if (SUPPORT_AUGMENTED_BLE_MODE)
/**@}
 */
/** @ingroup  aug_ble_cfg Augmented BLE Commands
 * @{
 */
/**
 * @brief Used to Start BLE Augmented Mode.
 *
 * @param  aug_access_address : [in]  the value of access address to be used in augmented mode.
 * @param  aug_whitening_init : [in]  the value of whitening initialization to be used in augmented mode.
 *
 * @retval Status.
 */
ble_stat_t ll_intf_le_start_augmented_mode(uint32_t aug_access_address, uint8_t aug_whitening_init);

/**
 * @brief Used to Stop BLE Augmented Mode
 *
 * @retval Status.
 */
ble_stat_t ll_intf_le_stop_augmented_mode(void);
/**@}
 */

/** @ingroup  vendor_cfg Vendor Specific Commands
 * @{
 */
/**
 * @brief Used to Start Energy detection on a specific channel map
 *
 * @param  chnnl_map : [in]  bit mask of channel map.
 * @param  duration : [in]  Duration of energy detection on each channel.
 *
 * @retval Status.
 */
ble_stat_t ll_intf_le_start_energy_detection(uint8_t * chnnl_map, uint32_t duration);
#endif /*(SUPPORT_AUGMENTED_BLE_MODE)*/

#if (USE_NON_ACCURATE_32K_SLEEP_CLK)
/*===============  LE Select Sleep Clock Source ===============*/
/**
 * @brief Used to select the source that drives the sleep clock, whether to use an external crystal oscillator or an integrated RC oscillator (RCO).
 *
 * @param  slp_clk_src 				: [in] Indicate which source to drive the sleep clock. 0: Crystal Oscillator (default). 1: RC0
 * @param  ptr_slp_clk_freq_value 	: [out] Indicate the nominal frequency value of the sleep clock.
 *
 * @retval ble_stat_t : Command status to be sent to the Host.
 */
ble_stat_t ll_intf_le_select_slp_clk_src(uint8_t slp_clk_src, uint16_t *ptr_slp_clk_freq_value);
#endif /* USE_NON_ACCURATE_32K_SLEEP_CLK */

#if (USE_NON_ACCURATE_32K_SLEEP_CLK)
/*===============  LE Set RCO Calibration Event Parameters ===============*/
/**
 * @brief Used to configure the runtime RCO calibration event parameters.
 *
 * @param  rco_clbr_event_duration : [in] Indicate the number of sleep clock cycles for performing the RCO calibration process.
 * @param  rco_clbr_event_interval : [in] Indicate the periodicity of running the runtime RCO calibration event.
 *
 * @retval ble_stat_t : Command status to be sent to the Host.
 */
ble_stat_t ll_intf_le_set_rco_clbr_evnt_params(uint8_t rco_clbr_event_duration, uint32_t rco_clbr_event_interval);
#endif /* USE_NON_ACCURATE_32K_SLEEP_CLK */

/*===============  LE Select TX_Power Table  ===============*/
/**
 * @brief Used to specify the used power table and its size based on the selected TX_Power table ID.
 *
 * @param  tx_power_table_id : [in] Selected TX_Power table ID.
 *
 * @retval Status 		 : 0: SUCCESS. Otherwise: Error code.
 */
uint8_t ll_intf_select_tx_power_table(uint8_t tx_power_table_id);

#if(SUPPORT_CONNECTED_ISOCHRONOUS &&( SUPPORT_MASTER_CONNECTION || SUPPORT_SLAVE_CONNECTION)) || (SUPPORT_BRD_ISOCHRONOUS)
/*===============  LE Enable Sync Event ===============*/
/**
 * @brief Used to enable or disable generation of sync event and generation of calibration signal .
 *
 * @param  group_id            : [in] contain the identifier of the CIG or BIG.
 * @param  enable_sync 	       : [in] enable or disable generation of sync event.
 * @param  enable_clbr_trigger : [in] enable or disable generation of calibration signal
 * @param  trigger_source      : [in] identify trigger source (CIG or BIG) 
 */
ble_stat_t ll_intf_le_enable_sync_evnt(uint8_t group_id ,uint8_t enable_sync,
		uint8_t enable_clbr_trigger,uint8_t trigger_source);
#endif /* SUPPORT_CONNECTED_ISOCHRONOUS &&( SUPPORT_MASTER_CONNECTION || SUPPORT_SLAVE_CONNECTION) */
/**@}
 */

/** @ingroup  alloc_pkt_cfg Packet Allocation Commands
 * @{
 */
#if (SUPPORT_MASTER_CONNECTION || SUPPORT_SLAVE_CONNECTION)
/*===============  ll_intf_alloc_ll_pkt ===============*/
/**
 * @brief  Allocates LL packet that will be used for LL Tx/Rx.
 *
 * @retval void * : Pointer to the raw LL packet.
 */
void* ll_intf_alloc_ll_pkt(void);
#endif /* SUPPORT_MASTER_CONNECTION || SUPPORT_SLAVE_CONNECTION */

/*===============  ll_intf_free_ll_pkt ===============*/
/**
 * @brief  This function shall be called on any packets that has been passed from the LL to the host.
 *
 * @param  pkt  : [in] Pointer to the raw LL packet
 */
void ll_intf_free_ll_pkt(void* pkt);

/*===============  ll_intf_free_ll_pkt_hndlr ===============*/
/**
 * @brief  This function free both the LL packet and the handler asociated with it.
 *
 * @param  pkt  : [in] Pointer to ble_buff_hdr_t that points to the LL packet
 */
void ll_intf_free_ll_pkt_hndlr(ble_buff_hdr_t* pkt);
/**@}
 */

#if (SUPPORT_SLEEP_CLOCK_ACCURCY_UPDATES&&( SUPPORT_MASTER_CONNECTION || SUPPORT_SLAVE_CONNECTION))
/** @ingroup modify_slpclk_cfg Sleep Clock Accuracy Commands
 * @{
 */
/*=============== LE Request Peer SCA Command ===============*/
/**
 * @brief  								: is used to read the Sleep Clock Accuracy (SCA) of the peer device.
 *
 * @param  conn_hndl					: contains the identifier of the Connection_handler of the ACL_Connection
 *
 * @retval ble_stat_t					: Command status.
 */
ble_stat_t ll_intf_req_peer_sca(uint16_t conn_hndl);
/**@}
 */
#endif /* Sleep Clock Accuracy update &&( SUPPORT_MASTER_CONNECTION || SUPPORT_SLAVE_CONNECTION)*/

/*################################## Isochronous  ################################## */
/** @ingroup  iso_cfg
 *  @{
 */
#if((SUPPORT_CONNECTED_ISOCHRONOUS &&( SUPPORT_MASTER_CONNECTION || SUPPORT_SLAVE_CONNECTION)) || (SUPPORT_SYNC_ISOCHRONOUS))
/*===============  LE Set from controller to host function path  ===============*/
/**
 * @brief it sets the output path function in a CIS context
 *
 * @param conn_hndl		:[IN] ISO handle
 * @param ptr_func		:[IN] output data path
 *
 * @retval ble_stat_t.
 */
ble_stat_t ll_intf_set_output_data_path(uint16_t conn_hndl ,vendor_specific_from_cntrl_to_host_cbk func_ptr);
#endif  /*((SUPPORT_CONNECTED_ISOCHRONOUS &&( SUPPORT_MASTER_CONNECTION || SUPPORT_SLAVE_CONNECTION)) || (SUPPORT_SYNC_ISOCHRONOUS))*/
#if(SUPPORT_CONNECTED_ISOCHRONOUS &&( SUPPORT_MASTER_CONNECTION || SUPPORT_SLAVE_CONNECTION))
#if(SUPPORT_MASTER_CONNECTION)
/*=============== LE Set CIG Parameters Command ===============*/
/**
 * @brief  							: used to set the parameters of one or more CISes that are associated with a CIG in the Controller
 *
 * @param  ptr_st_set_cig_params	: [IN]  pointer to ble_intf_set_cig_params_cmd_st that contains CIG parameters coming from the Host
 * @param  conn_hndl				: [out] pointer to array of connection handles in the CIG
 *
 * @retval ble_stat_t				: Command status.
 */
ble_stat_t ll_intf_le_set_cig_params(ble_intf_set_cig_params_comman_cmd_st*  ptr_st_set_cig_params, uint8_t* conn_hndl);

/*=============== LE Set CIG Parameters Test Command ===============*/
/**
 * @brief  							 	: used to set the parameters of one or more CISes that are associated with a CIG in the Controller
 *
 * @param  ptr_st_set_cig_params_test	: [IN]  pointer to ble_intf_set_cig_params_cmd_st that contains CIG parameters coming from the Host
 * @param  conn_hndl					: [out] pointer to array of connection handles in the CIG
 *
 * @retval ble_stat_t					: Command status.
 */
ble_stat_t ll_intf_le_set_cig_params_test(ble_intf_set_cig_params_comman_cmd_st*  ptr_st_set_cig_params_test, uint8_t* conn_hndl);

/*=============== LE Create CIS Command ===============*/
/**
 * @brief  								: The HCI_LE_Create_CIS command is used by the master’s Host to create one or more CISes
 * 										  using the connections identified by the ACL_Connection_Handle[i] parameter array
 * @param  ptr_st_create_cis_params		: pointer to ble_intf_create_cis_cmd_st that contains ACL_Connection_Handles,
 * 										  ISO_Connection_Handles and Number of CISes.
 * @retval ble_stat_t					: Command status.
 */
ble_stat_t ll_intf_le_create_cis(ble_intf_create_cis_cmd_st* ptr_st_create_cis_params);
#endif /* SUPPORT_MASTER_CONNECTION */

/*=============== LE Accept CIS Request Command ===============*/
/**
 * @brief  								: is used by the slave’s Host to inform the Controller to accept
 * 										  the request for the CIS that is identified by the Connection_Handle.
 *
 * @param  conn_hndl					: contains the identifier of the Connection_handler of the master
 *
 * @retval ble_stat_t					: Command status.
 */
ble_stat_t ll_intf_accept_cis_req(uint16_t conn_hndl);

/*=============== LE Reject CIS Request Command ===============*/
/**
 * @brief  								: is used by the slave’s Host to inform the Controller to reject
 * 										  the request for the CIS that is identified by the Connection_Handle.
 *
 * @param  conn_hndl					: contains the identifier of the Connection_handler of the master
 * @param reason						: the reason for rejection
 *
 * @retval ble_stat_t					: Command status.
 */
ble_stat_t ll_intf_reject_cis_req(uint16_t conn_hndl, uint8_t reason);

/**
 * @brief Used to set cis req event mask value .
 *
 * @param cis_req_evnt_mask           : [in] event mask value.
 */
void ll_intf_set_cis_req_evnt_mask(uint32_t cis_req_evnt_mask);
/*=============== LE Remove CIG Command ===============*/
/**
 * @brief  								: is used by the master’s Host to remove all the CISes associated with the CIG identified by CIG_ID
 *
 * @param  cig_id						: contains the identifier of the CIG
 *
 * @retval ble_stat_t					: Command status.
 */
ble_stat_t ll_intf_rmv_cig(uint8_t cig_id);
/**  @}
*/

typedef void (*ll_intf_clbr_cb_t)(uint32_t);

/** @ingroup  clbr_cbk_cfg Calibration Callback
 * @{
 */
/**
 * @brief Registers a calibration function callback
 *
 * @param clbr_cb : Calibration function callback
 */
void ll_intf_rgstr_clbr_cbk(ll_intf_clbr_cb_t clbr_cb);
/**@}
 */

/** @ingroup  alloc_pkt_cfg Packet Allocation Commands
 * @{
 */
/**
 * @brief Allocates an ISO packet
 *
 * @retval Pointer to the allocated ISO packet
 */
void* ll_intf_alloc_iso_pkt(void);
/**@}
 */

/** @ingroup  conn_cte_cfg Connection CTE Commands
 * @{
 */
#if (SUPPORT_LE_POWER_CONTROL)
/**
 * @brief 	Custom command to read RSSI of CIS handle to be used in power control testing.
 *
 * @param conn_handle_id		: [in] ACL_CONNECTION_ID
 * @param ptr_cis_rssi_value    : [out] CIS RSSI value
 *
 * @retval ble_stat_t					: Command status.
 */
ble_stat_t ll_intf_cis_read_rssi(uint16_t conn_handle_id, int8_t *ptr_cis_rssi_value);
#endif /* SUPPORT_LE_POWER_CONTROL */
/**@}
 */
#endif/* SUPPORT_CONNECTED_ISOCHRONOUS &&( SUPPORT_MASTER_CONNECTION || SUPPORT_SLAVE_CONNECTION) */

#if(SUPPORT_BRD_ISOCHRONOUS || SUPPORT_SYNC_ISOCHRONOUS)
#if(SUPPORT_SYNC_ISOCHRONOUS)
/** @ingroup  iso_cfg
 *  @{
 */
/*=============== LE BIG Create Sync Command ===============*/
/**
 * @brief  								: is used to synchronize to a BIG described in the periodic advertising train specified by the Sync_Handle parameter.
 * @param  ptr_str_big_create_sync_cmd	: pointer to ble_intf_big_create_sync_cmd_st that contains the command parameters
 * @retval ble_stat_t					: Command status.
 */
ble_stat_t ll_intf_le_big_create_sync(ble_intf_big_create_sync_cmd_st * ptr_str_big_create_sync_cmd);

/*=============== LE BIG Terminate Sync Command ===============*/
/**
 * @brief  								: is used to stop synchronizing or cancel the process of synchronizing to the BIG identified by the BIG_Handle parameter.
 * 										  destroys the associated connection handles of the BISes in the BIG and removes the data paths for all BISes
 * 										  in the BIG identified by BIG_Handle.
 * @param  big_hndle					: contains the identifier of the BIG_Handler.
 *
 * @retval ble_stat_t					: Command status.
 */
ble_stat_t ll_intf_le_big_term_sync(uint8_t* big_hndle);

#endif /* SUPPORT_SYNC_ISOCHRONOUS */

#if(SUPPORT_BRD_ISOCHRONOUS)
/*=============== LE Create BIG Command ===============*/
/**
 * @brief  								: is used to create a BIG with one or more BISes (All BISes in a BIG have the same value for all parameters)
 * @param  ptr_create_big_cmd_st		: pointer to ble_intf_create_big_st that contains the parameters of create big / test command
 *
 * @retval ble_stat_t					: Command status.
 */
ble_stat_t ll_intf_le_create_big(ble_intf_create_big_st* ptr_create_big_cmd_st);

/*=============== LE Create BIG Test Command ===============*/
/**
 * @brief  								: (should be used in the ISO Test mode) is used to create a BIG with one or more BISes (All BISes in a BIG have the same value for all parameters)
 * @param  ptr_create_big_test_cmd_st	: pointer to ble_intf_create_big_st that contains the parameters of create big / test command
 *
 * @retval ble_stat_t					: Command status.
 */
ble_stat_t ll_intf_le_create_big_test(ble_intf_create_big_st* ptr_create_big_test_cmd_st);
#endif	/* SUPPORT_BRD_ISOCHRONOUS */

/*=============== LE Terminate BIG Command ===============*/
/**
 * @brief  								: is used to terminate a BIG identified by the BIG_Handle parameter
 * @param  big_hndle					: contains the identifier of the BIG_Handler.
 * @param  reason						: indicate the reason why the BIG is to be terminated
 *
 * @retval ble_stat_t					: Command status.
 */
ble_stat_t ll_intf_le_term_big(uint8_t big_hndle, uint8_t reason);

#endif /* SUPPORT_BRD_ISOCHRONOUS || SUPPORT_SYNC_ISOCHRONOUS*/

#if(SUPPORT_CONNECTED_ISOCHRONOUS && SUPPORT_SLAVE_CONNECTION)
/*=============== LL write connection accept timeout Command ===============*/
/**
 * @brief  								:this command is used to write connection timeout for cis connection
 * 										 after that the cis is rejected
 * @param  accept_tout[in]				: the accept timeout to be written
 *
 * @retval ble_stat_t					: Command status.
 */

ble_stat_t ll_intf_write_connection_accept_tout(uint16_t accept_tout);

/*=============== LL read connection accept timeout Command ===============*/
/**
 * @brief  								:this command is used to read connection timeout for cis connection
 * 										 after that the cis is rejected
 * @param  ptr_accept_tout[out]				: pointer to timeout to be read
 *
 * @retval ble_stat_t					: Command status.
 */

ble_stat_t ll_intf_read_connection_accept_tout(uint16_t *ptr_accept_tout);
#endif

#if (SUPPORT_LE_POWER_CONTROL)
/**
 * @brief  Used for setting the custom golden range RSSI
 *
 * @param  upper_limit			: [in]
 * @param  lower_limit		: [in]
 *
 * @retval Success
 */
ble_stat_t ll_intf_set_cstm_rssi_golden_range(int lower_limit , int upper_limit);
#endif /* (SUPPORT_LE_POWER_CONTROL) */
#if ((SUPPORT_LE_ENHANCED_CONN_UPDATE || SUPPORT_CONNECTED_ISOCHRONOUS )&&( SUPPORT_MASTER_CONNECTION || SUPPORT_SLAVE_CONNECTION))
/**  @}
*/

/** @ingroup  controller_info
 *  @{
 */
/*=============== LE Set Host Feature Command ===============*/
/**
 * @brief  : The HCI_LE_Set_Host_Feature command is used by the Host to set or clear a bit controlled by the Host in the Link Layer FeatureSet stored in the Controller
 *
 * @param  bit_num     		: bit number to be changed
 * @param  bit_value     	: value to be stored in the link_layer features
 *
 * @retval ble_stat_t	: Command status.
 */
ble_stat_t ll_intf_le_set_host_feature(uint8_t bit_num, uint8_t bit_value);
#endif /* #if ((SUPPORT_LE_ENHANCED_CONN_UPDATE || SUPPORT_CONNECTED_ISOCHRONOUS )&&( SUPPORT_MASTER_CONNECTION || SUPPORT_SLAVE_CONNECTION)) */
#if((SUPPORT_CONNECTED_ISOCHRONOUS &&( SUPPORT_MASTER_CONNECTION || SUPPORT_SLAVE_CONNECTION)) \
	||(SUPPORT_BRD_ISOCHRONOUS || SUPPORT_SYNC_ISOCHRONOUS))


/*=============== LE Setup ISO Data Path Command ===============*/
/**
 * @brief  								: is used to identify and create the isochronous data path between the Host and the Controller
 * 										  for an established CIS or BIS identified by the Connection_Handle parameter.
 * @param  conn_hndl					: contains the identifier of the Connection_Handler.
 * @param  ptr_st_setup_iso_data_path	: pointer that carries the information parameters of setup_iso_data_path
 *
 * @retval ble_stat_t					: Command status.
 */
ble_stat_t ll_intf_setup_iso_data_path(uint16_t conn_hndl, ble_intf_setup_iso_data_path* ptr_st_setup_iso_data_path);

/*=============== LE Remove ISO Data Path Command ===============*/
/**
 * @brief  								: is used to remove the input and/or output data path(s) associated
 * 										  with a CIS or BIS identified by the Connection_Handle parameter
 * @param  conn_hndl					: contains the identifier of the Connection_Handler.
 * @param  data_path_dirc				: ( w.r.t the controller) specifies the data path to be removed
 *
 * @retval ble_stat_t					: Command status.
 */
ble_stat_t ll_intf_rmv_iso_data_path(uint16_t conn_hndl, uint8_t data_path_dirc);

/*=============== LE ISO Test End Command ===============*/
/**
 * @brief  								: (This command should only be used for testing purposes) is used to terminate the ISO Transmit and/or Receive Test mode for a CIS or BIS
 * 										  specified by the Connection_Handle parameter but does not terminate the CIS or BIS.
 * @param  conn_hndl					: contains the identifier of the Connection_Handler.
 * @param  rcvd_pckt_cntr				: number of received packets
 * @param  missed_pckt_cntr				: number of missed packets
 * @param  failed_pckt_cntr				: number of failed packets
 *
 * @retval ble_stat_t					: Command status.
 */
ble_stat_t ll_intf_le_iso_test_end(uint16_t conn_hndl, uint32_t* rcvd_pckt_cntr,
		uint32_t * missed_pckt_cntr, uint32_t *failed_pckt_cntr);



#if(SUPPORT_BRD_ISOCHRONOUS|| SUPPORT_MASTER_CONNECTION || SUPPORT_SLAVE_CONNECTION || SUPPORT_SYNC_ISOCHRONOUS)

/*=============== LE Read Buffer Size V2 Command ===============*/
/**
 * @brief  :	Read the maximum size of the data portion of HCI LE ACL Data Packets, ISO packets sent from the Host to the Controller .
 *
 * @param  le_acl_data_pkt_length     	: Max length (in octets) of the data portion of each HCI ACL Data Packet that the controller is able to accept .
 * @param  total_num_le_acl_data_pkts 	: Total number of HCI ACL Data Packets that can be stored in the data buffers of the controller .
 * @param  iso_data_pkt_length     	: Max length (in octets) of the data portion of each HCI ISO Data Packet that the controller is able to accept .
 * @param  total_num_iso_data_pkts 	: Total number of HCI ISO Data Packets that can be stored in the data buffers of the controller .
 *
 * @retval ble_stat_t	: Command status.
 */
ble_stat_t ll_intf_le_read_buffer_size_v2(uint16_t *le_acl_data_pkt_length,
		uint8_t *total_num_le_acl_data_pkts, uint16_t *iso_data_pkt_length,
		uint8_t *total_num_iso_data_pkts);

/**  @}
*/

/** @ingroup  iso_cfg
 *  @{
 */
/*=============== LE Read ISO Tx Sync Command ===============*/
/**
 * @brief  								: is used to read the Time_Stamp and Time_Offset of a transmitted SDU identified
 * 										  by the Packet_Sequence_Number on a CIS or BIS identified by the Connection_Handle parameter on the master or slave.
 * @param  conn_hndl					: contains the identifier of the Connection_Handler.
 * @param  pkt_seq_num					: contains the sequence number of a transmitted SDU
 * @param  time_stamp					: contains the time stamp of a transmitted SDU
 * @param  time_ofst					: contains the time offset of a transmitted SDU
 *
 * @retval ble_stat_t					: Command status.
 */
ble_stat_t ll_intf_le_read_iso_tx_sync(uint16_t conn_hndl, uint16_t* pkt_seq_num,
		uint32_t *time_stamp,uint32_t * time_ofst);

/*=============== LE ISO Tx Test Command ===============*/
/**
 * @brief  								: is used to configure an established CIS or BIS specified by the Connection_Handle parameter,
 * 										  and transmit test payloads which are generated by the Controller
 * @param  conn_hndl					: contains the identifier of the Connection_Handler.
 * @param  pyld_t						: defines the configuration of SDUs in the payload
 *
 * @retval ble_stat_t					: Command status.
 */
ble_stat_t ll_intf_le_iso_tx_test(uint16_t conn_hndl, uint8_t pyld_t);
#endif /* (SUPPORT_EXPLCT_BROADCASTER_ROLE|| SUPPORT_MASTER_CONNECTION || SUPPORT_SLAVE_CONNECTION) */


#if(SUPPORT_SYNC_ISOCHRONOUS || SUPPORT_MASTER_CONNECTION || SUPPORT_SLAVE_CONNECTION)

/*=============== LE Read ISO Link Quality Command ===============*/
/**
 * @brief  :	Read the maximum size of the data portion of HCI LE ACL Data Packets, ISO packets sent from the Host to the Controller .
 *
 * @param  conn_hndl     					: connection handle of CIS or BIS.
 * @param  ptr_read_iso_link_output     	: pointer to structure that contains counters to be filled in the specified CIS Identified by the cis_hndl .
 *
 * @retval ble_stat_t	: Command status.
 */
ble_stat_t ll_intf_le_read_iso_link_quality(uint16_t conn_hndl, ble_intf_read_iso_link_cmd_st * ptr_read_iso_link_output);

/*=============== LE ISO Rx Test Command ===============*/
/**
 * @brief  								: (This command should only be used for testing purposes) is used to configure an established CIS
 * 										  or a synchronized BIG specified by the Connection_Handle parameter to receive payloads
 * @param  conn_hndl					: contains the identifier of the Connection_Handler.
 * @param  pyld_t						: defines the configuration of SDUs in the payload
 *
 * @retval ble_stat_t					: Command status.
 */
ble_stat_t ll_intf_le_iso_rx_test(uint16_t conn_hndl, uint8_t pyld_t);

/*=============== LE ISO Rx Test Counetrs Command ===============*/
/**
 * @brief  								: (This command should only be used for testing purposes) is used to read the test counters ) in the Controller which is configured in
 * 										  ISO Receive Test mode for a CIS or BIS specified by the Connection_Handle.
 * @param  conn_hndl					: contains the identifier of the Connection_Handler.
 * @param  rcvd_pckt_cntr				: number of received packets
 * @param  missed_pckt_cntr				: number of missed packets
 * @param  failed_pckt_cntr				: number of failed packets
 *
 * @retval ble_stat_t					: Command status.
 */
ble_stat_t ll_intf_le_iso_read_test_cntrs(uint16_t conn_hndl, uint32_t* rcvd_pckt_cntr, uint32_t * missed_pckt_cntr, uint32_t *failed_pckt_cntr );
#endif /* (SUPPORT_EXPLCT_OBSERVER_ROLE || SUPPORT_MASTER_CONNECTION || SUPPORT_SLAVE_CONNECTION) */

#endif /* (SUPPORT_CONNECTED_ISOCHRONOUS &&( SUPPORT_MASTER_CONNECTION || SUPPORT_SLAVE_CONNECTION)) \
	||(SUPPORT_BRD_ISOCHRONOUS || SUPPORT_SYNC_ISOCHRONOUS) */

/*=============== LE Set EcoSystem Base Interval Command ===============*/
/**
 * @brief  : TheSet EcoSystem Base Interval Command is used by the Host to hint the controller with the best radio period
 *
 * @param  interval     	: hinted interval from the host
 *
 * @retval ble_stat_t	: Command status.
 */
ble_stat_t ll_intf_set_ecosystem_base_interval(uint16_t interval);
/**  @}
*/

/*##### Curb Sleep State Commands Group #####*/
/** @ingroup  curb_sleep_ll_intf
 *  @{
 */
/*=============== Curb Sleep State Command ===============*/
/**
 * @brief Forwards to llhwc_cmn to take decision whether to prevent device form
 * 			entering sleep state
 *
 * @param state [in]: Enable/Disable preventing sleep state mode
 *
 * @retval ble_state_t : Command status
 */
ble_stat_t ll_intf_curb_sleep_state(uint8_t state);
/**  @}
*/

/** @ingroup  vendor_cfg Vendor Specific Commands
 * @{
 */
/*=============== Configure LL Context Control Command ===============*/
/**
 * @brief Used to configure the LL contexts, where:
 * 			1. For bare-metal:
 * 			- High ISR is executed in the ISR context
 * 			- Low ISR can be executed in the high ISR context, or switched to low ISR context
 * 			2. For RTOS:
 * 			- High ISR is executed in the ISR context
 * 			- Low ISR is executed in the thread of the "linkLayerHighPrioTask"
 *
 * @param allow_low_isr : [in] Configuration parameter for the context of the low ISR in the bare-metal model. Range is [0,1].
 * 								0: Low ISR code is executed in the same context of the high ISR.
 * 								1: Low ISR code is executed in the context of the low ISR (by configuring a low priority interrupt that is triggered by FW).
 * @param run_post_evnt_frm_isr : [in] Configuration parameter to decide whether the scheduling of the next BLE event is done in the low ISR context or to be handled by the LL main thread. Range is [0,1].
 * 								0: BLE next event scheduling is handled in the LL main thread.
 * 								1: BLE next event scheduling is handled in the low ISR context.
 *
 * @retval ble_state_t : Command status
 */
ble_stat_t ll_intf_config_ll_ctx_params(uint8_t allow_low_isr, uint8_t run_post_evnt_frm_isr);



/**
* @brief  Get the value of link layer timer in microsecond aligned with sleep timer clock edge
* Microsecond timing can be calculated as Return value (steps) * Multiplier /divider taking into consideration to implement calculation in good accuracy
*
* @param  multiplier : Value that should be multiplied by the return steps
* @param  divider    : the product of the steps and multiplier should be divided by this value
*
* @retval number of steps : Read number of steps.
* @note Caller should call it in a critical section to make sure the timing is not drifted by interrupt serving
*/
uint32_t ll_intf_get_aligned_us_now(uint32_t*  multiplier ,   uint32_t *divider);
/**@}
 */

#if SUPPORT_PTA
/*##### Packet Traffic Arbitration (PTA) Commands Group #####*/
/** @ingroup  pta_ll_intf
 *  @{
 */
/**
 * @brief Initializes the PTA init
 *
 * @param request_to_event_time :[IN] Time between the request signal assertion
 * 									  and beginning of event on air.
 *
 * @retval INVALID_HCI_COMMAND_PARAMETERS:
 * 			If request to event time is not in range 20us to MIN(Tx Config / Rx Config)
 * @retval COMMAND_DISALLOWED: All other PTA error codes
 * @retval SUCCESS: Otherwise
 */
ble_stat_t ll_intf_pta_init(
		const uint8_t request_to_event_time);

/**
 * @brief Enables the PTA in the hardware
 *
 * @param enable: [IN] Enable/Disable Indicator
 *
 * @retval COMMAND_DISALLOWED: If events exist in the system or the pta_enable
 * 				returns any error code.
 * @retval SUCCESS: Otherwise
 */
ble_stat_t ll_intf_pta_enable(
		const uint8_t enable);

#if (SUPPORT_MASTER_CONNECTION || SUPPORT_SLAVE_CONNECTION || \
	(SUPPORT_LE_EXTENDED_ADVERTISING && SUPPORT_LE_PERIODIC_ADVERTISING && (SUPPORT_EXPLCT_OBSERVER_ROLE || SUPPORT_SYNC_ISOCHRONOUS)))
/**
 * @brief Priority configuration function for the ACL and Periodic Scan events
 *
 * @param event_type	:[IN] Either ACL or Periodic Scan event.
 * @param handle		:[IN] ACL Handle or Periodic Scan Handle.
 * @param priority		:[IN] Determines the state of each priority mode.
 * @param priority_mask	:[IN] Determines which priorities are in effect in
 * 							  the priority variable.
 * @param acl_multi_slot_nbr_of_packets	:[IN] Number of protected slots.
 * @param link_loss_limit_timeout		:[IN] Timeout percentage for link loss mode
 *
 * @retval COMMAND_DISALLOWED: If the PTA is not enabled.
 * @retval INVALID_HCI_COMMAND_PARAMETERS: For all the other PTA error codes.
 * @retval SUCCESS: Otherwise
 */
ble_stat_t ll_intf_pta_ble_set_link_coex_priority(
		const pta_link_coex_event_type event_type,
		const uint16_t handle,
		const uint32_t priority,
		const uint32_t priority_mask,
		const uint8_t acl_multi_slot_nbr_of_packets,
		const uint8_t link_loss_limit_timeout);
#endif /* (SUPPORT_MASTER_CONNECTION || SUPPORT_SLAVE_CONNECTION || \
		  (SUPPORT_LE_EXTENDED_ADVERTISING && SUPPORT_LE_PERIODIC_ADVERTISING && (SUPPORT_EXPLCT_OBSERVER_ROLE || SUPPORT_SYNC_ISOCHRONOUS))) */

#if (SUPPORT_BRD_ISOCHRONOUS || SUPPORT_SYNC_ISOCHRONOUS || \
	(SUPPORT_CONNECTED_ISOCHRONOUS && (SUPPORT_MASTER_CONNECTION || SUPPORT_SLAVE_CONNECTION)))

/**
 * @brief Priority configuration function for the BIG and CIG events.
 *
 * @param iso_type		:[IN] Either BIG or CIG event.
 * @param group_id		:[IN] Isochronous Group ID.
 * @param priority		:[IN] Determines the state of each priority mode.
 * @param priority_mask	:[IN] Determines which priorities are in effect in
 * 							  the priority variable.
 * @param link_loss_limit_timeout :[IN] Timeout percentage for link loss mode
 *
 * @retval COMMAND_DISALLOWED: If the PTA is not enabled.
 * @retval INVALID_HCI_COMMAND_PARAMETERS: For all the other PTA error codes.
 * @retval SUCCESS: Otherwise
 */
ble_stat_t ll_intf_pta_ble_set_iso_coex_priority(
		const pta_iso_type iso_type,
		const uint8_t group_id,
		const uint32_t priority,
		const uint32_t priority_mask,
		const uint8_t link_loss_limit_timeout);
#endif /* (SUPPORT_BRD_ISOCHRONOUS || SUPPORT_SYNC_ISOCHRONOUS || \
		  (SUPPORT_CONNECTED_ISOCHRONOUS && (SUPPORT_MASTER_CONNECTION || SUPPORT_SLAVE_CONNECTION))) */

/**
 * @brief Generic Priority configuration function.
 *
 * @param priority		:[IN] Determines the state of each priority mode.
 * @param priority_mask	:[IN] Determines which priorities are in effect in
 * 							  the priority variable.
 *
 * @retval COMMAND_DISALLOWED: If the PTA is not enabled.
 * @retval INVALID_HCI_COMMAND_PARAMETERS: For all the other PTA error codes.
 * @retval SUCCESS: Otherwise
 */
ble_stat_t ll_intf_pta_ble_set_coex_priority(
		const uint32_t priority,
		const uint32_t priority_mask);
/** @}
*/
#endif /* SUPPORT_PTA */

/** @ingroup vendor_cfg Vendor Specific Commands
 *  @{
 */
/**
 * @brief this function is used to Start unmodulated carrier  Mode
 * @param channel : input to selected channel from 0 to 39
 * @param offset  : offset will have a step of 244 hz
 * 					from -8196 steps(around -2Mhz) to 8196 steps(around 2Mhz)
 * @param phy     : rate to start unmodulated carrier mode on ( LE_1M , LE_2M )
 * @param  Tx_power_level		: indicate TX Power level.
 * @retval status.
 */
ble_stat_t ll_init_start_unmod_carrier(uint8_t channel, int16_t offset , uint8_t phy, int8_t tx_power_level);
/*===========	End working phy mode (continuous modulation mode or unmodulated carrier mode)	============*/
/**
 * @brief function to check and stop the running phy mode in  case of a new event is
 *  started while the continuous modulation mode or unmodulated carrier mode is running
 * @retval status.
 */
ble_stat_t ll_init_stop_unmod_carrier();

/**
 * @brief this function is used to Start continuous DTM  Mode
 * @param  ch_index				: Logical channel index of DTM .
 * @param  packet_payload		: DTM pay-load type.
 * @param  phy					: PHY type, 1M/2M/coded PHY.
 * @param  Tx_power_level		: indicate TX Power level.
 * @retval status.
 */
ble_stat_t ll_init_start_cont_dtm(uint8_t ch_index, uint8_t phy, uint8_t packet_payload, int8_t tx_power_level);
/**
 * @brief this function is used to Read Register from Phy
 * @param  phy_reg				: Address of register .
 * @param  value				: Pointer to store value of register in it.
 * @retval status.
 * @note this APi should be called after curb sleep to have a proper
 * 		 functionality as it should be called after PHY is started
 * 		 ,otherwise, it will return COMMAND_DISALLOWED
 */
ble_stat_t ll_intf_le_read_phy_reg(uint8_t phy_reg, uint8_t* value);

/**
 * @brief this function is used to Write value in Register of Phy
 * @param  phy_reg				: Address of register .
 * @param  value				: value to be stored in register.
 * @retval status.
 * @note this APi should be called after curb sleep to have a proper
 * 		 functionality as it should be called after PHY is started
 * 		 ,otherwise, it will return COMMAND_DISALLOWED
 */
ble_stat_t ll_intf_le_write_phy_reg(uint8_t phy_reg, uint8_t value);

/**
 * @brief flag to the LL the existence of a temperature sensor
 * @retval status
 */
void ll_intf_set_temperature_sensor_state(void);
/**
 * @brief set the current temperature
 * @param temperature		:	The current temperature
 * @retval status
 */
uint32_t  ll_intf_set_temperature_value(uint32_t temperature);
/**
 * @brief This function returns the number of packets sent in Direct Test Mode.
 * @param[out] packet_number	: number of packets 
 * @retval ble_stat_t	: Command status.
 * @note the value will not be cleared until the next Direct TX test starts.
 */
ble_stat_t ll_intf_le_tx_test_packet_number(uint32_t* packet_number);

/**
 * @brief This function returns the value of rssi.
 * @param[out] rssi    	: rssi value 
 * @retval ble_stat_t	: Command status.
 */
ble_stat_t ll_intf_read_raw_rssi(int32_t* rssi);

/*===============  Set Tx Free Carrier Command ===============*/
/**
 * @brief  Set Tx free carrier mode .
 * This function is used ot disable or enable Transmit Free carrier on a given channel
 * @note this API should only be called if there is no events registered ( for example , Advertising , Connection, etc..)
 *
 * @param  enable     : [in] input argument to control TX free carrier mode
 * 						True --> start transmission of free carrier on specific channel
 * 						False --> Stop transmission of free carrier if it is already started
 *
 * @param  channel_idx     : [in] RF channel index of the used channel
 *
 * @retval ble_stat_t : Command status to be sent to the Host.
 */
ble_stat_t ll_intf_set_tx_free_carrier(uint8_t enable, uint8_t channel_idx);

#if(END_OF_RADIO_ACTIVITY_REPORTING)
/**
 * @brief This function sets the bitmask associated to END_OF_RADIO_ACTIVITY_EVENT.
 * 		Only the radio activities enabled in the mask will be reported to application by 
 * 		END_OF_RADIO_ACTIVITY_EVENT.
 * 		 
 * @param[in] mask    	: bitmask of the events, the mask can take one of the following
 * 					 	values (or a bitwise OR of them in case of a mask for multiple events)
 * 			(0x0001) idle
 * 			(0x0002) advertising and extended advertising events
 * 			(0x0004) peripeheral in connection state event
 * 			(0x0008) scanning and extended scanning events
 * 			(0x0020) central in connection state event
 * 			(0x0200) periodic advertising event
 * 			(0x0400) periodic scanning event
 * 			(0x0800) isochronous broadcast advertising event
 * 			(0x1000) isochronous broadcast scanning event
 * 			(0x2000) peripheral in isochronous connection state event
 * 			(0x4000) central in isochronous connection state event
 * 		note that the following values are reserved and will be ignored upon recepient
 * 			(0x0010, 0x0040, 0x0080, 0x0100, 0x8000)
 * 
 * @retval ble_stat_t	     : Command status.
 */
ble_stat_t ll_intf_set_end_of_activity_mask(uint16_t mask);
#endif /* END_OF_RADIO_ACTIVITY_REPORTING */

/**
 * @brief This function returns the status of the 8 BLE links managed by the device.
 * @param[out] sm_status    		: pointer to array of per running state machine status.
 * @param[out] link_conn_handle		: pointer to array of per running state machine handle.
 * @retval ble_stat_t	: Command status.
 */
ble_stat_t ll_intf_get_link_status(uint8_t *sm_status, uint8_t *link_conn_handle);

#if (SUPPORT_MASTER_CONNECTION && SUPPORT_CHANNEL_CLASSIFICATION)
/**
 * @brief this function is used control the channel reporting mode of the controller
 * @param[in]  conn_handle_id	: identifier of the connection.
 * @param[in]  ptr_reporting_params		: pointer to structure holding the reporting parameters as follows:
 * 					report_mode		: reporting mode value.
 * 										0 : disable
 * 										1 : enable
 * 					min_spacing 	:min spacing value (min time between
 * 									2 consecutive LL_CHANNEL_STATUS 
 * 									"unit of 200 ms")
 * 										5 (1 sec) <= min_spacing <= 150 (30 sec)
 * 					max_delay 		:max delay value (max time between
 * 									channel classification change and 
 * 									LL_CHANNEL_STATUS sending "unit of 200 ms")
 * 										5 (1 sec) <= max_delay <= 150 (30 sec)
 * @retval status.
 */
ble_stat_t ll_intf_cntrl_chnl_clsfction_report(uint16_t conn_handle_id, void *ptr_reporting_params);
#endif /* (SUPPORT_MASTER_CONNECTION && SUPPORT_CHANNEL_CLASSIFICATION) */

#if SUPPORT_LE_ENHANCED_CONN_UPDATE
/*===============  LE Set Default Subrate Parameters  ===============*/
/**
 * @brief Used to save default subrate parameters to be used to test the future incoming subrate requests from the slave against them to decide whether to accept or reject them
 *
 * @param  subrate_default_params : [in] pointer to structure includes all subrate default parameters from the host.
 *
 * @retval Status(0:SUCCESS, 0xXX:ERROR_CODE)..
 */
ble_stat_t ll_intf_le_set_default_subrate(
		subrate_default_params_t * subrate_default_params
				);
/*===============  LE Subrate Request  ===============*/
/**
 * @brief Used to process the subrate request from the host to start the subrate procedure based on the current controller role in the input connection.
 *
 * @param  conn_handle_id : [in] the identifier of the ACL connection to start the subrate procedure on it.
 *
 * @param  subrate_default_params : [in] structure includes all subrate parameters from the host to start the procedure based on them.
 *
 * @retval Status(0:SUCCESS, 0xXX:ERROR_CODE).
 */
ble_stat_t ll_intf_le_subrate_req(
			uint16_t conn_handle      ,
			subrate_default_params_t subrate_requested_param
			);
#endif /* SUPPORT_LE_ENHANCED_CONN_UPDATE */

/**  @}
*/


#if SUPPORT_HCI_EVENT_ONLY

/*
 * @brief register callback to be called on LL queue is full
 * @param cbk:  host callback
 * @retval None
 * */
void ll_intf_rgstr_hst_cbk_ll_queue_full(hst_cbk_queue_full cbk);

/*
 * @brief register callback to be called sending data to host
 * @param upper_layer_cbk:  host callback
 * @retval None
 * */
void ll_intf_rgstr_hst_cbk(hst_cbk upper_layer_cbk);

typedef union _change_state_options_t
{
	uint8_t  combined_value;
	struct {
		uint8_t allow_generic_event: 1;
		uint8_t allow_acl_data: 1;
		uint8_t allow_iso_data: 1;
		uint8_t allow_reports: 1;
		uint8_t rfu: 4;
	} bitfield;
} change_state_options_t;
/**
 * @brief This function is used to indicate to the LL that the host
 * 		  is ready to receive events as indicated by options parameter
 * @param options: [In] bit-field to set specific events on
 * @retval None
 */
void ll_intf_chng_evnt_hndlr_state(change_state_options_t options);




/*
 * @brief sets the event mask in hci event only configuration
 * @param event_mask : [In] an array of 8 bytes representing new event mask
 * @retval: 		   None
 * */
void ll_intf_set_event_mask(uint8_t event_mask[8]);

/*
 * @brief sets page2 event mask in hci event only configuration
 * @param event_mask : [In] an array of 8 bytes representing new event mask
 * @retval: 		   None
 * */
void ll_intf_set_event_mask_page2(uint8_t event_mask[8]);


/*
 * @brief sets the LE event mask in hci event only configuration
 * @param event_mask : [In] an array of 8 bytes representing new event mask
 * @retval: 		   None
 * */
void ll_intf_set_le_event_mask(uint8_t event_mask[8]);


/*
 * @brief Delete ACL/ISO data related to a specific connection handle
 * @param : [In] ACL or Cis or Bis conenction handle
 * @retval: UNKNOWN_CONNECTION_IDENTIF if conn_Handle doesn't belong to any state machine. False
 * 			if no data was found for conn_Handle and True if any data was deleted.
 * */
ble_stat_t ll_intf_clear_event(uint16_t conn_Handle);

/*
 * @brief sets the custom event mask in hci event only configuration
 * @param cstm_evnt_mask : [In] custom event mask bitfield
 * @retval: 		  		None
 * */
void ll_intf_set_custom_event_mask(uint8_t cstm_evnt_mask);

#endif /* SUPPORT_HCI_EVENT_ONLY */
/** @ingroup  iso_cfg
 *  @{
 */
#if (SUPPORT_CONNECTED_ISOCHRONOUS && (SUPPORT_MASTER_CONNECTION || SUPPORT_SLAVE_CONNECTION))
/**
 * @brief  register a callback function to be called on missed cig events,
 * 			the cbk reports the current cig id, number of accumulated missed
 * 			events and the anchor point of the next scheduled cig event
 *
 * @param  cbk : [in] pointer to the callback function to be registered 
 *
 * @retval None
 */
void ll_intf_rgstr_missed_cig_evnts_cbk(hst_cig_missed_evnt_cbk cbk);

#endif /* (SUPPORT_CONNECTED_ISOCHRONOUS && (SUPPORT_MASTER_CONNECTION || SUPPORT_SLAVE_CONNECTION)) */

#if (SUPPORT_BRD_ISOCHRONOUS || SUPPORT_SYNC_ISOCHRONOUS)
/**
 * @brief  register a callback function to be called on missed big events,
* 			the cbk reports the current big handle, number of accumulated missed
 * 			events and the anchor point of the next scheduled big event
 *
 * @param  cbk : [in] pointer to the callback function to be registered 
 *
 * @retval None
 */
void ll_intf_rgstr_missed_big_evnts_cbk(hst_big_missed_evnt_cbk cbk);

#endif /* (SUPPORT_BRD_ISOCHRONOUS || SUPPORT_SYNC_ISOCHRONOUS) */
/**@}
*/
/** @ingroup  vendor_cfg Vendor Specific Commands
*  @{
*/
#if (SUPPORT_AOA_AOD)

/**
 * @brief	Set the number of antennas to be used by the controller, number of 
 * 			antennas is used as an upper limit for antenna_id set by the host
 * 
 * @param	num_of_antennas: [in] number of antennas
 * 
 * @retval status  : [out] 0:SUCCESS, 0xXX:ERROR_CODE.
 */
ble_stat_t ll_intf_set_num_of_antennas(uint8_t num_of_antennas);

/**
 * @brief 	Get the number of antennas configured to the controller
 * 
 * @param	ptr_num_of_antennas: [out] pointer to a variable hold
 *  			number of antennas retrived
 * 
 * @retval status  : [out] 0:SUCCESS, 0xXX:ERROR_CODE.
 */
ble_stat_t ll_intf_get_num_of_antennas(uint8_t *ptr_num_of_antennas);

#endif /* SUPPORT_AOA_AOD */

/**
 * @brief 	Set number of packets to be transmitted on DTM mode.
 *
 * @param	pckt_count: [in] number of packets to be transmitter
 *
 * @note   for non-zero values of pckt_count, DTM start on TX mode will trigger sending packets with the specified 
 * 		number (pckt_count), if the value of pckt_count is Zero, DTM start on TX mode will trigger sending
 *  		indefinite number of packets untill subsequent DTM stop is called or HCI reset is sent.
 *
 * @retval status  : [out] 0:SUCCESS, 0xXX:ERROR_CODE.
 */
ble_stat_t ll_intf_set_dtm_with_spcfc_pckt_count(uint16_t pckt_count);

/**
 * @brief  used to update the event timing.
 *
 * @param  p_evnt_timing[in]: pointer to structure containing the new Event timing requested from the Upper layer.
 *
 * @retval None
 */
void ll_intf_config_schdling_time(Evnt_timing_t * p_evnt_timing);
/**@}
*/

#endif /* INCLUDE_LL_INTF_H */
