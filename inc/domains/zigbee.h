#ifndef __INC_WHAD_ZIGBEE_H
#define __INC_WHAD_ZIGBEE_H

#include "types.h"

#define ZIGBEE_PACKET_MAX_SIZE  (255)

#ifdef __cplusplus
extern "C" {
#endif

/*********************************
 * Zigbee domain
 ********************************/

typedef enum {
    WHAD_ZIGBEE_UNKNOWN=0,
    WHAD_ZIGBEE_SET_NODE_ADDRESS=zigbee_Message_set_node_addr_tag,
    WHAD_ZIGBEE_SNIFF=zigbee_Message_sniff_tag,
    WHAD_ZIGBEE_JAM=zigbee_Message_jam_tag,
    WHAD_ZIGBEE_NRG_DETECTION=zigbee_Message_ed_tag,
    WHAD_ZIGBEE_SEND=zigbee_Message_send_tag,
    WHAD_ZIGBEE_SEND_RAW=zigbee_Message_send_raw_tag,
    WHAD_ZIGBEE_END_DEVICE_MODE=zigbee_Message_end_device_tag,
    WHAD_ZIGBEE_ROUTER_MODE=zigbee_Message_router_tag,
    WHAD_ZIGBEE_COORD_MODE=zigbee_Message_coordinator_tag,
    WHAD_ZIGBEE_START=zigbee_Message_start_tag,
    WHAD_ZIGBEE_STOP=zigbee_Message_stop_tag,
    WHAD_ZIGBEE_MITM_MODE=zigbee_Message_mitm_tag,
    WHAD_ZIGBEE_JAMMED=zigbee_Message_jammed_tag,
    WHAD_ZIGBEE_NRG_DETECTION_SAMPLE=zigbee_Message_ed_sample_tag,
    WHAD_ZIGBEE_RAW_PDU_RECEIVED=zigbee_Message_raw_pdu_tag,
    WHAD_ZIGBEE_PDU_RECEIVED=zigbee_Message_pdu_tag
} whad_zigbee_msgtype_t;

typedef enum {
    WHAD_ZIGBEE_ADDR_SHORT=zigbee_AddressType_SHORT,
    WHAD_ZIGBEE_ADDR_EXTENDED=zigbee_AddressType_EXTENDED
} whad_zigbee_addr_type_t;

typedef enum {
    WHAD_ZIGBEE_MITM_REACTIVE=zigbee_ZigbeeMitmRole_REACTIVE_JAMMER,
    WHAD_ZIGBEE_MITM_CORRECTOR=zigbee_ZigbeeMitmRole_CORRECTOR
} whad_zigbee_mitm_role_t;

typedef struct {
    whad_zigbee_addr_type_t type;
    uint64_t address;
} whad_zigbee_address_t;

typedef struct {
    uint8_t bytes[ZIGBEE_PACKET_MAX_SIZE];
    int length;
} whad_zigbee_packet_t;

typedef struct {
    uint32_t channel;
    whad_zigbee_packet_t packet;
    uint32_t fcs;
} whad_zigbee_send_params_t;

typedef struct {
    uint32_t timestamp;
    uint32_t sample;
} whad_zigbee_ed_sample_t;

/**
 * Zigbee PduReceived and RawPduReceived parameters 
 **/

typedef struct {
    uint32_t channel;
    bool has_rssi;
    int32_t rssi;
    bool has_timestamp;
    uint32_t timestamp;
    bool has_fcs_validity;
    bool fcs_validity;
    uint32_t fcs;
    bool has_lqi;
    uint32_t lqi;
    whad_zigbee_packet_t packet;
} whad_zigbee_recvd_packet_t;

whad_zigbee_msgtype_t whad_zigbee_get_message_type(Message *p_message);


whad_result_t whad_zigbee_set_node_address(Message *p_message, whad_zigbee_address_t *p_addr);
whad_result_t whad_zigbee_set_node_address_parse(Message *p_message, whad_zigbee_address_t *p_addr);
whad_result_t whad_zigbee_sniff(Message *p_message, uint32_t channel);
whad_result_t whad_zigbee_sniff_parse(Message *p_message, uint32_t *p_channel);
whad_result_t whad_zigbee_jam(Message *p_message, uint32_t channel);
whad_result_t whad_zigbee_jam_parse(Message *p_message, uint32_t *p_channel);
whad_result_t whad_zigbee_energy_detect(Message *p_message, uint32_t channel);
whad_result_t whad_zigbee_energy_detect_parse(Message *p_message, uint32_t *p_channel);
whad_result_t whad_zigbee_send(Message *p_message, uint32_t channel, uint8_t *p_packet, int length);
whad_result_t whad_zigbee_send_parse(Message *p_message, whad_zigbee_send_params_t *p_params);
whad_result_t whad_zigbee_send_raw(Message *p_message, uint32_t channel, uint8_t *p_packet, int length, uint32_t fcs);
whad_result_t whad_zigbee_send_raw_parse(Message *p_message, whad_zigbee_send_params_t *p_params);

whad_result_t whad_zigbee_end_device_mode(Message *p_message, uint32_t channel);
whad_result_t whad_zigbee_end_device_mode_parse(Message *p_message, uint32_t *p_channel);
whad_result_t whad_zigbee_router_mode(Message *p_message, uint32_t channel);
whad_result_t whad_zigbee_router_mode_parse(Message *p_message, uint32_t *p_channel);
whad_result_t whad_zigbee_coord_mode(Message *p_message, uint32_t channel);
whad_result_t whad_zigbee_coord_mode_parse(Message *p_message, uint32_t *p_channel);
whad_result_t whad_zigbee_mitm_mode(Message *p_message, whad_zigbee_mitm_role_t role);
whad_result_t whad_zigbee_mitm_mode_parse(Message *p_message, whad_zigbee_mitm_role_t *p_role);

whad_result_t whad_zigbee_start(Message *p_message);
whad_result_t whad_zigbee_stop(Message *p_message);

whad_result_t whad_zigbee_jammed(Message *p_message, uint32_t timestamp);
whad_result_t whad_zigbee_jammed_parse(Message *p_message, uint32_t *p_timestamp);
whad_result_t whad_zigbee_energy_detect_sample(Message *p_message, uint32_t timestamp,
                                               uint32_t sample);
whad_result_t whad_zigbee_energy_detect_sample_parse(Message *p_message, whad_zigbee_ed_sample_t *p_sample);
whad_result_t whad_zigbee_raw_pdu_received(Message *p_message, whad_zigbee_recvd_packet_t *p_packet);
whad_result_t whad_zigbee_raw_pdu_received_parse(Message *p_message, whad_zigbee_recvd_packet_t *p_packet);
whad_result_t whad_zigbee_pdu_received(Message *p_message, whad_zigbee_recvd_packet_t *p_packet);
whad_result_t whad_zigbee_pdu_received_parse(Message *p_message, whad_zigbee_recvd_packet_t *p_packet);


#ifdef __cplusplus
}
#endif

#endif /* __INC_WHAD_ZIGBEE_H */