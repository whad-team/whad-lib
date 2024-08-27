Bluetooth Low Energy
====================

Parsing BLE messages
--------------------

When processing Bluetooth Low Energy messages sent to a compatible interface,
the :cpp:func:`whad_ble_get_message_type` function returns the corresponding
message type (:cpp:enum:`whad_ble_msgtype_t`). This message type is then used
to process and parse the incoming message.

The following example code shows a message processing function defined for a
compatible interface that only supports BLE device scanning. The supported
commands must also be indicated in the interface's capabilities as described
in :ref:`whad_discovery_cap`.

.. code-block:: c

    void process_ble_message(Message *p_message)
    {
        Message response;

        switch (whad_ble_get_message_type(p_message))
        {
            case WHAD_BLE_SCAN_MODE:
            {
                /* Configure our interface in scan mode ... (custom code) */
                /* ... */

                /* Return a success message. */
                whad_generic_cmd_result(&response, WHAD_RESULT_SUCCESS);
            }
            break;

            case WHAD_BLE_START:
            {
                /* Start current mode. */
                /* ... */

                /* Return a success message. */
                whad_generic_cmd_result(&response, WHAD_RESULT_SUCCESS);                
            }
            break;

            case WHAD_BLE_STOP:
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

Bluetooth Low Energy API reference
----------------------------------

.. doxygenfile:: inc/domains/ble.h
    :sections: define enums

.. doxygenfile:: src/domains/ble.c
