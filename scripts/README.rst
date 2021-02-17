STM32Cube HAL packages updater.
###############################

Introduction:

This module provides scripts to update the STM32Cube for Zephyr.
Follow below steps to update the STM32Cube HAL from the latest
version found in STM32CubeXX repositories.

Step 1: Modify the code
***********************

In order to update all the STM32CubeXX versions at once, run::

    $ python3 ./update_stm32_package.py

Alternatively, in order to update STM32CubeXX versions one by one, run for example::

    $ python3 ./update_stm32_package.py -s stm32f1

Note: This requires $ZEPHYR_BASE is set in your environment.

Check STM32CubeXX changes
=========================

Check that all existing change to modules are correctly reported
in the new hal_stm32 version

Update each modified stm32cube/stm32XXxx/README in the last section,

Remove the following line::
	--> please check that the following list is still valid:


Step 2: Open a pull requests
****************************

hal_stm32 PR
============
Open a single pull request with 1 commit per stm32 familly (stm32xx)
in repo https://github.com/zephyrproject-rtos/hal_stm32


Modify the west.yml
===================
In order to benefit from this PR in zephyr, modify zephyrproject/zephyr/west.yml
so that hal_stm32 points to above pull request. Example::

	    - name: hal_stm32
	      revision: pull/60/head
	      path: modules/hal/stm32


Open a 2nd pull request with west.yml in repo
https://github.com/zephyrproject-rtos/zephyr


Step 3: After Merge
*******************

re-Modify the west.yml
======================

Once the hal_stm32 pull request is merged (see step 2), in the zephyrproject-rtos/hal_stm32

then change again the zephyrproject-rtos/zephyr/west.yml

to reflect the actual zephyrproject-rtos/hal_stm32 SHA1, example::

	    - name: hal_stm32
	      revision: a813cd83b0cfbaaa625f4941d04baa3f93c37476
	      path: modules/hal/stm32

The zephyrproject-rtos/zephyr pull request (see 2) must be updated consequently.

COMMENT:

- "set the SHA1 after merge of STM32Cube versions (modules/hal/stm32)"

See Example : https://github.com/zephyrproject-rtos/zephyr/pull/23259


clean
=====
once all is correct, clean .rej and .log files, with :

::

 $ git clean -fdx
