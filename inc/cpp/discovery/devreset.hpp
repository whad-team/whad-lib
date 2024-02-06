#ifndef __INC_WHAD_DISCOVERY_DEVRESET_HPP
#define __INC_WHAD_DISCOVERY_DEVRESET_HPP

#include <string>
#include "message.hpp"
#include "common.hpp"
#include <discovery/base.hpp>

namespace whad::discovery {

    /* Device reset query. */
    class DeviceReset : public DiscoveryMsg
    {
        public:
            DeviceReset();
            DeviceReset(NanoPbMsg &message);

        private:
            void pack();
    };
}

#endif /* __INC_WHAD_DISCOVERY_DEVRESET_HPP */