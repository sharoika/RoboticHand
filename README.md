# RoboticHand
This is a device that will pickup signals from pressure sensors on a hand. It is designed to allow individuals experiencing severe disability to communicate yes and no with only the slight movement of a hand.

The requirements are:
- a Raspberry Pi that is Bluetooth capable.
- An ESP32 Arduino device.
- A pressure sensor (resistance changes based on bend).

You connect the ESP32 from V++ to Pin1 of pressure sensor; then Pin2 of pressure sensor to ground through a 10 Kiloohm resistor; then you attach GPIO Pin 34 (ADC Pin) to the connection of Pin2 and the resistor.

The RaspberryPi just needs to be connected to a computer and the script should run to connect to the correct MAC Address. 

https://www.youtube.com/shorts/WBknikstMlg
