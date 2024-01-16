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
 * @brief Initialize a message specifying the Amplitude Shift Keying modulation
 * 
 * @param[in,out]   p_message           Pointer to the message structure to initialize
 * @param[in]       on_off_keying       Set to true to use On/Off keying, false otherwise
 * 
 * @retval          WHAD_SUCCESS        Success.
 * @retval          WHAD_ERROR          Invalid message pointer or supported ranges pointer.
 **/

whad_result_t whad_phy_set_ask_mod(Message *p_message, bool on_off_keying)
{
     /* Sanity check. */
    if (p_message == NULL)
    {
        return WHAD_ERROR;
    }

    /* Configure protobuf message. */
    p_message->which_msg = Message_phy_tag;
    p_message->msg.phy.which_msg =  phy_Message_mod_ask_tag;
    p_message->msg.phy.msg.mod_ask.ook = on_off_keying;

    /* Success. */
    return WHAD_SUCCESS;
}


/**
 * @brief Initialize a message specifying the Frequency Shift Keying modulation
 * 
 * @param[in,out]   p_message           Pointer to the message structure to initialize
 * @param[in]       deviation           Set FSK deviation in Hz
 * 
 * @retval          WHAD_SUCCESS        Success.
 * @retval          WHAD_ERROR          Invalid message pointer or supported ranges pointer.
 **/

whad_result_t whad_phy_set_fsk_mod(Message *p_message, uint32_t deviation)
{
     /* Sanity check. */
    if (p_message == NULL)
    {
        return WHAD_ERROR;
    }

    /* Configure protobuf message. */
    p_message->which_msg = Message_phy_tag;
    p_message->msg.phy.which_msg =  phy_Message_mod_fsk_tag;
    p_message->msg.phy.msg.mod_fsk.deviation = deviation;

    /* Success. */
    return WHAD_SUCCESS;
}


/**
 * @brief Initialize a message specifying the 4 Frequency Shift Keying modulation
 * 
 * @param[in,out]   p_message           Pointer to the message structure to initialize
 * @param[in]       deviation           Set 4FSK deviation in Hz
 * 
 * @retval          WHAD_SUCCESS        Success.
 * @retval          WHAD_ERROR          Invalid message pointer or supported ranges pointer.
 **/

whad_result_t whad_phy_set_4fsk_mod(Message *p_message, uint32_t deviation)
{
     /* Sanity check. */
    if (p_message == NULL)
    {
        return WHAD_ERROR;
    }

    /* Configure protobuf message. */
    p_message->which_msg = Message_phy_tag;
    p_message->msg.phy.which_msg =  phy_Message_mod_4fsk_tag;
    p_message->msg.phy.msg.mod_4fsk.deviation = deviation;

    /* Success. */
    return WHAD_SUCCESS;
}


/**
 * @brief Initialize a message specifying the Gaussian Frequency Shift Keying modulation
 * 
 * @param[in,out]   p_message           Pointer to the message structure to initialize
 * @param[in]       deviation           Set GFSK deviation in Hz
 * 
 * @retval          WHAD_SUCCESS        Success.
 * @retval          WHAD_ERROR          Invalid message pointer or supported ranges pointer.
 **/

whad_result_t whad_phy_set_gfsk_mod(Message *p_message, uint32_t deviation)
{
     /* Sanity check. */
    if (p_message == NULL)
    {
        return WHAD_ERROR;
    }

    /* Configure protobuf message. */
    p_message->which_msg = Message_phy_tag;
    p_message->msg.phy.which_msg =  phy_Message_mod_gfsk_tag;
    p_message->msg.phy.msg.mod_gfsk.deviation = deviation;

    /* Success. */
    return WHAD_SUCCESS;
}


/**
 * @brief Initialize a message specifying the Binary Phase Shift Keying modulation
 * 
 * @param[in,out]   p_message           Pointer to the message structure to initialize
 * 
 * @retval          WHAD_SUCCESS        Success.
 * @retval          WHAD_ERROR          Invalid message pointer or supported ranges pointer.
 **/

