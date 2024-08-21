Introducing WHAD C/C++ library
==============================

The WHAD C/C++ library provides all the features for WHAD message creation and
parsing as well as a transparent communication layer for UART that follows our
standard encapsulation protocol.

This library relies on `NanoPb <https://github.com/nanopb/nanopb>`_, an optimized
Protocol Buffers C library for embedded systems. 


Transparent communication layer
-------------------------------

The library implements an abstraction layer for UART communication, allowing the
developer to focus on message processing and let the library process the incoming
data, parse messages and send pending outgoing data.

This abstract layer can be configured to specify custom callback functions and
can adapt to any type of hardware and reception/transmission buffers. It uses its
own ring buffer implementation.

WHAD message creation and parsing
---------------------------------

The library provides a series of C functions to create and parse messages, for
all the supported domains as well as WHAD generic and discovery messages. It also
provides C++ wrappers with dedicated namespaces for the supported domains that
makes message creation and parsing easier.