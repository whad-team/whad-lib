#include "cpp/ble.hpp"

using namespace whad::ble;

/**
 * @brief   BD Address constructor.
 * 
 * @param[in]   type        Address type
 * @param[in]   p_bdaddr    BD address byte buffer (6 bytes)
 **/

BDAddress::BDAddress(AddressType type, uint8_t *p_bdaddr)
{
    this->m_type = type;
    memcpy(this->m_address, p_bdaddr, 6);
}


/**
 * @brief   Get address type.
 * 
 * @retval  AddressPublic   Address type is public
 * @retval  AddressRandom   Address type is random
 **/

AddressType BDAddress::getType(void)
{
    return this->m_type;
}


ChannelMap::ChannelMap()
{
    /* By default, all 40 channels are active. */
    memset(this->m_map, 0xff, 5);
}

ChannelMap::ChannelMap(uint8_t channelMap[5])
{
    /* Import channel map. */
    memcpy(this->m_map, channelMap, 5);
}

void ChannelMap::enableChannel(int channel)
{
    int n,o;

    if ((channel >= 0) && (channel <= 39))
    {
        n = channel / 8;
        o = channel % 8;
        m_map[n] |= (1 << o);
    }
}

void ChannelMap::disableChannel(int channel)
{
    int n,o;

    if ((channel >= 0) && (channel <= 39))
    {
        n = channel / 8;
        o = channel % 8;
        m_map[n] &= ~(1 << o);
    }
}

bool ChannelMap::isChannelEnabled(int channel)
{
    int n,o;
    
    if ((channel >= 0) && (channel <= 39))
    {
        n = channel / 8;
        o = channel % 8;
        return ((m_map[n] & (1 << o)) != 0);
    }

    /* Bad channel, not enabled. */
    return false;
}

uint8_t *ChannelMap::getChannelMapBuf(void)
{
    return this->m_map;
}


/**
 * @brief   Get a pointer onto the underlying Bluetooth Device address buffer.
 * 
 * @return  Pointer to the byte-buffer containing the device BD address (6 bytes) 
 **/

uint8_t *BDAddress::getAddressBuf(void)
{
    return this->m_address;
}


/**
 * @brief   Create a LinkLayerPdu object from a BLE PDU.
 * 
 * @param[in]   pdu         Pointer to a byte array containing the PDU
 * @param[in]   length      Size in bytes of the PDU
 * @param[in]   direction   Direction of the PDU (host to slave, slave to host, ...)
 **/

LinkLayerPdu::LinkLayerPdu(uint32_t conn_handle, PDU pdu, Direction direction, bool processed, bool decrypted) : NanoPbMsg()
{
    /* Initialize our data pdu message. */
    whad_ble_pdu(this->getRaw(), pdu.getBuf(), pdu.getLength(), (whad_ble_direction_t)direction, conn_handle, processed, decrypted);
}

/**
 * @brief   Raw PDU constructor, including timestamp.
 * 
 * @param[in]       channel             Channel on which this PDU has been received
 * @param[in]       rssi                Received Signal Strength Indicator
 * @param[in]       conn_handle         Connection handle
 * @param[in]       access_address      Access Address of the connection
 * @param[in]       p_pdu               Pointer to a byte array containing the PDU
 * @param[in]       length              Length of the data PDU, in bytes
 * @param[in]       crc                 PDU CRC value
 * @param[in]       crc_validity        Set to true if CRC matches the expected value, false otherwise
 * @param[in]       timestamp           PDU timestamp (in micro-seconds)
 * @param[in]       relative_timestamp  PDU relative timestamp (number of micro-seconds in the last connection event)
 * @param[in]       direction           Direction of the PDU (master -> slave / slave -> master)
 * @param[in]       processed           Set to true if PDU has been processed by the device, false otherwise
 * @param[in]       decrypted           Set to true if PDU has been decrypted, false otherwise
 **/

