#!/usr/bin/python

# Copyright (c) 2019 STMicroelectronics.
# This script will update the repo on each STM32Cube
# from the latest version on https://github.com/STMicroelectronics
#
# usage : 'python fetch_cubes.py'

import os
import sys
import time

cube_path = os.path.join(os.getenv("HOME"), "STM32Cube_repo")
os.chdir(cube_path)

for stm in os.listdir(cube_path):
    if os.path.isdir(os.path.join(cube_path, stm)):
        os.chdir(os.path.join(cube_path, stm))
        print("updating repo " + stm)
        if os.system("git fetch origin") == 0:
            os.system("git reset --hard origin/master")
            os.system("git checkout master")
