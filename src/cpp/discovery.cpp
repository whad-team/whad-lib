#include "cpp/discovery.hpp"

/********************************
 * Discovery message base class
 *******************************/

/**
 * @brief   Discovery message base class.
 **/

whad::discovery::DiscoveryMsg::DiscoveryMsg() : NanoPbMsg()
{
}


/**
 * @brief       Discovery message base class.
 * 
 * @param[in]   pMessage    NanoPbMsg object containing a discovery domain message 
 **/

whad::discovery::DiscoveryMsg::DiscoveryMsg(NanoPbMsg pMessage) : NanoPbMsg(pMessage.getRaw())
{
}


/**
 * @brief   Discovery message base class destructor.
 **/

whad::discovery::DiscoveryMsg::~DiscoveryMsg()
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

whad::discovery::MessageType whad::discovery::DiscoveryMsg::getType(void)
{
    whad::discovery::MessageType msgType = (whad::discovery::MessageType)whad_discovery_get_message_type(
        this->getRaw()
    );

    /* Return message type. */
    return msgType;
}


/********************************
 * Discovery messages classes
 *******************************/


/**
 * @brief   Build a device reset message.
 **/

whad::discovery::DeviceReset::DeviceReset() : DiscoveryMsg()
{
    whad_discovery_device_reset(this->getRaw());
}


/**
 * @brief       Build a device reset message from a NanoPb message.
 * 
 * @param[in]   NanoPb message to wrap as a DeviceReset message
 **/

whad::discovery::DeviceReset::DeviceReset(NanoPbMsg message) : DiscoveryMsg(message)
{
}


/**
 * @brief   Build a discovery ready response message.
 * 
 * This message must be sent in response to a Reset query from the host,
 * to acknowledge the fact the device has been reset and is ready to process
 * incoming commands.
 **/

whad::discovery::ReadyResp::ReadyResp() : DiscoveryMsg()
{
    whad_discovery_ready_resp(this->getRaw());
}


/* TODO: add doc */
whad::discovery::DomainInfoQuery::DomainInfoQuery(Domains domain) : DiscoveryMsg()
{
    whad_discovery_domain_info_query(this->getRaw(), (whad_domain_t)domain);
}

whad::discovery::DomainInfoQuery::DomainInfoQuery(NanoPbMsg message) : DiscoveryMsg(message)
{
}

/* TODO: add doc */
whad::discovery::Domains whad::discovery::DomainInfoQuery::getDomain()
{
    whad_domain_t domain;

    if (whad_discovery_domain_info_query_parse(this->getRaw(), &domain) == WHAD_SUCCESS)
    {
        return (whad::discovery::Domains)domain;
    }

    /* Failed to get domain. */
    return DomainNone;
}


/**
 * @brief   Build a domain information response.
 * 
 * This message must be sent in response to a Domain Information request sent by the host
 * to provide the supported capabilities.
 * 
 * @param   domain          The target domain queried by the host
 * @param   capabilities    The device's capabilities structure
 **/

whad::discovery::DomainInfoResp::DomainInfoResp(Domains domain, whad_domain_desc_t *capabilities) : DiscoveryMsg()
{
    whad_discovery_domain_info_resp(this->getRaw(), (whad_domain_t)domain, capabilities);
}


/**
 * @brief   Build a device information response.
 * 
 * This message must be sent in response to a Device Information request sent by the host
 * to give all the details about the device and its firmware.
 * 
 * @param   deviceType          Specifies the device type
 * @param   deviceId            An ID that uniquely identifies this device\
 * @param   protoMinVer         Minimal version of WHAD protocol supported by this device
 * @param   maxSpeed            Maximum communication speed supported by the device
 * @param   sFirmwareAuthor     Firmware's author name
 * @param   sFirmwareUrl        Firmware source code or project URL
 * @param   fwVersionMajor      Major version of the firmware running on the device
 * @param   fwVersionMinor      Minor version of the firmware running on the device
 * @param   fwVersionRevision   Minor version of the firmware running on the device
 * @param   capabilities        Specifies the device capabilities and supported commands per domain
 **/

whad::discovery::DeviceInfoResp::DeviceInfoResp(
    whad::discovery::Devices deviceType,
    uint8_t deviceId[16],
    uint32_t protoMinVer,
    uint32_t maxSpeed,
    std::string sFirmwareAuthor,
    std::string sFirmwareUrl,
    uint32_t fwVersionMajor,
    uint32_t fwVersionMinor,
    uint32_t fwVersionRevision,
    whad_domain_desc_t *capabilities
) : DiscoveryMsg()
{
    whad_discovery_device_info_resp(
        this->getRaw(),
        (discovery_DeviceType)deviceType,
        deviceId,
        protoMinVer,
        maxSpeed,
        (char *)sFirmwareAuthor.c_str(),
        (char *)sFirmwareUrl.c_str(),
        fwVersionMajor, fwVersionMinor, fwVersionRevision,
        capabilities
    );
}

whad::discovery::SetTransportSpeed::SetTransportSpeed(uint32_t speed)
{
    whad_discovery_set_speed(this->getRaw(), speed);
}

whad::discovery::SetTransportSpeed::SetTransportSpeed(NanoPbMsg message) : DiscoveryMsg(message)
{
}

uint32_t whad::discovery::SetTransportSpeed::getSpeed()
{
    uint32_t speed = 0;

    if (whad_discovery_set_speed_parse(this->getRaw(), &speed) == WHAD_SUCCESS)
    {
        return speed;
    }

    /* Error. */
    return 0;
}

whad::discovery::DeviceInfoQuery::DeviceInfoQuery(NanoPbMsg message) : DiscoveryMsg(message)
{
}

whad::discovery::DeviceInfoQuery::DeviceInfoQuery(uint32_t protoVersion) : DiscoveryMsg()
{
    whad_discovery_device_info_query(this->getRaw(), protoVersion);
}

uint32_t whad::discovery::DeviceInfoQuery::getVersion(void)
{
    uint32_t version;

    if (whad_discovery_device_info_query_parse(this->getRaw(), &version) == WHAD_SUCCESS)
    {
        return version;
    }

    /* Error. */
    return 0;
}