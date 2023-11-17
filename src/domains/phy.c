#include <whad.h>
#include <domains/phy.h>

bool whad_phy_frequency_range_encode_cb(pb_ostream_t *ostream, const pb_field_t *field, void * const *arg)
{
  phy_SupportedFrequencyRanges_FrequencyRange *frequency_range = *(phy_SupportedFrequencyRanges_FrequencyRange **)arg;
  if (ostream != NULL && field->tag == phy_SupportedFrequencyRanges_frequency_ranges_tag)
  {
    while ((frequency_range->start != 0) && (frequency_range->end != 0))
    {
      if (!pb_encode_tag_for_field(ostream, field))
      {
          const char * error = PB_GET_ERROR(ostream);
          PB_UNUSED(error);
          return false;
      }

      if (!pb_encode_submessage(ostream, phy_SupportedFrequencyRanges_FrequencyRange_fields, frequency_range))
      {
          const char * error = PB_GET_ERROR(ostream);
          PB_UNUSED(error);
          return false;
      }
      frequency_range++;
    }
  }
  return true;
}


/**
 * @brief Initialize a message specifying the supported frequency ranges for the current device
 * 
 * @param[in,out]   p_message           Pointer to the message structure to initialize
 * @param[in]       p_ranges            Pointer to a list of supported frequency ranges
 * @param[in]       nb_ranges           Number of ranges in the provided list
 * 
 * @retval          WHAD_SUCCESS        Success.
 * @retval          WHAD_ERROR          Invalid message pointer or supported ranges pointer.
 **/

whad_result_t whad_phy_supported_frequencies(Message *p_message, phy_SupportedFrequencyRanges_FrequencyRange *p_ranges,
                                             int nb_ranges)
{
    /* Sanity check. */
    if ((p_message == NULL) || (p_ranges == NULL))
    {
        return WHAD_ERROR;
    }

    /* Populate field. */
    p_message->which_msg = Message_phy_tag;
    p_message->msg.phy.which_msg = phy_Message_supported_freq_tag;
    p_message->msg.phy.msg.supported_freq.frequency_ranges.arg = p_ranges;
    p_message->msg.phy.msg.supported_freq.frequency_ranges.funcs.encode = whad_phy_frequency_range_encode_cb;

    /* Success. */
    return WHAD_SUCCESS;
}


/**
 * @brief Initialize a message reporting a PHY packet
 * 
 * @param[in,out]   p_message           Pointer to the message structure to initialize
 * @param[in]       frequency           Frequency on which the PHY packet has been captured
 * @param[in]       rssi                Received Signal Strength Indicator in dBm
 * @param[in]       ts_sec              Timestamp (seconds) at which the packet has been received
 * @param[in]       ts_usec             Timestamp (microseconds) at which the packet has been received
 * @param[in]       payload              Pointer to the packet payload
 * @param[in]       length              Payload size in bytes
 * 
 * @retval          WHAD_SUCCESS        Success.
 * @retval          WHAD_ERROR          Invalid message pointer or payload pointer.
 **/

whad_result_t whad_phy_packet_received(Message *p_message, uint32_t frequency, int32_t rssi, uint32_t ts_sec, uint32_t ts_usec,
                              uint8_t *payload, int length)
{
    /* Sanity check. */
    if ((p_message == NULL) || (payload == NULL))
    {
        return WHAD_ERROR;
    }

    /* Populate fields. */
    p_message->which_msg = Message_phy_tag;
    p_message->msg.phy.which_msg = phy_Message_packet_tag;
    p_message->msg.phy.msg.packet.frequency = frequency;

    /* Set timestamp if provided. */
    if ((ts_sec > 0) || (ts_usec > 0))
    {
        p_message->msg.phy.msg.packet.has_timestamp = true;
        p_message->msg.phy.msg.packet.timestamp.sec = ts_sec;
        p_message->msg.phy.msg.packet.timestamp.usec = ts_usec;
    }
    else
    {
        p_message->msg.phy.msg.packet.has_timestamp = false;
        p_message->msg.phy.msg.packet.timestamp.sec = 0;
        p_message->msg.phy.msg.packet.timestamp.usec = 0;
    }

    /* Set rssi. */
    p_message->msg.phy.msg.packet.has_rssi = true;
    p_message->msg.phy.msg.packet.rssi = rssi;

    /* Copy packet into our message. */
    p_message->msg.phy.msg.packet.packet.size = length;
    memcpy(p_message->msg.phy.msg.packet.packet.bytes, payload, length);

    /* Success. */
    return WHAD_SUCCESS;
}


/**
 * @brief Initialize a message indicating the result of a scheduled packet request
 * 
 * @param[in,out]   p_message           Pointer to the message structure to initialize
 * @param[in]       id                  Scheduled packet identifier
 * @param[in]       full                If set to true, indicate the scheduled packets FIFO is full
 *
 * @retval          WHAD_SUCCESS        Success.
 * @retval          WHAD_ERROR          Invalid message pointer or payload pointer.
 **/

whad_result_t whad_phy_packet_scheduled(Message *p_message, uint8_t id, bool full)
{
    /* Sanity check. */
    if (p_message == NULL)
    {
        return WHAD_ERROR;
    }

    /* Populate fields. */
    p_message->which_msg = Message_phy_tag;
    p_message->msg.phy.which_msg = phy_Message_sched_pkt_rsp_tag;
    p_message->msg.phy.msg.sched_pkt_rsp.id = id;
    if (full)
    {
        p_message->msg.phy.msg.sched_pkt_rsp.has_full = true;
        p_message->msg.phy.msg.sched_pkt_rsp.full = true;
    }
    else
    {
       p_message->msg.phy.msg.sched_pkt_rsp.has_full = false; 
    }

    /* Success. */
    return WHAD_SUCCESS;
}