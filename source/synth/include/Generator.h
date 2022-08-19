#ifndef SYNTH_GENERATOR_H
#define SYNTH_GENERATOR_H

#include <cmath>
#include "AudioProcessor.h"

#ifndef M_PI
#   define M_PI 3.14159265358979323846
#endif

template<class CFunction>
class Generator : public AudioProcessor
{
public:

    Generator(double scale = 1.0)
        : m_func(),
          m_freqScale(scale),
          m_phase(0.0),
          m_phaseIncrement(0.0),
          m_modulationPhase(0.0),
          m_modulationPhaseIncrement(0.0),
          m_modulationLevel(0.0),
          m_lastSample(0.0)
    {
    }

    void setFrequencyScale(double s)
    {
        m_freqScale = s;
    }

    void setFrequency(double f)
    {
        m_phaseIncrement = (f * m_freqScale) / sampleRate();
    }

    void setModulationFrequency(double f)
    {
        m_modulationPhaseIncrement = f / sampleRate();
    }

    void setModulationLevel(double l)
    {
        m_modulationLevel = l;
    }

    // IAudioProcessor interface
    double tickProcess(double *input, int nChannels) override
    {
        (void)input;
        (void)nChannels;

        m_lastSample = m_func(m_phase);
        incrementPhase();
        return m_lastSample;
    }

    double lastSample(int channel) const override
    {
        return m_lastSample;
    }

    void reset() override
    {
        m_phase = 0.0;
        m_modulationPhase = 0.0;
    }

protected:

    double phase() const { return m_phase; }

    void incrementPhase()
    {
        double dPhase = m_phaseIncrement;
        dPhase += m_phaseIncrement * m_modulationLevel * sin(2.0 * M_PI * m_modulationPhase);

        m_phase = fmod(m_phase + dPhase, 1.0);
        m_modulationPhase = fmod(m_modulationPhase + m_modulationPhaseIncrement, 1.0);
    }

private:

    CFunction m_func;

    double m_freqScale;

    double m_phase;
    double m_phaseIncrement;

    double m_modulationPhase;
    double m_modulationPhaseIncrement;
    double m_modulationLevel;

    double m_lastSample;
};

#endif // SYNTH_GENERATOR_H

