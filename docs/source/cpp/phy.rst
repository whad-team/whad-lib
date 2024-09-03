PHY
===

Parsing PHY messages
--------------------

When processing PHY messages sent to a compatible interface,
the :cpp:func:`whad::phy::PhyMsg::getType` function returns the corresponding
message type (:cpp:enum:`whad::phy::MessageType`). This message type is then used
to process and parse the incoming message.

The following example code shows a message processing function defined for a
compatible interface that only supports PHY packet sniffing. The supported
commands must also be indicated in the interface's capabilities as described
in :ref:`whad_discovery_cap`.

.. code-block:: c

    void process_phy_message(Message *p_message)
    {
        NanoPbMsg *response = NULL;

        /* Wrap our NanoPbMsg into a PhyMsg. */
        whad::phy::PhyMsg phy_msg(message);

        switch (phy_msg.getType())
        {
            case whad::phy::MessageType::SetGfskModMsg:
            {
                /* Configure PHY to GFSK mod/demod ... (custom code) */
                /* ... */

                /* Return a success message. */
                response = new whad::generic::Success();                 
            }
            break;

            case whad::phy::MessageType::SetSniffModeMsg:
            {
                /* Configure our interface in sniffing mode ... (custom code) */
                /* ... */

                /* Return a success message. */
                response = new whad::generic::Success();  
            }
            break;

            case whad::phy::MessageType::StartMsg:
            {
                /* Start current mode. */
                /* ... */

                /* Return a success message. */
                response = new whad::generic::Success();                 
            }
            break;

            case whad::phy::MessageType::StopMsg:
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
                whad_generic_cmd_result(&response, WHAD_RESULT_ERROR);                 
            }
            break;
        }

        /* Send the response to the host. */
        whad::send(*response);
        delete response;
    }

PHY API reference
-----------------

.. doxygennamespace:: whad::phy
    :members: