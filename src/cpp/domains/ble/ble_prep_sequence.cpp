#include <ble/prep_sequence.hpp>

using namespace whad::ble;

/**
 * @brief       Convert a vecor of PDU into a WHAD prepared packets array
 * 
 * @param[in]   packets     Vector of packets to convert into a WHAD prepared packets array
 * 
 * @return      Dynamically allocated packets array
 **/

whad_prepared_packet_t *buildPacketsArray(std::vector<PDU> packets)
{
    whad_prepared_packet_t *packetsArr;
    int packetCount = packets.size();

    if (packetCount > 0)
    {
        /* We need to create an array of packets. */
        packetsArr = new whad_prepared_packet_t[packetCount];

        /* Then we populate this array with our packets. */
        for (int i=0; i<packetCount; i++)
        {
            memcpy(packetsArr[i].p_bytes, packets[i].getBytes(), packets[i].getSize());
            packetsArr[i].length = packets[i].getSize();
        }

        /* Success. */
        return packetsArr;
    }
    else
    {
        /* Nothing to allocate. */
        return NULL;
    }
}


/***************************************************
 * PrepareSequence base class
 ***************************************************/

/**
 * @brief   Default constructor.
 */

PrepareSequence::PrepareSequence()
{
    m_id = 0;
    m_direction = DirectionMasterToSlave;
}


/**
 * @brief   Create a prepared sequence
 * 
 * @param[in]   id          Sequence ID
 * @param[in]   direction   Packet(s) direction
 * @param[in]   packets     List of packets
 */

PrepareSequence::PrepareSequence(uint32_t id, Direction direction, std::vector<PDU> packets)
{
    m_id = id;
    m_direction = direction;
    m_packets = packets;
}


/**
 * @brief   Get the sequence ID
 * 
 * @retval  Sequence ID
 */

uint32_t PrepareSequence::getId()
{
    return m_id;
}


/**
 * @brief   Get packets direction
 * 
 * @retval  Packets direction
 */

Direction PrepareSequence::getDirection()
{
    return m_direction;
}


/**
 * @brief   Get packet list
 * 
 * @retval  Reference to packet list
 */

std::vector<PDU>& PrepareSequence::getPackets()
{
    return m_packets;
}


/***************************************************
 * PrepareSequence with manual trigger.
 ***************************************************/

/**
 * @brief   Parse a BleMsg as a PrepareSequenceManual object
 * 
 * @param[in]   message     Message to parse
 */

PrepareSequenceManual::PrepareSequenceManual(BleMsg &message) : BleMsg(message), PrepareSequence()
{
    this->unpack();
}


/**
 * @brief   Create a PrepareSequenceManual message
 * 
 * @param[in]   id          Sequence ID
 * @param[in]   direction   Packets direction
 * @param[in]   packets     List of packets to send when a manual trigger is issued
 */

PrepareSequenceManual::PrepareSequenceManual(uint32_t id, Direction direction,
    std::vector<PDU> packets) : BleMsg(), PrepareSequence(id, direction, packets)
{
}


/**
 * @brief   Pack parameters into a BleMsg
 */

void PrepareSequenceManual::pack()
{
    whad_prepared_packet_t *p_packets = buildPacketsArray(m_packets);

    whad_ble_prepare_sequence_manual(
        this->getMessage(),
        m_id,
        (whad_ble_direction_t)m_direction,
        p_packets,
        m_packets.size()
    );

    delete[] p_packets;
}


/**
 * @brief   Extract parameters from a BleMsg
 */

void PrepareSequenceManual::unpack()
{
    unsigned int i;
    whad_result_t result;
    whad_ble_prepseq_params_t params;

    result = whad_ble_prepare_sequence_manual_parse(
        this->getMessage(),
        &params
    );

    if (result == WHAD_ERROR)
    {
        throw WhadMessageParsingError();
    }
    else
    {
        /* Save parameters and packets. */
        m_id = params.id;
        m_direction = (Direction)params.direction;

        m_packets.clear();
        for (i=0; i<params.packet_count; i++)
        {
            m_packets.push_back(PDU(params.packets[i].p_bytes, params.packets[i].length));
        }
    }
}


/***************************************************
 * PrepareSequence with connection event trigger.
 ***************************************************/

/**
 * @brief   Parse a BleMsg as a PrepareSequenceConnEvt message.
 * 
 * @param[in]   message     Message to parse
 */

PrepareSequenceConnEvt::PrepareSequenceConnEvt(BleMsg &message) : BleMsg(message), PrepareSequence()
{
    this->unpack();
}


/**
 * @brief   Create a PrepareSequenceConnEvt message.
 * 
 * @param[in]   id          Sequence ID
 * @param[in]   direction   Packets direction
 * @param[in]   packets     List of packets to send when a manual trigger is issued
 * @param[in]   connEvt     Connection Event at which these packets must be sent
 */

PrepareSequenceConnEvt::PrepareSequenceConnEvt(uint32_t id, Direction direction,
    std::vector<PDU> packets, uint32_t connEvt) : BleMsg(), PrepareSequence(id, direction, packets)
{
    m_connEvt = connEvt;
}


/**
 * @brief   Get the connection event value
 * 
 * @retval  Connection event value
 */

uint32_t PrepareSequenceConnEvt::getConnEvt()
{
    return m_connEvt;
}


/**
 * @brief   Pack parameters into a BleMsg
 */

void PrepareSequenceConnEvt::pack()
{
    whad_prepared_packet_t *p_packets = buildPacketsArray(m_packets);

    whad_ble_prepare_sequence_conn_evt(
        this->getMessage(),
        m_connEvt,
        m_id,
        (whad_ble_direction_t)m_direction,
        p_packets,
        m_packets.size()
    );

    delete[] p_packets;    
}


/**
 * @brief   Extract parameters from a BleMsg
 */

void PrepareSequenceConnEvt::unpack()
{
    unsigned int i;
    whad_result_t result;
    whad_ble_prepseq_params_t params;

    result = whad_ble_prepare_sequence_conn_evt_parse(
        this->getMessage(),
        &params
    );

    if (result == WHAD_ERROR)
    {
        throw WhadMessageParsingError();
    }
    else
    {
        /* Save parameters and packets. */
        m_id = params.id;
        m_direction = (Direction)params.direction;
        m_connEvt = params.conn_evt;

        m_packets.clear();
        for (i=0; i<params.packet_count; i++)
        {
            m_packets.push_back(PDU(params.packets[i].p_bytes, params.packets[i].length));
        }
    }
}