#ifndef __INC_WHAD_DOT15D4_H
#define __INC_WHAD_DOT15D4_H

#include "types.h"

#define DOT15D4_PACKET_MAX_SIZE  (255)

#ifdef __cplusplus
extern "C" {
#endif

/*********************************
 * Zigbee domain
 ********************************/

typedef enum {
    WHAD_DOT15D4_UNKNOWN=0,
    WHAD_DOT15D4_SET_NODE_ADDRESS=dot15d4_Message_set_node_addr_tag,
    WHAD_DOT15D4_SNIFF=dot15d4_Message_sniff_tag,
    WHAD_DOT15D4_JAM=dot15d4_Message_jam_tag,
    WHAD_DOT15D4_NRG_DETECTION=dot15d4_Message_ed_tag,
    WHAD_DOT15D4_SEND=dot15d4_Message_send_tag,
    WHAD_DOT15D4_SEND_RAW=dot15d4_Message_send_raw_tag,
    WHAD_DOT15D4_END_DEVICE_MODE=dot15d4_Message_end_device_tag,
    WHAD_DOT15D4_ROUTER_MODE=dot15d4_Message_router_tag,
    WHAD_DOT15D4_COORD_MODE=dot15d4_Message_coordinator_tag,
    WHAD_DOT15D4_START=dot15d4_Message_start_tag,
    WHAD_DOT15D4_STOP=dot15d4_Message_stop_tag,
    WHAD_DOT15D4_MITM_MODE=dot15d4_Message_mitm_tag,
    WHAD_DOT15D4_HOPPING_CMD = dot15d4_Message_hopping_tag,
    WHAD_DOT15D4_ADD_LINKS_CMD = dot15d4_Message_addLinks_tag,
    WHAD_DOT15D4_DELETE_LINK_CMD = dot15d4_Message_deleteLink_tag,
    WHAD_DOT15D4_WRITE_MODIFY_SUPERFRAME_CMD = dot15d4_Message_writeModifySuperframeCmd_tag,
    WHAD_DOT15D4_DELETE_SUPERFRAME_CMD = dot15d4_Message_deleteSuperframeCmd_tag,
    WHAD_DOT15D4_CHANNEL_MAP_CMD = dot15d4_Message_channelMap_tag,
    WHAD_DOT15D4_JAMMED=dot15d4_Message_jammed_tag,
    WHAD_DOT15D4_DISCOVERED_COMMUNICATION=dot15d4_Message_discovered_communication_tag,
    WHAD_DOT15D4_NRG_DETECTION_SAMPLE=dot15d4_Message_ed_sample_tag,
    WHAD_DOT15D4_RAW_PDU_RECEIVED=dot15d4_Message_raw_pdu_tag,
    WHAD_DOT15D4_PDU_RECEIVED=dot15d4_Message_pdu_tag,
    WHAD_DOT15D4_SEND_IN_SLOT=dot15d4_Message_send_in_slot_tag
} whad_dot15d4_msgtype_t;

typedef enum {
    WHAD_DOT15D4_ADDR_SHORT=dot15d4_AddressType_SHORT,
    WHAD_DOT15D4_ADDR_EXTENDED=dot15d4_AddressType_EXTENDED
} whad_dot15d4_addr_type_t;

typedef enum {
    WHAD_DOT15D4_MITM_REACTIVE=dot15d4_Dot15d4MitmRole_REACTIVE_JAMMER,
    WHAD_DOT15D4_MITM_CORRECTOR=dot15d4_Dot15d4MitmRole_CORRECTOR
} whad_dot15d4_mitm_role_t;

typedef struct {
    whad_dot15d4_addr_type_t type;
    uint64_t address;
} whad_dot15d4_address_t;

typedef struct {
    uint8_t bytes[DOT15D4_PACKET_MAX_SIZE];
    int length;
} whad_dot15d4_packet_t;

typedef struct {
    uint32_t channel;
    whad_dot15d4_packet_t packet;
    uint32_t fcs;
} whad_dot15d4_send_params_t;

typedef struct {
    uint64_t slot;
    uint64_t wait_offset;
    whad_dot15d4_packet_t packet;
} whad_dot15d4_send_in_slot_params_t;

typedef struct {
    uint32_t timestamp;
    uint32_t sample;
} whad_dot15d4_ed_sample_t;

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
    whad_dot15d4_packet_t packet;
} whad_dot15d4_recvd_packet_t;

/**
 * Link configuration 
 */
typedef struct whad_dot15d4_link_t whad_dot15d4_link_t;

struct whad_dot15d4_link_t{
    uint16_t src;
    uint16_t join_slot;
    uint8_t offset;
    uint16_t neighbor;
    uint8_t options;
    uint8_t type;
    whad_dot15d4_link_t* next;
};

/**
 * Links chained list
 */
typedef struct{
    uint8_t nb_links;
    whad_dot15d4_link_t* first;
} whad_dot15d4_chained_link_list_t;


/**
 * Superframe configuration
 */
typedef struct {
    uint8_t id;
    uint16_t size;
    uint8_t flags;
    whad_dot15d4_chained_link_list_t* links;
} whad_dot15d4_superframe_t;

/**
 * Superframes stucture
 */
typedef struct whad_dot15d4_superframes_t whad_dot15d4_superframes_t;

struct whad_dot15d4_superframes_t{
    whad_dot15d4_superframe_t *superframe;
    whad_dot15d4_superframes_t *next;
};

