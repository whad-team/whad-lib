#include <ble/connected.hpp>

using namespace whad::ble;

/**
 * @brief       Connection notification constructor. 
 * 
 * @param[in]   connHandle  Connection handle assigned to this connection
 * @param[in]   advAddr     Advertiser BD address
 * @param[in]   initAddr    Initiator BD address
 **/

Connected::Connected(uint32_t connHandle, BDAddress advAddr, BDAddress initAddr)  : BleMsg()
{
    whad_ble_notify_connected(
        this->getRaw(),
        
        /* Specify advertiser BD address */
        (whad_ble_addrtype_t)advAddr.getType(), advAddr.getAddressBuf(),

        /* Specify initiator BD address */
        (whad_ble_addrtype_t)initAddr.getType(), initAddr.getAddressBuf(),

        /* Connection handle */
        connHandle
    );
}