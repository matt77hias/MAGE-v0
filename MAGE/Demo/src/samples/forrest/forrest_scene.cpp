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

	ForrestScene::ForrestScene()
		: Scene("forrest_scene") {}

	ForrestScene::ForrestScene(ForrestScene&& scene) = default;

	ForrestScene::~ForrestScene() = default;

	void ForrestScene::Load([[maybe_unused]] Engine& engine) {
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

		const auto plane_model_desc 
			= rendering_factory.GetOrCreate< ModelDescriptor >(
				L"assets/models/plane/plane.obj", mesh_desc);
		const auto tree1_model_desc 
			= rendering_factory.GetOrCreate< ModelDescriptor >(
				L"assets/models/tree/tree1a_lod0.mdl", mesh_desc);
		const auto tree2_model_desc 
			= rendering_factory.GetOrCreate< ModelDescriptor >(
				L"assets/models/tree/tree1b_lod0.mdl", mesh_desc);
		const auto tree3_model_desc 
			= rendering_factory.GetOrCreate< ModelDescriptor >(
				L"assets/models/tree/tree2a_lod0.mdl", mesh_desc);
		const auto tree4_model_desc 
			= rendering_factory.GetOrCreate< ModelDescriptor >(
				L"assets/models/tree/tree2b_lod0.mdl", mesh_desc);
		const auto tree5_model_desc 
			= rendering_factory.GetOrCreate< ModelDescriptor >(
				L"assets/models/tree/tree3a_lod0.mdl", mesh_desc);
		const auto tree6_model_desc 
			= rendering_factory.GetOrCreate< ModelDescriptor >(
				L"assets/models/tree/tree3b_lod0.mdl", mesh_desc);
		const auto tree7_model_desc 
			= rendering_factory.GetOrCreate< ModelDescriptor >(
				L"assets/models/tree/tree4a_lod0.mdl", mesh_desc);
		const auto tree8_model_desc 
			= rendering_factory.GetOrCreate< ModelDescriptor >(
				L"assets/models/tree/tree4b_lod0.mdl", mesh_desc);
		const auto windmill_model_desc 
			= rendering_factory.GetOrCreate< ModelDescriptor >(
				L"assets/models/windmill/windmill.mdl", mesh_desc);
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
		const auto plane_node = Import(engine, *plane_model_desc);
		plane_node->GetTransform().SetScale(30.0f);
		
		const auto tree1_node = Import(engine, *tree1_model_desc);
		tree1_node->GetTransform().SetScale(5.0f);
		tree1_node->GetTransform().SetTranslation(-5.0f, 2.5f, -10.0f);
		const auto tree2_node = Import(engine, *tree2_model_desc);
		tree2_node->GetTransform().SetScale(5.0f);
		tree2_node->GetTransform().SetTranslation(-5.0f, 2.5f, -5.0f);
		const auto tree3_node = Import(engine, *tree3_model_desc);
		tree3_node->GetTransform().SetScale(5.0f);
		tree3_node->GetTransform().SetTranslation(-5.0f, 2.5f, 5.0f);
		const auto tree4_node = Import(engine, *tree4_model_desc);
		tree4_node->GetTransform().SetScale(5.0f);
		tree4_node->GetTransform().SetTranslation(-5.0f, 2.5f, 10.0f);
		const auto tree5_node = Import(engine, *tree5_model_desc);
		tree5_node->GetTransform().SetScale(5.0f);
		tree5_node->GetTransform().SetTranslation(-10.0f, 2.5f, -10.0f);
		const auto tree6_node = Import(engine, *tree6_model_desc);
		tree6_node->GetTransform().SetScale(5.0f);
		tree6_node->GetTransform().SetTranslation(-10.0f, 2.5f, -5.0f);
		const auto tree7_node = Import(engine, *tree7_model_desc);
		tree7_node->GetTransform().SetScale(5.0f);
		tree7_node->GetTransform().SetTranslation(-10.0f, 2.5f, 5.0f);
		const auto tree8_node = Import(engine, *tree8_model_desc);
		tree8_node->GetTransform().SetScale(5.0f);
		tree8_node->GetTransform().SetTranslation(-10.0f, 2.5f, 10.0f);
		
		std::vector< ProxyPtr< Node > >windmill_nodes;
		const auto windmill_node = Import(engine, *windmill_model_desc, 
										  windmill_nodes);
		windmill_node->GetTransform().SetScale(10.0f);
		windmill_node->GetTransform().SetTranslationY(4.25f);

		//---------------------------------------------------------------------
		// Lights
		//---------------------------------------------------------------------
		const auto light = rendering_world.Create< SpotLight >();
		light->SetRange(20.0f);
		light->SetAngularCutoff(1.0f, sqrt(2.0f) / 2.0f);
		light->SetIntensity(40.0f);
		light->EnableShadows();

		const auto light_node = Create< Node >("Spotlight");
		light_node->Add(light);
		light_node->GetTransform().SetTranslationY(15.0f);
		light_node->GetTransform().SetRotationX(XM_PIDIV2);

		const auto spot_light = rendering_world.Create< SpotLight >();
		spot_light->SetRange(5.0f);
		spot_light->SetAngularCutoff(1.0f, 0.5f);

		camera_node->Add(spot_light);

		const auto directional_light = rendering_world.Create< DirectionalLight >();
		directional_light->SetIrradiance(4.0f);
		
		const auto directional_light_node = Create< Node >("Directional Light");
		directional_light_node->Add(directional_light);
		directional_light_node->GetTransform().SetTranslation(20.0f, 20.0f, 0.0f);
		directional_light_node->GetTransform().SetRotationZ(XM_PIDIV4);
		
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
		Create< script::SwitchSceneScript< BRDFScene > >();
		Create< script::EditorScript >();

		camera_node->Add(Create< script::StatsScript >());
		camera_node->Add(Create< script::MouseLookScript >());
		camera_node->Add(Create< script::CharacterMotorScript >());

		auto script = Create< script::RotationScript >();
		script->SetRotationAxis(script::RotationScript::RotationAxis::X);
		
		windmill_nodes[0]->Add(script);
	}
}