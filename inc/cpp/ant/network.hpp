#ifndef __INC_WHAD_ANT_NETWORK_HPP
#define __INC_WHAD_ANT_NETWORK_HPP

#include <string>
#include "message.hpp"
#include "common.hpp"
#include "ant/base.hpp"

namespace whad::ant {

    class SetNetworkKey : public AntMsg
    {
        public:

            /* Constructors. */
            SetNetworkKey(AntMsg &message);
            SetNetworkKey(uint32_t network_number, uint8_t *network_key);

            uint32_t getNetworkNumber();
            uint8_t* getNetworkKey();

        private:
            uint32_t m_network_number;
            uint8_t m_network_key[ANT_NETWORK_KEY_SIZE];

            void pack();
            void unpack();
    };

    class ListNetworks : public AntMsg
    {
        public:
            ListNetworks(AntMsg &message);
            ListNetworks();

        private:
            void pack();
    };


    class AvailableNetworks : public AntMsg
    {
        public:
            AvailableNetworks(AntMsg &message);
            AvailableNetworks(uint32_t number_of_networks);

            uint32_t getNumberOfNetworks();

        private:
            void pack();
            void unpack();

            uint32_t m_number_of_networks;
    };
}
#endif /* __INC_WHAD_ANT_NETWORK_HPP */