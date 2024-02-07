#include <discovery/speed.hpp>

using namespace whad::discovery;

/**
 * @brief       Create a SetTransportSpeed message from a discovery message.
 * 
 * @param[in]   speed Transport speed to use (in bauds)
 */

SetTransportSpeed::SetTransportSpeed(uint32_t speed)
{
    m_speed = speed;
}


/**
 * @brief       Create a SetTransportSpeed message from a discovery message.
 * 
 * @param[in]   message Discovery message to parse as a SetTransportSpeed message.
 */

SetTransportSpeed::SetTransportSpeed(DiscoveryMsg &message) : DiscoveryMsg(message)
{
    this->unpack();
}


/**
 * @brief   Get transport speed.
 * 
 * @retval  Transport speed in bauds.
 */

uint32_t SetTransportSpeed::getSpeed()
{
    return m_speed;
}


/**
 * @brief   Message pack callback, create the corresponding NanoPb message.
 */

void SetTransportSpeed::pack()
{
    whad_discovery_set_speed(this->getMessage(), m_speed);
}


/**
 * @brief   Message unpack, extract speed from discovery message.
 */

void SetTransportSpeed::unpack()
{
    whad_discovery_set_speed_parse(this->getMessage(), &m_speed);
}