#!/usr/bin/python

# SPDX-License-Identifier: Apache-2.0
# Copyright (c) 2019 STMicroelectronics.
# This script will update the stm32cube module for Zephyr
# from the latest version on https://github.com/STMicroelectronics
# get the patch between initial version and latest version
# apply this patch on the zephyr module
# usage : 'python update_stm32_package.py <stm32_serie>'

import os
import sys; sys.dont_write_bytecode = True    # do not generate pyc file
import subprocess
import time
import make_stm32_module
import shutil


# execute with argument
option_clean = True
option_force = False
module_serie = ''

arg_names = ['command', 'a1', 'a2', 'a3']
args = map(None, arg_names, sys.argv)
args = {k: v for (k, v) in args}

if args['a1']:
    if 'stm32' in args['a1']:
        module_serie = args['a1']
    elif '-c' in args['a1']:
        option_clean = False
    elif '-f' in args['a1']:
        option_force = True
    elif '-h' in args['a1']:
        print "usage: python update_stm32_package.py [--help] [-f] [-c] stm32XX\n"
        print "       -c    will NOT clean the working repo"
        print "       -f    will force the merge except .rej files"
        print ""
        sys.exit()
    else:
        print 'unknown option'
if args['a2']:
    if 'stm32' in args['a2']:
        module_serie = args['a2']
    elif '-c' in args['a2']:
        option_clean = False
    elif 'f' in args['a2']:
        option_force = True
    else:
        print 'unknown option'
if args['a3']:
    if 'stm32' in args['a3']:
        module_serie = args['a3']
    elif '-c' in args['a3']:
        option_clean = False
    elif '-f' in args['a3']:
        option_force = True
    else:
        print 'unknown option'

if not module_serie or (not args['a1'] and not args['a2'] and not args['a3']):
    print " Usage: " + sys.argv[0] + " stm32XX <Serie to create>"
    print " --> example : python update_stm32_package.py stm32f3"
    sys.exit()

module_seriexx = module_serie + "xx"        # example 'stm32f3xx'
module_SERIE = module_serie.upper()         # example 'STM32F3'
module_SERIExx = module_SERIE + "xx"        # example 'STM32F3xx'

# prepare the dir where to store the module repo
if os.path.exists(os.getenv('ZEPHYR_BASE')):
    os.chdir(os.getenv('ZEPHYR_BASE'))
else:
    print "Error: cannot find ./zephyr project"
    sys.exit()

# 1) clone full repo from github : get the repo STM32CubeXX
repo_path = os.path.join(os.getenv('HOME'), 'STM32Cube_repo')
if not os.path.exists(repo_path):
    os.mkdir(repo_path)

os.chdir(repo_path)
repo_path = os.path.join(repo_path, 'STM32Cube' + module_SERIE[5:])
print "Create repo in "+repo_path
if not os.path.exists(repo_path):
    git_cmd = 'git clone https://github.com/STMicroelectronics/STM32Cube' + module_SERIE[5:] + '.git'
    while os.system(git_cmd) != 0:
        time.sleep(2)
    os.chdir(repo_path)
else:
    # if already exists, then just clean and fetch
    os.chdir(repo_path)
    os.system('git clean -fdx')
    while os.system('git fetch') != 0:
        time.sleep(2)
    os.system('git reset --hard master')

# get the latest version of cube: git tag -l to get a listing of all tags,
# with the most recent one created being the last entry.
git_cmd = 'git checkout master'
os.system(git_cmd)
version_tag = subprocess.check_output('git tag -l', shell=True).splitlines()
latest_version = version_tag[-1]

# 2) prepare a repo where to store module versions
new_repo = os.path.join(os.getenv('HOME'), 'STM32Cube_repo', 'zephyr_module')
if os.path.exists(new_repo):
    shutil.rmtree(new_repo, ignore_errors=True)

os.mkdir(new_repo)
os.chdir(new_repo)
os.system('git init')

# 3) get the version of cube which is in the zephyr module
os.chdir(os.path.join(os.getenv('ZEPHYR_BASE'), '../modules/hal/stm32/stm32cube',
         module_seriexx))
