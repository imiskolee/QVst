#pragma once

#include "QVstController.h"

class PluginController : public QVstController
{
public:

    PluginController();

    Steinberg::tresult PLUGIN_API initialize(Steinberg::FUnknown *pContext);

    Steinberg::IPlugView* PLUGIN_API createView(Steinberg::FIDString name);

    static Steinberg::FUnknown* createInstance (void*) { return (Steinberg::Vst::IEditController*)new PluginController(); }
};
