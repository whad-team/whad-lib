#include <phy/fskmod.hpp>

using namespace whad::phy;

/**
 * @brief   Default constructor.
 */

FskMod::FskMod()
{
    m_deviation = 0;
}


/**
 * @brief   Constructor.
 * 
 * @param[in]   deviation   FSK deviation in Hz
 */

FskMod::FskMod(uint32_t deviation)
{
    m_deviation = deviation;
}


/**
 * @brief   Get deviation
 * 
 * @retval  Deviation in Hz
 */

uint32_t FskMod::getDeviation()
{
    return m_deviation;
}