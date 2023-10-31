#ifndef __INC_WHAD_RINGBUF_H
#define __INC_WHAD_RINGBUF_H

#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "types.h"

#define     WHAD_RINGBUF_MAX_SIZE    1024


#ifdef __cplusplus
extern "C" {
#endif

typedef struct t_whad_ring {
    int head;
    int tail;
    uint8_t data[WHAD_RINGBUF_MAX_SIZE];
} whad_ringbuf_t;

/**
 * Exported functions.
 */

void whad_ringbuf_init(whad_ringbuf_t *p_ringbuf);
int whad_ringbuf_get_size(whad_ringbuf_t *p_ringbuf);
whad_result_t whad_ringbuf_push(whad_ringbuf_t *p_ringbuf, uint8_t data);
whad_result_t whad_ringbuf_pull(whad_ringbuf_t *p_ringbuf, uint8_t *p_data);
whad_result_t whad_ringbuf_copy(whad_ringbuf_t *p_ringbuf, uint8_t *p_data, int size);
whad_result_t whad_ringbuf_skip(whad_ringbuf_t *p_ringbuf, int size);

#ifdef __cplusplus
}
#endif

#endif /* __INC_WHAD_RINGBUF_H */