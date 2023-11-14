#ifndef __INC_WHAD_DISCOVERY_HPP
#define __INC_WHAD_DISCOVERY_HPP

#include <string>
#include "message.hpp"

namespace whad
{
    namespace discovery
    {

        /* Available domains. */
        enum Domains {
            DomainNone = discovery_Domain__DomainNone,
            DomainPhy = discovery_Domain_Phy,
            DomainBtClassic = discovery_Domain_BtClassic,
            DomainBtLE = discovery_Domain_BtLE,
            DomainZigbee = discovery_Domain_Zigbee,
            DomainSixLowPan = discovery_Domain_SixLowPan,
            DomainEsb = discovery_Domain_Esb,
            DomainLogitechUnifying = discovery_Domain_LogitechUnifying,
            DomainMosart = discovery_Domain_Mosart,
            DomainAnt = discovery_Domain_ANT,
            DomainAntPlus = discovery_Domain_ANT_Plus,
            DomainAntFs = discovery_Domain_ANT_FS,
        };

        /* Available devices. */
        enum Devices {
            Esp32BleFuzzer = discovery_DeviceType_Esp32BleFuzzer,
            Butterfly = discovery_DeviceType_Butterfly,
            Btlejack = discovery_DeviceType_BtleJack,
            VirtualDevice = discovery_DeviceType_VirtualDevice
        };

        class ReadyRespMessage : public NanoPbMsg
        {
            public:
                ReadyRespMessage();
        };

        class DomainInfoRespMessage : public NanoPbMsg
        {
            public:
                DomainInfoRespMessage(Domains domain, DeviceCapability *capabilities);
        };


        class DeviceInfoRespMessage : public NanoPbMsg
        {
            public:
                DeviceInfoRespMessage(
                    Devices deviceType,
                    uint8_t deviceId[16],
                    uint32_t protoMinVer,
                    uint32_t maxSpeed,
                    std::string sFirmwareAuthor,
                    std::string sFirmwareUrl,
                    uint32_t fwVersionMajor,
                    uint32_t fwVersionMinor,
                    uint32_t fwVersionRevision,
                    DeviceCapability *capabilities
                );
        };
    };
};

#endif /* __INC_WHAD_DISCOVERY_HPP  */