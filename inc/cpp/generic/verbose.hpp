#ifndef __INC_WHAD_GENERIC_VERBOSE_HPP
#define __INC_WHAD_GENERIC_VERBOSE_HPP

#include <string>
#include "message.hpp"
#include "common.hpp"
#include "generic/generic.hpp"

namespace whad::generic {

    /* Verbose message. */
    class Verbose : public GenericMsg
    {
        public:
            Verbose(std::string message);

        private:
            void pack();

            std::string m_message;
    };
  
}

#endif /* __INC_WHAD_GENERIC_VERBOSE_HPP */