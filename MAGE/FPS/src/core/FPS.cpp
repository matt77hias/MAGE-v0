#include "stdafx.h"

#include "script\fps_input_controller_script.hpp"
#include "script\stats_script.hpp"

using namespace mage;

class TestScript final : public BehaviorScript {

public:

	TestScript(SharedPtr< Model > model)
		: BehaviorScript(), m_model(model) {}
	TestScript(const TestScript &script) = delete;
	TestScript(TestScript &&script) = default;
	virtual ~TestScript() = default;
	TestScript &operator=(const TestScript &script) = delete;
	TestScript &operator=(TestScript &&script) = delete;

	virtual void Update(double delta_time) override {
		m_model->GetTransform()->AddRotationY((float)delta_time);

		if (g_engine->GetInputManager()->GetKeyboard()->GetKeyPress(DIK_F2)) {
			//PostQuitMessage(0);
			VariableScript s(L"assets/scripts/script_test.vs");
			s.ExportScript(L"assets/scripts/output.vs");
		}
	}

private:
	
	SharedPtr< Model > m_model;
};

class TestScene final : public Scene {

public:

	TestScene()
		: Scene("testscene") {}
	TestScene(const TestScene &scene) = delete;
	TestScene(TestScene &&scene) = delete;
	virtual ~TestScene() = default;
	TestScene &operator=(const TestScene &scene) = delete;
	TestScene &operator=(TestScene &&scene) = delete;

	virtual void Load() override {

		// Camera
		SharedPtr< Camera > camera = CreatePerspectiveCamera("camera");
		camera->GetTransform()->SetTranslation(0.0f, 1.0f, -4.0f);
		SetCamera(camera);
		
		// ModelDescriptor
		MeshDescriptor< VertexPositionNormalTexture > mesh_desc(true, true);
		SharedPtr< ModelDescriptor > model_desc = CreateModelDescriptor(L"assets/models/cube.obj", mesh_desc);
		// Model
		SharedPtr< Model > model(new MeshModel("model", *model_desc));
		GetWorld()->AddModel(model);
		
		// Light
		SharedPtr< PointLight > light(new PointLight("light", 100.0f, RGBSpectrum(0.5f, 0.5f, 0.0f)));
		GetWorld()->AddLight(light);

		// Font
		SharedPtr< SpriteFont > font = CreateFont(L"assets/fonts/consolas.spritefont", SpriteFontDescriptor());
		// Text
		SharedPtr< SpriteText > text(new NormalSpriteText("text", font));
		GetWorld()->AddText(text);

		// Texture
		SharedPtr< Texture > texture = CreateTexture(L"assets/sprites/mage.dds");
		// Image
		SharedPtr< SpriteImage > image(new SpriteImage("image", texture));
		image->GetTransform()->SetScale(0.25f, 0.25f);
		image->GetTransform()->SetNormalizedTranslation(0.90f, 0.88f);
		GetWorld()->AddImage(image);

		// Scripts
		//SharedPtr< BehaviorScript > script(new TestScript(model));
		//AddScript(script);
		SharedPtr< BehaviorScript > controller(new FPSInputControllerScript(camera->GetTransform()));
		AddScript(controller);
		SharedPtr< BehaviorScript > stats(new StatsScript(text));
		AddScript(stats);
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
