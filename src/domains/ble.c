#include <whad.h>
#include <domains/ble.h>

whad_ble_msgtype_t whad_ble_get_message_type(Message *p_message)
{
    whad_ble_msgtype_t msg_type = WHAD_BLE_UNKNOWN;

    /* Ensure it is a BLE message. */
    if (whad_get_message_domain(p_message) == DOMAIN_BTLE)
    {
        /* Retrieve the message type. */
        msg_type = (whad_ble_msgtype_t)p_message->msg.ble.which_msg;
    }

    /* Success. */
    return msg_type;
}


/********************************
 * Bluetooth Low Energy messages
 *******************************/


/**
 * @brief Initialize a message reporting a BLE raw PDU
 * 
 * @param[in,out]   p_message           Pointer to the message structure to initialize
 * @param[in]       channel             Channel on which this PDU has been received
 * @param[in]       rssi                Received Signal Strength Indicator
 * @param[in]       conn_handle         Connection handle
 * @param[in]       access_address      Access Address of the connection
 * @param[in]       p_pdu               Pointer to a byte array containing the PDU
 * @param[in]       length              Length of the data PDU, in bytes
 * @param[in]       crc                 PDU CRC value
 * @param[in]       crc_validity        Set to true if CRC matches the expected value, false otherwise
 * @param[in]       timestamp           PDU timestamp (in micro-seconds)
 * @param[in]       relative_timestamp  PDU relative timestamp (number of micro-seconds in the last connection event)
 * @param[in]       direction           Direction of the PDU (master -> slave / slave -> master)
 * @param[in]       processed           Set to true if PDU has been processed by the device, false otherwise
 * @param[in]       decrypted           Set to true if PDU has been decrypted, false otherwise
 * @param[in]       use_timestamp       If set to true, message will include timestamp and relative timestamp        
 * 
 * @retval          WHAD_SUCCESS        Success.
 * @retval          WHAD_ERROR          Invalid message pointer or PDU pointer.
 **/

whad_result_t whad_ble_raw_pdu(Message *p_message, uint32_t channel, int32_t rssi, uint32_t conn_handle,
                               uint32_t access_address, uint8_t *p_pdu, int length, uint32_t crc,
                               bool crc_validity, uint32_t timestamp, uint32_t relative_timestamp,
                               whad_ble_direction_t direction, bool processed, bool decrypted, bool use_timestamp)
{
    /* Sanity check. */
    if ((p_message == NULL) || (p_pdu == NULL) )
    {
        return WHAD_ERROR;
    }

    /* Populate fields. */
    p_message->which_msg = Message_ble_tag;
    p_message->msg.ble.which_msg = ble_Message_raw_pdu_tag;

    /* Set connection handle, access address and direction. */
    p_message->msg.ble.msg.raw_pdu.access_address = access_address;
    p_message->msg.ble.msg.raw_pdu.conn_handle = conn_handle;
    p_message->msg.ble.msg.raw_pdu.direction = (ble_BleDirection)direction;

    /* Copy PDU into our message. */
    p_message->msg.ble.msg.raw_pdu.pdu.size = length;
    memcpy(p_message->msg.ble.msg.raw_pdu.pdu.bytes, p_pdu, length);

    /* Insert timestamp if set. */
    if (use_timestamp)
    {
        /* Set timestamp. */
        p_message->msg.ble.msg.raw_pdu.has_timestamp = true;
        p_message->msg.ble.msg.raw_pdu.timestamp = timestamp;

        /* Set relative timestamp. */
        p_message->msg.ble.msg.raw_pdu.has_relative_timestamp = true;
        p_message->msg.ble.msg.raw_pdu.relative_timestamp = relative_timestamp;
    }

    /* CRC */
    p_message->msg.ble.msg.raw_pdu.crc = crc;
    p_message->msg.ble.msg.raw_pdu.has_crc_validity = true;
    p_message->msg.ble.msg.raw_pdu.crc_validity = crc_validity;

    /* RSSI */
    if (rssi != BLE_RSSI_NONE)
    {
        p_message->msg.ble.msg.raw_pdu.has_rssi = true;
        p_message->msg.ble.msg.raw_pdu.rssi = rssi;
    }

    /* Processed / decrypted. */
    p_message->msg.ble.msg.raw_pdu.processed = processed;
    p_message->msg.ble.msg.raw_pdu.decrypted = decrypted;

    /* Success. */
    return WHAD_SUCCESS;
}


/**
 * @brief Initialize a message reporting a BLE link-layer data PDU
 * 
 * @param[in,out]   p_message           Pointer to the message structure to initialize
 * @param[in]       p_pdu               Pointer to a byte array containing the PDU
 * @param[in]       length              Length of the data PDU, in bytes
 * @param[in]       direction           Direction of the PDU (master -> slave / slave -> master)
 * @param[in]       conn_handle         Connection handle of the connection this PDU has been captured from
 * @param[in]       processed           Set to true if PDU has been processed by the device, false otherwise
 * @param[in]       decrypted           Set to true if PDU has been decrypted, false otherwise
 * 
 * @retval          WHAD_SUCCESS        Success.
 * @retval          WHAD_ERROR          Invalid message pointer or PDU pointer.
 **/

whad_result_t whad_ble_pdu(Message *p_message, uint8_t *p_pdu, int length, whad_ble_direction_t direction,
                          int conn_handle, bool processed, bool decrypted)
{
    /* Sanity check. */
    if ((p_message == NULL) || (p_pdu == NULL) )
    {
        return WHAD_ERROR;
    }

    /* Populate fields. */
    p_message->which_msg = Message_ble_tag;
    p_message->msg.ble.which_msg = ble_Message_pdu_tag;
    p_message->msg.ble.msg.pdu.processed = processed?1:0;
    p_message->msg.ble.msg.pdu.decrypted = decrypted?1:0;
    p_message->msg.ble.msg.pdu.direction = (ble_BleDirection)direction;
    p_message->msg.ble.msg.pdu.conn_handle = conn_handle;
    p_message->msg.ble.msg.pdu.pdu.size = length;
    memcpy(&p_message->msg.ble.msg.pdu.pdu.bytes, p_pdu, length);

    /* Success. */
    return WHAD_SUCCESS;
}


/**
 * @brief Parse a message reporting a BLE link-layer data PDU
 * 
 * @param[in]       p_message           Pointer to the message structure to initialize
 * @param[in,out]   p_parameters        Pointer to a whad_ble_pdu_t structure
 * 
 * @retval          WHAD_SUCCESS        Success.
 * @retval          WHAD_ERROR          Invalid message pointer or PDU pointer.
 **/

whad_result_t whad_ble_pdu_parse(Message *p_message, whad_ble_pdu_t *p_parameters)
{
    /* Sanity check. */
    if ((p_message == NULL) || (p_parameters == NULL) )
    {
        return WHAD_ERROR;
    }

    /* Extract parameters. */
    p_parameters->conn_handle = p_message->msg.ble.msg.pdu.conn_handle;
    p_parameters->processed = p_message->msg.ble.msg.pdu.processed;
    p_parameters->decrypted = p_message->msg.ble.msg.pdu.decrypted;
    p_parameters->pdu_length = p_message->msg.ble.msg.pdu.pdu.size;
    p_parameters->p_pdu = p_message->msg.ble.msg.pdu.pdu.bytes;

    /* Success. */
    return WHAD_SUCCESS;
}


/**
 * @brief Initialize a message reporting a BLE connection
 * 
 * @param[in,out]   p_message           Pointer to the message structure to initialize
 * @param[in]       adv_addr_type       Advertiser address type (public/random)
 * @param[in]       p_adv_addr          Pointer to the advertiser BD address (6 bytes)
 * @param[in]       init_addr_type      Initiator address type (public/random)
 * @param[in]       p_init_addr         Pointer to the initiator BD address (6 bytes)
 * @param[in]       conn_handle         Connection handle of the connection this PDU has been captured from
 * 
 * @retval          WHAD_SUCCESS        Success.
 * @retval          WHAD_ERROR          Invalid message pointer.
 **/

whad_result_t whad_ble_notify_connected(Message *p_message, whad_ble_addrtype_t adv_addr_type, uint8_t *p_adv_addr, whad_ble_addrtype_t init_addr_type, uint8_t *p_init_addr, uint32_t conn_handle)
{
    /* Sanity check. */
    if ((p_message == NULL) || (p_adv_addr == NULL) || (p_init_addr == NULL) )
    {
        return WHAD_ERROR;
    }

    p_message->which_msg = Message_ble_tag;
    p_message->msg.ble.which_msg = ble_Message_connected_tag;

    /* Save Access Address (unknown, set to 0). */
    p_message->msg.ble.msg.connected.access_address = 0;

    /* Save connection handle. */
    p_message->msg.ble.msg.connected.conn_handle = conn_handle;

    /* Save advertiser address and address type. */
    memcpy(p_message->msg.ble.msg.connected.advertiser, p_adv_addr, 6);
    p_message->msg.ble.msg.connected.adv_addr_type = (ble_BleAddrType)adv_addr_type;

    /* Save initiator address and address type. */
    memcpy(p_message->msg.ble.msg.connected.initiator, p_init_addr, 6);
    p_message->msg.ble.msg.connected.init_addr_type = (ble_BleAddrType)init_addr_type;

    /* Success. */
    return WHAD_SUCCESS;
}


/**
 * @brief Initialize a message reporting a BLE disconnection
 * 
 * @param[in,out]   p_message           Pointer to the message structure to initialize
 * @param[in]       conn_handle         Connection handle of the connection this PDU has been captured from
 * @param[in]       reason              Disconnection reason (as defined in the BLE specification)
 * 
 * @retval          WHAD_SUCCESS        Success.
 * @retval          WHAD_ERROR          Invalid message pointer.
 **/

whad_result_t whad_ble_notify_disconnected(Message *p_message, uint32_t conn_handle, uint32_t reason)
{
    /* Sanity check. */
    if (p_message == NULL)
    {
        return WHAD_ERROR;
    }

    /* Populate fields. */
    p_message->which_msg = Message_ble_tag;
    p_message->msg.ble.which_msg = ble_Message_disconnected_tag;
    p_message->msg.ble.msg.disconnected.conn_handle = conn_handle;
    p_message->msg.ble.msg.disconnected.reason = reason;

    /* Success. */
    return WHAD_SUCCESS;
}


/**
 * @brief Parse a message reporting a BLE disconnection
 * 
 * @param[in,out]   p_message           Pointer to the message structure to initialize
 * @param[in]       conn_handle         Connection handle of the connection this PDU has been captured from
 * @param[in]       reason              Disconnection reason (as defined in the BLE specification)
 * 
 * @retval          WHAD_SUCCESS        Success.
 * @retval          WHAD_ERROR          Invalid message pointer.
 **/

whad_result_t whad_ble_notify_disconnected_parse(Message *p_message, whad_ble_disconnected_params_t *p_parameters)
{
    /* Sanity check. */
    if ((p_message == NULL) || (p_parameters == NULL))
    {
        return WHAD_ERROR;
    }

    /* Extract parameters. */
    p_parameters->conn_handle = p_message->msg.ble.msg.disconnected.conn_handle;
    p_parameters->reason = p_message->msg.ble.msg.disconnected.reason;

    /* Success. */
    return WHAD_SUCCESS;
}

/**
 * @brief Initialize a message setting the BD address of the adapter
 * 
 * @param[in,out]   p_message           Pointer to the message structure to initialize
 * @param[in]       addr_type           BD address type
 * @param[in]       p_bdaddr            Pointer to a buffer containing the target BD address (6-byte array)
 * 
 * @retval          WHAD_SUCCESS        Success.
 * @retval          WHAD_ERROR          Invalid message pointer.
 **/

