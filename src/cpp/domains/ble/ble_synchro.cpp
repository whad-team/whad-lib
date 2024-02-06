#include <ble/synchro.hpp>

using namespace whad::ble;

/**
 * @brief       Notify a successful connection synchronization
 * 
 * @param[in]   accessAddress       Connection access address
 * @param[in]   crcInit             Recovered CRC initial value (seed)
 * @param[in]   hopInterval         Recovered hop interval
 * @param[in]   hopIncrement        Recovered hop increment
 * @param[in]   channelMap          Recovered channel map
 **/

Synchronized::Synchronized(uint32_t accessAddress, uint32_t crcInit, uint32_t hopInterval,
                                 uint32_t hopIncrement, ChannelMap channelMap) : BleMsg()
{
    whad_ble_synchronized(
        this->getRaw(),
        accessAddress,
        crcInit,
        hopInterval,
        hopIncrement,
        channelMap.getChannelMapBuf()
    );
}


/**
 * @brief       Notify a connection desynchronization
 * 
 * @param[in]   accessAddress       Connection access address
 **/

Desynchronized::Desynchronized(uint32_t accessAddress) : BleMsg()
{
    whad_ble_desynchronized(
        this->getRaw(),
        accessAddress
    );
}