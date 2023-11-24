#include "whad.h"

whad_generic_msgtype_t whad_generic_get_message_type(Message *p_message)
{
    whad_generic_msgtype_t msg_type = WHAD_GENERIC_UNKNOWN;

    /* Sanity check. */
    if (p_message->which_msg != Message_generic_tag)
        return msg_type;

    switch (p_message->msg.generic.which_msg)
    {
        case generic_Message_cmd_result_tag:
            msg_type = WHAD_GENERIC_CMDRESULT;
            break;

        case generic_Message_verbose_tag:
            msg_type = WHAD_GENERIC_VERBOSE;
            break;

        case generic_Message_debug_tag:
            msg_type = WHAD_GENERIC_DEBUG;
            break;
        
        case generic_Message_progress_tag:
            msg_type = WHAD_GENERIC_PROGRESS;
            break;

        default:
            break;
    }

    /* Return message type. */
    return msg_type;
}

/**
 * @brief Initialize a generic command result message
 * 
 * @param[in]   p_message       Pointer to a `Message` structure
 * @param[in]   result          Result code to include in the message
 * @retval      WHAD_SUCCESS    Success
 * @retval      WHAD_ERROR      Wrong message pointer
 **/

whad_result_t whad_generic_cmd_result(Message *p_message, whad_result_code_t result)
{
    /* Sanity check. */
    if (p_message == NULL)
    {
        return WHAD_ERROR;
    }

    /* Build a generic command result message. */
    p_message->which_msg = Message_generic_tag;
    p_message->msg.generic.which_msg = generic_Message_cmd_result_tag;
    p_message->msg.generic.msg.cmd_result.result = result;

    /* Success. */
    return WHAD_SUCCESS;
}


/**
 * @brief Initialize a generic command result message
 * 
 * @param[in]       p_message       Pointer to a `Message` structure
 * @param[in,out]   p_result        Pointer to a result code
 * 
 * @retval      WHAD_SUCCESS    Success
 * @retval      WHAD_ERROR      Wrong message pointer or result code pointer
 **/

whad_result_t whad_generic_cmd_result_parse(Message *p_message, whad_result_code_t *p_result)
{
    /* Sanity check. */
    if ((p_message == NULL) || (p_result == NULL))
    {
        return WHAD_ERROR;
    }

    if (p_message->which_msg == Message_generic_tag)
    {
        if (p_message->msg.generic.which_msg == generic_Message_cmd_result_tag)
        {
            /* Save result. */
            *p_result = (whad_result_code_t)p_message->msg.generic.msg.cmd_result.result;

            /* Success. */
            return WHAD_SUCCESS;
        }
    }

    /* Nope. */
    return WHAD_ERROR;
}


/**
 * @brief Generic verbose message encoding callback.
 * 
 * @param[in,out]   ostream Output stream
 * @param[in]       field   Pointer to a field descriptor.
 * @param[in]       arg     Pointer to a custom argument storing a pointer onto the text message to encode.
 * @return true if everything went ok, false otherwise.
 */

bool whad_verbose_msg_encode_cb(pb_ostream_t *ostream, const pb_field_t *field, void * const *arg)
{
    /* Take arg and encode it. */
    char *psz_message = *(char **)arg;
    int message_length = strlen(psz_message);

    if (ostream != NULL && field->tag == generic_VerboseMsg_data_tag)
    {
        /* This encodes the header for the field, based on the constant info
        * from pb_field_t. */
        if (!pb_encode_tag_for_field(ostream, field))
            return false;

        pb_encode_string(ostream, (pb_byte_t *)psz_message, message_length);
    }

    return true;
}


/**
 * @brief Initialize a generic verbose message.
 * 
 * @param[in,out]   p_message     Pointer to a `Message` structure representing a message.
 * @param[in]       psz_message   Pointer to the message string to include in this verbose message.
 * @retval          WHAD_SUCCESS  Success
 * @retval          WHAD_ERROR    Wrong message pointer
 */

whad_result_t whad_generic_verbose_message(Message *p_message, char *psz_message)
{
    /* Sanity check. */
    if (p_message == NULL)
    {
        return WHAD_ERROR;
    }

    /* Specify payload type. */
    p_message->which_msg = Message_generic_tag;

    /* Fills verbose message data. */
    p_message->msg.generic.which_msg = generic_Message_verbose_tag;
    p_message->msg.generic.msg.verbose.data.arg = psz_message;
    p_message->msg.generic.msg.verbose.data.funcs.encode = whad_verbose_msg_encode_cb;

    /* Success. */
    return WHAD_SUCCESS;
}

