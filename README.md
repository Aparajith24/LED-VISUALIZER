# Real-Time LED Audio Waveform with Arduino

## Project Overview
Create a real-time LED audio waveform display using an Arduino microcontroller. This project uses a frequency-to-voltage converter, a WS2812B LED strip, and Arduino to visualize audio pitch and volume in the form of vibrant LED patterns. The LED strip functions as a dynamic audio waveform visualizer, providing a captivating and colorful representation of the audio input.

## Requirements
- [Frequency to voltage converter](http://mathscinotes.com/2014/03/a-simple-frequency-to-voltage-converter/)
- WS2812B LED strip
- Arduino microcontroller

## How It Works
Every 1 millisecond, the system reads the frequency (pitch) of the audio signal through the frequency-to-voltage converter. Simultaneously, it captures the volume of the amplified audio signal. These two pieces of data are then used to determine the color and brightness of individual LEDs on the WS2812B LED strip.

- **Color Mapping**: The pitch information is mapped to RGB colors, creating a visually appealing color palette. Different pitches correspond to different colors, adding depth and variety to the visual representation.

- **Brightness Control**: The volume of the audio signal controls the brightness of the LEDs. Louder audio results in brighter LEDs, while quieter sections are displayed with lower intensity.

- **LED Shift and Memory Effect**: The LED strip consists of multiple LEDs arranged sequentially. To create a real-time audio waveform display, all LEDs shift to the right, updating the first LED with the latest audio data. This shifting allows the system to display a portion of the audio waveform in real time.
