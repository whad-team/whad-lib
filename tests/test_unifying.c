#include <string.h>

#include "test.h"
#include "whad.h"

/**
 * Test Unifying node-address configuration.
 * Check maximum address size, parsing, message type and invalid inputs.
 **/

result_t test_unifying_node_address(void)
{
    Message message;
    whad_unifying_address_t address;
    whad_unifying_address_t parsed_address;

    /* Craft and parse a maximum-size node address. */
    memset(&message, 0, sizeof(message));
    memset(&address, 0, sizeof(address));
    memset(&parsed_address, 0, sizeof(parsed_address));
    address.size = UNIFYING_ADDR_MAX_SIZE;
    memcpy(address.address, "\x01\x02\x03\x04\x05", UNIFYING_ADDR_MAX_SIZE);
    assert_success(whad_unifying_set_node_address(&message, &address));
    assert_eq(whad_unifying_get_message_type(&message), WHAD_UNIFYING_SET_NODE_ADDR);
    assert_success(whad_unifying_set_node_address_parse(&message, &parsed_address));
    assert_eq(parsed_address.size, address.size);
    assert_buf_eq(parsed_address.address, address.address, address.size);

    /* Check invalid pointers and an oversized address. */
    assert_error(whad_unifying_set_node_address(NULL, &address));
    assert_error(whad_unifying_set_node_address(&message, NULL));
    address.size = UNIFYING_ADDR_MAX_SIZE + 1;
    assert_error(whad_unifying_set_node_address(&message, &address));
    assert_error(whad_unifying_set_node_address_parse(NULL, &parsed_address));
    assert_error(whad_unifying_set_node_address_parse(&message, NULL));

    /* Passed. */
    return PASS;
}

/**
 * Test Unifying sniffing configuration.
 * Check filtering address, channel, acknowledgement reporting and errors.
 **/

result_t test_unifying_sniff(void)
{
    Message message;
    whad_unifying_address_t address;
    whad_unifying_sniff_params_t parameters;

    /* Craft and parse a filtered sniffing request. */
    memset(&message, 0, sizeof(message));
    memset(&address, 0, sizeof(address));
    memset(&parameters, 0, sizeof(parameters));
    address.size = 3;
    memcpy(address.address, "\xaa\xbb\xcc", 3);
    assert_success(whad_unifying_sniff(&message, &address, 42, true));
    assert_eq(whad_unifying_get_message_type(&message), WHAD_UNIFYING_SNIFF_MODE);
    assert_success(whad_unifying_sniff_parse(&message, &parameters));
    assert_eq(parameters.channel, 42);
    assert(parameters.show_acks);
    assert_eq(parameters.address.size, address.size);
    assert_buf_eq(parameters.address.address, address.address, address.size);

    /* Check invalid pointers and an oversized address. */
    assert_error(whad_unifying_sniff(NULL, &address, 1, false));
    assert_error(whad_unifying_sniff(&message, NULL, 1, false));
    address.size = UNIFYING_ADDR_MAX_SIZE + 1;
    assert_error(whad_unifying_sniff(&message, &address, 1, false));
    assert_error(whad_unifying_sniff_parse(NULL, &parameters));
    assert_error(whad_unifying_sniff_parse(&message, NULL));

    /* Passed. */
    return PASS;
}

/**
 * Test Unifying jam, dongle, keyboard and mouse modes.
 * Check their channels, message types, parsers and invalid pointers.
 **/

