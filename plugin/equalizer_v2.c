/****************************************************************************
   equalizer_v2.c - RaffoSynth equalizer module, with AnClark's bugfix

   Fixed: CPU usage surging when synthesizer is idle after note input

   Copyright (c) 2014, Nicolas Roulet,
   Copyright (c) 2014, Julian Palladino,
   Copyright (C) 2023, AnClark Liu.

   This file conforms to MIT license.

   For more details, see:
   https://github.com/nicoroulet/RaffoSynth/blob/master/LICENSE.md

*****************************************************************************/

#include <math.h>
#include <stdint.h>

// hace lo mismo que la versión en asm
void equalizer(float* buffer, float* prev_vals, uint32_t sample_count, float psuma0, float psuma2, float psuma3, float ssuma0, float ssuma1, float ssuma2, float ssuma3, float factorSuma2)
{
    float psuma1 = psuma0 * 2;
    for (int i = 0; i < sample_count; i++) {
        /* low-pass filter */

        float temp = buffer[i];
        if (temp == 0.0f) // Skip process when sample is empty. This can reduce CPU usage on idle
            continue;

        buffer[i] *= psuma0; // psuma0 == factorsuma1
        buffer[i] += psuma0 * prev_vals[0] + psuma1 * prev_vals[1]
                     + psuma2 * prev_vals[2] + psuma3 * prev_vals[3];
        prev_vals[0] = prev_vals[1];
        prev_vals[1] = temp;

        /* peaking EQ (resonance) */

        float temp2 = buffer[i];
        if (temp2 == 0.0f) // Skip process when sample is empty. This can reduce CPU usage on idle
            continue;

        buffer[i] *= factorSuma2;
        buffer[i] += ssuma0 * prev_vals[2] + ssuma1 * prev_vals[3]
                     + ssuma2 * prev_vals[4] + ssuma3 * prev_vals[5];
        prev_vals[2] = prev_vals[3];
        prev_vals[3] = temp;
        prev_vals[4] = prev_vals[5];
        prev_vals[5] = buffer[i];
    }
}
