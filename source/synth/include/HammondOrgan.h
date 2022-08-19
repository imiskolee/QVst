#ifndef SYNTH_HAMMONDORGAN_H
#define SYNTH_HAMMONDORGAN_H

#include "HammondVoice.h"
#include "Instrument.h"

typedef Instrument<HammondVoice, 16> HammondInstrument;

class HammondOrgan : public HammondInstrument
{
public:
    HammondOrgan();

    void setAttackTime(double t);
    void setDecayTime(double t);
    void setSustainLevel(double s);
    void setReleaseTime(double t);

    void setDrawBar(HammondVoice::Harmonic h, double normalizedPosition);

    void setModulationFrequency(double f);
    void setModulationLevel(double l);
};

#endif // SYNTH_HAMMONDINSTRUMENT_H