whad_result_t whad_phy_set_bpsk_mod(Message *p_message)
{
     /* Sanity check. */
    if (p_message == NULL)
    {
        return WHAD_ERROR;
    }

    /* Configure protobuf message. */
    p_message->which_msg = Message_phy_tag;
    p_message->msg.phy.which_msg =  phy_Message_mod_bpsk_tag;

    /* Success. */
    return WHAD_SUCCESS;
}


/**
 * @brief Initialize a message specifying the Quadrature Phase Shift Keying modulation
 * 
 * @param[in,out]   p_message           Pointer to the message structure to initialize
 * @param[in]       offset              QPSK offset
 * 
 * @retval          WHAD_SUCCESS        Success.
 * @retval          WHAD_ERROR          Invalid message pointer or supported ranges pointer.
 **/

whad_result_t whad_phy_set_qpsk_mod(Message *p_message, bool b_offset)
{
     /* Sanity check. */
    if (p_message == NULL)
    {
        return WHAD_ERROR;
    }

    /* Configure protobuf message. */
    p_message->which_msg = Message_phy_tag;
    p_message->msg.phy.which_msg =  phy_Message_mod_qpsk_tag;
    p_message->msg.phy.msg.mod_qpsk.offset_qpsk = b_offset;

    /* Success. */
    return WHAD_SUCCESS;
}


/**
 * @brief Initialize a message specifying the Minimum Shift Keying modulation
 * 
 * @param[in,out]   p_message           Pointer to the message structure to initialize
 * @param[in]       deviation           Set MSK deviation in Hz
 * 
 * @retval          WHAD_SUCCESS        Success.
 * @retval          WHAD_ERROR          Invalid message pointer or supported ranges pointer.
 **/

whad_result_t whad_phy_set_msk_mod(Message *p_message, uint32_t deviation)
{
     /* Sanity check. */
    if (p_message == NULL)
    {
        return WHAD_ERROR;
    }

    /* Configure protobuf message. */
    p_message->which_msg = Message_phy_tag;
    p_message->msg.phy.which_msg =  phy_Message_mod_msk_tag;
    p_message->msg.phy.msg.mod_msk.deviation = deviation;

    /* Success. */
    return WHAD_SUCCESS;
}


/**
 * @brief Initialize a message specifying the LoRa modulation
 * 
 * @param[in,out]   p_message           Pointer to the message structure to initialize
 * @param[in]       bandwith            Bandwidth in Hz
 * @param[in]       spreading_factor    Spreading factor to use
 * @param[in]       coding_rate         Coding rate to use
 * @param[in]       preamble_length     Preamble length in symbols
 * @param[in]       enable_crc          Enable CRC if set to true, disabled otherwise
 * @param[in]       explicit_mode       Enable explicit mode if set to true, disabled otherwise
 * @param[in]       invert_iq           Invert IQ if set to true (downlink)
 * 
 * @retval          WHAD_SUCCESS        Success.
 * @retval          WHAD_ERROR          Invalid message pointer or supported ranges pointer.
 **/

whad_result_t whad_phy_set_lora_mod(Message *p_message, uint32_t bandwidth, whad_phy_lora_sf_t spreading_factor,
                                    whad_phy_lora_cr_t coding_rate, uint32_t preamble_length, bool enable_crc,
                                    bool explicit_mode, bool invert_iq)
{
     /* Sanity check. */
    if (p_message == NULL)
    {
        return WHAD_ERROR;
    }

    /* Configure protobuf message. */
    p_message->which_msg = Message_phy_tag;
    p_message->msg.phy.which_msg =  phy_Message_mod_lora_tag;
    p_message->msg.phy.msg.mod_lora.bandwidth = bandwidth;
    p_message->msg.phy.msg.mod_lora.spreading_factor = spreading_factor;
    p_message->msg.phy.msg.mod_lora.coding_rate = coding_rate;
    p_message->msg.phy.msg.mod_lora.preamble_length = preamble_length;
    p_message->msg.phy.msg.mod_lora.enable_crc = enable_crc;
    p_message->msg.phy.msg.mod_lora.explicit_mode = explicit_mode;
    p_message->msg.phy.msg.mod_lora.invert_iq = invert_iq;

    /* Success. */
    return WHAD_SUCCESS;
}


