#ifndef INC_WHAD_PROTOCOL_H
#define INC_WHAD_PROTOCOL_H

#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif

/*********************************
 * Enum/Structure definitions
 ********************************/

typedef enum {
    PHY_LORA_SF7 = phy_LoRaSpreadingFactor_SF7,
    PHY_LORA_SF8 = phy_LoRaSpreadingFactor_SF8,
    PHY_LORA_SF9 = phy_LoRaSpreadingFactor_SF9,
    PHY_LORA_SF10 = phy_LoRaSpreadingFactor_SF10,
    PHY_LORA_SF11 = phy_LoRaSpreadingFactor_SF11,
    PHY_LORA_SF12 = phy_LoRaSpreadingFactor_SF12
} whad_phy_lora_sf_t;

typedef enum {
    PHY_LORA_CR45 = phy_LoRaCodingRate_CR45,
    PHY_LORA_CR46 = phy_LoRaCodingRate_CR46,
    PHY_LORA_CR47 = phy_LoRaCodingRate_CR47,
    PHY_LORA_CR48 = phy_LoRaCodingRate_CR48,
} whad_phy_lora_cr_t;

typedef enum {
    PHY_BIG_ENDIAN = phy_Endianness_BIG,
    PHY_LITTLE_ENDIAN = phy_Endianness_LITTLE
} whad_phy_endian_t;

typedef enum {
  MOD_ASK  = phy_Modulation_ASK,
  MOD_FSK  = phy_Modulation_FSK,
  MOD_4FSK = phy_Modulation_FOURFSK,
  MOD_GFSK = phy_Modulation_GFSK,
  MOD_MSK  = phy_Modulation_MSK,
  MOD_BPSK = phy_Modulation_BPSK,
  MOD_QPSK = phy_Modulation_QPSK,
  MOD_LORA = phy_Modulation_LORA
} whad_phy_modulation_t;

typedef enum {
    PHY_TXPOWER_LOW = phy_TXPower_LOW,
    PHY_TXPOWER_MEDIUM = phy_TXPower_MEDIUM,
    PHY_TXPOWER_HIGH = phy_TXPower_HIGH
} whad_phy_txpower_t;

typedef enum {
    PHY_JAM_MODE_CONTINUOUS = phy_JammingMode_CONTINUOUS,
    PHY_JAM_MODE_REACTIVE = phy_JammingMode_REACTIVE
} whad_phy_jam_mode_t;

typedef struct {
    uint32_t bandwidth;
    whad_phy_lora_sf_t sf;
    whad_phy_lora_cr_t cr;
    uint32_t preamble_length;
    bool enable_crc;
    bool explicit_mode;
    bool invert_iq;
} whad_phy_lora_params_t;

typedef struct {
    uint8_t syncword[10];
    int length;
} whad_phy_syncword_t;

typedef struct {
    uint8_t payload[256];
    int length;
} whad_phy_packet_t;

typedef struct {
    uint32_t ts_sec;
    uint32_t ts_usec;
} whad_phy_timestamp_t;

typedef struct {
    whad_phy_packet_t packet;
    whad_phy_timestamp_t ts;
} whad_phy_sched_packet_t;

typedef struct {
    uint32_t freq;
    int32_t rssi;
    whad_phy_timestamp_t ts;
    whad_phy_packet_t packet;
} whad_phy_received_packet_t;

typedef struct {
    uint8_t id;
    bool full;
} whad_phy_scheduled_packet_t;

typedef struct {
    uint32_t start;
    uint32_t end;
} whad_phy_frequency_range_t;

