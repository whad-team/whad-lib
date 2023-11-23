#include "cpp/generic.hpp"

/**
 * @brief   Build a generic verbose message.
 * 
 * @param   message Message string to pass to the host.
 **/

whad::generic::Verbose::Verbose(std::string message) : NanoPbMsg()
{
    whad_generic_verbose_message(this->getRaw(), (char *)message.c_str());
}


/**
 * @brief   Build a generic commmand result message.
 * 
 * @param   resultCode Command result code.
 **/

whad::generic::CommandResult::CommandResult(whad_result_code_t resultCode) : NanoPbMsg()
{
    whad_generic_cmd_result(this->getRaw(), resultCode);
}

whad::generic::Success::Success(void) : CommandResult(WHAD_RESULT_SUCCESS)
{
}

whad::generic::Error::Error(void) : CommandResult(WHAD_RESULT_ERROR)
{
}

whad::generic::ParameterError::ParameterError(void) : CommandResult(WHAD_RESULT_PARAMETER_ERROR)
{
}

whad::generic::Disconnected::Disconnected(void) : CommandResult(WHAD_RESULT_DISCONNECTED)
{
}

whad::generic::WrongMode::WrongMode(void) : CommandResult(WHAD_RESULT_WRONG_MODE)
{
}

whad::generic::UnsupportedDomain::UnsupportedDomain(void) : CommandResult(WHAD_RESULT_UNSUPPORTED_DOMAIN)
{
}

whad::generic::Busy::Busy(void) : CommandResult(WHAD_RESULT_BUSY)
{
}


/**
 * @brief   Build a generic verbose message.
 * 
 * @param   level   Debug level
 * @param   message Message string to pass to the host.
 **/

whad::generic::Debug::Debug(int32_t level, std::string message) : NanoPbMsg()
{
    whad_generic_debug_message(this->getRaw(), level, (char *)message.c_str());
}


/**
 * @brief   Build a generic progress message.
 * 
 * @param   value   Progress value or step.
 **/

whad::generic::Progress::Progress(int32_t value) : NanoPbMsg()
{
    whad_generic_progress_message(this->getRaw(), value);
}