RawPdu::RawPdu(uint32_t channel, int32_t rssi, uint32_t conn_handle, uint32_t access_address,
                          PDU pdu, uint32_t crc, bool crc_validity, uint32_t timestamp,
                          uint32_t relative_timestamp, Direction direction, bool processed,
                          bool decrypted) : NanoPbMsg()
{
    whad_ble_raw_pdu(this->getRaw(), channel, rssi, conn_handle, access_address, pdu.getBuf(), pdu.getLength(), crc, 
                     crc_validity, timestamp, relative_timestamp, (whad_ble_direction_t)direction, processed,
                     decrypted, true);
}

/**
 * @brief   Raw PDU constructor, no timestamp.
 * 
 * @param[in]       channel             Channel on which this PDU has been received
 * @param[in]       rssi                Received Signal Strength Indicator
 * @param[in]       conn_handle         Connection handle
 * @param[in]       access_address      Access Address of the connection
 * @param[in]       p_pdu               Pointer to a byte array containing the PDU
 * @param[in]       length              Length of the data PDU, in bytes
 * @param[in]       crc                 PDU CRC value
 * @param[in]       crc_validity        Set to true if CRC matches the expected value, false otherwise
 * @param[in]       direction           Direction of the PDU (master -> slave / slave -> master)
 * @param[in]       processed           Set to true if PDU has been processed by the device, false otherwise
 * @param[in]       decrypted           Set to true if PDU has been decrypted, false otherwise
 **/

RawPdu::RawPdu(uint32_t channel, int32_t rssi, uint32_t conn_handle, uint32_t access_address,
                           PDU pdu, uint32_t crc, bool crc_validity, Direction direction,
                           bool processed, bool decrypted) : NanoPbMsg()
{
    whad_ble_raw_pdu(this->getRaw(), channel, rssi, conn_handle, access_address, pdu.getBuf(), pdu.getLength(),
                     crc, crc_validity, 0, 0, (whad_ble_direction_t)direction, processed, decrypted, false);
}


/**
 * @brief       Connection notification constructor. 
 * 
 * @param[in]   connHandle  Connection handle assigned to this connection
 * @param[in]   advAddr     Advertiser BD address
 * @param[in]   initAddr    Initiator BD address
 **/

Connected::Connected(uint32_t connHandle, BDAddress advAddr, BDAddress initAddr)  : NanoPbMsg()
{
    whad_ble_notify_connected(
        this->getRaw(),
        
        /* Specify advertiser BD address */
        (whad_ble_addrtype_t)advAddr.getType(), advAddr.getAddressBuf(),

        /* Specify initiator BD address */
        (whad_ble_addrtype_t)initAddr.getType(), initAddr.getAddressBuf(),

        /* Connection handle */
        connHandle
    );
}


/**
 * @brief       Disconnection notification constructor. 
 * 
 * @param[in]   connHandle  Connection handle assigned to this connection
 * @param[in]   reason      Disconnection reason (see BLE specs.)
 **/

Disconnected::Disconnected(uint32_t connHandle, uint32_t reason) : NanoPbMsg()
{
    whad_ble_notify_disconnected(this->getRaw(), connHandle, reason);
}


/**
 * @brief       Set adapter BD address message constructor.
 * 
 * @param[in]   address     BD address to use
 **/

SetBdAddress::SetBdAddress(BDAddress address) : NanoPbMsg()
{
    whad_ble_set_bdaddress(
        this->getRaw(),
        (whad_ble_addrtype_t)address.getType(),
        address.getAddressBuf()
    );
}


/**
 * @brief       SniffAdv message constructor.
 * 
 * @param[in]   channel     Channel to use for sniffing
 * @param[in]   targetAddr  Target device BD address
 * @param[in]   useExtAdv   If set to true, use extended advertising (BLE 5.x)
 **/

SniffAdv::SniffAdv(uint32_t channel, BDAddress targetAddr, bool useExtAdv) : NanoPbMsg()
{
    whad_ble_sniff_adv(
        this->getRaw(),
        useExtAdv,
        channel,
        targetAddr.getAddressBuf()
    );
}


