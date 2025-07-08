#include <whad.h>
#include <domains/ant.h>

whad_ant_msgtype_t whad_ant_get_message_type(Message *p_message)
{
    whad_ant_msgtype_t msg_type = WHAD_ANT_UNKNOWN;

    /* Ensure it is an ANT message. */
    if (whad_get_message_domain(p_message) == DOMAIN_ANT)
    {
        /* Retrieve the message type. */
        msg_type = (whad_ant_msgtype_t)p_message->msg.ant.which_msg;
    }

    /* Success. */
    return msg_type;
}

/********************************
 * ANT messages
 *******************************/

/**
 * @brief   Create a SetDeviceNumberCmd message
 *
 * @param[in]   p_message       Pointer to a NanoPb Message structure
 * @param[in]   channel_number  Integer indicating the channel number
 * @param[in]   device_number   Integer indicating the device number to use
 *
 * @retval          WHAD_SUCCESS        Success.
 * @retval          WHAD_ERROR          Invalid message or address pointer.
 **/

whad_result_t whad_ant_set_device_number(Message *p_message, uint32_t channel_number, uint32_t device_number)
{
    /* Sanity checks. */
    if (p_message == NULL)
    {
        return WHAD_ERROR;
    }

    p_message->which_msg = Message_ant_tag;
    p_message->msg.ant.which_msg = ant_Message_set_device_number_tag;
    p_message->msg.ant.msg.set_device_number.channel_number = channel_number;
    p_message->msg.ant.msg.set_device_number.device_number = device_number;

    /* Success. */
    return WHAD_SUCCESS;
}

/**
 * @brief   Parse a SetDeviceNumberCmd message
 *
 * @param[in]       p_message           Pointer to a NanoPb Message structure
 * @param[in,out]   p_channel_number    Pointer to a channel number
 * @param[in,out]   p_device_number     Pointer to a device number
 *
 * @retval          WHAD_SUCCESS        Success.
 * @retval          WHAD_ERROR          Invalid message or address pointer.
 **/

whad_result_t whad_ant_set_device_number_parse(Message *p_message, uint32_t *p_channel_number, uint32_t *p_device_number)
{
    /* Sanity checks. */
    if (
        (p_message == NULL) || 
        (p_channel_number == NULL) || 
        (p_device_number == NULL)
    )
    {
        return WHAD_ERROR;
    }

    if (p_message->msg.ant.which_msg == ant_Message_set_device_number_tag)
    {
        *p_channel_number = p_message->msg.ant.msg.set_device_number.channel_number;
        *p_device_number = p_message->msg.ant.msg.set_device_number.device_number;
        
        /* Success. */
        return WHAD_SUCCESS;
    }

    /* Wrong message or address size. */
    return WHAD_ERROR;
}

/**
 * @brief   Create a SetDeviceTypeCmd message
 *
 * @param[in]   p_message       Pointer to a NanoPb Message structure
 * @param[in]   channel_number  Integer indicating the channel number
 * @param[in]   device_type   Integer indicating the device type to use
 *
 * @retval          WHAD_SUCCESS        Success.
 * @retval          WHAD_ERROR          Invalid message or address pointer.
 **/

whad_result_t whad_ant_set_device_type(Message *p_message, uint32_t channel_number, uint32_t device_type)
{
    /* Sanity checks. */
    if (p_message == NULL)
    {
        return WHAD_ERROR;
    }

    p_message->which_msg = Message_ant_tag;
    p_message->msg.ant.which_msg = ant_Message_set_device_type_tag;
    p_message->msg.ant.msg.set_device_type.channel_number = channel_number;
    p_message->msg.ant.msg.set_device_type.device_type = device_type;

    /* Success. */
    return WHAD_SUCCESS;
}

/**
 * @brief   Parse a SetDeviceTypeCmd message
 *
 * @param[in]       p_message           Pointer to a NanoPb Message structure
 * @param[in,out]   p_channel_number    Pointer to a channel number
 * @param[in,out]   p_device_type       Pointer to a device type
 *
 * @retval          WHAD_SUCCESS        Success.
 * @retval          WHAD_ERROR          Invalid message or address pointer.
 **/

whad_result_t whad_ant_set_device_type_parse(Message *p_message, uint32_t *p_channel_number, uint32_t *p_device_type)
{
    /* Sanity checks. */
    if (
        (p_message == NULL) || 
        (p_channel_number == NULL) || 
        (p_device_type == NULL)
    )
    {
        return WHAD_ERROR;
    }

    if (p_message->msg.ant.which_msg == ant_Message_set_device_type_tag)
    {
        *p_channel_number = p_message->msg.ant.msg.set_device_type.channel_number;
        *p_device_type = p_message->msg.ant.msg.set_device_type.device_type;
        
        /* Success. */
        return WHAD_SUCCESS;
    }

    /* Wrong message or address size. */
    return WHAD_ERROR;
}


/**
 * @brief   Create a SetTransmissionTypeCmd message
 *
 * @param[in]   p_message           Pointer to a NanoPb Message structure
 * @param[in]   channel_number      Integer indicating the channel number
 * @param[in]   transmission_type   Integer indicating the transmission type to use
 *
 * @retval          WHAD_SUCCESS        Success.
 * @retval          WHAD_ERROR          Invalid message or address pointer.
 **/

whad_result_t whad_ant_set_transmission_type(Message *p_message, uint32_t channel_number, uint32_t transmission_type)
{
    /* Sanity checks. */
    if (p_message == NULL)
    {
        return WHAD_ERROR;
    }

    p_message->which_msg = Message_ant_tag;
    p_message->msg.ant.which_msg = ant_Message_set_transmission_type_tag;
    p_message->msg.ant.msg.set_transmission_type.channel_number = channel_number;
    p_message->msg.ant.msg.set_transmission_type.transmission_type = transmission_type;

    /* Success. */
    return WHAD_SUCCESS;
}

/**
 * @brief   Parse a SetTransmissionTypeCmd message
 *
 * @param[in]       p_message               Pointer to a NanoPb Message structure
 * @param[in,out]   p_channel_number        Pointer to a channel number
 * @param[in,out]   p_transmission_type     Pointer to a transmission type
 *
 * @retval          WHAD_SUCCESS        Success.
 * @retval          WHAD_ERROR          Invalid message or address pointer.
 **/

