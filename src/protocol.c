#include "whad.h"


/**
 * @brief Initialize a generic command result message
 * 
 * @param[in]   p_message       Pointer to a `Message` structure
 * @param[in]   result          Result code to include in the message
 * @retval      WHAD_SUCCESS    Success
 * @retval      WHAD_ERROR      Wrong message pointer
 **/

whad_result_t whad_generic_cmd_result(Message *p_message, whad_result_code_t result)
{
    /* Sanity check. */
    if (p_message == NULL)
    {
        return WHAD_ERROR;
    }

    /* Build a generic command result message. */
    p_message->which_msg = Message_generic_tag;
    p_message->msg.generic.which_msg = generic_Message_cmd_result_tag;
    p_message->msg.generic.msg.cmd_result.result = result;

    /* Success. */
    return WHAD_SUCCESS;
}


/**
 * @brief Generic verbose message encoding callback.
 * 
 * @param[in,out]   ostream Output stream
 * @param[in]       field   Pointer to a field descriptor.
 * @param[in]       arg     Pointer to a custom argument storing a pointer onto the text message to encode.
 * @return true if everything went ok, false otherwise.
 */

bool whad_verbose_msg_encode_cb(pb_ostream_t *ostream, const pb_field_t *field, void * const *arg)
{
    /* Take arg and encode it. */
    char *psz_message = *(char **)arg;
    int message_length = strlen(psz_message);

    if (ostream != NULL && field->tag == generic_VerboseMsg_data_tag)
    {
        /* This encodes the header for the field, based on the constant info
        * from pb_field_t. */
        if (!pb_encode_tag_for_field(ostream, field))
            return false;

        pb_encode_string(ostream, (pb_byte_t *)psz_message, message_length);
    }

    return true;
}


/**
 * @brief Initialize a generic verbose message.
 * 
 * @param[in,out]   p_message     Pointer to a `Message` structure representing a message.
 * @param[in]       psz_message   Pointer to the message string to include in this verbose message.
 * @retval          WHAD_SUCCESS  Success
 * @retval          WHAD_ERROR    Wrong message pointer
 */

whad_result_t whad_generic_verbose_message(Message *p_message, char *psz_message)
{
    /* Sanity check. */
    if (p_message == NULL)
    {
        return WHAD_ERROR;
    }

    /* Specify payload type. */
    p_message->which_msg = Message_generic_tag;

    /* Fills verbose message data. */
    p_message->msg.generic.which_msg = generic_Message_verbose_tag;
    p_message->msg.generic.msg.verbose.data.arg = psz_message;
    p_message->msg.generic.msg.verbose.data.funcs.encode = whad_verbose_msg_encode_cb;

    /* Success. */
    return WHAD_SUCCESS;
}


/**
 * @brief WHAD verbose helper
 * 
 * This function sends a verbose message to the host.
 * 
 * @param[in]       psz_message   Pointer to the message string to include in this verbose message.
 * 
 * @retval          WHAD_SUCCESS  Success
 * @retval          WHAD_ERROR    Wrong message pointer
 */

whad_result_t whad_verbose(char *psz_message)
{
    whad_result_t result;
    Message msg;

    result = whad_generic_verbose_message(&msg, psz_message);
    if (result == WHAD_SUCCESS)
    {
        return whad_send_message(&msg);
    }
    else
    {
        return WHAD_ERROR;
    }
}


/**
 * @brief Generic debug message encoding callback.
 * 
 * @param[in,out]   ostream Output stream
 * @param[in]       field   Pointer to a field descriptor.
 * @param[in]       arg     Pointer to a custom argument storing a pointer onto the text message to encode.
 * @return true if everything went ok, false otherwise.
 */

