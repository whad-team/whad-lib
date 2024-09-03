Enhanced ShockBurst
===================

Parsing Enhanced ShockBurst messages
------------------------------------

When processing ESB messages sent to a compatible interface,
the :cpp:func:`whad::esb::EsbMsg::getType` function returns the corresponding
message type (:cpp:enum:`whad::esb::MessageType`). This message type is then used
to process and parse the incoming message.

The following example code shows a message processing function defined for a
compatible interface that only supports ESB packet sniffing. The supported
commands must also be indicated in the interface's capabilities as described
in :ref:`cpp_whad_discovery_cap`.

.. code-block:: c

    void process_esb_message(Message *p_message)
    {
        NanoPbMsg *response = NULL;

        /* Wrap our NanoPbMsg into an EsbMsg. */
        whad::esb::EsbMsg esb_msg(message);

        switch (esb_msg.getType())
        {
            case whad::esb::MessageType::SniffMsg:
            {
                /* Configure our interface in sniff mode ... (custom code) */
                /* ... */

                /* Return a success message. */
                response = new whad::generic::Success();  
            }
            break;

            case whad::esb::MessageType::StartMsg:
            {
                /* Start current mode. */
                /* ... */

                /* Return a success message. */
                response = new whad::generic::Success();                
            }
            break;

            case whad::esb::MessageType::StopMsg:
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

Enhanced ShockBurst API reference
---------------------------------

.. doxygennamespace:: whad::esb
    :members: