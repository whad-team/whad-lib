#include <esb/sniff.hpp>

using namespace whad::esb;


SniffMode::SniffMode(EsbMsg &message) : EsbMsg(message)
{
}

SniffMode::SniffMode(uint32_t channel, EsbAddress &address, bool showAcks)
{
    whad_esb_address_t addr;

    /* Convert address. */
    addr.size = address.getLength();
    memcpy(addr.address, address.getAddressBuf(), address.getLength());

    whad_esb_sniff(
        this->getRaw(),
        &addr,
        channel,
        showAcks
    );
}

SniffMode::SniffMode(uint32_t channel, EsbAddress &address) : SniffMode(channel, address, false)
{
}

SniffMode::SniffMode(EsbAddress &address) : SniffMode(WHAD_ESB_CHANNEL_AUTO, address, false)
{
}

SniffMode::SniffMode(uint32_t channel) : SniffMode(channel, PromiscAddr, false)
{
}

SniffMode::SniffMode() : SniffMode(WHAD_ESB_CHANNEL_AUTO, PromiscAddr, false)
{
}

bool SniffMode::parse(void)
{
    whad_result_t result;
    whad_esb_sniff_params_t params;

    result = whad_esb_sniff_parse(
        this->getRaw(),
        &params
    );

    if (result == WHAD_ERROR)
        return false;

    /* Saved parsed parameters. */
    this->m_channel = params.channel;
    this->m_address.setAddress(params.address.address, params.address.size);
    this->m_showacks = params.show_acks;

    /* Success. */
    return true;
}

uint32_t SniffMode::getChannel(void)
{
    if (this->parse())
    {
        return this->m_channel;
    }
    else
        return 0;
}

EsbAddress& SniffMode::getAddress(void)
{
    if (this->parse())
    {
        return this->m_address;
    }
    else
        return NullAddr;
}

bool SniffMode::mustShowAcks(void)
{
    if (this->parse())
    {
        return this->m_showacks;
    }
    else
        return false;
}