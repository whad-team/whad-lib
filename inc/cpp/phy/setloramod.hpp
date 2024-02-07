#ifndef __INC_WHAD_PHY_SETLORAMOD_HPP
#define __INC_WHAD_PHY_SETLORAMOD_HPP

#include <string>
#include <vector>
#include "message.hpp"
#include "common.hpp"
#include "../domains/phy.h"
#include <phy/base.hpp>

namespace whad::phy {

    enum LoRaSpreadingFactor {
        LoraSfError = -1,
        LoraSf7 = PHY_LORA_SF7,
        LoraSf8 = PHY_LORA_SF8,
        LoraSf9 = PHY_LORA_SF9,
        LoraSf10 = PHY_LORA_SF10,
        LoraSf11 = PHY_LORA_SF11,
        LoraSf12 = PHY_LORA_SF12
    };

    enum LoRaCodingRate {
        LoraCrError = -1,
        LoraCr45 = PHY_LORA_CR45,
        LoraCr46 = PHY_LORA_CR46,
        LoraCr47 = PHY_LORA_CR47,
        LoraCr48 = PHY_LORA_CR48
    };

    class SetLoraMod : public PhyMsg
    {
        public:
            SetLoraMod(PhyMsg &message);
            SetLoraMod(uint32_t bandwidth, LoRaSpreadingFactor sf,
                        LoRaCodingRate cr, uint32_t preambleLength,
                        bool enableCrc, bool explicitMode, bool invertIq);

            uint32_t getBandwidth();
            uint32_t getPreambleLength();
            LoRaSpreadingFactor getSpreadingFactor();
            LoRaCodingRate getCodingRate();
            bool isCrcEnabled();
            bool isExplicitMode();
            bool isIqInverted();

        private:
            void pack();
            void unpack();

            uint32_t m_bandwidth;
            LoRaSpreadingFactor m_sf;
            LoRaCodingRate m_cr;
            uint32_t m_preambleLength;
            bool m_enableCrc;
            bool m_explicitMode;
            bool m_invertIq;
    };

}

#endif /* __INC_WHAD_PHY_SETLORAMOD_HPP */