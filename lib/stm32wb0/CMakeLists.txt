# Copyright (c) 2024 STMicroelectronics
#
# SPDX-License-Identifier: Apache-2.0

zephyr_library()

# Set the correct directory
zephyr_include_directories(STM32_BLE)
zephyr_include_directories(STM32_BLE/stack/include)
zephyr_include_directories(BLE_TransparentMode/System/Modules/PKAMGR/Inc)
zephyr_include_directories(BLE_TransparentMode/System/Modules)
zephyr_include_directories(BLE_TransparentMode/System/Interfaces)
zephyr_include_directories(BLE_TransparentMode/System/Modules/RADIO_utils/Inc)
zephyr_include_directories(BLE_TransparentMode/System/Config/Debug_GPIO)
zephyr_include_directories(BLE_TransparentMode/System/Modules/RTDebug)
zephyr_include_directories(BLE_TransparentMode/Core/Inc)
zephyr_include_directories(BLE_TransparentMode/STM32_BLE/App)

target_link_directories(app PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../../zephyr/blobs/stm32wb0/lib)
target_link_libraries(app PUBLIC -l:stm32wb0x_ble_stack_controller_only.a)

function(min OUT_VAR)
	list(SORT ARGN COMPARE NATURAL ORDER ASCENDING)
	list(GET ARGN 0 MIN_ELEMENT)
	set(${OUT_VAR} ${MIN_ELEMENT} PARENT_SCOPE)
endfunction()

########### Begining of modularity selection ###########
set(CFG_BLE_CONTROLLER_MASTER_ENABLED "0")
set(CFG_BLE_CONTROLLER_SCAN_ENABLED "0")
set(CFG_BLE_CONTROLLER_PRIVACY_ENABLED "0")
set(CFG_BLE_SECURE_CONNECTIONS_ENABLED "0")
set(CFG_BLE_CONTROLLER_DATA_LENGTH_EXTENSION_ENABLED "0")
set(CFG_BLE_CONTROLLER_2M_CODED_PHY_ENABLED "1")
set(CFG_BLE_CONTROLLER_EXT_ADV_SCAN_ENABLED "0")
set(CFG_BLE_L2CAP_COS_ENABLED "0")
set(CFG_BLE_CONTROLLER_PERIODIC_ADV_ENABLED "0")
set(CFG_BLE_CONTROLLER_PERIODIC_ADV_WR_ENABLED "0")
set(CFG_BLE_CONTROLLER_CTE_ENABLED "0")
set(CFG_BLE_CONTROLLER_POWER_CONTROL_ENABLED "0")
set(CFG_BLE_CONNECTION_ENABLED "0")
set(CFG_BLE_CONTROLLER_CHAN_CLASS_ENABLED "0")
set(CFG_BLE_CONTROLLER_BIS_ENABLED "0")
set(CFG_BLE_CONNECTION_SUBRATING_ENABLED "0")
set(CFG_BLE_CONTROLLER_CIS_ENABLED "0")

zephyr_compile_definitions(
	-DBLESTACK_CONTROLLER_ONLY=1
	-DACI_HAL_GET_FIRMWARE_DETAILS_ENABLED=0
	-DACI_HAL_GET_FIRMWARE_DETAILS_V2_ENABLED=0
	-DACI_HAL_UPDATER_START_ENABLED=0
	-DACI_HAL_TRANSMITTER_TEST_PACKETS_ENABLED=0
	-DACI_HAL_TRANSMITTER_TEST_PACKETS_V2_ENABLED=0
	-DACI_HAL_WRITE_RADIO_REG_ENABLED=0
	-DACI_HAL_READ_RADIO_REG_ENABLED=0
)

if(CONFIG_BT_OBSERVER)
	set(CFG_BLE_CONTROLLER_SCAN_ENABLED "1")
endif()

if(CONFIG_BT_PRIVACY)
	set(CFG_BLE_CONTROLLER_PRIVACY_ENABLED "1")
endif()

if(CONFIG_BT_SMP)
	set(CFG_BLE_SECURE_CONNECTIONS_ENABLED "1")
endif()

if(CONFIG_BT_CTLR_DATA_LENGTH GREATER 27)
	set(CFG_BLE_CONTROLLER_DATA_LENGTH_EXTENSION_ENABLED "1")
endif()

if(CONFIG_BT_EXT_ADV)
	set(CFG_BLE_CONTROLLER_EXT_ADV_SCAN_ENABLED "1")
