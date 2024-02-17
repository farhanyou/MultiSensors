#include <iterator>
// Core libraries
#include "Arduino.h"
#include "multiSensors.h"


/*----- Public -----*/


// Calss instance
multiSensors::multiSensors(int mux_0, int mux_1, int mux_2, int analogPin, int numSensors) {
  mux_A = mux_0;
  mux_B = mux_1;
  mux_C = mux_2;
  mux_commonPin = analogPin;
  mux_numSensors = numSensors;
}

// Initialization
void multiSensors::initialize() {
  for (int i = 0; i < MUX_CHANNEL_PINS; i++) {  // loop through all muliplexer control pins
    pinMode(mux_channelPins[i], OUTPUT);        // set pin mode
    digitalWrite(mux_channelPins[i], LOW);      // set muliplexer to channel 0 read state;
  }
}

/*-----  Read from all a channel @return int array -----*/
int multiSensors::read(int mux_chnl_num) {  // when a specific channel is to be read
  return mux_readChannel(mux_chnl_num);     // send output data of the channel
}

int *multiSensors::readAll() {  // when all multiplexer sensors are intended to be read
  return mux_readAll();               // send output array
}


/*----- Private -----*/


// Read from a specific channel @return integer value
int multiSensors::mux_readChannel(int chnl_num) {
  for (int i = 0; i < MUX_CHANNEL_PINS; i++) {                    // loop through all multiplexer channel control pins
    digitalWrite(mux_channelPins[i], mux_channels[chnl_num][i]);  // set low/high state according to the multiplexer truth channel config
  }
  return analogRead(mux_commonPin);  // read and send output sensor value
}

// Read from all analog channels @return integer array
int *multiSensors::mux_readAll() {  // read through all attached multiplexer sensors
  static int array[MUX_CHANNELS];          // set up an array to hold sensor values
  int array_sz = sizeof(array) / sizeof(array[0]);
  for (int num_chnl = 0; num_chnl < array_sz; num_chnl++) {         // loop through all multiplexer channels
    for (int i = 0; i < MUX_CHANNEL_PINS; i++) {                    // loop through channel control pins for each multiplexer channel
      digitalWrite(mux_channelPins[i], mux_channels[num_chnl][i]);  // set pin state according to the multiplexer truth table
    }
    array[num_chnl] = analogRead(mux_commonPin);  // read and add sensor value to the array
  }
  return array;  //send output as an array
}
