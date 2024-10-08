#include "phy/timestamp.hpp"

using namespace whad::phy;


/**
 * @brief       Create a null timestamp
 */

Timestamp::Timestamp()
{
    this->m_sec = 0;
    this->m_usec = 0;
}

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
 * @brief   Set the number of seconds
 * 
 * @param[in]   seconds Number of seconds
 */

void Timestamp::setSeconds(uint32_t seconds)
{
    m_sec = seconds;
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


/**
 * @brief   Set the number of microseconds
 * 
 * @param[in]   microseconds    Number of microseconds
 */

void Timestamp::setMicroseconds(uint32_t microseconds)
{
    m_usec = microseconds;
}

/**
 * @brief   Set the timestamp value.
 * 
 * @param[in]   sec     Number of seconds
 * @param[in]   usec    Number of microseconds
 */

void Timestamp::set(uint32_t sec, uint32_t usec)
{
    m_sec = sec;
    m_usec = usec;
}