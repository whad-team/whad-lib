#include <esb/jam.hpp>

using namespace whad::esb;


JamMode::JamMode(EsbMsg &message) : EsbMsg(message)
{
    /* Unpack message. */
    this->unpack();
}

JamMode::JamMode(uint32_t channel) : EsbMsg()
{
    m_channel = channel;
}

uint32_t JamMode::getChannel(void)
{
    return m_channel;
}

void JamMode::pack()
{
    whad_esb_jam(
        this->getMessage(),
        m_channel
    );
}

void JamMode::unpack()
{
    if (whad_esb_jam_parse(this->getMessage(), &m_channel) == WHAD_ERROR)
    {
        throw WhadMessageParsingError();
    }
}