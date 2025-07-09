#ifndef __INC_WHAD_ANT_H
#define __INC_WHAD_ANT_H

#include "types.h"

#define ANT_PACKET_MAX_SIZE     255
#define ANT_NETWORK_KEY_SIZE    8

#ifdef __cplusplus
extern "C" {
#endif

/*********************************
 * ANT domain
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
    WHAD_ANT_UNKNOWN=0,
    WHAD_ANT_SET_DEVICE_NUMBER=ant_Message_set_device_number_tag,
    WHAD_ANT_SET_DEVICE_TYPE=ant_Message_set_device_type_tag,
    WHAD_ANT_SET_TRANSMISSION_TYPE=ant_Message_set_transmission_type_tag,
    WHAD_ANT_SET_CHANNEL_PERIOD=ant_Message_set_channel_period_tag,
    WHAD_ANT_SET_NETWORK_KEY=ant_Message_set_network_key_tag,
    WHAD_ANT_ASSIGN_CHANNEL=ant_Message_assign_channel_tag,
    WHAD_ANT_UNASSIGN_CHANNEL=ant_Message_unassign_channel_tag,
    WHAD_ANT_OPEN_CHANNEL=ant_Message_open_channel_tag,
    WHAD_ANT_CLOSE_CHANNEL=ant_Message_close_channel_tag,
    WHAD_ANT_SET_RF_CHANNEL=ant_Message_set_rf_channel_tag,
    WHAD_ANT_SNIFF=ant_Message_sniff_tag,
    WHAD_ANT_JAM=ant_Message_jam_tag,
    WHAD_ANT_SEND=ant_Message_send_tag,
    WHAD_ANT_SEND_RAW=ant_Message_send_raw_tag,
    WHAD_ANT_MASTER_MODE=ant_Message_master_mode_tag,
    WHAD_ANT_SLAVE_MODE=ant_Message_slave_mode_tag,
    WHAD_ANT_START=ant_Message_start_tag,
    WHAD_ANT_STOP=ant_Message_stop_tag,
    WHAD_ANT_LIST_CHANNELS=ant_Message_list_channels_tag,
    WHAD_ANT_LIST_NETWORKS=ant_Message_list_networks_tag,
    WHAD_ANT_JAMMED=ant_Message_jammed_tag,
    WHAD_ANT_RAW_PDU_RECEIVED=ant_Message_raw_pdu_tag,
    WHAD_ANT_PDU_RECEIVED=ant_Message_pdu_tag, 
    WHAD_ANT_AVAILABLE_CHANNELS=ant_Message_available_channels_tag,
    WHAD_ANT_AVAILABLE_NETWORKS=ant_Message_available_networks_tag, 

} whad_ant_msgtype_t;


typedef enum {
    ANT_CHANNEL_TYPE_BIDIRECTIONAL_RECEIVE_CHANNEL = ant_AntChannelType_BIDIRECTIONAL_RECEIVE_CHANNEL, 
    ANT_CHANNEL_TYPE_BIDIRECTIONAL_TRANSMIT_CHANNEL = ant_AntChannelType_BIDIRECTIONAL_TRANSMIT_CHANNEL, 
    ANT_CHANNEL_TYPE_SHARED_BIDIRECTIONAL_RECEIVE_CHANNEL = ant_AntChannelType_SHARED_BIDIRECTIONAL_RECEIVE_CHANNEL, 
    ANT_CHANNEL_TYPE_SHARED_BIDIRECTIONAL_TRANSMIT_CHANNEL = ant_AntChannelType_SHARED_BIDIRECTIONAL_TRANSMIT_CHANNEL,  
    ANT_CHANNEL_TYPE_RECEIVE_ONLY_CHANNEL = ant_AntChannelType_RECEIVE_ONLY_CHANNEL,
    ANT_CHANNEL_TYPE_TRANSMIT_ONLY_CHANNEL = ant_AntChannelType_TRANSMIT_ONLY_CHANNEL
} whad_ant_channel_type_t;

/**
 * ANT packet structure 
 **/

typedef struct {
    uint8_t bytes[ANT_PACKET_MAX_SIZE];
    uint8_t length;
} whad_ant_packet_t;


/**
 * ANT AssignChannelCmd parameters 
 **/

typedef struct {
    uint32_t channel_number;
    uint32_t network_number;
    whad_ant_channel_type_t channel_type;

    bool has_background_scanning;
    bool background_scanning;

    bool has_frequency_agility;
    bool frequency_agility;

    bool has_fast_channel_initiation;
    bool fast_channel_initiation;

    bool has_asynchronous_transmission;
    bool asynchronous_transmission;

} whad_ant_assign_channel_params_t;

/**
 * ANT SniffCmd parameters 
 **/

typedef struct {
    uint32_t rf_channel;
    uint8_t network_key[ANT_NETWORK_KEY_SIZE];
    uint16_t device_number;
    uint16_t device_type;
    uint8_t transmission_type;
} whad_ant_sniff_params_t;


/**
 * ESB SendCmd parameters 
 **/

typedef struct {
    uint32_t rf_channel;
    uint32_t channel_number;
    whad_ant_packet_t packet;
} whad_ant_send_params_t;

/**
 * ESB PduReceived and RawPduReceived parameters 
 **/

typedef struct {
    uint32_t channel_number;
    bool has_rssi;
    int32_t rssi;
    bool has_timestamp;
    uint32_t timestamp;
    bool has_crc_validity;
    bool crc_validity;
    whad_ant_packet_t packet;
    uint32_t rf_channel;
} whad_ant_recvd_packet_t;

/* Get ANT message type from NanoPb message. */
whad_ant_msgtype_t whad_ant_get_message_type(Message *p_message);

/**
 * WHAD ANT messages creation and parsing.
 */

whad_result_t whad_ant_set_device_number(Message *p_message, uint32_t channel_number, uint32_t device_number);
whad_result_t whad_ant_set_device_number_parse(Message *p_message, uint32_t *p_channel_number, uint32_t *p_device_number);
whad_result_t whad_ant_set_device_type(Message *p_message, uint32_t channel_number, uint32_t device_type);
whad_result_t whad_ant_set_device_type_parse(Message *p_message, uint32_t *p_channel_number, uint32_t *p_device_type);
whad_result_t whad_ant_set_transmission_type(Message *p_message, uint32_t channel_number, uint32_t transmission_type);
whad_result_t whad_ant_set_transmission_type_parse(Message *p_message, uint32_t *p_channel_number, uint32_t *p_transmission_type);
whad_result_t whad_ant_set_channel_period(Message *p_message, uint32_t channel_number, uint32_t channel_period);
whad_result_t whad_ant_set_channel_period_parse(Message *p_message, uint32_t *p_channel_number, uint32_t *p_channel_period);
whad_result_t whad_ant_set_network_key(Message *p_message, uint32_t network_number, uint8_t *p_network_key);
whad_result_t whad_ant_set_network_key_parse(Message *p_message, uint32_t *p_network_number, uint8_t *p_network_key);
whad_result_t whad_ant_assign_channel(
    Message *p_message, uint32_t channel_number, uint32_t network_number, whad_ant_channel_type_t channel_type, 
    bool background_scanning, bool frequency_agility, bool fast_channel_initiation, bool asynchronous_transmission
);
whad_result_t whad_ant_assign_channel_parse(Message *p_message, whad_ant_assign_channel_params_t *p_params);
whad_result_t whad_ant_unassign_channel(Message *p_message, uint32_t channel_number);
whad_result_t whad_ant_unassign_channel_parse(Message *p_message, uint32_t *p_channel_number);
whad_result_t whad_ant_open_channel(Message *p_message, uint32_t channel_number);
whad_result_t whad_ant_open_channel_parse(Message *p_message, uint32_t *p_channel_number);
whad_result_t whad_ant_close_channel(Message *p_message, uint32_t channel_number);
whad_result_t whad_ant_close_channel_parse(Message *p_message, uint32_t *p_channel_number);
whad_result_t whad_ant_set_rf_channel(Message *p_message, uint32_t channel_number, uint32_t rf_channel);
whad_result_t whad_ant_set_rf_channel_parse(Message *p_message, uint32_t *p_channel_number, uint32_t *p_rf_channel);
whad_result_t whad_ant_sniff(
    Message *p_message, uint32_t rf_channel, uint8_t *network_key, uint32_t device_number, uint32_t device_type, 
    uint32_t transmission_type
);
whad_result_t whad_ant_sniff_parse(Message *p_message, whad_ant_sniff_params_t *p_params);
whad_result_t whad_ant_jam(Message *p_message, uint32_t rf_channel);
whad_result_t whad_ant_jam_parse(Message *p_message, uint32_t *p_rf_channel);
whad_result_t whad_ant_send(Message *p_message, uint32_t rf_channel, uint32_t channel_number, uint8_t *p_packet, size_t packet_len);
whad_result_t whad_ant_send_parse(Message *p_message, whad_ant_send_params_t* p_params);
whad_result_t whad_ant_send_raw(Message *p_message, uint32_t rf_channel, uint32_t channel_number, uint8_t *p_packet, size_t packet_len);
whad_result_t whad_ant_send_raw_parse(Message *p_message, whad_ant_send_params_t* p_params);
whad_result_t whad_ant_master_mode(Message *p_message, uint32_t channel_number);
whad_result_t whad_ant_master_mode_parse(Message *p_message, uint32_t *p_channel_number);
whad_result_t whad_ant_slave_mode(Message *p_message, uint32_t channel_number);
whad_result_t whad_ant_slave_mode_parse(Message *p_message, uint32_t *p_channel_number);
whad_result_t whad_ant_start(Message *p_message);
whad_result_t whad_ant_stop(Message *p_message);
whad_result_t whad_ant_list_channels(Message *p_message);
whad_result_t whad_ant_list_networks(Message *p_message);

/* Notifications */
whad_result_t whad_ant_jammed(Message *p_message, uint32_t timestamp);
whad_result_t whad_ant_jammed_parse(Message *p_message, uint32_t *p_timestamp);
whad_result_t whad_ant_available_channels(Message *p_message, uint32_t number_of_channels);
whad_result_t whad_ant_available_channels_parse(Message *p_message, uint32_t *p_number_of_channels);
whad_result_t whad_ant_available_networks(Message *p_message, uint32_t number_of_networks);
whad_result_t whad_ant_available_networks_parse(Message *p_message, uint32_t *p_number_of_networks);
whad_result_t whad_ant_raw_pdu_received(Message *p_message, whad_ant_recvd_packet_t *p_pdu, uint32_t crc);
whad_result_t whad_ant_raw_pdu_received_parse(Message *p_message, whad_ant_recvd_packet_t *p_pdu,  uint32_t *p_crc);
whad_result_t whad_ant_pdu_received(Message *p_message, whad_ant_recvd_packet_t *p_pdu);
whad_result_t whad_ant_pdu_received_parse(Message *p_message, whad_ant_recvd_packet_t *p_pdu);


#ifdef __cplusplus
}
#endif

#endif /* __INC_WHAD_ANT_H */