endif()

if(CONFIG_BT_L2CAP_ECRED)
	set(CFG_BLE_L2CAP_COS_ENABLED "1")
endif()

if(CONFIG_BT_PER_ADV OR CONFIG_BT_PER_ADV_SYNC)
	set(CFG_BLE_CONTROLLER_PERIODIC_ADV_ENABLED "1")
endif()

if(CONFIG_BT_PER_ADV_RSP)
  set(CFG_BLE_CONTROLLER_PERIODIC_ADV_WR_ENABLED "1")
endif()

if(CONFIG_BT_DF)
	set(CFG_BLE_CONTROLLER_CTE_ENABLED "1")
endif()

if(CONFIG_BT_TRANSMIT_POWER_CONTROL)
	set(CFG_BLE_CONTROLLER_POWER_CONTROL_ENABLED "1")
endif()

if(CONFIG_BT_CONN)
	set(CFG_BLE_CONNECTION_ENABLED "1")
endif()

if(CONFIG_BT_ISO_BROADCAST)
	set(CFG_BLE_CONTROLLER_BIS_ENABLED "1")
endif()

if(CONFIG_BT_ISO_UNICAST)
	set(CFG_BLE_CONTROLLER_CIS_ENABLED "1")
endif()

message(STATUS "BLE Stack modularity configuration:")
message(STATUS "CONTROLLER_SCAN_ENABLED=${CFG_BLE_CONTROLLER_SCAN_ENABLED}")
message(STATUS "CONTROLLER_PRIVACY_ENABLED=${CFG_BLE_CONTROLLER_PRIVACY_ENABLED}")
message(STATUS "SECURE_CONNECTIONS_ENABLED=${CFG_BLE_SECURE_CONNECTIONS_ENABLED}")
message(STATUS "CONTROLLER_DATA_LENGTH_EXTENSION_ENABLED=${CFG_BLE_CONTROLLER_DATA_LENGTH_EXTENSION_ENABLED}")
message(STATUS "CONTROLLER_2M_CODED_PHY_ENABLED=${CFG_BLE_CONTROLLER_2M_CODED_PHY_ENABLED}")
message(STATUS "CONTROLLER_EXT_ADV_SCAN_ENABLED=${CFG_BLE_CONTROLLER_EXT_ADV_SCAN_ENABLED}")
message(STATUS "L2CAP_COS_ENABLED=${CFG_BLE_L2CAP_COS_ENABLED}")
message(STATUS "CONTROLLER_PERIODIC_ADV_ENABLED=${CFG_BLE_CONTROLLER_PERIODIC_ADV_ENABLED}")
message(STATUS "CONTROLLER_PERIODIC_ADV_WR_ENABLED=${CFG_BLE_CONTROLLER_PERIODIC_ADV_WR_ENABLED}")
message(STATUS "CONTROLLER_CTE_ENABLED=${CFG_BLE_CONTROLLER_CTE_ENABLED}")
message(STATUS "CONTROLLER_POWER_CONTROL_ENABLED=${CFG_BLE_CONTROLLER_POWER_CONTROL_ENABLED}")
message(STATUS "CONNECTION_ENABLED=${CFG_BLE_CONNECTION_ENABLED}")
message(STATUS "CONTROLLER_CHAN_CLASS_ENABLED=${CFG_BLE_CONTROLLER_CHAN_CLASS_ENABLED}")
message(STATUS "CONTROLLER_BIS_ENABLED=${CFG_BLE_CONTROLLER_BIS_ENABLED}")
message(STATUS "CONNECTION_SUBRATING_ENABLED=${CFG_BLE_CONNECTION_SUBRATING_ENABLED}")
message(STATUS "CONTROLLER_CIS_ENABLED=${CFG_BLE_CONTROLLER_CIS_ENABLED}")

