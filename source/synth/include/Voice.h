#ifndef SYNTH_VOICE_H
#define SYNTH_VOICE_H

#include "ADSR.h"
#include "AudioProcessor.h"
#include "INotesListener.h"

class Voice : public AudioProcessor,
              public INotesListener
{
public:

    Voice();

    virtual int noteNumber() const = 0;

};

#endif // SYNTH_VOICE_H

