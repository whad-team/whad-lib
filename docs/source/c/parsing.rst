Parsing WHAD messages
=====================

When a firmware receives a WHAD message, it must determine its type and dispatch
it accordingly.

Determining a message type
--------------------------

The :cpp:func:`whad_get_message_type` function must be called to discover the basic
type of a received message. The return value is one of the :cpp:enum:`whad_msgtype_t`
enum values:

 - ``WHAD_MSGTYPE_UNKNOWN``: unknown message type, message must be discarded
 - ``WHAD_MSGTYPE_GENERIC``: generic message, must be dispatched to generic messages handler
 - ``WHAD_MSGTYPE_DISCOVERY``: discovery message, see :ref:`whad_discovery`
 - ``WHAD_MSGTYPE_DOMAIN``: domain-related message, must be dispatched to domain handler

Handling generic messages
-------------------------

Host-side message processing must determine the type of every incoming generic
message using :cpp:func:`whad_generic_get_message_type`, following the template below.
This function returns a value from the :cpp:enum:`whad_generic_msgtype_t`:

 - ``WHAD_GENERIC_UNKNOWN``: unknown generic message, message must be discarded
 - ``WHAD_GENERIC_CMDRESULT``: command result message
 - ``WHAD_GENERIC_VERBOSE``: verbose message
 - ``WHAD_GENERIC_DEBUG``: debug message
 - ``WHAD_GENERIC_PROGRESS``: current progress by the firmware, value in range 0-100

.. code-block:: c

    void generic_handler(Message *p_message)
    {
        whad_result_code_t result_code;

        switch (whad_generic_get_message_type(p_message))
        {
            case WHAD_GENERIC_CMDRESULT:
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

            case WHAD_GENERIC_VERBOSE:
            {
                /* No default parsing method available yet :/ */
            }
            break;

            case WHAD_GENERIC_DEBUG:
            {
                /* No default parsing method available yet :/ */
            }
            break;


            case WHAD_GENERIC_UNKNOWN:
            {
               /* Discard message. */
            }
            break;
        }
    }


.. _whad_domain_message_processing:

Handling domain messages
------------------------

Domain messages must be dispatched to their respective domain message handler,
using the :cpp:func:`whad_get_message_domain` function that returns a value
of :cpp:enum:`whad_domain_t` enum. The following code template shows how such
a dispatching process can be implemented:

.. code-block:: C

    void dispatch_domain_message(Message *p_message)
    {
        Message response;

        switch (whad_get_message_domain(p_message))
        {
            /* Bluetooth Low Energy. */
            case DOMAIN_BTLE:
            {
                /* Forward message to BLE domain handler. */
                process_ble_message(p_message);
            }
            break;

            /* Bluetooth Low Energy. */
            case DOMAIN_DOT15D4:
            {
                /* Forward message to Dot15d4 domain handler. */
                process_dot15d4_message(p_message);
            }
            break;

            /* Bluetooth Low Energy. */
            case DOMAIN_ESB:
            {
                /* Forward message to ESB domain handler. */
                process_esb_message(p_message);
            }
            break;

            /* Bluetooth Low Energy. */
            case DOMAIN_PHY:
            {
                /* Forward message to PHY domain handler. */
                process_phy_message(p_message);
            }
            break;

            /* Bluetooth Low Energy. */
            case DOMAIN_UNIFYING:
            {
                /* Forward message to Unifying domain handler. */
                process_unifying_message(p_message);
            }
            break;

            /* Don't support other domains. */
            default:
            {
                /* Tell the host we don't support this domain. */
                whad_generic_cmd_result(&response, WHAD_RESULT_UNSUPPORTED_DOMAIN);
            }
            break;
        }
    }

.. important::

    If the hosts sends messages for an unsupported domain, the interface must
    answer with a :cpp:enumerator:`whad_result_code_t::WHAD_RESULT_UNSUPPORTED_DOMAIN`