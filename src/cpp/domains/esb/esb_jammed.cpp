#include <esb/jammed.hpp>

using namespace whad::esb;

/** Jammed **/

Jammed::Jammed(EsbMsg &message) : EsbMsg(message)
{
}

Jammed::Jammed(uint32_t timestamp) : EsbMsg()
{
    whad_esb_jammed(
        this->getRaw(),
        timestamp
    );
}

uint32_t Jammed::getTimestamp()
{
    uint32_t timestamp;

    if (whad_esb_jammed_parse(this->getRaw(), &timestamp) == WHAD_SUCCESS)
    {
        return timestamp;
    }
    else
    {
        throw WhadMessageParsingError();
    } 
}
