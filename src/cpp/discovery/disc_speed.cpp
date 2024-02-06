#include <discovery/speed.hpp>

using namespace whad::discovery;


SetTransportSpeed::SetTransportSpeed(uint32_t speed)
{
    m_speed = speed;
}

SetTransportSpeed::SetTransportSpeed(NanoPbMsg &message) : DiscoveryMsg(message)
{
    this->unpack();
}

uint32_t SetTransportSpeed::getSpeed()
{
    return m_speed;
}

void SetTransportSpeed::pack()
{
    whad_discovery_set_speed(this->getMessage(), m_speed);
}

void SetTransportSpeed::unpack()
{
    whad_discovery_set_speed_parse(this->getMessage(), &m_speed);
}