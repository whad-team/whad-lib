#ifndef __INC_WHAD_GENERIC_HPP
#define __INC_WHAD_GENERIC_HPP

#include <string>
#include "message.hpp"

namespace whad
{
    namespace generic
    {
        class VerboseMessage : public NanoPbMsg
        {
            public:
                VerboseMessage(std::string message);
        };

        class CommandResult : public NanoPbMsg
        {
            public:
                CommandResult(whad_result_code_t result);
        };

        class DebugMessage : public NanoPbMsg
        {
            public:
                DebugMessage(int32_t level, std::string message);
        };

        class ProgressMessage : public NanoPbMsg
        {
            public:
                ProgressMessage(int32_t value);
        };
    }
};

#endif /* __INC_WHAD_GENERIC_HPP */