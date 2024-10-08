#ifndef __INC_WHAD_TRANSPORT_H
#define __INC_WHAD_TRANSPORT_H

#include "types.h"
#include "ringbuf.h"

#define WHAD_TRANSPORT_MSG_MAXSIZE  1024

#ifdef __cplusplus
extern "C" {
#endif

/* Define callback function types. */
typedef void (*whad_transport_data_send_buffer_cb_t)(uint8_t *p_buffer, int size);
typedef void (*whad_transport_message_cb_t)(Message *p_msg);

typedef enum {
    WHAD_TRANSPORT_IDLE,
    WHAD_TRANSPORT_SENDING
} whad_transport_state_t;

/**
 * @struct whad_transport_cfg_t
 * @brief WHAD Transport configuration structure.
 * 
 * @var whad_transport_cfg_t::max_txbuf_size
 * Maximum size of transmission buffer.
 * @var whad_transport_cfg_t::pfn_data_send_buffer
 * Pointer to a callback function that sends data over UART.
 */
typedef struct {
    /* Max transmission buffer size. */
    int max_txbuf_size;

    /* Callbacks. */
    whad_transport_data_send_buffer_cb_t pfn_data_send_buffer;
    /* whad_transport_message_cb_t pfn_message_cb; */
} whad_transport_cfg_t;

/**
 * WHAD transport state structure.
 */

typedef struct {
    /* WHAD message. */
    Message msg;

    /* State. */
    whad_transport_state_t state;

    /* RX and TX buffers. */
    whad_ringbuf_t rx_buf; /* Transport RX ring buffer */
    whad_ringbuf_t tx_buf; /* Transport TX ring buffer */

    /* Callbacks. */
    whad_transport_cfg_t config;
} whad_transport_t;


void whad_transport_init(whad_transport_cfg_t *p_transport_cfg);
whad_result_t whad_transport_data_received(uint8_t *p_data, int size);
whad_result_t whad_transport_transfer(void);
whad_result_t whad_transport_send_pending(void);
void whad_transport_data_sent(void);
whad_result_t whad_transport_send_byte(uint8_t data);
int whad_transport_send(uint8_t *p_data, int size);

whad_result_t whad_transport_get_message(uint8_t *p_buffer, int *p_size);
whad_result_t whad_transport_send_message(uint8_t *p_message, int size);

int whad_transport_get_txbuf_size(void);
int whad_transport_get_rxbuf_size(void);

#ifdef __cplusplus
}
#endif

#endif /* __INC_WHAD_TRANSPORT_H */