/**
 * @brief       JamAdv message constructor.
 * 
 **/

JamAdv::JamAdv(void) : NanoPbMsg()
{
    whad_ble_jam_adv(this->getRaw());
}

/**
 * @brief       JamAdv message constructor.
 * 
 * @param[in]   channel     Channel to jam.
 **/

JamAdv::JamAdv(uint32_t channel) : NanoPbMsg()
{
    whad_ble_jam_adv_channel(this->getRaw(), channel);
}


/**
 * @brief       SnifConnReq message constructor.
 * 
 * @param[in]   channel     Channel to sniff for connection request
 * @param[in]   targetAddr  Target device BD address
 * @param[in]   showAdv     If set to true, adapter will report every advertisement received
 * @param[in]   showEmpty   If set to true, adapter will report empty PDUs
 **/

SniffConnReq::SniffConnReq(uint32_t channel, BDAddress targetAddr, bool showAdv, bool showEmpty) : NanoPbMsg()
{
    whad_ble_sniff_conn_req(
        this->getRaw(),
        showEmpty,
        showAdv,
        channel,
        targetAddr.getAddressBuf()
    );
}


/**
 * @brief       SnifAccessAddress message constructor.
 * 
 * @param[in]   channelMap  Channel map specifying the channels to use for access adress
 *                          sniffing
 **/

SniffAccessAddress::SniffAccessAddress(ChannelMap channelMap) : NanoPbMsg()
{
    whad_ble_sniff_access_address(this->getRaw(), channelMap.getChannelMapBuf());
}


/**
 * @brief       SniffActiveConn message constructor.
 * 
 * @param[in]   accessAddress   Connection access address
 * @param[in]   crcInit         Connection CRC init value (seed)
 * @param[in]   hopInterval     Hop interval
 * @param[in]   hopIncrement    Hop increment
 * @param[in]   channelMap      Connection channel map
 * @param[in]   channels        Channel map specifying the channels to use when recovering the
 *                              channel map (if multiple sniffers are used -- collaborative
 *                              channel map recovery).
 **/

SniffActiveConn::SniffActiveConn(uint32_t accessAddress, uint32_t crcInit, uint32_t hopInterval, uint32_t hopIncrement, ChannelMap channelMap, ChannelMap channels) : NanoPbMsg()
{
    whad_ble_sniff_active_conn(
        this->getRaw(),
        accessAddress,
        crcInit,
        hopInterval,
        hopIncrement,
        channelMap.getChannelMapBuf(),
        channels.getChannelMapBuf()
    );
}


/**
 * @brief       JamActiveConn message constructor.
 * 
 * @param[in]   accessAddress   Connection access address
 **/

JamActiveConn::JamActiveConn(uint32_t accessAddress) : NanoPbMsg()
{
    whad_ble_jam_active_conn(this->getRaw(), accessAddress);
}


/**
 * @brief       ScanMode message constructor.
 * 
 * @param[in]   active      If set to true, adapter will perform an active scan
 **/

ScanMode::ScanMode(bool active) : NanoPbMsg()
{
    whad_ble_scan_mode(this->getRaw(), active);
}


/**
 * @brief       AdvMode message constructor.
 * 
 * @param[in]   pAdvData        Pointer to a byte buffer containing the device advertising data
 * @param[in]   advDataLength   Size in bytes of the advertising data
 * @param[in]   pScanRsp        Pointer to a byte buffer containing the device scan response data
 * @param[in]   scanRspLength   Size in bytes of the scan response data
 **/

AdvMode::AdvMode(uint8_t *pAdvData, int advDataLength, uint8_t *pScanRsp, int scanRspLength) : NanoPbMsg()
{
    whad_ble_adv_mode(
        this->getRaw(),
        pAdvData,
        advDataLength,
        pScanRsp,
        scanRspLength
    );
}


