#include <ble/del_sequence.hpp>

using namespace whad::ble;

DeleteSequence::DeleteSequence(BleMsg &message) : BleMsg(message)
{
    /* TODO: parsing code in C and C++ */
}

/**
 * @brief       Delete a prepared sequence
 * 
 * @param[in]   id          Sequence ID
 **/

DeleteSequence::DeleteSequence(uint32_t id) : BleMsg()
{
   m_seqId = id;
}


/**
 * @brief   Pack parameters in a BleMsg
 */

void DeleteSequence::pack()
{
    whad_ble_prepare_sequence_delete(
        this->getMessage(),
        m_seqId
    );   
}


/**
 * @brief   Retrieve the sequence Id
 * 
 * @retval  Sequence Id
 */

uint32_t DeleteSequence::getId()
{
    return m_seqId;
}