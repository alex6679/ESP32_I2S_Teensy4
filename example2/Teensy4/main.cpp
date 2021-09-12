#include "input_i2s_esp32.h"
#include "output_i2s_esp32.h"
#include "plotter.h"

#include <Audio.h>

AudioInputI2S_ESP32 i2s1;
Plotter plotter(8);
AudioConnection          patchCord1(i2s1, 0, plotter, 0);
AudioConnection          patchCord2(i2s1, 1, plotter, 1);


void setup() {
  AudioMemory(20);
  Serial.begin(115200);
  plotter.activate(true);
}

void loop() {
   
}