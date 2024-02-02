#include "cpp/common.hpp"

using namespace whad;

/******************************************
 * Generic Whad Exceptions
 ******************************************/

WhadInvalidSize::WhadInvalidSize() : WhadException()
{
    /* No size provided. */
    m_size = -1;
}

WhadInvalidSize::WhadInvalidSize(int size, int expectedSize) : WhadException()
{
    m_size = size;
    m_expectedSize = expectedSize;
}

int WhadInvalidSize::getExpectedSize()
{
    return m_expectedSize;
}

int WhadInvalidSize::getSize()
{
    return m_size;
}
