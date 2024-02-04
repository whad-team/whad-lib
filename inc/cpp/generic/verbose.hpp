#ifndef __INC_WHAD_GENERIC_VERBOSE_HPP
#define __INC_WHAD_GENERIC_VERBOSE_HPP

#include <string>
#include "message.hpp"
#include "common.hpp"
#include "generic/base.hpp"

namespace whad::generic {

    /* Verbose message. */
    class Verbose : public GenericMsg
    {
        public:
            Verbose(GenericMsg &message);
            Verbose(std::string message);

        private:
            void pack();
            void unpack();

            std::string m_message;
    };
  
}

#endif /* __INC_WHAD_GENERIC_VERBOSE_HPP */