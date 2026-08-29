#include "test.h"
#include "whad.h"

using namespace whad;
using namespace whad::ble;

/* Bluetooth Device address 'BDAddress' class. */

result_t test_bdaddress(void)
{
    uint8_t nulladdr[6] = {0, 0, 0, 0, 0, 0};
    uint8_t addr[6] = {0x11, 0x22, 0x33, 0x44, 0x55, 0x66};
    uint8_t other_addr[6] = {0x77, 0x88, 0x99, 0xaa, 0xbb, 0xcc};

    /* Build an address from its 6-byte value and type. */
    BDAddress bdaddr(AddressType::AddressRandom, addr);

    /* Check address type and value match. */
    assert_eq(bdaddr.getType(), AddressRandom);
    assert_buf_eq(bdaddr.getAddressBuf(), addr, 6);

    /* Check setType() modifies the address type. */
    bdaddr.setType(AddressPublic);
    assert_eq(bdaddr.getType(), AddressPublic);

    /* Check setAddress() modifies the address value. */
    bdaddr.setAddress(other_addr);
    assert_buf_eq(bdaddr.getAddressBuf(), other_addr, 6);

    /* Build a default empty address. */
    BDAddress defaddr;
    
    /* Check default address type is public and filled with zeroes. */
    assert_eq(defaddr.getType(), AddressPublic);
    assert_buf_eq(defaddr.getAddressBuf(), nulladdr, 6);

    /* Passed. */
    return PASS;
}

/* BLE Channel Map 'ChannelMap' class. */

result_t test_chanmap(void)
{

    /* Check that default channel map has its 40 channels active. */
    ChannelMap chanmap;
    for (int i=0; i<40; i++)
    {
        if (!chanmap.isChannelEnabled(i))
        {
            return FAILURE;
        }
    }

    /* Create a NULL channel map and check it is detected as such. */
    ChannelMap null_chanmap((uint8_t[5]){0, 0, 0, 0, 0});
    assert(null_chanmap.isNull());

    /* Create a channel map with a 5 channels enabled and check if they are
     * correctly set.
     */
    ChannelMap single_chanmap((uint8_t[5]){1, 2, 4, 8, 16});
    assert(single_chanmap.isChannelEnabled(0));
    assert(single_chanmap.isChannelEnabled(9));
    assert(single_chanmap.isChannelEnabled(18));
    assert(single_chanmap.isChannelEnabled(27));
    assert(single_chanmap.isChannelEnabled(36));

    /* Check a disabled channel is really disabled. */
    single_chanmap.disableChannel(18);
    assert(!single_chanmap.isChannelEnabled(18));

    /* Check a channel enabled is really enabled. */
    single_chanmap.enableChannel(5);
    assert(single_chanmap.isChannelEnabled(5));

    /* Passed. */
    return PASS;
}

/* Central mode */

result_t test_central_mode(void)
{
    Message msg;
    
    /* Craft a default CentralMode message. */
    CentralMode central;

    /* Check the generated protobuf message. */
    central.getRaw();
    assert_eq(central.getDomain(), DomainBle);
    assert_eq(central.getType(), CentralModeMsg);

    /* Check message parsing. */
    whad_ble_central_mode(&msg);
    NanoPbMsg message(&msg);
    assert_eq(message.getType(), DomainMsg);
    assert_eq(message.getDomain(), DomainBle);
    BleMsg bleMessage(message);
    assert_eq(bleMessage.getType(), CentralModeMsg);

    /* Passed. */
    return PASS;
}

/* Start */

result_t test_start(void)
{
    Message msg;

    /* Craft a default Start message. */
    Start start;

    /* Check message properties. */
    start.getRaw();
    assert_eq(start.getDomain(), DomainBle);
    assert_eq(start.getType(), StartMsg);

    /* Check parsing. */
    whad_ble_start(&msg);
    BleMsg bleMessage(&msg);
    assert_eq(bleMessage.getType(), StartMsg);

    /* Passed. */
    return PASS;
}

/* Stop */

result_t test_stop(void)
{
    Message msg;

    /* Craft a default Stop message. */
    Stop stop;

    /* Check message properties. */
    stop.getRaw();
    assert_eq(stop.getDomain(), DomainBle);
    assert_eq(stop.getType(), StopMsg);

    /* Check parsing. */
    whad_ble_stop(&msg);
    BleMsg bleMessage(&msg);
    assert_eq(bleMessage.getType(), StopMsg);

    /* Passed. */
    return PASS;
}

/**
 * Test the AdvMode convenience constructor.
 * Check its default advertising parameters, stored payloads and packed message.
 **/

