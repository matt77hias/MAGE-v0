#pragma once

#include "targetver.h"

//-----------------------------------------------------------------------------
// System Includes
//-----------------------------------------------------------------------------
#include <stdint.h>
#include <stdio.h>
#include <tchar.h>

#include <string>
using std::string;

//-----------------------------------------------------------------------------
// Defines
//-----------------------------------------------------------------------------
#ifndef MAGE_POINTER_SIZE
#if defined(__amd64__) || defined(_M_X64)
#define MAGE_POINTER_SIZE 8
#elif defined(__i386__) || defined(_M_IX86)
#define MAGE_POINTER_SIZE 4
#endif
#endif

//-----------------------------------------------------------------------------
// Declarations and Definitions
//-----------------------------------------------------------------------------
struct GeneralConfiguration {
	GeneralConfiguration() : m_quiet(false), m_verbose(false) {}
	
	bool IsQuiet() const {
		return m_quiet;
	}
	bool IsVerbose() const {
		return m_verbose;
	}

	bool m_quiet, m_verbose;
};
extern GeneralConfiguration general_configuration;

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#include "math/math.hpp"
#include "collection/collection.hpp"
#include "parallel/parallel.hpp"
#include "log/log.hpp"
#include "memory/memory.hpp"
#include "resource/resource.hpp"