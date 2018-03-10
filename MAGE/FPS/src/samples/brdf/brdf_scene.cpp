//-----------------------------------------------------------------------------
// Game Includes
//-----------------------------------------------------------------------------
#pragma region

#include "samples\brdf\brdf_scene.hpp"
#include "samples\sponza\sponza_scene.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "resource\texture\texture_factory.hpp"

#include "editor_script.hpp"
#include "stats_script.hpp"
#include "switch_scene_script.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Game Definitions
//-----------------------------------------------------------------------------
namespace mage {

	BRDFScene::BRDFScene()
		: Scene("brdf_scene") {}
	
	BRDFScene::BRDFScene(BRDFScene&& scene) = default;
	
	BRDFScene::~BRDFScene() = default;

	void BRDFScene::Load([[maybe_unused]] Engine& engine) {
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

		const auto teapot_model_desc 
			= rendering_factory.GetOrCreate< ModelDescriptor >(
				L"assets/models/teapot/teapot.mdl", mesh_desc);
		const auto skull_model_desc 
			= rendering_factory.GetOrCreate< ModelDescriptor >(
				L"assets/models/skull/skull.mdl", mesh_desc);
		const auto cone_model_desc 
			= rendering_factory.GetOrCreate< ModelDescriptor >(
				L"assets/models/cone/cone.mdl", mesh_desc);
		const auto cube_model_desc 
			= rendering_factory.GetOrCreate< ModelDescriptor >(
				L"assets/models/cube/cube.mdl", mesh_desc);
		const auto cylinder_model_desc 
			= rendering_factory.GetOrCreate< ModelDescriptor >(
				L"assets/models/cylinder/cylinder.mdl", mesh_desc);
		const auto plane_model_desc 
			= rendering_factory.GetOrCreate< ModelDescriptor >(
				L"assets/models/plane/plane.mdl", mesh_desc);
		const auto sphere_model_desc 
			= rendering_factory.GetOrCreate< ModelDescriptor >(
				L"assets/models/sphere/sphere.mdl", mesh_desc);
		const auto trous_model_desc 
			= rendering_factory.GetOrCreate< ModelDescriptor >(
				L"assets/models/torus/torus.mdl", mesh_desc);
		const auto sky_texture 
			= rendering_factory.GetOrCreate< Texture >(L"assets/textures/sky/sky.dds");
		const auto logo_texture = CreateMAGETexture(rendering_factory);

		//---------------------------------------------------------------------
		// Cameras
		//---------------------------------------------------------------------
		const auto camera = rendering_world.Create< PerspectiveCamera >();
		camera->GetSettings().GetSky().SetTexture(sky_texture);

		auto camera_node = Create< Node >("Player");
		camera_node->Add(camera);
		camera_node->GetTransform().SetTranslation(-0.66f, 20.0f, -15.23f);
		camera_node->GetTransform().SetRotationX(0.54f);

		//---------------------------------------------------------------------
		// Models
		//---------------------------------------------------------------------
		const auto teapot_node   = Import(engine, *teapot_model_desc);
		const auto skull_node    = Import(engine, *skull_model_desc);
		const auto cone_node     = Import(engine, *cone_model_desc);
		const auto cube_node     = Import(engine, *cube_model_desc);
		const auto cylinder_node = Import(engine, *cylinder_model_desc);
		const auto plane_node    = Import(engine, *plane_model_desc);
		const auto sphere_node   = Import(engine, *sphere_model_desc);
		const auto torus_node    = Import(engine, *trous_model_desc);

		teapot_node->GetTransform().SetScale(30.0f);
		teapot_node->GetTransform().SetTranslationY(10.0f);
		skull_node->SetState(State::Passive);
		skull_node->GetTransform().SetScale(20.0f);
		skull_node->GetTransform().SetTranslationY(10.0f);
		cone_node->SetState(State::Passive);
		cone_node->GetTransform().SetScale(10.0f);
		cone_node->GetTransform().SetTranslationY(10.0f);
		cube_node->SetState(State::Passive);
		cube_node->GetTransform().SetScale(10.0f);
		cube_node->GetTransform().SetTranslationY(10.0f);
		cylinder_node->SetState(State::Passive);
		cylinder_node->GetTransform().SetScale(10.0f);
		cylinder_node->GetTransform().SetTranslationY(10.0f);
		plane_node->SetState(State::Passive);
		plane_node->GetTransform().SetScale(20.0f);
		plane_node->GetTransform().SetTranslationY(10.0f);
		sphere_node->SetState(State::Passive);
		sphere_node->GetTransform().SetScale(10.0f);
		sphere_node->GetTransform().SetTranslationY(10.0f);
		torus_node->SetState(State::Passive);
		torus_node->GetTransform().SetScale(10.0f);
		torus_node->GetTransform().SetTranslationY(10.0f);

		//---------------------------------------------------------------------
		// Lights
		//---------------------------------------------------------------------
		const auto omni_light = rendering_world.Create< OmniLight >();
		omni_light->SetRange(50.0f);
		omni_light->SetIntensity(50.0f);

		const auto omni_light_node = Create< Node >("Omni Light");
		omni_light_node->Add(omni_light);
		omni_light_node->GetTransform().SetTranslation(0.0f, 20.0f, -15.0f);
		
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
		Create< script::SwitchSceneScript< SponzaScene > >();
		Create< script::EditorScript >();

		camera_node->Add(Create< script::StatsScript >());
	}
}