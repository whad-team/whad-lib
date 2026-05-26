#include <dot15d4/updatesuperframe.hpp>

using namespace whad::dot15d4;

/**
 * @brief   Parse a message as a UpdateSuperframe message.
 */

UpdateSuperframe::UpdateSuperframe(Dot15d4Msg &message) : Dot15d4Msg(message)
{
    this->unpack();
}


/**
 * @brief       UpdateSuperframe message constructor.
 * 
 * @param[in]   superframe_id       Specify the identifier of the superframe
 * @param[in]   number_of_slots     Size of the superframe (in number of slots)
 * @param[in]   flags               Flags associated to the superframe
 * @param[in]   asn                 Absolute Slot Number
 **/

UpdateSuperframe::UpdateSuperframe(uint32_t superframe_id, uint32_t number_of_slots, uint32_t flags, uint64_t asn) : Dot15d4Msg()
{
    /* Save superframe identifier.*/
    m_superframe_id = superframe_id;

    /* Save number of slots. */
    m_number_of_slots = number_of_slots;

    /* Save flags. */
    m_flags = flags;

    /* Save absolute slot number. */
    m_asn = asn;
}

/**
 * @brief   Pack parameters into a Dot15d4Msg object
 */

void UpdateSuperframe::pack()
{
    whad_dot15d4_update_superframe(
        this->getMessage(),
        m_superframe_id,
        m_number_of_slots,
        m_flags, 
        m_asn
    );
}


/**
 * @brief   Extract parameters from a Dot15d4Msg
 */

void UpdateSuperframe::unpack()
{
    whad_result_t result;
    
    uint32_t superframe_id;
    uint32_t number_of_slots;
    uint32_t flags;
    uint64_t asn;

    result = whad_dot15d4_update_superframe_parse(
        this->getMessage(),
        &superframe_id,
        &number_of_slots,
        &flags,
        &asn
    );

    if (result == WHAD_ERROR)
    {
        /* Error occured during parsing. */
        throw WhadMessageParsingError();
    }
    else
    {
        /* Save parameters. */
        m_superframe_id = superframe_id;
        m_number_of_slots = number_of_slots;
        m_flags = flags;
        m_asn = asn;
    }
}


/**
 * @brief   Retrieve the Superframe identifier
 * 
 * @retval  Superframe identifier
 */
uint32_t UpdateSuperframe::getSuperframeId()
{
    return m_superframe_id;
}


/**
 * @brief   Retrieve the number of slots of the Superframe
 * 
 * @retval  Number of slots
 */
 
uint32_t UpdateSuperframe::getNumberOfSlots()
{
    return m_number_of_slots;
}

/**
 * @brief   Retrieve the flags associated with the superframe
 * 
 * @retval  Flags of Superframe 
 */
uint32_t UpdateSuperframe::getFlags()
{
    return m_flags;
}


/**
 * @brief   Retrieve the absolute slot number (ASN) starting the superframe
 * 
 * @retval  absolute slot number (ASN) 
 */
uint64_t UpdateSuperframe::getASN()
{
    return m_asn;
}