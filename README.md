# Otrv4 Toolkit

The OTR Toolkit is useful for analyzing and/or forging OTR messages.
It  makes  absolutely  sure  that  transcripts  of OTR conversations are really
easy to forge after the fact [Note that during an OTR conversation, messages
can't be forged without real-time access to the secret keys on the participants'
computers,  and in that case, all security has already been lost].
Easily-forgeable transcripts help us provide the "Deniability" property: if
someone claims you said something over OTR, they'll have no proof, as anyone at
all can modify a transcript  to make it say whatever they like, and still have
all the verification come out correctly.
