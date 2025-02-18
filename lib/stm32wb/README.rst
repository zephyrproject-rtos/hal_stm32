STM32WB HCI
###########

Origin
------
`STM32CubeWB GitHub`_

Purpose
-------
| This library is used on stm32wb series to enable HCI communication between a host BLE running on the Cortex-M4 core
| and a controller BLE firmware running on the Cortex-M0 core.

Status
------
version v1.20.0

Coprocessor Binaries
--------------------
The table below details the history of the released binaries for the Cortex-M0 processor to be flashed to run BLE:

+----------------+---------------------+---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
| Zephyr Version | STM32CubeWB Version | Binaries                                                                                                                                                                                                |
+================+=====================+=========================================================================================================================================================================================================+
| 3.0            | 1.12.1              | `stm32wb5x_BLE_HCILayer_fw.bin <https://github.com/STMicroelectronics/STM32CubeWB/blob/v1.12.1/Projects/STM32WB_Copro_Wireless_Binaries/STM32WB5x/stm32wb5x_BLE_HCILayer_fw.bin>`__                     |
+----------------+---------------------+---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
| 3.1            | 1.13.2              | | `stm32wb5x_BLE_HCILayer_fw.bin <https://github.com/STMicroelectronics/STM32CubeWB/blob/v1.13.2/Projects/STM32WB_Copro_Wireless_Binaries/STM32WB5x/stm32wb5x_BLE_HCILayer_fw.bin>`__                   |
|                |                     | | `stm32wb5x_BLE_HCILayer_extended_fw.bin <https://github.com/STMicroelectronics/STM32CubeWB/blob/v1.13.2/Projects/STM32WB_Copro_Wireless_Binaries/STM32WB5x/stm32wb5x_BLE_HCILayer_extended_fw.bin>`__ |
+----------------+---------------------+---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
| 3.2            | 1.14.0              | | `stm32wb5x_BLE_HCILayer_fw.bin <https://github.com/STMicroelectronics/STM32CubeWB/blob/v1.14.0/Projects/STM32WB_Copro_Wireless_Binaries/STM32WB5x/stm32wb5x_BLE_HCILayer_fw.bin>`__                   |
|                |                     | | `stm32wb5x_BLE_HCILayer_extended_fw.bin <https://github.com/STMicroelectronics/STM32CubeWB/blob/v1.14.0/Projects/STM32WB_Copro_Wireless_Binaries/STM32WB5x/stm32wb5x_BLE_HCILayer_extended_fw.bin>`__ |
+----------------+---------------------+---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
| 3.4            | 1.16.0              | | `stm32wb5x_BLE_HCILayer_fw.bin <https://github.com/STMicroelectronics/STM32CubeWB/blob/v1.16.0/Projects/STM32WB_Copro_Wireless_Binaries/STM32WB5x/stm32wb5x_BLE_HCILayer_fw.bin>`__                   |
|                |                     | | `stm32wb5x_BLE_HCILayer_extended_fw.bin <https://github.com/STMicroelectronics/STM32CubeWB/blob/v1.16.0/Projects/STM32WB_Copro_Wireless_Binaries/STM32WB5x/stm32wb5x_BLE_HCILayer_extended_fw.bin>`__ |
+----------------+---------------------+---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
| 3.6            | 1.18.0              | | `stm32wb5x_BLE_HCILayer_fw.bin <https://github.com/STMicroelectronics/STM32CubeWB/blob/v1.18.0/Projects/STM32WB_Copro_Wireless_Binaries/STM32WB5x/stm32wb5x_BLE_HCILayer_fw.bin>`__                   |
|                |                     | | `stm32wb5x_BLE_HCILayer_extended_fw.bin <https://github.com/STMicroelectronics/STM32CubeWB/blob/v1.18.0/Projects/STM32WB_Copro_Wireless_Binaries/STM32WB5x/stm32wb5x_BLE_HCILayer_extended_fw.bin>`__ |
+----------------+---------------------+---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
| 3.7            | 1.19.1              | | `stm32wb5x_BLE_HCILayer_fw.bin <https://github.com/STMicroelectronics/STM32CubeWB/blob/v1.19.1/Projects/STM32WB_Copro_Wireless_Binaries/STM32WB5x/stm32wb5x_BLE_HCILayer_fw.bin>`__                   |
|                |                     | | `stm32wb5x_BLE_HCILayer_extended_fw.bin <https://github.com/STMicroelectronics/STM32CubeWB/blob/v1.19.1/Projects/STM32WB_Copro_Wireless_Binaries/STM32WB5x/stm32wb5x_BLE_HCILayer_extended_fw.bin>`__ |
+----------------+---------------------+---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
| 4.0            | 1.20.0              | | `stm32wb5x_BLE_HCILayer_fw.bin <https://github.com/STMicroelectronics/STM32CubeWB/blob/v1.20.0/Projects/STM32WB_Copro_Wireless_Binaries/STM32WB5x/stm32wb5x_BLE_HCILayer_fw.bin>`__                   |
|                |                     | | `stm32wb5x_BLE_HCILayer_extended_fw.bin <https://github.com/STMicroelectronics/STM32CubeWB/blob/v1.20.0/Projects/STM32WB_Copro_Wireless_Binaries/STM32WB5x/stm32wb5x_BLE_HCILayer_extended_fw.bin>`__ |
+----------------+---------------------+---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+

