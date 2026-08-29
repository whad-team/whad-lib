#include "test.h"
#include "cpp/whad.hpp"

using namespace whad;
using namespace whad::phy;

/**
 * Test PHY modulation configuration messages.
 * Check modulation parameters and packed message types.
 **/
result_t test_phy_modulations(void)
{
    SetAskMod ask(true);
    SetBpskMod bpsk;
    SetQpskMod qpsk(true);
    SetFskMod fsk(10000);
    SetGfskMod gfsk(11000);
    Set4FskMod four_fsk(12000);
    SetMskMod msk(13000);

    /* Check modulation-specific values. */
    assert(ask.isOok());
    assert(qpsk.getOffset());
    assert_eq(fsk.getDeviation(), 10000);
    assert_eq(gfsk.getDeviation(), 11000);
    assert_eq(four_fsk.getDeviation(), 12000);
    assert_eq(msk.getDeviation(), 13000);

    /* Check packed modulation types. */
    ask.getRaw(); bpsk.getRaw(); qpsk.getRaw(); fsk.getRaw();
    gfsk.getRaw(); four_fsk.getRaw(); msk.getRaw();
    assert_eq(ask.getType(), SetAskModMsg);
    assert_eq(bpsk.getType(), SetBpskModMsg);
    assert_eq(qpsk.getType(), SetQpskModMsg);
    assert_eq(fsk.getType(), SetFskModMsg);
    assert_eq(gfsk.getType(), SetGfskModMsg);
    assert_eq(four_fsk.getType(), Set4FskModMsg);
    assert_eq(msk.getType(), SetMskModMsg);
    return PASS;
}

/**
 * Test PHY LoRa modulation configuration.
 * Check all LoRa-specific parameters and message identity.
 **/
result_t test_phy_lora_modulation(void)
{
    SetLoraMod lora(125000, LoraSf9, LoraCr47, 12, true, false, true);

    /* Check every LoRa parameter. */
    assert_eq(lora.getBandwidth(), 125000);
    assert_eq(lora.getSpreadingFactor(), LoraSf9);
    assert_eq(lora.getCodingRate(), LoraCr47);
    assert_eq(lora.getPreambleLength(), 12);
    assert(lora.isCrcEnabled());
    assert(!lora.isExplicitMode());
    assert(lora.isIqInverted());
    lora.getRaw();
    assert_eq(lora.getType(), SetLoRaModMsg);
    return PASS;
}

/**
 * Test PHY radio and packet configuration messages.
 * Check scalar values, synchronization word and message types.
 **/
result_t test_phy_radio_configuration(void)
{
    uint8_t sync_bytes[] = {0xaa, 0xbb, 0xcc};
    SyncWord sync_word(sync_bytes, sizeof(sync_bytes));
    SetFreq frequency(2402000000U);
    SetDatarate datarate(2000000);
    SetEndianness endian(PhyBigEndian);
    SetTxPower power(PhyTxPowerHigh);
    SetPacketSize packet_size(64);
    SetSyncWord sync(sync_word);

    /* Check retained configuration values. */
    assert_eq(frequency.getFrequency(), 2402000000U);
    assert_eq(datarate.getDatarate(), 2000000);
    assert_eq(endian.getEndianness(), PhyBigEndian);
    assert_eq(power.getPower(), PhyTxPowerHigh);
    assert_eq(packet_size.getSize(), 64);
    assert_eq(sync.get().getSize(), sizeof(sync_bytes));
    assert_buf_eq(sync.get().get(), sync_bytes, sizeof(sync_bytes));

    /* Check packed configuration types. */
    frequency.getRaw(); datarate.getRaw(); endian.getRaw(); power.getRaw();
    packet_size.getRaw(); sync.getRaw();
    assert_eq(frequency.getType(), SetFreqMsg);
    assert_eq(datarate.getType(), SetDatarateMsg);
    assert_eq(endian.getType(), SetEndiannessMsg);
    assert_eq(power.getType(), SetTxPowerMsg);
    assert_eq(packet_size.getType(), SetPacketSizeMsg);
    assert_eq(sync.getType(), SetSyncWordMsg);
    return PASS;
}

/**
 * Test PHY capture, jamming and lifecycle modes.
 * Check mode options and packed message identities.
 **/