typedef struct {
    uint32_t superframeId;
    uint32_t numberOfSlots;
    uint32_t flags;
    bool has_asn;
    uint64_t asn;
} whad_dot15d4_write_modify_superframes_packet_t;

whad_dot15d4_msgtype_t whad_dot15d4_get_message_type(Message *p_message);


whad_result_t whad_dot15d4_set_node_address(Message *p_message, whad_dot15d4_address_t *p_addr);
whad_result_t whad_dot15d4_set_node_address_parse(Message *p_message, whad_dot15d4_address_t *p_addr);
whad_result_t whad_dot15d4_sniff(Message *p_message, uint32_t channel);
whad_result_t whad_dot15d4_sniff_parse(Message *p_message, uint32_t *p_channel);
whad_result_t whad_dot15d4_jam(Message *p_message, uint32_t channel);
whad_result_t whad_dot15d4_jam_parse(Message *p_message, uint32_t *p_channel);
whad_result_t whad_dot15d4_energy_detect(Message *p_message, uint32_t channel);
whad_result_t whad_dot15d4_energy_detect_parse(Message *p_message, uint32_t *p_channel);
whad_result_t whad_dot15d4_send(Message *p_message, uint32_t channel, uint8_t *p_packet, int length);
whad_result_t whad_dot15d4_send_parse(Message *p_message, whad_dot15d4_send_params_t *p_params);
whad_result_t whad_dot15d4_send_raw(Message *p_message, uint32_t channel, uint8_t *p_packet, int length, uint32_t fcs);
whad_result_t whad_dot15d4_send_raw_parse(Message *p_message, whad_dot15d4_send_params_t *p_params);
whad_result_t whad_dot15d4_send_in_slot(Message *p_message, uint64_t slot, uint64_t wait_offset, uint8_t *p_packet, int length);
whad_result_t whad_dot15d4_send_in_slot_parse(Message *p_message, whad_dot15d4_send_in_slot_params_t *p_params);

whad_result_t whad_dot15d4_end_device_mode(Message *p_message, uint32_t channel);
whad_result_t whad_dot15d4_end_device_mode_parse(Message *p_message, uint32_t *p_channel);
whad_result_t whad_dot15d4_router_mode(Message *p_message, uint32_t channel);
whad_result_t whad_dot15d4_router_mode_parse(Message *p_message, uint32_t *p_channel);
whad_result_t whad_dot15d4_coord_mode(Message *p_message, uint32_t channel);
whad_result_t whad_dot15d4_coord_mode_parse(Message *p_message, uint32_t *p_channel);
whad_result_t whad_dot15d4_mitm_mode(Message *p_message, whad_dot15d4_mitm_role_t role);
whad_result_t whad_dot15d4_mitm_mode_parse(Message *p_message, whad_dot15d4_mitm_role_t *p_role);

whad_result_t whad_dot15d4_start(Message *p_message);
whad_result_t whad_dot15d4_stop(Message *p_message);

whad_result_t whad_dot15d4_jammed(Message *p_message, uint32_t timestamp);
whad_result_t whad_dot15d4_jammed_parse(Message *p_message, uint32_t *p_timestamp);
whad_result_t whad_dot15d4_energy_detect_sample(Message *p_message, uint32_t timestamp,
                                               uint32_t sample);
whad_result_t whad_dot15d4_energy_detect_sample_parse(Message *p_message, whad_dot15d4_ed_sample_t *p_sample);
whad_result_t whad_dot15d4_raw_pdu_received(Message *p_message, whad_dot15d4_recvd_packet_t *p_packet);
whad_result_t whad_dot15d4_raw_pdu_received_parse(Message *p_message, whad_dot15d4_recvd_packet_t *p_packet);
whad_result_t whad_dot15d4_pdu_received(Message *p_message, whad_dot15d4_recvd_packet_t *p_packet);
whad_result_t whad_dot15d4_pdu_received_parse(Message *p_message, whad_dot15d4_recvd_packet_t *p_packet);

whad_result_t whad_dot15d4_enable_hopping(Message *p_message, bool* hopping);
whad_result_t whad_dot15d4_add_links(Message *p_message, whad_dot15d4_superframes_t *superframes);
whad_result_t whad_dot15d4_delete_link(Message *p_message, whad_dot15d4_superframes_t *superframes);
whad_result_t whad_dot15d4_channel_map(Message *p_message, uint16_t* channel_map);
whad_result_t whad_dot15d4_write_modify_superframe(Message *p_message, whad_dot15d4_write_modify_superframes_packet_t *p_packet);
whad_dot15d4_superframe_t *whad_dot15d4_get_superframe(whad_dot15d4_superframes_t *superframes, uint8_t id);
whad_dot15d4_link_t *whad_dot15d4_get_link_from_sf(whad_dot15d4_superframe_t *sf, uint16_t join_slot);
whad_result_t whad_dot15d4_modify_superframe(whad_dot15d4_superframe_t *superframe, whad_dot15d4_write_modify_superframes_packet_t *pkt);
whad_result_t whad_dot15d4_add_superframe(whad_dot15d4_superframes_t *superframes, whad_dot15d4_write_modify_superframes_packet_t *pkt);
whad_result_t whad_dot15d4_delete_superframe(Message *p_message, whad_dot15d4_superframes_t **superframes);

whad_result_t whad_dot15d4_discovered_communication(Message *p_message, uint8_t* pkt, size_t size, uint16_t slot, uint16_t offset);

#ifdef __cplusplus
}
#endif

#endif /* __INC_WHAD_DOT15D4_H */