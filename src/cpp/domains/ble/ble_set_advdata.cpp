#include <ble/setadvdata.hpp>

using namespace whad::ble;

/**
 * @brief       SetAdvData message constructor.
 * 
 * @param[in]   pAdvData        Pointer to a byte buffer containing the device advertising data
 * @param[in]   advDataLength   Size in bytes of the advertising data
 * @param[in]   pScanRsp        Pointer to a byte buffer containing the device scan response data
 * @param[in]   scanRspLength   Size in bytes of the scan response data
 **/

SetAdvData::SetAdvData(uint8_t *pAdvData, int advDataLength, uint8_t *pScanRsp, int scanRspLength) : BleMsg()
{
    whad_ble_set_adv_data(
        this->getMessage(),
        pAdvData,
        advDataLength,
        pScanRsp,
        scanRspLength
    );
}