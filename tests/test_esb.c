#include <string.h>

#include "test.h"
#include "whad.h"

/**
 * Test ESB node-address configuration.
 * Check address boundaries, parsing, message type and invalid pointers.
 **/

result_t test_esb_node_address(void)
{
    Message message;
    whad_esb_address_t address;
    whad_esb_address_t parsed_address;

    /* Build the largest valid ESB address. */
    memset(&message, 0, sizeof(message));
    memset(&address, 0, sizeof(address));
    memset(&parsed_address, 0, sizeof(parsed_address));
    address.size = ESB_ADDR_MAX_SIZE;
    memcpy(address.address, "\x01\x02\x03\x04\x05", ESB_ADDR_MAX_SIZE);
    assert_success(whad_esb_set_node_address(&message, &address));
    assert_eq(whad_esb_get_message_type(&message), WHAD_ESB_SET_NODE_ADDRESS);

    /* Parse and compare the configured address. */
    assert_success(whad_esb_set_node_address_parse(&message, &parsed_address));
    assert_eq(parsed_address.size, address.size);
    assert_buf_eq(parsed_address.address, address.address, address.size);

    /* Check invalid pointers and an oversized address. */
    assert_error(whad_esb_set_node_address(NULL, &address));
    assert_error(whad_esb_set_node_address(&message, NULL));
    address.size = ESB_ADDR_MAX_SIZE + 1;
    assert_error(whad_esb_set_node_address(&message, &address));
    assert_error(whad_esb_set_node_address_parse(NULL, &parsed_address));
    assert_error(whad_esb_set_node_address_parse(&message, NULL));

    /* Passed. */
    return PASS;
}

/**
 * Test ESB sniffing configuration.
 * Check address, channel, acknowledgement reporting and invalid inputs.
 **/

result_t test_esb_sniff(void)
{
    Message message;
    whad_esb_address_t address;
    whad_esb_sniff_params_t parameters;

    /* Craft and parse a filtered sniffing request. */
    memset(&message, 0, sizeof(message));
    memset(&address, 0, sizeof(address));
    memset(&parameters, 0, sizeof(parameters));
    address.size = 3;
    memcpy(address.address, "\xaa\xbb\xcc", 3);
    assert_success(whad_esb_sniff(&message, &address, 42, true));
    assert_eq(whad_esb_get_message_type(&message), WHAD_ESB_SNIFF);
    assert_success(whad_esb_sniff_parse(&message, &parameters));
    assert_eq(parameters.channel, 42);
    assert(parameters.show_acks);
    assert_eq(parameters.address.size, address.size);
    assert_buf_eq(parameters.address.address, address.address, address.size);

    /* Check invalid pointers and an oversized address. */
    assert_error(whad_esb_sniff(NULL, &address, 1, false));
    assert_error(whad_esb_sniff(&message, NULL, 1, false));
    address.size = ESB_ADDR_MAX_SIZE + 1;
    assert_error(whad_esb_sniff(&message, &address, 1, false));
    assert_error(whad_esb_sniff_parse(NULL, &parameters));
    assert_error(whad_esb_sniff_parse(&message, NULL));

    /* Passed. */
    return PASS;
}

/**
 * Test ESB jamming, PRX and PTX mode commands.
 * Check channel values, message types, parsing and invalid pointers.
 **/

result_t test_esb_channel_modes(void)
{
    Message message;
    uint32_t channel;

    /* Craft and parse a jamming mode request. */
    memset(&message, 0, sizeof(message));
    assert_success(whad_esb_jam(&message, 8));
    assert_eq(whad_esb_get_message_type(&message), WHAD_ESB_JAM);
    assert_success(whad_esb_jam_parse(&message, &channel));
    assert_eq(channel, 8);

    /* Craft and parse primary receiver mode. */
    assert_success(whad_esb_prx(&message, 24));
    assert_eq(whad_esb_get_message_type(&message), WHAD_ESB_PRX);
    assert_success(whad_esb_prx_parse(&message, &channel));
    assert_eq(channel, 24);

    /* Craft and parse primary transmitter mode. */
    assert_success(whad_esb_ptx(&message, 64));
    assert_eq(whad_esb_get_message_type(&message), WHAD_ESB_PTX);
    assert_success(whad_esb_ptx_parse(&message, &channel));
    assert_eq(channel, 64);

    /* Check invalid input and output pointers. */
    assert_error(whad_esb_jam(NULL, 1));
    assert_error(whad_esb_jam_parse(&message, NULL));
    assert_error(whad_esb_prx(NULL, 1));
    assert_error(whad_esb_prx_parse(NULL, &channel));
    assert_error(whad_esb_ptx(NULL, 1));
    assert_error(whad_esb_ptx_parse(&message, NULL));

    /* Passed. */
    return PASS;
}

