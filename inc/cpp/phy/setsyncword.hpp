#ifndef __INC_WHAD_PHY_SETSYNCWORD_HPP
#define __INC_WHAD_PHY_SETSYNCWORD_HPP

#include <string>
#include <vector>
#include "message.hpp"
#include "common.hpp"
#include "../domains/phy.h"
#include <phy/base.hpp>

namespace whad::phy {

    class SetSyncWord : public PhyMsg
    {
        public:

            SetSyncWord(PhyMsg &message);
            SetSyncWord(SyncWord &syncWord);

            SyncWord& get();

        private:
            void pack();
            void unpack();

            SyncWord m_syncWord;
    };

}

#endif /* __INC_WHAD_PHY_SETSYNCWORD_HPP */