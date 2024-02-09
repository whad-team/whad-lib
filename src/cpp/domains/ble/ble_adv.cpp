#include <ble/adv.hpp>

using namespace whad::ble;

/**
 * @brief       AdvMode message constructor, parse an existing message.
 * 
 * @param[in]   message     Message to parse.
 */

AdvMode::AdvMode(BleMsg &message) : BleMsg(message)
{
    this->unpack();
}


/**
 * @brief       AdvMode message constructor.
 * 
 * @param[in]   pAdvData        Pointer to a byte buffer containing the device advertising data
 * @param[in]   advDataLength   Size in bytes of the advertising data
 * @param[in]   pScanRsp        Pointer to a byte buffer containing the device scan response data
 * @param[in]   scanRspLength   Size in bytes of the scan response data
 **/

AdvMode::AdvMode(uint8_t *pAdvData, unsigned int advDataLength, uint8_t *pScanRsp, unsigned int scanRspLength) : BleMsg()
{
    /* If advertising data is provided, save it. */
    if ((advDataLength <= 31) && (pAdvData != NULL))
    {
        m_advDataLength = advDataLength;
        memcpy(m_advData, pAdvData, m_advDataLength);
    }
    else
    {
        m_advDataLength = 0;
        memset(m_advData, 0, 31);
    }

    /* If scan response is provided, save it also. */
    if ((scanRspLength <= 31) && (pScanRsp != NULL))
    {
        m_scanRspLength = scanRspLength;
        memcpy(m_scanRsp, pScanRsp, m_scanRspLength);
    }
    else
    {
        m_scanRspLength = 0;
        memset(m_scanRsp, 0, 31);
    }
}


/**
 * @brief   Pack parameters into a BleMsg object.
 */

void AdvMode::pack()
{
    whad_ble_adv_mode(
        this->getMessage(),
        m_advData,
        m_advDataLength,
        m_scanRsp,
        m_scanRspLength
    );
}


/**
 * @brief   Extract parameters from a BleMsg message.
 */

void AdvMode::unpack()
{
    whad_result_t result;
    whad_ble_adv_mode_params_t params;

    result = whad_ble_adv_mode_parse(
        this->getMessage(),
        &params
    );

    if (result == WHAD_ERROR)
    {
        throw WhadMessageParsingError();
    }
    else
    {
        /* Save advertising data. */
        m_advDataLength = params.adv_data_length;
        if ((m_advDataLength > 0) && (m_advDataLength <= 31))
        {
            memcpy(m_advData, params.adv_data, m_advDataLength);
        }

        /* Save scan response data. */
        m_scanRspLength = params.scanrsp_data_length;
        if ((m_scanRspLength > 0) && (m_scanRspLength <= 31))
        {
            memcpy(m_scanRsp, params.scanrsp_data, m_scanRspLength);
        }
    }
}


/**
 * @brief   Get advertising data length
 * 
 * @retval  Length of advertising data
 */

unsigned int AdvMode::getAdvDataLength()
{
    return m_advDataLength;
}


/**
 * @brief   Get scan response data length
 * 
 * @retval  Length of scan response data
 */

unsigned int AdvMode::getScanRspLength()
{
    return m_scanRspLength;
}


/**
 * @brief   Get pointer to the advertising data
 * 
 * @retval  Pointer to the advertising data
 */

uint8_t *AdvMode::getAdvData()
{
    return m_advData;
}


/**
 * @brief   Get pointer to the scan response data
 * 
 * @retval  Pointer to the scan response data
 */

uint8_t *AdvMode::getScanRsp()
{
    return m_scanRsp;
}