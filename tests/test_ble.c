/**
 * Bluetooth Low Energy unit tests.
 **/
#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#include "whad.h"

#define BLE_MSG(m)  m.msg.ble.msg

/* Test result. */
typedef enum {
    PASS,
    FAILURE
} result_t;

/* Default test prototype. */
typedef result_t (*FTestProc)(void);

typedef struct {
    char *psz_desc;
    FTestProc p_func;
} test_t;

#define TEST_CASE(desc,f) {desc, f},
#define TEST_SUITE_BEGIN(group) test_t TEST_##group[]={
#define TEST_SUITE_RUN(group) test_run(TEST_##group, (sizeof TEST_##group / sizeof TEST_##group[0]))
#define TEST_SUITE_END() };

/* Assertions. */
#define assert(cdt) {\
    if (!(cdt)) return FAILURE; \
}

#define assert_success(p) assert((p)==WHAD_SUCCESS)
#define assert_error(p) assert((p)==WHAD_ERROR)
#define assert_eq(a,e) \
    do { \
        if ((e) != (a)) { \
            return FAILURE; \
        } \
    } while (0)

/**
 * Message type test.
 **/

result_t test_get_message_type(void)
{
    Message msg;

    /* Configure a BLE message of type Start. */
    msg.which_msg = Message_ble_tag;
    msg.msg.ble.which_msg = ble_Message_start_tag;

    /* Check whad_ble_get_message_type() returns the expected value. */
    assert_eq(whad_ble_get_message_type(&msg), WHAD_BLE_START);

    return PASS;
}

result_t test_get_message_type_not_ble(void)
{
    Message msg;

    /* Confgure a PHY message. */
    msg.which_msg = Message_phy_tag;

    /* Check whad_ble_get_message_type() returns WHAD_BLE_UNKNOWN */
    assert_eq(whad_ble_get_message_type(&msg), WHAD_BLE_UNKNOWN);

    return PASS;
}

/**
 * Bluetooth Device address related tests.
 **/

result_t test_set_bdaddress(void)
{
    Message msg;
    uint8_t addr[] = {0x11, 0x22, 0x33, 0x44, 0x55, 0x66};
    
    assert_success(whad_ble_set_bdaddress(&msg, BLE_ADDR_RANDOM, addr));

    return PASS;
}

result_t test_set_bdaddress_bad_pmsg(void)
{
    uint8_t addr[] = {0x11, 0x22, 0x33, 0x44, 0x55, 0x66};

    assert_error(whad_ble_set_bdaddress(NULL, BLE_ADDR_RANDOM, addr));

    return PASS;
}

result_t test_set_bdaddress_bad_addr(void)
{
    Message msg;

    assert_error(whad_ble_set_bdaddress(&msg, BLE_ADDR_RANDOM, NULL));

    return PASS;
}

result_t test_set_bdaddress_parse(void)
{
    Message msg;
    uint8_t address[] = {0x11, 0x22, 0x33, 0x44, 0x55, 0x66};
    uint8_t read_address[6];
    whad_ble_addrtype_t read_type;

    /* Build a SetBdAddress message. */
    assert_success(whad_ble_set_bdaddress(&msg, BLE_ADDR_RANDOM, address));
    
    /* Check function fails when message pointer is NULL. */
    assert_error(whad_ble_set_bdaddress_parse(NULL, &read_type, read_address));

    /* Check function fails when address type pointer is NULL. */
    assert_error(whad_ble_set_bdaddress_parse(&msg, NULL, read_address));

    /* Check function fails when address pointer is NULL. */
    assert_error(whad_ble_set_bdaddress_parse(&msg, &read_type, NULL));

    /* Reset address and read_type. */
    memset(read_address, 0, 6);
    read_type = 0;

    /* Parse it. */
    assert_success(whad_ble_set_bdaddress_parse(&msg, &read_type, read_address));
    assert_eq(read_type, BLE_ADDR_RANDOM);
    assert(!memcmp(read_address, address, 6));

    return PASS;
}


/**
 * SniffAdv
 **/

result_t test_sniff_adv_craft(void)
{
    Message msg;
    uint8_t addr[6] = {0x11, 0x22, 0x33, 0x44, 0x55, 0x66};

    /* Check bad pointers trigger an error. */
    assert_error(whad_ble_sniff_adv(NULL, false, 37, addr));
    assert_error(whad_ble_sniff_adv(&msg, false, 37, NULL));

    /* Craft a SniffAdv message. */
    assert_success(whad_ble_sniff_adv(&msg, false, 37, addr));

    /* Check crafted message. */
    assert_eq(msg.which_msg, Message_ble_tag);
    assert_eq(msg.msg.ble.which_msg, WHAD_BLE_SNIFF_ADV);
    assert_eq(msg.msg.ble.msg.sniff_adv.use_ext_adv, false);
    assert(!memcmp(msg.msg.ble.msg.sniff_adv.bd_address, addr, 6));

    /* Success. */
    return PASS;
}

result_t test_sniff_adv_parse(void)
{
    Message msg;
    whad_ble_sniff_adv_params_t params;
    uint8_t addr[6] = {0x11, 0x22, 0x33, 0x44, 0x55, 0x66};

    /* Build message. */
    assert_success(whad_ble_sniff_adv(&msg, false, 37, addr));

    /* Check sanity checks work as expected. */
    assert_error(whad_ble_sniff_adv_parse(NULL, &params));
    assert_error(whad_ble_sniff_adv_parse(&msg, NULL));

    /* Check parsing. */
    assert_success(whad_ble_sniff_adv_parse(&msg, &params));

    /* Check parameters. */
    assert_eq(params.channel, 37);
    assert_eq(params.use_ext_adv, false);
    assert(!memcmp(params.p_bdaddr, addr, 6));
    
    /* Success. */
    return PASS;
}

/**
 * JamAdv
 **/

result_t test_jam_adv(void)
{
    Message msg;

    /* Check sanity check. */
    assert_error(whad_ble_jam_adv(NULL));

    /* Craft message. */
    assert_success(whad_ble_jam_adv(&msg));

    /* Check message. */
    assert_eq(msg.which_msg, Message_ble_tag);
    assert_eq(msg.msg.ble.which_msg, WHAD_BLE_JAM_ADV);

    /* Pass. */
    return PASS;
}

/**
 * JamAdvOnChannel
 **/

result_t test_jam_adv_channel(void) 
{
    Message msg;

    /* Test sanity check. */
    assert_error(whad_ble_jam_adv_channel(NULL, 37));

    /* Craft message. */
    assert_success(whad_ble_jam_adv_channel(&msg, 37));

    /* Check parameters. */
    assert_eq(msg.which_msg, Message_ble_tag);
    assert_eq(msg.msg.ble.which_msg, WHAD_BLE_JAM_ADV_CHANNEL);
    assert_eq(msg.msg.ble.msg.jam_adv_chan.channel, 37);

    /* Passed. */
    return PASS;
}

result_t test_jam_adv_channel_parse(void)
{
    Message msg;
    uint32_t channel;

    /* Create message. */
    assert_success(whad_ble_jam_adv_channel(&msg, 38));

    /* Test sanity checks. */
    assert_error(whad_ble_jam_adv_channel_parse(NULL, &channel));
    assert_error(whad_ble_jam_adv_channel_parse(&msg, NULL));

    /* Parse and check parameters. */
    assert_success(whad_ble_jam_adv_channel_parse(&msg, &channel));
    assert_eq(channel, 38);

    /* Passed. */
    return PASS;
}

/**
 * SniffConnReq
 **/

result_t test_sniff_connreq(void)
{
    Message msg;
    uint8_t addr[6] = {0x11, 0x22, 0x33, 0x44, 0x55, 0x66};

    /* Test sanity checks. */
    assert_error(whad_ble_sniff_conn_req(NULL, false, false, 37, addr));
    assert_error(whad_ble_sniff_conn_req(&msg, false, false, 37, NULL));

    /* Craft message. */
    assert_success(whad_ble_sniff_conn_req(&msg, false, true, 38, addr));

    /* Check message. */
    assert_eq(msg.which_msg, Message_ble_tag);
    assert_eq(msg.msg.ble.which_msg, WHAD_BLE_SNIFF_CONN_REQ);
    assert_eq(msg.msg.ble.msg.sniff_connreq.show_empty_packets, false);
    assert_eq(msg.msg.ble.msg.sniff_connreq.show_advertisements, true);
    assert_eq(msg.msg.ble.msg.sniff_connreq.channel, 38);
    assert(!memcmp(msg.msg.ble.msg.sniff_connreq.bd_address, addr, 6));

    /* Passed. */
    return PASS;
}

result_t test_sniff_connreq_parse(void)
{
    Message msg;
    uint8_t addr[6] = {0x11, 0x22, 0x33, 0x44, 0x55, 0x66};
    whad_ble_sniff_connreq_params_t params;

    /* Craft a SniffConnReq message. */
    assert_success(whad_ble_sniff_conn_req(&msg, false, true, 37, addr));

    /* Test sanity checks. */
    assert_error(whad_ble_sniff_conn_req_parse(NULL, &params));
    assert_error(whad_ble_sniff_conn_req_parse(&msg, NULL));

    /* Parse SniffConnReq message. */
    assert_success(whad_ble_sniff_conn_req_parse(&msg, &params));

    /* Check parameters. */
    assert_eq(params.channel, 37);
    assert_eq(params.show_adv, true);
    assert_eq(params.show_empty_packets, false);
    assert(!memcmp(params.p_bdaddr, addr, 6));

    /* Passed. */
    return PASS;
}

/**
 * SniffAA
 **/

result_t test_sniff_aa(void)
{
    Message msg;
    uint8_t chanmap[5] = {0xff, 0xff, 0xff, 0xff, 0x1f};

    /* Test sanity checks. */
    assert_error(whad_ble_sniff_access_address(NULL, chanmap, BLE_PHY_LE_1M));
    assert_error(whad_ble_sniff_access_address(&msg, NULL, BLE_PHY_LE_1M));

    /* Craft SniffAA message. */
    assert_success(whad_ble_sniff_access_address(&msg, chanmap, BLE_PHY_LE_1M));

    /* Check message. */
    assert_eq(msg.which_msg, Message_ble_tag);
    assert_eq(msg.msg.ble.which_msg, ble_Message_sniff_aa_tag);
    assert_eq(msg.msg.ble.msg.sniff_aa.phy, BLE_PHY_LE_1M);
    assert(!memcmp(msg.msg.ble.msg.sniff_aa.monitored_channels, chanmap, 5));

    /* Passed. */
    return PASS;
}

result_t test_sniff_aa_parse(void)
{
    Message msg;
    uint8_t chanmap[5] = {0xff, 0xff, 0xff, 0xff, 0x1f};
    uint8_t out_chanmap[5];
    whad_ble_phy_t out_phy;

    /* Create a SniffAA message. */
    assert_success(whad_ble_sniff_access_address(&msg, chanmap, BLE_PHY_LE_2M));

    /* Test sanity checks. */
    assert_error(whad_ble_sniff_access_address_parse(NULL, out_chanmap, &out_phy));
    assert_error(whad_ble_sniff_access_address_parse(&msg, NULL, &out_phy));
    assert_error(whad_ble_sniff_access_address_parse(&msg, out_chanmap, NULL));

    /* Parse message. */
    assert_success(whad_ble_sniff_access_address_parse(&msg, out_chanmap, &out_phy));

    /* Check parameters. */
    assert_eq(out_phy, BLE_PHY_LE_2M);
    assert(!memcmp(out_chanmap, chanmap, 5));

    /* Passed. */
    return PASS;
}

/* Sniff active connection */

