#ifndef __INC_WHAD_BLE_ADV_EXT_HPP
#define __INC_WHAD_BLE_ADV_EXT_HPP

#include "../domains/ble.h"
#include "ble/base.hpp"

namespace whad::ble {

    /* AuxPtr class */
    class AuxPtr
    {
        public:

            AuxPtr();
            AuxPtr(uint8_t channel, uint8_t ca, uint8_t offset_units, uint16_t offset, Phy phy);

            uint8_t getChannel();
            uint8_t getCA();
            uint8_t getOffsetUnits();
            uint16_t getOffset();
            Phy getPhy();

        private:
            uint8_t m_channel;
            uint8_t m_ca;
            uint8_t m_offsetUnits;
            uint16_t m_offset;
            uint8_t m_phy;
    };

    /* Extended Advertising PDU */
    class ExtAdvPdu
    {
        public:

            ExtAdvPdu();
            ExtAdvPdu(uint8_t *p_advData, size_t length);
            ExtAdvPdu(uint8_t *p_advData, size_t length, AuxPtr *auxptr);

            size_t getLength();
            AuxPtr* getAuxPtr();
            uint8_t *getData();

        private:
            size_t m_advLen;
            uint8_t m_advData[254+64];
            AuxPtr *m_pAuxPtr;
    };
}

#endif /* __INC_WHAD_BLE_ADV_EXT_HPP */
