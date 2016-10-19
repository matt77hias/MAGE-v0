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
using std::wstring;

#include <windows.h>

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

namespace mage {

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

}

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#include "collection/collection.hpp"
#include "math/math.hpp"
#include "parallel/parallel.hpp"
#include "log/log.hpp"
#include "memory/memory.hpp"
#include "resource/resource.hpp"

namespace mage {

	//-----------------------------------------------------------------------------
	// EngineSetup
	//-----------------------------------------------------------------------------
	struct EngineSetup {

	public:

		EngineSetup(const wstring &name = L"Application") : m_instance(NULL), m_name(name) {}
		EngineSetup(const EngineSetup &setup) : m_instance(setup.m_instance), m_name(setup.m_name) {}

		// Application instance handle
		HINSTANCE m_instance;
		// Name of the application
		wstring m_name;
	};

	//-----------------------------------------------------------------------------
	// Engine
	//-----------------------------------------------------------------------------
	class Engine {

	public:

		Engine(const EngineSetup *setup = NULL);
		virtual ~Engine();

		void Run();

		HWND GetWindow() const {
			return m_window;
		}
		void SetDeactiveFlag(bool deactive) {
			m_deactive = deactive;
		}

	private:

		// Indicates if the engine is loaded
		bool m_loaded;
		// Main window handle
		HWND m_window;
		// Indicates if the application is active or not
		bool m_deactive;
		// Copy of the engine setup structure
		EngineSetup m_setup;
	};

	extern Engine *g_engine;

}