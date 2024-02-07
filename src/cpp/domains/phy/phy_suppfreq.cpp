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
    m_freqRanges = pFreqRanges;
}


/**
 * @brief       parse a supported frequency ranges message
 * 
 * @param[in]   message     Base PhyMsg message to use.
 **/

SupportedFreqsResp::SupportedFreqsResp(PhyMsg &message) : PhyMsg(message)
{
    /* Not yet supported. */
}


/**
 * @brief   Pack parameters into a PhyMsg.
 */

void SupportedFreqsResp::pack()
{
    int nRanges = 0;

    /* Count ranges (last range must be {0,0}). */
    for (nRanges=0; (m_freqRanges[nRanges].start != 0) && (m_freqRanges[nRanges].end != 0); nRanges++);

    whad_phy_supported_frequencies(
        this->getMessage(),
        (whad_phy_frequency_range_t *)m_freqRanges,
        nRanges
    );   
}