whad_result_t whad_ble_set_bdaddress(Message *p_message, whad_ble_addrtype_t addr_type, uint8_t *p_bdaddr)
{
    /* Sanity check. */
    if ((p_message == NULL) || (p_bdaddr == NULL))
    {
        return WHAD_ERROR;
    }

    /* Populate message fields. */
    p_message->which_msg = Message_ble_tag;
    p_message->msg.ble.which_msg = ble_Message_set_bd_addr_tag;

    /* Copy BD address. */
    p_message->msg.ble.msg.set_bd_addr.addr_type = (ble_BleAddrType)addr_type;
    memcpy(p_message->msg.ble.msg.set_bd_addr.bd_address, p_bdaddr, 6);

    /* Success. */
    return WHAD_SUCCESS;
}


/**
 * @brief Parse a message setting the BD address of the adapter
 * 
 * @param[in]       p_message           Pointer to the message structure to parse
 * @param[out]      p_addr_type         Pointer to output BD address type
 * @param[out]      p_bdaddr            Pointer to a buffer where the target BD address will be copied (6-byte array)
 * 
 * @retval          WHAD_SUCCESS        Success.
 * @retval          WHAD_ERROR          Invalid message pointer.
 **/

whad_result_t whad_ble_set_bdaddress_parse(Message *p_message, whad_ble_addrtype_t *p_addr_type, uint8_t *p_bdaddr)
{
    /* Sanity check. */
    if ((p_message == NULL) || (p_addr_type == NULL) || (p_bdaddr == NULL))
    {
        return WHAD_ERROR;
    }

    /* Extract parameters. */
    *p_addr_type = (whad_ble_addrtype_t)p_message->msg.ble.msg.set_bd_addr.addr_type;
    memcpy(p_bdaddr, p_message->msg.ble.msg.set_bd_addr.bd_address, 6);

    /* Success. */
    return WHAD_SUCCESS;
}


/**
 * @brief Initialize a message enabling sniffing mode for advertisements
 * 
 * @param[in,out]   p_message           Pointer to the message structure to initialize
 * @param[in]       use_ext_adv         If set to true, sniffer will sniff extended advertisements
 * @param[in]       channel             The advertising channel on which the sniffing must be performed
 * @param[in]       p_bdaddr            The target BD address, as a pointer to a 6-byte array
 * 
 * @retval          WHAD_SUCCESS        Success.
 * @retval          WHAD_ERROR          Invalid message pointer.
 **/

whad_result_t whad_ble_sniff_adv(Message *p_message, bool use_ext_adv, uint32_t channel, uint8_t *p_bdaddr)
{
    /* Sanity check. */
    if ((p_message == NULL) || (p_bdaddr == NULL))
    {
        return WHAD_ERROR;
    }

    /* Populate message fields. */
    p_message->which_msg = Message_ble_tag;
    p_message->msg.ble.which_msg = ble_Message_sniff_adv_tag;
    p_message->msg.ble.msg.sniff_adv.use_extended_adv = use_ext_adv;
    p_message->msg.ble.msg.sniff_adv.channel = channel;
    memcpy(p_message->msg.ble.msg.sniff_adv.bd_address, p_bdaddr, 6);

    /* Success. */
    return WHAD_SUCCESS;
}


/**
 * @brief Parse a message enabling sniffing mode for advertisements
 * 
 * @param[in]       p_message           Pointer to the message structure to parse
 * @param[in,out]   p_parameters        Pointer to a `whad_ble_sniff_adv_params_t` structure
 * 
 * @retval          WHAD_SUCCESS        Success.
 * @retval          WHAD_ERROR          Invalid message pointer.
 **/

whad_result_t whad_ble_sniff_adv_parse(Message *p_message, whad_ble_sniff_adv_params_t *p_parameters)
{
    /* Sanity check. */
    if ((p_message == NULL) || (p_parameters == NULL))
    {
        return WHAD_ERROR;
    }

    /* Extract message info. */
    p_parameters->channel = p_message->msg.ble.msg.sniff_adv.channel;
    p_parameters->use_ext_adv = p_message->msg.ble.msg.sniff_adv.use_extended_adv;
    p_parameters->p_bdaddr = p_message->msg.ble.msg.sniff_adv.bd_address;

    /* Success. */
    return WHAD_SUCCESS;
}


/**
 * @brief Initialize a message enabling advertisement jamming mode
 * 
 * @param[in,out]   p_message           Pointer to the message structure to initialize
 * 
 * @retval          WHAD_SUCCESS        Success.
 * @retval          WHAD_ERROR          Invalid message pointer.
 **/

whad_result_t whad_ble_jam_adv(Message *p_message)
{
    /* Sanity check. */
    if (p_message == NULL)
    {
        return WHAD_ERROR;
    }

    /* Populate message fields. */
    p_message->which_msg = Message_ble_tag;
    p_message->msg.ble.which_msg = ble_Message_jam_adv_tag;

    /* Success. */
    return WHAD_SUCCESS;    
}


/**
 * @brief Initialize a message enabling jamming on a specific advertising channel
 * 
 * @param[in,out]   p_message           Pointer to the message structure to initialize
 * @param[in]       channel             The advertising channel on which the jamming must be performed
 * 
 * @retval          WHAD_SUCCESS        Success.
 * @retval          WHAD_ERROR          Invalid message pointer.
 **/

whad_result_t whad_ble_jam_adv_channel(Message *p_message, uint32_t channel)
{
    /* Sanity check. */
    if (p_message == NULL)
    {
        return WHAD_ERROR;
    }

    /* Populate message fields. */
    p_message->which_msg = Message_ble_tag;
    p_message->msg.ble.which_msg = ble_Message_jam_adv_chan_tag;
    p_message->msg.ble.msg.jam_adv_chan.channel = channel;

    /* Success. */
    return WHAD_SUCCESS;       
}


/**
 * @brief Parse a message enabling jamming on a specific advertising channel
 * 
 * @param[in]       p_message           Pointer to the message structure to parse
 * @param[in,out]   p_channel           Pointer to the extracted advertising channel
 * 
 * @retval          WHAD_SUCCESS        Success.
 * @retval          WHAD_ERROR          Invalid message pointer.
 **/

whad_result_t whad_ble_jam_adv_channel_parse(Message *p_message, uint32_t *p_channel)
{
    /* Sanity check. */
    if ((p_message == NULL) || (p_channel == NULL))
    {
        return WHAD_ERROR;
    }

    /* Extract channel from message. */
    *p_channel = p_message->msg.ble.msg.jam_adv_chan.channel;

    /* Success. */
    return WHAD_SUCCESS;
}


/**
 * @brief Initialize a message enabling connection request sniffing mode
 * 
 * @param[in,out]   p_message           Pointer to the message structure to initialize
 * @param[in]       show_empty_packets  If set to true, empty packets will also be reported
 * @param[in]       show_adv            If set to true, advertisements received during the device lookup phase
 *                                      will be reported
 * @param[in]       channel             If specified, will listen only on this channel
 * @param[in]       p_bdaddr            Target BD address
 * 
 * @retval          WHAD_SUCCESS        Success.
 * @retval          WHAD_ERROR          Invalid message pointer.
 **/

whad_result_t whad_ble_sniff_conn_req(Message *p_message, bool show_empty_packets, bool show_adv,
                                      uint32_t channel, uint8_t *p_bdaddr)
{
    /* Sanity check. */
    if ((p_message == NULL) || (p_bdaddr == NULL))
    {
        return WHAD_ERROR;
    }

    /* Populate message fields. */
    p_message->which_msg = Message_ble_tag;
    p_message->msg.ble.which_msg = ble_Message_sniff_connreq_tag;
    p_message->msg.ble.msg.sniff_connreq.show_empty_packets = show_empty_packets;
    p_message->msg.ble.msg.sniff_connreq.show_advertisements = show_adv;
    p_message->msg.ble.msg.sniff_connreq.channel = channel;
    memcpy(p_message->msg.ble.msg.sniff_connreq.bd_address, p_bdaddr, 6);

    /* Success. */
    return WHAD_SUCCESS;
}


/**
 * @brief Parse a connection sniffing request message.
 * 
 * @param p_message         Pointer to a `Message` structure.
 * @param p_parameters      Pointer to a `whad_ble_sniff_connreq_params_t` structure
 * 
 * @return whad_result_t 
 */

whad_result_t whad_ble_sniff_conn_req_parse(Message *p_message, whad_ble_sniff_connreq_params_t *p_parameters)
{
    /* Sanity check. */
    if ((p_message == NULL) || (p_parameters == NULL))
    {
        return WHAD_ERROR;
    }

    /* Extract parameters. */
    p_parameters->channel = p_message->msg.ble.msg.sniff_connreq.channel;
    p_parameters->show_adv = p_message->msg.ble.msg.sniff_connreq.show_advertisements;
    p_parameters->show_empty_packets = p_message->msg.ble.msg.sniff_connreq.show_empty_packets;
    memcpy(p_parameters->p_bdaddr, p_message->msg.ble.msg.sniff_connreq.bd_address, 6);

    /* Success. */
    return WHAD_SUCCESS;
}




/**
 * @brief Initialize a message enabling access address sniffing
 * 
 * @param[in,out]   p_message           Pointer to the message structure to initialize
 * @param[in]       p_channelmap        Channel map to use for sniffing as a 5-byte array (40 bits)
 * 
 * @retval          WHAD_SUCCESS        Success.
 * @retval          WHAD_ERROR          Invalid message pointer.
 **/

whad_result_t whad_ble_sniff_access_address(Message *p_message, uint8_t *p_channelmap)
{
    /* Sanity check. */
    if ((p_message == NULL) || (p_channelmap == NULL))
    {
        return WHAD_ERROR;
    }

    /* Populate message fields. */
    p_message->which_msg = Message_ble_tag;
    p_message->msg.ble.which_msg = ble_Message_sniff_aa_tag;
    memcpy(p_message->msg.ble.msg.sniff_aa.monitored_channels, p_channelmap, 5);

    /* Success. */
    return WHAD_SUCCESS;
}


/**
 * @brief Parse an access address sniffing message.
 * 
 * @param[in]   p_message       Pointer to the message to parse
 * @param[out]  p_channelmap    Pointer to a 5-byte array that will contain the extracted channel map
 * 
 * @return whad_result_t 
 */

whad_result_t whad_ble_sniff_access_address_parse(Message *p_message, uint8_t *p_channelmap)
{
    /* Sanity check. */
    if ((p_message == NULL) || (p_channelmap == NULL))
    {
        return WHAD_ERROR;
    }

    /* Extract channel map. */
    memcpy(p_channelmap, p_message->msg.ble.msg.sniff_aa.monitored_channels, 5);

    /* Success. */
    return WHAD_SUCCESS;
}

/**
 * @brief Initialize a message enabling active connection sniffing
 * 
 * @param[in,out]   p_message           Pointer to the message structure to initialize
 * @param[in]       access_address      Access address of the active connection to sniff
 * @param[in]       crc_init            CRC initial value (seed)
 * @param[in]       hop_interval        Hopping interval
 * @param[in]       hop_increment       Hopping increment
 * @param[in]       p_channelmap        Provided channel map to use for synchronization
 * @param[in]       p_channels          A set of channels to use to dynamically reconstruct the channel map.
 *                                      This parameter is used when parallelized channel map recovery is enabled.
 * 
 * @retval          WHAD_SUCCESS        Success.
 * @retval          WHAD_ERROR          Invalid message pointer.
 **/

