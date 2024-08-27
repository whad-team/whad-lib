Generic messages
================

Command result
--------------

Command results are messages sent by an interface to the host to indicate the
result of a requested operation. The :cpp:func:`whad_generic_cmd_result` function
provides an easy way to create such messages:

.. code-block:: C

    Message msg;
    
    /* Create a command result message indicating an error. */
    whad_generic_cmd_result(&msg, WHAD_RESULT_ERROR);


Verbose messages
----------------

Verbose messages contain text that will be sent to the host and that will be
displayed when verbose mode is enabled by the user. These messages can be
created using the :cpp:func:`whad_verbose` function (which is a wrapper for the
:cpp:func:`whad_generic_verbose_message` function):

.. code-block:: C

    /* Create a verbose message. */
    whad_verbose("This is some information for the user.");


Debug messages
--------------

Debug messages are not intended to be displayed to the user and will only be
showed when debug mode is enabled on host-side. These messages can be created
through the :cpp:func:`whad_generic_debug_message` function:

.. code-block:: C

    Message msg;

    /* Create a debug message. */
    whad_generic_debug_message(&msg, 1, "Some debug message.");   


Generic API reference
---------------------

.. doxygenfile:: inc/generic.h
    :sections: define enum

.. doxygenfile:: src/generic.c