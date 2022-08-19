project(qvst)

set(USE_QT TRUE)
set(USE_VST TRUE)

set(DEPENDS_QT
    Widgets
)

set(DEPENDS
)

set(QVST_SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR} CACHE INTERNAL "QVst source directory" FORCE)
set(QVST_PLUGIN_DLL_DEF ${QVST_SRC_DIR}/common/plugin.def CACHE INTERNAL "QVst plugin dll def file" FORCE)
set(QVST_PLUGIN_DLLMAIN_SRC ${QVST_SRC_DIR}/common/dllmain.cpp CACHE INTERNAL "QVst plugin dllmain source file" FORCE)

include(build_library)
