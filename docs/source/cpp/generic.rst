Generic messages
================

Command result
--------------

Command results are messages sent by an interface to the host to indicate the
result of a requested operation. The :cpp:class:`whad::generic::CommandResult`
class provides an easy way to create such messages:

.. code-block:: C

    /* Create and send a command result message indicating an error. */
    whad::generic::CommandResult result(whad::generic::ResultCode::ResultError);
    whad::send(result);


Verbose messages
----------------

Verbose messages contain text that will be sent to the host and that will be
displayed when verbose mode is enabled by the user. These messages can be
created using the :cpp:class:`whad::generic::Verbose` class:

.. code-block:: C

    /* Create and send a verbose message. */
    whad::generic::Verbose verb_msg("This is some information for the user.");
    whad::send(verb_msg);


Debug messages
--------------

Debug messages are not intended to be displayed to the user and will only be
showed when debug mode is enabled on host-side. These messages can be created
through the :cpp:class:`whad::generic::Debug` function:

.. code-block:: C

    /* Create and send a debug message. */
    whad::generic::Debug debug_msg(1, "This is some information for the user.");
    whad::send(verb_msg); 


Generic API reference
---------------------

.. doxygennamespace:: whad::generic
    :members:
