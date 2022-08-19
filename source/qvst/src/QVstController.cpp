#include "pluginterfaces/base/ustring.h"
#include "pluginterfaces/base/ibstream.h"
#include "pluginterfaces/vst/ivstinterappaudio.h"
#include "QVstEditorView.h"
#include "QVstController.h"

QVstController::QVstController()
    : EditController()
{
}

QVstController::~QVstController()
{
}

Steinberg::tresult PLUGIN_API QVstController::initialize(Steinberg::FUnknown *pContext)
{
    Steinberg::tresult res = Steinberg::Vst::EditController::initialize(pContext);
    return res;
}

Steinberg::tresult PLUGIN_API QVstController::terminate()
{
    return Steinberg::Vst::EditController::terminate();
}

Steinberg::tresult PLUGIN_API QVstController::setComponentState(Steinberg::IBStream *pState)
{
    if (pState == nullptr) {
        return Steinberg::kResultFalse;
    }

    // Deserialize all parameters
    Steinberg::int32 nParams = getParameterCount();
    for (int i = 0; i < nParams; i++) {
        Steinberg::Vst::Parameter *pParam = parameters.getParameterByIndex(i);
        //Steinberg::Vst::ParameterInfo info;
        //getParameterInfo(i, &info);

        //if (info.flags & Steinberg::Vst::ParameterInfo::kIsReadOnly == 0) {
            Steinberg::Vst::ParamValue value = 0.0;
            if (pState->read(&value, sizeof(Steinberg::Vst::ParamValue)) != Steinberg::kResultOk) {
                return Steinberg::kResultFalse;
            }
            pParam->setNormalized(value);
        //}

    }

    return Steinberg::kResultOk;
}

Steinberg::IPlugView* PLUGIN_API QVstController::createView(Steinberg::FIDString name)
{
    if (strcmp(name, Steinberg::Vst::ViewType::kEditor) == 0) {
        return new QVstEditorView(this);
    }
    return 0;
}

Steinberg::tresult PLUGIN_API QVstController::getMidiControllerAssignment(Steinberg::int32 busIndex,
                                                                            Steinberg::int16 channel,
                                                                            Steinberg::Vst::CtrlNumber midiControllerNumber,
                                                                            Steinberg::Vst::ParamID& tag/*out*/) {
    if (m_midiCtrlMap.contains(midiControllerNumber)) {
        tag = m_midiCtrlMap.value(midiControllerNumber);
        return Steinberg::kResultTrue;
    }
    return Steinberg::kResultFalse;
}

Steinberg::tresult PLUGIN_API QVstController::queryInterface(const Steinberg::TUID _iid, void **obj)
{
    QUERY_INTERFACE (_iid, obj, Steinberg::Vst::IMidiMapping::iid, Steinberg::Vst::IMidiMapping)
    return Steinberg::Vst::EditController::queryInterface(_iid, obj);
}

void QVstController::addParameter(Steinberg::Vst::ParamID id, const QString &name, quint32 stepCount, double defaultValue, const QString &units, quint16 midiCtrl)
{
    wchar_t *wchName = new wchar_t[name.length() + 1];
    name.toWCharArray(wchName);
    wchName[name.length()] = 0;

    wchar_t *wchUnits = nullptr;
    if (!units.isEmpty()) {
        wchUnits = new wchar_t[units.length() + 1];
        units.toWCharArray(wchUnits);
        wchUnits[units.length()] = 0;
    }

    Steinberg::Vst::Parameter *pParam = parameters.addParameter(wchName, wchUnits, stepCount, defaultValue, 0, id);

    if (midiCtrl != 0) {
        m_midiCtrlMap.insert(midiCtrl, pParam->getInfo().id);
    }

    delete[] wchUnits;
    delete[] wchName;
}
