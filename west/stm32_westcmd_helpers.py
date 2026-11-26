# SPDX-FileCopyrightText: Copyright (c) 2025-2026 STMicroelectronics
# SPDX-License-Identifier: Apache-2.0

from west.commands import WestCommand


def SC_do_add_parser(self: WestCommand,
                     subparser_help_text: str,
                     parser_adder):
    """
    do_add_parser implementation for STM32Command subclasses.
    This avoids repeating boilerplate across commands.

    NOTE: even though "self" is typed as WestCommand, it must actually be
    a subclass of STM32Command which provides the "subcommands" field.
    """
    p = parser_adder.add_parser(self.name,
                                help=self.help,
                                description=self.description)

    sp = p.add_subparsers(dest='command',
                          required=True,
                          help=subparser_help_text)

    for sc in self.subcommands:  # type: ignore
        sc.add_parser(sp)

    return p


def SC_do_run(self: WestCommand, args, unknown):
    """
    do_run implementation for STM32Command subclasses.
    This dispatches the call to the appropriate subcommand based on args.command.
    """
    all_subcommands = self.subcommands  # type: ignore
    chosen_sc = next(filter(lambda sc: args.command == sc.name, all_subcommands))
    chosen_sc.run(args, unknown, self.topdir, self.manifest, self.config)


class STM32Command(WestCommand):
    """
    Abstract base class for top-level STM32 west commands.

    Only top-level commands should inherit from this; custom subcommands should inherit
    from WestCommand instead (and be attached to an STM32Command).
    """
