#ifndef __INC_WHAD_DOT15D4_UPDATE_SUPERFRAME_HPP
#define __INC_WHAD_DOT15D4_UPDATE_SUPERFRAME_HPP

#include <string>
#include "message.hpp"
#include "common.hpp"
#include <dot15d4/base.hpp>


namespace whad::dot15d4 {

    class UpdateSuperframe : public Dot15d4Msg
    {
        public:
            UpdateSuperframe(Dot15d4Msg &message);
            UpdateSuperframe(uint32_t superframe_id, uint32_t number_of_slots, uint32_t flags, uint64_t asn);

            /* Getters. */
            uint32_t getSuperframeId();
            uint32_t getNumberOfSlots();
            uint32_t getFlags();
            uint64_t getASN();

        private:
            void pack();
            void unpack();

            uint32_t m_superframe_id;
            uint32_t m_number_of_slots;
            uint32_t m_flags;
            uint64_t m_asn;
    };

}

#endif /* __INC_WHAD_DOT15D4_UPDATE_SUPERFRAME_HPP */