# QVst

VST plugins using Qt.

This is a small framework that allows creating VST3 plugins with Qt 5.
Includes VSTi plugin example.

![Screenshot 1](https://raw.githubusercontent.com/Archie3d/QVst/master/screenshots/vst3_host.png)

# Building
Configure with CMake. No external dependencies required (except Qt 5). VST3 SDK is referenced as git submodule.

Compilation tested with MS Windows (Visual Studio 2017), and Qt 5.9.1.

# Limitations
This software is work in progress. MS Windows VST3 hosts only.