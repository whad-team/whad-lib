#include <string.h>

#include "test.h"
#include "whad.h"

/**
 * Test ASK, BPSK and QPSK modulation messages.
 * Check message selection, parameters, parsing and invalid pointers.
 **/

result_t test_phy_phase_and_amplitude_modulations(void)
{
    Message message;
    bool option;

    /* Craft and parse ASK modulation parameters. */
    memset(&message, 0, sizeof(message));
    assert_success(whad_phy_set_ask_mod(&message, true));
    assert_eq(whad_phy_get_message_type(&message), WHAD_PHY_SET_ASK_MOD);
    assert_success(whad_phy_set_ask_mod_parse(&message, &option));
    assert(option);

    /* Craft BPSK and QPSK messages and parse the QPSK offset. */
    assert_success(whad_phy_set_bpsk_mod(&message));
    assert_eq(whad_phy_get_message_type(&message), WHAD_PHY_SET_BPSK_MOD);
    assert_success(whad_phy_set_qpsk_mod(&message, true));
    assert_eq(whad_phy_get_message_type(&message), WHAD_PHY_SET_QPSK_MOD);
    option = false;
    assert_success(whad_phy_set_qpsk_mod_parse(&message, &option));
    assert(option);

    /* Check invalid message and output pointers. */
    assert_error(whad_phy_set_ask_mod(NULL, true));
    assert_error(whad_phy_set_ask_mod_parse(NULL, &option));
    assert_error(whad_phy_set_qpsk_mod_parse(&message, NULL));

    /* Passed. */
    return PASS;
}

/**
 * Test frequency-shift modulation messages.
 * Check FSK, 4FSK, GFSK and MSK deviations and invalid pointers.
 **/

result_t test_phy_frequency_shift_modulations(void)
{
    Message message;
    uint32_t deviation;

    /* Craft and parse an FSK modulation message. */
    memset(&message, 0, sizeof(message));
    assert_success(whad_phy_set_fsk_mod(&message, 250000));
    assert_eq(whad_phy_get_message_type(&message), WHAD_PHY_SET_FSK_MOD);
    assert_success(whad_phy_set_fsk_mod_parse(&message, &deviation));
    assert_eq(deviation, 250000);

    /* Craft and parse a 4FSK modulation message. */
    assert_success(whad_phy_set_4fsk_mod(&message, 125000));
    assert_eq(whad_phy_get_message_type(&message), WHAD_PHY_SET_4FSK_MOD);
    assert_success(whad_phy_set_4fsk_mod_parse(&message, &deviation));
    assert_eq(deviation, 125000);

    /* Craft and parse GFSK and MSK modulation messages. */
    assert_success(whad_phy_set_gfsk_mod(&message, 500000));
    assert_success(whad_phy_set_gfsk_mod_parse(&message, &deviation));
    assert_eq(deviation, 500000);
    assert_success(whad_phy_set_msk_mod(&message, 1000000));
    assert_success(whad_phy_set_msk_mod_parse(&message, &deviation));
    assert_eq(deviation, 1000000);

    /* Check invalid input and output pointers. */
    assert_error(whad_phy_set_fsk_mod(NULL, 1));
    assert_error(whad_phy_set_4fsk_mod_parse(&message, NULL));
    assert_error(whad_phy_set_gfsk_mod_parse(NULL, &deviation));
    assert_error(whad_phy_set_msk_mod(NULL, 1));

    /* Passed. */
    return PASS;
}

/**
 * Test LoRa modulation messages.
 * Check every LoRa parameter, parsing and invalid pointers.
 **/

