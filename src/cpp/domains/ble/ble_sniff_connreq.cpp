#include <ble/sniff_connreq.hpp>

using namespace whad::ble;

/**
 * @brief       SnifConnReq message constructor.
 * 
 * @param[in]   channel     Channel to sniff for connection request
 * @param[in]   targetAddr  Target device BD address
 * @param[in]   showAdv     If set to true, adapter will report every advertisement received
 * @param[in]   showEmpty   If set to true, adapter will report empty PDUs
 **/

SniffConnReq::SniffConnReq(uint32_t channel, BDAddress targetAddr, bool showAdv, bool showEmpty) : BleMsg()
{
    whad_ble_sniff_conn_req(
        this->getRaw(),
        showEmpty,
        showAdv,
        channel,
        targetAddr.getAddressBuf()
    );
}
