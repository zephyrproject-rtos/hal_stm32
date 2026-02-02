/*$Id: //dwh/bluetooth/DWC_ble154combo/firmware/rel/2.00a-lca04/firmware/public_inc/ral.h#1 $*/
/**
 ********************************************************************************
 * @file    ral.h
 * @brief   The file include description for the RAL (Radio Abstraction Layer) interfaces and call backs,
 * 			RAL provides functionalities to start, stop and manage different types of events [Transmission - Reception - Energy scanning].
 *
 *
 *
 ******************************************************************************
 * @copy
 * Synopsys MIT License:
 * Copyright (c) 2020-Present Synopsys, Inc
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of the software and
 * associated documentation files (the “Software”), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies
 * of the Software, and to permit persons to whom the Software is furnished to do so, subject to the
 * following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial
 * portions of the Software.
 *
 * THIS SOFTWARE IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING, BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE, AND NONINFRINGEMENT. IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT, OR OTHERWISE
 * ARISING FROM, OUT OF, OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 * */
 
#ifndef INCLUDE_RAL_H_
#define INCLUDE_RAL_H_

#include "common_types.h"
#include "os_wrapper.h"
#include "mac_host_intf.h"
#include "instance.h"
#include "radio.h"
#if SUPPORT_ENH_ACK_LINK_METRICS_PROBING_OT_1_2
#include "platform.h"
#endif
/* Defines */
/** An index used in multi-instance for specifying which instance to perform operation on */
typedef uint8_t ral_instance_t;
/**
 * @brief Enum defines the current state for RAL events
 *
 *
 *						ral event allocation
 *						  ==============
 *ral_add_tx_fifo() _ _ _ =  RAL_IDLE  =
 *						  ==============
 *
 *																					      ==============
 *											      			_ _(Requires ack)_ _ _ _ _ _ _= RAL_RX_ACK =
 *						ral event allocation     		  /             			      ==============
 *						  =============                	 /
 * ral_start_tx() _ _ _ _ = RAL_TX_PKT =_ _ ral_isr()_ _/
 *						  =============		   			\
 *						  					    		 \								  ==============
 *						  					     		  \_ _(Doesn't require ack)_ _ _ _= RAL_TX_PKT =
 *																						  ==============
 *
 *																				      	  ==============
 *											      			_ _(Requires ack)_ _ _ _ _ _ _= RAL_TX_ACK =
 *						ral event allocation     		  /             			      ==============
 *						  =============                	 /
 * ral_start_rx() _ _ _ _ = RAL_RX_PKT =_ _ ral_isr()_ _/
 *						  =============		   			\
 *						  					    		 \								  ==============
 *						  					     		  \_ _(Doesn't require ack)_ _ _ _= RAL_RX_PKT =
 *																						  ==============
 *						ral event allocation
 *						  ==============
 *ral_ed_scan() _ _ _ _ _ =   RAL_ED   =
 *						  ==============
 *
 *
 */
typedef enum ral_event_state_enum {
	RAL_IDLE,
	RAL_RX_PKT,
	RAL_TX_PKT,
	RAL_RX_ACK,
	RAL_TX_ACK,
	RAL_ED
} ral_event_state_enum_t;

/**
 * @brief Enum used for RAL configuration assignment
 *
 */
typedef enum ral_state_enum {
	RAL_DISABLE = 0,
	RAL_ENABLE = 1
} ral_state_enum_t;

/**
 * @brief Enum defines RAL error codes
 *
 */
typedef enum ral_error_enum {
    RAL_ERROR_NONE = 0,
    RAL_ERROR_FAILED = 1,
    RAL_ERROR_DROP = 2,
    RAL_ERROR_NO_BUFS = 3,
    RAL_ERROR_BUSY = 5,
    RAL_ERROR_INVALID_PARAMETERS = 7,
    RAL_ERROR_SECURITY = 8,
    RAL_ERROR_NO_ADDRESS = 10,
    RAL_ERROR_ABORT = 11,
    RAL_ERROR_NOT_SUPPORTED = 12,
    RAL_ERROR_INVALID_STATE = 13,
    RAL_ERROR_NO_ACK = 14,
    RAL_ERROR_CCA_FAILURE = 15,
    RAL_ERROR_FCS = 17,
    RAL_ERROR_NO_FRAME_RECEIVED = 18,
    RAL_ERROR_INVALID_SOURCE_ADDRESS = 20,
    RAL_ERROR_DESTINATION_ADDRESS_FILTERED = 22,
	RAL_ERROR_TIMER_ISR = 23,
#if SUPPORT_ENH_ACK_LINK_METRICS_PROBING_OT_1_2
	RAL_ERROR_LINK_METRICS_INVALID_ARGS,
	RAL_ERROR_LINK_METRICS_NOT_FOUND,
	RAL_ERROR_LINK_METRICS_NO_BUF,
#endif /* SUPPORT_ENH_ACK_LINK_METRICS_PROBING_OT_1_2 */
#if SUPPORT_ANT_DIV
	RAL_ERROR_AD_NOT_IN_CONFIG_STATE,
#endif /* SUPPORT_ANT_DIV */
#if SUPPORT_CONFIG_LIB
	RAL_ERROR_CONFIG_LIB_NOT_IN_CONFIG_STATE,
#endif /* SUPPORT_CONFIG_LIB */
    RAL_ERROR_GENERIC = 255
} ral_error_enum_t;

/**
 * @brief Enum defines power states for RAL where:
 *
 * RAL_POWER_SLEEP: power state of the RAL when not executing any event.
 * RAL_POWER_ACTIVE: power state of the RAL before starting of any event.
 */
typedef enum ral_power_state_enum {
	RAL_POWER_SLEEP,
	RAL_POWER_ACTIVE
} ral_power_state_enum_t;

/**
 * @brief Enum defines new TX retrial type:
 *
 * CONTINUE_CSMA_RETRY: continue of CSMA retry from csma_backoff_count.
 * START_NEW_FULL_TX_RETRY: start new TX retry from frm_retries_count.
 */
typedef enum tx_new_retry_enum {
	CONTINUE_CSMA_RETRY,
	START_NEW_FULL_TX_RETRY
}tx_new_retry_enum_t;

/**
 * @brief Enum defines packet source for transmission when calling ral_start_tx() to be added properly in RAL packet.
 *
 * RAL_SOURCE_PACKET: used in case of single packet transmission mode the packet is passed in ral_start_tx() and then copied to the allocated event.
 */
typedef enum ral_pkt_src_enum {
#if SUPPORT_A_MAC
/* RAL_SOURCE_FIFO: this mode is defined only for A_MAC. And used in case of burst transmission each packet is copied to a ral event using ral_add_tx_fifo().
 * 					all ral events linked to each other in a linked list which is attached to the ral instance initialized by the application.
 */
	RAL_SOURCE_FIFO,
#endif
	RAL_SOURCE_PACKET
} ral_pkt_src_enum_t;
/**
 * @brief Enum defines type of acknowledgment packet used in MAC 802.15.4
 *
 */
typedef enum ral_ack_type_enum {
	RAL_NO_ACK,
#if SUPPORT_A_MAC
	RAL_ACK_CUSTOM,
#endif
	RAL_ACK_MAC
} ral_ack_type_enum_t;
#if SUPPORT_CONFIG_LIB
/**
 * @brief Enum defines configurable library feature states
 *
 */
typedef enum config_lib_state_enum {
	NOT_CONFIGURED_NOT_INITIALIZED, ///< Initial state
	CONFIGURED_NOT_INITIALIZED, 	///< The state of post-reset or configuring using API
	CONFIGURED_INITIALIZED			///< Post-initialization state
} config_lib_state_enum_t;
#endif /* SUPPORT_CONFIG_LIB */
/** Define RAL time structure that contains fine and base */
typedef ble_time_t ral_time_st;

/**
 * @brief Structure represents RAL packet and contains the parameters of the sent/received RAL packet
 *
 */