result_t test_phy_lora_modulation(void)
{
    Message message;
    whad_phy_lora_params_t parameters;

    /* Craft and parse a fully configured LoRa modulation message. */
    memset(&message, 0, sizeof(message));
    memset(&parameters, 0, sizeof(parameters));
    assert_success(whad_phy_set_lora_mod(&message, 125000, PHY_LORA_SF10,
            PHY_LORA_CR47, 12, true, false, true));
    assert_eq(whad_phy_get_message_type(&message), WHAD_PHY_SET_LORA_MOD);
    assert_success(whad_phy_set_lora_mod_parse(&message, &parameters));
    assert_eq(parameters.bandwidth, 125000);
    assert_eq(parameters.sf, PHY_LORA_SF10);
    assert_eq(parameters.cr, PHY_LORA_CR47);
    assert_eq(parameters.preamble_length, 12);
    assert(parameters.enable_crc);
    assert(!parameters.explicit_mode);
    assert(parameters.invert_iq);

    /* Check invalid input and output pointers. */
    assert_error(whad_phy_set_lora_mod(NULL, 1, PHY_LORA_SF7,
            PHY_LORA_CR45, 1, false, false, false));
    assert_error(whad_phy_set_lora_mod_parse(NULL, &parameters));
    assert_error(whad_phy_set_lora_mod_parse(&message, NULL));

    /* Passed. */
    return PASS;
}

/**
 * Test frequency and datarate configuration messages.
 * Check their values, message types, parsing and invalid pointers.
 **/

result_t test_phy_frequency_and_datarate(void)
{
    Message message;
    uint32_t value;

    /* Craft and parse a frequency message. */
    memset(&message, 0, sizeof(message));
    assert_success(whad_phy_set_freq(&message, 2402000000U));
    assert_eq(whad_phy_get_message_type(&message), WHAD_PHY_SET_FREQ);
    assert_success(whad_phy_set_freq_parse(&message, &value));
    assert_eq(value, 2402000000U);

    /* Craft and parse a datarate message. */
    assert_success(whad_phy_set_datarate(&message, 2000000));
    assert_eq(whad_phy_get_message_type(&message), WHAD_PHY_SET_DATARATE);
    assert_success(whad_phy_set_datarate_parse(&message, &value));
    assert_eq(value, 2000000);

    /* Check invalid input and output pointers. */
    assert_error(whad_phy_set_freq(NULL, 1));
    assert_error(whad_phy_set_freq_parse(&message, NULL));
    assert_error(whad_phy_set_datarate(NULL, 1));
    assert_error(whad_phy_set_datarate_parse(NULL, &value));

    /* Passed. */
    return PASS;
}

/**
 * Test endianness, transmit-power and packet-size messages.
 * Check parameters, message types, parsing and invalid pointers.
 **/

result_t test_phy_radio_parameters(void)
{
    Message message;
    whad_phy_endian_t endianness;
    whad_phy_txpower_t power;
    uint32_t packet_size;

    /* Craft and parse packet endianness. */
    memset(&message, 0, sizeof(message));
    assert_success(whad_phy_set_endianness(&message, PHY_LITTLE_ENDIAN));
    assert_eq(whad_phy_get_message_type(&message), WHAD_PHY_SET_ENDIANNESS);
    assert_success(whad_phy_set_endianness_parse(&message, &endianness));
    assert_eq(endianness, PHY_LITTLE_ENDIAN);

    /* Craft and parse transmit power. */
    assert_success(whad_phy_set_tx_power(&message, PHY_TXPOWER_HIGH));
    assert_eq(whad_phy_get_message_type(&message), WHAD_PHY_SET_TX_POWER);
    assert_success(whad_phy_set_tx_power_parse(&message, &power));
    assert_eq(power, PHY_TXPOWER_HIGH);

    /* Craft and parse packet size. */
    assert_success(whad_phy_set_packet_size(&message, 255));
    assert_eq(whad_phy_get_message_type(&message), WHAD_PHY_SET_PACKET_SIZE);
    assert_success(whad_phy_set_packet_size_parse(&message, &packet_size));
    assert_eq(packet_size, 255);

    /* Check invalid input and output pointers. */
    assert_error(whad_phy_set_endianness(NULL, PHY_BIG_ENDIAN));
    assert_error(whad_phy_set_tx_power_parse(&message, NULL));
    assert_error(whad_phy_set_packet_size(NULL, 1));

    /* Passed. */
    return PASS;
}

