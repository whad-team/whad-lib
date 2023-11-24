#include "cpp/generic.hpp"

/********************************
 * Generic message base class
 *******************************/

/**
 * @brief   Discovery message base class.
 **/

whad::generic::GenericMsg::GenericMsg() : NanoPbMsg()
{
}


/**
 * @brief       Discovery message base class.
 * 
 * @param[in]   pMessage    NanoPbMsg object containing a discovery domain message 
 **/

whad::generic::GenericMsg::GenericMsg(NanoPbMsg pMessage) : NanoPbMsg(pMessage.getRaw())
{
}


/**
 * @brief   Discovery message base class destructor.
 **/

whad::generic::GenericMsg::~GenericMsg()
{
}


/**
 * @brief       Identify the underlying discovery message.
 *
 * This method can be used when parsing incoming Discovery domain message to identify
 * the type of message it contains and process it later.
 * 
 * @return      Discovery message type.
 **/

whad::generic::MessageType whad::generic::GenericMsg::getType(void)
{
    whad::generic::MessageType msgType = (whad::generic::MessageType)whad_generic_get_message_type(
        this->getRaw()
    );

    /* Return message type. */
    return msgType;
}


/********************************
 * Generic messages classes
 *******************************/


/**
 * @brief   Build a generic verbose message.
 * 
 * @param   message Message string to pass to the host.
 **/

whad::generic::Verbose::Verbose(std::string message) : GenericMsg()
{
    whad_generic_verbose_message(this->getRaw(), (char *)message.c_str());
}


/**
 * @brief   Build a generic commmand result message.
 * 
 * @param   resultCode Command result code.
 **/

whad::generic::CommandResult::CommandResult(ResultCode resultCode) : GenericMsg()
{
    whad_generic_cmd_result(this->getRaw(), (whad_result_code_t)resultCode);
}

/**
 * @brief   Build a generic commmand result message.
 * 
 * @param   resultCode Command result code.
 **/

whad::generic::CommandResult::CommandResult(NanoPbMsg message) : GenericMsg(message)
{
}

whad::generic::ResultCode whad::generic::CommandResult::getResultCode()
{
    whad::generic::ResultCode resultCode = ResultError;

    if (whad_generic_cmd_result_parse(this->getRaw(), (whad_result_code_t *)&resultCode) == WHAD_SUCCESS)
    {
        return resultCode;
    }

    /* TODO: raise exception */
    return resultCode;
}


whad::generic::Success::Success(void) : CommandResult(ResultSuccess)
{
}

whad::generic::Error::Error(void) : CommandResult(ResultError)
{
}

whad::generic::ParameterError::ParameterError(void) : CommandResult(ResultParameterError)
{
}

whad::generic::Disconnected::Disconnected(void) : CommandResult(ResultDisconnected)
{
}

whad::generic::WrongMode::WrongMode(void) : CommandResult(ResultWrongMode)
{
}

whad::generic::UnsupportedDomain::UnsupportedDomain(void) : CommandResult(ResultUnsupportedDomain)
{
}

whad::generic::Busy::Busy(void) : CommandResult(ResultBusy)
{
}


/**
 * @brief   Build a generic verbose message.
 * 
 * @param   level   Debug level
 * @param   message Message string to pass to the host.
 **/

whad::generic::Debug::Debug(int32_t level, std::string message) : GenericMsg()
{
    whad_generic_debug_message(this->getRaw(), level, (char *)message.c_str());
}


/**
 * @brief   Build a generic progress message.
 * 
 * @param   value   Progress value or step.
 **/

whad::generic::Progress::Progress(int32_t value) : GenericMsg()
{
    whad_generic_progress_message(this->getRaw(), value);
}