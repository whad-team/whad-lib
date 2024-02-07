#include <esb/stop.hpp>

using namespace whad::esb;


/**
 * @brief   Constructor, create a Stop message
*/
Stop::Stop() : EsbMsg()
{
}


/**
 * @brief   Constructor, parse an EsbMsg as a Stop message.
 * 
 * @param[in]   message     Message to parse
 */

Stop::Stop(EsbMsg &message) : EsbMsg(message)
{
}


/**
 * @brief   Pack parameters into an EsbMsg.
 */

void Stop::pack()
{
    whad_esb_stop(this->getMessage());
}