whad_result_t whad_ant_set_transmission_type_parse(Message *p_message, uint32_t *p_channel_number, uint32_t *p_transmission_type)
{
    /* Sanity checks. */
    if (
        (p_message == NULL) || 
        (p_channel_number == NULL) || 
        (p_transmission_type == NULL)
    )
    {
        return WHAD_ERROR;
    }

    if (p_message->msg.ant.which_msg == ant_Message_set_device_type_tag)
    {
        *p_channel_number = p_message->msg.ant.msg.set_transmission_type.channel_number;
        *p_transmission_type = p_message->msg.ant.msg.set_transmission_type.transmission_type;
        
        /* Success. */
        return WHAD_SUCCESS;
    }

    /* Wrong message or address size. */
    return WHAD_ERROR;
}

/**
 * @brief   Create a SetChannelPeriodCmd message
 *
 * @param[in]   p_message           Pointer to a NanoPb Message structure
 * @param[in]   channel_number      Integer indicating the channel number
 * @param[in]   channel_period      Integer indicating the channel period to use
 *
 * @retval          WHAD_SUCCESS        Success.
 * @retval          WHAD_ERROR          Invalid message or address pointer.
 **/

whad_result_t whad_ant_set_channel_period(Message *p_message, uint32_t channel_number, uint32_t channel_period)
{
    /* Sanity checks. */
    if (p_message == NULL)
    {
        return WHAD_ERROR;
    }

    p_message->which_msg = Message_ant_tag;
    p_message->msg.ant.which_msg = ant_Message_set_channel_period_tag;
    p_message->msg.ant.msg.set_channel_period.channel_number = channel_number;
    p_message->msg.ant.msg.set_channel_period.channel_period = channel_period;

    /* Success. */
    return WHAD_SUCCESS;
}

/**
 * @brief   Parse a SetChannelPeriodCmd message
 *
 * @param[in]       p_message               Pointer to a NanoPb Message structure
 * @param[in,out]   p_channel_number        Pointer to a channel number
 * @param[in,out]   p_channel_period        Pointer to a channel period
 *
 * @retval          WHAD_SUCCESS        Success.
 * @retval          WHAD_ERROR          Invalid message or address pointer.
 **/

whad_result_t whad_ant_set_channel_period_parse(Message *p_message, uint32_t *p_channel_number, uint32_t *p_channel_period)
{
    /* Sanity checks. */
    if (
        (p_message == NULL) || 
        (p_channel_number == NULL) || 
        (p_channel_period == NULL)
    )
    {
        return WHAD_ERROR;
    }

    if (p_message->msg.ant.which_msg == ant_Message_set_channel_period_tag)
    {
        *p_channel_number = p_message->msg.ant.msg.set_channel_period.channel_number;
        *p_channel_period = p_message->msg.ant.msg.set_channel_period.channel_period;
        
        /* Success. */
        return WHAD_SUCCESS;
    }

    /* Wrong message or address size. */
    return WHAD_ERROR;
}



/**
 * @brief   Create a SetNetworkKeyCmd message
 *
 * @param[in]   p_message           Pointer to a NanoPb Message structure
 * @param[in]   channel_number      Integer indicating the channel number
 * @param[in]   p_network_key       Pointer to a 8-bytes long string representing a network key 
 *
 * @retval          WHAD_SUCCESS        Success.
 * @retval          WHAD_ERROR          Invalid message or address pointer.
 **/

whad_result_t whad_ant_set_network_key(Message *p_message, uint32_t network_number, uint8_t *p_network_key)
{
    /* Sanity checks. */
    if ((p_message == NULL) || (network_key == NULL) )
    {
        return WHAD_ERROR;
    }

    p_message->which_msg = Message_ant_tag;
    p_message->msg.ant.which_msg = ant_Message_set_network_key_tag;

    p_message->msg.ant.msg.set_network_key.network_number = network_number;
    p_message->msg.ant.msg.set_network_key.network_key.size = ANT_NETWORK_KEY_SIZE; 
    memcpy(p_message->msg.ant.msg.set_network_key.network_key.bytes, p_network_key, ANT_NETWORK_KEY_SIZE);

    /* Success. */
    return WHAD_SUCCESS;
}

/**
 * @brief   Parse a SetNetworkKeyCmd message
 *
 * @param[in]       p_message               Pointer to a NanoPb Message structure
 * @param[in,out]   p_network_number        Pointer to a network number
 * @param[in,out]   p_network_key           Pointer to a network key
 *
 * @retval          WHAD_SUCCESS        Success.
 * @retval          WHAD_ERROR          Invalid message or address pointer.
 **/

whad_result_t whad_ant_set_network_key_parse(Message *p_message, uint32_t *p_network_number, uint8_t *p_network_key)
{
    /* Sanity checks. */
    if (
        (p_message == NULL) || 
        (p_network_number == NULL) || 
        (p_network_key == NULL)
    )
    {
        return WHAD_ERROR;
    }

    if (p_message->msg.ant.which_msg == ant_Message_set_network_key_tag)
    {
        *p_network_number = p_message->msg.ant.msg.set_network_key.network_number;
        memcpy(
                p_network_key,
                p_message->msg.ant.msg.set_network_key.network_key.bytes,
                ANT_NETWORK_KEY_SIZE
        );

        /* Success. */
        return WHAD_SUCCESS;
    }

    /* Wrong message or address size. */
    return WHAD_ERROR;
}


/**
 * @brief   Create a AssignChannelCmd message
 *
 * @param[in]   p_message                   Pointer to a NanoPb Message structure
 * @param[in]   channel_number              Integer indicating a channel number 
 * @param[in]   network_number              Integer indicating a network number 
 * @param[in]   channel_type                `whad_ant_channel_type_t` indicating the channel type
 * @param[in]   background_scanning         Boolean indicating if background scanning must be enabled 
 * @param[in]   frequency_agility           Boolean indicating if frequency agility must be enabled 
 * @param[in]   fast_channel_initiation     Boolean indicating if fast channel initiation must be enabled 
 * @param[in]   asynchronous_transmission   Boolean indicating if asynchronous transmission must be enabled 
 *
 * @retval          WHAD_SUCCESS        Success.
 * @retval          WHAD_ERROR          Invalid message or address pointer.
 **/

