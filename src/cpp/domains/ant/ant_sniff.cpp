#include <ant/sniff.hpp>

using namespace whad::ant;

/**
 * @brief   Constructor, parse a message as a Sniff message.
 *
 * @param[in]   message     Message to parse
 */

Sniff::Sniff(AntMsg &message) : AntMsg(message)
{
    /* Unpack message. */
    this->unpack();
}


/**
 * @brief   Constructor, create a Sniff
 *
 * @param[in]   rf_channel         ANT RF channel to set
 * @param[in]   network_key        ANT network key to set
 * @param[in]   device_number      ANT device number to select
 * @param[in]   device_type        ANT device type to select
 * @param[in]   transmission_type  ANT transmission type to select
 */

Sniff::Sniff(uint32_t rf_channel, uint8_t *network_key, uint32_t device_number, uint32_t device_type, uint32_t transmission_type) : AntMsg()
{
    /* Copy RF channel. */
    this->m_rf_channel = rf_channel;

    /* Copy network key. */
    memcpy(this->m_network_key, network_key, ANT_NETWORK_KEY_SIZE);

    /* Copy device number. */
    this->m_device_number = device_number;
    /* Copy device type. */
    this->m_device_type = device_type;
    /* Copy transmission type. */
    this->m_transmission_type = transmission_type;

}


/**
 * @brief   Retrieve the ANT RF channel
 *
 * @retval  ANT RF channel
 */

uint32_t Sniff::getRFChannel(void)
{
    return this->m_rf_channel;
}


/**
 * @brief   Retrieve the ANT Network Key
 *
 * @retval  ANT network key
 */

uint8_t* Sniff::getNetworkKey(void)
{
    return this->m_network_key;
}

/**
 * @brief   Retrieve the ANT device number
 *
 * @retval  ANT device number
 */

uint32_t Sniff::getDeviceNumber(void)
{
    return this->m_device_number;
}


/**
 * @brief   Retrieve the ANT device type
 *
 * @retval  ANT device type
 */

uint32_t Sniff::getDeviceType(void)
{
    return this->m_device_type;
}

/**
 * @brief   Retrieve the ANT transmission type
 *
 * @retval  ANT transmission type
 */

uint32_t Sniff::getTransmissionType(void)
{
    return this->m_transmission_type;
}


/**
 * @brief   Pack parameters into an AntMsg.
 **/

void Sniff::pack()
{
    /* Craft message. */
    whad_ant_sniff(
        this->getMessage(), 
        this->m_rf_channel,
        this->m_network_key,
        this->m_device_number,
        this->m_device_type, 
        this->m_transmission_type
    );
}


/**
 * @brief   Extract parameters from AntMsg.
 */

void Sniff::unpack()
{
    whad_ant_sniff_params_t parameters;

    /* Parse message. */
    if (whad_ant_sniff_parse(this->getMessage(), &parameters) == WHAD_SUCCESS)
    {
        this->m_rf_channel = parameters.rf_channel;
        memcpy(this->m_network_key, parameters.network_key, ANT_NETWORK_KEY_SIZE);
        this->m_device_number = parameters.device_number;
        this->m_device_type = parameters.device_type;
        this->m_transmission_type = parameters.transmission_type;
    }
    else
    {
        /* Error. */
        throw WhadMessageParsingError();
    }
}