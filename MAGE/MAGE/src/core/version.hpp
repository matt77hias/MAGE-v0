#pragma once

//-----------------------------------------------------------------------------
// Engine Defines
//-----------------------------------------------------------------------------
#pragma region

#define MAGE_VERSION_MAJOR 0
#define MAGE_VERSION_MINOR 1
#define MAGE_VERSION_PATCH 0

#define MAGE_QUOTE(S) #S
#define MAGE_STR(S) MAGE_QUOTE(S)
#define MAGE_VERSION_STRING MAGE_STR(MAGE_VERSION_MAJOR) "." MAGE_STR(MAGE_VERSION_MINOR) "." MAGE_STR(MAGE_VERSION_PATCH)

#pragma endregion