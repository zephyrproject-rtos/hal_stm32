# Copyright (c) 2024 STMicroelectronics
#
# SPDX-License-Identifier: Apache-2.0

zephyr_include_directories(hci)

zephyr_sources(hci/hw_ipcc.c)
zephyr_sources(hci/shci.c)
zephyr_sources(hci/shci_tl.c)
zephyr_sources(hci/shci_tl_if.c)
zephyr_sources(hci/stm_list.c)
zephyr_sources(hci/tl_mbox.c)
