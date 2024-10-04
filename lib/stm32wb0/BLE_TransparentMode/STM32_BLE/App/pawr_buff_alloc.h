#ifndef _PAWR_BUFF_ALLOC_H_
#define _PAWR_BUFF_ALLOC_H_

/* Maximum size of data in a subevent of PAwR.
  This number must be kept to at least 249 for full compliance with standard HCI.
  It may be reduced if application does not need the maximum data size. */
#define MAX_PAWR_SUBEVENT_DATA_SIZE             249

/* Maximum size of data in a response slot of a PAwR subevent.
  This number must be kept to at least 247 for full compliance with standard HCI.
  It may be reduced if application does not need the maximum data size. */
#define MAX_PAWR_RESPONSE_DATA_SIZE             247

/* Maximum number of response data that can be queued for transmission.
   This BLE stack allows up to 8 response data packets in the queue.  */
#define MAX_PAWR_RESPONSE_SUBEVENT_COUNT        8

void pawr_buff_init(void);
void pawr_buff_free(void * p, uint8_t t);
void * pawr_buff_subevent_alloc(void);
void * pawr_buff_resp_alloc(void);
uint8_t pawr_buff_subevent_num_available(void);

#endif /* _PAWR_BUFF_ALLOC_H_ */
