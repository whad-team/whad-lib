#include <ble/sniff_act_conn.hpp>

using namespace whad::ble;

/**
 * @brief       SniffActiveConn message constructor.
 * 
 * @param[in]   accessAddress   Connection access address
 * @param[in]   crcInit         Connection CRC init value (seed)
 * @param[in]   hopInterval     Hop interval
 * @param[in]   hopIncrement    Hop increment
 * @param[in]   channelMap      Connection channel map
 * @param[in]   channels        Channel map specifying the channels to use when recovering the
 *                              channel map (if multiple sniffers are used -- collaborative
 *                              channel map recovery).
 **/

SniffActiveConn::SniffActiveConn(uint32_t accessAddress, uint32_t crcInit, uint32_t hopInterval, uint32_t hopIncrement, ChannelMap channelMap, ChannelMap channels) : BleMsg()
{
    whad_ble_sniff_active_conn(
        this->getRaw(),
        accessAddress,
        crcInit,
        hopInterval,
        hopIncrement,
        channelMap.getChannelMapBuf(),
        channels.getChannelMapBuf()
    );
}