result_t test_unifying_channel_modes(void)
{
    Message message;
    uint32_t channel;

    /* Craft and parse jamming mode. */
    memset(&message, 0, sizeof(message));
    assert_success(whad_unifying_jam(&message, 8));
    assert_eq(whad_unifying_get_message_type(&message), WHAD_UNIFYING_JAM_MODE);
    assert_success(whad_unifying_jam_parse(&message, &channel));
    assert_eq(channel, 8);

    /* Craft and parse dongle mode. */
    assert_success(whad_unifying_dongle_mode(&message, 24));
    assert_eq(whad_unifying_get_message_type(&message), WHAD_UNIFYING_DONGLE_MODE);
    assert_success(whad_unifying_dongle_mode_parse(&message, &channel));
    assert_eq(channel, 24);

    /* Craft and parse keyboard and mouse modes. */
    assert_success(whad_unifying_keyboard_mode(&message, 32));
    assert_success(whad_unifying_keyboard_mode_parse(&message, &channel));
    assert_eq(channel, 32);
    assert_success(whad_unifying_mouse_mode(&message, 40));
    assert_success(whad_unifying_mouse_mode_parse(&message, &channel));
    assert_eq(channel, 40);

    /* Check invalid input and output pointers. */
    assert_error(whad_unifying_jam(NULL, 1));
    assert_error(whad_unifying_jam_parse(&message, NULL));
    assert_error(whad_unifying_dongle_mode(NULL, 1));
    assert_error(whad_unifying_keyboard_mode_parse(NULL, &channel));
    assert_error(whad_unifying_mouse_mode(NULL, 1));

    /* Passed. */
    return PASS;
}

/**
 * Test cooked Unifying packet transmission.
 * Check maximum payload, channel, retry count and invalid pointers.
 **/

result_t test_unifying_send(void)
{
    Message message;
    uint8_t packet[UNIFYING_PACKET_MAX_SIZE];
    whad_unifying_send_params_t parameters;
    int index;

    /* Initialize and send a maximum-size packet. */
    for (index = 0; index < UNIFYING_PACKET_MAX_SIZE; index++)
    {
        packet[index] = (uint8_t)index;
    }
    memset(&message, 0, sizeof(message));
    memset(&parameters, 0, sizeof(parameters));
    assert_success(whad_unifying_send(&message, 17, 4, packet, sizeof(packet)));
    assert_eq(whad_unifying_get_message_type(&message), WHAD_UNIFYING_SEND);
    assert_success(whad_unifying_send_parse(&message, &parameters));
    assert_eq(parameters.channel, 17);
    assert_eq(parameters.retr_count, 4);
    assert_eq(parameters.packet.length, sizeof(packet));
    assert_buf_eq(parameters.packet.bytes, packet, sizeof(packet));

    /* Check invalid input and output pointers. */
    assert_error(whad_unifying_send(NULL, 1, 1, packet, 1));
    assert_error(whad_unifying_send(&message, 1, 1, NULL, 1));
    assert_error(whad_unifying_send_parse(NULL, &parameters));
    assert_error(whad_unifying_send_parse(&message, NULL));

    /* Passed. */
    return PASS;
}

/**
 * Test raw Unifying packet transmission.
 * Check payload, channel, retry count, message type and invalid pointers.
 **/

result_t test_unifying_send_raw(void)
{
    Message message;
    uint8_t packet[] = {0xde, 0xad, 0xbe, 0xef};
    whad_unifying_send_params_t parameters;

    /* Craft and parse a raw transmission request. */
    memset(&message, 0, sizeof(message));
    memset(&parameters, 0, sizeof(parameters));
    assert_success(whad_unifying_send_raw(&message, 33, 2, packet, sizeof(packet)));
    assert_eq(whad_unifying_get_message_type(&message), WHAD_UNIFYING_SEND_RAW);
    assert_success(whad_unifying_send_raw_parse(&message, &parameters));
    assert_eq(parameters.channel, 33);
    assert_eq(parameters.retr_count, 2);
    assert_eq(parameters.packet.length, sizeof(packet));
    assert_buf_eq(parameters.packet.bytes, packet, sizeof(packet));

    /* Check invalid input and output pointers. */
    assert_error(whad_unifying_send_raw(NULL, 1, 1, packet, 1));
    assert_error(whad_unifying_send_raw(&message, 1, 1, NULL, 1));
    assert_error(whad_unifying_send_raw_parse(NULL, &parameters));
    assert_error(whad_unifying_send_raw_parse(&message, NULL));

    /* Passed. */
    return PASS;
}

/**
 * Test parameter-free Unifying commands.
 * Check start, stop and pairing-sniff message types and invalid pointers.
 **/

