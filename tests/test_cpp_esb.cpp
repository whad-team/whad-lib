#include "test.h"
#include "cpp/whad.hpp"

using namespace whad;
using namespace whad::esb;

/**
 * Test ESB addresses and node address messages.
 * Check address storage and packed message identification.
 **/
result_t test_esb_addresses(void)
{
    uint8_t bytes[] = {1, 2, 3, 4, 5};
    EsbAddress address(bytes, sizeof(bytes));
    SetNodeAddress message(address);

    /* Check address storage and message identity. */
    assert_eq(address.getLength(), sizeof(bytes));
    assert_buf_eq(address.getAddressBuf(), bytes, sizeof(bytes));
    assert_buf_eq(message.getAddress().getAddressBuf(), bytes, sizeof(bytes));
    message.getRaw();
    assert_eq(message.getType(), SetNodeAddrMsg);
    assert_eq(message.getDomain(), DomainEsb);
    return PASS;
}

/**
 * Test ESB cooked and raw transmission messages.
 * Check channel, retry count and packet retention.
 **/
result_t test_esb_transmission(void)
{
    uint8_t bytes[] = {0x11, 0x22, 0x33};
    esb::Packet packet(bytes, sizeof(bytes));
    SendPacket cooked(12, 3, packet);
    SendPacketRaw raw(13, 4, packet);

    /* Check routing, retry and packet values. */
    assert_eq(cooked.getChannel(), 12);
    assert_eq(cooked.getRetrCount(), 3);
    assert_buf_eq(cooked.getPacket().getBytes(), bytes, sizeof(bytes));
    assert_eq(raw.getChannel(), 13);
    assert_eq(raw.getRetrCount(), 4);
    cooked.getRaw(); raw.getRaw();
    assert_eq(cooked.getType(), SendMsg);
    assert_eq(raw.getType(), SendRawMsg);
    return PASS;
}

/**
 * Test ESB received packet metadata and message variants.
 * Check every optional field and both notification types.
 **/
result_t test_esb_received_packets(void)
{
    uint8_t bytes[] = {0x44, 0x55};
    uint8_t address_bytes[] = {1, 2, 3};
    esb::Packet packet(bytes, sizeof(bytes));
    EsbAddress address(address_bytes, sizeof(address_bytes));
    RawPacketReceived raw(20, packet);
    PacketReceived cooked(21, packet);

    /* Add all optional metadata to the raw notification. */
    raw.setRssi(-48);
    raw.setTimestamp(7654);
    raw.setAddress(address);
    raw.setCrcValidity(true);
    assert(raw.hasRssi());
    assert_eq(raw.getRssi(), -48);
    assert(raw.hasTimestamp());
    assert(raw.hasAddress());
    assert(raw.hasCrcValidity());
    assert(raw.isCrcValid());

    /* Check notification identities. */
    raw.getRaw(); cooked.getRaw();
    assert_eq(raw.getType(), RawPduReceivedMsg);
    assert_eq(cooked.getType(), PduReceivedMsg);
    return PASS;
}

/**
 * Test ESB operating modes and status notifications.
 * Check mode channels, timestamps and message identification.
 **/
result_t test_esb_modes_and_status(void)
{
    JamMode jam(30);
    PrxMode prx(31);
    PtxMode ptx(32);
    Jammed jammed(1234);
    Start start;
    Stop stop;

    /* Check retained mode and status values. */
    assert_eq(jam.getChannel(), 30);
    assert_eq(prx.getChannel(), 31);
    assert_eq(ptx.getChannel(), 32);
    assert_eq(jammed.getTimestamp(), 1234);

    /* Check packed types. */
    jam.getRaw(); prx.getRaw(); ptx.getRaw(); jammed.getRaw(); start.getRaw(); stop.getRaw();
    assert_eq(jam.getType(), JamMsg);
    assert_eq(prx.getType(), PrxMsg);
    assert_eq(ptx.getType(), PtxMsg);
    assert_eq(jammed.getType(), JammedMsg);
    assert_eq(start.getType(), StartMsg);
    assert_eq(stop.getType(), StopMsg);
    return PASS;
}

TEST_SUITE_BEGIN(cpp_esb)
TEST_CASE("Addresses", test_esb_addresses)
TEST_CASE("Packet transmission", test_esb_transmission)
TEST_CASE("Received packets", test_esb_received_packets)
TEST_CASE("Modes and status", test_esb_modes_and_status)
TEST_SUITE_END()

int main(void)
{
    /* Run the ESB C++ API tests. */
    printf("*** Testing ESB C++ API\n");
    return TEST_SUITE_RUN(cpp_esb);
}
