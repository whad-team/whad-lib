#include <cstring>

#include "test.h"
#include "cpp/whad.hpp"

using namespace whad;

/**
 * Test the generic Packet template with valid data.
 * Check its default state, capacity, byte copying and replacement behavior.
 **/

result_t test_packet_storage(void)
{
    uint8_t first_bytes[] = {0x10, 0x20, 0x30};
    uint8_t second_bytes[] = {0xaa, 0xbb};
    uint8_t capacity_bytes[] = {0, 1, 2, 3, 4, 5, 6, 7};
    Packet<8> empty_packet;
    Packet<8> packet(first_bytes, sizeof(first_bytes));

    /* Check the default packet and the compile-time capacity. */
    assert_eq(empty_packet.getSize(), 0);
    assert_eq(Packet<8>::getMaxSize(), 8);

    /* Check that construction copies the supplied bytes. */
    assert_eq(packet.getSize(), sizeof(first_bytes));
    assert_buf_eq(packet.getBytes(), first_bytes, sizeof(first_bytes));
    first_bytes[0] = 0xff;
    assert_eq(packet.getBytes()[0], 0x10);

    /* Check replacement with a second packet. */
    Packet<8> replacement(second_bytes, sizeof(second_bytes));
    packet.set(replacement);
    assert_eq(packet.getSize(), sizeof(second_bytes));
    assert_buf_eq(packet.getBytes(), second_bytes, sizeof(second_bytes));

    /* Check construction and copying at the exact storage capacity. */
    Packet<8> full_packet(capacity_bytes, sizeof(capacity_bytes));
    Packet<8> full_copy;
    full_copy.set(full_packet);
    assert_eq(full_packet.getSize(), Packet<8>::getMaxSize());
    assert_eq(full_copy.getSize(), Packet<8>::getMaxSize());
    assert_buf_eq(full_copy.getBytes(), capacity_bytes, sizeof(capacity_bytes));

    /* Passed. */
    return PASS;
}

/**
 * Test Packet size validation.
 * Check that an oversized payload reports both supplied and maximum sizes.
 **/

result_t test_packet_size_error(void)
{
    uint8_t bytes[] = {0, 1, 2, 3, 4};
    bool exception_caught = false;

    /* Attempt to construct a packet larger than its storage. */
    try
    {
        Packet<4> packet(bytes, sizeof(bytes));
        (void)packet;
    }
    catch (WhadInvalidSize &error)
    {
        exception_caught = true;
        assert_eq(error.getSize(), sizeof(bytes));
        assert_eq(error.getExpectedSize(), 4);
    }

    /* Check that invalid input was rejected. */
    assert(exception_caught);

    /* Passed. */
    return PASS;
}

/**
 * Test the DeviceAddress template with valid lengths.
 * Check construction, accessors, assignment and equality.
 **/

result_t test_device_address(void)
{
    uint8_t first_bytes[] = {0x11, 0x22, 0x33};
    uint8_t second_bytes[] = {0xaa, 0xbb, 0xcc, 0xdd};
    DeviceAddress<2, 4> first_address(first_bytes, sizeof(first_bytes));
    DeviceAddress<2, 4> second_address(second_bytes, sizeof(second_bytes));

    /* Check configured bounds and copied address data. */
    assert_eq(first_address.getMinLength(), 2);
    assert_eq(first_address.getMaxLength(), 4);
    assert_eq(first_address.getLength(), sizeof(first_bytes));
    assert_buf_eq(first_address.getBytes(), first_bytes, sizeof(first_bytes));

    /* Check assignment copies both length and bytes. */
    first_address = second_address;
    assert_eq(first_address.getLength(), sizeof(second_bytes));
    assert_buf_eq(first_address.getBytes(), second_bytes, sizeof(second_bytes));

    /* Passed. */
    return PASS;
}

/**
 * Test invalid DeviceAddress construction.
 * Check that the default size exception exposes deterministic sentinel values.
 **/