typedef struct _ral_pkt_st {
	uint8_t * ptr_pyld;						///< Pointer to packet
	ral_time_st time_stamp;					///< Exact time in which the packet transmitted/received
	uint16_t num_ov_cycles;					///< Variable to store the number of cycles the overflow when packet is received
	uint16_t pyld_len;						///< Packet length
	uint8_t channel;						///< Channel at which the packet will be transmitted
	uint8_t rxchannelaftertxdone;			///< The RX channel after frame TX is done (after all frame retries - ack received, or timeout, or abort).
    /**
     * @brief Union represents TX/RX info
     *
     */
	union
    {
        struct
        {
		ral_pkt_src_enum_t pkt_src;		///< Source of transmitted packet
#if SUPPORT_RADIO_SECURITY_OT_1_2
		uint8_t *sec_key;				///< Pointer to the security key used in security processing
			uint8_t is_sec_proc_by_radio;	///< Flag to mark if security processed by radio or not
#endif
		int8_t tx_power;				///< Power of transmitted packet
		uint8_t last_tx_pkt;			///< Last transmitted packet flag
		uint8_t csl_frame;			    ///< True only if the current TX frame is a CSL frame
		uint8_t is_poll_req;		    ///< True only if the current TX frame is a poll reuest frame
        } tx_info;

        struct
        {
#if SUPPORT_RADIO_SECURITY_OT_1_2
		uint32_t ack_frm_cntr;  		///< frame counter used for secured Enhanced ACK
		uint8_t ack_key_id;				///< key index used for secured Enhanced ACK
		uint8_t is_sec_enh_ack; 		///< flag to mark usage of secured Enhanced ACK
#endif
            int8_t  rssi;					///< received signal strength indicator
            uint8_t lqi;					///< link quality indicator
            uint8_t ackFrmPending;			///< This indicates if this frame was acknowledged with frame pending set
        } rx_info;
    } tx_rx_u;
} ral_pkt_st;

/**
 * @brief Structure represents RAL event information and contains the full information of the transmitted/received event
 *
 */
typedef struct _ral_evnt_info_st{
	struct _ral_evnt_info_st * ptr_nxt_evnt;			///< Pointer to the next event, used in case of FIFO transmission
	/**
	 * @brief Union represents TX/RX and ED event info
	 *
	 */
	union
	{
		struct
		{
			ral_pkt_st * ptr_pkt;						///< Pointer to data packet
			ral_pkt_st * ptr_ack_pkt;					///< Pointer to the ACK packet used by this event
		} pkt_info;
		struct
		{
			uint32_t ed_scn_durn;						///< Energy detection scan duration
			int8_t ed_max_rssi;							///< Energy detection max RSSI value
		} ed_info;
	} ral_evnt_info_u;
	uint32_t ral_status_mask;							///< HW error mask of the received packet
	ral_instance_t ral_instance;						///< RAL identifier of this event
	ral_event_state_enum_t event_state;					///< Event type
	ral_error_enum_t evnt_error;						///< Event error passed to higher layers
#if (SUPPORT_PTA)
	uint8_t tx_pta_counter;								///< Either the PTA TX or RX reject counter depending on the packet type
	uint8_t rx_pta_counter;								///< Either the PTA TX or RX reject counter depending on the packet type
#endif /* SUPPORT_PTA */
} ral_evnt_info_st;

/**
 * @brief Structure represents MAC filtration parameters used by HW to filter received packets
 *
 */
typedef struct _ral_mac_fltr_confg_st {
	uint8_t ext_addr[EXT_ADDRESS_LENGTH];		///< The device extended address to compare the received address with
	uint16_t short_addr;						///< The device short address to compare the received address with
	uint16_t pan_id;							///< The device PAN ID to compare the received PAN ID in the packet with
	ral_state_enum_t mac_fltr_state;			///< MAC filter state, if disabled so the promiscuous mode is enabled
	uint8_t mac_implicit_broadcast;				///< MAC ImplictBoradcast PIB that is set in MAC layer
	/**
	 * The first bit used to determine if the device is pan coordinator or not.
	 * The second bit is indicating if this instance is currently performing scanning or not.
	 */
	uint8_t is_pan_coord;
} ral_mac_fltr_confg_st;

/**
 * @brief Structure represents configurations of filtration before sending ACK.
 *
 * 		  This structure contains the parameters used to filter the received packet
 * 		  and respond to this packet with ack or not
 *
 */
typedef struct _ral_ack_rspnd_fltr_confg_st {
#if SUPPORT_A_MAC
	uint8_t * ptr_comp_value;				///< Pointer to value to be compared with received data
	uint8_t byte_index;						///< Position of the byte start to be compared in the received data
	uint8_t byte_len;						///< Number of bytes to be compared in the received data
#endif
	ral_state_enum_t ack_fltr_state;		///< Enable/Disable packet filtration before sending ack
} ral_ack_rspnd_fltr_confg_st;

/**
 * @brief Structure represents ACK request bit configuration
 *
 */
typedef struct _ral_ack_req_confg_st {
	ral_state_enum_t ack_req_bit_state;	///< Enable/Disable ACK request bit check
	uint8_t byte_index;					///< Byte index of ACK request bit in TX/RX packet
	uint8_t bit_index;					///< Bit index of ACK request bit in TX/RX packet
} ral_ack_req_confg_st;

/**
 * @brief Structure represents RAL ACK data and contains the parameters of the acknowledgment configuration
 *
 */
typedef struct _ral_auto_ack_confg_st {
	ral_ack_rspnd_fltr_confg_st rspnd_fltr_confg;		///< Contains configured filters applied to the received packet to determine whether to send ACK or not
	ral_ack_req_confg_st ack_req_confg;					///< Contains configured ACK request bit configuration
	uint16_t auto_tx_ack_turnaround;					///< Time in microseconds between the received packet and TX ACK
	uint16_t auto_rx_ack_turnaround;					///< Time in microseconds between the transmitted packet and RX ACK
	uint16_t auto_rx_ack_timeout;						///< Timeout in microseconds to wait for receiving immediate ACK
	uint16_t auto_rx_enh_ack_timeout;					///< Timeout in microseconds to wait for receiving enhanced ACK
	ral_ack_type_enum_t ack_type;						///< ACK type
	ral_state_enum_t auto_tx_ack_state;					///< Enable/Disable automatic ACK transmission
	ral_state_enum_t auto_rx_ack_state;					///< Enable/Disable automatic ACK reception
} ral_auto_ack_confg_st;

#if SUPPORT_A_MAC
/**
 * @brief Structure represents AMAC parameters
 *
 */
typedef struct _ral_a_mac_params_st {
	ral_auto_ack_confg_st auto_ack_config;		///< ACK configurations
	uint16_t ifs;								///< Interframe spacing value
	ral_phy_rate_enum_t phy_rate;				///< PHY rate
}ral_a_mac_params_st;
#endif /*SUPPORT_A_MAC*/

/**
 * @brief Structure represents RAL event info in case of coexistence
 *
 */
typedef struct _ral_coex_info_st {
	void * evnt_hndl;				///< Pointer to RAL event handle given from the event scheduler after registration
	ble_time_t grant_end_time;		///< End time in sleep timer steps of grant given from the event scheduler
} ral_coex_info_st;

#if SUPPORT_ENH_ACK_LINK_METRICS_PROBING_OT_1_2 || CONFIG_MAC_CSL_RECEIVER_ENABLE
/**
 * @brief Structure represents MAC address
 *
 */
typedef struct mac_address_{
	uint8_t * ptr_address;				///< Pointer to the address
	mac_addrs_mode_enum_t address_mode; ///< Address mode
} mac_address_st;

#if SUPPORT_ENH_ACK_LINK_METRICS_PROBING_OT_1_2
/**
 * @brief Structure represents RAL Copy of radio otLinkMetrics structure
 *
 */
typedef struct link_metrics_info_
{
    uint8_t mPduCount 	: 1;   ///< Pdu count.
    uint8_t mLqi 	  	: 1;   ///< Link Quality Indicator.
    uint8_t mLinkMargin : 1;   ///< Link Margin.
    uint8_t mRssi 		: 1;   ///< Received Signal Strength Indicator.
    uint8_t mReserved 	: 1;   ///< Reserved, this is for reference device.
} link_metrics_info_st;

typedef struct  link_metric_data_info_st_* p_link_metric_data_info_st;	///< Pointer to link metrics initiator node
/**
 * @brief Structure represents link metrics initiator node
 *
 */
typedef struct link_metric_data_info_st_{

	p_link_metric_data_info_st ptr_nxt_node;			///< Pointer to the next initiator node
	/**
	 * @brief Structure represents initiator address
	 *
	 */
	struct{
		uint8_t extended_address[EXT_ADDRESS_LENGTH];	///< The extended address of the initiator node
		uint16_t short_address;							///< The short address of the initiator node
	} initiator_address_field_st;
	link_metrics_info_st initiator_link_metrics;		///< Link metrics info

} link_metric_data_info_st;
#endif // SUPPORT_ENH_ACK_LINK_METRICS_PROBING_OT_1_2
#endif // SUPPORT_ENH_ACK_LINK_METRICS_PROBING_OT_1_2 || CONFIG_MAC_CSL_RECEIVER_ENABLE

/* Callback API */
/**
 * @brief Structure represents RAL callback functions which should be called after TX/RX/ED is done
 *
 */
