#include <dot15d4/superframes.hpp>

using namespace whad::dot15d4;



Superframes::Superframes(){
    m_superframes = (whad_dot15d4_superframes_t*) malloc(sizeof(whad_dot15d4_superframes_t));
    m_superframes->next = nullptr;
    m_superframes->superframe = nullptr;
}

void Superframes::writeModifySuperframe(Dot15d4Msg *message){
    this->unpack( message);
}

void Superframes::unpack(Dot15d4Msg *message){
    whad_result_t result;
    whad_dot15d4_write_modify_superframes_packet_t superframe_pkt;

    result = whad_dot15d4_write_modify_superframe(
        message->getMessage(),
        &superframe_pkt
    );
    if (result == WHAD_ERROR)
    {
        /* Error occured during parsing. */
        throw WhadMessageParsingError();
    }
    else
    {

        whad_dot15d4_superframe_t *superframe = this->getSuperframe(superframe_pkt.superframeId);

        if(superframe_pkt.has_asn){
            // todo add this function addSuperframe with its parameters to a queue that the timer is going to check its time
            if(superframe == nullptr){
                //Program adding superframe on asn timer
            }
            else{
                //program modifying superframe on asn timer
            }
        }
        else{
            
            if(superframe == nullptr){
                this->addSuperframe(superframe_pkt.superframeId, superframe_pkt.numberOfSlots, superframe_pkt.flags);
            }
            else{
                this->modifySuperframe(superframe, superframe_pkt.numberOfSlots, superframe_pkt.flags);
            }
            
        }
    }
}

void Superframes::addSuperframe(int superframeId, int numberOfSlots, int flags){
    whad_dot15d4_superframes_t *curr = m_superframes;
    whad_dot15d4_superframe_t * superframe = (whad_dot15d4_superframe_t*) malloc(sizeof(whad_dot15d4_superframe_t));
    superframe->id = superframeId;
    superframe->size = numberOfSlots;
    superframe->links = (whad_dot15d4_chained_link_list_t*) malloc(sizeof(whad_dot15d4_chained_link_list_t));
    superframe->links->first = nullptr;
    superframe->links->nb_links = 0;

    if (m_superframes->superframe == nullptr && m_superframes->next == nullptr){
        m_superframes->superframe = superframe;
    }else{
        while (curr->next != nullptr){
            curr = curr->next;
        }
        curr->next = (whad_dot15d4_superframes_t*) malloc (sizeof(whad_dot15d4_superframes_t));
        curr->next->superframe = superframe;
        curr->next->next = nullptr;
    }
}

void Superframes::modifySuperframe(whad_dot15d4_superframe_t *superframe, int numberOfSlots,int flags){
    if (superframe != nullptr){
        superframe->size = numberOfSlots;
        superframe->flags = flags;
        if (superframe->links != nullptr){
            whad_dot15d4_link_t* link = superframe->links->first;
            while (link!=nullptr)
            {
                if(link->join_slot > numberOfSlots){
                    whad_dot15d4_link_t *link_to_free = link;
                    link = link->next;
                    free(link_to_free);
                }
                else{
                    link = link->next;
                }
            }
        }
    }
}

whad_dot15d4_superframes_t* Superframes::getSuperframes(){
    return m_superframes;
}

whad_dot15d4_superframe_t* Superframes::getSuperframe(int id){
    return whad_dot15d4_get_superframe(m_superframes, id);
}
