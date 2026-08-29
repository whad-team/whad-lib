#include <string.h>

#include "test.h"
#include "whad.h"

/**
 * Test ANT channel identity and timing setters.
 * Check device number, device type, transmission type and channel period.
 **/

result_t test_ant_channel_parameters(void)
{
    Message message;
    uint32_t channel;
    uint32_t value;

    /* Round-trip each two-value channel configuration. */
    memset(&message, 0, sizeof(message));
    assert_success(whad_ant_set_device_number(&message, 1, 0x1234));
    assert_success(whad_ant_set_device_number_parse(&message, &channel, &value));
    assert_eq(channel, 1);
    assert_eq(value, 0x1234);
    assert_success(whad_ant_set_device_type(&message, 2, 120));
    assert_success(whad_ant_set_device_type_parse(&message, &channel, &value));
    assert_eq(value, 120);
    assert_success(whad_ant_set_transmission_type(&message, 3, 5));
    assert_success(whad_ant_set_transmission_type_parse(&message, &channel, &value));
    assert_eq(value, 5);
    assert_success(whad_ant_set_channel_period(&message, 4, 8192));
    assert_success(whad_ant_set_channel_period_parse(&message, &channel, &value));
    assert_eq(value, 8192);

    /* Check representative invalid pointers. */
    assert_error(whad_ant_set_device_number(NULL, 1, 1));
    assert_error(whad_ant_set_device_type_parse(&message, NULL, &value));
    assert_error(whad_ant_set_channel_period_parse(&message, &channel, NULL));

    /* Passed. */
    return PASS;
}

/**
 * Test ANT network-key and sniffing messages.
 * Check fixed-size keys, filters, message types and invalid pointers.
 **/

result_t test_ant_network_and_sniff(void)
{
    Message message;
    uint8_t key[ANT_NETWORK_KEY_SIZE] = {1, 2, 3, 4, 5, 6, 7, 8};
    uint8_t parsed_key[ANT_NETWORK_KEY_SIZE] = {0};
    uint32_t network;
    whad_ant_sniff_params_t parameters;

    /* Craft and parse a network key. */
    memset(&message, 0, sizeof(message));
    memset(&parameters, 0, sizeof(parameters));
    assert_success(whad_ant_set_network_key(&message, 2, key));
    assert_eq(whad_ant_get_message_type(&message), WHAD_ANT_SET_NETWORK_KEY);
    assert_success(whad_ant_set_network_key_parse(&message, &network, parsed_key));
    assert_eq(network, 2);
    assert_buf_eq(parsed_key, key, sizeof(key));

    /* Craft and parse ANT sniffing filters. */
    assert_success(whad_ant_sniff(&message, 66, key, 0x1234, 120, 7));
    assert_success(whad_ant_sniff_parse(&message, &parameters));
    assert_eq(parameters.rf_channel, 66);
    assert_buf_eq(parameters.network_key, key, sizeof(key));
    assert_eq(parameters.device_number, 0x1234);
    assert_eq(parameters.device_type, 120);
    assert_eq(parameters.transmission_type, 7);

    /* Check invalid key and output pointers. */
    assert_error(whad_ant_set_network_key(&message, 1, NULL));
    assert_error(whad_ant_set_network_key_parse(NULL, &network, parsed_key));
    assert_error(whad_ant_sniff_parse(&message, NULL));

    /* Passed. */
    return PASS;
}

/**
 * Test ANT channel assignment.
 * Check required and optional assignment parameters through a round trip.
 **/

result_t test_ant_assign_channel(void)
{
    Message message;
    whad_ant_assign_channel_params_t parameters;

    /* Craft and parse a channel with all optional features enabled. */
    memset(&message, 0, sizeof(message));
    memset(&parameters, 0, sizeof(parameters));
    assert_success(whad_ant_assign_channel(&message, 3, 2,
            ANT_CHANNEL_TYPE_SHARED_BIDIRECTIONAL_TRANSMIT_CHANNEL,
            true, true, true, true));
    assert_eq(whad_ant_get_message_type(&message), WHAD_ANT_ASSIGN_CHANNEL);
    assert_success(whad_ant_assign_channel_parse(&message, &parameters));
    assert_eq(parameters.channel_number, 3);
    assert_eq(parameters.network_number, 2);
    assert_eq(parameters.channel_type, ANT_CHANNEL_TYPE_SHARED_BIDIRECTIONAL_TRANSMIT_CHANNEL);
    assert(parameters.background_scanning);
    assert(parameters.frequency_agility);
    assert(parameters.fast_channel_initiation);
    assert(parameters.asynchronous_transmission);

    /* Check invalid input and output pointers. */
    assert_error(whad_ant_assign_channel(NULL, 1, 1,
            ANT_CHANNEL_TYPE_RECEIVE_ONLY_CHANNEL, false, false, false, false));
    assert_error(whad_ant_assign_channel_parse(&message, NULL));

    /* Passed. */
    return PASS;
}