/**
 * Test synchronization-word configuration.
 * Check bytes, length, message type, parsing and invalid pointers.
 **/

result_t test_phy_sync_word(void)
{
    Message message;
    uint8_t bytes[] = {0xaa, 0xbb, 0xcc, 0xdd};
    uint8_t oversized[11] = {0};
    whad_phy_syncword_t sync_word;

    /* Craft and parse a synchronization word. */
    memset(&message, 0, sizeof(message));
    memset(&sync_word, 0, sizeof(sync_word));
    assert_success(whad_phy_set_sync_word(&message, bytes, sizeof(bytes)));
    assert_eq(whad_phy_get_message_type(&message), WHAD_PHY_SET_SYNC_WORD);
    assert_success(whad_phy_set_sync_word_parse(&message, &sync_word));
    assert_eq(sync_word.length, sizeof(bytes));
    assert_buf_eq(sync_word.syncword, bytes, sizeof(bytes));

    /* Check invalid pointers and an oversized synchronization word. */
    assert_error(whad_phy_set_sync_word(NULL, bytes, sizeof(bytes)));
    assert_error(whad_phy_set_sync_word(&message, NULL, sizeof(bytes)));
    assert_error(whad_phy_set_sync_word(&message, oversized, sizeof(oversized)));
    assert_error(whad_phy_set_sync_word_parse(&message, NULL));

    /* Passed. */
    return PASS;
}

/**
 * Test sniffing, jamming and parameter-free mode messages.
 * Check mode parameters, message types, parsing and invalid pointers.
 **/

result_t test_phy_modes(void)
{
    Message message;
    bool iq_stream;
    whad_phy_jam_mode_t jam_mode;

    /* Craft and parse sniff mode. */
    memset(&message, 0, sizeof(message));
    assert_success(whad_phy_sniff_mode(&message, true));
    assert_eq(whad_phy_get_message_type(&message), WHAD_PHY_SET_SNIFF_MODE);
    assert_success(whad_phy_sniff_mode_parse(&message, &iq_stream));
    assert(iq_stream);

    /* Craft and parse reactive jamming mode. */
    assert_success(whad_phy_jam_mode(&message, PHY_JAM_MODE_REACTIVE));
    assert_eq(whad_phy_get_message_type(&message), WHAD_PHY_SET_JAM_MODE);
    assert_success(whad_phy_jam_mode_parse(&message, &jam_mode));
    assert_eq(jam_mode, PHY_JAM_MODE_REACTIVE);

    /* Check monitor, start and stop commands. */
    assert_success(whad_phy_monitor_mode(&message));
    assert_eq(whad_phy_get_message_type(&message), WHAD_PHY_SET_MONITOR_MODE);
    assert_success(whad_phy_start(&message));
    assert_eq(whad_phy_get_message_type(&message), WHAD_PHY_START);
    assert_success(whad_phy_stop(&message));
    assert_eq(whad_phy_get_message_type(&message), WHAD_PHY_STOP);

    /* Check invalid pointers. */
    assert_error(whad_phy_sniff_mode(NULL, false));
    assert_error(whad_phy_jam_mode_parse(&message, NULL));
    assert_error(whad_phy_monitor_mode(NULL));
    assert_error(whad_phy_start(NULL));
    assert_error(whad_phy_stop(NULL));

    /* Passed. */
    return PASS;
}

/**
 * Test immediate packet transmission.
 * Check payload boundaries, parsing and invalid parameters.
 **/