bool whad_debug_msg_encode_cb(pb_ostream_t *ostream, const pb_field_t *field, void * const *arg)
{
    /* Take arg and encode it. */
    char *psz_message = *(char **)arg;
    int message_length = strlen(psz_message);

    if (ostream != NULL && field->tag == generic_DebugMsg_data_tag)
    {
        /* This encodes the header for the field, based on the constant info
        * from pb_field_t. */
        if (!pb_encode_tag_for_field(ostream, field))
            return false;

        pb_encode_string(ostream, (pb_byte_t *)psz_message, message_length);
    }

    return true;
}


/**
 * @brief Initialize a generic debug message.
 * 
 * @param[in,out]   p_message     Pointer to a `Messsage` structure
 * @param[in]       level         Debug level
 * @param[in]       psz_message   Pointer to a text string corresponding to the debug message to send
 * 
 * @retval          WHAD_SUCCESS  Success.
 * @retval          WHAD_ERROR    Invalid message pointer.
 **/

whad_result_t whad_generic_debug_message(Message *p_message, uint32_t level, char *psz_message)
{
    /* Sanity check. */
    if (p_message == NULL)
    {
        return WHAD_ERROR;
    }

    /* Specify payload type. */
    p_message->which_msg = Message_generic_tag;

    /* Fills debug message data. */\
    p_message->msg.generic.which_msg = generic_Message_debug_tag;
    p_message->msg.generic.msg.debug.level = level;
    p_message->msg.generic.msg.debug.data.arg = psz_message;
    p_message->msg.generic.msg.debug.data.funcs.encode = whad_debug_msg_encode_cb;

    /* Success. */
    return WHAD_SUCCESS;
}

/**
 * @brief Initialize a generic progress message.
 * 
 * @param[in,out]   p_message     Pointer to a `Messsage` structure
 * @param[in]       value         Progress value
 * @param[in]       psz_message   Pointer to a text string corresponding to the debug message to send
 * 
 * @retval          WHAD_SUCCESS  Success.
 * @retval          WHAD_ERROR    Invalid message pointer.
 **/

whad_result_t whad_generic_progress_message(Message *p_message, uint32_t value)
{
    /* Sanity check. */
    if (p_message == NULL)
    {
        return WHAD_ERROR;
    }

    /* Specify payload type. */
    p_message->which_msg = Message_generic_tag;

    /* Fills debug message data. */
    p_message->msg.generic.which_msg = generic_Message_progress_tag;
    p_message->msg.generic.msg.progress.value = value;

    /* Success. */
    return WHAD_SUCCESS;
}

/*****************************
 * Discovery messages
 ****************************/

bool whad_disc_enum_capabilities_cb(pb_ostream_t *ostream, const pb_field_t *field, void * const *arg)
{
    whad_domain_desc_t *capabilities = *(whad_domain_desc_t **)arg;
    if (ostream != NULL && field->tag == discovery_DeviceInfoResp_capabilities_tag)
    {
        while ((capabilities->cap != 0) && (capabilities->domain != 0))
        {
            if (!pb_encode_tag_for_field(ostream, field))
                return false;

            if (!pb_encode_varint(ostream, capabilities->domain | capabilities->cap))
                return false;

            /* Go to next capability. */
            capabilities++;
        }
    }

    return true;
}

uint64_t whad_discovery_get_supported_commands(whad_domain_t domain, whad_domain_desc_t *p_capabilities) {
  uint64_t supportedCommands = 0x00000000;
  int index = 0;
  while (p_capabilities[index].domain != 0) {
    if (p_capabilities[index].domain == domain) {
      supportedCommands = p_capabilities[index].supported_commands;
      break;
    }
    index++;
  }
  return supportedCommands;
}


/**
 * @brief Initialize a discovery device info query.
 * 
 * @param[in,out]   p_message           Pointer to the message structure to initialize
 * @param[in]       proto_version       Version of the WHAD protocol supported by the sender
 * 
 * @retval          WHAD_SUCCESS        Success.
 * @retval          WHAD_ERROR          Invalid message pointer.
 **/

