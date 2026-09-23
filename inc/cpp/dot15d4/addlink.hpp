#ifndef __INC_WHAD_DOT15D4_ADD_LINK_HPP
#define __INC_WHAD_DOT15D4_ADD_LINK_HPP

#include <string>
#include "message.hpp"
#include "common.hpp"
#include <dot15d4/base.hpp>



namespace whad::dot15d4 {

    class AddLink : public Dot15d4Msg
    {
        public:
            AddLink(Dot15d4Msg &message);
            AddLink(uint32_t superframe_id, uint16_t src, uint32_t time_slot, uint32_t channel_offset, uint32_t neighbor, LinkOptions options, LinkType type);

            /* Getters. */
            uint32_t getSuperframeId();
            uint16_t getSource();
            uint32_t getTimeSlot();
            uint32_t getChannelOffset();
            uint16_t getNeighbor();
            LinkOptions getLinkOptions();
            LinkType getLinkType();

        private:
            void pack();
            void unpack();

            uint32_t m_superframe_id;
            uint16_t m_source;
            uint32_t m_time_slot;
            uint32_t m_channel_offset;
            uint16_t m_neighbor;
            LinkOptions m_options;
            LinkType m_type;
    };

}

#endif /* __INC_WHAD_DOT15D4_ADD_LINK_HPP */