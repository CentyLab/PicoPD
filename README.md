# PicoPD
Pico PD is a development board for USB Power Delivery development with Raspberry Pi Pico footprint. The board can help you negotiate voltage from USB PD 2.0, 3.0, and 3.1 with PPS (programable power supply) up to 5A of current at 20V max. The board feature input current/voltage reading as well as power switch to cut of the current to external devices.

# Quick links
[AP33772 Library](https://github.com/CentyLab/AP33772-Cpp)

[PicoPD Pinout](#picopd-pinout)

[Setup for AP33772 objects](#setup-for-ap33772-objects)

[Basic AP33772 functions](#basic-ap33772-functions)

[Important note](#important-note)

[Arduino IDE setup](#arduino-ide-setup)

# Pin out
![pinout](https://github.com/CentyLab/PicoPD/blob/main/Hardware/PicoPD%20Pin%20Out.png?raw=true)


# Setup for AP33772 objects
To use AP33772 IC with the library, first you need to create a `usbpd` object. Then set up your I2C pins and start collecting the power profiles from your charger. Ensure your delay after `Wire.begin()` is more than 500ms for stable PDOs request. Enable pin 23 to allow VBUS pass-through.
```
AP33772 usbpd; // Automatically wire to Wire0

void setup()
{
  Wire.setSDA(0);
  Wire.setSCL(1);
  Wire.begin();
  delay(1000); 		// Delay is needed for the IC to obtain PDOs
  usbpd.begin(); 	// Start pulling the PDOs from power supply

  pinMode(25, OUTPUT); // Built in LED
  pinMode(23, OUTPUT); // Load Switch
  digitalWrite(23, HIGH); // Turn on VBUS pin
}
```

# Basic AP33772 functions
Common functions are:
```
setVoltage(int targetVoltage)       //Set voltage, read libary for logic flow
setMaxCurrent(int targetMaxCurrent) //Allow current limit if source has that capability
readVoltage()                       //Return voltage in mV
readCurrent()                       //Return current in mA
printPDO()                          //Print out PDOs in Serial
```

Set over tempearture protection
```
usbpd.setOTPTHR(100);               //Turn off output if NTC detect 100C or above
usbpd.setMask(OTP_EN);              //Enable Over Temp Protection flag
```

# Important note
After programming, you will need to disconnect the board and reconnect to the charger to re-request the PDOs profile. Else, the system will just get 5V after flashing.

# Arduino IDE setup
Open Arduino IDE, select File -> Preference
![Preference](https://github.com/CentyLab/PicoPD/blob/main/Documentation/doc1.png?raw=true)

Copy this line below and place in "Aditional Boards Manager URLs" -> OK. This will allow you to pull the Earlephilhower Pico core that work with the AP33772 library.

```
https://github.com/earlephilhower/arduino-pico/releases/download/global/package_rp2040_index.json
```
![boardmanagerURL](https://github.com/CentyLab/PicoPD/blob/main/Documentation/doc2.png?raw=true)

From Board Manager, search for "Pico" and install the "Raspberry Pi Pico/RP2040" core by Earlephilhower

![boardmanager](https://github.com/CentyLab/PicoPD/blob/main/Documentation/doc3.png?raw=true)

Now from Tool -> Board -> Raspberry Pi Pico/RP2040 -> Raspberry Pi Pico

![boardmanager](https://github.com/CentyLab/PicoPD/blob/main/Documentation/doc4.png?raw=true)

Now download the latest AP33772 library as a Zip file

```
https://github.com/CentyLab/AP33772-Cpp
```
![ap33772lib](https://github.com/CentyLab/PicoPD/blob/main/Documentation/doc5.png?raw=true)

Import the AP33772 library into your Arduino IDE. Sketch -> Include library -> Add .ZIP Library ...

![importlib](https://github.com/CentyLab/PicoPD/blob/main/Documentation/doc6.png?raw=true)

Now you start using the Example code in File -> Examples -> AP33772-Cpp-main. The example is ready to compile and flash on to your PicoPD.
![importlib](https://github.com/CentyLab/PicoPD/blob/main/Documentation/doc8.png?raw=true)