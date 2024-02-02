#ifndef __INC_WHAD_UNIFYING_H
#define __INC_WHAD_UNIFYING_H

#include "types.h"

#define UNIFYING_PACKET_MAX_SIZE     255
#define UNIFYING_ADDR_MAX_SIZE       5

#ifdef __cplusplus
extern "C" {
#endif

/*********************************
 * Logitech Unifying domain
 ********************************/

/** @brief  Message types
 * 
 * This enum defines aliases for NanoPb commands bitmask in order to hide
 * the NanoPb implementation.
 * 
 * This structure needs to be updated if a command is added or removed in
 * WHAD protocol.
 **/

typedef enum {
    WHAD_UNIFYING_UNKNOWN=0,
    WHAD_UNIFYING_SET_NODE_ADDR = unifying_Message_set_node_addr_tag,
    WHAD_UNIFYING_SNIFF_MODE = unifying_Message_sniff_tag,
    WHAD_UNIFYING_JAM_MODE = unifying_Message_jam_tag,
    WHAD_UNIFYING_SEND = unifying_Message_send_tag,
    WHAD_UNIFYING_SEND_RAW = unifying_Message_send_raw_tag,
    WHAD_UNIFYING_DONGLE_MODE = unifying_Message_dongle_tag,
    WHAD_UNIFYING_KEYBOARD_MODE = unifying_Message_keyboard_tag,
    WHAD_UNIFYING_MOUSE_MODE = unifying_Message_mouse_tag,
    WHAD_UNIFYING_START = unifying_Message_start_tag,
    WHAD_UNIFYING_STOP = unifying_Message_stop_tag,
    WHAD_UNIFYING_SNIFF_PAIRING = unifying_Message_sniff_pairing_tag,
    WHAD_UNIFYING_JAMMED = unifying_Message_jammed_tag,
    WHAD_UNIFYING_RAW_PDU_RECEIVED = unifying_Message_raw_pdu_tag,
    WHAD_UNIFYING_PDU_RECEIVED = unifying_Message_pdu_tag
} whad_unifying_msgtype_t;

/**
 * Unifying address structure
 **/

typedef struct {
    uint8_t address[UNIFYING_ADDR_MAX_SIZE];
    int size;
} whad_unifying_address_t;

/**
 * Unifying packet structure 
 **/

typedef struct {
    uint8_t bytes[UNIFYING_PACKET_MAX_SIZE];
    uint8_t length;
} whad_unifying_packet_t;


/**
 * Unifying SniffCmd parameters 
 **/

typedef struct {
    whad_unifying_address_t address;
    uint32_t channel;
    bool show_acks;
} whad_unifying_sniff_params_t;

/**
 * Unifying SendCmd parameters 
 **/

typedef struct {
    uint32_t channel;
    uint32_t retr_count;
    whad_unifying_packet_t packet;
} whad_unifying_send_params_t;

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
    whad_unifying_address_t address;
    whad_unifying_packet_t packet;
} whad_unifying_recvd_packet_t;

whad_unifying_msgtype_t whad_unifying_get_message_type(Message *p_message);


whad_result_t whad_unifying_set_node_address(Message *p_message, whad_unifying_address_t *p_addr);
whad_result_t whad_unifying_set_node_address_parse(Message *p_message, whad_unifying_address_t *p_addr);
whad_result_t whad_unifying_sniff(Message *p_message, whad_unifying_address_t *p_addr, uint32_t channel, bool show_ack);
whad_result_t whad_unifying_sniff_parse(Message *p_message, whad_unifying_sniff_params_t *p_params);
whad_result_t whad_unifying_jam(Message *p_message, uint32_t channel);
whad_result_t whad_unifying_jam_parse(Message *p_message, uint32_t *p_channel);
whad_result_t whad_unifying_send(Message *p_message, uint32_t channel, int retr_count,
                            uint8_t *p_packet, uint8_t packet_len);
whad_result_t whad_unifying_send_parse(Message *p_message, whad_unifying_send_params_t *p_params);
whad_result_t whad_unifying_send_raw(Message *p_message, uint32_t channel, int retr_count,
                                uint8_t *p_packet, uint8_t packet_len);
whad_result_t whad_unifying_send_raw_parse(Message *p_message, whad_unifying_send_params_t *p_params);
whad_result_t whad_unifying_dongle_mode(Message *p_message, uint32_t channel);
whad_result_t whad_unifying_dongle_mode_parse(Message *p_message, uint32_t *p_channel);
whad_result_t whad_unifying_keyboard_mode(Message *p_message, uint32_t channel);
whad_result_t whad_unifying_keyboard_mode_parse(Message *p_message, uint32_t *p_channel);
whad_result_t whad_unifying_mouse_mode(Message *p_message, uint32_t channel);
whad_result_t whad_unifying_mouse_mode_parse(Message *p_message, uint32_t *p_channel);
whad_result_t whad_unifying_start(Message *p_message);
whad_result_t whad_unifying_stop(Message *p_message);
whad_result_t whad_unifying_sniff_pairing(Message *p_message);

/* Notifications. */
whad_result_t whad_unifying_jammed(Message *p_message, uint32_t timestamp);
whad_result_t whad_unifying_jammed_parse(Message *p_message, uint32_t *p_timestamp);
whad_result_t whad_unifying_raw_pdu_received(Message *p_message, whad_unifying_recvd_packet_t *p_pdu);
whad_result_t whad_unifying_raw_pdu_received_parse(Message *p_message, whad_unifying_recvd_packet_t *p_pdu);
whad_result_t whad_unifying_pdu_received(Message *p_message, whad_unifying_recvd_packet_t *p_pdu);
whad_result_t whad_unifying_pdu_received_parse(Message *p_message, whad_unifying_recvd_packet_t *p_pdu);



#ifdef __cplusplus
}
#endif

#endif /* __INC_WHAD_UNIFYING_H */