#include <esb/ptx.hpp>

using namespace whad::esb;

/** PtxMode **/

PtxMode::PtxMode(EsbMsg &message) : EsbMsg(message)
{
}

PtxMode::PtxMode(uint32_t channel) : EsbMsg()
{
    whad_esb_ptx(
        this->getRaw(),
        channel
    );
}

uint32_t PtxMode::getChannel()
{
    uint32_t channel;

    if (whad_esb_ptx_parse(this->getRaw(), &channel) == WHAD_SUCCESS)
    {
        return channel;
    }
    else
    {
        throw WhadMessageParsingError();
    }
}