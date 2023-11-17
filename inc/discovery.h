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
    DOMAIN_ANT_FS = discovery_Domain_ANT_FS
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

typedef struct {
    whad_domain_t domain;
    whad_capability_t cap;
    uint64_t supported_commands;
} whad_domain_desc_t;

whad_result_t whad_discovery_device_info_query(Message *p_message, uint32_t proto_version);
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
whad_result_t whad_discovery_domain_info_query(Message *p_message, whad_domain_t domain);
whad_result_t whad_discovery_domain_info_resp(Message *p_message, whad_domain_t domain, whad_domain_desc_t *p_capabilities);
whad_result_t whad_discovery_device_reset(Message *p_message);
whad_result_t whad_discovery_ready_resp(Message *p_message);


#ifdef __cplusplus
}
#endif

#endif /* __INC_DISCOVERY_H */
