#include <generic/debug.hpp>

using namespace whad::generic;

/**
 * @brief   Build a generic verbose message.
 * 
 * @param   level   Debug level
 * @param   message Message string to pass to the host.
 **/

Debug::Debug(int32_t level, std::string message) : GenericMsg()
{
    m_level = level;
    m_message = message;
}


/**
 * @brief   Build the corresponding NanoPb message.
 */

void Debug::pack()
{
    /* Use parameters to craft the NanoPb message. */
    whad_generic_debug_message(this->getMessage(), m_level,
                               (char *)m_message.c_str());
}
