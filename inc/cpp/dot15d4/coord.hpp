#ifndef __INC_WHAD_DOT15D4_COORD_HPP
#define __INC_WHAD_DOT15D4_COORD_HPP

#include <string>
#include "message.hpp"
#include "common.hpp"
#include <dot15d4/base.hpp>

namespace whad::dot15d4 {

    class CoordMode : public Dot15d4Msg
    {
        public:
            CoordMode(Dot15d4Msg &message);
            CoordMode(uint32_t channel);

            /* Getters. */
            uint32_t getChannel();

        private:
            void pack();
            void unpack();

            uint32_t m_channel;               
    };

}

#endif /* __INC_WHAD_DOT15D4_COORD_HPP */