#ifndef __INC_WHAD_DOT15D4_ASN_HPP
#define __INC_WHAD_DOT15D4_ASN_HPP

#include <string>
#include "message.hpp"
#include "common.hpp"

namespace whad::dot15d4 {

    class ASN 
    {
        public:

            ASN();   
            ASN(uint64_t val);
                     
            

            void incrementASN();

            /* Getters. */
            uint64_t getASN();

            /* Setters. */
            void setASN(uint64_t);

        private:
            uint64_t m_asn;
            
    };

}

#endif /* __INC_WHAD_DOT15D4_ASN_HPP */
