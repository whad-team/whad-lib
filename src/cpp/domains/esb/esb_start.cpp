#include <esb/start.hpp>

using namespace whad::esb;

/** Start **/

Start::Start() : EsbMsg()
{
}

Start::Start(EsbMsg &message) : EsbMsg(message)
{
}
