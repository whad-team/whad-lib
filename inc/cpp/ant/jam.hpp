#ifndef __INC_WHAD_ANT_JAM_HPP
#define __INC_WHAD_ANT_JAM_HPP

#include <string>
#include "message.hpp"
#include "common.hpp"
#include "ant/base.hpp"

namespace whad::ant {

    class Jam : public AntMsg
    {
        public:

            /* Constructors. */
            Jam(AntMsg &message);
            Jam(uint32_t rf_channel);
            uint32_t getRFChannel();
            

        private:
            uint32_t m_rf_channel;

            void pack();
            void unpack();
    };

#endif /* __INC_WHAD_ANT_JAM_HPP */