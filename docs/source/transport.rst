.. _comm_layer:

Transparent communication layer
===============================

The library provides a transparent communication layer that only supports UART
at the moment but could be extended in the future to other communication protocols.

Configuring the communication layer
-----------------------------------

In order to establish a communication between the hardware and the host computer,
the library communication layer must be correctly configured.

First, a :c:struct:`whad_transport_cfg_t` structure needs to be allocated and
filled to provide the library with 

- the maximum number of bytes that can be sent over UART in a single transmission
- a callback function the communication layer will use to send data through UART
- a callback function for the communication layer to notify the reception of a WHAD message

.. doxygenstruct:: whad_transport_cfg_t
    :members:

The following code configures a communication layer with a maximum of 16 bytes per
transmission and two callback functions implemented by the developer to handle UART
transmission and WHAD message processing.

Note that the UART transmission callback calls :c:func:`whad_transport_data_sent`
to notify the communication layer that the data has been successfully sent and it
is ready to send more data.

.. code-block:: c

    struct whad_transport_cfg_t my_config;

    void my_uart_tx(uint8_t *p_buffer, int size)
    {
        /* Handle UART TX of p_buffer ... */

        /* Call whad_transport_data_sent() when data has been sent. */
        whad_transport_data_sent();
    }

    void my_message_cb(Message *p_message)
    {
        /* Process incoming WHAD message. */
    }

    /* UART TX can only send a maximum of 16 bytes at a time. */
    my_config.max_txbuf_size = 16;

    /* Set up our UART TX callback. */
    my_config.pfn_data_send_buffer = my_uart_tx;

    /* And the incoming message callback. */
    my_config.pfn_message_cb = my_message_cb;

    /* Initialize our transport layer. */
    whad_transport_init(&my_config);


Queuing a WHAD message for transmission
---------------------------------------

Once configured, the library is able to send WHAD messages through a call to
:c:func:`whad_send_message()`. This message will be queued for transmission
and sent when the hardware is ready to transmit data over UART.

.. doxygenfunc:: whad_send_message

The following code shows how to send a WHAD message:

.. code-block:: c

    struct Message msg;

    /* Create a simple WHAD message. */
    whad_discovery_ready_resp(&msg);

    /* Queue it for transmission. */
    whad_send_message(&msg);


Sending pending messages
------------------------

The hardware must regularly flush any pending transmission data in order to keep
the transmission queue as small as possible to allow further messages to be sent.

A call to :c:func:`whad_transport_send_pending()` causes the communication
layer to transmit as many bytes as possible over the UART communication channel
to the host, through a call to the configured transmission callback function.

Once the data transmitted, the firmware must call
:c:func:`whad_transport_data_sent()` to allow further transmissions.

Feeding the library with received data
--------------------------------------

The communication layer is able to send messages over UART but
still needs to get notified when some data has been received. This is
done through a call to :c:func:`whad_transport_data_received()` in which
the received bytes are provided to the communication layer:

.. doxygenfunction:: whad_transport_data_received

Receiving WHAD messages
-----------------------

The communication layer is fed with incoming data from UART and will decode
messages as they arrive. If a valid WHAD message has been received, a call to
:c:func:`whad_get_message()` will succeed and provide the raw NanoPb message.

.. doxygenfunction:: whad_get_message

Basic communication loop
------------------------

The following code provides an example of a basic communication loop that
checks for pending messages to be sent and process incoming WHAD messages
as soon as they are received.

.. code-block:: c

    static struct Message *g_pending_message;
    struct Message msg;

    /* ... */

    while (true)
    {
        /* Check if we have a pending message to send. */
        if (g_pending_message != NULL)
        {
            if (whad_send_message(g_pending_message) == WHAD_SUCCESS)
            {
                /* Mark pending message as sent. */
                g_pending_message = NULL;
            }
        }

        /* Check if we have received a WHAD message. */
        if (whad_get_message(&msg) == WHAD_SUCCESS)
        {
            /* Process message through custom function. */
            dispatch_message(&msg);
        }

        /* Handle pending transmission data. */
        whad_transport_send_pending();
    }

    