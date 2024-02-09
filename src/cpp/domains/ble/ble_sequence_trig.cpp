#include <ble/sequence_trig.hpp>

using namespace whad::ble;

/**
 * @brief   Parse a BleMsg as a SequenceTriggered message
 * 
 * @param[in]   message     Message to parse
 */

SequenceTriggered::SequenceTriggered(BleMsg &message) : BleMsg(message)
{
    this->unpack();
}


/**
 * @brief       Prepared sequence has been triggered
 * 
 * @param[in]   id          Sequence ID
 **/

SequenceTriggered::SequenceTriggered(uint32_t id) : BleMsg()
{
    m_id = id;
}


/**
 * @brief   Pack parameters into a BleMsg
 */

void SequenceTriggered::pack()
{
    whad_ble_triggered(
        this->getMessage(),
        m_id
    ); 
}


/**
 * @brief   Extract parameters from a BleMsg
 */

void SequenceTriggered::unpack()
{
    whad_result_t result;

    result = whad_ble_triggered_parse(
        this->getMessage(),
        &m_id
    );

    if (result == WHAD_ERROR)
    {
        throw WhadMessageParsingError();
    }
}