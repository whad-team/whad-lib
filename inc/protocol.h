#ifndef INC_WHAD_PROTOCOL_H
#define INC_WHAD_PROTOCOL_H

#include "types.h"
#include "../nanopb/pb_encode.h"
#include "../nanopb/pb_decode.h"
#include "../protocol/whad.pb.h"


//460800
#define BAUDRATE_MAX 921600
//#define BAUDRATE_MAX 115200

#ifdef __cplusplus
extern "C" {
#endif

/*********************************
 * Generic messages
 ********************************/

typedef enum {
    WHAD_RESULT_SUCCESS = 0, 
    WHAD_RESULT_ERROR = 1, 
    WHAD_RESULT_PARAMETER_ERROR = 2, 
    WHAD_RESULT_DISCONNECTED = 3, 
    WHAD_RESULT_WRONG_MODE = 4, 
    WHAD_RESULT_UNSUPPORTED_DOMAIN = 5, 
    WHAD_RESULT_BUSY = 6 
} whad_result_code_t;

/* Populate a generic command result message. */
whad_result_t whad_generic_cmd_result(Message *p_message, whad_result_code_t result);

/* Populate a generic verbose message. */
whad_result_t whad_generic_verbose_message(Message *p_message, char *psz_message);

/* Populate a debug message. */
whad_result_t whad_generic_debug_message(Message *p_message, uint32_t level, char *psz_message);

/* Populate a progress message. */
whad_result_t whad_generic_progress_message(Message *p_message, uint32_t value);

/* Verbose message helper. */
whad_result_t whad_verbose(char *psz_message);

/*********************************
 * Discovery
 ********************************/

typedef struct {
    discovery_Domain domain;
    discovery_Capability cap;
} WhadDeviceCapability;

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
    WhadDeviceCapability *capabilities);
whad_result_t whad_discovery_domain_info_resp(Message *p_message, discovery_Domain domain, uint64_t supported_commands); 
whad_result_t whad_discovery_ready_resp(Message *p_message);

/*********************************
 * Bluetooth Low Energy domain
 ********************************/

typedef struct {
    int rssi;
    ble_BleAdvType adv_type;
    uint8_t bd_addr[6];
    uint8_t addr_type;
    uint8_t *p_adv_data;
    int adv_data_length;
    uint8_t *p_scan_rsp;
    int scan_rsp_length;
} whad_adv_data_t;

whad_result_t whad_ble_adv_pdu(Message *p_message, whad_adv_data_t *args);
whad_result_t whad_ble_data_pdu(Message *p_message, uint8_t *p_pdu, int length, ble_BleDirection direction);
whad_result_t whad_ble_ll_data_pdu(Message *p_message, uint16_t header, uint8_t *p_pdu, int length,
                          ble_BleDirection direction, int conn_handle, bool processed, bool decrypted);
whad_result_t whad_ble_notify_connected(Message *p_message, uint8_t adv_addr_type, uint8_t *p_adv_addr, uint8_t init_addr_type, uint8_t *p_init_addr, uint32_t conn_handle);
whad_result_t whad_ble_notify_disconnected(Message *p_message, uint32_t conn_handle, uint32_t reason);


/*********************************
 * PHY domain
 ********************************/

whad_result_t whad_phy_supported_frequencies(Message *p_message, phy_SupportedFrequencyRanges_FrequencyRange *p_ranges,
                                             int nb_ranges);
whad_result_t whad_phy_packet_received(Message *p_message, uint32_t frequency, int32_t rssi, uint32_t ts_sec, uint32_t ts_usec,
                              uint8_t *payload, int length);
whad_result_t whad_phy_packet_scheduled(Message *p_message, uint8_t id, bool full);

#ifdef __cplusplus
}
#endif

#endif /* INC_WHAD_PROTOCOL_H */