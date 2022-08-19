#ifndef SYNTH_ADSR_H
#define SYNTH_ADSR_H

#include "AudioProcessor.h"

class ADSR : public AudioProcessor
{
public:

    enum State {
        State_Attack,
        State_Decay,
        State_Sustain,
        State_Release,
        State_Off
    };

    ADSR();

    void setAttackTime(double s);
    void setDecayTime(double s);
    void setSustainLevel(double s);
    void setReleaseTime(double s);

    void noteOn();
    void noteOff();

    State state() const { return m_state; }

    // IAudioProcessor interface
    double tickProcess(double *input, int nChannels) override;
    double lastSample(int channel) const override;
    void setEnabled(bool ena) override;


private:

    void recomputeRates();
    void process();
    void setState(State s);

    State m_state;      ///< ADSR state.
    double m_envelope;  ///< Current envelope value.
    double m_attackTime;
    double m_decayTime;
    double m_sustainLevel;
    double m_releaseTime;

    double m_attackRate;
    double m_decayRate;
    double m_releaseRate;
};

#endif // SYNTH_ADSR_H
