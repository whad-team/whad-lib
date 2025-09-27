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

    /* Set default advertising parameters. */
    m_type = AdvType::AdvInd;
    m_channelMap = ChannelMap();
    m_channelMap.enableChannel(37);
    m_channelMap.enableChannel(38);
    m_channelMap.enableChannel(39);
    m_interMin = 0x20;
    m_interMax = 0x4000;
}

/**
 * @brief       AdvMode message constructor.
 * 
 * @param[in]   pAdvData        Pointer to a byte buffer containing the device advertising data
 * @param[in]   advDataLength   Size in bytes of the advertising data
 * @param[in]   pScanRsp        Pointer to a byte buffer containing the device scan response data
 * @param[in]   scanRspLength   Size in bytes of the scan response data
 * @param[in]   type            Advertisement type
 * @param[in]   chanMap         Advertising channel map
 * @param[in]   interMin        Minimum advertising interval value
 * @param[in]   interMax        Maximum advertising interval value
 **/

AdvMode::AdvMode(uint8_t *pAdvData, unsigned int advDataLength, uint8_t *pScanRsp, unsigned int scanRspLength,
        AdvType type, ChannelMap channelMap, uint16_t interMin, uint16_t interMax)
    : AdvMode(pAdvData, advDataLength, pScanRsp, scanRspLength)
{
    m_type = type;
    m_channelMap = channelMap;
    m_interMin = interMin;
    m_interMax = interMax;
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
        m_scanRspLength,
        (whad_ble_advtype_t)m_type,
        m_channelMap.getChannelMapBuf(),
        m_interMin,
        m_interMax
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

        /* Save advertising type. */
        m_type = (AdvType)params.adv_type;

        /* Save advertising channel map. */
        m_channelMap = ChannelMap(params.channel_map);

        /* Save advertising interval. */
        m_interMin = params.inter_min;
        m_interMax = params.inter_max;
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


/**
 * @brief   Get advertisement type
 *
 * @retval  Advertisement type
 */
AdvType AdvMode::getAdvType()
{
    return m_type;
}


/**
 * @brief   Get advertising channel map
 *
 * @retval  Channel map
 */
ChannelMap &AdvMode::getChannelMap()
{
    return m_channelMap;
}


/**
 * @brief   Get advertising mimimum interval
 *
 * @retval  Advertising minimum interval
 */
uint16_t AdvMode::getIntervalMin()
{
    return m_interMin;
}

/**
 * @brief   Get advertising maximum interval
 *
 * @retval  Advertising maximum interval
 */
uint16_t AdvMode::getIntervalMax()
{
    return m_interMax;
}

