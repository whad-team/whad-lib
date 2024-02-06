#include <ble/del_sequence.hpp>

using namespace whad::ble;

/**
 * @brief       Delete a prepared sequence
 * 
 * @param[in]   id          Sequence ID
 **/

DeleteSequence::DeleteSequence(uint32_t id) : BleMsg()
{
    whad_ble_prepare_sequence_delete(
        this->getMessage(),
        id
    );
}