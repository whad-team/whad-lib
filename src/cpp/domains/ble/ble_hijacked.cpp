#include <ble/hijacked.hpp>

using namespace whad::ble;

/**
 * @brief       Notify a successful/unsuccessful connection hijacking
 * 
 * @param[in]   accessAddress       Connection access address
 * @param[in]   success             If true hijacking was successful, unsuccessful otherwise 
 **/

Hijacked::Hijacked(uint32_t accessAddress, bool success) : BleMsg()
{
    whad_ble_hijacked(
        this->getMessage(),
        accessAddress,
        success
    );
}