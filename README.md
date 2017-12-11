# Quigo - Flight Search Engine
Quigo is an advanced flight search engine based on C++, and is fully featured to perform searches to find direct and connected flights between airports, as well as sort the results in terms of fare, arrival time or duration as per user request.

## Current Limitations (and Scope)
* User-account feature is limited to admin. New user types/roles can be added using the same base class, and specidic functionality allowed can be allowed to them.
* Password stored is not encrypted. The password can be accessed if the associated binary file is opened. An encryption-decryption algorithm can be implemented while storing and retrieving passwords.
* Name of airports, airlines are not shown, instead only their codes are shown. Their names can be incorporated easily by adding referential-class holding their names.
