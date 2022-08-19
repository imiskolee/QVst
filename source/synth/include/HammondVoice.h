#ifndef SYNTH_HAMMONDVOICE_H
#define SYNTH_HAMMONDVOICE_H

#include <map>
#include <vector>
#include "ADSR.h"
#include "Functions.h"
#include "Generator.h"
#include "Voice.h"

typedef Generator<Function::Sine> SineGenerator;

class HammondVoice : public Voice
{
public:

    enum Harmonic {
        Harmonic_16,    // Sub fundamental (0.5)
        Harmonic_5_13,  // Sub 3rd (1.5)
        Harmonic_8,     // Fundamental (1.0)
        Harmonic_4,     // 2nd harmonic (2.0)
        Harmonic_2_35,  // 3rd harmonic (3.0)
        Harmonic_2,     // 4th harmonic (4.0)
        Harmonic_1_35,  // 5th harmonic (5.0)
        Harmonic_1_13,  // 6th harmonic (6.0)
        Harmonic_1      // 8th harmonic (8.0)
    };

    HammondVoice();
    ~HammondVoice();

    ADSR& adsr() { return m_adsr; }
    void setDrawBar(Harmonic h, double normalizedPosition) { m_drawBars[h] = normalizedPosition; }

    void setModulationFrequency(double f);
    void setModulationLevel(double l);

    // Voice
    int noteNumber() const override { return m_noteNumber; }

    // IAudioProcessor
    double tickProcess(double *input, int nChannels) override;
    double lastSample(int channel) const override { return m_lastSample; }

    // INotesListener
    void noteOn(int number, double velocity) override;
    void noteOff(int number, double velocity) override;

private:

    void createHarmonics();
    void deleteHarmonics();
    void setFrequency(double f);

    ADSR m_adsr;
    int m_noteNumber;

    std::map<Harmonic, double> m_drawBars;
    std::map<Harmonic, SineGenerator*> m_harmonics;

    double m_lastSample;
};

#endif // SYNTH_HAMMONDVOICE_H

