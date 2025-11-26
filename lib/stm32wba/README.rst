STM32WBA BLE and IEEE802154 controller interfacing library
###########################################

Origin:
   ST Microelectronics
   https://github.com/STMicroelectronics/STM32CubeWBA

Status:
   version v1.7.0

Purpose:
   This library is used on STM32WBA series to port BLE and IEEE802154 controller libraries in
   a hosting environment (Zephyr RTOS in current case).

Description:

   This library is using the following files extracted the STM32CubeWBA package:
      Middlewares/ST/STM32_WPAN/ble/stack/include/auto/ble_types.h
      Middlewares/ST/STM32_WPAN/ble/stack/include/ble_bufsize.h
      Middlewares/ST/STM32_WPAN/ble/stack/include/ble_const.h
      Middlewares/ST/STM32_WPAN/ble/stack/include/ble_defs.h
      Middlewares/ST/STM32_WPAN/ble/stack/include/ble_std.h
      Middlewares/ST/STM32_WPAN/ble/stack/include/bleplat.h
      Middlewares/ST/STM32_WPAN/ble/stack/include/blestack.h
      Middlewares/ST/STM32_WPAN/link_layer/ll_cmd_lib/_40nm_reg_files/_40nm_reg_files/DWC_ble154combo.h
      Middlewares/ST/STM32_WPAN/link_layer/ll_cmd_lib/inc/bsp.h
      Middlewares/ST/STM32_WPAN/link_layer/ll_cmd_lib/inc/common_types.h
      Middlewares/ST/STM32_WPAN/link_layer/ll_cmd_lib/inc/dtm.h
      Middlewares/ST/STM32_WPAN/link_layer/ll_cmd_lib/inc/event_manager.h
      Middlewares/ST/STM32_WPAN/link_layer/ll_cmd_lib/inc/evnt_schdlr_gnrc_if.h
      Middlewares/ST/STM32_WPAN/link_layer/ll_cmd_lib/inc/hci.h
      Middlewares/ST/STM32_WPAN/link_layer/ll_cmd_lib/inc/ll_error.h
      Middlewares/ST/STM32_WPAN/link_layer/ll_cmd_lib/inc/ll_intf.h
      Middlewares/ST/STM32_WPAN/link_layer/ll_cmd_lib/inc/mac_host_intf.h
      Middlewares/ST/STM32_WPAN/link_layer/ll_cmd_lib/inc/mem_intf.h
      Middlewares/ST/STM32_WPAN/link_layer/ll_cmd_lib/inc/os_wrapper.h
      Middlewares/ST/STM32_WPAN/link_layer/ll_cmd_lib/inc/platform.h
      Middlewares/ST/STM32_WPAN/link_layer/ll_cmd_lib/inc/power_table.h
      Middlewares/ST/STM32_WPAN/link_layer/ll_cmd_lib/inc/pta.h
      Middlewares/ST/STM32_WPAN/link_layer/ll_cmd_lib/inc/ral.h
      Middlewares/ST/STM32_WPAN/link_layer/ll_cmd_lib/inc/ll_intf_cmn.h
      Middlewares/ST/STM32_WPAN/link_layer/ll_cmd_lib/inc/rfd_dev_config.h
      Middlewares/ST/STM32_WPAN/link_layer/ll_cmd_lib/inc/ot_inc/crypto.h
      Middlewares/ST/STM32_WPAN/link_layer/ll_cmd_lib/inc/ot_inc/error.h
      Middlewares/ST/STM32_WPAN/link_layer/ll_cmd_lib/inc/ot_inc/instance.h
      Middlewares/ST/STM32_WPAN/link_layer/ll_cmd_lib/inc/ot_inc/logging.h
      Middlewares/ST/STM32_WPAN/link_layer/ll_cmd_lib/inc/ot_inc/radio.h
      Middlewares/ST/STM32_WPAN/link_layer/ll_cmd_lib/inc/ot_inc/toolchain.h
      Middlewares/ST/STM32_WPAN/link_layer/ll_cmd_lib/inc/ot_inc/types.h
      Middlewares/ST/STM32_WPAN/link_layer/ll_cmd_lib/config/ble_full/ll_fw_config.h
      Middlewares/ST/STM32_WPAN/link_layer/ll_cmd_lib/config/ble_basic/ll_fw_config.h
      Middlewares/ST/STM32_WPAN/link_layer/ll_cmd_lib/config/ieee_15_4_basic/ll_fw_config.h
      Middlewares/ST/STM32_WPAN/link_layer/ll_cmd_lib/config/thread/ll_fw_config.h
      Middlewares/ST/STM32_WPAN/link_layer/ll_cmd_lib/config/concurrent/ble_15_4/ll_fw_config.h
      Middlewares/ST/STM32_WPAN/link_layer/ll_cmd_lib/config/concurrent/ble_full_15_4/ll_fw_config.h
      Middlewares/ST/STM32_WPAN/link_layer/ll_sys/inc/linklayer_plat.h
      Middlewares/ST/STM32_WPAN/link_layer/ll_sys/inc/ll_sys.h
      Middlewares/ST/STM32_WPAN/link_layer/ll_sys/src/ll_sys_cs.c
      Middlewares/ST/STM32_WPAN/link_layer/ll_sys/src/ll_sys_dp_slp.c
      Middlewares/ST/STM32_WPAN/link_layer/ll_sys/src/ll_sys_intf.c
      Middlewares/ST/STM32_WPAN/link_layer/ll_sys/src/ll_sys_startup.c
      Middlewares/ST/STM32_WPAN/link_layer/ll_sys/inc/ll_sys_startup.h
      Middlewares/ST/STM32_WPAN/stm32_wpan_common.h
      Projects/NUCLEO-WBA65RI/Applications/BLE/BLE_TransparentMode/Core/Inc/app_common.h
      Projects/NUCLEO-WBA65RI/Applications/BLE/BLE_TransparentMode/Core/Inc/app_conf.h
      Projects/NUCLEO-WBA65RI/Applications/BLE/BLE_TransparentMode/Core/Inc/app_entry.h
      Projects/NUCLEO-WBA65RI/Applications/BLE/BLE_TransparentMode/Core/Inc/utilities_conf.h
      Projects/NUCLEO-WBA65RI/Applications/BLE/BLE_TransparentMode/Core/Inc/main.h
      Projects/Common/WPAN/Modules/Flash/rf_timing_synchro.c
      Projects/Common/WPAN/Modules/Flash/rf_timing_synchro.h
      Projects/Common/WPAN/Modules/Flash/flash_driver.c
      Projects/Common/WPAN/Modules/Flash/flash_driver.h
      Projects/Common/WPAN/Modules/Flash/flash_manager.c
      Projects/Common/WPAN/Modules/Flash/flash_manager.h
      Projects/Common/WPAN/Modules/RTDebug/debug_signals.h
      Projects/Common/WPAN/Modules/RTDebug/RTDebug.c
      Projects/Common/WPAN/Modules/RTDebug/RTDebug.h
      Projects/Common/WPAN/Modules/RTDebug/local_debug_tables.h
      Projects/Common/WPAN/Modules/scm.c
      Projects/Common/WPAN/Modules/scm.h
      Projects/Common/WPAN/Modules/stm_list.c
      Projects/Common/WPAN/Modules/stm_list.h
      Projects/Common/WPAN/Modules/utilities_common.h
      Projects/Common/WPAN/Interfaces/hw.h
      Projects/Common/WPAN/Interfaces/hw_aes.c
      Projects/Common/WPAN/Interfaces/hw_if.h
      Projects/Common/WPAN/Interfaces/hw_pka.c
      Projects/Common/WPAN/Interfaces/hw_pka_p256.c
      Projects/Common/WPAN/Modules/Log/log_module.c
      Projects/Common/WPAN/Modules/Log/log_module.h
      Projects/Common/WPAN/Modules/BasicAES/baes.h
      Projects/Common/WPAN/Modules/BasicAES/baes_ccm.c
      Projects/Common/WPAN/Modules/BasicAES/baes_cmac.c
      Projects/Common/WPAN/Modules/BasicAES/baes_ecb.c
      Projects/Common/WPAN/Modules/BasicAES/baes_global.h
      Projects/NUCLEO-WBA65RI/Applications/BLE/BLE_TransparentMode/System/Config/Debug_GPIO/app_debug.h
      Projects/NUCLEO-WBA65RI/Applications/BLE/BLE_TransparentMode/System/Config/Log/log_module_conf.h
      Projects/NUCLEO-WBA65RI/Applications/BLE/BLE_TransparentMode/STM32_WPAN/Target/power_table.c
      Projects/NUCLEO-WBA65RI/Applications/BLE/BLE_TransparentMode/STM32_WPAN/Target/bpka.c
      Projects/NUCLEO-WBA65RI/Applications/BLE/BLE_TransparentMode/STM32_WPAN/Target/bpka.h
      Projects/NUCLEO-WBA65RI/Applications/BLE/BLE_TransparentMode/STM32_WPAN/Target/linklayer_plat.c
      Projects/NUCLEO-WBA65RI/Applications/BLE/BLE_TransparentMode/STM32_WPAN/Target/ll_sys_if.c
      Projects/NUCLEO-WBA65RI/Applications/BLE/BLE_TransparentMode/STM32_WPAN/Target/ll_sys_if.h
      Utilities/trace/adv_trace/stm32_adv_trace.h
      Utilities/misc/stm32_mem.h
      Utilities/tim_serv/stm32_timer.h
      Utilities/misc/stm32_tiny_vsnprintf.h

   The files issued from the Projects/NUCLEO-WBA65RI/Applications/BLE/BLE_TransparentMode folder
   are used as reference in RF_Integration folder and reworked to support ieee802154 feature
   according to STM32Cube projects Zigbee_OnOff_Client_SED and BLE_HeartRate_Zigbee projects.

