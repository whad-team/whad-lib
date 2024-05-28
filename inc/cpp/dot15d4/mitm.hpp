#ifndef __INC_WHAD_DOT15D4_MITMMODE_HPP
#define __INC_WHAD_DOT15D4_MITMMODE_HPP

#include <string>
#include "message.hpp"
#include "common.hpp"
#include <dot15d4/base.hpp>

namespace whad::dot15d4 {

    class MitmMode : public Dot15d4Msg
    {
        public:
            MitmMode(Dot15d4Msg &message);
            MitmMode(MitmRole role);

            /* Getters. */
            MitmRole getRole();

        private:
            void pack();
            void unpack();

            MitmRole m_role;               
    };
}

#endif /* __INC_WHAD_DOT15D4_MITMMODE_HPP */