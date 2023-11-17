#ifndef __INC_GENERIC_H
#define __INC_GENERIC_H

#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif

/*********************************
 * Generic messages
 ********************************/

typedef enum {
    WHAD_RESULT_SUCCESS = 0, 
    WHAD_RESULT_ERROR = 1, 
    WHAD_RESULT_PARAMETER_ERROR = 2, 
    WHAD_RESULT_DISCONNECTED = 3, 
    WHAD_RESULT_WRONG_MODE = 4, 
    WHAD_RESULT_UNSUPPORTED_DOMAIN = 5, 
    WHAD_RESULT_BUSY = 6 
} whad_result_code_t;

/* Populate a generic command result message. */
whad_result_t whad_generic_cmd_result(Message *p_message, whad_result_code_t result);

/* Populate a generic verbose message. */
whad_result_t whad_generic_verbose_message(Message *p_message, char *psz_message);

/* Populate a debug message. */
whad_result_t whad_generic_debug_message(Message *p_message, uint32_t level, char *psz_message);

/* Populate a progress message. */
whad_result_t whad_generic_progress_message(Message *p_message, uint32_t value);

/* Verbose message helper. */
whad_result_t whad_verbose(char *psz_message);

#ifdef __cplusplus
}
#endif

#endif /* __INC_GENERIC_H */