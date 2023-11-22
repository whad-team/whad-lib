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
 * @brief   Create a DataPdu object from a BLE PDU.
 * 
 * @param[in]   pdu         Pointer to a byte array containing the PDU
 * @param[in]   length      Size in bytes of the PDU
 * @param[in]   direction   Direction of the PDU (host to slave, slave to host, ...)
 **/

Pdu::Pdu(uint32_t conn_handle, uint8_t *pdu, int length, Direction direction, bool processed, bool decrypted) : NanoPbMsg()
{
    /* Initialize our data pdu message. */
    whad_ble_pdu(this->getRaw(), pdu, length, (whad_ble_direction_t)direction, conn_handle, processed, decrypted);
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
                          uint8_t *p_pdu, int length, uint32_t crc, bool crc_validity, uint32_t timestamp,
                          uint32_t relative_timestamp, whad_ble_direction_t direction, bool processed,
                          bool decrypted) : NanoPbMsg()
{
    whad_ble_raw_pdu(this->getRaw(), channel, rssi, conn_handle, access_address, p_pdu, length, crc, crc_validity,
                     timestamp, relative_timestamp, (whad_ble_direction_t)direction, processed, decrypted, true);
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
                           uint8_t *p_pdu, int length, uint32_t crc, bool crc_validity, whad_ble_direction_t direction,
                           bool processed, bool decrypted) : NanoPbMsg()
{
    whad_ble_raw_pdu(this->getRaw(), channel, rssi, conn_handle, access_address, p_pdu, length, crc, crc_validity,
                     0, 0, (whad_ble_direction_t)direction, processed, decrypted, false);
}


/**
 * @brief       Connection notification constructor. 
 * 
 * @param[in]   connHandle  Connection handle assigned to this connection
 * @param[in]   advAddr     Advertiser BD address
 * @param[in]   initAddr    Initiator BD address
 **/

NotifyConnected::NotifyConnected(uint32_t connHandle, BDAddress advAddr, BDAddress initAddr)  : NanoPbMsg()
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

NotifyDisconnected::NotifyDisconnected(uint32_t connHandle, uint32_t reason) : NanoPbMsg()
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