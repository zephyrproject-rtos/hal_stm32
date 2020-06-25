#!/usr/bin/python

# SPDX-License-Identifier: Apache-2.0
# Copyright (c) 2019 STMicroelectronics.
# This script will build module, readme and CMakelists.txt files
# to use with zephyr_module.py

import os
import subprocess

##############################################################################
# create the module for zephyr in a new folder named '.<current_version>'
# where the <current_version> is the checkout one
# in the current directory( $HOME/STM32Cube/STM32CubeXX)


def module(make_serie):

    make_path = os.getcwd()

    if 'stm32' not in make_serie:
        make_serie = 'stm32' + make_serie    # example 'stm32f3'

    make_seriexx = make_serie.lower() + "xx"    # example 'stm32f3xx'
    make_SERIE = make_serie.upper()    # example 'STM32F3'
    make_SERIExx = make_SERIE + "xx"    # example 'STM32F3xx'

    # build and populate new directories from the repo :  .versionID
    # build the new zephyr module from the stm32cube
    make_repo = os.path.join(os.getenv("HOME"),
                             "STM32Cube_repo/STM32Cube" + make_SERIE[5:])
    # identify the version being made
    if not os.path.isdir(make_repo):
        return "Error : directory " + make_repo + " does not exist"
    else:
        os.chdir(make_repo)

    make_version = subprocess.check_output("git describe --tags", shell=True)[:-1]
    make_path = os.path.join(make_path, make_seriexx + "." + make_version)

    if os.path.exists(make_path):
        return "Error : directory " + make_path + " already exists"
    else:
        os.mkdir(make_path)

    #  for CMSIS files
    os.mkdir(os.path.join(make_path, "soc"))
    for repo_file in os.listdir(os.path.join(make_repo, "Drivers/CMSIS/Device/ST",
                                             make_SERIExx, "Include")):
        repo_src = os.path.join(make_repo, "Drivers/CMSIS/Device/ST",
                                make_SERIExx, "Include", repo_file)
        repo_dst = os.path.join(make_path, "soc", repo_file)
        os.rename(repo_src, repo_dst)

    for repo_file in os.listdir(os.path.join(make_repo, "Drivers/CMSIS/Device/ST",
                                             make_SERIExx, "Source/Templates")):
        repo_src = os.path.join(make_repo, "Drivers/CMSIS/Device/ST",
                                make_SERIExx, "Source/Templates", repo_file)
        if os.path.isfile(repo_src):
            repo_dst = os.path.join(make_path, "soc", repo_file)
            os.rename(repo_src, repo_dst)

    # for hal and ll drivers
    os.mkdir(os.path.join(make_path, "drivers"))

    os.mkdir(os.path.join(make_path, "drivers/include"))
    for repo_file in os.listdir(os.path.join(make_repo,
                                             "Drivers",
                                             make_SERIExx + "_HAL_Driver/Inc")):
        repo_src = os.path.join(make_repo, "Drivers",
                                make_SERIExx + "_HAL_Driver/Inc", repo_file)
        repo_dst = os.path.join(make_path, "drivers", "include", repo_file)
        os.renames(repo_src, repo_dst)

    # except for _hal_conf_template.h
    temp = [f for f in os.listdir(os.path.join(make_path, "drivers", "include")) if 'hal_conf_template.h' in f]
    if os.path.isfile(os.path.join(make_path, "drivers", "include", temp[0])):
        os.rename(os.path.join(make_path, "drivers", "include", temp[0]),
                  os.path.join(make_path, "drivers", "include",
                  os.path.splitext(temp[0])[0][:-9] + '.h'))

    os.mkdir(os.path.join(make_path, "drivers/src"))
    for repo_file in os.listdir(os.path.join(make_repo, "Drivers",
                                             make_SERIExx + "_HAL_Driver/Src")):
        repo_src = os.path.join(make_repo, "Drivers",
                                make_SERIExx + "_HAL_Driver/Src", repo_file)
        repo_dst = os.path.join(make_path, "drivers", "src", repo_file)
        os.rename(repo_src, repo_dst)

    return make_path

##############################################################################
# into the current dir = ./module/stm32cube/stm32<serie>xx


def readme(make_serie, make_version, make_commit):
    if 'stm32' not in make_serie:
        make_serie = 'stm32' + make_serie         # example 'stm32f3'

    make_seriexx = make_serie.lower() + "xx"      # example 'stm32f3xx'
    make_SERIE = make_serie.upper()               # example 'STM32F3'

    if os.path.exists(os.path.join('./stm32cube', make_seriexx, 'README')):
        # build new README from previous one if exists
        readme_file = open(os.path.join('./stm32cube',
                                        make_seriexx, 'README.new'), 'w')
    else:
        print 'Error: no README file'
        return

    with open(os.path.join('./stm32cube', make_seriexx, 'README'), 'r') as readme_prev:
        Lines = enumerate(readme_prev.read().splitlines())
        readme_prev.close()

    for LineItem in Lines:
        # change version nb
        if "status" in LineItem[1].lower():
            readme_file.write("Status:\n")
            readme_file.write("   version {0}\n".format(make_version))
            Lines.next()        # skip next line
        elif "commit" in LineItem[1].lower():
            readme_file.write("Commit:\n")
            readme_file.write("   {0}".format(make_commit))
            Lines.next()        # skip next line
        elif "URL" in LineItem[1].upper():
            readme_file.write("URL:\n")
            readme_file.write("   https://github.com/STMicroelectronics/STM32Cube{0}\n".format(make_SERIE[5:]))
            Lines.next()        # skip next line
        # change patch list with a link to the release_note.html
        elif "Patch List" in LineItem[1]:
            readme_file.write("Patch List:\n")
            readme_file.write("--> please check that the following list is still valid:\n")
        else:
            readme_file.write("{0}\n".format(LineItem[1]))
            # at the very end of the file :

    readme_file.write("\n   See release_note.html from STM32Cube\n")

    readme_file.flush()
    readme_file.close()

    os.rename(os.path.join('./stm32cube', make_seriexx, 'README.new'),
              os.path.join('./stm32cube', make_seriexx, 'README'))

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

