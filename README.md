# ESP32_I2S_Teensy4
Two examples that show how an ESP32 can send an audio signal via I2S to a Teensy 4. The Teensy program uses the Teensy Audio Library to receive the signal. The classes AudioInputI2S_ESP32 and AudioOutputI2S_ESP32 are copies of AudioInputI2S and AudioOutputI2S from the audio library. They were only slightly adopted for the 16 bit audio samples of the ESP32.
