#include "test.h"
#include "cpp/whad.hpp"

using namespace whad;
using namespace whad::ant;

/**
 * Test ANT channel configuration messages.
 * Check all scalar channel parameters and their message types.
 **/
result_t test_ant_channel_configuration(void)
{
    SetDeviceNumber device_number(1, 1234);
    SetDeviceType device_type(2, 45);
    SetTransmissionType transmission_type(3, 67);
    SetChannelPeriod channel_period(4, 8192);
    SetRFChannel rf_channel(5, 66);

    /* Check retained parameters. */
    assert_eq(device_number.getChannelNumber(), 1);
    assert_eq(device_number.getDeviceNumber(), 1234);
    assert_eq(device_type.getChannelNumber(), 2);
    assert_eq(device_type.getDeviceType(), 45);
    assert_eq(transmission_type.getChannelNumber(), 3);
    assert_eq(transmission_type.getTransmissionType(), 67);
    assert_eq(channel_period.getChannelNumber(), 4);
    assert_eq(channel_period.getChannelPeriod(), 8192);
    assert_eq(rf_channel.getChannelNumber(), 5);
    assert_eq(rf_channel.getRFChannel(), 66);

    /* Check packed message identities. */
    device_number.getRaw();
    device_type.getRaw();
    transmission_type.getRaw();
    channel_period.getRaw();
    rf_channel.getRaw();
    assert_eq(device_number.getType(), SetDeviceNumberMsg);
    assert_eq(device_type.getType(), SetDeviceTypeMsg);
    assert_eq(transmission_type.getType(), SetTransmissionTypeMsg);
    assert_eq(channel_period.getType(), SetChannelPeriodMsg);
    assert_eq(rf_channel.getType(), SetRFChannelMsg);
    return PASS;
}

/**
 * Test ANT channel lifecycle messages.
 * Check assignment options and open, close and unassign commands.
 **/
result_t test_ant_channel_lifecycle(void)
{
    AssignChannel assign(1, 2, BidirectionalTransmitChannel, true, true, false, true);
    OpenChannel open(1);
    CloseChannel close(2);
    UnassignChannel unassign(3);

    /* Check assignment options. */
    assert_eq(assign.getChannelNumber(), 1);
    assert_eq(assign.getNetworkNumber(), 2);
    assert_eq(assign.getChannelType(), BidirectionalTransmitChannel);
    assert(assign.getBackgroundScanning());
    assert(assign.getFrequencyAgility());
    assert(!assign.getFastChannelInitiation());
    assert(assign.getAsynchronousTransmission());

    /* Check lifecycle commands. */
    assert_eq(open.getChannelNumber(), 1);
    assert_eq(close.getChannelNumber(), 2);
    assert_eq(unassign.getChannelNumber(), 3);
    assign.getRaw();
    open.getRaw();
    close.getRaw();
    unassign.getRaw();
    assert_eq(assign.getType(), AssignChannelMsg);
    assert_eq(open.getType(), OpenChannelMsg);
    assert_eq(close.getType(), CloseChannelMsg);
    assert_eq(unassign.getType(), UnassignChannelMsg);
    return PASS;
}

/**
 * Test ANT network and sniffing messages.
 * Check network keys, filters and list response values.
 **/
result_t test_ant_network_messages(void)
{
    uint8_t key[] = {1, 2, 3, 4, 5, 6, 7, 8};
    SetNetworkKey network(2, key);
    Sniff sniff(57, key, 123, 4, 5);
    ListNetworks list;
    AvailableNetworks available(3);

    /* Check network and sniff parameters. */
    assert_eq(network.getNetworkNumber(), 2);
    assert_buf_eq(network.getNetworkKey(), key, sizeof(key));
    assert_eq(sniff.getRFChannel(), 57);
    assert_buf_eq(sniff.getNetworkKey(), key, sizeof(key));
    assert_eq(sniff.getDeviceNumber(), 123);
    assert_eq(sniff.getDeviceType(), 4);
    assert_eq(sniff.getTransmissionType(), 5);
    assert_eq(available.getNumberOfNetworks(), 3);

    /* Check message identities. */
    network.getRaw();
    sniff.getRaw();
    list.getRaw();
    available.getRaw();
    assert_eq(network.getType(), SetNetworkKeyMsg);
    assert_eq(sniff.getType(), SniffMsg);
    assert_eq(list.getType(), ListNetworksMsg);
    assert_eq(available.getType(), AvailableNetworksMsg);
    return PASS;
}

