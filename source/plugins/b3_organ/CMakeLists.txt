project(b3_organ)

set(USE_QT TRUE)
set(USE_VST TRUE)

# Set to TRUE in order to enable the debug output console
set(VST_CONSOLE FALSE)

set(DEPENDS_QT
    Widgets
)

set(DEPENDS
    qvst
    synth
)

include(build_vst_plugin)
