#include <whad.h>
#include <domains/dot15d4.h>

whad_dot15d4_msgtype_t whad_dot15d4_get_message_type(Message *p_message)
{
    whad_dot15d4_msgtype_t msg_type = WHAD_DOT15D4_UNKNOWN;

    /* Ensure it is a BLE message. */
    if (whad_get_message_domain(p_message) == DOMAIN_DOT15D4)
    {
        /* Retrieve the message type. */
        msg_type = (whad_dot15d4_msgtype_t)p_message->msg.dot15d4.which_msg;
    }

    /* Success. */
    return msg_type;
}


/********************************
 * Zigbee messages
 *******************************/

/**
 * @brief   Create a SetNodeAddrCmd message
 *
 * @param[in]   p_message   Pointer to a NanoPb Message structure
 * @param[in]   p_addr      Pointer to a whad_dot15d4_address_t structure containing the address
 *
 * @retval          WHAD_SUCCESS        Success.
 * @retval          WHAD_ERROR          Invalid message or address pointer.
 **/

whad_result_t whad_dot15d4_set_node_address(Message *p_message, whad_dot15d4_address_t *p_addr)
{
    /* Sanity checks. */
    if ((p_message == NULL) || (p_addr))
    {
        return WHAD_ERROR;
    }

    p_message->which_msg = Message_dot15d4_tag;
    p_message->msg.dot15d4.which_msg = dot15d4_Message_set_node_addr_tag;

    p_message->msg.dot15d4.msg.set_node_addr.address_type = p_addr->type;
    p_message->msg.dot15d4.msg.set_node_addr.address = p_addr->address;

    /* Success. */
    return WHAD_SUCCESS;
}


/**
 * @brief   Parse a SetNodeAddrCmd message
 *
 * @param[in]       p_message   Pointer to a NanoPb Message structure
 * @param[in,out]   p_addr      Pointer to a whad_dot15d4_address_t structure
 *
 * @retval          WHAD_SUCCESS        Success.
 * @retval          WHAD_ERROR          Invalid message or address pointer.
 **/

whad_result_t whad_dot15d4_set_node_address_parse(Message *p_message, whad_dot15d4_address_t *p_addr)
{
    /* Sanity checks. */
    if ((p_message == NULL) || (p_addr == NULL) || (p_addr == NULL))
    {
        return WHAD_ERROR;
    }

    p_addr->address = p_message->msg.dot15d4.msg.set_node_addr.address;
    p_addr->type = p_message->msg.dot15d4.msg.set_node_addr.address_type;

    /* Success. */
    return WHAD_SUCCESS;
}


/**
 * @brief   Create a SniffCmd message
 *
 * @param[in]   p_message   Pointer to a NanoPb Message structure
 * @param[in]   channel     Channel to sniff
 * 
 * @retval          WHAD_SUCCESS        Success.
 * @retval          WHAD_ERROR          Invalid message or address pointer.
 **/

whad_result_t whad_dot15d4_sniff(Message *p_message, uint32_t channel)
{
    /* Sanity checks. */
    if (p_message == NULL)
    {
        return WHAD_ERROR;
    }

    p_message->which_msg = Message_dot15d4_tag;
    p_message->msg.dot15d4.which_msg = dot15d4_Message_sniff_tag;

    p_message->msg.dot15d4.msg.sniff.channel = channel;

    /* Success. */
    return WHAD_SUCCESS;
}


/**
 * @brief   Parse a SniffCmd message
 *
 * @param[in]       p_message   Pointer to a NanoPb Message structure
 * @param[in,out]   p_channel   Pointer to an integer that will contain the extracted
 *                              channel value
 *
 * @retval          WHAD_SUCCESS        Success.
 * @retval          WHAD_ERROR          Invalid message or address pointer.
 **/

whad_result_t whad_dot15d4_sniff_parse(Message *p_message, uint32_t *p_channel)
{
    /* Sanity checks. */
    if ((p_message == NULL) || (p_channel == NULL))
    {
        return WHAD_ERROR;
    }

    *p_channel = p_message->msg.dot15d4.msg.sniff.channel;

    /* Success. */
    return WHAD_SUCCESS;
}


/**
 * @brief   Create a JamCmd message
 *
 * @param[in]   p_message   Pointer to a NanoPb Message structure
 * @param[in]   channel     Channel to sniff
 * 
 * @retval          WHAD_SUCCESS        Success.
 * @retval          WHAD_ERROR          Invalid message or address pointer.
 **/

whad_result_t whad_dot15d4_jam(Message *p_message, uint32_t channel)
{
    /* Sanity checks. */
    if (p_message == NULL)
    {
        return WHAD_ERROR;
    }

    p_message->which_msg = Message_dot15d4_tag;
    p_message->msg.dot15d4.which_msg = dot15d4_Message_jam_tag;

    p_message->msg.dot15d4.msg.jam.channel = channel;

    /* Success. */
    return WHAD_SUCCESS;
}


/**
 * @brief   Parse a JamCmd message
 *
 * @param[in]       p_message   Pointer to a NanoPb Message structure
 * @param[in,out]   p_channel   Pointer to an integer that will contain the extracted
 *                              channel value
 *
 * @retval          WHAD_SUCCESS        Success.
 * @retval          WHAD_ERROR          Invalid message or address pointer.
 **/

whad_result_t whad_dot15d4_jam_parse(Message *p_message, uint32_t *p_channel)
{
    /* Sanity checks. */
    if ((p_message == NULL) || (p_channel == NULL))
    {
        return WHAD_ERROR;
    }

    *p_channel = p_message->msg.dot15d4.msg.jam.channel;

    /* Success. */
    return WHAD_SUCCESS;
}


/**
 * @brief   Create a EnergyDetectionCmd message
 *
 * @param[in]   p_message   Pointer to a NanoPb Message structure
 * @param[in]   channel     Channel to sniff
 * 
 * @retval          WHAD_SUCCESS        Success.
 * @retval          WHAD_ERROR          Invalid message or address pointer.
 **/

