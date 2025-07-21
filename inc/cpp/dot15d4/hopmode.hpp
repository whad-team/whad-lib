#ifndef __INC_WHAD_DOT15D4_HOPMODE_HPP
#define __INC_WHAD_DOT15D4_HOPMODE_HPP

#include <string>
#include "message.hpp"
#include "common.hpp"
#include <dot15d4/base.hpp>

namespace whad::dot15d4 {

    class HopMode : public Dot15d4Msg
    {
        public:
            HopMode(Dot15d4Msg &message);
            HopMode(bool channel);

            /* Getters. */
            bool getHopMode();

            /* Setters. */
            void setHopMode(bool mode);

        private:
            void pack();
            void unpack();

            bool m_hopping;               
    };

}

#endif /* __INC_WHAD_DOT15D4_HOPMODE_HPP */