typedef struct _ral_cbk_dispatch_tbl_st {
	/** RAL TX done callback */
	void (*ral_tx_done)(ral_instance_t ral_instance, ral_pkt_st * ptr_tx_pkt, ral_pkt_st * ptr_ack_pkt, ral_error_enum_t tx_error);
	/** RAL RX done callback */
	void (*ral_rx_done)(ral_instance_t ral_instance, ral_pkt_st * ptr_rx_pkt, ral_error_enum_t rx_error);
	/** RAL ED done callback */
	void (*ral_ed_scan_done)(ral_instance_t ral_instance, uint32_t scan_durn, int8_t max_rssi);
#if (!SUPPORT_COEXISTENCE)
	/** RAL resume RX after timer error callback */
	void (*ral_resume_rx_after_tmr_err)(void);
#endif /*end of (!SUPPORT_COEXISTENCE)*/
#if SUPPORT_A_MAC
	/** This callback will be called when device receives packet that requires custom ack */
	void (*ral_configure_custom_ack)(ral_instance_t ral_instance,  uint8_t *ptr_ack_pkt, uint16_t*ack_len,uint8_t * ptr_rx_pkt);
#endif /*end of SUPPORT_A_MAC*/
} ral_cbk_dispatch_tbl_st;
/* Definition for hardware control flags */
//--------------------------------------------
/*
 * Tx PHY Rate:
 * 0:125k
 * 1:250k
 * 2:1M
 * 3:2M
 *
 * */
#define DEFAULT_PHY_RATE					1		///< Default PHY rate (256K)
/* :
 * */
#define DEFAULT_PHY_TX_LOWLTNCY				0		///< Default PHY TX low latency
/* :
 * */
#define DEFAULT_PHY_RX_LOWLTNCY				0		///< Default PHY RX low latency
/**
 * Bypass CRC check [used for testing purpose]
 * 1'b1 : Bypassing CRC check on the received packet.
 * 1'b0 : perform CRC check on the received packet.
 * */
#define DEFAULT_TXPP_BYPASS_CRC				0
/* :
 * */
#define DEFAULT_SCAN_BCN					0		///< Default scan beacon
/**
 * Packet processor configuration
 * 1'b1 : RX PP will discard packet when mac_prmsicsmode is FALSE and generate error flags
 * 1'b0 : RX PP will not discard packet when mac_prmiscsmode is FALSE and will only generate error flags
 * */
#define DEFAULT_DROP_ON_ERR					1
/**
 * PAN Coordinator identifier (used in third-level filtering when only source PAN ID is present in the received packet):
 * 1'b1 - The device is PAN coordinator
 * 1'b0 - The device is not PAN coordinator
 *
 * */
#define DEFAULT_PANCOORD					0
/**
 * Indicates whether frames without a destination PAN ID and a destination address are to treated
 * as though they are addressed to the broadcast PAN ID and broadcast short address.
 *
 * */
#define DEFAULT_MACIMPLICITBROADCAST		0
/* :
 * */
#define DEFAULT_MACGRPRXMODE				0		///< Default MAC group RX mode
/**
 * MAC Promiscuous Mode - Indication of whether the MAC sublayer is in a promiscuous (receive all) mode.
 * A value of TRUE indicates that the MAC sublayer accepts all frames received from the PHY.
 * Shall be used for reception second-level filtering requirements
 * */
#define DEFAULT_MAC_PRMISCMOD				0
//--------------------------------------------
/**
 * @brief Enum defines bit shift amount for control flags used to configure HW
 *
 */
enum control_flags_shift {
	PHY_RATE_SHIFT,
	PHY_TX_LOWLTNCY_SHIFT=2,
	PHY_RX_LOWLTNCY_SHIFT,
	TXPP_BYPASS_CRC_SHIFT,
	SCAN_BCN_SHIFT,
	DROP_ON_ERR_SHIFT,
	PANCOORD_SHIFT,
	MACIMPLICITBROADCAST_SHIFT,
	MACGRPRXMODE_SHIFT,
	MAC_PRMISCMOD_SHIFT,
	VDDH_PA_SHIFT,
	EPA_DISABLE_SHIFT = 15
};

/**
 * @brief Enum defines bit shift amount for errors returned after event completion
 *
 */
enum error_flags_shift{
	TIMEOUT_FLAG_SHIFT = 2,  /* bit location for timeout flag reception error */
	ADDMODE_ERR_SHIFT,		 /* bit location for Address Mode reception error. asserted when either of the following is asserted (dstaddr_err,srcpanid_err,dstpanid_err)*/
	RX_ERR_SHIFT,			 /* bit location for rx operation error. asserted when either rx_err or ppdu_err is asserted */
	PPDU_ERR_SHIFT,			 /* bit location for PPDU reception error. asserted when any of the following is asserted
								(ack_err, crc_err,dstaddr_err,srcpanid_err,dstpanid_err,frmvrsn_err,frmtype_err,frmlngth_err)*/
	FRMLNGTH_ERR_SHIFT,		 /* bit location for Frame Length reception error. Asserted when received frame length is one of the reserved values mac_prmiscmode=0 and
	 	 	 	 	 	 	 	decoded MAC header indicates MAC frame longer than received frame length*/
	FRMTYPE_ERR_SHIFT,		 /* bit location for Frame type reception error asserted when received frame type is one of the reserved values.
								Available only when mac_prmiscmode=0 */
	FRMVRSN_ERR_SHIFT,		 /* bit location for Frame version reception error asserted when received frame version is neither 2'b00 not 2'b01.
								Available only when mac_prmiscmode=0 */
	DSTPANID_ERR_SHIFT,		 /* bit location for Destination PAN ID reception error. Available only when mac_prmiscmode=0 */
	SRCPANID_ERR_SHIFT,		 /* bit location for Source PAN ID reception error. Available only when mac_prmiscmode=0 */
	ACK_OK_SHIFT,			 /* bit location for Acknowledgment received correctly flag */
	ACK_ERR_SHIFT,			 /* bit location for Acknowledgment received with errors flag */
	CRC_ERR_SHIFT,			 /* bit location for CRC error indicator flag*/
	DSTADDR_ERR_SHIFT,		 /* bit location for Destination Address reception error. Available only when mac_prmiscmode=0 */
	SEC_ERR_SHIFT = 30		 /* bit location for security processing error occurred in case of secured Enhanced Ack  */
};


/** Start of frame delimiter length as defined in OQPSK phy in MAC 802.15.4 std */
#define DEFAULT_MAC_SFD_LENGTH 			1
/** Preample length as defined in OQPSK phy in MAC 802.15.4 std */
#define DEFAULT_MAC_PREAMBLE_LENGTH 	4
/** Start of frame delimiter value as defined in OQPSK phy in MAC 802.15.4 std */
#define DEFAULT_MAC_SFD_VALUE			0xA7
/** Preample value as defined in OQPSK phy in MAC 802.15.4 std */
#define DEFAULT_MAC_PEAMBLE_VALUE		0x0

#if(SUPPORT_A_MAC)
/* 1M preamble and SFD used only in A_MAC */
/** Custom start of frame delimiter length used in 1M phy_rate */
#define DEFAULT_A_MAC_SFD_LENGTH_1M 		4
/** Custom preample length used in 1M phy rate */
#define DEFAULT_A_MAC_PREAMBLE_LENGTH_1M 	1
/** Custom start of frame delimiter value used in 1M phy_rate */
#define DEFAULT_A_MAC_SFD_VALUE_1M			0x71764129
/** Custom preample value used in 1M phy rate */
#define DEFAULT_A_MAC_PEAMBLE_VALUE_1M		0xAA

/* 2M preamble and SFD used only in A_MAC */
/** Custom start of frame delimiter length used in 2M phy_rate */
#define DEFAULT_A_MAC_SFD_LENGTH_2M 		4
/** Custom preample length used in 2M phy rate */
#define DEFAULT_A_MAC_PREAMBLE_LENGTH_2M 	2
/** Custom start of frame delimiter value used in 2M phy_rate */
#define DEFAULT_A_MAC_SFD_VALUE_2M			0x71764129
/** Custom preample value used in 2M phy rate */
#define DEFAULT_A_MAC_PEAMBLE_VALUE_2M		0xAAAA
#endif

