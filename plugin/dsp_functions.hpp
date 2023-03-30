/****************************************************************************
   dsp_functions.hpp - External definitions for synth engine functions

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

#ifndef DSP_FUNCTIONS_HPP
#define DSP_FUNCTIONS_HPP

#include <cstdint>

extern "C" void ondaTriangular(uint32_t from, uint32_t to, uint32_t counter, float* buffer, float subperiod, float vol, float env);

extern "C" void ondaSierra(uint32_t from, uint32_t to, uint32_t counter, float* buffer, float subperiod, float vol, float env);

extern "C" void ondaPulso(uint32_t from, uint32_t to, uint32_t counter, float* buffer, float subperiod, float vol, float env);

extern "C" void ondaCuadrada(uint32_t from, uint32_t to, uint32_t counter, float* buffer, float subperiod, float vol, float env);

extern "C" void equalizer(float* buffer, float* prev, uint32_t sample_count, float psuma0, float psuma2, float psuma3, float ssuma0, float ssuma1, float ssuma2, float ssuma3, float factorSuma2);

extern "C" void limpiarBuffer(uint32_t from, uint32_t to, float* buffer);

#endif // DSP_FUNCTIONS_HPP
