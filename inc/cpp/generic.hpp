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

            /* Success command result.  */
            class Success : public CommandResult
            {
                public:
                    Success(void);
            };

            /* Error command result.  */
            class Error : public CommandResult
            {
                public:
                    Error(void);
            };

            /* Parameter error command result. */
            class ParameterError : public CommandResult
            {
                public:
                    ParameterError(void);
            };

            /* Disconnected command result. */
            class Disconnected : public CommandResult
            {
                public:
                    Disconnected(void);
            };

            /* Wrong mode command result. */
            class WrongMode : public CommandResult
            {
                public:
                    WrongMode(void);
            };

            /* Unsupported domain command result. */
            class UnsupportedDomain : public CommandResult
            {
                public:
                    UnsupportedDomain(void);
            };

            /* Busy command result. */
            class Busy : public CommandResult
            {
                public:
                    Busy(void);
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