result_t test_phy_send_packet(void)
{
    Message message;
    uint8_t packet_bytes[255];
    uint8_t oversized[256];
    whad_phy_packet_t packet;
    int i;

    /* Initialize deterministic boundary-size packet data. */
    for (i = 0; i < 255; i++)
    {
        packet_bytes[i] = (uint8_t)i;
    }
    memset(oversized, 0, sizeof(oversized));
    memset(&message, 0, sizeof(message));
    memset(&packet, 0, sizeof(packet));

    /* Craft and parse the largest accepted packet. */
    assert_success(whad_phy_send(&message, packet_bytes, sizeof(packet_bytes)));
    assert_eq(whad_phy_get_message_type(&message), WHAD_PHY_SEND);
    assert_success(whad_phy_send_parse(&message, &packet));
    assert_eq(packet.length, sizeof(packet_bytes));
    assert_buf_eq(packet.payload, packet_bytes, sizeof(packet_bytes));

    /* Check invalid pointers and an oversized packet. */
    assert_error(whad_phy_send(NULL, packet_bytes, 1));
    assert_error(whad_phy_send(&message, NULL, 1));
    assert_error(whad_phy_send(&message, oversized, sizeof(oversized)));
    assert_error(whad_phy_send_parse(&message, NULL));

    /* Passed. */
    return PASS;
}

/**
 * Test raw-IQ transmission message creation.
 * Check message selection, supported size validation and invalid pointers.
 **/

result_t test_phy_send_raw_iq(void)
{
    Message message;
    uint8_t iq_stream[255] = {0};
    uint8_t oversized[256] = {0};

    /* Craft the largest accepted raw-IQ message. */
    memset(&message, 0, sizeof(message));
    assert_success(whad_phy_send_raw_iq(&message, iq_stream, sizeof(iq_stream)));
    assert_eq(whad_phy_get_message_type(&message), WHAD_PHY_SEND_RAW);

    /* Check invalid pointers and an oversized stream. */
    assert_error(whad_phy_send_raw_iq(NULL, iq_stream, 1));
    assert_error(whad_phy_send_raw_iq(&message, NULL, 1));
    assert_error(whad_phy_send_raw_iq(&message, oversized, sizeof(oversized)));

    /* Passed. */
    return PASS;
}

/**
 * Test scheduled packet transmission.
 * Check payload, timestamp, message type, parsing and invalid parameters.
 **/

result_t test_phy_schedule_packet(void)
{
    Message message;
    uint8_t bytes[] = {0x10, 0x20, 0x30};
    uint8_t oversized[256] = {0};
    whad_phy_sched_packet_t packet;

    /* Craft and parse a scheduled packet. */
    memset(&message, 0, sizeof(message));
    memset(&packet, 0, sizeof(packet));
    assert_success(whad_phy_sched_packet(&message, bytes, sizeof(bytes), 123, 456789));
    assert_eq(whad_phy_get_message_type(&message), WHAD_PHY_SEND_SCHED_PACKET);
    assert_success(whad_phy_sched_packet_parse(&message, &packet));
    assert_eq(packet.packet.length, sizeof(bytes));
    assert_buf_eq(packet.packet.payload, bytes, sizeof(bytes));
    assert_eq(packet.ts.ts_sec, 123);
    assert_eq(packet.ts.ts_usec, 456789);

    /* Check invalid pointers and oversized packet rejection. */
    assert_error(whad_phy_sched_packet(NULL, bytes, sizeof(bytes), 1, 1));
    assert_error(whad_phy_sched_packet(&message, NULL, 1, 1, 1));
    assert_error(whad_phy_sched_packet(&message, oversized, sizeof(oversized), 1, 1));
    assert_error(whad_phy_sched_packet_parse(&message, NULL));

    /* Passed. */
    return PASS;
}

/**
 * Test jammed notification messages.
 * Check nonzero and absent timestamps, parsing and invalid pointers.
 **/

