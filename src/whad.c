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

/**
 * @brief   Free a WHAD message's dynamically allocated resources.
 * 
 * @param[in]   p_msg   Pointer to a WHAD message
 */

void whad_free_message_resources(Message *p_msg)
{
    switch (whad_get_message_type(p_msg))
    {
        case WHAD_MSGTYPE_DOMAIN:
            switch (whad_get_message_domain(p_msg))
            {
                case DOMAIN_PHY:
                    whad_phy_message_free(p_msg);
                    break;

                default:
                    break;
            }
            break;

        default:
            break;
    }
}


/**
 * @brief Send a WHAD message over the communication layer
 * 
 * @param[in]   p_msg        Pointer to a NanoPb message structure
 * @retval      WHAD_ERROR   An error occurred while sending message
 * @retval      WHAD_SUCCESS Message has successfully been queued for transmission
 */

whad_result_t whad_send_message(Message *p_msg)
{
    /* Serialize our message. */
    pb_ostream_t stream = pb_ostream_from_buffer(g_tx_message_buf, 1024);
    if (pb_encode(&stream, Message_fields, p_msg))
    {
        if (stream.bytes_written >0)
        {
            /* Free any dynamically allocated resources.*/
            whad_free_message_resources(p_msg);

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


/**
 * @brief Retrieve a received WHAD message from the communication layer
 * 
 * @param[in]   p_msg        Pointer to a NanoPb message structure
 * @retval      WHAD_ERROR   An error occurred while getting the message
 * @retval      WHAD_SUCCESS Message has successfully been retrieved
 * @retval      WHAD_NONE    No received message to be retrieved
 */

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


/**
 * @brief Retrieve the message type of a given message
 * 
 * @param[in]   p_msg        Pointer to a NanoPb message structure
 * @return      Message type
 */

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
        case Message_dot15d4_tag:
            msg_type = WHAD_MSGTYPE_DOMAIN;
            break;

        default:
            break;
    }

    /* Return message type. */
    return msg_type;
}


/**
 * @brief Retrieve the domain of a domain message
 * 
 * @param[in]   p_msg        Pointer to a NanoPb message structure
 * @return      Message domain
 */

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

        case Message_dot15d4_tag:
            domain = DOMAIN_DOT15D4;
            break;

        default:
            break;
    }

    /* Return guessed domain. */
    return domain;
}