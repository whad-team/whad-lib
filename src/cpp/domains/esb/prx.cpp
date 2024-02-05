#include <esb/prx.hpp>

using namespace whad::esb;

/** PrxMode **/

PrxMode::PrxMode(EsbMsg &message) : EsbMsg(message)
{
}

PrxMode::PrxMode(uint32_t channel) : EsbMsg()
{
    whad_esb_prx(
        this->getRaw(),
        channel
    );
}

uint32_t PrxMode::getChannel()
{
    uint32_t channel;

    if (whad_esb_prx_parse(this->getRaw(), &channel) == WHAD_SUCCESS)
    {
        return channel;
    }
    else
    {
        throw WhadMessageParsingError();
    }
}
