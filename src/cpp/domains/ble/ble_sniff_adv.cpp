#include <ble/sniff_adv.hpp>

using namespace whad::ble;

/**
 * @brief       SniffAdv message constructor.
 * 
 * @param[in]   channel     Channel to use for sniffing
 * @param[in]   targetAddr  Target device BD address
 * @param[in]   useExtAdv   If set to true, use extended advertising (BLE 5.x)
 **/

SniffAdv::SniffAdv(uint32_t channel, BDAddress targetAddr, bool useExtAdv) : BleMsg()
{
    whad_ble_sniff_adv(
        this->getRaw(),
        useExtAdv,
        channel,
        targetAddr.getAddressBuf()
    );
}


/**
 * @brief       SniffAdv message constructor.
 * 
 * @param[in]   channel     Channel to use for sniffing
 * @param[in]   targetAddr  Target device BD address
 * @param[in]   useExtAdv   If set to true, use extended advertising (BLE 5.x)
 **/

SniffAdv::SniffAdv(NanoPbMsg message) : BleMsg(message)
{
    whad_ble_sniff_adv_params_t params;
    this->m_channel = 0;
    this->m_useExtAdv = false;

    if (whad_ble_sniff_adv_parse(this->getRaw(), &params) == WHAD_SUCCESS)
    {
        this->m_channel = params.channel;
        this->m_useExtAdv = params.use_ext_adv;
        this->m_targetAddr.setAddress(params.p_bdaddr);
    }
}


/**
 * @brief   Get advertising channel.
 * 
 * @return  Advertising channel number. 
 **/

uint32_t SniffAdv::getChannel(void)
{
    return this->m_channel;
}


/**
 * @brief   Determine if we must use extended advertisements.
 * 
 * @return  True if extended advertisements must be used, false otherwise. 
 **/

bool SniffAdv::mustUseExtAdv(void)
{
    return this->m_useExtAdv;
}


/**
 * @brief   Get the target BD address.
 * 
 * @return  BD address of the target device to sniff.
 **/

BDAddress SniffAdv::getAddress(void)
{
    return this->m_targetAddr;
}