/**
 * @brief       SetAdvData message constructor.
 * 
 * @param[in]   pAdvData        Pointer to a byte buffer containing the device advertising data
 * @param[in]   advDataLength   Size in bytes of the advertising data
 * @param[in]   pScanRsp        Pointer to a byte buffer containing the device scan response data
 * @param[in]   scanRspLength   Size in bytes of the scan response data
 **/

SetAdvData::SetAdvData(uint8_t *pAdvData, int advDataLength, uint8_t *pScanRsp, int scanRspLength) : NanoPbMsg()
{
    whad_ble_set_adv_data(
        this->getRaw(),
        pAdvData,
        advDataLength,
        pScanRsp,
        scanRspLength
    );
}



/**
 * @brief       CentralMode message constructor.
 **/

CentralMode::CentralMode(void) : NanoPbMsg()
{
    whad_ble_central_mode(this->getRaw());
}


/**
 * @brief       ConnectTo message constructor.
 * 
 * @param[in]   targetAddr      Target device BD address
 * @param[in]   accessAddress   Specify the access address to use for this connection, if supported
 *                              by the adapter
 * @param[in]   channelMap      Specify the channel map to use for this connection, if supported by
 *                              the adapter
 * @param[in]   hopInterval     Connection hop interval
 * @param[in]   hopIncrement    Connection hop increment
 * @param[in]   crcInit         CRC initial value (seed)
 **/

ConnectTo::ConnectTo(BDAddress targetAddr, uint32_t accessAddress, ChannelMap channelMap,
                              uint32_t hopInterval, uint32_t hopIncrement, uint32_t crcInit) : NanoPbMsg()
{
    whad_ble_connect_to(
        this->getRaw(),
        targetAddr.getAddressBuf(),
        (whad_ble_addrtype_t)targetAddr.getType(),
        accessAddress,
        channelMap.getChannelMapBuf(),
        hopInterval,
        hopIncrement,
        crcInit
    );
}


/**
 * @brief       SendRawPdu message constructor.
 * 
 * @param[in]   direction       PDU direction
 * @param[in]   connHandle      Connection handle in which the PDU is to be sent
 * @param[in]   accessAddress   Connection access address
 * @param[in]   pPdu            Pointer to a byte buffer containing the PDU
 * @param[in]   length          PDU size in bytes (cannot exceed 250 bytes)
 * @param[in]   crc             PDU CRC value
 * @param[in]   encrypt         If set to true and encryption enabled, adapter will encrypt the PDU
 **/

SendRawPdu::SendRawPdu(Direction direction, uint32_t connHandle, uint32_t accessAddress, uint8_t *pPdu,
                       int length, uint32_t crc, bool encrypt) : NanoPbMsg()
{
    whad_ble_send_raw_pdu(
        this->getRaw(),
        (whad_ble_direction_t)direction,
        connHandle,
        accessAddress,
        pPdu,
        length,
        crc,
        encrypt
    );
}


/**
 * @brief       SendPdu message constructor.
 * 
 * @param[in]   direction       PDU direction
 * @param[in]   connHandle      Connection handle in which the PDU is to be sent
 * @param[in]   pPdu            Pointer to a byte buffer containing the PDU
 * @param[in]   length          PDU size in bytes (cannot exceed 250 bytes)
 * @param[in]   encrypt         If set to true and encryption enabled, adapter will encrypt the PDU
 **/

SendPdu::SendPdu(Direction direction, uint32_t connHandle, uint8_t *pPdu, int length, bool encrypt) : NanoPbMsg()
{
    whad_ble_send_pdu(
        this->getRaw(),
        (whad_ble_direction_t)direction,
        connHandle,
        pPdu,
        length,
        encrypt
    );
}


/**
 * @brief       Disconnect message constructor.
 * 
 * @param[in]   connHandle      Connection handle
 **/

Disconnect::Disconnect(uint32_t connHandle) : NanoPbMsg()
{
    whad_ble_disconnect(this->getRaw(), connHandle);
}


