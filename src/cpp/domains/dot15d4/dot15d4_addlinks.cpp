#include "dot15d4/addlinks.hpp"

using namespace whad::dot15d4;

AddLinks::AddLinks(Dot15d4Msg &msg, whad_dot15d4_superframes_t* superframes)
    : Dot15d4Msg(msg) {
    unpack(superframes);
}

AddLinks::AddLinks(Message *msg, whad_dot15d4_superframes_t* superframes)
    : Dot15d4Msg(msg) {
    unpack(superframes);
}

void AddLinks::unpack(whad_dot15d4_superframes_t* superframes) {

    whad_result_t result = whad_dot15d4_add_links(getMessage(), superframes);
    if (result == WHAD_ERROR)
    {
        /* Error occured during parsing. */
        throw WhadMessageParsingError();
    }

}

void AddLinks::pack() {
    // toDo
}