result_t test_unifying_parameter_free_commands(void)
{
    Message message;

    /* Craft and identify start, stop and pairing-sniff commands. */
    memset(&message, 0, sizeof(message));
    assert_success(whad_unifying_start(&message));
    assert_eq(whad_unifying_get_message_type(&message), WHAD_UNIFYING_START);
    assert_success(whad_unifying_stop(&message));
    assert_eq(whad_unifying_get_message_type(&message), WHAD_UNIFYING_STOP);
    assert_success(whad_unifying_sniff_pairing(&message));
    assert_eq(whad_unifying_get_message_type(&message), WHAD_UNIFYING_SNIFF_PAIRING);

    /* Check invalid message pointers. */
    assert_error(whad_unifying_start(NULL));
    assert_error(whad_unifying_stop(NULL));
    assert_error(whad_unifying_sniff_pairing(NULL));

    /* Passed. */
    return PASS;
}

/**
 * Test Unifying jammed notifications.
 * Check timestamp storage, parsing, message type and invalid pointers.
 **/

result_t test_unifying_jammed(void)
{
    Message message;
    uint32_t timestamp;

    /* Craft and parse a jammed notification. */
    memset(&message, 0, sizeof(message));
    assert_success(whad_unifying_jammed(&message, 0x12345678));
    assert_eq(whad_unifying_get_message_type(&message), WHAD_UNIFYING_JAMMED);
    assert_success(whad_unifying_jammed_parse(&message, &timestamp));
    assert_eq(timestamp, 0x12345678);

    /* Check invalid input and output pointers. */
    assert_error(whad_unifying_jammed(NULL, 1));
    assert_error(whad_unifying_jammed_parse(NULL, &timestamp));
    assert_error(whad_unifying_jammed_parse(&message, NULL));

    /* Passed. */
    return PASS;
}

/**
 * Test raw Unifying PDU received notifications.
 * Check payload and every optional metadata field through a round trip.
 **/

result_t test_unifying_raw_pdu_received(void)
{
    Message message;
    whad_unifying_recvd_packet_t packet;
    whad_unifying_recvd_packet_t parsed_packet;

    /* Initialize a raw packet with all optional metadata. */
    memset(&message, 0, sizeof(message));
    memset(&packet, 0, sizeof(packet));
    memset(&parsed_packet, 0, sizeof(parsed_packet));
    packet.channel = 55;
    packet.packet.length = 4;
    memcpy(packet.packet.bytes, "\x01\x02\x03\x04", 4);
    packet.has_rssi = true;
    packet.rssi = -67;
    packet.has_timestamp = true;
    packet.timestamp = 0x10203040;
    packet.has_crc_validity = true;
    packet.crc_validity = true;
    packet.has_address = true;
    packet.address.size = 5;
    memcpy(packet.address.address, "\xaa\xbb\xcc\xdd\xee", 5);

    /* Craft, parse and compare all raw PDU fields. */
    assert_success(whad_unifying_raw_pdu_received(&message, &packet));
    assert_eq(whad_unifying_get_message_type(&message), WHAD_UNIFYING_RAW_PDU_RECEIVED);
    assert_success(whad_unifying_raw_pdu_received_parse(&message, &parsed_packet));
    assert_eq(parsed_packet.channel, packet.channel);
    assert_eq(parsed_packet.packet.length, packet.packet.length);
    assert_buf_eq(parsed_packet.packet.bytes, packet.packet.bytes, packet.packet.length);
    assert(parsed_packet.has_rssi);
    assert_eq(parsed_packet.rssi, packet.rssi);
    assert(parsed_packet.has_timestamp);
    assert_eq(parsed_packet.timestamp, packet.timestamp);
    assert(parsed_packet.has_crc_validity);
    assert(parsed_packet.crc_validity);
    assert(parsed_packet.has_address);
    assert_buf_eq(parsed_packet.address.address, packet.address.address, packet.address.size);

    /* Check invalid pointers and an oversized address. */
    assert_error(whad_unifying_raw_pdu_received(NULL, &packet));
    assert_error(whad_unifying_raw_pdu_received(&message, NULL));
    packet.address.size = UNIFYING_ADDR_MAX_SIZE + 1;
    assert_error(whad_unifying_raw_pdu_received(&message, &packet));
    assert_error(whad_unifying_raw_pdu_received_parse(NULL, &parsed_packet));
    assert_error(whad_unifying_raw_pdu_received_parse(&message, NULL));

    /* Passed. */
    return PASS;
}

