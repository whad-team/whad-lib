#ifndef __INC_WHAD_BLE_PREP_SEQUENCE_HPP
#define __INC_WHAD_BLE_PREP_SEQUENCE_HPP

#include <string>
#include "message.hpp"
#include "common.hpp"
#include <ble/base.hpp>

namespace whad::ble {

    class PrepareSequence : public BleMsg
    {
        private:
            whad_prepared_packet_t *buildPacketsArray(std::vector<PDU> packets);

        public:
            /* Manual trigger */
            PrepareSequence(uint32_t id, Direction direction, std::vector<PDU> packets);

            /* Pattern trigger */
            PrepareSequence(uint32_t id, Direction direction, std::vector<PDU> packets, PatternTrigger trigger);

            /* Connection event trigger */
            PrepareSequence(uint32_t id, Direction direction, std::vector<PDU> packets,
                            ConnEventTrigger trigger);
    };

}

#endif /* __INC_WHAD_BLE_PREP_SEQUENCE_HPP */