#ifndef SYNTH_INOTESLISTENER_H
#define SYNTH_INOTESLISTENER_H

class INotesListener
{
public:

    virtual ~INotesListener() {}

    virtual void noteOn(int number, double velocity) = 0;
    virtual void noteOff(int number, double velocity) = 0;
};

#endif // SYNTH_INOTESLISTENER_H