whad_result_t whad_dot15d4_energy_detect(Message *p_message, uint32_t channel)
{
    /* Sanity checks. */
    if (p_message == NULL)
    {
        return WHAD_ERROR;
    }

    p_message->which_msg = Message_dot15d4_tag;
    p_message->msg.dot15d4.which_msg = dot15d4_Message_ed_tag;

    p_message->msg.dot15d4.msg.ed.channel = channel;

    /* Success. */
    return WHAD_SUCCESS;
}


/**
 * @brief   Parse a EnergyDetectionCmd message
 *
 * @param[in]       p_message   Pointer to a NanoPb Message structure
 * @param[in,out]   p_channel   Pointer to an integer that will contain the extracted
 *                              channel value
 *
 * @retval          WHAD_SUCCESS        Success.
 * @retval          WHAD_ERROR          Invalid message or address pointer.
 **/

whad_result_t whad_dot15d4_energy_detect_parse(Message *p_message, uint32_t *p_channel)
{
    /* Sanity checks. */
    if ((p_message == NULL) || (p_channel == NULL))
    {
        return WHAD_ERROR;
    }

    *p_channel = p_message->msg.dot15d4.msg.ed.channel;

    /* Success. */
    return WHAD_SUCCESS;
}


/**
 * @brief   Create a SendCmd message
 *
 * @param[in]   p_message   Pointer to a NanoPb Message structure
 * @param[in]   channel     Channel on which the packet will be sent
 * @param[in]   p_packet    Pointer to a Zigbee packet
 * @param[in]   length      Packet length in bytes
 * 
 * @retval          WHAD_SUCCESS        Success.
 * @retval          WHAD_ERROR          Invalid message or address pointer.
 **/

whad_result_t whad_dot15d4_send(Message *p_message, uint32_t channel, uint8_t *p_packet, int length)
{
    /* Sanity checks. */
    if ((p_message == NULL) || (p_packet == NULL))
    {
        return WHAD_ERROR;
    }

    p_message->which_msg = Message_dot15d4_tag;
    p_message->msg.dot15d4.which_msg = dot15d4_Message_send_tag;

    p_message->msg.dot15d4.msg.send.channel = channel;

    if ((length >= 0) && (length <= 255))
    {
        /* Copy packet into our message structure. */
        p_message->msg.dot15d4.msg.send.pdu.size = length;
        memcpy(p_message->msg.dot15d4.msg.send.pdu.bytes, p_packet, length);

        /* Success. */
        return WHAD_SUCCESS;
    }
    else
    {
        /* Error, packet too big. */
        return WHAD_ERROR;
    }
}


/**
 * @brief   Parse a SendCmd message
 *
 * @param[in]       p_message   Pointer to a NanoPb Message structure
 * @param[in,out]   p_params    Pointer to a `whad_dot15d4_send_params_t` structure
 *
 * @retval          WHAD_SUCCESS        Success.
 * @retval          WHAD_ERROR          Invalid message or address pointer.
 **/

whad_result_t whad_dot15d4_send_parse(Message *p_message, whad_dot15d4_send_params_t *p_params)
{
    /* Sanity checks. */
    if ((p_message == NULL) || (p_params == NULL))
    {
        return WHAD_ERROR;
    }

    p_params->channel = p_message->msg.dot15d4.msg.send.channel;

    /* Check packet size. */
    if (p_message->msg.dot15d4.msg.send.pdu.size > DOT15D4_PACKET_MAX_SIZE)
    {
        return WHAD_ERROR;
    }

    /* Copy packet bytes and length. */
    p_params->packet.length = p_message->msg.dot15d4.msg.send.pdu.size;
    memcpy(p_params->packet.bytes, p_message->msg.dot15d4.msg.send.pdu.bytes, p_params->packet.length);

    /* Set FCS to zero (not used in send command). */
    p_params->fcs = 0;

    /* Success. */
    return WHAD_SUCCESS;
}


/**
 * @brief   Create a SendRawCmd message
 *
 * @param[in]   p_message   Pointer to a NanoPb Message structure
 * @param[in]   channel     Channel on which the packet will be sent
 * @param[in]   p_packet    Pointer to a Zigbee packet
 * @param[in]   length      Packet length in bytes
 * @param[in]   fcs         Frame Control Sequence
 * 
 * @retval          WHAD_SUCCESS        Success.
 * @retval          WHAD_ERROR          Invalid message or address pointer.
 **/

whad_result_t whad_dot15d4_send_raw(Message *p_message, uint32_t channel, uint8_t *p_packet, int length, uint32_t fcs)
{
    /* Sanity checks. */
    if ((p_message == NULL) || (p_packet == NULL))
    {
        return WHAD_ERROR;
    }

    p_message->which_msg = Message_dot15d4_tag;
    p_message->msg.dot15d4.which_msg = dot15d4_Message_send_tag;

    p_message->msg.dot15d4.msg.send.channel = channel;

    if ((length >= 0) && (length <= 255))
    {
        /* Copy packet into our message structure. */
        p_message->msg.dot15d4.msg.send.pdu.size = length;
        memcpy(p_message->msg.dot15d4.msg.send.pdu.bytes, p_packet, length);

        /* Success. */
        return WHAD_SUCCESS;
    }
    else
    {
        /* Error, packet too big. */
        return WHAD_ERROR;
    }
}


/**
 * @brief   Parse a SendRawCmd message
 *
 * @param[in]       p_message   Pointer to a NanoPb Message structure
 * @param[in,out]   p_params    Pointer to a `whad_dot15d4_send_params_t` structure
 *
 * @retval          WHAD_SUCCESS        Success.
 * @retval          WHAD_ERROR          Invalid message or address pointer.
 **/

