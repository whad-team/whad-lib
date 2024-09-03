Logitech Unifying
=================


Parsing Logitech Unifying messages
----------------------------------

When processing Logitech Unifying messages sent to a compatible interface,
the :cpp:func:`whad::unifying::UnifyingMsg::getType` function returns the corresponding
message type (:cpp:enum:`whad::unifying::MessageType`). This message type is then used
to process and parse the incoming message.

The following example code shows a message processing function defined for a
compatible interface that only supports Logitech Unifying packet sniffing. The supported
commands must also be indicated in the interface's capabilities as described
in :ref:`whad_discovery_cap`.

.. code-block:: c

    void process_unifying_message(Message *p_message)
    {
        NanoPbMsg *response = NULL;

        /* Wrap our NanoPbMsg into a UnifyingMsg. */
        whad::unifying::UnifyingMsg uni_msg(message);

        switch (uni_msg.getType())
        {
            case whad::unifying::MessageType::SniffModeMsg:
            {
                /* Configure our interface in sniffing mode ... (custom code) */
                /* ... */

                /* Return a success message. */
                response = new whad::generic::Success(); 
            }
            break;

            case whad::unifying::MessageType::StartMsg:
            {
                /* Start current mode. */
                /* ... */

                /* Return a success message. */
                response = new whad::generic::Success();                
            }
            break;

            case whad::unifying::MessageType::StopMsg:
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

Logitech Unifying API reference
-------------------------------

.. doxygennamespace:: whad::unifying
    :members: