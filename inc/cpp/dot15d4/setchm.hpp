#ifndef __INC_WHAD_DOT15D4_SET_CHM_HPP
#define __INC_WHAD_DOT15D4_SET_CHM_HPP

#include <string>
#include "message.hpp"
#include "common.hpp"
#include <dot15d4/base.hpp>

namespace whad::dot15d4 {

    class SetChannelMap : public Dot15d4Msg
    {
        public:
            SetChannelMap(Dot15d4Msg &message);
            SetChannelMap(uint32_t channel_map);

            /* Getters. */
            uint32_t getChannelMap();

        private:
            void pack();
            void unpack();

            uint32_t m_channel_map;
    };
}

#endif /* __INC_WHAD_DOT15D4_SET_CHM_HPP */