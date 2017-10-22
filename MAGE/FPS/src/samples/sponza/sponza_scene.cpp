//-----------------------------------------------------------------------------
// Game Includes
//-----------------------------------------------------------------------------
#pragma region

#include "samples\sponza\sponza_scene.hpp"
#include "samples\forrest\forrest_scene.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "script\stats_script.hpp"
#include "script\input_controller_script.hpp"
#include "script\render_mode_script.hpp"
#include "script\rotation_script.hpp"
#include "script\switch_scene_script.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Game Definitions
//-----------------------------------------------------------------------------
namespace mage {

	SponzaScene::SponzaScene()
		: Scene("sponza_scene") {}

	SponzaScene::SponzaScene(SponzaScene &&scene) = default;

	SponzaScene::~SponzaScene() = default;

	void SponzaScene::Load() {
		
		//---------------------------------------------------------------------
		// Fog
		//---------------------------------------------------------------------
		auto fog = GetSceneFog();
		fog->SetDistanceFalloff(0.0f, 150.0f);

		//---------------------------------------------------------------------
		// Sky
		//---------------------------------------------------------------------
		auto sky_texture = 
			ResourceManager::Get()->GetOrCreateTexture(L"assets/textures/sky/sky.dds");
		auto sky = GetSky();
		sky->SetTexture(sky_texture);

		//---------------------------------------------------------------------
		// Camera
		//---------------------------------------------------------------------
		auto camera = Create< PerspectiveCameraNode >("camera");
		camera->GetTransform()->SetTranslationY(2.0f);

		//---------------------------------------------------------------------
		// ModelDescriptors
		//---------------------------------------------------------------------
		MeshDescriptor< VertexPositionNormalTexture > mesh_desc(true, true);
		auto model_desc_sponza = 
			ResourceManager::Get()->GetOrCreateModelDescriptor(L"assets/models/sponza/sponza.mdl", mesh_desc);
		auto model_desc_tree = 
			ResourceManager::Get()->GetOrCreateModelDescriptor(L"assets/models/tree/tree1a_lod0.mdl", mesh_desc);
		
		//---------------------------------------------------------------------
		// Models
		//---------------------------------------------------------------------
		auto model_sponza = CreateModel(*model_desc_sponza);
		model_sponza->GetTransform()->SetScale(10.0f);
		auto model_tree = CreateModel(*model_desc_tree);
		model_tree->GetTransform()->AddTranslationY(0.5f);
		
		//---------------------------------------------------------------------
		// Lights
		//---------------------------------------------------------------------
		auto omni_light = Create< OmniLightNode >("light");
		omni_light->GetTransform()->SetTranslationY(2.0f);
		omni_light->GetLight()->SetDistanceFalloff(0.0f, 3.0f);
		omni_light->GetLight()->SetIntensity(RGBSpectrum(4.0f));
		omni_light->GetLight()->EnableShadows();

		//auto spot_light = Create< SpotLightNode >("light");
		//spot_light->GetTransform()->SetTranslationY(2.0f);
		//spot_light->GetTransform()->SetRotationX(XM_PIDIV2);
		//spot_light->GetLight()->SetDistanceFalloff(0.0f, 3.0f);
		//spot_light->GetLight()->SetAngularCutoff(1.0f, sqrt(2.0f) / 2.0f);
		//spot_light->GetLight()->EnableShadows();

		auto light = Create< SpotLightNode >("light");
		light->GetLight()->SetDistanceFalloff(0.0f, 5.0f);
		light->GetLight()->SetAngularCutoff(1.0f, 0.5f);
		camera->AddChildNode(light);

		//---------------------------------------------------------------------
		// Image
		//---------------------------------------------------------------------
		auto texture_logo = CreateMAGETexture();
		auto logo = Create< SpriteImageNode >("logo", texture_logo);
		logo->GetSpriteTransform()->SetScale(0.25f, 0.25f);
		logo->GetSpriteTransform()->SetNormalizedTranslation(0.90f, 0.88f);

		//---------------------------------------------------------------------
		// Text
		//---------------------------------------------------------------------
		auto font = 
			ResourceManager::Get()->GetOrCreateSpriteFont(L"assets/fonts/consolas.spritefont");
		auto text = Create< NormalSpriteTextNode >("stats", font);

		//---------------------------------------------------------------------
		// Scripts
		//---------------------------------------------------------------------
		AddScript(MakeShared< SwitchSceneScript< ForrestScene > >());
		AddScript(MakeShared< RotationScript >(model_tree->GetTransform()));
		AddScript(MakeShared< FPSInputControllerScript >(camera->GetTransform()));
		AddScript(MakeShared< StatsScript >(text->GetSprite()));
		AddScript(MakeShared< RenderModeScript >(camera->GetSettings()));
	}
}