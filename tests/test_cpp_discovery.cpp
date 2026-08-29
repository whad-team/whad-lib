#include "test.h"
#include "cpp/whad.hpp"

using namespace whad;
using namespace whad::discovery;

/**
 * Test construction and parsing of a device-information query.
 * Check its protocol version and discovery message type in both directions.
 **/

result_t test_device_info_query(void)
{
    DeviceInfoQuery query(0x01020304);
    Message *message = query.getRaw();

    /* Check the constructed wrapper and encoded message. */
    assert_eq(query.getType(), DeviceInfoQueryMsg);
    assert_eq(query.getVersion(), 0x01020304);
    NanoPbMsg base_message(message);
    assert_eq(base_message.getType(), whad::DiscoveryMsg);

    /* Parse the encoded query through the C++ API. */
    whad::discovery::DiscoveryMsg discovery_message(base_message);
    DeviceInfoQuery parsed_query(discovery_message);
    assert_eq(parsed_query.getVersion(), 0x01020304);
    assert_eq(parsed_query.getType(), DeviceInfoQueryMsg);

    /* Passed. */
    return PASS;
}

/**
 * Test construction and parsing of a domain-information query.
 * Check the selected domain and discovery message type in both directions.
 **/

result_t test_domain_info_query(void)
{
    DomainInfoQuery query(Domains::DomainAnt);
    Message *message = query.getRaw();

    /* Check the constructed query. */
    assert_eq(query.getType(), DomainInfoQueryMsg);
    assert_eq(query.getDomain(), Domains::DomainAnt);

    /* Parse the encoded query through the C++ API. */
    NanoPbMsg base_message(message);
    whad::discovery::DiscoveryMsg discovery_message(base_message);
    DomainInfoQuery parsed_query(discovery_message);
    assert_eq(parsed_query.getDomain(), Domains::DomainAnt);
    assert_eq(parsed_query.getType(), DomainInfoQueryMsg);

    /* Passed. */
    return PASS;
}

/**
 * Test construction and parsing of a transport-speed request.
 * Check the baud rate and discovery message type in both directions.
 **/

result_t test_transport_speed(void)
{
    SetTransportSpeed speed(2000000);
    Message *message = speed.getRaw();

    /* Check the constructed speed request. */
    assert_eq(speed.getType(), SetSpeedMsg);
    assert_eq(speed.getSpeed(), 2000000);

    /* Parse the encoded request through the C++ API. */
    NanoPbMsg base_message(message);
    whad::discovery::DiscoveryMsg discovery_message(base_message);
    SetTransportSpeed parsed_speed(discovery_message);
    assert_eq(parsed_speed.getSpeed(), 2000000);
    assert_eq(parsed_speed.getType(), SetSpeedMsg);

    /* Passed. */
    return PASS;
}

/**
 * Test the parameter-free reset and ready discovery messages.
 * Check their packed discovery message types.
 **/

result_t test_reset_and_ready(void)
{
    DeviceReset reset;
    ReadyResp ready;

    /* Pack and identify the reset request. */
    reset.getRaw();
    assert_eq(reset.getType(), DeviceResetMsg);

    /* Pack and identify the ready response. */
    ready.getRaw();
    assert_eq(ready.getType(), ReadyRespMsg);

    /* Passed. */
    return PASS;
}

/**
 * Test the public discovery domain-support helper.
 * Check supported, unsupported and terminating descriptor entries.
 **/

result_t test_domain_support(void)
{
    whad_domain_desc_t capabilities[] = {
        {DOMAIN_BTLE, CAP_SNIFF, 0},
        {DOMAIN_ANT, CAP_SNIFF, 0},
        {DOMAIN_NONE, CAP_NONE, 0}
    };

    /* Check domains present and absent from the descriptor array. */
    assert(isDomainSupported(capabilities, Domains::DomainBtLE));
    assert(isDomainSupported(capabilities, Domains::DomainAnt));
    assert(!isDomainSupported(capabilities, Domains::DomainEsb));

    /* Passed. */
    return PASS;
}

TEST_SUITE_BEGIN(cpp_discovery)
TEST_CASE("Device information query", test_device_info_query)
TEST_CASE("Domain information query", test_domain_info_query)
TEST_CASE("Transport speed", test_transport_speed)
TEST_CASE("Reset and ready messages", test_reset_and_ready)
TEST_CASE("Domain support helper", test_domain_support)
TEST_SUITE_END()

int main(void)
{
    /* Run the C++ discovery API tests. */
    printf("*** Testing discovery C++ API\n");
    return TEST_SUITE_RUN(cpp_discovery);
}
