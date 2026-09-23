#ifndef __INC_WHAD_DOT15D4_DELETE_SUPERFRAME_HPP
#define __INC_WHAD_DOT15D4_DELETE_SUPERFRAME_HPP

#include <string>
#include "message.hpp"
#include "common.hpp"
#include <dot15d4/base.hpp>


namespace whad::dot15d4 {

    class DeleteSuperframe : public Dot15d4Msg
    {
        public:
            DeleteSuperframe(Dot15d4Msg &message);
            DeleteSuperframe(uint32_t superframe_id);

            /* Getters. */
            uint32_t getSuperframeId();
            
        private:
            void pack();
            void unpack();

            uint32_t m_superframe_id;
    };

}

#endif /* __INC_WHAD_DOT15D4_DELETE_SUPERFRAME_HPP */