result_t test_phy_modes(void)
{
    SniffMode sniff(true);
    JamMode jam(PhyReactiveJamming);
    MonitorMode monitor;
    Start start;
    Stop stop;

    /* Check mode parameters and packed types. */
    assert(sniff.isIqModeEnabled());
    assert_eq(jam.getMode(), PhyReactiveJamming);
    sniff.getRaw(); jam.getRaw(); monitor.getRaw(); start.getRaw(); stop.getRaw();
    assert_eq(sniff.getType(), SetSniffModeMsg);
    assert_eq(jam.getType(), SetJamModeMsg);
    assert_eq(monitor.getType(), SetMonitorModeMsg);
    assert_eq(start.getType(), StartMsg);
    assert_eq(stop.getType(), StopMsg);
    return PASS;
}

/**
 * Test PHY immediate and scheduled transmissions.
 * Check packet, timestamp and scheduling response values.
 **/
result_t test_phy_transmissions(void)
{
    uint8_t bytes[] = {1, 3, 5, 7};
    phy::Packet packet(bytes, sizeof(bytes));
    Timestamp timestamp(12, 3456);
    SendPacket send(packet);
    SchedulePacket schedule(packet, timestamp);
    PacketScheduled response(7, true);
    ScheduledPacketSent sent(8);

    /* Check packet and scheduling values. */
    assert_buf_eq(send.getPacket().getBytes(), bytes, sizeof(bytes));
    assert_eq(schedule.getTimestamp().getSeconds(), 12);
    assert_eq(schedule.getTimestamp().getMicroseconds(), 3456);
    assert_eq(response.getPacketId(), 7);
    assert(response.isFull());
    assert_eq(sent.getPacketId(), 8);

    /* Check packed transmission types. */
    send.getRaw(); schedule.getRaw(); response.getRaw(); sent.getRaw();
    assert_eq(send.getType(), SendMsg);
    assert_eq(schedule.getType(), SendSchedPacketMsg);
    assert_eq(response.getType(), SchedPacketRespMsg);
    assert_eq(sent.getType(), SchedPacketSentMsg);
    return PASS;
}

/**
 * Test PHY received packet metadata.
 * Check implemented metadata getters and message identification.
 **/
result_t test_phy_received_packet(void)
{
    uint8_t bytes[] = {0x10, 0x11};
    uint8_t sync_bytes[] = {0xd3, 0x91};
    phy::Packet packet(bytes, sizeof(bytes));
    SyncWord sync_word(sync_bytes, sizeof(sync_bytes));
    Timestamp timestamp(45, 6789);
    PacketReceived received(868000000, -72, timestamp, packet, sync_word,
            PhyLittleEndian, 50000, 25000, ModulationGFSK);

    /* Check all received packet metadata. */
    assert_eq(received.getFrequency(), 868000000);
    assert_eq(received.getRssi(), -72);
    assert_eq(received.getTimestamp().getSeconds(), 45);
    assert_buf_eq(received.getPacket().getBytes(), bytes, sizeof(bytes));
    received.getRaw();
    assert_eq(received.getType(), PacketReceivedMsg);
    return PASS;
}

/**
 * Test PHY timestamp, synchronization word and status objects.
 * Check value setters and status notification types.
 **/
result_t test_phy_values_and_status(void)
{
    uint8_t bytes[] = {0x12, 0x34};
    Timestamp timestamp(1, 2);
    SyncWord sync_word(bytes, sizeof(bytes));
    Jammed jammed(timestamp);
    whad_phy_frequency_range_t ranges[] = {{100, 200}, {300, 400}, {0, 0}};
    SupportedFreqsResp supported(ranges);

    /* Check value object setters. */
    timestamp.setSeconds(3);
    timestamp.setMicroseconds(4);
    assert_eq(timestamp.getSeconds(), 3);
    assert_eq(timestamp.getMicroseconds(), 4);
    assert_eq(sync_word.getSize(), sizeof(bytes));
    assert_buf_eq(sync_word.get(), bytes, sizeof(bytes));

    /* Check status message types. */
    assert_eq(jammed.getTimestamp().getSeconds(), 1);
    jammed.getRaw(); supported.getRaw();
    assert_eq(jammed.getType(), JammedMsg);
    assert_eq(supported.getType(), SupportedFreqsMsg);
    return PASS;
}

TEST_SUITE_BEGIN(cpp_phy)
TEST_CASE("Modulations", test_phy_modulations)
TEST_CASE("LoRa modulation", test_phy_lora_modulation)
TEST_CASE("Radio configuration", test_phy_radio_configuration)
TEST_CASE("Operating modes", test_phy_modes)
TEST_CASE("Transmissions", test_phy_transmissions)
TEST_CASE("Received packet", test_phy_received_packet)
TEST_CASE("Values and status", test_phy_values_and_status)
TEST_SUITE_END()

int main(void)
{
    /* Run the PHY C++ API tests. */
    printf("*** Testing PHY C++ API\n");
    return TEST_SUITE_RUN(cpp_phy);
}
