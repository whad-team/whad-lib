#include <string.h>

#include "test.h"
#include "whad.h"

/**
 * Test IEEE 802.15.4 address and channel commands.
 * Check node address, sniffing, jamming and energy detection round trips.
 **/

result_t test_dot15d4_address_and_channels(void)
{
    Message message;
    whad_dot15d4_address_t address;
    whad_dot15d4_address_t parsed_address;
    uint32_t channel;

    /* Check the currently rejected valid address and parse controlled raw data. */
    memset(&message, 0, sizeof(message));
    address.type = WHAD_DOT15D4_ADDR_EXTENDED;
    address.address = 0x0102030405060708ULL;
    assert_error(whad_dot15d4_set_node_address(&message, &address));
    message.which_msg = Message_dot15d4_tag;
    message.msg.dot15d4.which_msg = dot15d4_Message_set_node_addr_tag;
    message.msg.dot15d4.msg.set_node_addr.address_type = address.type;
    message.msg.dot15d4.msg.set_node_addr.address = address.address;
    assert_success(whad_dot15d4_set_node_address_parse(&message, &parsed_address));
    assert_eq(parsed_address.type, address.type);
    assert_eq(parsed_address.address, address.address);

    /* Round-trip channel-based modes. */
    assert_success(whad_dot15d4_sniff(&message, 11));
    assert_success(whad_dot15d4_sniff_parse(&message, &channel));
    assert_eq(channel, 11);
    assert_success(whad_dot15d4_jam(&message, 15));
    assert_success(whad_dot15d4_jam_parse(&message, &channel));
    assert_eq(channel, 15);
    assert_success(whad_dot15d4_energy_detect(&message, 20));
    assert_success(whad_dot15d4_energy_detect_parse(&message, &channel));
    assert_eq(channel, 20);

    /* Check representative invalid pointers. */
    assert_error(whad_dot15d4_set_node_address(NULL, &address));
    assert_error(whad_dot15d4_sniff_parse(&message, NULL));
    assert_error(whad_dot15d4_energy_detect(NULL, 1));

    /* Passed. */
    return PASS;
}

/**
 * Test cooked and raw IEEE 802.15.4 transmission.
 * Check payload, channel, FCS, boundaries and invalid pointers.
 **/

result_t test_dot15d4_send_messages(void)
{
    Message message;
    uint8_t packet[DOT15D4_PACKET_MAX_SIZE];
    uint8_t oversized[DOT15D4_PACKET_MAX_SIZE + 1];
    whad_dot15d4_send_params_t parameters;
    int index;

    /* Initialize and round-trip a maximum-size cooked packet. */
    for (index = 0; index < DOT15D4_PACKET_MAX_SIZE; index++)
    {
        packet[index] = (uint8_t)index;
    }
    memset(oversized, 0, sizeof(oversized));
    memset(&message, 0, sizeof(message));
    memset(&parameters, 0, sizeof(parameters));
    assert_success(whad_dot15d4_send(&message, 18, packet, sizeof(packet)));
    assert_success(whad_dot15d4_send_parse(&message, &parameters));
    assert_eq(parameters.channel, 18);
    assert_eq(parameters.packet.length, sizeof(packet));
    assert_buf_eq(parameters.packet.bytes, packet, sizeof(packet));

    /* Exercise raw transmission and parse a controlled raw message. */
    assert_success(whad_dot15d4_send_raw(&message, 19, packet, 4, 0xaabb));
    message.msg.dot15d4.which_msg = dot15d4_Message_send_raw_tag;
    message.msg.dot15d4.msg.send_raw.channel = 19;
    message.msg.dot15d4.msg.send_raw.pdu.size = 4;
    memcpy(message.msg.dot15d4.msg.send_raw.pdu.bytes, packet, 4);
    message.msg.dot15d4.msg.send_raw.fcs = 0xaabb;
    assert_success(whad_dot15d4_send_raw_parse(&message, &parameters));
    assert_eq(parameters.fcs, 0xaabb);
    assert_error(whad_dot15d4_send(NULL, 1, packet, 1));
    assert_error(whad_dot15d4_send(&message, 1, NULL, 1));
    assert_error(whad_dot15d4_send(&message, 1, oversized, sizeof(oversized)));
    assert_error(whad_dot15d4_send_raw_parse(&message, NULL));

    /* Passed. */
    return PASS;
}

