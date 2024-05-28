#ifndef __INC_WHAD_DOT15D4_JAMMED_HPP
#define __INC_WHAD_DOT15D4_JAMMED_HPP

#include <string>
#include "message.hpp"
#include "common.hpp"
#include <dot15d4/base.hpp>

namespace whad::dot15d4 {

    class Jammed : public Dot15d4Msg
    {
        public:
            Jammed(Dot15d4Msg &message);
            Jammed(uint32_t timestamp);

            /* Getters. */
            uint32_t getTimestamp();

        private:
            void pack();
            void unpack();

            uint32_t m_timestamp;               
    };
}

#endif /* __INC_WHAD_DOT15D4_JAMMED_HPP */