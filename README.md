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

<img width="836" height="788" alt="{D3550DE7-3E9F-4D46-96A9-C850F0888C3A}" src="https://github.com/user-attachments/assets/d60bcc22-eb78-4c64-a555-c08693b1ee7d" />




### CHANGELOG

- Version v1.0.0 -  08/04/2025
    - first release
- Version v2.0.0 -  08/05/2025
    - Ctrl+click to copy sysex message only to buffer
    - Print out result now prints checksum
