#include <ble/setbdaddr.hpp>

using namespace whad::ble;

/**
 * @brief       Set adapter BD address message constructor.
 * 
 * @param[in]   address     BD address to use
 **/

SetBdAddress::SetBdAddress(BDAddress address) : BleMsg()
{
    whad_ble_set_bdaddress(
        this->getRaw(),
        (whad_ble_addrtype_t)address.getType(),
        address.getAddressBuf()
    );
}


/**
 * @brief       parse a BD address message constructor.
 * 
 * @param[in]   message     Base NanoPb message to use.
 **/

SetBdAddress::SetBdAddress(NanoPbMsg message) : BleMsg(message)
{
}


/**
 * @brief   Retrieve the BD address.
 * 
 * @return  An instance of BDAddress on success, NULL otherwise.
 **/

BDAddress *SetBdAddress::getAddress()
{
    whad_ble_addrtype_t addrType;
    uint8_t bdAddress[6];

    /* Parse the underlying message to extract BD address. */
    if (whad_ble_set_bdaddress_parse(this->getRaw(), &addrType, bdAddress) == WHAD_SUCCESS)
    {
        /* Parsing ok, return BD address. */
        return new BDAddress((whad::ble::AddressType)addrType, (uint8_t *)bdAddress);
    }

    /* Fail. */
    return NULL;
}