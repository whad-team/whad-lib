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
            DeleteSequence(uint32_t id);
    };

}

#endif /* __INC_WHAD_DEL_SEQUENCE_HPP */