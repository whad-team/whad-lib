#include "cpp/ble.hpp"

using namespace whad::ble;

/********************************
 * BLE basic information elements
 *******************************/

/**
 * @brief   BD Address default constructor.
 **/

BDAddress::BDAddress(void)
{
    this->m_type = whad::ble::AddressType::AddressPublic;
    memset(this->m_address, 0, 6);
}


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


/**
 * @brief   Set address type.
 * 
 * @param[in]   type    Address type to set
 **/

void BDAddress::setType(AddressType type)
{
    this->m_type = type;
}


/**
 * @brief   Get address buffer.
 * 
 * @return  Pointer to the BD address byte buffer (6 bytes)
 **/

uint8_t *BDAddress::getAddressBuf(void)
{
    return this->m_address;
}


/**
 * @brief   Set BD address.
 * 
 * @param[in]   pBdAddress    Pointer to a 6-byte BD address buffer
 **/

void BDAddress::setAddress(uint8_t *pBdAddress)
{
    /* Copy BD address. */
    memcpy(this->m_address, pBdAddress, 6);
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


/********************************
 * BLE message base class
 *******************************/

/**
 * @brief   BLE message base class.
 **/

whad::ble::BleMsg::BleMsg() : NanoPbMsg()
{
}


/**
 * @brief       BLE message base class.
 * 
 * @param[in]   pMessage    NanoPbMsg object containing a discovery domain message 
 **/

whad::ble::BleMsg::BleMsg(NanoPbMsg pMessage) : NanoPbMsg(pMessage.getRaw())
{
}


/**
 * @brief   BLE message base class destructor.
 **/

whad::ble::BleMsg::~BleMsg()
{
}


/**
 * @brief       Identify the underlying discovery message.
 *
 * This method can be used when parsing incoming Discovery domain message to identify
 * the type of message it contains and process it later.
 * 
 * @return      Discovery message type.
 **/

whad::ble::MessageType whad::ble::BleMsg::getType(void)
{
    whad::ble::MessageType msgType = (whad::ble::MessageType)whad_ble_get_message_type(
        this->getRaw()
    );

    /* Return message type. */
    return msgType;
}


/********************************
 * BLE messages classes
 *******************************/


/**
 * @brief   Create a LinkLayerPdu object from a BLE PDU.
 * 
 * @param[in]   pdu         Pointer to a byte array containing the PDU
 * @param[in]   length      Size in bytes of the PDU
 * @param[in]   direction   Direction of the PDU (host to slave, slave to host, ...)
 **/

LinkLayerPdu::LinkLayerPdu(uint32_t conn_handle, PDU pdu, Direction direction, bool processed, bool decrypted) : BleMsg()
{
    /* Initialize our data pdu message. */
    whad_ble_pdu(this->getRaw(), pdu.getBytes(), pdu.getSize(), (whad_ble_direction_t)direction, conn_handle, processed, decrypted);
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
                          bool decrypted) : BleMsg()
{
    whad_ble_raw_pdu(this->getRaw(), channel, rssi, conn_handle, access_address, pdu.getBytes(), pdu.getSize(), crc, 
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
                           bool processed, bool decrypted) : BleMsg()
{
    whad_ble_raw_pdu(this->getRaw(), channel, rssi, conn_handle, access_address, pdu.getBytes(), pdu.getSize(),
                     crc, crc_validity, 0, 0, (whad_ble_direction_t)direction, processed, decrypted, false);
}


/**
 * @brief       Connection notification constructor. 
 * 
 * @param[in]   connHandle  Connection handle assigned to this connection
 * @param[in]   advAddr     Advertiser BD address
 * @param[in]   initAddr    Initiator BD address
 **/

Connected::Connected(uint32_t connHandle, BDAddress advAddr, BDAddress initAddr)  : BleMsg()
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

Disconnected::Disconnected(uint32_t connHandle, uint32_t reason) : BleMsg()
{
    whad_ble_notify_disconnected(this->getRaw(), connHandle, reason);
}


/**
 * @brief       Set adapter BD address message constructor.
 * 
 * @param[in]   address     BD address to use
 **/

SetBdAddress::SetBdAddress(BDAddress address) : BleMsg()
{
    whad_ble_set_bdaddress(
        this->getRaw(),
        (whad_ble_addrtype_t)address.getType(),
        address.getAddressBuf()
    );
}


/**
 * @brief       parse a BD address message constructor.
 * 
 * @param[in]   message     Base NanoPb message to use.
 **/

SetBdAddress::SetBdAddress(NanoPbMsg message) : BleMsg(message)
{
}


/**
 * @brief   Retrieve the BD address.
 * 
 * @return  An instance of BDAddress on success, NULL otherwise.
 **/

BDAddress *SetBdAddress::getAddress()
{
    whad_ble_addrtype_t addrType;
    uint8_t bdAddress[6];

    /* Parse the underlying message to extract BD address. */
    if (whad_ble_set_bdaddress_parse(this->getRaw(), &addrType, bdAddress) == WHAD_SUCCESS)
    {
        /* Parsing ok, return BD address. */
        return new BDAddress((whad::ble::AddressType)addrType, (uint8_t *)bdAddress);
    }

    /* Fail. */
    return NULL;
}

/**
 * @brief       SniffAdv message constructor.
 * 
 * @param[in]   channel     Channel to use for sniffing
 * @param[in]   targetAddr  Target device BD address
 * @param[in]   useExtAdv   If set to true, use extended advertising (BLE 5.x)
 **/

SniffAdv::SniffAdv(uint32_t channel, BDAddress targetAddr, bool useExtAdv) : BleMsg()
{
    whad_ble_sniff_adv(
        this->getRaw(),
        useExtAdv,
        channel,
        targetAddr.getAddressBuf()
    );
}


/**
 * @brief       SniffAdv message constructor.
 * 
 * @param[in]   channel     Channel to use for sniffing
 * @param[in]   targetAddr  Target device BD address
 * @param[in]   useExtAdv   If set to true, use extended advertising (BLE 5.x)
 **/

SniffAdv::SniffAdv(NanoPbMsg message) : BleMsg(message)
{
    whad_ble_sniff_adv_params_t params;
    this->m_channel = 0;
    this->m_useExtAdv = false;

    if (whad_ble_sniff_adv_parse(this->getRaw(), &params) == WHAD_SUCCESS)
    {
        this->m_channel = params.channel;
        this->m_useExtAdv = params.use_ext_adv;
        this->m_targetAddr.setAddress(params.p_bdaddr);
    }
}


/**
 * @brief   Get advertising channel.
 * 
 * @return  Advertising channel number. 
 **/

uint32_t SniffAdv::getChannel(void)
{
    return this->m_channel;
}


/**
 * @brief   Determine if we must use extended advertisements.
 * 
 * @return  True if extended advertisements must be used, false otherwise. 
 **/

bool SniffAdv::mustUseExtAdv(void)
{
    return this->m_useExtAdv;
}


/**
 * @brief   Get the target BD address.
 * 
 * @return  BD address of the target device to sniff.
 **/

BDAddress SniffAdv::getAddress(void)
{
    return this->m_targetAddr;
}


/**
 * @brief       JamAdv message constructor.
 * 
 **/

JamAdv::JamAdv(void) : BleMsg()
{
    whad_ble_jam_adv(this->getRaw());
}


/**
 * @brief       JamAdv message constructor.
 * 
 * @param[in]   channel     Channel to jam.
 **/

JamAdv::JamAdv(uint32_t channel) : BleMsg()
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

SniffConnReq::SniffConnReq(uint32_t channel, BDAddress targetAddr, bool showAdv, bool showEmpty) : BleMsg()
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

SniffAccessAddress::SniffAccessAddress(ChannelMap channelMap) : BleMsg()
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

SniffActiveConn::SniffActiveConn(uint32_t accessAddress, uint32_t crcInit, uint32_t hopInterval, uint32_t hopIncrement, ChannelMap channelMap, ChannelMap channels) : BleMsg()
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

JamActiveConn::JamActiveConn(uint32_t accessAddress) : BleMsg()
{
    whad_ble_jam_active_conn(this->getRaw(), accessAddress);
}


/**
 * @brief       ScanMode message constructor.
 * 
 * @param[in]   active      If set to true, adapter will perform an active scan
 **/

ScanMode::ScanMode(bool active) : BleMsg()
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

AdvMode::AdvMode(uint8_t *pAdvData, int advDataLength, uint8_t *pScanRsp, int scanRspLength) : BleMsg()
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

SetAdvData::SetAdvData(uint8_t *pAdvData, int advDataLength, uint8_t *pScanRsp, int scanRspLength) : BleMsg()
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

CentralMode::CentralMode(void) : BleMsg()
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
                              uint32_t hopInterval, uint32_t hopIncrement, uint32_t crcInit) : BleMsg()
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
                       int length, uint32_t crc, bool encrypt) : BleMsg()
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

