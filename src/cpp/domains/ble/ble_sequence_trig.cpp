#include <ble/sequence_trig.hpp>

using namespace whad::ble;

/**
 * @brief       Prepared sequence has been triggered
 * 
 * @param[in]   id          Sequence ID
 **/

SequenceTriggered::SequenceTriggered(uint32_t id) : BleMsg()
{
    whad_ble_triggered(
        this->getMessage(),
        id
    );
}