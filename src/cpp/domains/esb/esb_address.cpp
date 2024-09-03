#include <esb/address.hpp>

using namespace whad::esb;

static EsbAddress PromiscAddr(WHAD_ESB_ADDR_ANY, 5);
static EsbAddress NullAddr((uint8_t *)"\x00\x00\x00\x00\x00", 5);


/**
 * @brief   BD Address default constructor.
 **/

EsbAddress::EsbAddress(void)
{
    memset(this->m_address, 0, 5);
    this->m_size = 0;
}


/**
 * @brief   ESB Address constructor.
 * 
 * @param[in]   pAddress    ESB address byte buffer (5 bytes max)
 * @param[in]   size        Address size in bytes
 **/

EsbAddress::EsbAddress(uint8_t *pAddress, uint8_t size)
{
    if (size <= 5)
    {
        this->m_size = size;
        memcpy(this->m_address, pAddress, size);
    }
}


/**
 * @brief   Get address length.
 * 
 * @retval  int   Address length in bytes
 **/

uint8_t EsbAddress::getLength(void)
{
    return this->m_size;
}


/**
 * @brief   Get address buffer.
 * 
 * @return  Pointer to the BD address byte buffer (6 bytes)
 **/

uint8_t *EsbAddress::getAddressBuf(void)
{
    return this->m_address;
}


/**
 * @brief   Set ESB address.
 * 
 * @param[in]   pAddress    Pointer to a 6-byte BD address buffer
 * @param[in]   size        Address size in bytes (0-5 bytes)
 **/

void EsbAddress::setAddress(uint8_t *pAddress, uint8_t size)
{
    if (pAddress == NULL)
    {
        memset(this->m_address, 0, 5);
        this->m_size = 0;
    }

    if (size <= 5)
    {
        /* Copy BD address. */
        memcpy(this->m_address, pAddress, size);
        this->m_size = size;
    }
}
