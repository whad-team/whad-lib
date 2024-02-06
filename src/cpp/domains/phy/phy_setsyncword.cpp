#include "phy/setsyncword.hpp"

using namespace whad::phy;

/** Set Sync word **/

/**
 * @brief       Create a SetSyncWord message based on raw PHY message.
 * 
 * @param[in]   message     Base NanoPb message to use.
 **/

SetSyncWord::SetSyncWord(NanoPbMsg &message) : PhyMsg(message)
{
}


/**
 * @brief       Create a SetSyncWord message from a specified synchronization word.
 * 
 * @param[in]   syncWord    Synchronization word to use
 **/

SetSyncWord::SetSyncWord(SyncWord &syncWord) : PhyMsg()
{
    whad_phy_set_sync_word(
        this->getRaw(),
        syncWord.get(),
        syncWord.getSize()
    );
}


/**
 * @brief       Get the specified synchronization word
 * 
 * @retval      Synchronization word in use
 **/

SyncWord SetSyncWord::get()
{
    whad_phy_syncword_t syncword;

    whad_phy_set_sync_word_parse(
        this->getRaw(),
        &syncword
    );

    return SyncWord(syncword.syncword, syncword.length);
}
