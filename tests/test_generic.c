#include <string.h>

#include "test.h"
#include "whad.h"

/**
 * Test generic command-result messages.
 * Check every result code, parsing, message type and invalid pointers.
 **/

result_t test_generic_command_results(void)
{
    Message message;
    whad_result_code_t parsed_result;
    whad_result_code_t result;

    /* Round-trip every public command result. */
    memset(&message, 0, sizeof(message));
    for (result = WHAD_RESULT_SUCCESS; result <= WHAD_RESULT_BUSY; result++)
    {
        assert_success(whad_generic_cmd_result(&message, result));
        assert_eq(whad_generic_get_message_type(&message), WHAD_GENERIC_CMDRESULT);
        assert_success(whad_generic_cmd_result_parse(&message, &parsed_result));
        assert_eq(parsed_result, result);
    }

    /* Check invalid input and output pointers. */
    assert_error(whad_generic_cmd_result(NULL, WHAD_RESULT_SUCCESS));
    assert_error(whad_generic_cmd_result_parse(NULL, &parsed_result));
    assert_error(whad_generic_cmd_result_parse(&message, NULL));

    /* Passed. */
    return PASS;
}

/**
 * Test verbose and debug generic messages.
 * Check callback arguments, debug level, message type and invalid pointers.
 **/

result_t test_generic_text_messages(void)
{
    Message message;
    char verbose_text[] = "radio ready";
    char debug_text[] = "diagnostic";

    /* Craft and inspect a verbose message. */
    memset(&message, 0, sizeof(message));
    assert_success(whad_generic_verbose_message(&message, verbose_text));
    assert_eq(whad_generic_get_message_type(&message), WHAD_GENERIC_VERBOSE);
    assert(message.msg.generic.msg.verbose.data.funcs.encode != NULL);
    assert(message.msg.generic.msg.verbose.data.arg == verbose_text);

    /* Craft and inspect a debug message. */
    assert_success(whad_generic_debug_message(&message, 7, debug_text));
    assert_eq(whad_generic_get_message_type(&message), WHAD_GENERIC_DEBUG);
    assert_eq(message.msg.generic.msg.debug.level, 7);
    assert(message.msg.generic.msg.debug.data.funcs.encode != NULL);
    assert(message.msg.generic.msg.debug.data.arg == debug_text);

    /* Check invalid message pointers. */
    assert_error(whad_generic_verbose_message(NULL, verbose_text));
    assert_error(whad_generic_debug_message(NULL, 1, debug_text));

    /* Passed. */
    return PASS;
}

/**
 * Test generic progress messages and type discrimination.
 * Check value parsing, invalid pointers and unrelated domains.
 **/

result_t test_generic_progress(void)
{
    Message message;
    uint32_t value;

    /* Craft and parse a progress notification. */
    memset(&message, 0, sizeof(message));
    assert_success(whad_generic_progress_message(&message, 73));
    assert_eq(whad_generic_get_message_type(&message), WHAD_GENERIC_PROGRESS);
    assert_success(whad_generic_progress_message_parse(&message, &value));
    assert_eq(value, 73);

    /* Check invalid pointers and another domain. */
    assert_error(whad_generic_progress_message(NULL, 1));
    assert_error(whad_generic_progress_message_parse(NULL, &value));
    assert_error(whad_generic_progress_message_parse(&message, NULL));
    assert_success(whad_ble_start(&message));
    assert_eq(whad_generic_get_message_type(&message), WHAD_GENERIC_UNKNOWN);

    /* Passed. */
    return PASS;
}

TEST_SUITE_BEGIN(generic)
TEST_CASE("Command results", test_generic_command_results)
TEST_CASE("Text messages", test_generic_text_messages)
TEST_CASE("Progress and type", test_generic_progress)
TEST_SUITE_END()

int main(void)
{
    /* Run the generic C API tests. */
    printf("*** Testing generic C API\n");
    return TEST_SUITE_RUN(generic);
}
