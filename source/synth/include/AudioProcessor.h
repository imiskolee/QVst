#ifndef SYNTH_AUDIOPROCESSOR_H
#define SYNTH_AUDIOPROCESSOR_H

#include "IAudioProcessor.h"

class AudioProcessor : public IAudioProcessor
{
public:

    AudioProcessor();

    // IAudioProcessor interface
    void setSampleRate(double sr) override;
    void setEnabled(bool e) override;
    bool isEnabled() const override;

    double tick() final override;
    double tick(double input) final override;

    void reset() override;

protected:

    double sampleRate() const { return m_sampleRate; }

private:

    double m_sampleRate;
    bool m_enabled;
};

#endif // SYNTH_AUDIOPROCESSOR_H

