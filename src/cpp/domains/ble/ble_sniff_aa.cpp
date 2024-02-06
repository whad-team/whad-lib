#include <ble/sniff_aa.hpp>

using namespace whad::ble;

/**
 * @brief       SnifAccessAddress message constructor.
 * 
 * @param[in]   channelMap  Channel map specifying the channels to use for access adress
 *                          sniffing
 **/

SniffAccessAddress::SniffAccessAddress(ChannelMap channelMap) : BleMsg()
{
    whad_ble_sniff_access_address(this->getRaw(), channelMap.getChannelMapBuf());
}


/**
 * @brief       Notify the discovery of an access address
 * 
 * @param[in]   accessAddress       Discovered access address
 **/

AccessAddressDiscovered::AccessAddressDiscovered(uint32_t accessAddress) : BleMsg()
{
    whad_ble_access_address_discovered(
        this->getRaw(),
        accessAddress,
        0,
        0,
        false,
        false
    );
}


/**
 * @brief       Notify the discovery of an access address including RSSI
 * 
 * @param[in]   accessAddress       Discovered access address
 * @param[in]   rssi                Received Signal Strength Indicator
 **/

AccessAddressDiscovered::AccessAddressDiscovered(uint32_t accessAddress, int32_t rssi) : BleMsg()
{
    whad_ble_access_address_discovered(
        this->getRaw(),
        accessAddress,
        0,
        rssi,
        false,
        true
    );
}


/**
 * @brief       Notify the discovery of an access address including timestamp
 * 
 * @param[in]   accessAddress       Discovered access address
 * @param[in]   timestamp           Timestamp
 **/

AccessAddressDiscovered::AccessAddressDiscovered(uint32_t accessAddress, uint32_t timestamp) : BleMsg()
{
    whad_ble_access_address_discovered(
        this->getRaw(),
        accessAddress,
        timestamp,
        0,
        true,
        false
    );
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
    whad_ble_access_address_discovered(
        this->getRaw(),
        accessAddress,
        timestamp,
        rssi,
        true,
        true
    );
}