whad_result_t whad_ble_sniff_active_conn(Message *p_message, uint32_t access_address, uint32_t crc_init,
                                         uint32_t hop_interval, uint32_t hop_increment, uint8_t *p_channelmap,
                                         uint8_t *p_channels)
{
    /* Sanity check. */
    if ((p_message == NULL) || (p_channelmap == NULL) || (p_channels == NULL))
    {
        return WHAD_ERROR;
    }

    /* Populate message fields. */
    p_message->which_msg = Message_ble_tag;
    p_message->msg.ble.which_msg = ble_Message_sniff_conn_tag;
    p_message->msg.ble.msg.sniff_conn.access_address = access_address;
    p_message->msg.ble.msg.sniff_conn.crc_init = crc_init;
    p_message->msg.ble.msg.sniff_conn.hop_interval = hop_interval;
    p_message->msg.ble.msg.sniff_conn.hop_increment = hop_increment;
    memcpy(p_message->msg.ble.msg.sniff_conn.channel_map, p_channelmap, 5);
    memcpy(p_message->msg.ble.msg.sniff_conn.monitored_channels, p_channels, 5);

    /* Success. */
    return WHAD_SUCCESS;
}


/**
 * @brief Parse an active connection sniffing message.
 * 
 * @param[in]   p_message       Pointer to the message to parse 
 * @param[out]  p_parameters    Pointer to a `whad_ble_sniff_conn_params_t` structure that will contain the extracted
 *                              parameters.
 * @return whad_result_t 
 */


whad_result_t whad_ble_sniff_active_conn_parse(Message *p_message, whad_ble_sniff_conn_params_t *p_parameters)
{
    /* Sanity check. */
    if ((p_message == NULL) || (p_parameters == NULL))
    {
        return WHAD_ERROR;
    }

    /* Extract parameters from message. */
    p_parameters->access_address = p_message->msg.ble.msg.sniff_conn.access_address;
    p_parameters->crc_init = p_message->msg.ble.msg.sniff_conn.crc_init;
    p_parameters->hop_interval = p_message->msg.ble.msg.sniff_conn.hop_interval;
    p_parameters->hop_increment = p_message->msg.ble.msg.sniff_conn.hop_increment;
    memcpy(p_parameters->channelmap, p_message->msg.ble.msg.sniff_conn.channel_map, 5);
    memcpy(p_parameters->channels, p_message->msg.ble.msg.sniff_conn.monitored_channels, 5);

    /* Success. */
    return WHAD_SUCCESS; 
}

/**
 * @brief Initialize an active connection jamming message
 * 
 * @param[in,out]   p_message           Pointer to the message structure to initialize
 * @param[in]       access_address      Access address of the active connection to sniff
 * 
 * @retval          WHAD_SUCCESS        Success.
 * @retval          WHAD_ERROR          Invalid message pointer.
 **/

whad_result_t whad_ble_jam_active_conn(Message *p_message, uint32_t access_address)
{
    /* Sanity check. */
    if (p_message == NULL)
    {
        return WHAD_ERROR;
    }

    /* Populate message fields. */
    p_message->which_msg = Message_ble_tag;
    p_message->msg.ble.which_msg = ble_Message_jam_conn_tag;
    p_message->msg.ble.msg.jam_conn.access_address = access_address;

    /* Success. */
    return WHAD_SUCCESS; 
}


/**
 * @brief Parse an active connection jamming message
 * 
 * @param[in]       p_message           Pointer to the message structure to parse
 * @param[in, out]  p_access_address    Pointer to the extracted access address
 * 
 * @retval          WHAD_SUCCESS        Success.
 * @retval          WHAD_ERROR          Invalid message pointer.
 **/

whad_result_t whad_ble_jam_active_conn_parse(Message *p_message, uint32_t *p_access_address)
{
    /* Sanity check. */
    if ((p_message == NULL) || (p_access_address == NULL))
    {
        return WHAD_ERROR;
    }   

    /* Extract access address from message. */
    *p_access_address = p_message->msg.ble.msg.jam_conn.access_address;

    /* Success. */
    return WHAD_SUCCESS;
}


/**
 * @brief Initialize a message enabling scanning mode
 * 
 * @param[in,out]   p_message           Pointer to the message structure to initialize
 * @param[in]       active_scan         If set to true, the adapter will send SCAN_REQ PDU to get additional data
 * 
 * @retval          WHAD_SUCCESS        Success.
 * @retval          WHAD_ERROR          Invalid message pointer.
 **/

whad_result_t whad_ble_scan_mode(Message *p_message, bool active_scan)
{
    /* Sanity check. */
    if (p_message == NULL)
    {
        return WHAD_ERROR;
    }

    /* Populate message fields. */
    p_message->which_msg = Message_ble_tag;
    p_message->msg.ble.which_msg = ble_Message_scan_mode_tag;
    p_message->msg.ble.msg.scan_mode.active_scan = active_scan; 

    /* Success. */
    return WHAD_SUCCESS;   
}


/**
 * @brief Parse a scan mode message.
 * 
 * @param[in]   p_message         Pointer to the message to parse. 
 * @param[out]  p_active_scan     Pointer to a boolean value, if true an active scan has to be performed.
 * @return whad_result_t 
 */

whad_result_t whad_ble_scan_mode_parse(Message *p_message, bool *p_active_scan)
{
    /* Sanity check. */
    if ((p_message == NULL) || (p_active_scan == NULL))
    {
        return WHAD_ERROR;
    }    

    *p_active_scan = p_message->msg.ble.msg.scan_mode.active_scan;

    /* Success. */
    return WHAD_SUCCESS;
}


/**
 * @brief Initialize a message enabling advertising mode (and only advertising)
 * 
 * Advertising data and scan response data buffers cannot exceed 31-byte each.
 * 
 * @param[in,out]   p_message           Pointer to the message structure to initialize
 * @param[in]       p_adv_data          Pointer to a byte array containing the advertising data
 * @param[in]       adv_data_length     Length of advertising data
 * @param[in]       p_scanrsp_data      Pointer to a byte array containing the scan response data
 * @param[in]       adv_data_length     Length of scan response data
 * 
 * @retval          WHAD_SUCCESS        Success.
 * @retval          WHAD_ERROR          Invalid message pointer.
 **/

whad_result_t whad_ble_adv_mode(Message *p_message, uint8_t *p_adv_data, int adv_data_length, uint8_t *p_scanrsp_data, int scanrsp_data_length)
{
    /* Sanity check. */
    if ((p_message == NULL) || (p_adv_data == NULL) || (p_scanrsp_data == NULL))
    {
        return WHAD_ERROR;
    }

    /* Populate message fields. */
    p_message->which_msg = Message_ble_tag;
    p_message->msg.ble.which_msg = ble_Message_adv_mode_tag;

    /* Set avertising data, if provided. */
    if (adv_data_length > 0)
    {
        /* Cannot send more than 31 bytes in advertisement data. */
        if (adv_data_length > 31)
        {
            adv_data_length = 31;
        }
        p_message->msg.ble.msg.adv_mode.scan_data.size = adv_data_length;
        memcpy(p_message->msg.ble.msg.adv_mode.scan_data.bytes, p_adv_data, adv_data_length);
    }

    /* Set scan response data, if provided. */
    if (scanrsp_data_length > 0)
    {
        /* Cannot send more than 31 bytes in scan response data. */
        if (scanrsp_data_length > 31)
        {
            scanrsp_data_length = 31;
        }

        p_message->msg.ble.msg.adv_mode.scanrsp_data.size = scanrsp_data_length;
        memcpy(p_message->msg.ble.msg.adv_mode.scanrsp_data.bytes, p_scanrsp_data, scanrsp_data_length);
    }

    /* Success. */
    return WHAD_SUCCESS;   
}

whad_result_t whad_ble_adv_mode_parse(Message *p_message, whad_ble_adv_mode_params_t *p_parameters)
{
    /* Sanity check. */
    if ((p_message == NULL) || (p_parameters == NULL))
    {
        return WHAD_ERROR;
    }

    /* Extract advertising data from message. */
    p_parameters->adv_data_length = p_message->msg.ble.msg.adv_mode.scan_data.size;
    if ((p_parameters->adv_data_length > 0) && (p_parameters->adv_data_length < 31))
    {
        memcpy(
            p_parameters->adv_data,
            p_message->msg.ble.msg.adv_mode.scan_data.bytes,
            p_parameters->adv_data_length
        );
    }
    else
    {
        memset(p_parameters->adv_data, 0, 31);
    }

    /* Extract scan response from message. */
    p_parameters->scanrsp_data_length = p_message->msg.ble.msg.adv_mode.scanrsp_data.size;
    if ((p_parameters->scanrsp_data_length > 0) && (p_parameters->scanrsp_data_length < 31))
    {
        memcpy(
            p_parameters->scanrsp_data,
            p_message->msg.ble.msg.adv_mode.scanrsp_data.bytes,
            p_parameters->scanrsp_data_length
        );
    }
    else
    {
        memset(p_parameters->scanrsp_data, 0, 31);
    }

    /* Success. */
    return WHAD_SUCCESS;
}


/** TODO Not yet supported, need some fix in whad-protocol. */
whad_result_t whad_ble_set_adv_data(Message *p_message, uint8_t *p_adv_data, int adv_data_length, uint8_t *p_scanrsp_data, int scanrsp_data_length)
{
    /* Sanity check. */
    if ((p_message == NULL) || (p_adv_data == NULL) || (p_scanrsp_data == NULL))
    {
        return WHAD_ERROR;
    }

    /* Populate message fields. */
    p_message->which_msg = Message_ble_tag;
    p_message->msg.ble.which_msg = ble_Message_set_adv_data_tag;

    /* Set avertising data, if provided. */
    if (adv_data_length > 0)
    {
        /* Cannot send more than 31 bytes in advertisement data. */
        if (adv_data_length > 31)
        {
            adv_data_length = 31;
        }
        //p_message->msg.ble.msg.adv_mode.scan_data.size = scan_data_length;
        //memcpy(p_message->msg.ble.msg.adv_mode.scan_data.bytes, p_scan_data, scan_data_length);
    }

    /* Set scan response data, if provided. */
    if (scanrsp_data_length > 0)
    {
        /* Cannot send more than 31 bytes in scan response data. */
        if (scanrsp_data_length > 31)
        {
            scanrsp_data_length = 31;
        }

        //p_message->msg.ble.msg.adv_mode.scanrsp_data.size = scanrsp_data_length;
        //memcpy(p_message->msg.ble.msg.adv_mode.scanrsp_data.bytes, p_scanrsp_data, scanrsp_data_length);
    }

    /* Success. */
    return WHAD_SUCCESS;   
}

/* TODO */
whad_result_t whad_ble_set_adv_data_parse(Message *p_message, uint8_t *p_adv_data, int *p_adv_data_length, 
                                    uint8_t *p_scanrsp_data, int *p_scanrsp_data_length)
{
    return WHAD_ERROR;
}


/**
 * @brief Initialize a message enabling central mode.
 * 
 * @param[in,out]   p_message           Pointer to the message structure to initialize
 * 
 * @retval          WHAD_SUCCESS        Success.
 * @retval          WHAD_ERROR          Invalid message pointer.
 **/

whad_result_t whad_ble_central_mode(Message *p_message)
{
    /* Sanity check. */
    if (p_message == NULL)
    {
        return WHAD_ERROR;
    }

    /* Populate message fields. */
    p_message->which_msg = Message_ble_tag;
    p_message->msg.ble.which_msg = ble_Message_central_mode_tag; 

    /* Success. */
    return WHAD_SUCCESS;
}


