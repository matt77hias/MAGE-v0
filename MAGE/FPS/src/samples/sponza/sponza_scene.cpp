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

#include "character_motor_script.hpp"
#include "mouse_look_script.hpp"
#include "rotation_script.hpp"
#include "editor_script.hpp"
#include "stats_script.hpp"
#include "switch_scene_script.hpp"

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
		// Resources
		//---------------------------------------------------------------------
		ResourceManager * const factory = ResourceManager::Get();
		MeshDescriptor< VertexPositionNormalTexture > mesh_desc(true, true);
		
		auto sponza_model_desc = factory->GetOrCreate< ModelDescriptor >(
			L"assets/models/sponza/sponza.mdl",    mesh_desc);
		auto tree_model_desc_tree = factory->GetOrCreate< ModelDescriptor >(
			L"assets/models/tree/tree1a_lod0.mdl", mesh_desc);
		auto sky_texture = factory->GetOrCreate< Texture >(
			L"assets/textures/sky/sky.dds");

		//---------------------------------------------------------------------
		// Cameras
		//---------------------------------------------------------------------
		auto camera = Create< PerspectiveCamera >();
		
		// Camera: Lens
		// camera->GetLens().SetLensRadius(0.01f);
		// camera->GetLens().SetFocalLength(3.0f);
		// camera->GetLens().SetMaximumCoCRadius(2.0f);
		// Camera: Viewport
		// camera->GetViewport().SetNormalizedWidth(0.5f);
		// Camera: Fog
		camera->GetSettings().GetFog().SetDensity(0.001f);
		// Camera: Sky
		camera->GetSettings().GetSky().SetTexture(sky_texture);
		
		auto camera_node = Create< Node >("Player");
		camera_node->Add(camera);
		camera_node->GetTransform().SetTranslationY(2.0f);

		//---------------------------------------------------------------------
		// Models
		//---------------------------------------------------------------------
		auto sponza_node = Import(*sponza_model_desc);
		sponza_node->GetTransform().SetScale(10.0f);
		sponza_node->GetTransform().SetTranslationY(2.1f);
		
		auto tree_node = Import(*tree_model_desc_tree);
		tree_node->GetTransform().AddTranslationY(1.0f);
		
		//---------------------------------------------------------------------
		// Lights
		//---------------------------------------------------------------------
		auto omni_light = Create< OmniLight >();
		omni_light->SetRange(5.0f);
		omni_light->SetIntensity(4.0f);
		omni_light->EnableShadows();
		
		auto omni_light_node = Create< Node >("Omni Light");
		omni_light_node->Add(omni_light);
		omni_light_node->GetTransform().SetTranslationY(2.0f);
		
		auto spot_light = Create< SpotLight >();
		spot_light->SetRange(5.0f);
		spot_light->SetAngularCutoff(1.0f, 0.5f);

		camera_node->Add(spot_light);

		//---------------------------------------------------------------------
		// Sprites
		//---------------------------------------------------------------------
		auto logo = Create< SpriteImage >();
		logo->SetBaseColorTexture(CreateMAGETexture());
		logo->GetSpriteTransform().SetScale(0.25f, 0.25f);
		logo->GetSpriteTransform().SetTranslation(NormalizedToAbsolutePixel(0.90f, 0.88f));

		camera_node->Add(logo);

		auto text = Create< SpriteText >();

		camera_node->Add(text);

		//---------------------------------------------------------------------
		// Scripts
		//---------------------------------------------------------------------
		Create< script::SwitchSceneScript< SibenikScene > >();
		Create< script::EditorScript >();
		
		camera_node->Add(Create< script::StatsScript >());
		camera_node->Add(Create< script::MouseLookScript >());
		camera_node->Add(Create< script::CharacterMotorScript >());
		tree_node->Add(Create< script::RotationScript >());
	}
}