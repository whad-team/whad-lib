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
    m_interval = SCAN_INTERVAL_DEFAULT;
    m_useExtAdv = false;
}


/**
 * @brief       ScanMode message constructor.
 * 
 * @param[in]   active      If set to true, adapter will perform an active scan
 * @param[in]   interval    Scan interval in ms.
 **/

ScanMode::ScanMode(bool active, uint32_t interval) : BleMsg()
{
    m_active = active;
    m_interval = interval;
    m_useExtAdv = false;
}


/**
 * @brief       ScanMode message constructor.
 * 
 * @param[in]   active      If set to true, adapter will perform an active scan
 * @param[in]   interval    Scan interval in ms.
 * @param[in]   useExtAdv   If set to true, will follow extended advertisements.
 **/

ScanMode::ScanMode(bool active, uint32_t interval, bool useExtAdv) : BleMsg()
{
    m_active = active;
    m_interval = interval;
    m_useExtAdv = useExtAdv;
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
 * @brief   Retrieve the scan interval.
 * 
 * @retval  Scan interval, in ms.
 */

uint32_t ScanMode::getInterval()
{
    return m_interval;
}

/**
 * @brief   Determine if scan mode uses extended advertisements.
 * 
 * @retval  true if extended advertisements are supported, false otherwise.
 */

bool ScanMode::useExtAdv()
{
    return m_useExtAdv;
}


/**
 * @brief   Pack parameters into a BleMsg
 */

void ScanMode::pack()
{
    whad_ble_scan_mode(this->getMessage(), m_active, m_interval, m_useExtAdv); 
}


/**
 * @brief   Extract parameters from a BleMsg 
 */

void ScanMode::unpack()
{
    whad_result_t result;

    result = whad_ble_scan_mode_parse(
        this->getMessage(),
        &m_active,
        &m_interval,
        &m_useExtAdv
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
 * @param[in]   rssi                Received signal strength indicator
 * @param[in]   address             Advertiser BD address
 * @param[in]   pAdvData            Pointer to the advertising data byte buffer
 * @param[in]   advDataLength       Advertising data length in bytes
 **/

AdvPdu::AdvPdu(AdvType advType, int32_t rssi, BDAddress address, uint8_t *pAdvData, unsigned int advDataLength, uint32_t channel, Phy phy) : BleMsg()
{
    m_advType = advType;
    m_rssi = rssi;
    m_address = address;
    m_advData = pAdvData;
    m_advDataLength = advDataLength;
    m_channel = channel;
    m_phy = phy;
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
        m_advDataLength,
        m_channel,
        (whad_ble_phy_t)m_phy
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
        m_channel = params.channel;
        m_phy = (Phy)params.phy;
    }
}


/**
 * @brief   Get advertisement type.
 *
 * @retval  Advertisement type.
 */

AdvType AdvPdu::getAdvType()
{
    return m_advType;
}


/**
 * @brief   Get RSSI.
 *
 * @retval  RSSI level (dBm)
 */

int32_t AdvPdu::getRssi()
{
    return m_rssi;
}


/**
 * @brief   Get BD address.
 *
 * @retval  BD address.
 */

BDAddress& AdvPdu::getAddress()
{
    return m_address;
}


/**
 * @brief   Get advertising data.
 *
 * @retval  Pointer to this pdu's advertising data
 */

uint8_t *AdvPdu::getAdvData()
{
    return m_advData;
}


/**
 * @brief   Get length of advertising data.
 *
 * @retval  Advertising data length, in bytes.
 */

unsigned int AdvPdu::getAdvDataLength()
{
    return m_advDataLength;
}


/**
 * @brief   Get channel number this PDU has been received on.
 *
 * @retval  Channel number.
 */

uint32_t AdvPdu::getChannel()
{
    return m_channel;
}


/**
 * @brief   Get RX PHY when PDU has been received.
 *
 * @retval  PHY
 */

Phy AdvPdu::getPhy()
{
    return m_phy;
}