##############################################################################
# copy the Release_Note.html from the original STM32Cube repo
# into the current dir = ./module/stm32cube/stm32<serie>xx


def release_note(make_serie):
    if 'stm32' not in make_serie:
        make_serie = 'stm32' + make_serie       # example 'stm32f3'

    make_seriexx = make_serie.lower() + "xx"    # example 'stm32f3xx'
    make_SERIE = make_serie.upper()             # example 'STM32F3'
    make_SERIExx = make_SERIE + "xx"            # example 'STM32F3xx'

    make_path = os.path.join(os.getenv("HOME"), "STM32Cube_repo/zephyr_module/stm32cube", make_seriexx)
    make_repo = os.path.join(os.getenv("HOME"), "STM32Cube_repo", "STM32Cube" + make_SERIE[5:])
    if os.path.exists(os.path.join(make_repo, 'Release_Notes.html')):
        os.rename(os.path.join(make_repo, 'Release_Notes.html'),
                  os.path.join(make_path, 'release_note.html'))

##############################################################################
# format the log error file after applying patch
# return True if error where found
# into the current dir = ./zephyr_module


def log_file(make_serie):
    if 'stm32' not in make_serie:
        make_serie = 'stm32' + make_serie         # example 'stm32f3'
    result = False
    if os.path.exists('module.log'):
        log_file = open('module.log', 'r')
        log_file_new = open('module.new', 'w')
        Lines = enumerate(log_file.read().splitlines())
        log_file.close()
        for LineItem in Lines:
            if "error:" in LineItem[1].lower():
                log_file_new.write("{0}\n".format(LineItem[1]))
                result = True

        log_file_new.flush()
        log_file_new.close()
        os.rename('module.new', 'module.log')

    return result

##############################################################################
# clean the STM32Cube repo


def cleanup(make_serie):
    if 'stm32' not in make_serie:
        make_serie = 'stm32' + make_serie       # example 'stm32f3'

    make_seriexx = make_serie.lower() + "xx"    # example 'stm32f3xx'
    make_SERIE = make_serie.upper()             # example 'STM32F3'
    make_SERIExx = make_SERIE + "xx"            # example 'STM32F3xx'

    os.chdir(os.path.join(os.getenv('HOME'), 'STM32Cube_repo'))
    # 10.2) cleanup repo path
    os.chdir("STM32Cube" + make_SERIE[5:])
    os.system('git reset --hard HEAD &>/dev/null')
    # 10.1) cleanup temp folder for zephyr module in STM32Cube repo
    make_path = os.path.join(os.getenv('HOME'), 'STM32Cube_repo')
    for root, dirs, files in os.walk(os.path.join(make_path, 'zephyr_module'), topdown=False):
        for name in files:
            os.remove(os.path.join(root, name))
        for name in dirs:
            os.rmdir(os.path.join(root, name))

    os.rmdir(os.path.join(make_path, 'zephyr_module'))

##############################################################################


def reject(make_serie):
    if 'stm32' not in make_serie:
        make_serie = 'stm32' + make_serie       # example 'stm32f3'

    make_seriexx = make_serie.lower() + "xx"    # example 'stm32f3xx'
    make_SERIE = make_serie.upper()             # example 'STM32F3'
    make_SERIExx = make_SERIE + "xx"            # example 'STM32F3xx'

    make_path = os.path.join(os.getcwd(), 'stm32cube', make_seriexx)

    for r, d, f in os.walk(make_path):
        for file in f:
            if '.rej' in file:
                os.remove(os.path.join(r, file))


##############################################################################


def merge(make_serie):
    if not os.path.exists('module.log'):
        print "Error: no file to merge"
        return

    if os.path.exists('module.log'):
        with open('module.log', 'r') as log_module:
            log_files = enumerate(log_module.read().splitlines())
            log_module.close()
    for i, j in log_files:
        log_file = j[21:21+j[21:].index(':')]
        print 'Merging file : ' + log_file
        merge_src = open(log_file, 'r')
        lines = merge_src.read().splitlines()
        if '<<<<<<< ours' not in [b for a, b in enumerate(lines)]:
                merge_src.close()
                continue
        else:
                merge_src.seek(0, 0)
        merge_dest = open(log_file + '.new', 'w')
        l = True
        while l != '':
                l = merge_src.readline()
                if '<<<<<<< ours' in l:
                        continue
                if '=======' in l:
                        l = merge_src.readline()
                        while '>>>>>>> theirs' not in l:
                                l = merge_src.readline()
                if '>>>>>>> theirs' in l:
                        continue
                merge_dest.write(l)

        merge_src.close()
        merge_dest.close()
        os.rename(log_file + '.new', log_file)