/**
 * @brief Initialize a message to initiate a connection to a specific device identified by its BD address.
 *  
 * @param[in,out]   p_message           Pointer to the message structure to initialize
 * @param[in]       p_bdaddr            Pointer to the BD address of the device to connect to, as a 6-byte array
 * @param[in]       addr_type           Device address type
 * @param[in]       access_address      Specify the connection access address, if supported by the adapter
 * @param[in]       p_channelmap        Channel map to use for the connectionm if supported by the adapter
 * @param[in]       hop_interval        Hop interval to use for the connection, if supported by the adapter
 * @param[in]       hop_increment       Hop increment to use for the connection, if supported by the adapter
 * @param[in]       crc_init            CRC initial value (seed) to use for the connection, if supported by the adapter
 * 
 * @retval          WHAD_SUCCESS        Success.
 * @retval          WHAD_ERROR          Invalid message pointer.
 **/

whad_result_t whad_ble_connect_to(Message *p_message, uint8_t *p_bdaddr, whad_ble_addrtype_t addr_type, uint32_t access_address, uint8_t *p_channelmap, uint32_t hop_interval, uint32_t hop_increment, uint32_t crc_init)
{
    /* Sanity check. */
    if ((p_message == NULL) || (p_bdaddr == NULL))
    {
        return WHAD_ERROR;
    }

    /* Populate message fields. */
    p_message->which_msg = Message_ble_tag;
    p_message->msg.ble.which_msg = ble_Message_connect_tag;

    /* Mandatory fields. */
    p_message->msg.ble.msg.connect.addr_type = (ble_BleAddrType)addr_type;
    memcpy(p_message->msg.ble.msg.connect.bd_address, p_bdaddr, 6);

    /* Optional fields. */
    if (access_address != 0)
    {
        p_message->msg.ble.msg.connect.has_access_address = true;
        p_message->msg.ble.msg.connect.access_address = access_address;
    }

    if (p_channelmap != NULL)
    {
        p_message->msg.ble.msg.connect.has_channel_map = true;
        memcpy(p_message->msg.ble.msg.connect.channel_map, p_channelmap, 5);
    }

    if (hop_interval > 0)
    {
        p_message->msg.ble.msg.connect.has_hop_interval = true;
        p_message->msg.ble.msg.connect.hop_interval = hop_interval;
    }
    
    if (hop_increment > 0)
    {
        p_message->msg.ble.msg.connect.has_hop_increment = true;
        p_message->msg.ble.msg.connect.hop_increment = hop_increment;
    }

    if (crc_init != 0)
    {
        p_message->msg.ble.msg.connect.has_crc_init = true;
        p_message->msg.ble.msg.connect.crc_init = crc_init;
    }

    /* Success. */
    return WHAD_SUCCESS;
}


/**
 * @brief Parse a message to initiate a connection to a specific device identified by its BD address.
 *  
 * @param[in]       p_message           Pointer to the message structure to initialize
 * @param[in,out]   p_parameters        Pointer to a `whad_ble_connect_params_t` structure that will receive the
 *                                      extracted information
 * 
 * @retval          WHAD_SUCCESS        Success.
 * @retval          WHAD_ERROR          Invalid message pointer or parameters pointer.
 **/

whad_result_t whad_ble_connect_to_parse(Message *p_message, whad_ble_connect_params_t *p_parameters)
{
    /* Sanity check. */
    if ((p_message == NULL) || (p_parameters == NULL))
    {
        return WHAD_ERROR;
    }

    /* Extract BD address and type. */
    memcpy(p_parameters->bdaddr, p_message->msg.ble.msg.connect.bd_address, 6);
    p_parameters->addr_type = (whad_ble_addrtype_t)p_message->msg.ble.msg.connect.addr_type;

    /* Retrieve connection access address. */
    if (p_message->msg.ble.msg.connect.has_access_address)
    {
        p_parameters->access_address = p_message->msg.ble.msg.connect.access_address;
    }
    else
    {
        /* Set access address to 0 (invalid value for Bluetooth Spec). */
        p_parameters->access_address = 0;
    }
    
    /* Retrieve hop interval, if provided. */
    if (p_message->msg.ble.msg.connect.has_hop_interval)
    {
        p_parameters->hop_interval = p_message->msg.ble.msg.connect.hop_interval;
    }
    else
    {
        /* By default, hop interval cannot be 0. We are using this value to indicate that
           we don't have this parameter (since it's optional). */
        p_parameters->hop_interval = 0;
    }

    /* Retrieve hop increment, if present. */
    if (p_message->msg.ble.msg.connect.has_hop_increment)
    {
        p_parameters->hop_increment = p_message->msg.ble.msg.connect.hop_increment;
    }
    else
    {
        /* By default, hop increment cannot be 0. We are using this value to indicate that
           we don't have this parameter (since it's optional). */
        p_parameters->hop_increment = 0;
    }

    /* Retrieve CRC Init value, if provided. */
    if (p_message->msg.ble.msg.connect.has_crc_init)
    {
        p_parameters->crc_init = p_message->msg.ble.msg.connect.crc_init;
    }
    else
    {
        /* CRC Init (seed) is set to 0 by default. */
        p_parameters->crc_init = 0;
    }

    /* Retrieve channel map. */
    if (p_message->msg.ble.msg.connect.has_channel_map)
    {
        memcpy(p_parameters->channelmap, p_message->msg.ble.msg.connect.channel_map, 5);
    }
    else
    {
        /* Set channel map to 0. */
        memset(p_parameters->channelmap, 0, 5);
    }

    /* Success. */
    return WHAD_SUCCESS;
}


/**
 * @brief Initialize a message to send a raw PDU to a target device in an established connection
 *  
 * @param[in,out]   p_message           Pointer to the message structure to initialize
 * @param[in]       direction           Specify the target device (initiator or advertiser)
 * @param[in]       conn_handle         Connection handle
 * @param[in]       access_address      Specify the access address to use when sending the PDU
 * @param[in]       p_pdu               Pointer to a byte array containing the PDU to send
 * @param[in]       length              PDU length in bytes
 * @param[in]       crc                 PDU CRC value
 * @param[in]       encrypt             If set to true, PDU will be encrypted with the current cryptographic material
 *                                      associated with the target connection
 * 
 * @retval          WHAD_SUCCESS        Success.
 * @retval          WHAD_ERROR          Invalid message pointer.
 **/

whad_result_t whad_ble_send_raw_pdu(Message *p_message, whad_ble_direction_t direction, uint32_t conn_handle,
                                    uint32_t access_address, uint8_t *p_pdu, int length, uint32_t crc, bool encrypt)
{
    /* Sanity check. */
    if ((p_message == NULL) || (p_pdu == NULL))
    {
        return WHAD_ERROR;
    }

    /* Populate message fields. */
    p_message->which_msg = Message_ble_tag;
    p_message->msg.ble.which_msg = ble_Message_send_raw_pdu_tag;

    /* Set message parameters. */
    p_message->msg.ble.msg.send_raw_pdu.direction = (ble_BleDirection)direction;
    p_message->msg.ble.msg.send_raw_pdu.conn_handle = conn_handle;
    p_message->msg.ble.msg.send_raw_pdu.access_address = access_address;
    p_message->msg.ble.msg.send_raw_pdu.crc = crc;
    p_message->msg.ble.msg.send_raw_pdu.encrypt = encrypt;

    /* Copy PDU in memory. */
    memcpy(p_message->msg.ble.msg.send_raw_pdu.pdu.bytes, p_pdu, length);

    /* Success. */
    return WHAD_SUCCESS;
}


/**
 * @brief parse a message to send a raw PDU to a target device in an established connection
 *  
 * @param[in,out]   p_message           Pointer to the message structure to initialize
 * @param[in,out]   p_parameters        Pointer to a `whad_ble_pdu_params_t` structure that will receive the
 *                                      extracted information
 * 
 * @retval          WHAD_SUCCESS        Success.
 * @retval          WHAD_ERROR          Invalid message pointer.
 **/

whad_result_t whad_ble_send_raw_pdu_parse(Message *p_message, whad_ble_pdu_params_t *p_parameters)
{
    /* Sanity check. */
    if ((p_message == NULL) || (p_parameters == NULL))
    {
        return WHAD_ERROR;
    }

    /* Extract raw PDU information. */
    p_parameters->access_address = p_message->msg.ble.msg.send_raw_pdu.access_address;
    p_parameters->conn_handle = p_message->msg.ble.msg.send_raw_pdu.conn_handle;
    p_parameters->crc = p_message->msg.ble.msg.send_raw_pdu.crc;
    p_parameters->direction = (whad_ble_direction_t)p_message->msg.ble.msg.send_raw_pdu.direction;
    p_parameters->encrypt = p_message->msg.ble.msg.send_raw_pdu.encrypt;
    p_parameters->length = p_message->msg.ble.msg.send_raw_pdu.pdu.size;
    p_parameters->p_pdu = p_message->msg.ble.msg.send_raw_pdu.pdu.bytes;

    /* Success. */
    return WHAD_SUCCESS;
}


/**
 * @brief Initialize a message to send a PDU to a target device in an established connection
 *  
 * @param[in,out]   p_message           Pointer to the message structure to initialize
 * @param[in]       direction           Specify the target device (initiator or advertiser)
 * @param[in]       conn_handle         Connection handle
 * @param[in]       p_pdu               Pointer to a byte array containing the PDU to send
 * @param[in]       length              PDU length in bytes
 * @param[in]       encrypt             If set to true, PDU will be encrypted with the current cryptographic material
 *                                      associated with the target connection
 * 
 * @retval          WHAD_SUCCESS        Success.
 * @retval          WHAD_ERROR          Invalid message pointer.
 **/

whad_result_t whad_ble_send_pdu(Message *p_message, whad_ble_direction_t direction, uint32_t conn_handle,
                                uint8_t *p_pdu, int length, bool encrypt)
{
    /* Sanity check. */
    if ((p_message == NULL) || (p_pdu == NULL))
    {
        return WHAD_ERROR;
    }

    /* Populate message fields. */
    p_message->which_msg = Message_ble_tag;
    p_message->msg.ble.which_msg = ble_Message_send_pdu_tag;
    p_message->msg.ble.msg.send_pdu.direction = (ble_BleDirection)direction;
    p_message->msg.ble.msg.send_pdu.conn_handle = conn_handle;
    p_message->msg.ble.msg.send_pdu.encrypt = encrypt;

    /* Copy PDU in memory. */
    memcpy(p_message->msg.ble.msg.send_raw_pdu.pdu.bytes, p_pdu, length);

    /* Success. */
    return WHAD_SUCCESS;
}


/**
 * @brief Parse a message to send a raw PDU to a target device in an established connection
 *  
 * @param[in,out]   p_message           Pointer to the message structure to initialize
 * @param[in,out]   p_parameters        Pointer to a `whad_ble_pdu_params_t` structure that will receive the
 *                                      extracted information
 * 
 * @retval          WHAD_SUCCESS        Success.
 * @retval          WHAD_ERROR          Invalid message pointer.
 **/

whad_result_t whad_ble_send_pdu_parse(Message *p_message, whad_ble_pdu_params_t *p_parameters)
{
    /* Sanity check. */
    if ((p_message == NULL) || (p_parameters == NULL))
    {
        return WHAD_ERROR;
    }

    /* Extract information. */
    p_parameters->access_address = 0;
    p_parameters->crc = 0;
    p_parameters->conn_handle = p_message->msg.ble.msg.send_pdu.conn_handle;
    p_parameters->direction = (whad_ble_direction_t)p_message->msg.ble.msg.send_pdu.direction;
    p_parameters->encrypt = p_message->msg.ble.msg.send_pdu.encrypt;
    p_parameters->length = p_message->msg.ble.msg.send_pdu.pdu.size;
    p_parameters->p_pdu = p_message->msg.ble.msg.send_pdu.pdu.bytes;

    /* Success. */
    return WHAD_SUCCESS;
}