/**
 * Test IEEE 802.15.4 role and MITM modes.
 * Check end-device, router, coordinator and MITM parameters.
 **/

result_t test_dot15d4_role_modes(void)
{
    Message message;
    uint32_t channel;
    whad_dot15d4_mitm_role_t role;

    /* Round-trip each device role. */
    memset(&message, 0, sizeof(message));
    assert_success(whad_dot15d4_end_device_mode(&message, 11));
    assert_success(whad_dot15d4_end_device_mode_parse(&message, &channel));
    assert_eq(channel, 11);
    assert_success(whad_dot15d4_router_mode(&message, 12));
    assert_success(whad_dot15d4_router_mode_parse(&message, &channel));
    assert_eq(channel, 12);
    assert_success(whad_dot15d4_coord_mode(&message, 13));
    assert_success(whad_dot15d4_coord_mode_parse(&message, &channel));
    assert_eq(channel, 13);

    /* Round-trip MITM role selection. */
    assert_success(whad_dot15d4_mitm_mode(&message, WHAD_DOT15D4_MITM_CORRECTOR));
    assert_success(whad_dot15d4_mitm_mode_parse(&message, &role));
    assert_eq(role, WHAD_DOT15D4_MITM_CORRECTOR);

    /* Check representative invalid pointers. */
    assert_error(whad_dot15d4_router_mode(NULL, 1));
    assert_error(whad_dot15d4_coord_mode_parse(&message, NULL));
    assert_error(whad_dot15d4_mitm_mode_parse(NULL, &role));

    /* Passed. */
    return PASS;
}

/**
 * Test control and scalar notification messages.
 * Check start, stop, jammed and energy sample messages.
 **/

result_t test_dot15d4_control_notifications(void)
{
    Message message;
    uint32_t timestamp;
    whad_dot15d4_ed_sample_t sample;

    /* Craft parameter-free control messages. */
    memset(&message, 0, sizeof(message));
    assert_success(whad_dot15d4_start(&message));
    assert_eq(whad_dot15d4_get_message_type(&message), WHAD_DOT15D4_START);
    assert_success(whad_dot15d4_stop(&message));

    /* Round-trip jammed and energy-detection notifications. */
    assert_success(whad_dot15d4_jammed(&message, 1234));
    assert_success(whad_dot15d4_jammed_parse(&message, &timestamp));
    assert_eq(timestamp, 1234);
    assert_success(whad_dot15d4_energy_detect_sample(&message, 5678, 91));
    assert_success(whad_dot15d4_energy_detect_sample_parse(&message, &sample));
    assert_eq(sample.timestamp, 5678);
    assert_eq(sample.sample, 91);

    /* Check invalid pointers. */
    assert_error(whad_dot15d4_start(NULL));
    assert_error(whad_dot15d4_jammed_parse(&message, NULL));
    assert_error(whad_dot15d4_energy_detect_sample_parse(NULL, &sample));

    /* Passed. */
    return PASS;
}

/**
 * Test cooked and raw received-PDU notifications.
 * Check payload, radio metadata, FCS and optional TSCH fields.
 **/

result_t test_dot15d4_received_packets(void)
{
    Message message;
    whad_dot15d4_recvd_packet_t packet;
    whad_dot15d4_recvd_packet_t parsed_packet;

    /* Initialize a received packet with all metadata. */
    memset(&message, 0, sizeof(message));
    memset(&packet, 0, sizeof(packet));
    memset(&parsed_packet, 0, sizeof(parsed_packet));
    packet.channel = 15;
    packet.packet.length = 4;
    memcpy(packet.packet.bytes, "\x01\x02\x03\x04", 4);
    packet.has_rssi = true;
    packet.rssi = -61;
    packet.has_timestamp = true;
    packet.timestamp = 100;
    packet.has_fcs_validity = true;
    packet.fcs_validity = true;
    packet.fcs = 0xbeef;
    packet.has_lqi = true;
    packet.lqi = 200;
    packet.has_asn = true;
    packet.asn = 0x123456789ULL;
    packet.has_time_slot = true;
    packet.time_slot = 17;

    /* Round-trip raw and cooked packet notifications. */
    assert_success(whad_dot15d4_raw_pdu_received(&message, &packet));
    assert_success(whad_dot15d4_raw_pdu_received_parse(&message, &parsed_packet));
    assert_eq(parsed_packet.fcs, 0xbeef);
    assert_buf_eq(parsed_packet.packet.bytes, packet.packet.bytes, packet.packet.length);
    memset(&parsed_packet, 0, sizeof(parsed_packet));
    assert_success(whad_dot15d4_pdu_received(&message, &packet));
    assert_success(whad_dot15d4_pdu_received_parse(&message, &parsed_packet));

    /* Check invalid pointers. */
    assert_error(whad_dot15d4_raw_pdu_received(NULL, &packet));
    assert_error(whad_dot15d4_raw_pdu_received_parse(&message, NULL));
    assert_error(whad_dot15d4_pdu_received(&message, NULL));

    /* Passed. */
    return PASS;
}

