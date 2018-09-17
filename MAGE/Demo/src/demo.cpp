#include "samples\sponza\sponza_scene.hpp"

/**
 The user-provided entry point for MAGE.

 @param[in]		instance
				A handle to the current instance of the application.
 @param[in]		prev_instance
				A handle to the previous instance of the application.
				This parameter is always @c nullptr.
 @param[in]		lpCmdLine
				The command line for the application, excluding the program 
				name.
 @param[in]		nCmdShow
				Controls how the window is to be shown.
 @return		@c 0, if the function terminates before entering the message 
				loop.
 @return		The @c wParam parameter contained in the @c WM_QUIT message.
 */
int WINAPI WinMain(HINSTANCE instance, 
				   [[maybe_unused]] HINSTANCE prev_instance, 
				   [[maybe_unused]] LPSTR lpCmdLine, 
				   int nCmdShow) {

	using namespace mage;

	// Create the engine setup.
	const auto not_null_instance = NotNull< HINSTANCE >(instance);
	EngineSetup setup(not_null_instance);

	// Create the engine.
	UniquePtr< Engine > engine = CreateEngine(setup);
	if (engine) {

		const char* const ca = "foo";
		const wchar_t* const wca = L"bar";
		const std::string sa = ca;
		const std::wstring wsa = wca;
		const std::string_view sva = ca;
		const std::wstring_view wsva = wca;

		Warning("{}", wsa);
		Warning(L"{}", sa);
		Warning("{}", wsva);
		Warning(L"{}", sva);

		// Run the engine.
		return engine->Run(MakeUnique< SponzaScene >(), nCmdShow);
	}

	return 0;
}

//VariableScript s(L"assets/scripts/script_test.var");
//s.ExportScript(L"assets/scripts/output.var");