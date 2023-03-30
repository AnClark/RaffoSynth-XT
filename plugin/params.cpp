/****************************************************************************
   params.cpp - RaffoSynth parameter manager

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

#include "params.hpp"

static struct ParamDefinition raffo_params[ParamId::m_n_params] = {
    // symbol, name, min, max, def, type
    { "volume", "Volume", 0, 10.01, 7, PARAM_FLOAT },
    { "wave0", "Wafeform Osc0", 0, 3, 2, PARAM_INT },
    { "wave1", "Waveform Osc1", 0, 3, 2, PARAM_INT },
    { "wave2", "Waveform Osc2", 0, 3, 0, PARAM_INT },
    { "wave3", "Waveform Osc3", 0, 3, 3, PARAM_INT },
    { "range0", "Range Osc0", 1, 5, 2, PARAM_INT },
    { "range1", "Range Osc1", 1, 5, 2, PARAM_INT },
    { "range2", "Range Osc2", 1, 5, 1, PARAM_INT },
    { "range3", "Range Osc3", 1, 5, 2, PARAM_INT },
    { "vol0", "Volume 0", 0, 10.01, 7, PARAM_FLOAT },
    { "vol1", "Volume 1", 0, 10.01, 5, PARAM_FLOAT },
    { "vol2", "Volume 2", 0, 10.01, 4, PARAM_FLOAT },
    { "vol3", "Volume 3", 0, 10.01, 7, PARAM_FLOAT },
    { "attack", "Attack", 10, 1000.01, 0, PARAM_FLOAT },
    { "decay", "Decay", 0, 1000.01, 200, PARAM_FLOAT },
    { "sustain", "Sustain", 0, 1.01, 0.8, PARAM_FLOAT },
    { "release", "Release", 0.01, 1.01, 0.4, PARAM_FLOAT },
    { "filter_cutoff", "Cutoff", 500, 10000, 3000, PARAM_FLOAT },
    { "filter_attack", "Filter Attack", 0, 1000.01, 200, PARAM_FLOAT },
    { "filter_decay", "Filter Decay", 0, 1000.01, 400, PARAM_FLOAT },
    { "filter_sustain", "Filter Sustain", 0, 1.01, 0.7, PARAM_FLOAT },
    { "glide", "Glide", 0, 10.01, 1, PARAM_FLOAT },
    { "oscButton0", "Button Osc0", 0, 1, 1, PARAM_BOOL },
    { "oscButton1", "Button Osc1", 0, 1, 1, PARAM_BOOL },
    { "oscButton2", "Button Osc2", 0, 1, 0, PARAM_BOOL },
    { "oscButton3", "Button Osc3", 0, 1, 0, PARAM_BOOL },
    { "filter_resonance", "Resonance", 0, 10.01, 3, PARAM_FLOAT },
    { "tuning0", "Osc tuning 0", -12, 12.01, 0, PARAM_FLOAT },
    { "tuning1", "Osc tuning 1", -12, 12.01, -0.02, PARAM_FLOAT },
    { "tuning2", "Osc tuning 2", -12, 12.01, 0.02, PARAM_FLOAT },
    { "tuning3", "Osc tuning 3", -12, 12.01, 0, PARAM_FLOAT },
    { "filter_release", "Filter release", 0, 1.01, 0.5, PARAM_FLOAT },
};

const char* RaffoParams::paramName(ParamId index)
{
    return raffo_params[index].name;
}

const char* RaffoParams::paramSymbol(ParamId index)
{
    return raffo_params[index].symbol;
}

float RaffoParams::paramDefaultValue(ParamId index)
{
    return raffo_params[index].def;
}

float RaffoParams::paramMinValue(ParamId index)
{
    return raffo_params[index].min;
}

float RaffoParams::paramMaxValue(ParamId index)
{
    return raffo_params[index].max;
}

bool RaffoParams::paramFloat(ParamId index)
{
    return (raffo_params[index].type == PARAM_FLOAT);
}

bool RaffoParams::paramBool(ParamId index)
{
    return (raffo_params[index].type == PARAM_BOOL);
}

bool RaffoParams::paramInt(ParamId index)
{
    return (raffo_params[index].type == PARAM_INT);
}