previous_version = subprocess.check_output('cat README | grep version | head -n1',
                                           shell=True)[1:]
previous_version = previous_version[previous_version.index('version ') + 8:-1]
print "Version " + previous_version + " is the original version for " + os.getcwd()

# 3.1) match previous version and list of existing tags which could be vx.y or x.y
pos_version = [i for i, a in enumerate(version_tag) if previous_version in a]
if pos_version:
    previous_version = version_tag[pos_version[0]]
else:
    print "Error: cannot find version " + previous_version + " in STM32Cube_repo"
    make_stm32_module.cleanup(module_serie)
    sys.exit()

# 3.2) do not process if versions are similar
if (previous_version in latest_version) or (latest_version in previous_version):
    print "Versions are identical: abandoned"
    make_stm32_module.cleanup(module_serie)
    sys.exit()

# 4) build the module from this previous version
# reset the STM32Cube repo to this previous version
os.chdir(repo_path)
git_cmd = 'git reset --hard ' + previous_version
print git_cmd
os.system(git_cmd)

# build the zephyr module from the stm32cube
previous_module = make_stm32_module.module(module_serie)
print "Building module from STM32Cube_repo "+previous_version

# populate the new repo with this previous_version
os.renames(previous_module, os.path.join(new_repo, 'stm32cube', module_seriexx))
print "Transfer previous module from " + previous_module + " to " + new_repo
os.chdir(new_repo)

git_cmd = 'git add -A stm32cube/' + module_seriexx + '/*'
print git_cmd
os.system(git_cmd)

git_cmd = 'git commit -am \"module' + previous_version + '\"'
print git_cmd
os.system(git_cmd)

git_cmd = 'git rebase --whitespace=fix HEAD~1'
print "Remove remove trailing spaces: " + git_cmd
os.system(git_cmd)

# 5) build the module from the current version
# clean-up the module
os.chdir(new_repo)
os.system('rm -rf ./stm32cube/*')

# 5.1) and populate the new repo with this current zephyr module
git_cmd = 'cp -rf ' + os.path.join(os.getenv('ZEPHYR_BASE'),
                                   '../modules/hal/stm32/stm32cube',
                                   module_seriexx) + ' ./stm32cube'
print git_cmd
os.system(git_cmd)

# 5.2) commit this current version module
git_cmd = 'git add * && git commit -am \"module\"'
print git_cmd
os.system(git_cmd)

git_cmd = 'git rebase --whitespace=fix HEAD~1'
print "Remove remove trailing spaces: " + git_cmd
os.system(git_cmd)

# 5.3) generate a patch for files and _hal.conf.h file in the module
print 'Building patch from ' + previous_version + ' to current module'
os.chdir(new_repo)
if os.system('git diff --ignore-space-at-eol HEAD^ >> module.patch') == 0:
    os.system('dos2unix module.patch')

hal_conf = os.path.join('stm32cube', module_seriexx, 'drivers', 'include',
                        module_seriexx + '_hal_conf.h')
if os.path.exists(hal_conf):
    git_cmd = 'git diff HEAD@{1} -- ' + hal_conf + ' >> hal_conf.patch'
    os.system(git_cmd)
    os.system('dos2unix hal_conf.patch')

# 6) build the module from this latest version
# reset the STM32Cube repo to this latest version
os.chdir(repo_path)
git_cmd = 'git reset --hard ' + latest_version
print git_cmd
os.system(git_cmd)

# 6.1) include the commit id of this latest version
git_cmd = 'git rev-parse HEAD'
latest_commit = subprocess.check_output(git_cmd, shell=True)

# 6.2) build the zephyr module from the stm32cube
latest_module = make_stm32_module.module(module_serie)
print "Building module from STM32Cube "+latest_version

