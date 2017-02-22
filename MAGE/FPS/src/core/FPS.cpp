#include "stdafx.h"

#include "core\engine.hpp"
#include "camera\perspective_camera.hpp"
#include "model\meshmodel.hpp"
#include "shader\lambertian_shader.hpp"
#include "scripting\behavior_script.hpp"

using namespace mage;

class TestScript : public BehaviorScript {

public:

	TestScript(SharedPtr< Model > model)
		: BehaviorScript(), m_model(model) {}
	~TestScript() = default;

	virtual void Update(double elapsed_time, const Scene &scene) override {
		UNUSED(scene);
		m_model->GetTransform().AddRotationY((float)elapsed_time);
		
		if (g_engine->GetInputManager().GetKeyboard().GetKeyPress(DIK_F2)) {
			//PostQuitMessage(0);
			VariableScript s(L"C:/Users/Matthias/Documents/Visual Studio 2015/Projects/MAGE/MAGE/FPS/script/script_test.vs");
			s.ExportScript(L"C:/Users/Matthias/Documents/Visual Studio 2015/Projects/MAGE/MAGE/FPS/script/output.vs");
		}
	}

private:
	
	TestScript(const TestScript &script) = delete;
	TestScript &operator=(const TestScript &script) = delete;

	SharedPtr< Model > m_model;
};

class TestScene : public Scene {

public:

	TestScene()
		: Scene("testscene") {}
	~TestScene() = default;

	virtual void Load() override {

		// @TODO: put the display mode in the renderer
		const float width  = (float)g_device_enumeration->GetDisplayMode()->Width;
		const float height = (float)g_device_enumeration->GetDisplayMode()->Height;
		SharedPtr< Camera > camera(new PerspectiveCamera(width, height));
		SetCamera(camera);
		camera->GetTransform().SetTranslationZ(-6.0f);
		
		ComPtr< ID3D11Device2 > device = g_engine->GetRenderer().GetDevice();
		
		CombinedShader shader = CreateLambertianShader(device);

		MeshDescriptor desc(true, true);
		SharedPtr< Model > test_model(new MeshModel< VertexPositionNormalTexture >("model", device, L"C:/Users/Matthias/Documents/Visual Studio 2015/Projects/MAGE/MAGE/FPS/model/cube2.obj", desc, shader));
		GetWorld().AddModel(test_model);

		SharedPtr< BehaviorScript > test_script(new TestScript(test_model));
		AddScript(test_script);
	}

private:

	TestScene(const TestScene &scene) = delete;
	TestScene &operator=(const TestScene &scene) = delete;
};

struct TestSetup : public EngineSetup {

	TestSetup(HINSTANCE hinstance = nullptr, const wstring &name = MAGE_DEFAULT_APPLICATION_NAME)
		: EngineSetup(hinstance, name) {}
	virtual ~TestSetup() = default;

	virtual SharedPtr< Scene > CreateScene() const override {
		return SharedPtr< Scene >(new TestScene());
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
 @return		If the function succeeds, terminating when it receives a WM_QUIT message, 
				it returns the exit value contained in that message's @c wParam parameter. 
				If the function terminates before entering the message loop, it returns 0.
 */
int WINAPI WinMain(HINSTANCE hinstance, HINSTANCE, LPSTR, int nCmdShow) {

	// Create the engine setup structure.
	TestSetup setup(hinstance, L"Engine Control Test");

	// Create the engine, then run it.
	g_engine = new Engine(setup);
	g_engine->Run(nCmdShow);
	delete g_engine;

	return 0;
}