whad_result_t whad_ant_assign_channel(
                                        Message *p_message, uint32_t channel_number, 
                                        uint32_t network_number, whad_ant_channel_type_t channel_type, 
                                        bool background_scanning, bool frequency_agility, 
                                        bool fast_channel_initiation, bool asynchronous_transmission
)
{
    /* Sanity checks. */
    if ((p_message == NULL) || (network_key == NULL) )
    {
        return WHAD_ERROR;
    }

    p_message->which_msg = Message_ant_tag;
    p_message->msg.ant.which_msg = ant_Message_assign_channel_tag;

    p_message->msg.ant.msg.assign_channel.channel_number = channel_number;
    p_message->msg.ant.msg.assign_channel.network_number = network_number;
    p_message->msg.ant.msg.assign_channel.channel_type   = (ant_AntChannelType)channel_type;

    p_message->msg.ant.msg.assign_channel.has_background_scanning = true;
    p_message->msg.ant.msg.assign_channel.background_scanning = background_scanning;

    p_message->msg.ant.msg.assign_channel.has_frequency_agility = true;
    p_message->msg.ant.msg.assign_channel.frequency_agility = frequency_agility;

    p_message->msg.ant.msg.assign_channel.has_fast_channel_initiation = true;
    p_message->msg.ant.msg.assign_channel.fast_channel_initiation = fast_channel_initiation;

    p_message->msg.ant.msg.assign_channel.has_asynchronous_transmission = true;
    p_message->msg.ant.msg.assign_channel.asynchronous_transmission = asynchronous_transmission;

    /* Success. */
    return WHAD_SUCCESS;
}

/**
 * @brief   Parse a AssignChannelCmd message
 *
 * @param[in]       p_message               Pointer to a NanoPb Message structure
 * @param[in,out]   p_params                Pointer to a `whad_ant_assign_channel_params_t`
 *
 * @retval          WHAD_SUCCESS        Success.
 * @retval          WHAD_ERROR          Invalid message or address pointer.
 **/

whad_result_t whad_ant_assign_channel_parse(Message *p_message, whad_ant_assign_channel_params_t *p_params)
{
    /* Sanity checks. */
    if (
        (p_message == NULL) || 
        (p_params == NULL)
    )
    {
        return WHAD_ERROR;
    }

    if (p_message->msg.ant.which_msg == ant_Message_set_assign_channel_tag)
    {
        p_params->channel_number = p_message->msg.ant.msg.assign_channel.channel_number;
        p_params->network_number = p_message->msg.ant.msg.assign_channel.network_number;
        p_params->channel_type = (whad_ant_channel_type_t)p_message->msg.ant.msg.assign_channel.channel_type;

        p_params->has_background_scanning = p_message->msg.ant.msg.assign_channel.has_background_scanning;
        if (p_message->msg.ant.msg.assign_channel.has_background_scanning) {
            p_params->background_scanning = p_message->msg.ant.msg.assign_channel.background_scanning;
        }

        p_params->has_frequency_agility = p_message->msg.ant.msg.assign_channel.has_frequency_agility;
        if (p_message->msg.ant.msg.assign_channel.has_frequency_agility) {
            p_params->frequency_agility = p_message->msg.ant.msg.assign_channel.frequency_agility;
        }

        p_params->has_fast_channel_initiation = p_message->msg.ant.msg.assign_channel.has_fast_channel_initiation;
        if (p_message->msg.ant.msg.assign_channel.has_fast_channel_initiation) {
            p_params->fast_channel_initiation = p_message->msg.ant.msg.assign_channel.fast_channel_initiation;
        }
        p_params->has_asynchronous_transmission = p_message->msg.ant.msg.assign_channel.has_asynchronous_transmission;
        if (p_message->msg.ant.msg.assign_channel.has_asynchronous_transmission) {
            p_params->asynchronous_transmission = p_message->msg.ant.msg.assign_channel.asynchronous_transmission;
        }

        /* Success. */
        return WHAD_SUCCESS;
    }

    /* Wrong message or address size. */
    return WHAD_ERROR;
}


/**
 * @brief   Create a UnassignChannelCmd message
 *
 * @param[in]   p_message           Pointer to a NanoPb Message structure
 * @param[in]   channel_number      Integer indicating the channel number
 *
 * @retval          WHAD_SUCCESS        Success.
 * @retval          WHAD_ERROR          Invalid message or address pointer.
 **/

whad_result_t whad_ant_unassign_channel(Message *p_message, uint32_t channel_number)
{
    /* Sanity checks. */
    if (p_message == NULL) {
        return WHAD_ERROR;
    }

    p_message->which_msg = Message_ant_tag;
    p_message->msg.ant.which_msg = ant_Message_unassign_channel_tag;

    p_message->msg.ant.msg.unassign_channel.channel_number = channel_number;

    /* Success. */
    return WHAD_SUCCESS;
}

/**
 * @brief   Parse a UnassignChannelCmd message
 *
 * @param[in]       p_message               Pointer to a NanoPb Message structure
 * @param[in,out]   p_channel_number        Pointer to a channel number
 *
 * @retval          WHAD_SUCCESS        Success.
 * @retval          WHAD_ERROR          Invalid message or address pointer.
 **/

whad_result_t whad_ant_unassign_channel_parse(Message *p_message, uint32_t *p_channel_number)
{
    /* Sanity checks. */
    if ((p_message == NULL) || (p_channel_number == NULL))
    {
        return WHAD_ERROR;
    }

    if (p_message->msg.ant.which_msg == ant_Message_unassign_channel_tag)
    {
        *p_channel_number = p_message->msg.ant.msg.unassign_channel.channel_number;
        /* Success. */
        return WHAD_SUCCESS;
    }

    /* Wrong message or address size. */
    return WHAD_ERROR;
}


/**
 * @brief   Create a OpenChannelCmd message
 *
 * @param[in]   p_message           Pointer to a NanoPb Message structure
 * @param[in]   channel_number      Integer indicating the channel number
 *
 * @retval          WHAD_SUCCESS        Success.
 * @retval          WHAD_ERROR          Invalid message or address pointer.
 **/

whad_result_t whad_ant_open_channel(Message *p_message, uint32_t channel_number)
{
    /* Sanity checks. */
    if (p_message == NULL) {
        return WHAD_ERROR;
    }

    p_message->which_msg = Message_ant_tag;
    p_message->msg.ant.which_msg = ant_Message_open_channel_tag;

    p_message->msg.ant.msg.open_channel.channel_number = channel_number;

    /* Success. */
    return WHAD_SUCCESS;
}

/**
 * @brief   Parse a OpenChannelCmd message
 *
 * @param[in]       p_message               Pointer to a NanoPb Message structure
 * @param[in,out]   p_channel_number        Pointer to a channel number
 *
 * @retval          WHAD_SUCCESS        Success.
 * @retval          WHAD_ERROR          Invalid message or address pointer.
 **/