/* Bitfield sizes defined for MAC descriptor */
#define MAC_SFD_VALUE_SIZE 				32		///< The size in bits of SFD value parameter of the event descriptor
#define MAC_PREAMBLE_VAL_SIZE			32		///< The size in bits of preamble value parameter of the event descriptor
#define	MAC_PANID_SIZE					16		///< The size in bits of PAN ID parameter of the event descriptor
#define MAC_SHORTADDR_SIZE				16		///< The size in bits of short address parameter of the event descriptor
#define EUI64ADD_LSW_SIZE				32		///< The size in bits of LSW of EUI64 address parameter of the event descriptor
#define EUI64ADD_MSW_SIZE				32		///< The size in bits of MSW of EUI64 address parameter of the event descriptor
#define MAC_EXTADDR_LSW_SIZE			32		///< The size in bits of LSW of extended address parameter of the event descriptor
#define MAC_EXTADDR_MSW_SIZE			32		///< The size in bits of MSW of extended address parameter of the event descriptor
#define ERROR_FLAGS_SIZE				15		///< The size in bits of error flags parameter of the event descriptor
#define RX_FRAME_LEN_SIZE				7		///< The size in bits of RX frame length parameter of the event descriptor
#define DEBUG_PORTS_SIZE				5		///< The size in bits of debug ports parameter of the event descriptor
#define POINTER_TO_CURRENT_TX_SIZE		16		///< The size in bits of current TX pointer parameter of the event descriptor
#define POINTER_TO_CURRENT_RX_SIZE		16		///< The size in bits of current RX pointer parameter of the event descriptor
#define FRMLNGTH_SIZE					7		///< The size in bits of frame length parameter of the event descriptor
#define MAC_SFD_LEN_SIZE				3		///< The size in bits of SFD length parameter of the event descriptor
#define MAC_PREAMBLE_LEN_SIZE			3		///< The size in bits of preamble length parameter of the event descriptor
#define SEQNUM_SIZE						8		///< The size in bits of sequence number parameter of the event descriptor
#define TX_MAC_LATENCY_SIZE				6		///< The size in bits of TX latency parameter of the event descriptor
#define CONTROL_FLAGS_SIZE				16		///< The size in bits of control flags parameter of the event descriptor
#define PHY_DRV_SEQ_STRT_ADDR_SIZE		7		///< The size in bits of start address of the sequencer ram parameter of the event descriptor
#define PHY_DRV_SEQ_END_ADDR_SIZE		7		///< The size in bits of end address of the sequencer ram parameter of the event descriptor
#define PHY_DRV_RSSI_VALUE_SIZE		    16		///< The size in bits of RSSI parameter of the event descriptor
#define PHY_DRV_LQI_VALUE_SIZE		    8		///< The size in bits of LQI parameter of the event descriptor
/**
 * @brief Structure contains HW event descriptor fields that:
 * 		  1- Required to be filled before start of the event
 * 		  2- Need to be checked after the end of the event.
 *
 */
typedef struct llhwc_mac_evnt_info_mem_st {
	uint32_t mac_sfd_value			:MAC_SFD_VALUE_SIZE; 		///< Start of frame delimiter value used by serializer and deserializer
	uint32_t mac_preamble_val		:MAC_PREAMBLE_VAL_SIZE;		///< Preamble value used by serializer
	uint32_t mac_panid				:MAC_PANID_SIZE;			///< The identifier of the PAN on which the device is operating.used for third-level filtering
	uint32_t mac_shortaddr			:MAC_SHORTADDR_SIZE;		///< The address that the device uses to communicate in the PAN.used for fourth-level filtering
	uint32_t eui64add_LSW			:EUI64ADD_LSW_SIZE;			///< Least significant word for EUI Extended address defined in 2015
	uint32_t eui64add_MSW			:EUI64ADD_MSW_SIZE;			///< Most significant word for EUI Extended address defined in 2015
	uint32_t mac_extaddr_LSW		:MAC_EXTADDR_LSW_SIZE;		///< Least significant word for device Extended address
	uint32_t mac_extaddr_MSW		:MAC_EXTADDR_MSW_SIZE;		///< Most significant word for device Extended address
	uint32_t error_flags			:ERROR_FLAGS_SIZE;			///< Error flags set by hardware to indicate filteration errors
	uint32_t 						:1;
	uint32_t rx_frm_len				:RX_FRAME_LEN_SIZE;			///< Length of the received frame
	uint32_t debug_ports			:DEBUG_PORTS_SIZE;			///< Debugging ports defined for ST
	uint32_t 						:4;
	uint32_t rssi_out				:PHY_DRV_RSSI_VALUE_SIZE;	///< RSSI of the received frame
	uint32_t LQI				    :PHY_DRV_LQI_VALUE_SIZE;	///< LQI of the received frame
	uint32_t   				        :8;
	uint32_t frmlngth				:FRMLNGTH_SIZE;				///< Length of the transmitted MAC frame
	uint32_t						:1;
	uint32_t mac_sfd_len			:MAC_SFD_LEN_SIZE;			///< SFD length: 1 octet
	uint32_t mac_preamble_len		:MAC_PREAMBLE_LEN_SIZE;		///< Preamble length: 4 octets
	uint32_t						:2;
	uint32_t seqnum					:SEQNUM_SIZE;				///< Sequence number compared against sequence number extracted from mac header of a received ACK frame
	uint32_t tx_latency				:TX_MAC_LATENCY_SIZE;		///< This field sets the required time for the TX path to flush the last bit on the air
	uint32_t						:2;
	uint32_t control_flags			:CONTROL_FLAGS_SIZE;		///< Flags used to Enable/Disable features in HW
	uint32_t phy_drv_seq_strt_addr	:PHY_DRV_SEQ_STRT_ADDR_SIZE;///< Pointer to start address for sequencer ram
	uint32_t						:1;
	uint32_t phy_drv_seq_end_addr	:PHY_DRV_SEQ_END_ADDR_SIZE;	///< Pointer to end address for sequencer ram
	uint32_t						:1;
	uint32_t Pointer_To_current_TX	:POINTER_TO_CURRENT_TX_SIZE;///< Pointer to the packet in shared memory to be transmitted
	uint32_t Pointer_To_current_RX	:POINTER_TO_CURRENT_RX_SIZE;///< Pointer to shared memory place at which the packet will be received

}llhwc_mac_evnt_info_mem_t;
#if SUPPORT_RADIO_SECURITY_OT_1_2
/**
 * @brief Structure represents updated security parameters
 *
 */
typedef struct sec_update_desc_st_{
	uint8_t * ptr_key;		///< Pointer to the security key
	uint32_t frm_cntr;		///< Frame counter
	uint32_t hdr_len;		///< Header length
	uint8_t  mic_len;		///< MIC length
	uint8_t sec_lvl;		///< Security level
} sec_update_desc_st;
#endif

extern llhwc_mac_evnt_info_mem_t* g_mac_event_info;		///< MAC event descriptor shared between HW and FW

/**  @ingroup ral_intf_cmn
*  @{
*/
/* Generic APIs  ----------------------------------------------------------------------------------- */
/**
 * @brief	RAL initialization
 *
 * @param[in] ptr_cbk_dispatch_tbl : Pointer to callbacks dispatch table
 *
 * @retval RAL instance associated to this context that should be used with any RAL interface
 */
ral_instance_t ral_init(ral_cbk_dispatch_tbl_st * ptr_cbk_dispatch_tbl);
/**
 * @brief	RAL reset
 *
 * @param[in] ral_instance : RAL instance
 */
void ral_reset(ral_instance_t ral_instance);

/**
 * @brief	Switch power either sleep or active
 *
 * @param[in] ral_instance  : RAL instance
 * @param[in] power_state   : New power state
 * @param[in] ptr_coex_info : Pointer to the current coexistence parameters
 *
 * @retval RAL_ERROR_NONE if power state changed successfully
 */
ral_error_enum_t ral_power_switch(ral_instance_t ral_instance,
		ral_power_state_enum_t power_state, ral_coex_info_st * ptr_coex_info);

/**
 * @brief	Get current power state
 *
 * @param[in] ral_instance : RAL instance
 *
 * @retval Current power state: RAL_POWER_SLEEP or RAL_POWER_ACTIVE
 */
ral_power_state_enum_t ral_get_power_state(ral_instance_t ral_instance);

/**
 * @brief	Get current event state and current channel if not idle
 *
 * @param[out] curr_ral_instance : Current RAL instance if not idle
 * @param[out] curr_event_channel : Current event channel if not idle
 *
 * @retval Current event state: RX, TX, ED, or IDLE
 */
ral_event_state_enum_t ral_get_current_event_state(ral_instance_t * curr_ral_instance, uint8_t * curr_event_channel);

#if SUPPORT_ANT_DIV
/**
 * @brief	Set antenna diversity feature parameters
 *
 * @param[in] ral_instance       : RAL instance
 * @param[in] ptr_ant_div_params : Pointer to antenna diversity parameters
 *
 * @retval RAL_ERROR_NONE if antenna diversity parameters are set correctly
 */
ral_error_enum_t ral_set_ant_div_params(ral_instance_t ral_instance, antenna_diversity_st* ptr_ant_div_params);

/**
 * @brief	Get current antenna diversity feature parameters
 *
 * @param[in] ral_instance       	: RAL instance
 * @param[out] ptr_ant_div_params 	: Pointer to current antenna diversity parameters
 */
