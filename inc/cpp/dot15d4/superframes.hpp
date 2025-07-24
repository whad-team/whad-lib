#ifndef __INC_WHAD_DOT15D4_SUPERFRAMES_HPP
#define __INC_WHAD_DOT15D4_SUPERFRAMES_HPP

#include <string>
#include "message.hpp"
#include "common.hpp"
#include <dot15d4/base.hpp>

namespace whad::dot15d4 {

    class Superframes 
    {
        public:
            Superframes();

            void writeModifySuperframe(Dot15d4Msg &message);
            void addSuperframe(int superframeId, int numberOfSlots, int flags);
            void modifySuperframe(whad_dot15d4_superframe_t *superframe, int numberOfSlots,int flags);
            void deleteSuperframe(Dot15d4Msg &message);

            void addLinks(Dot15d4Msg &message);
            void deleteLink(Dot15d4Msg &message);

            /* Getters. */
            whad_dot15d4_superframes_t* getSuperframes();
            whad_dot15d4_superframe_t* getSuperframe(int id);
            uint32_t getMaximumSuperframeSize();

        private:
            void unpack(Dot15d4Msg *message);
            uint32_t lookForMaximumSuperframeSize();

            whad_dot15d4_superframes_t* m_superframes ;
            uint32_t max_size;
            uint8_t* discoveryTable;
    };

}

#endif /* __INC_WHAD_DOT15D4_SUPERFRAMES_HPP */