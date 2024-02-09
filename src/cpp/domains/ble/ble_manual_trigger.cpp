#include <ble/manual_trigger.hpp>

using namespace whad::ble;

/**
 * @brief   Parse a BleMsg as a ManualTrigger message.
 */

ManualTrigger::ManualTrigger(BleMsg &message) : BleMsg(message)
{
    this->unpack();
}


/**
 * @brief       Manually triggers a packet sequence
 * 
 * @param[in]   id          Sequence ID
 **/

ManualTrigger::ManualTrigger(uint32_t id) : BleMsg()
{
    m_id = id;
}


/**
 * @brief   Get the trigger ID
 * 
 * @retval  Trigger ID
 */

uint32_t ManualTrigger::getId()
{
    return m_id;
}


/**
 * @brief   Pack parameters into a BleMsg
 */

void ManualTrigger::pack()
{
    whad_ble_prepare_sequence_trigger(
        this->getMessage(),
        m_id
    ); 
}


/**
 * @brief   Extract parameters from a BleMsg
 */

void ManualTrigger::unpack()
{
    whad_result_t result;

    result = whad_ble_prepare_sequence_trigger_parse(
        this->getMessage(),
        &m_id
    );

    if (result == WHAD_ERROR)
    {
        throw WhadMessageParsingError();
    }
}