result_t test_adv_mode_defaults(void)
{
    /* Define the advertising data, scan response and expected default channel map. */
    uint8_t adv_data[] = {0x02, 0x01, 0x06};
    uint8_t scanrsp_data[] = {0x05, 0x09, 0x41, 0x42, 0x43, 0x44};
    uint8_t default_chanmap[] = {0x00, 0x00, 0x00, 0x00, 0xe0};

    /* Create an advertising mode with the convenience constructor. */
    AdvMode mode(adv_data, sizeof(adv_data), scanrsp_data, sizeof(scanrsp_data));

    /* Check the default parameters and copied payloads exposed by the object. */
    assert_eq(mode.getAdvType(), AdvType::AdvInd);
    assert_eq(mode.getIntervalMin(), 0x20);
    assert_eq(mode.getIntervalMax(), 0x4000);
    assert_eq(mode.getCsa(), Csa::Csa1);
    assert_eq(mode.getAdvDataLength(), sizeof(adv_data));
    assert_buf_eq(mode.getAdvData(), adv_data, sizeof(adv_data));
    assert_eq(mode.getScanRspLength(), sizeof(scanrsp_data));
    assert_buf_eq(mode.getScanRsp(), scanrsp_data, sizeof(scanrsp_data));
    assert_buf_eq(mode.getChannelMap().getChannelMapBuf(), default_chanmap, sizeof(default_chanmap));

    /* Pack the object and check the generated protobuf message. */
    Message *message = mode.getRaw();
    assert_eq(mode.getDomain(), DomainBle);
    assert_eq(mode.getType(), AdvModeMsg);
    assert_eq((int)message->msg.ble.msg.adv_mode.adv_type, (int)BLE_ADV_IND);
    assert_eq(message->msg.ble.msg.adv_mode.inter_min, 0x20);
    assert_eq(message->msg.ble.msg.adv_mode.inter_max, 0x4000);
    assert_eq((int)message->msg.ble.msg.adv_mode.csa, (int)BLE_CSA1);
    assert_buf_eq(message->msg.ble.msg.adv_mode.adv_data.bytes, adv_data, sizeof(adv_data));
    assert_buf_eq(message->msg.ble.msg.adv_mode.scanrsp_data.bytes, scanrsp_data, sizeof(scanrsp_data));

    /* Passed. */
    return PASS;
}

/**
 * Test the fully parameterized AdvMode constructor.
 * Check that custom advertising parameters are retained and packed correctly.
 **/

result_t test_adv_mode_custom_parameters(void)
{
    /* Define custom payloads and an advertising channel map. */
    uint8_t adv_data[] = {0xaa, 0xbb};
    uint8_t scanrsp_data[] = {0xcc};
    uint8_t chanmap_data[] = {0x00, 0x00, 0x00, 0x00, 0xa0};
    ChannelMap chanmap(chanmap_data);

    /* Create and pack an advertising mode with custom parameters. */
    AdvMode mode(AdvType::AdvNonConnInd, 0x40, 0x80, adv_data, sizeof(adv_data),
            scanrsp_data, sizeof(scanrsp_data), chanmap, Csa::Csa2);
    Message *message = mode.getRaw();

    /* Check the custom parameters exposed by the object. */
    assert_eq(mode.getAdvType(), AdvType::AdvNonConnInd);
    assert_eq(mode.getIntervalMin(), 0x40);
    assert_eq(mode.getIntervalMax(), 0x80);
    assert_eq(mode.getCsa(), Csa::Csa2);
    assert_buf_eq(mode.getChannelMap().getChannelMapBuf(), chanmap_data, sizeof(chanmap_data));

    /* Check the custom parameters in the packed protobuf message. */
    assert_eq((int)message->msg.ble.msg.adv_mode.adv_type, (int)BLE_ADV_NONCONN_IND);
    assert_eq((int)message->msg.ble.msg.adv_mode.csa, (int)BLE_CSA2);
    assert_buf_eq(message->msg.ble.msg.adv_mode.channel_map, chanmap_data, sizeof(chanmap_data));

    /* Passed. */
    return PASS;
}

/**
 * Test construction of an AdvMode object from an existing BLE message.
 * Check that every legacy advertising parameter and payload is unpacked.
 **/

result_t test_adv_mode_parse(void)
{
    /* Define the raw message and the values it will contain. */
    Message message;
    uint8_t adv_data[] = {0x02, 0x01, 0x05};
    uint8_t scanrsp_data[] = {0x03, 0x09, 0x57, 0x48};
    uint8_t chanmap[] = {0x00, 0x00, 0x00, 0x00, 0xe0};

    /* Craft a valid raw AdvMode message. */
    assert_success(whad_ble_adv_mode(&message, BLE_ADV_SCAN_IND, 100, 200, chanmap,
                adv_data, sizeof(adv_data), scanrsp_data, sizeof(scanrsp_data), BLE_CSA2,
                NULL, 0));

    /* Wrap and parse the raw BLE message as an AdvMode object. */
    BleMsg ble_message(&message);
    AdvMode mode(ble_message);

    /* Check all parsed advertising parameters and payloads. */
    assert_eq(mode.getAdvType(), AdvType::AdvScanInd);
    assert_eq(mode.getIntervalMin(), 100);
    assert_eq(mode.getIntervalMax(), 200);
    assert_eq(mode.getCsa(), Csa::Csa2);
    assert_eq(mode.getAdvDataLength(), sizeof(adv_data));
    assert_buf_eq(mode.getAdvData(), adv_data, sizeof(adv_data));
    assert_eq(mode.getScanRspLength(), sizeof(scanrsp_data));
    assert_buf_eq(mode.getScanRsp(), scanrsp_data, sizeof(scanrsp_data));
    assert_buf_eq(mode.getChannelMap().getChannelMapBuf(), chanmap, sizeof(chanmap));

    /* Passed. */
    return PASS;
}

