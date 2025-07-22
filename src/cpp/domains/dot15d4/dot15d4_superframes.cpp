#include <dot15d4/superframes.hpp>
#include <core.h>

using namespace whad::dot15d4;



Superframes::Superframes(){
    m_superframes = (whad_dot15d4_superframes_t*) malloc(sizeof(whad_dot15d4_superframes_t));
    m_superframes->next = nullptr;
    m_superframes->superframe = nullptr;
}

void Superframes::deleteSuperframe(Dot15d4Msg &message){
    whad_dot15d4_delete_superframe(message.getMessage(), &m_superframes);
}

void Superframes::writeModifySuperframe(Dot15d4Msg &message){
    whad_result_t result;
    whad_dot15d4_write_modify_superframes_packet_t* superframe_pkt = (whad_dot15d4_write_modify_superframes_packet_t*) malloc(sizeof(whad_dot15d4_write_modify_superframes_packet_t));

    result = whad_dot15d4_write_modify_superframe(
        message.getMessage(),
        superframe_pkt
    );
    if (result == WHAD_ERROR)
    {
        /* Error occured during parsing. */
        free(superframe_pkt);
        throw WhadMessageParsingError();
    }
    else
    {

        whad_dot15d4_superframe_t *superframe = this->getSuperframe(superframe_pkt->superframeId);

        if(superframe_pkt->has_asn){
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
                whad_dot15d4_add_superframe(m_superframes, superframe_pkt);
            }
            else{
                whad_dot15d4_modify_superframe(superframe, superframe_pkt);
            }
            
        }
        free(superframe_pkt);
    }
}

void Superframes::addLinks(Dot15d4Msg &Message){
    whad_result_t result = whad_dot15d4_add_links(Message.getMessage(), m_superframes);
    if (result == WHAD_ERROR)
    {
        /* Error occured during parsing. */
        throw WhadMessageParsingError();
    }
}

void Superframes::deleteLink(Dot15d4Msg &Message){
    whad_dot15d4_delete_link(Message.getMessage(), m_superframes);
}

whad_dot15d4_superframes_t* Superframes::getSuperframes(){
    return m_superframes;
}

whad_dot15d4_superframe_t* Superframes::getSuperframe(int id){
    return whad_dot15d4_get_superframe(m_superframes, id);
}
