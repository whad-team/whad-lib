#include "whad.h"

static uint8_t g_rx_message_buf[WHAD_MESSAGE_MAX_SIZE];
static uint8_t g_tx_message_buf[WHAD_MESSAGE_MAX_SIZE];

/***
 * WHAD driver
 */

void whad_init(whad_transport_cfg_t *p_transport_cfg)
{
    /* Initialize transport. */
    whad_transport_init(p_transport_cfg);
}

whad_result_t whad_send_message(Message *p_msg)
{
    /* Serialize our message. */
    pb_ostream_t stream = pb_ostream_from_buffer(g_tx_message_buf, 1024);
    if (pb_encode(&stream, Message_fields, p_msg))
    {
        if (stream.bytes_written >0)
        {
            /* Send our serialized message to transport. */
            return whad_transport_send_message(g_tx_message_buf, stream.bytes_written);
        }
        else
        {
            return WHAD_ERROR;
        }
    }
    else
        return WHAD_ERROR;
}


whad_result_t whad_get_message(Message *p_msg)
{
    whad_result_t result;
    int message_size = WHAD_MESSAGE_MAX_SIZE;

    result = whad_transport_get_message(g_rx_message_buf, &message_size);
    if (result == WHAD_SUCCESS)
    {
        /* Do we have a message to parse ? */
        if (message_size > 0)
        {
            /* Parse message. */
            pb_istream_t stream = pb_istream_from_buffer(g_rx_message_buf, message_size);

            /* Now we are ready to decode the message. */
            if (pb_decode(&stream, Message_fields, p_msg))
            {
                /* Success, we got a message. */
                return WHAD_SUCCESS;
            }
            else
            {
                /* Fail. */
                return WHAD_ERROR;
            }
        }
        else
        {
            /* No message. */
            return WHAD_NONE;
        }
    }
    else
    {
        /* Failure. */
        return WHAD_ERROR;
    }
}


whad_msgtype_t whad_get_message_type(Message *p_msg)
{
    whad_msgtype_t msg_type = WHAD_MSGTYPE_UNKNOWN;

    switch (p_msg->which_msg)
    {
        case Message_generic_tag:
            msg_type = WHAD_MSGTYPE_GENERIC;
            break;

        case Message_discovery_tag:
            msg_type = WHAD_MSGTYPE_DISCOVERY;
            break;

        case Message_ble_tag:
        case Message_esb_tag:
        case Message_phy_tag:
        case Message_unifying_tag:
        case Message_zigbee_tag:
            msg_type = WHAD_MSGTYPE_DOMAIN;
            break;

        default:
            break;
    }

    /* Return message type. */
    return msg_type;
}

whad_domain_t whad_get_message_domain(Message *p_msg)
{
    whad_domain_t domain = DOMAIN_NONE;

    switch (p_msg->which_msg)
    {
        case Message_ble_tag:
            domain = DOMAIN_BTLE;
            break;

        case Message_esb_tag:
            domain = DOMAIN_ESB;
            break;

        case Message_phy_tag:
            domain = DOMAIN_PHY;
            break;

        case Message_unifying_tag:
            domain = DOMAIN_LOGITECH_UNIFYING;
            break;

        case Message_zigbee_tag:
            domain = DOMAIN_ZIGBEE;
            break;

        default:
            break;
    }

    /* Return guessed domain. */
    return domain;
}