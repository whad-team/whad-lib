/** \file generic.h
 * WHAD generic messages crafting and parsing.
 */

#ifndef __INC_GENERIC_H
#define __INC_GENERIC_H

#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif

/*********************************
 * Generic messages
 ********************************/

/**
 * Generic command result codes.
 * 
 */
typedef enum {
    WHAD_RESULT_SUCCESS = 0,            /*!< Operation succeeded. */
    WHAD_RESULT_ERROR = 1,              /*!< An error occurred. */
    WHAD_RESULT_PARAMETER_ERROR = 2,    /*!< A wrong parameter has been supplied. */
    WHAD_RESULT_DISCONNECTED = 3,       /*!< Device has disconnected. */
    WHAD_RESULT_WRONG_MODE = 4,         /*!< Requested operation does not match current operating mode. */
    WHAD_RESULT_UNSUPPORTED_DOMAIN = 5, /*!< Domain is not supported by this interface. */
    WHAD_RESULT_BUSY = 6                /*!< Interface is busy and cannot handle the requested operation. */
} whad_result_code_t;


/**
 * Generic message types
 * 
 * This enumeration is an alias for NanoPb generated constants.
 */

typedef enum {
    WHAD_GENERIC_UNKNOWN=0,                                 /*!< Unknown generic message */
    WHAD_GENERIC_CMDRESULT=generic_Message_cmd_result_tag,  /*!< Command result */
    WHAD_GENERIC_VERBOSE=generic_Message_verbose_tag,       /*!< Verbose message */
    WHAD_GENERIC_DEBUG=generic_Message_debug_tag,           /*!< Debug message */
    WHAD_GENERIC_PROGRESS=generic_Message_progress_tag      /*!< Progress message */
} whad_generic_msgtype_t;

/* Get generic message type from NanoPb message. */
whad_generic_msgtype_t whad_generic_get_message_type(Message *p_message);

/* Populate a generic command result message. */
whad_result_t whad_generic_cmd_result(Message *p_message, whad_result_code_t result);
whad_result_t whad_generic_cmd_result_parse(Message *p_message, whad_result_code_t *p_result);

/* Populate a generic verbose message. */
whad_result_t whad_generic_verbose_message(Message *p_message, char *psz_message);

/* Populate a debug message. */
whad_result_t whad_generic_debug_message(Message *p_message, uint32_t level, char *psz_message);

/* Populate a progress message. */
whad_result_t whad_generic_progress_message(Message *p_message, uint32_t value);
whad_result_t whad_generic_progress_message_parse(Message *p_message, uint32_t *p_value);

/* Verbose message helper. */
whad_result_t whad_verbose(char *psz_message);

#ifdef __cplusplus
}
#endif

#endif /* __INC_GENERIC_H */