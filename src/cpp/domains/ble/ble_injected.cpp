#include <ble/injected.hpp>

using namespace whad::ble;

/**
 * @brief       Notify a successful/unsuccessful PDU injection
 * 
 * @param[in]   accessAddress       Connection access address
 * @param[in]   attempts            Number of attempts
 * @param[in]   success             If true injection was successful, unsuccessful otherwise 
 **/

Injected::Injected(uint32_t accessAddress, uint32_t attempts, bool success) : BleMsg()
{
    whad_ble_injected(
        this->getMessage(),
        accessAddress,
        attempts,
        success
    );
}