result_t test_sniff_active_conn(void)
{
    Message msg;
    uint8_t channels[5] = {0xff, 0xff, 0xff, 0xff, 0x1f};

    /* Test sanity checks. */
    assert_error(whad_ble_sniff_active_conn(NULL, 0, 0, 0, 0, channels, channels, BLE_PHY_LE_1M));
    assert_error(whad_ble_sniff_active_conn(&msg, 0, 0, 0, 0, NULL, channels, BLE_PHY_LE_1M));
    assert_error(whad_ble_sniff_active_conn(&msg, 0, 0, 0, 0, channels, NULL, BLE_PHY_LE_1M));

    /* Craft SniffActiveCon message. */
    assert_success(whad_ble_sniff_active_conn(&msg, 0x11223344, 0x556677, 6, 11, channels, channels,
            BLE_PHY_LE_1M));

    /* Check message. */
    assert_eq(msg.which_msg, Message_ble_tag);
    assert_eq(msg.msg.ble.which_msg, ble_Message_sniff_conn_tag);
    assert_eq(msg.msg.ble.msg.sniff_conn.access_address, 0x11223344);
    assert_eq(msg.msg.ble.msg.sniff_conn.crc_init, 0x556677);
    assert_eq(msg.msg.ble.msg.sniff_conn.hop_interval, 6);
    assert_eq(msg.msg.ble.msg.sniff_conn.hop_increment, 11);
    assert_eq(msg.msg.ble.msg.sniff_conn.phy, BLE_PHY_LE_1M);
    assert(!memcmp(msg.msg.ble.msg.sniff_conn.channel_map, channels, 5));
    assert(!memcmp(msg.msg.ble.msg.sniff_conn.monitored_channels, channels, 5));

    /* Passed. */
    return PASS;
}

result_t test_sniff_active_conn_parse(void)
{
    Message msg;
    uint8_t channels[5] = {0xaa, 0xbb, 0xcc, 0xdd, 0xee};
    whad_ble_sniff_conn_params_t params;

    /* Create a SniffActiveCon message. */
    assert_success(whad_ble_sniff_active_conn(&msg, 0x11223344, 0x556677, 6, 11, channels, channels, BLE_PHY_LE_2M));

    /* Test sanity checks. */
    assert_error(whad_ble_sniff_active_conn_parse(NULL, &params));
    assert_error(whad_ble_sniff_active_conn_parse(&msg, NULL));

    /* Parse message. */
    assert_success(whad_ble_sniff_active_conn_parse(&msg, &params));

    /* Check parameters. */
    assert_eq(params.access_address, 0x11223344);
    assert_eq(params.crc_init, 0x556677);
    assert_eq(params.hop_interval, 6);
    assert_eq(params.hop_increment, 11);
    assert_eq(params.phy, BLE_PHY_LE_2M);
    assert(!memcmp(params.channelmap, channels, 5));
    assert(!memcmp(params.channels, channels, 5));

    /* Passed. */
    return PASS;
}

/* Jam active connection. */

result_t test_jam_active_conn(void)
{
    Message msg;

    /* Test sanity check. */
    assert_error(whad_ble_jam_active_conn(NULL, 0x11223344, BLE_PHY_LE_1M));

    /* Craft a JamActiveConn message. */
    assert_success(whad_ble_jam_active_conn(&msg, 0x11223344, BLE_PHY_LE_2M));

    /* Check message structure. */
    assert_eq(msg.which_msg, Message_ble_tag);
    assert_eq(msg.msg.ble.which_msg, ble_Message_jam_conn_tag);
    assert_eq(msg.msg.ble.msg.jam_conn.access_address, 0x11223344);
    assert_eq(msg.msg.ble.msg.jam_conn.phy, BLE_PHY_LE_2M);

    /* Passed. */
    return PASS;
}

result_t test_jam_active_conn_parse(void)
{
    Message msg;
    uint32_t access_address = 0;
    whad_ble_phy_t phy = BLE_PHY_UNDEFINED;

    /* Test sanity checks. */
    assert_error(whad_ble_jam_active_conn_parse(NULL, &access_address, &phy));
    assert_error(whad_ble_jam_active_conn_parse(&msg, NULL, &phy));
    assert_error(whad_ble_jam_active_conn_parse(&msg, &access_address, NULL));

    /* Craft a valid JamActiveConn message. */
    assert_success(whad_ble_jam_active_conn(&msg, 0x11223344, BLE_PHY_LE_2M));

    /* Check parsing. */
    assert_success(whad_ble_jam_active_conn_parse(&msg, &access_address, &phy));
    assert_eq(access_address, 0x11223344);
    assert_eq(phy, BLE_PHY_LE_2M);

    /* Passed. */
    return PASS;
}

/* Scan mode */

result_t test_scan_mode(void)
{
    Message msg;

    /* Test sanity check. */
    assert_error(whad_ble_scan_mode(NULL, false, 0, false));
    
    /* Craft a ScanMode message. */
    assert_success(whad_ble_scan_mode(&msg, true, 100, false));

    /* Check message. */
    assert_eq(msg.which_msg, Message_ble_tag);
    assert_eq(msg.msg.ble.which_msg, ble_Message_scan_mode_tag);
    assert_eq(msg.msg.ble.msg.scan_mode.active_scan, true);
    assert_eq(msg.msg.ble.msg.scan_mode.interval, 100);
    assert_eq(msg.msg.ble.msg.scan_mode.use_ext_adv, false);

    /* Passed. */
    return PASS;
}

result_t test_scan_mode_parse(void)
{
    Message msg;
    bool active = false, use_ext_adv = false;
    uint32_t interval = 0;

    /* Test sanity checks. */
    assert_error(whad_ble_scan_mode_parse(NULL, &active, &interval, &use_ext_adv));
    assert_error(whad_ble_scan_mode_parse(&msg, NULL, &interval, &use_ext_adv));
    assert_error(whad_ble_scan_mode_parse(&msg, &active, NULL, &use_ext_adv));
    assert_error(whad_ble_scan_mode_parse(&msg, &active, &interval, NULL));

    /* Craft a valid ScanMode message. */
    assert_success(whad_ble_scan_mode(&msg, true, 100, false));

    /* Parse and check parameters. */
    assert_success(whad_ble_scan_mode_parse(&msg, &active, &interval, &use_ext_adv));
    assert_eq(active, true);
    assert_eq(interval, 100);
    assert_eq(use_ext_adv, false);

    /* Passed. */
    return PASS;
}

/* AdvMode */

result_t test_adv_mode_legacy(void)
{
    Message msg;
    uint8_t chanmap[5] = {0x00, 0x00, 0x00, 0x00, 0xe0};
    uint8_t bad_chanmap[5] = {0x00, 0x00, 0x00, 0x00, 0x03};
    uint8_t adv_data[] = {0x02, 0x01, 0x06};
    uint8_t scanrsp_data[] = {0x05, 0x09, 0x41, 0x42, 0x43, 0x44};

    /* Test sanity checks. */
    assert_error(whad_ble_adv_mode(NULL, BLE_ADV_IND, 200, 4000, chanmap, adv_data, 3, 
                scanrsp_data, 6, BLE_CSA1, NULL, 0));
    assert_error(whad_ble_adv_mode(&msg, BLE_ADV_IND, 200, 4000, chanmap, NULL, 3, 
                scanrsp_data, 6, BLE_CSA1, NULL, 0));
    assert_error(whad_ble_adv_mode(&msg, BLE_ADV_IND, 200, 4000, chanmap, adv_data, 3, 
                NULL, 6, BLE_CSA1, NULL, 0));

    /* Check bad channel map. */
    assert_error(whad_ble_adv_mode(&msg, BLE_ADV_IND, 200, 4000, bad_chanmap, adv_data, 3, 
                scanrsp_data, 6, BLE_CSA1, NULL, 0));

    /* Craft a valid AdvMode message. */
    assert_success(whad_ble_adv_mode(&msg, BLE_ADV_IND, 200, 4000, chanmap, adv_data, 3,
                scanrsp_data, 6, BLE_CSA1, NULL, 0));

    /* Check message. */
    assert_eq(msg.which_msg, Message_ble_tag);
    assert_eq(msg.msg.ble.which_msg, ble_Message_adv_mode_tag);
    assert_eq(msg.msg.ble.msg.adv_mode.adv_type, BLE_ADV_IND);
    assert_eq(msg.msg.ble.msg.adv_mode.csa, BLE_CSA1);
    assert_eq(msg.msg.ble.msg.adv_mode.inter_min, 200);
    assert_eq(msg.msg.ble.msg.adv_mode.inter_max, 4000);
    assert_eq(msg.msg.ble.msg.adv_mode.adv_data.size, 3);
    assert(!memcmp(msg.msg.ble.msg.adv_mode.adv_data.bytes, adv_data, 3));
    assert_eq(msg.msg.ble.msg.adv_mode.scanrsp_data.size, 6);
    assert(!memcmp(msg.msg.ble.msg.adv_mode.scanrsp_data.bytes, scanrsp_data, 6));
    assert_eq(msg.msg.ble.msg.adv_mode.ext_pdus_count, 0);
    assert(!memcmp(msg.msg.ble.msg.adv_mode.channel_map, chanmap, 5)); 

    /* Craft a valid AdvMode message with no channel map. */
    assert_success(whad_ble_adv_mode(&msg, BLE_ADV_IND, 200, 4000, NULL, adv_data, 3,
                scanrsp_data, 6, BLE_CSA1, NULL, 0));
    assert(!memcmp(msg.msg.ble.msg.adv_mode.channel_map, chanmap, 5));

    /* Passed. */
    return PASS;
}

result_t test_adv_mode_legacy_parse(void)
{
    Message msg;
    uint8_t chanmap[5] = {0x00, 0x00, 0x00, 0x00, 0xe0};
    uint8_t adv_data[] = {0x02, 0x01, 0x06};
    uint8_t scanrsp_data[] = {0x05, 0x09, 0x41, 0x42, 0x43, 0x44};
    whad_ble_adv_mode_params_t params;

    /* Test sanity checks. */
    assert_error(whad_ble_adv_mode_parse(NULL, &params));
    assert_error(whad_ble_adv_mode_parse(&msg, NULL));


    /* Craft a valid AdvMode message. */
    assert_success(whad_ble_adv_mode(&msg, BLE_ADV_IND, 200, 4000, NULL, adv_data, 3,
                scanrsp_data, 6, BLE_CSA1, NULL, 0));

    /* Parse and check parameters. */
    assert_success(whad_ble_adv_mode_parse(&msg, &params));
    assert_eq(params.adv_type, BLE_ADV_IND);
    assert_eq(params.inter_min, 200);
    assert_eq(params.inter_max, 4000);
    assert_eq(params.adv_data_length, 3);
    assert_eq(params.scanrsp_data_length, 6);
    assert(!memcmp(params.adv_data, adv_data, 3));
    assert(!memcmp(params.scanrsp_data, scanrsp_data, 6));
    assert(!memcmp(params.channel_map, chanmap, 5));

    /* Passed. */
    return PASS;
}