whad_result_t whad_generic_verbose_message_parse(Message *p_message, char **ppsz_message)
{
    /* Sanity check. */
    if ((p_message == NULL) || (ppsz_message == NULL))
    {
        return WHAD_ERROR;
    }

    if (p_message->which_msg == Message_generic_tag)
    {
        if (p_message->msg.generic.which_msg == generic_Message_verbose_tag)
        {
            /* Save result. */
            /* TODO: how to get a pointer to the bytes ?? */
            *ppsz_message = NULL;

            /* Success. */
            return WHAD_SUCCESS;
        }
    }

    /* Nope. */
    return WHAD_ERROR;    
}


/**
 * @brief WHAD verbose helper
 * 
 * This function sends a verbose message to the host.
 * 
 * @param[in]       psz_message   Pointer to the message string to include in this verbose message.
 * 
 * @retval          WHAD_SUCCESS  Success
 * @retval          WHAD_ERROR    Wrong message pointer
 */

whad_result_t whad_verbose(char *psz_message)
{
    whad_result_t result;
    Message msg;

    result = whad_generic_verbose_message(&msg, psz_message);
    if (result == WHAD_SUCCESS)
    {
        return whad_send_message(&msg);
    }
    else
    {
        return WHAD_ERROR;
    }
}


/**
 * @brief Generic debug message encoding callback.
 * 
 * @param[in,out]   ostream Output stream
 * @param[in]       field   Pointer to a field descriptor.
 * @param[in]       arg     Pointer to a custom argument storing a pointer onto the text message to encode.
 * @return true if everything went ok, false otherwise.
 */

bool whad_debug_msg_encode_cb(pb_ostream_t *ostream, const pb_field_t *field, void * const *arg)
{
    /* Take arg and encode it. */
    char *psz_message = *(char **)arg;
    int message_length = strlen(psz_message);

    if (ostream != NULL && field->tag == generic_DebugMsg_data_tag)
    {
        /* This encodes the header for the field, based on the constant info
        * from pb_field_t. */
        if (!pb_encode_tag_for_field(ostream, field))
            return false;

        pb_encode_string(ostream, (pb_byte_t *)psz_message, message_length);
    }

    return true;
}


/**
 * @brief Initialize a generic debug message.
 * 
 * @param[in,out]   p_message     Pointer to a `Messsage` structure
 * @param[in]       level         Debug level
 * @param[in]       psz_message   Pointer to a text string corresponding to the debug message to send
 * 
 * @retval          WHAD_SUCCESS  Success.
 * @retval          WHAD_ERROR    Invalid message pointer.
 **/

whad_result_t whad_generic_debug_message(Message *p_message, uint32_t level, char *psz_message)
{
    /* Sanity check. */
    if (p_message == NULL)
    {
        return WHAD_ERROR;
    }

    /* Specify payload type. */
    p_message->which_msg = Message_generic_tag;

    /* Fills debug message data. */\
    p_message->msg.generic.which_msg = generic_Message_debug_tag;
    p_message->msg.generic.msg.debug.level = level;
    p_message->msg.generic.msg.debug.data.arg = psz_message;
    p_message->msg.generic.msg.debug.data.funcs.encode = whad_debug_msg_encode_cb;

    /* Success. */
    return WHAD_SUCCESS;
}

/**
 * @brief Initialize a generic progress message.
 * 
 * @param[in,out]   p_message     Pointer to a `Messsage` structure
 * @param[in]       value         Progress value
 * @param[in]       psz_message   Pointer to a text string corresponding to the debug message to send
 * 
 * @retval          WHAD_SUCCESS  Success.
 * @retval          WHAD_ERROR    Invalid message pointer.
 **/

whad_result_t whad_generic_progress_message(Message *p_message, uint32_t value)
{
    /* Sanity check. */
    if (p_message == NULL)
    {
        return WHAD_ERROR;
    }

    /* Specify payload type. */
    p_message->which_msg = Message_generic_tag;

    /* Fills debug message data. */
    p_message->msg.generic.which_msg = generic_Message_progress_tag;
    p_message->msg.generic.msg.progress.value = value;

    /* Success. */
    return WHAD_SUCCESS;
}

