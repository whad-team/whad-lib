#include <vector>

#include "test.h"
#include "cpp/whad.hpp"
#include "cpp/ble/disconnect.hpp"
#include "cpp/ble/phy.hpp"
#include "cpp/ble/txpower.hpp"

using namespace whad;
using namespace whad::ble;

/**
 * Test the SetBdAddress message wrapper.
 * Check its address property, message type and BLE domain.
 **/

result_t test_set_bd_address(void)
{
    uint8_t address_bytes[] = {1, 2, 3, 4, 5, 6};
    BDAddress address(AddressRandom, address_bytes);
    SetBdAddress message(address);

    /* Check the retained address and packed message identity. */
    assert_eq(message.getAddress()->getType(), AddressRandom);
    assert_buf_eq(message.getAddress()->getAddressBuf(), address_bytes, sizeof(address_bytes));
    message.getRaw();
    assert_eq(message.getDomain(), DomainBle);
    assert_eq(message.getType(), SetBdAddressMsg);

    /* Passed. */
    return PASS;
}

/**
 * Test the SetAdvData message wrapper.
 * Check advertising and scan-response payloads and the packed message type.
 **/

result_t test_set_advertising_data(void)
{
    uint8_t advertising_data[] = {0x02, 0x01, 0x06};
    uint8_t scan_response[] = {0x03, 0x09, 0x57, 0x48};
    SetAdvData message(advertising_data, sizeof(advertising_data),
            scan_response, sizeof(scan_response));

    /* Check the raw payloads produced directly by the constructor. */
    Message *raw_message = message.getMessage();
    assert_eq(whad_ble_get_message_type(raw_message), WHAD_BLE_SET_ADV_DATA);
    assert_eq(raw_message->msg.ble.msg.set_adv_data.adv_data.size, sizeof(advertising_data));
    assert_buf_eq(raw_message->msg.ble.msg.set_adv_data.adv_data.bytes,
            advertising_data, sizeof(advertising_data));
    assert_eq(raw_message->msg.ble.msg.set_adv_data.scanrsp_data.size, sizeof(scan_response));
    assert_buf_eq(raw_message->msg.ble.msg.set_adv_data.scanrsp_data.bytes,
            scan_response, sizeof(scan_response));

    /* Passed. */
    return PASS;
}

/**
 * Test BLE access-address sniffing and discovery messages.
 * Check channel, PHY, access address and optional metadata.
 **/

result_t test_access_address_messages(void)
{
    uint8_t channels[] = {0xff, 0xff, 0xff, 0xff, 0x1f};
    ChannelMap channel_map(channels);
    SniffAccessAddress sniff(channel_map, LE2Mbit);
    AccessAddressDiscovered discovered(0x8e89bed6, 123456U, -42);

    /* Check the sniffing request. */
    assert_buf_eq(sniff.getChannelMap().getChannelMapBuf(), channels, sizeof(channels));
    assert_eq(sniff.getPhy(), LE2Mbit);
    sniff.getRaw();
    assert_eq(sniff.getType(), SniffAAMsg);

    /* Check the resulting discovery notification. */
    assert_eq(discovered.getAccessAddress(), 0x8e89bed6);
    assert(discovered.hasTimestamp());
    assert_eq(discovered.getTimestamp(), 123456);
    assert(discovered.hasRssi());
    assert_eq(discovered.getRssi(), -42);
    discovered.getRaw();
    assert_eq(discovered.getType(), AccessAddressDiscoveredMsg);

    /* Passed. */
    return PASS;
}

/**
 * Test advertisement and connection-request sniffing messages.
 * Check their filtering parameters and packed message types.
 **/

result_t test_advertisement_sniffing_messages(void)
{
    uint8_t address_bytes[] = {6, 5, 4, 3, 2, 1};
    BDAddress address(AddressPublic, address_bytes);
    SniffAdv sniff_advertisements(37, address, true);
    SniffConnReq sniff_requests(38, address, true, false);

    /* Check advertisement sniffing parameters. */
    assert_eq(sniff_advertisements.getChannel(), 37);
    assert(sniff_advertisements.mustUseExtAdv());
    assert_buf_eq(sniff_advertisements.getAddress().getAddressBuf(), address_bytes, 6);
    sniff_advertisements.getRaw();
    assert_eq(sniff_advertisements.getType(), SniffAdvMsg);

    /* Check the connection-request message produced by its constructor. */
    assert_eq(whad_ble_get_message_type(sniff_requests.getMessage()), WHAD_BLE_SNIFF_CONN_REQ);

    /* Passed. */
    return PASS;
}

/**
 * Test active-connection sniffing and synchronization messages.
 * Check connection parameters, channel maps, PHY and packed message types.
 **/

result_t test_connection_sniffing_messages(void)
{
    uint8_t channel_map_bytes[] = {0xff, 0xff, 0xff, 0xff, 0x1f};
    uint8_t monitored_bytes[] = {0x03, 0, 0, 0, 0};
    ChannelMap channel_map(channel_map_bytes);
    ChannelMap monitored_channels(monitored_bytes);
    SniffActiveConn sniff(0x11223344, 0x00a1b2c3, 24, 9,
            channel_map, monitored_channels, LE1Mbit);
    Synchronized synchronized(0x11223344, 0x00a1b2c3, 24, 9,
            channel_map, LE1Mbit);
    Desynchronized desynchronized(0x11223344);

    /* Check active-connection sniffing parameters. */
    assert_eq(sniff.getAccessAddress(), 0x11223344);
    assert_eq(sniff.getCrcInit(), 0x00a1b2c3);
    assert_eq(sniff.getHopInterval(), 24);
    assert_eq(sniff.getHopIncrement(), 9);
    assert_buf_eq(sniff.getChannels().getChannelMapBuf(), monitored_bytes, 5);
    sniff.getRaw();
    assert_eq(sniff.getType(), SniffActConnMsg);

    /* Check synchronization and desynchronization notifications. */
    assert_eq(synchronized.getPhy(), LE1Mbit);
    synchronized.getRaw();
    assert_eq(synchronized.getType(), SynchronizedMsg);
    assert_eq(desynchronized.getAccessAddress(), 0x11223344);
    desynchronized.getRaw();
    assert_eq(desynchronized.getType(), DesynchronizedMsg);

    /* Passed. */
    return PASS;
}

/**
 * Test scanning mode and received advertising PDU wrappers.
 * Check extended scanning options and notification payload metadata.
 **/

result_t test_scan_and_advertising_pdu(void)
{
    uint8_t address_bytes[] = {0xaa, 0xbb, 0xcc, 0xdd, 0xee, 0xff};
    uint8_t advertising_data[] = {0x02, 0x01, 0x05};
    BDAddress address(AddressRandom, address_bytes);
    ScanMode scan(true, 160, true);
    AdvPdu pdu(AdvScanInd, -51, address, advertising_data,
            sizeof(advertising_data), 39, LE1MbitCoded);

    /* Check scanning configuration. */
    assert(scan.isActiveModeEnabled());
    assert_eq(scan.getInterval(), 160);
    assert(scan.useExtAdv());
    scan.getRaw();
    assert_eq(scan.getType(), ScanModeMsg);

    /* Check the received advertising PDU. */
    assert_eq(pdu.getAdvType(), AdvScanInd);
    assert_eq(pdu.getRssi(), -51);
    assert_eq(pdu.getAdvDataLength(), sizeof(advertising_data));
    assert_buf_eq(pdu.getAdvData(), advertising_data, sizeof(advertising_data));
    assert_eq(pdu.getChannel(), 39);
    assert_eq(pdu.getPhy(), LE1MbitCoded);
    pdu.getRaw();
    assert_eq(pdu.getType(), AdvPduMsg);

    /* Passed. */
    return PASS;
}

/**
 * Test peripheral mode construction.
 * Check custom advertising parameters, payloads and packed message type.
 **/

