cmake_minimum_required(VERSION 3.15.0)
project(organ_vst3
		VERSION 1.0.0
		DESCRIPTION "My Organ"
		)
set(VST3_SDK_ROOT ${CMAKE_CURRENT_SOURCE_DIR}/../../../externals/vst3sdk)
set (CMAKE_PREFIX_PATH "C:/Qt/6.2.4/msvc2019_64/")
set(SMTG_OS_WINDOWS)
set(target organ_vst3)
set(Qt5_DIR "")
set(WIN 1)


include(vst_sdk.cmake)


set(sources
		include/projectversion.h
		include/PluginController.h
		include/ids.h
		include/PluginEffect.h
		include/PluginView.h
		include/version.h
		source/factory.cpp
		source/PluginController.cpp
		source/PluginEffect.cpp
		source/PluginView.cpp
		../../qvst/common/dllmain.cpp
		resource/plug.uidesc
		)

set(VST3_OUTPUT_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../../../dest)

smtg_add_vst3plugin(${target} ${VST3_SDK_ROOT} ${sources})
target_sources(${target}
		PRIVATE
		resource/info.rc
		)
smtg_target_add_plugin_resources(${target}
		RESOURCES
		resource/plug.uidesc
		resource/background.png
		resource/animation_knob.png
		resource/background_2x.png
		resource/background_3x.png
		resource/animation_knob_3x.png
		)


smtg_target_add_plugin_snapshots(${target}
		RESOURCES
		resource/A2EAF7DB320640F48EDE380DDF89562C_snapshot.png
		resource/A2EAF7DB320640F48EDE380DDF89562C_snapshot_2.0x.png
		)

target_compile_definitions(${target} PUBLIC -D_SILENCE_EXPERIMENTAL_FILESYSTEM_DEPRECATION_WARNING)



target_include_directories(organ_vst3 PUBLIC
		include
		../../qvst/include
		../../synth/include
		../../../externals/vst3sdk
		)
target_link_libraries(organ_vst3
		PRIVATE
		vstgui_support
		base
		sdk
		qvst
		synth
		)

target_compile_features(organ_vst3
		PUBLIC
		cxx_std_14
		)
