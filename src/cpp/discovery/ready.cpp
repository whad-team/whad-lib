#include <discovery/ready.hpp>

using namespace whad::discovery;

/**
 * @brief   Build a discovery ready response message.
 * 
 * This message must be sent in response to a Reset query from the host,
 * to acknowledge the fact the device has been reset and is ready to process
 * incoming commands.
 **/

ReadyResp::ReadyResp() : DiscoveryMsg()
{
}


/**
 * @brief   Callback method that packs all the data into a NanoPb
 *          message.
 */

void ReadyResp::pack()
{
    whad_discovery_ready_resp(this->getMessage());
}