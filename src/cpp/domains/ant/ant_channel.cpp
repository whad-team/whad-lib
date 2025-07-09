#include <ant/channel.hpp>

using namespace whad::ant;

/**
 * @brief   Constructor, parse a message as a SetDeviceNumber message.
 *
 * @param[in]   message     Message to parse
 */

SetDeviceNumber::SetDeviceNumber(AntMsg &message) : AntMsg(message)
{
    /* Unpack message. */
    this->unpack();
}


/**
 * @brief   Constructor, create a SetDeviceNumber
 *
 * @param[in]   channel_number     ANT channel number to select
 * @param[in]   device_number     ANT device number to set
 */

SetDeviceNumber::SetDeviceNumber(uint32_t channel_number, uint32_t device_number) : AntMsg()
{
    /* Copy channel number. */
    this->m_channel_number = channel_number;

    /* Copy device number. */
    this->m_device_number = device_number;
}


/**
 * @brief   Retrieve the ANT Channel Number
 *
 * @retval  ANT channel number
 */

uint32_t SetDeviceNumber::getChannelNumber(void)
{
    return this->m_channel_number;
}


/**
 * @brief   Retrieve the ANT Device Number
 *
 * @retval  ANT device number
 */

uint32_t SetDeviceNumber::getDeviceNumber(void)
{
    return this->m_device_number;
}


/**
 * @brief   Pack parameters into an AntMsg.
 **/

void SetDeviceNumber::pack()
{
    /* Craft message. */
    whad_ant_set_device_number(this->getMessage(), this->m_channel_number, this->m_device_number);
}


/**
 * @brief   Extract parameters from AntMsg.
 */

void SetDeviceNumber::unpack()
{
    uint32_t channel_number;
    uint32_t device_number;

    /* Parse message. */
    if (whad_ant_set_device_number_parse(this->getMessage(), &channel_number, &device_number) == WHAD_SUCCESS)
    {
        this->m_channel_number = channel_number;
        this->m_device_number = device_number;
    }
    else
    {
        /* Error. */
        throw WhadMessageParsingError();
    }
}

/* ******************************************************************************************************* */

/**
 * @brief   Constructor, parse a message as a SetDeviceType message.
 *
 * @param[in]   message     Message to parse
 */

SetDeviceType::SetDeviceType(AntMsg &message) : AntMsg(message)
{
    /* Unpack message. */
    this->unpack();
}


/**
 * @brief   Constructor, create a SetDeviceType
 *
 * @param[in]   channel_number     ANT channel number to select
 * @param[in]   device_number     ANT device type to set
 */

SetDeviceType::SetDeviceType(uint32_t channel_number, uint32_t device_type) : AntMsg()
{
    /* Copy channel number. */
    this->m_channel_number = channel_number;

    /* Copy device type. */
    this->m_device_type = device_type;
}


/**
 * @brief   Retrieve the ANT Channel Number
 *
 * @retval  ANT channel number
 */

uint32_t SetDeviceType::getChannelNumber(void)
{
    return this->m_channel_number;
}


/**
 * @brief   Retrieve the ANT Device Type
 *
 * @retval  ANT device type
 */

uint32_t SetDeviceType::getDeviceType(void)
{
    return this->m_device_type;
}


/**
 * @brief   Pack parameters into an AntMsg.
 **/

void SetDeviceType::pack()
{
    /* Craft message. */
    whad_ant_set_device_type(this->getMessage(), this->m_channel_number, this->m_device_type);
}


/**
 * @brief   Extract parameters from AntMsg.
 */

void SetDeviceType::unpack()
{
    uint32_t channel_number;
    uint32_t device_type;

    /* Parse message. */
    if (whad_ant_set_device_type_parse(this->getMessage(), &channel_number, &device_type) == WHAD_SUCCESS)
    {
        this->m_channel_number = channel_number;
        this->m_device_type = device_type;
    }
    else
    {
        /* Error. */
        throw WhadMessageParsingError();
    }
}

/* ******************************************************************************************************* */

/**
 * @brief   Constructor, parse a message as a SetTransmissionType message.
 *
 * @param[in]   message     Message to parse
 */

