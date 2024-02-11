#include <ble/setadvdata.hpp>

using namespace whad::ble;

SetAdvData::SetAdvData(BleMsg &message) : BleMsg(message)
{
    this->unpack();
}


/**
 * @brief       SetAdvData message constructor.
 * 
 * @param[in]   pAdvData        Pointer to a byte buffer containing the device advertising data
 * @param[in]   advDataLength   Size in bytes of the advertising data
 * @param[in]   pScanRsp        Pointer to a byte buffer containing the device scan response data
 * @param[in]   scanRspLength   Size in bytes of the scan response data
 **/

SetAdvData::SetAdvData(uint8_t *pAdvData, unsigned int advDataLength, uint8_t *pScanRsp, unsigned int scanRspLength) : BleMsg()
{
    whad_ble_set_adv_data(
        this->getMessage(),
        pAdvData,
        advDataLength,
        pScanRsp,
        scanRspLength
    );
}

void SetAdvData::pack()
{
    whad_ble_set_adv_data(
        this->getMessage(),
        m_advData,
        m_advDataLength,
        m_scanRsp,
        m_scanRspLength
    );   
}


void SetAdvData::unpack()
{
    /* TODO */
}

uint8_t *SetAdvData::getAdvData()
{
    return m_advData;
}

unsigned int SetAdvData::getAdvDataLength()
{
    return m_advDataLength;
}

uint8_t *SetAdvData::getScanRsp()
{
    return m_scanRsp;
}

unsigned int SetAdvData::getScanRspLength()
{
    return m_scanRspLength;
}