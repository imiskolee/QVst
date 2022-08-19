#include <cmath>
#include "HammondVoice.h"

HammondVoice::HammondVoice()
    : m_adsr(),
      m_noteNumber(-1),
      m_drawBars(),
      m_harmonics(),
      m_lastSample(0.0)
{
    createHarmonics();
}

HammondVoice::~HammondVoice()
{
    deleteHarmonics();
}

void HammondVoice::setModulationFrequency(double f)
{
    std::map<Harmonic, SineGenerator*>::iterator it = m_harmonics.begin();
    while (it != m_harmonics.end()) {
        it->second->setModulationFrequency(f);
        ++it;
    }
}

void HammondVoice::setModulationLevel(double l)
{
    std::map<Harmonic, SineGenerator*>::iterator it = m_harmonics.begin();
    while (it != m_harmonics.end()) {
        it->second->setModulationLevel(l);
        ++it;
    }
}

double HammondVoice::tickProcess(double *input, int nChannels)
{
    (void)input;
    (void)nChannels;

    m_lastSample = 0.0;

    if (isEnabled()) {
        if (m_adsr.state() == ADSR::State_Off) {
            // Disable this voice when envelope fades out
            setEnabled(false);
        } else {
            double envelope = m_adsr.tick();
            m_lastSample += m_harmonics[Harmonic_16]->tick() * m_drawBars[Harmonic_16];
            m_lastSample += m_harmonics[Harmonic_5_13]->tick() * m_drawBars[Harmonic_5_13];
            m_lastSample += m_harmonics[Harmonic_8]->tick() * m_drawBars[Harmonic_8];
            m_lastSample += m_harmonics[Harmonic_4]->tick() * m_drawBars[Harmonic_4];
            m_lastSample += m_harmonics[Harmonic_2_35]->tick() * m_drawBars[Harmonic_2_35];
            m_lastSample += m_harmonics[Harmonic_2]->tick() * m_drawBars[Harmonic_2];
            m_lastSample += m_harmonics[Harmonic_1_35]->tick() * m_drawBars[Harmonic_1_35];
            m_lastSample += m_harmonics[Harmonic_1_13]->tick() * m_drawBars[Harmonic_1_13];
            m_lastSample += m_harmonics[Harmonic_1]->tick() * m_drawBars[Harmonic_1];
            m_lastSample *= envelope;
        }
    }

    return m_lastSample;
}

void HammondVoice::noteOn(int number, double velocity)
{
    (void)velocity;

    m_noteNumber = number;
    m_adsr.noteOn();

    double f = pow(2.0, (number - 69)/12.0) * 440.0;
    setFrequency(f);

    setEnabled(true);
}

void HammondVoice::noteOff(int number, double velocity)
{
    (void)number;
    (void)velocity;

    m_adsr.noteOff();
}

void HammondVoice::createHarmonics()
{
    m_harmonics[Harmonic_16] = new SineGenerator(0.5);
    m_harmonics[Harmonic_5_13] = new SineGenerator(1.5);
    m_harmonics[Harmonic_8] = new SineGenerator(1.0);
    m_harmonics[Harmonic_4] = new SineGenerator(2.0);
    m_harmonics[Harmonic_2_35] = new SineGenerator(3.0);
    m_harmonics[Harmonic_2] = new SineGenerator(4.0);
    m_harmonics[Harmonic_1_35] = new SineGenerator(5.0);
    m_harmonics[Harmonic_1_13] = new SineGenerator(6.0);
    m_harmonics[Harmonic_1] = new SineGenerator(8.0);

    m_drawBars[Harmonic_16] = 1.0;
    m_drawBars[Harmonic_5_13] = 1.0;
    m_drawBars[Harmonic_8] = 1.0;
    m_drawBars[Harmonic_4] = 0.8;
    m_drawBars[Harmonic_2_35] = 0.0;
    m_drawBars[Harmonic_2] = 0.0;
    m_drawBars[Harmonic_1_35] = 0.0;
    m_drawBars[Harmonic_1_13] = 0.0;
    m_drawBars[Harmonic_1] = 2.0;
}

void HammondVoice::deleteHarmonics()
{
    for (std::map<Harmonic, SineGenerator*>::const_iterator it = m_harmonics.begin();
         it != m_harmonics.end();
         ++it) {
        delete it->second;
    }
    m_harmonics.clear();
}

void HammondVoice::setFrequency(double f)
{
    m_harmonics[Harmonic_16]->setFrequency(f);
    m_harmonics[Harmonic_5_13]->setFrequency(f);
    m_harmonics[Harmonic_8]->setFrequency(f);
    m_harmonics[Harmonic_4]->setFrequency(f);
    m_harmonics[Harmonic_2_35]->setFrequency(f);
    m_harmonics[Harmonic_2]->setFrequency(f);
    m_harmonics[Harmonic_1_35]->setFrequency(f);
    m_harmonics[Harmonic_1_13]->setFrequency(f);
    m_harmonics[Harmonic_1]->setFrequency(f);
}