SetTransmissionType::SetTransmissionType(AntMsg &message) : AntMsg(message)
{
    /* Unpack message. */
    this->unpack();
}


/**
 * @brief   Constructor, create a SetTransmissionType
 *
 * @param[in]   channel_number     ANT channel number to select
 * @param[in]   transmission_type  ANT transmission type to set
 */

SetTransmissionType::SetTransmissionType(uint32_t channel_number, uint32_t transmission_type) : AntMsg()
{
    /* Copy channel number. */
    this->m_channel_number = channel_number;

    /* Copy transmission type. */
    this->m_transmission_type = transmission_type;
}


/**
 * @brief   Retrieve the ANT Channel Number
 *
 * @retval  ANT channel number
 */

uint32_t SetTransmissionType::getChannelNumber(void)
{
    return this->m_channel_number;
}


/**
 * @brief   Retrieve the ANT Transmission Type
 *
 * @retval  ANT transmission type
 */

uint32_t SetTransmissionType::getTransmissionType(void)
{
    return this->m_transmission_type;
}


/**
 * @brief   Pack parameters into an AntMsg.
 **/

void SetTransmissionType::pack()
{
    /* Craft message. */
    whad_ant_set_transmission_type(this->getMessage(), this->m_channel_number, this->m_transmission_type);
}


/**
 * @brief   Extract parameters from AntMsg.
 */

void SetTransmissionType::unpack()
{
    uint32_t channel_number;
    uint32_t transmission_type;

    /* Parse message. */
    if (whad_ant_set_transmission_type_parse(this->getMessage(), &channel_number, &transmission_type) == WHAD_SUCCESS)
    {
        this->m_channel_number = channel_number;
        this->m_transmission_type = transmission_type;
    }
    else
    {
        /* Error. */
        throw WhadMessageParsingError();
    }
}


/* ******************************************************************************************************* */

/**
 * @brief   Constructor, parse a message as a SetChannelPeriod message.
 *
 * @param[in]   message     Message to parse
 */

SetChannelPeriod::SetChannelPeriod(AntMsg &message) : AntMsg(message)
{
    /* Unpack message. */
    this->unpack();
}


/**
 * @brief   Constructor, create a SetChannelPeriod
 *
 * @param[in]   channel_number     ANT channel number to select
 * @param[in]   channel_period     ANT channel period to set
 */

SetChannelPeriod::SetChannelPeriod(uint32_t channel_number, uint32_t channel_period) : AntMsg()
{
    /* Copy channel number. */
    this->m_channel_number = channel_number;

    /* Copy channel period. */
    this->m_channel_period = channel_period;
}


/**
 * @brief   Retrieve the ANT Channel Number
 *
 * @retval  ANT channel number
 */

uint32_t SetChannelPeriod::getChannelNumber(void)
{
    return this->m_channel_number;
}


/**
 * @brief   Retrieve the ANT Channel Period
 *
 * @retval  ANT channel period
 */

uint32_t SetChannelPeriod::getChannelPeriod(void)
{
    return this->m_channel_period;
}


/**
 * @brief   Pack parameters into an AntMsg.
 **/

void SetChannelPeriod::pack()
{
    /* Craft message. */
    whad_ant_set_channel_period(this->getMessage(), this->m_channel_number, this->m_channel_period);
}


/**
 * @brief   Extract parameters from AntMsg.
 */

void SetChannelPeriod::unpack()
{
    uint32_t channel_number;
    uint32_t channel_period;

    /* Parse message. */
    if (whad_ant_set_channel_period_parse(this->getMessage(), &channel_number, &channel_period) == WHAD_SUCCESS)
    {
        this->m_channel_number = channel_number;
        this->m_channel_period = channel_period;
    }
    else
    {
        /* Error. */
        throw WhadMessageParsingError();
    }
}


/* ******************************************************************************************************* */

/**
 * @brief   Constructor, parse a message as a AssignChannel message.
 *
 * @param[in]   message     Message to parse
 */

AssignChannel::AssignChannel(AntMsg &message) : AntMsg(message)
{
    /* Unpack message. */
    this->unpack();
}


