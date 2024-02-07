#ifndef __INC_WHAD_GENERIC_DEBUG_HPP
#define __INC_WHAD_GENERIC_DEBUG_HPP

#include <string>
#include "message.hpp"
#include "common.hpp"
#include "generic/generic.hpp"

namespace whad::generic {
            
    /* Debug message and level. */
    class Debug : public GenericMsg
    {
        public:
            Debug(int32_t level, std::string message);

        private:
            void pack();

            std::string m_message;
            int32_t m_level;
    };

}

#endif /* __INC_WHAD_GENERIC_DEBUG_HPP */