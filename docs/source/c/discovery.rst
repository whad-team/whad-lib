WHAD Device discovery
=====================

When a host computer starts communicating with a WHAD interface, it sends a series
of message to discover its characteristics and its supported domains in order
to tailor the host features and match the capabilities exposed by the interface.

Discovery of interface characteristics
--------------------------------------

First, the host sends a *DeviceInfoQuery* message to the WHAD interface that is
expected to responds with a *DeviceInfoResp* message. This message must provide
the following information:

- the device type 
- the device unique ID
- the minimum supported version of WHAD protocol
- the device maximum communication speed
- the author name (limited to 64 characters)
- the firmware project URL (linited to 256 characters)
- the firmware major version number
- the firmware minor version number
- the firmware revision number
- a list of capabilities

To build such a message, we need to define first our capabilities:

.. code-block:: c

    const whad_domain_desc_t CAPABILITIES[] = {
        {
            /* We support the Bluetooth Low Energy wireless protocol. */
            DOMAIN_BTLE,

            /* For this protocol, we are able to sniff, inject and emulate
               central and peripheral roles. */
            (whad_capability_t)(CAP_SNIFF | CAP_INJECT | CAP_SIMULATE_ROLE),

            /* We define the list of supported commands, based on NanoPb command values. */
            (
            CMD(ble_BleCommand_SniffAdv) |
            CMD(ble_BleCommand_SniffConnReq) |
            CMD(ble_BleCommand_SniffActiveConn) |
            CMD(ble_BleCommand_Start) |
            CMD(ble_BleCommand_Stop) |
            CMD(ble_BleCommand_SendRawPDU) |
            CMD(ble_BleCommand_SendPDU) |
            CMD(ble_BleCommand_CentralMode) |
            CMD(ble_BleCommand_PeripheralMode) |
            CMD(ble_BleCommand_ConnectTo) |
            CMD(ble_BleCommand_Disconnect) |
            CMD(ble_BleCommand_PrepareSequence) |
            CMD(ble_BleCommand_TriggerSequence) |
            CMD(ble_BleCommand_DeleteSequence) |
            CMD(ble_BleCommand_ScanMode)

            )
        },

        /* End of supported domains, MUST be there to mark the end of this list. */
        {DOMAIN_NONE, CAP_NONE, 0x00000000}
    };

Once our capabilities defined, we can build the response message:

.. code-block:: c


    Message response;
    whad_result_t result;

    /* Create a device info response. */
    result = whad_discovery_device_info_resp(
        /* Pointer to our response message. */
        &response,

        /* Butterfly device, does not really matter. */                              
        discovery_DeviceType_Butterfly,

        /* "Unique" device ID, usually customized */
        (uint8_t *)"MyAwesomeDevice",

        /* Supports WHAD protocol v2 */
        2,

        /* Max speed for our UART hw */
        115200,

        /* Firmware author. */
        "John Doe <jdoe@example.org",

        /* Firmware project URL. */
        "https://github.com/whad-team/demofw",

        /* Firmware version: major, minor, rev. */
        1, 0, 0,

        /* Capabilities as defined above. */
        CAPABILITIES
    );

.. note::

    The ``CAPABILITIES`` structure created above is used by both :c:func:`whad_discovery_device_info_resp`
    and :c:func:`whad_discovery_domain_info_resp` to provide the host with the supported
    domains and the related interface capabilities for the first one, and the supported
    commands for a specific domain for the second one.

Discovery of supported commands for a given domain
--------------------------------------------------

Once the host has discovered the device' supported domains and its capabilities,
it queries the WHAD interface to retrieve the implemented commands for each
supported domain by sending multiple *DeviceDomainInfoQuery* messages.

Each of these messages must be answered by the WHAD interface with a
*DeviceDomainInfoResp* specifying the supported commands for the requested
domain. This message can be created through the :c:func:`whad_discovery_domain_info_resp`
function, as shown below:

.. code-block:: c

    void process_discovery_message(Message *message)
    {
        whad_result_t result;
        whad_domain_t domain;
        Message response;

        /* ... */
        
        /* Process any discovery message. */
        switch(whad_discovery_get_message_type(message))
        {
            /* DeviceDomainInfoQuery message. */
            case WHAD_DISCOVERY_DOMAIN_INFO_QUERY:
            {
                /* Parse incoming message. */
                if (whad_discovery_domain_info_query_parse(message, &domain) == WHAD_SUCCESS)
                {
                    /* Fill response message with DeviceDomainInfoResp. */
                    whad_discovery_domain_info_resp(
                        &response,
                        domain,
                        CAPABILITIES
                    );
                }
                else
                {
                    /* Error. */
                    whad_generic_cmd_result(&response, WHAD_RESULT_ERROR);
                }
            }
            break;

            /* ... */
        }

    }


