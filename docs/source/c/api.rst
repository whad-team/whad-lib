Introduction
============

The WHAD C API provides a set of functions to create and parse WHAD messages.
The `communication layer <comm_layer>`_ is used to send and receive such messages.

Code structure
--------------

The C API is composed of multiple files:

- Include files:
    - ``inc/whad.h``: main header file
    - ``inc/types.h``: header file containing most of the main types used by the API
    - ``inc/discovery.h``: header file related to the WHAD device discovery process
    - ``inc/generic.h``: header file related to WHAD generic messages
    - ``inc/ringbuf.h``: header file providing a ring buffer implementation
    - ``inc/transport.h``: header file providing the transparent communication layer functions
    - ``inc/domains/ble.h``: header file related to WHAD BLE domain messages
    - ``inc/domains/dot15d4.h``: header file related to WHAD IEEE 802.15.4 domain messages
    - ``inc/domains/esb.h``: header file related to Nordic Semiconductor Enhanced ShockBurst protocol
    - ``inc/domains/phy.h``: header file related to WHAD PHY domain (raw modulation/demodulation)
    - ``inc/domains/unifying.h``: header file related to WHAD Logitech Unifying domain messages
- Source files:
    - ``src/whad.c``: main WHAD library routines
    - ``src/discovery.c``: WHAD discovery messages creation and parsing
    - ``src/generic.c``: WHAD generic messages creation and parsing
    - ``src/ringbuf.c``: WHAD internal ring buffer implementation
    - ``src/transport.c``: WHAD transparent communication layer
    - ``src/domains/ble.c``: WHAD BLE messages creation and parsing
    - ``src/domains/dot15d4.c``: WHAD IEEE 802.15.4 messages creation and parsing
    - ``src/domains/esb.c``: WHAD ESB messages creation and parsing
    - ``src/domains/phy.c``: WHAD PHY messages creation and parsing
    - ``src/domains/unifying.c``: WHAD Unifying messages creation and parsing


Processing incoming WHAD messages
---------------------------------

When an incoming WHAD message is returned by the library, following a call to
:c:func:`whad_get_message()`, it must be processed by the firmware. The first
thing to do is to determine the type of the received message by calling
:c:func:`whad_get_message_type()` and then if it is a domain-related message to
call the :c:func:`whad_get_message_domain()` to determine which domain it is
related to.

.. code-block:: c

    Message msg, response;
    whad_msgtype_t msg_type; 

    /* Do we have a message to process ? */
    if (whad_get_message(&msg) == WHAD_SUCCESS)
    {
        /* Yes, determine type. */
        msg_type = whad_get_message_type(&msg);

        switch (msg_type)
        {
            /* Message is a generic one, process. */
            case WHAD_MSGTYPE_GENERIC:
            {
                /* Handle generic message ... */
            }
            break;

            /* Message is a discovery message, process. */
            case WHAD_MSGTYPE_DISCOVERY:
            {
                /* Handle discovery message ... */
            }
            break;        

            /* Message is a discovery message, process. */
            case WHAD_MSGTYPE_DOMAIN:
            {
                /* Dispatch to our supported domains. */
                switch (whad_get_message_domain(&msg))
                {
                    case DOMAIN_BTLE:
                    {
                        /* Dispatch to BLE handler. */
                        process_ble_message(&msg);
                    }
                    break;

                    default:
                    {
                        /* Return an error message (domain not supported). */
                        whad_generic_cmd_result(&response, WHAD_RESULT_UNSUPPORTED_DOMAIN);
                        whad_send_message(&response);
                    }
                    break;
                }
            }
            break;         
        }
    }


Creating and sending a WHAD message
-----------------------------------

To create a WHAD message, one must use the `whad_<domain>_...` functions exposed
by the WHAD generic, discovery, and various supported domains header files. The
messages must be sent following the WHAD protocol, and are basically created and
then queued for transmission.

In the above code, we used the :c:func:`whad_generic_cmd_result()` function to
create a WHAD generic command result message with a specific error code that tells
the host the required domain is not supported by our hardware. Since our hardware
is supposed to advertise its supported domains, the host is not supposed to send
such a message but we need to take care of all possibilities. This call will
fill our ``Message`` structure with all the required information, ready to be
sent to the host. 

To send this message to the host, we call the :c:func:`whad_send_message()`
function to enqueue the message and make it sent to the host whenever the
hardware is ready to transmit.