/**
 * @brief       PeripheralMode message constructor.
 * 
 * @param[in]   pAdvData        Pointer to a byte buffer containing the device advertising data
 * @param[in]   advDataLength   Size in bytes of the advertising data
 * @param[in]   pScanRsp        Pointer to a byte buffer containing the device scan response data
 * @param[in]   scanRspLength   Size in bytes of the scan response data
 **/

PeripheralMode::PeripheralMode(uint8_t *pAdvData, int advDataLength, uint8_t *pScanRsp, int scanRspLength) : NanoPbMsg()
{
    whad_ble_peripheral_mode(
        this->getRaw(),
        pAdvData,
        advDataLength,
        pScanRsp,
        scanRspLength
    );
}


/**
 * @brief       Start message constructor.
 **/

Start::Start(void) : NanoPbMsg()
{
    whad_ble_start(this->getRaw());
}


/**
 * @brief       Stop message constructor.
 **/

Stop::Stop(void) : NanoPbMsg()
{
    whad_ble_stop(this->getRaw());
}


/**
 * @brief       HijackMaster message constructor.
 * 
 * @param[in]   accessAddress   Target connection access address
 **/

HijackMaster::HijackMaster(uint32_t accessAddress) : NanoPbMsg()
{
    whad_ble_hijack_master(this->getRaw(), accessAddress);
}


/**
 * @brief       HijackSlave message constructor.
 * 
 * @param[in]   accessAddress   Target connection access address
 **/

HijackSlave::HijackSlave(uint32_t accessAddress) : NanoPbMsg()
{
    whad_ble_hijack_slave(this->getRaw(), accessAddress);
}


/**
 * @brief       HijackBoth message constructor.
 * 
 * @param[in]   accessAddress   Target connection access address
 **/

HijackBoth::HijackBoth(uint32_t accessAddress) : NanoPbMsg()
{
    whad_ble_hijack_both(this->getRaw(), accessAddress);
}


/**
 * @brief       SetEncryption message constructor.
 * 
 * @param[in]   connHandle      Connection handle
 * @param[in]   llKey           Link-layer encryption key (16 bytes)
 * @param[in]   llIv            Link-layer encryption initialization vector (8 bytes)
 * @param[in]   key             Encryption key
 * @param[in]   rand            Random buffer used in link-layer key derivation
 * @param[in]   eDiv            Diversifier used in link-layer key derivation
 **/

SetEncryption::SetEncryption(uint32_t connHandle, uint8_t llKey[16],
                                  uint8_t llIv[8], uint8_t key[16], uint8_t rand[8],
                                  uint8_t eDiv[2], bool enabled) : NanoPbMsg()
{
    whad_ble_set_encryption(
        this->getRaw(),
        connHandle,
        enabled,
        llKey,
        llIv,
        key,
        rand,
        eDiv
    );
}


/**
 * @brief       SetEncryption message constructor.
 * 
 * @param[in]   channel         Channel to listen on
 * @param[in]   pPattern        Byte buffer containing the byte pattern to match
 * @param[in]   length          Pattern length in bytes
 * @param[in]   position        Start position for pattern search
 **/

ReactiveJam::ReactiveJam(uint32_t channel, uint8_t *pPattern, int length, uint32_t position) : NanoPbMsg()
{
    whad_ble_reactive_jam(this->getRaw(), channel, pPattern, length, position);
}


/**
 * @brief       PatternTrigger constructor
 * 
 * @param[in]   pPattern        Byte buffer containing the byte pattern to match
 * @param[in]   pMask           Byte buffer containing a bitmask to apply with the pattern
 * @param[in]   length          Pattern and mask size in bytes
 * @param[in]   offset          Offset at which the pattern must be applied
 **/

PatternTrigger::PatternTrigger(uint8_t *pPattern, uint8_t *pMask, int length, uint32_t offset)
{
    this->m_pattern = pPattern;
    this->m_mask = pMask;
    this->m_length = length;
    this->m_offset = offset;
}