/**
 * @brief Initialize a message specifying the frequency to use
 * 
 * @param[in,out]   p_message           Pointer to the message structure to initialize
 * @param[in]       frequency           Frequency to use, in Hz
 * 
 * @retval          WHAD_SUCCESS        Success.
 * @retval          WHAD_ERROR          Invalid message pointer or supported ranges pointer.
 **/

whad_result_t whad_phy_set_freq(Message *p_message, uint32_t frequency)
{
     /* Sanity check. */
    if (p_message == NULL)
    {
        return WHAD_ERROR;
    }

    /* Configure protobuf message. */
    p_message->which_msg = Message_phy_tag;
    p_message->msg.phy.which_msg =  phy_Message_set_freq_tag;
    p_message->msg.phy.msg.set_freq.frequency = frequency;

    /* Success. */
    return WHAD_SUCCESS;
}


/**
 * @brief Initialize a message specifying the datarate to use
 * 
 * @param[in,out]   p_message           Pointer to the message structure to initialize
 * @param[in]       datarate            Frequency to use, in Hz
 * 
 * @retval          WHAD_SUCCESS        Success.
 * @retval          WHAD_ERROR          Invalid message pointer or supported ranges pointer.
 **/

whad_result_t whad_phy_set_datarate(Message *p_message, uint32_t datarate)
{
     /* Sanity check. */
    if (p_message == NULL)
    {
        return WHAD_ERROR;
    }

    /* Configure protobuf message. */
    p_message->which_msg = Message_phy_tag;
    p_message->msg.phy.which_msg =  phy_Message_datarate_tag;
    p_message->msg.phy.msg.datarate.rate = datarate;

    /* Success. */
    return WHAD_SUCCESS;
}


/**
 * @brief Initialize a message specifying the endianness
 * 
 * @param[in,out]   p_message           Pointer to the message structure to initialize
 * @param[in]       endianness          Packet endianness
 * 
 * @retval          WHAD_SUCCESS        Success.
 * @retval          WHAD_ERROR          Invalid message pointer or supported ranges pointer.
 **/

whad_result_t whad_phy_set_endianness(Message *p_message, whad_phy_endian_t endianness)
{
     /* Sanity check. */
    if (p_message == NULL)
    {
        return WHAD_ERROR;
    }

    /* Configure protobuf message. */
    p_message->which_msg = Message_phy_tag;
    p_message->msg.phy.which_msg =  phy_Message_endianness_tag;
    p_message->msg.phy.msg.endianness.endianness = endianness;

    /* Success. */
    return WHAD_SUCCESS;
}


/**
 * @brief Initialize a message specifying the transmit power
 * 
 * @param[in,out]   p_message           Pointer to the message structure to initialize
 * @param[in]       tx_power            TX power
 * 
 * @retval          WHAD_SUCCESS        Success.
 * @retval          WHAD_ERROR          Invalid message pointer or supported ranges pointer.
 **/

whad_result_t whad_phy_set_tx_power(Message *p_message, whad_phy_txpower_t tx_power)
{
     /* Sanity check. */
    if (p_message == NULL)
    {
        return WHAD_ERROR;
    }

    /* Configure protobuf message. */
    p_message->which_msg = Message_phy_tag;
    p_message->msg.phy.which_msg =  phy_Message_tx_power_tag;
    p_message->msg.phy.msg.tx_power.tx_power = tx_power;

    /* Success. */
    return WHAD_SUCCESS;
}


/**
 * @brief Initialize a message specifying the packet size in bytes
 * 
 * @param[in,out]   p_message           Pointer to the message structure to initialize
 * @param[in]       size                Packet size in bytes
 * 
 * @retval          WHAD_SUCCESS        Success.
 * @retval          WHAD_ERROR          Invalid message pointer or supported ranges pointer.
 **/

