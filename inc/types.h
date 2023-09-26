#ifndef __INC_WHAD_TYPES_H
#define __INC_WHAD_TYPES_H
typedef enum {
    WHAD_SUCCESS = 0,
    WHAD_ERROR,
    WHAD_NONE,
    WHAD_RINGBUF_EMPTY,
    WHAD_RINGBUF_FULL
} whad_result_t;

#endif /* __INC_WHAD_TYPES_H */