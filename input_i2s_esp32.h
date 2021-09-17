/* Audio Library for Teensy 3.X
 * Copyright (c) 2014, Paul Stoffregen, paul@pjrc.com
 *
 * Development of this audio library was funded by PJRC.COM, LLC by sales of
 * Teensy and Audio Adaptor boards.  Please support PJRC's efforts to develop
 * open source software by purchasing Teensy or other PJRC products.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice, development funding notice, and this permission
 * notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#ifndef _input_i2s_esp32_h_
#define _input_i2s_esp32_h_

#include "Arduino.h"
#include "AudioStream.h"
#include "DMAChannel.h"

class AudioInputI2S_ESP32 : public AudioStream
{
public:
	AudioInputI2S_ESP32(void) : AudioStream(0, NULL) { begin(); }
	virtual void update(void);
	void begin(void);
	uint32_t getCounter() const;
protected:	
	AudioInputI2S_ESP32(int dummy): AudioStream(0, NULL) {} // to be used only inside AudioInputI2Sslave_ESP32 !!
	static bool update_responsibility;
	static DMAChannel dma;
	static void isr(void);
private:
	static audio_block_t *block_left;
	static audio_block_t *block_right;
	static uint16_t block_offset;
};


class AudioInputI2Sslave_ESP32 : public AudioInputI2S_ESP32
{
public:
	AudioInputI2Sslave_ESP32(void) : AudioInputI2S_ESP32(0) { begin(); }
	void begin(void);
	friend void dma_ch1_isr(void);
};



#if defined(__IMXRT1062__)	
class AsyncAudioInputI2Sslave_esp32
{
public:
	AsyncAudioInputI2Sslave_esp32() { begin(); }
	void begin();

	//interface required by AsyncAudioInput: 
	///@param buffer array of arrays, outer array: array of channels, inner arrays contain the samples of an channel
	static void setResampleBuffer(float** buffer, int32_t bufferLength);

	constexpr static int32_t getNumberOfChannels() {return 2;}	
    typedef void (*FrequencyM) ();
	static void setFrequencyMeasurment(FrequencyM frequencyM);
	static int32_t getBufferOffset();
	static int32_t getNumberOfSamplesPerIsr();
	static void setResampleOffset(int32_t offset);
	//======================================
	
private:
	static DMAChannel asyncDma;
	static void isrResample(void);
	
	static volatile int32_t buffer_offset;
	static volatile int32_t resample_offset;
	static float* sampleBuffer[2];
	static int32_t sampleBufferLength;
	static FrequencyM frequencyM;	
};
#endif

#endif
