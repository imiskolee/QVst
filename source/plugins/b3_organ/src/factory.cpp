#include "pluginterfaces/base/funknown.h"
#include "public.sdk/source/main/pluginfactoryvst3.h"
#include "ids.h"
#include "version.h"
#include "PluginEffect.h"
#include "PluginController.h"

#define stringPluginName "B3 Organ QVST"


BEGIN_FACTORY_DEF ("Arthur Benilov",
                   "https://github.com/Archie3d/QVst",
                   "mailto:arthur.benilov@gmail.com")

	DEF_CLASS2 (INLINE_UID_FROM_FUID(PluginProcessorUID),
				PClassInfo::kManyInstances,
				kVstAudioEffectClass,
				stringPluginName,
				Vst::kDistributable,
                Vst::PlugType::kInstrumentSynth,
				FULL_VERSION_STR,		// Plug-in version (to be changed)
				kVstVersionString,
				PluginEffect::createInstance)

    DEF_CLASS2 (INLINE_UID_FROM_FUID(PluginControllerUID),
				PClassInfo::kManyInstances,
				kVstComponentControllerClass,
				stringPluginName "Controller",	// controller name (could be the same than component name)
				0,						// not used here
				"",						// not used here
				FULL_VERSION_STR,		// Plug-in version (to be changed)
				kVstVersionString,
                PluginController::createInstance)

END_FACTORY

bool InitModule () { return true; }
bool DeinitModule () { return true; }

