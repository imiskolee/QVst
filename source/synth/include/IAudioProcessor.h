#ifndef SYNTH_IAUDIOPROCESSOR_H
#define SYNTH_IAUDIOPROCESSOR_H

class IAudioProcessor
{
public:

    virtual ~IAudioProcessor() {}

    virtual void setSampleRate(double sr) = 0;
    virtual double tick() = 0;
    virtual double tick(double input) = 0;
    virtual double tickProcess(double *input, int nChannels) = 0;
    virtual double lastSample(int channel) const = 0;
    virtual void setEnabled(bool e) = 0;
    virtual bool isEnabled() const = 0;
    virtual void reset() = 0;
};

#endif // SYNTH_IAUDIOPROCESSOR_H

