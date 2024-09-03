#ifndef __INC_WHAD_DISCOVERY_DEVINFO_HPP
#define __INC_WHAD_DISCOVERY_DEVINFO_HPP

#include <string>
#include "message.hpp"
#include "common.hpp"
#include <discovery/discovery.hpp>

namespace whad::discovery {

    /* Available devices. */
    enum Devices {
        Esp32BleFuzzer = discovery_DeviceType_Esp32BleFuzzer,   /*!< Espressif ESP32 BLE fuzzer */
        Butterfly = discovery_DeviceType_Butterfly,             /*!< nRF52 running ButteRFly firmware. */
        Btlejack = discovery_DeviceType_BtleJack,               /*!< Btlejack (nRF52-based Micro:Bit or DK) */
        VirtualDevice = discovery_DeviceType_VirtualDevice      /*!< Virtual device */
    };

    /* Device domain information query. */
    class DeviceInfoQuery : public DiscoveryMsg
    {
        public:
            DeviceInfoQuery(DiscoveryMsg &message);
            DeviceInfoQuery(uint32_t protoVersion);

            uint32_t getVersion();

        private:
            void pack();
            void unpack();

            uint32_t m_version;
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
}

#endif /* __INC_WHAD_DISCOVERY_DEVINFO_HPP */