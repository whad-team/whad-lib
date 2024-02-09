#include <ble/injected.hpp>

using namespace whad::ble;

Injected::Injected(BleMsg &message) : BleMsg(message)
{
    this->unpack();
}

/**
 * @brief       Notify a successful/unsuccessful PDU injection
 * 
 * @param[in]   accessAddress       Connection access address
 * @param[in]   attempts            Number of attempts
 * @param[in]   success             If true injection was successful, unsuccessful otherwise 
 **/

Injected::Injected(uint32_t accessAddress, uint32_t attempts, bool success) : BleMsg()
{
    m_accessAddr = accessAddress;
    m_attempts = attempts;
    m_success = success;
}


/**
 * @brief   Retrieve the access address
 * 
 * @retval  Access address
 */

uint32_t Injected::getAccessAddress()
{
    return m_accessAddr;
}


/**
 * @brief   Retrieve the number of attempts
 * 
 * @retval  Number of attempts
 */

uint32_t Injected::getAttempts()
{
    return m_attempts;
}


/**
 * @brief   Determine if the injection attack has been successful
 * 
 * @retval  True if sucessful, false otherwise
 */

bool Injected::isSuccessful()
{
    return m_success;
}


/**
 * @brief   Pack parameters into a BleMsg
 */

void Injected::pack()
{
    whad_ble_injected(
        this->getMessage(),
        m_accessAddr,
        m_attempts,
        m_success
    ); 
}


/**
 * @brief   Extract parameters from BleMsg
 */

void Injected::unpack()
{
    whad_result_t result;
    whad_ble_injected_params_t params;

    result = whad_ble_injected_parse(
        this->getMessage(),
        &params
    );

    if (result == WHAD_ERROR)
    {
        throw WhadMessageParsingError();
    }
    else
    {
        /* Save parameters. */
        m_accessAddr = params.access_address;
        m_attempts = params.attempts;
        m_success = params.success;
    }
}