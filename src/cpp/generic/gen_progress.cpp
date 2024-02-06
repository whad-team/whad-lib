#include <generic/progress.hpp>

using namespace whad::generic;

/**
 * @brief   Build a generic progress message.
 * 
 * @param   value   Progress value or step.
 **/

whad::generic::Progress::Progress(int32_t value) : GenericMsg()
{
    whad_generic_progress_message(this->getRaw(), value);
}