whad_result_t whad_dot15d4_send_raw_parse(Message *p_message, whad_dot15d4_send_params_t *p_params)
{
    /* Sanity checks. */
    if ((p_message == NULL) || (p_params == NULL))
    {
        return WHAD_ERROR;
    }

    p_params->channel = p_message->msg.dot15d4.msg.send_raw.channel;

    /* Check packet size. */
    if (p_message->msg.dot15d4.msg.send_raw.pdu.size > DOT15D4_PACKET_MAX_SIZE)
    {
        return WHAD_ERROR;
    }

    /* Copy packet bytes and length. */
    p_params->packet.length = p_message->msg.dot15d4.msg.send_raw.pdu.size;
    memcpy(p_params->packet.bytes, p_message->msg.dot15d4.msg.send_raw.pdu.bytes, p_params->packet.length);

    /* Set FCS. */
    p_params->fcs = p_message->msg.dot15d4.msg.send_raw.fcs;

    /* Success. */
    return WHAD_SUCCESS;
}


/**
 * @brief   Create a EndDeviceCmd message
 *
 * @param[in]   p_message   Pointer to a NanoPb Message structure
 * @param[in]   channel     Channel to use by the device
 * 
 * @retval          WHAD_SUCCESS        Success.
 * @retval          WHAD_ERROR          Invalid message or address pointer.
 **/

whad_result_t whad_dot15d4_end_device_mode(Message *p_message, uint32_t channel)
{
    /* Sanity checks. */
    if (p_message == NULL)
    {
        return WHAD_ERROR;
    }

    p_message->which_msg = Message_dot15d4_tag;
    p_message->msg.dot15d4.which_msg = dot15d4_Message_end_device_tag;

    p_message->msg.dot15d4.msg.end_device.channel = channel;

    /* Success. */
    return WHAD_SUCCESS;
}


/**
 * @brief   Parse a EndDeviceCmd message
 *
 * @param[in]       p_message   Pointer to a NanoPb Message structure
 * @param[in,out]   p_channel   Pointer to an integer that will contain the extracted
 *                              channel value
 *
 * @retval          WHAD_SUCCESS        Success.
 * @retval          WHAD_ERROR          Invalid message or address pointer.
 **/

whad_result_t whad_dot15d4_end_device_mode_parse(Message *p_message, uint32_t *p_channel)
{
    /* Sanity checks. */
    if ((p_message == NULL) || (p_channel == NULL))
    {
        return WHAD_ERROR;
    }

    *p_channel = p_message->msg.dot15d4.msg.end_device.channel;

    /* Success. */
    return WHAD_SUCCESS;
}


/**
 * @brief   Create a RouterCmd message
 *
 * @param[in]   p_message   Pointer to a NanoPb Message structure
 * @param[in]   channel     Channel to use by the device
 * 
 * @retval          WHAD_SUCCESS        Success.
 * @retval          WHAD_ERROR          Invalid message or address pointer.
 **/

whad_result_t whad_dot15d4_router_mode(Message *p_message, uint32_t channel)
{
    /* Sanity checks. */
    if (p_message == NULL)
    {
        return WHAD_ERROR;
    }

    p_message->which_msg = Message_dot15d4_tag;
    p_message->msg.dot15d4.which_msg = dot15d4_Message_router_tag;

    p_message->msg.dot15d4.msg.router.channel = channel;

    /* Success. */
    return WHAD_SUCCESS;
}


/**
 * @brief   Parse a RouterCmd message
 *
 * @param[in]       p_message   Pointer to a NanoPb Message structure
 * @param[in,out]   p_channel   Pointer to an integer that will contain the extracted
 *                              channel value
 *
 * @retval          WHAD_SUCCESS        Success.
 * @retval          WHAD_ERROR          Invalid message or address pointer.
 **/

whad_result_t whad_dot15d4_router_mode_parse(Message *p_message, uint32_t *p_channel)
{
    /* Sanity checks. */
    if ((p_message == NULL) || (p_channel == NULL))
    {
        return WHAD_ERROR;
    }

    *p_channel = p_message->msg.dot15d4.msg.router.channel;

    /* Success. */
    return WHAD_SUCCESS;
}


/**
 * @brief   Create a CoordinatorCmd message
 *
 * @param[in]   p_message   Pointer to a NanoPb Message structure
 * @param[in]   channel     Channel to use by the device
 * 
 * @retval          WHAD_SUCCESS        Success.
 * @retval          WHAD_ERROR          Invalid message or address pointer.
 **/

whad_result_t whad_dot15d4_coord_mode(Message *p_message, uint32_t channel)
{
    /* Sanity checks. */
    if (p_message == NULL)
    {
        return WHAD_ERROR;
    }

    p_message->which_msg = Message_dot15d4_tag;
    p_message->msg.dot15d4.which_msg = dot15d4_Message_coordinator_tag;

    p_message->msg.dot15d4.msg.coordinator.channel = channel;

    /* Success. */
    return WHAD_SUCCESS;
}


/**
 * @brief   Parse a CoordinatorMsg message
 *
 * @param[in]       p_message   Pointer to a NanoPb Message structure
 * @param[in,out]   p_channel   Pointer to an integer that will contain the extracted
 *                              channel value
 *
 * @retval          WHAD_SUCCESS        Success.
 * @retval          WHAD_ERROR          Invalid message or address pointer.
 **/

whad_result_t whad_dot15d4_coord_mode_parse(Message *p_message, uint32_t *p_channel)
{
    /* Sanity checks. */
    if ((p_message == NULL) || (p_channel == NULL))
    {
        return WHAD_ERROR;
    }

    *p_channel = p_message->msg.dot15d4.msg.coordinator.channel;

    /* Success. */
    return WHAD_SUCCESS;
}


/**
 * @brief   Create a ManInTheMiddleCmd message
 *
 * @param[in]   p_message   Pointer to a NanoPb Message structure
 * @param[in]   role        Mitm role to use
 * 
 * @retval          WHAD_SUCCESS        Success.
 * @retval          WHAD_ERROR          Invalid message or address pointer.
 **/

