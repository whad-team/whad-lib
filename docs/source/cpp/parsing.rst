Parsing WHAD messages
=====================

When a firmware receives a WHAD message, it must determine its type and dispatch
it accordingly.

Determining a message type
--------------------------

The :cpp:func:`whad::NanoPbMsg::getType` method must be called to discover the basic
type of a received message. The return value is one of the :cpp:enum:`whad::MessageType`
enum values:

 - :cpp:enumerator:`whad::MessageType::UnknownMsg`: unknown message type, message must be discarded
 - :cpp:enumerator:`whad::MessageType::GenericMsg`: generic message, must be dispatched to generic messages handler
 - :cpp:enumerator:`whad::MessageType::DiscoveryMsg`: discovery message, see :ref:`whad_discovery`
 - :cpp:enumerator:`whad::MessageType::DomainMsg`: domain-related message, must be dispatched to domain handler

Handling generic messages
-------------------------

Host-side message processing must determine the type of every incoming generic
message using :cpp:func:`whad::generic::GenericMsg::getType`, following the template below.
This function returns a value from the :cpp:enum:`whad::generic::MessageType`:

 - :cpp:enumerator:`whad::generic::MessageType::UnknownMsg`: unknown generic message, message must be discarded
 - :cpp:enumerator:`whad::generic::MessageType::CommandResultMsg`: command result message
 - :cpp:enumerator:`whad::generic::MessageType::VerboseMsg`: verbose message
 - :cpp:enumerator:`whad::generic::MessageType::DebugMsg`: debug message
 - :cpp:enumerator:`whad::generic::MessageType::ProgressMsg`: progress message

.. code-block:: c

    void generic_handler(NanoPbMsg p_message)
    {
        /* Wrap our NanoPbMsg into a GenericMsg instance. */
        whad::generic::GenericMsg generic_msg(p_message);

        switch (generic_msg.getType())
        {
            case whad::generic::MessageType::CommandResultMsg:
            {
                /* Process command result. */
                if (whad_generic_cmd_result_parse(p_message, &result_code) == WHAD_SUCCESS)
                {
                    /* Process command result. */
                }
                else
                {
                    /* Error while parsing command result. */
                }
            }
            break;

            case whad::generic::MessageType::VerboseMsg:
            {
                /* No default parsing method available yet :/ */
            }
            break;

            case whad::generic::MessageType::DebugMsg:
            {
                /* No default parsing method available yet :/ */
            }
            break;


            case whad::generic::MessageType::UnknownMsg:
            {
               /* Discard message. */
            }
            break;
        }
    }


.. _cpp_whad_domain_message_processing:

Handling domain messages
------------------------

Domain messages must be dispatched to their respective domain message handler,
using the :cpp:func:`whad::NanoPbMsg::getDomain` function that returns a value
of :cpp:enum:`whad::MessageDomain` enum. The following code template shows how such
a dispatching process can be implemented:

.. code-block:: C

    void dispatch_domain_message(NanoPbMessage message)
    {
        Message response;

        switch (message.getDomain())
        {
            /* Bluetooth Low Energy. */
            case whad::MessageDomain::DomainBle:
            {
                /* Forward message to BLE domain handler. */
                process_ble_message(message);
            }
            break;

            /* Bluetooth Low Energy. */
            case whad::MessageDomain::DomainDot15d4:
            {
                /* Forward message to Dot15d4 domain handler. */
                process_dot15d4_message(message);
            }
            break;

            /* Bluetooth Low Energy. */
            case whad::MessageDomain::DomainEsb:
            {
                /* Forward message to ESB domain handler. */
                process_esb_message(message);
            }
            break;

            /* Bluetooth Low Energy. */
            case whad::MessageDomain::DomainPhy:
            {
                /* Forward message to PHY domain handler. */
                process_phy_message(message);
            }
            break;

            /* Bluetooth Low Energy. */
            case whad::MessageDomain::DomainUnifying:
            {
                /* Forward message to Unifying domain handler. */
                process_unifying_message(message);
            }
            break;

            /* Don't support other domains. */
            default:
            {
                /* Tell the host we don't support this domain. */
                whad::generic::UnsupportedDomain resp(&response);
                whad::send(resp);
            }
            break;
        }
    }

.. important::

    If the hosts sends messages for an unsupported domain, the interface must
    answer with a :cpp:class:`whad::generic::UnsupportedDomain` class instance.


Message API reference
---------------------

.. doxygenfile:: inc/cpp/message.hpp
