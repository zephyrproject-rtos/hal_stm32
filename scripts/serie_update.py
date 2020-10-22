#!/usr/bin/python
"""
SPDX-License-Identifier: Apache-2.0
Copyright (c) 2019 STMicroelectronics.
This script define Stm32SerieUpdate class
to be used by update_stm32_package.py
"""

import os
import stat
import shutil
import subprocess
import re
from pathlib import Path
import logging

STM32_CUBE_REPO_BASE = "https://github.com/STMicroelectronics/STM32Cube"

logging.basicConfig(level=logging.INFO)


def remove_readonly(func, path, _):
    """Remove read only protection"""
    os.chmod(path, stat.S_IWRITE)
    func(path)


def os_cmd(cmd, cwd=None, shell=False):
    """Execute a command with subprocess.check_call()
    Args:
        cmd: string command to execute.
        cwd: directory where to run command

    Returns:
        return the returncode of the command after execution.
    """
    logging.info(cmd)
    return subprocess.check_call(cmd, shell=shell, cwd=cwd)


class Stm32SerieUpdate:
    """class Stm32SerieUpdate"""

    def __init__(self, stm32_serie, stm32cube_repo_path, force, noclean):
        """Class Stm32SerieUpdate constructor

        Args:
            stm32_serie: stm32 serie ex:stm32f3xx
            stm32cube_repo_path: directory path where to fetch github repo
            force: boolean to force or not git commit after applying update
            noclean: boolean to clean or not github repo after update done

        Returns:
            return previous zephyr cube version.

        Raises:
            ValueError: If stm32 serie is not recognised.
            FileNotFoundError: If Zphyr STM32 cube path is not found
        """
        if not stm32_serie.startswith("stm32"):
            raise ValueError(
                "Error: Unknown stm32 serie: "
                + stm32_serie
                + ". Must start with 'stm32'"
            )

        # Set serie variables
        self.stm32_serie = stm32_serie
        self.stm32_seriexx = stm32_serie + "xx"  # ex:stm32f3xx
        self.stm32_serie_upper = stm32_serie.upper()  # ex:STM32F3
        self.stm32_seriexx_upper = self.stm32_serie_upper + "xx"  # ex:STM32F3xx
        self.serie = self.stm32_serie_upper[5:]
        self.force = force
        self.noclean = noclean

        # #####  3 root directories to work with ########
        # 1: STM32Cube repo Default $HOME/STM32Cube_repo
        # 2 : zephyr stm32 path  : ex: .../zephyr_project/module/hal/stm32
        # 3: Temporary directory to construct the update
        # (within STM32Cube repo dir)
        self.stm32cube_repo_path = stm32cube_repo_path
        if not self.stm32cube_repo_path.exists():
            self.stm32cube_repo_path.mkdir()

        self.zephyr_hal_stm32_path = (
            Path(os.getenv("ZEPHYR_BASE")).absolute()
            / ".."
            / "modules"
            / "hal"
            / "stm32"
        )
        if not self.zephyr_hal_stm32_path.exists():
            raise FileNotFoundError("Error: cannot find zephyr project")

        self.stm32cube_temp = self.stm32cube_repo_path / "temp_stm32xx_update"
        if self.stm32cube_temp.exists():
            shutil.rmtree(str(self.stm32cube_temp), onerror=remove_readonly)
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
        shutil.rmtree(str(self.stm32cube_temp), onerror=remove_readonly)
        self.stm32cube_temp_serie.mkdir(parents=True)

        self.readme_file_path = self.zephyr_module_serie_path / "README"
        self.version_tag = []
        self.current_version = ""
        self.latest_version = ""
        self.latest_commit = ""

    def clone_cube_repo(self):
        """Clone or fetch a stm32 serie repo"""
        if self.stm32cube_serie_path.exists():
            logging.info("fetching repo " + str(self.stm32cube_serie_path))
            # if already exists, then just clean and fetch
            os_cmd(("git", "clean", "-fdx"), cwd=self.stm32cube_serie_path)
            os_cmd(("git", "fetch"), cwd=self.stm32cube_serie_path)
            os_cmd(
                ("git", "reset", "--hard", "master"),
                cwd=self.stm32cube_serie_path,
            )
        else:
            os_cmd(
                ("git", "clone", STM32_CUBE_REPO_BASE + self.serie + ".git"),
                cwd=self.stm32cube_repo_path,
            )

        # get the latest version of cube,
        # with the most recent one created being the last entry.
        os_cmd(("git", "checkout", "master"), cwd=self.stm32cube_serie_path)
        self.version_tag = subprocess.check_output(
            "git tag -l", cwd=self.stm32cube_serie_path
        ).splitlines()
        self.version_tag = [x.decode("utf-8") for x in self.version_tag]
        # Set latest version
        self.latest_version = self.version_tag[-1]

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
                "Error: cannot find version "
                + previous_version
                + " in STM32Cube_repo"
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
        os_cmd(
            (
                "cp",
                "-r",
                str(stm32cube_cmsis_include_path),
                str(temp_cmsis_soc_path),
            )
        )

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
        temp_drivers_include_path = (
            self.stm32cube_temp_serie / "drivers" / "include"
        )
        temp_drivers_include_path.parent.mkdir(parents=True)
        stm32cube_driver_inc = (
            self.stm32cube_serie_path
            / "Drivers"
            / Path(self.stm32_seriexx_upper + "_HAL_Driver")
            / "Inc"
        )
        os_cmd(
            (
                "cp",
                "-r",
                str(stm32cube_driver_inc),
                str(temp_drivers_include_path),
            )
        )

        # except for _hal_conf_template.h
        hal_conf_template = [
            f
            for f in temp_drivers_include_path.iterdir()
            if "hal_conf_template.h" in f.name
        ][0]
        hal_conf_template_fullpath = (
            temp_drivers_include_path / hal_conf_template
        )
        if hal_conf_template_fullpath.is_file():
            hal_conf_fullpath = Path(
                re.sub("_template", r"", str(hal_conf_template_fullpath))
            )
            if hal_conf_fullpath.exists():
                hal_conf_fullpath.unlink()
            hal_conf_template_fullpath.rename(hal_conf_fullpath)

        temp_drivers_src_path = self.stm32cube_temp_serie / "drivers" / "src"
        temp_drivers_src_path.mkdir()
        stm32cube_drivers_src_path = (
            self.stm32cube_serie_path
            / "Drivers"
            / Path(self.stm32_seriexx_upper + "_HAL_Driver")
            / "Src"
        )
        os_cmd(
            (
                "cp",
                "-r",
                str(stm32cube_drivers_src_path) + "/*.*",
                str(temp_drivers_src_path),
            )
        )

    def build_from_current_cube_version(self):
        """Build a commit in temporary dir with STM32Cube version
        corresponding to zephyr current hal version
        """
        # reset the STM32Cube repo to this current version
        os_cmd(
            ("git", "reset", "--hard", self.current_version),
            cwd=self.stm32cube_serie_path,
        )

        # build the zephyr module from the stm32cube
        self.extract_source()
        logging.info(
            "Building module from STM32Cube_repo " + self.current_version
        )

        if not self.stm32cube_temp_serie.parent.exists():
            self.stm32cube_temp_serie.parent.mkdir(parents=True)

        os_cmd(
            ("git", "add", "-A", "stm32cube/" + self.stm32_seriexx + "/*"),
            cwd=self.stm32cube_temp,
        )
        os_cmd(
            ("git", "commit", "-am", '"module' + self.current_version + '"'),
            cwd=self.stm32cube_temp,
        )

    def build_patch_from_current_zephyr_version(self):
        """Build patch between zephyr current hal version and
        corresponding official STM32Cube version
        """
        # clean-up the module
        shutil.rmtree(str(self.stm32cube_temp_serie), onerror=remove_readonly)

        # populate the new repo with this current zephyr module
        os_cmd(
            (
                "cp",
                "-rf",
                str(self.zephyr_module_serie_path),
                str(self.stm32cube_temp_serie),
            )
        )

        # commit this current version module
        os_cmd(("git", "add", "*"), cwd=self.stm32cube_temp)
        os_cmd(("git", "commit", "-am", '"module"'), cwd=self.stm32cube_temp)

        # Remove trailing space
        os_cmd(
            ("git", "rebase", "--whitespace=fix", "HEAD~1"),
            cwd=self.stm32cube_temp,
        )

        # generate a patch for files and _hal.conf.h file in the module
        logging.info(
            "Building patch from " + self.current_version + " to current module"
        )
        os_cmd(
            (
                "git",
                "diff",
                "--ignore-space-at-eol",
                "HEAD~1",
                ">>",
                "module.patch",
            ),
            shell=True,
            cwd=self.stm32cube_temp,
        )

        os_cmd(("dos2unix", "module.patch"), cwd=self.stm32cube_temp)

        hal_conf = (
            self.stm32cube_temp_serie
            / "drivers"
            / "include"
            / Path(self.stm32_seriexx + "_hal_conf.h")
        )
        hal_conf_patch = self.stm32cube_temp / "hal_conf.patch"
        if hal_conf.exists():
            os_cmd(
                (
                    "git",
                    "diff",
                    "HEAD@{1}",
                    "--",
                    str(hal_conf),
                    ">>",
                    str(hal_conf_patch),
                ),
                shell=True,
                cwd=self.stm32cube_temp,
            )
            if hal_conf_patch.stat().st_size == 0:
                hal_conf_patch.unlink()
            else:
                os_cmd(("dos2unix", str(hal_conf_patch)))

    def update_readme(self, make_version, make_commit):
        """Update README file

        Args:
            make_version: latest STM32Cube version.
            make_commit: Commit corresponding to latest STM32Cube version.
        """
        see_release_note = True

        readme_path = self.stm32cube_temp_serie / "README"

        with readme_path.open(mode="r") as readme_prev:
            lines = (x for x in readme_prev.read().splitlines())

        readme_path.unlink()

        # Write README from previous one if exists
        with open(str(readme_path), "w") as readme_file:
            for LineItem in lines:
                # change version nb
                if "status" in LineItem.lower():
                    readme_file.write("Status:\n")
                    readme_file.write("   version {0}\n".format(make_version))
                    next(lines)  # skip next line
                elif "commit" in LineItem.lower():
                    readme_file.write("Commit:\n")
                    readme_file.write("   {0}".format(make_commit))
                    next(lines)  # skip next line
                elif "URL" in LineItem.upper():
                    readme_file.write("URL:\n")
                    readme_file.write(
                        "   https://github.com/STMicroelectronics/"
                        + "STM32Cube{0}\n".format(self.serie)
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
                    readme_file.write("{0}\n".format(LineItem))

            # at the very end of the file :
            if see_release_note:
                readme_file.write("\n   See release_note.html from STM32Cube\n")
            readme_file.flush()

        os_cmd(("dos2unix", str(readme_path)))

    def copy_release_note(self):
        """Copy release_note.html file from STM32Cube to zephyr"""
        release_note_src = self.stm32cube_serie_path / "Release_Notes.html"
        release_note_dst = self.zephyr_module_serie_path / "release_note.html"
        if release_note_dst.exists():
            release_note_dst.unlink()
        if release_note_src.exists:
            release_note_src.rename(release_note_dst)
            os_cmd(("dos2unix", str(release_note_dst)))

    def update_cmakelist(self):
        """Update CMakeLists.txt file"""
        cmakelists_path = self.stm32cube_temp_serie / "CMakeLists.txt"
        if cmakelists_path.exists():
            # build new CMakeLists.txt
            with cmakelists_path.open("r") as cmakelists_old:
                # this line is the copyright line
                first_line = cmakelists_old.readline()
            cmakelists_path.unlink()
        else:
            first_line = ""

        logging.info("Create a new CMakeLists.txt file")

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
                "zephyr_library_sources(soc/system_"
                + self.stm32_seriexx
                + ".c)\n"
            )
            cmakelists_new.write(
                "zephyr_library_sources(drivers/src/"
                + self.stm32_seriexx
                + "_hal.c)\n"
            )
            cmakelists_new.write(
                "zephyr_library_sources(drivers/src/"
                + self.stm32_seriexx
                + "_hal_rcc.c)\n"
            )
            cmakelists_new.write(
                "zephyr_library_sources(drivers/src/"
                + self.stm32_seriexx
                + "_hal_rcc_ex.c)\n"
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
        os_cmd(("dos2unix", str(cmakelists_path)))

    def build_from_latest_version(self):
        """Build a commit in temporary dir with STM32Cube version
        corresponding to zephyr latest hal version
        """
        # reset the STM32Cube repo to this latest version
        os_cmd(
            ("git", "reset", "--hard", self.latest_version),
            cwd=self.stm32cube_serie_path,
        )

        # Get the commit id of this latest version
        self.latest_commit = subprocess.check_output(
            "git rev-parse HEAD", cwd=self.stm32cube_serie_path
        ).decode("utf-8")

        # clear previous version content before populating with latest version
        shutil.rmtree(str(self.stm32cube_temp_serie), onerror=remove_readonly)

        # populate temporary directory with latest version
        self.extract_source()

        # include README and CMakelists files from current zephyr module
        shutil.copy(
            str(self.readme_file_path),
            str(self.stm32cube_temp_serie / "README"),
        )
        shutil.copy(
            str(self.zephyr_module_serie_path / "CMakeLists.txt"),
            str(self.stm32cube_temp_serie / "CMakeLists.txt"),
        )

        # Commit files except log or patch files
        os_cmd(("git", "add", "*"), cwd=self.stm32cube_serie_path)
        os_cmd(("git", "reset", "--", "*.patch"), cwd=self.stm32cube_serie_path)
        os_cmd(("git", "reset", "--", "*.log"), cwd=self.stm32cube_serie_path)
        os_cmd(
            ("git", "commit", "-am", '"module' + self.latest_version + '"'),
            cwd=self.stm32cube_temp_serie,
        )

    def apply_zephyr_patch(self):
        """Apply zephyr stm32 patch to latest stm32Cube version"""
        logging.info("Apply zephyr patches to " + self.latest_version)

        # Update README and CMakeList, copy release note
        self.update_readme(self.latest_version, self.latest_commit)
        self.update_cmakelist()
        self.copy_release_note()

        # Apply previous patch on hal_conf.h file
        if os.path.exists("hal_conf.patch"):
            os_cmd(
                ("git", "apply", "--recount", "--3way", "./hal_conf.patch"),
                cwd=self.stm32cube_temp,
            )
            os.remove("hal_conf.patch")

        # Commit files except log or patch files
        os_cmd(("git", "add", "*"), cwd=self.stm32cube_temp)
        os_cmd(("git", "reset", "--", "*.patch"), cwd=self.stm32cube_temp)
        os_cmd(("git", "reset", "--", "*.log"), cwd=self.stm32cube_temp)
        os_cmd(
            ("git", "commit", "-am", '"module' + self.latest_version + '"'),
            cwd=self.stm32cube_temp,
        )

        # Remove trailing spaces
        os_cmd(
            ("git", "rebase", "--whitespace=fix", "HEAD~1"),
            cwd=self.stm32cube_temp,
        )

        # Generate a patch for each file in the module

        os_cmd(
            ("git", "diff", "HEAD~1", ">>", "new_version.patch"),
            shell=True,
            cwd=self.stm32cube_temp,
        )

        os_cmd(("dos2unix", "new_version.patch"), cwd=self.stm32cube_temp)

        # Copy from stm32cube_temp
        shutil.rmtree(
            str(self.zephyr_hal_stm32_path / "stm32cube" / self.stm32_seriexx),
            onerror=remove_readonly,
        )
        os_cmd(
            (
                "cp",
                "-r",
                str(self.stm32cube_temp_serie),
                str(
                    self.zephyr_hal_stm32_path
                    / "stm32cube"
                    / self.stm32_seriexx
                ),
            )
        )

        # Apply patch from new repo
        module_log_path = self.zephyr_hal_stm32_path / Path(
            "module_" + self.stm32_serie + ".log"
        )

        cmd = (
            "git",
            "apply",
            "--recount",
            "--reject",
            str(self.stm32cube_temp / "module.patch"),
        )
        with open(module_log_path, "w") as output_log:
            if subprocess.call(
                cmd, stderr=output_log, cwd=self.zephyr_hal_stm32_path
            ):
                logging.error(
                    "Error when applying patch to zephyr module: see "
                    + str(module_log_path)
                )

        # Add files but do not commit
        os_cmd(("git", "add", "*"), cwd=self.zephyr_hal_stm32_path)
        os_cmd(
            ("git", "reset", "--", "*.patch"), cwd=self.zephyr_hal_stm32_path
        )
        os_cmd(("git", "reset", "--", "*.log"), cwd=self.zephyr_hal_stm32_path)
        os_cmd(("git", "reset", "--", "*.rej"), cwd=self.zephyr_hal_stm32_path)
        logging.info(
            "README file : --> please check that the Patch list "
            + "is still valid"
        )

    def merge_commit(self):
        """Apply zephyr stm32 patch to latest stm32Cube version"""
        # Merge & commit if needed
        if self.force:
            logging.info("Force commit module ")
            # to clean the .rej files, uncomment line: reject()
            # reject()

            commit_file_path = self.zephyr_module_serie_path / "commit.msg"
            with open(commit_file_path, "w") as commit:
                commit.write(
                    "stm32cube: update "
                    + self.stm32_serie
                    + " to version "
                    + self.latest_version.upper()
                    + "\n"
                )

                commit.write("\n")
                commit.write(
                    "Update Cube version for "
                    + self.stm32_seriexx_upper
                    + " series"
                    + "\n"
                )
                commit.write("on https://github.com/STMicroelectronics" + "\n")
                commit.write("from version " + self.current_version + "\n")
                commit.write("to version " + self.latest_version + "\n")
            os_cmd(
                ("git", "commit", "-as", "-F", commit_file_path),
                cwd=self.zephyr_module_serie_path,
            )
            os_cmd(
                ("git", "rebase", "--whitespace=fix", "HEAD~1"),
                cwd=self.zephyr_module_serie_path,
            )
            Path(commit_file_path).unlink()

    def reject(self):
        """Clean *.rej files"""
        reject_files = [
            f for f in self.zephyr_module_serie_path.glob("**/*.rej")
        ]
        if reject_files:
            for f in reject_files:
                f.unlink()

    def cleanup_stm32cube_repo(self):
        """clean the STM32Cube repo"""
        os_cmd(
            ("git", "reset", "--hard", "HEAD"), cwd=self.stm32cube_serie_path
        )

    def clean_files(self):
        """Clean repo file if required"""
        # Remove temporary files unconditionally
        os.chdir(os.getenv("HOME"))
        shutil.rmtree(str(self.stm32cube_temp), onerror=remove_readonly)

        # remove STM32Cube repo only if required
        if not self.noclean:
            self.cleanup_stm32cube_repo()
            shutil.rmtree(
                str(self.stm32cube_repo_path), onerror=remove_readonly
            )
        else:
            os_cmd(
                ("git", "reset", "--hard", "HEAD"),
                cwd=self.stm32cube_serie_path,
            )

    def update_stm32_hal_serie(self):
        """Update one single STM32Cube"""
        # 1) clone full repo from github : get the repo STM32CubeXX
        self.clone_cube_repo()

        # 2) prepare a repo where to store module versions
        os_cmd(("git", "init"), cwd=self.stm32cube_temp)

        # 3) get the version of cube which is in the zephyr module
        self.current_version = self.get_zephyr_current_version()
        logging.info(
            "Version "
            + self.current_version
            + " is the original version for "
            + self.zephyr_module_serie_path.name
        )

        # do not process if versions are similar
        if (self.current_version in self.latest_version) or (
            self.latest_version in self.current_version
        ):
            logging.warning("Versions are identical: abandoned")
            self.clean_files()
            return

        # 4) build the module from this previous version
        self.build_from_current_cube_version()

        # 5) build the module from the current version
        self.build_patch_from_current_zephyr_version()

        # 6) build the module from this latest version
        self.build_from_latest_version()

        # 7) apply zephyr patch : in the zephyr module repo
        self.apply_zephyr_patch()

        # 8) merge and commit if needed
        self.merge_commit()

        # 9) clean
        self.clean_files()
        logging.info("Done " + self.stm32_serie)
