#include "stdafx.h"
#include "font\sprite_font.hpp"

using namespace mage;

class TestScript : public BehaviorScript {

public:

	TestScript(SharedPtr< Model > model)
		: BehaviorScript(), m_model(model), solid(true) {}
	TestScript(const TestScript &script) = delete;
	TestScript(TestScript &&script) = default;
	~TestScript() = default;
	TestScript &operator=(const TestScript &script) = delete;
	TestScript &operator=(TestScript &&script) = delete;

	virtual void Update(double elapsed_time, const Scene &scene) override {
		UNUSED(scene);
		m_model->GetTransform().AddRotationY((float)elapsed_time);

		if (g_engine->GetInputManager().GetKeyboard().GetKeyPress(DIK_UP)) {
			solid = !solid;
			if (solid) {
				g_engine->GetRenderer().GetRenderingState3D().SetCullCounterClockwiseRasterizerState();
			}
			else {
				g_engine->GetRenderer().GetRenderingState3D().SetWireframeRasterizerState();
			}
		}
		
		if (g_engine->GetInputManager().GetKeyboard().GetKeyPress(DIK_F2)) {
			//PostQuitMessage(0);
			VariableScript s(L"assets/scripts/script_test.vs");
			s.ExportScript(L"assets/scripts/output.vs");
		}
	}

private:
	
	SharedPtr< Model > m_model;
	bool solid;
};

class TestScene : public Scene {

public:

	TestScene()
		: Scene("testscene") {}
	TestScene(const TestScene &scene) = delete;
	TestScene(TestScene &&scene) = delete;
	~TestScene() = default;
	TestScene &operator=(const TestScene &scene) = delete;
	TestScene &operator=(TestScene &&scene) = delete;

	virtual void Load() override {

		// @TODO: cameras straight from renderer?
		const float width  = (float)g_engine->GetRenderer().GetWidth();
		const float height = (float)g_engine->GetRenderer().GetHeight();
		SharedPtr< Camera > camera(new PerspectiveCamera("camera", width, height));
		SetCamera(camera);
		camera->GetTransform().SetTranslation(0.0f, 1.0f, -4.0f);
		
		CombinedShader shader = CreateLambertianShader();

		MeshDescriptor< VertexPositionNormalTexture > mesh_desc(true, true);
		SharedPtr< ModelDescriptor > model_desc = CreateModelDescriptor(L"assets/models/cube.obj", mesh_desc);
		SharedPtr< Model > test_model(new MeshModel("model", *model_desc, shader));
		GetWorld().AddModel(test_model);
		
		SharedPtr< PointLight > light(new PointLight("light", 100.0f, RGBSpectrum(0.5f, 0.5f, 0.0f)));
		GetWorld().AddLight(light);

		SharedPtr< BehaviorScript > test_script(new TestScript(test_model));
		AddScript(test_script);

		//TODO
		GetWorld().m_font = SharedPtr< SpriteFont >(new SpriteFont(g_engine->GetRenderer().GetDevice(), L"assets/fonts/comicsansms.spritefont", SpriteFontDescriptor()));
	}
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
	SAFE_DELETE(g_engine);

	return 0;
}