whad_result_t whad_phy_set_packet_size(Message *p_message, uint32_t size)
{
     /* Sanity check. */
    if (p_message == NULL)
    {
        return WHAD_ERROR;
    }

    /* Configure protobuf message. */
    p_message->which_msg = Message_phy_tag;
    p_message->msg.phy.which_msg =  phy_Message_packet_size_tag;
    p_message->msg.phy.msg.packet_size.packet_size = size;

    /* Success. */
    return WHAD_SUCCESS;
}


/**
 * @brief Initialize a message specifying the synchronization word
 * 
 * @param[in,out]   p_message           Pointer to the message structure to initialize
 * @param[in]       p_syncword          Pointer to a buffer containing the synchronization word
 * @param[in]       length              Syncword length in bytes
 * 
 * @retval          WHAD_SUCCESS        Success.
 * @retval          WHAD_ERROR          Invalid message pointer or supported ranges pointer.
 **/

whad_result_t whad_phy_set_sync_word(Message *p_message, uint8_t *p_syncword, int length)
{
    /* Sanity check. */
    if ((p_message == NULL) || (p_syncword == NULL))
    {
        return WHAD_ERROR;
    }

    /* If syncword length is greater than 10, error. */
    if (length > 10)
    {
        return WHAD_ERROR;
    }

    /* Configure protobuf message. */
    p_message->which_msg = Message_phy_tag;
    p_message->msg.phy.which_msg =  phy_Message_sync_word_tag;
    p_message->msg.phy.msg.sync_word.sync_word.size = length;
    memcpy(p_message->msg.phy.msg.sync_word.sync_word.bytes, p_syncword, length);

    /* Success. */
    return WHAD_SUCCESS;
}


/**
 * @brief Initialize a message setting the hardware in sniffing mode
 * 
 * @param[in,out]   p_message           Pointer to the message structure to initialize
 * @param[in]       iq_stream           If set to true, will capture I/Q instead of packets
 * 
 * @retval          WHAD_SUCCESS        Success.
 * @retval          WHAD_ERROR          Invalid message pointer or supported ranges pointer.
 **/

whad_result_t whad_phy_sniff_mode(Message *p_message, bool iq_stream)
{
     /* Sanity check. */
    if (p_message == NULL)
    {
        return WHAD_ERROR;
    }

    /* Configure protobuf message. */
    p_message->which_msg = Message_phy_tag;
    p_message->msg.phy.which_msg =  phy_Message_sniff_tag;
    p_message->msg.phy.msg.sniff.has_iq_stream = true;
    p_message->msg.phy.msg.sniff.iq_stream = iq_stream;

    /* Success. */
    return WHAD_SUCCESS;
}


/**
 * @brief Initialize a message setting the hardware in jamming mode
 * 
 * @param[in,out]   p_message           Pointer to the message structure to initialize
 * @param[in]       mode                Jamming mode to use
 * 
 * @retval          WHAD_SUCCESS        Success.
 * @retval          WHAD_ERROR          Invalid message pointer or supported ranges pointer.
 **/

whad_result_t whad_phy_jam_mode(Message *p_message, whad_phy_jam_mode_t mode)
{
     /* Sanity check. */
    if (p_message == NULL)
    {
        return WHAD_ERROR;
    }

    /* Configure protobuf message. */
    p_message->which_msg = Message_phy_tag;
    p_message->msg.phy.which_msg =  phy_Message_jam_tag;
    p_message->msg.phy.msg.jam.mode = mode;

    /* Success. */
    return WHAD_SUCCESS;
}


/**
 * @brief Initialize a message setting the hardware in monitor mode
 * 
 * @param[in,out]   p_message           Pointer to the message structure to initialize
 * 
 * @retval          WHAD_SUCCESS        Success.
 * @retval          WHAD_ERROR          Invalid message pointer or supported ranges pointer.
 **/

