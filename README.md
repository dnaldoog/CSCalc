# CSCalc

## Sysex Checksum Calculator

### Calculate checksums for 

- #### Additive type checksums (2's Complement).
    - This includes Roland/Yamaha
- #### Additive type checksums (1's Complement).
- #### Simple Summing (additive) AND 0x7f
- #### SONY checksums MSB
- #### XOR checksums
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

<img width="671" height="754" alt="{A55605B5-1D84-43E7-98C8-2769F07A8892}" src="https://github.com/user-attachments/assets/51c2fc19-f516-44e3-a0c6-f9f42135efaf" />


### CHANGELOG

- Version v7.0 -  08/17/2025
    - Can now send MIDI out of corrected checksum message
- Version v6.0 -  08/16/2025
    - Changed name from <span style="color:red">Sysex Checksum Calculator</span> to <span style="color:blue">CSCalc</span>
    - Changed logo
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

