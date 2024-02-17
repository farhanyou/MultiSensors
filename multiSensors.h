
/*
--------------------------------------------------------------------------------------------------------------------------------------------------
  Multi Sense Library by Ferhan Y. (fehaan@hotmail.com)
--------------------------------------------------------------------------------------------------------------------------------------------------
  About:    This library uses multiplexer - CD4051 IC for sensing multiple analog sensors attached to the ESP / NodeMCU / Arduino board
  Author:   Ferhan Y. (fehaan@hotmail.com)
  License:  General Public (feel free to use it in your projects)

Description:
This library is developed to allow developers to read data from multiple analog inputs or sensors using the multiplexer ic CD4051 connected 
to the ESP8266/ESP32/NODEMCU/ARDUINO development boards.
It utilizes a digital multiplexer to select one or multiple input channels and read its data.
The sensor data can be read separately or in an array form for using it according to the needs.
--------------------------------------------------------------------------------------------------------------------------------------------------
*/

#ifndef multiSensors_h
#define multiSensors_h

// Core libraries
#include "Arduino.h"

// Constants
#define MUX_CHANNEL_PINS 3  // define multiplexer control pins
#define MUX_CHANNELS 8      // total number of analog channels available on the IC

class multiSensors {

public:

  multiSensors(int, int, int, int, int);
  void initialize();
  int *readAll();
  int read(int pin_num);

private:

  // Variables to hold multiplexer channel selector (S0, S1, S2) pin numbers attached to the microcontroller board
  int mux_A, mux_B, mux_C;

  // Array of multiplexer channel control pins
  int mux_channelPins[MUX_CHANNEL_PINS] = { this->mux_A,
                                            this->mux_B,
                                            this->mux_C };

  // Multiplexer channel selection configuration
  int mux_channels[MUX_CHANNELS][MUX_CHANNEL_PINS] = {
    { 0, 0, 0 },  //channel 0
    { 1, 0, 0 },  //channel 1
    { 0, 1, 0 },  //channel 2
    { 1, 1, 0 },  //channel 3
    { 0, 0, 1 },  //channel 4
    { 1, 0, 1 },  //channel 5
    { 0, 1, 1 },  //channel 6
    { 1, 1, 1 }   //channel 7
  };
  int mux_numSensors;        // Variable to hold total number of sensors attached to the multiplexer IC
  int mux_commonPin;         // Multiplexer common pin
  int mux_readChannel(int);  // Read from a specific sensor attached to the multiplexer pin
  int *mux_readAll();        // Read all connected sensors

};  // end of class
#endif
