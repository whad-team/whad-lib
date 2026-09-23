#include <ant/network.hpp>

using namespace whad::ant;

/**
 * @brief   Constructor, parse a message as a SetNetworkKey message.
 *
 * @param[in]   message     Message to parse
 */

SetNetworkKey::SetNetworkKey(AntMsg &message) : AntMsg(message)
{
    /* Unpack message. */
    this->unpack();
}


/**
 * @brief   Constructor, create a SetNetworkKey
 *
 * @param[in]   network_number     ANT network number to select
 * @param[in]   network_key        ANT network key to set
 */

SetNetworkKey::SetNetworkKey(uint32_t network_number, uint8_t *network_key) : AntMsg()
{
    /* Copy network number. */
    this->m_network_number = network_number;

    /* Copy network key. */
    memcpy(this->m_network_key, network_key, ANT_NETWORK_KEY_SIZE);
}


/**
 * @brief   Retrieve the ANT Network Number
 *
 * @retval  ANT channel number
 */

uint32_t SetNetworkKey::getNetworkNumber(void)
{
    return this->m_network_number;
}


/**
 * @brief   Retrieve the ANT Network Key
 *
 * @retval  ANT channel period
 */

uint8_t* SetNetworkKey::getNetworkKey(void)
{
    return this->m_network_key;
}


/**
 * @brief   Pack parameters into an AntMsg.
 **/

void SetNetworkKey::pack()
{
    /* Craft message. */
    whad_ant_set_network_key(this->getMessage(), this->m_network_number, this->m_network_key);
}


/**
 * @brief   Extract parameters from AntMsg.
 */

void SetNetworkKey::unpack()
{
    uint32_t network_number;
    uint8_t network_key[ANT_NETWORK_KEY_SIZE];

    /* Parse message. */
    if (whad_ant_set_network_key_parse(this->getMessage(), &network_number, network_key) == WHAD_SUCCESS)
    {
        this->m_network_number = network_number;
        memcpy(this->m_network_key, network_key, ANT_NETWORK_KEY_SIZE);
    }
    else
    {
        /* Error. */
        throw WhadMessageParsingError();
    }
}


/**
 * @brief   Constructor, create a ListNetworks message.
 */

ListNetworks::ListNetworks() : AntMsg()
{
}


/**
 * @brief   Constructor, parse an AntMsg as a ListNetworks message.
 * 
 * @param[in]   message     Message to parse
 */

ListNetworks::ListNetworks(AntMsg &message) : AntMsg(message)
{
}


/**
 * @brief   Pack parameters into an AntMsg.
 */

void ListNetworks::pack()
{
    whad_ant_list_networks(this->getMessage());
}


/**
 * @brief   Constructor, parses an AntMsg as a AvailableNetworks message.
 *
 * @param[in]   message Message to parse
 */

AvailableNetworks::AvailableNetworks(AntMsg &message) : AntMsg(message)
{
    this->unpack();
}


/**
 * @brief   Constructor, create a new AvailableNetworks message
 * 
 * @param[in]   number_of_networks   Number of available networks.
 * 
 */

AvailableNetworks::AvailableNetworks(uint32_t number_of_networks) : AntMsg()
{
    this->m_number_of_networks = number_of_networks;
}


/**
 * @brief   Retrieve the number of available networks.
 * 
 * @retval  Number of available networks
*/
uint32_t AvailableNetworks::getNumberOfNetworks()
{
    return this->m_number_of_networks;
}


/**
 * Pack parameters into an AntMsg.
 */

void AvailableNetworks::pack()
{
    whad_ant_available_networks(
        this->getMessage(),
        this->m_number_of_networks
    );
}


/**
 * Extract parameters from an AntMsg.
 */

void AvailableNetworks::unpack()
{
    if (whad_ant_available_networks_parse(this->getMessage(), &m_number_of_networks) == WHAD_ERROR)
    {
        throw WhadMessageParsingError();
    }
}
