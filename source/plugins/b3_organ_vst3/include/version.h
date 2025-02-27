#pragma once

#include "pluginterfaces/base/fplatform.h"

#define MAJOR_VERSION_STR "1"
#define MAJOR_VERSION_INT 1

#define SUB_VERSION_STR "1"
#define SUB_VERSION_INT 1

#define RELEASE_NUMBER_STR "0"
#define RELEASE_NUMBER_INT 0

#define BUILD_NUMBER_STR "1" // Build number to be sure that each result could identified.
#define BUILD_NUMBER_INT 1

// Version with build number (example "1.0.3.342")
#define FULL_VERSION_STR MAJOR_VERSION_STR "." SUB_VERSION_STR "." RELEASE_NUMBER_STR "." BUILD_NUMBER_STR

// Version without build number (example "1.0.3")
#define VERSION_STR MAJOR_VERSION_STR "." SUB_VERSION_STR "." RELEASE_NUMBER_STR

#define stringOriginalFilename	"b3_organ.vst3"
#if PLATFORM_64
#define stringFileDescription	"B3 Organ VST3 0731 (64Bit)"
#else
#define stringFileDescription	"B3 Organ VST3 0731"
#endif
#define stringCompanyName		"Misko Lee.\0"
#define stringLegalCopyright	"© 2022 Misko Lee."
#define stringLegalTrademarks	""
