#include <ble/jam_reactive.hpp>

using namespace whad::ble;

/**
 * @brief       ReactiveJam message constructor.
 * 
 * @param[in]   channel         Channel to listen on
 * @param[in]   pPattern        Byte buffer containing the byte pattern to match
 * @param[in]   length          Pattern length in bytes
 * @param[in]   position        Start position for pattern search
 **/

ReactiveJam::ReactiveJam(uint32_t channel, uint8_t *pPattern, int length, uint32_t position) : BleMsg()
{
    whad_ble_reactive_jam(this->getRaw(), channel, pPattern, length, position);
}