Dependencies:
   This library depends on STM32Cube HAL API.
   It is available in stm32cube/stm32wbaxx/drivers

URL:
   https://github.com/STMicroelectronics/STM32CubeWBA

Commit:
   f5b281ba4ca4d00aba59215728265f1d2cc80715

Maintained-by:
   External

License:
   BSD-3-Clause
   MIT

License Link:
   opensource.org/licenses/BSD-3-Clause
   opensource.org/license/mit

Patch List:
        * Discard "static" implementation of ll_sys_bg_temperature_measurement_init to allow specific zephyr implementation
          Impacted file: ll_sys_if.c
                         ll_sys.h

	* Enabled extended advertising in CFG_BLE_OPTIONS:
	  Impacted file: app_conf.h

	* Allowing Temperature based radio calibration configuration to be externally overwritten:
	  Impacted file: app_conf.h

	* Increased 2.4GHz RADIO low ISR priority:
	  Impacted file: app_conf.h

	* Minimize dependency list
	  Impacted files: stm_list.h
			  main.h
			  app_conf.h
			  ll_intf_cmn.h
			  ll_sys_if.c
			  linklayer_plat.c

	* #ifndef __ZEPHYR__ applied to remove Cube specific implementation
	  Impacted files: ll_sys_if.c
			  linklayer_plat.c

	* LL sleep timer clock source set to LSE by default
	  Impacted files: ll_sys_if.c
			  linklayer_plat.c

	* LL power table set not apllied
	  Impacted files: ll_sys_if.c

	* SCM_HSE_WaitUntilReady Cube mechanism not used
	  Impacted files: linklayer_plat.c

	* Changes from official delivery:
	- dos2unix applied
	- trailing white spaces removed

	* ble_plat.c is moved to zephyr/soc/st/stm32/stm32wbax/hci_if folder and renamed sys_wireless_plat.c
	  Shared with 802.15.4

	* host_stack.c is moved to zephyr/soc/st/stm32/stm32wbax/hci_if folder

	* linklayer_plat.c is splitted in two files:
	- linklayer_plat.c in RF_Integration subfolder in hal/stm32/lib/stm32wba
   - linklayer_plat_adapt.c in zephyr/soc/st/stm32/stm32wbax/hci_if

	* ll_sys_if.c is splitted in two files:
	- ll_sys_if.c in RF_Integration subfolder in hal/stm32/lib/stm32wba
   - ll_sys_if_adapt.c in zephyr/soc/st/stm32/stm32wbax/hci_if