result_t test_adv_mode_ext(void)
{
    Message msg;
    uint8_t chanmap[5] = {0x00, 0x00, 0x00, 0x00, 0xe0};
    uint8_t bad_chanmap[5] = {0x00, 0x00, 0x00, 0x00, 0x03};
    uint8_t adv_data[] = {0x02, 0x01, 0x06};
    uint8_t scanrsp_data[] = {0x05, 0x09, 0x41, 0x42, 0x43, 0x44};
    whad_ble_ext_adv_t ext_pdus[] = {
        {3, {0x02, 0x01, 0x06}, false, {0, 0, 0, 0, BLE_PHY_UNDEFINED}},
        {6, {0x05, 0x09, 0x41, 0x42, 0x43, 0x44}, false, {0, 0, 0, 0, BLE_PHY_UNDEFINED}}
    };

    /* Test sanity checks. */
    assert_error(whad_ble_adv_mode(NULL, BLE_ADV_IND, 200, 4000, chanmap, adv_data, 3, 
                scanrsp_data, 6, BLE_CSA1, NULL, 0));
    assert_error(whad_ble_adv_mode(&msg, BLE_ADV_IND, 200, 4000, chanmap, NULL, 3, 
                scanrsp_data, 6, BLE_CSA1, NULL, 0));
    assert_error(whad_ble_adv_mode(&msg, BLE_ADV_IND, 200, 4000, chanmap, adv_data, 3, 
                NULL, 6, BLE_CSA1, NULL, 0));

    /* Check bad channel map. */
    assert_error(whad_ble_adv_mode(&msg, BLE_ADV_IND, 200, 4000, bad_chanmap, adv_data, 3, 
                scanrsp_data, 6, BLE_CSA1, NULL, 0));

    /* Craft a valid AdvMode message. */
    assert_success(whad_ble_adv_mode(&msg, BLE_ADV_IND, 200, 4000, chanmap, adv_data, 3,
                scanrsp_data, 6, BLE_CSA1, ext_pdus, 2));
    /* Check message. */
    assert_eq(msg.which_msg, Message_ble_tag);
    assert_eq(msg.msg.ble.which_msg, ble_Message_adv_mode_tag);
    assert_eq(msg.msg.ble.msg.adv_mode.adv_type, BLE_ADV_IND);
    assert_eq(msg.msg.ble.msg.adv_mode.csa, BLE_CSA1);
    assert_eq(msg.msg.ble.msg.adv_mode.inter_min, 200);
    assert_eq(msg.msg.ble.msg.adv_mode.inter_max, 4000);
    assert_eq(msg.msg.ble.msg.adv_mode.adv_data.size, 3);
    assert(!memcmp(msg.msg.ble.msg.adv_mode.adv_data.bytes, adv_data, 3));
    assert_eq(msg.msg.ble.msg.adv_mode.scanrsp_data.size, 6);
    assert(!memcmp(msg.msg.ble.msg.adv_mode.scanrsp_data.bytes, scanrsp_data, 6));
    assert(!memcmp(msg.msg.ble.msg.adv_mode.channel_map, chanmap, 5)); 

    /* Check extended PDUs. */
    assert_eq(msg.msg.ble.msg.adv_mode.ext_pdus_count, 2);
    assert_eq(msg.msg.ble.msg.adv_mode.ext_pdus[0].has_aux_ptr, false);
    assert_eq(msg.msg.ble.msg.adv_mode.ext_pdus[0].adv_data.size, 3);
    assert(!memcmp(msg.msg.ble.msg.adv_mode.ext_pdus[0].adv_data.bytes, ext_pdus[0].adv_data, 3));
    assert_eq(msg.msg.ble.msg.adv_mode.ext_pdus[1].has_aux_ptr, false);
    assert_eq(msg.msg.ble.msg.adv_mode.ext_pdus[1].adv_data.size, 6);
    assert(!memcmp(msg.msg.ble.msg.adv_mode.ext_pdus[1].adv_data.bytes, ext_pdus[1].adv_data, 6));

    /* Craft a valid AdvMode message with no channel map. */
    assert_success(whad_ble_adv_mode(&msg, BLE_ADV_IND, 200, 4000, NULL, adv_data, 3,
                scanrsp_data, 6, BLE_CSA1, NULL, 0));
    assert(!memcmp(msg.msg.ble.msg.adv_mode.channel_map, chanmap, 5));

    /* Passed. */
    return PASS;
}

result_t test_adv_mode_ext_parse(void)
{
    Message msg;
    uint8_t chanmap[5] = {0x00, 0x00, 0x00, 0x00, 0xe0};
    uint8_t adv_data[] = {0x02, 0x01, 0x06};
    uint8_t scanrsp_data[] = {0x05, 0x09, 0x41, 0x42, 0x43, 0x44};
    whad_ble_ext_adv_t ext_pdus[] = {
        {3, {0x02, 0x01, 0x06}, false, {0, 0, 0, 0, BLE_PHY_UNDEFINED}},
        {6, {0x05, 0x09, 0x41, 0x42, 0x43, 0x44}, false, {0, 0, 0, 0, BLE_PHY_UNDEFINED}}
    };
    whad_ble_adv_mode_params_t params;

    /* Test sanity checks. */
    assert_error(whad_ble_adv_mode_parse(NULL, &params));
    assert_error(whad_ble_adv_mode_parse(&msg, NULL));


    /* Craft a valid AdvMode message. */
    assert_success(whad_ble_adv_mode(&msg, BLE_ADV_IND, 200, 4000, NULL, adv_data, 3,
                scanrsp_data, 6, BLE_CSA1, ext_pdus, 2));

    /* Parse and check parameters. */
    assert_success(whad_ble_adv_mode_parse(&msg, &params));
    assert_eq(params.adv_type, BLE_ADV_IND);
    assert_eq(params.inter_min, 200);
    assert_eq(params.inter_max, 4000);
    assert_eq(params.adv_data_length, 3);
    assert_eq(params.scanrsp_data_length, 6);
    assert(!memcmp(params.adv_data, adv_data, 3));
    assert(!memcmp(params.scanrsp_data, scanrsp_data, 6));
    assert(!memcmp(params.channel_map, chanmap, 5));

    /* TODO: check extended PDUs. */


    /* Passed. */
    return PASS;
}


/* SetAdvData (seems discarded at the moment, need to figure out what's going on) */

result_t test_set_adv_data(void)
{
    Message msg;
    uint8_t adv_data[] = {0x02, 0x06, 0x01};
    uint8_t scanrsp_data[] = {0x05, 0x09, 0x41, 0x42, 0x43, 0x44};

    /* Test sanity checks. */
    assert_error(whad_ble_set_adv_data(NULL, adv_data, 3, scanrsp_data, 6));
    assert_error(whad_ble_set_adv_data(&msg, NULL, 3, scanrsp_data, 6));
    assert_error(whad_ble_set_adv_data(&msg, adv_data, 3, NULL, 6));

    /* Craft a valid SetAdvData message. */
    assert_success(whad_ble_set_adv_data(&msg, adv_data, 3, scanrsp_data, 6));

    /* Check message. */
    assert_eq(msg.which_msg, Message_ble_tag);
    assert_eq(msg.msg.ble.which_msg, ble_Message_set_adv_data_tag);
    assert_eq(BLE_MSG(msg).set_adv_data.adv_data.size, 3);
    assert_eq(BLE_MSG(msg).set_adv_data.scanrsp_data.size, 6);
    assert(!memcmp(BLE_MSG(msg).set_adv_data.adv_data.bytes, adv_data, 3));
    assert(!memcmp(BLE_MSG(msg).set_adv_data.scanrsp_data.bytes, scanrsp_data, 6));

    /* Passed. */
    return PASS;
}

/* TODO: SetAdvData parsing. */

/* Central Mode. */

result_t test_central_mode(void)
{
    Message msg;

    /* Test sanity checks. */
    assert_error(whad_ble_central_mode(NULL));

    /* Craft a valid CentralMode message. */
    assert_success(whad_ble_central_mode(&msg));

    /* Check message. */
    assert_eq(msg.which_msg, Message_ble_tag);
    assert_eq(msg.msg.ble.which_msg, ble_Message_central_mode_tag);

    /* Passed. */
    return PASS;
}

/* ConnectTo message. */

result_t test_connect_to(void)
{
    Message msg;
    uint8_t bd_addr[] = {0x11, 0x22, 0x33, 0x44, 0x55, 0x66};
    uint8_t chanmap[] = {0xff, 0xff, 0xff, 0xff, 0x1f};

    /* Test sanity checks. */
    assert_error(whad_ble_connect_to(NULL, bd_addr, BLE_ADDR_RANDOM, 0, NULL, 6, 11, 0, BLE_CSA1));
    assert_error(whad_ble_connect_to(&msg, NULL, BLE_ADDR_RANDOM, 0, NULL, 6, 11, 0, BLE_CSA1));

    /* Craft a valid ConnectTo message. */
    assert_success(whad_ble_connect_to(&msg, bd_addr, BLE_ADDR_RANDOM, 0x11223344, chanmap, 6, 11, 0, BLE_CSA1));

    /* Check message. */
    assert_eq(msg.which_msg, Message_ble_tag);
    assert_eq(msg.msg.ble.which_msg, ble_Message_connect_tag);
    assert_eq(BLE_MSG(msg).connect.csa, BLE_CSA1);
    assert_eq(BLE_MSG(msg).connect.addr_type, BLE_ADDR_RANDOM);
    assert_eq(BLE_MSG(msg).connect.has_access_address, true);
    assert_eq(BLE_MSG(msg).connect.access_address, 0x11223344);
    assert_eq(BLE_MSG(msg).connect.has_channel_map, true);
    assert(!memcmp(BLE_MSG(msg).connect.channel_map, chanmap, 5));
    assert_eq(BLE_MSG(msg).connect.has_hop_interval, true);
    assert_eq(BLE_MSG(msg).connect.hop_interval, 6);
    assert_eq(BLE_MSG(msg).connect.has_hop_increment, true);
    assert_eq(BLE_MSG(msg).connect.hop_increment, 11);
    assert_eq(BLE_MSG(msg).connect.has_crc_init, false);

    /* Passed. */
    return PASS;
}

result_t test_connect_to_parse(void)
{
    Message msg;
    uint8_t bd_addr[] = {0x11, 0x22, 0x33, 0x44, 0x55, 0x66};
    uint8_t chanmap[] = {0xff, 0xff, 0xff, 0xff, 0x1f};
    whad_ble_connect_params_t params;

    /* Test sanity checks. */
    assert_error(whad_ble_connect_to_parse(NULL, &params));
    assert_error(whad_ble_connect_to_parse(&msg, NULL));

    /* Craft a valid ConnectTo message. */
    assert_success(whad_ble_connect_to(&msg, bd_addr, BLE_ADDR_RANDOM, 0x11223344, chanmap, 6, 11, 0, BLE_CSA1));

    /* Parse ConnectTo message and check parameters. */
    assert_success(whad_ble_connect_to_parse(&msg, &params));
    assert_eq(params.addr_type, BLE_ADDR_RANDOM);
    assert_eq(params.access_address, 0x11223344);
    assert_eq(params.hop_interval, 6);
    assert_eq(params.hop_increment, 11);
    assert_eq(params.crc_init, 0);
    assert(!memcmp(params.channelmap, chanmap, 5));

    /* Passed. */
    return PASS;
}

/* Disconnect message. */

result_t test_disconnect(void)
{
    Message msg;

    /* Test sanity check. */
    assert_error(whad_ble_disconnect(NULL, 0));

    /* Craft valid Disconnect message. */
    assert_success(whad_ble_disconnect(&msg, 42));

    /* Check message. */
    assert_eq(msg.which_msg, Message_ble_tag);
    assert_eq(msg.msg.ble.which_msg, ble_Message_disconnect_tag);
    assert_eq(BLE_MSG(msg).disconnect.conn_handle, 42);

    /* Passed. */
    return PASS;
}

result_t test_disconnect_parse(void)
{
    Message msg;
    uint32_t conn_handle = 0;

    /* Test sanity checks. */
    assert_error(whad_ble_disconnect_parse(NULL, &conn_handle));
    assert_error(whad_ble_disconnect_parse(&msg, NULL));

    /* Craft valid Disconnect message. */
    assert_success(whad_ble_disconnect(&msg, 1));

    /* Parse and check conn handle. */
    assert_success(whad_ble_disconnect_parse(&msg, &conn_handle));
    assert_eq(conn_handle, 1);

    /* Passed. */
    return PASS;
}

/* Start and Stop. */

