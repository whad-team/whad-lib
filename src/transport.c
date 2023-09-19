#include "transport.h"

static uint8_t gw_transport_message_buf[WHAD_TRANSPORT_MSG_MAXSIZE];
static whad_transport_t gw_transport;


void whad_transport_init(void)
{
    /* Initialiaze protobuf message. */
    memset(&gw_transport.msg, 0, sizeof(Message));

    /* Initialize RX and TX ring buffers. */
    whad_ringbuf_init(&gw_transport.rx_buf);
    whad_ringbuf_init(&gw_transport.tx_buf);

    /* Initialize callbacks. */
    gw_transport.pfn_data_send = NULL;
    gw_transport.pfn_message_cb = NULL;

    /* Set state to idle. */
    gw_transport.state = WHAD_TRANSPORT_IDLE;
}

whad_result_t whad_transport_data_received(uint8_t data)
{
    /* Enqueue data in RX buffer. */
    return whad_ringbuf_push(&gw_transport.rx_buf, data);
}


whad_result_t whad_transport_transfer(void)
{
    int i;
    uint8_t data;
    uint8_t header[4];
    uint16_t size;

    /* Check if we have a complete message. */
    if (whad_ringbuf_get_size(&gw_transport.rx_buf) >= 4)
    {
        /* Parse header. */
        if (whad_ringbuf_copy(&gw_transport.rx_buf, header, 4) == WHAD_ERROR)
            return WHAD_ERROR;

        /* Check magic */
        if ((header[0] == 0xAC) && (header[1] == 0xBE))
        {
            /* Best case scenario, deduce size and build message. */
            size = header[2] | (header[3] << 8);

            /* Do we have a complete message ? */
            if (whad_ringbuf_get_size(&gw_transport.rx_buf) >= (size + 4))
            {
                /* We have enough, extract message (skip header). */
                whad_ringbuf_skip(&gw_transport.rx_buf, 4);
                whad_ringbuf_copy(&gw_transport.rx_buf, gw_transport_message_buf, size);
                whad_ringbuf_skip(&gw_transport.rx_buf, size);

                /* TODO: Parse message and forward to user. */
            }
        }
        else if (header[1] == 0xAC) {
            whad_ringbuf_skip(&gw_transport.rx_buf, 1);
        }
        else
        {
            whad_ringbuf_skip(&gw_transport.rx_buf, 2);
        }

    }


    /* Start async sending if required. */
    if ((whad_ringbuf_get_size(&gw_transport.tx_buf) > 0) && (gw_transport.state == WHAD_TRANSPORT_IDLE))
    {
        if (whad_ringbuf_pull(&gw_transport.tx_buf, &data) == WHAD_SUCCESS)
        {
            /* Send one byte from tx buffer. */
            if (gw_transport.pfn_data_send != NULL)
            {
                gw_transport.state = WHAD_TRANSPORT_SENDING;
                gw_transport.pfn_data_send(data);
            }
            else
                return WHAD_ERROR;
        }
    }

    /* Success. */
    return WHAD_SUCCESS;
}

void whad_transport_data_sent(void)
{
    if (gw_transport.state == WHAD_TRANSPORT_SENDING)
    {
        gw_transport.state = WHAD_TRANSPORT_IDLE;
    }
}

whad_result_t whad_transport_send_byte(uint8_t data)
{
    /* Enqueue data in TX buffer. */
    return whad_ringbuf_push(&gw_transport.tx_buf, data);
}

int whad_transport_send(uint8_t *p_data, int size)
{
    int i=0;

    /* Enqueue as much data as possible. */
    while (whad_ringbuf_push(&gw_transport.tx_buf, p_data[i++]) == WHAD_SUCCESS);

    /* Return the number of bytes added to the send queue. */
    return i;
}

