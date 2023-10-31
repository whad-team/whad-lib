#ifndef __INC_WHAD_TYPES_H
#define __INC_WHAD_TYPES_H

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    WHAD_SUCCESS = 0,
    WHAD_ERROR,
    WHAD_NONE,
    WHAD_RINGBUF_EMPTY,
    WHAD_RINGBUF_FULL
} whad_result_t;

#ifdef __cplusplus
}
#endif

#endif /* __INC_WHAD_TYPES_H */