.. _cpp_whad_discovery:

WHAD Device discovery
=====================

When a host computer starts communicating with a WHAD interface, it sends a series
of message to discover its characteristics and its supported domains in order
to tailor the host features and match the capabilities exposed by the interface.

.. _cpp_whad_discovery_cap:

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

.. code-block:: cpp

    using namespace whad::discovery;

    DeviceInfoResp(
        Devices::Butterfly,

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

    The ``CAPABILITIES`` structure created above is used by both :cpp:class:`whad::discovery::DeviceInfoResp`
    and :cpp:class:`whad::discovery::DomainInfoResp` to provide the host with the supported
    domains and the related interface capabilities for the first one, and the supported
    commands for a specific domain for the second one.

Discovery of supported commands for a given domain
--------------------------------------------------

Once the host has discovered the device' supported domains and its capabilities,
it queries the WHAD interface to retrieve the implemented commands for each
supported domain by sending multiple *DeviceDomainInfoQuery* messages.

Each of these messages must be answered by the WHAD interface with a
*DeviceDomainInfoResp* specifying the supported commands for the requested
domain. This message can be created through the :cpp:class:`whad::discovery::DomainInfoResp`
class, as shown below:

.. code-block:: cpp

    void discovery_handler(NanoPbMsg message)
    {
        NanoPbMsg *response = NULL;

        /* ... */
        
        /* Wrap our NanoPbMsg into a GenericMsg instance. */
        whad::discovery::DiscoveryMsg disc_msg(p_message);

        switch (disc_msg.getType())
        {
            /* DeviceDomainInfoQuery message. */
            case whad::discovery::DomainInfoQueryMsg:
            {
                /* Parse our domain info query. */
                whad::discovery::DomainInfoQuery domain_info_query()

                if (domain_info_query.getDomain() == whad::discovery::Domains::DomainBtLE)
                {
                    response = new whad::discovery::DomainInfoResp(
                        domain_info_query.getDomain(),
                        CAPABILITIES
                    );
                }
                else
                {
                    /* Send an error if domain is not supported. */
                    response = new whad::generic::Error();
                }
            }
            break;

            /* ... */
        }

    }


.. note::

    :cpp:class:`whad::discovery::DomainInfoResp` will pick the corresponding
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

.. code-block:: cpp

    NanoPbMsg response = NULL;


    /* Send a success result code. */
    response = new whad::generic::Success();
    whad::send(*response);
    delete response;

    /* Re-configure communication hardware with new speed. */

    /* Once done and ready, send a DeviceReadyResp to host. */
    response = new whad::discovery::ReadyResp();
    whad::send(*response);
    delete response;


Discovery message processing template
-------------------------------------

The following code is a basic code template for processing discovery messages:

.. code-block:: cpp

    void discovery_handler(NanoPbMsg message)
    {
        NanoPbMsg *response = NULL;

        /* Parse the incoming message as a discovery message. */
        whad::discovery::DiscoveryMsg disc_msg(message);
        
        /* Process any discovery message. */
        switch(disc_msg.getType())
        {

            /* DeviceInfoQuery message. */
            case whad::discovery::MessageType::DeviceInfoQueryMsg:
            {
                /* Parse message as device info query. */
                whad::discovery::DeviceInfoQuery query(message);

                /* Make sure we support the provided protocol version. */
                if (query.getVersion() >= 2)
                {
                    /* Fill response message with DeviceInfoResp. */
                    response = new whad::discovery::DeviceInfoResp(
                        query.getDomain(),
                        CAPABILITIES
                    )
                }
                else
                {
                    /* Client protocol version is too old. */
                    response = new whad::generic::Error();
                }

            }
            break;

            /* DeviceDomainInfoQuery message. */
            case whad::discovery::MessageType::DomainInfoQueryMsg:
            {
                /* Parse incoming message. */
                whad::discovery::DomainInfoQuery query(message);

                response = new whad::discovery::DomainInfoResp(
                    query.getDomain(),
                    CAPABILITIES
                );
            }
            break;

            /* SetTransportSpeed */
            case whad::discovery::MessageType::SetSpeedMsg:
            {
                /* Send a success result code. */
                response = new whad::generic::Success();
                whad::send(*response);
                delete response;

                /*"
                 * Re-configure communication hardware with new speed:
                 *
                 * 1. Flush current UART buffer
                 * 2. Re-configure UART interface
                 **/

                /* Once done and ready, send a DeviceReadyResp to host. */
                response = new whad::discovery::ReadyResp();
            }
            break;

            /* DeviceResetQuery */
            case whad::discovery::MessageType::DeviceResetMsg:
            {
                /* Reset WHAD interface state. */
                interface_reset_state();

                /* Send a DeviceReadyResp. */
                response = new whad::discovery::ReadyResp();
            }
            break;

            default:
            {
                /* Unsupported command. */
                response = whad::generic::Error();
            }
            break;
        }

        /* Send response. */
        whad::send(*response);
        delete response;
    }

Discovery API reference
-----------------------

.. doxygennamespace:: whad::discovery
    :members: