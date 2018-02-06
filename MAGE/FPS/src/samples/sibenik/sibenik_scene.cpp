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

	SibenikScene::SibenikScene()
		: Scene("sibenik_scene") {}

	SibenikScene::SibenikScene(SibenikScene &&scene) = default;

	SibenikScene::~SibenikScene() = default;

	void SibenikScene::Load() {

		//---------------------------------------------------------------------
		// Resources
		//---------------------------------------------------------------------
		ResourceManager * const factory = ResourceManager::Get();
		MeshDescriptor< VertexPositionNormalTexture > mesh_desc(true, true);

		auto sibenik_model_desc = factory->GetOrCreate< ModelDescriptor >(
			L"assets/models/sibenik/sibenik.mdl", mesh_desc);
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
		auto sibenik_node = Import(*sibenik_model_desc);
		sibenik_node->GetTransform().SetScale(30.0f);
		sibenik_node->GetTransform().SetTranslationY(12.1f);

		auto tree_node = Import(*tree_model_desc_tree);
		tree_node->GetTransform().SetScale(5.0f);
		tree_node->GetTransform().AddTranslationY(2.5f);
		
		//---------------------------------------------------------------------
		// Lights
		//---------------------------------------------------------------------
		auto omni_light = Create< OmniLight >();
		omni_light->SetRange(20.0f);
		omni_light->SetIntensity(20.0f);
		omni_light->EnableShadows();

		auto omni_light_node = Create< Node >("Omni Light");
		omni_light_node->Add(omni_light);
		omni_light_node->GetTransform().SetTranslationY(7.0f);

		auto spot_light = Create< SpotLight >();
		spot_light->SetRange(15.0f);
		spot_light->SetAngularCutoff(1.0f, 0.5f);

		camera_node->Add(spot_light);

		//---------------------------------------------------------------------
		// Sprites
		//---------------------------------------------------------------------
		auto logo = Create< SpriteImage >();
		logo->SetBaseColorTexture(CreateMAGETexture());
		logo->GetSpriteTransform().SetScale(0.25f, 0.25f);
		logo->GetSpriteTransform().SetTranslation(NormalizedToAbsolutePixel(0.90f, 0.88f));

		auto text = Create< SpriteText >();

		camera_node->Add(text);

		//---------------------------------------------------------------------
		// Scripts
		//---------------------------------------------------------------------
		Create< script::SwitchSceneScript< ForrestScene > >();
		Create< script::EditorScript >();

		camera_node->Add(Create< script::StatsScript >());
		camera_node->Add(Create< script::MouseLookScript >());
		camera_node->Add(Create< script::CharacterMotorScript >());
		tree_node->Add(Create< script::RotationScript >());
	}
}