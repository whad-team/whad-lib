#ifndef __INC_WHAD_H
#define __INC_WHAD_H

#include "ringbuf.h"
#include "transport.h"
#include "generic.h"
#include "discovery.h"
#include "domains/ble.h"
#include "domains/phy.h"


#define WHAD_MESSAGE_MAX_SIZE       (4096)

#ifdef __cplusplus
extern "C" {
#endif

void whad_init(whad_transport_cfg_t *p_transport_cfg);
whad_result_t whad_get_message(Message *p_msg);
whad_result_t whad_send_message(Message *p_msg);


#ifdef __cplusplus
}
#endif


#ifdef __cplusplus
#include "cpp/whad.hpp"
#endif

#endif /* __INC_WHAD_H */