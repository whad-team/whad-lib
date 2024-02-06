#include <ble/connect.hpp>

using namespace whad::ble;

/**
 * @brief       ConnectTo message constructor.
 * 
 * @param[in]   targetAddr      Target device BD address
 * @param[in]   accessAddress   Specify the access address to use for this connection, if supported
 *                              by the adapter
 * @param[in]   channelMap      Specify the channel map to use for this connection, if supported by
 *                              the adapter
 * @param[in]   hopInterval     Connection hop interval
 * @param[in]   hopIncrement    Connection hop increment
 * @param[in]   crcInit         CRC initial value (seed)
 **/

ConnectTo::ConnectTo(BDAddress targetAddr, uint32_t accessAddress, ChannelMap channelMap,
                              uint32_t hopInterval, uint32_t hopIncrement, uint32_t crcInit) : BleMsg()
{
    whad_ble_connect_to(
        this->getMessage(),
        targetAddr.getAddressBuf(),
        (whad_ble_addrtype_t)targetAddr.getType(),
        accessAddress,
        channelMap.getChannelMapBuf(),
        hopInterval,
        hopIncrement,
        crcInit
    );
}
