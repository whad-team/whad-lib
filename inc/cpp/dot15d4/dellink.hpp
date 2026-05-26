#ifndef __INC_WHAD_DOT15D4_DELETE_LINK_HPP
#define __INC_WHAD_DOT15D4_DELETE_LINK_HPP

#include <string>
#include "message.hpp"
#include "common.hpp"
#include <dot15d4/base.hpp>



namespace whad::dot15d4 {

    class DeleteLink : public Dot15d4Msg
    {
        public:
            DeleteLink(Dot15d4Msg &message);
            DeleteLink(uint32_t superframe_id, uint32_t offset, uint32_t neighbor);

            /* Getters. */
            uint32_t getSuperframeId();
            uint32_t getOffset();
            uint16_t getNeighbor();
            

        private:
            void pack();
            void unpack();

            uint32_t m_superframe_id;
            uint32_t m_offset;
            uint16_t m_neighbor;
    };

}

#endif /* __INC_WHAD_DOT15D4_DELETE_LINK_HPP */