/**
 * @brief Initialize a message to disconnect from a device
 *  
 * @param[in,out]   p_message           Pointer to the message structure to initialize
 * @param[in]       conn_handle         Connection handle
 * 
 * @retval          WHAD_SUCCESS        Success.
 * @retval          WHAD_ERROR          Invalid message pointer.
 **/

whad_result_t whad_ble_disconnect(Message *p_message, uint32_t conn_handle)
{
    /* Sanity check. */
    if (p_message == NULL)
    {
        return WHAD_ERROR;
    }

    /* Populate message fields. */
    p_message->which_msg = Message_ble_tag;
    p_message->msg.ble.which_msg = ble_Message_disconnect_tag;
    p_message->msg.ble.msg.disconnect.conn_handle = conn_handle;

    /* Success. */
    return WHAD_SUCCESS;
}


/**
 * @brief Parse a message to disconnect from a device
 *  
 * @param[in]       p_message           Pointer to the message structure to initialize
 * @param[in,out]   p_conn_handle       Pointer to the retrieved connection handle
 * 
 * @retval          WHAD_SUCCESS        Success.
 * @retval          WHAD_ERROR          Invalid message pointer or connection handle pointer.
 **/

whad_result_t whad_ble_disconnect_parse(Message *p_message, uint32_t *p_conn_handle)
{
    /* Sanity check. */
    if ((p_message == NULL) || (p_conn_handle == NULL))
    {
        return WHAD_ERROR;
    }

    /* Extract connection handle. */
    *p_conn_handle = p_message->msg.ble.msg.disconnect.conn_handle;

    /* Success. */
    return WHAD_SUCCESS;
}


/**
 * @brief Initialize a message to enable Peripheral mode
 *  
 * @param[in,out]   p_message           Pointer to the message structure to initialize
 * @param[in]       p_adv_data          Pointer to the advertising data to use when advertising this peripheral
 * @param[in]       adv_data_length     Length of advertising data in bytes (max length: 31)
 * @param[in]       p_scanrsp_data      Pointer to the scan response data to use when advertising this peripheral
 * @param[in]       scanrsp_data_length Length of scan response data in bytes (max length: 31)
 * 
 * @retval          WHAD_SUCCESS        Success.
 * @retval          WHAD_ERROR          Invalid message pointer.
 **/

whad_result_t whad_ble_peripheral_mode(Message *p_message, uint8_t *p_adv_data, int adv_data_length, uint8_t *p_scanrsp_data, int scanrsp_data_length)
{
    /* Sanity check. */
    if ((p_message == NULL) || (p_adv_data == NULL) || (p_scanrsp_data == NULL))
    {
        return WHAD_ERROR;
    }

    /* Populate message fields. */
    p_message->which_msg = Message_ble_tag;
    p_message->msg.ble.which_msg = ble_Message_periph_mode_tag;

    /* Set avertising data, if provided. */
    if (adv_data_length > 0)
    {
        /* Cannot send more than 31 bytes in advertisement data. */
        if (adv_data_length > 31)
        {
            adv_data_length = 31;
        }
        p_message->msg.ble.msg.adv_mode.scan_data.size = adv_data_length;
        memcpy(p_message->msg.ble.msg.adv_mode.scan_data.bytes, p_adv_data, adv_data_length);
    }

    /* Set scan response data, if provided. */
    if (scanrsp_data_length > 0)
    {
        /* Cannot send more than 31 bytes in scan response data. */
        if (scanrsp_data_length > 31)
        {
            scanrsp_data_length = 31;
        }

        p_message->msg.ble.msg.adv_mode.scanrsp_data.size = scanrsp_data_length;
        memcpy(p_message->msg.ble.msg.adv_mode.scanrsp_data.bytes, p_scanrsp_data, scanrsp_data_length);
    }

    /* Success. */
    return WHAD_SUCCESS;   
}


whad_result_t whad_ble_peripheral_mode_parse(Message *p_message, whad_ble_adv_mode_params_t *p_parameters)
{
    /* Sanity check. */
    if ((p_message == NULL) || (p_parameters ==NULL))
    {
        return WHAD_ERROR;
    }

 /* Extract advertising data from message. */
    p_parameters->adv_data_length = p_message->msg.ble.msg.periph_mode.scan_data.size;
    if ((p_parameters->adv_data_length > 0) && (p_parameters->adv_data_length < 31))
    {
        memcpy(
            p_parameters->adv_data,
            p_message->msg.ble.msg.periph_mode.scan_data.bytes,
            p_parameters->adv_data_length
        );
    }
    else
    {
        memset(p_parameters->adv_data, 0, 31);
    }

    /* Extract scan response from message. */
    p_parameters->scanrsp_data_length = p_message->msg.ble.msg.periph_mode.scanrsp_data.size;
    if ((p_parameters->scanrsp_data_length > 0) && (p_parameters->scanrsp_data_length < 31))
    {
        memcpy(
            p_parameters->scanrsp_data,
            p_message->msg.ble.msg.periph_mode.scanrsp_data.bytes,
            p_parameters->scanrsp_data_length
        );
    }
    else
    {
        memset(p_parameters->scanrsp_data, 0, 31);
    }

    /* Success. */
    return WHAD_SUCCESS;
}

/**
 * @brief Initialize a message to start the current mode
 *  
 * @param[in,out]   p_message           Pointer to the message structure to initialize
 * 
 * @retval          WHAD_SUCCESS        Success.
 * @retval          WHAD_ERROR          Invalid message pointer.
 **/

whad_result_t whad_ble_start(Message *p_message)
{
    /* Sanity check. */
    if (p_message == NULL)
    {
        return WHAD_ERROR;
    }

    /* Populate message fields. */
    p_message->which_msg = Message_ble_tag;
    p_message->msg.ble.which_msg = ble_Message_start_tag;

    /* Success. */
    return WHAD_SUCCESS;
}


/**
 * @brief Initialize a message to stop the current mode
 *  
 * @param[in,out]   p_message           Pointer to the message structure to initialize
 * 
 * @retval          WHAD_SUCCESS        Success.
 * @retval          WHAD_ERROR          Invalid message pointer.
 **/

whad_result_t whad_ble_stop(Message *p_message)
{
    /* Sanity check. */
    if (p_message == NULL)
    {
        return WHAD_ERROR;
    }

    /* Populate message fields. */
    p_message->which_msg = Message_ble_tag;
    p_message->msg.ble.which_msg = ble_Message_stop_tag;

    /* Success. */
    return WHAD_SUCCESS;
}


/**
 * @brief Initialize a message to hijack the master (initiator) of an existing connection
 *  
 * @param[in,out]   p_message           Pointer to the message structure to initialize
 * @param[in]       access_address      Access address of the target connection
 * 
 * @retval          WHAD_SUCCESS        Success.
 * @retval          WHAD_ERROR          Invalid message pointer.
 **/

whad_result_t whad_ble_hijack_master(Message *p_message, uint32_t access_address)
{
    /* Sanity check. */
    if (p_message == NULL)
    {
        return WHAD_ERROR;
    }

    /* Populate message fields. */
    p_message->which_msg = Message_ble_tag;
    p_message->msg.ble.which_msg = ble_Message_hijack_master_tag;
    p_message->msg.ble.msg.hijack_master.access_address = access_address;

    /* Success. */
    return WHAD_SUCCESS;
}


/**
 * @brief Parse a message to hijack the master (initiator) of an existing connection
 *  
 * @param[in]       p_message           Pointer to the message structure to parse
 * @param[in,out]   p_access_address    pointer to the extracted access address
 * 
 * @retval          WHAD_SUCCESS        Success.
 * @retval          WHAD_ERROR          Invalid message pointer.
 **/

whad_result_t whad_ble_hijack_master_parse(Message *p_message, uint32_t *p_access_address)
{
    /* Sanity check. */
    if ((p_message == NULL) || (p_access_address == NULL))
    {
        return WHAD_ERROR;
    }

    /* Extract access address from message. */
    *p_access_address = p_message->msg.ble.msg.hijack_master.access_address;

    /* Success. */
    return WHAD_SUCCESS;
}


/**
 * @brief Initialize a message to hijack the slave (advertiser) of an existing connection
 *  
 * @param[in,out]   p_message           Pointer to the message structure to initialize
 * @param[in]       access_address      Access address of the target connection
 * 
 * @retval          WHAD_SUCCESS        Success.
 * @retval          WHAD_ERROR          Invalid message pointer.
 **/

whad_result_t whad_ble_hijack_slave(Message *p_message, uint32_t access_address)
{
    /* Sanity check. */
    if (p_message == NULL)
    {
        return WHAD_ERROR;
    }

    /* Populate message fields. */
    p_message->which_msg = Message_ble_tag;
    p_message->msg.ble.which_msg = ble_Message_hijack_slave_tag;
    p_message->msg.ble.msg.hijack_slave.access_address = access_address;

    /* Success. */
    return WHAD_SUCCESS;
}


/**
 * @brief Parse a message to hijack the slave (advertiser) of an existing connection
 *  
 * @param[in]       p_message           Pointer to the message structure to parse
 * @param[in,out]   p_access_address    pointer to the extracted access address
 * 
 * @retval          WHAD_SUCCESS        Success.
 * @retval          WHAD_ERROR          Invalid message pointer.
 **/

whad_result_t whad_ble_hijack_slave_parse(Message *p_message, uint32_t *p_access_address)
{
    /* Sanity check. */
    if ((p_message == NULL) || (p_access_address == NULL))
    {
        return WHAD_ERROR;
    }

    /* Extract access address from message. */
    *p_access_address = p_message->msg.ble.msg.hijack_slave.access_address;

    /* Success. */
    return WHAD_SUCCESS;
}


/**
 * @brief Initialize a message to hijack both the master (initiator) and the slave (advertiser) of an existing connection
 *  
 * @param[in,out]   p_message           Pointer to the message structure to initialize
 * @param[in]       access_address      Access address of the target connection
 * 
 * @retval          WHAD_SUCCESS        Success.
 * @retval          WHAD_ERROR          Invalid message pointer.
 **/

whad_result_t whad_ble_hijack_both(Message *p_message, uint32_t access_address)
{
    /* Sanity check. */
    if (p_message == NULL)
    {
        return WHAD_ERROR;
    }

    /* Populate message fields. */
    p_message->which_msg = Message_ble_tag;
    p_message->msg.ble.which_msg = ble_Message_hijack_both_tag;
    p_message->msg.ble.msg.hijack_both.access_address = access_address;

    /* Success. */
    return WHAD_SUCCESS;
}


/**
 * @brief Parse a message to hijack both the master (initiator) and the slave (advertiser) of
 *        an existing connection
 *  
 * @param[in]       p_message           Pointer to the message structure to parse
 * @param[in,out]   p_access_address    pointer to the extracted access address
 * 
 * @retval          WHAD_SUCCESS        Success.
 * @retval          WHAD_ERROR          Invalid message pointer.
 **/

whad_result_t whad_ble_hijack_both_parse(Message *p_message, uint32_t *p_access_address)
{
    /* Sanity check. */
    if ((p_message == NULL) || (p_access_address == NULL))
    {
        return WHAD_ERROR;
    }

    /* Extract access address from message. */
    *p_access_address = p_message->msg.ble.msg.hijack_both.access_address;

    /* Success. */
    return WHAD_SUCCESS;
}