/**
 * Test ESB cooked packet transmission.
 * Check maximum payload size, channel, retry count and invalid pointers.
 **/

result_t test_esb_send(void)
{
    Message message;
    uint8_t packet[ESB_PACKET_MAX_SIZE];
    whad_esb_send_params_t parameters;
    int index;

    /* Initialize and send a maximum-size packet. */
    for (index = 0; index < ESB_PACKET_MAX_SIZE; index++)
    {
        packet[index] = (uint8_t)index;
    }
    memset(&message, 0, sizeof(message));
    memset(&parameters, 0, sizeof(parameters));
    assert_success(whad_esb_send(&message, 17, 4, packet, sizeof(packet)));
    assert_eq(whad_esb_get_message_type(&message), WHAD_ESB_SEND);

    /* Parse and compare all transmission parameters. */
    assert_success(whad_esb_send_parse(&message, &parameters));
    assert_eq(parameters.channel, 17);
    assert_eq(parameters.retr_count, 4);
    assert_eq(parameters.packet.length, sizeof(packet));
    assert_buf_eq(parameters.packet.bytes, packet, sizeof(packet));

    /* Check invalid input and output pointers. */
    assert_error(whad_esb_send(NULL, 1, 1, packet, 1));
    assert_error(whad_esb_send(&message, 1, 1, NULL, 1));
    assert_error(whad_esb_send_parse(NULL, &parameters));
    assert_error(whad_esb_send_parse(&message, NULL));

    /* Passed. */
    return PASS;
}

/**
 * Test ESB raw packet transmission.
 * Check payload, channel, retry count, message type and invalid pointers.
 **/

result_t test_esb_send_raw(void)
{
    Message message;
    uint8_t packet[] = {0xde, 0xad, 0xbe, 0xef};
    whad_esb_send_params_t parameters;

    /* Craft and parse a raw transmission request. */
    memset(&message, 0, sizeof(message));
    memset(&parameters, 0, sizeof(parameters));
    assert_success(whad_esb_send_raw(&message, 33, 2, packet, sizeof(packet)));
    assert_eq(whad_esb_get_message_type(&message), WHAD_ESB_SEND_RAW);
    assert_success(whad_esb_send_raw_parse(&message, &parameters));
    assert_eq(parameters.channel, 33);
    assert_eq(parameters.retr_count, 2);
    assert_eq(parameters.packet.length, sizeof(packet));
    assert_buf_eq(parameters.packet.bytes, packet, sizeof(packet));

    /* Check invalid input and output pointers. */
    assert_error(whad_esb_send_raw(NULL, 1, 1, packet, 1));
    assert_error(whad_esb_send_raw(&message, 1, 1, NULL, 1));
    assert_error(whad_esb_send_raw_parse(NULL, &parameters));
    assert_error(whad_esb_send_raw_parse(&message, NULL));

    /* Passed. */
    return PASS;
}

/**
 * Test parameter-free ESB start and stop commands.
 * Check their message types and invalid pointers.
 **/

result_t test_esb_start_stop(void)
{
    Message message;

    /* Craft and identify a start command. */
    memset(&message, 0, sizeof(message));
    assert_success(whad_esb_start(&message));
    assert_eq(whad_esb_get_message_type(&message), WHAD_ESB_START);

    /* Craft and identify a stop command. */
    assert_success(whad_esb_stop(&message));
    assert_eq(whad_esb_get_message_type(&message), WHAD_ESB_STOP);

    /* Check invalid pointers. */
    assert_error(whad_esb_start(NULL));
    assert_error(whad_esb_stop(NULL));

    /* Passed. */
    return PASS;
}

/**
 * Test ESB jammed notifications.
 * Check timestamp storage, parsing, message type and invalid pointers.
 **/

result_t test_esb_jammed(void)
{
    Message message;
    uint32_t timestamp;

    /* Craft and parse a jammed notification. */
    memset(&message, 0, sizeof(message));
    assert_success(whad_esb_jammed(&message, 0x12345678));
    assert_eq(whad_esb_get_message_type(&message), WHAD_ESB_JAMMED);
    assert_success(whad_esb_jammed_parse(&message, &timestamp));
    assert_eq(timestamp, 0x12345678);

    /* Check invalid input and output pointers. */
    assert_error(whad_esb_jammed(NULL, 1));
    assert_error(whad_esb_jammed_parse(NULL, &timestamp));
    assert_error(whad_esb_jammed_parse(&message, NULL));

    /* Passed. */
    return PASS;
}