typedef enum {
    WHAD_PHY_UNKNOWN=0,
    WHAD_PHY_SET_ASK_MOD=phy_Message_mod_ask_tag,
    WHAD_PHY_SET_FSK_MOD=phy_Message_mod_fsk_tag,
    WHAD_PHY_SET_GFSK_MOD=phy_Message_mod_gfsk_tag,
    WHAD_PHY_SET_BPSK_MOD=phy_Message_mod_bpsk_tag,
    WHAD_PHY_SET_QPSK_MOD=phy_Message_mod_qpsk_tag,
    WHAD_PHY_SET_4FSK_MOD=phy_Message_mod_4fsk_tag,
    WHAD_PHY_SET_MSK_MOD=phy_Message_mod_msk_tag,
    WHAD_PHY_SET_LORA_MOD=phy_Message_mod_lora_tag,
    WHAD_PHY_GET_SUPPORTED_FREQS=phy_Message_get_supported_freq_tag,
    WHAD_PHY_SET_FREQ=phy_Message_set_freq_tag,
    WHAD_PHY_SET_DATARATE=phy_Message_datarate_tag,
    WHAD_PHY_SET_ENDIANNESS=phy_Message_endianness_tag,
    WHAD_PHY_SET_TX_POWER=phy_Message_tx_power_tag,
    WHAD_PHY_SET_PACKET_SIZE=phy_Message_packet_size_tag,
    WHAD_PHY_SET_SYNC_WORD=phy_Message_sync_word_tag,
    WHAD_PHY_SET_SNIFF_MODE=phy_Message_sniff_tag,
    WHAD_PHY_SEND=phy_Message_send_tag,
    WHAD_PHY_SEND_RAW=phy_Message_send_raw_tag,
    WHAD_PHY_START=phy_Message_start_tag,
    WHAD_PHY_STOP=phy_Message_stop_tag,
    WHAD_PHY_SET_JAM_MODE=phy_Message_jam_tag,
    WHAD_PHY_SET_MONITOR_MODE=phy_Message_monitor_tag,
    WHAD_PHY_PACKET_RECEIVED=phy_Message_packet_tag,
    WHAD_PHY_RAW_PACKET_RECEIVED=phy_Message_raw_packet_tag,
    WHAD_PHY_JAMMED=phy_Message_jammed_tag,
    WHAD_PHY_MONITOR_REPORT=phy_Message_monitor_report_tag,
    WHAD_PHY_SUPPORTED_FREQS=phy_Message_supported_freq_tag,
    WHAD_PHY_SEND_SCHED_PACKET=phy_Message_sched_send_tag,
    WHAD_PHY_SCHED_PACKET_RESP=phy_Message_sched_pkt_rsp_tag,
    WHAD_PHY_SCHED_PACKET_SENT=phy_Message_sched_pkt_sent_tag
} whad_phy_msgtype_t;

/*********************************
 * PHY domain
 ********************************/

/* Get PHY message type from NanoPb message. */
whad_phy_msgtype_t whad_phy_get_message_type(Message *p_message);
void whad_phy_message_free(Message *p_message);

/* Modulation selection. */
whad_result_t whad_phy_set_ask_mod(Message *p_message, bool on_off_keying);
whad_result_t whad_phy_set_ask_mod_parse(Message *p_message, bool *p_on_off_keying);
whad_result_t whad_phy_set_fsk_mod(Message *p_message, uint32_t deviation);
whad_result_t whad_phy_set_fsk_mod_parse(Message *p_message, uint32_t *p_deviation);
whad_result_t whad_phy_set_4fsk_mod(Message *p_message, uint32_t deviation);
whad_result_t whad_phy_set_4fsk_mod_parse(Message *p_message, uint32_t *p_deviation);
whad_result_t whad_phy_set_gfsk_mod(Message *p_message, uint32_t deviation);
whad_result_t whad_phy_set_gfsk_mod_parse(Message *p_message, uint32_t *p_deviation);
whad_result_t whad_phy_set_bpsk_mod(Message *p_message);
whad_result_t whad_phy_set_qpsk_mod(Message *p_message, bool b_offset);
whad_result_t whad_phy_set_qpsk_mod_parse(Message *p_message, bool *p_offset);
whad_result_t whad_phy_set_msk_mod(Message *p_message, uint32_t deviation);
whad_result_t whad_phy_set_msk_mod_parse(Message *p_message, uint32_t *p_deviation);
whad_result_t whad_phy_set_lora_mod(Message *p_message, uint32_t bandwidth, whad_phy_lora_sf_t spreading_factor,
                                    whad_phy_lora_cr_t coding_rate, uint32_t preamble_length, bool enable_crc,
                                    bool explicit_mode, bool invert_iq);
whad_result_t whad_phy_set_lora_mod_parse(Message *p_message, whad_phy_lora_params_t *p_lora_params);

