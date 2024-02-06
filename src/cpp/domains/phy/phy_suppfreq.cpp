#include "phy/suppfreq.hpp"

using namespace whad::phy;

/**
 * @brief       Create a SupportedFreqs message with the provided frequency ranges.
 * 
 * @param[in]   pFreqRanges     Pointer to an array containing the supported frequency ranges
 * @param[in]   nRanges         Number of supported frequency ranges
 **/

SupportedFreqsResp::SupportedFreqsResp(const whad_phy_frequency_range_t *pFreqRanges) : PhyMsg()
{
    int nRanges = 0;

    /* Count ranges (last range must be {0,0}). */
    for (nRanges=0; (pFreqRanges[nRanges].start != 0) && (pFreqRanges[nRanges].end != 0); nRanges++);

    whad_phy_supported_frequencies(
        this->getRaw(),
        (whad_phy_frequency_range_t *)pFreqRanges,
        nRanges
    );
}


/**
 * @brief       parse a supported frequency ranges message
 * 
 * @param[in]   message     Base NanoPb message to use.
 **/

SupportedFreqsResp::SupportedFreqsResp(NanoPbMsg &message) : PhyMsg(message)
{
}