whad_result_t whad_phy_monitor_mode(Message *p_message)
{
     /* Sanity check. */
    if (p_message == NULL)
    {
        return WHAD_ERROR;
    }

    /* Configure protobuf message. */
    p_message->which_msg = Message_phy_tag;
    p_message->msg.phy.which_msg =  phy_Message_monitor_tag;

    /* Success. */
    return WHAD_SUCCESS;
}


/**
 * @brief Initialize a message starting the current mode
 * 
 * @param[in,out]   p_message           Pointer to the message structure to initialize
 * 
 * @retval          WHAD_SUCCESS        Success.
 * @retval          WHAD_ERROR          Invalid message pointer or supported ranges pointer.
 **/

whad_result_t whad_phy_start(Message *p_message)
{
     /* Sanity check. */
    if (p_message == NULL)
    {
        return WHAD_ERROR;
    }

    /* Configure protobuf message. */
    p_message->which_msg = Message_phy_tag;
    p_message->msg.phy.which_msg =  phy_Message_start_tag;

    /* Success. */
    return WHAD_SUCCESS;
}


/**
 * @brief Initialize a message stopping the current mode
 * 
 * @param[in,out]   p_message           Pointer to the message structure to initialize
 * 
 * @retval          WHAD_SUCCESS        Success.
 * @retval          WHAD_ERROR          Invalid message pointer or supported ranges pointer.
 **/

whad_result_t whad_phy_stop(Message *p_message)
{
     /* Sanity check. */
    if (p_message == NULL)
    {
        return WHAD_ERROR;
    }

    /* Configure protobuf message. */
    p_message->which_msg = Message_phy_tag;
    p_message->msg.phy.which_msg =  phy_Message_stop_tag;

    /* Success. */
    return WHAD_SUCCESS;
}


/**
 * @brief Initialize a message to send a raw packet
 * 
 * @param[in,out]   p_message           Pointer to the message structure to initialize
 * @param[in]       p_packet            Pointer to packet bytes to send
 * @param[in]       length              Number of bytes to send
 * 
 * @retval          WHAD_SUCCESS        Success.
 * @retval          WHAD_ERROR          Invalid message pointer or supported ranges pointer.
 **/

whad_result_t whad_phy_send(Message *p_message, uint8_t *p_packet, int length)
{
     /* Sanity check. */
    if ((p_message == NULL) || (p_packet == NULL))
    {
        return WHAD_ERROR;
    }

    /* Check if packet length does not exceed 255 bytes. */
    if (length > 255)
    {
        return WHAD_ERROR;
    }

    /* Configure protobuf message. */
    p_message->which_msg = Message_phy_tag;
    p_message->msg.phy.which_msg =  phy_Message_send_tag;
    p_message->msg.phy.msg.send.packet.size = length;
    memcpy(p_message->msg.phy.msg.send.packet.bytes, p_packet, length);

    /* Success. */
    return WHAD_SUCCESS;
}


/**
 * @brief Initialize a message to send raw IQs
 * 
 * @param[in,out]   p_message           Pointer to the message structure to initialize
 * @param[in]       p_iq_stream         Pointer to IQ to send
 * @param[in]       length              Number of bytes to send
 * 
 * @retval          WHAD_SUCCESS        Success.
 * @retval          WHAD_ERROR          Invalid message pointer or supported ranges pointer.
 **/