/* Signal characteristics. */
whad_result_t whad_phy_set_freq(Message *p_message, uint32_t frequency);
whad_result_t whad_phy_set_freq_parse(Message *p_message, uint32_t *p_freq);
whad_result_t whad_phy_set_datarate(Message *p_message, uint32_t datarate);
whad_result_t whad_phy_set_datarate_parse(Message *p_message, uint32_t *p_datarate);
whad_result_t whad_phy_set_endianness(Message *p_message, whad_phy_endian_t endianness);
whad_result_t whad_phy_set_endianness_parse(Message *p_message, whad_phy_endian_t *p_endianness);
whad_result_t whad_phy_set_tx_power(Message *p_message, whad_phy_txpower_t tx_power);
whad_result_t whad_phy_set_tx_power_parse(Message *p_message, whad_phy_txpower_t *p_power);
whad_result_t whad_phy_set_packet_size(Message *p_message, uint32_t size);
whad_result_t whad_phy_set_packet_size_parse(Message *p_message, uint32_t *p_packet_size);
whad_result_t whad_phy_set_sync_word(Message *p_message, uint8_t *p_syncword, int length);
whad_result_t whad_phy_set_sync_word_parse(Message *p_message, whad_phy_syncword_t *p_syncword);
whad_result_t whad_phy_supported_frequencies(Message *p_message, whad_phy_frequency_range_t *p_ranges,
                                             int nb_ranges);

/* Modes */
whad_result_t whad_phy_sniff_mode(Message *p_message, bool iq_stream);
whad_result_t whad_phy_sniff_mode_parse(Message *p_message, bool *p_iq_stream);
whad_result_t whad_phy_jam_mode(Message *p_message, whad_phy_jam_mode_t mode);
whad_result_t whad_phy_jam_mode_parse(Message *p_message, whad_phy_jam_mode_t *p_mode);
whad_result_t whad_phy_monitor_mode(Message *p_message);
whad_result_t whad_phy_start(Message *p_message);
whad_result_t whad_phy_stop(Message *p_message);

/* Sending packets. */
whad_result_t whad_phy_send(Message *p_message, uint8_t *p_packet, int length);
whad_result_t whad_phy_send_parse(Message *p_message, whad_phy_packet_t *p_packet);
whad_result_t whad_phy_send_raw_iq(Message *p_message, uint8_t *p_iq_stream, int length); /* TODO !*/
whad_result_t whad_phy_sched_packet(Message *p_message, uint8_t *p_packet, int length, uint32_t ts_sec,
                                    uint32_t ts_usec);
whad_result_t whad_phy_sched_packet_parse(Message *p_message, whad_phy_sched_packet_t *p_sched_packet);

/* Notifications. */
whad_result_t whad_phy_jammed(Message *p_message, uint32_t ts_sec, uint32_t ts_usec);
whad_result_t whad_phy_jammed_parse(Message *p_message, whad_phy_timestamp_t *p_timestamp);
#if 0
whad_result_t whad_phy_packet_received(Message *p_message, uint32_t frequency, int32_t rssi, uint32_t ts_sec, uint32_t ts_usec,
                              uint8_t *payload, int length);
#else
whad_result_t whad_phy_packet_received(Message *p_message, uint32_t frequency, int32_t rssi, uint32_t ts_sec, uint32_t ts_usec,
                              uint8_t *payload, int length, uint8_t *syncword, int syncword_length, uint32_t deviation, uint32_t datarate,
                              whad_phy_endian_t endianness, whad_phy_modulation_t modulation);
#endif
whad_result_t whad_phy_packet_received_parse(Message *p_message, whad_phy_received_packet_t *p_received_pkt);
whad_result_t whad_phy_packet_scheduled(Message *p_message, uint8_t id, bool full);
whad_result_t whad_phy_packet_scheduled_parse(Message *p_message, whad_phy_scheduled_packet_t *p_sched_pkt);
whad_result_t whad_phy_sched_packet_sent(Message *p_message, uint32_t packet_id);
whad_result_t whad_phy_sched_packet_sent_parse(Message *p_message, uint32_t *p_packet_id);

#ifdef __cplusplus
}
#endif

#endif /* INC_WHAD_PROTOCOL_H */