whad_result_t whad_ant_open_channel_parse(Message *p_message, uint32_t *p_channel_number)
{
    /* Sanity checks. */
    if ((p_message == NULL) || (p_channel_number == NULL))
    {
        return WHAD_ERROR;
    }

    if (p_message->msg.ant.which_msg == ant_Message_open_channel_tag)
    {
        *p_channel_number = p_message->msg.ant.msg.open_channel.channel_number;
        /* Success. */
        return WHAD_SUCCESS;
    }

    /* Wrong message or address size. */
    return WHAD_ERROR;
}

/**
 * @brief   Create a CloseChannelCmd message
 *
 * @param[in]   p_message           Pointer to a NanoPb Message structure
 * @param[in]   channel_number      Integer indicating the channel number
 *
 * @retval          WHAD_SUCCESS        Success.
 * @retval          WHAD_ERROR          Invalid message or address pointer.
 **/

whad_result_t whad_ant_close_channel(Message *p_message, uint32_t channel_number)
{
    /* Sanity checks. */
    if (p_message == NULL) {
        return WHAD_ERROR;
    }

    p_message->which_msg = Message_ant_tag;
    p_message->msg.ant.which_msg = ant_Message_close_channel_tag;

    p_message->msg.ant.msg.close_channel.channel_number = channel_number;

    /* Success. */
    return WHAD_SUCCESS;
}

/**
 * @brief   Parse a CloseChannelCmd message
 *
 * @param[in]       p_message               Pointer to a NanoPb Message structure
 * @param[in,out]   p_channel_number        Pointer to a channel number
 *
 * @retval          WHAD_SUCCESS        Success.
 * @retval          WHAD_ERROR          Invalid message or address pointer.
 **/

whad_result_t whad_ant_close_channel_parse(Message *p_message, uint32_t *p_channel_number)
{
    /* Sanity checks. */
    if ((p_message == NULL) || (p_channel_number == NULL))
    {
        return WHAD_ERROR;
    }

    if (p_message->msg.ant.which_msg == ant_Message_close_channel_tag)
    {
        *p_channel_number = p_message->msg.ant.msg.close_channel.channel_number;
        /* Success. */
        return WHAD_SUCCESS;
    }

    /* Wrong message or address size. */
    return WHAD_ERROR;
}

/**
 * @brief   Create a SetRFChannelCmd message
 *
 * @param[in]   p_message           Pointer to a NanoPb Message structure
 * @param[in]   channel_number      Integer indicating the channel number
 * @param[in]   rf_channel          Integer indicating the RF channel
 *
 * @retval          WHAD_SUCCESS        Success.
 * @retval          WHAD_ERROR          Invalid message or address pointer.
 **/

whad_result_t whad_ant_set_rf_channel(Message *p_message, uint32_t channel_number, uint32_t rf_channel)
{
    /* Sanity checks. */
    if (p_message == NULL) {
        return WHAD_ERROR;
    }

    p_message->which_msg = Message_ant_tag;
    p_message->msg.ant.which_msg = ant_Message_set_rf_channel_tag;

    p_message->msg.ant.msg.set_rf_channel.channel_number = channel_number;
    p_message->msg.ant.msg.set_rf_channel.rf_channel = rf_channel;

    /* Success. */
    return WHAD_SUCCESS;
}

/**
 * @brief   Parse a SetRFChannelCmd message
 *
 * @param[in]       p_message               Pointer to a NanoPb Message structure
 * @param[in,out]   p_channel_number        Pointer to a channel number
 * @param[in,out]   p_rf_channel            Pointer to a RF channel
 *
 * @retval          WHAD_SUCCESS        Success.
 * @retval          WHAD_ERROR          Invalid message or address pointer.
 **/

whad_result_t whad_ant_set_rf_channel_parse(Message *p_message, uint32_t *p_channel_number, uint32_t *p_rf_channel)
{
    /* Sanity checks. */
    if ((p_message == NULL) || (p_channel_number == NULL) || (p_rf_channel == NULL))
    {
        return WHAD_ERROR;
    }

    if (p_message->msg.ant.which_msg == ant_Message_set_rf_channel_tag)
    {
        *p_channel_number = p_message->msg.ant.msg.set_rf_channel.channel_number;
        *p_rf_channel = p_message->msg.ant.msg.set_rf_channel.rf_channel;

        /* Success. */
        return WHAD_SUCCESS;
    }

    /* Wrong message or address size. */
    return WHAD_ERROR;
}


/**
 * @brief   Create a SniffCmd message
 *
 * @param[in]   p_message           Pointer to a NanoPb Message structure
 * @param[in]   rf_channel          Integer indicating the RF channel
 * @param[in]   network_key         Pointer to a 8-bytes long buffer indicating the network key
 * @param[in]   device_number       Integer indicating the device number
 * @param[in]   device_type         Integer indicating the device type
 * @param[in]   transmission_type   Integer indicating the transmission type
 *
 * @retval          WHAD_SUCCESS        Success.
 * @retval          WHAD_ERROR          Invalid message or address pointer.
 **/

whad_result_t whad_ant_sniff(Message *p_message, uint32_t rf_channel, uint8_t *network_key, uint32_t device_number, uint32_t device_type, uint32_t transmission_type)
{
    /* Sanity checks. */
    if (p_message == NULL) {
        return WHAD_ERROR;
    }

    p_message->which_msg = Message_ant_tag;
    p_message->msg.ant.which_msg = ant_Message_sniff_tag;

    p_message->msg.ant.msg.sniff.rf_channel = rf_channel;
    memcpy(p_message->msg.ant.msg.sniff.network_key, network_key, ANT_NETWORK_KEY_SIZE);
    p_message->msg.ant.msg.sniff.device_number = device_number;
    p_message->msg.ant.msg.sniff.device_type = device_type;
    p_message->msg.ant.msg.sniff.transmission_type = transmission_type;

    /* Success. */
    return WHAD_SUCCESS;
}

/**
 * @brief   Parse a SniffCmd message
 *
 * @param[in]       p_message               Pointer to a NanoPb Message structure
 * @param[in,out]   p_params                Pointer to a `whad_ant_sniff_params_t` parameters
 *
 * @retval          WHAD_SUCCESS        Success.
 * @retval          WHAD_ERROR          Invalid message or address pointer.
 **/