whad_result_t whad_dot15d4_mitm_mode(Message *p_message, whad_dot15d4_mitm_role_t role)
{
    /* Sanity checks. */
    if (p_message == NULL)
    {
        return WHAD_ERROR;
    }

    p_message->which_msg = Message_dot15d4_tag;
    p_message->msg.dot15d4.which_msg = dot15d4_Message_mitm_tag;

    p_message->msg.dot15d4.msg.mitm.role = role;

    /* Success. */
    return WHAD_SUCCESS;
}


/**
 * @brief   Parse a ManInTheMiddleCmd message
 *
 * @param[in]       p_message   Pointer to a NanoPb Message structure
 * @param[in,out]   p_role      Pointer to an integer that will contain the extracted
 *                              MitM role
 *
 * @retval          WHAD_SUCCESS        Success.
 * @retval          WHAD_ERROR          Invalid message or address pointer.
 **/

whad_result_t whad_dot15d4_mitm_mode_parse(Message *p_message, whad_dot15d4_mitm_role_t *p_role)
{
    /* Sanity checks. */
    if ((p_message == NULL) || (p_role == NULL))
    {
        return WHAD_ERROR;
    }

    *p_role = (whad_dot15d4_mitm_role_t)p_message->msg.dot15d4.msg.mitm.role;

    /* Success. */
    return WHAD_SUCCESS;
}


/**
 * @brief   Create a StartCmd message
 *
 * @param[in]   p_message   Pointer to a NanoPb Message structure
 *
 * @retval      WHAD_SUCCESS        Success.
 * @retval      WHAD_ERROR          Invalid message or packet pointer.
 **/

whad_result_t whad_dot15d4_start(Message *p_message)
{
    /* Sanity check. */
    if (p_message == NULL)
    {
        /* Error. */
        return WHAD_ERROR;
    }

    p_message->which_msg = Message_dot15d4_tag;
    p_message->msg.dot15d4.which_msg = dot15d4_Message_start_tag;

    /* Success. */
    return WHAD_SUCCESS;
}


/**
 * @brief   Create a StopCmd message
 *
 * @param[in]   p_message   Pointer to a NanoPb Message structure
 *
 * @retval      WHAD_SUCCESS        Success.
 * @retval      WHAD_ERROR          Invalid message or packet pointer.
 **/

whad_result_t whad_dot15d4_stop(Message *p_message)
{
    /* Sanity check. */
    if (p_message == NULL)
    {
        /* Error. */
        return WHAD_ERROR;
    }

    p_message->which_msg = Message_dot15d4_tag;
    p_message->msg.dot15d4.which_msg = dot15d4_Message_stop_tag;

    /* Success. */
    return WHAD_SUCCESS;
}


/**
 * @brief   Create a Jammed message
 *
 * @param[in]   p_message   Pointer to a NanoPb Message structure
 * @param[in]   timestamp   Timestamp at which the jamming has been detected
 *
 * @retval      WHAD_SUCCESS        Success.
 * @retval      WHAD_ERROR          Invalid message or packet pointer.
 **/

whad_result_t whad_dot15d4_jammed(Message *p_message, uint32_t timestamp)
{
    /* Sanity check. */
    if (p_message == NULL)
    {
        /* Error. */
        return WHAD_ERROR;
    }

    p_message->which_msg = Message_dot15d4_tag;
    p_message->msg.dot15d4.which_msg = dot15d4_Message_jammed_tag;
    p_message->msg.dot15d4.msg.jammed.timestamp = timestamp;

    /* Success. */
    return WHAD_SUCCESS;
}

/**
 * @brief   Parse a Jammed message
 *
 * @param[in]       p_message   Pointer to a NanoPb Message structure
 * @param[in,out]   p_timestamp Pointer to the timestamp
 *
 * @retval      WHAD_SUCCESS        Success.
 * @retval      WHAD_ERROR          Invalid message or channel pointer.
 **/

whad_result_t whad_dot15d4_jammed_parse(Message *p_message, uint32_t *p_timestamp)
{
    /* Sanity check. */
    if ((p_message == NULL) || (p_timestamp == NULL))
    {
        /* Error. */
        return WHAD_ERROR;
    }

    /* Set output channel. */
    *p_timestamp = p_message->msg.dot15d4.msg.jammed.timestamp;

    /* Success. */
    return WHAD_SUCCESS;
}


/**
 * @brief   Create a EnergyDetectionSample message
 *
 * @param[in]   p_message   Pointer to a NanoPb Message structure
 * @param[in]   timestamp   Sample timestamp
 * @param[in]   sample      Sample value
 *
 * @retval      WHAD_SUCCESS        Success.
 * @retval      WHAD_ERROR          Invalid message or packet pointer.
 **/

whad_result_t whad_dot15d4_energy_detect_sample(Message *p_message, uint32_t timestamp,
                                               uint32_t sample)
{
    /* Sanity check. */
    if (p_message == NULL)
    {
        /* Error. */
        return WHAD_ERROR;
    }

    p_message->which_msg = Message_dot15d4_tag;
    p_message->msg.dot15d4.which_msg = dot15d4_Message_ed_sample_tag;
    p_message->msg.dot15d4.msg.ed_sample.timestamp = timestamp;
    p_message->msg.dot15d4.msg.ed_sample.sample = sample;

    /* Success. */
    return WHAD_SUCCESS;
}

/**
 * @brief   Parse a EnergyDetectionSample message
 *
 * @param[in]       p_message   Pointer to a NanoPb Message structure
 * @param[in,out]   p_sample    Pointer to a `whad_dot15d4_ed_sample_t` structure
 *
 * @retval      WHAD_SUCCESS        Success.
 * @retval      WHAD_ERROR          Invalid message or channel pointer.
 **/

whad_result_t whad_dot15d4_energy_detect_sample_parse(Message *p_message, whad_dot15d4_ed_sample_t *p_sample)
{
    /* Sanity check. */
    if ((p_message == NULL) || (p_sample == NULL))
    {
        /* Error. */
        return WHAD_ERROR;
    }

    /* Set output channel. */
    p_sample->sample = p_message->msg.dot15d4.msg.ed_sample.sample;
    p_sample->timestamp = p_message->msg.dot15d4.msg.ed_sample.timestamp;

    /* Success. */
    return WHAD_SUCCESS;
}


