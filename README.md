# Otrv4 Toolkit

[![Build Status](https://travis-ci.org/otrv4/otrv4_toolkit.svg?branch=master)](https://travis-ci.org/otrv4/otrv4_toolkit)

This is OTRv4 toolkit implementation.

The OTR Toolkit is useful for analyzing and/or forging Otrv4 messages.

It  makes  absolutely  sure  that  transcripts  of OTR conversations are really
easy to forge after the fact (note that during an OTR conversation, messages
can't be forged without real-time access to the secret keys on the participants'
computers,  and in that case, all security has already been lost).

Easily-forgeable transcripts help us provide the "Deniability" property: if
someone claims you said something over OTR, they'll have no proof, as anyone at
all can modify a transcript  to make it say whatever they like, and still have
all the verification come out correctly.

## Build

Install the following dependencies:
* libglib2.0-dev
* libdecaf
* libsodium-dev
* libotr 4.x
* libotr4
* libgcrypt 1.8.0 or newer

To generate project configuration:
```
$ autoreconf --install
```

To configure the project:
```
$ ./configure
```

To build and install:
```
$ make && make install
```

To run the tests:
```
$ make test
```
