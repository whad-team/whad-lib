#ifndef __INC_WHAD_DISCOVERY_HPP
#define __INC_WHAD_DISCOVERY_HPP

#include <string>
#include <discovery.h>
#include <message.hpp>
#include <common.hpp>

namespace whad::discovery
{
    /*! Discovery message type */
    enum MessageType {
        UnknownMsg = WHAD_DISCOVERY_UNKNOWN,                    /*!< Unknown message type */
        DeviceInfoQueryMsg = WHAD_DISCOVERY_DEVICE_INFO_QUERY,  /*!< Device info query */
        DeviceInfoRespMsg = WHAD_DISCOVERY_DEVICE_INFO_RESP,    /*!< Device info response */
        DeviceResetMsg = WHAD_DISCOVERY_DEVICE_RESET,           /*!< Device reset query */
        ReadyRespMsg = WHAD_DISCOVERY_READY_RESP,               /*!< Device ready notification */
        DomainInfoQueryMsg = WHAD_DISCOVERY_DOMAIN_INFO_QUERY,  /*!< Device domain info query */
        DomainInfoRespMsg = WHAD_DISCOVERY_DOMAIN_INFO_RESP,    /*!< Device domain info response */
        SetSpeedMsg = WHAD_DISCOVERY_SET_SPEED                  /*!< Set device speed query */
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