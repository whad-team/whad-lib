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
#include "ble/rawpdu.hpp"
#include "ble/ll_pdu.hpp"
#include "ble/connected.hpp"
#include "ble/disconnected.hpp"
#include "ble/setbdaddr.hpp"
#include "ble/sniff_aa.hpp"
#include "ble/sniff_adv.hpp"
#include "ble/sniff_connreq.hpp"
#include "ble/sniff_act_conn.hpp"
#include "ble/jam_adv.hpp"
#include "ble/jam_act_conn.hpp"
#include "ble/scan.hpp"
#include "ble/adv.hpp"
#include "ble/setadvdata.hpp"
#include "ble/central.hpp"
#include "ble/connect.hpp"
#include "ble/send_raw_pdu.hpp"
#include "ble/send_pdu.hpp"
#include "ble/peripheral.hpp"
#include "ble/start.hpp"
#include "ble/stop.hpp"
#include "ble/hijack_master.hpp"
#include "ble/hijack_slave.hpp"
#include "ble/hijack_both.hpp"
#include "ble/set_encryption.hpp"
#include "ble/jam_reactive.hpp"
#include "ble/prep_sequence.hpp"
#include "ble/manual_trigger.hpp"
#include "ble/del_sequence.hpp"
#include "ble/sequence_trig.hpp"
#include "ble/synchro.hpp"
#include "ble/hijacked.hpp"
#include "ble/injected.hpp"



namespace whad
{
    void send(NanoPbMsg message);
}

#endif /* __INC_WHAD_HPP */