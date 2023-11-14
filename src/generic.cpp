#include "generic.hpp"

/**
 * @brief Build a generic verbose message.
 **/

whad::VerboseMessage::VerboseMessage(std::string message) : NanoPbMsg()
{
    whad_generic_verbose_message(this->getRaw(), (char *)message.c_str());
}