#include <ble/sniff_adv.hpp>

using namespace whad::ble;

/**
 * @brief   Parse a BleMsg as a SniffAdv message
 * 
 * @param[in]   message     Message to parse
 */

SniffAdv::SniffAdv(BleMsg &message) : BleMsg(message)
{
    this->unpack();
}


/**
 * @brief       SniffAdv message constructor.
 * 
 * @param[in]   channel     Channel to use for sniffing
 * @param[in]   targetAddr  Target device BD address
 * @param[in]   useExtAdv   If set to true, use extended advertising (BLE 5.x)
 **/

SniffAdv::SniffAdv(uint32_t channel, BDAddress targetAddr, bool useExtAdv) : BleMsg()
{
    m_channel = channel;
    m_targetAddr = targetAddr;
    m_useExtAdv = useExtAdv;
}


/**
 * @brief   Pack parameters into a BleMsg
 */

void SniffAdv::pack()
{
    whad_ble_sniff_adv(
        this->getMessage(),
        m_useExtAdv,
        m_channel,
        m_targetAddr.getAddressBuf()
    );  
}


/**
 * @brief   Extract parameters from BleMsg
 */

void SniffAdv::unpack()
{
    whad_ble_sniff_adv_params_t params;
    m_channel = 0;
    m_useExtAdv = false;

    if (whad_ble_sniff_adv_parse(this->getMessage(), &params) == WHAD_SUCCESS)
    {
        m_channel = params.channel;
        m_useExtAdv = params.use_ext_adv;
        m_targetAddr.setAddress(params.p_bdaddr);
    }
    else
    {
        throw WhadMessageParsingError();
    }
}


/**
 * @brief   Get advertising channel.
 * 
 * @return  Advertising channel number. 
 **/

uint32_t SniffAdv::getChannel(void)
{
    return m_channel;
}


/**
 * @brief   Determine if we must use extended advertisements.
 * 
 * @return  True if extended advertisements must be used, false otherwise. 
 **/

bool SniffAdv::mustUseExtAdv(void)
{
    return m_useExtAdv;
}


/**
 * @brief   Get the target BD address.
 * 
 * @return  BD address of the target device to sniff.
 **/

BDAddress SniffAdv::getAddress(void)
{
    return m_targetAddr;
}