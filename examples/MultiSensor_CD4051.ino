
/*
---------------------------------------------------------------------------------------------------------------------------------------------------------------------
  Multi Sensors Example by Ferhan Y. (fehaan@hotmail.com)
 
  About:    This program uses multiSensor Library for sensing multiple analog inputs/sensors attached to the ESP/NodeMCU/Arduino powered boards
  Author:   Ferhan Y. 
  Email:    fehaan@hotmail.com
---------------------------------------------------------------------------------------------------------------------------------------------------------------------

This program reads data from multiple analog inputs using a multiplexer ic CD4051 connected to the ESP8266/NODEMCU or Arduino development board.
It utilizes a digital multiplexer to select different sensor channels and reads data from each channel.
The sensor data can then be called separately for each specific sensor channel/pin or printed over serial communication.

Pinouts CD4051 IC:
         +--+--+--+
  IN0 -|13        16|- VCC
  IN1 -|14         6|- INH/EN
  IN2 -|15  4051   7|- VEE
  IN3 -|12         8|- VSS
  IN4 -|1          3|- COM (OUT/IN)
  IN5 -|5         11|- S0/A
  IN6 -|2         10|- S1/B
  IN7 -|4          9|- S2/C
         +--+--+--+

Here's how you can connect the CD4051 IC to the ESP8266/NODEMCU board pins:

- VCC (Pin 16): Connect to 3.3V or 5V power source from the ESP8266/NODEMCU board.
- VSS (Pin 8): Connect to GND of the ESP8266/NODEMCU board.
- VEE (Pin 7): Connect to GND of the ESP8266/NODEMCU board.
- INH/EN (Pin 6): Connect to GND of the ESP8266/NODEMCU board. You can also control the enable/disable state through MCU. Connect it to either VCC or GND based on whether you want to enable or disable the IC. If you want the IC to be always enabled, connect it to GND.
- COM (Pin 3): This is the output pin of the multiplexer. Connect it to the analog pin of the mcu.
- S0, S1, S2 (Pins 11, 10, 9): These are the address selection pins. Connect them to digital pins of the mcu to read channels. 
                               You can configure these pins to select one of the 8 channels of the multiplexer.
-IN0...IN7: these are the channels pins connected to the analog sensors/inputs.

Functionality:
- Define constants for the number of sensors and multiplexer pins
- Configure multiplexer channel settings
- Read data from sensors through the multiplexer
- Implemented a timer to read sensor data periodically without using delay
- Utilize a helper function to check if a second has elapsed
---------------------------------------------------------------------------------------------------------------------------------------------------------------------
*/


// Class library
#include "multiSensors.h"

//-- Macro --//
#define TEMP_C(X) ((X * (5000 / 1024)) / 10)  // macro to convert sensor value to Celcius  unit
#define TEMP_F(X) ((TEMP_C(X) * 1.8) + 32)    // macro to convert sensor value to Farenheit unit

//-- Sketch Constants --//
#define S0 D4  // S0 pin of 4051 connected to D4 pin of the board
#define S1 D5  // S1 pin of 4051 connected to D4 pin of the board
#define S2 D6  // S2 pin of 4051 connected to D4 pin of the board

#define NUM_SENSORS 8  // total sensors attached to the multiplexer ic
enum sensor_names { AMBIENT_LIGHT_SENSOR,
                    AMBIENT_TEMP_SENSOR,
                    CURRENT_SENSOR,
                    AUDIO_SENSOR,
                    COLOR_SENSOR,
                    IR_SENSOR,
                    POT_SENSOR,
                    SOIL_MOISTURE_SENSOR
};

#define ANALOG_PIN A0  // analog pin of the mcu board connected to the multiplexer ic

//-- Sketch variables --//
int analogPin = ANALOG_PIN;  // assign analog pin

int numSensors = NUM_SENSORS;


// class instantance
multiSensors mySensors(S0, S1, S2, analogPin, numSensors);

void setup() {
  // add delay
  delay(500);

  // serial port initialization
  Serial.begin(115200);

  // initialize multiplexer ic
  mySensors.initialize();

  // output acknowledgement
  Serial.println("Ready.");
}

void loop() {


  //--- Directly call sensor channel --- //

  Serial.printf("Ambient light: %d lux.\n", mySensors.read(AMBIENT_LIGHT_SENSOR) * (5 / 1024));  // read sensor value for ambient light sensor value
  delay(100);
  Serial.printf("Temperature: %.1f C.\n", (float)(TEMP_C(mySensors.read(AMBIENT_TEMP_SENSOR))));  // read temperature sensor value in Celcius
  delay(1000);


  //--- OR read all channels and retieve value from an array --- //

  int* sensors_data;
  sensors_data = mySensors.readAll();
  Serial.printf("Audio sensor = %d.\n", sensors_data[AUDIO_SENSOR] | 0);
  delay(5000);
}
