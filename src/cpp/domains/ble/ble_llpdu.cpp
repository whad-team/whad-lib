#include <ble/ll_pdu.hpp>

using namespace whad::ble;

LinkLayerPdu::LinkLayerPdu(BleMsg &message) : BleMsg(message)
{
    this->unpack();
}

/**
 * @brief   Create a LinkLayerPdu object from a BLE PDU.
 * 
 * @param[in]   conn_handle Connection handle
 * @param[in]   pdu         BLE PDU
 * @param[in]   direction   Direction of the PDU (host to slave, slave to host, ...)
 * @param[in]   processed   Set to `true` if this PDU has already been processed
 * @param[in]   decrypted   Set to `true` if PDU has been decrypted
 **/

LinkLayerPdu::LinkLayerPdu(uint32_t conn_handle, PDU pdu, Direction direction, bool processed, bool decrypted) : BleMsg()
{
    m_connHandle = conn_handle;
    m_pdu = pdu;
    m_direction = direction;
    m_processed = processed;
    m_decrypted = decrypted;
}

void LinkLayerPdu::pack()
{
    /* Initialize our data pdu message. */
    whad_ble_pdu(
        this->getMessage(),
        m_pdu.getBytes(),
        m_pdu.getSize(),
        (whad_ble_direction_t)m_direction,
        m_connHandle,
        m_processed,
        m_decrypted
    );    
}

void LinkLayerPdu::unpack()
{
    whad_result_t result;
    whad_ble_pdu_t params;

    result = whad_ble_pdu_parse(
        this->getMessage(),
        &params
    );

    if (result == WHAD_ERROR)
    {
        /* Parsing error. */
        throw WhadMessageParsingError();
    }
    else
    {
        /* Update properties. */
        m_connHandle = params.conn_handle;
        m_decrypted = params.decrypted;
        m_processed = params.processed;
        m_pdu = PDU(params.p_pdu, params.pdu_length);
        m_direction = (Direction)params.direction;
    }
}


/**
 * @brief   Get the connection handle
 * 
 * @retval  Connection handle value
 */

uint32_t LinkLayerPdu::getConnHandle()
{
    return m_connHandle;
}


/**
 * @brief   Get the PDU
 * 
 * @retval  Reference to the received PDU
 */

PDU& LinkLayerPdu::getPdu()
{
    return m_pdu;
}


/**
 * @brief   Get the PDU direction
 * 
 * @retval  Direction
 */

Direction LinkLayerPdu::getDirection()
{
    return m_direction;
}


/**
 * @brief   Determine if this PDU has already been processed or not by the firmware
 * 
 * @retval  True    PDU has been processed
 * @retval  False   PDU has not been processed
 */

bool LinkLayerPdu::isProcessed()
{
    return m_processed;
}


/**
 * @brief   Determine if the PDU has been decrypted by the firmware
 * 
 * @retval  True    PDU has been decrypted on-the-fly by the adapter firmware
 * @retval  False   PDU has not been decrypted
 */

bool LinkLayerPdu::isDecrypted()
{
    return m_decrypted;
}