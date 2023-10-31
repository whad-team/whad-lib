#ifndef __INC_WHAD_H
#define __INC_WHAD_H

#include "protocol.h"
#include "ringbuf.h"
#include "transport.h"

#define WHAD_MESSAGE_MAX_SIZE       (4096)

#ifdef __cplusplus
extern "C" {
#endif

void whad_init(whad_transport_cfg_t *p_transport_cfg);
whad_result_t whad_get_message(Message *p_msg);
whad_result_t whad_send_message(Message *p_msg);
void whad_verbose(char *psz_message);


#ifdef __cplusplus
}
#endif


#endif /* __INC_WHAD_H */