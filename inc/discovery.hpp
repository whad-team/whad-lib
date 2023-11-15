#ifndef __INC_WHAD_DISCOVERY_HPP
#define __INC_WHAD_DISCOVERY_HPP

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

            /* Device reset query. */
            class DeviceReset : public NanoPbMsg
            {
                public:
                    DeviceReset();
            };

            /* Device ready response. */
            class ReadyResp : public NanoPbMsg
            {
                public:
                    ReadyResp();
            };

            /* Device reset query. */
            class SetTransportSpeed : public NanoPbMsg
            {
                public:
                    SetTransportSpeed(uint32_t speed);
            };        

            /* Device domain information query. */
            class DomainInfoQuery : public NanoPbMsg
            {
                public:
                    DomainInfoQuery(Domains domain);
            };

            /* Domain information response. */
            class DomainInfoResp : public NanoPbMsg
            {
                public:
                    DomainInfoResp(Domains domain, whad_domain_desc_t *capabilities);
            };

            /* Device domain information query. */
            class DeviceInfoQuery : public NanoPbMsg
            {
                public:
                    DeviceInfoQuery(uint32_t protoVersion);
            };

            /* Device information response. */
            class DeviceInfoResp : public NanoPbMsg
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