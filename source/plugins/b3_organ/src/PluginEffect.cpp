#include <QDebug>
#include "ids.h"
#include "PluginEffect.h"

PluginEffect::PluginEffect()
    : QVstAudioEffect(),
      m_organ()
{
    setControllerClass(PluginControllerUID);

    m_organ.setModulationFrequency(7.0);
    m_organ.setModulationLevel(0.0);
}

Steinberg::tresult PLUGIN_API PluginEffect::initialize(Steinberg::FUnknown *pContext)
{
    Steinberg::tresult res = Steinberg::Vst::AudioEffect::initialize(pContext);
    if (res == Steinberg::kResultOk) {
        addEventInput(STR16("MIDI in"), 1);
        addAudioOutput(STR16("Stereo Out"), Steinberg::Vst::SpeakerArr::kStereo);
    }
	return res;
}

void PluginEffect::processActive(bool state)
{
    m_organ.setEnabled(state);
}

void PluginEffect::processAudio(Steinberg::Vst::ProcessData &data)
{
    Steinberg::int32 nSamples = data.numSamples;
    float *pLeft = data.outputs[0].channelBuffers32[0];
    float *pRight = data.outputs[0].channelBuffers32[1];

    for (Steinberg::int32 i = 0; i < nSamples; i++) {
        m_organ.tick();
        pLeft[i] = (float)m_organ.lastSample(0) * 0.1;
        pRight[i] = (float)m_organ.lastSample(1) * 0.1;
    }
}

void PluginEffect::parameterChanged(Steinberg::Vst::ParamID id, Steinberg::Vst::ParamValue value)
{
    qDebug() << __FUNCTION__ << id << value;
    switch (id) {
    case Param_DrawBar_16:
        m_organ.setDrawBar(HammondVoice::Harmonic_16, value);
        break;
    case Param_DrawBar_5_13:
        m_organ.setDrawBar(HammondVoice::Harmonic_5_13, value);
        break;
    case Param_DrawBar_8:
        m_organ.setDrawBar(HammondVoice::Harmonic_8, value);
        break;
    case Param_DrawBar_4:
        m_organ.setDrawBar(HammondVoice::Harmonic_4, value);
        break;
    case Param_DrawBar_2_35:
        m_organ.setDrawBar(HammondVoice::Harmonic_2_35, value);
        break;
    case Param_DrawBar_2:
        m_organ.setDrawBar(HammondVoice::Harmonic_2, value);
        break;
    case Param_DrawBar_1_35:
        m_organ.setDrawBar(HammondVoice::Harmonic_1_35, value);
        break;
    case Param_DrawBar_1_13:
        m_organ.setDrawBar(HammondVoice::Harmonic_1_13, value);
        break;
    case Param_DrawBar_1:
        m_organ.setDrawBar(HammondVoice::Harmonic_1, value);
        break;
    case Param_Attack:
        m_organ.setAttackTime(value);
        break;
    case Param_Decay:
        m_organ.setDecayTime(value);
        break;
    case Param_Sustain:
        m_organ.setSustainLevel(value);
        break;
    case Param_Release:
        m_organ.setReleaseTime(value);
        break;
    case Param_Modulation:
        m_organ.setModulationLevel(value);
        break;
    case Param_Volume:
        m_organ.setVolume(value);
        break;
    default:
        break;
    }
}

void PluginEffect::noteOn(int number, float velocity)
{
    if (velocity > 0.0f) {
        m_organ.noteOn(number, velocity);
    } else {
        // Treat note-on with zero velocity as note off
        m_organ.noteOff(number, velocity);
    }
}

void PluginEffect::noteOff(int number, float velocity)
{
    m_organ.noteOff(number, velocity);
}
