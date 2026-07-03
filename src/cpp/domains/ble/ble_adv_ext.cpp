#include "ble/adv_ext.hpp"

using namespace whad::ble;

AuxPtr::AuxPtr() : m_channel(0), m_ca(0), m_offsetUnits(0), m_offset(0), m_phy(0)
{
}

AuxPtr::AuxPtr(uint8_t channel, uint8_t ca, uint8_t offset_units, uint16_t offset, Phy phy) : 
    m_channel(channel), m_ca(ca), m_offsetUnits(offset_units), m_offset(offset)
{
    switch (phy) {
        default:
        case Phy::LE1Mbit:
            m_phy = 0;
            break;

        case Phy::LE2Mbit:
            m_phy = 1;
            break;

        case Phy::LE1MbitCoded:
            m_phy = 2;
            break;
    }
}

uint8_t AuxPtr::getChannel()
{
    return m_channel;
}

uint8_t AuxPtr::getCA()
{
    return m_ca;
}

uint8_t AuxPtr::getOffsetUnits()
{
    return m_offsetUnits;
}

uint16_t AuxPtr::getOffset()
{
    return m_offset & 0x1fff;
}

Phy AuxPtr::getPhy()
{
    Phy result = Phy::Undefined;

    switch (m_phy)
    {
        case 0:
            result = Phy::LE1Mbit;
            break;

        case 1:
            result = Phy::LE2Mbit;
            break;

        case 2:
            result = Phy::LE1MbitCoded;
            break;

        default:
            result = Phy::Undefined;
            break;
    }

    return result;
}

void AuxPtr::copyTo(whad_ble_auxptr_t *p_struct)
{
    p_struct->channel = getChannel();
    p_struct->ca = getCA();
    p_struct->offset_units = getOffsetUnits();
    p_struct->offset = getOffset();
    p_struct->phy = (whad_ble_phy_t)getPhy();
}

ExtAdvPdu::ExtAdvPdu()
{
    m_advLen = 0;
    m_pAuxPtr = NULL;
}

ExtAdvPdu::ExtAdvPdu(uint8_t *p_advData, size_t length)
{
    /* Copy advertising data length. */
    m_advLen = length;
    
    /* Copy advertising data but check cap m_advLen before. */
    if (m_advLen > (254 + 64))
    {
        m_advLen = 254 + 64;
    }
    memcpy(m_advData, p_advData, m_advLen);

    /* No AuxPtr. */
    m_pAuxPtr = NULL;
}

ExtAdvPdu::ExtAdvPdu(uint8_t *p_advData, size_t length, AuxPtr *auxptr) : ExtAdvPdu(p_advData, length)
{
    m_pAuxPtr = auxptr;
}

size_t ExtAdvPdu::getLength()
{
    return m_advLen;
}

AuxPtr* ExtAdvPdu::getAuxPtr()
{
    return m_pAuxPtr;
}

uint8_t* ExtAdvPdu::getData()
{
    return m_advData;
}

void ExtAdvPdu::copyTo(whad_ble_ext_adv_t *p_struct)
{
    p_struct->length = getLength();
    memcpy(p_struct->adv_data, getData(), getLength());
    if (getAuxPtr() != NULL)
    {
        p_struct->has_auxptr = true;
        m_pAuxPtr->copyTo(&p_struct->auxptr);

    }
    else
    {
        p_struct->has_auxptr = false;
    }
}
