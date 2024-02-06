#include "ble/channelmap.hpp"

using namespace whad::ble;

ChannelMap::ChannelMap()
{
    /* By default, all 40 channels are active. */
    memset(this->m_map, 0xff, 5);
}

ChannelMap::ChannelMap(uint8_t channelMap[5])
{
    /* Import channel map. */
    memcpy(this->m_map, channelMap, 5);
}

void ChannelMap::enableChannel(int channel)
{
    int n,o;

    if ((channel >= 0) && (channel <= 39))
    {
        n = channel / 8;
        o = channel % 8;
        m_map[n] |= (1 << o);
    }
}

void ChannelMap::disableChannel(int channel)
{
    int n,o;

    if ((channel >= 0) && (channel <= 39))
    {
        n = channel / 8;
        o = channel % 8;
        m_map[n] &= ~(1 << o);
    }
}

bool ChannelMap::isChannelEnabled(int channel)
{
    int n,o;
    
    if ((channel >= 0) && (channel <= 39))
    {
        n = channel / 8;
        o = channel % 8;
        return ((m_map[n] & (1 << o)) != 0);
    }

    /* Bad channel, not enabled. */
    return false;
}

uint8_t *ChannelMap::getChannelMapBuf(void)
{
    return this->m_map;
}