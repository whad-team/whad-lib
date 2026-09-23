#ifndef __INC_WHAD_ANT_JAMMED_HPP
#define __INC_WHAD_ANT_JAMMED_HPP

#include <string>
#include "message.hpp"
#include "common.hpp"
#include <ant/base.hpp>

namespace whad::ant {
    class Jammed : public AntMsg
    {
        public:
            Jammed(AntMsg &message);
            Jammed(uint32_t timestamp);

            uint32_t getTimestamp();

        private:
            void pack();
            void unpack();

            uint32_t m_timestamp;
    };
}

#endif /* __INC_WHAD_ANT_JAMMED_HPP */
