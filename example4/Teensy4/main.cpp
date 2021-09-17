#include "input_i2s2_16bit.h"
#include "output_i2s2_16bit.h"
#include "plotter.h"

#include <Audio.h>

AudioInputI2S2_16bitslave i2s2Slave;
Plotter plotter(8);
AudioConnection          patchCord1(i2s2Slave, 0, plotter, 0);
AudioConnection          patchCord2(i2s2Slave, 1, plotter, 1);

// AudioInputI2S_ESP32      i2s1;    
// AudioOutputSPDIF3        spdifOut;         
// AudioConnection          patchCord1(i2s1, 0, spdifOut, 0);
// AudioConnection          patchCord2(i2s1, 1, spdifOut, 1);


void setup() {
  AudioMemory(20);
  Serial.begin(115200);
  plotter.activate(true);
}

void loop() {
   
}