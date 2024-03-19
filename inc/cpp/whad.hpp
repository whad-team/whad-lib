#ifndef __INC_WHAD_HPP
#define __INC_WHAD_HPP

#include "message.hpp"

/* Generic messages. */
#include <generic/cmdresult.hpp>
#include <generic/verbose.hpp>
#include <generic/debug.hpp>

/* Discovery messages. */
#include <discovery/discovery.hpp>

/* ESB */
#include <esb/esb.hpp>

/* PHY messages. */
#include <phy/phy.hpp>

/* BLE messages. */
#include <ble/ble.hpp>

/* ZigBee messages. */
#include <zigbee/zigbee.hpp>

/* Unifying messages. */
#include <unifying/unifying.hpp>


namespace whad
{
    void send(NanoPbMsg message);
}

#endif /* __INC_WHAD_HPP */