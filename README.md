# MUltiSensors v1.2.0 Library
using **CD4051** ic for multiple analog sensors with **ESP8266**, **NodeMCU**, and **Arduino** development boards.

**Author:** Ferhan Y. (fehaan@hotmail.com)

This Library helps to read sensors/input data from multiple analog inputs or sensors using a multiplexer ic CD4051 connected to the ESP8266/NODEMCU or Arduino boards.
It utilizes a digital multiplexer to select different sensing channels and read its value.
The sensor data can be called separately for each specific sensor channel/pin or as an array for programming needs.


 ## Pinouts CD4051 IC:
```
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

```
Here's how you can connect the CD4051 IC to the ESP8266/NODEMCU board pins:

- **VCC (Pin 16):** Connect to 3.3V or 5V power source from the ESP8266/NODEMCU board.
- **VSS (Pin 8):** Connect to GND of the ESP8266/NODEMCU board.
- **VEE (Pin 7):** Connect to GND of the ESP8266/NODEMCU board.
- **INH/EN (Pin 6):** Connect to GND of the ESP8266/NODEMCU board. You can also control the enable/disable state through MCU. Connect it to either VCC or GND based on whether you want to enable or disable the IC. If you want the IC to be always enabled, connect it to GND.
- **COM (Pin 3):** This is the output pin of the multiplexer. Connect it to the analog pin of the ESP8266/NODEMCU board where you want to read the multiplexed analog signal.
- **S0, S1, S2 (Pins 11, 10, 9):** These are the channel/address selection pins. Connect them to digital pins of the ESP8266/NODEMCU board. 
                               You can configure these pins to select one of the 8 channels of the multiplexer.
- **IN0...IN7:** these are the pins conencted with the analog sensors/inputs.

## Functionality:

I have developed a multidimensional array to use the channel addresses in order to save time and maintain accuracy of sensor data. This is described as following.

### Multiplexer Channels (a.k.a. Multiplexer Truth Table)
```
// Multiplexer channel selection configurations
  int mux_channels[8][3] = {
    { 0, 0, 0 },  //channel 0
    { 1, 0, 0 },  //channel 1
    { 0, 1, 0 },  //channel 2
    { 1, 1, 0 },  //channel 3
    { 0, 0, 1 },  //channel 4
    { 1, 0, 1 },  //channel 5
    { 0, 1, 1 },  //channel 6
    { 1, 1, 1 }   //channel 7
  };
```

### Instantiate the Library:
You can easily create an instance of the library by parsing the following parameters

- **S0,S1,S3** IC channel/address selection pins connected to the ESP/NODEMCU/ARDUINO board pins.
- **AnalogPin**: refers to the analog pin of the microcontroller board connected with the multiplexer**CD4051** ic.
- **numSensors**: refers to the total sensors attached to the multiplexer **CD4051** ic.

```
multiSensors::multiSensors(int, int, int, int, int);
```
**Example:**
```
multiSensors mySensors(S0, S1, S2, AnalaogPin, numSensors);
```
### Initialize the CD4051 Multiplexer IC:
I have provided an easy way to initialize the multiplexer ic in order to start reading the sensors data accurately.
```
void setup(){

  mySensors.initialize(); // initialize the multiplexer ic

}
```

### Reading One Sensor Value:
This library is designed in a way to directly retieve a single sensor value by calling the respective channel or multiplexer truth table. Here's an example for your quick reference.
```
multiSensors::read(int chnl_num); // reads specific analog channel of the ic
```
**Example:**
```
// light (LDR) sensor connected to the ic (IN5) channel of CD4051
#define AMBIENT_LDR_SENSOR 5 

// assign a variable to hold the sensor data:
int amb_light_value;

void loop(){
  // call sensor directly using its address
  amb_light_value= mySensors.read(AMBIENT_LDR_SENSOR);

  Serial.print("Ambient Light:");
  Serial.println(amb_light_value);
  
  delay(5000);	//wait for 5 seconds
}
```
### Reading All Analog Sensors:
The MultiSensor library is also equiped with a feature of reading all connected sensors. This function returns an array which can be used with other variablesor pointers to separately displaying the individual sensor data.

```
multiSensor::readAll(); //returns an int array
```
**Example:**
```
int* sensor_data;
sensor_data = mySensor.readAll();

Serial.print("Third sensor value:");
Serial.println(sensor_data[2]);
```
