#ifndef __INC_WHAD_DISCOVERY_HPP
#define __INC_WHAD_DISCOVERY_HPP

#include <string>
#include <discovery.h>
#include <message.hpp>
#include <common.hpp>

namespace whad::discovery
{
    enum MessageType {
        UnknownMsg = WHAD_DISCOVERY_UNKNOWN,
        DeviceInfoQueryMsg = WHAD_DISCOVERY_DEVICE_INFO_QUERY,
        DeviceInfoRespMsg = WHAD_DISCOVERY_DEVICE_INFO_RESP,
        DeviceResetMsg = WHAD_DISCOVERY_DEVICE_RESET,
        ReadyRespMsg = WHAD_DISCOVERY_READY_RESP,
        DomainInfoQueryMsg = WHAD_DISCOVERY_DOMAIN_INFO_QUERY,
        DomainInfoRespMsg = WHAD_DISCOVERY_DOMAIN_INFO_RESP,
        SetSpeedMsg = WHAD_DISCOVERY_SET_SPEED
    };

    /* Default discovery message class. */
    class DiscoveryMsg : public NanoPbMsg
    {
        public:

            /* Constructor and destructor. */
            DiscoveryMsg();
            DiscoveryMsg(NanoPbMsg &pMessage);
            ~DiscoveryMsg();

            /* Override getType() message. */
            MessageType getType(void);
    };
}

#endif /* __INC_WHAD_DISCOVERY_HPP */