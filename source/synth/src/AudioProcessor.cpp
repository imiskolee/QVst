#include "AudioProcessor.h"

AudioProcessor::AudioProcessor()
    : m_sampleRate(44100.0),
      m_enabled(false)
{
}

void AudioProcessor::setSampleRate(double sr)
{
    m_sampleRate = sr;
}

void AudioProcessor::setEnabled(bool e)
{
    m_enabled = e;
}

bool AudioProcessor::isEnabled() const
{
    return m_enabled;
}

double AudioProcessor::tick()
{
    return tickProcess(nullptr, 0);
}

double AudioProcessor::tick(double input)
{
    return tickProcess(&input, 1);
}

void AudioProcessor::reset()
{
}