/**
 * Test ANT transmission messages.
 * Check cooked and raw packet payloads and routing parameters.
 **/
result_t test_ant_transmission_messages(void)
{
    uint8_t bytes[] = {0x10, 0x20, 0x30};
    ant::Packet packet(bytes, sizeof(bytes));
    SendPacket cooked(42, 1, packet);
    SendPacketRaw raw(43, 2, packet);

    /* Check both transmission variants. */
    assert_eq(cooked.getRFChannel(), 42);
    assert_eq(cooked.getChannelNumber(), 1);
    assert_buf_eq(cooked.getPacket().getBytes(), bytes, sizeof(bytes));
    assert_eq(raw.getRFChannel(), 43);
    assert_eq(raw.getChannelNumber(), 2);
    assert_buf_eq(raw.getPacket().getBytes(), bytes, sizeof(bytes));
    cooked.getRaw();
    raw.getRaw();
    assert_eq(cooked.getType(), SendMsg);
    assert_eq(raw.getType(), SendRawMsg);
    return PASS;
}

/**
 * Test ANT received packet notifications.
 * Check optional metadata, payloads and raw CRC handling.
 **/
result_t test_ant_received_packets(void)
{
    uint8_t bytes[] = {0xaa, 0xbb};
    ant::Packet packet(bytes, sizeof(bytes));
    PacketReceived cooked(60, 3, packet);
    RawPacketReceived raw(61, 4, packet);

    /* Add and check cooked packet metadata. */
    cooked.setRssi(-35);
    cooked.setTimestamp(123456);
    cooked.setCrcValidity(true);
    assert(cooked.hasRssi());
    assert_eq(cooked.getRssi(), -35);
    assert(cooked.hasTimestamp());
    assert_eq(cooked.getTimestamp(), 123456);
    assert(cooked.hasCrcValidity());
    assert(cooked.isCrcValid());

    /* Check raw packet CRC and identities. */
    raw.setCrc(0x1234);
    assert_eq(raw.getCrc(), 0x1234);
    cooked.getRaw();
    raw.getRaw();
    assert_eq(cooked.getType(), PduReceivedMsg);
    assert_eq(raw.getType(), RawPduReceivedMsg);
    return PASS;
}

/**
 * Test ANT status and control messages.
 * Check channel discovery, events, modes and jamming notification values.
 **/
result_t test_ant_status_and_control(void)
{
    ListChannels list;
    AvailableChannels available(8);
    ChannelEvent event(2, TransferTxCompleted);
    Jammed jammed(9876);
    MasterMode master(3);
    SlaveMode slave(4);
    Start start;
    Stop stop;

    /* Check status values. */
    assert_eq(available.getNumberOfChannels(), 8);
    assert_eq(event.getChannelNumber(), 2);
    assert_eq(event.getEvent(), TransferTxCompleted);
    assert_eq(jammed.getTimestamp(), 9876);

    /* Check all control and status types. */
    list.getRaw(); available.getRaw(); event.getRaw(); jammed.getRaw();
    master.getRaw(); slave.getRaw(); start.getRaw(); stop.getRaw();
    assert_eq(list.getType(), ListChannelsMsg);
    assert_eq(available.getType(), AvailableChannelsMsg);
    assert(event.getType() != ant::UnknownMsg);
    assert_eq(jammed.getType(), JammedMsg);
    assert_eq(master.getType(), MasterModeMsg);
    assert_eq(slave.getType(), SlaveModeMsg);
    assert_eq(start.getType(), StartMsg);
    assert_eq(stop.getType(), StopMsg);
    return PASS;
}

TEST_SUITE_BEGIN(cpp_ant)
TEST_CASE("Channel configuration", test_ant_channel_configuration)
TEST_CASE("Channel lifecycle", test_ant_channel_lifecycle)
TEST_CASE("Network messages", test_ant_network_messages)
TEST_CASE("Packet transmission", test_ant_transmission_messages)
TEST_CASE("Received packets", test_ant_received_packets)
TEST_CASE("Status and control", test_ant_status_and_control)
TEST_SUITE_END()

int main(void)
{
    /* Run the ANT C++ API tests. */
    printf("*** Testing ANT C++ API\n");
    return TEST_SUITE_RUN(cpp_ant);
}
