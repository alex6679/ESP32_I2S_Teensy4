#include "input_i2s2_16bit.h"
#include "output_i2s2_16bit.h"
#include "plotter.h"

#include <Audio.h>

AudioInputI2S2_16bit i2s2;
Plotter plotter(8);
AudioOutputSPDIF3 spdifOut;
AudioConnection          patchCord1(i2s2, 0, plotter, 0);
AudioConnection          patchCord2(i2s2, 1, plotter, 1);
AudioConnection          patchCord3(i2s2, 0, spdifOut, 0);
AudioConnection          patchCord4(i2s2, 1, spdifOut, 1);


void setup() {
  AudioMemory(26);
  Serial.begin(115200);
  plotter.activate(true);
}

void loop() {
   
}