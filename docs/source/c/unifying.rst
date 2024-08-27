Logitech Unifying
=================


Parsing Logitech Unifying messages
----------------------------------

When processing Logitech Unifying messages sent to a compatible interface,
the :cpp:func:`whad_unifying_get_message_type` function returns the corresponding
message type (:cpp:enum:`whad_unifying_msgtype_t`). This message type is then used
to process and parse the incoming message.

The following example code shows a message processing function defined for a
compatible interface that only supports Logitech Unifying packet sniffing. The supported
commands must also be indicated in the interface's capabilities as described
in :ref:`whad_discovery_cap`.

.. code-block:: c

    void process_unifying_message(Message *p_message)
    {
        Message response;

        switch (whad_unifying_get_message_type(p_message))
        {
            case WHAD_UNIFYING_SNIFF_MODE:
            {
                /* Configure our interface in sniffing mode ... (custom code) */
                /* ... */

                /* Return a success message. */
                whad_generic_cmd_result(&response, WHAD_RESULT_SUCCESS);
            }
            break;

            case WHAD_UNIFYING_START:
            {
                /* Start current mode. */
                /* ... */

                /* Return a success message. */
                whad_generic_cmd_result(&response, WHAD_RESULT_SUCCESS);                
            }
            break;

            case WHAD_UNIFYING_STOP:
            {
                /* Stop current mode. */
                /* ... */

                /* Return a success message. */
                whad_generic_cmd_result(&response, WHAD_RESULT_SUCCESS);                
            }
            break;

            default:
            {
                /* Return an error message. */
                whad_generic_cmd_result(&response, WHAD_RESULT_ERROR);                 
            }
            break;
        }

        /* Send the response to the host. */
        whad_send_message(&response);
    }

Logitech Unifying API reference
-------------------------------

.. doxygenfile:: inc/domains/unifying.h
    :sections: define enum

.. doxygenfile:: src/domains/unifying.c