result_t test_start(void)
{
    Message msg;

    /* Test sanity check. */
    assert_error(whad_ble_start(NULL));

    /* Craft a Start message and check. */
    assert_success(whad_ble_start(&msg));
    assert_eq(msg.which_msg, Message_ble_tag);
    assert_eq(msg.msg.ble.which_msg, ble_Message_start_tag);

    /* Passed. */
    return PASS;
}

result_t test_stop(void)
{
    Message msg;

    /* Test sanity check. */
    assert_error(whad_ble_stop(NULL));

    /* Craft a Start message and check. */
    assert_success(whad_ble_stop(&msg));
    assert_eq(msg.which_msg, Message_ble_tag);
    assert_eq(msg.msg.ble.which_msg, ble_Message_stop_tag);

    /* Passed. */
    return PASS;
}

/* Hijack Master */

result_t test_hijack_master(void)
{
    Message msg;
    uint32_t aa = 0;

    /* Test sanity check. */
    assert_error(whad_ble_hijack_master(NULL, 0));

    /* Craft a valid HijackMaster message. */
    assert_success(whad_ble_hijack_master(&msg, 0x11223344));
    
    /* Check message. */
    assert_eq(msg.which_msg, Message_ble_tag);
    assert_eq(msg.msg.ble.which_msg, ble_Message_hijack_master_tag);
    assert_eq(BLE_MSG(msg).hijack_master.access_address, 0x11223344);

    /* Passed. */
    return PASS;
}

result_t test_hijack_master_parse(void)
{
    Message msg;
    uint32_t aa = 0;

    /* Test sanity checks. */
    assert_error(whad_ble_hijack_master_parse(NULL, &aa));
    assert_error(whad_ble_hijack_master_parse(&msg, NULL));

    /* Craft a valid HijackMaster message. */
    assert_success(whad_ble_hijack_master(&msg, 0x11223344));

    /* Parse and check parameters. */
    assert_success(whad_ble_hijack_master_parse(&msg, &aa));
    assert_eq(aa, 0x11223344);

    /* Passed. */
    return PASS;
}

/* Hijack Slave */

result_t test_hijack_slave(void)
{
    Message msg;
    uint32_t aa = 0;

    /* Test sanity check. */
    assert_error(whad_ble_hijack_slave(NULL, 0));

    /* Craft a valid HijackSlave message. */
    assert_success(whad_ble_hijack_slave(&msg, 0x11223344));
    
    /* Check message. */
    assert_eq(msg.which_msg, Message_ble_tag);
    assert_eq(msg.msg.ble.which_msg, ble_Message_hijack_slave_tag);
    assert_eq(BLE_MSG(msg).hijack_slave.access_address, 0x11223344);

    /* Passed. */
    return PASS;
}

result_t test_hijack_slave_parse(void)
{
    Message msg;
    uint32_t aa = 0;

    /* Test sanity checks. */
    assert_error(whad_ble_hijack_slave_parse(NULL, &aa));
    assert_error(whad_ble_hijack_slave_parse(&msg, NULL));

    /* Craft a valid HijackSlave message. */
    assert_success(whad_ble_hijack_slave(&msg, 0x11223344));

    /* Parse and check parameters. */
    assert_success(whad_ble_hijack_slave_parse(&msg, &aa));
    assert_eq(aa, 0x11223344);

    /* Passed. */
    return PASS;
}

/* Hijack Both */

result_t test_hijack_both(void)
{
    Message msg;
    uint32_t aa = 0;

    /* Test sanity check. */
    assert_error(whad_ble_hijack_both(NULL, 0));

    /* Craft a valid HijackBoth message. */
    assert_success(whad_ble_hijack_both(&msg, 0x11223344));
    
    /* Check message. */
    assert_eq(msg.which_msg, Message_ble_tag);
    assert_eq(msg.msg.ble.which_msg, ble_Message_hijack_both_tag);
    assert_eq(BLE_MSG(msg).hijack_both.access_address, 0x11223344);

    /* Passed. */
    return PASS;
}

result_t test_hijack_both_parse(void)
{
    Message msg;
    uint32_t aa = 0;

    /* Test sanity checks. */
    assert_error(whad_ble_hijack_both_parse(NULL, &aa));
    assert_error(whad_ble_hijack_both_parse(&msg, NULL));

    /* Craft a valid HijackBoth message. */
    assert_success(whad_ble_hijack_both(&msg, 0x11223344));

    /* Parse and check parameters. */
    assert_success(whad_ble_hijack_both_parse(&msg, &aa));
    assert_eq(aa, 0x11223344);

    /* Passed. */
    return PASS;
}

/* BLE PDU */

result_t test_pdu(void)
{
    Message msg;
    uint8_t pdu[] = {0x02, 0x07, 0x03, 0x00, 0x04, 0x00, 0x0A, 0x03, 0x00};

    /* Test sanity checks. */
    assert_error(whad_ble_pdu(NULL, pdu, 9, BLE_SLAVE_TO_MASTER, 42, false, false, BLE_PHY_LE_1M)); 
    assert_error(whad_ble_pdu(&msg, NULL, 9, BLE_SLAVE_TO_MASTER, 42, false, false, BLE_PHY_LE_1M)); 

    /* Craft a valid BlePdu message. */
    assert_success(whad_ble_pdu(&msg, pdu, 9, BLE_SLAVE_TO_MASTER, 42, false, false, BLE_PHY_LE_1M));

    /* Check message. */
    assert_eq(msg.which_msg, Message_ble_tag);
    assert_eq(msg.msg.ble.which_msg, ble_Message_pdu_tag);
    assert_eq(BLE_MSG(msg).pdu.processed, 0);
    assert_eq(BLE_MSG(msg).pdu.decrypted, 0);
    assert_eq(BLE_MSG(msg).pdu.direction, BLE_SLAVE_TO_MASTER);
    assert_eq(BLE_MSG(msg).pdu.conn_handle, 42);
    assert_eq(BLE_MSG(msg).pdu.phy, BLE_PHY_LE_1M);
    assert_eq(BLE_MSG(msg).pdu.pdu.size, 9);
    assert(!memcmp(BLE_MSG(msg).pdu.pdu.bytes, pdu, 9));

    /* Passed. */
    return PASS;
}

result_t test_pdu_parse(void)
{
    Message msg;
    uint8_t pdu[] = {0x02, 0x07, 0x03, 0x00, 0x04, 0x00, 0x0A, 0x03, 0x00};
    whad_ble_pdu_t params;

    /* Test sanity checks. */
    assert_error(whad_ble_pdu_parse(NULL, &params));
    assert_error(whad_ble_pdu_parse(&msg, NULL));

    /* Parse and check parameters. */
    assert_success(whad_ble_pdu(&msg, pdu, 9, BLE_SLAVE_TO_MASTER, 42, false, false, BLE_PHY_LE_1M));
    assert_success(whad_ble_pdu_parse(&msg, &params));
    assert_eq(params.conn_handle, 42);
    assert_eq(params.processed, 0);
    assert_eq(params.decrypted, 0);
    assert_eq(params.pdu_length, 9);
    assert_eq(params.phy, BLE_PHY_LE_1M);
    assert(!memcmp(params.p_pdu, pdu, params.pdu_length));

    /* Passed. */
    return PASS;
}

/* BLE raw PDU */

result_t test_raw_pdu(void)
{
    Message msg;
    uint8_t pdu[] = {0x02, 0x07, 0x03, 0x00, 0x04, 0x00, 0x0A, 0x03, 0x00};

    /* Test sanity checks. */
    assert_error(whad_ble_raw_pdu(NULL, 0, 0, 0, 0, pdu, 0, 0, 0, 0, 0, BLE_SLAVE_TO_MASTER, false, false, true, BLE_PHY_LE_1M));
    assert_error(whad_ble_raw_pdu(&msg, 0, 0, 0, 0, NULL, 0, 0, 0, 0, 0, BLE_SLAVE_TO_MASTER, false, false, true, BLE_PHY_LE_1M));

    /* Craft a valid raw PDU message. */
    assert_success(whad_ble_raw_pdu(&msg, 10, -52, 1, 0x11223344, pdu, 9, 0x556677, true, 12345, 6789, BLE_SLAVE_TO_MASTER, false, false, true, BLE_PHY_LE_1M));

    /* Check message. */
    assert_eq(msg.which_msg, Message_ble_tag);
    assert_eq(msg.msg.ble.which_msg, ble_Message_raw_pdu_tag);
    assert_eq(BLE_MSG(msg).raw_pdu.channel, 10);
    assert_eq(BLE_MSG(msg).raw_pdu.access_address, 0x11223344);
    assert_eq(BLE_MSG(msg).raw_pdu.conn_handle, 1);
    assert_eq(BLE_MSG(msg).raw_pdu.direction, BLE_SLAVE_TO_MASTER);
    assert_eq(BLE_MSG(msg).raw_pdu.phy, BLE_PHY_LE_1M);
    assert_eq(BLE_MSG(msg).raw_pdu.has_timestamp, true);
    assert_eq(BLE_MSG(msg).raw_pdu.timestamp, 12345);
    assert_eq(BLE_MSG(msg).raw_pdu.has_relative_timestamp, true);
    assert_eq(BLE_MSG(msg).raw_pdu.relative_timestamp, 6789);
    assert_eq(BLE_MSG(msg).raw_pdu.crc, 0x556677);
    assert_eq(BLE_MSG(msg).raw_pdu.has_crc_validity, true);
    assert_eq(BLE_MSG(msg).raw_pdu.crc_validity, true);
    assert_eq(BLE_MSG(msg).raw_pdu.has_rssi, true);
    assert_eq(BLE_MSG(msg).raw_pdu.rssi, -52);
    assert_eq(BLE_MSG(msg).raw_pdu.processed, false);
    assert_eq(BLE_MSG(msg).raw_pdu.decrypted, false);


    /* Passed. */
    return PASS;
}

/* SendRawPdu */

result_t test_send_raw_pdu(void)
{
    Message msg;
    uint8_t pdu[] = {0x03, 0x02, 0x01};

    /* Test sanity checks. */
    assert_error(whad_ble_send_raw_pdu(NULL, BLE_MASTER_TO_SLAVE, 7,
                                      0x11223344, pdu, 3, 0x556677, true,
                                      BLE_PHY_LE_2M));
    assert_error(whad_ble_send_raw_pdu(&msg, BLE_MASTER_TO_SLAVE, 7,
                                      0x11223344, NULL, 3, 0x556677, true,
                                      BLE_PHY_LE_2M));

    /* Craft a valid SendRawPdu message. */
    assert_success(whad_ble_send_raw_pdu(&msg, BLE_MASTER_TO_SLAVE, 7,
                                        0x11223344, pdu, 3, 0x556677, true,
                                        BLE_PHY_LE_2M));

    /* Check message structure and parameters. */
    assert_eq(msg.which_msg, Message_ble_tag);
    assert_eq(msg.msg.ble.which_msg, ble_Message_send_raw_pdu_tag);
    assert_eq(BLE_MSG(msg).send_raw_pdu.direction, BLE_MASTER_TO_SLAVE);
    assert_eq(BLE_MSG(msg).send_raw_pdu.conn_handle, 7);
    assert_eq(BLE_MSG(msg).send_raw_pdu.access_address, 0x11223344);
    assert_eq(BLE_MSG(msg).send_raw_pdu.pdu.size, 3);
    assert(!memcmp(BLE_MSG(msg).send_raw_pdu.pdu.bytes, pdu, 3));
    assert_eq(BLE_MSG(msg).send_raw_pdu.crc, 0x556677);
    assert_eq(BLE_MSG(msg).send_raw_pdu.encrypt, true);
    assert_eq(BLE_MSG(msg).send_raw_pdu.phy, BLE_PHY_LE_2M);

    /* Passed. */
    return PASS;
}

