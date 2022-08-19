#ifndef PLUGIN_EFFECT_H
#define PLUGIN_EFFECT_H

#include "HammondOrgan.h"
#include "QVstAudioEffect.h"



class PluginEffect : public QVstAudioEffect
{
public:
	PluginEffect();
    Steinberg::tresult PLUGIN_API initialize(Steinberg::FUnknown *pContext);

    static Steinberg::FUnknown* createInstance(void*) { return (Steinberg::Vst::IAudioProcessor*)new PluginEffect(); }

protected:

    void processActive(bool state);
    void processAudio(Steinberg::Vst::ProcessData &data);
    void parameterChanged(Steinberg::Vst::ParamID id, Steinberg::Vst::ParamValue value);
    void noteOn(int number, float velocity);
    void noteOff(int number, float velocity);

private:

    HammondOrgan m_organ;

};

#endif // PLUGIN_EFFECT_H
