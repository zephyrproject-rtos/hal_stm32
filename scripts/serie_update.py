#!/usr/bin/python
"""
SPDX-License-Identifier: Apache-2.0
Copyright (c) 2024 STMicroelectronics.
This script define Stm32SerieUpdate class
to be used by update_stm32_package.py
"""

import os
import shutil
import subprocess
import re
from pathlib import Path
import logging
from jinja2 import Environment, FileSystemLoader
import ble_library
from common_utils import common_utils

STM32_CUBE_REPO_BASE = "https://github.com/STMicroelectronics/STM32Cube"
"""GitHub URL to get STM32Cube"""

SCRIPT_DIR = Path(__file__).absolute().parent
"""Script directory."""

REPO_ROOT = SCRIPT_DIR / ".."
"""Repository root (used for input/output default folders)."""

# list of created files. It is necessary to remove all of them
# as they are fully created when applying zephyr patch
zephyr_file_created = [
    "CMakeLists.txt",
    "README",
    "drivers/include/stm32_assert.h",
]


def version_tuple(version):
    """Remove 'v' in front of version and convert it to tuple,
    so that versions can be compared
    """
    v = re.sub("v", r"", version)
    return tuple(map(int, (v.split("."))))


class Stm32SerieUpdate:
    """class Stm32SerieUpdate"""

    def __init__(
        self,
        stm32_serie,
        stm32cube_repo_path,
        noclean,
        version_update,
        debug,
    ):
        """Class Stm32SerieUpdate constructor

        Args:
            stm32_serie: stm32 serie ex:stm32f3xx
            stm32cube_repo_path: directory path where to fetch github repo
            noclean: boolean to clean or not github repo after update done
            version_update: string to force a specified version to be updated
            debug: boolean to set log debug level

        Returns:
            return previous zephyr cube version.

        Raises:
            ValueError: If stm32 serie is not recognised.
            FileNotFoundError: If Zphyr STM32 cube path is not found
        """
        if not stm32_serie.startswith("stm32"):
            raise ValueError(
                f"Error: Unknown stm32 serie: {stm32_serie}. Must start with 'stm32'"
            )

        # Set serie variables
        self.stm32_serie = stm32_serie
        self.stm32_seriexx = stm32_serie + "xx"  # ex:stm32f3xx
        self.stm32_serie_upper = stm32_serie.upper()  # ex:STM32F3
        self.stm32_seriexx_upper = self.stm32_serie_upper + "xx"  # ex:STM32F3xx
        self.serie = self.stm32_serie_upper[5:]
        self.noclean = noclean
        self.version_update = version_update
        self.debug = debug
        self.module_patch = f"module_{self.stm32_serie}.patch"

        # #####  3 root directories to work with ########
        # 1: STM32Cube repo Default $HOME/STM32Cube_repo
        # 2: zephyr stm32 path  : ex: .../zephyr_project/module/hal/stm32
        # 3: Temporary directory to construct the update
        # (within STM32Cube repo dir)
        self.stm32cube_repo_path = stm32cube_repo_path
        if not self.stm32cube_repo_path.exists():
            self.stm32cube_repo_path.mkdir()

        self.zephyr_hal_stm32_path = REPO_ROOT
        if not self.zephyr_hal_stm32_path.exists():
            raise FileNotFoundError("Error: cannot find zephyr project")

        self.stm32cube_temp = self.stm32cube_repo_path / "temp_stm32xx_update"
        if self.stm32cube_temp.exists():
            shutil.rmtree(
                str(self.stm32cube_temp), onerror=common_utils.remove_readonly
            )
        self.stm32cube_temp.mkdir()

        # subdir specific to a stm32 serie
        self.stm32cube_serie_path = self.stm32cube_repo_path / Path(
            "STM32Cube" + self.serie
        )
        self.zephyr_module_serie_path = (
            self.zephyr_hal_stm32_path / "stm32cube" / self.stm32_seriexx
        )
        self.stm32cube_temp_serie = (
            self.stm32cube_temp / "stm32cube" / self.stm32_seriexx
        )
        shutil.rmtree(str(self.stm32cube_temp), onerror=common_utils.remove_readonly)
        self.stm32cube_temp_serie.mkdir(parents=True)

        self.readme_file_path = self.zephyr_module_serie_path / "README"
        self.version_tag = []
        self.current_version = ""
        self.update_commit = ""

        if self.debug:
            logging.basicConfig(format="%(levelname)s:%(message)s", level=logging.DEBUG)
            self.std_dest = None
        else:
            logging.basicConfig(format="%(levelname)s:%(message)s", level=logging.INFO)
            self.std_dest = subprocess.DEVNULL

    def os_cmd(self, cmd, cwd=None, shell=False):
        """Execute a command with subprocess.check_call()
        Args:
            cmd: string command to execute.
            cwd: directory where to run command
            shell: boolean to enable command interpretation by the shell

        Returns:
            return the returncode of the command after execution.
        """
        logging.debug("%s", f"{str(cmd)}      cwd:{str(cwd)}")

        return subprocess.check_call(
            cmd,
            shell=shell,
            stdout=self.std_dest,
            stderr=self.std_dest,
            cwd=cwd,
        )

    def rename_conf_template(self, path):
        """renames hal_conf_template.h to hal_conf.h ...
        Args:
            path: path where to apply the files processing
        """
        # except for _hal_conf_template.h which is renamed
        hal_conf_template_fullpath = Path(
            path / (self.stm32_seriexx + "_hal_conf_template.h")
        )
        if hal_conf_template_fullpath.is_file():
            hal_conf_fullpath = Path(
                re.sub("_template", r"", str(hal_conf_template_fullpath))
            )
            if hal_conf_fullpath.exists():
                hal_conf_fullpath.unlink()
            hal_conf_template_fullpath.rename(hal_conf_fullpath)

    def major_branch(self):
        # check whether master branch exist, otherwise use main branch
        master_branch_exist = subprocess.check_output(
            ("git", "ls-remote", "--heads", "origin", "master"),
            cwd=self.stm32cube_serie_path,
        ).decode("utf-8")
        if master_branch_exist:
            return "master"
        else:
            return "main"

    def clone_cube_repo(self):
        """Clone or fetch a stm32 serie repo"""
        repo_name = STM32_CUBE_REPO_BASE + self.serie + ".git"
        logging.info(
            "%s",
            "Cloning/fetching repo "
            + repo_name
            + " in "
            + str(self.stm32cube_serie_path),
        )
        if self.stm32cube_serie_path.exists():
            # if already exists, then just clean and fetch
            self.os_cmd(("git", "clean", "-fdx"), cwd=self.stm32cube_serie_path)
            self.os_cmd(("git", "fetch"), cwd=self.stm32cube_serie_path)
            # this is useful when HAL/CMSIS Device drivers submodules are not
            # already present locally, otherwise "git fetch" is sufficient
            self.os_cmd(("git", "submodule", "update", "--init"),
                        cwd=self.stm32cube_serie_path)
            branch = self.major_branch()
            # "Using --recurse-submodules will update the content of all active
            # submodules according to the commit recorded in the superproject.
            # If local modifications in a submodule would be overwritten the
            # checkout will fail unless -f is used."
            # https://git-scm.com/docs/git-checkout
            self.os_cmd(
                ("git", "checkout", "-f", "--recurse-submodules", branch),
                cwd=self.stm32cube_serie_path,
            )
        else:
            # HAL & CMSIS Device drivers are now included as git submodules in
            # upstream STM32Cube GitHub repositories
            # So to get them too, --recursive or --recurse-submodules is needed
            self.os_cmd(
                ("git", "clone", "--recursive", repo_name),
                cwd=self.stm32cube_repo_path,
            )
            branch = self.major_branch()

        logging.info("%s", f"Branch used: {branch}")

        # get the latest version of cube,
        # with the most recent one created being the last entry.
        self.os_cmd(("git", "checkout", branch), cwd=self.stm32cube_serie_path)
        self.version_tag = subprocess.check_output(
            ("git", "tag", "-l"), cwd=self.stm32cube_serie_path
        ).splitlines()
        self.version_tag = [x.decode("utf-8") for x in self.version_tag]
        # Search latest version
        if self.version_update == "":
            self.version_update = self.version_tag[0]
            for tag in self.version_tag:
                if version_tuple(tag) > version_tuple(self.version_update):
                    self.version_update = tag

    def get_zephyr_current_version(self):
        """Look for current zephyr hal version

        Returns:
            return previous zephyr cube version.

        Raises:
            ValueError: If version is not found.
        """
        with open(str(self.readme_file_path), "r") as f:
            for line in f:
                # pattern : "version " follow by optional "v",
                # followed by x.y or x.y.z  x,y,z may represent several digits
                # ex: 'version v1.8.9', 'version 10.20.25'
                pattern = r".*version v?(\d+\.\d+\.?\d*).*$"
                if re.match(pattern, line):
                    previous_version = re.sub(pattern, r"\1", line).rstrip("\n")
                    break

        # Match previous version and list of existing tags
        # which could be vx.y or x.y
        pos_version = [
            i for i, a in enumerate(self.version_tag) if previous_version in a
        ]
        if pos_version:
            # return previous zephyr version
            return self.version_tag[pos_version[0]]
        else:
            self.clean_files()
            raise ValueError(
                f"Error: cannot find version {previous_version} in STM32Cube_repo"
            )

    def extract_source(self):
        """Extract sources and includes files from STM32Cube repo
        and copy them in temporary directory
        """
        # for CMSIS files
        temp_cmsis_soc_path = self.stm32cube_temp_serie / "soc"
        Path.mkdir(temp_cmsis_soc_path, parents=True)

        stm32cube_cmsis_include_path = (
            self.stm32cube_serie_path
            / "Drivers"
            / "CMSIS"
            / "Device"
            / "ST"
            / self.stm32_seriexx_upper
            / "Include"
        )
        shutil.rmtree(temp_cmsis_soc_path, onerror=common_utils.remove_readonly)
        shutil.copytree(stm32cube_cmsis_include_path, temp_cmsis_soc_path)

        stm32cube_cmsis_templates_path = (
            self.stm32cube_serie_path
            / "Drivers"
            / "CMSIS"
            / "Device"
            / "ST"
            / self.stm32_seriexx_upper
            / "Source"
            / "Templates"
        )
        for repo_file in stm32cube_cmsis_templates_path.iterdir():
            repo_src = stm32cube_cmsis_templates_path / repo_file
            if repo_src.is_file():
                shutil.copy(str(repo_src), str(temp_cmsis_soc_path))

        # for hal and ll drivers
        temp_drivers_include_path = self.stm32cube_temp_serie / "drivers" / "include"
        temp_drivers_include_path.parent.mkdir(parents=True)

        stm32cube_driver_inc = (
            self.stm32cube_serie_path
            / "Drivers"
            / Path(self.stm32_seriexx_upper + "_HAL_Driver")
            / "Inc"
        )
        if temp_drivers_include_path.exists():
            shutil.rmtree(
                temp_drivers_include_path, onerror=common_utils.remove_readonly
            )
        shutil.copytree(stm32cube_driver_inc, temp_drivers_include_path)

        # except for _hal_conf_template.h which is renamed
        self.rename_conf_template(temp_drivers_include_path)

        temp_drivers_src_path = self.stm32cube_temp_serie / "drivers" / "src"
        temp_drivers_src_path.mkdir()
        stm32cube_drivers_src_path = (
            self.stm32cube_serie_path
            / "Drivers"
            / Path(self.stm32_seriexx_upper + "_HAL_Driver")
            / "Src"
        )
        shutil.rmtree(temp_drivers_src_path, onerror=common_utils.remove_readonly)
        shutil.copytree(stm32cube_drivers_src_path, temp_drivers_src_path)

    def build_from_current_cube_version(self):
        """Build a commit in temporary dir with STM32Cube version
        corresponding to zephyr current hal version
        """
        # Checkout the current Zephyr version of the STM32Cube repo
        self.os_cmd(
            ("git", "checkout", "-f", "--recurse-submodules", self.current_version),
            cwd=self.stm32cube_serie_path,
        )

        # build the zephyr module from the stm32cube
        self.extract_source()
        logging.info(
            "%s", "Building module from STM32Cube_repo " + self.current_version
        )

        if not self.stm32cube_temp_serie.parent.exists():
            self.stm32cube_temp_serie.parent.mkdir(parents=True)

        self.os_cmd(
            ("git", "add", "-A", "stm32cube/" + self.stm32_seriexx + "/*"),
            cwd=self.stm32cube_temp,
        )
        self.os_cmd(
            ("git", "commit", "-am", '"module' + self.current_version + '"'),
            cwd=self.stm32cube_temp,
        )
        # Remove trailing whitespaces
        self.os_cmd(
            ("git", "rebase", "--whitespace=fix", "HEAD~1"),
            cwd=self.stm32cube_temp,
        )

    def build_patch_from_current_zephyr_version(self):
        """Build patch between zephyr current hal version and
        corresponding official STM32Cube version
        """
        # clean-up the module
        shutil.rmtree(
            str(self.stm32cube_temp_serie), onerror=common_utils.remove_readonly
        )

        # populate the new repo with this current zephyr module
        shutil.copytree(self.zephyr_module_serie_path, self.stm32cube_temp_serie)

        # commit this current version module
        self.os_cmd(("git", "add", "*"), cwd=self.stm32cube_temp)
        self.os_cmd(("git", "commit", "-am", '"module"'), cwd=self.stm32cube_temp)

        # Remove trailing space
        self.os_cmd(
            ("git", "rebase", "--whitespace=fix", "HEAD~1"),
            cwd=self.stm32cube_temp,
        )

        # generate a patch for files and _hal.conf.h file in the module
        logging.info(
            "%s",
            "Building patch from official "
            + self.current_version
            + " to current zephyr module",
        )

        # For unclear reason, using tuple ("git", "diff", ...) is failing on Linux
        # especially for this command. Keep a single string.
        self.os_cmd(
            ("git diff --ignore-space-at-eol HEAD~1 --output=" + self.module_patch),
            shell=True,
            cwd=self.stm32cube_temp,
        )
        self.os_cmd(("dos2unix", self.module_patch), cwd=self.stm32cube_temp)

    def update_readme(self, make_version, make_commit):
        """Update README file

        Args:
            make_version: latest STM32Cube version.
            make_commit: Commit corresponding to latest STM32Cube version.
        """
        see_release_note = True

        readme_path = self.zephyr_module_serie_path / "README"

        with readme_path.open(mode="r") as readme_prev:
            lines = (x for x in readme_prev.read().splitlines())

        readme_path.unlink()

        # Write README from previous one if exists
        with open(str(readme_path), "w") as readme_file:
            for LineItem in lines:
                # change version nb
                if "status" in LineItem.lower():
                    readme_file.write("Status:\n")
                    readme_file.write(f"   version {make_version}\n")
                    next(lines)  # skip next line
                elif "commit" in LineItem.lower():
                    readme_file.write("Commit:\n")
                    readme_file.write(f"   {make_commit}")
                    next(lines)  # skip next line
                elif "URL" in LineItem.upper():
                    readme_file.write("URL:\n")
                    readme_file.write(
                        "   https://github.com/STMicroelectronics/"
                        + f"STM32Cube{self.serie}\n"
                    )
                    next(lines)  # skip next line
                # change patch list with a link to the release_note.html
                elif "Patch List" in LineItem:
                    readme_file.write("Patch List:\n")
                    readme_file.write(
                        "--> please check that the following list "
                        + "is still valid:\n"
                    )
                else:
                    if "See release_note.html from STM32Cube" in LineItem:
                        see_release_note = False
                    readme_file.write(f"{LineItem}\n")

            # at the very end of the file :
            if see_release_note:
                readme_file.write("\n   See release_note.html from STM32Cube\n")
            readme_file.flush()

        self.os_cmd(("dos2unix", str(readme_path)))

    def update_cmakelist(self):
        """Update CMakeLists.txt file"""
        cmakelists_path = self.zephyr_module_serie_path / "CMakeLists.txt"
        if cmakelists_path.exists():
            # build new CMakeLists.txt
            with cmakelists_path.open("r") as cmakelists_old:
                # this line is the copyright line
                first_line = cmakelists_old.readline()
                if "STMicroelectronics" in first_line:
                    first_line = ""
            cmakelists_path.unlink()
        else:
            first_line = ""

        logging.info("%s", "Create a new CMakeLists.txt file")

        with cmakelists_path.open("w") as cmakelists_new:
            if first_line:
                cmakelists_new.write(first_line)
            cmakelists_new.write("# Copyright (c) 2020 STMicroelectronics\n")
            cmakelists_new.write("#\n")
            cmakelists_new.write("# SPDX-License-Identifier: Apache-2.0\n")
            cmakelists_new.write("\n")

            src_path = self.stm32cube_temp_serie / "drivers" / "src"
            source_files = list(src_path.iterdir())
            source_files.sort()

            cmakelists_new.write(
                f"zephyr_library_sources(soc/system_{self.stm32_seriexx}.c)\n"
            )
            cmakelists_new.write(
                f"zephyr_library_sources(drivers/src/{self.stm32_seriexx}_hal.c)\n"
            )
            cmakelists_new.write(
                f"zephyr_library_sources(drivers/src/{self.stm32_seriexx}_hal_rcc.c)\n"
            )
            cmakelists_new.write(
                "zephyr_library_sources(drivers/src/"
                + f"{self.stm32_seriexx}_hal_rcc_ex.c)\n"
            )

            for filename in source_files:
                # also skipping  '_xxx_hal.c'
                if "template" in filename.name:
                    continue

                # also skipping  '_xxx_hal_rcc.c' and '_xxx_hal_rcc_ex.c'
                if "_hal_rcc" in filename.name:
                    continue

                if "_hal_" in filename.name:
                    # retrieve IP name from filename, like adc,
                    # which is delimited by
                    #   * _hal_ on one side
                    #   * and file extension on the other side
                    pattern = r".*_hal_(.*)\..*"
                    cmakelists_new.write(
                        "zephyr_library_sources_ifdef(CONFIG_USE_STM32_HAL_"
                        + re.sub(pattern, r"\1", filename.name).upper()
                        + " drivers/src/"
                        + filename.name
                        + ")\n"
                    )
                if "_ll_" in filename.name:
                    # retrieve IP name from filename, like adc,
                    # which is delimited by
                    #   * _ll_ on one side
                    #   * and file extension on the other side
                    pattern = r".*_ll_(.*)\..*"
                    cmakelists_new.write(
                        "zephyr_library_sources_ifdef(CONFIG_USE_STM32_LL_"
                        + re.sub(pattern, r"\1", filename.name).upper()
                        + " drivers/src/"
                        + filename.name
                        + ")\n"
                    )
        self.os_cmd(("dos2unix", str(cmakelists_path)))

    def generate_assert_file(self):
        """Remove stm32_assert_template.h file and create stm32_assert.h file"""
        # remove stm32_assert_template.h
        stm32_assert_template = (
            self.stm32cube_temp_serie
            / "drivers"
            / "include"
            / "stm32_assert_template.h"
        )
        if stm32_assert_template.exists():
            stm32_assert_template.unlink()

        # create stm32_assert.h from Jinja2 template
        # Create the jinja2 environment.
        templates_dir = self.zephyr_hal_stm32_path / "scripts"
        j2_env = Environment(
            loader=FileSystemLoader(str(templates_dir)),
            trim_blocks=True,
            lstrip_blocks=True,
        )
        stm32_assert_j2_template = j2_env.get_template("stm32_assert_template.txt")
        stm32_assert_h = (
            self.stm32cube_temp_serie / "drivers" / "include" / "stm32_assert.h"
        )

        with open(stm32_assert_h, "w") as stm32_assert_file:
            stm32_assert_file.write(
                stm32_assert_j2_template.render(stm32serie=self.stm32_serie)
            )

    def build_from_version_update(self):
        """Build a commit in temporary dir with STM32Cube version
        corresponding to zephyr latest hal version
        """
        # Checkout the latest version of the upstream STM32Cube repo
        self.os_cmd(
            ("git", "checkout", "-f", "--recurse-submodules", self.version_update),
            cwd=self.stm32cube_serie_path,
        )

        # Get the commit id of this latest version
        self.update_commit = subprocess.check_output(
            ("git", "rev-parse", "HEAD"), cwd=self.stm32cube_serie_path
        ).decode("utf-8")

        # clear previous version content before populating with latest version
        shutil.rmtree(
            str(self.stm32cube_temp_serie), onerror=common_utils.remove_readonly
        )

        # populate temporary directory with latest version
        self.extract_source()

        # Commit files except log or patch files
        self.os_cmd(("git", "add", "*"), cwd=self.stm32cube_serie_path)
        self.os_cmd(("git", "reset", "--", "*.patch"), cwd=self.stm32cube_serie_path)
        self.os_cmd(("git", "reset", "--", "*.log"), cwd=self.stm32cube_serie_path)
        self.os_cmd(
            ("git", "commit", "-am", '"module' + self.version_update + '"'),
            cwd=self.stm32cube_temp_serie,
        )

    def apply_zephyr_patch(self):
        """Apply zephyr stm32 patch to latest stm32Cube version"""
        logging.info("%s", "Apply zephyr patches to " + self.version_update)

        # Copy from stm32cube_temp
        shutil.rmtree(
            str(self.zephyr_module_serie_path),
            onerror=common_utils.remove_readonly,
        )
        shutil.copytree(self.stm32cube_temp_serie, self.zephyr_module_serie_path)

        # apply dos2unix to whole zephyr hal serie sub directory
        for child in self.zephyr_module_serie_path.glob("**/*"):
            if child.is_file:
                self.os_cmd(("dos2unix", child), cwd=self.zephyr_module_serie_path)

        # Remove file that will be fully created by zephyr patch
        # (otherwise applying patch will report error)
        for file in zephyr_file_created:
            if Path(self.zephyr_module_serie_path, file).exists():
                Path(self.zephyr_module_serie_path, file).unlink()

        # Apply patch from new repo
        common_utils.apply_patch(
            str(self.stm32cube_temp / self.module_patch), self.zephyr_hal_stm32_path
        )

        # save patch file so that it can be analysed in case of error
        patch_path = self.zephyr_hal_stm32_path / self.module_patch
        if patch_path.exists():
            os.remove(patch_path)
        shutil.copy(str(self.stm32cube_temp / self.module_patch), patch_path)

        # Update README and CMakeList
        self.update_readme(self.version_update, self.update_commit)
        self.update_cmakelist()

        # remove stm32_assert_template.h and create stm32_assert.h
        self.generate_assert_file()

        # Add files but do not commit
        self.os_cmd(("git", "add", "*"), cwd=self.zephyr_hal_stm32_path)
        self.os_cmd(("git", "reset", "--", "*.patch"), cwd=self.zephyr_hal_stm32_path)
        self.os_cmd(("git", "reset", "--", "*.log"), cwd=self.zephyr_hal_stm32_path)
        self.os_cmd(("git", "reset", "--", "*.rej"), cwd=self.zephyr_hal_stm32_path)
        logging.warning(
            "%s",
            "README file : --> please check that the Patch list is still valid",
        )

    def merge_commit(self, lib=False):
        """Apply zephyr stm32 patch to latest stm32Cube version"""
        # Merge & commit
        # to clean the .rej files, uncomment line: reject()
        # reject()
        if lib:
            logging.info("%s", "commit BLE library update")
            commit_msg = "lib/stm32: "
        else:
            logging.info("%s", "commit HAL/LL Cube update ")
            commit_msg = "stm32cube: "

        commit_file_path = self.zephyr_module_serie_path / "commit.msg"
        with open(commit_file_path, "w") as commit:
            commit.write(
                commit_msg
                + "update "
                + self.stm32_serie
                + " to cube version "
                + self.version_update.upper()
                + "\n"
            )

            commit.write("\n")
            commit.write(
                "Update Cube version for " + self.stm32_seriexx_upper + " series" + "\n"
            )
            commit.write("on https://github.com/STMicroelectronics" + "\n")
            commit.write(f"from version {self.current_version}\n")
            commit.write(f"to version {self.version_update}\n")
        self.os_cmd(
            ("git", "commit", "-as", "-F", commit_file_path),
            cwd=self.zephyr_module_serie_path,
        )
        self.os_cmd(
            ("git", "rebase", "--whitespace=fix", "HEAD~1"),
            cwd=self.zephyr_module_serie_path,
        )
        Path(commit_file_path).unlink()

    def reject(self):
        """Clean *.rej files"""
        reject_files = [f for f in self.zephyr_module_serie_path.glob("**/*.rej")]
        if reject_files:
            for f in reject_files:
                f.unlink()

    def cleanup_stm32cube_repo(self):
        """clean the STM32Cube repo"""
        self.os_cmd(("git", "checkout", "-f", "--recurse-submodules", "HEAD"),
                    cwd=self.stm32cube_serie_path)

    def clean_files(self):
        """Clean repo file if required"""
        # Remove temporary files unconditionally
        os.chdir(os.getenv("HOME"))
        shutil.rmtree(str(self.stm32cube_temp), onerror=common_utils.remove_readonly)

        # remove STM32Cube repo only if required
        if not self.noclean:
            self.cleanup_stm32cube_repo()
            shutil.rmtree(
                str(self.stm32cube_repo_path), onerror=common_utils.remove_readonly
            )
        else:
            self.os_cmd(
                ("git", "checkout", "-f", "--recurse-submodules", "HEAD"),
                cwd=self.stm32cube_serie_path,
            )

    def update_stm32_hal_serie(self):
        """Update one single STM32Cube"""
        # 1) clone full repo from github : get the repo STM32CubeXX
        self.clone_cube_repo()

        # 2) prepare a repo where to store module versions
        self.os_cmd(("git", "init"), cwd=self.stm32cube_temp)
        self.os_cmd(
            ("git", "commit", "--allow-empty", "-m", "'Trigger notification'"),
            cwd=self.stm32cube_temp,
        )

        # 3) get the version of cube which is in the zephyr module
        self.current_version = self.get_zephyr_current_version()
        logging.info(
            f"Version {self.current_version} is the current zephyr version for "
            + self.zephyr_module_serie_path.name
        )

        # do not process if versions are similar
        if (self.current_version in self.version_update) or (
            self.version_update in self.current_version
        ):
            logging.warning(
                "%s",
                f"*** Update abandoned: identical versions {self.version_update} ***\n",
            )
            self.clean_files()
            return
        logging.info(
            f"*** Updating zephyr {self.stm32_serie} "
            + f"from version {self.current_version} to {self.version_update}"
        )

        # 4) build the module from this previous version
        self.build_from_current_cube_version()

        # 5) build the patch from the current zephyr version
        self.build_patch_from_current_zephyr_version()

        # 6) build the module from this latest version
        self.build_from_version_update()

        # 7) apply zephyr patch : in the zephyr module repo
        self.apply_zephyr_patch()
        self.merge_commit()

        # 8) In case of stm32wb, update ble library
        if self.stm32_serie == "stm32wb":
            ble_library.update(
                self.stm32cube_serie_path,
                Path(self.zephyr_hal_stm32_path / "lib" / "stm32wb"),
                self.stm32cube_temp,
                self.current_version,
                self.version_update,
                self.update_commit,
                self.stm32_serie
            )
            self.merge_commit(lib=True)

        # 9) In case of stm32wba, update hci library
        elif self.stm32_serie == "stm32wba":
            ble_library.update(
                self.stm32cube_serie_path,
                Path(self.zephyr_hal_stm32_path / "lib" / "stm32wba"),
                self.stm32cube_temp,
                self.current_version,
                self.version_update,
                self.update_commit,
                self.stm32_serie
            )
            self.merge_commit(lib=True)

        # 10) clean
        self.clean_files()
        logging.info("%s", f"Done {self.stm32_serie}\n")