/**
 * @brief   Constructor, create a AssignChannel
 *
 * @param[in]   channel_number                  ANT channel number to select
 * @param[in]   network_number                  ANT network number to select
 * @param[in]   channel_type                    ANT channel type to set
 * @param[in]   background_scanning             ANT background scanning flag
 * @param[in]   frequency_agility               ANT frequency agility flag
 * @param[in]   fast_channel_initiation         ANT fast channel initiation flag
 * @param[in]   asynchronous_transmission       ANT asynchronous transmission flag
 */

AssignChannel::AssignChannel(
                               uint32_t channel_number, uint32_t network_number, 
                               ChannelType channel_type, bool background_scanning, 
                               bool frequency_agility, bool fast_channel_initiation, 
                               bool asynchronous_transmission

) : AntMsg()
{
    /* Copy channel number. */
    this->m_channel_number = channel_number;

    /* Copy network number. */
    this->m_network_number = network_number;

    /* Copy channel type. */
    this->m_channel_type = channel_type;
    
    /* Copy background scanning. */
    this->m_background_scanning = background_scanning;

    /* Copy frequency agility. */
    this->m_frequency_agility = frequency_agility;
    
    /* Copy fast channel initiation. */
    this->m_fast_channel_initiation = fast_channel_initiation;

    /* Copy asynchronous transmission. */
    this->m_asynchronous_transmission = asynchronous_transmission;
}


/**
 * @brief   Retrieve the ANT Channel Number
 *
 * @retval  ANT channel number
 */

uint32_t AssignChannel::getChannelNumber(void)
{
    return this->m_channel_number;
}

/**
 * @brief   Retrieve the ANT Network Number
 *
 * @retval  ANT network number
 */

uint32_t AssignChannel::getNetworkNumber(void)
{
    return this->m_network_number;
}


/**
 * @brief   Retrieve the ANT Channel type
 *
 * @retval  ANT channel type
 */

ChannelType AssignChannel::getChannelType(void)
{
    return this->m_channel_type;
}


/**
 * @brief   Retrieve the ANT Background Scanning flag
 *
 * @retval  ANT background scanning
 */

bool AssignChannel::getBackgroundScanning(void)
{
    return this->m_background_scanning;
}

/**
 * @brief   Retrieve the ANT Frequency Agility flag
 *
 * @retval  ANT frequency agility
 */

bool AssignChannel::getFrequencyAgility(void)
{
    return this->m_frequency_agility;
}


/**
 * @brief   Retrieve the ANT Fast Channel Initiation flag
 *
 * @retval  ANT fast channel initiation
 */

bool AssignChannel::getFastChannelInitiation(void)
{
    return this->m_fast_channel_initiation;
}


/**
 * @brief   Retrieve the ANT Asynchronous Transmission flag
 *
 * @retval  ANT asynchronous transmission
 */

bool AssignChannel::getAsynchronousTransmission(void)
{
    return this->m_asynchronous_transmission;
}


/**
 * @brief   Pack parameters into an AntMsg.
 **/

void AssignChannel::pack()
{
    /* Craft message. */
    whad_ant_assign_channel(
        this->getMessage(), this->m_channel_number, this->m_network_number, (whad_ant_channel_type_t)(this->m_channel_type), 
        this->m_background_scanning, this->m_frequency_agility, this->m_fast_channel_initiation, this->m_asynchronous_transmission
    );
}


/**
 * @brief   Extract parameters from AntMsg.
 */

void AssignChannel::unpack()
{
    whad_ant_assign_channel_params_t parameters;

    /* Parse message. */
    if (whad_ant_assign_channel_parse(this->getMessage(), &parameters) == WHAD_SUCCESS)
    {
        this->m_channel_number = parameters.channel_number;
        this->m_network_number = parameters.network_number;
        this->m_channel_type = (ChannelType)(parameters.channel_type);
        this->m_background_scanning = parameters.background_scanning;
        this->m_frequency_agility = parameters.frequency_agility;
        this->m_fast_channel_initiation = parameters.fast_channel_initiation;
        this->m_asynchronous_transmission = parameters.asynchronous_transmission;
    }
    else
    {
        /* Error. */
        throw WhadMessageParsingError();
    }
}

