#include "ble/address.hpp"

using namespace whad::ble;

/**
 * @brief   BD Address default constructor.
 **/

BDAddress::BDAddress(void)
{
    this->m_type = whad::ble::AddressType::AddressPublic;
    memset(this->m_address, 0, 6);
}


/**
 * @brief   BD Address constructor.
 * 
 * @param[in]   type        Address type
 * @param[in]   p_bdaddr    BD address byte buffer (6 bytes)
 **/

BDAddress::BDAddress(AddressType type, uint8_t *p_bdaddr)
{
    this->m_type = type;
    memcpy(this->m_address, p_bdaddr, 6);
}


/**
 * @brief   Get address type.
 * 
 * @retval  AddressPublic   Address type is public
 * @retval  AddressRandom   Address type is random
 **/

AddressType BDAddress::getType(void)
{
    return this->m_type;
}


/**
 * @brief   Set address type.
 * 
 * @param[in]   type    Address type to set
 **/

void BDAddress::setType(AddressType type)
{
    this->m_type = type;
}


/**
 * @brief   Get address buffer.
 * 
 * @return  Pointer to the BD address byte buffer (6 bytes)
 **/

uint8_t *BDAddress::getAddressBuf(void)
{
    return this->m_address;
}


/**
 * @brief   Set BD address.
 * 
 * @param[in]   pBdAddress    Pointer to a 6-byte BD address buffer
 **/

void BDAddress::setAddress(uint8_t *pBdAddress)
{
    /* Copy BD address. */
    memcpy(this->m_address, pBdAddress, 6);
}