SendPdu::SendPdu(Direction direction, uint32_t connHandle, uint8_t *pPdu, int length, bool encrypt) : BleMsg()
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

Disconnect::Disconnect(uint32_t connHandle) : BleMsg()
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

PeripheralMode::PeripheralMode(uint8_t *pAdvData, int advDataLength, uint8_t *pScanRsp, int scanRspLength) : BleMsg()
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

Start::Start(void) : BleMsg()
{
    whad_ble_start(this->getRaw());
}


/**
 * @brief       Stop message constructor.
 **/

Stop::Stop(void) : BleMsg()
{
    whad_ble_stop(this->getRaw());
}


/**
 * @brief       HijackMaster message constructor.
 * 
 * @param[in]   accessAddress   Target connection access address
 **/

HijackMaster::HijackMaster(uint32_t accessAddress) : BleMsg()
{
    whad_ble_hijack_master(this->getRaw(), accessAddress);
}


/**
 * @brief       HijackSlave message constructor.
 * 
 * @param[in]   accessAddress   Target connection access address
 **/

HijackSlave::HijackSlave(uint32_t accessAddress) : BleMsg()
{
    whad_ble_hijack_slave(this->getRaw(), accessAddress);
}


/**
 * @brief       HijackBoth message constructor.
 * 
 * @param[in]   accessAddress   Target connection access address
 **/

