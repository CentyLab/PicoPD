/*
  Example code allow you to request voltage through Serial
  Important: Select "No Line Ending" in Serial Monitor
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
  usbpd.setVoltage(12000); // Set voltage at 12V
  usbpd.setMaxCurrent(5000);
  delay(2000);
  pinMode(25, OUTPUT); // Built in LED
  pinMode(23, OUTPUT); // Load Switch
  digitalWrite(23, HIGH);
  usbpd.printPDO();
}

void loop()
{
int input;

if(Serial.available())
{
  input = Serial.parseInt(SKIP_ALL);
  usbpd.setVoltage(input);
  Serial.print("Received voltage (mV): ");
  Serial.println(input);
  Serial.print("Current reading (mA) ");
  Serial.println(usbpd.readCurrent());
}
}
