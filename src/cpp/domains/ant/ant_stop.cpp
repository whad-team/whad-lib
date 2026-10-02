#include <ant/stop.hpp>

using namespace whad::ant;

/**
 * @brief   Constructor, create a Stop message.
 */

Stop::Stop() : AntMsg()
{
}


/**
 * @brief   Constructor, parse an AntMsg as a Stop message.
 * 
 * @param[in]   message     Message to parse
 */

Stop::Stop(AntMsg &message) : AntMsg(message)
{
}


/**
 * @brief   Pack parameters into an AntMsg.
 */

void Stop::pack()
{
    whad_ant_stop(this->getMessage());
}
