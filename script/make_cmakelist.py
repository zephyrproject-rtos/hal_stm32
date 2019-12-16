#!/usr/bin/python

# Copyright (c) 2019 STMicroelectronics.
# This script will build  CMakelists.txt files

import os
import sys

####################################################################################################
# build the CMakeLists.txt file
# into the current dir = ./module/stm32cube/stm32<serie>xx


def makelist(make_serie):
    if 'stm32' not in make_serie:
        make_serie = 'stm32' + make_serie            # example 'stm32f3'

    make_seriexx = make_serie.lower() + "xx"         # example 'stm32f3xx'
    if os.path.exists(os.path.join('./stm32cube', make_seriexx, 'CMakeLists.txt')):
        # build new CMakeLists.txt
        make_file = open(os.path.join('./stm32cube', make_seriexx, 'CMakeLists.txt'), 'r')
		first_line = make_file.readline()         # this line is the copyright line
        make_file.close()
        os.remove(os.path.join('./stm32cube', make_seriexx, 'CMakeLists.txt'))
    else:
        first_line = '' 

    print 'Create a new CMakeLists.txt file'

    make_file = open(os.path.join('./stm32cube', make_seriexx, 'CMakeLists.txt'), 'w')
    if first_line:
        make_file.write(first_line)
    make_file.write("# Copyright (c) 2019 STMicroelectronics.\n")
    make_file.write("#\n")
    make_file.write("# SPDX-License-Identifier: Apache-2.0\n")
    make_file.write("\n")
    make_Files = os.listdir(os.path.join('./stm32cube', make_seriexx, 'drivers/src'))
    make_Files.sort()

    make_file.write("zephyr_library_sources(soc/system_" + make_seriexx + ".c)\n")
    make_file.write("zephyr_library_sources(drivers/src/" + make_seriexx + "_hal.c)\n")
    make_file.write("zephyr_library_sources(drivers/src/" + make_seriexx + "_hal_rcc.c)\n")

    for f in make_Files:
        # also skipping  '_xxx_hal.c'
        if 'template' in os.path.splitext(f)[0]:
            continue
        if '_hal_' in os.path.splitext(f)[0]:
            make_file.write("zephyr_library_sources_ifdef(CONFIG_USE_STM32_HAL_" +
                            os.path.splitext(f)[0][(os.path.splitext(f)[0].index('_hal_')+5):].upper() +
                            " " + os.path.join("drivers/src", f) + ")\n")
        if '_ll_' in os.path.splitext(f)[0]:
            make_file.write("zephyr_library_sources_ifdef(CONFIG_USE_STM32_LL_" +
                            os.path.splitext(f)[0][(os.path.splitext(f)[0].index('_ll_')+4):].upper() +
                            " " + os.path.join("drivers/src", f) + ")\n")

    make_file.close()

####################################################################################################


if len(sys.argv) > 1:
    if 'stm32' not in sys.argv[1]:
        module_serie = 'stm32' + sys.argv[1]   # example 'stm32f3'
    else:
        module_serie = sys.argv[1]             # example 'stm32f3'
else:
    print " Usage: " + sys.argv[0] + " stm32XX Serie to create"
    print " --> example : zephyr_module stm32f4"
    sys.exit()

module_path = os.path.join(os.getenv('ZEPHYR_BASE'), '../modules/hal/stm32')
if os.path.exists(module_path):
    os.chdir(module_path)
    makelist(module_serie)
