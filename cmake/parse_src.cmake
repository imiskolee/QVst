# Parse source code folder

file(GLOB SRC_CPP ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)
file(GLOB SRC_C ${CMAKE_CURRENT_SOURCE_DIR}/src/*.c)
file(GLOB SRC_H ${CMAKE_CURRENT_SOURCE_DIR}/include/*.h)
file(GLOB SRC_H_PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src/*.h)
file(GLOB RES ${CMAKE_CURRENT_SOURCE_DIR}/resources/*.qrc)
file(GLOB RCS ${CMAKE_CURRENT_SOURCE_DIR}/resources/*.rc)

include_directories("${CMAKE_CURRENT_SOURCE_DIR}/include")
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/src")

# Add Windows resources
set(WINRC "")
if(WIN32)
    set(WINRC ${RCS})
endif()

# VST SDK dependency
if(USE_VST)
    include_directories(${VST_INCLUDE})
endif()

# Add dependencies includes
foreach(DEP ${DEPENDS})
    if(${DEP}_INCLUDES)
        include_directories(${${DEP}_INCLUDES})
    else()
        message(FATAL_ERROR "Library ${DEP} has not been processed yet. Required by target ${PROJECT_NAME}")
    endif()
endforeach()

# Look for Qt dependencies
if(USE_QT)
    include_directories($ENV{QTDIR}/include)
    include_directories($ENV{QTDIR}/include/QtCore)
    include_directories($ENV{QTDIR}/include/QWidgets)
    set(QT5_PATH $ENV{QTDIR})
    set(QT5_PATH_CMAKE ${QT5_PATH}/lib/cmake)
    set(QT5CORE_PATH_CMAKE ${QT5_PATH_CMAKE}/Qt6Core)
    set(Qt6CoreTools_DIR ${QT5_PATH}/)
    list(APPEND CMAKE_PREFIX_PATH $ENV{QTDIR})
    find_package(Qt6Core REQUIRED HINTS ${QT5_PATH} ${QT5_PATH_CMAKE} ${QT5CORE_PATH_CMAKE})
    find_package(Qt6Widgets REQUIRED HINTS ${QT5_PATH} ${QT5_PATH_CMAKE} ${QT5CORE_PATH_CMAKE})
    qt6_add_resources(SRC_RES ${RES})
endif()
