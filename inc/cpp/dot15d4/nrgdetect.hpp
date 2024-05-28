#ifndef __INC_WHAD_DOT15D4_ENERGYDETECT_HPP
#define __INC_WHAD_DOT15D4_ENERGYDETECT_HPP

#include <string>
#include "message.hpp"
#include "common.hpp"
#include <dot15d4/base.hpp>

namespace whad::dot15d4 {

    class EnergyDetect : public Dot15d4Msg
    {
        public:
            EnergyDetect(Dot15d4Msg &message);
            EnergyDetect(uint32_t channel);

            /* Getters. */
            uint32_t getChannel();

        private:
            void pack();
            void unpack();

            uint32_t m_channel;               
    };

}

#endif /* __INC_WHAD_DOT15D4_ENERGYDETECT_HPP */