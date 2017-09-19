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
		auto scene_fog = GetSceneFog();
		scene_fog->SetDistanceFalloff(0.0f, 17.0f);

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
		auto model_desc_sphere =
			ResourceManager::Get()->GetOrCreateModelDescriptor(L"assets/models/sphere/sphere.mdl", mesh_desc);
		auto model_desc_tree = 
			ResourceManager::Get()->GetOrCreateModelDescriptor(L"assets/models/tree/tree1a_lod1.mdl", mesh_desc);
		
		//---------------------------------------------------------------------
		// Models
		//---------------------------------------------------------------------
		auto model_sponza = CreateModel(*model_desc_sponza);
		model_sponza->GetTransform()->SetScale(10.0f);
		auto model_sphere = CreateModel(*model_desc_sphere);
		model_sphere->GetTransform()->SetTranslationY(2.0f);
		model_sphere->GetTransform()->SetScale(0.25f);
		auto model_tree = CreateModel(*model_desc_tree);
		model_tree->GetTransform()->AddTranslationY(0.5f);
		
		//model_sphere->GetModel()->GetMaterial()->SetDiffuseReflectivityTexture(CreateReferenceTexture());

		//---------------------------------------------------------------------
		// Lights
		//---------------------------------------------------------------------
		auto omni_light = Create< OmniLightNode >("light");
		omni_light->GetTransform()->SetTranslationY(2.0f);
		omni_light->GetLight()->SetDistanceFalloff(0.0f, 3.0f);
		omni_light->GetLight()->EnableShadows();

		//auto light0 = Create< SpotLightNode >("light");
		//light0->GetTransform()->SetTranslationY(2.0f);
		//light0->GetLight()->SetDistanceFalloff(0.0f, 4.0f);
		//light0->GetLight()->SetUmbraAngle(XM_PI / 6.0f);
		//light0->GetLight()->EnableShadows();

		//auto light1 = Create< SpotLightNode >("light");
		//light1->GetTransform()->SetTranslationY(2.0f);
		//light1->GetTransform()->SetRotationY(XM_PI);
		//light1->GetLight()->SetDistanceFalloff(0.0f, 4.0f);
		//light1->GetLight()->SetUmbraAngle(XM_PI / 6.0f);
		//light1->GetLight()->EnableShadows();

		//auto spot_light = Create< SpotLightNode >("light");
		//spot_light->GetLight()->SetDistanceFalloff(0.0f, 5.0f);
		//spot_light->GetLight()->SetAngularCutoff(1.0f, 0.5f);
		//camera->AddChildNode(spot_light);

		//---------------------------------------------------------------------
		// Texture
		//---------------------------------------------------------------------
		auto texture_logo = CreateMAGETexture();
		//---------------------------------------------------------------------
		// Image
		//---------------------------------------------------------------------
		auto logo = Create< SpriteImageNode >("logo", texture_logo);
		logo->GetSpriteTransform()->SetScale(0.25f, 0.25f);
		logo->GetSpriteTransform()->SetNormalizedTranslation(0.90f, 0.88f);

		//---------------------------------------------------------------------
		// Font
		//---------------------------------------------------------------------
		auto font = 
			ResourceManager::Get()->GetOrCreateSpriteFont(L"assets/fonts/consolas.spritefont");

		//---------------------------------------------------------------------
		// Text
		//---------------------------------------------------------------------
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