zephyr_compile_definitions(
	-DCFG_BLE_CONTROLLER_SCAN_ENABLED=${CFG_BLE_CONTROLLER_SCAN_ENABLED}
	-DCFG_BLE_CONTROLLER_PRIVACY_ENABLED=${CFG_BLE_CONTROLLER_PRIVACY_ENABLED}
	-DCFG_BLE_SECURE_CONNECTIONS_ENABLED=${CFG_BLE_SECURE_CONNECTIONS_ENABLED}
	-DCFG_BLE_CONTROLLER_DATA_LENGTH_EXTENSION_ENABLED=${CFG_BLE_CONTROLLER_DATA_LENGTH_EXTENSION_ENABLED}
	-DCFG_BLE_CONTROLLER_2M_CODED_PHY_ENABLED=${CFG_BLE_CONTROLLER_2M_CODED_PHY_ENABLED}
	-DCFG_BLE_CONTROLLER_EXT_ADV_SCAN_ENABLED=${CFG_BLE_CONTROLLER_EXT_ADV_SCAN_ENABLED}
	-DCFG_BLE_L2CAP_COS_ENABLED=${CFG_BLE_L2CAP_COS_ENABLED}
	-DCFG_BLE_CONTROLLER_PERIODIC_ADV_ENABLED=${CFG_BLE_CONTROLLER_PERIODIC_ADV_ENABLED}
	-DCFG_BLE_CONTROLLER_PERIODIC_ADV_WR_ENABLED=${CFG_BLE_CONTROLLER_PERIODIC_ADV_WR_ENABLED}
	-DCFG_BLE_CONTROLLER_CTE_ENABLED=${CFG_BLE_CONTROLLER_CTE_ENABLED}
	-DCFG_BLE_CONTROLLER_POWER_CONTROL_ENABLED=${CFG_BLE_CONTROLLER_POWER_CONTROL_ENABLED}
	-DCFG_BLE_CONNECTION_ENABLED=${CFG_BLE_CONNECTION_ENABLED}
	-DCFG_BLE_CONTROLLER_CHAN_CLASS_ENABLED=${CFG_BLE_CONTROLLER_CHAN_CLASS_ENABLED}
	-DCFG_BLE_CONTROLLER_BIS_ENABLED=${CFG_BLE_CONTROLLER_BIS_ENABLED}
	-DCFG_BLE_CONNECTION_SUBRATING_ENABLED=${CFG_BLE_CONNECTION_SUBRATING_ENABLED}
	-DCFG_BLE_CONTROLLER_CIS_ENABLED=${CFG_BLE_CONTROLLER_CIS_ENABLED}
)
########### End of modularity selection ###########

########### Beginning of numeric value section ###########
set(CFG_BLE_NUM_SYNC_SLOTS "0")
set(CFG_BLE_NUM_ADV_SETS "1")
set(CFG_BLE_NUM_EATT_CHANNELS "0")
set(CFG_BLE_NUM_BRC_BIG_MAX "0")
set(CFG_BLE_NUM_SYNC_BIG_MAX "0")
set(CFG_BLE_NUM_SYNC_BIS_MAX "0")
set(CFG_BLE_NUM_BRC_BIS_MAX "0")
set(CFG_BLE_NUM_CIG_MAX "0")
set(CFG_BLE_NUM_CIS_MAX "0")
set(CFG_BLE_NUM_AUX_SCAN_SLOTS "4")

set(bt_max_conn "0")

if(CONFIG_BT_PER_ADV_SYNC_MAX)
	set(CFG_BLE_NUM_SYNC_SLOTS "${CONFIG_BT_PER_ADV_SYNC_MAX}")
endif()

if(CONFIG_BT_EXT_ADV_MAX_ADV_SET)
	set(CFG_BLE_NUM_ADV_SETS "${CONFIG_BT_EXT_ADV_MAX_ADV_SET}")
endif()

if (CONFIG_BT_MAX_CONN)
	#Maximum number of simultaneous connections
	set(bt_max_conn "${CONFIG_BT_MAX_CONN}")
endif()

if (CONFIG_BT_EATT_MAX)
	# Maximum number of Enhanced ATT bearers
	set(CFG_BLE_NUM_EATT_CHANNELS "${CONFIG_BT_EATT_MAX}")
endif()

if (CONFIG_BT_ISO_MAX_BIG)
	# Maximum number of Broadcast Isochronous Groups (BIGs) to support
	# A BIG can be used for either transmitting or receiving, but not at the same time.
	if (CONFIG_BT_ISO_BROADCASTER)
		set(CFG_BLE_NUM_BRC_BIG_MAX "${CONFIG_BT_ISO_MAX_BIG}")
	endif()
	if (CONFIG_BT_ISO_SYNC_RECEIVER)
		set(CFG_BLE_NUM_SYNC_BIG_MAX "${CONFIG_BT_ISO_MAX_BIG}")
	endif()
endif()