/**
 * @brief   Create a RawPduReceived message
 *
 * @param[in,out]   p_message   Pointer to a NanoPb Message structure
 * @param[in]       p_packet    Pointer to a `whad_dot15d4_recvd_packet_t` structure
 *
 * @retval      WHAD_SUCCESS        Success.
 * @retval      WHAD_ERROR          Invalid message or packet pointer.
 **/

whad_result_t whad_dot15d4_raw_pdu_received(Message *p_message, whad_dot15d4_recvd_packet_t *p_packet)
{
    /* Sanity check. */
    if ((p_message == NULL) || (p_packet == NULL))
    {
        /* Error. */
        return WHAD_ERROR;
    }

    /* Set message properties. */
    p_message->which_msg = Message_dot15d4_tag;
    p_message->msg.dot15d4.which_msg = dot15d4_Message_raw_pdu_tag;
    p_message->msg.dot15d4.msg.raw_pdu.channel = p_packet->channel;
    p_message->msg.dot15d4.msg.raw_pdu.pdu.size = p_packet->packet.length;
    p_message->msg.dot15d4.msg.raw_pdu.fcs = p_packet->fcs;
    memcpy(p_message->msg.dot15d4.msg.raw_pdu.pdu.bytes, p_packet->packet.bytes, p_packet->packet.length);

    /* Set message optional properties. */
    if (p_packet->has_rssi)
    {
        p_message->msg.dot15d4.msg.raw_pdu.has_rssi = true;
        p_message->msg.dot15d4.msg.raw_pdu.rssi = p_packet->rssi;
    }
    else
    {
        p_message->msg.dot15d4.msg.raw_pdu.has_rssi = false;
    }

    if (p_packet->has_timestamp)
    {
        p_message->msg.dot15d4.msg.raw_pdu.has_timestamp = true;
        p_message->msg.dot15d4.msg.raw_pdu.timestamp = p_packet->timestamp;
    }
    else
    {
        p_message->msg.dot15d4.msg.raw_pdu.has_timestamp = false;
    }

    if (p_packet->has_fcs_validity)
    {
        p_message->msg.dot15d4.msg.raw_pdu.has_fcs_validity = true;
        p_message->msg.dot15d4.msg.raw_pdu.fcs_validity = p_packet->fcs_validity;
    }
    else
    {
        p_message->msg.dot15d4.msg.raw_pdu.has_fcs_validity = false;
    }

    if (p_packet->has_lqi)
    {
        p_message->msg.dot15d4.msg.raw_pdu.has_lqi = true;
        p_message->msg.dot15d4.msg.raw_pdu.lqi = p_packet->lqi;
    }
    else
    {
        p_message->msg.dot15d4.msg.raw_pdu.has_lqi = false;
        p_message->msg.dot15d4.msg.raw_pdu.lqi = 0;
    }

    /* Success. */
    return WHAD_SUCCESS;
}

/**
 * @brief   Parse a RawPduReceived message
 *
 * @param[in]       p_message   Pointer to a NanoPb Message structure
 * @param[in,out]   p_packet    Pointer to a `whad_dot15d4_recvd_packet_t` structure
 *
 * @retval      WHAD_SUCCESS        Success.
 * @retval      WHAD_ERROR          Invalid message or packet pointer.
 **/

whad_result_t whad_dot15d4_raw_pdu_received_parse(Message *p_message, whad_dot15d4_recvd_packet_t *p_packet)
{
    /* Sanity check. */
    if ((p_message == NULL) || (p_packet == NULL))
    {
        /* Error. */
        return WHAD_ERROR;
    }

    /* Parse message properties. */
    p_packet->channel = p_message->msg.dot15d4.msg.raw_pdu.channel;
    p_packet->fcs = p_message->msg.dot15d4.msg.raw_pdu.fcs;
    p_packet->packet.length = p_message->msg.dot15d4.msg.raw_pdu.pdu.size;
    memcpy(p_packet->packet.bytes, p_message->msg.dot15d4.msg.raw_pdu.pdu.bytes, p_packet->packet.length);


    /* Parse message optional properties. */
    p_packet->has_rssi = p_message->msg.dot15d4.msg.raw_pdu.has_rssi;
    if (p_packet->has_rssi)
    {
        p_packet->rssi = p_message->msg.dot15d4.msg.raw_pdu.rssi;
    }

    p_packet->has_timestamp = p_message->msg.dot15d4.msg.raw_pdu.has_timestamp;
    if (p_packet->has_timestamp)
    {
        p_packet->timestamp = p_message->msg.dot15d4.msg.raw_pdu.timestamp;
    }

    p_packet->has_fcs_validity = p_message->msg.dot15d4.msg.raw_pdu.has_fcs_validity;
    if (p_packet->has_fcs_validity)
    {
        p_packet->fcs_validity = p_message->msg.dot15d4.msg.raw_pdu.fcs_validity;
    }

    p_packet->has_lqi = p_message->msg.dot15d4.msg.raw_pdu.has_lqi;
    if (p_packet->has_lqi)
    {
        p_packet->lqi = p_message->msg.dot15d4.msg.raw_pdu.lqi;
    }

    /* Success. */
    return WHAD_SUCCESS;
}


/**
 * @brief   Create a PduReceived message
 *
 * @param[in,out]   p_message   Pointer to a NanoPb Message structure
 * @param[in]       p_packet    Pointer to a `whad_dot15d4_recvd_packet_t` structure
 *
 * @retval      WHAD_SUCCESS        Success.
 * @retval      WHAD_ERROR          Invalid message or packet pointer.
 **/