/**
 * @brief Initialize a message to enable encryption
 * 
 * The `p_ll_key` and `p_ll_iv` parameters will be used by WHAD adapters supporting BLE encryption while
 * `p_key`, `p_rand` and `p_ediv` will be used by adapters that cannot control the link-layer. All these
 * fields must be set.
 *  
 * @param[in,out]   p_message           Pointer to the message structure to initialize
 * @param[in]       conn_handle         Connection handle
 * @param[in]       enabled             If set to true, encryption is immediately enabled. If set to false,
 *                                      cryptographic material is provided but encryption must be started later
 * @param[in]       p_ll_key            Pointer to a 16-byte array containing the encryption key (LTK)
 * @param[in]       p_ll_iv             Pointer to a 8-byte array containing the encryption IV
 * @param[in]       p_key               Pointer to a 16-byte array containing the encryption key
 * @param[in]       p_rand              Pointer to a 8-byte array containing the randomizer
 * @param[in]       p_ediv              Pointer to a 2-byte array containing the diversifier
 * 
 * @retval          WHAD_SUCCESS        Success.
 * @retval          WHAD_ERROR          Invalid message pointer.
 **/

whad_result_t whad_ble_set_encryption(Message *p_message, uint32_t conn_handle, bool enabled, uint8_t *p_ll_key, uint8_t *p_ll_iv, uint8_t *p_key, uint8_t *p_rand, uint8_t *p_ediv)
{
    /* Sanity check. */
    if ((p_message == NULL) || (p_ll_key == NULL) || (p_ll_iv == NULL) || (p_key == NULL) || (p_rand == NULL) || (p_ediv == NULL))
    {
        return WHAD_ERROR;
    }

    /* Populate message fields. */
    p_message->which_msg = Message_ble_tag;
    p_message->msg.ble.which_msg = ble_Message_encryption_tag;
    p_message->msg.ble.msg.encryption.conn_handle = conn_handle;
    p_message->msg.ble.msg.encryption.enabled = enabled;

    /* Copy cryptographic material. */
    memcpy(p_message->msg.ble.msg.encryption.ll_key, p_ll_key, 16);
    memcpy(p_message->msg.ble.msg.encryption.ll_iv, p_ll_iv, 8);
    memcpy(p_message->msg.ble.msg.encryption.key, p_key, 16);
    memcpy(p_message->msg.ble.msg.encryption.rand, p_rand, 8);
    memcpy(p_message->msg.ble.msg.encryption.ediv, p_ediv, 2);

    /* Success. */
    return WHAD_SUCCESS;
}


/**
 * @brief       Parse a BLE set encryption message and extract encryption parameters.   
 * 
 * @param[in]   p_message       Pointer to a `Message` structure
 * @param[out]  p_parameters    Pointer to a `whad_ble_encryption_params_t` structure
 * 
 * @return whad_result_t
 */

whad_result_t whad_ble_set_encryption_parse(Message *p_message, whad_ble_encryption_params_t *p_parameters)
{
    /* Sanity check. */
    if ((p_message == NULL) || (p_parameters == NULL))
    {
        return WHAD_ERROR;
    }

    /* Extract encryption parameters. */
    p_parameters->conn_handle = p_message->msg.ble.msg.encryption.conn_handle;
    p_parameters->enabled = p_message->msg.ble.msg.encryption.enabled;
    p_parameters->p_ll_key = p_message->msg.ble.msg.encryption.ll_key;
    p_parameters->p_ll_iv = p_message->msg.ble.msg.encryption.ll_iv;
    p_parameters->p_key = p_message->msg.ble.msg.encryption.key;
    p_parameters->p_rand = p_message->msg.ble.msg.encryption.rand;
    p_parameters->p_ediv = p_message->msg.ble.msg.encryption.ediv;

    /* Success. */
    return WHAD_SUCCESS;
}


/**
 * @brief Initialize a message to enable reactive jamming mode.
 * 
 * In reactive jamming, we are waiting for a PDU matching a specific pattern and start jamming right after
 * having receiving this pattern. This can be done only on a single channel that needs to be specified.
 *  
 * @param[in,out]   p_message           Pointer to the message structure to initialize
 * @param[in]       channel             Channel to listen on
 * @param[in]       p_pattern           Pointer to a byte array specifying a matching pattern
 * @param[in]       pattern_length      Length of the matching pattern in bytes
 * @param[in]       position            Specify the expected offset in a PDU of the matching pattern
 * 
 * @retval          WHAD_SUCCESS        Success.
 * @retval          WHAD_ERROR          Invalid message pointer.
 **/

whad_result_t whad_ble_reactive_jam(Message *p_message, uint32_t channel, uint8_t *p_pattern, int pattern_length, uint32_t position)
{
    /* Sanity check. */
    if (p_message == NULL)
    {
        return WHAD_ERROR;
    }

    /* Populate message fields. */
    p_message->which_msg = Message_ble_tag;
    p_message->msg.ble.which_msg = ble_Message_reactive_jam_tag;
    p_message->msg.ble.msg.reactive_jam.channel = channel;
    p_message->msg.ble.msg.reactive_jam.position = position;
    p_message->msg.ble.msg.reactive_jam.pattern.size = pattern_length;
    if (pattern_length > 0)
    {
        if (pattern_length > 20)
        {
            /* Pattern is too long, return error. */
            return WHAD_ERROR;
        }
        else
        {
            /* Copy pattern. */
            memcpy(p_message->msg.ble.msg.reactive_jam.pattern.bytes, p_pattern, pattern_length);
        }
    }

    /* Success. */
    return WHAD_SUCCESS;
}


whad_result_t whad_ble_reactive_jam_parse(Message *p_message, whad_ble_reactive_jam_params_t *p_parameters)
{
    /* Sanity check. */
    if ((p_message == NULL) || (p_parameters == NULL))
    {
        return WHAD_ERROR;
    }   

    /* Extract information from message. */
    p_parameters->channel = p_message->msg.ble.msg.reactive_jam.channel;
    p_parameters->position = p_message->msg.ble.msg.reactive_jam.position;
    p_parameters->pattern_length = p_message->msg.ble.msg.reactive_jam.pattern.size;

    if ((p_parameters->pattern_length > 0) && (p_parameters->pattern_length <= 20))
    {
        memcpy(p_parameters->pattern, p_message->msg.ble.msg.reactive_jam.pattern.bytes,
               p_parameters->pattern_length);
    }
    else
    {
        if (p_parameters->pattern_length > 20)
        {
            /* Pattern size exceeds storage capacity. */
            return WHAD_ERROR;
        }
        else
        {
            /* Fill pattern with zero bytes. */
            memset(p_parameters->pattern, 0, 20);
        }
    }

    /* Success. */
    return WHAD_SUCCESS;
}


/**
 * @brief Copy a sequence of prepared packets into a BLE prepared sequence message.
 * 
 * @param[in,out]   p_message         Pointer to the target message structure
 * @param[in]       p_packets         Pointer to an array of prepared packets
 * @param[in]       pkt_count         Number of packets to copy
 * 
 * @retval          WHAD_SUCCESS        Success.
 * @retval          WHAD_ERROR          Invalid message pointer.       
 */

whad_result_t _whad_ble_sequence_copy_packets(Message *p_message, whad_prepared_packet_t *p_packets, int pkt_count)
{
    int i;

    /* Set number of packets in the sequence. */
    p_message->msg.ble.msg.prepare.sequence_count = pkt_count;
    
    /* Copy prepared packets into our structure. */
    if (pkt_count > 0)
    {
        for (i=0; i<pkt_count; i++)
        {
            p_message->msg.ble.msg.prepare.sequence[i].packet.size = p_packets[i].length;

            /* If length is not zero and below maximum packet size ... */
            if ((p_packets[i].length > 0) && (p_packets[i].length <= BLE_PREPSEQ_PACKET_MAX_SIZE))
            {
                /* ... then we add this packet to the sequence. */
                memcpy(p_message->msg.ble.msg.prepare.sequence[i].packet.bytes, p_packets[i].p_bytes,
                       p_packets[i].length);
            }
            else
            {
                /* Packet is too big, return error. */
                return WHAD_ERROR;
            }
        }
    }

    /* Success. */
    return WHAD_SUCCESS;
}


whad_result_t whad_ble_prepare_sequence_get_trigger_type(Message *p_message, whad_ble_trigger_t *p_trigger_type)
{
    /* Sanity check. */
    if ((p_message == NULL) || (p_trigger_type == NULL))
    {
        return WHAD_ERROR;
    }

    /* Determine the trigger type. */
    switch (p_message->msg.ble.msg.prepare.trigger.which_trigger)
    {
        /* Manual mode. */
        case ble_PrepareSequenceCmd_Trigger_manual_tag:
        {
            *p_trigger_type = BLE_MANUAL_TRIGGER;
            return WHAD_SUCCESS;
        }
        break;

        case ble_PrepareSequenceCmd_Trigger_connection_event_tag:
        {
            *p_trigger_type = BLE_CONNEVT_TRIGGER;
            return WHAD_SUCCESS;
        }
        break;

        case ble_PrepareSequenceCmd_Trigger_reception_tag:
        {
            *p_trigger_type = BLE_PATTERN_TRIGGER;
            return WHAD_SUCCESS;
        }
        break;


        default:
            return WHAD_ERROR;
    }

}

/**
 * @brief Initialize a message to send a sequence of PDU when a matching PDU is received
 *  
 * @param[in,out]   p_message           Pointer to the message structure to initialize
 * @param[in]       p_pattern           Pointer to a byte array containing the matching pattern
 * @param[in]       p_mask              Pointer to a byte array specifying the matching mask to apply to the pattern
 * @param[in]       length              Pattern and mask length
 * @param[in]       offset              Offset at which the matching pattern must be applied
 * @param[in]       id                  Prepared sequence identifier
 * @param[in]       direction           PDU sequence direction
 * @param[in]       p_packets           Pointer to an array of prepared packets
 * @param[in]       pkt_count           Number of packets in the prepared packets sequence
 * 
 * @retval          WHAD_SUCCESS        Success.
 * @retval          WHAD_ERROR          Invalid pointer or packet size exceed the allowed size.
 **/

whad_result_t whad_ble_prepare_sequence_on_recv(Message *p_message, uint8_t *p_pattern, uint8_t *p_mask, int length,
                                                int offset, uint32_t id, whad_ble_direction_t direction, whad_prepared_packet_t *p_packets, int pkt_count) 
{
    /* Sanity check. */
    if ((p_message == NULL) || (p_pattern == NULL) || (p_mask == NULL) || (p_packets))
    {
        return WHAD_ERROR;
    }

    /* Populate message fields. */
    p_message->which_msg = Message_ble_tag;
    p_message->msg.ble.which_msg = ble_Message_prepare_tag;
    p_message->msg.ble.msg.prepare.id = id;

    /* Configure reception trigger. */
    p_message->msg.ble.msg.prepare.has_trigger = true;
    p_message->msg.ble.msg.prepare.trigger.which_trigger = ble_PrepareSequenceCmd_Trigger_reception_tag;
    if ((length > 0) && (length < BLE_PREPSEQ_TRIGGER_MAX_SIZE))
    {
        p_message->msg.ble.msg.prepare.trigger.trigger.reception.pattern.size = length;
        p_message->msg.ble.msg.prepare.trigger.trigger.reception.mask.size = length;
        memcpy(
            p_message->msg.ble.msg.prepare.trigger.trigger.reception.pattern.bytes,
            p_pattern,
            length
        );
        memcpy(
            p_message->msg.ble.msg.prepare.trigger.trigger.reception.mask.bytes,
            p_mask,
            length
        );
    }
    else
    {
        /* Pattern and mask are too big. */
        return WHAD_ERROR;
    }

    p_message->msg.ble.msg.prepare.direction = (ble_BleDirection)direction;

    /* Copy prepared packets into our sequence. */
    if (_whad_ble_sequence_copy_packets(p_message, p_packets, pkt_count) == WHAD_ERROR)
    {
        /* Something went wrong when copying prepared packets. */
        return WHAD_ERROR;
    }

    /* Success. */
    return WHAD_SUCCESS;
}


