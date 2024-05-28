#ifndef __INC_WHAD_DOT15D4_ENERGYSAMPLE_HPP
#define __INC_WHAD_DOT15D4_ENERGYSAMPLE_HPP

#include <string>
#include "message.hpp"
#include "common.hpp"
#include <dot15d4/base.hpp>

namespace whad::dot15d4 {

    class EnergySample : public Dot15d4Msg
    {
        public:
            EnergySample(Dot15d4Msg &message);
            EnergySample(uint32_t timestamp, uint32_t value);

            /* Getters. */
            uint32_t getTimestamp();
            uint32_t getValue();

        private:
            void pack();
            void unpack();

            uint32_t m_timestamp;
            uint32_t m_value;               
    };

}

#endif /* __INC_WHAD_DOT15D4_ENERGYSAMPLE_HPP */