whad_result_t whad_discovery_device_info_query(Message *p_message, uint32_t proto_version)
{
    /* Sanity check. */
    if (p_message == NULL)
    {
        return WHAD_ERROR;
    }

    /* Populate fieds. */
    p_message->which_msg = Message_discovery_tag;
    p_message->msg.discovery.which_msg = discovery_Message_info_query_tag;
    p_message->msg.discovery.msg.info_query.proto_ver = proto_version;

    /* Success. */
    return WHAD_SUCCESS;    
}


/**
 * @brief Initialize a discovery device information response message.
 * 
 * @param[in,out]   p_message           Pointer to the message structure to initialize
 * @param[in]       device_type         Device type
 * @param[in]       devid               Device identifier (text string, max 16 bytes)
 * @param[in]       proto_min_ver       WHAD protocol minimum supported version
 * @param[in]       max_speed           Maximum USART speed supported by the device
 * @param[in]       fw_author           Pointer to a text string containing the name of the author
 * @param[in]       fw_url              Pointer to a text string containing the URL of the firmware
 *                                      (Github repository, website, etc.)
 * @param[in]       fw_version_major    Firmware version major number
 * @param[in]       fw_version_minor    Firmware version minor number
 * @param[in]       fw_version_rev      Firmware version revision number
 * @param[in]       capabilities        Firmware capabilities, as a pointer to a WhadDeviceCapability structure
 *
 * @retval          WHAD_SUCCESS        Success.
 * @retval          WHAD_ERROR          Invalid message pointer.
 **/

whad_result_t whad_discovery_device_info_resp(
    Message *p_message,
    discovery_DeviceType device_type,
    uint8_t *devid,
    uint32_t proto_min_ver,
    uint32_t max_speed,
    char *fw_author,
    char *fw_url,
    uint32_t fw_version_major,
    uint32_t fw_version_minor,
    uint32_t fw_version_rev,
    whad_domain_desc_t *capabilities)
{
    /* Sanity check. */
    if (p_message == NULL)
    {
        return WHAD_ERROR;
    }

    p_message->which_msg = Message_discovery_tag;
    p_message->msg.discovery.which_msg = discovery_Message_info_resp_tag;
    p_message->msg.discovery.msg.info_resp.proto_min_ver = proto_min_ver;
    p_message->msg.discovery.msg.info_resp.max_speed = max_speed;
    if (fw_author != NULL)
    {
        strncpy((char *)p_message->msg.discovery.msg.info_resp.fw_author.bytes, (char *)fw_author, 63);
        p_message->msg.discovery.msg.info_resp.fw_author.size = strlen(fw_author);
    }
    else
    {
        p_message->msg.discovery.msg.info_resp.fw_author.size = 0;
    }

    if(fw_url != NULL)
    {
        strncpy((char *)p_message->msg.discovery.msg.info_resp.fw_url.bytes, (char *)fw_url, 255);
        p_message->msg.discovery.msg.info_resp.fw_url.size = strlen(fw_url);
    }
    else
    {
        p_message->msg.discovery.msg.info_resp.fw_url.size = 0;
    }
    
    p_message->msg.discovery.msg.info_resp.fw_version_major = fw_version_major;
    p_message->msg.discovery.msg.info_resp.fw_version_minor = fw_version_minor;
    p_message->msg.discovery.msg.info_resp.fw_version_rev = fw_version_rev;
    p_message->msg.discovery.msg.info_resp.type = device_type;
    strncpy((char *)p_message->msg.discovery.msg.info_resp.devid, (char *)devid, 15);
    p_message->msg.discovery.msg.info_resp.capabilities.arg = capabilities;
    p_message->msg.discovery.msg.info_resp.capabilities.funcs.encode = whad_disc_enum_capabilities_cb;

    /* Success. */
    return WHAD_SUCCESS;
}


/**
 * @brief Initialize a discovery device info query.
 * 
 * @param[in,out]   p_message           Pointer to the message structure to initialize
 * @param[in]       domain              Domain to query
 * 
 * @retval          WHAD_SUCCESS        Success.
 * @retval          WHAD_ERROR          Invalid message pointer.
 **/

