#include <generic/progress.hpp>

using namespace whad::generic;

/**
 * @brief   Build a generic progress message.
 * 
 * @param   value   Progress value or step.
 **/

Progress::Progress(int32_t value) : GenericMsg()
{
    m_value = value;
}

void Progress::pack()
{
    whad_generic_progress_message(this->getMessage(), m_value);
}
