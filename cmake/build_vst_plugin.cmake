if(VST_CONSOLE)
    add_definitions(-DQVST_CONSOLE)
endif()

# Parse target source code
include(parse_src)

# Build static library
add_library(${PROJECT_NAME} SHARED ${SRC_CPP} ${SRC_C} ${SRC_H} ${SRC_H_PRIVATE} ${SRC_RES} ${QVST_PLUGIN_DLLMAIN_SRC})
target_link_libraries(${PROJECT_NAME} ${DEPENDS})

# Plugin DLL interface definitions
set(CMAKE_SHARED_LINKER_FLAGS 
    "${CMAKE_SHARED_LINKER_FLAGS} /DEF:${QVST_PLUGIN_DLL_DEF}"
)

# Link with dependencies
include(link_libs)

# Process unit tests
include(parse_tests)

# Install this shared library
install(TARGETS ${PROJECT_NAME}
        RUNTIME DESTINATION ${INSTALL_BIN_PATH}
        LIBRARY DESTINATION ${INSTALL_LIB_PATH}
        COMPONENT plugins)