void ral_get_ant_div_params(ral_instance_t ral_instance, antenna_diversity_st* ptr_ant_div_params);

/**
 * @brief	Enable/disable antenna diversity feature
 *
 * @param[in] ral_instance   : RAL instance
 * @param[in] enable         : Enable:1 / disable:0
 *
 * @retval RAL_ERROR_NONE if antenna diversity is enabled/disabled correctly
 */
ral_error_enum_t ral_set_ant_div_enable(ral_instance_t ral_instance, uint8_t enable);

/**
 * @brief	Set the default antenna id to be used for transmission and reception
 *
 * @param[in] ral_instance    : RAL instance
 * @param[in] default_ant_id  : The antenna id to be used as default
 *
 * @retval RAL_ERROR_NONE if default antenna ID is set correctly
 */
ral_error_enum_t ral_set_default_ant_id(ral_instance_t ral_instance, uint8_t default_ant_id);

/**
 * @brief	Set RSSI threshold for antenna diversity feature
 *
 * @param[in] ral_instance     : RAL instance
 * @param[in] rssi_threshold   : RSSI threshold to compare with during antenna diversity measurements
 *
 * @retval RAL_ERROR_NONE if antenna diversity RSSI threshold is set correctly
 */
ral_error_enum_t ral_set_ant_div_rssi_threshold(ral_instance_t ral_instance, int8_t rssi_threshold);
#endif /* SUPPORT_ANT_DIV */

/**
 * @}
 */
#if((!SUPPORT_COEXISTENCE && DEFAULT_PHY_CALIBRATION_PERIOD))
/**
 * @brief	Execute PHY periodic calibration
 *
 */
void ral_exec_phy_prdc_clbr(void);
#endif
/**  @ingroup ral_intf_cmn
*  @{
*/
#if SUPPORT_MAC
#if SUPPORT_A_MAC
/**
 * @brief	Set PHY rate for transmission/reception
 *
 * @param[in] ral_instance : RAL instance
 * @param[in] phy_rate : New PHY rate [1M/2M/256K/125K]
 *
 * @retval RAL_ERROR_NONE if phy rate changed successfully
 */
ral_error_enum_t ral_set_rate(ral_instance_t ral_instance, ral_phy_rate_enum_t phy_rate);
/**
 * @brief	Set minimum interframe spacing between successive transmission/reception
 *
 * @param[in] ral_instance 	: RAL instance
 * @param[in] min_ifs 		: New minimum interframe spacing in microseconds
 */
void ral_set_min_ifs(ral_instance_t ral_instance, uint16_t min_ifs);
#endif

#if SUPPORT_A_MAC
/**
 * @brief	Set interframe spacing between successive transmission/reception
 *
 * @param[in] ral_instance 	: RAL instance
 * @param[in] ifs 			: New interframe spacing in microseconds
 *
 * @retval RAL_ERROR_NONE if interframe spacing changed successfully
 */
ral_error_enum_t ral_set_ifs(ral_instance_t ral_instance, uint16_t ifs);
#else
#if SUPPORT_ZIGBEE_PHY_CERTIFICATION
/**
 * @brief	Set interframe spacing between successive transmission/reception
 *
 * @param[in] ral_instance 	: RAL instance
 * @param[in] ifs 			: New interframe spacing in microseconds
 *
 * @retval RAL_ERROR_NONE if interframe spacing changed successfully
 */
ral_error_enum_t ral_set_ifs(ral_instance_t ral_instance, uint16_t ifs);
#endif /* SUPPORT_ZIGBEE_PHY_CERTIFICATION */
#endif
#endif
/**
 * @}
 */
/**  @ingroup ral_intf_tx
*  @{
*/
/* Transmission APIs ----------------------------------------------------------------------------------- */
/**
 * @brief	Start packet transmission
 * 			This function is responsible for preparation for transmission of a packet by allocating and preparing a new ral event/ral pkt to be executed by HW.
 * 			After completion of the Transmission event or if stop operation ral_tx_done() will be called carrying the status of event.
 *
 * @param[in] ral_instance 	  	: RAL instance
 * @param[in] pkt_src 	 	  	: Transmission packet source, FIFO based or Packet based
 * @param[in] ptr_pkt 	 	  	: Pointer to the transmitted packet if packet source is Packet based only
 * @param[in] ptr_start_time 	: Pointer to the start time structure which contains start time of transmission (SFD of packet)
 * 								  if NULL function will use the current time get from llhwc_slptmr_get
 * @param[in] periodic_interval : Periodic interval in microseconds, 0 means not periodic
 * @param[in] ptr_coex_info 	: Pointer to the current coexistence parameters
 *
 * @retval RAL_ERROR_NONE if transmission started successfully
 * 		   RAL_ERROR_INVALID_PARAMETERS if the passed parameters doesn't make sense e.g. starting fifo mode but ptr_fifo_head = NULL
 * 		   RAL_ERROR_BUSY if there is a transmission event that already started and not ended yet
 *
 * @note: ral_tx_done won't be called unless emngr_handle_all_events() is called to call ral_sm_done which will call the ral_tx_done call back
 *
 */
ral_error_enum_t ral_start_tx(ral_instance_t ral_instance, ral_pkt_src_enum_t pkt_src, ral_pkt_st * ptr_pkt,
		ral_time_st * ptr_start_time, uint32_t periodic_interval, ral_coex_info_st * ptr_coex_info);

/**
 * @brief	abort current transmission
 * 			This function is used for testing purpose
 *
 * @param[in] ral_instance : RAL instance
 *
 * @retval RAL_ERROR_NONE if transmission aborted successfully
 */
ral_error_enum_t ral_abort_tx(ral_instance_t ral_instance);

#if SUPPORT_A_MAC
/**
 * @brief	Add packet to transmission FIFO
 *
 * @param[in] ral_instance 	: RAL instance
 * @param[in] ptr_pkt 	 	: Pointer to input packet allocated by user application
 *
 * @retval RAL_ERROR_NONE if packet added to FIFO successfully
 */
ral_error_enum_t ral_add_tx_fifo(ral_instance_t ral_instance, ral_pkt_st * ptr_pkt);

/**
 * @brief	Flush current transmission FIFO
 *
 * @param[in] ral_instance : RAL instance
 *
 * @retval RAL_ERROR_NONE if FIFO flushed successfully
 */
ral_error_enum_t ral_flush_fifo(ral_instance_t ral_instance);
#endif

/**
 * @brief	Get transmission packet to prepare data before starting transmission.
 * 			It must be used in case of packet transmission mode, the packet is allocated from TX/RX shared memory.
 *
 * @param   ral_instance : RAL instance
 *
 * @retval Pointer to allocated RAL packet
 */
ral_pkt_st * ral_get_tx_buf(ral_instance_t ral_instance);
/**
 * @}
 */
/**  @ingroup ral_intf_ed
*  @{
*/
/**
 * @brief	Perform Clear Channel Assessment on selected channel
 *
 * @param[in] channel 			: Channel to perform CCA on.
 * @param[in] ptr_coex_info 	: Pointer to the current coexistence parameters
 * @param[in] energyThreshold 	: The minimum value of RSSI to mark the channel busy,
 *          					  It is used only in case of phy 2.00a_tc. defined by cca_change_threshold_seq for other PHYs.
 * @param[in] ral_instance		: RAL instance
 * @retval RAL_ERROR_NONE if no traffic on air, RAL_ERROR_CCA_FAILURE otherwise
 */
ral_error_enum_t ral_perform_cca(uint8_t channel, ral_coex_info_st * ptr_coex_info, int8_t energyThreshold
	, ral_instance_t ral_instance
);
/**
 * @}
 */
/**  @ingroup ral_intf_rx
*  @{
*/
/* Reception APIs  ----------------------------------------------------------------------------------- */
/**
 * @brief	Start packet reception
 * 			This function is responsible for preparation for reception of a packet by allocating and preparing a new RAL event/ral pkt to be executed by HW.
 * 			After completion of the Reception event or if stop operation, ral_rx_done() will be called carrying the status of event and the packet received.
 *
 *
 * @param[in] ral_instance 		: RAL instance
 * @param[in] rx_channel 		: Channel to receive on
 * @param[in] ptr_start_time 	: Pointer to the start time structure which contains start time of reception
 * @param[in] timeout 			: Timeout of reception in microsecond from the start of reception
 * @param[in] periodic_interval : Periodic interval in microsecond, 0 means not periodic
 * @param[in] ptr_coex_info 	: Pointer to the current coexistence parameters
 *
 * @retval RAL_ERROR_NONE if reception started successfully
 *  	   RAL_ERROR_INVALID_PARAMETERS if the passed parameters doesn't make sense e.g. if the reception channel out of MAC band
 * 		   RAL_ERROR_BUSY if there is a transmission event that already started and not ended yet
 *
 * @note: ral_rx_done won't be called unless emngr_handle_all_events() is called to call ral_sm_done which will call the ral_rx_done call back
 */
