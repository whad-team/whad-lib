/**
 * Bluetooth Low Energy unit tests.
 **/
#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#include "whad.h"

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


/* Define test suite for BLE C API. */
TEST_SUITE_BEGIN(ble_basic) 
TEST_CASE("setting bluetooth LE address", test_set_bdaddress)
TEST_CASE("setting bluetooth LE address (bad message pointer)", test_set_bdaddress_bad_pmsg)
TEST_CASE("setting bluetooth LE address (bad address pointer)", test_set_bdaddress_bad_addr)
TEST_CASE("parsing SetBdAddress message", test_set_bdaddress_parse)
TEST_CASE("crafting SniffAdv message", test_sniff_adv_craft)
TEST_CASE("parsing SniffAdv message", test_sniff_adv_craft)
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
