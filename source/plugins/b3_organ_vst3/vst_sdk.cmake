function(my_smtg_add_vst3plugin target sdkroot)
    set(sources ${ARGN})

    add_library(${target} MODULE ${sources})
    set_target_properties(${target} PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${VST3_OUTPUT_DIR})

    if(MAC)
        set_target_properties(${target} PROPERTIES BUNDLE TRUE)
        if(XCODE)
            set_target_properties(${target} PROPERTIES XCODE_ATTRIBUTE_GENERATE_PKGINFO_FILE "YES")
            set_target_properties(${target} PROPERTIES XCODE_ATTRIBUTE_WRAPPER_EXTENSION "vst3")
        else()
            set_target_properties(${target} PROPERTIES BUNDLE_EXTENSION "vst3")
        endif()
        smtg_set_exported_symbols(${target} "${sdkroot}/public.sdk/source/main/macexport.exp")

        target_link_libraries(${target} PRIVATE "-framework CoreFoundation")
    elseif(WIN)
        set_target_properties(${target} PROPERTIES SUFFIX ".vst3")
        set_target_properties(${target} PROPERTIES LINK_FLAGS "/EXPORT:GetPluginFactory")
    elseif(LINUX)
        # ...
        EXECUTE_PROCESS( COMMAND uname -m COMMAND tr -d '\n' OUTPUT_VARIABLE ARCHITECTURE )
        set(target_lib_dir ${ARCHITECTURE}-linux)
        set_target_properties(${target} PROPERTIES PREFIX "")
        set_target_properties(${target} PROPERTIES LIBRARY_OUTPUT_DIRECTORY "${VST3_OUTPUT_DIR}/${target}.vst3/Contents/${target_lib_dir}")
        add_custom_command(TARGET ${target} PRE_LINK
                COMMAND ${CMAKE_COMMAND} -E make_directory
                "${VST3_OUTPUT_DIR}/${target}.vst3/Contents/Resources"
                )

        # Strip symbols in Release config
        if(${CMAKE_BUILD_TYPE} MATCHES Release)
            smtg_strip_symbols(${target})
        endif()
    endif()
endfunction()