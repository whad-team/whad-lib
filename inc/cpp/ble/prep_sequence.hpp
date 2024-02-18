#ifndef __INC_WHAD_BLE_PREP_SEQUENCE_HPP
#define __INC_WHAD_BLE_PREP_SEQUENCE_HPP

#include <string>
#include "message.hpp"
#include "common.hpp"
#include <ble/base.hpp>

namespace whad::ble {

    enum SequenceType {
        SequencePattern = 0,
        SequenceManual,
        SequenceConnEvt,
    };

    /**
     * PrepareSequence base class.
     * 
     * This class provides the basic features to store a sequence ID, direction
     * and a list of PDUs.
     **/

    class PrepareSequence
    {
        public:
            PrepareSequence();
            PrepareSequence(uint32_t id, Direction direction, std::vector<PDU> packets);

            uint32_t getId();
            Direction getDirection();
            std::vector<PDU>& getPackets();

            static SequenceType getType(BleMsg &message);

        protected:
            uint32_t m_id;
            Direction m_direction;
            std::vector<PDU> m_packets;
    };

    /**
     * PrepareSequence with manual trigger
     **/

    class PrepareSequenceManual : public BleMsg, public PrepareSequence
    {
        public:
            PrepareSequenceManual(BleMsg &message);
            PrepareSequenceManual(uint32_t id, Direction direction, std::vector<PDU> packets);

        private:
            void pack();
            void unpack();
    };

    /**
     * PrepareSequence with a connection event based trigger.
     **/

    class PrepareSequenceConnEvt : public BleMsg, public PrepareSequence
    {
        public:
            PrepareSequenceConnEvt(BleMsg &message);
            PrepareSequenceConnEvt(uint32_t id, Direction direction, std::vector<PDU> packets, uint32_t connEvt);

            uint32_t getConnEvt();

        private:
            void pack();
            void unpack();

            uint32_t m_connEvt;
    };

    /* TODO: implement a mask-based trigger. */

    /* TODO: provide a way to determine which type of message is used. */
}

#endif /* __INC_WHAD_BLE_PREP_SEQUENCE_HPP */