ral_error_enum_t ral_start_rx(ral_instance_t ral_instance, uint8_t rx_channel, ral_time_st * ptr_start_time,
								uint32_t timeout, uint32_t periodic_interval, ral_coex_info_st * ptr_coex_info);

/**
 * @brief	Abort current reception
 * 			This function is used for tseting purpose
 *
 * @param[in] ral_instance : RAL instance
 *
 * @retval RAL_ERROR_NONE if reception aborted successfully
 */
ral_error_enum_t ral_abort_rx(ral_instance_t ral_instance);
/**
 * @}
 */
/**  @ingroup ral_intf_cmn
*  @{
*/
/**
 * @brief	Set automatic continuous reception after each event state
 *
 * @param[in] ral_instance 		: RAL instance
 * @param[in] cont_recp_state 	: Continuous reception state, Enable or Disable
 *
 * @retval RAL_ERROR_NONE if new state saved successfully
 */
ral_error_enum_t ral_set_cont_recp_state(ral_instance_t ral_instance, ral_state_enum_t cont_recp_state);

/**
 * @brief	Enable/Disable automatic switching to sleep mode after finish each event.
 * 			Set automatic sleep after each event state in case of continuous reception is disabled
 * 			as if enabled RAL shall schedule reception event from ral_isr() using active timer.
 *
 * @param[in] ral_instance 	 	: RAL instance
 * @param[in] auto_sleep_state 	: Automatic sleep state, Enable or Disable
 *
 * @retval RAL_ERROR_NONE if new state saved successfully
 */
ral_error_enum_t ral_set_auto_sleep_state(ral_instance_t ral_instance, ral_state_enum_t auto_sleep_state);
/**
 * @brief	Get the state of automatic switching to sleep mode
 *
 * @param[in] ral_instance : RAL instance
 *
 * @retval Automatic sleep state, enabled or disabled
 */
ral_state_enum_t ral_get_auto_sleep_state(ral_instance_t ral_instance);
/**
 * @brief	Configure MAC filter in RTL while reception.
 * 			when filter is disabled means reception in promiscuous mode.
 *
 * @param[in] ral_instance 	   		: RAL instance
 * @param[in] ptr_mac_fltr_confg 	: Pointer to MAC filter configuration
 *
 * @retval RAL_ERROR_NONE if new configuration saved successfully
 */
ral_error_enum_t ral_confg_mac_fltr(ral_instance_t ral_instance, ral_mac_fltr_confg_st * ptr_mac_fltr_confg);
/**
 * @brief	Configure MAC filter in scan mode
 *
 * @param[in] ral_instance : RAL instance
 * @param[in] Enable 	   : Set or clear scan mode
 *
 * @retval RAL_ERROR_NONE if new configuration saved successfully
 */
ral_error_enum_t ral_set_scan_filter(ral_instance_t ral_instance, uint8_t Enable);

/* Auto Acknowledge APIs ----------------------------------------------------------------------------------- */
/**
 * @brief	Configure automatic ACK after packet transmission/reception
 *
 * @param[in] ral_instance 	   	: RAL instance
 * @param[in] ptr_auto_ack_confg: Pointer to new automatic ACK configuration
 *
 * @retval RAL_ERROR_NONE if new configuration saved successfully
 */
ral_error_enum_t ral_confg_auto_ack(ral_instance_t ral_instance, ral_auto_ack_confg_st * ptr_auto_ack_confg);

/**
 * @brief	Temporary pause/resume automatic ACK state only after transmission/reception.
 *			This function is used for testing and custom purposes.
 *
 * @param[in] ral_instance 	  	: RAL instance
 * @param[in] auto_tx_ack_state : New state of automatic ACK transmission
 * @param[in] auto_rx_ack_state : New state of automatic ACK reception
 *
 * @retval RAL_ERROR_NONE if new configuration saved successfully
 */
ral_error_enum_t ral_pause_auto_ack(ral_instance_t ral_instance, ral_state_enum_t auto_tx_ack_state, ral_state_enum_t auto_rx_ack_state);
/**
 * @}
 */

/**
 * @brief	Set enhanced ACK header IE data
 *
 * @param[in] ral_instance	: RAL instance
 * @param[in] ptr_hdr_ie 	: Pointer to header IE data to be included in enhanced ACK
 * @param[in] hdr_ie_len 	: Header IE data length
 *
 * @retval RAL_ERROR_NONE if new configuration saved successfully
 */
ral_error_enum_t ral_set_enh_ack_hdr_ie(ral_instance_t ral_instance, uint8_t * ptr_hdr_ie, uint8_t hdr_ie_len);

/**  @ingroup ral_intf_cmn
*  @{
*/
/**
 * @brief	Enable/Disable source address match feature.
 *			If disabled, the RAL must set the "frame pending" on all ACKs to data request commands.
 * 			If enabled, the RAL uses the source address match table to determine whether to set or clear the
 * 			"frame pending" bit in an ACK to a data request command.
 *
 * @param[in] ral_instance 		: RAL instance
 * @param[in] src_match_state 	: Source address match state
 */
void ral_set_src_match_state(ral_instance_t ral_instance, ral_state_enum_t src_match_state);

/**
 * @brief	Add a short address to the source address match table
 *
 * @param[in] ral_instance  : RAL instance
 * @param[in] short_address : Short address to be added
 *
 * @retval RAL_ERROR_NONE if added successfully
 */
ral_error_enum_t ral_add_src_match_short(ral_instance_t ral_instance, const uint16_t short_address);

/**
 * @brief	Add an extended address to the source address match table
 *
 * @param[in] ral_instance : RAL instance
 * @param[in] ptr_ext_addr : Pointer to extended address to be added
 *
 * @retval RAL_ERROR_NONE if added successfully
 */
ral_error_enum_t ral_add_src_match_ext(ral_instance_t ral_instance, const uint8_t * ptr_ext_addr);

/**
 * @brief	Remove a short address from the source address match table
 *
 * @param[in] ral_instance  : RAL instance
 * @param[in] short_address : Short address to be removed
 *
 * @retval RAL_ERROR_NONE if removed successfully
 */
ral_error_enum_t ral_clr_src_match_short(ral_instance_t ral_instance, const uint16_t short_address);

/**
 * @brief	Remove an extended address from the source address match table
 *
 * @param[in] ral_instance : RAL instance
 * @param[in] ptr_ext_addr : Pointer to extended address to be removed
 *
 * @retval RAL_ERROR_NONE if removed successfully
 */
ral_error_enum_t ral_clr_src_match_ext(ral_instance_t ral_instance, const uint8_t * ptr_ext_addr);

/**
 * @brief	Remove all short addresses from the source address match table
 *
 * @param[in] ral_instance : RAL instance
 */
void ral_clr_all_src_match_short(ral_instance_t ral_instance);

/**
 * @brief	Remove all extended addresses from the source address match table
 *
 * @param[in] ral_instance : RAL instance
 */
void ral_clr_all_src_match_ext(ral_instance_t ral_instance);
/**
 * @}
 */
/* Energy Detect API  ----------------------------------------------------------------------------------- */
/**  @ingroup ral_intf_ed
*  @{
*/
/**
 * @brief	ED reset
 *
 */
void ral_reset_ed(void);
/**
 * @brief	Start energy detection scan on specific channel,
 * 			ral_ed_scan_done callback is called to notify upper layer that the energy scan is complete.
 *
 * @param[in] ral_instance 	: RAL instance
 * @param[in] scan_channel 	: The channel to perform the energy scan on
 * @param[in] scan_duration : Scan duration in microseconds
 * @param[in] ptr_coex_info : Pointer to the current coexistence parameters
 *
 * @retval RAL_ERROR_NONE if energy detection scanning started successfully
 *
 * @note: ral_ed_scan_done won't be called unless emngr_handle_all_events() is called to call ral_sm_done_cbk which will call ral_ed_scan_done
 */
ral_error_enum_t ral_ed_scan(ral_instance_t ral_instance, uint8_t scan_channel, uint32_t scan_duration,
		ral_coex_info_st * ptr_coex_info);
/**
 * @}
 */
#if SUPPORT_ZIGBEE_PHY_CERTIFICATION
/**
 * @brief Get the current LQI of the last received packet
 *
 * @param[in] last_rssi : RSSI of the last received packet
 * @return LQI value
 */
uint8_t ral_dtmGetLQIValue(int8_t last_rssi);
#endif /*SUPPORT_ZIGBEE_PHY_CERTIFICATION*/

/**
 * @brief	Check whether the RAL is about to transmit ACK or not.
 *
 * @retval TRUE if ACK is required and about to be transmitted, FALSE otherwise
 */