/**
 * Test ANT single-channel control commands.
 * Check unassign, open, close, RF selection, master and slave modes.
 **/

result_t test_ant_channel_commands(void)
{
    Message message;
    uint32_t channel;
    uint32_t rf_channel;

    /* Round-trip channel lifecycle commands. */
    memset(&message, 0, sizeof(message));
    assert_success(whad_ant_unassign_channel(&message, 1));
    assert_success(whad_ant_unassign_channel_parse(&message, &channel));
    assert_eq(channel, 1);
    assert_success(whad_ant_open_channel(&message, 2));
    assert_success(whad_ant_open_channel_parse(&message, &channel));
    assert_eq(channel, 2);
    assert_success(whad_ant_close_channel(&message, 3));
    assert_success(whad_ant_close_channel_parse(&message, &channel));
    assert_eq(channel, 3);

    /* Round-trip RF channel and role commands. */
    assert_success(whad_ant_set_rf_channel(&message, 4, 66));
    assert_success(whad_ant_set_rf_channel_parse(&message, &channel, &rf_channel));
    assert_eq(channel, 4);
    assert_eq(rf_channel, 66);
    assert_success(whad_ant_master_mode(&message, 5));
    assert_success(whad_ant_master_mode_parse(&message, &channel));
    assert_success(whad_ant_slave_mode(&message, 6));
    assert_success(whad_ant_slave_mode_parse(&message, &channel));
    assert_eq(channel, 6);

    /* Check representative invalid pointers. */
    assert_error(whad_ant_open_channel(NULL, 1));
    assert_error(whad_ant_set_rf_channel_parse(&message, NULL, &rf_channel));
    assert_error(whad_ant_slave_mode_parse(&message, NULL));

    /* Passed. */
    return PASS;
}

/**
 * Test ANT cooked and raw packet transmission.
 * Check maximum payload, radio/channel metadata and invalid sizes.
 **/

result_t test_ant_send_messages(void)
{
    Message message;
    uint8_t packet[ANT_PACKET_MAX_SIZE];
    whad_ant_send_params_t parameters;
    int index;

    /* Initialize a maximum-size packet and round-trip cooked send. */
    for (index = 0; index < ANT_PACKET_MAX_SIZE; index++)
    {
        packet[index] = (uint8_t)index;
    }
    memset(&message, 0, sizeof(message));
    memset(&parameters, 0, sizeof(parameters));
    assert_success(whad_ant_send(&message, 66, 3, packet, sizeof(packet)));
    assert_success(whad_ant_send_parse(&message, &parameters));
    assert_eq(parameters.rf_channel, 66);
    assert_eq(parameters.channel_number, 3);
    assert_buf_eq(parameters.packet.bytes, packet, sizeof(packet));

    /* Round-trip raw send and check invalid inputs. */
    assert_success(whad_ant_send_raw(&message, 67, 4, packet, 4));
    assert_success(whad_ant_send_raw_parse(&message, &parameters));
    assert_eq(parameters.rf_channel, 67);
    assert_error(whad_ant_send_raw(NULL, 1, 1, packet, 1));
    assert_error(whad_ant_send_parse(&message, NULL));

    /* Passed. */
    return PASS;
}

/**
 * Test ANT parameter-free and jamming messages.
 * Check message types, jamming channel and timestamp round trips.
 **/

result_t test_ant_control_and_jamming(void)
{
    Message message;
    uint32_t value;

    /* Craft and parse jamming configuration and notification. */
    memset(&message, 0, sizeof(message));
    assert_success(whad_ant_jam(&message, 70));
    assert_success(whad_ant_jam_parse(&message, &value));
    assert_eq(value, 70);
    assert_success(whad_ant_jammed(&message, 0x12345678));
    assert_success(whad_ant_jammed_parse(&message, &value));
    assert_eq(value, 0x12345678);

    /* Craft parameter-free control messages. */
    assert_success(whad_ant_start(&message));
    assert_success(whad_ant_stop(&message));
    assert_success(whad_ant_list_channels(&message));
    assert_eq(whad_ant_get_message_type(&message), WHAD_ANT_LIST_CHANNELS);
    assert_success(whad_ant_list_networks(&message));
    assert_eq(whad_ant_get_message_type(&message), WHAD_ANT_LIST_NETWORKS);

    /* Check representative invalid pointers. */
    assert_error(whad_ant_jam(NULL, 1));
    assert_error(whad_ant_jammed_parse(&message, NULL));
    assert_error(whad_ant_start(NULL));
    assert_error(whad_ant_list_networks(NULL));

    /* Passed. */
    return PASS;
}

