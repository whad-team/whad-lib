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
            DeleteLink(uint32_t superframe_id, uint32_t time_slot, uint32_t channel_offset);

            /* Getters. */
            uint32_t getSuperframeId();
            uint32_t getChannelOffset();
            uint32_t getTimeSlot();
            

        private:
            void pack();
            void unpack();

            uint32_t m_superframe_id;
            uint32_t m_channel_offset;
            uint16_t m_time_slot;
    };

}

#endif /* __INC_WHAD_DOT15D4_DELETE_LINK_HPP */