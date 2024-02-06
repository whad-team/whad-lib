#include "phy/syncword.hpp"

using namespace whad::phy;

SyncWord::SyncWord(uint8_t *syncword, uint8_t size)
{
    if (size <= 10)
    {
        memcpy(this->m_syncword, syncword, size);
        this->m_size = size;
    }
}

uint8_t *SyncWord::get()
{
    return this->m_syncword;
}

uint8_t SyncWord::getSize()
{
    return this->m_size;
}