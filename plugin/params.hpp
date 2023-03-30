/****************************************************************************
   params.hpp - RaffoSynth parameter manager

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

#ifndef RAFFO_PARAMS_HEADER
#define RAFFO_PARAMS_HEADER

enum ParamId {
    m_volume,
    m_wave0,
    m_wave1,
    m_wave2,
    m_wave3,
    m_range0,
    m_range1,
    m_range2,
    m_range3,
    m_vol0,
    m_vol1,
    m_vol2,
    m_vol3,
    m_attack,
    m_decay,
    m_sustain,
    m_release,
    m_filter_cutoff,
    m_filter_attack,
    m_filter_decay,
    m_filter_sustain,
    m_glide,
    m_oscButton0,
    m_oscButton1,
    m_oscButton2,
    m_oscButton3,
    m_filter_resonance,
    m_tuning0,
    m_tuning1,
    m_tuning2,
    m_tuning3,
    m_filter_release,
    m_n_params
};

enum ParamType {
    PARAM_FLOAT,
    PARAM_LOGARITHMIC,
    PARAM_INT,
    PARAM_BOOL
};

struct ParamDefinition {
    const char* symbol;
    const char* name;
    float       min;
    float       max;
    float       def;
    char        type;
};

namespace RaffoParams {
    const char* paramName(ParamId index);
    const char* paramSymbol(ParamId index);

    float paramDefaultValue(ParamId index);
    float paramMinValue(ParamId index);
    float paramMaxValue(ParamId index);

    bool paramFloat(ParamId index);
    bool paramBool(ParamId index);
    bool paramInt(ParamId index);
}

#endif // RAFFO_PARAMS_HEADER
