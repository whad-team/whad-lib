#include "phy/syncword.hpp"

using namespace whad::phy;

SyncWord::SyncWord()
{
    memset(m_syncword, 0, 10);
    m_size = 0;
}

SyncWord::SyncWord(uint8_t *syncword, uint8_t size)
{
    if (size <= 10)
    {
        memcpy(this->m_syncword, syncword, size);
        m_size = size;
    }
}

uint8_t *SyncWord::get()
{
    return m_syncword;
}

uint8_t SyncWord::getSize()
{
    return m_size;
}