#include "samples\sponza\sponza_scene.hpp"

using namespace mage;

/**
 The user-provided entry point for MAGE.

 @param[in]		instance
				A handle to the current instance of the application.
 @param[in]		prev_instance
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
int WINAPI WinMain(HINSTANCE instance, HINSTANCE, LPSTR, int nCmdShow) {

	// Create the engine setup.
	EngineSetup setup(instance);
	
	// Create the engine.
	UniquePtr< Engine > engine = CreateEngine(setup);
	if (engine) {
		// Run the engine.
		return engine->Run(MakeUnique< SponzaScene >(), nCmdShow);
	}

	return 0;
}

//VariableScript s(L"assets/scripts/script_test.var");
//s.ExportScript(L"assets/scripts/output.var");