#include <discovery/devreset.hpp>

using namespace whad::discovery;


/**
 * @brief   Build a device reset message.
 **/

DeviceReset::DeviceReset() : DiscoveryMsg()
{
}


/**
 * @brief       Build a device reset message from a NanoPb message.
 * 
 * @param[in]   message     message to wrap as a DeviceReset message
 **/

DeviceReset::DeviceReset(NanoPbMsg &message) : DiscoveryMsg(message)
{
}


/**
 * @brief   Pack the message into a NanoPb message.
 */

void DeviceReset::pack()
{
    /* Craft the corresponding NanoPb message. */
    whad_discovery_device_reset(this->getMessage());
}