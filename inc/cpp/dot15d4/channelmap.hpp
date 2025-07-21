#ifndef __INC_WHAD_DOT15D4_CHANNEL_MAP_HPP
#define __INC_WHAD_DOT15D4_CHANNEL_MAP_HPP

#include <string>
#include <bitset>
#include "message.hpp"
#include "common.hpp"
#include <dot15d4/base.hpp>

namespace whad::dot15d4 {

    class ChannelMap : public Dot15d4Msg
    {
        public:
            ChannelMap(Dot15d4Msg &message);
            ChannelMap(uint16_t channel_map);

            void countActiveChannels();

            uint16_t m_channel_map;
            /* Getters. */
            uint16_t getChannelMap();
            int getActiveChannel(int index);
            int getNumberOfActiveChannels();

            /* Setters. */
            void setChannelMap(uint16_t channel_map);

        private:                    
            void unpack();
            void pack();
            std::bitset<16> binary_bits ;    
            int m_nb_active_channels;          
    };

}

#endif /* __INC_WHAD_DOT15D4_CHANNEL_MAP_HPP */