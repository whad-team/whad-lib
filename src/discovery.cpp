#include "bsp.h"
#include "discovery.hpp"

/**
 * @brief   Build a discovery ready response message.
 **/

whad::discovery::ReadyRespMessage::ReadyRespMessage() : NanoPbMsg()
{
    if (whad_discovery_ready_resp(this->getRaw()) == WHAD_ERROR)
    {
        bsp_board_led_off(0);
    }
    else
    {
        bsp_board_led_off(0);
    }
}

whad::discovery::DomainInfoRespMessage::DomainInfoRespMessage(Domains domain, DeviceCapability *capabilities) : NanoPbMsg()
{
    whad_discovery_domain_info_resp(this->getRaw(), (discovery_Domain)domain, capabilities);
}


whad::discovery::DeviceInfoRespMessage::DeviceInfoRespMessage(
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

