//-----------------------------------------------------------------------------
// Game Includes
//-----------------------------------------------------------------------------
#pragma region

#include "samples\forrest\forrest_scene.hpp"
#include "samples\brdf\brdf_scene.hpp"

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

	ForrestScene::ForrestScene()
		: Scene("forrest_scene") {}

	ForrestScene::ForrestScene(ForrestScene &&scene) = default;

	ForrestScene::~ForrestScene() = default;

	void ForrestScene::Load() {

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
		auto model_desc_plane =
			ResourceManager::Get()->GetOrCreateModelDescriptor(L"assets/models/plane/plane.mdl", mesh_desc);
		auto model_desc_tree1 =
			ResourceManager::Get()->GetOrCreateModelDescriptor(L"assets/models/tree/tree1a_lod1.mdl", mesh_desc);
		auto model_desc_tree2 =
			ResourceManager::Get()->GetOrCreateModelDescriptor(L"assets/models/tree/tree1b_lod1.mdl", mesh_desc);
		auto model_desc_tree3 =
			ResourceManager::Get()->GetOrCreateModelDescriptor(L"assets/models/tree/tree2a_lod1.mdl", mesh_desc);
		auto model_desc_tree4 =
			ResourceManager::Get()->GetOrCreateModelDescriptor(L"assets/models/tree/tree2b_lod1.mdl", mesh_desc);
		auto model_desc_tree5 =
			ResourceManager::Get()->GetOrCreateModelDescriptor(L"assets/models/tree/tree3a_lod1.mdl", mesh_desc);
		auto model_desc_tree6 =
			ResourceManager::Get()->GetOrCreateModelDescriptor(L"assets/models/tree/tree3b_lod1.mdl", mesh_desc);
		auto model_desc_tree7 =
			ResourceManager::Get()->GetOrCreateModelDescriptor(L"assets/models/tree/tree4a_lod1.mdl", mesh_desc);
		auto model_desc_tree8 =
			ResourceManager::Get()->GetOrCreateModelDescriptor(L"assets/models/tree/tree4b_lod1.mdl", mesh_desc);

		//---------------------------------------------------------------------
		// Models
		//---------------------------------------------------------------------
		auto model_plane = CreateModel(*model_desc_plane);
		model_plane->GetTransform()->SetScale(5.0f);
		auto model_tree1 = CreateModel(*model_desc_tree1);
		model_tree1->GetTransform()->SetScale(2.0f);

		//---------------------------------------------------------------------
		// Lights
		//---------------------------------------------------------------------
		auto omni_light = Create< OmniLightNode >("light");
		omni_light->GetTransform()->SetTranslationY(3.0f);
		omni_light->GetLight()->SetDistanceFalloff(3.0f, 3.0f);
		omni_light->GetLight()->EnableShadows();

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
		AddScript(MakeShared< SwitchSceneScript< BRDFScene > >());
		AddScript(MakeShared< RotationScript >(model_tree1->GetTransform()));
		AddScript(MakeShared< FPSInputControllerScript >(camera->GetTransform()));
		AddScript(MakeShared< StatsScript >(text->GetSprite()));
		AddScript(MakeShared< RenderModeScript >(camera->GetSettings()));
	}
}