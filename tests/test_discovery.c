#include <string.h>

#include "test.h"
#include "whad.h"

/**
 * Test discovery query messages.
 * Check device-version and domain round trips with invalid pointers.
 **/

result_t test_discovery_queries(void)
{
    Message message;
    uint32_t version;
    whad_domain_t domain;

    /* Craft and parse device and domain queries. */
    memset(&message, 0, sizeof(message));
    assert_success(whad_discovery_device_info_query(&message, 0x01020304));
    assert_eq(whad_discovery_get_message_type(&message), WHAD_DISCOVERY_DEVICE_INFO_QUERY);
    assert_success(whad_discovery_device_info_query_parse(&message, &version));
    assert_eq(version, 0x01020304);
    assert_success(whad_discovery_domain_info_query(&message, DOMAIN_ANT));
    assert_success(whad_discovery_domain_info_query_parse(&message, &domain));
    assert_eq(domain, DOMAIN_ANT);

    /* Check invalid pointers. */
    assert_error(whad_discovery_device_info_query(NULL, 1));
    assert_error(whad_discovery_device_info_query_parse(&message, NULL));
    assert_error(whad_discovery_domain_info_query(NULL, DOMAIN_PHY));
    assert_error(whad_discovery_domain_info_query_parse(NULL, &domain));

    /* Passed. */
    return PASS;
}

/**
 * Test domain discovery helpers and response messages.
 * Check domain lookup, supported commands, parsing and invalid pointers.
 **/

result_t test_discovery_domain_response(void)
{
    Message message;
    whad_domain_desc_t capabilities[] = {
        {DOMAIN_BTLE, CAP_SNIFF, 0x1234},
        {DOMAIN_ANT, CAP_INJECT, 0xabcdef},
        {DOMAIN_NONE, CAP_NONE, 0}
    };
    whad_domain_t domain;
    uint64_t commands;

    /* Check domain lookup and response round trip. */
    memset(&message, 0, sizeof(message));
    assert(whad_discovery_is_domain_supported(capabilities, DOMAIN_BTLE));
    assert(!whad_discovery_is_domain_supported(capabilities, DOMAIN_ESB));
    assert_success(whad_discovery_domain_info_resp(&message, DOMAIN_ANT, capabilities));
    assert_eq(whad_discovery_get_message_type(&message), WHAD_DISCOVERY_DOMAIN_INFO_RESP);
    assert_success(whad_discovery_domain_info_resp_parse(&message, &domain, &commands));
    assert_eq(domain, DOMAIN_ANT);
    assert_eq(commands, 0xabcdef);

    /* Check invalid pointers accepted by the documented parser contract. */
    assert_error(whad_discovery_domain_info_resp(NULL, DOMAIN_ANT, capabilities));
    assert_error(whad_discovery_domain_info_resp_parse(NULL, &domain, &commands));
    assert_error(whad_discovery_domain_info_resp_parse(&message, NULL, &commands));

    /* Passed. */
    return PASS;
}

/**
 * Test discovery reset, ready and transport-speed messages.
 * Check message types, speed parsing and invalid pointers.
 **/

result_t test_discovery_control_messages(void)
{
    Message message;
    uint32_t speed;

    /* Craft reset and ready messages. */
    memset(&message, 0, sizeof(message));
    assert_success(whad_discovery_device_reset(&message));
    assert_eq(whad_discovery_get_message_type(&message), WHAD_DISCOVERY_DEVICE_RESET);
    assert_success(whad_discovery_ready_resp(&message));
    assert_eq(whad_discovery_get_message_type(&message), WHAD_DISCOVERY_READY_RESP);

    /* Craft and parse transport speed. */
    assert_success(whad_discovery_set_speed(&message, BAUDRATE_MAX));
    assert_eq(whad_discovery_get_message_type(&message), WHAD_DISCOVERY_SET_SPEED);
    assert_success(whad_discovery_set_speed_parse(&message, &speed));
    assert_eq(speed, BAUDRATE_MAX);

    /* Check invalid pointers. */
    assert_error(whad_discovery_device_reset(NULL));
    assert_error(whad_discovery_ready_resp(NULL));
    assert_error(whad_discovery_set_speed(NULL, 1));
    assert_error(whad_discovery_set_speed_parse(&message, NULL));

    /* Passed. */
    return PASS;
}

/**
 * Test device-information response construction.
 * Check scalar, text, identifier and capability callback fields.
 **/

result_t test_discovery_device_response(void)
{
    Message message;
    uint8_t device_id[16] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
    whad_domain_desc_t capabilities[] = {
        {DOMAIN_PHY, CAP_SNIFF, 1},
        {DOMAIN_NONE, CAP_NONE, 0}
    };

    /* Craft and inspect a complete device-information response. */
    memset(&message, 0, sizeof(message));
    assert_success(whad_discovery_device_info_resp(&message, discovery_DeviceType_VirtualDevice,
            device_id, 3, BAUDRATE_MAX, "author", "https://example.invalid",
            1, 2, 3, capabilities));
    assert_eq(whad_discovery_get_message_type(&message), WHAD_DISCOVERY_DEVICE_INFO_RESP);
    assert_eq(message.msg.discovery.msg.info_resp.proto_min_ver, 3);
    assert_eq(message.msg.discovery.msg.info_resp.max_speed, BAUDRATE_MAX);
    assert_eq(message.msg.discovery.msg.info_resp.fw_version_major, 1);
    assert(message.msg.discovery.msg.info_resp.capabilities.funcs.encode != NULL);
    assert(message.msg.discovery.msg.info_resp.capabilities.arg == capabilities);

    /* Check invalid message pointers. */
    assert_error(whad_discovery_device_info_resp(NULL, discovery_DeviceType_VirtualDevice,
            device_id, 1, 1, NULL, NULL, 1, 1, 1, capabilities));

    /* Passed. */
    return PASS;
}

TEST_SUITE_BEGIN(discovery)
TEST_CASE("Discovery queries", test_discovery_queries)
TEST_CASE("Domain response", test_discovery_domain_response)
TEST_CASE("Control messages", test_discovery_control_messages)
TEST_CASE("Device response", test_discovery_device_response)
TEST_SUITE_END()

int main(void)
{
    /* Run the discovery C API tests. */
    printf("*** Testing discovery C API\n");
    return TEST_SUITE_RUN(discovery);
}
