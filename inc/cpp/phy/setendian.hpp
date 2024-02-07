#ifndef __INC_WHAD_PHY_SETENDIAN_HPP
#define __INC_WHAD_PHY_SETENDIAN_HPP

#include <string>
#include <vector>
#include "message.hpp"
#include "common.hpp"
#include "../domains/phy.h"
#include <phy/base.hpp>

namespace whad::phy {

    enum Endianness {
        PhyLittleEndian = PHY_LITTLE_ENDIAN,
        PhyBigEndian = PHY_BIG_ENDIAN
    };

    class SetEndianness : public PhyMsg
    {
        public:
            SetEndianness(PhyMsg &message);
            SetEndianness(Endianness endian);

            Endianness getEndianness();

        private:
            void pack();
            void unpack();

            Endianness m_endian;
    };

}

#endif /* __INC_WHAD_PHY_SETENDIAN_HPP */