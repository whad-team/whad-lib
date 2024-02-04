#ifndef __INC_WHAD_HPP
#define __INC_WHAD_HPP

#include "message.hpp"
/* Generic messages. */
#include <generic/cmdresult.hpp>
#include <generic/verbose.hpp>
#include <generic/debug.hpp>

/* Discovery messages. */
#include "discovery.hpp"

/* BLE messages. */
#include "ble.hpp"

/* PHY messages. */
#include "phy.hpp"

namespace whad
{
    void send(NanoPbMsg message);
}

#endif /* __INC_WHAD_HPP */