#ifndef __INC_WHAD_GENERIC_HPP
#define __INC_WHAD_GENERIC_HPP

#include <string>
#include "message.hpp"
#include "common.hpp"

namespace whad
{
    namespace generic
    {
        /*! Generic message types. */
        enum MessageType {
            UnknownMsg = WHAD_GENERIC_UNKNOWN,          /*!< Unknown message type. */
            CommandResultMsg = WHAD_GENERIC_CMDRESULT,  /*!< Command result. */
            VerboseMsg = WHAD_GENERIC_VERBOSE,          /*!< Verbose message. */
            DebugMsg = WHAD_GENERIC_DEBUG,              /*!< Debug message. */
            ProgressMsg = WHAD_GENERIC_PROGRESS         /*!< Progress message. */
        };


        /*! Default generic message class. */
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