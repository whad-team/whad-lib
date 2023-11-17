#ifndef __INC_MESSAGE_HPP
#define __INC_MESSAGE_HPP

#include "../generic.h"

namespace whad
{
    /**
     * Whad Nanopb message wrapper class.
     **/

    class NanoPbMsg
    {
        protected:
            Message *p_nanopbMessage;

        public:

            /* Constructor and destructor. */
            NanoPbMsg();
            ~NanoPbMsg();

            /* Accessor. */
            Message *getRaw(void);
    };

};

#endif /* __INC_MESSAGE_HPP */