Description
-----------
This library provides an API for shared RAM communication with BLE controller firmware running on the Cortex-M0 core.

It is build using  the following files extracted the STM32CubeWB package:

* Middlewares/ST/STM32_WPAN/ble/core/ble_bufsize.h
* Middlewares/ST/STM32_WPAN/interface/patterns/ble_thread/hw.h
* Middlewares/ST/STM32_WPAN/interface/patterns/ble_thread/shci/shci.c
* Middlewares/ST/STM32_WPAN/interface/patterns/ble_thread/shci/shci.h
* Middlewares/ST/STM32_WPAN/interface/patterns/ble_thread/tl/hci_tl.h
* Middlewares/ST/STM32_WPAN/interface/patterns/ble_thread/tl/mbox_def.h
* Middlewares/ST/STM32_WPAN/interface/patterns/ble_thread/tl/shci_tl_if.c
* Middlewares/ST/STM32_WPAN/interface/patterns/ble_thread/tl/shci_tl.c
* Middlewares/ST/STM32_WPAN/interface/patterns/ble_thread/tl/shci_tl.h
* Middlewares/ST/STM32_WPAN/interface/patterns/ble_thread/tl/tl.h
* Middlewares/ST/STM32_WPAN/interface/patterns/ble_thread/tl/tl_mbox.c
* Middlewares/ST/STM32_WPAN/stm32_wpan_common.h
* Middlewares/ST/STM32_WPAN/utilities/dbg_trace.h
* Middlewares/ST/STM32_WPAN/utilities/stm_list.c
* Middlewares/ST/STM32_WPAN/utilities/stm_list.h
* Middlewares/ST/STM32_WPAN/utilities/utilities_common.h
* Projects/P-NUCLEO-WB55.Nucleo/Applications/BLE/BLE_Hid/Core/Inc/app_common.h
* Projects/P-NUCLEO-WB55.Nucleo/Applications/BLE/BLE_Hid/Core/Inc/app_conf.h
* Projects/P-NUCLEO-WB55.Nucleo/Applications/BLE/BLE_Hid/Core/Inc/hw_if.h
* Projects/P-NUCLEO-WB55.Nucleo/Applications/BLE/BLE_Hid/STM32_WPAN/Target/hw_ipcc.c
* Projects/P-NUCLEO-WB55.Nucleo/Applications/BLE/BLE_Hid/STM32_WPAN/App/tl_dbg_conf.h

Dependencies
------------
This library depends on STM32Cube IPCC HAL API. It is available in ``stm32cube/stm32wbxx/drivers``.

URL
---
https://github.com/STMicroelectronics/STM32CubeWB

Commit
------
529e571e91c93d4bf1aae6e0d69b9a5dcf4d828d

Maintained-by
-------------
External

License
-------
BSD-3-Clause

License Link
------------
https://opensource.org/license/BSD-3-Clause

Patch List
----------
* | Move some files license from ST SLA0044 to BSD-3 Clause.
  | Following files are distributed under ST License SLA0044 and they are made available under BSD-3 Clause for Zephyr:

  - hw_if.h
  - hw_ipcc.c
  - app_common.h
  - app_conf.h
  - stm32_wpan_common.h
  - ble_bufsize.h
  - tl_dbg_conf.h

* | (Z-WB-1) Remove dependency to hw_conf.h
  | This file is not actually needed. Remove inclusion so we don't need to include it in library.
  | Impacted file: app_conf.h

* | (Z-WB-2) Remove use of useless section SYSTEM_DRIVER_CONTEXT
  | Section has no use. Remove it.
  | Impacted file: shci_tl.c

* | (Z-WB-3) Inform C-M0 that BLE host should not be used.
  | In case C-M0 binary includes BLE Host, inform that it should not be
  | used as, in Zephyr context, it is  running on C-M4 side.
  | Impacted file: app_conf.h

* Changes from official delivery:

  - Trailing white spaces removed
  - dos2unix applied

.. _STM32CubeWB GitHub:
  https://github.com/STMicroelectronics/STM32CubeWB
