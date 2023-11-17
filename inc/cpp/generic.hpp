#ifndef __INC_WHAD_GENERIC_HPP
#define __INC_WHAD_GENERIC_HPP

#ifdef __cplusplus

    #include <string>
    #include "message.hpp"

    namespace whad
    {
        namespace generic
        {
            /* Verbose message. */
            class Verbose : public NanoPbMsg
            {
                public:
                    Verbose(std::string message);
            };

            /* Command result. */
            class CommandResult : public NanoPbMsg
            {
                public:
                    CommandResult(whad_result_code_t result);
            };

            /* Debug message and level. */
            class Debug : public NanoPbMsg
            {
                public:
                    Debug(int32_t level, std::string message);
            };

            /* Progress notification. */
            class Progress : public NanoPbMsg
            {
                public:
                    Progress(int32_t value);
            };
        }
    };

#endif /* _cplusplus */

#endif /* __INC_WHAD_GENERIC_HPP */