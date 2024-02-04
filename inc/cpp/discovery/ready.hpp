#ifndef __INC_WHAD_DISCOVERY_READY_HPP
#define __INC_WHAD_DISCOVERY_READY_HPP

#include <string>
#include "message.hpp"
#include "common.hpp"
#include <discovery/discovery.hpp>

namespace whad::discovery {

    /* Device ready response. */
    class ReadyResp : public DiscoveryMsg
    {
        public:
            ReadyResp();

        private:

            void pack();
    };

}

#endif /* __INC_WHAD_DISCOVERY_READY_HPP */