result_t test_peripheral_mode(void)
{
    uint8_t advertising_data[] = {0x02, 0x01, 0x06};
    uint8_t scan_response[] = {0x03, 0x09, 0x41, 0x42};
    uint8_t channel_map_bytes[] = {0, 0, 0, 0, 0xa0};
    ChannelMap channel_map(channel_map_bytes);
    PeripheralMode mode(advertising_data, sizeof(advertising_data), scan_response,
            sizeof(scan_response), AdvNonConnInd, channel_map, 64, 128, Csa2);

    /* Check custom mode parameters and packed identity. */
    assert_eq(mode.getAdvType(), AdvNonConnInd);
    assert_eq(mode.getIntervalMin(), 64);
    assert_eq(mode.getIntervalMax(), 128);
    assert_eq(mode.getCsa(), Csa2);
    assert_buf_eq(mode.getAdvData(), advertising_data, sizeof(advertising_data));
    mode.getRaw();
    assert_eq(mode.getType(), PeriphModeMsg);

    /* Passed. */
    return PASS;
}

/**
 * Test connection initiation and disconnection wrappers.
 * Check connection parameters and packed message types.
 **/

result_t test_connect_and_disconnect(void)
{
    uint8_t address_bytes[] = {1, 3, 5, 7, 9, 11};
    uint8_t channel_map_bytes[] = {0xff, 0xff, 0xff, 0xff, 0x1f};
    BDAddress address(AddressRandom, address_bytes);
    ChannelMap channel_map(channel_map_bytes);
    ConnectTo connect(address, 0x12345678, channel_map, 36, 11, 0xabcdef, Csa2);
    Disconnect disconnect(0x10203040);

    /* Check connection parameters and identity. */
    assert_eq(connect.getAccessAddr(), 0x12345678);
    assert_eq(connect.getHopInterval(), 36);
    assert_eq(connect.getHopIncrement(), 11);
    assert_eq(connect.getCrcInit(), 0xabcdef);
    assert_eq(connect.getCsa(), Csa2);
    connect.getRaw();
    assert_eq(connect.getType(), ConnectToMsg);

    /* Check disconnection parameters and identity. */
    disconnect.getRaw();
    assert_eq(disconnect.getType(), DisconnectMsg);

    /* Passed. */
    return PASS;
}

/**
 * Test cooked and raw PDU transmission wrappers.
 * Check payload, addressing, encryption, direction and PHY parameters.
 **/

result_t test_send_pdu_messages(void)
{
    uint8_t bytes[] = {0x01, 0x02, 0x03, 0x04};
    SendPdu cooked(DirectionMasterToSlave, 7, bytes, sizeof(bytes), true, LE2Mbit);
    SendRawPdu raw(DirectionSlaveToMaster, 8, 0x8e89bed6, bytes,
            sizeof(bytes), 0x00aabbcc, false, LE1Mbit);

    /* Check the cooked transmission request. */
    assert_eq(cooked.getDirection(), DirectionMasterToSlave);
    assert_eq(cooked.getConnHandle(), 7);
    assert(cooked.isEncrypted());
    assert_buf_eq(cooked.getPdu().getBytes(), bytes, sizeof(bytes));
    cooked.getRaw();
    assert_eq(cooked.getType(), SendPduMsg);

    /* Check the raw transmission request. */
    assert_eq(raw.getDirection(), DirectionSlaveToMaster);
    assert_eq(raw.getAccessAddress(), 0x8e89bed6);
    assert_eq(raw.getCrc(), 0x00aabbcc);
    assert(!raw.isEncrypted());
    raw.getRaw();
    assert_eq(raw.getType(), SendRawPduMsg);

    /* Passed. */
    return PASS;
}

/**
 * Test encryption configuration.
 * Check all cryptographic buffers, connection handle and enable flag.
 **/

result_t test_set_encryption(void)
{
    uint8_t ll_key[16] = {0};
    uint8_t ll_iv[8] = {1};
    uint8_t key[16] = {2};
    uint8_t random[8] = {3};
    uint8_t ediv[2] = {4, 5};
    SetEncryption encryption(12, ll_key, ll_iv, key, random, ediv, true);

    /* Check encryption parameters and packed identity. */
    assert_eq(encryption.getConnHandle(), 12);
    assert_buf_eq(encryption.getLLKey(), ll_key, sizeof(ll_key));
    assert_buf_eq(encryption.getLLIv(), ll_iv, sizeof(ll_iv));
    assert_buf_eq(encryption.getKey(), key, sizeof(key));
    assert_buf_eq(encryption.getRand(), random, sizeof(random));
    assert_buf_eq(encryption.getEDiv(), ediv, sizeof(ediv));
    assert(encryption.isEnabled());
    encryption.getRaw();
    assert_eq(encryption.getType(), SetEncryptionMsg);

    /* Passed. */
    return PASS;
}

