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

#include "resource\texture\texture_factory.hpp"

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

	SponzaScene::SponzaScene(SponzaScene&& scene) = default;

	SponzaScene::~SponzaScene() = default;

	void SponzaScene::Load([[maybe_unused]] Engine& engine) {
		using namespace rendering;
		
		const auto& rendering_manager = engine.GetRenderingManager();
		const auto& display_config    = rendering_manager.GetDisplayConfiguration();
		auto& rendering_world         = rendering_manager.GetWorld();
		auto& rendering_factory       = rendering_manager.GetResourceManager();
		const auto display_resolution = display_config.GetDisplayResolution();

		//---------------------------------------------------------------------
		// Resources
		//---------------------------------------------------------------------
		MeshDescriptor< VertexPositionNormalTexture > mesh_desc(true, true);
		
		const auto sponza_model_desc
			= rendering_factory.GetOrCreate< ModelDescriptor >(
				L"assets/models/sponza/sponza.mdl",    mesh_desc);
		const auto tree_model_desc_tree
			= rendering_factory.GetOrCreate< ModelDescriptor >(
				L"assets/models/tree/tree1a_lod0.mdl", mesh_desc);
		const auto sky_texture
			= rendering_factory.GetOrCreate< Texture >(
				L"assets/textures/sky/sky.dds");
		const auto logo_texture = CreateMAGETexture(rendering_factory);

		//---------------------------------------------------------------------
		// Cameras
		//---------------------------------------------------------------------
		const auto camera = rendering_world.Create< PerspectiveCamera >();
		camera->GetSettings().GetFog().SetDensity(0.001f);
		camera->GetSettings().GetSky().SetTexture(sky_texture);
		
		const auto camera_node = Create< Node >("Player");
		camera_node->Add(camera);
		camera_node->GetTransform().SetTranslationY(2.0f);

		//---------------------------------------------------------------------
		// Models
		//---------------------------------------------------------------------
		const auto sponza_node = Import(engine, *sponza_model_desc);
		sponza_node->GetTransform().SetScale(10.0f);
		sponza_node->GetTransform().SetTranslationY(2.1f);
		
		const auto tree_node = Import(engine, *tree_model_desc_tree);
		tree_node->GetTransform().AddTranslationY(1.0f);
		
		//---------------------------------------------------------------------
		// Lights
		//---------------------------------------------------------------------
		//const auto omni_light = rendering_world.Create< OmniLight >();
		//omni_light->SetRange(5.0f);
		//omni_light->SetIntensity(4.0f);
		//omni_light->EnableShadows();
		
		//const auto omni_light_node = Create< Node >("Omni Light");
		//omni_light_node->Add(omni_light);
		//omni_light_node->GetTransform().SetTranslationY(2.0f);

		const auto directional_light = rendering_world.Create< DirectionalLight >();
		directional_light->SetRange(5.0f);
		directional_light->SetIrradiance(4.0f);
		directional_light->EnableShadows();

		const auto directional_light_node = Create< Node >("Directional Light");
		directional_light_node->Add(directional_light);
		directional_light_node->GetTransform().SetRotationX(XM_PIDIV2);
		directional_light_node->GetTransform().SetTranslationY(2.0f);
		
		const auto spot_light = rendering_world.Create< SpotLight >();
		spot_light->SetRange(5.0f);
		spot_light->SetAngularCutoff(1.0f, 0.5f);

		camera_node->Add(spot_light);

		//---------------------------------------------------------------------
		// Sprites
		//---------------------------------------------------------------------
		const auto logo = rendering_world.Create< SpriteImage >();

		logo->SetBaseColorTexture(logo_texture);
		logo->GetSpriteTransform().SetScale(0.25f, 0.25f);
		logo->GetSpriteTransform().SetTranslation(
			NormalizedToAbsolute(F32x2(0.90f, 0.88f),
								 static_cast< F32x2 >(display_resolution)));

		camera_node->Add(logo);

		const auto text = rendering_world.Create< SpriteText >();

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