result_t test_device_address_size_error(void)
{
    uint8_t bytes[] = {0x11};
    bool exception_caught = false;

    /* Attempt to construct an address below its minimum length. */
    try
    {
        DeviceAddress<2, 4> address(bytes, sizeof(bytes));
        (void)address;
    }
    catch (WhadInvalidSize &error)
    {
        exception_caught = true;
        assert_eq(error.getSize(), -1);
        assert_eq(error.getExpectedSize(), -1);
    }

    /* Check that invalid input produced an initialized exception. */
    assert(exception_caught);
    return PASS;
}

/**
 * Test all specialized generic command-result messages.
 * Check their result codes and packed generic message type.
 **/

result_t test_generic_command_results(void)
{
    generic::Success success;
    generic::Error error;
    generic::ParameterError parameter_error;
    generic::Disconnected disconnected;
    generic::WrongMode wrong_mode;
    generic::UnsupportedDomain unsupported_domain;
    generic::Busy busy;

    /* Check each convenience class selects its documented result code. */
    assert_eq(success.getResultCode(), generic::ResultSuccess);
    assert_eq(error.getResultCode(), generic::ResultError);
    assert_eq(parameter_error.getResultCode(), generic::ResultParameterError);
    assert_eq(disconnected.getResultCode(), generic::ResultDisconnected);
    assert_eq(wrong_mode.getResultCode(), generic::ResultWrongMode);
    assert_eq(unsupported_domain.getResultCode(), generic::ResultUnsupportedDomain);
    assert_eq(busy.getResultCode(), generic::ResultBusy);

    /* Pack one result and check both wrapper type levels. */
    Message *message = busy.getRaw();
    NanoPbMsg base_message(message);
    assert_eq(base_message.getType(), whad::GenericMsg);
    assert_eq(busy.getType(), generic::CommandResultMsg);

    /* Passed. */
    return PASS;
}

/**
 * Test parsing a generic command result from a raw message.
 * Check that the wrapper retains the encoded result code.
 **/

result_t test_generic_command_result_parse(void)
{
    Message message;

    /* Craft and wrap a raw command-result message. */
    assert_success(whad_generic_cmd_result(&message, WHAD_RESULT_WRONG_MODE));
    NanoPbMsg base_message(&message);
    generic::CommandResult result(base_message);

    /* Check the decoded type and result. */
    assert_eq(result.getType(), generic::CommandResultMsg);
    assert_eq(result.getResultCode(), generic::ResultWrongMode);

    /* Passed. */
    return PASS;
}

/**
 * Test the generic verbose, debug and progress wrappers.
 * Check that each wrapper packs the expected generic message kind and value.
 **/

result_t test_generic_notifications(void)
{
    uint32_t progress_value = 0;
    generic::Verbose verbose("radio ready");
    generic::Debug debug(7, "diagnostic");
    generic::Progress progress(42);

    /* Pack and identify each generic notification. */
    verbose.getRaw();
    debug.getRaw();
    Message *progress_message = progress.getRaw();
    assert_eq(verbose.getType(), generic::VerboseMsg);
    assert_eq(debug.getType(), generic::DebugMsg);
    assert_eq(progress.getType(), generic::ProgressMsg);

    /* Parse the progress payload through the public C API. */
    assert_success(whad_generic_progress_message_parse(progress_message, &progress_value));
    assert_eq(progress_value, 42);

    /* Passed. */
    return PASS;
}

TEST_SUITE_BEGIN(cpp_core)
TEST_CASE("Packet storage", test_packet_storage)
TEST_CASE("Packet size error", test_packet_size_error)
TEST_CASE("DeviceAddress operations", test_device_address)
TEST_CASE("DeviceAddress size error", test_device_address_size_error)
TEST_CASE("Generic command results", test_generic_command_results)
TEST_CASE("Generic command-result parsing", test_generic_command_result_parse)
TEST_CASE("Generic notifications", test_generic_notifications)
TEST_SUITE_END()

int main(void)
{
    /* Run the C++ core API tests. */
    printf("*** Testing core C++ API\n");
    return TEST_SUITE_RUN(cpp_core);
}
