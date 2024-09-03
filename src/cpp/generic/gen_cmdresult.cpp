#include <generic/cmdresult.hpp>

using namespace whad::generic;


/**
 * @brief   Build a generic commmand result message.
 * 
 * @param[in]   resultCode Command result code.
 **/

CommandResult::CommandResult(ResultCode resultCode) : GenericMsg()
{
    m_code = resultCode;
}


/**
 * @brief   Build a generic commmand result message.
 * 
 * @param[in]   message     Underlying NanoPb message.
 **/

CommandResult::CommandResult(NanoPbMsg message) : GenericMsg(message)
{
    /* Default return code. */
    this->m_code = ResultError;

    /* Unpack NanoPb message. */
    this->unpack();
}


/**
 * @brief   Return the result code.
 * 
 * @retval  Result code
 */

ResultCode CommandResult::getResultCode()
{
    return this->m_code;
}


/**
 * @brief   Pack all parameters into the corresponding NanoPb message using
 *          C helper.
 */

void CommandResult::pack(void)
{
    whad_generic_cmd_result(this->getMessage(), (whad_result_code_t)m_code);
}


/**
 * @brief   Unpack parameters from message and load them into the corresponding
 *          properties.
 */

void CommandResult::unpack()
{
    ResultCode resultCode = ResultError;

    if (whad_generic_cmd_result_parse(this->getMessage(), (whad_result_code_t *)&resultCode) == WHAD_SUCCESS)
    {
        m_code = resultCode;
    }
    else
    {
        throw whad::WhadMessageParsingError();
    }
}


/**
 * @brief   Create a success command result object.
 */

Success::Success(void) : CommandResult(ResultSuccess)
{
}


/**
 * @brief   Create an error command result object.
 */

Error::Error(void) : CommandResult(ResultError)
{
}


/**
 * @brief   Create an parameter error command result object.
 */

ParameterError::ParameterError(void) : CommandResult(ResultParameterError)
{
}


/**
 * @brief   Create an disconnected command result object.
 */

Disconnected::Disconnected(void) : CommandResult(ResultDisconnected)
{
}


/**
 * @brief   Create a wrong mode error command result object.
 */

WrongMode::WrongMode(void) : CommandResult(ResultWrongMode)
{
}


/**
 * @brief   Create an unsupported domain error command result object.
 */

UnsupportedDomain::UnsupportedDomain(void) : CommandResult(ResultUnsupportedDomain)
{
}


/**
 * @brief   Create a busy command result object.
 */

Busy::Busy(void) : CommandResult(ResultBusy)
{
}