whad_result_t whad_dot15d4_pdu_received(Message *p_message, whad_dot15d4_recvd_packet_t *p_packet)
{
    /* Sanity check. */
    if ((p_message == NULL) || (p_packet == NULL))
    {
        /* Error. */
        return WHAD_ERROR;
    }

    /* Set message properties. */
    p_message->which_msg = Message_dot15d4_tag;
    p_message->msg.dot15d4.which_msg = dot15d4_Message_pdu_tag;
    p_message->msg.dot15d4.msg.pdu.channel = p_packet->channel;
    p_message->msg.dot15d4.msg.pdu.pdu.size = p_packet->packet.length;
    memcpy(p_message->msg.dot15d4.msg.pdu.pdu.bytes, p_packet->packet.bytes, p_packet->packet.length);

    /* Set message optional properties. */
    if (p_packet->has_rssi)
    {
        p_message->msg.dot15d4.msg.pdu.has_rssi = true;
        p_message->msg.dot15d4.msg.pdu.rssi = p_packet->rssi;
    }
    else
    {
        p_message->msg.dot15d4.msg.pdu.has_rssi = false;
    }

    if (p_packet->has_timestamp)
    {
        p_message->msg.dot15d4.msg.pdu.has_timestamp = true;
        p_message->msg.dot15d4.msg.pdu.timestamp = p_packet->timestamp;
    }
    else
    {
        p_message->msg.dot15d4.msg.pdu.has_timestamp = false;
    }

    if (p_packet->has_fcs_validity)
    {
        p_message->msg.dot15d4.msg.pdu.has_fcs_validity = true;
        p_message->msg.dot15d4.msg.pdu.fcs_validity = p_packet->fcs_validity;
    }
    else
    {
        p_message->msg.dot15d4.msg.pdu.has_fcs_validity = false;
    }

    if (p_packet->has_lqi)
    {
        p_message->msg.dot15d4.msg.pdu.has_lqi = true;
        p_message->msg.dot15d4.msg.pdu.lqi = p_packet->lqi;
    }
    else
    {
        p_message->msg.dot15d4.msg.pdu.has_lqi = false;
        p_message->msg.dot15d4.msg.pdu.lqi = 0;
    }

    /* Success. */
    return WHAD_SUCCESS;
}

/**
 * @brief   Parse a PduReceived message
 *
 * @param[in]       p_message   Pointer to a NanoPb Message structure
 * @param[in,out]   p_packet    Pointer to a `whad_dot15d4_recvd_packet_t` structure
 *
 * @retval      WHAD_SUCCESS        Success.
 * @retval      WHAD_ERROR          Invalid message or packet pointer.
 **/

whad_result_t whad_dot15d4_pdu_received_parse(Message *p_message, whad_dot15d4_recvd_packet_t *p_packet)
{
    /* Sanity check. */
    if ((p_message == NULL) || (p_packet == NULL))
    {
        /* Error. */
        return WHAD_ERROR;
    }

    /* Parse message properties. */
    p_packet->channel = p_message->msg.dot15d4.msg.raw_pdu.channel;
    p_packet->packet.length = p_message->msg.dot15d4.msg.raw_pdu.pdu.size;
    memcpy(p_packet->packet.bytes, p_message->msg.dot15d4.msg.raw_pdu.pdu.bytes, p_packet->packet.length);


    /* Parse message optional properties. */
    p_packet->has_rssi = p_message->msg.dot15d4.msg.raw_pdu.has_rssi;
    if (p_packet->has_rssi)
    {
        p_packet->rssi = p_message->msg.dot15d4.msg.raw_pdu.rssi;
    }

    p_packet->has_timestamp = p_message->msg.dot15d4.msg.raw_pdu.has_timestamp;
    if (p_packet->has_timestamp)
    {
        p_packet->timestamp = p_message->msg.dot15d4.msg.raw_pdu.timestamp;
    }

    p_packet->has_fcs_validity = p_message->msg.dot15d4.msg.raw_pdu.has_fcs_validity;
    if (p_packet->has_fcs_validity)
    {
        p_packet->fcs_validity = p_message->msg.dot15d4.msg.raw_pdu.fcs_validity;
    }

    p_packet->has_lqi = p_message->msg.dot15d4.msg.raw_pdu.has_lqi;
    if (p_packet->has_lqi)
    {
        p_packet->lqi = p_message->msg.dot15d4.msg.raw_pdu.lqi;
    }

    /* Success. */
    return WHAD_SUCCESS;
}

/**
 * @brief   Create an enable hopping message
 *
 * @param[in, out]   p_message   Pointer to a NanoPb Message structure
 * @param[in] hopping bool val to set to frequency hopping
 * 
 *
 * @retval      WHAD_SUCCESS        Success.
 * @retval      WHAD_ERROR          Invalid message or packet pointer.
 **/
whad_result_t whad_dot15d4_enable_hopping(Message *p_message, bool *hopping)
{
    /* Sanity check. */
    if (p_message == NULL)
    {
        /* Error. */
        return WHAD_ERROR;
    }

    p_message->which_msg = Message_dot15d4_tag;
    p_message->msg.dot15d4.which_msg = dot15d4_Message_hopping_tag;
    *hopping = p_message->msg.dot15d4.msg.hopping.hopping ;

    /* Success. */
    return WHAD_SUCCESS;
}

/**
 * @brief Returns true if the link defined by its join_slot exists in the suerframe given as parameter.
 * 
 * @param[in] sf Pointer to a `whad_dot15d4_superframe_t` structure
 * @param[in] join_slot uint16_t of the looked for link
 * 
 * @return boolean
 **/
bool link_exists_in_sf(whad_dot15d4_superframe_t *sf, uint16_t join_slot) {
    if (!sf || !sf->links) return false;

    for (whad_dot15d4_link_t *l = sf->links->first; l != NULL; l = l->next) {
        if (l->join_slot == join_slot) {
            return true;
        }
    }
    return false;
}

/**
 * @brief   Returns a pointer to the superframe corresponding to the id given else null
 *
 * @param[in] superframes    Pointer to a `whad_dot15d4_superframes_t` structure
 * @param[in] id int val to select the id
 * @param[out] superframe structure pointer corresponding to the given id or null
 * 
 *
 * @retval      WHAD_SUCCESS        Success.
 * @retval      WHAD_ERROR          Invalid message or packet pointer.
 **/
