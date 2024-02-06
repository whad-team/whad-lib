#include <discovery/domaininfo.hpp>

using namespace whad::discovery;


/***********************
 * Domain helper
 ***********************/

bool whad::discovery::isDomainSupported(const whad_domain_desc_t *capabilities, Domains domain)
{
    return whad_discovery_is_domain_supported(capabilities, (whad_domain_t)domain);
}

/**
 * Domain information query
 */

/**
 * @brief   Create a DomainInfoQuery with a specific domain.
 * 
 * @param   domain  Domain to query
 */

DomainInfoQuery::DomainInfoQuery(Domains domain) : DiscoveryMsg()
{
    m_domain = domain;
}


/**
 * @brief Parse a DomainInfoQuery from a DiscoveryMsg.
 * 
 * @param   message     Original DiscoveryMsg to parse as a DomainInfoQuery
 */

DomainInfoQuery::DomainInfoQuery(DiscoveryMsg &message) : DiscoveryMsg(message)
{
    this->unpack();
}


/**
 * @brief   Retrieve the current domain
 */

Domains DomainInfoQuery::getDomain()
{
    return m_domain;
}


/**
 * @brief   Callback method used to pack all parameters in the underlying NanoPb
 *          message.
 */
void DomainInfoQuery::pack()
{
    whad_domain_t domain = (whad_domain_t)m_domain;
    whad_discovery_domain_info_query(this->getMessage(), domain);
}


/**
 *  @brief  Unpack a DomainInfoQuery from the underlying NanoPb message.  
 */

void DomainInfoQuery::unpack()
{
    whad_domain_t domain;

    if (whad_discovery_domain_info_query_parse(this->getMessage(), &domain) == WHAD_ERROR)
    {
        throw WhadMessageParsingError();
    }

    /* Save domain. */
    m_domain = (Domains)domain;
}


/**
 * Domain information response
 * 
 * TODO: try to expose a vector of capabilities (or hashmap ?)
 */

/**
 * @brief   Build a domain information response.
 * 
 * This message must be sent in response to a Domain Information request sent by the host
 * to provide the supported capabilities.
 * 
 * @param   domain          The target domain queried by the host
 * @param   capabilities    The device's capabilities structure
 **/

DomainInfoResp::DomainInfoResp(Domains domain, whad_domain_desc_t *capabilities) : DiscoveryMsg()
{
    whad_discovery_domain_info_resp(this->getRaw(), (whad_domain_t)domain, capabilities);
}
