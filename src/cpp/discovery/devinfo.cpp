#include <discovery/devinfo.hpp>

using namespace whad::discovery;

/***********************
 * Device Info Response
 **********************/

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

DeviceInfoResp::DeviceInfoResp(
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

/***********************
 * Device Info Query
 **********************/

/**
 *  @brief  Parse a DiscoveryMsg object as a DeviceInfoQuery and extract its
 *          parameters.
 */

DeviceInfoQuery::DeviceInfoQuery(DiscoveryMsg &message) : DiscoveryMsg(message)
{
    this->unpack();
}


/**
 *  @brief  Create a DeviceInfoQuery message with a specific protocol version.
 * 
 *  @param  protoVersion    Version of the WHAD protocol supported by this device
 */

DeviceInfoQuery::DeviceInfoQuery(uint32_t protoVersion) : DiscoveryMsg()
{
    m_version = protoVersion;
}


/**
 *  @brief  Return the current protocol version
 * 
 *  @retval Protocol version
 */

uint32_t DeviceInfoQuery::getVersion(void)
{
    return m_version;
}


/**
 *  @brief  Callback method to pack the message parameters into a raw message.
 */

void DeviceInfoQuery::pack()
{
    whad_discovery_device_info_query(this->getMessage(), m_version);
}


/**
 * @brief   Unpack the parameters of a DeviceInfoQuery message.
 */

void DeviceInfoQuery::unpack()
{
    if(whad_discovery_device_info_query_parse(this->getMessage(), &m_version) == WHAD_ERROR)
    {
        throw WhadMessageParsingError();
    }
}