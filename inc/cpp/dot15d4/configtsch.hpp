#ifndef __INC_WHAD_DOT15D4_TSCH_HPP
#define __INC_WHAD_DOT15D4_TSCH_HPP

#include <string>
#include "message.hpp"
#include "common.hpp"
#include <dot15d4/base.hpp>

namespace whad::dot15d4 {

    class ConfigureTSCH : public Dot15d4Msg
    {
        public:
            ConfigureTSCH(Dot15d4Msg &message);
            ConfigureTSCH(bool enabled);

            /* Getters. */
            bool getEnabled();

        private:
            void pack();
            void unpack();

            bool m_enabled;
                    
    };


    
}

#endif /* __INC_WHAD_DOT15D4_TSCH_HPP */