/* ******************************************************************************************************* */

/**
 * @brief   Constructor, parse a message as a UnassignChannel message.
 *
 * @param[in]   message     Message to parse
 */

UnassignChannel::UnassignChannel(AntMsg &message) : AntMsg(message)
{
    /* Unpack message. */
    this->unpack();
}


/**
 * @brief   Constructor, create a UnassignChannel
 *
 * @param[in]   channel_number                  ANT channel number to select
 */

UnassignChannel::UnassignChannel(uint32_t channel_number) : AntMsg()
{
    /* Copy channel number. */
    this->m_channel_number = channel_number;
}


/**
 * @brief   Retrieve the ANT Channel Number
 *
 * @retval  ANT channel number
 */

uint32_t UnassignChannel::getChannelNumber(void)
{
    return this->m_channel_number;
}

/**
 * @brief   Pack parameters into an AntMsg.
 **/

void UnassignChannel::pack()
{
    /* Craft message. */
    whad_ant_unassign_channel(this->getMessage(), this->m_channel_number);
}


/**
 * @brief   Extract parameters from AntMsg.
 */

void UnassignChannel::unpack()
{
    uint32_t channel_number;

    /* Parse message. */
    if (whad_ant_unassign_channel_parse(this->getMessage(), &channel_number) == WHAD_SUCCESS)
    {
        this->m_channel_number = channel_number;
    }
    else
    {
        /* Error. */
        throw WhadMessageParsingError();
    }
}

/* ******************************************************************************************************* */

/**
 * @brief   Constructor, parse a message as a OpenChannel message.
 *
 * @param[in]   message     Message to parse
 */

OpenChannel::OpenChannel(AntMsg &message) : AntMsg(message)
{
    /* Unpack message. */
    this->unpack();
}


/**
 * @brief   Constructor, create a OpenChannel
 *
 * @param[in]   channel_number                  ANT channel number to select
 */

OpenChannel::OpenChannel(uint32_t channel_number) : AntMsg()
{
    /* Copy channel number. */
    this->m_channel_number = channel_number;
}


/**
 * @brief   Retrieve the ANT Channel Number
 *
 * @retval  ANT channel number
 */

uint32_t OpenChannel::getChannelNumber(void)
{
    return this->m_channel_number;
}

/**
 * @brief   Pack parameters into an AntMsg.
 **/

void OpenChannel::pack()
{
    /* Craft message. */
    whad_ant_open_channel(this->getMessage(), this->m_channel_number);
}


/**
 * @brief   Extract parameters from AntMsg.
 */

void OpenChannel::unpack()
{
    uint32_t channel_number;

    /* Parse message. */
    if (whad_ant_open_channel_parse(this->getMessage(), &channel_number) == WHAD_SUCCESS)
    {
        this->m_channel_number = channel_number;
    }
    else
    {
        /* Error. */
        throw WhadMessageParsingError();
    }
}

/* ******************************************************************************************************* */

/**
 * @brief   Constructor, parse a message as a CloseChannel message.
 *
 * @param[in]   message     Message to parse
 */

CloseChannel::CloseChannel(AntMsg &message) : AntMsg(message)
{
    /* Unpack message. */
    this->unpack();
}


/**
 * @brief   Constructor, create a CloseChannel
 *
 * @param[in]   channel_number                  ANT channel number to select
 */

CloseChannel::CloseChannel(uint32_t channel_number) : AntMsg()
{
    /* Copy channel number. */
    this->m_channel_number = channel_number;
}


/**
 * @brief   Retrieve the ANT Channel Number
 *
 * @retval  ANT channel number
 */

uint32_t CloseChannel::getChannelNumber(void)
{
    return this->m_channel_number;
}

/**
 * @brief   Pack parameters into an AntMsg.
 **/

void CloseChannel::pack()
{
    /* Craft message. */
    whad_ant_close_channel(this->getMessage(), this->m_channel_number);
}


/**
 * @brief   Extract parameters from AntMsg.
 */

