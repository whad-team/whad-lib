#ifndef __INC_WHAD_H
#define __INC_WHAD_H

#include "ringbuf.h"
#include "transport.h"
#include "generic.h"
#include "discovery.h"
#include "domains/ble.h"
#include "domains/phy.h"
#include "domains/esb.h"
#include "domains/unifying.h"
#include "domains/dot15d4.h"


#define WHAD_MESSAGE_MAX_SIZE       (4096)

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    WHAD_MSGTYPE_UNKNOWN,
    WHAD_MSGTYPE_GENERIC,
    WHAD_MSGTYPE_DISCOVERY,
    WHAD_MSGTYPE_DOMAIN
} whad_msgtype_t;

/* Whad initialization and message sending/receive. */
void whad_init(whad_transport_cfg_t *p_transport_cfg);
whad_result_t whad_get_message(Message *p_msg);
whad_result_t whad_send_message(Message *p_msg);

/* Whad message decoding. */
whad_msgtype_t whad_get_message_type(Message *p_msg);
whad_domain_t whad_get_message_domain(Message *p_msg);

#ifdef __cplusplus
}
#endif


#ifdef __cplusplus
#include "cpp/whad.hpp"
#endif

#endif /* __INC_WHAD_H */