#ifndef __INC_WHAD_DISCOVERY_DOMAININFO_HPP
#define __INC_WHAD_DISCOVERY_DOMAININFO_HPP

#include <string>
#include "message.hpp"
#include "common.hpp"
#include <discovery/base.hpp>

namespace whad::discovery {

    /*! Available domains. */
    enum Domains {
        DomainNone = DOMAIN_NONE,                           /*!< None */
        DomainPhy = DOMAIN_PHY,                             /*!< PHY domain */
        DomainBtClassic = DOMAIN_BT_CLASSIC,                /*!< Bluetooth Classic */
        DomainBtLE = DOMAIN_BTLE,                           /*!< Bluetooth Low Energy */
        DomainDot15d4 = DOMAIN_DOT15D4,                     /*!< IEEE 802.15.4 */
        DomainSixLowPan = DOMAIN_SIXLOWPAN,                 /*!< 6LoWPAN */
        DomainEsb = DOMAIN_ESB,                             /*!< Nordic Semiconductor Enhanced ShockBurst */
        DomainLogitechUnifying = DOMAIN_LOGITECH_UNIFYING,  /*!< Logitech Unifying */
        DomainMosart = DOMAIN_MOSART,                       /*!< Mosart */
        DomainAnt = DOMAIN_ANT,                             /*!< Nordic Semiconductor ANT */
        DomainAntPlus = DOMAIN_ANT_PLUS,                    /*!< Nordic Semiconductor ANT+ */
        DomainAntFs = DOMAIN_ANT_FS,                        /*!< Nordic Semiconductor ANT-FS */
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