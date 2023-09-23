/****************************************************************************
   raffo.cpp - RaffoSynth engine

   Copyright (c) 2014, Nicolas Roulet,
   Copyright (c) 2014, Julian Palladino,
   Copyright (C) 2023, AnClark Liu. All rights reserved.

   This program is free software; you can redistribute it and/or
   modify it under the terms of the GNU General Public License
   as published by the Free Software Foundation; either version 3
   of the License, or (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License along
   with this program; if not, write to the Free Software Foundation, Inc.,
   51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.

*****************************************************************************/

#ifndef RAFFO_SYNTH_ENGINE_HEADER
#define RAFFO_SYNTH_ENGINE_HEADER

#include "params.hpp"
#include <cstdint>
#include <list>

using namespace std;

class RaffoSynth {

protected:
    double              sample_rate;
    list<unsigned char> keys;
    uint32_t            period; // periodo de la nota presionada
    float               glide_period; // periodo que se esta reproduciendo

    float last_val[4];
    float pre_buf_end; // el valor del ultimo sample del buffer anterior
    float prev_vals[6]; // [in[n-2], in[n-1], lpf[n-2], lpf[n-1], peak[n-2], peak[n-1]]
    bool  primer_nota;

    uint32_t counter;
    int      envelope_count;
    int      filter_count;
    float    modwheel;
    float    pitch;

    double glide;

    uint32_t midi_type;

#ifdef EXPERIENCIA
    Tiempo t_run;
    Tiempo t_osc;
    Tiempo t_eq;
    int    run_count;

    ofstream output;
#endif

    void equ_wrapper(float* output_mono, int sample_count);

public:
    RaffoSynth(double rate);

    void activate();
    void deactivate();

    void render(float* output_mono, uint32_t from, uint32_t to);
    void handle_midi(uint32_t size, const unsigned char* data);
    void run(float* output_mono, uint32_t sample_count);

    void  set_param(ParamId index, float value);
    float get_param(ParamId index);

    void set_samplerate(float new_sample_rate);

protected:
    float  m_parameters[m_n_params];
    float* p(uint32_t paramId);
};

#endif // RAFFO_SYNTH_ENGINE_HEADER
