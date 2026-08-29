#include "test.h"
#include "cpp/whad.hpp"

using namespace whad;
using namespace whad::unifying;

/**
 * Test Unifying addresses and node configuration.
 * Check address storage and packed message identification.
 **/
result_t test_unifying_address(void)
{
    uint8_t bytes[] = {1, 2, 3, 4, 5};
    UnifyingAddress address(bytes, sizeof(bytes));
    SetNodeAddress message(address);

    /* Check retained address and message identity. */
    assert_eq(message.getAddress().getLength(), sizeof(bytes));
    assert_buf_eq(message.getAddress().getBytes(), bytes, sizeof(bytes));
    message.getRaw();
    assert_eq(message.getDomain(), DomainUnifying);
    assert_eq(message.getType(), SetNodeAddressMsg);
    return PASS;
}

/**
 * Test Unifying sniffing and operating modes.
 * Check parameters and packed message types for every mode.
 **/
result_t test_unifying_modes(void)
{
    uint8_t bytes[] = {0xaa, 0xbb, 0xcc};
    UnifyingAddress address(bytes, sizeof(bytes));
    SniffMode sniff(address, 12, true);
    JamMode jam(13);
    DongleMode dongle(14);
    KeyboardMode keyboard(15);
    MouseMode mouse(16);

    /* Check retained mode parameters. */
    assert_eq(sniff.getChannel(), 12);
    assert(sniff.mustShowAcks());
    assert_buf_eq(sniff.getAddress().getBytes(), bytes, sizeof(bytes));
    assert_eq(jam.getChannel(), 13);
    assert_eq(dongle.getChannel(), 14);
    assert_eq(keyboard.getChannel(), 15);
    assert_eq(mouse.getChannel(), 16);

    /* Check packed mode types. */
    sniff.getRaw(); jam.getRaw(); dongle.getRaw(); keyboard.getRaw(); mouse.getRaw();
    assert_eq(sniff.getType(), SniffModeMsg);
    assert_eq(jam.getType(), JamModeMsg);
    assert_eq(dongle.getType(), DongleModeMsg);
    assert_eq(keyboard.getType(), KeyboardModeMsg);
    assert_eq(mouse.getType(), MouseModeMsg);
    return PASS;
}

/**
 * Test Unifying cooked and raw transmission messages.
 * Check channel, retry count and PDU storage.
 **/
result_t test_unifying_transmission(void)
{
    uint8_t bytes[] = {0x10, 0x20, 0x30};
    SendPdu cooked(20, 3, bytes, sizeof(bytes));
    SendRawPdu raw(21, 4, bytes, sizeof(bytes));

    /* Check channel, retries and payload values. */
    assert_eq(cooked.getChannel(), 20);
    assert_eq(cooked.getRetrCounter(), 3);
    assert_eq(cooked.getPdu().getSize(), sizeof(bytes));
    assert_buf_eq(cooked.getPdu().getBytes(), bytes, sizeof(bytes));
    assert_eq(raw.getChannel(), 21);
    assert_eq(raw.getRetrCounter(), 4);
    assert_buf_eq(raw.getPdu().getBytes(), bytes, sizeof(bytes));
    cooked.getRaw(); raw.getRaw();
    assert_eq(cooked.getType(), SendMsg);
    assert_eq(raw.getType(), SendRawMsg);
    return PASS;
}

/**
 * Test the Unifying packet value object and optional metadata.
 * Check payload, radio metadata and CRC validity flags.
 **/
result_t test_unifying_packet(void)
{
    uint8_t bytes[] = {0x40, 0x50};
    UnifyingPacket packet(24, bytes, sizeof(bytes), 0x1234, -45, 9988);

    /* Check constructor-provided values. */
    assert_eq(packet.getChannel(), 24);
    assert_eq(packet.getCrc(), 0x1234);
    assert_eq(packet.getPdu().getSize(), sizeof(bytes));
    assert(packet.hasRssi());
    assert_eq(packet.getRssi(), -45);
    assert(packet.hasTimestamp());
    assert_eq(packet.getTimestamp(), 9988);

    /* Check optional CRC validity. */
    packet.addCrcValidity(true);
    assert(packet.hasCrcValidity());
    assert(packet.isCrcValid());
    return PASS;
}

/**
 * Test Unifying received PDU wrappers and jamming notification.
 * Check addresses, packets and packed message types.
 **/
result_t test_unifying_notifications(void)
{
    uint8_t bytes[] = {0x61, 0x62};
    uint8_t address_bytes[] = {1, 2, 3};
    UnifyingPacket packet(25, bytes, sizeof(bytes), 0xabcd);
    UnifyingAddress address(address_bytes, sizeof(address_bytes));
    PduReceived cooked(packet);
    RawPduReceived raw(packet);
    Jammed jammed(4567);

    /* Add and check source addresses. */
    cooked.addAddress(address);
    raw.addAddress(address);
    assert(cooked.hasAddress());
    assert(raw.hasAddress());
    assert_buf_eq(cooked.getAddress().getBytes(), address_bytes, sizeof(address_bytes));
    assert_eq(cooked.getPacket().getChannel(), 25);
    assert_eq(raw.getPacket().getCrc(), 0xabcd);
    assert_eq(jammed.getTimestamp(), 4567);

    /* Check notification identities. */
    cooked.getRaw(); raw.getRaw(); jammed.getRaw();
    assert_eq(cooked.getType(), PduReceivedMsg);
    assert_eq(raw.getType(), RawPduReceivedMsg);
    assert_eq(jammed.getType(), JamModeMsg);
    return PASS;
}

TEST_SUITE_BEGIN(cpp_unifying)
TEST_CASE("Address", test_unifying_address)
TEST_CASE("Operating modes", test_unifying_modes)
TEST_CASE("Transmission", test_unifying_transmission)
TEST_CASE("Packet value object", test_unifying_packet)
TEST_CASE("Notifications", test_unifying_notifications)
TEST_SUITE_END()

int main(void)
{
    /* Run the Unifying C++ API tests. */
    printf("*** Testing Unifying C++ API\n");
    return TEST_SUITE_RUN(cpp_unifying);
}