whad_result_t whad_ant_sniff_parse(Message *p_message, whad_ant_sniff_params_t *p_params)
{
    /* Sanity checks. */
    if ((p_message == NULL) || (p_params == NULL))
    {
        return WHAD_ERROR;
    }

    if (p_message->msg.ant.which_msg == ant_Message_sniff_tag)
    {
        p_params->rf_channel = p_message->msg.ant.msg.sniff.rf_channel;
        memcpy(p_params->network_key, p_message->msg.ant.msg.sniff.network_key, ANT_NETWORK_KEY_SIZE);
        p_params->device_number = p_message->msg.ant.msg.sniff.device_number;
        p_params->device_type = p_message->msg.ant.msg.sniff.device_type;
        p_params->transmission_type = p_message->msg.ant.msg.sniff.transmission_type;

        /* Success. */
        return WHAD_SUCCESS;
    }

    /* Wrong message or address size. */
    return WHAD_ERROR;
}

/**
 * @brief   Create a JamCmd message
 *
 * @param[in]   p_message           Pointer to a NanoPb Message structure
 * @param[in]   rf_channel          Integer indicating the RF channel
 *
 * @retval          WHAD_SUCCESS        Success.
 * @retval          WHAD_ERROR          Invalid message or address pointer.
 **/

whad_result_t whad_ant_jam(Message *p_message, uint32_t rf_channel)
{
    /* Sanity checks. */
    if (p_message == NULL) {
        return WHAD_ERROR;
    }

    p_message->which_msg = Message_ant_tag;
    p_message->msg.ant.which_msg = ant_Message_jam_tag;

    p_message->msg.ant.msg.jam.rf_channel = rf_channel;

    /* Success. */
    return WHAD_SUCCESS;
}

/**
 * @brief   Parse a JamCmd message
 *
 * @param[in]       p_message               Pointer to a NanoPb Message structure
 * @param[in,out]   p_rf_channel            Pointer to an integer indicating the RF channel
 *
 * @retval          WHAD_SUCCESS        Success.
 * @retval          WHAD_ERROR          Invalid message or address pointer.
 **/

whad_result_t whad_ant_jam_parse(Message *p_message, uint32_t *p_rf_channel)
{
    /* Sanity checks. */
    if ((p_message == NULL) || (p_rf_channel == NULL))
    {
        return WHAD_ERROR;
    }

    if (p_message->msg.ant.which_msg == ant_Message_jam_tag)
    {
        *p_rf_channel = p_message->msg.ant.msg.jam.rf_channel;
        
        /* Success. */
        return WHAD_SUCCESS;
    }

    /* Wrong message or address size. */
    return WHAD_ERROR;
}


/**
 * @brief   Create a SendCmd message
 *
 * @param[in]   p_message           Pointer to a NanoPb Message structure
 * @param[in]   rf_channel          Integer indicating the RF channel
 * @param[in]   channel_number      Integer indicating the channel number
 * @param[in]   p_packet            Pointer to a PDU
 * @param[in]   packet_len          Integer indicating the PDU length
 *
 * @retval          WHAD_SUCCESS        Success.
 * @retval          WHAD_ERROR          Invalid message or address pointer.
 **/

whad_result_t whad_ant_send(Message *p_message, uint32_t rf_channel, uint32_t channel_number, uint8_t *p_packet, size_t packet_len)
{
    /* Sanity checks. */
    if (p_message == NULL) {
        return WHAD_ERROR;
    }

    p_message->which_msg = Message_ant_tag;
    p_message->msg.ant.which_msg = ant_Message_send_tag;

    p_message->msg.ant.msg.send.rf_channel = rf_channel;
    p_message->msg.ant.msg.send.channel_number = channel_number;
    p_message->msg.ant.msg.send.pdu.size = packet_len;
    memcpy(p_message->msg.ant.msg.send.pdu.bytes, p_packet, packet_len);

    /* Success. */
    return WHAD_SUCCESS;
}

/**
 * @brief   Parse a SendCmd message
 *
 * @param[in]       p_message               Pointer to a NanoPb Message structure
 * @param[in,out]   p_params                Pointer to a `whad_ant_send_params_t` parameters
 *
 * @retval          WHAD_SUCCESS        Success.
 * @retval          WHAD_ERROR          Invalid message or address pointer.
 **/

whad_result_t whad_ant_send_parse(Message *p_message, whad_ant_send_params_t* p_params)
{
    /* Sanity checks. */
    if ((p_message == NULL) || (p_params == NULL))
    {
        return WHAD_ERROR;
    }

    if (p_message->msg.ant.which_msg == ant_Message_send_tag)
    {
        p_params->rf_channel = p_message->msg.ant.msg.send.rf_channel;
        p_params->channel_number = p_message->msg.ant.msg.send.channel_number;
        p_params->packet.length = p_message->msg.ant.msg.send.pdu.size;
        memcpy(p_params->packet.bytes, p_message->msg.ant.msg.send.pdu.bytes, p_message->msg.ant.msg.send.pdu.size);
        
        /* Success. */
        return WHAD_SUCCESS;
    }

    /* Wrong message or address size. */
    return WHAD_ERROR;
}


/**
 * @brief   Create a SendRawCmd message
 *
 * @param[in]   p_message           Pointer to a NanoPb Message structure
 * @param[in]   rf_channel          Integer indicating the RF channel
 * @param[in]   channel_number      Integer indicating the channel number
 * @param[in]   p_packet            Pointer to a PDU
 * @param[in]   packet_len          Integer indicating the PDU length
 *
 * @retval          WHAD_SUCCESS        Success.
 * @retval          WHAD_ERROR          Invalid message or address pointer.
 **/

whad_result_t whad_ant_send_raw(Message *p_message, uint32_t rf_channel, uint32_t channel_number, uint8_t *p_packet, size_t packet_len)
{
    /* Sanity checks. */
    if (p_message == NULL) {
        return WHAD_ERROR;
    }

    p_message->which_msg = Message_ant_tag;
    p_message->msg.ant.which_msg = ant_Message_send_raw_tag;

    p_message->msg.ant.msg.send_raw.rf_channel = rf_channel;
    p_message->msg.ant.msg.send_raw.channel_number = channel_number;
    p_message->msg.ant.msg.send_raw.pdu.size = packet_len;
    memcpy(p_message->msg.ant.msg.send_raw.pdu.bytes, p_packet, packet_len);

    /* Success. */
    return WHAD_SUCCESS;
}

