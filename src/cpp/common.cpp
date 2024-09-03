#include "cpp/common.hpp"

using namespace whad;

/******************************************
 * Generic Whad Exceptions
 ******************************************/

/**
 * @brief   WHAD Invalid size exception constructor.
 */

WhadInvalidSize::WhadInvalidSize() : WhadException()
{
    /* No size provided. */
    m_size = -1;
}


/**
 * @brief   WHAD Invalid size exception constructor.
 * 
 * @param[in]   size            Current data size
 * @param[in]   expectedSize    Expected data size
 */

WhadInvalidSize::WhadInvalidSize(int size, int expectedSize) : WhadException()
{
    m_size = size;
    m_expectedSize = expectedSize;
}


/**
 * @brief   Get expected size
 * 
 * @return  Expected size in bytes
 */

int WhadInvalidSize::getExpectedSize()
{
    return m_expectedSize;
}


/**
 * @brief   Get current size
 * 
 * @return  Current data size in bytes
 */

int WhadInvalidSize::getSize()
{
    return m_size;
}
