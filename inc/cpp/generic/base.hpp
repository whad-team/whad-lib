#ifndef __INC_WHAD_GENERIC_HPP
#define __INC_WHAD_GENERIC_HPP

#include <string>
#include "message.hpp"
#include "common.hpp"

namespace whad
{
    namespace generic
    {
        enum MessageType {
            UnknownMsg = WHAD_GENERIC_UNKNOWN,
            CommandResultMsg = WHAD_GENERIC_CMDRESULT,
            VerboseMsg = WHAD_GENERIC_VERBOSE,
            DebugMsg = WHAD_GENERIC_DEBUG,
            ProgressMsg = WHAD_GENERIC_PROGRESS
        };


        /* Default generic message class. */
        class GenericMsg : public NanoPbMsg
        {
            public:

                /* Constructor and destructor. */
                GenericMsg();
                GenericMsg(NanoPbMsg pMessage);
                ~GenericMsg();

                /* Override getType() message. */
                MessageType getType(void);
        };
    }
};

#endif /* __INC_WHAD_GENERIC_HPP */