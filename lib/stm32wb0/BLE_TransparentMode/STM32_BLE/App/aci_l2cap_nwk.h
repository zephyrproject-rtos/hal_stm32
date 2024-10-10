
#ifndef ACI_L2CAP_NWK_H
#define ACI_L2CAP_NWK_H

void aci_l2cap_cos_sdu_data_rx_nwk_event(uint16_t Connection_Handle,
                                         uint16_t CID,
                                         uint16_t RX_Credit_Balance,
                                         uint16_t SDU_Length,
                                         uint8_t SDU_Data[]);

void aci_l2cap_cos_sdu_data_tx_nwk_event(uint16_t Connection_Handle,
                                         uint16_t CID,
                                         uint16_t SDU_Length,
                                         uint16_t TX_Credit_Balance);

#endif
