## Sysex Checksum Calculator

### Calculate checksums for 

- #### Additive type checksums (2's Complement).
    - This includes Roland/Yamaha
- #### Additive type checksums (1's Complement).
- #### Simple Summing (additive) AND 0x7f
- #### SONY checksums MSB
- #### XOR checksums
- #### Kawai K5 checksums
    - Many manufacturers also use this system.
----
Paste in a sysex string and enter the start byte for the data.<BR>
The end byte can either be determined using the subsequent bytes from start
or determined by counting back from the end.

***Example***. To calculate the Roland checksum for the sysex string:

````f0 41 10 57 12 03 00 01 10 31 00 f7````

The checksum (0x3B) can be calculated by entering in:

- Start Byte Index=5 : End Offset =2 `03 00 01 10 31`
- Start Byte Index=5 : Length =5 `03 00 01 10 31`

<img width="947" height="760" alt="{AC91A0FA-FDE7-4A42-A94D-5FDC6D67201F}" src="https://github.com/user-attachments/assets/1ba99780-cf25-4a6a-9d5c-41ba5ebcb4a5" />

### CHANGELOG

- Version v5.1 -  08/09/2025
    - removed Kawai K5 checksum code
- Version v5.0 -  08/08/2025
    - Slight refactor of Roland checksum
    - Added Kawai K5(m) checksum
- Version v4.0 -  08/07/2025
    - Using Slider() for star/end parameters
    - Added SONY MSB checksum
- Version v3.0.0 -  08/07/2025
    - Changed to lighter theme
    - Added 1's complement checksum
    - Added Simple summing checksum
    - Moved sysex input window to main window for easier editing.
- Version v2.0.0 -  08/05/2025
    - Ctrl+click to copy sysex message only to buffer
    - Print out result now prints checksum
- Version v1.0.0 -  08/04/2025
    - first release