/**
 * @brief       Get pattern and mask length
 * 
 * @return      Pattern and mask length in bytes
 **/

int PatternTrigger::getLength(void)
{
    return this->m_length;
}


/**
 * @brief       Get trigger pattern
 * 
 * @return      Pointer to the trigger's pattern byte buffer
 **/

uint8_t *PatternTrigger::getPattern(void)
{
    return this->m_pattern;
}


/**
 * @brief       Get trigger mask
 * 
 * @return      Pointer to the trigger's mask byte buffer
 **/

uint8_t *PatternTrigger::getMask(void)
{
    return this->m_mask;
}


/**
 * @brief       Get trigger pattern offset
 * 
 * @return      Pattern offset
 **/

uint32_t PatternTrigger::getOffset(void)
{
    return this->m_offset;
}


/**
 * @brief       Connection Event trigger constructor
 * 
 * @param[in]   connEvent       Connection event at which a set of packets must be sent
 **/

ConnEventTrigger::ConnEventTrigger(uint32_t connEvent)
{
    this->m_connEvent = connEvent;
}


/**
 * @brief       Get trigger connection event
 * 
 * @return      Connection event
 **/

uint32_t ConnEventTrigger::getConnEvent(void)
{
    return this->m_connEvent;
}


/**
 * @brief       Build an empty PDU with a specific length
 * 
 * @param[in]   length          PDU length
 **/

PDU::PDU(int length)
{
    /* Allocate a new buffer. */
    this->m_length = length;
    this->m_buf = new uint8_t[length];
}


/**
 * @brief       Build a PDU with a specific length and fill with the provided bytes
 *
 * @param[in]   bytes           PDU bytes (byte array)
 * @param[in]   length          PDU length
 **/

PDU::PDU(uint8_t *bytes, int length) : PDU(length)
{
    /* Allocate a new buffer. */
    //this->m_length = length;
    //this->m_buf = new uint8_t[length];
    memcpy(this->m_buf, bytes, length);
}


/**
 * @brief       PDU destructor
 *
 * Free the allocated byte buffer.
 **/

PDU::~PDU()
{
    /* Free our byte buffer. */
    delete[] this->m_buf;
}


/**
 * @brief       Get a poiner to the PDU byte buffer
 *
 * @return      Pointer to the PDU byte buffer
 **/

uint8_t *PDU::getBuf(void)
{
    return this->m_buf;
}


/**
 * @brief       Get PDU current length
 * 
 * @return      PDU byte buffer length
 **/

int PDU::getLength(void)
{
    return this->m_length;
}


/**
 * @brief       Convert a vecor of PDU into a WHAD prepared packets array
 * 
 * @param[in]   packets     Vector of packets to convert into a WHAD prepared packets array
 * 
 * @return      Dynamically allocated packets array
 **/

whad_prepared_packet_t *buildPacketsArray(std::vector<PDU> packets)
{
    whad_prepared_packet_t *packetsArr;
    int packetCount = packets.size();

    if (packetCount > 0)
    {
        /* We need to create an array of packets. */
        packetsArr = new whad_prepared_packet_t[packetCount];

        /* Then we populate this array with our packets. */
        for (int i=0; i<packetCount; i++)
        {
            memcpy(packetsArr[i].p_bytes, packets[i].getBuf(), packets[i].getLength());
            packetsArr[i].length = packets[i].getLength();
        }

        /* Success. */
        return packetsArr;
    }
    else
    {
        /* Nothing to allocate. */
        return NULL;
    }
}


/**
 * @brief       Create a manually triggered prepared sequence
 * 
 * @param[in]   id          Sequence ID
 * @param[in]   direction   Sequence direction
 * @param[in]   packets     Vector of PDU to send (packets list)
 **/

