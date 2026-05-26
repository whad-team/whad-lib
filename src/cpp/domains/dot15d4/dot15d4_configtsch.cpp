#include <dot15d4/configtsch.hpp>

using namespace whad::dot15d4;

/**
 * @brief   Parse a message as a ConfigureTSCH message.
 */

ConfigureTSCH::ConfigureTSCH(Dot15d4Msg &message) : Dot15d4Msg(message)
{
    this->unpack();
}


/**
 * @brief       ConfigureTSCH message constructor.
 * 
 * @param[in]   enabled         Indicate if the TSCH mode must be enabled or not.
 **/

ConfigureTSCH::ConfigureTSCH(bool enabled) : Dot15d4Msg()
{
    /* Save enabled indicator. */
    m_enabled = enabled;
}


/**
 * @brief   Pack parameters into a Dot15d4Msg object
 */

void ConfigureTSCH::pack()
{
    /* Construct the configure TSCH structure. */
    whad_dot15d4_config_tsch(
        this->getMessage(),
        m_enabled
    );
}


/**
 * @brief   Extract parameters from a Dot15d4Msg
 */

void ConfigureTSCH::unpack()
{
    whad_result_t result;
    
    bool enabled; 
    result = whad_dot15d4_config_tsch_parse(
        this->getMessage(),
        &enabled
    );

    if (result == WHAD_ERROR)
    {
        /* Error occured during parsing. */
        throw WhadMessageParsingError();
    }
    else
    {
        /* Save parameters. */
        m_enabled = enabled;
    }
}


/**
 * @brief   Retrieve the enabled boolean indicator
 * 
 * @retval  Enabled boolean indicator
 */

bool ConfigureTSCH::getEnabled()
{
    return m_enabled;
}