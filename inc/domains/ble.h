#ifndef __INC_WHAD_BLE_H
#define __INC_WHAD_BLE_H

#include "types.h"

#define BLE_PREPSEQ_PACKET_MAX_SIZE     255
#define BLE_PREPSEQ_TRIGGER_MAX_SIZE    255
#define BLE_RSSI_NONE                   (-4096)

#ifdef __cplusplus
extern "C" {
#endif

/*********************************
 * Bluetooth Low Energy domain
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
    BLE_SET_BDADDRESS = ble_BleCommand_SetBdAddress,
    BLE_SNIFF_ADV = ble_BleCommand_SniffAdv,
    BLE_JAM_ADV = ble_BleCommand_JamAdv,
    BLE_JAM_ADV_ON_CHANNEL = ble_BleCommand_JamAdvOnChannel,
    BLE_REACTIVE_JAM = ble_BleCommand_ReactiveJam,
    BLE_SNIFF_CONN_REQ = ble_BleCommand_SniffConnReq,
    BLE_SNIFF_ACCESS_ADDRESS = ble_BleCommand_SniffAccessAddress,
    BLE_SNIFF_ACT_CONNECTION = ble_BleCommand_SniffActiveConn,
    BLE_JAM_CONNECTION = ble_BleCommand_JamConn,
    BLE_SCAN_MODE = ble_BleCommand_ScanMode,
    BLE_ADV_MODE = ble_BleCommand_AdvMode,
    BLE_SET_ADV_DATA = ble_BleCommand_SetAdvData,
    BLE_CENTRAL_MODE = ble_BleCommand_CentralMode,
    BLE_CONNECT_TO = ble_BleCommand_ConnectTo,
    BLE_SEND_RAW_PDU = ble_BleCommand_SendRawPDU,
    BLE_SEND_PDU = ble_BleCommand_SendPDU,
    BLE_DISCONNECT = ble_BleCommand_Disconnect,
    BLE_PERIPH_MODE = ble_BleCommand_PeripheralMode,
    BLE_START = ble_BleCommand_Start,
    BLE_STOP = ble_BleCommand_Stop,
    BLE_SET_ENCRYPTION = ble_BleCommand_SetEncryption,
    BLE_HIJACK_MASTER = ble_BleCommand_HijackMaster,
    BLE_HIJACK_SLAVE = ble_BleCommand_HijackSlave,
    BLE_HIJACK_BOTH = ble_BleCommand_HijackBoth,
    BLE_PREPARE_SEQUENCE = ble_BleCommand_PrepareSequence,
    BLE_TRIGGER_SEQUENCE = ble_BleCommand_TriggerSequence,
    BLE_DELETE_SEQUENCE = ble_BleCommand_DeleteSequence
} whad_ble_command_t;

/**
 * @brief Advertising types
 * 
 * This enum defines aliases for NanoPb enums in order to hide the underlying
 * NanoPb implementation.
 */

typedef enum {
    BLE_ADV_UNKNOWN = ble_BleAdvType_ADV_UNKNOWN,
    BLE_ADV_IND = ble_BleAdvType_ADV_IND,
    BLE_ADV_DIRECT_IND = ble_BleAdvType_ADV_DIRECT_IND,
    BLE_ADV_NONCONN_IND = ble_BleAdvType_ADV_NONCONN_IND,
    BLE_ADV_SCAN_IND = ble_BleAdvType_ADV_SCAN_IND,
    BLE_ADV_SCAN_RSP = ble_BleAdvType_ADV_SCAN_RSP
} whad_ble_advtype_t;


/**
 * @brief BLE direction
 * 
 * This enum lists every possible direction that are supported by the WHAD
 * protocol for BLE, including some specific direction used in hijacking.
 * 
 * Again, these are aliases for NanoPb messages.
 */

typedef enum {
    BLE_DIR_UNKNOWN = ble_BleDirection_UNKNOWN,
    BLE_MASTER_TO_SLAVE = ble_BleDirection_MASTER_TO_SLAVE,
    BLE_SLAVE_TO_MASTER = ble_BleDirection_SLAVE_TO_MASTER,
    BLE_INJECTION_TO_SLAVE = ble_BleDirection_INJECTION_TO_SLAVE,
    BLE_INJECTION_TO_MASTER = ble_BleDirection_INJECTION_TO_MASTER
} whad_ble_direction_t;


/**
 * @brief BLE address type
 * 
 * Only two values possible: public or random.
 * 
 * This enum defines aliases for NanoPb messages.
 */

typedef enum {
    BLE_ADDR_PUBLIC = ble_BleAddrType_PUBLIC,
    BLE_ADDR_RANDOM = ble_BleAddrType_RANDOM
} whad_ble_addrtype_t;


typedef enum {
    BLE_PATTERN_TRIGGER,
    BLE_CONNEVT_TRIGGER,
    BLE_MANUAL_TRIGGER
} whad_ble_trigger_t;

/**
 * @brief Advertising data structure
 * 
 * This structure is used to report an advertising PDU and contains the essential information:
 * - the received signal strength indicator (rssi)
 * - the BD address (6-byte array) and the BD address type (random/public)
 * - the received advertising data and associated length
 * - the received scan response data (if in active mode) and associated length
 */
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

typedef struct {
    uint8_t *p_bytes[256];
    int length;
} whad_prepared_packet_t;

typedef enum {
    WHAD_BLE_UNKNOWN=0,
    WHAD_BLE_SET_BDADDRESS=ble_Message_set_bd_addr_tag,
    WHAD_BLE_SET_ADV_DATA=ble_Message_set_adv_data_tag,
    WHAD_BLE_SET_ENCRYPTION=ble_Message_encryption_tag,
    WHAD_BLE_SNIFF_ADV=ble_Message_sniff_adv_tag,
    WHAD_BLE_SNIFF_CONN_REQ=ble_Message_sniff_connreq_tag,
    WHAD_BLE_SNIFF_ACT_CONN=ble_Message_sniff_conn_tag,
    WHAD_BLE_SCAN_MODE=ble_Message_scan_mode_tag,
    WHAD_BLE_ADV_MODE=ble_Message_adv_mode_tag,
    WHAD_BLE_PERIPH_MODE=ble_Message_periph_mode_tag,
    WHAD_BLE_CENTRAL_MODE=ble_Message_central_mode_tag,
    WHAD_BLE_START=ble_Message_start_tag,
    WHAD_BLE_STOP=ble_Message_stop_tag,
    WHAD_BLE_CONNECT_TO=ble_Message_connect_tag,
    WHAD_BLE_SEND_RAW_PDU=ble_Message_send_raw_pdu_tag,
    WHAD_BLE_SEND_PDU=ble_Message_send_pdu_tag,
    WHAD_BLE_DISCONNECT=ble_Message_disconnect_tag,
    WHAD_BLE_PREPARE_SEQ=ble_Message_prepare_tag,
    WHAD_BLE_PREPARE_SEQ_TRIGGER=ble_Message_trigger_tag,
    WHAD_BLE_PREPARE_SEQ_DELETE=ble_Message_delete_seq_tag,
    WHAD_BLE_JAM_ADV=ble_Message_jam_adv_tag,
    WHAD_BLE_JAM_ADV_CHANNEL=ble_Message_jam_adv_chan_tag,
    WHAD_BLE_JAM_ACT_CONN=ble_Message_jam_conn_tag,
    WHAD_BLE_HIJACK_MASTER=ble_Message_hijack_master_tag,
    WHAD_BLE_HIJACK_SLAVE=ble_Message_hijack_slave_tag,
    WHAD_BLE_HIJACK_BOTH=ble_Message_hijack_both_tag,
    WHAD_BLE_REACTIVE_JAM=ble_Message_reactive_jam_tag,
    WHAD_BLE_NOTIFY_CONNECTED=ble_Message_connected_tag,
    WHAD_BLE_NOTIFY_DISCONNECTED=ble_Message_disconnected_tag,
    WHAD_BLE_RAW_PDU=ble_Message_raw_pdu_tag,
    WHAD_BLE_PDU=ble_Message_pdu_tag,
    WHAD_BLE_TRIGGERED=ble_Message_triggered_tag,
    WHAD_BLE_ACCESS_ADDRESS_DISCOVERED=ble_Message_aa_disc_tag,
    WHAD_BLE_ADV_PDU=ble_Message_adv_pdu_tag,
    WHAD_BLE_SYNCHRONIZED=ble_Message_synchronized_tag,
    WHAD_BLE_DESYNCHRONIZED=ble_Message_desynchronized_tag,
    WHAD_BLE_HIJACKED=ble_Message_hijacked_tag,
    WHAD_BLE_INJECTED=ble_Message_injected_tag
} whad_ble_msgtype_t;

/* Get BLE message type from NanoPb message. */
whad_ble_msgtype_t whad_ble_get_message_type(Message *p_message);

/* Set BLE parameters */
whad_result_t whad_ble_set_bdaddress(Message *p_message, whad_ble_addrtype_t addr_type, uint8_t *p_bdaddr);
whad_result_t whad_ble_set_bdaddress_parse(Message *p_message, whad_ble_addrtype_t *p_addr_type, uint8_t *p_bdaddr);

whad_result_t whad_ble_set_adv_data(Message *p_message, uint8_t *p_adv_data, int adv_data_length, 
                                    uint8_t *p_scanrsp_data, int scanrsp_data_length);
whad_result_t whad_ble_set_adv_data_parse(Message *p_message, uint8_t *p_adv_data, int *p_adv_data_length, 
                                    uint8_t *p_scanrsp_data, int *p_scanrsp_data_length);

typedef struct {
    uint32_t conn_handle;
    bool enabled;
    uint8_t *p_ll_key;
    uint8_t *p_ll_iv;
    uint8_t *p_key;
    uint8_t *p_rand;
    uint8_t *p_ediv;
} whad_ble_encryption_params_t;

whad_result_t whad_ble_set_encryption(Message *p_message, uint32_t conn_handle, bool enabled, uint8_t *p_ll_key, uint8_t *p_ll_iv, uint8_t *p_key, uint8_t *p_rand, uint8_t *p_ediv);
whad_result_t whad_ble_set_encryption_parse(Message *p_message, whad_ble_encryption_params_t *p_parameters);

/* Sniffing */
typedef struct {
    bool use_ext_adv;
    uint32_t channel;
    uint8_t *p_bdaddr;
} whad_ble_sniff_adv_params_t;

whad_result_t whad_ble_sniff_adv(Message *p_message, bool use_ext_adv, uint32_t channel, uint8_t *p_bdaddr);
whad_result_t whad_ble_sniff_adv_parse(Message *p_message, whad_ble_sniff_adv_params_t *p_parameters);


typedef struct {
    bool show_empty_packets;
    bool show_adv;
    uint32_t channel;
    uint8_t p_bdaddr[6];
} whad_ble_sniff_connreq_params_t;

whad_result_t whad_ble_sniff_conn_req(Message *p_message, bool show_empty_packets, bool show_adv,
                                      uint32_t channel, uint8_t *p_bdaddr);
whad_result_t whad_ble_sniff_conn_req_parse(Message *p_message, whad_ble_sniff_connreq_params_t *p_parameters);


whad_result_t whad_ble_sniff_access_address(Message *p_message, uint8_t *p_channelmap);
whad_result_t whad_ble_sniff_access_address_parse(Message *p_message, uint8_t *p_channelmap);

typedef struct {
    uint32_t access_address;
    uint32_t crc_init;
    uint32_t hop_interval;
    uint32_t hop_increment;
    uint8_t channelmap[5];
    uint8_t channels[5];
} whad_ble_sniff_conn_params_t;

whad_result_t whad_ble_sniff_active_conn(Message *p_message, uint32_t access_address, uint32_t crc_init,
                                         uint32_t hop_interval, uint32_t hop_increment, uint8_t *p_channelmap,
                                         uint8_t *p_channels);
whad_result_t whad_ble_sniff_active_conn_parse(Message *p_message, whad_ble_sniff_conn_params_t *p_parameters);

/* Set BLE mode */
whad_result_t whad_ble_scan_mode(Message *p_message, bool active_scan);
whad_result_t whad_ble_scan_mode_parse(Message *p_message, bool *p_active_scan);

typedef struct {
    uint8_t adv_data[31];
    uint8_t adv_data_length;
    uint8_t scanrsp_data[31];
    uint8_t scanrsp_data_length;
} whad_ble_adv_mode_params_t;
whad_result_t whad_ble_adv_mode(Message *p_message, uint8_t *p_adv_data, int adv_data_length, uint8_t *p_scanrsp_data, int scanrsp_data_length);
whad_result_t whad_ble_adv_mode_parse(Message *p_message, whad_ble_adv_mode_params_t *p_parameters);


whad_result_t whad_ble_peripheral_mode(Message *p_message, uint8_t *p_adv_data, int adv_data_length, uint8_t *p_scanrsp_data, int scanrsp_data_length);
whad_result_t whad_ble_peripheral_mode_parse(Message *p_message, whad_ble_adv_mode_params_t *p_parameters);

/* No parsing functions for these three messages :) */
whad_result_t whad_ble_central_mode(Message *p_message);
whad_result_t whad_ble_start(Message *p_message);
whad_result_t whad_ble_stop(Message *p_message);

/* BLE connection */
typedef struct {
    uint8_t bdaddr[6];
    whad_ble_addrtype_t addr_type;
    uint32_t access_address;
    uint8_t channelmap[5];
    uint32_t hop_interval;
    uint32_t hop_increment;
    uint32_t crc_init;
} whad_ble_connect_params_t;

whad_result_t whad_ble_connect_to(Message *p_message, uint8_t *p_bdaddr, whad_ble_addrtype_t addr_type, uint32_t access_address, uint8_t *p_channelmap, uint32_t hop_interval, uint32_t hop_increment, uint32_t crc_init);
whad_result_t whad_ble_connect_to_parse(Message *p_message, whad_ble_connect_params_t *p_parameters);

typedef struct {
    whad_ble_direction_t direction;
    uint32_t conn_handle;
    uint32_t access_address;
    uint8_t *p_pdu;
    int length;
    uint32_t crc;
    bool encrypt;
} whad_ble_pdu_params_t;

typedef struct {
    uint32_t conn_handle;
    uint32_t reason;
} whad_ble_disconnected_params_t;

typedef struct {
    uint32_t access_address;
    bool success;
} whad_ble_hijacked_params_t;

whad_result_t whad_ble_send_raw_pdu(Message *p_message, whad_ble_direction_t direction, uint32_t conn_handle,
                                    uint32_t access_address, uint8_t *p_pdu, int length, uint32_t crc, bool encrypt);
whad_result_t whad_ble_send_raw_pdu_parse(Message *p_message, whad_ble_pdu_params_t *p_parameters);
whad_result_t whad_ble_send_pdu(Message *p_message, whad_ble_direction_t direction, uint32_t conn_handle,
                                uint8_t *p_pdu, int length, bool encrypt);
whad_result_t whad_ble_send_pdu_parse(Message *p_message, whad_ble_pdu_params_t *p_parameters);


whad_result_t whad_ble_disconnect(Message *p_message, uint32_t conn_handle);
whad_result_t whad_ble_disconnect_parse(Message *p_message, uint32_t *p_conn_handle);

typedef struct {
    uint8_t *p_bytes;
    unsigned int length;
} whad_prepared_packet_ref_t;

typedef struct {
    uint32_t id;
    uint32_t conn_evt;
    uint8_t *p_pattern;
    uint8_t *p_mask;
    int length;
    int offset;
    whad_ble_direction_t direction;
    whad_prepared_packet_ref_t packets[25];
    unsigned int packet_count;
} whad_ble_prepseq_params_t;

/* Prepared sequences management. */
whad_result_t whad_ble_prepare_sequence_get_trigger_type(Message *p_message, whad_ble_trigger_t *p_trigger_type);
whad_result_t whad_ble_prepare_sequence_on_recv(Message *p_message, uint8_t *p_pattern, uint8_t *p_mask, int length,
                                                int offset, uint32_t id, whad_ble_direction_t direction, whad_prepared_packet_t *p_packets, int pkt_count);
whad_result_t whad_ble_prepare_sequence_conn_evt(Message *p_message, uint32_t connection_event, 
                                               uint32_t id, whad_ble_direction_t direction,
                                               whad_prepared_packet_t *p_packets, int pkt_count);
whad_result_t whad_ble_prepare_sequence_conn_evt_parse(Message *p_message, whad_ble_prepseq_params_t *p_parameters);
whad_result_t whad_ble_prepare_sequence_manual(Message *p_message, uint32_t id, whad_ble_direction_t direction,
                                               whad_prepared_packet_t *p_packets, int pkt_count);
whad_result_t whad_ble_prepare_sequence_manual_parse(Message *p_message, whad_ble_prepseq_params_t *p_parameters);
whad_result_t whad_ble_prepare_sequence_trigger(Message *p_message, uint32_t id);
whad_result_t whad_ble_prepare_sequence_trigger_parse(Message *p_message, uint32_t *p_id);
whad_result_t whad_ble_prepare_sequence_delete(Message *p_message, uint32_t id);

/* Attacks */
whad_result_t whad_ble_jam_adv(Message *p_message);

whad_result_t whad_ble_jam_adv_channel(Message *p_message, uint32_t channel);
whad_result_t whad_ble_jam_adv_channel_parse(Message *p_message, uint32_t *p_channel);

whad_result_t whad_ble_jam_active_conn(Message *p_message, uint32_t access_address);
whad_result_t whad_ble_jam_active_conn_parse(Message *p_message, uint32_t *p_access_address);

whad_result_t whad_ble_hijack_master(Message *p_message, uint32_t access_address);
whad_result_t whad_ble_hijack_master_parse(Message *p_message, uint32_t *p_access_address);

whad_result_t whad_ble_hijack_slave(Message *p_message, uint32_t access_address);
whad_result_t whad_ble_hijack_slave_parse(Message *p_message, uint32_t *p_access_address);

whad_result_t whad_ble_hijack_both(Message *p_message, uint32_t access_address);
whad_result_t whad_ble_hijack_both_parse(Message *p_message, uint32_t *p_access_address);

typedef struct {
    uint32_t channel;
    uint8_t pattern[20];
    int pattern_length;
    uint32_t position;
} whad_ble_reactive_jam_params_t;

typedef struct {
    uint32_t access_address;
    uint32_t attempts;
    bool success;
} whad_ble_injected_params_t;

typedef struct {
    uint32_t conn_handle;
    uint8_t *p_pdu;
    unsigned int pdu_length;
    whad_ble_direction_t direction;
    bool processed;
    bool decrypted;
} whad_ble_pdu_t;

typedef struct {
    whad_ble_advtype_t adv_type;
    int32_t rssi;
    uint8_t *p_bdaddr;
    whad_ble_addrtype_t addr_type;
    uint8_t *p_adv_data;
    int adv_data_length;
} whad_ble_adv_pdu_t;

whad_result_t whad_ble_reactive_jam(Message *p_message, uint32_t channel, uint8_t *p_pattern, int pattern_length, uint32_t position);
whad_result_t whad_ble_reactive_jam_parse(Message *p_message, whad_ble_reactive_jam_params_t *p_parameters);

/* Notifications (Adapter -> Host)*/
whad_result_t whad_ble_notify_connected(Message *p_message, whad_ble_addrtype_t adv_addr_type, uint8_t *p_adv_addr, whad_ble_addrtype_t init_addr_type, uint8_t *p_init_addr, uint32_t conn_handle);
whad_result_t whad_ble_notify_disconnected(Message *p_message, uint32_t conn_handle, uint32_t reason);
whad_result_t whad_ble_notify_disconnected_parse(Message *p_message, whad_ble_disconnected_params_t *p_parameters);
whad_result_t whad_ble_raw_pdu(Message *p_message, uint32_t channel, int32_t rssi, uint32_t conn_handle,
                               uint32_t access_address, uint8_t *p_pdu, int length, uint32_t crc,
                               bool crc_validity, uint32_t timestamp, uint32_t relative_timestamp,
                               whad_ble_direction_t direction, bool processed, bool decrypted, bool use_timestamp);
whad_result_t whad_ble_pdu(Message *p_message, uint8_t *p_pdu, int length, whad_ble_direction_t direction,
                           int conn_handle, bool processed, bool decrypted);
whad_result_t whad_ble_pdu_parse(Message *p_message, whad_ble_pdu_t *p_parameters);
whad_result_t whad_ble_triggered(Message *p_message, uint32_t id);
whad_result_t whad_ble_triggered_parse(Message *p_message, uint32_t *p_id);
whad_result_t whad_ble_access_address_discovered(Message *p_message, uint32_t access_address, uint32_t timestamp, 
                                                 int32_t rssi, bool inc_ts, bool inc_rssi);
whad_result_t whad_ble_adv_pdu(Message *p_message, whad_ble_advtype_t adv_type, int32_t rssi, uint8_t *p_bdaddr,
                               whad_ble_addrtype_t addr_type, uint8_t *p_adv_data, int adv_data_length);
whad_result_t whad_ble_adv_pdu_parse(Message *p_message, whad_ble_adv_pdu_t *p_parameters);
whad_result_t whad_ble_synchronized(Message *p_message, uint32_t access_address, uint32_t crc_init,
                                    uint32_t hop_interval, uint32_t hop_increment, uint8_t *p_channelmap);
whad_result_t whad_ble_desynchronized(Message *p_message, uint32_t access_address);
whad_result_t whad_ble_hijacked(Message *p_message, uint32_t access_address, bool success);
whad_result_t whad_ble_hijacked_parse(Message *p_message, whad_ble_hijacked_params_t *p_parameters);
whad_result_t whad_ble_injected(Message *p_message, uint32_t access_address, uint32_t attempts, bool success);
whad_result_t whad_ble_injected_parse(Message *p_message, whad_ble_injected_params_t *p_parameters);


#ifdef __cplusplus
}
#endif

#endif /* __INC_WHAD_BLE_H */