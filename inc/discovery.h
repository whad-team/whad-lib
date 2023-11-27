#ifndef __INC_DISCOVERY_H
#define __INC_DISCOVERY_H

#include "types.h"
#include "../nanopb/pb_encode.h"
#include "../nanopb/pb_decode.h"
#include "../protocol/whad.pb.h"

#define BAUDRATE_MAX 921600

#ifdef __cplusplus
extern "C" {
#endif

/*********************************
 * Discovery
 ********************************/
typedef enum {
    DOMAIN_NONE = discovery_Domain__DomainNone,
    DOMAIN_PHY = discovery_Domain_Phy,
    DOMAIN_BT_CLASSIC = discovery_Domain_BtClassic,
    DOMAIN_BTLE = discovery_Domain_BtLE,
    DOMAIN_ZIGBEE = discovery_Domain_Zigbee,
    DOMAIN_SIXLOWPAN = discovery_Domain_SixLowPan,
    DOMAIN_ESB = discovery_Domain_Esb,
    DOMAIN_LOGITECH_UNIFYING = discovery_Domain_LogitechUnifying,
    DOMAIN_MOSART = discovery_Domain_Mosart,
    DOMAIN_ANT = discovery_Domain_ANT,
    DOMAIN_ANT_PLUS = discovery_Domain_ANT_Plus,
    DOMAIN_ANT_FS = discovery_Domain_ANT_FS,
} whad_domain_t;

typedef enum {
    CAP_NONE = discovery_Capability__CapNone,
    CAP_SCAN = discovery_Capability_Scan,
    CAP_SNIFF = discovery_Capability_Sniff,
    CAP_INJECT = discovery_Capability_Inject,
    CAP_JAM = discovery_Capability_Jam,
    CAP_HIJACK = discovery_Capability_Hijack,
    CAP_HOOK = discovery_Capability_Hook,
    CAP_SIMULATE_ROLE = discovery_Capability_SimulateRole,
    CAP_NO_RAW_DATA = discovery_Capability_NoRawData
} whad_capability_t;

typedef enum {
    WHAD_DISCOVERY_UNKNOWN=0,
    WHAD_DISCOVERY_DEVICE_INFO_QUERY=discovery_Message_info_query_tag,
    WHAD_DISCOVERY_DEVICE_INFO_RESP=discovery_Message_info_resp_tag,
    WHAD_DISCOVERY_DEVICE_RESET=discovery_Message_reset_query_tag,
    WHAD_DISCOVERY_READY_RESP=discovery_Message_ready_resp_tag,
    WHAD_DISCOVERY_DOMAIN_INFO_QUERY=discovery_Message_domain_query_tag,
    WHAD_DISCOVERY_DOMAIN_INFO_RESP=discovery_Message_domain_resp_tag,
    WHAD_DISCOVERY_SET_SPEED=discovery_Message_set_speed_tag
} whad_discovery_msgtype_t;

typedef struct {
    whad_domain_t domain;
    whad_capability_t cap;
    uint64_t supported_commands;
} whad_domain_desc_t;

/* Get discovery message type from NanoPb message. */
whad_discovery_msgtype_t whad_discovery_get_message_type(Message *p_message);

/* Create/parse a device info query. */
whad_result_t whad_discovery_device_info_query(Message *p_message, uint32_t proto_version);
whad_result_t whad_discovery_device_info_query_parse(Message *p_message, uint32_t *p_proto_version);

/* Create/parse a domain info query. */
whad_result_t whad_discovery_domain_info_query(Message *p_message, whad_domain_t domain);
whad_result_t whad_discovery_domain_info_query_parse(Message *p_message, whad_domain_t *p_domain);

/* Create a device info response. */
whad_result_t whad_discovery_device_info_resp(
    Message *p_message,
    discovery_DeviceType device_type,
    uint8_t *devid,
    uint32_t proto_min_ver,
    uint32_t max_speed,
    char *fw_author,
    char *fw_url,
    uint32_t fw_version_major,
    uint32_t fw_version_minor,
    uint32_t fw_version_rev,
    whad_domain_desc_t *capabilities);

/* Create/parse a domain info response. */
whad_result_t whad_discovery_domain_info_resp(Message *p_message, whad_domain_t domain, whad_domain_desc_t *p_capabilities);
whad_result_t whad_discovery_domain_info_resp_parse(Message *p_message, whad_domain_t *p_domain,
                                                    uint64_t *p_supp_commands);

/* Create a device reset query. */
whad_result_t whad_discovery_device_reset(Message *p_message);

/* Create a device ready response. */
whad_result_t whad_discovery_ready_resp(Message *p_message);

/* Create/parse a transport speed selection message. */
whad_result_t whad_discovery_set_speed(Message *p_message, uint32_t speed);
whad_result_t whad_discovery_set_speed_parse(Message *p_message, uint32_t *p_speed);

#ifdef __cplusplus
}
#endif

#endif /* __INC_DISCOVERY_H */