/**
 * Test TSCH configuration and slotted packet transmission.
 * Check enable state, slot timing, payload and invalid pointers.
 **/

result_t test_dot15d4_tsch_configuration(void)
{
    Message message;
    bool enabled;
    whad_dot15d4_packet_t packet;
    whad_dot15d4_send_in_slot_params_t parameters;

    /* Round-trip TSCH enable state. */
    memset(&message, 0, sizeof(message));
    memset(&packet, 0, sizeof(packet));
    memset(&parameters, 0, sizeof(parameters));
    assert_success(whad_dot15d4_config_tsch(&message, true));
    assert_success(whad_dot15d4_config_tsch_parse(&message, &enabled));
    assert(enabled);

    /* Round-trip a slotted packet. */
    packet.length = 3;
    memcpy(packet.bytes, "\xaa\xbb\xcc", 3);
    assert_success(whad_dot15d4_send_in_slot(&message, 0x123456789ULL, 250, packet));
    assert_success(whad_dot15d4_send_in_slot_parse(&message, &parameters));
    assert_eq(parameters.slot, 0x123456789ULL);
    assert_eq(parameters.wait_offset, 250);
    assert_buf_eq(parameters.packet.bytes, packet.bytes, packet.length);

    /* Check invalid pointers. */
    assert_error(whad_dot15d4_config_tsch(NULL, true));
    assert_error(whad_dot15d4_config_tsch_parse(&message, NULL));
    assert_error(whad_dot15d4_send_in_slot_parse(NULL, &parameters));

    /* Passed. */
    return PASS;
}

/**
 * Test TSCH link management commands.
 * Check complete link parameters and deletion selectors.
 **/

result_t test_dot15d4_tsch_links(void)
{
    Message message;
    whad_dot15d4_add_link_params_t link;
    whad_dot15d4_add_link_params_t parsed_link;
    uint32_t superframe;
    uint32_t time_slot;
    uint32_t offset;

    /* Round-trip a complete link description. */
    memset(&message, 0, sizeof(message));
    memset(&link, 0, sizeof(link));
    memset(&parsed_link, 0, sizeof(parsed_link));
    link.superframe_id = 2;
    link.src = 0x1234;
    link.time_slot = 7;
    link.channel_offset = 3;
    link.neighbor = 0xabcd;
    link.options = WHAD_DOT15D4_LINK_OPTIONS_TRANSMIT;
    link.type = WHAD_DOT15D4_LINK_TYPE_NORMAL;
    assert_success(whad_dot15d4_add_link(&message, link));
    assert_success(whad_dot15d4_add_link_parse(&message, &parsed_link));
    assert_eq(parsed_link.superframe_id, link.superframe_id);
    assert_eq(parsed_link.neighbor, link.neighbor);
    assert_eq(parsed_link.options, link.options);

    /* Round-trip link deletion selectors. */
    assert_success(whad_dot15d4_del_link(&message, 2, 7, 3));
    assert_success(whad_dot15d4_del_link_parse(&message, &superframe, &time_slot, &offset));
    assert_eq(superframe, 2);
    assert_eq(time_slot, 7);
    assert_eq(offset, 3);

    /* Check invalid pointers. */
    assert_error(whad_dot15d4_add_link(NULL, link));
    assert_error(whad_dot15d4_add_link_parse(&message, NULL));
    assert_error(whad_dot15d4_del_link_parse(&message, NULL, &time_slot, &offset));

    /* Passed. */
    return PASS;
}

/**
 * Test TSCH superframe and channel-map commands.
 * Check update/delete parameters and channel-map round trips.
 **/

