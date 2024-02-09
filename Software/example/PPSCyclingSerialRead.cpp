/*
  Example code that will cycle through all possble PPS voltage starting at 4.2V
  Will print out current reading through the 10mOhm sense resistor and blink LED
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

  pinMode(25, OUTPUT); //Built in LED
  pinMode(23, OUTPUT); //Load Switch
  digitalWrite(23, HIGH); //Turn on Load Switch
  delay(2000); //Random delay, optional
  usbpd.printPDO();
  
}

void loop()
{
  for (int i = 4200; i < 20000; i = i + 40)
  {
    usbpd.setVoltage(i);
    delay(150);
    Serial.print("Set Voltage to (mV): ");
    Serial.println(i);
    Serial.print("Read voltage (mV): ");
    Serial.println(usbpd.readVoltage());
    Serial.print("Read current (mA): ");
    Serial.println(usbpd.readCurrent());

    //Blinking LED (25)
    if (state == 0)
    {
      digitalWrite(25, HIGH);
      state = 1;
    }
    else
    {
      digitalWrite(25, LOW);
      state = 0;
    }
  }
}
