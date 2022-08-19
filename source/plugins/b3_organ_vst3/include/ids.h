#pragma once

#include "pluginterfaces/base/funknown.h"

// parameter tags
enum {
    Param_DrawBar_16,
    Param_DrawBar_5_13,
    Param_DrawBar_8,
    Param_DrawBar_4,
    Param_DrawBar_2_35,
    Param_DrawBar_2,
    Param_DrawBar_1_35,
    Param_DrawBar_1_13,
    Param_DrawBar_1,

    Param_Attack,
    Param_Decay,
    Param_Sustain,
    Param_Release,

    Param_Modulation,
    Param_Volume
};

// unique class ids
// These are generated by guidgen tool from Visual Studio.

static const Steinberg::FUID PluginProcessorUID (0x671b06b2, 0x4d6742a1, 0xa6922457, 0xbea26ec0);
static const Steinberg::FUID PluginControllerUID (0xc7ad26fa, 0x439c4c82, 0xbfab5b87, 0x573fc144);
