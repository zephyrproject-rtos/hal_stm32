#ifndef _ADV_BUFF_ALLOC_H_
#define _ADV_BUFF_ALLOC_H_

/** @defgroup ADV_DATA_TYPES
  * @{
  */
#define ADV_DATA                0
#define SCAN_RESP_DATA          1
#define PERIODIC_ADV_DATA       2
/**
  * @}
  */

void adv_buff_init(void);
uint8_t *adv_buff_alloc(uint8_t handle, uint16_t buffer_len, uint8_t extend, uint16_t *old_buff_len, uint8_t data_type);
void adv_buff_free_current(uint8_t handle, uint8_t data_type);
void adv_buff_free_next(uint8_t handle, uint8_t data_type);
void adv_buff_free_old(uint8_t *buff);
void adv_buff_activate_next(uint8_t handle, uint8_t data_type);
void adv_buff_deactivate_current(uint8_t handle, uint8_t data_type);
uint8_t new_buff_pending(uint8_t handle, uint8_t data_type);

#endif /* _ADV_BUFF_ALLOC_H_ */