result_t test_phy_jammed_notification(void)
{
    Message message;
    whad_phy_timestamp_t timestamp;

    /* Craft and parse a timestamped jammed notification. */
    memset(&message, 0, sizeof(message));
    assert_success(whad_phy_jammed(&message, 42, 999999));
    assert_eq(whad_phy_get_message_type(&message), WHAD_PHY_JAMMED);
    assert_success(whad_phy_jammed_parse(&message, &timestamp));
    assert_eq(timestamp.ts_sec, 42);
    assert_eq(timestamp.ts_usec, 999999);

    /* Check the zero-timestamp representation. */
    assert_success(whad_phy_jammed(&message, 0, 0));
    assert_success(whad_phy_jammed_parse(&message, &timestamp));
    assert_eq(timestamp.ts_sec, 0);
    assert_eq(timestamp.ts_usec, 0);

    /* Check invalid pointers. */
    assert_error(whad_phy_jammed(NULL, 1, 1));
    assert_error(whad_phy_jammed_parse(NULL, &timestamp));
    assert_error(whad_phy_jammed_parse(&message, NULL));

    /* Passed. */
    return PASS;
}

/**
 * Test received packet notifications.
 * Check packet metadata, optional timestamp, parsing and invalid pointers.
 **/

result_t test_phy_packet_received_notification(void)
{
    Message message;
    uint8_t payload[] = {0xde, 0xad, 0xbe, 0xef};
    uint8_t sync_word[] = {0xaa, 0xbb};
    whad_phy_received_packet_t packet;

    /* Craft and parse a timestamped received packet. */
    memset(&message, 0, sizeof(message));
    memset(&packet, 0, sizeof(packet));
    assert_success(whad_phy_packet_received(&message, 868100000, -73, 7, 1234,
            payload, sizeof(payload), sync_word, sizeof(sync_word), 25000,
            50000, PHY_LITTLE_ENDIAN, MOD_GFSK));
    assert_eq(whad_phy_get_message_type(&message), WHAD_PHY_PACKET_RECEIVED);
    assert_success(whad_phy_packet_received_parse(&message, &packet));
    assert_eq(packet.freq, 868100000);
    assert_eq(packet.rssi, -73);
    assert_eq(packet.ts.ts_sec, 7);
    assert_eq(packet.ts.ts_usec, 1234);
    assert_eq(packet.packet.length, sizeof(payload));
    assert_buf_eq(packet.packet.payload, payload, sizeof(payload));

    /* Check invalid message, payload and output pointers. */
    assert_error(whad_phy_packet_received(NULL, 1, 1, 1, 1, payload,
            sizeof(payload), sync_word, sizeof(sync_word), 1, 1,
            PHY_BIG_ENDIAN, MOD_FSK));
    assert_error(whad_phy_packet_received(&message, 1, 1, 1, 1, NULL,
            1, sync_word, sizeof(sync_word), 1, 1, PHY_BIG_ENDIAN, MOD_FSK));
    assert_error(whad_phy_packet_received_parse(&message, NULL));

    /* Passed. */
    return PASS;
}

/**
 * Test scheduled-packet response and sent notifications.
 * Check identifiers, queue-full state, parsing and invalid pointers.
 **/

result_t test_phy_scheduling_notifications(void)
{
    Message message;
    whad_phy_scheduled_packet_t response;
    uint32_t packet_id;

    /* Craft and parse a full-queue scheduling response. */
    memset(&message, 0, sizeof(message));
    assert_success(whad_phy_packet_scheduled(&message, 23, true));
    assert_eq(whad_phy_get_message_type(&message), WHAD_PHY_SCHED_PACKET_RESP);
    assert_success(whad_phy_packet_scheduled_parse(&message, &response));
    assert_eq(response.id, 23);
    assert(response.full);

    /* Craft and parse a scheduled-packet-sent notification. */
    assert_success(whad_phy_sched_packet_sent(&message, 0x12345678));
    assert_eq(whad_phy_get_message_type(&message), WHAD_PHY_SCHED_PACKET_SENT);
    assert_success(whad_phy_sched_packet_sent_parse(&message, &packet_id));
    assert_eq(packet_id, 0x12345678);

    /* Check invalid input and output pointers. */
    assert_error(whad_phy_packet_scheduled(NULL, 1, false));
    assert_error(whad_phy_packet_scheduled_parse(&message, NULL));
    assert_error(whad_phy_sched_packet_sent(NULL, 1));
    assert_error(whad_phy_sched_packet_sent_parse(NULL, &packet_id));

    /* Passed. */
    return PASS;
}

