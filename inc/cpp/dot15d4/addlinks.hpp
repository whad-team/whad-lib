#ifndef WHAD_DOT15D4_ADD_LINKS_HPP
#define WHAD_DOT15D4_ADD_LINKS_HPP

#include <string>
#include "message.hpp"
#include "common.hpp"
#include <dot15d4/base.hpp>

namespace whad {
namespace dot15d4 {

class AddLinks : public Dot15d4Msg {
public:
    AddLinks(Dot15d4Msg &msg, whad_dot15d4_superframes_t* superframes);

    AddLinks(Message *msg, whad_dot15d4_superframes_t* superframes);

    

private:
    void unpack(whad_dot15d4_superframes_t* superframes);
    void pack();
};

} 
} 

#endif
