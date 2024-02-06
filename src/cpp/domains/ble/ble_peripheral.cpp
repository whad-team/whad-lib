#include <ble/peripheral.hpp>

using namespace whad::ble;

PeripheralMode::PeripheralMode(uint8_t *pAdvData, int advDataLength, uint8_t *pScanRsp, int scanRspLength) : BleMsg()
{
    whad_ble_peripheral_mode(this->getMessage(), pAdvData, advDataLength, pScanRsp, scanRspLength);
}