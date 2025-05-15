STM32WB0 BLE controller interfacing library
###########################################

Origin:
   STMicroelectronics
   https://github.com/STMicroelectronics/STM32CubeWB0

Status:
   version v1.0.0

Purpose:
   This library is used on STM32WB0 series to port BLE controller library in
   a hosting environment (Zephyr RTOS in current case).

Description:

   This library is using the following files extracted from the STM32CubeWB0 package:
      Middlewares/ST/STM32_BLE/ble.h
      Middlewares/ST/STM32_BLE/stack/config/ble_stack_user_cfg.c
      Middlewares/ST/STM32_BLE/stack/include/ble_api.h
      Middlewares/ST/STM32_BLE/stack/include/ble_const.h
      Middlewares/ST/STM32_BLE/stack/include/ble_events.h
      Middlewares/ST/STM32_BLE/stack/include/ble_gatt.h
      Middlewares/ST/STM32_BLE/stack/include/ble_stack.h
      Middlewares/ST/STM32_BLE/stack/include/ble_stack_user_cfg.h
      Middlewares/ST/STM32_BLE/stack/include/ble_status.h
      Middlewares/ST/STM32_BLE/stack/include/ble_types.h
      Middlewares/ST/STM32_BLE/stack/include/bleplat.h
      Middlewares/ST/STM32_BLE/stack/include/bleplat_cntr.h
      Middlewares/ST/STM32_BLE/stack/include/uuid.h
      Projects/NUCLEO-WB09KE/Applications/BLE/BLE_TransparentMode/Core/Inc/app_common.h
      Projects/NUCLEO-WB09KE/Applications/BLE/BLE_TransparentMode/Core/Inc/app_conf.h
      Projects/NUCLEO-WB09KE/Applications/BLE/BLE_TransparentMode/Core/Src/stm32wb0x_hal_msp.c
      Projects/NUCLEO-WB09KE/Applications/BLE/BLE_TransparentMode/STM32_BLE/App/aci_adv_nwk.c
      Projects/NUCLEO-WB09KE/Applications/BLE/BLE_TransparentMode/STM32_BLE/App/aci_adv_nwk.h
      Projects/NUCLEO-WB09KE/Applications/BLE/BLE_TransparentMode/STM32_BLE/App/aci_gatt_nwk.h
      Projects/NUCLEO-WB09KE/Applications/BLE/BLE_TransparentMode/STM32_BLE/App/aci_l2cap_nwk.h
      Projects/NUCLEO-WB09KE/Applications/BLE/BLE_TransparentMode/STM32_BLE/App/adv_buff_alloc.c
      Projects/NUCLEO-WB09KE/Applications/BLE/BLE_TransparentMode/STM32_BLE/App/adv_buff_alloc.h
      Projects/NUCLEO-WB09KE/Applications/BLE/BLE_TransparentMode/STM32_BLE/App/adv_buff_alloc_tiny.c
      Projects/NUCLEO-WB09KE/Applications/BLE/BLE_TransparentMode/STM32_BLE/App/adv_buff_alloc_tiny.h
      Projects/NUCLEO-WB09KE/Applications/BLE/BLE_TransparentMode/STM32_BLE/App/app_ble.h
      Projects/NUCLEO-WB09KE/Applications/BLE/BLE_TransparentMode/STM32_BLE/App/ble_conf.h
      Projects/NUCLEO-WB09KE/Applications/BLE/BLE_TransparentMode/STM32_BLE/App/dm_alloc.c
      Projects/NUCLEO-WB09KE/Applications/BLE/BLE_TransparentMode/STM32_BLE/App/dm_alloc.h
      Projects/NUCLEO-WB09KE/Applications/BLE/BLE_TransparentMode/STM32_BLE/App/dtm_burst.h
      Projects/NUCLEO-WB09KE/Applications/BLE/BLE_TransparentMode/STM32_BLE/App/dtm_cmd_db.c
      Projects/NUCLEO-WB09KE/Applications/BLE/BLE_TransparentMode/STM32_BLE/App/dtm_cmd_db.h
      Projects/NUCLEO-WB09KE/Applications/BLE/BLE_TransparentMode/STM32_BLE/App/dtm_cmd_en.h
      Projects/NUCLEO-WB09KE/Applications/BLE/BLE_TransparentMode/STM32_BLE/App/dtm_cmd_stack_en.h
      Projects/NUCLEO-WB09KE/Applications/BLE/BLE_TransparentMode/STM32_BLE/App/dtm_cmds.c
      Projects/NUCLEO-WB09KE/Applications/BLE/BLE_TransparentMode/STM32_BLE/App/dtm_preprocess_events.c
      Projects/NUCLEO-WB09KE/Applications/BLE/BLE_TransparentMode/STM32_BLE/App/dtm_preprocess_events.h
      Projects/NUCLEO-WB09KE/Applications/BLE/BLE_TransparentMode/STM32_BLE/App/fifo.h
      Projects/NUCLEO-WB09KE/Applications/BLE/BLE_TransparentMode/STM32_BLE/App/hci_parser.h
      Projects/NUCLEO-WB09KE/Applications/BLE/BLE_TransparentMode/STM32_BLE/App/pawr_buff_alloc.c
      Projects/NUCLEO-WB09KE/Applications/BLE/BLE_TransparentMode/STM32_BLE/App/pawr_buff_alloc.h
      Projects/NUCLEO-WB09KE/Applications/BLE/BLE_TransparentMode/STM32_BLE/App/transport_layer.c
      Projects/NUCLEO-WB09KE/Applications/BLE/BLE_TransparentMode/STM32_BLE/App/transport_layer.h
      Projects/NUCLEO-WB09KE/Applications/BLE/BLE_TransparentMode/STM32_BLE/Target/bleplat.c
      Projects/NUCLEO-WB09KE/Applications/BLE/BLE_TransparentMode/STM32_BLE/Target/bleplat_cntr.c
      Projects/NUCLEO-WB09KE/Applications/BLE/BLE_TransparentMode/System/Interfaces/hw_aes.c
      Projects/NUCLEO-WB09KE/Applications/BLE/BLE_TransparentMode/System/Interfaces/hw_aes.h
      Projects/NUCLEO-WB09KE/Applications/BLE/BLE_TransparentMode/System/Interfaces/hw_pka.c
      Projects/NUCLEO-WB09KE/Applications/BLE/BLE_TransparentMode/System/Interfaces/hw_pka.h
      Projects/NUCLEO-WB09KE/Applications/BLE/BLE_TransparentMode/System/Interfaces/hw_rng.c
      Projects/NUCLEO-WB09KE/Applications/BLE/BLE_TransparentMode/System/Interfaces/hw_rng.h
      Projects/NUCLEO-WB09KE/Applications/BLE/BLE_TransparentMode/System/Modules/asm.h
      Projects/NUCLEO-WB09KE/Applications/BLE/BLE_TransparentMode/System/Modules/blue_unit_conversion.s
      Projects/NUCLEO-WB09KE/Applications/BLE/BLE_TransparentMode/System/Modules/compiler.h
      Projects/NUCLEO-WB09KE/Applications/BLE/BLE_TransparentMode/System/Modules/crash_handler.h
      Projects/NUCLEO-WB09KE/Applications/BLE/BLE_TransparentMode/System/Modules/miscutil.c
      Projects/NUCLEO-WB09KE/Applications/BLE/BLE_TransparentMode/System/Modules/miscutil.h
      Projects/NUCLEO-WB09KE/Applications/BLE/BLE_TransparentMode/System/Modules/osal.h
      Projects/NUCLEO-WB09KE/Applications/BLE/BLE_TransparentMode/System/Modules/osal_memcpy.s
      Projects/NUCLEO-WB09KE/Applications/BLE/BLE_TransparentMode/System/Modules/PKAMGR/Inc/pka_manager.h
      Projects/NUCLEO-WB09KE/Applications/BLE/BLE_TransparentMode/System/Modules/PKAMGR/Src/pka_manager.c
      Projects/NUCLEO-WB09KE/Applications/BLE/BLE_TransparentMode/System/Modules/RADIO_utils/Inc/RADIO_utils.h
      Projects/NUCLEO-WB09KE/Applications/BLE/BLE_TransparentMode/System/Modules/RADIO_utils/Src/RADIO_utils.c

