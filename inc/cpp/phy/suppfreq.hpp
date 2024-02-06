#ifndef __INC_WHAD_PHY_SUPPFREQ_HPP
#define __INC_WHAD_PHY_SUPPFREQ_HPP

#include <string>
#include <vector>
#include "message.hpp"
#include "common.hpp"
#include "../domains/phy.h"
#include <phy/base.hpp>

namespace whad::phy {

    class SupportedFreqsResp : public PhyMsg
    {
        public:
            SupportedFreqsResp(NanoPbMsg &message);
            SupportedFreqsResp(const whad_phy_frequency_range_t *pFreqRanges);
    };

}

#endif /* __INC_WHAD_PHY_SUPPFREQ_HPP */