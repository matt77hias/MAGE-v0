#include "samples\forrest\forrest_scene.hpp"

using namespace mage;

/**
 The user-provided entry point for MAGE.

 @param[in]		hinstance
				A handle to the current instance of the application.
 @param[in]		hPrevInstance
				A handle to the previous instance of the application.
				This parameter is always @c nullptr.
 @param[in]		lpCmdLine
				The command line for the application, excluding the program name.
 @param[in]		nCmdShow
				Controls how the window is to be shown.
 @return		If the function succeeds, terminating when it receives a @c WM_QUIT message, 
				it returns the exit value contained in that message's @c wParam parameter. 
				If the function terminates before entering the message loop, it returns 0.
 */
int WINAPI WinMain(HINSTANCE hinstance, HINSTANCE, LPSTR, int nCmdShow) {

#ifdef _DEBUG
	const int debug_flags = _CrtSetDbgFlag(_CRTDBG_REPORT_FLAG);
	// Perform automatic leak checking at program exit through a call to 
	// _CrtDumpMemoryLeaks and generate an error report if the application 
	// failed to free all the memory it allocated.
	_CrtSetDbgFlag(debug_flags | _CRTDBG_LEAK_CHECK_DF);
#endif

	// Create the engine setup.
	EngineSetup setup(hinstance, L"MAGE");
	// Create the engine.
	UniquePtr< Engine > engine = MakeUnique< Engine >(setup);
	
	if (engine->IsLoaded()) {
		// Create the scene.
		UniquePtr< Scene > scene = MakeUnique< ForrestScene >();

		// Run the engine.
		return engine->Run(std::move(scene), nCmdShow);
	}

	return 0;
}

//VariableScript s(L"assets/scripts/script_test.var");
//s.ExportScript(L"assets/scripts/output.var");