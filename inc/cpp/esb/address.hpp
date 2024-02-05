#ifndef __INC_WHAD_ESB_ADDRESS_HPP
#define __INC_WHAD_ESB_ADDRESS_HPP

#include <string>
#include <vector>
#include "message.hpp"
#include "common.hpp"
#include "../domains/esb.h"

namespace whad::esb {

        class EsbAddress
        {
            private:

                /* ESB address as a byte buffer. */
                uint8_t m_address[5];
                uint8_t m_size;

            public:
                EsbAddress(void);
                EsbAddress(uint8_t *pAddress, uint8_t size);

                /* Getters. */
                uint8_t *getAddressBuf(void);
                uint8_t getLength(void);

                /* Setters. */
                void setAddress(uint8_t *pAddress, uint8_t size);
        };

        extern EsbAddress PromiscAddr;
        extern EsbAddress NullAddr;
}

#endif /* __INC_WHAD_ESB_ADDRESS_HPP */