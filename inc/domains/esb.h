#ifndef __INC_WHAD_ESB_H
#define __INC_WHAD_ESB_H

#include "types.h"

#define BLE_PREPSEQ_PACKET_MAX_SIZE     255
#define BLE_PREPSEQ_TRIGGER_MAX_SIZE    255
#define BLE_RSSI_NONE                   (-4096)

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

typedef struct {
    uint8_t address[5];
    int size;
} whad_esb_address_t;

typedef struct {
    whad_esb_address_t address;
    uint32_t channel;
    bool show_acks;
} whad_esb_sniff_params_t;

/* Get ESB message type from NanoPb message. */
whad_esb_msgtype_t whad_esb_get_message_type(Message *p_message);


whad_result_t whad_esb_set_node_address(Message *p_message, whad_esb_address_t *p_addr);
whad_result_t whad_esb_set_node_address_parse(Message *p_message, whad_esb_address_t *p_addr);


#ifdef __cplusplus
}
#endif

#endif /* __INC_WHAD_ESB_H */