/**
 * @brief   Parse a SendRawCmd message
 *
 * @param[in]       p_message               Pointer to a NanoPb Message structure
 * @param[in,out]   p_params                Pointer to a `whad_ant_send_params_t` parameters
 *
 * @retval          WHAD_SUCCESS        Success.
 * @retval          WHAD_ERROR          Invalid message or address pointer.
 **/

whad_result_t whad_ant_send_raw_parse(Message *p_message, whad_ant_send_params_t* p_params)
{
    /* Sanity checks. */
    if ((p_message == NULL) || (p_params == NULL))
    {
        return WHAD_ERROR;
    }

    if (p_message->msg.ant.which_msg == ant_Message_send_raw_tag)
    {
        p_params->rf_channel = p_message->msg.ant.msg.send_raw.rf_channel;
        p_params->channel_number = p_message->msg.ant.msg.send_raw.channel_number;
        p_params->packet.length = p_message->msg.ant.msg.send_raw.pdu.size;
        memcpy(p_params->packet.bytes, p_message->msg.ant.msg.send_raw.pdu.bytes, p_message->msg.ant.msg.send_raw.pdu.size);
        
        /* Success. */
        return WHAD_SUCCESS;
    }

    /* Wrong message or address size. */
    return WHAD_ERROR;
}

/**
 * @brief   Create a MasterModeCmd message
 *
 * @param[in]   p_message           Pointer to a NanoPb Message structure
 * @param[in]   channel_number      Integer indicating the channel number
 *
 * @retval          WHAD_SUCCESS        Success.
 * @retval          WHAD_ERROR          Invalid message or address pointer.
 **/

whad_result_t whad_ant_master_mode(Message *p_message, uint32_t channel_number)
{
    /* Sanity checks. */
    if (p_message == NULL) {
        return WHAD_ERROR;
    }

    p_message->which_msg = Message_ant_tag;
    p_message->msg.ant.which_msg = ant_Message_master_mode_tag;

    p_message->msg.ant.msg.master_mode.channel_number = channel_number;

    /* Success. */
    return WHAD_SUCCESS;
}

/**
 * @brief   Parse a MasterModeCmd message
 *
 * @param[in]       p_message               Pointer to a NanoPb Message structure
 * @param[in,out]   p_channel_number        Pointer to a channel number
 *
 * @retval          WHAD_SUCCESS        Success.
 * @retval          WHAD_ERROR          Invalid message or address pointer.
 **/

whad_result_t whad_ant_master_mode_parse(Message *p_message, uint32_t *p_channel_number)
{
    /* Sanity checks. */
    if ((p_message == NULL) || (p_channel_number == NULL))
    {
        return WHAD_ERROR;
    }

    if (p_message->msg.ant.which_msg == ant_Message_master_mode_tag)
    {
        *p_channel_number = p_message->msg.ant.msg.master_mode.channel_number;
        /* Success. */
        return WHAD_SUCCESS;
    }

    /* Wrong message or address size. */
    return WHAD_ERROR;
}

/**
 * @brief   Create a SlaveModeCmd message
 *
 * @param[in]   p_message           Pointer to a NanoPb Message structure
 * @param[in]   channel_number      Integer indicating the channel number
 *
 * @retval          WHAD_SUCCESS        Success.
 * @retval          WHAD_ERROR          Invalid message or address pointer.
 **/

whad_result_t whad_ant_slave_mode(Message *p_message, uint32_t channel_number)
{
    /* Sanity checks. */
    if (p_message == NULL) {
        return WHAD_ERROR;
    }

    p_message->which_msg = Message_ant_tag;
    p_message->msg.ant.which_msg = ant_Message_slave_mode_tag;

    p_message->msg.ant.msg.slave_mode.channel_number = channel_number;

    /* Success. */
    return WHAD_SUCCESS;
}

/**
 * @brief   Parse a SlaveModeCmd message
 *
 * @param[in]       p_message               Pointer to a NanoPb Message structure
 * @param[in,out]   p_channel_number        Pointer to a channel number
 *
 * @retval          WHAD_SUCCESS        Success.
 * @retval          WHAD_ERROR          Invalid message or address pointer.
 **/

whad_result_t whad_ant_slave_mode_parse(Message *p_message, uint32_t *p_channel_number)
{
    /* Sanity checks. */
    if ((p_message == NULL) || (p_channel_number == NULL))
    {
        return WHAD_ERROR;
    }

    if (p_message->msg.ant.which_msg == ant_Message_slave_mode_tag)
    {
        *p_channel_number = p_message->msg.ant.msg.slave_mode.channel_number;
        /* Success. */
        return WHAD_SUCCESS;
    }

    /* Wrong message or address size. */
    return WHAD_ERROR;
}


/**
 * @brief   Create a StartCmd message
 *
 * @param[in]   p_message   Pointer to a NanoPb Message structure
 *
 * @retval      WHAD_SUCCESS        Success.
 * @retval      WHAD_ERROR          Invalid message or packet pointer.
 **/