whad_result_t whad_discovery_domain_info_query(Message *p_message, whad_domain_t domain)
{
    /* Sanity check. */
    if (p_message == NULL)
    {
        return WHAD_ERROR;
    }

    /* Populate fieds. */
    p_message->which_msg = Message_discovery_tag;
    p_message->msg.discovery.which_msg = discovery_Message_domain_query_tag;
    p_message->msg.discovery.msg.domain_query.domain = domain;

    /* Success. */
    return WHAD_SUCCESS;    
}


/**
 * @brief Initialize a discovery domain information response message.
 * 
 * @param[in,out]   p_message           Pointer to the message structure to initialize
 * @param[in]       domain              Device supported domain
 * @param[in]       supported_commands  Supported commands as a 64-bits integer (bitmap)
 *
 * @retval          WHAD_SUCCESS        Success.
 * @retval          WHAD_ERROR          Invalid message pointer.
 **/

whad_result_t whad_discovery_domain_info_resp(Message *p_message, whad_domain_t domain, whad_domain_desc_t *p_capabilities)
{
    /* Sanity check. */
    if (p_message == NULL)
    {
        return WHAD_ERROR;
    }

    /* Populate fields. */
    p_message->which_msg = Message_discovery_tag;
    p_message->msg.discovery.which_msg = discovery_Message_domain_resp_tag;
    p_message->msg.discovery.msg.domain_resp.domain = (discovery_Domain)domain;
    p_message->msg.discovery.msg.domain_resp.supported_commands = whad_discovery_get_supported_commands(domain, p_capabilities);

    /* Success. */
    return WHAD_SUCCESS;
}

/**
 * @brief Initialize a discovery device reset message.
 * 
 * @param[in,out]   p_message           Pointer to the message structure to initialize
 * 
 * @retval          WHAD_SUCCESS        Success.
 * @retval          WHAD_ERROR          Invalid message pointer.
 **/

whad_result_t whad_discovery_device_reset(Message *p_message)
{
    /* Sanity check. */
    if (p_message == NULL)
    {
        return WHAD_ERROR;
    }

    /* Populate fieds. */
    p_message->which_msg = Message_discovery_tag;
    p_message->msg.discovery.which_msg = discovery_Message_reset_query_tag;

    /* Success. */
    return WHAD_SUCCESS;    
}


/**
 * @brief Initialize a discovery ready response message.
 * 
 * @param[in,out]   p_message           Pointer to the message structure to initialize
 * @param[in]       domain              Device supported domain
 * @param[in]       supported_commands  Supported commands as a 64-bits integer (bitmap)
 * 
 * @retval          WHAD_SUCCESS        Success.
 * @retval          WHAD_ERROR          Invalid message pointer.
 **/

whad_result_t whad_discovery_ready_resp(Message *p_message)
{
    /* Sanity check. */
    if (p_message == NULL)
    {
        return WHAD_ERROR;
    }

    /* Populate fields. */    
    p_message->which_msg = Message_discovery_tag;
    p_message->msg.discovery.which_msg = discovery_Message_ready_resp_tag;

    /* Success. */
    return WHAD_SUCCESS;
}


/********************************
 * Bluetooth Low Energy messages
 *******************************/

/**
 * @brief Initialize a message reporting a BLE advertisement PDU
 * 
 * @param[in,out]   p_message           Pointer to the message structure to initialize
 * @param[in]       args                Pointer to a whad_adv_data_t structure containing the advertisement details
 * 
 * @retval          WHAD_SUCCESS        Success.
 * @retval          WHAD_ERROR          Invalid message pointer.
 **/

