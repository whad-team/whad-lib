#include "test.h"
#include "cpp/whad.hpp"

using namespace whad;

/**
 * Test representative ESB control messages.
 * Check parameters, message kinds and domain classification.
 **/

result_t test_esb_control_messages(void)
{
    esb::JamMode jam(37);
    esb::PrxMode prx(21);
    esb::PtxMode ptx(42);
    esb::Start start;
    esb::Stop stop;

    /* Check parameter retention. */
    assert_eq(jam.getChannel(), 37);
    assert_eq(prx.getChannel(), 21);
    assert_eq(ptx.getChannel(), 42);

    /* Pack and identify each representative ESB message. */
    jam.getRaw();
    prx.getRaw();
    ptx.getRaw();
    start.getRaw();
    stop.getRaw();
    assert_eq(jam.getDomain(), DomainEsb);
    assert_eq(jam.getType(), esb::JamMsg);
    assert_eq(prx.getType(), esb::PrxMsg);
    assert_eq(ptx.getType(), esb::PtxMsg);
    assert_eq(start.getType(), esb::StartMsg);
    assert_eq(stop.getType(), esb::StopMsg);

    /* Passed. */
    return PASS;
}

/**
 * Test representative ANT control messages.
 * Check parameters, message kinds and domain classification.
 **/

result_t test_ant_control_messages(void)
{
    ant::Jam jam(66);
    ant::MasterMode master(3);
    ant::SlaveMode slave(4);
    ant::Start start;
    ant::Stop stop;

    /* Check parameter retention. */
    assert_eq(jam.getRFChannel(), 66);
    assert_eq(master.getChannelNumber(), 3);
    assert_eq(slave.getChannelNumber(), 4);

    /* Pack and identify each representative ANT message. */
    jam.getRaw();
    master.getRaw();
    slave.getRaw();
    start.getRaw();
    stop.getRaw();
    assert_eq(jam.getDomain(), DomainAnt);
    assert_eq(jam.getType(), ant::JamMsg);
    assert_eq(master.getType(), ant::MasterModeMsg);
    assert_eq(slave.getType(), ant::SlaveModeMsg);
    assert_eq(start.getType(), ant::StartMsg);
    assert_eq(stop.getType(), ant::StopMsg);

    /* Passed. */
    return PASS;
}

/**
 * Test representative PHY control messages.
 * Check parameters, message kinds and domain classification.
 **/

result_t test_phy_control_messages(void)
{
    phy::SetFreq frequency(2402000000U);
    phy::Start start;
    phy::Stop stop;

    /* Check parameter retention and packed message types. */
    assert_eq(frequency.getFrequency(), 2402000000U);
    frequency.getRaw();
    start.getRaw();
    stop.getRaw();
    assert_eq(frequency.getDomain(), DomainPhy);
    assert_eq(frequency.getType(), phy::SetFreqMsg);
    assert_eq(start.getType(), phy::StartMsg);
    assert_eq(stop.getType(), phy::StopMsg);

    /* Passed. */
    return PASS;
}

/**
 * Test representative IEEE 802.15.4 control messages.
 * Check parameters, message kinds and domain classification.
 **/

result_t test_dot15d4_control_messages(void)
{
    dot15d4::JamMode jam(15);
    dot15d4::SetChannelMap channel_map(0x07fff800);

    /* Check parameter retention and packed message types. */
    assert_eq(jam.getChannel(), 15);
    assert_eq(channel_map.getChannelMap(), 0x07fff800);
    jam.getRaw();
    channel_map.getRaw();
    assert_eq(jam.getDomain(), DomainDot15d4);
    assert_eq(jam.getType(), dot15d4::JamModeMsg);
    assert_eq(channel_map.getType(), dot15d4::SetChannelMapMsg);

    /* Passed. */
    return PASS;
}

/**
 * Test representative Logitech Unifying control messages.
 * Check parameters, message kinds and domain classification.
 **/

result_t test_unifying_control_messages(void)
{
    unifying::JamMode jam(8);
    unifying::DongleMode dongle(24);
    unifying::KeyboardMode keyboard(32);
    unifying::MouseMode mouse(40);

    /* Check parameter retention. */
    assert_eq(jam.getChannel(), 8);
    assert_eq(dongle.getChannel(), 24);
    assert_eq(keyboard.getChannel(), 32);
    assert_eq(mouse.getChannel(), 40);

    /* Pack and identify each representative Unifying message. */
    jam.getRaw();
    dongle.getRaw();
    keyboard.getRaw();
    mouse.getRaw();
    assert_eq(jam.getDomain(), DomainUnifying);
    assert_eq(jam.getType(), unifying::JamModeMsg);
    assert_eq(dongle.getType(), unifying::DongleModeMsg);
    assert_eq(keyboard.getType(), unifying::KeyboardModeMsg);
    assert_eq(mouse.getType(), unifying::MouseModeMsg);

    /* Passed. */
    return PASS;
}

TEST_SUITE_BEGIN(cpp_domains)
TEST_CASE("ESB control messages", test_esb_control_messages)
TEST_CASE("ANT control messages", test_ant_control_messages)
TEST_CASE("PHY control messages", test_phy_control_messages)
TEST_CASE("IEEE 802.15.4 control messages", test_dot15d4_control_messages)
TEST_CASE("Unifying control messages", test_unifying_control_messages)
TEST_SUITE_END()

int main(void)
{
    /* Run the C++ domain API smoke tests. */
    printf("*** Testing domain C++ APIs\n");
    return TEST_SUITE_RUN(cpp_domains);
}