/**
 * Test manual and connection-event prepared sequences.
 * Check trigger helpers, sequence payloads and command message types.
 **/

result_t test_prepared_sequence_messages(void)
{
    uint8_t first_bytes[] = {0x01, 0x02};
    uint8_t second_bytes[] = {0x03, 0x04, 0x05};
    PDU first(first_bytes, sizeof(first_bytes));
    PDU second(second_bytes, sizeof(second_bytes));
    std::vector<PDU> packets;
    packets.push_back(first);
    packets.push_back(second);
    PrepareSequenceManual manual(5, DirectionMasterToSlave, packets);
    PrepareSequenceConnEvt connection_event(6, DirectionSlaveToMaster, packets, 99);
    ManualTrigger trigger(5);
    DeleteSequence deletion(6);
    SequenceTriggered notification(5);
    Triggered alternate_notification(7);

    /* Check sequence parameters and packed identities. */
    assert_eq(manual.getId(), 5);
    assert_eq(manual.getPackets().size(), 2);
    manual.getRaw();
    assert_eq(manual.BleMsg::getType(), PrepareSeqMsg);
    assert_eq(connection_event.getConnEvt(), 99);
    connection_event.getRaw();
    assert_eq(connection_event.BleMsg::getType(), PrepareSeqMsg);

    /* Check trigger, deletion and notification messages. */
    assert_eq(trigger.getId(), 5);
    trigger.getRaw();
    assert_eq(trigger.getType(), PrepareSeqTriggerMsg);
    assert_eq(deletion.getId(), 6);
    deletion.getRaw();
    assert_eq(deletion.getType(), PrepareSeqDeleteMsg);
    notification.getRaw();
    assert_eq(notification.getType(), TriggeredMsg);
    assert_eq(alternate_notification.getId(), 7);
    alternate_notification.getRaw();
    assert_eq(alternate_notification.getType(), TriggeredMsg);

    /* Passed. */
    return PASS;
}

/**
 * Test standalone sequence trigger helper classes.
 * Check default and configured connection-event and pattern values.
 **/

result_t test_sequence_trigger_helpers(void)
{
    uint8_t pattern[] = {0xaa, 0xbb, 0xcc};
    uint8_t mask[] = {0xff, 0x0f, 0xf0};
    ConnEventTrigger connection_event(123);
    PatternTrigger pattern_trigger(pattern, mask, sizeof(pattern), 7);

    /* Check connection-event and pattern trigger values. */
    assert_eq(connection_event.getConnEvent(), 123);
    assert_eq(pattern_trigger.getLength(), sizeof(pattern));
    assert_buf_eq(pattern_trigger.getPattern(), pattern, sizeof(pattern));
    assert_buf_eq(pattern_trigger.getMask(), mask, sizeof(mask));
    assert_eq(pattern_trigger.getOffset(), 7);

    /* Passed. */
    return PASS;
}

/**
 * Test advertisement and active-connection jamming wrappers.
 * Check optional channel, access address, PHY and packed message kinds.
 **/

result_t test_jamming_messages(void)
{
    JamAdv all_advertising;
    JamAdv one_channel(38);
    JamActiveConn active_connection(0x11223344, LE2Mbit);

    /* Check advertisement jamming variants. */
    assert(!all_advertising.hasChannel());
    all_advertising.getRaw();
    assert_eq(all_advertising.getType(), JamAdvMsg);
    assert(one_channel.hasChannel());
    assert_eq(one_channel.getChannel(), 38);
    one_channel.getRaw();
    assert_eq(one_channel.getType(), JamAdvChannelMsg);

    /* Check active-connection jamming. */
    assert_eq(active_connection.getAccessAddress(), 0x11223344);
    assert_eq(active_connection.getPhy(), LE2Mbit);
    active_connection.getRaw();
    assert_eq(active_connection.getType(), JamActConnMsg);

    /* Passed. */
    return PASS;
}

/**
 * Test reactive jamming configuration.
 * Check matching pattern, position, channel, PHY and packed message type.
 **/

