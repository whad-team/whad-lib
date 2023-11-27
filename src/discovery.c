#include <whad.h>


whad_discovery_msgtype_t whad_discovery_get_message_type(Message *p_message)
{
    whad_discovery_msgtype_t msg_type = WHAD_DISCOVERY_UNKNOWN;

    /* Sanity check. */
    if (p_message->which_msg != Message_discovery_tag)
        return msg_type;

    /* Convert NanoPb message type to whadd_discovery_msgtype_t */
    msg_type = (whad_discovery_msgtype_t)p_message->msg.discovery.which_msg;

    /* Return message type. */
    return msg_type;
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
 * @brief Parse a discovery device info query.
 * 
 * @param[in]       p_message           Pointer to the message structure to initialize
 * @param[in,out]   p_proto_version     Pointer to the output protocol version variable
 * 
 * @retval          WHAD_SUCCESS        Success.
 * @retval          WHAD_ERROR          Invalid message pointer.
 **/

whad_result_t whad_discovery_device_info_query_parse(Message *p_message, uint32_t *p_proto_version)
{
    /* Sanity check. */
    if ((p_message == NULL) || (p_proto_version == NULL))
    {
        return WHAD_ERROR;
    }

    if (p_message->which_msg == Message_discovery_tag)
    {
        if (p_message->msg.discovery.which_msg == discovery_Message_info_query_tag)
        {
            /* Return protocol version. */
            *p_proto_version = p_message->msg.discovery.msg.info_query.proto_ver;

            /* Success. */
            return WHAD_SUCCESS;
        }
    }

    /* Nope. */
    return WHAD_ERROR;
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
 * @brief Parse a domain info query.
 * 
 * @param[in]       p_message           Pointer to the message to parse
 * @param[in,out]   p_domain            Pointer to the domain contained in the query
 * 
 * @retval          WHAD_SUCCESS        Success.
 * @retval          WHAD_ERROR          Invalid message or domain pointer.
 **/

whad_result_t whad_discovery_domain_info_query_parse(Message *p_message, whad_domain_t *p_domain)
{
     /* Sanity check. */
    if ((p_message == NULL) || (p_domain == NULL))
    {
        return WHAD_ERROR;
    }

    if (p_message->which_msg == Message_discovery_tag)
    {
        if (p_message->msg.discovery.which_msg == discovery_Message_domain_query_tag)
        {
            /* Report selected domain. */
            *p_domain = p_message->msg.discovery.msg.domain_query.domain;

            /* Success. */
            return WHAD_SUCCESS;
        }
    }

    /* Nope, that's not a Discovery Domain info query :( */
    return WHAD_ERROR;
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
 * @brief Parse a domain info query.
 * 
 * @param[in]       p_message           Pointer to the message to parse
 * @param[in,out]   p_domain            Pointer to the domain contained in the query
 * 
 * @retval          WHAD_SUCCESS        Success.
 * @retval          WHAD_ERROR          Invalid message or domain pointer.
 **/

whad_result_t whad_discovery_domain_info_resp_parse(Message *p_message, whad_domain_t *p_domain,
                                                    uint64_t *p_supp_commands)
{
     /* Sanity check. */
    if ((p_message == NULL) || (p_domain == NULL) || (p_supp_commands == NULL))
    {
        return WHAD_ERROR;
    }

    if (p_message->which_msg == Message_discovery_tag)
    {
        if (p_message->msg.discovery.which_msg == discovery_Message_domain_resp_tag)
        {
            /* Report selected domain. */
            *p_domain = p_message->msg.discovery.msg.domain_resp.domain;
            *p_supp_commands = p_message->msg.discovery.msg.domain_resp.supported_commands;

            /* Success. */
            return WHAD_SUCCESS;
        }
    }

    /* Nope, that's not a Discovery Domain info query :( */
    return WHAD_ERROR;
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


/**
 * @brief Initialize a device speed configuration message.
 * 
 * @param[in,out]   p_message           Pointer to the message structure to initialize
 * @param[in]       speed               Communication speed
 * 
 * @retval          WHAD_SUCCESS        Success.
 * @retval          WHAD_ERROR          Invalid message pointer.
 **/

whad_result_t whad_discovery_set_speed(Message *p_message, uint32_t speed)
{
    /* Sanity check. */
    if (p_message == NULL)
    {
        return WHAD_ERROR;
    }

    /* Populate fields. */    
    p_message->which_msg = Message_discovery_tag;
    p_message->msg.discovery.which_msg = discovery_Message_set_speed_tag;
    p_message->msg.discovery.msg.set_speed.speed = speed;

    /* Success. */
    return WHAD_SUCCESS;
}


/**
 * @brief Parse a domain info query.
 * 
 * @param[in]       p_message           Pointer to the message to parse
 * @param[in,out]   p_domain            Pointer to the domain contained in the query
 * 
 * @retval          WHAD_SUCCESS        Success.
 * @retval          WHAD_ERROR          Invalid message or domain pointer.
 **/

whad_result_t whad_discovery_set_speed_parse(Message *p_message, uint32_t *p_speed)
{
     /* Sanity check. */
    if ((p_message == NULL) || (p_speed == NULL))
    {
        return WHAD_ERROR;
    }

    if (p_message->which_msg == Message_discovery_tag)
    {
        if (p_message->msg.discovery.which_msg == discovery_Message_set_speed_tag)
        {
            /* Report selected domain. */
            *p_speed = p_message->msg.discovery.msg.set_speed.speed;

            /* Success. */
            return WHAD_SUCCESS;
        }
    }

    /* Nope, that's not a Discovery Domain info query :( */
    return WHAD_ERROR;
}