whad_result_t whad_ble_adv_pdu(Message *p_message, whad_adv_data_t *args)
{
    /* Sanity check. */
    if (p_message == NULL)
    {
        return WHAD_ERROR;
    }

    /* Populate fields. */    
    p_message->which_msg = Message_ble_tag;
    p_message->msg.ble.which_msg = ble_Message_adv_pdu_tag;
    memcpy(p_message->msg.ble.msg.adv_pdu.bd_address, args->bd_addr, 6);
    p_message->msg.ble.msg.adv_pdu.addr_type = args->addr_type;
    memcpy(p_message->msg.ble.msg.adv_pdu.adv_data.bytes, args->p_adv_data, args->adv_data_length);
    p_message->msg.ble.msg.adv_pdu.adv_data.size = args->adv_data_length;
    p_message->msg.ble.msg.adv_pdu.rssi = args->rssi;
    p_message->msg.ble.msg.adv_pdu.adv_type = args->adv_type;

    /* Success. */
    return WHAD_SUCCESS;
}


/**
 * @brief Initialize a message reporting a BLE data PDU
 * 
 * @param[in,out]   p_message           Pointer to the message structure to initialize
 * @param[in]       p_pdu               Pointer to a byte array containing the PDU
 * @param[in]       length              Length of the data PDU, in bytes
 * @param[in]       direction           Direction of the PDU (master -> slave / slave -> master)
 * 
 * @retval          WHAD_SUCCESS        Success.
 * @retval          WHAD_ERROR          Invalid message pointer or PDU pointer.
 **/

whad_result_t whad_ble_data_pdu(Message *p_message, uint8_t *p_pdu, int length, whad_ble_direction_t direction)
{
    /* Sanity check. */
    if ((p_message == NULL) || (p_pdu == NULL) )
    {
        return WHAD_ERROR;
    }

    /* Populate fields. */
    p_message->which_msg = Message_ble_tag;
    p_message->msg.ble.which_msg = ble_Message_pdu_tag;
    p_message->msg.ble.msg.pdu.direction = (ble_BleDirection)direction;
    p_message->msg.ble.msg.pdu.pdu.size = length;
    memcpy(p_message->msg.ble.msg.pdu.pdu.bytes, p_pdu, length);

    /* Success. */
    return WHAD_SUCCESS;
}


