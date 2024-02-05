#include <esb/jam.hpp>

using namespace whad::esb;

/** JamMode **/

JamMode::JamMode(EsbMsg &message) : EsbMsg(message)
{
}

JamMode::JamMode(uint32_t channel) : EsbMsg()
{
    this->m_channel = channel;

    whad_esb_jam(
        this->getRaw(),
        channel
    );
}

bool JamMode::parse(void)
{
    return (whad_esb_jam_parse(this->getRaw(), &this->m_channel) == WHAD_SUCCESS);
}

uint32_t JamMode::getChannel(void)
{
    if (this->parse())
    {
        return this->m_channel;
    }
    else
        return 0;
}