if (CONFIG_BT_ISO_MAX_CHAN)
	# Maximum number of simultaneous Bluetooth isochronous channels supported.
	if (CONFIG_BT_ISO_BROADCASTER)
		set(CFG_BLE_NUM_BRC_BIS_MAX "${CONFIG_BT_ISO_MAX_BIG}")
	endif()
	if (CONFIG_BT_ISO_SYNC_RECEIVER)
		set(CFG_BLE_NUM_SYNC_BIS_MAX "${CONFIG_BT_ISO_MAX_BIG}")
	endif()
endif()

if (CONFIG_BT_ISO_MAX_CIG)
	# Maximum number of CIGs that are supported by the host.
	# A CIG can be used for either transmitting or receiving.
	set(CFG_BLE_NUM_CIG_MAX "${CONFIG_BT_ISO_MAX_CIG}")
endif()

if (CONFIG_BT_ISO_MAX_CHAN)
	# Maximum number of simultaneous Bluetooth isochronous channels supported.
	set(CFG_BLE_NUM_CIS_MAX "${CONFIG_BT_ISO_MAX_CHAN}")
endif()

zephyr_compile_definitions(
	-DCFG_BLE_NUM_SYNC_SLOTS=${CFG_BLE_NUM_SYNC_SLOTS}
	-DCFG_BLE_NUM_ADV_SETS=${CFG_BLE_NUM_ADV_SETS}
	-DCFG_BLE_NUM_EATT_CHANNELS=${CFG_BLE_NUM_EATT_CHANNELS}
	-DCFG_BLE_NUM_BRC_BIG_MAX=${CFG_BLE_NUM_BRC_BIG_MAX}
	-DCFG_BLE_NUM_SYNC_BIG_MAX=${CFG_BLE_NUM_SYNC_BIG_MAX}
	-DCFG_BLE_NUM_SYNC_BIS_MAX=${CFG_BLE_NUM_SYNC_BIS_MAX}
	-DCFG_BLE_NUM_BRC_BIS_MAX=${CFG_BLE_NUM_BRC_BIS_MAX}
	-DCFG_BLE_NUM_CIG_MAX=${CFG_BLE_NUM_CIG_MAX}
	-DCFG_BLE_NUM_CIS_MAX=${CFG_BLE_NUM_CIS_MAX}
	-DCFG_BLE_NUM_AUX_SCAN_SLOTS=${CFG_BLE_NUM_AUX_SCAN_SLOTS}
)
########### End of numeric value section ###########

########### Beginning of number of radio tasks calculation ###########
set(tasks "1")

if(${CFG_BLE_CONTROLLER_EXT_ADV_SCAN_ENABLED})
	MATH(EXPR tasks "2 * ${CFG_BLE_NUM_ADV_SETS}")
	if(${CFG_BLE_CONTROLLER_PERIODIC_ADV_ENABLED})
		MATH(EXPR tasks "${tasks} + ${CFG_BLE_NUM_ADV_SETS}")
		if(${CFG_BLE_CONTROLLER_PERIODIC_ADV_WR_ENABLED} AND ${CFG_BLE_CONNECTION_ENABLED})
			MATH(EXPR tasks "${tasks} + 2 * ${CFG_BLE_NUM_ADV_SETS}")
		endif()
		if(${CFG_BLE_CONTROLLER_BIS_ENABLED})
			#radio_tasks += min(NUM_ADV_SETS_CONF, MAX_NUM_BRC_BIG)
			min(temp ${CFG_BLE_NUM_ADV_SETS} ${CFG_BLE_NUM_BRC_BIG_MAX})
			MATH(EXPR tasks "${tasks} + ${temp}")
		endif()
	endif()
endif()

if(${CFG_BLE_CONTROLLER_CIS_ENABLED} AND ${CFG_BLE_CONNECTION_ENABLED})
	MATH(EXPR tasks "${tasks} + ${CFG_BLE_NUM_CIG_MAX}")
endif()

