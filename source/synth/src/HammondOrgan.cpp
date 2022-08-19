#include "HammondOrgan.h"

HammondOrgan::HammondOrgan()
    : HammondInstrument()
{
}

void HammondOrgan::setAttackTime(double t)
{
    std::vector<HammondVoice*>::iterator it = voices().begin();
    while (it != voices().end()) {
        (*it)->adsr().setAttackTime(t);
        ++it;
    }
}

void HammondOrgan::setDecayTime(double t)
{
    std::vector<HammondVoice*>::iterator it = voices().begin();
    while (it != voices().end()) {
        (*it)->adsr().setDecayTime(t);
        ++it;
    }
}

void HammondOrgan::setSustainLevel(double s)
{
    std::vector<HammondVoice*>::iterator it = voices().begin();
    while (it != voices().end()) {
        (*it)->adsr().setSustainLevel(s);
        ++it;
    }
}

void HammondOrgan::setReleaseTime(double t)
{
    std::vector<HammondVoice*>::iterator it = voices().begin();
    while (it != voices().end()) {
        (*it)->adsr().setReleaseTime(t);
        ++it;
    }
}

void HammondOrgan::setDrawBar(HammondVoice::Harmonic h, double normalizedPosition)
{
    std::vector<HammondVoice*>::iterator it = voices().begin();
    while (it != voices().end()) {
        (*it)->setDrawBar(h, normalizedPosition);
        ++it;
    }
}

void HammondOrgan::setModulationFrequency(double f)
{
    std::vector<HammondVoice*>::iterator it = voices().begin();
    while (it != voices().end()) {
        (*it)->setModulationFrequency(f);
        ++it;
    }
}

void HammondOrgan::setModulationLevel(double l)
{
    double level = l < 0 ? -l : l;
    if (level > 1.0) {
        level = 1.0;
    }

    // Adjust for reasonable modulation depth assuming [0..1] input range.
    level *= 0.025;

    std::vector<HammondVoice*>::iterator it = voices().begin();
    while (it != voices().end()) {
        (*it)->setModulationLevel(level);
        ++it;
    }
}
