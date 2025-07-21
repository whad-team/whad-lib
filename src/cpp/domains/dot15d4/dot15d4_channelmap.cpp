#include "dot15d4/channelmap.hpp"
#include <string>

using namespace whad::dot15d4;

ChannelMap::ChannelMap(Dot15d4Msg &message) : Dot15d4Msg(message)
{
    this->unpack();
    this->countActiveChannels();
}

ChannelMap::ChannelMap(uint16_t channel_map)
{
    m_channel_map = channel_map;
    binary_bits = std::bitset<16>(channel_map);
    this->countActiveChannels();
}

uint16_t ChannelMap::getChannelMap()
{
    return m_channel_map;
}

int ChannelMap::getActiveChannel(int index)
{
    if (index >= 0 && index <= 15)
    {
        for (int i = 0; i < 15; i++)
        {
            if (binary_bits[i])
            {
                if (index == 0)
                    return i;
                else
                    index -= 1;
            }
        }
    }
    return -1;
}

void ChannelMap::setChannelMap(uint16_t channel_map)
{
    m_channel_map = channel_map;
    binary_bits = std::bitset<16>(channel_map);
    this->countActiveChannels();
}

void ChannelMap::unpack()
{
    whad_result_t result;
    uint16_t channel_map;

    result = whad_dot15d4_channel_map(
        this->getMessage(),
        &channel_map);

    if (result == WHAD_ERROR)
    {
        /* Error occured during parsing. */
        throw WhadMessageParsingError();
    }
    else
    {
        /* Save parameters. */
        m_channel_map = channel_map;
        binary_bits = std::bitset<16>(channel_map);
    }
}

void ChannelMap::pack(){

}

void ChannelMap::countActiveChannels(){
    int nb = 0;
    for (int i = 0; i < 15; i++)
        {
            if (binary_bits[i])
            {
                nb++;
            }
        }
    m_nb_active_channels = nb;
}

int ChannelMap::getNumberOfActiveChannels(){
    return m_nb_active_channels;
}