# 6.3) clean-up the module
os.chdir(new_repo)
git_cmd = 'rm -rf ' + './stm32cube/*'
os.system(git_cmd)
# and populate the new repo with this latest zephyr module
os.renames(latest_module, os.path.join(new_repo, 'stm32cube', module_seriexx))
# include README except CMakelists files from current module and update
git_cmd = 'cp -rf ' + os.path.join(os.getenv('ZEPHYR_BASE'),
                                   '../modules/hal/stm32/stm32cube',
                                   module_seriexx,
                                   'README') + os.path.join(
                                   ' ./stm32cube',
                                   module_seriexx,
                                   'README')
print git_cmd
os.system(git_cmd)
git_cmd = 'cp -rf ' + os.path.join(os.getenv('ZEPHYR_BASE'),
                                   '../modules/hal/stm32/stm32cube',
                                   module_seriexx,
                                   'CMakeLists.txt') + os.path.join(
                                   ' ./stm32cube',
                                   module_seriexx,
                                   'CMakeLists.txt')
print git_cmd
os.system(git_cmd)

# 6.4) update README and CMakeList and copy release note
make_stm32_module.readme(module_serie, latest_version, latest_commit)
make_stm32_module.makelist(module_serie)
make_stm32_module.release_note(module_serie)

# 6.5) apply previous patch on hal_conf.h file
if os.path.exists('hal_conf.patch'):
    git_cmd = 'git apply --recount --3way ./hal_conf.patch'
    os.system(git_cmd + ' &>/dev/null')
    os.remove('hal_conf.patch')

# 6.6) commit files except log or patch files
git_cmd = 'git add * && git reset -- *.patch && git reset -- *.log'
print git_cmd
os.system(git_cmd)
git_cmd = 'git commit -am \"module' + latest_version + '\"'
print git_cmd
os.system(git_cmd)

# 6.7) remove trailing spaces
git_cmd = 'git rebase --whitespace=fix HEAD~1'
print "Remove remove trailing spaces: " + git_cmd
os.system(git_cmd)

# 6.8) generate a patch for each file in the module
if os.system('git diff  HEAD^ >> new_version.patch') == 0:
    os.system('dos2unix new_version.patch')

# 7) build the patch : in the zephyr module repo
print 'Building zephyr module from ' + previous_version + ' to ' + latest_version
module_path = os.path.join(os.getenv('ZEPHYR_BASE'), '../modules/hal/stm32')
os.chdir(module_path)

# 7.1) copy from new_repo
git_cmd = 'rm -rf ' + os.path.join('stm32cube', module_seriexx)
os.system(git_cmd)
git_cmd = 'cp -r ' + os.path.join(new_repo, 'stm32cube', module_seriexx) + ' ' + os.path.join('stm32cube', module_seriexx)
os.system(git_cmd)

# 7.2) apply patch from new repo
module_log = "module_" + module_serie + ".log"
git_cmd = 'git apply --recount --reject ' + os.path.join(new_repo, 'module.patch') + ' &>' + module_log
if os.system(git_cmd):
    print "Error when applying patch to zephyr module: see "+os.path.join(module_path, module_log)
else:
    option_force = True

# 7.3) add files but do not commit
os.system('git add * && git reset -- *.patch && git reset -- *.log && git reset -- *.rej')
print "README file : --> please check that the Patch list is still valid"

# 7.5) merge & commit if needed
if option_force:
    print "Force commit module "
    # to clean the .rej files, use: make_stm32_module.reject(module_serie)
    git_cmd = 'git commit -asm \"stm32cube: update ' + module_serie + ' to version ' + latest_version.upper() + '\n'
    git_cmd = git_cmd + '\n   Update Cube version for ' + module_SERIExx + ' series'
    git_cmd = git_cmd + '\n   on https://github.com/STMicroelectronics'
    git_cmd = git_cmd + '\n   from version ' + previous_version
    git_cmd = git_cmd + '\n   to version ' + latest_version + '\"'
    print git_cmd
    update_list = subprocess.check_output(git_cmd, shell=True).splitlines()

# 8) end
if option_clean:
    make_stm32_module.cleanup(module_serie)

os.chdir(repo_path)
os.system('git reset --hard HEAD &>/dev/null')

print "Done "
