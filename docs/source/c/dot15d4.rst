IEEE 802.15.4
=============

Parsing Dot15d4 messages
------------------------

When processing Dot15d4 messages sent to a compatible interface,
the :cpp:func:`whad_dot15d4_get_message_type` function returns the corresponding
message type (:cpp:enum:`whad_dot15d4_msgtype_t`). This message type is then used
to process and parse the incoming message.

The following example code shows a message processing function defined for a
compatible interface that only supports Dot15d4 packet sniffing. The supported
commands must also be indicated in the interface's capabilities as described
in :ref:`whad_discovery_cap`.

.. code-block:: c

    void process_dot15d4_message(Message *p_message)
    {
        Message response;

        switch (whad_dot15d4_get_message_type(p_message))
        {
            case WHAD_DOT15D4_SNIFF:
            {
                /* Configure our interface in sniff mode ... (custom code) */
                /* ... */

                /* Return a success message. */
                whad_generic_cmd_result(&response, WHAD_RESULT_SUCCESS);
            }
            break;

            case WHAD_DOT15D4_START:
            {
                /* Start current mode. */
                /* ... */

                /* Return a success message. */
                whad_generic_cmd_result(&response, WHAD_RESULT_SUCCESS);                
            }
            break;

            case WHAD_DOT15D4_STOP:
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

Dot15d4 API reference
---------------------

.. doxygenfile:: inc/domains/dot15d4.h
    :sections: define enum

.. doxygenfile:: src/domains/dot15d4.c