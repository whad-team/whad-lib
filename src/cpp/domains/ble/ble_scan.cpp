#include <ble/scan.hpp>

using namespace whad::ble;

/**
 * @brief       ScanMode message constructor.
 * 
 * @param[in]   active      If set to true, adapter will perform an active scan
 **/

ScanMode::ScanMode(bool active) : BleMsg()
{
    whad_ble_scan_mode(this->getMessage(), active);
}


/**
 * @brief       Notify an advertising PDU
 * 
 * @param[in]   advType             Advertisement type
 * @param[in]   address             Advertiser BD address
 * @param[in]   pAdvData            Pointer to the advertising data byte buffer
 * @param[in]   advDataLength       Advertising data length in bytes
 **/

AdvPdu::AdvPdu(AdvType advType, int32_t rssi, BDAddress address, uint8_t *pAdvData, int advDataLength) : BleMsg()
{
    whad_ble_adv_pdu(
        this->getRaw(),
        (whad_ble_advtype_t)advType,
        rssi,
        address.getAddressBuf(),
        (whad_ble_addrtype_t)address.getType(),
        pAdvData,
        advDataLength
    );
}
