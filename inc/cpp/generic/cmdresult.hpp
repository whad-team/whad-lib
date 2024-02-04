#ifndef __INC_WHAD_GENERIC_CMDRESULT_HPP
#define __INC_WHAD_GENERIC_CMDRESULT_HPP

#include <string>
#include "message.hpp"
#include "common.hpp"
#include "generic/generic.hpp"

namespace whad::generic {

enum ResultCode {
    ResultSuccess = WHAD_RESULT_SUCCESS,
    ResultError = WHAD_RESULT_ERROR,
    ResultParameterError = WHAD_RESULT_PARAMETER_ERROR,
    ResultDisconnected = WHAD_RESULT_DISCONNECTED,
    ResultWrongMode = WHAD_RESULT_WRONG_MODE,
    ResultUnsupportedDomain = WHAD_RESULT_UNSUPPORTED_DOMAIN,
    ResultBusy = WHAD_RESULT_BUSY
};

/**
 * The CommandResult class represents a result returned by a firmware
 * and contains a code indicating a specific status. This code is used
 * to report success, errors but also some notifications.
 */

class CommandResult : public GenericMsg
{
    public:
        CommandResult(ResultCode result);
        CommandResult(NanoPbMsg message);

        ResultCode getResultCode();

    private:
        void pack();
        void unpack();

        ResultCode m_code;
};

/**
 * Specialized classes
 * 
 * The following classes are helpers to create various result commands based
 * on the CommandResult class. There is no specific data processing except
 * setting the correct error code into the parent CommandResult object.
 */

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

}

#endif /* __INC_WHAD_GENERIC_CMDRESULT_HPP */