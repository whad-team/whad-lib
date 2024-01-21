#ifndef __INC_WHAD_HPP
#define __INC_WHAD_HPP

#include "message.hpp"
#include "generic.hpp"
#include "discovery.hpp"
#include "ble.hpp"
#include "phy.hpp"

namespace whad
{
    void send(NanoPbMsg message);
}

#endif /* __INC_WHAD_HPP */