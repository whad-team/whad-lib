#ifndef __INC_WHAD_GENERIC_HPP
#define __INC_WHAD_GENERIC_HPP

#ifdef __cplusplus

    #include <string>
    #include "message.hpp"

    namespace whad
    {
        namespace generic
        {
            enum MessageType {
                UnknownMsg = WHAD_GENERIC_UNKNOWN,
                CommandResultMsg = WHAD_GENERIC_CMDRESULT,
                VerboseMsg = WHAD_GENERIC_VERBOSE,
                DebugMsg = WHAD_GENERIC_DEBUG,
                ProgressMsg = WHAD_GENERIC_PROGRESS
            };

            enum ResultCode {
                ResultSuccess = WHAD_RESULT_SUCCESS,
                ResultError = WHAD_RESULT_ERROR,
                ResultParameterError = WHAD_RESULT_PARAMETER_ERROR,
                ResultDisconnected = WHAD_RESULT_DISCONNECTED,
                ResultWrongMode = WHAD_RESULT_WRONG_MODE,
                ResultUnsupportedDomain = WHAD_RESULT_UNSUPPORTED_DOMAIN,
                ResultBusy = WHAD_RESULT_BUSY
            };

            /* Default generic message class. */
            class GenericMsg : public NanoPbMsg
            {
                public:

                    /* Constructor and destructor. */
                    GenericMsg();
                    GenericMsg(NanoPbMsg pMessage);
                    ~GenericMsg();

                    /* Override getType() message. */
                    MessageType getType(void);
            };

            /* Verbose message. */
            class Verbose : public GenericMsg
            {
                public:
                    Verbose(std::string message);
            };

            /* Command result. */
            class CommandResult : public GenericMsg
            {
                public:
                    CommandResult(ResultCode result);
                    CommandResult(NanoPbMsg message);

                    ResultCode getResultCode();
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
            class Debug : public GenericMsg
            {
                public:
                    Debug(int32_t level, std::string message);
            };

            /* Progress notification. */
            class Progress : public GenericMsg
            {
                public:
                    Progress(int32_t value);
            };
        }
    };

#endif /* _cplusplus */

#endif /* __INC_WHAD_GENERIC_HPP */