Dependencies:
   This library depends on STM32Cube HAL API.
   It is available in stm32cube/stm32wb0x/drivers

URL:
   https://github.com/STMicroelectronics/STM32CubeWB0

Commit:
   61d80e00cdb6136a58a33b95d2137e3bc9baa28e

Maintained-by:
   External

License:
   BSD-3-Clause

License Link:
   opensource.org/licenses/BSD-3-Clause

Patch List:

	* Changes from the official delivery:
	- Removed "gatt_profile.h" and "gap_profile.h":
	  Impacted file: dtm_cmd_db.c
	- Added "#if (BLESTACK_CONTROLLER_ONLY == 0)" to hci_events_table:
	  Impacted file: dtm_preprocess_events.c
	- Added "#ifndef __ZEPHYR__":
	  Impacted file: transport_layer.c
	- Added "#ifndef __ZEPHYR__":
	  Impacted file: app_conf.h
	- Defined Error_Handler function:
	  Impacted file: stm32wb0x_hal_msp.c
	- Removed RT_DEBUG_GPIO_Init:
	  Impacted file: stm32wb0x_hal_msp.c
	- Replaced "main.h" with "stm32wb0x_hal.h":
	  Impacted file: stm32wb0x_hal_msp.c
	- Initialized Init_Delay to 0:
	  Impacted file: bleplat_cntr.c
	- Removed cryptolib directory
	- Removed lib directory
	- Removed doc directory
	- Added "#ifndef __ZEPHYR__":
	  Impacted file: dtm_cmd_en.h
	- Added "#if (BLESTACK_CONTROLLER_ONLY == 0)":
	  Impacted file: bleplat.c
	- Changed the value for CFG_BLE_NUM_CTE_ANTENNA_IDS_MAX to 11:
	  Impacted file: app_conf.h
	- Exclude HAL_UART_MspInit and HAL_UART_MspDeInit from compilation:
	  Impacted file: stm32wb0x_hal_msp.c
	- Removed BLEPLAT_RngGetRandom16 and BLEPLAT_RngGetRandom32 functions:
	  Impacted file: bleplat.c
	- dos2unix applied
	- trailing white spaces removed