HijackBoth::HijackBoth(uint32_t accessAddress) : BleMsg()
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
                                  uint8_t eDiv[2], bool enabled) : BleMsg()
{
    /* Save properties. */
    this->m_connHandle = connHandle;
    this->m_enabled = enabled;
    memcpy(this->m_LLKey, llKey, 16);
    memcpy(this->m_llIv, llIv, 8);
    memcpy(this->m_key, key, 16);
    memcpy(this->m_rand, rand, 8);
    memcpy(this->m_eDiv, eDiv, 2);

    /* Fill the NanoPb message with the correct values. */
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
 * @param[in]   message         NanoPb message to use
 **/

SetEncryption::SetEncryption(NanoPbMsg message) : BleMsg(message)
{
    whad_ble_encryption_params_t params;

    /* Set our properties to default values. */
    this->m_connHandle = 0;
    this->m_enabled = false;
    memset(this->m_LLKey, 0, 16);
    memset(this->m_llIv, 0, 8);
    memset(this->m_key, 0, 16);
    memset(this->m_rand, 0, 8);
    memset(this->m_eDiv, 0, 2);

    /* Parse SetEncryption message. */
    if (whad_ble_set_encryption_parse(this->getRaw(), &params) == WHAD_SUCCESS)
    {
        this->m_connHandle = params.conn_handle;
        this->m_enabled = params.enabled;
        memcpy(this->m_LLKey, params.p_ll_key, 16);
        memcpy(this->m_llIv, params.p_ll_iv, 8);
        memcpy(this->m_key, params.p_key, 16);
        memcpy(this->m_rand, params.p_rand, 8);
        memcpy(this->m_eDiv, params.p_ediv, 2);
    }

    /* TODO: trigger an exception if parsing fails. */
}


/**
 * @brief   Get connection handle
 * 
 * @return  Connection handle value.
 **/

uint32_t SetEncryption::getConnHandle()
{
    return this->m_connHandle;
}


/**
 * @brief   Determine if encryption must be enabled or not.
 * 
 * @return  True if encryption must be enabled, false otherwise.
 **/

bool SetEncryption::isEnabled()
{
    return this->m_enabled;
}


/**
 * @brief   Get the key 16-byte buffer
 * 
 * @return  Pointer to the key buffer.
 **/

uint8_t *SetEncryption::getKey()
{
    return this->m_key;
}


/**
 * @brief   Get the key 8-byte Rand buffer
 * 
 * @return  Pointer to the Rand buffer.
 **/

uint8_t *SetEncryption::getRand()
{
    return this->m_rand;
}


/**
 * @brief   Get the link-layer 16-byte encryption key buffer
 * 
 * @return  Pointer to the link-layer encryption key buffer.
 **/

uint8_t *SetEncryption::getLLKey()
{
    return this->m_LLKey;
}


/**
 * @brief   Get the link-layer 8-byte IV buffer
 * 
 * @return  Pointer to the link-layer encryption IV buffer.
 **/

uint8_t *SetEncryption::getLLIv()
{
    return this->m_llIv;
}


/**
 * @brief   Get the encryption diversifier.
 * 
 * @return  Pointer to the encryption diversifier buffer.
 **/

uint8_t *SetEncryption::getEDiv()
{
    return this->m_eDiv;
}


/**
 * @brief       ReactiveJam message constructor.
 * 
 * @param[in]   channel         Channel to listen on
 * @param[in]   pPattern        Byte buffer containing the byte pattern to match
 * @param[in]   length          Pattern length in bytes
 * @param[in]   position        Start position for pattern search
 **/

ReactiveJam::ReactiveJam(uint32_t channel, uint8_t *pPattern, int length, uint32_t position) : BleMsg()
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
            memcpy(packetsArr[i].p_bytes, packets[i].getBytes(), packets[i].getSize());
            packetsArr[i].length = packets[i].getSize();
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

PrepareSequence::PrepareSequence(uint32_t id, Direction direction, std::vector<PDU> packets) : BleMsg()
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

PrepareSequence::PrepareSequence(uint32_t id, Direction direction, std::vector<PDU> packets, PatternTrigger trigger) : BleMsg()
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
                                    ConnEventTrigger trigger) : BleMsg()
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

