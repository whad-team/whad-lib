#ifndef INC_WHAD_H
#define INC_WHAD_H

#include "../nanopb/pb_encode.h"
#include "../nanopb/pb_decode.h"
#include "../protocol/whad.pb.h"
#include "ringbuf.h"
#include "transport.h"

//460800
#define BAUDRATE_MAX 921600
//#define BAUDRATE_MAX 115200

typedef enum {
    WHAD_SUCCESS = 0,
    WHAD_ERROR,
    WHAD_RINGBUF_EMPTY,
    WHAD_RINGBUF_FULL
} whad_result_t;

typedef struct {
    discovery_Domain domain;
    discovery_Capability cap;
} DeviceCapability;

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

void whad_init_verbose_message(Message *message, char *psz_message);
void whad_init_error_message(Message *message, generic_ResultCode error);
void whad_discovery_device_info_resp(
    Message *message,
    discovery_DeviceType device_type,
    uint8_t *devid,
    uint32_t proto_min_ver,
    uint32_t max_speed,
    char *fw_author,
    char *fw_url,
    uint32_t fw_version_major,
    uint32_t fw_version_minor,
    uint32_t fw_version_rev,
    DeviceCapability *capabilities);

void whad_discovery_domain_info_resp(
    Message *message, discovery_Domain domain,
    uint64_t supported_commands);

void whad_discovery_ready_resp(Message *message);

void whad_ble_adv_pdu(
    Message *message,
    whad_adv_data_t *args
);
void whad_ble_data_pdu(
    Message *message,
    uint8_t *p_pdu,
    int length,
    ble_BleDirection direction
);

void whad_ble_notify_connected(
    Message *message,
    uint8_t adv_addr_type,
    uint8_t *p_adv_addr,
    uint8_t init_addr_type,
    uint8_t *p_init_addr,
    uint32_t conn_handle
);
void whad_ble_notify_disconnected(Message *message, uint32_t conn_handle, uint32_t reason);

void whad_ble_ll_data_pdu(
    Message *message,
    uint16_t header,
    uint8_t *p_pdu,
    int length,
    ble_BleDirection direction,
    int conn_handle,
    bool processed,
    bool decrypted
);
void whad_generic_cmd_result(
    Message *message,
    generic_ResultCode result
);


/**
 * Exported functions
 */

void whad_init(void);

void whad_generic_cmd_result(
    Message *message,
    generic_ResultCode result
);

bool whad_verbose_msg_encode_cb(pb_ostream_t *ostream, const pb_field_t *field, void * const *arg);
void whad_init_verbose_message(Message *message, char *psz_message);
void whad_init_error_message(Message *message, generic_ResultCode error);
bool whad_disc_enum_capabilities_cb(pb_ostream_t *ostream, const pb_field_t *field, void * const *arg);
void whad_discovery_device_info_resp(
    Message *message,
    discovery_DeviceType device_type,
    uint8_t *devid,
    uint32_t proto_min_ver,
    uint32_t max_speed,
    char *fw_author,
    char *fw_url,
    uint32_t fw_version_major,
    uint32_t fw_version_minor,
    uint32_t fw_version_rev,
    DeviceCapability *capabilities);
void whad_discovery_domain_info_rWHAD_INC_Homain domain,
    uint64_t supported_commands);
void whad_discovery_ready_resp(Message *message);
void whad_ble_adv_pdu(
    Message *message,
    whad_adv_data_t *args
);
void whad_ble_data_pdu(
    Message *message,
    uint8_t *p_pdu,
    int length,
    ble_BleDirection direction
);
void whad_ble_ll_data_pdu(
    Message *message,
    uint16_t header,
    uint8_t *p_pdu,
    int length,
    ble_BleDirection direction,
    int conn_handle,
    bool processed,
    bool decrypted
);
void whad_ble_notify_connected(Message *message, uint8_t adv_addr_type, uint8_t *p_adv_addr, uint8_t init_addr_type, uint8_t *p_init_addr, uint32_t conn_handle);
void whad_ble_notify_disconnected(Message *message, uint32_t conn_handle, uint32_t reason);


#endif /* INC_WHAD_H */