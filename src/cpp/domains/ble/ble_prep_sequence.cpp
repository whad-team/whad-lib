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


/**
 * @brief       Create a manually triggered prepared sequence
 * 
 * @param[in]   id          Sequence ID
 * @param[in]   direction   Sequence direction
 * @param[in]   packets     Vector of PDU to send (packets list)
 **/

PrepareSequence::PrepareSequence(uint32_t id, Direction direction, std::vector<PDU> packets) : BleMsg()
{
    /* Convert our vector into a dynamically allocated array. */
    whad_prepared_packet_t *packetsArr = buildPacketsArray(packets);

    /* And we initialize our message. */
    whad_ble_prepare_sequence_manual(
        this->getRaw(),
        id,
        (whad_ble_direction_t)direction,
        packetsArr,
        packets.size()
    );

    /* Free our packets array. */
    delete[] packetsArr;
}


/**
 * @brief       Create a pattern-triggered prepared sequence
 * 
 * @param[in]   id          Sequence ID
 * @param[in]   direction   Sequence direction
 * @param[in]   packets     Vector of PDU to send (packets list)
 * @param[in]   trigger     Pattern trigger to apply with this sequence
 **/

PrepareSequence::PrepareSequence(uint32_t id, Direction direction, std::vector<PDU> packets, PatternTrigger trigger) : BleMsg()
{
    /* Convert our vector into a dynamically allocated array. */
    whad_prepared_packet_t *packetsArr = buildPacketsArray(packets);

    whad_ble_prepare_sequence_on_recv(
        this->getRaw(),
        trigger.getPattern(),
        trigger.getMask(),
        trigger.getLength(),
        trigger.getOffset(),
        id,
        (whad_ble_direction_t)direction,
        packetsArr,
        packets.size()
    );

    /* Free our packets array. */
    delete[] packetsArr;
}


/**
 * @brief       Create a connection event triggered prepared sequence
 * 
 * @param[in]   id          Sequence ID
 * @param[in]   direction   Sequence direction
 * @param[in]   packets     Vector of PDU to send (packets list)
 * @param[in]   trigger     Connection event trigger to apply with this sequence
 **/

PrepareSequence::PrepareSequence(uint32_t id, Direction direction, std::vector<PDU> packets,
                                    ConnEventTrigger trigger) : BleMsg()
{
    /* Convert our vector into a dynamically allocated array. */
    whad_prepared_packet_t *packetsArr = buildPacketsArray(packets);

    whad_ble_prepare_sequence_conn_evt(
        this->getRaw(),
        trigger.getConnEvent(),
        id,
        (whad_ble_direction_t)direction,
        packetsArr,
        packets.size()
    );

    /* Free our packets array. */
    delete[] packetsArr;
}