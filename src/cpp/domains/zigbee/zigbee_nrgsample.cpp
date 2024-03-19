#include <zigbee/nrgsample.hpp>

using namespace whad::zigbee;

/**
 * @brief   Parse a message as a EnergySample message.
 */

EnergySample::EnergySample(ZigbeeMsg &message) : ZigbeeMsg(message)
{
    this->unpack();
}


/**
 * @brief       EnergySample message constructor.
 * 
 * @param[in]   timestamp         Specify the sample timestamp
 * @param[in]   sample            Sample value
 **/

EnergySample::EnergySample(uint32_t timestamp, uint32_t value) : ZigbeeMsg()
{
    /* Save sample info. */
    m_timestamp = timestamp;
    m_value = value;
}


/**
 * @brief   Pack parameters into a ZigbeeMsg object
 */

void EnergySample::pack()
{
    whad_zigbee_energy_detect_sample(
        this->getMessage(),
        m_timestamp,
        m_value
    );
}


/**
 * @brief   Extract parameters from a ZigbeeMsg
 */

void EnergySample::unpack()
{
    whad_result_t result;
    whad_zigbee_ed_sample_t sample_info;

    result = whad_zigbee_energy_detect_sample_parse(
        this->getMessage(),
        &sample_info
    );

    if (result == WHAD_ERROR)
    {
        /* Error occured during parsing. */
        throw WhadMessageParsingError();
    }
    else
    {
        /* Save parameters. */
        m_timestamp = sample_info.timestamp;
        m_value = sample_info.sample;
    }
}


/**
 * @brief   Retrieve the sample timestamp
 * 
 * @retval  Timestamp value (in seconds1)
 */

uint32_t EnergySample::getTimestamp()
{
    return m_timestamp;
}


/**
 * @brief   Retrieve the sample value
 * 
 * @retval  Sample value
 */

uint32_t EnergySample::getValue()
{
    return m_value;
}
