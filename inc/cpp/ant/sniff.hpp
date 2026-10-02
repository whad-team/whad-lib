#ifndef __INC_WHAD_ANT_SNIFF_HPP
#define __INC_WHAD_ANT_SNIFF_HPP

#include <string>
#include "message.hpp"
#include "common.hpp"
#include "ant/base.hpp"

namespace whad::ant {

    class Sniff : public AntMsg
    {
        public:

            /* Constructors. */
            Sniff(AntMsg &message);
            Sniff(uint32_t rf_channel, uint8_t *network_key, uint32_t device_number, uint32_t device_type, uint32_t transmission_type);

            uint32_t getRFChannel();
            uint8_t* getNetworkKey();
            uint32_t getDeviceNumber();
            uint32_t getDeviceType();
            uint32_t getTransmissionType();

        private:
            uint32_t m_rf_channel;
            uint8_t m_network_key[ANT_NETWORK_KEY_SIZE];
            uint32_t m_device_number;
            uint32_t m_device_type;
            uint32_t m_transmission_type;


            void pack();
            void unpack();
    };
}
#endif /* __INC_WHAD_ANT_SNIFF_HPP */