/**
 * Test raw ESB PDU received notifications.
 * Check payload and every optional metadata field through a round trip.
 **/

result_t test_esb_raw_pdu_received(void)
{
    Message message;
    whad_esb_recvd_packet_t packet;
    whad_esb_recvd_packet_t parsed_packet;

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

    /* Craft, parse and compare the raw PDU notification. */
    assert_success(whad_esb_raw_pdu_received(&message, &packet));
    assert_eq(whad_esb_get_message_type(&message), WHAD_ESB_RAW_PDU_RECEIVED);
    assert_success(whad_esb_raw_pdu_received_parse(&message, &parsed_packet));
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
    assert_error(whad_esb_raw_pdu_received(NULL, &packet));
    assert_error(whad_esb_raw_pdu_received(&message, NULL));
    packet.address.size = ESB_ADDR_MAX_SIZE + 1;
    assert_error(whad_esb_raw_pdu_received(&message, &packet));
    assert_error(whad_esb_raw_pdu_received_parse(NULL, &parsed_packet));
    assert_error(whad_esb_raw_pdu_received_parse(&message, NULL));

    /* Passed. */
    return PASS;
}

/**
 * Test cooked ESB PDU received notifications.
 * Check absent optional metadata and a fully populated notification.
 **/

result_t test_esb_pdu_received(void)
{
    Message message;
    whad_esb_recvd_packet_t packet;
    whad_esb_recvd_packet_t parsed_packet;

    /* Initialize a cooked packet without optional metadata. */
    memset(&message, 0, sizeof(message));
    memset(&packet, 0, sizeof(packet));
    memset(&parsed_packet, 0, sizeof(parsed_packet));
    packet.channel = 7;
    packet.packet.length = 3;
    memcpy(packet.packet.bytes, "\x10\x20\x30", 3);

    /* Craft, parse and check absent optional fields. */
    assert_success(whad_esb_pdu_received(&message, &packet));
    assert_eq(whad_esb_get_message_type(&message), WHAD_ESB_PDU_RECEIVED);
    assert_success(whad_esb_pdu_received_parse(&message, &parsed_packet));
    assert_eq(parsed_packet.channel, packet.channel);
    assert_buf_eq(parsed_packet.packet.bytes, packet.packet.bytes, packet.packet.length);
    assert(!parsed_packet.has_rssi);
    assert(!parsed_packet.has_timestamp);
    assert(!parsed_packet.has_crc_validity);
    assert(!parsed_packet.has_address);

    /* Check invalid pointers and oversized addresses. */
    assert_error(whad_esb_pdu_received(NULL, &packet));
    assert_error(whad_esb_pdu_received(&message, NULL));
    packet.has_address = true;
    packet.address.size = ESB_ADDR_MAX_SIZE + 1;
    assert_error(whad_esb_pdu_received(&message, &packet));
    assert_error(whad_esb_pdu_received_parse(NULL, &parsed_packet));
    assert_error(whad_esb_pdu_received_parse(&message, NULL));

    /* Passed. */
    return PASS;
}

/**
 * Test ESB message-type discrimination.
 * Check that messages from another domain are reported as unknown.
 **/

result_t test_esb_message_type(void)
{
    Message message;

    /* Check a valid ESB message. */
    memset(&message, 0, sizeof(message));
    assert_success(whad_esb_start(&message));
    assert_eq(whad_esb_get_message_type(&message), WHAD_ESB_START);

    /* Check a message belonging to another domain. */
    assert_success(whad_ble_start(&message));
    assert_eq(whad_esb_get_message_type(&message), WHAD_ESB_UNKNOWN);

    /* Passed. */
    return PASS;
}

TEST_SUITE_BEGIN(esb)
TEST_CASE("Node address", test_esb_node_address)
TEST_CASE("Sniffing configuration", test_esb_sniff)
TEST_CASE("Channel modes", test_esb_channel_modes)
TEST_CASE("Cooked packet transmission", test_esb_send)
TEST_CASE("Raw packet transmission", test_esb_send_raw)
TEST_CASE("Start and stop", test_esb_start_stop)
TEST_CASE("Jammed notification", test_esb_jammed)
TEST_CASE("Raw PDU received", test_esb_raw_pdu_received)
TEST_CASE("Cooked PDU received", test_esb_pdu_received)
TEST_CASE("ESB message type", test_esb_message_type)
TEST_SUITE_END()

int main(void)
{
    /* Run the ESB C API tests. */
    printf("*** Testing ESB C API\n");
    return TEST_SUITE_RUN(esb);
}
