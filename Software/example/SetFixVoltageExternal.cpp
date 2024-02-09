/*
  Example code that will just request a fixed voltage if there is external power (5V) or battery feeding the circuit VBUS
  Reset() is requested so that we can ask for available PDO again
  Important: Current can flow through load switch and charge the battery, or back current flow from the battery to the wall adapter
*/

#include <Arduino.h>
#include <AP33772.h>

AP33772 usbpd; // Automatically wire to Wire0,

bool state = 0;

void setup()
{
    Wire.setSDA(0);
    Wire.setSCL(1);
    Wire.begin();

    Serial.begin(115200);
    delay(1000); 		// Delay is need for the IC to obtain PDOs
    usbpd.begin(); 	// Start pulling the PDOs from power supply
    
    //Reset to request PDO again
    usbpd.reset();
    Wire.end();
    delay(1000); //Reboot time
    Wire.begin();
    usbpd.begin();
    
    usbpd.setVoltage(12000); //Set voltage at 12V
    usbpd.setMaxCurrent(4000);
    pinMode(25, OUTPUT); // Built in LED
    pinMode(23, OUTPUT); // Load Switch
    digitalWrite(23, HIGH);
}

void loop()
{
    //Your code here
}

