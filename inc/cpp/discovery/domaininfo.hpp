#ifndef __INC_WHAD_DISCOVERY_DOMAININFO_HPP
#define __INC_WHAD_DISCOVERY_DOMAININFO_HPP

#include <string>
#include "message.hpp"
#include "common.hpp"
#include <discovery/discovery.hpp>

namespace whad::discovery {

    /* Available domains. */
    enum Domains {
        DomainNone = DOMAIN_NONE,
        DomainPhy = DOMAIN_PHY,
        DomainBtClassic = DOMAIN_BT_CLASSIC,
        DomainBtLE = DOMAIN_BTLE,
        DomainZigbee = DOMAIN_ZIGBEE,
        DomainSixLowPan = DOMAIN_SIXLOWPAN,
        DomainEsb = DOMAIN_ESB,
        DomainLogitechUnifying = DOMAIN_LOGITECH_UNIFYING,
        DomainMosart = DOMAIN_MOSART,
        DomainAnt = DOMAIN_ANT,
        DomainAntPlus = DOMAIN_ANT_PLUS,
        DomainAntFs = DOMAIN_ANT_FS,
    };

    bool isDomainSupported(const whad_domain_desc_t *capabilities, Domains domain);

    /* Device domain information query. */
    class DomainInfoQuery : public DiscoveryMsg
    {
        public:
            /* Constructor. */
            DomainInfoQuery(DiscoveryMsg &message);
            DomainInfoQuery(Domains domain);

            /* Accessors. */
            Domains getDomain();

        private:
            void pack();
            void unpack();

            Domains m_domain;
    };

    /* Domain information response. */
    class DomainInfoResp : public DiscoveryMsg
    {
        public:
            DomainInfoResp(Domains domain, whad_domain_desc_t *capabilities);
    };
}

#endif /* __INC_WHAD_DISCOVERY_INFOQUERY_HPP */