whad_result_t whad_ant_start(Message *p_message)
{
    /* Sanity check. */
    if (p_message == NULL)
    {
        /* Error. */
        return WHAD_ERROR;
    }

    p_message->which_msg = Message_ant_tag;
    p_message->msg.ant.which_msg = ant_Message_start_tag;

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

whad_result_t whad_ant_stop(Message *p_message)
{
    /* Sanity check. */
    if (p_message == NULL)
    {
        /* Error. */
        return WHAD_ERROR;
    }

    p_message->which_msg = Message_ant_tag;
    p_message->msg.ant.which_msg = ant_Message_stop_tag;

    /* Success. */
    return WHAD_SUCCESS;
}


/**
 * @brief   Create a ListChannelsCmd message
 *
 * @param[in]   p_message   Pointer to a NanoPb Message structure
 *
 * @retval      WHAD_SUCCESS        Success.
 * @retval      WHAD_ERROR          Invalid message or packet pointer.
 **/

whad_result_t whad_ant_list_channels(Message *p_message)
{
    /* Sanity check. */
    if (p_message == NULL)
    {
        /* Error. */
        return WHAD_ERROR;
    }

    p_message->which_msg = Message_ant_tag;
    p_message->msg.ant.which_msg = ant_Message_list_channels_tag;

    /* Success. */
    return WHAD_SUCCESS;
}


/**
 * @brief   Create a ListNetworksCmd message
 *
 * @param[in]   p_message   Pointer to a NanoPb Message structure
 *
 * @retval      WHAD_SUCCESS        Success.
 * @retval      WHAD_ERROR          Invalid message or packet pointer.
 **/

whad_result_t whad_ant_list_networks(Message *p_message)
{
    /* Sanity check. */
    if (p_message == NULL)
    {
        /* Error. */
        return WHAD_ERROR;
    }

    p_message->which_msg = Message_ant_tag;
    p_message->msg.ant.which_msg = ant_Message_list_networks_tag;

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

whad_result_t whad_ant_jammed(Message *p_message, uint32_t timestamp)
{
    /* Sanity check. */
    if (p_message == NULL)
    {
        /* Error. */
        return WHAD_ERROR;
    }

    p_message->which_msg = Message_ant_tag;
    p_message->msg.ant.which_msg = ant_Message_jammed_tag;
    p_message->msg.ant.msg.jammed.timestamp = timestamp;

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

whad_result_t whad_ant_jammed_parse(Message *p_message, uint32_t *p_timestamp)
{
    /* Sanity check. */
    if ((p_message == NULL) || (p_timestamp == NULL))
    {
        /* Error. */
        return WHAD_ERROR;
    }

    /* Set output channel. */
    *p_timestamp = p_message->msg.ant.msg.jammed.timestamp;

    /* Success. */
    return WHAD_SUCCESS;
}


/**
 * @brief   Create a AvailableChannels message
 *
 * @param[in]   p_message           Pointer to a NanoPb Message structure
 * @param[in]   number_of_channels  Integer indicating the number of channels 
 *
 * @retval      WHAD_SUCCESS        Success.
 * @retval      WHAD_ERROR          Invalid message or packet pointer.
 **/

whad_result_t whad_ant_available_channels(Message *p_message, uint32_t number_of_channels)
{
    /* Sanity check. */
    if (p_message == NULL)
    {
        /* Error. */
        return WHAD_ERROR;
    }

    p_message->which_msg = Message_ant_tag;
    p_message->msg.ant.which_msg = ant_Message_available_channels_tag;
    p_message->msg.ant.msg.available_channels.number_of_channels = number_of_channels;

    /* Success. */
    return WHAD_SUCCESS;
}

/**
 * @brief   Parse a AvailableChannels message
 *
 * @param[in]       p_message   Pointer to a NanoPb Message structure
 * @param[in,out]   p_timestamp Pointer to the timestamp
 *
 * @retval      WHAD_SUCCESS        Success.
 * @retval      WHAD_ERROR          Invalid message or channel pointer.
 **/

whad_result_t whad_ant_available_channels_parse(Message *p_message, uint32_t *p_number_of_channels)
{
    /* Sanity check. */
    if ((p_message == NULL) || (p_number_of_channels == NULL))
    {
        /* Error. */
        return WHAD_ERROR;
    }

    /* Set output channel. */
    *p_number_of_channels = p_message->msg.ant.msg.available_channels.number_of_channels;

    /* Success. */
    return WHAD_SUCCESS;
}

/**
 * @brief   Create a AvailableNetworks message
 *
 * @param[in]   p_message           Pointer to a NanoPb Message structure
 * @param[in]   number_of_networks  Integer indicating the number of networks 
 *
 * @retval      WHAD_SUCCESS        Success.
 * @retval      WHAD_ERROR          Invalid message or packet pointer.
 **/

whad_result_t whad_ant_available_networks(Message *p_message, uint32_t number_of_networks)
{
    /* Sanity check. */
    if (p_message == NULL)
    {
        /* Error. */
        return WHAD_ERROR;
    }

    p_message->which_msg = Message_ant_tag;
    p_message->msg.ant.which_msg = ant_Message_available_networks_tag;
    p_message->msg.ant.msg.available_networks.number_of_networks = number_of_networks;

    /* Success. */
    return WHAD_SUCCESS;
}

/**
 * @brief   Parse a AvailableNetworks message
 *
 * @param[in]       p_message   Pointer to a NanoPb Message structure
 * @param[in,out]   p_timestamp Pointer to the timestamp
 *
 * @retval      WHAD_SUCCESS        Success.
 * @retval      WHAD_ERROR          Invalid message or channel pointer.
 **/

whad_result_t whad_ant_available_networks_parse(Message *p_message, uint32_t *p_number_of_networks)
{
    /* Sanity check. */
    if ((p_message == NULL) || (p_number_of_networks == NULL))
    {
        /* Error. */
        return WHAD_ERROR;
    }

    /* Set output channel. */
    *p_number_of_networks = p_message->msg.ant.msg.available_networks.number_of_networks;

    /* Success. */
    return WHAD_SUCCESS;
}



/**
 * @brief   Create a RawPduReceived message
 *
 * @param[in,out]   p_message   Pointer to a NanoPb Message structure
 * @param[in]       p_pdu       Pointer to a `whad_ant_recvd_packet_t` structure
 *
 * @retval      WHAD_SUCCESS        Success.
 * @retval      WHAD_ERROR          Invalid message or packet pointer.
 **/

whad_result_t whad_ant_raw_pdu_received(Message *p_message, whad_ant_recvd_packet_t *p_pdu)
{
    /* Sanity check. */
    if ((p_message == NULL) || (p_pdu == NULL))
    {
        /* Error. */
        return WHAD_ERROR;
    }

    /* Set message properties. */
    p_message->which_msg = Message_ant_tag;
    p_message->msg.ant.which_msg = ant_Message_raw_pdu_tag;
    p_message->msg.ant.msg.raw_pdu.channel_number = p_pdu->channel_number;
    p_message->msg.ant.msg.raw_pdu.rf_channel = p_pdu->rf_channel;

    p_message->msg.ant.msg.raw_pdu.pdu.size = p_pdu->packet.length;
    memcpy(p_message->msg.ant.msg.raw_pdu.pdu.bytes, p_pdu->packet.bytes, p_pdu->packet.length);

    /* Set message optional properties. */
    if (p_pdu->has_rssi)
    {
        p_message->msg.ant.msg.raw_pdu.has_rssi = true;
        p_message->msg.ant.msg.raw_pdu.rssi = p_pdu->rssi;
    }
    else
    {
        p_message->msg.ant.msg.raw_pdu.has_rssi = false;
    }

    if (p_pdu->has_timestamp)
    {
        p_message->msg.ant.msg.raw_pdu.has_timestamp = true;
        p_message->msg.ant.msg.raw_pdu.timestamp = p_pdu->timestamp;
    }
    else
    {
        p_message->msg.ant.msg.raw_pdu.has_timestamp = false;
    }

    if (p_pdu->has_crc_validity)
    {
        p_message->msg.ant.msg.raw_pdu.has_crc_validity = true;
        p_message->msg.ant.msg.raw_pdu.crc_validity = p_pdu->crc_validity;
    }
    else
    {
        p_message->msg.ant.msg.raw_pdu.has_crc_validity = false;
    }

    /* Success. */
    return WHAD_SUCCESS;
}


/**
 * @brief   Parse a RawPduReceived message
 *
 * @param[in]       p_message   Pointer to a NanoPb Message structure
 * @param[in,out]   p_pdu       Pointer to a `whad_ant_recvd_packet_t` structure
 *
 * @retval      WHAD_SUCCESS        Success.
 * @retval      WHAD_ERROR          Invalid message or packet pointer.
 **/

whad_result_t whad_ant_raw_pdu_received_parse(Message *p_message, whad_ant_recvd_packet_t *p_pdu)
{
    /* Sanity check. */
    if ((p_message == NULL) || (p_pdu == NULL))
    {
        /* Error. */
        return WHAD_ERROR;
    }

    /* Parse message properties. */
    p_pdu->channel_number = p_message->msg.ant.msg.raw_pdu.channel_number;
    p_pdu->rf_channel = p_message->msg.ant.msg.raw_pdu.rf_channel;
    p_pdu->packet.length = p_message->msg.ant.msg.raw_pdu.pdu.size;
    memcpy(p_pdu->packet.bytes, p_message->msg.ant.msg.raw_pdu.pdu.bytes, p_pdu->packet.length);


    /* Parse message optional properties. */
    p_pdu->has_rssi = p_message->msg.ant.msg.raw_pdu.has_rssi;
    if (p_pdu->has_rssi)
    {
        p_pdu->rssi = p_message->msg.ant.msg.raw_pdu.rssi;
    }

    p_pdu->has_timestamp = p_message->msg.ant.msg.raw_pdu.has_timestamp;
    if (p_pdu->has_timestamp)
    {
        p_pdu->timestamp = p_message->msg.ant.msg.raw_pdu.timestamp;
    }

    p_pdu->has_crc_validity = p_message->msg.ant.msg.raw_pdu.has_crc_validity;
    if (p_pdu->has_crc_validity)
    {
        p_pdu->crc_validity = p_message->msg.ant.msg.raw_pdu.crc_validity;
    }


    /* Success. */
    return WHAD_SUCCESS;
}

/**
 * @brief   Create a PduReceived message
 *
 * @param[in,out]   p_message   Pointer to a NanoPb Message structure
 * @param[in]       p_pdu       Pointer to a `whad_ant_recvd_packet_t` structure
 *
 * @retval      WHAD_SUCCESS        Success.
 * @retval      WHAD_ERROR          Invalid message or packet pointer.
 **/

whad_result_t whad_ant_pdu_received(Message *p_message, whad_ant_recvd_packet_t *p_pdu)
{
    /* Sanity check. */
    if ((p_message == NULL) || (p_pdu == NULL))
    {
        /* Error. */
        return WHAD_ERROR;
    }

    /* Set message properties. */
    p_message->which_msg = Message_ant_tag;
    p_message->msg.ant.which_msg = ant_Message_pdu_tag;
    p_message->msg.ant.msg.pdu.channel_number = p_pdu->channel_number;
    p_message->msg.ant.msg.pdu.rf_channel = p_pdu->rf_channel;

    p_message->msg.ant.msg.pdu.pdu.size = p_pdu->packet.length;
    memcpy(p_message->msg.ant.msg.pdu.pdu.bytes, p_pdu->packet.bytes, p_pdu->packet.length);

    /* Set message optional properties. */
    if (p_pdu->has_rssi)
    {
        p_message->msg.ant.msg.pdu.has_rssi = true;
        p_message->msg.ant.msg.pdu.rssi = p_pdu->rssi;
    }
    else
    {
        p_message->msg.ant.msg.pdu.has_rssi = false;
    }

    if (p_pdu->has_timestamp)
    {
        p_message->msg.ant.msg.pdu.has_timestamp = true;
        p_message->msg.ant.msg.pdu.timestamp = p_pdu->timestamp;
    }
    else
    {
        p_message->msg.ant.msg.pdu.has_timestamp = false;
    }

    if (p_pdu->has_crc_validity)
    {
        p_message->msg.ant.msg.pdu.has_crc_validity = true;
        p_message->msg.ant.msg.pdu.crc_validity = p_pdu->crc_validity;
    }
    else
    {
        p_message->msg.ant.msg.pdu.has_crc_validity = false;
    }

    /* Success. */
    return WHAD_SUCCESS;
}


/**
 * @brief   Parse a PduReceived message
 *
 * @param[in]       p_message   Pointer to a NanoPb Message structure
 * @param[in,out]   p_pdu       Pointer to a `whad_ant_recvd_packet_t` structure
 *
 * @retval      WHAD_SUCCESS        Success.
 * @retval      WHAD_ERROR          Invalid message or packet pointer.
 **/

whad_result_t whad_ant_pdu_received_parse(Message *p_message, whad_ant_recvd_packet_t *p_pdu)
{
    /* Sanity check. */
    if ((p_message == NULL) || (p_pdu == NULL))
    {
        /* Error. */
        return WHAD_ERROR;
    }

    /* Parse message properties. */
    p_pdu->channel_number = p_message->msg.ant.msg.pdu.channel_number;
    p_pdu->rf_channel = p_message->msg.ant.msg.pdu.rf_channel;
    p_pdu->packet.length = p_message->msg.ant.msg.pdu.pdu.size;
    memcpy(p_pdu->packet.bytes, p_message->msg.ant.msg.pdu.pdu.bytes, p_pdu->packet.length);


    /* Parse message optional properties. */
    p_pdu->has_rssi = p_message->msg.ant.msg.pdu.has_rssi;
    if (p_pdu->has_rssi)
    {
        p_pdu->rssi = p_message->msg.ant.msg.pdu.rssi;
    }

    p_pdu->has_timestamp = p_message->msg.ant.msg.pdu.has_timestamp;
    if (p_pdu->has_timestamp)
    {
        p_pdu->timestamp = p_message->msg.ant.msg.pdu.timestamp;
    }

    p_pdu->has_crc_validity = p_message->msg.ant.msg.pdu.has_crc_validity;
    if (p_pdu->has_crc_validity)
    {
        p_pdu->crc_validity = p_message->msg.ant.msg.pdu.crc_validity;
    }


    /* Success. */
    return WHAD_SUCCESS;
}
