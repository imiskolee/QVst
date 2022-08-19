#ifndef QVSTAUDIOEFFECT_H
#define QVSTAUDIOEFFECT_H

#include "pluginterfaces/base/funknown.h"
#include "public.sdk/source/vst/vstaudioeffect.h"

class QVstAudioEffect : public Steinberg::Vst::AudioEffect
{
public:

    QVstAudioEffect();

    Steinberg::tresult PLUGIN_API setActive(Steinberg::TBool state) override;
    Steinberg::tresult PLUGIN_API process(Steinberg::Vst::ProcessData &data) override;

    bool isActive() const { return m_active; }

protected:

    virtual void parameterChanged(Steinberg::Vst::ParamID id, Steinberg::Vst::ParamValue value);
    virtual void processAudio(Steinberg::Vst::ProcessData &data);
    virtual void processEvents(Steinberg::Vst::IEventList *pEventList);
    virtual void processActive(bool state);
    virtual void noteOn(int number, float velocity);
    virtual void noteOff(int number, float velocity);

private:


    bool m_active;

};

#endif // QVSTAUDIOEFFECT_H

