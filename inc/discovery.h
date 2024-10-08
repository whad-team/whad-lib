#ifndef __INC_DISCOVERY_H
#define __INC_DISCOVERY_H

#include "types.h"
#include "../nanopb/pb_encode.h"
#include "../nanopb/pb_decode.h"

#define BAUDRATE_MAX 921600

#ifdef __cplusplus
extern "C" {
#endif

/*********************************
 * Discovery
 ********************************/
typedef enum {
    DOMAIN_NONE = discovery_Domain__DomainNone, /*!< Domain is unknown*/
    DOMAIN_PHY = discovery_Domain_Phy, /*!< PHY domain*/
    DOMAIN_BT_CLASSIC = discovery_Domain_BtClassic, /*!< Bluetooth Classic domain*/
    DOMAIN_BTLE = discovery_Domain_BtLE, /*!< Bluetooth Low Energy domain*/
    DOMAIN_DOT15D4 = discovery_Domain_Dot15d4, /*!< IEEE802.15.4 domain*/
    DOMAIN_SIXLOWPAN = discovery_Domain_SixLowPan, /*!< 6LowPAN domain*/
    DOMAIN_ESB = discovery_Domain_Esb, /*!< Enhanced ShockBurst domain*/
    DOMAIN_LOGITECH_UNIFYING = discovery_Domain_LogitechUnifying, /*!< Logitech Unifying domain*/
    DOMAIN_MOSART = discovery_Domain_Mosart, /*!< Mosart domain*/
    DOMAIN_ANT = discovery_Domain_ANT, /*!< ANT domain*/
    DOMAIN_ANT_PLUS = discovery_Domain_ANT_Plus, /*!< ANT+ domain*/
    DOMAIN_ANT_FS = discovery_Domain_ANT_FS, /*!< ANT FS domain*/
} whad_domain_t;

/* Device capabilities (pre-protocol) */
typedef enum {
    CAP_NONE = discovery_Capability__CapNone, /*!< No capability*/
    CAP_SCAN = discovery_Capability_Scan, /*!< Can scan other devices */
    CAP_SNIFF = discovery_Capability_Sniff, /*!< Can sniff packets/data */
    CAP_INJECT = discovery_Capability_Inject, /*!< Can inject packets/data */
    CAP_JAM = discovery_Capability_Jam, /*!< Can jam */
    CAP_HIJACK = discovery_Capability_Hijack, /*!< Can hijack connection */
    CAP_HOOK = discovery_Capability_Hook, /*!< Can hook connection */
    CAP_SIMULATE_ROLE = discovery_Capability_SimulateRole, /*!< Can simulate a role */
    CAP_NO_RAW_DATA = discovery_Capability_NoRawData /*!< Cannot access raw data */
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

/* Determine if a given domain is supported. */
bool whad_discovery_is_domain_supported(const whad_domain_desc_t *p_capabilities, whad_domain_t domain);

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
