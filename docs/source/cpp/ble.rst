Bluetooth Low Energy
====================

Parsing BLE messages
--------------------

When processing Bluetooth Low Energy messages sent to a compatible interface,
the :cpp:func:`whad::ble::BleMsg::getType` function returns the corresponding
message type (:cpp:enum:`whad::ble::MessageType`). This message type is then used
to process and parse the incoming message.

The following example code shows a message processing function defined for a
compatible interface that only supports BLE device scanning. The supported
commands must also be indicated in the interface's capabilities as described
in :ref:`cpp_whad_discovery_cap`.

.. code-block:: c

    void process_ble_message(NanoPbMsg message)
    {   
        NanoPbMsg *response = NULL;

        /* Wrap our NanoPbMsg into a BleMsg. */
        whad::ble::BleMsg ble_msg(message);

        switch (ble_msg.getType())
        {
            case whad::ble::MessageType::ScanModeMsg:
            {
                /* Configure our interface in scan mode ... (custom code) */
                /* ... */

                /* Return a success message. */
                response = new whad::generic::Success();
            }
            break;

            case whad::ble::MessageType::StartMsg:
            {
                /* Start current mode. */
                /* ... */

                /* Return a success message. */
                response = new whad::generic::Success();               
            }
            break;

            case whad::ble::MessageType::StopMsg:
            {
                /* Stop current mode. */
                /* ... */

                /* Return a success message. */
                response = new whad::generic::Success();                 
            }
            break;

            default:
            {
                /* Return an error message. */
                response = new whad::generic::Error();                  
            }
            break;
        }

        /* Send the response to the host. */
        whad::send(*response);
        delete response;
    }

Bluetooth Low Energy API reference
----------------------------------

.. doxygennamespace:: whad::ble
    :members: