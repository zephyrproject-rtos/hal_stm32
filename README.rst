This module provides the required STM32cube packages and libraries needed to
build a Zephyr application running on STM32 silicon.

Packages and libraries are updated regularly in order for STM32 users to benefit
from the latest STM32Cube versions, features and bug fixes. Updates are
generally done once in each Zephyr release, preferably soon after the opening
of the merge window to give time to users to use it, potentially report issues
if some are faced and get them fixed before the new version in released.

STM32Cube packages
******************

How to introduce a new version of stm32cube:
============================================
Original STM32Cube tree structure has been modified to a minimum
structure for a better fit into Zephyr.
STM32Cube is divided into drivers and soc section, with:

.. code-block:: none

   drivers/
       include/ contains Cube HAL/LL files from: Drivers/STM32YYxx_HAL_Driver/Inc/*
       src/ contains: Drivers/STM32YYxx_HAL_Driver/Src/*
   soc/ contains STM32 CMSIS files from
       *Drivers/CMSIS/Device/ST/STM32F1xx/Include/*
       *Drivers/CMSIS/Device/ST/STM32F1xx/Source/Templates/system_stm32f1xx.c

Additionally ``driver/include/stm32f1xx_hal_conf_template.h`` is renamed into
``driver/include/stm32f1xx_hal_conf.h``

If there are changes in the number of *.c files the Kconfig file in the
stm32cube directory and the ``CMakeLists.txt`` files in the stm32yyxx/ directories
will have to be updated. If *.c have been removed drivers that used them will
also have to be updated.

IMPORTANT:
----------
STM32Cube, as an external library, is not supposed to be modified.
In practice, it might be required to patch it.
When updating a STM32Cube package to a new version, please have a look
to the patch list in dedicated README file, to make sure you don't overwrite
some earlier modifications of the package.
In case of doubt, contact Zephyr code owner for stm32cube.


How to use STM32Cube:
=====================
In order to enjoy ST CMSIS definitions, ``CONFIG_HAS_STM32CUBE`` should be defined
and ``stm32yyxx.h`` should be included in ``soc.h``

.. code-block:: c

   #include <stm32f1xx.h>

Additionally, in order to use STM32Cube LL, include ``stm32yyxx_ll_foo.h`` in ``soc.h``.

.. code-block:: c

   #include <stm32f1xx_ll_usart.h>

Drivers and applications that need functions from the STM32Cube HAL/LL C-files
will need to add the appropriate select entries in their Kconfig files.
For example when functions from ``stm32f4xx_hal_uart.c`` are used, the following
entry should apear in driver's Kconfig file.

.. code-block:: none

	select USE_STM32_HAL_UART

should be added to the Kconfig file.


And if the driver for example needs functions from the LL I2C C-files, the
driver Kconfig file should include the following entry

.. code-block:: none

	select USE_STM32_LL_I2C


Use STM32Cube in your application:
==================================
It may happen that you want to access STM32Cube APIs in your application,
either because it is not available as a zephyr API or because you want to
by-pass use of existing Zephyr API.
In this case, you need to create a Kconfig file in your application which
contains the following:

.. code-block:: none

   mainmenu "MYAPP"

   source "Kconfig.zephyr"
   config MYAPP_STM32
     default y
     bool
     select USE_STM32_HAL_FOO
     select USE_STM32_LL_BAR

Additionally, you need to add the following includes:

.. code-block:: c

   #include <soc.h>
   #include <stm32YYxx_ll_bar.h>


STM32Cube based libraries:
**************************

For some specific features, in order to benefit from already available and
validated code. Libraries from STM32Cube packages are extracted and made
available in this module under `lib` folder.

No script is available for these libraries, so update is done manually, but
it should follow the same rhythm than STM32Cube packages.
