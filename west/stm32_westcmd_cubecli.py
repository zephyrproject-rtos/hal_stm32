# SPDX-FileCopyrightText: Copyright (c) 2025-2026 STMicroelectronics
# SPDX-License-Identifier: Apache-2.0
"""
west commands wrapping the STM32CubeCLI tool
"""
import shutil
import subprocess
from pathlib import Path

from stm32_westcmd_helpers import STM32Command


class STM32ToolsInstallCommand(STM32Command):
    """
    Installs STM32 tools used in Zephyr environment:
     - STM32CubeProgrammer
     - ST-Link GDB Server
    """
    INSTALL_URL = ("https://dev.st.com/stm32cube-docs/stm32cubecli/"
                   "latest/en/docs/markup/STM32CubeCLI_Getting_Started/"
                   "STM32CubeCLI_Installation.html")

    STM32CUBEPROGRAMMER_BUNDLE_NAME = "programmer"

    ST_LINK_GDB_SERVER_BUNDLE_NAME = "stlink-gdbserver"

    def __init__(self):
        super().__init__(
            'tools-install',
            'Installs STM32 tools used in Zephyr environment',
            self.__doc__,  # type: ignore
            accepts_unknown_args=False)

    def do_add_parser(self, parser_adder):
        parser = parser_adder.add_parser(self.name,
                                         help=self.help,
                                         description=self.description)
        parser.add_argument('--pin', action='store_true',
                            help="Create `cube` project and pin tool versions")
        parser.add_argument('--programmer-version',
                            help="Version of STM32CubeProgrammer to download")
        parser.add_argument('--gdb-server-version',
                            help="Version of ST-Link GDB Server to download")

        return parser

    def _call_cli(self, cli_exe_path: str, cmd: str|list[str]):  # noqa: E227
        self.dbg(f"Running command: 'cube {cmd}'")
        try:
            if isinstance(cmd, str):
                cmd = cmd.split()
            if (status := subprocess.call([cli_exe_path] + cmd)) != 0:
                self.die(f"STM32CubeCLI returned non-zero status code {status}")
        except subprocess.TimeoutExpired:
            self.die(f"Command 'cube {cmd}' timed out")

    def do_run(self, args, unknown):
        if not (cube_tool := shutil.which("cube")):
            self.die("Could not find STM32CubeCLI in PATH.\n"
                     f"Refer to {self.INSTALL_URL} for the installation procedure.")

        if args.pin and not Path("./.settings/bundles.store.json").is_file():
            # Create STM32CubeCLI project if it doesn't exist
            cwd = Path('.').resolve()
            self.banner(f"Creating STM32CubeCLI project in {cwd}")
            self._call_cli(cube_tool, "bundle init --project")

        bundle_install_args = ["bundle", "install"]

        if args.pin:
            # Use --project flag to indicate bundles should be installed in project.
            # This pins the specific version we install in the project, which will
            # be picked up by STM32CubeCLI when actual commands are invoked.
            bundle_install_args.append("--project")

        programmer = self.STM32CUBEPROGRAMMER_BUNDLE_NAME
        if args.programmer_version is not None:
            programmer += f'@{args.programmer_version}'
        bundle_install_args.append(programmer)

        gdbserver = self.ST_LINK_GDB_SERVER_BUNDLE_NAME
        if args.gdb_server_version is not None:
            gdbserver += f'@{args.gdb_server_version}'
        bundle_install_args.append(gdbserver)

        self.banner("Installing STM32CubeProgrammer and ST-Link GDB Server")
        self._call_cli(cube_tool, bundle_install_args)