/**
 * @brief Initialize a message reporting a BLE link-layer data PDU
 * 
 * @param[in,out]   p_message           Pointer to the message structure to initialize
 * @param[in]       header              16-bit header including LLID and length
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

whad_result_t whad_ble_ll_data_pdu(Message *p_message, uint16_t header, uint8_t *p_pdu, int length,
                          whad_ble_direction_t direction, int conn_handle, bool processed, bool decrypted)
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
    p_message->msg.ble.msg.pdu.pdu.size = length + 2;
    p_message->msg.ble.msg.pdu.pdu.bytes[0] = (header & 0xff);
    p_message->msg.ble.msg.pdu.pdu.bytes[1] = (header >> 8) & 0xff;
    memcpy(&p_message->msg.ble.msg.pdu.pdu.bytes[2], p_pdu, length);

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

whad_result_t whad_ble_adv_mode(Message *p_message, uint8_t *p_scan_data, int scan_data_length, uint8_t *p_scanrsp_data, int scanrsp_data_length)
{
    /* Sanity check. */
    if ((p_message == NULL) || (p_scan_data == NULL) || (p_scanrsp_data == NULL))
    {
        return WHAD_ERROR;
    }

    /* Populate message fields. */
    p_message->which_msg = Message_ble_tag;
    p_message->msg.ble.which_msg = ble_Message_adv_mode_tag;

    /* Set avertising data, if provided. */
    if (scan_data_length > 0)
    {
        /* Cannot send more than 31 bytes in advertisement data. */
        if (scan_data_length > 31)
        {
            scan_data_length = 31;
        }
        p_message->msg.ble.msg.adv_mode.scan_data.size = scan_data_length;
        memcpy(p_message->msg.ble.msg.adv_mode.scan_data.bytes, p_scan_data, scan_data_length);
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

/** TODO Not yet supported, need some fix in whad-protocol. */
whad_result_t whad_ble_set_adv_data(Message *p_message, uint8_t *p_scan_data, int scan_data_length, uint8_t *p_scanrsp_data, int scanrsp_data_length)
{
    /* Sanity check. */
    if ((p_message == NULL) || (p_scan_data == NULL) || (p_scanrsp_data == NULL))
    {
        return WHAD_ERROR;
    }

    /* Populate message fields. */
    p_message->which_msg = Message_ble_tag;
    p_message->msg.ble.which_msg = ble_Message_set_adv_data_tag;

    /* Set avertising data, if provided. */
    if (scan_data_length > 0)
    {
        /* Cannot send more than 31 bytes in advertisement data. */
        if (scan_data_length > 31)
        {
            scan_data_length = 31;
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

whad_result_t whad_ble_peripheral_mode(Message *p_message, uint8_t *p_scan_data, int scan_data_length, uint8_t *p_scanrsp_data, int scanrsp_data_length)
{
    /* Sanity check. */
    if ((p_message == NULL) || (p_scan_data == NULL) || (p_scanrsp_data == NULL))
    {
        return WHAD_ERROR;
    }

    /* Populate message fields. */
    p_message->which_msg = Message_ble_tag;
    p_message->msg.ble.which_msg = ble_Message_periph_mode_tag;

    /* Set avertising data, if provided. */
    if (scan_data_length > 0)
    {
        /* Cannot send more than 31 bytes in advertisement data. */
        if (scan_data_length > 31)
        {
            scan_data_length = 31;
        }
        p_message->msg.ble.msg.adv_mode.scan_data.size = scan_data_length;
        memcpy(p_message->msg.ble.msg.adv_mode.scan_data.bytes, p_scan_data, scan_data_length);
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

whad_result_t whad_ble_reactive_jam(Message *p_message, uint32_t channel, uint8_t *pattern, int pattern_length, uint32_t position)
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
            memcpy(p_message->msg.ble.msg.reactive_jam.pattern.bytes, pattern, pattern_length);
        }
    }

    /* Success. */
    return WHAD_SUCCESS;
}

/********************************
 * PHY layer messages
 *******************************/

bool whad_phy_frequency_range_encode_cb(pb_ostream_t *ostream, const pb_field_t *field, void * const *arg)
{
  phy_SupportedFrequencyRanges_FrequencyRange *frequency_range = *(phy_SupportedFrequencyRanges_FrequencyRange **)arg;
  if (ostream != NULL && field->tag == phy_SupportedFrequencyRanges_frequency_ranges_tag)
  {
    while ((frequency_range->start != 0) && (frequency_range->end != 0))
    {
      if (!pb_encode_tag_for_field(ostream, field))
      {
          const char * error = PB_GET_ERROR(ostream);
          PB_UNUSED(error);
          return false;
      }

      if (!pb_encode_submessage(ostream, phy_SupportedFrequencyRanges_FrequencyRange_fields, frequency_range))
      {
          const char * error = PB_GET_ERROR(ostream);
          PB_UNUSED(error);
          return false;
      }
      frequency_range++;
    }
  }
  return true;
}


/**
 * @brief Initialize a message specifying the supported frequency ranges for the current device
 * 
 * @param[in,out]   p_message           Pointer to the message structure to initialize
 * @param[in]       p_ranges            Pointer to a list of supported frequency ranges
 * @param[in]       nb_ranges           Number of ranges in the provided list
 * 
 * @retval          WHAD_SUCCESS        Success.
 * @retval          WHAD_ERROR          Invalid message pointer or supported ranges pointer.
 **/

whad_result_t whad_phy_supported_frequencies(Message *p_message, phy_SupportedFrequencyRanges_FrequencyRange *p_ranges,
                                             int nb_ranges)
{
    /* Sanity check. */
    if ((p_message == NULL) || (p_ranges == NULL))
    {
        return WHAD_ERROR;
    }

    /* Populate field. */
    p_message->which_msg = Message_phy_tag;
    p_message->msg.phy.which_msg = phy_Message_supported_freq_tag;
    p_message->msg.phy.msg.supported_freq.frequency_ranges.arg = p_ranges;
    p_message->msg.phy.msg.supported_freq.frequency_ranges.funcs.encode = whad_phy_frequency_range_encode_cb;

    /* Success. */
    return WHAD_SUCCESS;
}


/**
 * @brief Initialize a message reporting a PHY packet
 * 
 * @param[in,out]   p_message           Pointer to the message structure to initialize
 * @param[in]       frequency           Frequency on which the PHY packet has been captured
 * @param[in]       rssi                Received Signal Strength Indicator in dBm
 * @param[in]       ts_sec              Timestamp (seconds) at which the packet has been received
 * @param[in]       ts_usec             Timestamp (microseconds) at which the packet has been received
 * @param[in]       payload              Pointer to the packet payload
 * @param[in]       length              Payload size in bytes
 * 
 * @retval          WHAD_SUCCESS        Success.
 * @retval          WHAD_ERROR          Invalid message pointer or payload pointer.
 **/

whad_result_t whad_phy_packet_received(Message *p_message, uint32_t frequency, int32_t rssi, uint32_t ts_sec, uint32_t ts_usec,
                              uint8_t *payload, int length)
{
    /* Sanity check. */
    if ((p_message == NULL) || (payload == NULL))
    {
        return WHAD_ERROR;
    }

    /* Populate fields. */
    p_message->which_msg = Message_phy_tag;
    p_message->msg.phy.which_msg = phy_Message_packet_tag;
    p_message->msg.phy.msg.packet.frequency = frequency;

    /* Set timestamp if provided. */
    if ((ts_sec > 0) || (ts_usec > 0))
    {
        p_message->msg.phy.msg.packet.has_timestamp = true;
        p_message->msg.phy.msg.packet.timestamp.sec = ts_sec;
        p_message->msg.phy.msg.packet.timestamp.usec = ts_usec;
    }
    else
    {
        p_message->msg.phy.msg.packet.has_timestamp = false;
        p_message->msg.phy.msg.packet.timestamp.sec = 0;
        p_message->msg.phy.msg.packet.timestamp.usec = 0;
    }

    /* Set rssi. */
    p_message->msg.phy.msg.packet.has_rssi = true;
    p_message->msg.phy.msg.packet.rssi = rssi;

    /* Copy packet into our message. */
    p_message->msg.phy.msg.packet.packet.size = length;
    memcpy(p_message->msg.phy.msg.packet.packet.bytes, payload, length);

    /* Success. */
    return WHAD_SUCCESS;
}


/**
 * @brief Initialize a message indicating the result of a scheduled packet request
 * 
 * @param[in,out]   p_message           Pointer to the message structure to initialize
 * @param[in]       id                  Scheduled packet identifier
 * @param[in]       full                If set to true, indicate the scheduled packets FIFO is full
 *
 * @retval          WHAD_SUCCESS        Success.
 * @retval          WHAD_ERROR          Invalid message pointer or payload pointer.
 **/

whad_result_t whad_phy_packet_scheduled(Message *p_message, uint8_t id, bool full)
{
    /* Sanity check. */
    if (p_message == NULL)
    {
        return WHAD_ERROR;
    }

    /* Populate fields. */
    p_message->which_msg = Message_phy_tag;
    p_message->msg.phy.which_msg = phy_Message_sched_pkt_rsp_tag;
    p_message->msg.phy.msg.sched_pkt_rsp.id = id;
    if (full)
    {
        p_message->msg.phy.msg.sched_pkt_rsp.has_full = true;
        p_message->msg.phy.msg.sched_pkt_rsp.full = true;
    }
    else
    {
       p_message->msg.phy.msg.sched_pkt_rsp.has_full = false; 
    }

    /* Success. */
    return WHAD_SUCCESS;
}