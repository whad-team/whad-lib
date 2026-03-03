#include <dot15d4/sendinslot.hpp>

using namespace whad::dot15d4;

/**
 * @brief   Parse a message as a SendInSlot message.
 */

SendInSlot::SendInSlot(Dot15d4Msg &message) : Dot15d4Msg(message)
{
    this->unpack();
}


/**
 * @brief       SendInSlot message constructor.
 * 
 * @param[in]   slot            Specify the slot to send in
 * @param[in]   wait_offset     Specif the wait duration before sending in the specified slot
 * @param[in]   pPdu            Pointer to a byte buffer to send
 * @param[in]   length          PDU length in bytes
 **/

SendInSlot::SendInSlot(uint64_t slot, uint64_t wait_offset, uint8_t *pPdu, int length) : Dot15d4Msg()
{
    /* Save slot. */
    m_slot = slot;

    /* Save offset*/
    m_wait_offset = wait_offset;

    /* Save PDU. */
    m_pdu = PDU(pPdu, length);
}




/**
 * @brief   Pack parameters into a Dot15d4Msg object
 */

void SendInSlot::pack()
{
    whad_dot15d4_send_in_slot(
        this->getMessage(),
        m_slot,
        m_wait_offset,
        m_pdu.getBytes(),
        m_pdu.getSize()
    );
}


/**
 * @brief   Extract parameters from a Dot15d4Msg
 */

void SendInSlot::unpack()
{
    whad_result_t result;
    whad_dot15d4_send_in_slot_params_t params;

    result = whad_dot15d4_send_in_slot_parse(
        this->getMessage(),
        &params
    );

    if (result == WHAD_ERROR)
    {
        /* Error occured during parsing. */
        throw WhadMessageParsingError();
    }
    else
    {
        /* Save parameters. */
        m_slot = params.slot;
        m_wait_offset = params.wait_offset;
        m_pdu.setBytes(params.packet.bytes, params.packet.length);
    }
}


/**
 * @brief   Retrieve the dot15d4 slot to use
 * 
 * @retval  absolute slot number
 */

uint64_t SendInSlot::getSlot()
{
    return m_slot;
}

uint64_t SendInSlot::getWaitOffset(){
    return m_wait_offset;
}

/**
 * @brief   Retrieve the PDU to send
 * 
 * @retval  Reference to the PDU object containing the bytes to send
 */

PDU& SendInSlot::getPdu()
{
    return m_pdu;
}


