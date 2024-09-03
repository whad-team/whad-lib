#include <dot15d4/nrgsample.hpp>

using namespace whad::dot15d4;

/**
 * @brief   Parse a message as a EnergySample message.
 */

EnergySample::EnergySample(Dot15d4Msg &message) : Dot15d4Msg(message)
{
    this->unpack();
}


/**
 * @brief       EnergySample message constructor.
 * 
 * @param[in]   timestamp         Specify the sample timestamp
 * @param[in]   value             Sample value
 **/

EnergySample::EnergySample(uint32_t timestamp, uint32_t value) : Dot15d4Msg()
{
    /* Save sample info. */
    m_timestamp = timestamp;
    m_value = value;
}


/**
 * @brief   Pack parameters into a Dot15d4Msg object
 */

void EnergySample::pack()
{
    whad_dot15d4_energy_detect_sample(
        this->getMessage(),
        m_timestamp,
        m_value
    );
}


/**
 * @brief   Extract parameters from a Dot15d4Msg
 */

void EnergySample::unpack()
{
    whad_result_t result;
    whad_dot15d4_ed_sample_t sample_info;

    result = whad_dot15d4_energy_detect_sample_parse(
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