PrepareSequence::PrepareSequence(uint32_t id, Direction direction, std::vector<PDU> packets) : NanoPbMsg()
{
    /* Convert our vector into a dynamically allocated array. */
    whad_prepared_packet_t *packetsArr = buildPacketsArray(packets);

    /* And we initialize our message. */
    whad_ble_prepare_sequence_manual(
        this->getRaw(),
        id,
        (whad_ble_direction_t)direction,
        packetsArr,
        packets.size()
    );

    /* Free our packets array. */
    delete[] packetsArr;
}


/**
 * @brief       Create a pattern-triggered prepared sequence
 * 
 * @param[in]   id          Sequence ID
 * @param[in]   direction   Sequence direction
 * @param[in]   packets     Vector of PDU to send (packets list)
 * @param[in]   trigger     Pattern trigger to apply with this sequence
 **/

PrepareSequence::PrepareSequence(uint32_t id, Direction direction, std::vector<PDU> packets, PatternTrigger trigger) : NanoPbMsg()
{
    /* Convert our vector into a dynamically allocated array. */
    whad_prepared_packet_t *packetsArr = buildPacketsArray(packets);

    whad_ble_prepare_sequence_on_recv(
        this->getRaw(),
        trigger.getPattern(),
        trigger.getMask(),
        trigger.getLength(),
        trigger.getOffset(),
        id,
        (whad_ble_direction_t)direction,
        packetsArr,
        packets.size()
    );

    /* Free our packets array. */
    delete[] packetsArr;
}


/**
 * @brief       Create a connection event triggered prepared sequence
 * 
 * @param[in]   id          Sequence ID
 * @param[in]   direction   Sequence direction
 * @param[in]   packets     Vector of PDU to send (packets list)
 * @param[in]   trigger     Connection event trigger to apply with this sequence
 **/

PrepareSequence::PrepareSequence(uint32_t id, Direction direction, std::vector<PDU> packets,
                                    ConnEventTrigger trigger) : NanoPbMsg()
{
    /* Convert our vector into a dynamically allocated array. */
    whad_prepared_packet_t *packetsArr = buildPacketsArray(packets);

    whad_ble_prepare_sequence_conn_evt(
        this->getRaw(),
        trigger.getConnEvent(),
        id,
        (whad_ble_direction_t)direction,
        packetsArr,
        packets.size()
    );

    /* Free our packets array. */
    delete[] packetsArr;
}


/**
 * @brief       Manually triggers a packet sequence
 * 
 * @param[in]   id          Sequence ID
 **/

ManualTrigger::ManualTrigger(uint32_t id) : NanoPbMsg()
{
    whad_ble_prepare_sequence_trigger(
        this->getRaw(),
        id
    );
}


/**
 * @brief       Delete a prepared sequence
 * 
 * @param[in]   id          Sequence ID
 **/

DeleteSequence::DeleteSequence(uint32_t id) : NanoPbMsg()
{
    whad_ble_prepare_sequence_delete(
        this->getRaw(),
        id
    );
}


/**
 * @brief       Prepared sequence has been triggered
 * 
 * @param[in]   id          Sequence ID
 **/

SequenceTriggered::SequenceTriggered(uint32_t id) : NanoPbMsg()
{
    whad_ble_triggered(
        this->getRaw(),
        id
    );
}


/**
 * @brief       Notify the discovery of an access address
 * 
 * @param[in]   accessAddress       Discovered access address
 **/

AccessAddressDiscovered::AccessAddressDiscovered(uint32_t accessAddress) : NanoPbMsg()
{
    whad_ble_access_address_discovered(
        this->getRaw(),
        accessAddress,
        0,
        0,
        false,
        false
    );
}


/**
 * @brief       Notify the discovery of an access address including RSSI
 * 
 * @param[in]   accessAddress       Discovered access address
 * @param[in]   rssi                Received Signal Strength Indicator
 **/

