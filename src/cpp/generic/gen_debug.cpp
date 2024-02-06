#include <generic/debug.hpp>

using namespace whad::generic;

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
