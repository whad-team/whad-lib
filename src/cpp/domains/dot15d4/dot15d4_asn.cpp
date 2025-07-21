#include "dot15d4/asn.hpp"

using namespace whad::dot15d4;

ASN::ASN()
{
    m_asn = 0;
}

ASN::ASN(uint64_t val)
{
    setASN(val);
}

void ASN::setASN(uint64_t val)
{
    val &= (1ULL << 40) - 1; // masque sur 40 bits
    m_asn = val;
}

uint64_t ASN::getASN()
{
    return m_asn;
}

void ASN::incrementASN()
{
    uint64_t val = getASN();
    ++val;
    setASN(val);
}
