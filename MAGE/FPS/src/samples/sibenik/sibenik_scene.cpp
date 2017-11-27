//-----------------------------------------------------------------------------
// Game Includes
//-----------------------------------------------------------------------------
#pragma region

#include "samples\sibenik\sibenik_scene.hpp"
#include "samples\forrest\forrest_scene.hpp"

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

	SibenikScene::SibenikScene()
		: Scene("sibenik_scene") {}

	SibenikScene::SibenikScene(SibenikScene &&scene) = default;

	SibenikScene::~SibenikScene() = default;

	void SibenikScene::Load() {
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

		//---------------------------------------------------------------------
		// ModelDescriptors
		//---------------------------------------------------------------------
		MeshDescriptor< VertexPositionNormalTexture > mesh_desc(true, true);

		auto model_desc_sibenik = 
			ResourceManager::Get()->GetOrCreateModelDescriptor(L"assets/models/sibenik/sibenik.obj", mesh_desc);
		auto model_desc_tree = 
			ResourceManager::Get()->GetOrCreateModelDescriptor(L"assets/models/tree/tree1a_lod0.mdl", mesh_desc);
		
		//---------------------------------------------------------------------
		// Models
		//---------------------------------------------------------------------
		auto model_sibenik = CreateModel(*model_desc_sibenik);
		model_sibenik->GetTransform()->SetScale(30.0f);
		model_sibenik->GetTransform()->SetTranslationY(12.0f);
		auto model_tree = CreateModel(*model_desc_tree);
		model_tree->GetTransform()->SetScale(5.0f);
		model_tree->GetTransform()->AddTranslationY(2.5f);
		
		//---------------------------------------------------------------------
		// Lights
		//---------------------------------------------------------------------
		auto omni_light = Create< OmniLightNode >();
		omni_light->GetTransform()->SetTranslationY(7.0f);
		omni_light->GetLight()->SetRange(20.0f);
		omni_light->GetLight()->SetIntensity(20.0f);
		omni_light->GetLight()->EnableShadows();

		auto light = Create< SpotLightNode >();
		light->GetLight()->SetRange(15.0f);
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
		Create< script::SwitchSceneScript< ForrestScene > >();
		Create< script::RotationScript >(model_tree->GetTransform());
		Create< script::FPSInputControllerScript >(camera->GetTransform());
		Create< script::RenderModeScript >(camera->GetSettings());
		Create< script::StatsScript >(text->GetSprite());
	}
}