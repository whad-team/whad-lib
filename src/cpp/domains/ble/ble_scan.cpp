#include <ble/scan.hpp>

using namespace whad::ble;

/**
 * @brief   Parse a BleMsg as a ScanMode message.
 */

ScanMode::ScanMode(BleMsg &message) : BleMsg(message)
{
    this->unpack();
}


/**
 * @brief       ScanMode message constructor.
 * 
 * @param[in]   active      If set to true, adapter will perform an active scan
 **/

ScanMode::ScanMode(bool active) : BleMsg()
{
    m_active = active;
}

/**
 * @brief   Determine if an active scan is requested or not
 * 
 * @retval  True if active scan is requested, False otherwise.
 */

bool ScanMode::isActiveModeEnabled()
{
    return m_active;
}

/**
 * @brief   Pack parameters into a BleMsg
 */

void ScanMode::pack()
{
    whad_ble_scan_mode(this->getMessage(), m_active); 
}


/**
 * @brief   Extract parameters from a BleMsg 
 */

void ScanMode::unpack()
{
    whad_result_t result;

    result = whad_ble_scan_mode_parse(
        this->getMessage(),
        &m_active
    );

    if (result == WHAD_ERROR)
    {
        throw WhadMessageParsingError();
    }
}


/**
 * @brief   Parse a BleMsg as an AdvPdu message
 * 
 * @param[in]   message     Message to parse
 */

AdvPdu::AdvPdu(BleMsg &message) : BleMsg(message)
{
    this->unpack();
}


/**
 * @brief       Notify an advertising PDU
 * 
 * @param[in]   advType             Advertisement type
 * @param[in]   address             Advertiser BD address
 * @param[in]   pAdvData            Pointer to the advertising data byte buffer
 * @param[in]   advDataLength       Advertising data length in bytes
 **/

AdvPdu::AdvPdu(AdvType advType, int32_t rssi, BDAddress address, uint8_t *pAdvData, unsigned int advDataLength) : BleMsg()
{
    m_advType = advType;
    m_rssi = rssi;
    m_address = address;
    m_advData = pAdvData;
    m_advDataLength = advDataLength;
}


/**
 * @brief   Pack parameters into a BleMsg.
 */

void AdvPdu::pack()
{
    whad_ble_adv_pdu(
        this->getMessage(),
        (whad_ble_advtype_t)m_advType,
        m_rssi,
        m_address.getAddressBuf(),
        (whad_ble_addrtype_t)m_address.getType(),
        m_advData,
        m_advDataLength
    );
}


/**
 * @brief   Extract parameters from a BleMsg
 */

void AdvPdu::unpack()
{
    whad_result_t result;
    whad_ble_adv_pdu_t params;

    result = whad_ble_adv_pdu_parse(
        this->getMessage(),
        &params
    );

    if (result == WHAD_ERROR)
    {
        throw WhadMessageParsingError();
    }
    else
    {
        m_rssi = params.rssi;
        m_advType = (AdvType)params.adv_type;
        m_address = BDAddress((AddressType)params.addr_type, params.p_bdaddr);
        m_advDataLength = params.adv_data_length;
        m_advData = params.p_adv_data;
    }
}