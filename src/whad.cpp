#include "whad.h"

using namespace whad;

void send(NanoPbMsg message)
{ 
    /* Send WHAD message. */
    whad_send_message(message.getRaw());
}