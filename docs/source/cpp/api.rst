Introduction
============

The WHAD C++ API provides a set of classes and functions to create and parse WHAD messages.
The `communication layer <cpp_comm_layer>`_ is used to send and receive such messages.

Code structure
--------------

The C API is composed of multiple files:

- Include files:
    - ``inc/cpp/whad.hpp``: main header file
    - ``inc/cpp/common.hpp``: header file related to the WHAD device discovery process
    - ``inc/cpp/message.hpp``: header file defining our base message class
    - ``inc/cpp/discovery/``: header files related to WHAD generic messages
    - ``inc/cpp/ble/``: header file related to WHAD BLE domain messages
    - ``inc/cpp/discovery/``: header files related to WHAD generic messages
    - ``inc/cpp/dot15d4/``: header file related to WHAD IEEE 802.15.4 domain messages
    - ``inc/cpp/esb/``: header file related to WHAD ESB domain messages
    - ``inc/cpp/generic/``: header files related to WHAD generic messages
    - ``inc/cpp/phy/``: header file related to WHAD PHY domain messages
    - ``inc/cpp/unifying/``: header file related to WHAD PHY domain messages
- Source files:
    - ``src/cpp/whad.cpp``: main WHAD library routines
    - ``src/cpp/common.cpp``: common WHAD classes
    - ``src/cpp/message.cpp``: WHAD message base class
    - ``src/cpp/discovery/``: WHAD discovery message classes
    - ``src/cpp/domains/ble/``: WHAD BLE domain message classes
    - ``src/cpp/domains/dot15d4/``: WHAD IEEE 802.15.4 domain message classes
    - ``src/cpp/domains/esb/``: WHAD ESB domain message classes
    - ``src/cpp/domains/phy/``: WHAD PHY domain message classes
    - ``src/cpp/domains/unifying/``: WHAD Logitech Unifying domain message classes


Processing incoming WHAD messages
---------------------------------

When an incoming WHAD message is returned by the library, following a call to
:cpp:func:`whad_get_message()`, it must be processed by the firmware. The first
thing to do is to determine the type of the received message by calling
:cpp:func:`whad_get_message_type()` and then if it is a domain-related message to
call the :cpp:func:`whad_get_message_domain()` to determine which domain it is
related to.

.. code-block:: c

    Message msg, response;
    whad_msgtype_t msg_type; 

    /* Do we have a message to process ? */
    if (whad_get_message(&msg) == WHAD_SUCCESS)
    {
        /* Wrap our message into a message container. */
        whad::NanoPbMsg whad_message(&msg);
        
        /* Determine message type. */
        switch (whad_message.getType())
        {
            /* Message is a generic one, process. */
            case whad::MessageType::GenericMsg:
            {
                /* Handle generic message. */
                generic_handler(whad_message);
            }
            break;

            /* Message is a discovery message, process. */
            case whad::MessageType::DiscoveryMsg:
            {
                /* Handle discovery message ... */
            }
            break;        

            /* Message is a discovery message, process. */
            case whad::MessageType::DomainMsg:
            {
                /* Dispatch to our supported domains. */
                switch (whad_message.getDomain())
                {
                    case whad::MessageDomain::DomainBle:
                    {
                        /* Dispatch to BLE handler. */
                        process_ble_message(whad_message);
                    }
                    break;

                    default:
                    {
                        /* Send back an error message (domain not supported). */
                        whad::generic::UnsupportedDomain response(&response);
                        whad::send(response);
                    }
                    break;
                }
            }
            break;         
        }
    }


Creating and sending a WHAD message
-----------------------------------

To create a WHAD message, one must simply instantiate a message class inherited
from :cpp:class:``NanoPbMsg``. Messages are then sent through a call to
:cpp:func:`whad::send`, they will be queued for transmission and transmitted
by the transport layer.

In the above code, we used the :cpp:class:`whad::generic::UnsupportedDomain` class to
create a WHAD generic command result message with a specific error code that tells
the host the required domain is not supported by our hardware. Since our hardware
is supposed to advertise its supported domains, the host is not supposed to send
such a message but we need to take care of all possibilities.

To send this message to the host, we call the :cpp:func:`whad::send`
function to enqueue the message and make it sent to the host whenever the
hardware is ready to transmit.

.. important::

    Dispatching domain-related messages is detailed in :ref:`cpp_whad_domain_message_processing`


WHAD Transport API reference
----------------------------

.. doxygenfile:: inc/cpp/whad.hpp
    :sections: define enums

.. doxygenfile:: src/cpp/whad.cpp