#ifndef __INC_WHAD_BLE_ADDRESS_HPP
#define __INC_WHAD_BLE_ADDRESS_HPP

#include <string>
#include "message.hpp"
#include "common.hpp"
#include <ble/base.hpp>

namespace whad::ble {

    /*! Bluetooth Device address type. */
    enum AddressType {
        AddressRandom = BLE_ADDR_RANDOM,    /*!< Device address is random. */
        AddressPublic = BLE_ADDR_PUBLIC     /*!< Device address is public. */
    };

    class BDAddress
    {
        private:

            /* BD address as a byte buffer. */
            uint8_t m_address[6];
            AddressType m_type;

        public:
            BDAddress(void);
            BDAddress(AddressType type, uint8_t *p_bdaddr);

            /* Getters. */
            AddressType getType(void);
            uint8_t *getAddressBuf(void);

            /* Setters. */
            void setType(AddressType type);
            void setAddress(uint8_t *pBdAddress);
    };

}

#endif /* __INC_WHAD_BLE_CONNECTED_HPP */