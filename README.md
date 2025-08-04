### Sysex Checksum Calculator

#### Calculate checksums for 

- ### Additive type checksums.
    - This includes Roland/Yamaha
- ### XOR checksums
    - Many manufacturers also use this system.

----
Paste in a sysex string and enter the start byte for the data
The end byte can either be determined using the subsequent bytes from start
or determined by counting back from the end.

***Example***. To calculate the Roland checksum for the sysex string:

````f0 41 10 57 12 03 00 01 10 31 00 f7````

The checksum (0x3B) can be calculated by entering in:

- Start Byte Index=5 : End Offset =2 `03 00 01 10 31`
- Start Byte Index=5 : Length =5 `03 00 01 10 31`

<img width="821" height="639" alt="{5208AB39-9C1C-482B-989E-5F933F1541EE}" src="https://github.com/user-attachments/assets/460cbb87-95f4-4d08-b271-2e16939b99b9" />


### CHANGELOG

- Version v1.0.0 first release 08/04/2025
