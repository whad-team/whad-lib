#include "phy/setsyncword.hpp"

using namespace whad::phy;

/**
 * @brief       Create a SetSyncWord message based on raw PHY message.
 * 
 * @param[in]   message     Base NanoPb message to use.
 **/

SetSyncWord::SetSyncWord(PhyMsg &message) : PhyMsg(message)
{
    this->unpack();
}


/**
 * @brief       Create a SetSyncWord message from a specified synchronization word.
 * 
 * @param[in]   syncWord    Synchronization word to use
 **/

SetSyncWord::SetSyncWord(SyncWord &syncWord) : PhyMsg()
{
    m_syncWord = syncWord;
}


/**
 * @brief       Get the specified synchronization word
 * 
 * @retval      Synchronization word in use
 **/

SyncWord& SetSyncWord::get()
{
    return m_syncWord;
}


/**
 * @brief   Pack parameters into a PhyMsg.
 */

void SetSyncWord::pack()
{
    whad_phy_set_sync_word(
        this->getMessage(),
        m_syncWord.get(),
        m_syncWord.getSize()
    );
}


/**
 * @brief   Extract parameters from PhyMsg.
 */

void SetSyncWord::unpack()
{
    whad_phy_syncword_t syncword;

    if (whad_phy_set_sync_word_parse(this->getMessage(), &syncword) == WHAD_SUCCESS)
    {
        m_syncWord = SyncWord(syncword.syncword, syncword.length);
    }
    else
    {
        throw WhadMessageParsingError();
    }
}