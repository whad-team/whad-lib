#include "transport.h"

static whad_transport_t gw_transport;
static uint8_t tx_buf[WHAD_RINGBUF_MAX_SIZE];


/**
 * @brief   Initialize WHAD transport API.
 * @param   p_transport_cfg Pointer to a `whad_transport_cfg_t` structure holding the
 *                          configuration to use
 */

void whad_transport_init(whad_transport_cfg_t *p_transport_cfg)
{
    /* Initialiaze protobuf message. */
    memset(&gw_transport.msg, 0, sizeof(Message));

    /* Initialize RX and TX ring buffers. */
    whad_ringbuf_init(&gw_transport.rx_buf);
    whad_ringbuf_init(&gw_transport.tx_buf);

    /* Initialize callbacks. */
    gw_transport.config.max_txbuf_size = p_transport_cfg->max_txbuf_size;
    gw_transport.config.pfn_data_send_buffer = p_transport_cfg->pfn_data_send_buffer;

    /* Set state to idle. */
    gw_transport.state = WHAD_TRANSPORT_IDLE;
}


/**
 * @brief   WHAD incoming data callback.
 * 
 * This callback must be called to notify WHAD a byte has been received.
*/
whad_result_t whad_transport_data_received(uint8_t *p_data, int size)
{
    int i;

    /* Enqueue data in RX buffer. */
    for (i=0; i<size; i++)
    {
        if (whad_ringbuf_push(&gw_transport.rx_buf, p_data[i]) == WHAD_RINGBUF_FULL)
        {
            return WHAD_RINGBUF_FULL;
        }
    }

    /* Success. */
    return WHAD_SUCCESS;
}


whad_result_t whad_transport_send_pending(void)
{
    int buf_size;

    /* Cannot send if we are already sending. */
    if (gw_transport.state != WHAD_TRANSPORT_IDLE)
    {
        return WHAD_ERROR;
    }

    /* Make sure we have a working callback. */
    if (gw_transport.config.pfn_data_send_buffer != NULL)
    {
        /* Compute buffer size. */
        buf_size = whad_ringbuf_get_size(&gw_transport.tx_buf);
        if (buf_size > 0)
        {
            if (buf_size > gw_transport.config.max_txbuf_size)
            {
                /* Cap buf_size to max_txbuf_size. */
                buf_size = gw_transport.config.max_txbuf_size;
            }

            /* Read buffer from TX queue. */
            if (whad_ringbuf_copy(&gw_transport.tx_buf, tx_buf, buf_size) == WHAD_SUCCESS)
            {
                /* Send it through UART. */
                gw_transport.state = WHAD_TRANSPORT_SENDING;
                gw_transport.config.pfn_data_send_buffer(tx_buf, buf_size);

                /* Skip sent bytes. */
                whad_ringbuf_skip(&gw_transport.tx_buf, buf_size);
            }
            else
                return WHAD_ERROR;
        }
        else
            return WHAD_RINGBUF_EMPTY;
    }

    return WHAD_SUCCESS;
}


/**
 * @brief Retrieve a WHAD message from RX queue, if any
 * 
 * This function must be called regularly to handle incoming WHAD
 * messages.
 * 
 * @param   p_buffer  Pointer to a buffer large enough to receive data
 * @param   p_size    Pointer to an integer specifying the size of the destination buffer
 * @returns WHAD_SUCCESS on success, WHAD_ERROR otherwise.
 */

whad_result_t whad_transport_get_message(uint8_t *p_buffer, int *p_size)
{
    uint8_t header[4];
    uint16_t size;

    /* Check if we have a complete message. */
    if (whad_ringbuf_get_size(&gw_transport.rx_buf) >= 4)
    {
        /* Parse header. */
        if (whad_ringbuf_copy(&gw_transport.rx_buf, header, 4) == WHAD_ERROR)
        {
            *p_size = 0;
            return WHAD_ERROR;
        }

        /* Check magic */
        if ((header[0] == 0xAC) && (header[1] == 0xBE))
        {
            /* Best case scenario, deduce size and build message. */
            size = header[2] | (header[3] << 8);

            /* Ensure our destination buffer is large enough. */
            if (*p_size >= size)
            {
                /* Do we have a complete message ? */
                if (whad_ringbuf_get_size(&gw_transport.rx_buf) >= (size + 4))
                {
                    /* We have enough, extract message (skip header). */
                    whad_ringbuf_skip(&gw_transport.rx_buf, 4);
                    whad_ringbuf_copy(&gw_transport.rx_buf, p_buffer, size);
                    whad_ringbuf_skip(&gw_transport.rx_buf, size);

                    /* Return message size. */
                    *p_size = size;

                    /* Success. */
                    return WHAD_SUCCESS;
                }
            }
            else
            {
                /* Provide the expected buffer size. */
                *p_size = size;
                return WHAD_ERROR;
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

    /* Nothing to process. */
    *p_size = 0;
    return WHAD_SUCCESS;
}

whad_result_t whad_transport_send_message(uint8_t *p_message, int size)
{
    uint8_t header[4];
    int nb_bytes_sent;

    if (size == 0)
        return WHAD_SUCCESS;

    /* Write header. */
    header[0] = '\xAC';
    header[1] = '\xBE';
    header[2] = (size & 0xff);
    header[3] = (size >> 8) & 0xff;
    
    /* Send header, then message payload. */
    nb_bytes_sent = whad_transport_send(header, 4);
    if (nb_bytes_sent < 4)
    {
        /* Could not send the whole header. */
        return WHAD_ERROR;
    }

    nb_bytes_sent = whad_transport_send(p_message, size);
    if (nb_bytes_sent < size)
    {
        /* Could not send the whole buffer. */
        return WHAD_ERROR;
    }

    /* Success. */
    return WHAD_SUCCESS;
}

/**
 * @brief   WHAD transport data sent callback.
 * 
 * This function must be called whenever a transmit operation has ended in
 * order for WHAD to continue sending pending data (if any).
 */

void whad_transport_data_sent(void)
{
    if (gw_transport.state == WHAD_TRANSPORT_SENDING)
    {
        gw_transport.state = WHAD_TRANSPORT_IDLE;
    }
}


/**
 * @brief   Add a data byte to WHAD transport TX buffer.
 * @param   data    Byte to send
 * @returns WHAD_SUCCESS on success, WHAD_ERROR otherwise.
 */

whad_result_t whad_transport_send_byte(uint8_t data)
{
    /* Enqueue data in TX buffer. */
    return whad_ringbuf_push(&gw_transport.tx_buf, data);
}


/**
 * @brief   Add a buffer to WHAD transport TX buffer
 * @param   p_data  Pointer to a buffer to send
 * @param   size    Number of bytes to send
 * @returns WHAD_SUCCESS on success, WHAD_ERROR otherwise
 */

int whad_transport_send(uint8_t *p_data, int size)
{
    int i=0;

    /* Enqueue as much data as possible. */
    while (i<size)
    {
        if (whad_ringbuf_push(&gw_transport.tx_buf, p_data[i++]) == WHAD_ERROR)
            break;
    }

    /* Return the number of bytes added to the send queue. */
    return i;
}

int whad_transport_get_txbuf_size(void)
{
    return whad_ringbuf_get_size(&gw_transport.tx_buf);
}

int whad_transport_get_rxbuf_size(void)
{
    return whad_ringbuf_get_size(&gw_transport.rx_buf);
}