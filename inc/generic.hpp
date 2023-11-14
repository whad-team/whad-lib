#ifndef __INC_WHAD_GENERIC_HPP
#define __INC_WHAD_GENERIC_HPP

#include <string>
#include "message.hpp"

namespace whad
{
    class VerboseMessage : public NanoPbMsg
    {
        public:
            VerboseMessage(std::string message);
    };
};

#endif /* __INC_WHAD_GENERIC_HPP */