/**
 * Test supported-frequency notification construction and cleanup.
 * Check copied ranges, callback setup, message type and invalid pointers.
 **/

result_t test_phy_supported_frequencies(void)
{
    Message message;
    whad_phy_frequency_range_t ranges[] = {
        {2400000000U, 2483500000U},
        {863000000U, 870000000U}
    };
    phy_SupportedFrequencyRanges_FrequencyRange *encoded_ranges;

    /* Craft a supported-frequency notification. */
    memset(&message, 0, sizeof(message));
    assert_success(whad_phy_supported_frequencies(&message, ranges, 2));
    assert_eq(whad_phy_get_message_type(&message), WHAD_PHY_SUPPORTED_FREQS);
    assert(message.msg.phy.msg.supported_freq.frequency_ranges.funcs.encode != NULL);
    encoded_ranges = message.msg.phy.msg.supported_freq.frequency_ranges.arg;
    assert(encoded_ranges != NULL);
    assert_eq(encoded_ranges[0].start, ranges[0].start);
    assert_eq(encoded_ranges[0].end, ranges[0].end);
    assert_eq(encoded_ranges[1].start, ranges[1].start);
    assert_eq(encoded_ranges[1].end, ranges[1].end);
    assert_eq(encoded_ranges[2].start, 0);
    assert_eq(encoded_ranges[2].end, 0);

    /* Release the callback data through the public cleanup helper. */
    whad_phy_message_free(&message);

    /* Check invalid message and range pointers. */
    assert_error(whad_phy_supported_frequencies(NULL, ranges, 2));
    assert_error(whad_phy_supported_frequencies(&message, NULL, 2));

    /* Passed. */
    return PASS;
}

/**
 * Test PHY message-type discrimination.
 * Check that non-PHY messages are reported as unknown.
 **/

result_t test_phy_message_type(void)
{
    Message message;

    /* Check a valid PHY message type. */
    memset(&message, 0, sizeof(message));
    assert_success(whad_phy_start(&message));
    assert_eq(whad_phy_get_message_type(&message), WHAD_PHY_START);

    /* Check a message belonging to another domain. */
    assert_success(whad_ble_start(&message));
    assert_eq(whad_phy_get_message_type(&message), WHAD_PHY_UNKNOWN);

    /* Passed. */
    return PASS;
}

TEST_SUITE_BEGIN(phy)
TEST_CASE("ASK, BPSK and QPSK modulation", test_phy_phase_and_amplitude_modulations)
TEST_CASE("FSK-family modulations", test_phy_frequency_shift_modulations)
TEST_CASE("LoRa modulation", test_phy_lora_modulation)
TEST_CASE("Frequency and datarate", test_phy_frequency_and_datarate)
TEST_CASE("Radio parameters", test_phy_radio_parameters)
TEST_CASE("Synchronization word", test_phy_sync_word)
TEST_CASE("PHY modes", test_phy_modes)
TEST_CASE("Immediate packet transmission", test_phy_send_packet)
TEST_CASE("Raw-IQ transmission", test_phy_send_raw_iq)
TEST_CASE("Scheduled packet transmission", test_phy_schedule_packet)
TEST_CASE("Jammed notification", test_phy_jammed_notification)
TEST_CASE("Received packet notification", test_phy_packet_received_notification)
TEST_CASE("Scheduling notifications", test_phy_scheduling_notifications)
TEST_CASE("Supported frequencies", test_phy_supported_frequencies)
TEST_CASE("PHY message type", test_phy_message_type)
TEST_SUITE_END()

int main(void)
{
    /* Run the PHY C API tests. */
    printf("*** Testing PHY C API\n");
    return TEST_SUITE_RUN(phy);
}
