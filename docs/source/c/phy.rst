PHY
===

Parsing PHY messages
--------------------

When processing PHY messages sent to a compatible interface,
the :cpp:func:`whad_phy_get_message_type` function returns the corresponding
message type (:cpp:enum:`whad_phy_msgtype_t`). This message type is then used
to process and parse the incoming message.

The following example code shows a message processing function defined for a
compatible interface that only supports PHY packet sniffing. The supported
commands must also be indicated in the interface's capabilities as described
in :ref:`whad_discovery_cap`.

.. code-block:: c

    void process_phy_message(Message *p_message)
    {
        Message response;

        switch (whad_phy_get_message_type(p_message))
        {
            case WHAD_PHY_SET_GFSK_MOD:
            {
                /* Configure PHY to GFSK mod/demod ... (custom code) */
                /* ... */

                /* Return a success message. */
                whad_generic_cmd_result(&response, WHAD_RESULT_SUCCESS);                
            }
            break;

            case WHAD_PHY_SET_SNIFF_MODE:
            {
                /* Configure our interface in sniffing mode ... (custom code) */
                /* ... */

                /* Return a success message. */
                whad_generic_cmd_result(&response, WHAD_RESULT_SUCCESS);
            }
            break;

            case WHAD_PHY_START:
            {
                /* Start current mode. */
                /* ... */

                /* Return a success message. */
                whad_generic_cmd_result(&response, WHAD_RESULT_SUCCESS);                
            }
            break;

            case WHAD_PHY_STOP:
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

PHY API reference
-----------------

.. doxygenfile:: inc/domains/phy.h
    :sections: define enum

.. doxygenfile:: src/domains/phy.c