uint8_t ral_is_about_to_transmit_ack(void);
/**
 * @brief	Start the triggering of pre TX sequence from sequence ram as early as possible to save time in case of transmitting ACK
 *
 */
void ral_early_perpare_phy_to_tx_ack(void);
/**
 * @brief	PHY driver ISR handler in case of MAC event.
 *			It is used to restore the phy state after triggering of the pre interpacket sequence from sequence ram.
 *
 */
void ral_handle_phy_driver_isr(void);
#if SUPPORT_RADIO_SECURITY_OT_1_2
/**
 * @brief  Update frame counter sustained in RAL instance.
 * 		   This function is called only in case of radio support OT_RADIO_CAPS_TRANSMIT_SEC.
 *
 * @param[in] instance    	: RAL instance
 * @param[in] mac_frm_cntr	: Frame counter passed by upper layers
 */
void ral_update_mac_frm_cntr(ral_instance_t instance, uint32_t mac_frm_cntr);
/**
 * @brief  Update frame counter sustained in RAL instance only if the new value larger than the old one.
 * 		   This function is called only in case of radio support OT_RADIO_CAPS_TRANSMIT_SEC.
 *
 * @param[in] instance    	: RAL instance
 * @param[in] mac_frm_cntr	: Frame counter passed by upper layers
 */
void ral_update_larger_mac_frm_cntr(ral_instance_t instance, uint32_t mac_frm_cntr);
/**
 * @brief  Update keys and keyId sustained in RAL instance.
 * 		   This function is called only in case of radio support OT_RADIO_CAPS_TRANSMIT_SEC.
 *
 * @param[in]  instance : RAL instance
 * @param[in]  aKeyId	: Key index is used for comparison in case of keyId mode '1'
 * 						  To select between different keys.
 * 						  ------------
 * 						  for example:
 * 						  ------------
 * 						  if keyId (key index) equivalent to the received in MHR
 * 						  Then the used key is the current key.
 *
 * 						  But if it isn't equivalent due to any connected neighbor's key index
 * 						  mismatch the key generator in upper layers shall be notified to take action
 * 						  based on the relation between the different key index
 *
 * 						  ------------
 * 						  for example:
 * 						  -----------
 * 						  if keyId (key index) less than the received in MHR. this means that the
 * 						  communicating device has already generate a new key and started to rotate keys.
 * 						  so the next key is the key that shall be used in this situation.
 *
 * 						  This kind of process synchronization beside another timing triggered events for
 * 						  new key generation and rotation allows a difference of only one between keyIds.
 *
 * 						  see thread specification under security section subsection of "Key Rotation"
 *
 * @param[in] aPrevKey	: Key used in case of keyid of received MHR less than the keyid sustained by ral_instance by one.
 * @param[in] aCurrKey	: Key used in case of keyid of received MHR equivalent to the keyid sustained by ral_instance.
 * @param[in] aNextKey	: Key used in case of keyid of received MHR greater than the keyid sustained by ral_instance by one.
 */
void ral_update_mac_keys(   ral_instance_t    instance,
							uint8_t             aKeyId,
							const uint8_t    *aPrevKey,
							const uint8_t    *aCurrKey,
							const uint8_t    *aNextKey );
/**
 * @brief  Get the current key of an instance.
 * 		   This function is called only in case of radio support OT_RADIO_CAPS_TRANSMIT_SEC.
 *
 * @param[in] ral_instance : RAL instance
 *
 * @retval Pointer to the current key
 */
const otMacKeyMaterial  * ral_get_inst_curr_key(ral_instance_t ral_instance);
/**
 * @brief  Get the previous key of an instance.
 * 		   This function is called only in case of radio support OT_RADIO_CAPS_TRANSMIT_SEC.
 *
 * @param[in] ral_instance : RAL instance
 *
 * @retval Pointer to the previous key sustained by RAL layer
 */
uint8_t * ral_get_inst_prev_key(ral_instance_t ral_instance);
/**
 * @brief  Get the frame counter of an instance.
 * 		   This function is called only in case of radio support OT_RADIO_CAPS_TRANSMIT_SEC.
 *
 * @param[in] ral_instance : RAL instance
 *
 * @retval Frame counter value sustained by RAL layer
 */
uint32_t ral_get_inst_frm_cntr(ral_instance_t ral_instance);
/**
 * @brief  Get the key index of an instance.
 * 		   This function is called only in case of radio support OT_RADIO_CAPS_TRANSMIT_SEC.
 *
 * @param[in] ral_instance : RAL instance
 *
 * @retval Key index sustained by RAL layer
 */
uint8_t ral_get_inst_keyId(ral_instance_t ral_instance);

#endif /*SUPPORT_RADIO_SECURITY_OT_1_2*/
#if SUPPORT_ENH_ACK_LINK_METRICS_PROBING_OT_1_2
/**
 * @brief  Configure [remove/add/modify] initiator device
 *
 * @param[in] short_addr    : The address info for initiator
 * @param[in] ptr_ext_addr  : Pointer to the extended address of the initiator node
 * @param[in] link_metrics  : Pointer to the initiator link metrics
 *
 * @retval Status
 * 		   RAL_ERROR_NONE						: successfully configured.
 * 		   RAL_ERROR_LINK_METRICS_INVALID_ARGS	: in case of ptr_ext_addr NULL.
 * 		   RAL_ERROR_LINK_METRICS_NOT_FOUND		: in case of remove non-existing node.
 * 		   RAL_ERROR_LINK_METRICS_NO_BUF		: in case of not enough supported nodes.
 */
ral_error_enum_t ral_config_enh_ack_probing(uint16_t short_addr, const uint8_t * ptr_ext_addr, void* link_metrics);
/**
 * @brief Set the link metrics noise floor value needed to calculate the link margin
 *
 * @param[in] noise_floor : The noise floor used by link metrics. It should be set to the platform's
 *                          noise floor (measured noise floor, receiver sensitivity or a constant).
 */
void ral_link_metrics_set_noise_floor(int8_t noise_floor);
#endif /*SUPPORT_ENH_ACK_LINK_METRICS_PROBING_OT_1_2*/
/**
 * @brief Set the value of the openthread base time.
 * 		  This value will be subtracted from all timing values sent/received to openthread.
 *
 * @param[in] time : Base time value
 */
void ral_set_ot_base_slp_time_value(uint32_t time);
/**
 * @brief Get the value of the openthread base time.
 * 		  The value may be set through @ref ral_set_ot_base_slp_time_value
 *
 * @return OT base time
 */
uint64_t ral_get_ot_base_slp_time_value(void);
/**
 * @brief  Convert the value of sleep timer to openthread time.
 * 		   If openthread is not integrated, @ref ral_ot_base_slp_time is set to zero, so no conversion will take place.
 *
 * @param[in] time 				: Sleep timer value to be converted to openthread time
 * @param[in] num_of_overflow 	: Number of overflow cycles to be added
 * @retval The converted time value
 */
uint64_t ral_cnvert_slp_tim_to_ot_tim(uint32_t time, uint16_t num_of_overflow);
/**
 * @brief  Convert the value of openthread time to sleep timer value.
 * 		   If openthread is not integrated, @ref ral_ot_base_slp_time is set to zero, so no conversion will take place.
 *
 * @param[in] time : Openthread time value to be converted to sleep timer
 * @retval The converted time value
 */
uint32_t ral_cnvert_ot_tim_to_slp_tim(uint64_t time);

#if SUPPORT_OPENTHREAD_1_2
/**
 * @brief  Convert the microsecond time to the proper value the should be set for the sleep timer to start the event
 *
 * @param[in]  curr_time 	: Current sleep timer value to be converted to openthread time
 * @param[in]  base_tim  	: Base time in microseconds to be converted
 * @param[in]  delay_time 	: Microsecond delay from the base time
 * @retval The converted sleep timer set point to be used in setting active timer
 */
uint32_t ral_cnvrt_req_time_to_set_point(uint32_t curr_time, uint32_t base_tim , uint32_t delay_time);
#if CONFIG_MAC_CSL_RECEIVER_ENABLE
/**
 * @brief	Set CSL receiver parameters to enable/disable CSL.
 *
 * @param[in] ral_instance     : RAL instance
 * @param[in] cslPeriod        : CSL period to be included in CSL header IE, or 0 to disable CSL
 * @param[in] csl_short_addr   : The short source address of CSL receiver's peer.
 * @param[in] ptr_csl_ext_addr : Pointer to the parent extended address
 */
void ral_set_csl_rcv_param(ral_instance_t ral_instance, uint32_t cslPeriod ,uint16_t csl_short_addr, uint8_t* ptr_csl_ext_addr);
/**
 * @brief	Set CSL receiver next sample time to be used in calculating phase. the sample time points to the time of he next sample window
 *
 * @param[in] ral_instance  : RAL instance
 * @param[in] cslSampleTime	: The LSB part of sample time in us
 */
