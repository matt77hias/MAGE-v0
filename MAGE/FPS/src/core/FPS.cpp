#include "samples\brdf\brdf_scene.hpp"
#include "samples\sponza\sponza_scene.hpp"

using namespace mage;

struct Setup : public EngineSetup {

	Setup(HINSTANCE hinstance = nullptr, const wstring &name = MAGE_DEFAULT_APPLICATION_NAME)
		: EngineSetup(hinstance, name) {}
	
	virtual ~Setup() = default;

	virtual SharedPtr< Scene > CreateScene() const override {
		return std::make_shared< SponzaScene >();
	}
};

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

	// Create the engine setup structure.
	Setup setup(hinstance, L"Engine Control Test");

	// Create the engine, then run it.
	g_engine = new Engine(setup);
	g_engine->Run(nCmdShow);
	SAFE_DELETE(g_engine);

	return 0;
}

//VariableScript s(L"assets/scripts/script_test.vs");
//s.ExportScript(L"assets/scripts/output.vs");