/**
 * @brief Initialize a message to send a sequence of PDU all at once on a manual trigger
 *  
 * @param[in,out]   p_message           Pointer to the message structure to initialize
 * @param[in]       id                  Prepared sequence identifier
 * @param[in]       direction           PDU sequence direction
 * @param[in]       p_packets           Pointer to an array of prepared packets
 * @param[in]       pkt_count           Number of packets in the prepared packets sequence
 * 
 * @retval          WHAD_SUCCESS        Success.
 * @retval          WHAD_ERROR          Invalid pointer or packet size exceed the allowed size.
 **/

whad_result_t whad_ble_prepare_sequence_manual(Message *p_message, uint32_t id, whad_ble_direction_t direction,
                                               whad_prepared_packet_t *p_packets, int pkt_count) 
{
    /* Sanity check. */
    if ((p_message == NULL) || (p_packets == NULL))
    {
        return WHAD_ERROR;
    }

    /* Populate message fields. */
    p_message->which_msg = Message_ble_tag;
    p_message->msg.ble.which_msg = ble_Message_prepare_tag;
    p_message->msg.ble.msg.prepare.id = id;

    /* Configure manual trigger. */
    p_message->msg.ble.msg.prepare.has_trigger = true;
    p_message->msg.ble.msg.prepare.trigger.which_trigger = ble_PrepareSequenceCmd_Trigger_manual_tag;
    p_message->msg.ble.msg.prepare.direction = (ble_BleDirection)direction;

    /* Copy prepared packets into our sequence. */
    if (_whad_ble_sequence_copy_packets(p_message, p_packets, pkt_count) == WHAD_ERROR)
    {
        /* Something went wrong when copying prepared packets. */
        return WHAD_ERROR;
    }

    /* Success. */
    return WHAD_SUCCESS;
}


/**
 * @brief Parse a message to send a sequence of PDU all at once on a manual trigger
 *  
 * @param[in]       p_message           Pointer to the message to parse
 * @param[in,out]   p_parameters        Pointer to a `whad_ble_prepseq_params_t`
 * 
 * @retval          WHAD_SUCCESS        Success.
 * @retval          WHAD_ERROR          Invalid pointer or packet size exceed the allowed size.
 **/

whad_result_t whad_ble_prepare_sequence_manual_parse(Message *p_message, whad_ble_prepseq_params_t *p_parameters) 
{
    int i;

    /* Sanity check. */
    if ((p_message == NULL) || (p_parameters == NULL))
    {
        return WHAD_ERROR;
    }

    /* Extract parameters (id and direction) */
    memset(p_parameters, 0, sizeof(whad_ble_prepseq_params_t));
    p_parameters->id = p_message->msg.ble.msg.prepare.id;
    p_parameters->direction = p_message->msg.ble.msg.prepare.direction;

    /* Set prepared packets array. */
    for (i=0; i<p_message->msg.ble.msg.prepare.sequence_count; i++)
    {
        p_parameters->packets[i].length = p_message->msg.ble.msg.prepare.sequence[i].packet.size;
        p_parameters->packets[i].p_bytes = p_message->msg.ble.msg.prepare.sequence[i].packet.bytes;
    }

    /* Success. */
    return WHAD_SUCCESS;
}

/**
 * @brief Initialize a message to send a sequence of PDU all at once on a specific connection event
 *  
 * @param[in,out]   p_message           Pointer to the message structure to initialize
 * @param[in]       connection_event    Connection event value at which the PDUs must be sent
 * @param[in]       id                  Prepared sequence identifier
 * @param[in]       direction           PDU sequence direction
 * @param[in]       p_packets           Pointer to an array of prepared packets
 * @param[in]       pkt_count           Number of packets in the prepared packets sequence
 * 
 * @retval          WHAD_SUCCESS        Success.
 * @retval          WHAD_ERROR          Invalid pointer or packet size exceed the allowed size.
 **/

whad_result_t whad_ble_prepare_sequence_conn_evt(Message *p_message, uint32_t connection_event, 
                                               uint32_t id, whad_ble_direction_t direction,
                                               whad_prepared_packet_t *p_packets, int pkt_count) 
{
    /* Sanity check. */
    if ((p_message == NULL) || (p_packets == NULL))
    {
        return WHAD_ERROR;
    }

    /* Populate message fields. */
    p_message->which_msg = Message_ble_tag;
    p_message->msg.ble.which_msg = ble_Message_prepare_tag;
    p_message->msg.ble.msg.prepare.id = id;

    /* Configure connection event trigger. */
    p_message->msg.ble.msg.prepare.has_trigger = true;
    p_message->msg.ble.msg.prepare.trigger.which_trigger = ble_PrepareSequenceCmd_Trigger_connection_event_tag;
    p_message->msg.ble.msg.prepare.trigger.trigger.connection_event.connection_event = connection_event;

    p_message->msg.ble.msg.prepare.direction = (ble_BleDirection)direction;

    /* Copy prepared packets into our sequence. */
    if (_whad_ble_sequence_copy_packets(p_message, p_packets, pkt_count) == WHAD_ERROR)
    {
        /* Something went wrong when copying prepared packets. */
        return WHAD_ERROR;
    }

    /* Success. */
    return WHAD_SUCCESS;
}


/**
 * @brief Parse a message to send a sequence of PDU all at once on a connection event trigger
 *  
 * @param[in]       p_message           Pointer to the message to parse
 * @param[in,out]   p_parameters        Pointer to a `whad_ble_prepseq_params_t`
 * 
 * @retval          WHAD_SUCCESS        Success.
 * @retval          WHAD_ERROR          Invalid pointer or packet size exceed the allowed size.
 **/

whad_result_t whad_ble_prepare_sequence_conn_evt_parse(Message *p_message, whad_ble_prepseq_params_t *p_parameters) 
{
    unsigned int i;

    /* Sanity check. */
    if ((p_message == NULL) || (p_parameters == NULL))
    {
        return WHAD_ERROR;
    }

    /* Extract parameters. */
    memset(p_parameters, 0, sizeof(whad_ble_prepseq_params_t));
    p_parameters->id = p_message->msg.ble.msg.prepare.id;
    p_parameters->direction = p_message->msg.ble.msg.prepare.direction;
    p_parameters->conn_evt = p_message->msg.ble.msg.prepare.trigger.trigger.connection_event.connection_event;

    /* Set prepared packets array. */
    for (i=0; i<p_message->msg.ble.msg.prepare.sequence_count; i++)
    {
        p_parameters->packets[i].length = p_message->msg.ble.msg.prepare.sequence[i].packet.size;
        p_parameters->packets[i].p_bytes = p_message->msg.ble.msg.prepare.sequence[i].packet.bytes;
    }

    /* Success. */
    return WHAD_SUCCESS;
}


/**
 * @brief Initialize a message to manually trigger the sending of a prepared sequence of PDUs
 *  
 * @param[in,out]   p_message           Pointer to the message structure to initialize
 * @param[in]       id                  Prepared sequence identifier
 * 
 * @retval          WHAD_SUCCESS        Success.
 * @retval          WHAD_ERROR          Invalid pointer or packet size exceed the allowed size.
 **/

whad_result_t whad_ble_prepare_sequence_trigger(Message *p_message, uint32_t id) 
{
    /* Sanity check. */
    if (p_message == NULL)
    {
        return WHAD_ERROR;
    }

    /* Populate message fields. */
    p_message->which_msg = Message_ble_tag;
    p_message->msg.ble.which_msg = ble_Message_trigger_tag;
    p_message->msg.ble.msg.trigger.id = id;

    /* Success. */
    return WHAD_SUCCESS;
}


/**
 * @brief Parse a message to manually trigger the sending of a prepared sequence of PDUs
 *  
 * @param[in]       p_message           Pointer to the message structure to initialize
 * @param[in,out]   p_id                Pointer to the trigger id
 * 
 * @retval          WHAD_SUCCESS        Success.
 * @retval          WHAD_ERROR          Invalid pointer or packet size exceed the allowed size.
 **/

whad_result_t whad_ble_prepare_sequence_trigger_parse(Message *p_message, uint32_t *p_id) 
{
    /* Sanity check. */
    if ((p_message == NULL) || (p_id == NULL))
    {
        return WHAD_ERROR;
    }

    /* Extract value. */
    *p_id = p_message->msg.ble.msg.trigger.id;

    /* Success. */
    return WHAD_SUCCESS;
}


/**
 * @brief Initialize a message to delete a previously registered prepared sequence
 *  
 * @param[in,out]   p_message           Pointer to the message structure to initialize
 * @param[in]       id                  Prepared sequence identifier
 * 
 * @retval          WHAD_SUCCESS        Success.
 * @retval          WHAD_ERROR          Invalid pointer or packet size exceed the allowed size.
 **/

whad_result_t whad_ble_prepare_sequence_delete(Message *p_message, uint32_t id) 
{
    /* Sanity check. */
    if (p_message == NULL)
    {
        return WHAD_ERROR;
    }

    /* Populate message fields. */
    p_message->which_msg = Message_ble_tag;
    p_message->msg.ble.which_msg = ble_Message_delete_seq_tag;
    p_message->msg.ble.msg.delete_seq.id = id;

    /* Success. */
    return WHAD_SUCCESS;
}


/**
 * @brief Initialize a message to notify that a prepared sequence has been triggered
 *  
 * @param[in,out]   p_message           Pointer to the message structure to initialize
 * @param[in]       id                  Prepared sequence identifier
 * 
 * @retval          WHAD_SUCCESS        Success.
 * @retval          WHAD_ERROR          Invalid pointer or packet size exceed the allowed size.
 **/

whad_result_t whad_ble_triggered(Message *p_message, uint32_t id) 
{
    /* Sanity check. */
    if (p_message == NULL)
    {
        return WHAD_ERROR;
    }

    /* Populate message fields. */
    p_message->which_msg = Message_ble_tag;
    p_message->msg.ble.which_msg = ble_Message_triggered_tag;
    p_message->msg.ble.msg.triggered.id = id;

    /* Success. */
    return WHAD_SUCCESS;
}


/**
 * @brief Parse a message to notify that a prepared sequence has been triggered
 *  
 * @param[in]       p_message           Pointer to the message structure to initialize
 * @param[in,out]   p_id                Pointer to the sequence id
 * 
 * @retval          WHAD_SUCCESS        Success.
 * @retval          WHAD_ERROR          Invalid pointer or packet size exceed the allowed size.
 **/

whad_result_t whad_ble_triggered_parse(Message *p_message, uint32_t *p_id) 
{
    /* Sanity check. */
    if ((p_message == NULL) || (p_id == NULL))
    {
        return WHAD_ERROR;
    }

    /* Extract sequence id. */
    *p_id = p_message->msg.ble.msg.triggered.id;

    /* Success. */
    return WHAD_SUCCESS;
}


