#ifndef _ADV_BUFF_ALLOC_TINY_H_
#define _ADV_BUFF_ALLOC_TINY_H_

/* More buffers for advertising and scan response data are used to
  allow application to change data on the fly even in the middle of an advertising event.
  aci_hal_adv_scan_resp_data_update_event is used to be sure that the new buffer where
  advertising data will be copied is not currently used by the Link Layer.
  In a middle of an advertising event, the stack may not free the old buffer: in this
  case consecutive updates of the advertising data may cause a BLE_ERROR_CONTROLLER_BUSY. */
#define NUM_BUFFERS 4

void adv_tiny_buff_init(void);

void * adv_tiny_buff_alloc(void);

void adv_tiny_buff_free(void * p);

#endif /* _ADV_BUFF_ALLOC_TINY_H_ */
