#include <ble/pattern_trigger.hpp>

using namespace whad::ble;

/**
 * @brief       PatternTrigger constructor
 * 
 * @param[in]   pPattern        Byte buffer containing the byte pattern to match
 * @param[in]   pMask           Byte buffer containing a bitmask to apply with the pattern
 * @param[in]   length          Pattern and mask size in bytes
 * @param[in]   offset          Offset at which the pattern must be applied
 **/

PatternTrigger::PatternTrigger(uint8_t *pPattern, uint8_t *pMask, int length, uint32_t offset)
{
    this->m_pattern = pPattern;
    this->m_mask = pMask;
    this->m_length = length;
    this->m_offset = offset;
}


/**
 * @brief       Get pattern and mask length
 * 
 * @return      Pattern and mask length in bytes
 **/

int PatternTrigger::getLength(void)
{
    return this->m_length;
}


/**
 * @brief       Get trigger pattern
 * 
 * @return      Pointer to the trigger's pattern byte buffer
 **/

uint8_t *PatternTrigger::getPattern(void)
{
    return this->m_pattern;
}


/**
 * @brief       Get trigger mask
 * 
 * @return      Pointer to the trigger's mask byte buffer
 **/

uint8_t *PatternTrigger::getMask(void)
{
    return this->m_mask;
}


/**
 * @brief       Get trigger pattern offset
 * 
 * @return      Pattern offset
 **/

uint32_t PatternTrigger::getOffset(void)
{
    return this->m_offset;
}
