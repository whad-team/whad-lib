#ifndef __INC_WHAD_DISCOVERY_HPP
#define __INC_WHAD_DISCOVERY_HPP

#include "../discovery.h"

#ifdef __cplusplus

    #include <string>
    #include "message.hpp"

    namespace whad
    {
        namespace discovery
        {
            /* Available domains. */
            enum Domains {
                DomainNone = DOMAIN_NONE,
                DomainPhy = DOMAIN_PHY,
                DomainBtClassic = DOMAIN_BT_CLASSIC,
                DomainBtLE = DOMAIN_BTLE,
                DomainZigbee = DOMAIN_ZIGBEE,
                DomainSixLowPan = DOMAIN_SIXLOWPAN,
                DomainEsb = DOMAIN_ESB,
                DomainLogitechUnifying = DOMAIN_LOGITECH_UNIFYING,
                DomainMosart = DOMAIN_MOSART,
                DomainAnt = DOMAIN_ANT,
                DomainAntPlus = DOMAIN_ANT_PLUS,
                DomainAntFs = DOMAIN_ANT_FS,
            };

            /* Available devices. */
            enum Devices {
                Esp32BleFuzzer = discovery_DeviceType_Esp32BleFuzzer,
                Butterfly = discovery_DeviceType_Butterfly,
                Btlejack = discovery_DeviceType_BtleJack,
                VirtualDevice = discovery_DeviceType_VirtualDevice
            };

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
                    DiscoveryMsg(NanoPbMsg pMessage);
                    ~DiscoveryMsg();

                    /* Override getType() message. */
                    whad::discovery::MessageType getType(void);
            };

            /* Device reset query. */
            class DeviceReset : public DiscoveryMsg
            {
                public:
                    DeviceReset();
                    DeviceReset(NanoPbMsg message);
            };

            /* Device ready response. */
            class ReadyResp : public DiscoveryMsg
            {
                public:
                    ReadyResp();
            };

            /* Device reset query. */
            class SetTransportSpeed : public DiscoveryMsg
            {
                public:
                    SetTransportSpeed(NanoPbMsg pMessage);
                    SetTransportSpeed(uint32_t speed);
                    uint32_t getSpeed();
            };        

            /* Device domain information query. */
            class DomainInfoQuery : public DiscoveryMsg
            {
                public:
                    /* Constructor. */
                    DomainInfoQuery(NanoPbMsg message);
                    DomainInfoQuery(Domains domain);

                    /* Accessors. */
                    Domains getDomain();
            };

            /* Domain information response. */
            class DomainInfoResp : public DiscoveryMsg
            {
                public:
                    DomainInfoResp(Domains domain, whad_domain_desc_t *capabilities);
            };

            /* Device domain information query. */
            class DeviceInfoQuery : public DiscoveryMsg
            {
                public:
                    DeviceInfoQuery(NanoPbMsg message);
                    DeviceInfoQuery(uint32_t protoVersion);
                    uint32_t getVersion();
            };

            /* Device information response. */
            class DeviceInfoResp : public DiscoveryMsg
            {
                public:
                    DeviceInfoResp(
                        Devices deviceType,
                        uint8_t deviceId[16],
                        uint32_t protoMinVer,
                        uint32_t maxSpeed,
                        std::string sFirmwareAuthor,
                        std::string sFirmwareUrl,
                        uint32_t fwVersionMajor,
                        uint32_t fwVersionMinor,
                        uint32_t fwVersionRevision,
                        whad_domain_desc_t *capabilities
                    );
            };
        };
    };

#endif /* _cplusplus */

#endif /* __INC_WHAD_DISCOVERY_HPP  */