#ifndef __INC_WHAD_ESB_H
#define __INC_WHAD_ESB_H

#include "types.h"

#define ESB_PACKET_MAX_SIZE     255
#define ESB_ADDR_MAX_SIZE       5

#ifdef __cplusplus
extern "C" {
#endif

/*********************************
 * Enhanced ShockBurst domain
 ********************************/

/** @brief  Supported commands
 * 
 * This enum defines aliases for NanoPb commands bitmask in order to hide
 * the NanoPb implementation.
 * 
 * This structure needs to be updated if a command is added or removed in
 * WHAD protocol.
 **/

typedef enum {
    WHAD_ESB_UNKNOWN=0,
    WHAD_ESB_SET_NODE_ADDRESS=esb_Message_set_node_addr_tag,
    WHAD_ESB_SNIFF=esb_Message_sniff_tag,
    WHAD_ESB_JAM=esb_Message_jam_tag,
    WHAD_ESB_SEND=esb_Message_send_tag,
    WHAD_ESB_SEND_RAW=esb_Message_send_raw_tag,
    WHAD_ESB_PRX=esb_Message_prx_tag,
    WHAD_ESB_PTX=esb_Message_ptx_tag,
    WHAD_ESB_START=esb_Message_start_tag,
    WHAD_ESB_STOP=esb_Message_stop_tag,
    WHAD_ESB_JAMMED=esb_Message_jammed_tag,
    WHAD_ESB_RAW_PDU_RECEIVED=esb_Message_raw_pdu_tag,
    WHAD_ESB_PDU_RECEIVED=esb_Message_pdu_tag
} whad_esb_msgtype_t;

/**
 * ESB address structure
 **/

typedef struct {
    uint8_t address[ESB_ADDR_MAX_SIZE];
    int size;
} whad_esb_address_t;

/**
 * ESB packet structure 
 **/

typedef struct {
    uint8_t bytes[ESB_PACKET_MAX_SIZE];
    uint8_t length;
} whad_esb_packet_t;


/**
 * ESB SniffCmd parameters 
 **/

typedef struct {
    whad_esb_address_t address;
    uint32_t channel;
    bool show_acks;
} whad_esb_sniff_params_t;


/**
 * ESB SendCmd parameters 
 **/

typedef struct {
    uint32_t channel;
    uint32_t retr_count;
    whad_esb_packet_t packet;
} whad_esb_send_params_t;

/**
 * ESB PduReceived and RawPduReceived parameters 
 **/

typedef struct {
    uint32_t channel;
    bool has_rssi;
    int32_t rssi;
    bool has_timestamp;
    uint32_t timestamp;
    bool has_crc_validity;
    bool crc_validity;
    bool has_address;
    whad_esb_address_t address;
    whad_esb_packet_t packet;
} whad_esb_recvd_packet_t;

/* Get ESB message type from NanoPb message. */
whad_esb_msgtype_t whad_esb_get_message_type(Message *p_message);

/**
 * WHAD ESB messages creation and parsing.
 */

whad_result_t whad_esb_set_node_address(Message *p_message, whad_esb_address_t *p_addr);
whad_result_t whad_esb_set_node_address_parse(Message *p_message, whad_esb_address_t *p_addr);
whad_result_t whad_esb_sniff(Message *p_message, whad_esb_address_t *p_addr, uint32_t channel, bool show_ack);
whad_result_t whad_esb_sniff_parse(Message *p_message, whad_esb_sniff_params_t *p_params);
whad_result_t whad_esb_jam(Message *p_message, uint32_t channel);
whad_result_t whad_esb_jam_parse(Message *p_message, uint32_t *p_channel);
whad_result_t whad_esb_send(Message *p_message, uint32_t channel, int retr_count,
                            uint8_t *p_packet, uint8_t packet_len);
whad_result_t whad_esb_send_parse(Message *p_message, whad_esb_send_params_t *p_params);
whad_result_t whad_esb_send_raw(Message *p_message, uint32_t channel, int retr_count,
                            uint8_t *p_packet, uint8_t packet_len);
whad_result_t whad_esb_send_raw_parse(Message *p_message, whad_esb_send_params_t *p_params);
whad_result_t whad_esb_prx(Message *p_message, uint32_t channel);
whad_result_t whad_esb_prx_parse(Message *p_message, uint32_t *p_channel);
whad_result_t whad_esb_ptx(Message *p_message, uint32_t channel);
whad_result_t whad_esb_ptx_parse(Message *p_message, uint32_t *p_channel);
whad_result_t whad_esb_start(Message *p_message);
whad_result_t whad_esb_stop(Message *p_message);

/* Notifications */
whad_result_t whad_esb_jammed(Message *p_message, uint32_t timestamp);
whad_result_t whad_esb_jammed_parse(Message *p_message, uint32_t *p_timestamp);
whad_result_t whad_esb_raw_pdu_received(Message *p_message, whad_esb_recvd_packet_t *p_pdu);
whad_result_t whad_esb_raw_pdu_received_parse(Message *p_message, whad_esb_recvd_packet_t *p_pdu);
whad_result_t whad_esb_pdu_received(Message *p_message, whad_esb_recvd_packet_t *p_pdu);
whad_result_t whad_esb_pdu_received_parse(Message *p_message, whad_esb_recvd_packet_t *p_pdu);

#ifdef __cplusplus
}
#endif

#endif /* __INC_WHAD_ESB_H */