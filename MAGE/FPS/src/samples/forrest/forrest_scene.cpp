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
		auto model_desc_plane =
			ResourceManager::Get()->GetOrCreateModelDescriptor(L"assets/models/plane/plane.mdl", mesh_desc);
		auto model_desc_tree1 =
			ResourceManager::Get()->GetOrCreateModelDescriptor(L"assets/models/tree/tree1a_lod0.mdl", mesh_desc);
		auto model_desc_tree2 =
			ResourceManager::Get()->GetOrCreateModelDescriptor(L"assets/models/tree/tree1b_lod0.mdl", mesh_desc);
		auto model_desc_tree3 =
			ResourceManager::Get()->GetOrCreateModelDescriptor(L"assets/models/tree/tree2a_lod0.mdl", mesh_desc);
		auto model_desc_tree4 =
			ResourceManager::Get()->GetOrCreateModelDescriptor(L"assets/models/tree/tree2b_lod0.mdl", mesh_desc);
		auto model_desc_tree5 =
			ResourceManager::Get()->GetOrCreateModelDescriptor(L"assets/models/tree/tree3a_lod0.mdl", mesh_desc);
		auto model_desc_tree6 =
			ResourceManager::Get()->GetOrCreateModelDescriptor(L"assets/models/tree/tree3b_lod0.mdl", mesh_desc);
		auto model_desc_tree7 =
			ResourceManager::Get()->GetOrCreateModelDescriptor(L"assets/models/tree/tree4a_lod0.mdl", mesh_desc);
		auto model_desc_tree8 =
			ResourceManager::Get()->GetOrCreateModelDescriptor(L"assets/models/tree/tree4b_lod0.mdl", mesh_desc);

		//---------------------------------------------------------------------
		// Models
		//---------------------------------------------------------------------
		auto model_plane = CreateModel(*model_desc_plane);
		model_plane->GetTransform()->SetScale(5.0f);

		//auto model_plane2 = CreateModel(*model_desc_plane);
		//model_plane2->GetTransform()->SetScale(5.0f);
		//model_plane2->GetTransform()->SetRotationZ(XM_PIDIV4);

		//auto model_plane3 = CreateModel(*model_desc_plane);
		//model_plane3->GetTransform()->SetScale(5.0f);
		//model_plane3->GetTransform()->SetTranslationY(0.5f);

		auto model_tree1 = CreateModel(*model_desc_tree1);
		model_tree1->GetTransform()->SetScale(2.0f);
		model_tree1->GetTransform()->SetTranslation(0.5f, 0.0f, 0.0f);
		auto model_tree2 = CreateModel(*model_desc_tree2);
		model_tree2->GetTransform()->SetScale(2.0f);
		model_tree2->GetTransform()->SetTranslation(-0.5f, 0.0f, 0.0f);
		auto model_tree3 = CreateModel(*model_desc_tree3);
		model_tree3->GetTransform()->SetScale(2.0f);
		model_tree3->GetTransform()->SetTranslation(1.0f, 0.0f, 0.0f);
		auto model_tree4 = CreateModel(*model_desc_tree4);
		model_tree4->GetTransform()->SetScale(2.0f);
		model_tree4->GetTransform()->SetTranslation(-1.0f, 0.0f, 0.0f);
		auto model_tree5 = CreateModel(*model_desc_tree5);
		model_tree5->GetTransform()->SetScale(2.0f);
		model_tree5->GetTransform()->SetTranslation(0.5f, 0.0f, 0.5f);
		auto model_tree6 = CreateModel(*model_desc_tree6);
		model_tree6->GetTransform()->SetScale(2.0f);
		model_tree6->GetTransform()->SetTranslation(-0.5f, 0.0f, 0.5f);
		auto model_tree7 = CreateModel(*model_desc_tree7);
		model_tree7->GetTransform()->SetScale(2.0f);
		model_tree7->GetTransform()->SetTranslation(1.0f, 0.0f, 0.5f);
		auto model_tree8 = CreateModel(*model_desc_tree8);
		model_tree8->GetTransform()->SetScale(2.0f);
		model_tree8->GetTransform()->SetTranslation(-1.0f, 0.0f, 0.5f);

		//---------------------------------------------------------------------
		// Lights
		//---------------------------------------------------------------------
		//auto omni_light = Create< OmniLightNode >("light");
		//omni_light->GetTransform()->SetTranslationY(3.0f);
		//omni_light->GetLight()->SetDistanceFalloff(3.0f, 4.0f);
		//omni_light->GetLight()->EnableShadows();

		auto spot_light = Create< SpotLightNode >("light");
		spot_light->GetTransform()->SetTranslationY(4.0f);
		spot_light->GetTransform()->SetRotationX(XM_PIDIV2);
		spot_light->GetLight()->SetDistanceFalloff(0.0f, 5.0f);
		spot_light->GetLight()->SetAngularCutoff(1.0f, sqrt(2.0f)/2.0f);
		spot_light->GetLight()->SetIntensity(RGBSpectrum(4.0f));
		spot_light->GetLight()->EnableShadows();

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
		// Font
		//---------------------------------------------------------------------
		auto font =
			ResourceManager::Get()->GetOrCreateSpriteFont(L"assets/fonts/consolas.spritefont");
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