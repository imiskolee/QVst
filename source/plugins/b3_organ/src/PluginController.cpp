#include <QDebug>
#include "ids.h"
#include "pluginterfaces/base/ustring.h"
#include "pluginterfaces/base/ibstream.h"
#include "pluginterfaces/vst/ivstinterappaudio.h"
#include "PluginView.h"
#include "PluginController.h"

#include "QVstApplication.h"

PluginController::PluginController()
    : QVstController()
{
}

Steinberg::tresult PLUGIN_API PluginController::initialize(Steinberg::FUnknown *pContext)
{
    Steinberg::tresult res = Steinberg::Vst::EditController::initialize(pContext);
    if (res == Steinberg::kResultOk) {
        addParameter(Param_DrawBar_16, "16", 0, 0.0);
        addParameter(Param_DrawBar_5_13, "5 1/3", 0, 0.0);
        addParameter(Param_DrawBar_8, "8", 0, 0.0);
        addParameter(Param_DrawBar_4, "4", 0, 0.0);
        addParameter(Param_DrawBar_2_35, "2 3/5", 0, 0.0);
        addParameter(Param_DrawBar_2, "2", 0, 0.0);
        addParameter(Param_DrawBar_1_35, "1 3/5", 0, 0.0);
        addParameter(Param_DrawBar_1_13, "1 1/3", 0, 0.0);
        addParameter(Param_DrawBar_1, "1", 0, 0.0);

        addParameter(Param_Attack, "Attack", 0, 0.0, "s");
        addParameter(Param_Decay, "Decay", 0, 0.0, "s");
        addParameter(Param_Sustain, "Sustain", 0, 0.0);
        addParameter(Param_Release, "Release", 0, 0.0, "s");

        addParameter(Param_Modulation, "Modulation", 0, 0.0);
    }
    return res;
}

Steinberg::IPlugView* PLUGIN_API PluginController::createView(Steinberg::FIDString name)
{
    if (strcmp(name, Steinberg::Vst::ViewType::kEditor) == 0) {
        return new PluginView(this);
    }
    return 0;
}