result_t test_send_raw_pdu_parse(void)
{
    Message msg;
    uint8_t pdu[] = {0x03, 0x02, 0x01};
    whad_ble_pdu_params_t params;

    assert_error(whad_ble_send_raw_pdu_parse(NULL, &params));
    assert_error(whad_ble_send_raw_pdu_parse(&msg, NULL));

    assert_success(whad_ble_send_raw_pdu(&msg, BLE_MASTER_TO_SLAVE, 7,
                                        0x11223344, pdu, 3, 0x556677, true,
                                        BLE_PHY_LE_2M));
    assert_success(whad_ble_send_raw_pdu_parse(&msg, &params));
    assert_eq(params.direction, BLE_MASTER_TO_SLAVE);
    assert_eq(params.conn_handle, 7);
    assert_eq(params.access_address, 0x11223344);
    assert_eq(params.length, 3);
    assert(!memcmp(params.p_pdu, pdu, params.length));
    assert_eq(params.crc, 0x556677);
    assert_eq(params.encrypt, true);
    assert_eq(params.phy, BLE_PHY_LE_2M);

    return PASS;
}

/* SendPdu */

result_t test_send_pdu(void)
{
    Message msg;
    uint8_t pdu[] = {0x01, 0x02, 0x03, 0x04};

    assert_error(whad_ble_send_pdu(NULL, BLE_SLAVE_TO_MASTER, 9, pdu, 4,
                                  false, BLE_PHY_LE_1M));
    assert_error(whad_ble_send_pdu(&msg, BLE_SLAVE_TO_MASTER, 9, NULL, 4,
                                  false, BLE_PHY_LE_1M));

    assert_success(whad_ble_send_pdu(&msg, BLE_SLAVE_TO_MASTER, 9, pdu, 4,
                                    false, BLE_PHY_LE_1M));
    assert_eq(msg.which_msg, Message_ble_tag);
    assert_eq(msg.msg.ble.which_msg, ble_Message_send_pdu_tag);
    assert_eq(BLE_MSG(msg).send_pdu.direction, BLE_SLAVE_TO_MASTER);
    assert_eq(BLE_MSG(msg).send_pdu.conn_handle, 9);
    assert_eq(BLE_MSG(msg).send_pdu.pdu.size, 4);
    assert(!memcmp(BLE_MSG(msg).send_pdu.pdu.bytes, pdu, 4));
    assert_eq(BLE_MSG(msg).send_pdu.encrypt, false);
    assert_eq(BLE_MSG(msg).send_pdu.phy, BLE_PHY_LE_1M);

    return PASS;
}

result_t test_send_pdu_parse(void)
{
    Message msg;
    uint8_t pdu[] = {0x01, 0x02, 0x03, 0x04};
    whad_ble_pdu_params_t params;

    assert_error(whad_ble_send_pdu_parse(NULL, &params));
    assert_error(whad_ble_send_pdu_parse(&msg, NULL));

    assert_success(whad_ble_send_pdu(&msg, BLE_SLAVE_TO_MASTER, 9, pdu, 4,
                                    true, BLE_PHY_LE_1M));
    assert_success(whad_ble_send_pdu_parse(&msg, &params));
    assert_eq(params.direction, BLE_SLAVE_TO_MASTER);
    assert_eq(params.conn_handle, 9);
    assert_eq(params.access_address, 0);
    assert_eq(params.length, 4);
    assert(!memcmp(params.p_pdu, pdu, params.length));
    assert_eq(params.crc, 0);
    assert_eq(params.encrypt, true);

    return PASS;
}

/* Encryption and PHY configuration. */

result_t test_set_encryption_craft(void)
{
    /* Test crafting a SetEncryption message. */
    Message msg;
    uint8_t key[16] = {0}, iv[8] = {0}, rand[8] = {0}, ediv[2] = {0};

    /* Craft a valid SetEncryption message. */
    assert_success(whad_ble_set_encryption(&msg, 42, true, key, iv, key, rand, ediv));

    /* Check the crafted message structure. */
    assert_eq(msg.which_msg, Message_ble_tag);
    assert_eq(msg.msg.ble.which_msg, ble_Message_encryption_tag);
    assert_eq(BLE_MSG(msg).encryption.conn_handle, 42);
    assert_eq(BLE_MSG(msg).encryption.enabled, true);
    assert(!memcmp(BLE_MSG(msg).encryption.ll_key, key, 16));
    return PASS;
}