whad_dot15d4_superframe_t *whad_dot15d4_get_superframe(whad_dot15d4_superframes_t *superframes, uint8_t id) {
    whad_dot15d4_superframes_t* curr = superframes;
    do
    {
       if(curr->superframe != NULL){
        if (curr->superframe->id == id) return curr->superframe;
       }
       curr = curr->next;
    } while (curr != NULL);
    return NULL;
}


/**
 * @brief   Parse a message into the superframes links
 *
 * @param[in]       p_message   Pointer to a NanoPb Message structure
 * @param[in,out]   superframes    Pointer to a `whad_dot15d4_superframes_t` structure
 *
 * @retval      WHAD_SUCCESS        Success.
 * @retval      WHAD_ERROR          Invalid message or packet pointer.
 */
whad_result_t whad_dot15d4_add_links(Message *p_message, whad_dot15d4_superframes_t *superframes) {
    if (!p_message || !superframes) return WHAD_ERROR;

    dot15d4_AddLinksCmd_links_t links = p_message->msg.dot15d4.msg.addLinks.links;
    uint8_t nb_links = p_message->msg.dot15d4.msg.addLinks.nb_links;

    for (int i = 0; i < nb_links; i++) {
        uint8_t *raw = &(links.bytes[10 * i]);

        uint8_t id_superframe = raw[0];
        uint16_t src = (raw[1] << 8) | raw[2]; 
        uint16_t join_slot = (raw[3] << 8) | raw[4]; 
        uint8_t offset = raw[5];
        uint16_t neighbor = (raw[6] << 8) | raw[7];
        uint8_t options = raw[8];
        uint8_t type = raw[9];

        whad_dot15d4_superframe_t *sf = whad_dot15d4_get_superframe(superframes, id_superframe);
        if (!sf) return WHAD_ERROR;

        if (link_exists_in_sf(sf, join_slot)) {
            //if the link already exists, this message is discarded, as to modify a link one should delete it then create a one one
            continue;
        }

        whad_dot15d4_link_t *new_link = malloc(sizeof(whad_dot15d4_link_t));
        if (!new_link) return WHAD_ERROR;

        new_link->src = src;
        new_link->join_slot = join_slot;
        new_link->offset = offset;
        new_link->neighbor = neighbor;
        new_link->options = options;
        new_link->type = type;
        new_link->next = sf->links->first;

        sf->links->first = new_link;
        sf->links->nb_links++; 
    }

    return WHAD_SUCCESS;
}

/**
 * @brief   Delete a link from a superframes struct
 *
 * @param[in]       p_message   Pointer to a NanoPb Message structure
 * @param[in,out]   superframes    Pointer to a `whad_dot15d4_superframes_t` structure
 *
 * @retval      WHAD_SUCCESS        Success.
 * @retval      WHAD_ERROR          Invalid message or packet pointer.
 */
whad_result_t whad_dot15d4_delete_link(Message *p_message, whad_dot15d4_superframes_t *superframes) {
    if (!p_message || !superframes) return WHAD_ERROR;
    uint8_t superframeId = (uint8_t)p_message->msg.dot15d4.msg.deleteLink.superframeId;
    uint16_t join_slot = (uint16_t)p_message->msg.dot15d4.msg.deleteLink.slotNumber;
    uint16_t neighbor = (uint16_t)p_message->msg.dot15d4.msg.deleteLink.neighbor;
    whad_dot15d4_superframe_t *sf = whad_dot15d4_get_superframe(superframes, superframeId);
    if (!sf) return WHAD_ERROR;
    sf->links->nb_links--;
    if (!sf->links) return WHAD_ERROR;
    whad_dot15d4_link_t* prev = NULL;
    whad_dot15d4_link_t* link = sf->links->first;
    while(link){
        if (link->join_slot == join_slot && link->neighbor == neighbor){
            if(!prev){
                sf->links->first = link->next;
            }else{
                prev->next = link->next;
            }
            free(link);
            return WHAD_SUCCESS;
        }
        prev = link;
        link = link->next;
    }
    return WHAD_ERROR;
}

/**
 * @brief   Parse a message into the channel map
 *
 * @param[in]       p_message   Pointer to a NanoPb Message structure
 * @param[in,out]   channel_map    Pointer to a uint16_t representing the map
 *
 * @retval      WHAD_SUCCESS        Success.
 * @retval      WHAD_ERROR          Invalid message or packet pointer.
 **/
whad_result_t whad_dot15d4_channel_map(Message *p_message, uint16_t *channel_map){
    /* Sanity check. */
    if (p_message == NULL)
    {
        /* Error. */
        return WHAD_ERROR;
    }

    *channel_map = (uint16_t)(p_message->msg.dot15d4.msg.channelMap.channelMap);
    return WHAD_SUCCESS;
}

/**
 * @brief   Parse a message into the 'whad_dot15d4_write_modify_superframes_packet_t' structure
 *
 * @param[in]       p_message   Pointer to a NanoPb Message structure
 * @param[in,out]   p_packet    Pointer to a 'whad_dot15d4_write_modify_superframes_packet_t' 
 *
 * @retval      WHAD_SUCCESS        Success.
 * @retval      WHAD_ERROR          Invalid message or packet pointer.
 */
whad_result_t whad_dot15d4_write_modify_superframe(Message *p_message, whad_dot15d4_write_modify_superframes_packet_t *p_packet){
    if (!p_message || !p_packet) return WHAD_ERROR;

    p_packet->superframeId = p_message->msg.dot15d4.msg.writeModifySuperframeCmd.superframeId;
    p_packet->numberOfSlots = p_message->msg.dot15d4.msg.writeModifySuperframeCmd.numberOfSlots;
    p_packet->flags = p_message->msg.dot15d4.msg.writeModifySuperframeCmd.flags;
    p_packet->has_asn = p_message->msg.dot15d4.msg.writeModifySuperframeCmd.has_asn;
    if (p_packet->has_asn){
        p_packet->asn = p_message->msg.dot15d4.msg.writeModifySuperframeCmd.asn;
    }    
    /* Success. */
    return WHAD_SUCCESS;
}