void ral_set_csl_sample_time(ral_instance_t ral_instance, uint32_t cslSampleTime);
/**
 * @brief Check whether the RAL is receiving within the CSL sample window
 *
 * @return TRUE 1 if the receiver is in CSL window, FALSE otherwise.
 */
uint8_t ral_is_rcv_in_csl_smple_wndw(void);
/**
 * @brief	Check and add CSL header IE to any outgoing frame if CSL receiver is enabled.
 * 			For any outgoing frames except the enhanced ACK frame, it assumes that the CSL header IE is stubbed in frame.
 *
 * @param[in] ral_instance : RAL instance
 * @param[in] frame_ptr    : Pointer the frame to be transmitted, either enhanced ACK or any other frame.
 * @param[in,out] ie_index : Index of the first byte of CSL header IE. if the CSL header IE will be included , It will be incremented with the length of CSL header IE
 * @param[in] data_ptr     : Data pointer to the parent address in case of enhanced ACK, and frame total length for TX frames
 * @param[in] enh_ack_flag : Flag to indicate whether enhanced ACK or new TX Frame
 */
void ral_hndl_csl_hdr_ie(ral_instance_t ral_instance, uint8_t *frame_ptr,uint8_t *ie_index, uint8_t * data_ptr , uint8_t enh_ack_flag);
#endif /*CONFIG_MAC_CSL_RECEIVER_ENABLE*/
#endif /* SUPPORT_OPENTHREAD_1_2 */
/**
 * @brief	Set the CCA Energy Detection threshold in PHY
 *
 * @param[in] threshold : CCA Energy Detection threshold value to be set
 * @retval OT_ERROR_NONE if the the threshold is successfully set, OT_ERROR_FAILED if the given value is out of range.
 */
otError ral_set_cca_ed_threshold(int8_t threshold);
/**
 * @brief	Get the CCA Energy Detection threshold in PHY
 *
 * @retval CCA Energy Detection threshold value
 */
int8_t ral_get_cca_ed_threshold(void);
#if (SUPPORT_COEXISTENCE)
/**
 * @brief	Radio CSMA error callback.
 *
 * @param[in] error : Status error returned from this transmission
 */
void radio_coex_tx_error_cbk(uint32_t error);
#endif /*end of (SUPPORT_COEXISTENCE)*/
#if (RADIO_CSMA) &&(!SUPPORT_COEXISTENCE)
/**
 * @brief	Set maximum time to start CSMA
 *
 * @param[in] rx_timeout     : RX timeout time in sleep timer steps when there's RX while waiting CSMA backoff delay to fire
 * @param[in] max_csma_delay : Max start time to start CSMA in sleep timer steps
 */
void ral_set_csma_time(
#if ENHANCED_RX_WHILE_CSMA_BACKOFF_DELAY
		ble_time_t rx_timeout,
#endif /*end of ENHANCED_RX_WHILE_CSMA_BACKOFF_DELAY*/
					ble_time_t max_csma_delay);
#endif /*end of (RADIO_CSMA) &&(!SUPPORT_COEXISTENCE)*/
/**
 * @brief	Handle frame pending bit in ACK of all packets (set to true) or for ACK of data request command only (set to false)
 *
 * @param[in] hndle_frm_pending_bit_for_acks : TRUE means handle pending frame bit in ACK for all frame types, FALSE means handle frame pending bit in ACK for data request command only
 */
void ral_set_frm_pend_bit_for_acks(uint8_t hndle_frm_pending_bit_for_acks);

#if RADIO_CSMA
/**
 * @brief   Set CSMA enable flag
 *
 * @param[in] csma_en : Value for CSMA enable flag to be set
 */
void radio_set_csma_en(uint8_t csma_en);
/**
 * @brief	Get CSMA enable flag
 *
 * @retval CSMA enable flag
 */
uint8_t radio_get_csma_en(void);
#endif /*end of RADIO_CSMA*/
/**
 * @brief   Set CCA enable flag
 *
 * @param[in] cca_en : Value for CCA enable flag to be set
 */
void radio_set_cca_en(uint8_t cca_en);
/**
 * @brief   Get CCA enable flag
 *
 * @retval CCA enable flag .
 */
uint8_t radio_get_cca_en(void);
/**
 * @brief   Set pending TX retry flags
 *
 * @param[in] evnt_type     : Type of new retry (CONTINUE_CSMA_RETRY, START_NEW_FULL_TX_RETRY)
 * @param[in] radio_error	: Error returned from previous TX trial
 * @param[in] is_tx_blocked	: Flag to indicate that TX event is blocked
 */
void radio_set_tx_retry_pending(tx_new_retry_enum_t evnt_type, otError radio_error, uint8_t is_tx_blocked);
/**
 * @brief   Handle pending TX retry event
 *
 */
void radio_handle_pnding_tx_retry_event(void);
/**
 * @brief   Check if there's pending TX retry waiting to be executed
 *
 * @retval TRUE if there is a pending TX retry, FALSE otherwise.
 */
uint8_t radio_is_tx_retry_event_pending(void);
/**
 * @brief   Set MAC implicit broadcast PIB from MAC layer to be used in filtration
 *
 * @param[in] ImplicitBroadcast: Value for MAC implicit broadcast PIB to be set
 */
void radio_set_implicitbroadcast(uint8_t ImplicitBroadcast);
/**
 * @brief   Set MAC implicit broadcast PIB from radio layer to be used in filtration
 *
 * @param[in] ral_instance		: RAL instance
 * @param[in] ImplicitBroadcast	: Value for MAC implicit broadcast PIB to be set
 */
void ral_set_implicitbroadcast(ral_instance_t ral_instance, uint8_t ImplicitBroadcast);
/**
 * @brief	Energy detection timer event handle
 *
 * @param[in] ptr_info : Pointer to current RAL context
 */
void ed_timer_hndl(void* ptr_info);
#if SUPPORT_CONFIG_LIB
/**
 * @brief	Set configurable library parameters
 *
 * @param[in] ptr_config_lib_params : Pointer to configurable library parameters
 *
 * @retval RAL_ERROR_NONE if configurable library parameters are set correctly
 */
ral_error_enum_t ral_set_config_lib_params(config_lib_st* ptr_config_lib_params);
/**
 * @brief	Get configurable library parameters
 *
 * @param[out] ptr_config_lib_params : Pointer to configurable library parameters
 */
void ral_get_config_lib_params(config_lib_st* ptr_config_lib_params);
/**
 * @brief	Set RTL polling time
 *
 * @param[in] rtl_polling_time : RTL polling time
 */
void ral_set_rtl_polling_time(uint8_t rtl_polling_time);

/**
 * @brief	Get current RTL polling time
 *
 * @retval Current RTL polling time
 */
uint8_t ral_get_rtl_polling_time(void);
#endif /* SUPPORT_CONFIG_LIB */
#if SUPPORT_MAC_CONT_TESTING_CMDS_PHY_SUPPORT
/**
 * @brief Set the PHY continuous modulation and continuous wave modes.
 * 		  upon enable, if the selected mode is already enabled and likewise
 * 		  in disabling, the change will take no effect.
 *
 * @param[in] ral_instance 	: RAL instance
 * @param[in] type			: The type of the modulation (0: modulation, 1: wave)
 * @param[in] enable_mode	: 1 for enable \ 0 for disable
 * @param[in] chnl_num		: Channel number to be used in modulation (range: 0 to 15)
 * @param[in] tx_pwr        : The used power in dBm.
 */
void ral_phy_set_zigbee_phy_cont_test_mode(ral_instance_t ral_instance, uint8_t type, uint8_t enable_mode, uint8_t chnl_num, int8_t tx_pwr);
#endif /*end of SUPPORT_MAC_CONT_TESTING_CMDS_PHY_SUPPORT */

#if SUPPORT_A_MAC
/**
 * @brief   Get parameters used in augmented MAC (IFS, phy_rate, auto_ACK_config)
 *
 * @param[in] ral_instance 	: RAL instance
 * @param[out] a_mac_params : Current augmented MAC parameters
 * @retval Status
 */
ral_error_enum_t ral_get_a_mac_params(ral_instance_t ral_instance,ral_a_mac_params_st* a_mac_params);
#endif /*SUPPORT_A_MAC*/
/**
 * @brief   Set value for drop on error flag
 *
 * @param[in] ral_instance  : RAL instance
 * @param[in] drop_on_error : Value for drop on error flag
 */
void ral_set_drop_on_error(ral_instance_t ral_instance, uint8_t drop_on_error);

#endif /* INCLUDE_RAL_H_ */