.. note::

    :c:func:`whad_discovery_domain_info_resp` will pick the corresponding
    supported commands from the provided ``capabilities`` array and build
    a valid message from it.


Transport speed update
----------------------

The WHAD interface, in its *DeviceInfoResp* message, provides the host with its
maximum communication speed and the host can at anytime decide to switch to that
speed to get faster communication. This speed change is requested by the host
through a *SetTransportSpeed* message. This message must be acknowledged by
the WHAD interface before setting up the hardware to use this new speed setting.

First, the WHAD interface needs to create and send a generic *CommandResult*
message with a result code of ``WHAD_RESULT_SUCCESS`` and then setup the new
communication speed. Once the new speed configured and in use, the WHAD
interface must send a new *DeviceReadyResp* message to let the host know that
it is ready to operate.

.. code-block:: c

    Message response;


    /* Send a success result code. */
    whad_generic_cmd_result(&response, WHAD_RESULT_SUCCESS);
    whad_send_message(&response);

    /* Re-configure communication hardware with new speed. */

    /* Once done and ready, send a DeviceReadyResp to host. */
    whad_discovery_device_ready_resp(&response);
    whad_send_message(&response);


Discovery message processing template
-------------------------------------

The following code is a basic code template for processing discovery messages:

.. code-block:: c

    void process_discovery_message(Message *message)
    {
        whad_result_t result;
        whad_domain_t domain;
        uint32_t proto_version;
        Message response;
        
        /* Process any discovery message. */
        switch(whad_discovery_get_message_type(message))
        {

            /* DeviceInfoQuery message. */
            case WHAD_DISCOVERY_DEVICE_INFO_QUERY:
            {
                /* Parse incoming message. */
                if (whad_discovery_device_info_query_parse(message, &proto_version) == WHAD_SUCCESS)
                {
                    /* Make sure we support the provided protocol version. */
                    if (proto_version >= 2)
                    {
                        /* Fill response message with DeviceInfoResp. */
                        whad_discovery_domain_info_resp(
                            &response,
                            domain,
                            CAPABILITIES
                        );
                    }
                    else
                    {
                        /* Client protocol version is too old. */
                        whad_generic_cmd_result(&response, WHAD_RESULT_ERROR);
                    }
                }
                else
                {
                    /* Error. */
                    whad_generic_cmd_result(&response, WHAD_RESULT_ERROR);
                }
            }
            break;

            /* DeviceDomainInfoQuery message. */
            case WHAD_DISCOVERY_DOMAIN_INFO_QUERY:
            {
                /* Parse incoming message. */
                if (whad_discovery_domain_info_query_parse(message, &domain) == WHAD_SUCCESS)
                {
                    /* Fill response message with DeviceDomainInfoResp. */
                    whad_discovery_domain_info_resp(
                        &response,
                        domain,
                        CAPABILITIES
                    );
                }
                else
                {
                    /* Error. */
                    whad_generic_cmd_result(&response, WHAD_RESULT_ERROR);
                }
            }
            break;

            /* SetTransportSpeed */
            case WHAD_DISCOVERY_SET_TRANSPORT_SPEED:
            {
                /* Send a success result code. */
                whad_generic_cmd_result(&response, WHAD_RESULT_SUCCESS);
                whad_send_message(&response);
                whad_transport_send_pending();

                /* Re-configure communication hardware with new speed. */

                /* Once done and ready, send a DeviceReadyResp to host. */
                whad_discovery_device_ready_resp(&response);
                whad_send_message(&response);
            }
            break;

            /* DeviceResetQuery */
            case WHAD_DISCOVERY_DEVICE_RESET_QUERY:
            {
                /* Reset WHAD interface state. */
                interface_reset_state();

                /* Send a DeviceReadyResp. */
                whad_discovery_ready_resp(&response);
            }
            break;

            default:
            {
                /* Unsupported command. */
                whad_generic_cmd_result(&response, WHAD_RESULT_ERROR);
            }
            break;
        }
    }   