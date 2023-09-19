#ifndef __INC_WHAD_TRANSPORT_H
#define __INC_WHAD_TRANSPORT_H

#include <whad.h>

#define WHAD_TRANSPORT_MSG_MAXSIZE  1024

typedef void (*whad_transport_data_send_cb_t)(uint8_t data);
typedef void (*whad_transport_message_cb_t)(Message *p_msg);

typedef enum {
    WHAD_TRANSPORT_IDLE,
    WHAD_TRANSPORT_SENDING
} whad_transport_state_t;

typedef struct {
    /* WHAD message. */
    Message msg;

    /* State. */
    whad_transport_state_t state;

    /* RX and TX buffers. */
    whad_ringbuf_t rx_buf;
    whad_ringbuf_t tx_buf;

    /* Callbacks. */
    whad_transport_data_send_cb_t pfn_data_send;
    whad_transport_message_cb_t pfn_message_cb;
} whad_transport_t;


#endif /* __INC_WHAD_TRANSPORT_H */