whad_result_t whad_phy_send_raw_iq(Message *p_message, uint8_t *p_iq_stream, int length)
{
     /* Sanity check. */
    if ((p_message == NULL) || (p_iq_stream == NULL))
    {
        return WHAD_ERROR;
    }

    /* Check if packet length does not exceed 255 bytes. */
    if (length > 255)
    {
        return WHAD_ERROR;
    }

    /* Configure protobuf message. */
    p_message->which_msg = Message_phy_tag;
    p_message->msg.phy.which_msg =  phy_Message_send_raw_tag;
    
    /* TODO: implement support for repeated and packed IQs */

    /* Success. */
    return WHAD_SUCCESS;
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
 * @brief Initialize a message to schedule a packet to be sent
 * 
 * @param[in,out]   p_message           Pointer to the message structure to initialize
 * @param[in]       p_packet            Pointer to a packet buffer to send
 * @param[in]       length              Packet length in bytes
 * @param[in]       ts_sec              Timestamp, seconds
 * @param[in]       ts_usec             Timestamp, microseconds
 * 
 * @retval          WHAD_SUCCESS        Success.
 * @retval          WHAD_ERROR          Invalid message pointer or supported ranges pointer.
 **/

whad_result_t whad_phy_sched_packet(Message *p_message, uint8_t *p_packet, int length, uint32_t ts_sec,
                                             uint32_t ts_usec)
{
    /* Sanity check. */
    if ((p_message == NULL) || (p_packet == NULL))
    {
        return WHAD_ERROR;
    }

    /* Packet size must not exceed 255 bytes. */
    if (length > 255)
    {
        return WHAD_ERROR;
    }

    /* Populate field. */
    p_message->which_msg = Message_phy_tag;
    p_message->msg.phy.which_msg = phy_Message_sched_send_tag;

    /* Copy packet. */
    p_message->msg.phy.msg.sched_send.packet.size = length;
    memcpy(p_message->msg.phy.msg.sched_send.packet.bytes, p_packet, length);

    /* Set timestamp. */
    p_message->msg.phy.msg.sched_send.has_timestamp = true;
    p_message->msg.phy.msg.sched_send.timestamp.sec = ts_sec;
    p_message->msg.phy.msg.sched_send.timestamp.usec = ts_usec;

    /* Success. */
    return WHAD_SUCCESS;
}


/**
 * @brief Initialize a message notifying the target has been jammed
 * 
 * @param[in,out]   p_message           Pointer to the message structure to initialize
 * @param[in]       ts_sec              Timestamp, seconds
 * @param[in]       ts_usec             Timestamp, microseconds
 *
 * @retval          WHAD_SUCCESS        Success.
 * @retval          WHAD_ERROR          Invalid message pointer or payload pointer.
 **/

whad_result_t whad_phy_jammed(Message *p_message, uint32_t ts_sec, uint32_t ts_usec)
{
    /* Sanity check. */
    if (p_message == NULL)
    {
        return WHAD_ERROR;
    }

    /* Populate fields. */
    p_message->which_msg = Message_phy_tag;
    p_message->msg.phy.which_msg = phy_Message_jammed_tag;
    
    if ((ts_sec > 0) || (ts_usec > 0))
    {
        p_message->msg.phy.msg.jammed.has_timestamp = true;
        p_message->msg.phy.msg.jammed.timestamp.sec = ts_sec;
        p_message->msg.phy.msg.jammed.timestamp.usec = ts_usec;
    }
    else
    {
        p_message->msg.phy.msg.jammed.has_timestamp = false;
        p_message->msg.phy.msg.jammed.timestamp.sec = 0;
        p_message->msg.phy.msg.jammed.timestamp.usec = 0;
    }

    /* Success. */
    return WHAD_SUCCESS;
}


/**
 * @brief Initialize a message notifying a scheduled packet has been sent.
 * 
 * @param[in,out]   p_message           Pointer to the message structure to initialize
 * @param[in]       packet_id           Packet id
 *
 * @retval          WHAD_SUCCESS        Success.
 * @retval          WHAD_ERROR          Invalid message pointer or payload pointer.
 **/

whad_result_t whad_phy_sched_packet_sent(Message *p_message, uint32_t packet_id)
{
    /* Sanity check. */
    if (p_message == NULL)
    {
        return WHAD_ERROR;
    }

    /* Populate fields. */
    p_message->which_msg = Message_phy_tag;
    p_message->msg.phy.which_msg = phy_Message_sched_pkt_sent_tag;
    p_message->msg.phy.msg.sched_pkt_sent.id = packet_id;

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