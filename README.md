If You Need to Flash a Board Using Arduino IDE Download arduino-ide_2.3.8_Windows_64bit.exe

Add Boards Manager URLs File/preferences/additional boards manager
Hit the button to the right of the text box and paste url’s, then hit ok. Board libraries will begin to install in bottom right corner.

https://cos.thinkcreate.us/package_ch55xduino_mcs51_newest_cloudflare_index.json
https://raw.githubusercontent.com/DeqingSun/ch55xduino/ch55xduino/package_ch55xduino_mcs51_index.json
https://raw.githubusercontent.com/DeqingSun/ch55xduino/package_ch55xduino_mcs51_index.json
https://raw.githubusercontent.com/atc1441/atc1441.github.io/master/package_ch55xduino_index.json

Open Board Manager

Add both CH55XDuino titles that appear. 

Download Folder and Open File 

Download entire Wiegand_HEX26_Raw_Cred_Output_V13 folder and open .ino file in Arduino IDE 

Click check mark to compile code without flashing the USB

The right arrow will flash the convertor. Place into ISP mode first by shorting the 2 pins in the .JPG files while plugging in the usb device. (Sharp pointed tweezers work great)

Console at the bottom of the program with finish with a reset ok. 

The device has now been flashed with the file Wiegand_HEX26_Raw_Cred_Output_V13 and is ready for use.

Testing Only

Unplug and replug usb device into laptop.

Testing with notepad while usb is plugged into laptop should return a hex value that can be translated using https://www.ccdesignworks.com/wiegand_calc.htm
Subsequent scans of the same or different credentials should start on a new line automatically and is normal operation. 