AccessAddressDiscovered::AccessAddressDiscovered(uint32_t accessAddress, int32_t rssi) : NanoPbMsg()
{
    whad_ble_access_address_discovered(
        this->getRaw(),
        accessAddress,
        0,
        rssi,
        false,
        true
    );
}


/**
 * @brief       Notify the discovery of an access address including timestamp
 * 
 * @param[in]   accessAddress       Discovered access address
 * @param[in]   timestamp           Timestamp
 **/

AccessAddressDiscovered::AccessAddressDiscovered(uint32_t accessAddress, uint32_t timestamp) : NanoPbMsg()
{
    whad_ble_access_address_discovered(
        this->getRaw(),
        accessAddress,
        timestamp,
        0,
        true,
        false
    );
}


/**
 * @brief       Notify the discovery of an access address including timestamp and RSSI
 * 
 * @param[in]   accessAddress       Discovered access address
 * @param[in]   timestamp           Timestamp
 * @param[in]   rssi                Received Signal Strength Indicator
 **/

AccessAddressDiscovered::AccessAddressDiscovered(uint32_t accessAddress, uint32_t timestamp, int32_t rssi) : NanoPbMsg()
{
    whad_ble_access_address_discovered(
        this->getRaw(),
        accessAddress,
        timestamp,
        rssi,
        true,
        true
    );
}


/**
 * @brief       Notify an advertising PDU
 * 
 * @param[in]   advType             Advertisement type
 * @param[in]   address             Advertiser BD address
 * @param[in]   pAdvData            Pointer to the advertising data byte buffer
 * @param[in]   advDataLength       Advertising data length in bytes
 **/

AdvPdu::AdvPdu(AdvType advType, int32_t rssi, BDAddress address, uint8_t *pAdvData, int advDataLength) : NanoPbMsg()
{
    whad_ble_adv_pdu(
        this->getRaw(),
        (whad_ble_advtype_t)advType,
        rssi,
        address.getAddressBuf(),
        (whad_ble_addrtype_t)address.getType(),
        pAdvData,
        advDataLength
    );
}


/**
 * @brief       Notify a successful connection synchronization
 * 
 * @param[in]   accessAddress       Connection access address
 * @param[in]   crcInit             Recovered CRC initial value (seed)
 * @param[in]   hopInterval         Recovered hop interval
 * @param[in]   hopIncrement        Recovered hop increment
 * @param[in]   channelMap          Recovered channel map
 **/

Synchronized::Synchronized(uint32_t accessAddress, uint32_t crcInit, uint32_t hopInterval,
                                 uint32_t hopIncrement, ChannelMap channelMap) : NanoPbMsg()
{
    whad_ble_synchronized(
        this->getRaw(),
        accessAddress,
        crcInit,
        hopInterval,
        hopIncrement,
        channelMap.getChannelMapBuf()
    );
}


/**
 * @brief       Notify a connection desynchronization
 * 
 * @param[in]   accessAddress       Connection access address
 **/

Desynchronized::Desynchronized(uint32_t accessAddress) : NanoPbMsg()
{
    whad_ble_desynchronized(
        this->getRaw(),
        accessAddress
    );
}


/**
 * @brief       Notify a successful/unsuccessful connection hijacking
 * 
 * @param[in]   accessAddress       Connection access address
 * @param[in]   success             If true hijacking was successful, unsuccessful otherwise 
 **/

Hijacked::Hijacked(uint32_t accessAddress, bool success) : NanoPbMsg()
{
    whad_ble_hijacked(
        this->getRaw(),
        accessAddress,
        success
    );
}


/**
 * @brief       Notify a successful/unsuccessful PDU injection
 * 
 * @param[in]   accessAddress       Connection access address
 * @param[in]   attempts            Number of attempts
 * @param[in]   success             If true injection was successful, unsuccessful otherwise 
 **/

Injected::Injected(uint32_t accessAddress, uint32_t attempts, bool success) : NanoPbMsg()
{
    whad_ble_injected(
        this->getRaw(),
        accessAddress,
        attempts,
        success
    );
}