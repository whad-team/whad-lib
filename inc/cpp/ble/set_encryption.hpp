#ifndef __INC_WHAD_BLE_SETENC_HPP
#define __INC_WHAD_BLE_SETENC_HPP

#include <string>
#include "message.hpp"
#include "common.hpp"
#include <ble/base.hpp>

namespace whad::ble {

    class SetEncryption : public BleMsg
    {
        public:
            SetEncryption(BleMsg &message);
            SetEncryption(uint32_t connHandle, uint8_t pLLKey[16],
                            uint8_t llIv[8], uint8_t key[16], uint8_t rand[8],
                            uint8_t eDiv[2], bool enabled);

            /* Getters. */
            uint32_t getConnHandle();
            uint8_t *getLLKey();
            uint8_t *getLLIv();
            uint8_t *getKey();
            uint8_t *getRand();
            uint8_t *getEDiv();
            bool isEnabled();

        private:
            void pack();
            void unpack();
            
            uint32_t m_connHandle;
            uint8_t m_LLKey[16];
            uint8_t m_llIv[8];
            uint8_t m_key[16];
            uint8_t m_rand[8];
            uint8_t m_eDiv[2];
            bool m_enabled;
    };

}

#endif /* __INC_WHAD_BLE_SETENC_HPP */