result_t test_reactive_jamming(void)
{
    uint8_t pattern[] = {0xde, 0xad, 0xbe, 0xef};
    ReactiveJam jam(20, pattern, sizeof(pattern), 3, LE1MbitCoded);

    /* Check reactive jamming parameters and identity. */
    assert_eq(jam.getChannel(), 20);
    assert_eq(jam.getPatternLength(), sizeof(pattern));
    assert_buf_eq(jam.getPattern(), pattern, sizeof(pattern));
    assert_eq(jam.getPosition(), 3);
    assert_eq(jam.getPhy(), LE1MbitCoded);
    jam.getRaw();
    assert_eq(jam.getType(), ReactiveJamMsg);

    /* Passed. */
    return PASS;
}

/**
 * Test all connection-hijacking command wrappers.
 * Check access addresses and packed message types.
 **/

result_t test_hijacking_messages(void)
{
    HijackMaster master(0x11111111);
    HijackSlave slave(0x22222222);
    HijackBoth both(0x33333333);

    /* Check access addresses and command identities. */
    assert_eq(master.getAccessAddress(), 0x11111111);
    master.getRaw();
    assert_eq(master.getType(), HijackMasterMsg);
    assert_eq(slave.getAccessAddress(), 0x22222222);
    slave.getRaw();
    assert_eq(slave.getType(), HijackSlaveMsg);
    assert_eq(both.getAccessAddress(), 0x33333333);
    both.getRaw();
    assert_eq(both.getType(), HijackBothMsg);

    /* Passed. */
    return PASS;
}

/**
 * Test connection and disconnection notification wrappers.
 * Check addresses, connection metadata and packed message types.
 **/

result_t test_connection_notifications(void)
{
    uint8_t advertiser_bytes[] = {1, 2, 3, 4, 5, 6};
    uint8_t initiator_bytes[] = {6, 5, 4, 3, 2, 1};
    BDAddress advertiser(AddressPublic, advertiser_bytes);
    BDAddress initiator(AddressRandom, initiator_bytes);
    Connected connected(17, advertiser, initiator, LE2Mbit);
    Disconnected disconnected(17, 0x13);

    /* Check the connection notification. */
    assert_eq(connected.getConnHandle(), 17);
    assert_eq(connected.getPhy(), LE2Mbit);
    assert_buf_eq(connected.getAdvertiserAddr().getAddressBuf(), advertiser_bytes, 6);
    connected.getRaw();
    assert_eq(connected.getType(), NotifyConnectedMsg);

    /* Check the disconnection notification. */
    assert_eq(disconnected.getConnHandle(), 17);
    assert_eq(disconnected.getReasonCode(), 0x13);
    disconnected.getRaw();
    assert_eq(disconnected.getType(), NotifyDisconnectedMsg);

    /* Passed. */
    return PASS;
}

/**
 * Test injection and hijacking status notifications.
 * Check their status fields and packed message types.
 **/

result_t test_operation_notifications(void)
{
    Injected injected(0x12345678, 4, true);
    Hijacked hijacked(0x87654321, false);

    /* Check injection status. */
    assert_eq(injected.getAccessAddress(), 0x12345678);
    assert_eq(injected.getAttempts(), 4);
    assert(injected.isSuccessful());
    injected.getRaw();
    assert_eq(injected.getType(), InjectedMsg);

    /* Check hijacking status. */
    assert_eq(hijacked.getAccessAddress(), 0x87654321);
    hijacked.getRaw();
    assert_eq(hijacked.getType(), HijackedMsg);

    /* Passed. */
    return PASS;
}

/**
 * Test cooked and raw received-PDU wrappers.
 * Check packet metadata, timestamps, direction, PHY and message types.
 **/