if(${CFG_BLE_CONTROLLER_SCAN_ENABLED})
	MATH(EXPR tasks "${tasks} + 1")
	if(${CFG_BLE_CONTROLLER_EXT_ADV_SCAN_ENABLED})
		MATH(EXPR tasks "${tasks} + ${CFG_BLE_NUM_AUX_SCAN_SLOTS}")
		if (${CFG_BLE_CONTROLLER_2M_CODED_PHY_ENABLED})
			MATH(EXPR tasks "${tasks} + 1")
		endif()
		if(${CFG_BLE_CONTROLLER_PERIODIC_ADV_ENABLED})
			# radio_tasks += min(NUM_AUX_SCAN_SLOTS_CONF, NUM_SYNC_SLOTS_CONF)
			min(temp ${CFG_BLE_NUM_AUX_SCAN_SLOTS} ${CFG_BLE_NUM_SYNC_SLOTS})
			MATH(EXPR tasks "${tasks} + ${temp}")
			if(${CFG_BLE_CONTROLLER_PERIODIC_ADV_WR_ENABLED} AND ${CFG_BLE_CONNECTION_ENABLED})
				# radio_tasks += 2 * min(NUM_AUX_SCAN_SLOTS_CONF, NUM_SYNC_SLOTS_CONF)
				min(temp ${CFG_BLE_NUM_AUX_SCAN_SLOTS} ${CFG_BLE_NUM_SYNC_SLOTS})
				MATH(EXPR tasks "${tasks} + 2*${temp}")
			endif()
			if(${CFG_BLE_CONTROLLER_BIS_ENABLED})
				#radio_tasks += min(NUM_AUX_SCAN_SLOTS_CONF, MAX_NUM_SYNC_BIG)
				min(temp ${CFG_BLE_NUM_AUX_SCAN_SLOTS} ${CFG_BLE_NUM_SYNC_BIG_MAX})
				MATH(EXPR tasks "${tasks} +${temp}")
			endif()
		endif()
	endif() # ${CFG_BLE_CONTROLLER_EXT_ADV_SCAN_ENABLED}
	if(${CFG_BLE_CONTROLLER_CIS_ENABLED} AND ${CFG_BLE_CONNECTION_ENABLED})
		MATH(EXPR tasks "${tasks} + ${CFG_BLE_NUM_CIG_MAX}")
	endif()
endif()

message(STATUS "Number of computed radio tasks: ${tasks}")
zephyr_compile_definitions(-DCFG_BLE_NUM_RADIO_TASKS=${tasks})

########### End of number of radio tasks calculation ###########

zephyr_library_sources(BLE_TransparentMode/STM32_BLE/App/dm_alloc.c)
zephyr_library_sources(BLE_TransparentMode/STM32_BLE/App/dtm_cmd_db.c)
zephyr_library_sources(BLE_TransparentMode/STM32_BLE/App/aci_adv_nwk.c)

set_source_files_properties(BLE_TransparentMode/STM32_BLE/App/dtm_cmd_db.c PROPERTIES COMPILE_FLAGS -Wno-array-bounds)
set_source_files_properties(STM32_BLE/stack/config/ble_stack_user_cfg.c PROPERTIES COMPILE_FLAGS -Wno-array-parameter)
zephyr_library_sources(BLE_TransparentMode/STM32_BLE/Target/bleplat_cntr.c)
zephyr_library_sources(BLE_TransparentMode/STM32_BLE/Target/bleplat.c)
zephyr_library_sources(BLE_TransparentMode/System/Modules/PKAMGR/Src/pka_manager.c)
zephyr_library_sources(BLE_TransparentMode/System/Interfaces/hw_aes.c)
zephyr_library_sources(BLE_TransparentMode/System/Interfaces/hw_pka.c)
zephyr_library_sources(BLE_TransparentMode/System/Interfaces/hw_rng.c)
zephyr_library_sources(BLE_TransparentMode/System/Modules/blue_unit_conversion.s)
zephyr_library_sources(BLE_TransparentMode/System/Modules/osal_memcpy.s)
zephyr_library_sources(BLE_TransparentMode/STM32_BLE/App/adv_buff_alloc_tiny.c)
zephyr_library_sources(BLE_TransparentMode/STM32_BLE/App/transport_layer.c)
zephyr_library_sources(BLE_TransparentMode/STM32_BLE/App/dtm_preprocess_events.c)
zephyr_library_sources(BLE_TransparentMode/STM32_BLE/App/adv_buff_alloc.c)
zephyr_library_sources(BLE_TransparentMode/System/Modules/RADIO_utils/Src/RADIO_utils.c)
zephyr_library_sources(BLE_TransparentMode/System/Modules/miscutil.c)
zephyr_library_sources(BLE_TransparentMode/STM32_BLE/App/pawr_buff_alloc.c)
zephyr_library_sources(STM32_BLE/stack/config/ble_stack_user_cfg.c)
zephyr_library_sources(BLE_TransparentMode/STM32_BLE/App/dtm_cmds.c)
zephyr_library_sources(BLE_TransparentMode/Core/Src/stm32wb0x_hal_msp.c)
