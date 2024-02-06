#include <ble/adv.hpp>

using namespace whad::ble;

/**
 * @brief       AdvMode message constructor.
 * 
 * @param[in]   pAdvData        Pointer to a byte buffer containing the device advertising data
 * @param[in]   advDataLength   Size in bytes of the advertising data
 * @param[in]   pScanRsp        Pointer to a byte buffer containing the device scan response data
 * @param[in]   scanRspLength   Size in bytes of the scan response data
 **/

AdvMode::AdvMode(uint8_t *pAdvData, int advDataLength, uint8_t *pScanRsp, int scanRspLength) : BleMsg()
{
    whad_ble_adv_mode(
        this->getRaw(),
        pAdvData,
        advDataLength,
        pScanRsp,
        scanRspLength
    );
}