result_t test_received_pdu_messages(void)
{
    uint8_t bytes[] = {0x02, 0x01, 0x00};
    PDU packet(bytes, sizeof(bytes));
    LinkLayerPdu cooked(23, packet, DirectionSlaveToMaster, true, true, LE2Mbit);
    RawPdu raw(37, -65, 23, 0x8e89bed6, packet, 0x00abcdef, true,
            1000, 25, DirectionMasterToSlave, false, false, LE1Mbit);

    /* Check the cooked received PDU. */
    assert_eq(cooked.getConnHandle(), 23);
    assert(cooked.isProcessed());
    assert(cooked.isDecrypted());
    assert_buf_eq(cooked.getPdu().getBytes(), bytes, sizeof(bytes));
    cooked.getRaw();
    assert_eq(cooked.getType(), PduMsg);

    /* Check the raw received PDU. */
    assert_eq(raw.getChannel(), 37);
    assert_eq(raw.getRssi(), -65);
    assert(raw.isCrcValid());
    assert(raw.hasTimestamp());
    assert_eq(raw.getTimestamp(), 1000);
    assert_eq(raw.getRelativeTimestamp(), 25);
    raw.getRaw();
    assert_eq(raw.getType(), RawPduMsg);

    /* Passed. */
    return PASS;
}

/**
 * Test BLE PHY configuration and update wrappers.
 * Check TX/RX PHYs, supported sets and packed message types.
 **/

result_t test_phy_messages(void)
{
    SetPhy set_phy(LE2Mbit, LE1MbitCoded);
    PhyUpdated updated(LE1Mbit, LE2Mbit);
    SetSupportedPhys supported;

    /* Configure and check supported PHY lists. */
    assert(supported.addTxPhy(LE1Mbit));
    assert(supported.addTxPhy(LE2Mbit));
    assert(supported.addRxPhy(LE1MbitCoded));
    assert_eq(supported.countTxPhy(), 2);
    assert_eq(supported.countRxPhy(), 1);
    assert_eq(supported.getTxPhy(1), LE2Mbit);
    assert_eq(supported.getRxPhy(0), LE1MbitCoded);

    /* Pack and identify PHY configuration messages. */
    assert_eq(set_phy.getTx(), LE2Mbit);
    assert_eq(set_phy.getRx(), LE1MbitCoded);
    set_phy.getRaw();
    assert_eq(set_phy.getType(), SetPhyMsg);
    updated.getRaw();
    assert_eq(updated.getTx(), LE1Mbit);
    assert_eq(updated.getRx(), LE2Mbit);
    supported.getRaw();
    assert_eq(supported.getType(), SetSupportedPhysMsg);

    /* Passed. */
    return PASS;
}

/**
 * Test transmit-power configuration.
 * Check the signed level and packed message type.
 **/

result_t test_tx_power(void)
{
    SetTxPowerLevel power(-12);

    /* Check the configured power and message identity. */
    assert_eq(power.getLevel(), -12);
    power.getRaw();
    assert_eq(power.getType(), SetTxPowerMsg);

    /* Passed. */
    return PASS;
}

TEST_SUITE_BEGIN(ble_remaining)
TEST_CASE("Set BLE address", test_set_bd_address)
TEST_CASE("Set advertising data", test_set_advertising_data)
TEST_CASE("Access-address messages", test_access_address_messages)
TEST_CASE("Advertisement sniffing messages", test_advertisement_sniffing_messages)
TEST_CASE("Connection sniffing messages", test_connection_sniffing_messages)
TEST_CASE("Scan and advertising PDU", test_scan_and_advertising_pdu)
TEST_CASE("Peripheral mode", test_peripheral_mode)
TEST_CASE("Connect and disconnect", test_connect_and_disconnect)
TEST_CASE("Send PDU messages", test_send_pdu_messages)
TEST_CASE("Set encryption", test_set_encryption)
TEST_CASE("Prepared sequence messages", test_prepared_sequence_messages)
TEST_CASE("Sequence trigger helpers", test_sequence_trigger_helpers)
TEST_CASE("Jamming messages", test_jamming_messages)
TEST_CASE("Reactive jamming", test_reactive_jamming)
TEST_CASE("Hijacking messages", test_hijacking_messages)
TEST_CASE("Connection notifications", test_connection_notifications)
TEST_CASE("Operation notifications", test_operation_notifications)
TEST_CASE("Received PDU messages", test_received_pdu_messages)
TEST_CASE("PHY messages", test_phy_messages)
TEST_CASE("TX power", test_tx_power)
TEST_SUITE_END()

int main(void)
{
    /* Run the remaining BLE C++ API tests. */
    printf("*** Testing remaining Bluetooth Low Energy C++ API\n");
    return TEST_SUITE_RUN(ble_remaining);
}
