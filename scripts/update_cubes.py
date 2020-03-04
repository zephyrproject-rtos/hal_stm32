#!/usr/bin/python

# Copyright (c) 2019 STMicroelectronics.
# This script will update the repo on each STM32Cube
# from the latest version on https://github.com/STMicroelectronics
#
# usage : 'python update_cubes.py'

import os
import sys

if not os.path.exists(os.getenv("ZEPHYR_BASE")):
    print("Error: cannot find ./zephyr project")
    sys.exit()

module_path = os.path.join(os.getenv("ZEPHYR_BASE"), "../modules/hal/stm32/stm32cube")
script_path = os.path.join(os.getenv("ZEPHYR_BASE"), "../modules/hal/stm32/scripts")
os.chdir(script_path)

for stmxx in os.listdir(module_path):
    if os.path.isdir(os.path.join(module_path, stmxx)):
        print("updating module " + stmxx[:-2])
        os.system("python update_stm32_package.py -f " + stmxx[:-2])
