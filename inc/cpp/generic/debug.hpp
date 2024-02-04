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
    };

}

#endif /* __INC_WHAD_GENERIC_DEBUG_HPP */