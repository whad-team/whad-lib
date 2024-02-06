#include "ble/conn_evt_trigger.hpp"

using namespace whad::ble;

/**
 * @brief       Connection Event trigger constructor
 * 
 * @param[in]   connEvent       Connection event at which a set of packets must be sent
 **/

ConnEventTrigger::ConnEventTrigger(uint32_t connEvent)
{
    this->m_connEvent = connEvent;
}


/**
 * @brief       Get trigger connection event
 * 
 * @return      Connection event
 **/

uint32_t ConnEventTrigger::getConnEvent(void)
{
    return this->m_connEvent;
}