void CloseChannel::unpack()
{
    uint32_t channel_number;

    /* Parse message. */
    if (whad_ant_close_channel_parse(this->getMessage(), &channel_number) == WHAD_SUCCESS)
    {
        this->m_channel_number = channel_number;
    }
    else
    {
        /* Error. */
        throw WhadMessageParsingError();
    }
}

/* ******************************************************************************************************* */

/**
 * @brief   Constructor, parse a message as a SetRFChannel message.
 *
 * @param[in]   message     Message to parse
 */

SetRFChannel::SetRFChannel(AntMsg &message) : AntMsg(message)
{
    /* Unpack message. */
    this->unpack();
}


/**
 * @brief   Constructor, create a SetRFChannel
 *
 * @param[in]   channel_number                  ANT channel number to select
 * @param[in]   rf_channel                      ANT RF channel to set

 */

SetRFChannel::SetRFChannel(uint32_t channel_number, uint32_t rf_channel) : AntMsg()
{
    /* Copy channel number. */
    this->m_channel_number = channel_number;

    /* Copy RF channel. */
    this->m_rf_channel = rf_channel;
}


/**
 * @brief   Retrieve the ANT Channel Number
 *
 * @retval  ANT channel number
 */

uint32_t SetRFChannel::getChannelNumber(void)
{
    return this->m_channel_number;
}

/**
 * @brief   Retrieve the ANT RF Channel
 *
 * @retval  ANT RF channel
 */

uint32_t SetRFChannel::getRFChannel(void)
{
    return this->m_rf_channel;
}

/**
 * @brief   Pack parameters into an AntMsg.
 **/

void SetRFChannel::pack()
{
    /* Craft message. */
    whad_ant_set_rf_channel(this->getMessage(), this->m_channel_number, this->m_rf_channel);
}


/**
 * @brief   Extract parameters from AntMsg.
 */

void SetRFChannel::unpack()
{
    uint32_t channel_number;
    uint32_t rf_channel;

    /* Parse message. */
    if (whad_ant_set_rf_channel_parse(this->getMessage(), &channel_number, &rf_channel) == WHAD_SUCCESS)
    {
        this->m_channel_number = channel_number;
        this->m_rf_channel = rf_channel;
    }
    else
    {
        /* Error. */
        throw WhadMessageParsingError();
    }
}


/**
 * @brief   Constructor, create a ListChannels message.
 */

ListChannels::ListChannels() : AntMsg()
{
}


/**
 * @brief   Constructor, parse an AntMsg as a ListChannels message.
 * 
 * @param[in]   message     Message to parse
 */

ListChannels::ListChannels(AntMsg &message) : AntMsg(message)
{
}


/**
 * @brief   Pack parameters into an AntMsg.
 */

void ListChannels::pack()
{
    whad_ant_list_channels(this->getMessage());
}

/**************************************** */

/**
 * @brief   Constructor, parses an AntMsg as a AvailableChannels message.
 *
 * @param[in]   message Message to parse
 */

AvailableChannels::AvailableChannels(AntMsg &message) : AntMsg(message)
{
    this->unpack();
}


/**
 * @brief   Constructor, create a new AvailableChannels message
 * 
 * @param[in]   number_of_channels   Number of available channels.
 * 
 */

AvailableChannels::AvailableChannels(uint32_t number_of_channels) : AntMsg()
{
    this->m_number_of_channels = number_of_channels;
}


/**
 * @brief   Retrieve the number of available channels.
 * 
 * @retval  Number of available channels
*/
uint32_t AvailableChannels::getNumberOfChannels()
{
    return this->m_number_of_channels;
}


/**
 * Pack parameters into an AntMsg.
 */

void AvailableChannels::pack()
{
    whad_ant_available_channels(
        this->getMessage(),
        this->m_number_of_channels
    );
}


/**
 * Extract parameters from an AntMsg.
 */

void AvailableChannels::unpack()
{
    if (whad_ant_available_channels_parse(this->getMessage(), &m_number_of_channels) == WHAD_ERROR)
    {
        throw WhadMessageParsingError();
    }
}
