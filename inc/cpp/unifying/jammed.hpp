#ifndef __INC_WHAD_UNIFYING_JAMMED_HPP
#define __INC_WHAD_UNIFYING_JAMMED_HPP

#include <string>
#include "message.hpp"
#include "common.hpp"
#include <unifying/base.hpp>

namespace whad::unifying {

    class Jammed : public UnifyingMsg
    {
        public:
            Jammed(UnifyingMsg &message);
            Jammed(uint32_t timestamp);

            /* Getters. */
            uint32_t getTimestamp();

        private:
            void pack();
            void unpack();

            uint32_t m_timestamp;
    };

}

#endif /* __INC_WHAD_UNIFYING_JAMMED_HPP */