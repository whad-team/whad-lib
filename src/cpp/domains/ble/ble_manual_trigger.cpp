#include <ble/manual_trigger.hpp>

using namespace whad::ble;

/**
 * @brief       Manually triggers a packet sequence
 * 
 * @param[in]   id          Sequence ID
 **/

ManualTrigger::ManualTrigger(uint32_t id) : BleMsg()
{
    whad_ble_prepare_sequence_trigger(
        this->getMessage(),
        id
    );
}