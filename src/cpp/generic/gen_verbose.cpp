#include <generic/verbose.hpp>

using namespace whad::generic;


/**
 * @brief   Build a generic verbose message.
 * 
 * @param   message Message string to pass to the host.
 **/

Verbose::Verbose(std::string message) : GenericMsg()
{
    m_message = message;
}


void Verbose::pack()
{
    whad_generic_verbose_message(this->getMessage(), (char *)m_message.c_str());
}
