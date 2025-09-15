/*
 * Copyright (c) 2025 STMicroelectronics
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * 3. Neither the name of STMicroelectronics nor the names of its
 *    contributors may be used to endorse or promote products derived from this
 *    software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY, AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 */

/**
 * @defgroup STM32WBA 802.15.4 interface
 * @{
 *
 */

#ifndef STM32WBA_802154_INTF_H_
#define STM32WBA_802154_INTF_H_

#include <ll_sys.h>
#include <ll_sys_startup.h>
#include <stm32wba_802154_callbacks.h>

#ifdef __cplusplus
extern "C" {
#endif
 /* support CSL transmitter configuration flag, RADIO TX at specific time , 1  supported , 0 not supported */
#define STM32WBA_802154_CSL_TRANSMITTER_ENABLE      CONFIG_MAC_CSL_TRANSMITTER_ENABLE
/* support of CSL receiver configuration flag, RADIO RX at specific time, 1  supported , 0 not supported */
#define STM32WBA_802154_CSL_RECEIVER_ENABLE         CONFIG_MAC_CSL_RECEIVER_ENABLE


/** @} */

#ifdef __cplusplus
}
#endif

#endif /* STM32WBA_802154_INTF_H_ */

/** @} */
