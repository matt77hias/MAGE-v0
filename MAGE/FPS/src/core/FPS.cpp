#include "core\engine.hpp"
#include "text\normal_sprite_text.hpp"
#include "sprite\sprite_image.hpp"
#include "script\fps_input_controller_script.hpp"
#include "script\stats_script.hpp"
#include "script\wireframe_script.hpp"

using namespace mage;

class TestScript final : public BehaviorScript {

public:

	TestScript(TransformNode *transform)
		: BehaviorScript(), m_transform(transform) {}
	TestScript(const TestScript &script) = delete;
	TestScript(TestScript &&script) = default;
	virtual ~TestScript() = default;
	TestScript &operator=(const TestScript &script) = delete;
	TestScript &operator=(TestScript &&script) = delete;

	virtual void Update(double delta_time) override {
		m_transform->AddRotationY(static_cast< float >(delta_time));

		if (g_engine->GetInputManager()->GetKeyboard()->GetKeyPress(DIK_F2)) {
			//PostQuitMessage(0);
			VariableScript s(L"assets/scripts/script_test.vs");
			s.ExportScript(L"assets/scripts/output.vs");
		}
	}

private:
	
	TransformNode * const m_transform;
};

class TestScene final : public Scene {

public:

	TestScene()
		: Scene("testscene") {}
	TestScene(const TestScene &scene) = delete;
	TestScene(TestScene &&scene) = default;
	virtual ~TestScene() = default;
	TestScene &operator=(const TestScene &scene) = delete;
	TestScene &operator=(TestScene &&scene) = delete;

private:

	virtual void Load() override {

		//---------------------------------------------------------------------
		// Camera
		//---------------------------------------------------------------------
		SharedPtr< PerspectiveCameraNode > camera = CreatePerspectiveCameraNode();
		camera->GetTransform()->SetTranslationY(4.0f);
		SetCamera(camera);
		
		//---------------------------------------------------------------------
		// ModelDescriptors
		//---------------------------------------------------------------------
		MeshDescriptor< VertexPositionNormalTexture > mesh_desc(true, true);
		SharedPtr< ModelDescriptor > model_desc_sponza = CreateModelDescriptor(L"assets/models/sponza/sponza.mdl", mesh_desc);
		SharedPtr< ModelDescriptor > model_desc_sphere = CreateModelDescriptor(L"assets/models/sphere/sphere.mdl", mesh_desc);
		//---------------------------------------------------------------------
		// Models
		//---------------------------------------------------------------------
		SharedPtr< ModelNode > model_sponza = CreateModelNode(*model_desc_sponza);
		model_sponza->GetTransform()->SetScale(10.0f);
		SharedPtr< ModelNode > model_sphere = CreateModelNode(*model_desc_sphere);
		model_sphere->GetTransform()->AddTranslationY(0.5f);

		//---------------------------------------------------------------------
		// Lights
		//---------------------------------------------------------------------
		SharedPtr< OmniLightNode > omni_light = CreateOmniLightNode();
		omni_light->GetTransform()->SetTranslationY(2.0f);
		omni_light->GetLight()->SetDistanceFalloff(0.0f, 2.0f);
		SharedPtr< SpotLightNode > spot_light = CreateSpotLightNode();
		spot_light->GetLight()->SetAngularCutoff(1.0f, 0.86602540f);
		spot_light->GetLight()->SetDistanceFalloff(0.0f, 3.0f);
		camera->AddChildNode(spot_light);

		//---------------------------------------------------------------------
		// Texture
		//---------------------------------------------------------------------
		SharedPtr< Texture > texture_logo = CreateTexture(L"assets/sprites/mage.dds");
		//---------------------------------------------------------------------
		// Image
		//---------------------------------------------------------------------
		SharedPtr< SpriteImage > logo(new SpriteImage("logo", texture_logo));
		logo->GetTransform()->SetScale(0.25f, 0.25f);
		logo->GetTransform()->SetNormalizedTranslation(0.90f, 0.88f);
		AddSprite(logo);

		//---------------------------------------------------------------------
		// Font
		//---------------------------------------------------------------------
		SharedPtr< SpriteFont > font = CreateFont(L"assets/fonts/consolas.spritefont", SpriteFontDescriptor());
		//---------------------------------------------------------------------
		// Text
		//---------------------------------------------------------------------
		SharedPtr< SpriteText > text(new NormalSpriteText("text", font));
		AddSprite(text);

		//---------------------------------------------------------------------
		// Scripts
		//---------------------------------------------------------------------
		//SharedPtr< BehaviorScript > script(new TestScript(model_sphere->GetTransform()));
		//AddScript(script);
		
		SharedPtr< BehaviorScript > controller_script(new FPSInputControllerScript(camera->GetTransform()));
		AddScript(controller_script);
		SharedPtr< BehaviorScript > stats_script(new StatsScript(text));
		AddScript(stats_script);
		SharedPtr< BehaviorScript > wireframe_script(new WireframeScript());
		AddScript(wireframe_script);
	}
};

#include "samples\brdf\brdf_scene.hpp"

struct TestSetup : public EngineSetup {

	TestSetup(HINSTANCE hinstance = nullptr, const wstring &name = MAGE_DEFAULT_APPLICATION_NAME)
		: EngineSetup(hinstance, name) {}
	virtual ~TestSetup() = default;

	virtual SharedPtr< Scene > CreateScene() const override {
		return SharedPtr< Scene >(new BRDFScene());
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

	// Create the engine setup structure.
	TestSetup setup(hinstance, L"Engine Control Test");

	// Create the engine, then run it.
	g_engine = new Engine(setup);
	g_engine->Run(nCmdShow);
	SAFE_DELETE(g_engine);

	return 0;
}
