STM32WB HCI
###########

Origin:
   ST Microelectronics
   https://github.com/STMicroelectronics/STM32CubeWB

Status:
   version {{ version }}

Purpose:
   This library is used on stm32wb series to enable HCI communication between
   a host BLE running on CM-4 STM32WB core and a controller BLE firmware running
   on CM-0 core.

Description:
   This library provides an API for shared RAM communication with BLE controller
   firmware running on STM32WB C-M0 core.

   It is build using  the following files extracted the STM32CubeWB package:
{{ extracted_file_list }}
Dependencies:
   This library depends on STM32Cube IPCC HAL API.
   It is available in stm32cube/stm32wbxx/drivers

URL:
   https://github.com/STMicroelectronics/STM32CubeWB

commit:
   {{ commit }}
Maintained-by:
   External

License:
   BSD-3-Clause

License Link:
   opensource.org/licenses/BSD-3-Clause

Patch List:
--> please check that the following list
        * Move some files license from ST SLA0044 to BSD-3 Clause
            Following files are distributed under ST License SLA0044.
            For Zephyr they are made available under BSD-3 Clause.
            - hw_if.h
            - hw_ipcc.c
            - app_common.h
            - app_conf.h
            - stm32_wpan_common.h
            - ble_bufsize.h
            - tl_dbg_conf.h

        *  (Z-WB-1) Remove dependency to hw_conf.h
            This file is not actually needed. Remove inclusion so we don't need
            to include it in library.
          Impacted file: app_conf.h

        *  (Z-WB-2) Remove use of useless section SYSTEM_DRIVER_CONTEXT
            Section has no use. Remove it.
          Impacted file: shci_tl.c

        *  (Z-WB-3) Inform C-M0 that BLE host should not be used.
            In case C-M0 binary includes BLE Host, inform that it should not be
            used as, in Zephyr context, it is  running on C-M4 side.
          Impacted file: app_conf.h


	* Remove trailing whitespaces
