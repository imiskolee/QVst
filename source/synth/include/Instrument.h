#ifndef SYNTH_INSTRUMENT_H
#define SYNTH_INSTRUMENT_H

#include <vector>
#include <map>
#include "AudioProcessor.h"
#include "INotesListener.h"

template< class CVoice,  int polyphony = 1>
class Instrument : public AudioProcessor,
                   public INotesListener
{
public:
    Instrument()
        : m_voices(),
          m_volume(1.0)
    {
        for (int i = 0; i < polyphony; i++) {
            m_voices.push_back(new CVoice());
        }
    }

    ~Instrument()
    {
        for (typename std::vector<CVoice*>::iterator it = m_voices.begin();
             it != m_voices.end();
             ++it) {
            delete (*it);
        }
    }

    void setEnabled(bool ena) override
    {
        if (!ena) {
            for (typename std::vector<CVoice*>::const_iterator it = m_voices.begin();
                 it != m_voices.end();
                ++it) {
                // Disable the voice
                (*it)->setEnabled(false);
            }
        }
        AudioProcessor::setEnabled(ena);
    }

    double tickProcess(double *input, int nChannels)
    {
        (void)input;
        (void)nChannels;

        double sample = 0.0;
        for (typename std::vector<CVoice*>::iterator it = m_voices.begin();
             it != m_voices.end();
             ++it) {
            CVoice *pVoice = *it;
            if (pVoice->isEnabled()) {
                sample += pVoice->tick();
            }
        }
        sample *= m_volume;

        return sample;
    }

    double lastSample(int channel) const
    {
        double sample = 0.0;
        for (typename std::vector<CVoice*>::const_iterator it = m_voices.begin();
             it != m_voices.end();
             ++it) {
            CVoice *pVoice = *it;
            if (pVoice->isEnabled()) {
                sample += pVoice->lastSample(channel);
            }
        }
        sample *= m_volume;

        return sample;
    }

    void noteOn(int number, double velocity) override
    {
        CVoice *pVoice = nullptr;

        // Look for enabled note
        typename std::vector<CVoice*>::const_iterator it = m_voices.begin();
        while (pVoice == nullptr && it != m_voices.end()) {
            if ((*it)->isEnabled() && (*it)->noteNumber() == number) {
                pVoice = *it;
            }
            ++it;
        }

        // Look for first idle voice
        if (pVoice == nullptr) {
            typename std::vector<CVoice*>::const_iterator it = m_voices.begin();
            while (pVoice == nullptr && it != m_voices.end()) {
                if (!(*it)->isEnabled()) {
                    pVoice = *it;
                }
                ++it;
            }
        }

        if (pVoice != nullptr) {
            pVoice->noteOn(number, velocity);
        }
    }

    void noteOff(int number, double velocity) override
    {
        // Look for the enbaled voice with corresponding note number
        CVoice *pVoice = nullptr;
        typename std::vector<CVoice*>::const_iterator it = m_voices.begin();
        while (pVoice == nullptr && it != m_voices.end()) {
            if ((*it)->isEnabled() && (*it)->noteNumber() == number) {
                pVoice = *it;
            }
            ++it;
        }

        if (pVoice != nullptr) {
            pVoice->noteOff(number, velocity);
        }
    }

    void setVolume(double volume)
    {
        m_volume = volume;
    }

protected:

    std::vector<CVoice*>& voices() { return m_voices; }
    const std::vector<CVoice*>& voices() const { return m_voices; }

private:

    std::vector<CVoice*> m_voices;
    double m_volume;
};

#endif // SYNTH_INSTRUMENT_H

