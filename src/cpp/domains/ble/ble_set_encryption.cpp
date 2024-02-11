#include <ble/set_encryption.hpp>

using namespace whad::ble;

SetEncryption::SetEncryption(BleMsg &message) : BleMsg(message)
{
    this->unpack();
}

/**
 * @brief       SetEncryption message constructor.
 * 
 * @param[in]   connHandle      Connection handle
 * @param[in]   llKey           Link-layer encryption key (16 bytes)
 * @param[in]   llIv            Link-layer encryption initialization vector (8 bytes)
 * @param[in]   key             Encryption key
 * @param[in]   rand            Random buffer used in link-layer key derivation
 * @param[in]   eDiv            Diversifier used in link-layer key derivation
 **/

SetEncryption::SetEncryption(uint32_t connHandle, uint8_t llKey[16],
                                  uint8_t llIv[8], uint8_t key[16], uint8_t rand[8],
                                  uint8_t eDiv[2], bool enabled) : BleMsg()
{
    /* Save properties. */
    m_connHandle = connHandle;
    m_enabled = enabled;
    memcpy(m_LLKey, llKey, 16);
    memcpy(m_llIv, llIv, 8);
    memcpy(m_key, key, 16);
    memcpy(m_rand, rand, 8);
    memcpy(m_eDiv, eDiv, 2);
}


/**
 * @brief   Pack parameters into a BleMsg
 */

void SetEncryption::pack()
{
    whad_ble_set_encryption(
        this->getMessage(),
        m_connHandle,
        m_enabled,
        m_LLKey,
        m_llIv,
        m_key,
        m_rand,
        m_eDiv
    );
}


/**
 * @brief       Extract parameters from a BleMsg
 **/

void SetEncryption::unpack()
{
    whad_ble_encryption_params_t params;

    /* Parse SetEncryption message. */
    if (whad_ble_set_encryption_parse(this->getRaw(), &params) == WHAD_SUCCESS)
    {
        this->m_connHandle = params.conn_handle;
        this->m_enabled = params.enabled;
        memcpy(this->m_LLKey, params.p_ll_key, 16);
        memcpy(this->m_llIv, params.p_ll_iv, 8);
        memcpy(this->m_key, params.p_key, 16);
        memcpy(this->m_rand, params.p_rand, 8);
        memcpy(this->m_eDiv, params.p_ediv, 2);
    }
    else
    {
        throw WhadMessageParsingError();
    }
}


/**
 * @brief   Get connection handle
 * 
 * @return  Connection handle value.
 **/

uint32_t SetEncryption::getConnHandle()
{
    return this->m_connHandle;
}


/**
 * @brief   Determine if encryption must be enabled or not.
 * 
 * @return  True if encryption must be enabled, false otherwise.
 **/

bool SetEncryption::isEnabled()
{
    return this->m_enabled;
}


/**
 * @brief   Get the key 16-byte buffer
 * 
 * @return  Pointer to the key buffer.
 **/

uint8_t *SetEncryption::getKey()
{
    return this->m_key;
}


/**
 * @brief   Get the key 8-byte Rand buffer
 * 
 * @return  Pointer to the Rand buffer.
 **/

uint8_t *SetEncryption::getRand()
{
    return this->m_rand;
}


/**
 * @brief   Get the link-layer 16-byte encryption key buffer
 * 
 * @return  Pointer to the link-layer encryption key buffer.
 **/

uint8_t *SetEncryption::getLLKey()
{
    return this->m_LLKey;
}


/**
 * @brief   Get the link-layer 8-byte IV buffer
 * 
 * @return  Pointer to the link-layer encryption IV buffer.
 **/

uint8_t *SetEncryption::getLLIv()
{
    return this->m_llIv;
}


/**
 * @brief   Get the encryption diversifier.
 * 
 * @return  Pointer to the encryption diversifier buffer.
 **/

uint8_t *SetEncryption::getEDiv()
{
    return this->m_eDiv;
}