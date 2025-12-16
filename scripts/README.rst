STM32Cube HAL packages updater.
###############################

Introduction:

This module provides scripts to update the STM32Cube for Zephyr.
Follow below steps to update the STM32Cube HAL from the latest
versions found in STM32CubeXX repositories.

Step 1: Modify the code
***********************

In order to update all the STM32CubeXX versions at once, run::

    $ python3 ./update_stm32_package.py

Alternatively, in order to update STM32CubeXX versions one by one, run for example::

    $ python3 ./update_stm32_package.py -s stm32f1

Check STM32CubeXX changes
=========================

Check that all existing changes to modules are correctly reported
in the new hal_stm32 version.

Update each modified stm32cube/stm32XXxx/README file in their last section.

Remove the following line::
	--> please check that the following list is still valid:


Step 2: Open a pull requests
****************************

hal_stm32 PR
============
Open a single pull request with 1 commit per stm32 familly (stm32xx)
in repo https://github.com/zephyrproject-rtos/hal_stm32.


Modify the west.yml
===================
In order to benefit from this pull request in Zephyr, modify
zephyrproject/zephyr/west.yml
so that hal_stm32 points to the above pull request. For example::

	    - name: hal_stm32
	      revision: pull/60/head
	      path: modules/hal/stm32


Open a 2nd pull request with west.yml in repo
https://github.com/zephyrproject-rtos/zephyr.


Step 3: After Merge
*******************

Re-Modify the west.yml
======================

Once the hal_stm32 pull request is merged (see step 2), in the zephyrproject-rtos/hal_stm32
repo, change again the zephyrproject-rtos/zephyr/west.yml
to reflect the actual zephyrproject-rtos/hal_stm32 latest commit SHA1, for example::

	    - name: hal_stm32
	      revision: a813cd83b0cfbaaa625f4941d04baa3f93c37476
	      path: modules/hal/stm32

The zephyrproject-rtos/zephyr pull request (see 2) must be updated consequently.

COMMENT:

- "set the SHA1 after merge of STM32Cube versions (modules/hal/stm32)"

See for example https://github.com/zephyrproject-rtos/zephyr/pull/23259.


Clean
=====
Once all is correctly merged, clean .rej and .log files, with :

::

 $ git clean -fdx
