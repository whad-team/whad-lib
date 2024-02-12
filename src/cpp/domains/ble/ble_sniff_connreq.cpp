#include <ble/sniff_connreq.hpp>

using namespace whad::ble;

/**
 * @brief   Parse a BleMsg as a SniffConnReq message
 * 
 * @param[in]   message     Message to parse
 */

SniffConnReq::SniffConnReq(BleMsg &message) : BleMsg(message)
{
    this->unpack();
}


/**
 * @brief       SnifConnReq message constructor.
 * 
 * @param[in]   channel     Channel to sniff for connection request
 * @param[in]   targetAddr  Target device BD address
 * @param[in]   showAdv     If set to true, adapter will report every advertisement received
 * @param[in]   showEmpty   If set to true, adapter will report empty PDUs
 **/

SniffConnReq::SniffConnReq(uint32_t channel, BDAddress targetAddr, bool showAdv, bool showEmpty) : BleMsg()
{
    whad_ble_sniff_conn_req(
        this->getRaw(),
        showEmpty,
        showAdv,
        channel,
        targetAddr.getAddressBuf()
    );
}


/**
 * @brief   Pack parameters into a BleMsg
 */

void SniffConnReq::pack()
{
    whad_ble_sniff_conn_req(
        this->getMessage(),
        m_showEmpty,
        m_showAdv,
        m_channel,
        m_targetAddr.getAddressBuf()
    ); 
}


/**
 * @brief   Extract parameters from BleMsg
 */

void SniffConnReq::unpack()
{
    whad_result_t result;
    whad_ble_sniff_connreq_params_t params;

    result = whad_ble_sniff_conn_req_parse(
        this->getMessage(),
        &params
    );

    if (result == WHAD_ERROR)
    {
        throw WhadMessageParsingError();
    }
    else
    {
        /* Extract parameters. */
        m_channel = params.channel;
        m_showAdv = params.show_adv;
        m_showEmpty = params.show_empty_packets;
        m_targetAddr = BDAddress(AddressPublic, params.p_bdaddr);
    }
}


/**
 * @brief   Get channel
 * 
 * @retval  Channel number
 */

uint32_t SniffConnReq::getChannel()
{
    return m_channel;
}


/**
 * @brief   Get target BD address
 * 
 * @retval  Target BD address
 */

BDAddress& SniffConnReq::getTargetAddress()
{
    return m_targetAddr;
}


/**
 * @brief   Determine if advertisements must be reported while sniffing for a
 *          connection request.
 * 
 * @retval  True if advertisements must be reported, false otherwise
 */

bool SniffConnReq::mustReportAdv()
{
    return m_showAdv;
}


/**
 * @brief   Determine if empty PDUs must be reported
 * 
 * @retval  True if empty PDUs must be reported, false otherwise.
 */

bool SniffConnReq::mustReportEmpty()
{
    return m_showEmpty;
}