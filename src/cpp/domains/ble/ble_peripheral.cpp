#include <ble/peripheral.hpp>

using namespace whad::ble;

/**
 * @brief   Parse a BleMsg as a PeripheralMode message
 * 
 * @param[in]   message Message to parse
 */

PeripheralMode::PeripheralMode(BleMsg &message) : BleMsg(message)
{
    this->unpack();
}


/**
 * @brief   Create a PeripheralMode message.
 * 
 * @param[in]   pAdvData        Pointer to a buffer containing the advertising data
 * @param[in]   advDataLength   Size of the advertising data in bytes
 * @param[in]   pScanRsp        Pointer to a buffer containing the scan response data
 * @param[in]   scanRspLength   Size of the scan response data in bytes
 */

PeripheralMode::PeripheralMode(uint8_t *pAdvData, unsigned int advDataLength,
                               uint8_t *pScanRsp, unsigned int scanRspLength) : BleMsg()
{
    /* Save advertising data. */
    m_advDataLength = advDataLength;
    if (m_advDataLength <= 31)
    {
        memcpy(m_advData, pAdvData, m_advDataLength);
    }
    else
    {
        memset(m_advData, 0, 31);
    }

    /* Save scan response. */
    m_scanRspLength = scanRspLength;
    if (m_scanRspLength <= 31)
    {
        memcpy(m_scanRsp, pScanRsp, m_scanRspLength);
    }
    else
    {
        memset(m_scanRsp, 0, 31);
    }
}


/**
 * @brief   Pack parameters into a BleMsg
 */

void PeripheralMode::pack()
{
    whad_ble_peripheral_mode(this->getMessage(), m_advData, m_advDataLength,
                             m_scanRsp, m_scanRspLength);
}


/**
 * @brief   Extract parameters from BleMsg
 */

void PeripheralMode::unpack()
{
    whad_result_t result;
    whad_ble_adv_mode_params_t params;

    result = whad_ble_peripheral_mode_parse(
        this->getMessage(),
        &params
    );

    if (result == WHAD_ERROR)
    {
        throw WhadMessageParsingError();
    }
    else
    {
        /* Extract parameters. */
        m_advDataLength = params.adv_data_length;
        if (m_advDataLength <= 31)
        {
            memcpy(m_advData, params.adv_data, m_advDataLength);
        }
        else
        {
            memset(m_advData, 0, 31);
        }

        m_scanRspLength = params.scanrsp_data_length;
        if (m_scanRspLength <= 31)
        {
            memcpy(m_scanRsp, params.scanrsp_data, m_scanRspLength);
        }
        else
        {
            memset(m_scanRsp, 0, 31);
        }
    }
}


/**
 * @brief   Get the advertising data
 * 
 * @retval  Pointer to the advertising data buffer
 */

uint8_t *PeripheralMode::getAdvData()
{
    return m_advData;
}


/**
 * @brief   Get the size of advertising data
 * 
 * @retval  Size of advertising data in bytes
 */

unsigned int PeripheralMode::getAdvDataLength()
{
    return m_advDataLength;
}


/**
 * @brief   Get the scan response data
 * 
 * @retval  Pointer to the scan response data buffer
 */

uint8_t *PeripheralMode::getScanRsp()
{
    return m_scanRsp;
}


/**
 * @brief   Get the size of scan response data
 * 
 * @retval  Size of scan response data in bytes
 */

unsigned int PeripheralMode::getScanRspLength()
{
    return m_scanRspLength;
}