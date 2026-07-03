#ifndef __INC_WHAD_BLE_PHY_HPP
#define __INC_WHAD_BLE_PHY_HPP

#include <string>
#include "message.hpp"
#include "common.hpp"
#include <ble/base.hpp>

namespace whad::ble {

    class SetPhy : public BleMsg
    {
        public:
            SetPhy(BleMsg &message);
            SetPhy(Phy tx, Phy rx);

            /* Getters. */
            Phy getTx();
            Phy getRx();

        private:
            void pack();
            void unpack();

            Phy m_tx;
            Phy m_rx;

    };


    class SetSupportedPhys : public BleMsg
    {
        public:
            SetSupportedPhys(BleMsg &message);
            SetSupportedPhys();

            /* Setters. */
            bool addTxPhy(Phy phy);
            bool addRxPhy(Phy phy);

            /* Getters. */
            size_t countTxPhy();
            size_t countRxPhy();
            Phy getTxPhy(unsigned int index);
            Phy getRxPhy(unsigned int index);

        private:
            void pack();
            void unpack();

            size_t m_tx_count;
            Phy m_tx[4];
            size_t m_rx_count;
            Phy m_rx[4];
    };
}

#endif /* __INC_WHAD_BLE_PHY_HPP */
