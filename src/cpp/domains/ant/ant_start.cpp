#include <ant/start.hpp>

using namespace whad::ant;

/**
 * @brief   Constructor, create a Start message.
 */

Start::Start() : AntMsg()
{
}


/**
 * @brief   Constructor, parse an AntMsg as a Start message.
 * 
 * @param[in]   message     Message to parse
 */

Start::Start(AntMsg &message) : AntMsg(message)
{
}


/**
 * @brief   Pack parameters into an AntMsg.
 */

void Start::pack()
{
    whad_ant_start(this->getMessage());
}
