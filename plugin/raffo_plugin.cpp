/****************************************************************************
   raffo_plugin.cpp - RaffoSynth DPF plugin interface

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

#include "raffo_plugin.hpp"

#include "raffo.hpp"

START_NAMESPACE_DISTRHO

RaffoSynthPlugin::RaffoSynthPlugin()
    : Plugin(ParamId::m_n_params, 0, 0) // parameters, programs, states
{
    fSampleRate = getSampleRate();
    fBufferSize = getBufferSize();

    fSynthesizer = std::make_unique<RaffoSynth>(fSampleRate);
}

RaffoSynthPlugin::~RaffoSynthPlugin()
{
}

void RaffoSynthPlugin::initParameter(uint32_t index, Parameter& parameter)
{
    parameter.hints = kParameterIsAutomatable;

    parameter.name       = RaffoParams::paramName(ParamId(index));
    parameter.shortName  = RaffoParams::paramSymbol(ParamId(index));
    parameter.symbol     = RaffoParams::paramSymbol(ParamId(index));
    parameter.ranges.min = RaffoParams::paramMinValue(ParamId(index));
    parameter.ranges.max = RaffoParams::paramMaxValue(ParamId(index));
    parameter.ranges.def = RaffoParams::paramDefaultValue(ParamId(index));

    if (RaffoParams::paramInt(ParamId(index)))
        parameter.hints |= kParameterIsInteger;
    else if (RaffoParams::paramBool(ParamId(index)))
        parameter.hints |= kParameterIsBoolean;

    // Handle enumeration values
    switch (index) {
        case m_wave0:
        case m_wave1:
        case m_wave2:
        case m_wave3: {
            parameter.enumValues.count          = 4;
            parameter.enumValues.restrictedMode = true;
            {
                ParameterEnumerationValue* const values = new ParameterEnumerationValue[4];
                parameter.enumValues.values             = values;

                values[0].label = "Saw";
                values[0].value = 0;
                values[1].label = "Triangle";
                values[1].value = 1;
                values[2].label = "Square";
                values[2].value = 2;
                values[3].label = "Pulse";
                values[3].value = 3;
            }

            break;
        }

        case m_range0:
        case m_range1:
        case m_range2:
        case m_range3: {
            parameter.enumValues.count          = 5;
            parameter.enumValues.restrictedMode = true;
            {
                ParameterEnumerationValue* const values = new ParameterEnumerationValue[5];
                parameter.enumValues.values             = values;

                values[0].label = "32'";
                values[0].value = 1;
                values[1].label = "16'";
                values[1].value = 2;
                values[2].label = "8'";
                values[2].value = 3;
                values[3].label = "4'";
                values[3].value = 4;
                values[4].label = "2'";
                values[4].value = 5;
            }

            break;
        }
    }

    setParameterValue(index, parameter.ranges.def);
}

float RaffoSynthPlugin::getParameterValue(uint32_t index) const
{
    if (fSynthesizer == nullptr)
        return 0.0f;

    return fSynthesizer->get_param((ParamId)index);
}

void RaffoSynthPlugin::setParameterValue(uint32_t index, float value)
{
    if (fSynthesizer != nullptr)
        fSynthesizer->set_param((ParamId)index, value);
}

void RaffoSynthPlugin::activate()
{
    if (fSynthesizer != nullptr)
        fSynthesizer->activate();
}

void RaffoSynthPlugin::run(const float** inputs, float** outputs, uint32_t frames, const MidiEvent* midiEvents, uint32_t midiEventCount)
{
    if (fSynthesizer == nullptr)
        return;

    // Which to be processed first obeys the original design.
    // First, process audio frames.
    fSynthesizer->run(outputs[0], frames);

    // Then, process MIDI events.
    for (uint32_t i = 0; i < midiEventCount; i++) {
        fSynthesizer->handle_midi(midiEvents[i].size, midiEvents[i].data);
    }
}

// Reinit synth engine on buffer size change.
void RaffoSynthPlugin::bufferSizeChanged(int newBufferSize)
{
    if (fBufferSize != newBufferSize) {
        d_stderr("[DSP] Buffer size changed: from %d to %d", fBufferSize, newBufferSize);

        fBufferSize = newBufferSize;

        // Reinit synth engine
        fSynthesizer.reset();
        fSynthesizer = std::make_unique<RaffoSynth>(fSampleRate);
    } else {
        d_stderr("[DSP] Buffer size changed: same as current value, %d", fBufferSize);
    }
}

// Reinit synth engine on sample rate change.
void RaffoSynthPlugin::sampleRateChanged(double newSampleRate)
{
    if (fSampleRate != newSampleRate) {
        d_stderr("[DSP] Sample rate changed: from %f to %f", fSampleRate, newSampleRate);

        fSampleRate = newSampleRate;
        fSynthesizer->set_samplerate(fSampleRate);
    } else {
        d_stderr("[DSP] Sample rate changed: same as current value, %f", fSampleRate);
    }
}

Plugin* createPlugin()
{
    return new RaffoSynthPlugin();
}

END_NAMESPACE_DISTRHO