result_t test_set_encryption_parse(void)
{
    /* Test parsing a SetEncryption message. */
    Message msg;
    whad_ble_encryption_params_t params;
    uint8_t ll_key[16] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
    uint8_t ll_iv[8] = {1, 2, 3, 4, 5, 6, 7, 8};
    uint8_t key[16] = {15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
    uint8_t rand[8] = {8, 7, 6, 5, 4, 3, 2, 1};
    uint8_t ediv[2] = {0x34, 0x12};

    /* Test sanity checks. */
    assert_error(whad_ble_set_encryption(NULL, 1, true, ll_key, ll_iv, key, rand, ediv));
    assert_error(whad_ble_set_encryption(&msg, 1, true, NULL, ll_iv, key, rand, ediv));
    assert_error(whad_ble_set_encryption_parse(NULL, &params));
    assert_error(whad_ble_set_encryption_parse(&msg, NULL));

    /* Craft and parse a valid SetEncryption message. */
    assert_success(whad_ble_set_encryption(&msg, 42, true, ll_key, ll_iv, key, rand, ediv));
    assert_success(whad_ble_set_encryption_parse(&msg, &params));

    /* Check parsed parameters. */
    assert_eq(params.conn_handle, 42);
    assert_eq(params.enabled, true);
    assert(!memcmp(params.p_ll_key, ll_key, sizeof ll_key));
    assert(!memcmp(params.p_ll_iv, ll_iv, sizeof ll_iv));
    assert(!memcmp(params.p_key, key, sizeof key));
    assert(!memcmp(params.p_rand, rand, sizeof rand));
    assert(!memcmp(params.p_ediv, ediv, sizeof ediv));
    return PASS;
}

/* PHYs */

result_t test_set_phy_craft(void)
{
    /* Test crafting a SetPhy message. */
    Message msg;

    /* Craft a valid SetPhy message. */
    assert_success(whad_ble_set_phy(&msg, BLE_PHY_LE_2M, BLE_PHY_LE_1M_CODED));

    /* Check the crafted message structure. */
    assert_eq(msg.which_msg, Message_ble_tag);
    assert_eq(msg.msg.ble.which_msg, ble_Message_set_phy_tag);
    assert_eq(BLE_MSG(msg).set_phy.tx_phy, BLE_PHY_LE_2M);
    assert_eq(BLE_MSG(msg).set_phy.rx_phy, BLE_PHY_LE_1M_CODED);
    
    /* Passed. */
    return PASS;
}

result_t test_set_phy_parse(void)
{
    /* Test parsing a SetPhy message. */
    Message msg;
    whad_ble_phy_t tx, rx;

    /* Test sanity checks. */
    assert_error(whad_ble_set_phy_parse(NULL, &tx, &rx));
    assert_error(whad_ble_set_phy_parse(&msg, NULL, NULL));

    /* Craft and parse a valid SetPhy message. */
    assert_success(whad_ble_set_phy(&msg, BLE_PHY_LE_2M, BLE_PHY_LE_1M_CODED));
    assert_success(whad_ble_set_phy_parse(&msg, &tx, &rx));

    /* Check parsed parameters. */
    assert_eq(tx, BLE_PHY_LE_2M);
    assert_eq(rx, BLE_PHY_LE_1M_CODED);
    
    /* Passed. */
    return PASS;
}

result_t test_set_supported_phys_craft(void)
{
    /* Test crafting a SetSupportedPhys message. */
    Message msg;
    whad_ble_phys_t phys = {.tx_count = 1, .rx_count = 1,
                           .tx = {BLE_PHY_LE_2M}, .rx = {BLE_PHY_LE_1M_CODED}};
    /* Test sanity checks. */
    assert_error(whad_ble_set_supp_phys(NULL, phys));
    phys.tx_count = MAX_SUPP_PHYS + 1;
    assert_error(whad_ble_set_supp_phys(&msg, phys));
    phys.tx_count = 1;

    /* Craft a valid SetSupportedPhys message. */
    assert_success(whad_ble_set_supp_phys(&msg, phys));

    /* Check the crafted message structure. */
    assert_eq(msg.which_msg, Message_ble_tag);
    assert_eq(msg.msg.ble.which_msg, ble_Message_set_supp_phys_tag);
    assert_eq(BLE_MSG(msg).set_supp_phys.tx_phy_count, 1);
    assert_eq(BLE_MSG(msg).set_supp_phys.rx_phy_count, 1);
    assert_eq(BLE_MSG(msg).set_supp_phys.tx_phy[0], BLE_PHY_LE_2M);
    assert_eq(BLE_MSG(msg).set_supp_phys.rx_phy[0], BLE_PHY_LE_1M_CODED);
    
    /* Passed. */
    return PASS;
}

result_t test_set_supported_phys_parse(void)
{
    /* Test parsing a SetSupportedPhys message. */
    Message msg;
    whad_ble_phys_t input = {
        .tx_count = 2, .rx_count = 2,
        .tx = {BLE_PHY_LE_1M, BLE_PHY_LE_2M},
        .rx = {BLE_PHY_LE_1M_CODED, BLE_PHY_LE_1M}
    };
    whad_ble_phys_t output = {0};

    /* Test sanity checks. */
    assert_error(whad_ble_set_supp_phys_parse(NULL, &output));
    assert_error(whad_ble_set_supp_phys_parse(&msg, NULL));

    /* Craft and parse a valid SetSupportedPhys message. */
    assert_success(whad_ble_set_supp_phys(&msg, input));
    assert_success(whad_ble_set_supp_phys_parse(&msg, &output));

    /* Check parsed parameters. */
    assert_eq(output.tx_count, 2);
    assert_eq(output.rx_count, 2);
    assert_eq(output.tx[0], BLE_PHY_LE_1M);
    assert_eq(output.tx[1], BLE_PHY_LE_2M);
    assert_eq(output.rx[0], BLE_PHY_LE_1M_CODED);
    assert_eq(output.rx[1], BLE_PHY_LE_1M);
    
    /* Passed. */
    return PASS;
}

/* TX Power level */

result_t test_set_tx_power_craft(void)
{
    /* Test crafting a SetTxPowerLevel message. */
    Message msg;

    /* Test sanity checks. */
    assert_error(whad_ble_set_tx_power_level(NULL, -12));

    /* Craft a valid SetTxPowerLevel message. */
    assert_success(whad_ble_set_tx_power_level(&msg, -12));

    /* Check the crafted message structure. */
    assert_eq(msg.which_msg, Message_ble_tag);
    assert_eq(msg.msg.ble.which_msg, ble_Message_set_tx_pwr_tag);
    assert_eq(BLE_MSG(msg).set_tx_pwr.level, -12);
    
    /* Passed. */
    return PASS;
}

result_t test_set_tx_power_parse(void)
{
    /* Test parsing a SetTxPowerLevel message. */
    Message msg;
    int power = 0;

    /* Test sanity checks. */
    assert_error(whad_ble_set_tx_power_level_parse(NULL, &power));
    assert_error(whad_ble_set_tx_power_level_parse(&msg, NULL));

    /* Craft and parse a valid SetTxPowerLevel message. */
    assert_success(whad_ble_set_tx_power_level(&msg, -12));
    assert_success(whad_ble_set_tx_power_level_parse(&msg, &power));

    /* Check parsed parameters. */
    assert_eq(power, -12);

    /* Passed. */
    return PASS;
}

/* Reactive Jam */ 

result_t test_reactive_jam_craft(void)
{
    /* Test crafting a ReactiveJam message. */
    Message msg;
    uint8_t pattern[] = {0xaa, 0xbb, 0xcc};

    /* Test sanity checks. */
    assert_error(whad_ble_reactive_jam(NULL, 20, pattern, 3, 2, BLE_PHY_LE_1M));

    /* Craft a valid ReactiveJam message. */
    assert_success(whad_ble_reactive_jam(&msg, 20, pattern, 3, 2, BLE_PHY_LE_1M));

    /* Check the crafted message structure. */
    assert_eq(msg.which_msg, Message_ble_tag);
    assert_eq(msg.msg.ble.which_msg, ble_Message_reactive_jam_tag);
    assert_eq(BLE_MSG(msg).reactive_jam.pattern.size, 3);
    assert(!memcmp(BLE_MSG(msg).reactive_jam.pattern.bytes, pattern, 3));
    
    /* Passed. */
    return PASS;
}

result_t test_reactive_jam_parse(void)
{
    /* Test parsing a ReactiveJam message. */
    Message msg;
    uint8_t pattern[] = {0xaa, 0xbb, 0xcc};
    whad_ble_reactive_jam_params_t params;

    /* Test sanity checks. */
    assert_error(whad_ble_reactive_jam_parse(NULL, &params));
    assert_error(whad_ble_reactive_jam_parse(&msg, NULL));

    /* Craft and parse a valid ReactiveJam message. */
    assert_success(whad_ble_reactive_jam(&msg, 20, pattern, 3, 2, BLE_PHY_LE_1M));
    assert_success(whad_ble_reactive_jam_parse(&msg, &params));

    /* Check parsed parameters. */
    assert_eq(params.channel, 20);
    assert_eq(params.position, 2);
    assert_eq(params.phy, BLE_PHY_LE_1M);
    assert_eq(params.pattern_length, 3);
    assert(!memcmp(params.pattern, pattern, 3));
    
    /* Passed. */
    return PASS;
}

/* Adapter notifications. */

result_t test_connected_notification(void)
{
    /* Test crafting a Connected notification. */
    Message msg;
    uint8_t advertiser[] = {1, 2, 3, 4, 5, 6};
    uint8_t initiator[] = {6, 5, 4, 3, 2, 1};

    /* Test sanity checks. */
    assert_error(whad_ble_notify_connected(NULL, BLE_ADDR_RANDOM, advertiser,
                                          BLE_ADDR_PUBLIC, initiator, 3, BLE_PHY_LE_2M));
    assert_error(whad_ble_notify_connected(&msg, BLE_ADDR_RANDOM, NULL,
                                          BLE_ADDR_PUBLIC, initiator, 3, BLE_PHY_LE_2M));

    /* Craft a valid Connected notification. */
    assert_success(whad_ble_notify_connected(&msg, BLE_ADDR_RANDOM, advertiser,
                                            BLE_ADDR_PUBLIC, initiator, 3, BLE_PHY_LE_2M));

    /* Check the crafted message structure. */
    assert_eq(msg.which_msg, Message_ble_tag);
    assert_eq(msg.msg.ble.which_msg, ble_Message_connected_tag);
    assert_eq(BLE_MSG(msg).connected.conn_handle, 3);
    assert_eq(BLE_MSG(msg).connected.adv_addr_type, BLE_ADDR_RANDOM);
    assert_eq(BLE_MSG(msg).connected.init_addr_type, BLE_ADDR_PUBLIC);
    assert(!memcmp(BLE_MSG(msg).connected.advertiser, advertiser, 6));
    assert(!memcmp(BLE_MSG(msg).connected.initiator, initiator, 6));
    assert_eq(BLE_MSG(msg).connected.phy, BLE_PHY_LE_2M);
    
    /* Passed. */
    return PASS;
}

result_t test_disconnected_notification_craft(void)
{
    /* Test crafting a Disconnected notification. */
    Message msg;

    /* Test sanity checks. */
    assert_error(whad_ble_notify_disconnected(NULL, 2, 0x13));

    /* Craft a valid Disconnected notification. */
    assert_success(whad_ble_notify_disconnected(&msg, 2, 0x13));

    /* Check the crafted message structure. */
    assert_eq(msg.which_msg, Message_ble_tag);
    assert_eq(msg.msg.ble.which_msg, ble_Message_disconnected_tag);
    assert_eq(BLE_MSG(msg).disconnected.conn_handle, 2);
    assert_eq(BLE_MSG(msg).disconnected.reason, 0x13);
    
    /* Passed. */
    return PASS;
}

result_t test_disconnected_notification_parse(void)
{
    /* Test parsing a Disconnected notification. */
    Message msg;
    whad_ble_disconnected_params_t params;

    /* Test sanity checks. */
    assert_error(whad_ble_notify_disconnected_parse(NULL, &params));
    assert_error(whad_ble_notify_disconnected_parse(&msg, NULL));

    /* Craft and parse a valid Disconnected notification. */
    assert_success(whad_ble_notify_disconnected(&msg, 2, 0x13));
    assert_success(whad_ble_notify_disconnected_parse(&msg, &params));

    /* Check parsed parameters. */
    assert_eq(params.conn_handle, 2);
    assert_eq(params.reason, 0x13);
    
    /* Passed. */
    return PASS;
}

result_t test_triggered_notification_craft(void)
{
    /* Test crafting a Triggered notification. */
    Message msg;

    /* Test sanity checks. */
    assert_error(whad_ble_triggered(NULL, 17));

    /* Craft a valid Triggered notification. */
    assert_success(whad_ble_triggered(&msg, 17));

    /* Check the crafted message structure. */
    assert_eq(msg.which_msg, Message_ble_tag);
    assert_eq(msg.msg.ble.which_msg, ble_Message_triggered_tag);
    assert_eq(BLE_MSG(msg).triggered.id, 17);
    
    /* Passed. */
    return PASS;
}

result_t test_triggered_notification_parse(void)
{
    /* Test parsing a Triggered notification. */
    Message msg;
    uint32_t id = 0;

    /* Test sanity checks. */
    assert_error(whad_ble_triggered_parse(NULL, &id));
    assert_error(whad_ble_triggered_parse(&msg, NULL));

    /* Craft and parse a valid Triggered notification. */
    assert_success(whad_ble_triggered(&msg, 17));
    assert_success(whad_ble_triggered_parse(&msg, &id));

    /* Check parsed parameters. */
    assert_eq(id, 17);
    
    /* Passed. */
    return PASS;
}

result_t test_connection_status_notifications(void)
{
    /* Test crafting and parsing connection status notifications. */
    Message msg;
    uint32_t aa;
    whad_ble_hijacked_params_t hijacked;
    whad_ble_injected_params_t injected;

    /* Test the Desynchronized notification and its parser. */
    assert_error(whad_ble_desynchronized(NULL, 0));
    assert_success(whad_ble_desynchronized(&msg, 0x11223344));
    assert_eq(msg.msg.ble.which_msg, ble_Message_desynchronized_tag);
    assert_success(whad_ble_desynchronized_parse(&msg, &aa));
    assert_eq(aa, 0x11223344);

    /* Test the Hijacked notification and its parser. */
    assert_error(whad_ble_hijacked(NULL, 0, false));
    assert_success(whad_ble_hijacked(&msg, 0x22334455, true));
    assert_eq(msg.msg.ble.which_msg, ble_Message_hijacked_tag);
    assert_success(whad_ble_hijacked_parse(&msg, &hijacked));
    assert_eq(hijacked.access_address, 0x22334455);
    assert_eq(hijacked.success, true);

    /* Test the Injected notification and its parser. */
    assert_error(whad_ble_injected(NULL, 0, 0, false));
    assert_success(whad_ble_injected(&msg, 0x33445566, 4, false));
    assert_eq(msg.msg.ble.which_msg, ble_Message_injected_tag);
    assert_success(whad_ble_injected_parse(&msg, &injected));
    assert_eq(injected.access_address, 0x33445566);
    assert_eq(injected.attempts, 4);
    assert_eq(injected.success, false);
    
    /* Passed. */
    return PASS;
}

result_t test_phy_updated_craft(void)
{
    /* Test crafting a PhyUpdated notification. */
    Message msg;

    /* Test sanity checks. */
    assert_error(whad_ble_phy_updated(NULL, BLE_PHY_LE_2M, BLE_PHY_LE_1M));

    /* Craft a valid PhyUpdated notification. */
    assert_success(whad_ble_phy_updated(&msg, BLE_PHY_LE_2M, BLE_PHY_LE_1M));

    /* Check the crafted message structure. */
    assert_eq(msg.which_msg, Message_ble_tag);
    assert_eq(msg.msg.ble.which_msg, ble_Message_set_phy_tag);
    assert_eq(BLE_MSG(msg).phy_updated.tx_phy, BLE_PHY_LE_2M);
    assert_eq(BLE_MSG(msg).phy_updated.rx_phy, BLE_PHY_LE_1M);
    
    /* Passed. */
    return PASS;
}

result_t test_phy_updated_parse(void)
{
    /* Test parsing a PhyUpdated notification. */
    Message msg;
    whad_ble_phy_t tx, rx;

    /* Test sanity checks. */
    assert_error(whad_ble_phy_updated_parse(NULL, &tx, &rx));
    assert_error(whad_ble_phy_updated_parse(&msg, NULL, NULL));

    /* Craft and parse a valid PhyUpdated notification. */
    assert_success(whad_ble_phy_updated(&msg, BLE_PHY_LE_2M, BLE_PHY_LE_1M));
    assert_success(whad_ble_phy_updated_parse(&msg, &tx, &rx));

    /* Check parsed parameters. */
    assert_eq(tx, BLE_PHY_LE_2M);
    assert_eq(rx, BLE_PHY_LE_1M);
    
    /* Passed. */
    return PASS;
}

result_t test_extended_adv_pdus_craft(void)
{
    /* Test crafting a SetExtAdvPdus message. */
    Message msg;
    whad_ble_ext_adv_t pdu = {.length = 2};
    memcpy(pdu.adv_data, (uint8_t[]){1, 2}, 2);

    /* Test sanity checks. */
    assert_error(whad_ble_set_ext_adv_pdus(NULL, &pdu, 2));
    assert_error(whad_ble_set_ext_adv_pdus(&msg, NULL, 2));
    assert_error(whad_ble_set_ext_adv_pdus(&msg, &pdu, 0));

    /* Craft a valid SetExtAdvPdus message. */
    assert_success(whad_ble_set_ext_adv_pdus(&msg, &pdu, 1));

    /* Check the crafted message structure. */
    assert_eq(msg.which_msg, Message_ble_tag);
    assert_eq(msg.msg.ble.which_msg, ble_Message_set_ext_adv_pdus_tag);
    assert_eq(BLE_MSG(msg).set_ext_adv_pdus.pdus_count, 1);
    assert_eq(BLE_MSG(msg).set_ext_adv_pdus.pdus[0].adv_data.size, 2);
    assert(!memcmp(BLE_MSG(msg).set_ext_adv_pdus.pdus[0].adv_data.bytes, pdu.adv_data, 2));
    
    /* Passed. */
    return PASS;
}

result_t test_extended_adv_pdus_parse(void)
{
    /* Test parsing a SetExtAdvPdus message. */
    Message msg;
    whad_ble_ext_adv_t input[2] = {0};
    whad_ble_ext_adv_t output[2] = {0};
    size_t count = 0;

    input[0].length = 3;
    memcpy(input[0].adv_data, (uint8_t[]){1, 2, 3}, 3);
    input[0].has_auxptr = true;
    input[0].auxptr.channel = 18;
    input[0].auxptr.ca = 1;
    input[0].auxptr.offset_units = 1;
    input[0].auxptr.offset = 24;
    input[0].auxptr.phy = BLE_PHY_LE_2M;
    input[1].length = 2;
    memcpy(input[1].adv_data, (uint8_t[]){4, 5}, 2);

    /* Test sanity checks. */
    assert_error(whad_ble_set_ext_adv_pdus_parse(NULL, output, &count));
    assert_error(whad_ble_set_ext_adv_pdus_parse(&msg, output, NULL));

    /* Craft and parse a valid SetExtAdvPdus message. */
    assert_success(whad_ble_set_ext_adv_pdus(&msg, input, 2));
    assert_success(whad_ble_set_ext_adv_pdus_parse(&msg, output, &count));

    /* Check parsed parameters and PDU buffers. */
    assert_eq(count, 2);
    assert_eq(output[0].length, 3);
    assert(!memcmp(output[0].adv_data, input[0].adv_data, 3));
    assert_eq(output[1].length, 2);
    assert(!memcmp(output[1].adv_data, input[1].adv_data, 2));
    
    /* Passed. */
    return PASS;
}

result_t test_synchronized_craft(void)
{
    /* Test crafting a Synchronized notification. */
    Message msg;
    uint8_t channelmap[] = {0xff, 0xff, 0xff, 0xff, 0x1f};

    /* Test sanity checks. */
    assert_error(whad_ble_synchronized(NULL, 0, 0, 0, 0, channelmap, BLE_PHY_LE_1M));
    assert_error(whad_ble_synchronized(&msg, 0, 0, 0, 0, NULL, BLE_PHY_LE_1M));

    /* Craft a valid Synchronized notification. */
    assert_success(whad_ble_synchronized(&msg, 0x11223344, 0xabcdef, 24, 9,
                                        channelmap, BLE_PHY_LE_2M));

    /* Check the crafted message structure. */
    assert_eq(msg.which_msg, Message_ble_tag);
    assert_eq(msg.msg.ble.which_msg, ble_Message_synchronized_tag);
    assert_eq(BLE_MSG(msg).synchronized.access_address, 0x11223344);
    assert(!memcmp(BLE_MSG(msg).synchronized.channel_map, channelmap, 5));
    return PASS;
}

result_t test_synchronized_parse(void)
{
    /* Test parsing a Synchronized notification. */
    Message msg;
    uint8_t channelmap[] = {0xff, 0xff, 0xff, 0xff, 0x1f};
    whad_ble_synchro_params_t params;

    /* Test sanity checks. */
    assert_error(whad_ble_synchronized_parse(NULL, &params));
    assert_error(whad_ble_synchronized_parse(&msg, NULL));

    /* Craft and parse a valid Synchronized notification. */
    assert_success(whad_ble_synchronized(&msg, 0x11223344, 0xabcdef, 24, 9,
                                        channelmap, BLE_PHY_LE_2M));
    assert_success(whad_ble_synchronized_parse(&msg, &params));

    /* Check parsed parameters. */
    assert_eq(params.access_address, 0x11223344);
    assert_eq(params.crc_init, 0xabcdef);
    assert_eq(params.hop_interval, 24);
    assert_eq(params.hop_increment, 9);
    assert(!memcmp(params.channelmap, channelmap, 5));
    
    /* Passed. */
    return PASS;
}

result_t test_access_address_discovered_craft(void)
{
    /* Test crafting an AccessAddressDiscovered notification. */
    Message msg;

    /* Test sanity checks. */
    assert_error(whad_ble_access_address_discovered(NULL, 0, 0, 0, false, false));

    /* Craft a valid AccessAddressDiscovered notification. */
    assert_success(whad_ble_access_address_discovered(&msg, 0x11223344, 1234, -40,
                                                     true, true));

    /* Check the crafted message structure. */
    assert_eq(msg.which_msg, Message_ble_tag);
    assert_eq(msg.msg.ble.which_msg, ble_Message_aa_disc_tag);
    assert_eq(BLE_MSG(msg).aa_disc.access_address, 0x11223344);
    assert_eq(BLE_MSG(msg).aa_disc.has_timestamp, true);
    assert_eq(BLE_MSG(msg).aa_disc.timestamp, 1234);
    assert_eq(BLE_MSG(msg).aa_disc.has_rssi, true);
    assert_eq(BLE_MSG(msg).aa_disc.rssi, -40);
    
    /* Passed. */
    return PASS;
}

result_t test_access_address_discovered_parse(void)
{
    /* Test parsing an AccessAddressDiscovered notification. */
    Message msg;
    whad_ble_aa_disc_params_t params;

    /* Test sanity checks. */
    assert_error(whad_ble_access_address_discovered_parse(NULL, &params));
    assert_error(whad_ble_access_address_discovered_parse(&msg, NULL));

    /* Craft and parse a valid AccessAddressDiscovered notification. */
    assert_success(whad_ble_access_address_discovered(&msg, 0x11223344, 1234, -40,
                                                     true, true));
    assert_success(whad_ble_access_address_discovered_parse(&msg, &params));

    /* Check parsed parameters. */
    assert_eq(params.access_address, 0x11223344);
    assert_eq(params.timestamp, 1234);
    assert_eq(params.rssi, -40);
    assert_eq(params.inc_ts, true);
    assert_eq(params.inc_rssi, true);
    
    /* Passed. */
    return PASS;
}

result_t test_adv_pdu_craft(void)
{
    /* Test crafting an AdvPdu notification. */
    Message msg;
    uint8_t address[] = {1, 2, 3, 4, 5, 6};
    uint8_t data[] = {2, 1, 6};

    /* Test sanity checks. */
    assert_error(whad_ble_adv_pdu(NULL, BLE_ADV_IND, -35, address, BLE_ADDR_RANDOM,
                                  data, 3, 37, BLE_PHY_LE_1M));
    assert_error(whad_ble_adv_pdu(&msg, BLE_ADV_IND, -35, NULL, BLE_ADDR_RANDOM,
                                  data, 3, 37, BLE_PHY_LE_1M));

    /* Craft a valid AdvPdu notification. */
    assert_success(whad_ble_adv_pdu(&msg, BLE_ADV_IND, -35, address, BLE_ADDR_RANDOM,
                                   data, 3, 37, BLE_PHY_LE_1M));

    /* Check the crafted message structure and buffers. */
    assert_eq(msg.which_msg, Message_ble_tag);
    assert_eq(msg.msg.ble.which_msg, ble_Message_adv_pdu_tag);
    assert_eq(BLE_MSG(msg).adv_pdu.adv_type, BLE_ADV_IND);
    assert_eq(BLE_MSG(msg).adv_pdu.rssi, -35);
    assert_eq(BLE_MSG(msg).adv_pdu.addr_type, BLE_ADDR_RANDOM);
    assert(!memcmp(BLE_MSG(msg).adv_pdu.bd_address, address, 6));
    assert_eq(BLE_MSG(msg).adv_pdu.adv_data.size, 3);
    assert(!memcmp(BLE_MSG(msg).adv_pdu.adv_data.bytes, data, 3));
    
    /* Passed. */
    return PASS;
}

result_t test_adv_pdu_parse(void)
{
    /* Test parsing an AdvPdu notification. */
    Message msg;
    uint8_t address[] = {1, 2, 3, 4, 5, 6};
    uint8_t data[] = {2, 1, 6};
    whad_ble_adv_pdu_t params;

    /* Test sanity checks. */
    assert_error(whad_ble_adv_pdu_parse(NULL, &params));
    assert_error(whad_ble_adv_pdu_parse(&msg, NULL));

    /* Craft and parse a valid AdvPdu notification. */
    assert_success(whad_ble_adv_pdu(&msg, BLE_ADV_IND, -35, address, BLE_ADDR_RANDOM,
                                   data, 3, 37, BLE_PHY_LE_1M));
    assert_success(whad_ble_adv_pdu_parse(&msg, &params));

    /* Check parsed parameters and buffers. */
    assert_eq(params.adv_type, BLE_ADV_IND);
    assert_eq(params.rssi, -35);
    assert_eq(params.addr_type, BLE_ADDR_RANDOM);
    assert(!memcmp(params.p_bdaddr, address, 6));
    assert_eq(params.adv_data_length, 3);
    assert(!memcmp(params.p_adv_data, data, 3));
    assert_eq(params.channel, 37);
    assert_eq(params.phy, BLE_PHY_LE_1M);
    
    /* Passed. */
    return PASS;
}

result_t test_prepare_sequence_controls(void)
{
    /* Test crafting and parsing prepared sequence control messages. */
    Message msg;
    uint32_t id;

    /* Test TriggerSequence sanity checks. */
    assert_error(whad_ble_prepare_sequence_trigger(NULL, 5));

    /* Craft and parse a valid TriggerSequence message. */
    assert_success(whad_ble_prepare_sequence_trigger(&msg, 5));
    assert_eq(msg.msg.ble.which_msg, ble_Message_trigger_tag);
    assert_success(whad_ble_prepare_sequence_trigger_parse(&msg, &id));
    assert_eq(id, 5);
    assert_error(whad_ble_prepare_sequence_trigger_parse(NULL, &id));
    assert_error(whad_ble_prepare_sequence_trigger_parse(&msg, NULL));

    /* Test DeleteSequence sanity checks. */
    assert_error(whad_ble_prepare_sequence_delete(NULL, 6));

    /* Craft and check a valid DeleteSequence message. */
    assert_success(whad_ble_prepare_sequence_delete(&msg, 6));
    assert_eq(msg.msg.ble.which_msg, ble_Message_delete_seq_tag);
    assert_eq(BLE_MSG(msg).delete_seq.id, 6);
    return PASS;
}

result_t test_prepare_sequence_roundtrip(void)
{
    /* Test crafting and parsing prepared sequence messages. */
    Message msg;
    whad_prepared_packet_t packet = {0};
    whad_ble_prepseq_params_t params;
    whad_ble_trigger_t trigger;
    uint8_t pattern[] = {0xaa, 0xbb};
    uint8_t mask[] = {0xff, 0xf0};

    /* Initialize a prepared packet. */
    packet.length = 1;
    packet.p_bytes[0] = (uint8_t *)0x12;

    /* Test manual sequence sanity checks. */
    assert_error(whad_ble_prepare_sequence_manual(NULL, 1, BLE_MASTER_TO_SLAVE, &packet, 1));
    assert_error(whad_ble_prepare_sequence_manual(&msg, 1, BLE_MASTER_TO_SLAVE, NULL, 1));

    /* Craft and parse a manually triggered sequence. */
    assert_success(whad_ble_prepare_sequence_manual(&msg, 7, BLE_MASTER_TO_SLAVE, &packet, 1));
    assert_success(whad_ble_prepare_sequence_get_trigger_type(&msg, &trigger));
    assert_eq(trigger, BLE_MANUAL_TRIGGER);
    assert_success(whad_ble_prepare_sequence_manual_parse(&msg, &params));

    /* Check manual sequence parameters and packet data. */
    assert_eq(params.id, 7);
    assert_eq(params.direction, BLE_MASTER_TO_SLAVE);
    assert_eq(params.packet_count, 1);
    assert_eq(params.packets[0].length, 1);
    assert(!memcmp(params.packets[0].p_bytes, packet.p_bytes, 1));

    /* Craft and parse a connection-event triggered sequence. */
    assert_success(whad_ble_prepare_sequence_conn_evt(&msg, 12, 8,
                                                     BLE_SLAVE_TO_MASTER, &packet, 1));
    assert_success(whad_ble_prepare_sequence_get_trigger_type(&msg, &trigger));
    assert_eq(trigger, BLE_CONNEVT_TRIGGER);
    assert_success(whad_ble_prepare_sequence_conn_evt_parse(&msg, &params));

    /* Check connection-event sequence parameters. */
    assert_eq(params.id, 8);
    assert_eq(params.conn_evt, 12);
    assert_eq(params.packet_count, 1);

    /* Craft a reception-pattern triggered sequence. */
    assert_success(whad_ble_prepare_sequence_on_recv(&msg, pattern, mask, 2, 1, 9,
                                                    BLE_MASTER_TO_SLAVE, &packet, 1));
    assert_success(whad_ble_prepare_sequence_get_trigger_type(&msg, &trigger));

    /* Check the reception trigger and its pattern buffers. */
    assert_eq(trigger, BLE_PATTERN_TRIGGER);
    assert_eq(BLE_MSG(msg).prepare.id, 9);
    assert(!memcmp(BLE_MSG(msg).prepare.trigger.trigger.reception.pattern.bytes,
                   pattern, 2));
    assert(!memcmp(BLE_MSG(msg).prepare.trigger.trigger.reception.mask.bytes,
                   mask, 2));
    return PASS;
}

result_t test_peripheral_mode_craft(void)
{
    /* Test crafting a PeripheralMode message. */
    Message msg;
    uint8_t adv[] = {2, 1, 6}, scanrsp[] = {3, 9, 'W', 'H'};
    uint8_t channelmap[] = {0, 0, 0, 0, 0xe0};
    whad_ble_ext_adv_t pdu = {.length = 1};
    pdu.adv_data[0] = 0x11;

    /* Test sanity checks. */
    assert_error(whad_ble_peripheral_mode(NULL, adv, 3, scanrsp, 4, BLE_ADV_IND,
                                         channelmap, 0x20, 0x40, BLE_CSA1, &pdu, 1));

    /* Craft a valid PeripheralMode message. */
    assert_success(whad_ble_peripheral_mode(&msg, adv, 3, scanrsp, 4, BLE_ADV_IND,
                                           channelmap, 0x20, 0x40, BLE_CSA1, &pdu, 1));

    /* Check the crafted message structure and buffers. */
    assert_eq(msg.which_msg, Message_ble_tag);
    assert_eq(msg.msg.ble.which_msg, ble_Message_periph_mode_tag);
    assert(!memcmp(BLE_MSG(msg).periph_mode.adv_data.bytes, adv, 3));
    assert(!memcmp(BLE_MSG(msg).periph_mode.scanrsp_data.bytes, scanrsp, 4));
    return PASS;
}

result_t test_peripheral_mode_parse(void)
{
    /* Test parsing a PeripheralMode message. */
    Message msg;
    uint8_t adv[] = {2, 1, 6};
    uint8_t scanrsp[] = {3, 9, 'W', 'H'};
    uint8_t channelmap[] = {0, 0, 0, 0, 0xe0};
    whad_ble_ext_adv_t pdu = {0};
    whad_ble_adv_mode_params_t params;

    pdu.length = 2;
    memcpy(pdu.adv_data, (uint8_t[]){0x11, 0x22}, 2);

    /* Test sanity checks. */
    assert_error(whad_ble_peripheral_mode_parse(NULL, &params));
    assert_error(whad_ble_peripheral_mode_parse(&msg, NULL));

    /* Craft and parse a valid PeripheralMode message. */
    assert_success(whad_ble_peripheral_mode(&msg, adv, 3, scanrsp, 4, BLE_ADV_IND,
                                           channelmap, 0x20, 0x40, BLE_CSA1, &pdu, 1));
    assert_success(whad_ble_peripheral_mode_parse(&msg, &params));

    /* Check parsed parameters and advertising buffers. */
    assert_eq(params.adv_data_length, 3);
    assert(!memcmp(params.adv_data, adv, 3));
    assert_eq(params.scanrsp_data_length, 4);
    assert(!memcmp(params.scanrsp_data, scanrsp, 4));
    assert_eq(params.adv_type, BLE_ADV_IND);
    assert_eq(params.inter_min, 0x20);
    assert_eq(params.inter_max, 0x40);
    assert_eq(params.csa, BLE_CSA1);
    assert(!memcmp(params.channel_map, channelmap, 5));
    
    /* Passed. */
    return PASS;
}

result_t test_unsupported_set_adv_data_parse(void)
{
    /* Test that SetAdvData parsing reports unsupported behavior. */
    Message msg;
    uint8_t adv[31], scanrsp[31];
    int adv_length, scanrsp_length;

    /* Check that the unsupported parser returns an error. */
    assert_error(whad_ble_set_adv_data_parse(&msg, adv, &adv_length,
                                             scanrsp, &scanrsp_length));
    
    /* Passed. */
    return PASS;
}

/* Define test suite for BLE C API. */
TEST_SUITE_BEGIN(ble_basic) 
TEST_CASE("setting bluetooth LE address", test_set_bdaddress)
TEST_CASE("setting bluetooth LE address (bad message pointer)", test_set_bdaddress_bad_pmsg)
TEST_CASE("setting bluetooth LE address (bad address pointer)", test_set_bdaddress_bad_addr)
TEST_CASE("parsing SetBdAddress message", test_set_bdaddress_parse)
TEST_CASE("crafting SniffAdv message", test_sniff_adv_craft)
TEST_CASE("parsing SniffAdv message", test_sniff_adv_parse)
TEST_CASE("crafting JamAdv message", test_jam_adv)
TEST_CASE("crafting JamAdvChannel message", test_jam_adv_channel)
TEST_CASE("parsing JamAdvChannel message", test_jam_adv_channel_parse)
TEST_CASE("crafting SniffConnReq message", test_sniff_connreq)
TEST_CASE("parsing SniffConnReq message", test_sniff_connreq_parse)
TEST_CASE("crafting SniffAccessAddress message", test_sniff_aa)
TEST_CASE("parsing SniffAccessAddress message", test_sniff_aa_parse)
TEST_CASE("crafting SniffActiveConn message", test_sniff_active_conn)
TEST_CASE("parsing SniffActiveConn message", test_sniff_active_conn_parse)
TEST_CASE("crafting JamActiveConn message", test_jam_active_conn)
TEST_CASE("parsing JamActiveConn message", test_jam_active_conn_parse)
TEST_CASE("crafting ScanMode message", test_scan_mode)
TEST_CASE("parsing ScanMode message", test_scan_mode_parse)
TEST_CASE("crafting legacy AdvMode message", test_adv_mode_legacy)
TEST_CASE("parsing legacy AdvMode message", test_adv_mode_legacy_parse)
TEST_CASE("crafting extended AdvMode message", test_adv_mode_ext)
TEST_CASE("parsing extende AdvMode message", test_adv_mode_ext_parse)
TEST_CASE("crafting SetAdvData message", test_set_adv_data)
TEST_CASE("crafting CentralMode message", test_central_mode)
TEST_CASE("crafting ConnectTo message", test_connect_to)
TEST_CASE("parsing ConnectTo message", test_connect_to_parse)
TEST_CASE("crafting Disconnect message", test_disconnect)
TEST_CASE("parsing Disconnect message", test_disconnect_parse)
TEST_CASE("crafting Start message", test_start)
TEST_CASE("crafting Stop message", test_stop)
TEST_CASE("crafting HijackMaster message", test_hijack_master)
TEST_CASE("parsing HijackMaster message", test_hijack_master_parse)
TEST_CASE("crafting HijackSlave message", test_hijack_slave)
TEST_CASE("parsing HijackSlave message", test_hijack_slave_parse)
TEST_CASE("crafting HijackBoth message", test_hijack_both)
TEST_CASE("parsing HijackBoth message", test_hijack_both_parse)
TEST_CASE("crafting BlePdu message", test_pdu)
TEST_CASE("parsing BlePdu message", test_pdu_parse)
TEST_CASE("crafting RawBlePdu message", test_raw_pdu)
TEST_CASE("crafting SendRawPdu message", test_send_raw_pdu)
TEST_CASE("parsing SendRawPdu message", test_send_raw_pdu_parse)
TEST_CASE("crafting SendPdu message", test_send_pdu)
TEST_CASE("parsing SendPdu message", test_send_pdu_parse)
TEST_CASE("crafting SetEncryption message", test_set_encryption_craft)
TEST_CASE("parsing SetEncryption message", test_set_encryption_parse)
TEST_CASE("crafting SetPhy message", test_set_phy_craft)
TEST_CASE("parsing SetPhy message", test_set_phy_parse)
TEST_CASE("crafting SetSupportedPhys message", test_set_supported_phys_craft)
TEST_CASE("parsing SetSupportedPhys message", test_set_supported_phys_parse)
TEST_CASE("crafting SetTxPower message", test_set_tx_power_craft)
TEST_CASE("parsing SetTxPower message", test_set_tx_power_parse)
TEST_CASE("crafting ReactiveJam message", test_reactive_jam_craft)
TEST_CASE("parsing ReactiveJam message", test_reactive_jam_parse)
TEST_CASE("crafting Connected notification", test_connected_notification)
TEST_CASE("crafting Disconnected notification", test_disconnected_notification_craft)
TEST_CASE("parsing Disconnected notification", test_disconnected_notification_parse)
TEST_CASE("crafting Triggered notification", test_triggered_notification_craft)
TEST_CASE("parsing Triggered notification", test_triggered_notification_parse)
TEST_CASE("checking connection status notifications", test_connection_status_notifications)
TEST_CASE("crafting PhyUpdated notification", test_phy_updated_craft)
TEST_CASE("parsing PhyUpdated notification", test_phy_updated_parse)
TEST_CASE("crafting extended advertising PDUs", test_extended_adv_pdus_craft)
TEST_CASE("parsing extended advertising PDUs", test_extended_adv_pdus_parse)
TEST_CASE("crafting Synchronized notification", test_synchronized_craft)
TEST_CASE("parsing Synchronized notification", test_synchronized_parse)
TEST_CASE("crafting access-address notification", test_access_address_discovered_craft)
TEST_CASE("parsing access-address notification", test_access_address_discovered_parse)
TEST_CASE("crafting advertising PDU", test_adv_pdu_craft)
TEST_CASE("parsing advertising PDU", test_adv_pdu_parse)
TEST_CASE("checking prepared-sequence controls", test_prepare_sequence_controls)
TEST_CASE("checking prepared sequences", test_prepare_sequence_roundtrip)
TEST_CASE("crafting PeripheralMode message", test_peripheral_mode_craft)
TEST_CASE("parsing PeripheralMode message", test_peripheral_mode_parse)
TEST_CASE("SetAdvData parser reports unsupported", test_unsupported_set_adv_data_parse)

TEST_CASE("getting message type", test_get_message_type)
TEST_CASE("getting message type (wrong domain)", test_get_message_type_not_ble)
TEST_SUITE_END()


bool test_run(test_t *p_test_suite, int count)
{
    pid_t pid, wpid;
    int status;
    int i, failed=0, succeeded=0;
    for (i=0; i<count; i++)
    {
        pid = fork();

        if (!pid)
        {
            exit((p_test_suite[i].p_func()==FAILURE)?1:0);
        }
        else
        {
            printf("[%d/%d] Testing %s... ", i+1, count, p_test_suite[i].psz_desc);

            /* Wait for test result. */
            wpid = waitpid(pid, &status, 0);
            if (wpid < 0) {
                printf("ERR\n");
                return false;
            }

            /* Process has exited normally. */
            if (WIFEXITED(status))
            {
                if (WEXITSTATUS(status) == 0)
                {
                    succeeded++;
                    printf("OK\n");
                }
                else
                {
                    failed++;
                    printf("KO\n");
                }
            }

            /* Process has crashed. */
            else if (WIFSIGNALED(status))
            {
                failed++;
                printf("ERROR (%d)\n", WTERMSIG(status));
            }
        }
    }
    printf("Result: %d PASSED, %d FAILED, %d TOTAL\n", succeeded, failed, count);
    return (failed != 0);
}


/** Main runner. **/

int main(int argc, char **argv)
{
    printf("*** Testing Bluetooth Low Energy C API\n");
    TEST_SUITE_RUN(ble_basic);
}
