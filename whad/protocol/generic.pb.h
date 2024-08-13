/* Automatically generated nanopb header */
/* Generated by nanopb-0.4.7-dev */

#ifndef PB_GENERIC_WHAD_PROTOCOL_GENERIC_PB_H_INCLUDED
#define PB_GENERIC_WHAD_PROTOCOL_GENERIC_PB_H_INCLUDED
#include <pb.h>

#if PB_PROTO_HEADER_VERSION != 40
#error Regenerate this file with the current version of nanopb generator.
#endif

/* Enum definitions */
typedef enum _generic_ResultCode { 
    generic_ResultCode_SUCCESS = 0, 
    generic_ResultCode_ERROR = 1, 
    generic_ResultCode_PARAMETER_ERROR = 2, 
    generic_ResultCode_DISCONNECTED = 3, 
    generic_ResultCode_WRONG_MODE = 4, 
    generic_ResultCode_UNSUPPORTED_DOMAIN = 5, 
    generic_ResultCode_BUSY = 6 
} generic_ResultCode;

/* Struct definitions */
typedef struct _generic_VerboseMsg { 
    pb_callback_t data;
} generic_VerboseMsg;

typedef struct _generic_CmdResult { 
    generic_ResultCode result;
} generic_CmdResult;

typedef struct _generic_DebugMsg { 
    uint32_t level;
    pb_callback_t data;
} generic_DebugMsg;

typedef struct _generic_Progress { 
    uint32_t value;
} generic_Progress;

typedef struct _generic_Message { 
    pb_size_t which_msg;
    union {
        generic_ResultCode result;
        generic_CmdResult cmd_result;
        generic_Progress progress;
        generic_DebugMsg debug;
        generic_VerboseMsg verbose;
    } msg;
} generic_Message;


/* Helper constants for enums */
#define _generic_ResultCode_MIN generic_ResultCode_SUCCESS
#define _generic_ResultCode_MAX generic_ResultCode_BUSY
#define _generic_ResultCode_ARRAYSIZE ((generic_ResultCode)(generic_ResultCode_BUSY+1))


#ifdef __cplusplus
extern "C" {
#endif

/* Initializer values for message structs */
#define generic_CmdResult_init_default           {_generic_ResultCode_MIN}
#define generic_Progress_init_default            {0}
#define generic_DebugMsg_init_default            {0, {{NULL}, NULL}}
#define generic_VerboseMsg_init_default          {{{NULL}, NULL}}
#define generic_Message_init_default             {0, {_generic_ResultCode_MIN}}
#define generic_CmdResult_init_zero              {_generic_ResultCode_MIN}
#define generic_Progress_init_zero               {0}
#define generic_DebugMsg_init_zero               {0, {{NULL}, NULL}}
#define generic_VerboseMsg_init_zero             {{{NULL}, NULL}}
#define generic_Message_init_zero                {0, {_generic_ResultCode_MIN}}

/* Field tags (for use in manual encoding/decoding) */
#define generic_VerboseMsg_data_tag              1
#define generic_CmdResult_result_tag             1
#define generic_DebugMsg_level_tag               1
#define generic_DebugMsg_data_tag                2
#define generic_Progress_value_tag               1
#define generic_Message_result_tag               1
#define generic_Message_cmd_result_tag           2
#define generic_Message_progress_tag             3
#define generic_Message_debug_tag                4
#define generic_Message_verbose_tag              5

/* Struct field encoding specification for nanopb */
#define generic_CmdResult_FIELDLIST(X, a) \
X(a, STATIC,   SINGULAR, UENUM,    result,            1)
#define generic_CmdResult_CALLBACK NULL
#define generic_CmdResult_DEFAULT NULL

#define generic_Progress_FIELDLIST(X, a) \
X(a, STATIC,   SINGULAR, UINT32,   value,             1)
#define generic_Progress_CALLBACK NULL
#define generic_Progress_DEFAULT NULL

#define generic_DebugMsg_FIELDLIST(X, a) \
X(a, STATIC,   SINGULAR, UINT32,   level,             1) \
X(a, CALLBACK, SINGULAR, BYTES,    data,              2)
#define generic_DebugMsg_CALLBACK pb_default_field_callback
#define generic_DebugMsg_DEFAULT NULL

#define generic_VerboseMsg_FIELDLIST(X, a) \
X(a, CALLBACK, SINGULAR, BYTES,    data,              1)
#define generic_VerboseMsg_CALLBACK pb_default_field_callback
#define generic_VerboseMsg_DEFAULT NULL

#define generic_Message_FIELDLIST(X, a) \
X(a, STATIC,   ONEOF,    UENUM,    (msg,result,msg.result),   1) \
X(a, STATIC,   ONEOF,    MESSAGE,  (msg,cmd_result,msg.cmd_result),   2) \
X(a, STATIC,   ONEOF,    MESSAGE,  (msg,progress,msg.progress),   3) \
X(a, STATIC,   ONEOF,    MESSAGE,  (msg,debug,msg.debug),   4) \
X(a, STATIC,   ONEOF,    MESSAGE,  (msg,verbose,msg.verbose),   5)
#define generic_Message_CALLBACK NULL
#define generic_Message_DEFAULT NULL
#define generic_Message_msg_cmd_result_MSGTYPE generic_CmdResult
#define generic_Message_msg_progress_MSGTYPE generic_Progress
#define generic_Message_msg_debug_MSGTYPE generic_DebugMsg
#define generic_Message_msg_verbose_MSGTYPE generic_VerboseMsg

extern const pb_msgdesc_t generic_CmdResult_msg;
extern const pb_msgdesc_t generic_Progress_msg;
extern const pb_msgdesc_t generic_DebugMsg_msg;
extern const pb_msgdesc_t generic_VerboseMsg_msg;
extern const pb_msgdesc_t generic_Message_msg;

/* Defines for backwards compatibility with code written before nanopb-0.4.0 */
#define generic_CmdResult_fields &generic_CmdResult_msg
#define generic_Progress_fields &generic_Progress_msg
#define generic_DebugMsg_fields &generic_DebugMsg_msg
#define generic_VerboseMsg_fields &generic_VerboseMsg_msg
#define generic_Message_fields &generic_Message_msg

/* Maximum encoded size of messages (where known) */
/* generic_DebugMsg_size depends on runtime parameters */
/* generic_VerboseMsg_size depends on runtime parameters */
/* generic_Message_size depends on runtime parameters */
#define generic_CmdResult_size                   2
#define generic_Progress_size                    6

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif