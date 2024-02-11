#include <ble/sniff_aa.hpp>

using namespace whad::ble;

/**
 * @brief   Parse a BleMsg as a SniffAccessAddress message.
 * 
 * @param[in]   message     Message to parse
 */

SniffAccessAddress::SniffAccessAddress(BleMsg &message) : BleMsg(message)
{
    this->unpack();
}


/**
 * @brief       SnifAccessAddress message constructor.
 * 
 * @param[in]   channelMap  Channel map specifying the channels to use for access adress
 *                          sniffing
 **/

SniffAccessAddress::SniffAccessAddress(ChannelMap channelMap) : BleMsg()
{
    m_channelMap = channelMap;
}


/**
 * @brief   Get channel map
 * 
 * @retval  Channel map reference
 */
ChannelMap& SniffAccessAddress::getChannelMap()
{
    return m_channelMap;
}


/**
 * @brief   Pack paremeters into a BleMsg.
 */

void SniffAccessAddress::pack()
{
    whad_ble_sniff_access_address(
        this->getMessage(),
        m_channelMap.getChannelMapBuf()
    );
}


/**
 * @brief   Parse a BleMsg as an AccessAddressDiscovered message
 * 
 * @param[in]   message     Message to parse
 */

AccessAddressDiscovered::AccessAddressDiscovered(BleMsg &message) : BleMsg(message)
{
    this->unpack();
}


/**
 * @brief       Notify the discovery of an access address
 * 
 * @param[in]   accessAddress       Discovered access address
 **/

AccessAddressDiscovered::AccessAddressDiscovered(uint32_t accessAddress) : BleMsg()
{
    m_accessAddr = accessAddress;
    m_hasRssi = false;
    m_rssi = 0;
    m_hasTimestamp = false;
    m_timestamp = 0;
}


/**
 * @brief       Notify the discovery of an access address including RSSI
 * 
 * @param[in]   accessAddress       Discovered access address
 * @param[in]   rssi                Received Signal Strength Indicator
 **/

AccessAddressDiscovered::AccessAddressDiscovered(uint32_t accessAddress, int32_t rssi) : BleMsg()
{
    m_accessAddr = accessAddress;
    m_hasRssi = true;
    m_rssi = rssi;
    m_hasTimestamp = false;
    m_timestamp = 0;
}


/**
 * @brief       Notify the discovery of an access address including timestamp
 * 
 * @param[in]   accessAddress       Discovered access address
 * @param[in]   timestamp           Timestamp
 **/

AccessAddressDiscovered::AccessAddressDiscovered(uint32_t accessAddress, uint32_t timestamp) : BleMsg()
{
    m_accessAddr = accessAddress;
    m_hasRssi = false;
    m_rssi = 0;
    m_hasTimestamp = true;
    m_timestamp = timestamp;
}


/**
 * @brief       Notify the discovery of an access address including timestamp and RSSI
 * 
 * @param[in]   accessAddress       Discovered access address
 * @param[in]   timestamp           Timestamp
 * @param[in]   rssi                Received Signal Strength Indicator
 **/

AccessAddressDiscovered::AccessAddressDiscovered(uint32_t accessAddress, uint32_t timestamp, int32_t rssi) : BleMsg()
{
    m_accessAddr = accessAddress;
    m_hasRssi = true;
    m_rssi = rssi;
    m_hasTimestamp = true;
    m_timestamp = timestamp;
}


/**
 * @brief   Pack parameters into a BleMsg
 */

void AccessAddressDiscovered::pack()
{
    whad_ble_access_address_discovered(
        this->getMessage(),
        m_accessAddr,
        m_timestamp,
        m_rssi,
        m_hasTimestamp,
        m_hasRssi
    );
}


/**
 * @brief   Extract parameters from a BleMsg
 */

void AccessAddressDiscovered::unpack()
{
    whad_result_t result;
    whad_ble_aa_disc_params_t params;

    result = whad_ble_access_address_discovered_parse(
        this->getMessage(),
        &params
    );

    if (result == WHAD_ERROR)
    {
        throw WhadMessageParsingError();
    }
    else
    {
        /* Extract parameters. */
        m_accessAddr = params.access_address;
        m_hasRssi = params.inc_rssi;
        m_rssi = params.rssi;
        m_hasTimestamp = params.inc_ts;
        m_timestamp = params.timestamp;
    }
}


/**
 * @brief   Get the access address
 * 
 * @retval  Access Address
 */

uint32_t AccessAddressDiscovered::getAccessAddress()
{
    return m_accessAddr;
}


/**
 * @brief   Determine if an RSSI is available
 * 
 * @retval  true    The RSSI is available
 * @retval  false   The RSSI is not available (default to 0)
 */

bool AccessAddressDiscovered::hasRssi()
{
    return m_hasRssi;
}


/**
 * @brief   Determine if a timestamp is available
 * 
 * @retval  true    The timestamp is available
 * @retval  false   The timestamp is not available (default to 0)
 */

bool AccessAddressDiscovered::hasTimestamp()
{
    return m_hasTimestamp;
}


/**
 * @brief   Get the RSSI value
 * 
 * @retval  RSSI value
 */

int32_t AccessAddressDiscovered::getRssi()
{
    return m_rssi;
}


/**
 * @brief   Get the Timestamp value
 * 
 * @retval  Timestamp in milliseconds
 */

uint32_t AccessAddressDiscovered::getTimestamp()
{
    return m_timestamp;
}