void whad_dot15d4_free_superframe_struct(whad_dot15d4_superframe_t* superframe){
    if(superframe != NULL){
        whad_dot15d4_chained_link_list_t* links = superframe->links;
        if(links!=NULL){
            whad_dot15d4_link_t *link = links->first;
            whad_dot15d4_link_t *to_free;
            while(link!=NULL){
                to_free = link;
                link = link->next;
                
                free(to_free);
            }
            free(links);
        }
        free(superframe);
        
    }
}

/**
 * @brief   Parse a message and delete the corresponding superframe if it exists
 *
 * @param[in]       p_message   Pointer to a NanoPb Message structure
 * @param[in,out]   superframes    Pointer to a pointer to the 'whad_dot15d4_superframes_t' that contains all links
 *
 * @retval      WHAD_SUCCESS        Success.
 * @retval      WHAD_ERROR          Invalid message.
 */
whad_result_t whad_dot15d4_delete_superframe(Message *p_message, whad_dot15d4_superframes_t **superframes){
    if (!p_message) return WHAD_ERROR;
    uint8_t id = p_message->msg.dot15d4.msg.deleteSuperframeCmd.superframeId;
    whad_dot15d4_superframes_t *prev = NULL;
    whad_dot15d4_superframes_t *curr = *superframes;

    while (curr != NULL) {
        if (curr->superframe != NULL && curr->superframe->id == id) {
            if (prev != NULL) {
                prev->next = curr->next;
            } else {
                whad_dot15d4_free_superframe_struct(curr->superframe);
                if (curr->next==NULL){
                    (*superframes)->superframe = NULL;
                    (*superframes)->next = NULL;

                }else{
                    *superframes = curr->next;
                    free(curr);
                }
                
            }
            return WHAD_SUCCESS;
        }
        prev = curr;
        curr = curr->next;
    }
    return WHAD_SUCCESS;    
}

/**
 * @brief   Add the corresponding superframe from 'whad_dot15d4_write_modify_superframes_packet_t' to 'whad_dot15d4_superframes_t'
 *
 * @param[in,out]   superframes     Pointer to 'whad_dot15d4_superframes_t' struct
 * @param[in]       pkt             Pointer to a 'whad_dot15d4_write_modify_superframes_packet_t' that contains superframes details
 *
 */
whad_result_t whad_dot15d4_add_superframe( whad_dot15d4_superframes_t *superframes, whad_dot15d4_write_modify_superframes_packet_t *pkt){
    whad_dot15d4_superframes_t *curr = superframes;
    whad_dot15d4_superframe_t * superframe = (whad_dot15d4_superframe_t*) malloc(sizeof(whad_dot15d4_superframe_t));
    superframe->id = pkt->superframeId;
    superframe->size = pkt->numberOfSlots;
    superframe->links = (whad_dot15d4_chained_link_list_t*) malloc(sizeof(whad_dot15d4_chained_link_list_t));
    superframe->links->first = NULL;
    superframe->links->nb_links = 0;

    if (superframes->superframe == NULL && superframes->next == NULL){
        superframes->superframe = superframe;
    }else{
        while (curr->next != NULL){
            curr = curr->next;
        }
        curr->next = (whad_dot15d4_superframes_t*) malloc (sizeof(whad_dot15d4_superframes_t));
        curr->next->superframe = superframe;
        curr->next->next = NULL;
    }
    return WHAD_SUCCESS;
}

/**
 * @brief   Update the corresponding superframe from 'whad_dot15d4_write_modify_superframes_packet_t' to 'whad_dot15d4_superframes_t'
 *
 * @param[in,out]   superframes     Pointer to 'whad_dot15d4_superframes_t' struct
 * @param[in]       pkt             Pointer to a 'whad_dot15d4_write_modify_superframes_packet_t' that contains superframes details
 *
 */
whad_result_t whad_dot15d4_modify_superframe(whad_dot15d4_superframe_t *superframe, whad_dot15d4_write_modify_superframes_packet_t *pkt){
    if (superframe != NULL){
        superframe->size = pkt->numberOfSlots;
        superframe->flags = pkt->flags;
        if (superframe->links != NULL){
            whad_dot15d4_link_t* link = superframe->links->first;
            while (link!=NULL)
            {
                if(link->join_slot > pkt->numberOfSlots){
                    whad_dot15d4_link_t *link_to_free = link;
                    link = link->next;
                    free(link_to_free);
                }
                else{
                    link = link->next;
                }
            }
        }
    }
    return WHAD_SUCCESS;
}

/**
 * @brief   Create a DiscoveredCommunication message
 *
 * @param[in]   p_message   Pointer to a NanoPb Message structure
 * @param[in]   src         Source  of the message discovered
 * @param[in]   dst         Destination  of the message discovered
 * @param[in]   slot        Slot in which the communication was got
 * @param[in]   offset      Calculated offset based on number of active channels
 * 
 * @retval          WHAD_SUCCESS        Success.
 * @retval          WHAD_ERROR          Invalid message or address pointer.
 **/
whad_result_t whad_dot15d4_discovered_communication(Message *p_message, uint16_t src, uint16_t dst, uint16_t slot, uint16_t offset){
    /* Sanity check */
    if (!p_message) return WHAD_ERROR;

    /* Set parameters*/
    p_message->which_msg = Message_dot15d4_tag;
    p_message->msg.dot15d4.which_msg = dot15d4_Message_discovered_communication_tag;
    p_message->msg.dot15d4.msg.discovered_communication.src = src;
    p_message->msg.dot15d4.msg.discovered_communication.dst = dst;
    p_message->msg.dot15d4.msg.discovered_communication.slot = slot;
    p_message->msg.dot15d4.msg.discovered_communication.offset = offset;

    /*Success*/
    return WHAD_SUCCESS;
}