/**
 * Test ANT availability and channel-event notifications.
 * Check counts, channel event data and invalid pointers.
 **/

result_t test_ant_status_notifications(void)
{
    Message message;
    uint32_t value;
    uint32_t channel;
    whad_ant_channel_event_t event;

    /* Round-trip available channel and network counts. */
    memset(&message, 0, sizeof(message));
    assert_success(whad_ant_available_channels(&message, 8));
    assert_success(whad_ant_available_channels_parse(&message, &value));
    assert_eq(value, 8);
    assert_success(whad_ant_available_networks(&message, 4));
    assert_success(whad_ant_available_networks_parse(&message, &value));
    assert_eq(value, 4);

    /* Round-trip a channel event. */
    assert_success(whad_ant_channel_event(&message, 3, ANT_CHANNEL_EVENT_TRANSFER_TX_COMPLETED));
    assert_success(whad_ant_channel_event_parse(&message, &channel, &event));
    assert_eq(channel, 3);
    assert_eq(event, ANT_CHANNEL_EVENT_TRANSFER_TX_COMPLETED);

    /* Check invalid pointers. */
    assert_error(whad_ant_available_channels(NULL, 1));
    assert_error(whad_ant_available_networks_parse(&message, NULL));
    assert_error(whad_ant_channel_event_parse(&message, NULL, &event));

    /* Passed. */
    return PASS;
}

/**
 * Test ANT cooked and raw received-PDU notifications.
 * Check packet metadata, optional fields, CRC and invalid pointers.
 **/

result_t test_ant_received_packets(void)
{
    Message message;
    whad_ant_recvd_packet_t packet;
    whad_ant_recvd_packet_t parsed_packet;
    uint32_t crc;

    /* Initialize a packet with all optional metadata. */
    memset(&message, 0, sizeof(message));
    memset(&packet, 0, sizeof(packet));
    memset(&parsed_packet, 0, sizeof(parsed_packet));
    packet.rf_channel = 66;
    packet.channel_number = 2;
    packet.packet.length = 4;
    memcpy(packet.packet.bytes, "\x01\x02\x03\x04", 4);
    packet.has_rssi = true;
    packet.rssi = -55;
    packet.has_timestamp = true;
    packet.timestamp = 1234;
    packet.has_crc_validity = true;
    packet.crc_validity = true;

    /* Round-trip raw and cooked notifications. */
    assert_success(whad_ant_raw_pdu_received(&message, &packet, 0xaabbccdd));
    assert_success(whad_ant_raw_pdu_received_parse(&message, &parsed_packet, &crc));
    assert_eq(crc, 0xaabbccdd);
    assert_eq(parsed_packet.rssi, -55);
    assert_buf_eq(parsed_packet.packet.bytes, packet.packet.bytes, packet.packet.length);
    memset(&parsed_packet, 0, sizeof(parsed_packet));
    assert_success(whad_ant_pdu_received(&message, &packet));
    assert_success(whad_ant_pdu_received_parse(&message, &parsed_packet));
    assert_eq(parsed_packet.rf_channel, 66);
    assert_eq(parsed_packet.channel_number, 2);

    /* Check invalid pointers. */
    assert_error(whad_ant_raw_pdu_received(NULL, &packet, 1));
    assert_error(whad_ant_raw_pdu_received_parse(&message, NULL, &crc));
    assert_error(whad_ant_pdu_received(&message, NULL));
    assert_error(whad_ant_pdu_received_parse(NULL, &parsed_packet));

    /* Passed. */
    return PASS;
}

TEST_SUITE_BEGIN(ant)
TEST_CASE("Channel parameters", test_ant_channel_parameters)
TEST_CASE("Network and sniff", test_ant_network_and_sniff)
TEST_CASE("Assign channel", test_ant_assign_channel)
TEST_CASE("Channel commands", test_ant_channel_commands)
TEST_CASE("Packet transmission", test_ant_send_messages)
TEST_CASE("Control and jamming", test_ant_control_and_jamming)
TEST_CASE("Status notifications", test_ant_status_notifications)
TEST_CASE("Received packets", test_ant_received_packets)
TEST_SUITE_END()

int main(void)
{
    /* Run the ANT C API tests. */
    printf("*** Testing ANT C API\n");
    return TEST_SUITE_RUN(ant);
}
