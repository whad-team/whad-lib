#include <esb/start.hpp>

using namespace whad::esb;

/**
 * @brief   Constructor, create a Start message.
 */

Start::Start() : EsbMsg()
{
}


/**
 * @brief   Constructor, parse an EsbMsg as a Start message.
 * 
 * @param[in]   message     Message to parse
 */

Start::Start(EsbMsg &message) : EsbMsg(message)
{
}


/**
 * @brief   Pack parameters into an EsbMsg.
 */

void Start::pack()
{
    whad_esb_start(this->getMessage());
}
