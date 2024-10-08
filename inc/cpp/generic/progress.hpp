#ifndef __INC_WHAD_GENERIC_PROGRESS_HPP
#define __INC_WHAD_GENERIC_PROGRESS_HPP

#include <string>
#include "message.hpp"
#include "common.hpp"
#include "generic/generic.hpp"

namespace whad::generic {

    /* Progress notification. */
    class Progress : public GenericMsg
    {
        public:
            Progress(int32_t value);

        private:
            void pack();
            int32_t m_value;
    };

}

#endif /* __INC_WHAD_GENERIC_PROGRESS_HPP */