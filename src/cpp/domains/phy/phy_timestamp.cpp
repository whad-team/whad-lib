#include "phy/timestamp.hpp"

using namespace whad::phy;

/**
 * @brief       Create a timestamp with a precision to the microsecond
 * 
 * @param[in]   sec     Number of seconds
 * @param[in]   usec    Number of microseconds
 */

Timestamp::Timestamp(uint32_t sec, uint32_t usec)
{
    this->m_sec = sec;
    this->m_usec = usec;
}


/**
 * @brief   Get the number of seconds from a timestamp.
 * 
 * @retval  Number of seconds
 */

uint32_t Timestamp::getSeconds()
{
    return this->m_sec;
}


/**
 * @brief   Get the number of microseconds from a timestamp.
 * 
 * @retval  Number of microseconds
 */

uint32_t Timestamp::getMicroseconds()
{
    return this->m_usec;
}