/**
 * Test cooked Unifying PDU received notifications.
 * Check payload, absent optional metadata and invalid inputs.
 **/

result_t test_unifying_pdu_received(void)
{
    Message message;
    whad_unifying_recvd_packet_t packet;
    whad_unifying_recvd_packet_t parsed_packet;

    /* Initialize a cooked packet without optional metadata. */
    memset(&message, 0, sizeof(message));
    memset(&packet, 0, sizeof(packet));
    memset(&parsed_packet, 0, sizeof(parsed_packet));
    packet.channel = 7;
    packet.packet.length = 3;
    memcpy(packet.packet.bytes, "\x10\x20\x30", 3);

    /* Craft, parse and check the notification. */
    assert_success(whad_unifying_pdu_received(&message, &packet));
    assert_eq(whad_unifying_get_message_type(&message), WHAD_UNIFYING_PDU_RECEIVED);
    assert_success(whad_unifying_pdu_received_parse(&message, &parsed_packet));
    assert_eq(parsed_packet.channel, packet.channel);
    assert_buf_eq(parsed_packet.packet.bytes, packet.packet.bytes, packet.packet.length);
    assert(!parsed_packet.has_rssi);
    assert(!parsed_packet.has_timestamp);
    assert(!parsed_packet.has_crc_validity);
    assert(!parsed_packet.has_address);

    /* Check invalid pointers and an oversized address. */
    assert_error(whad_unifying_pdu_received(NULL, &packet));
    assert_error(whad_unifying_pdu_received(&message, NULL));
    packet.has_address = true;
    packet.address.size = UNIFYING_ADDR_MAX_SIZE + 1;
    assert_error(whad_unifying_pdu_received(&message, &packet));
    assert_error(whad_unifying_pdu_received_parse(NULL, &parsed_packet));
    assert_error(whad_unifying_pdu_received_parse(&message, NULL));

    /* Passed. */
    return PASS;
}

/**
 * Test Unifying message-type discrimination.
 * Check that another domain is reported as an unknown Unifying message.
 **/

result_t test_unifying_message_type(void)
{
    Message message;

    /* Check valid Unifying and unrelated BLE messages. */
    memset(&message, 0, sizeof(message));
    assert_success(whad_unifying_start(&message));
    assert_eq(whad_unifying_get_message_type(&message), WHAD_UNIFYING_START);
    assert_success(whad_ble_start(&message));
    assert_eq(whad_unifying_get_message_type(&message), WHAD_UNIFYING_UNKNOWN);

    /* Passed. */
    return PASS;
}

TEST_SUITE_BEGIN(unifying)
TEST_CASE("Node address", test_unifying_node_address)
TEST_CASE("Sniffing configuration", test_unifying_sniff)
TEST_CASE("Channel modes", test_unifying_channel_modes)
TEST_CASE("Cooked packet transmission", test_unifying_send)
TEST_CASE("Raw packet transmission", test_unifying_send_raw)
TEST_CASE("Parameter-free commands", test_unifying_parameter_free_commands)
TEST_CASE("Jammed notification", test_unifying_jammed)
TEST_CASE("Raw PDU received", test_unifying_raw_pdu_received)
TEST_CASE("Cooked PDU received", test_unifying_pdu_received)
TEST_CASE("Unifying message type", test_unifying_message_type)
TEST_SUITE_END()

int main(void)
{
    /* Run the Logitech Unifying C API tests. */
    printf("*** Testing Logitech Unifying C API\n");
    return TEST_SUITE_RUN(unifying);
}
