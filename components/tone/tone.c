#include "tone.h"
#include <stdlib.h>
#include <math.h>

#define BIAS 0x80
#define EIGHT_BIT_MAX 0xFF

uint8_t *waveform_buffer;
uint32_t sample_rate;

// Initialize the tone driver. Must be called before using.
// May be called again to change sample rate.
// sample_hz: sample rate in Hz to playback tone.
// Return zero if successful, or non-zero otherwise.
int32_t tone_init(uint32_t sample_hz) {
    // Checks if the sample_hz is less than 2 times the lowest frequency
    if (sample_hz < (2 * LOWEST_FREQ)) {
        return -1;
    }
    sample_rate = sample_hz;
    sound_init(sample_hz);
    waveform_buffer = (uint8_t *)malloc(sample_hz / LOWEST_FREQ);
    // Makes sure that the malloc worked correctly
    if (waveform_buffer == NULL) {
        return -1;
    }
    return 0;
}

// Free resources used for tone generation (DAC, DMA hardware, buffers, etc.).
// Return zero if successful, or non-zero otherwise.
int32_t tone_deinit(void) {
    free(waveform_buffer);
    sound_deinit();
    return 0;
}

// Start playing the specified tone.
// tone: one of the enumerated tone types.
// freq: frequency of the tone in Hz.
void tone_start(tone_t tone, uint32_t freq) {
    // Checks to see if the frequency is in a good range
    if (freq < LOWEST_FREQ || freq > sample_rate / 2) {
        return;
    }
    uint32_t num_samples = sample_rate / freq;
    // Creates a different waveform based on the tone wanted
    switch (tone) {
        case SINE_T:
            // Cycles through the number of samples to create the sine waveform
            for (uint32_t i = 0; i < num_samples; i++) {
                waveform_buffer[i] = (uint8_t)(BIAS + (BIAS * sin(2 * M_PI * i / num_samples)));
            }
            break;
        case SQUARE_T:
            // Cycles through the number of samples to create the square waveform
            for (uint32_t i = 0; i < num_samples; i++) {
                waveform_buffer[i] = (uint8_t)(i < num_samples / 2 ? EIGHT_BIT_MAX : 0);
            }
            break;
        case TRIANGLE_T:
            // Cycles through the number of samples to create the triangle waveform
            for (uint32_t i = 0; i < num_samples; i++) {
                uint8_t value = 0;
                if (i < num_samples / 2) {
                    value = BIAS + (BIAS * i * 2 / (num_samples / 2));
                } else {
                    value = EIGHT_BIT_MAX - (BIAS * (i - num_samples / 2) * 2 / (num_samples / 2));
                }
                waveform_buffer[i] = (uint8_t)value;
            }
            break;
        case SAW_T:
            // Cycles through the number of samples to create the saw waveform
            for (uint32_t i = 0; i < num_samples; i++) {
                waveform_buffer[i] = (uint8_t)((BIAS * i * 2 / num_samples) + BIAS);
            }
            break;
        default:
            break;
    }
    sound_cyclic(waveform_buffer, num_samples);
}