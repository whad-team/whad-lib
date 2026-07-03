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

AdvMode::AdvMode(AdvType advType, uint32_t interMin, uint32_t interMax, uint8_t *pAdvData, unsigned int advDataLength, uint8_t *pScanRsp, unsigned int scanRspLength) : BleMsg()
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

    /* Save advertising parameters. */
    m_type = advType;
    m_interMin = interMin;
    m_interMax = interMax;
    m_csa = Csa::Csa1;
}


/**
 * @brief   Pack parameters into a BleMsg object.
 */

void AdvMode::pack()
{
    whad_ble_ext_adv_t ext_pdus[4];
    std::vector<ExtAdvPdu>::iterator it;
    int nb_ext_adv = 0;

    /* Populate extended advertising PDUs, if any. */
    if (m_pdus.size() > 0)
    {
        for (it = m_pdus.begin(); it < m_pdus.end(); it++)
        {
            /* Fill ext_pdus array with the current ExtAdvPdu info. */
            it->copyTo(&ext_pdus[nb_ext_adv++]);
        }
    }

    whad_ble_adv_mode(
        this->getMessage(),
        (whad_ble_advtype_t)m_type,
        m_interMin,
        m_interMax,
        m_channelMap.getChannelMapBuf(),
        m_advData,
        m_advDataLength,
        m_scanRsp,
        m_scanRspLength,
        (whad_ble_csa_t)m_csa,
        ext_pdus,
        nb_ext_adv
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
        /* Save advertising parameters. */
        m_type = (AdvType)params.type;
        m_interMin = params.inter_min;
        m_interMax = params.inter_max;
        m_csa = (Csa)params.csa;
        memcpy(m_channelMap.getChannelMapBuf(), params.channel_map, 5);

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


/**
 * @brief   Get advertisement type
 *
 * @retval  Advertisement type (AdvType)
 */

AdvType AdvMode::getAdvType()
{
    return m_type;
}


/**
 * @brief   Get minimum advertising interval
 *
 * @retval  Minimum advertising interval (0x0020 < interval < 0x4000)
 */

uint32_t AdvMode::getIntervalMin()
{
    return m_interMin;
}


/**
 * @brief   Get maximum advertising interval
 *
 * @retval  Maximum advertising interval (0x0020 < interval < 0x4000)
 */

uint32_t AdvMode::getIntervalMax()
{
    return m_interMax;
}


/**
 * @brief   Get selected Channel Selection Algorithm (CSA)
 *
 * @retval  Selected Channel Selection Algorithm
 */

Csa AdvMode::getCsa()
{
    return m_csa;
}

/**
 * @brief   Get channel map
 *
 * @retval  Configured channel map
 */

ChannelMap& AdvMode::getChannelMap()
{
    return m_channelMap;
}

/**
 * @brief   Add an extended advertising PDU.
 *
 * @retval  True if PDU has successfully been added, false otherwise.
 **/

bool AdvMode::addExtPdu(ExtAdvPdu& pdu)
{
    if (m_pdus.size() < 4)
    {
        m_pdus.push_back(pdu);

        /* Success. */
        return true;
    }
    else
    {
        /* Failed, maximum number of extended PDU reached. */
        return false;
    }
}


/**
 * @brief   Get the number of extended advertising PDU already defined.
 *
 * @retval  Number of extended advertising PDU.
 **/
size_t AdvMode::getNumberOfExtPdus()
{
    return m_pdus.size();
}

/**
 * @brief   Retrieve a specific extended advertising PDU.
 *
 * @retval  Reference to an extended advertising PDU, NULL if index is invalid.
 **/
ExtAdvPdu* AdvMode::getExtPdu(unsigned int index)
{
    if (index < m_pdus.size())
    {
        return &m_pdus.at(index);
    }
    else
        return NULL;
}

