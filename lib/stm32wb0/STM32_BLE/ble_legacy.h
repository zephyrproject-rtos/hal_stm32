/**
  ******************************************************************************
  * @file    ble_legacy.h
  * @author  GPM WBL Application Team
  * @brief   This file contains legacy definitions used for BLE.
  *****************************************************************************
  * @attention
  *
  * Copyright (c) 2026 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  *****************************************************************************
  */

#ifndef BLE_LEGACY_H
#define BLE_LEGACY_H

/* Deprecated names for ACI/HCI commands and events
 */

#define hci_le_read_local_supported_features \
        hci_le_read_local_supported_features_page_0
          
#define hci_le_read_remote_features \
        hci_le_read_remote_features_page_0

#define HCI_LE_READ_REMOTE_FEATURES_COMPLETE_SUBEVT_CODE \
        HCI_LE_READ_REMOTE_FEATURES_PAGE_0_COMPLETE_SUBEVT_CODE

#define hci_le_read_remote_features_complete_event_rp0 \
        hci_le_read_remote_features_page_0_complete_event_rp0

#define hci_le_read_remote_features_complete_event_rp0_s \
        hci_le_read_remote_features_page_0_complete_event_rp0_s


#endif /* BLE_LEGACY_H */
