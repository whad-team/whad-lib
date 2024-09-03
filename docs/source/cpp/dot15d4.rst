IEEE 802.15.4
=============

Parsing Dot15d4 messages
------------------------

When processing Dot15d4 messages sent to a compatible interface,
the :cpp:func:`whad::dot15d4::Dot15d4Msg::getType` function returns the corresponding
message type (:cpp:enum:`whad::dot15d4::MessageType`). This message type is then used
to process and parse the incoming message.

The following example code shows a message processing function defined for a
compatible interface that only supports Dot15d4 packet sniffing. The supported
commands must also be indicated in the interface's capabilities as described
in :ref:`whad_discovery_cap`.

.. code-block:: c

    void process_dot15d4_message(Message *p_message)
    {
        NanoPbMsg *response = NULL;

        /* Wrap our NanoPbMsg into a Dot15d4Msg. */
        whad::dot15d4::Dot15d4Msg dot15d4_msg(message);

        switch (dot15d4_msg.getType())
        {
            case whad::dot15d4::MessageType::SniffModeMsg:
            {
                /* Configure our interface in sniff mode ... (custom code) */
                /* ... */

                /* Return a success message. */
                response = new whad::generic::Success();  
            }
            break;

            case whad::dot15d4::MessageType::StartMsg:
            {
                /* Start current mode. */
                /* ... */

                /* Return a success message. */
                response = new whad::generic::Success();                  
            }
            break;

            case whad::dot15d4::MessageType::StopMsg:
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

Dot15d4 API reference
---------------------

.. doxygennamespace:: whad::dot15d4
    :members: