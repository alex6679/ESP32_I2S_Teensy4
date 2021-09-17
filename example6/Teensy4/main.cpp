
#include "plotter.h"
#include <Audio.h>

#include "input_i2s2_16bit.h"
#include "async_input.h"

#define DEBUG
#define PLOTWAVE

AudioOutputSPDIF3   spdifOut;
#ifdef PLOTWAVE
Plotter plotter(8);  //only plot every 8th sample
#endif

// bool dither = false;
// bool noiseshaping = false;
// float attenuation = 100;
// int32_t minHalfFilterLength=80;
// int32_t maxHalfFilterLength=1;
// AsyncAudioInput<AsyncAudioInputI2S2_16bitslave> i2sSlaveInput(dither, noiseshaping, attenuation, minHalfFilterLength, maxHalfFilterLength);
AsyncAudioInput<AsyncAudioInputI2S2_16bitslave> i2sSlaveInput;
AudioConnection          patchCord1(i2sSlaveInput, 0, spdifOut, 0);
AudioConnection          patchCord2(i2sSlaveInput, 1, spdifOut, 1);
#ifdef PLOTWAVE
AudioConnection          patchCord3(i2sSlaveInput, 0, plotter, 0);     
#endif

void setup() {
  #ifdef DEBUG
    Serial.begin(115200);
    while (!Serial);
    #ifdef PLOTWAVE
        plotter.activate(true);
    #endif
  #endif
  AudioMemory(15);
 

}

void loop() {
#ifdef DEBUG
#ifndef PLOTWAVE


	double bufferedTine=i2sSlaveInput.getBufferedTime();
	double targetLatency = i2sSlaveInput.getTargetLantency();
	Serial.print("buffered time [micro seconds]: ");
	Serial.print(bufferedTine*1e6,2);
	Serial.print(", target: ");
	Serial.println(targetLatency*1e6,2);
	
	double pUsageIn=i2sSlaveInput.processorUsage(); 
	Serial.print("processor usage [%]: ");
	Serial.println(pUsageIn);

	double f=i2sSlaveInput.getInputFrequency();
	Serial.print("frequency: ");
	Serial.println(f);

	double attenuation=i2sSlaveInput.getAttenuation();
	Serial.print("achieved attenuation: ");
	Serial.println(attenuation);

	int32_t halfFilterLength=i2sSlaveInput.getHalfFilterLength();
	Serial.print("length of used interpolation filter: ");
	Serial.println(2*halfFilterLength +1);

	// Serial.print("Memory max: ");
  	// Serial.println(AudioMemoryUsageMax());
	delay(500);
#endif
#endif
}
