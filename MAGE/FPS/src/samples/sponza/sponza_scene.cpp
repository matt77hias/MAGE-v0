//-----------------------------------------------------------------------------
// Game Includes
//-----------------------------------------------------------------------------
#pragma region

#include "samples\sponza\sponza_scene.hpp"
#include "samples\sibenik\sibenik_scene.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "script\input_controller_script.hpp"
#include "script\render_mode_script.hpp"
#include "script\rotation_script.hpp"
#include "script\stats_script.hpp"
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
		fog->SetDensity(0.001f);

		//---------------------------------------------------------------------
		// Sky
		//---------------------------------------------------------------------
		auto sky = GetSky();
		auto sky_texture =
			ResourceManager::Get()->GetOrCreateTexture(L"assets/textures/sky/sky.dds");
		sky->SetTexture(sky_texture);

		//---------------------------------------------------------------------
		// Camera
		//---------------------------------------------------------------------
		auto camera = Create< PerspectiveCameraNode >();
		camera->GetTransform()->SetTranslationY(2.0f);
		//camera->GetCamera()->SetLensRadius(0.01f);
		//camera->GetCamera()->SetFocalLength(3.0f);
		//camera->GetCamera()->SetMaximumCoCRadius(2.0f);
		//camera->GetViewport().SetNormalizedWidth(0.5f);

		//auto camera2 = Create< PerspectiveCameraNode >();
		//camera2->GetTransform()->SetTranslationY(2.0f);
		//camera2->GetViewport().SetNormalizedTopLeft(0.5f, 0.0f);
		//camera2->GetViewport().SetNormalizedWidth(0.5f);

		//---------------------------------------------------------------------
		// ModelDescriptors
		//---------------------------------------------------------------------
		MeshDescriptor< VertexPositionNormalTexture > mesh_desc(true, true);
		auto model_desc_sponza = 
			ResourceManager::Get()->GetOrCreateModelDescriptor(L"assets/models/sponza/sponza.mdl",    mesh_desc);
		auto model_desc_tree = 
			ResourceManager::Get()->GetOrCreateModelDescriptor(L"assets/models/tree/tree1a_lod0.mdl", mesh_desc);
		
		//---------------------------------------------------------------------
		// Models
		//---------------------------------------------------------------------
		auto model_sponza = CreateModel(*model_desc_sponza);
		model_sponza->GetTransform()->SetScale(10.0f);
		model_sponza->GetTransform()->SetTranslationY(2.1f);
		auto model_tree = CreateModel(*model_desc_tree);
		model_tree->GetTransform()->AddTranslationY(1.0f);
		
		//---------------------------------------------------------------------
		// Lights
		//---------------------------------------------------------------------
		auto omni_light = Create< OmniLightNode >();
		omni_light->GetTransform()->SetTranslationY(2.0f);
		omni_light->GetLight()->SetRange(5.0f);
		omni_light->GetLight()->SetIntensity(4.0f);
		omni_light->GetLight()->EnableShadows();

		auto light = Create< SpotLightNode >();
		light->GetLight()->SetRange(5.0f);
		light->GetLight()->SetAngularCutoff(1.0f, 0.5f);
		camera->AddChildNode(light);

		//---------------------------------------------------------------------
		// Image
		//---------------------------------------------------------------------
		auto logo = Create< SpriteImageNode >();
		logo->GetSprite()->SetBaseColorTexture(CreateMAGETexture());
		logo->GetSpriteTransform()->SetScale(0.25f, 0.25f);
		logo->GetSpriteTransform()->SetNormalizedTranslation(0.90f, 0.88f);

		//---------------------------------------------------------------------
		// Text
		//---------------------------------------------------------------------
		auto text = Create< NormalSpriteTextNode >();

		//---------------------------------------------------------------------
		// Scripts
		//---------------------------------------------------------------------
		Create< script::SwitchSceneScript< SibenikScene > >();
		Create< script::RotationScript >(model_tree->GetTransform());
		Create< script::FPSInputControllerScript >(camera->GetTransform());
		Create< script::RenderModeScript >(camera->GetSettings());
		Create< script::StatsScript >(text->GetSprite());
	}
}