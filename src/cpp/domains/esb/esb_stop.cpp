#include <esb/stop.hpp>

using namespace whad::esb;

/** Stop **/

Stop::Stop() : EsbMsg()
{
}

Stop::Stop(EsbMsg &message) : EsbMsg(message)
{
}