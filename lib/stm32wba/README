STM32WBA BLE controller interfacing library
###########################################

Origin:
   ST Microelectronics
   https://github.com/STMicroelectronics/STM32CubeWBA

Status:
   version v1.4.1

Purpose:
   This library is used on STM32WBA series to port  BLE controller library in
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
      Middlewares/ST/STM32_WPAN/link_layer/ll_cmd_lib/inc/_40nm_reg_files/DWC_ble154combo.h
      Middlewares/ST/STM32_WPAN/link_layer/ll_cmd_lib/inc/bsp.h
      Middlewares/ST/STM32_WPAN/link_layer/ll_cmd_lib/inc/common_types.h
      Middlewares/ST/STM32_WPAN/link_layer/ll_cmd_lib/inc/event_manager.h
      Middlewares/ST/STM32_WPAN/link_layer/ll_cmd_lib/inc/evnt_schdlr_gnrc_if.h
      Middlewares/ST/STM32_WPAN/link_layer/ll_cmd_lib/inc/hci.h
      Middlewares/ST/STM32_WPAN/link_layer/ll_cmd_lib/inc/ll_intf.h
      Middlewares/ST/STM32_WPAN/link_layer/ll_cmd_lib/inc/mem_intf.h
      Middlewares/ST/STM32_WPAN/link_layer/ll_cmd_lib/inc/os_wrapper.h
      Middlewares/ST/STM32_WPAN/link_layer/ll_cmd_lib/inc/power_table.h
      Middlewares/ST/STM32_WPAN/link_layer/ll_cmd_lib/inc/pta.h
      Middlewares/ST/STM32_WPAN/link_layer/ll_cmd_lib/inc/ll_intf_cmn.h
      Middlewares/ST/STM32_WPAN/link_layer/ll_cmd_lib/config/ble_full/ll_fw_config.h
      Middlewares/ST/STM32_WPAN/link_layer/ll_sys/inc/linklayer_plat.h
      Middlewares/ST/STM32_WPAN/link_layer/ll_sys/inc/ll_sys.h
      Middlewares/ST/STM32_WPAN/link_layer/ll_sys/src/ll_sys_cs.c
      Middlewares/ST/STM32_WPAN/link_layer/ll_sys/src/ll_sys_dp_slp.c
      Middlewares/ST/STM32_WPAN/link_layer/ll_sys/src/ll_sys_intf.c
      Middlewares/ST/STM32_WPAN/link_layer/ll_sys/src/ll_sys_startup.c
      Middlewares/ST/STM32_WPAN/link_layer/ll_sys/inc/ll_sys_startup.h
      Middlewares/ST/STM32_WPAN/stm32_wpan_common.h
      Projects/NUCLEO-WBA55CG/Applications/BLE/BLE_TransparentMode/Core/Inc/app_common.h
      Projects/NUCLEO-WBA55CG/Applications/BLE/BLE_TransparentMode/Core/Inc/app_conf.h
      Projects/NUCLEO-WBA55CG/Applications/BLE/BLE_TransparentMode/Core/Inc/app_entry.h
      Projects/NUCLEO-WBA55CG/Applications/BLE/BLE_TransparentMode/Core/Inc/utilities_conf.h
      Projects/NUCLEO-WBA55CG/Applications/BLE/BLE_TransparentMode/Core/Inc/main.h
      Projects/NUCLEO-WBA55CG/Applications/BLE/BLE_TransparentMode/System/Modules/Flash/rf_timing_synchro.c
      Projects/NUCLEO-WBA55CG/Applications/BLE/BLE_TransparentMode/System/Modules/Flash/rf_timing_synchro.h
      Projects/NUCLEO-WBA55CG/Applications/BLE/BLE_TransparentMode/System/Modules/Flash/flash_driver.c
      Projects/NUCLEO-WBA55CG/Applications/BLE/BLE_TransparentMode/System/Modules/Flash/flash_driver.h
      Projects/NUCLEO-WBA55CG/Applications/BLE/BLE_TransparentMode/System/Modules/Flash/flash_manager.c
      Projects/NUCLEO-WBA55CG/Applications/BLE/BLE_TransparentMode/System/Modules/Flash/flash_manager.h
      Projects/NUCLEO-WBA55CG/Applications/BLE/BLE_TransparentMode/System/Modules/RTDebug/debug_signals.h
      Projects/NUCLEO-WBA55CG/Applications/BLE/BLE_TransparentMode/System/Modules/RTDebug/RTDebug.c
      Projects/NUCLEO-WBA55CG/Applications/BLE/BLE_TransparentMode/System/Modules/RTDebug/RTDebug.h
      Projects/NUCLEO-WBA55CG/Applications/BLE/BLE_TransparentMode/System/Modules/RTDebug/local_debug_tables.h
      Projects/NUCLEO-WBA55CG/Applications/BLE/BLE_TransparentMode/System/Modules/scm.c
      Projects/NUCLEO-WBA55CG/Applications/BLE/BLE_TransparentMode/System/Modules/scm.h
      Projects/NUCLEO-WBA55CG/Applications/BLE/BLE_TransparentMode/System/Modules/stm_list.c
      Projects/NUCLEO-WBA55CG/Applications/BLE/BLE_TransparentMode/System/Modules/stm_list.h
      Projects/NUCLEO-WBA55CG/Applications/BLE/BLE_TransparentMode/System/Modules/utilities_common.h
      Projects/NUCLEO-WBA55CG/Applications/BLE/BLE_TransparentMode/System/Interfaces/hw.h
      Projects/NUCLEO-WBA55CG/Applications/BLE/BLE_TransparentMode/System/Interfaces/hw_aes.c
      Projects/NUCLEO-WBA55CG/Applications/BLE/BLE_TransparentMode/System/Interfaces/hw_if.h
      Projects/NUCLEO-WBA55CG/Applications/BLE/BLE_TransparentMode/System/Interfaces/hw_pka.c
      Projects/NUCLEO-WBA55CG/Applications/BLE/BLE_TransparentMode/System/Interfaces/pka_p256.c
      Projects/NUCLEO-WBA55CG/Applications/BLE/BLE_TransparentMode/System/Config/Log/log_module.c
      Projects/NUCLEO-WBA55CG/Applications/BLE/BLE_TransparentMode/System/Config/Log/log_module.h
      Projects/NUCLEO-WBA55CG/Applications/BLE/BLE_TransparentMode/System/Config/Debug_GPIO/app_debug.h
      Projects/NUCLEO-WBA55CG/Applications/BLE/BLE_TransparentMode/System/Config/Debug_GPIO/debug_config.h
      Projects/NUCLEO-WBA55CG/Applications/BLE/BLE_TransparentMode/STM32_WPAN/Target/power_table.c
      Projects/NUCLEO-WBA55CG/Applications/BLE/BLE_TransparentMode/STM32_WPAN/Target/bpka.c
      Projects/NUCLEO-WBA55CG/Applications/BLE/BLE_TransparentMode/STM32_WPAN/Target/bpka.h
      Projects/NUCLEO-WBA55CG/Applications/BLE/BLE_TransparentMode/STM32_WPAN/Target/linklayer_plat.c
      Projects/NUCLEO-WBA55CG/Applications/BLE/BLE_TransparentMode/STM32_WPAN/Target/ll_sys_if.c
      Utilities/trace/adv_trace/stm32_adv_trace.h
      Utilities/misc/stm32_mem.h
      Utilities/tim_serv/stm32_timer.h
      Utilities/misc/stm32_tiny_vsnprintf.h

Dependencies:
   This library depends on STM32Cube HAL API.
   It is available in stm32cube/stm32wbaxx/drivers

URL:
   https://github.com/STMicroelectronics/STM32CubeWBA

Commit:
   3820501e7e128592290861c9cc0f7189246bf00d

Maintained-by:
   External

License:
   BSD-3-Clause
   MIT

License Link:
   opensource.org/licenses/BSD-3-Clause
   opensource.org/license/mit

Patch List:

	* Enabled extended advertising in CFG_BLE_OPTIONS:
	  Impacted file: app_conf.h

	* Disable Temperature based radio calibration:
	  Impacted file: app_conf.h

	* Increased 2.4GHz RADIO low ISR priority:
	  Impacted file: app_conf.h

	* Minimize dependency list
	  Impacted files: stm_list.h
			  main.h
			  app_conf.h
			  scm.c
			  ll_intf_cmn.h
			  ll_sys_if.c
			  linklayer_plat.c

	* #ifndef __ZEPHYR__ applied to remove Cube specific implementation
	  Impacted files: ll_sys_if.c
			  linklayer_plat.c

	* Changes from official delivery:
	- dos2unix applied
	- trailing white spaces removed
