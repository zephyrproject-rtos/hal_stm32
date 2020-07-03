.. _Updating the stm32Cube modules:

Steps to update the stm32Cube modules for zephyrproject
#######################################################

Overview
********
This is a brief description of the different steps to update
the stm32Cube hal, from the newest STM32CubeXX repositories.

1. modify code
**************

get STM32CubeXX version
=======================
From the ~/zephyrproject/modules/hal/stm32/scripts,
fetch all the STM32CubeXX directories from the STM, with :

::

 $ python fetch_cubes.py

Then update all the STM32CubeXX directories, with :

::

$ python update_cubes.py

check STM32CubeXX changes
=========================
Check that all existing change to modules are correctly reported
in the new hal_stm32 version

Update each modified stm32cube/stm32XXxx/README in the last section,

Remove the following line "--> please check that the following list is still valid:\n"

       Patch List:

       	See release_note.html from STM32Cube


2. create pull requests
***********************
Optionnaly:
===========
put each hal_stm32 cube update in a PR
of hal_stm32 github 'zephyrproject-rtos/hal_stm32'

global PR
=========
Set a global PR in the hal_stm32 github 'zephyrproject-rtos/hal_stm32'
with all the hal_stm32 cube update.

- See Example : https://github.com/zephyrproject-rtos/hal_stm32/pull/60

--> this is the temporary branch of hal_stm32 until it's merged.


Modify the west.yml
===================
in the the ~/zephyrproject/zephyr, to include this (temporary) PR as hal_stm32.

The west.yml module now points to this hal_stm32/pull request, like:

- name: hal_stm32

- revision: pull/60/head

- path: modules/hal/stm32


create the PR
=============
Create the corresponding zephyrproject-rtos/zephyr pull request
TITLE : west.yml: update hal stm32xx modules
DESRIPTION:
- This updates the stm32cube/stm32xx to latest branches

- Requires zephyrproject-rtos/hal_stm32#60

- Signed-off-by: xxx

See Example : https://github.com/zephyrproject-rtos/zephyr/pull/26240


3. after Merge
**************

re-Modify the west.yml
======================

Once the hal_stm32 pull request is merged (see 2.2), in the zephyrproject-rtos/hal_stm32

then change again the zephyrproject-rtos/zephyr/west.yml

to reflect the actual zephyrproject-rtos/hal_stm32 SHA1, like:

- name: hal_stm32

      revision: a813cd83b0cfbaaa625f4941d04baa3f93c37476

      path: modules/hal/stm32

The zephyrproject-rtos/zephyr pull request (see 2.4) must be updated consequently.

COMMENT:

- "set the SHA1 after merge of stm32cube versions (modules/hal/stm32)"

See Example : https://github.com/zephyrproject-rtos/zephyr/pull/23259


clean
=====
once all is correct, clean .rej and .log files, with :

::

 $ git clean -fdx