/**
 * Test AdvMode handling of advertising payloads larger than 31 bytes.
 * Check oversized advertising and scan-response data are independently rejected.
 **/

result_t test_adv_mode_rejects_oversized_data(void)
{
    /* Define one oversized payload and one valid payload. */
    uint8_t oversized_data[32] = {0};
    uint8_t valid_data[] = {0x01};

    /* Check oversized advertising data is rejected without affecting scan data. */
    AdvMode oversized_adv(oversized_data, sizeof(oversized_data), valid_data, sizeof(valid_data));
    assert_eq(oversized_adv.getAdvDataLength(), 0);
    assert_eq(oversized_adv.getScanRspLength(), sizeof(valid_data));

    /* Check oversized scan data is rejected without affecting advertising data. */
    AdvMode oversized_scan(valid_data, sizeof(valid_data), oversized_data, sizeof(oversized_data));
    assert_eq(oversized_scan.getAdvDataLength(), sizeof(valid_data));
    assert_eq(oversized_scan.getScanRspLength(), 0);

    /* Passed. */
    return PASS;
}

/**
 * Test management and packing of AdvMode extended advertising PDUs.
 * Check the four-PDU limit, indexed access and generated protobuf entries.
 **/

result_t test_adv_mode_extended_pdus(void)
{
    /* Define the primary payload and five extended advertising payloads. */
    uint8_t adv_data[] = {0x11, 0x22, 0x33};
    uint8_t ext_data[][2] = {
        {0x01, 0x02}, {0x03, 0x04}, {0x05, 0x06}, {0x07, 0x08}, {0x09, 0x0a}
    };
    AdvMode mode(adv_data, sizeof(adv_data), NULL, 0);
    ExtAdvPdu pdus[] = {
        ExtAdvPdu(ext_data[0], sizeof(ext_data[0])),
        ExtAdvPdu(ext_data[1], sizeof(ext_data[1])),
        ExtAdvPdu(ext_data[2], sizeof(ext_data[2])),
        ExtAdvPdu(ext_data[3], sizeof(ext_data[3])),
        ExtAdvPdu(ext_data[4], sizeof(ext_data[4]))
    };

    /* Add the maximum number of PDUs and check a fifth PDU is rejected. */
    for (unsigned int i = 0; i < 4; i++)
        assert(mode.addExtPdu(pdus[i]));
    assert(!mode.addExtPdu(pdus[4]));
    assert_eq(mode.getNumberOfExtPdus(), 4);
    assert(mode.getExtPdu(4) == NULL);

    /* Check every stored PDU can be retrieved with its original payload. */
    for (unsigned int i = 0; i < 4; i++)
    {
        assert(mode.getExtPdu(i) != NULL);
        assert_eq(mode.getExtPdu(i)->getLength(), sizeof(ext_data[i]));
        assert_buf_eq(mode.getExtPdu(i)->getData(), ext_data[i], sizeof(ext_data[i]));
    }

    /* Pack the object and check the number of extended PDUs. */
    Message *message = mode.getRaw();
    assert_eq(message->msg.ble.msg.adv_mode.ext_pdus_count, 4);

    /* Check each packed PDU contains its payload and no auxiliary pointer. */
    for (unsigned int i = 0; i < 4; i++)
    {
        assert_eq(message->msg.ble.msg.adv_mode.ext_pdus[i].adv_data.size, sizeof(ext_data[i]));
        assert_buf_eq(message->msg.ble.msg.adv_mode.ext_pdus[i].adv_data.bytes,
                ext_data[i], sizeof(ext_data[i]));
        assert(!message->msg.ble.msg.adv_mode.ext_pdus[i].has_aux_ptr);
    }

    /* Passed. */
    return PASS;
}

TEST_SUITE_BEGIN(ble_basic) 
TEST_CASE("BDAddress class", test_bdaddress)
TEST_CASE("ChannelMap class", test_chanmap)
TEST_CASE("CentralMode message", test_central_mode)
TEST_CASE("Start message", test_start)
TEST_CASE("Stop message", test_stop)
TEST_CASE("AdvMode default parameters", test_adv_mode_defaults)
TEST_CASE("AdvMode custom parameters", test_adv_mode_custom_parameters)
TEST_CASE("AdvMode parsing", test_adv_mode_parse)
TEST_CASE("AdvMode oversized data", test_adv_mode_rejects_oversized_data)
TEST_CASE("AdvMode extended PDUs", test_adv_mode_extended_pdus)
TEST_SUITE_END()


/** Main runner. **/
int main(int argc, char **argv)
{
    printf("*** Testing Bluetooth Low Energy C++ API\n");
    TEST_SUITE_RUN(ble_basic);
}
