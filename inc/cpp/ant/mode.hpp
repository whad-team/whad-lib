#ifndef __INC_WHAD_ANT_MODE_HPP
#define __INC_WHAD_ANT_MODE_HPP

#include <string>
#include "message.hpp"
#include "common.hpp"
#include "ant/base.hpp"

namespace whad::ant {

    class MasterMode : public AntMsg
    {
        public:

            /* Constructors. */
            MasterMode(AntMsg &message);
            MasterMode(uint32_t channel_number);

            uint32_t getChannelNumber();

        private:
            uint32_t m_channel_number;
            void pack();
            void unpack();
    };

    class SlaveMode : public AntMsg
    {
        public:

            /* Constructors. */
            SlaveMode(AntMsg &message);
            SlaveMode(uint32_t channel_number);

            uint32_t getChannelNumber();

        private:
            uint32_t m_channel_number;
            void pack();
            void unpack();
    };
#endif /* __INC_WHAD_ANT_MODE_HPP */