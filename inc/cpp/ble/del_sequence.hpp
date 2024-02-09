#ifndef __INC_WHAD_DEL_SEQUENCE_HPP
#define __INC_WHAD_DEL_SEQUENCE_HPP

#include <string>
#include "message.hpp"
#include "common.hpp"
#include <ble/base.hpp>

namespace whad::ble {

    class DeleteSequence : public BleMsg
    {
        public:
            DeleteSequence(BleMsg &message);
            DeleteSequence(uint32_t id);

            uint32_t getId();

        private:
            void pack();

            uint32_t m_seqId;

    };

}

#endif /* __INC_WHAD_DEL_SEQUENCE_HPP */