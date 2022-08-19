#ifndef QVSTCONTROLLER_H
#define QVSTCONTROLLER_H

#include <QString>
#include <QMap>
#include "pluginterfaces/base/funknown.h"
#include "pluginterfaces/vst/ivstmidicontrollers.h"
#include "public.sdk/source/vst/vsteditcontroller.h"

class QVstController : public virtual Steinberg::Vst::EditController,
                       public virtual Steinberg::Vst::IMidiMapping
{
public:

    QVstController();
    ~QVstController();

    Steinberg::tresult PLUGIN_API initialize(Steinberg::FUnknown *pContext);
    Steinberg::tresult PLUGIN_API terminate();

    Steinberg::tresult PLUGIN_API setComponentState(Steinberg::IBStream *pState);

    Steinberg::IPlugView* PLUGIN_API createView(Steinberg::FIDString name);

    Steinberg::tresult PLUGIN_API getMidiControllerAssignment(Steinberg::int32 busIndex,
                                                              Steinberg::int16 channel,
                                                              Steinberg::Vst::CtrlNumber midiControllerNumber,
                                                              Steinberg::Vst::ParamID& tag/*out*/);

    Steinberg::tresult PLUGIN_API queryInterface(const Steinberg::TUID _iid, void** obj);

    void addParameter(Steinberg::Vst::ParamID id, const QString &name, quint32 stepCount, double defaultValue = 0.0, const QString &units = QString(), quint16 midiCtrl = 0);

    DELEGATE_REFCOUNT(Steinberg::Vst::EditController)

private:

    // MIDI controllers mapping
    QMap<Steinberg::Vst::CtrlNumber, Steinberg::Vst::ParamID> m_midiCtrlMap;


};

#endif // QVSTCONTROLLER_H