result_t test_dot15d4_tsch_superframes(void)
{
    Message message;
    uint32_t superframe;
    uint32_t slots;
    uint32_t flags;
    uint32_t channel_map;
    uint64_t asn;

    /* Round-trip superframe update and deletion. */
    memset(&message, 0, sizeof(message));
    assert_success(whad_dot15d4_update_superframe(&message, 4, 101, 3, 0x123456789ULL));
    assert_success(whad_dot15d4_update_superframe_parse(&message, &superframe, &slots, &flags, &asn));
    assert_eq(superframe, 4);
    assert_eq(slots, 101);
    assert_eq(flags, 3);
    assert_eq(asn, 0x123456789ULL);
    assert_success(whad_dot15d4_del_superframe(&message, 4));
    assert_success(whad_dot15d4_del_superframe_parse(&message, &superframe));
    assert_eq(superframe, 4);

    /* Round-trip the TSCH channel map. */
    assert_success(whad_dot15d4_set_chm(&message, 0x07fff800));
    assert_success(whad_dot15d4_set_chm_parse(&message, &channel_map));
    assert_eq(channel_map, 0x07fff800);

    /* Check representative invalid pointers. */
    assert_error(whad_dot15d4_update_superframe(NULL, 1, 1, 1, 1));
    assert_error(whad_dot15d4_del_superframe_parse(&message, NULL));
    assert_error(whad_dot15d4_set_chm_parse(NULL, &channel_map));

    /* Passed. */
    return PASS;
}

/**
 * Test discovered TSCH communication notifications.
 * Check slot, offset, packet data, output capacity and invalid pointers.
 **/

result_t test_dot15d4_discovered_communication(void)
{
    Message message;
    uint8_t packet[] = {0xde, 0xad, 0xbe, 0xef};
    uint8_t parsed_packet[DOT15D4_PACKET_MAX_SIZE] = {0};
    uint64_t slot;
    uint32_t offset;
    uint32_t length;

    /* Craft and parse a discovered communication. */
    memset(&message, 0, sizeof(message));
    assert_success(whad_dot15d4_discovered_comm(&message, 0xabcdefULL, 42,
            packet, sizeof(packet)));
    length = sizeof(parsed_packet);
    assert_success(whad_dot15d4_discovered_comm_parse(&message, &slot, &offset,
            parsed_packet, &length));
    assert_eq(slot, 0xabcdefULL);
    assert_eq(offset, 42);
    assert_eq(length, sizeof(packet));
    assert_buf_eq(parsed_packet, packet, sizeof(packet));

    /* Check invalid pointers. */
    assert_error(whad_dot15d4_discovered_comm(NULL, 1, 1, packet, 1));
    assert_error(whad_dot15d4_discovered_comm(&message, 1, 1, NULL, 1));
    assert_error(whad_dot15d4_discovered_comm_parse(NULL, &slot, &offset,
            parsed_packet, &length));

    /* Passed. */
    return PASS;
}

/**
 * Test IEEE 802.15.4 message-type discrimination.
 * Check valid domain messages and rejection of another domain.
 **/

result_t test_dot15d4_message_type(void)
{
    Message message;

    /* Check valid IEEE 802.15.4 and unrelated BLE messages. */
    memset(&message, 0, sizeof(message));
    assert_success(whad_dot15d4_start(&message));
    assert_eq(whad_dot15d4_get_message_type(&message), WHAD_DOT15D4_START);
    assert_success(whad_ble_start(&message));
    assert_eq(whad_dot15d4_get_message_type(&message), WHAD_DOT15D4_UNKNOWN);

    /* Passed. */
    return PASS;
}

TEST_SUITE_BEGIN(dot15d4)
TEST_CASE("Address and channels", test_dot15d4_address_and_channels)
TEST_CASE("Packet transmission", test_dot15d4_send_messages)
TEST_CASE("Role modes", test_dot15d4_role_modes)
TEST_CASE("Control notifications", test_dot15d4_control_notifications)
TEST_CASE("Received packets", test_dot15d4_received_packets)
TEST_CASE("TSCH configuration", test_dot15d4_tsch_configuration)
TEST_CASE("TSCH links", test_dot15d4_tsch_links)
TEST_CASE("TSCH superframes", test_dot15d4_tsch_superframes)
TEST_CASE("Discovered communication", test_dot15d4_discovered_communication)
TEST_CASE("Message type", test_dot15d4_message_type)
TEST_SUITE_END()

int main(void)
{
    /* Run the IEEE 802.15.4 C API tests. */
    printf("*** Testing IEEE 802.15.4 C API\n");
    return TEST_SUITE_RUN(dot15d4);
}
