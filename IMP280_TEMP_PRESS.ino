#include <Arduino.h>
#include <BMx280I2C.h>
#include <Wire.h>
#define I2C_ADDRESS  0x76
BMx280I2C bmx280(I2C_ADDRESS);
void setup( )  {
Serial.begin(9600);
while(!Serial);
Wire.begin( );
if  (! bmx280.begin( ) )
{
Serial.println("begin( )  failed.check your bmx280  interface  and i2c  address.");
while(1);
}
bmx280.resetToDefaults();
bmx280.writeOversamplingPressure(BMx280MI::OSRS_P_x16);
bmx280.writeOversamplingTemperature(BMx280MI::OSRS_T_x16);
bmx280.measure();
bmx280.hasValue();
}
void loop( )
  {
delay(1000);
if (!bmx280.measure( ) )
{
Serial.println("could not start measurement, is a  measurement  already running?");
return;
}
do
{
delay(100);
}   while  (!bmx280.hasValue( )  );
Serial.print("Pressure"); 
Serial.println(bmx280.getPressure( )  );
Serial.print("pressure (64 bit): ");
Serial.println(bmx280.getPressure64( )  );
Serial.print("temperature:  ");
Serial.println(bmx280.getTemperature( ) );
}