#include <ble/set_encryption.hpp>

using namespace whad::ble;

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
    this->m_connHandle = connHandle;
    this->m_enabled = enabled;
    memcpy(this->m_LLKey, llKey, 16);
    memcpy(this->m_llIv, llIv, 8);
    memcpy(this->m_key, key, 16);
    memcpy(this->m_rand, rand, 8);
    memcpy(this->m_eDiv, eDiv, 2);

    /* Fill the NanoPb message with the correct values. */
    whad_ble_set_encryption(
        this->getRaw(),
        connHandle,
        enabled,
        llKey,
        llIv,
        key,
        rand,
        eDiv
    );
}


/**
 * @brief       SetEncryption message constructor.
 * 
 * @param[in]   message         NanoPb message to use
 **/

SetEncryption::SetEncryption(NanoPbMsg message) : BleMsg(message)
{
    whad_ble_encryption_params_t params;

    /* Set our properties to default values. */
    this->m_connHandle = 0;
    this->m_enabled = false;
    memset(this->m_LLKey, 0, 16);
    memset(this->m_llIv, 0, 8);
    memset(this->m_key, 0, 16);
    memset(this->m_rand, 0, 8);
    memset(this->m_eDiv, 0, 2);

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

    /* TODO: trigger an exception if parsing fails. */
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