ManualTrigger::ManualTrigger(uint32_t id) : BleMsg()
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

DeleteSequence::DeleteSequence(uint32_t id) : BleMsg()
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

SequenceTriggered::SequenceTriggered(uint32_t id) : BleMsg()
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

AccessAddressDiscovered::AccessAddressDiscovered(uint32_t accessAddress) : BleMsg()
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

AccessAddressDiscovered::AccessAddressDiscovered(uint32_t accessAddress, int32_t rssi) : BleMsg()
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

AccessAddressDiscovered::AccessAddressDiscovered(uint32_t accessAddress, uint32_t timestamp) : BleMsg()
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

AccessAddressDiscovered::AccessAddressDiscovered(uint32_t accessAddress, uint32_t timestamp, int32_t rssi) : BleMsg()
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

AdvPdu::AdvPdu(AdvType advType, int32_t rssi, BDAddress address, uint8_t *pAdvData, int advDataLength) : BleMsg()
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
                                 uint32_t hopIncrement, ChannelMap channelMap) : BleMsg()
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

Desynchronized::Desynchronized(uint32_t accessAddress) : BleMsg()
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

Hijacked::Hijacked(uint32_t accessAddress, bool success) : BleMsg()
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

Injected::Injected(uint32_t accessAddress, uint32_t attempts, bool success) : BleMsg()
{
    whad_ble_injected(
        this->getRaw(),
        accessAddress,
        attempts,
        success
    );
}