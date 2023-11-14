#include "bsp.h"
#include "discovery.hpp"

/**
 * @brief   Build a discovery ready response message.
 * 
 * This message must be sent in response to a Reset query from the host,
 * to acknowledge the fact the device has been reset and is ready to process
 * incoming commands.
 **/

whad::discovery::ReadyResp::ReadyResp() : NanoPbMsg()
{
    whad_discovery_ready_resp(this->getRaw());
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

whad::discovery::DomainInfoResp::DomainInfoResp(Domains domain, DeviceCapability *capabilities) : NanoPbMsg()
{
    whad_discovery_domain_info_resp(this->getRaw(), (discovery_Domain)domain, capabilities);
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
    DeviceCapability *capabilities
) : NanoPbMsg()
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