/**
 * @brief Initialize a message to notify that an access address has been discovered
 *  
 * @param[in,out]   p_message           Pointer to the message structure to initialize
 * @param[in]       access_address      Discovered access address
 * @param[in]       timestamp           Timestamp at which the address was discovered
 * @param[in]       rssi                Received Signal Strength Indicator
 * @param[in]       inc_ts              If set to true, the message will include a timestamp.
 * @param[in]       inc_rssi            If set to true, the message will include the RSSI.
 * 
 * @retval          WHAD_SUCCESS        Success.
 * @retval          WHAD_ERROR          Invalid pointer or packet size exceed the allowed size.
 **/

whad_result_t whad_ble_access_address_discovered(Message *p_message, uint32_t access_address, uint32_t timestamp, 
                                                 int32_t rssi, bool inc_ts, bool inc_rssi)
{
    /* Sanity check. */
    if (p_message == NULL)
    {
        return WHAD_ERROR;
    }

    /* Populate message fields. */
    p_message->which_msg = Message_ble_tag;
    p_message->msg.ble.which_msg = ble_Message_aa_disc_tag;
    p_message->msg.ble.msg.aa_disc.access_address = access_address;

    /* Include timestamp if told to. */
    if (inc_ts)
    {
        p_message->msg.ble.msg.aa_disc.has_timestamp = true;
        p_message->msg.ble.msg.aa_disc.timestamp = timestamp;
    }

    /* Include RSSI if told to. */
    if (inc_rssi)
    {
        p_message->msg.ble.msg.aa_disc.has_rssi = true;
        p_message->msg.ble.msg.aa_disc.rssi = rssi;
    }

    /* Success. */
    return WHAD_SUCCESS;
}

/**
 * @brief Initialize a message to notify an advertising PDU
 *  
 * @param[in,out]   p_message           Pointer to the message structure to initialize
 * @param[in]       adv_type            Advertisement type
 * @param[in]       rssi                Received Signal Strength Indicator
 * @param[in]       p_bdaddr            Pointer to a byte buffer containing the BD address (6 bytes)
 * @param[in]       addr_type           Specifies the advertiser's BD address type (public/random)
 * @param[in]       p_adv_data          Pointer to a byte buffer containing the advertising data
 * @param[in]       adv_data_length     Length of advertising data in bytes
 * 
 * @retval          WHAD_SUCCESS        Success.
 * @retval          WHAD_ERROR          Invalid pointer or packet size exceed the allowed size.
 **/

whad_result_t whad_ble_adv_pdu(Message *p_message, whad_ble_advtype_t adv_type, int32_t rssi, uint8_t *p_bdaddr,
                               whad_ble_addrtype_t addr_type, uint8_t *p_adv_data, int adv_data_length)
{
    /* Sanity check. */
    if ((p_message == NULL) || (p_bdaddr == NULL) || (p_adv_data == NULL))
    {
        return WHAD_ERROR;
    }

    /* Populate message fields. */
    p_message->which_msg = Message_ble_tag;
    p_message->msg.ble.which_msg = ble_Message_adv_pdu_tag;
    p_message->msg.ble.msg.adv_pdu.addr_type = (ble_BleAddrType)addr_type;
    p_message->msg.ble.msg.adv_pdu.rssi = rssi;
    p_message->msg.ble.msg.adv_pdu.adv_type = (ble_BleAdvType)adv_type;

    /* Copy BD address. */
    memcpy(p_message->msg.ble.msg.adv_pdu.bd_address, p_bdaddr, 6);

    /* Copy advertising data. */
    if ((adv_data_length > 0) && (adv_data_length < 31))
    {
        p_message->msg.ble.msg.adv_pdu.adv_data.size = adv_data_length;
        memcpy(p_message->msg.ble.msg.adv_pdu.adv_data.bytes, p_adv_data, adv_data_length);
    }

    /* Success. */
    return WHAD_SUCCESS;
}


/**
 * @brief Parse a message notifying an advertising PDU
 *  
 * @param[in]       p_message           Pointer to the message to parse
 * @param[in,out]   p_parameters        Pointer to a `whad_ble_prepseq_params_t`
 * 
 * @retval          WHAD_SUCCESS        Success.
 * @retval          WHAD_ERROR          Invalid pointer or packet size exceed the allowed size.
 **/

whad_result_t whad_ble_adv_pdu_parse(Message *p_message, whad_ble_adv_pdu_t *p_parameters)
{
    /* Sanity check. */
    if ((p_message == NULL) || (p_parameters == NULL))
    {
        return WHAD_ERROR;
    }

    /* Extract parameters. */
    p_parameters->addr_type = p_message->msg.ble.msg.adv_pdu.addr_type;
    p_parameters->adv_type = p_message->msg.ble.msg.adv_pdu.adv_type;
    p_parameters->rssi = p_message->msg.ble.msg.adv_pdu.rssi;
    p_parameters->p_bdaddr = p_message->msg.ble.msg.adv_pdu.bd_address;
    p_parameters->p_adv_data = p_message->msg.ble.msg.adv_pdu.adv_data.bytes;
    p_parameters->adv_data_length = p_message->msg.ble.msg.adv_pdu.adv_data.size;

    /* Success. */
    return WHAD_SUCCESS;
}


/**
 * @brief Initialize a message to notify that the adapter has synchronized with an active connection
 *  
 * @param[in,out]   p_message           Pointer to the message structure to initialize
 * @param[in]       access_address      Access address
 * @param[in]       crc_init            CRC initial value (seed)
 * @param[in]       hop_interval        Connection recovered hop interval
 * @param[in]       hop_increment       Connection recovered hop increment
 * @param[in]       p_channelmap        Connection channel map
 * 
 * @retval          WHAD_SUCCESS        Success.
 * @retval          WHAD_ERROR          Invalid pointer or packet size exceed the allowed size.
 **/

whad_result_t whad_ble_synchronized(Message *p_message, uint32_t access_address, uint32_t crc_init,
                                    uint32_t hop_interval, uint32_t hop_increment, uint8_t *p_channelmap)
{
    /* Sanity check. */
    if ((p_message == NULL) || (p_channelmap == NULL))
    {
        return WHAD_ERROR;
    }

    /* Populate message fields. */
    p_message->which_msg = Message_ble_tag;
    p_message->msg.ble.which_msg = ble_Message_synchronized_tag;
    p_message->msg.ble.msg.synchronized.access_address = access_address;
    p_message->msg.ble.msg.synchronized.hop_interval = hop_interval;
    p_message->msg.ble.msg.synchronized.hop_increment = hop_increment;
    p_message->msg.ble.msg.synchronized.crc_init = crc_init;
    memcpy(p_message->msg.ble.msg.synchronized.channel_map, p_channelmap, 5);

    /* Success. */
    return WHAD_SUCCESS;
}


/**
 * @brief Initialize a message to notify that the adapter has been desynchronized from an active connection
 *  
 * @param[in,out]   p_message           Pointer to the message structure to initialize
 * @param[in]       access_address      Access address
 * 
 * @retval          WHAD_SUCCESS        Success.
 * @retval          WHAD_ERROR          Invalid pointer or packet size exceed the allowed size.
 **/

whad_result_t whad_ble_desynchronized(Message *p_message, uint32_t access_address)
{
    /* Sanity check. */
    if (p_message == NULL)
    {
        return WHAD_ERROR;
    }

    /* Populate message fields. */
    p_message->which_msg = Message_ble_tag;
    p_message->msg.ble.which_msg = ble_Message_desynchronized_tag;
    p_message->msg.ble.msg.desynchronized.access_address = access_address;

    /* Success. */
    return WHAD_SUCCESS;
}


/**
 * @brief Initialize a message to notify that the adapter has successfully (or not) hijacked a connection
 *  
 * @param[in,out]   p_message           Pointer to the message structure to initialize
 * @param[in]       access_address      Access address
 * @param[in]       success             Set to true to notify a successful hijacking, false otherwise.
 * 
 * @retval          WHAD_SUCCESS        Success.
 * @retval          WHAD_ERROR          Invalid pointer or packet size exceed the allowed size.
 **/

whad_result_t whad_ble_hijacked(Message *p_message, uint32_t access_address, bool success)
{
    /* Sanity check. */
    if (p_message == NULL)
    {
        return WHAD_ERROR;
    }

    /* Populate message fields. */
    p_message->which_msg = Message_ble_tag;
    p_message->msg.ble.which_msg = ble_Message_hijacked_tag;
    p_message->msg.ble.msg.hijacked.access_address = access_address;
    p_message->msg.ble.msg.hijacked.success = success;

    /* Success. */
    return WHAD_SUCCESS;
}


/**
 * @brief Parse a message to notify that the adapter has successfully (or not) hijacked a connection
 *  
 * @param[in]           p_message           Pointer to the message structure to initialize
 * @param[in,out]       p_parameters        Pointer to the message parameters
 * 
 * @retval          WHAD_SUCCESS        Success.
 * @retval          WHAD_ERROR          Invalid pointer or packet size exceed the allowed size.
 **/

whad_result_t whad_ble_hijacked_parse(Message *p_message, whad_ble_hijacked_params_t *p_parameters)
{
    /* Sanity check. */
    if ((p_message == NULL) || (p_parameters == NULL))
    {
        return WHAD_ERROR;
    }

    /* Extract parameters. */
    p_parameters->access_address = p_message->msg.ble.msg.hijacked.access_address;
    p_parameters->success = p_message->msg.ble.msg.hijacked.success;

    /* Success. */
    return WHAD_SUCCESS;
}

/**
 * @brief Initialize a message to notify that the adapter has successfully (or not) hijacked a connection
 *  
 * @param[in,out]   p_message           Pointer to the message structure to initialize
 * @param[in]       access_address      Access address
 * @param[in]       attempts            Number of attempts
 * @param[in]       success             Set to true to notify a successful hijacking, false otherwise.
 * 
 * @retval          WHAD_SUCCESS        Success.
 * @retval          WHAD_ERROR          Invalid pointer or packet size exceed the allowed size.
 **/

whad_result_t whad_ble_injected(Message *p_message, uint32_t access_address, uint32_t attempts, bool success)
{
    /* Sanity check. */
    if (p_message == NULL)
    {
        return WHAD_ERROR;
    }

    /* Populate message fields. */
    p_message->which_msg = Message_ble_tag;
    p_message->msg.ble.which_msg = ble_Message_injected_tag;
    p_message->msg.ble.msg.injected.access_address = access_address;
    p_message->msg.ble.msg.injected.injection_attempts = attempts;
    p_message->msg.ble.msg.injected.success = success;

    /* Success. */
    return WHAD_SUCCESS;
}


/**
 * @brief Parse a message to notify that the adapter has successfully (or not) hijacked a connection
 *  
 * @param[in]       p_message           Pointer to the message structure to initialize
 * @param[in,out]   p_parameters        Pointer to a structure containing the parameters
 * 
 * @retval          WHAD_SUCCESS        Success.
 * @retval          WHAD_ERROR          Invalid pointer or packet size exceed the allowed size.
 **/

whad_result_t whad_ble_injected_parse(Message *p_message, whad_ble_injected_params_t *p_parameters)
{
    /* Sanity check. */
    if ((p_message == NULL) || (p_parameters == NULL))
    {
        return WHAD_ERROR;
    }

    /* Extract parameters. */
    p_parameters->access_address = p_message->msg.ble.msg.injected.access_address;
    p_parameters->attempts = p_message->msg.ble.msg.injected.injection_attempts;
    p_parameters->success = p_message->msg.ble.msg.injected.success;

    /* Success. */
    return WHAD_SUCCESS;
}