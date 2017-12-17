//-----------------------------------------------------------------------------
// Game Includes
//-----------------------------------------------------------------------------
#pragma region

#include "samples\brdf\brdf_scene.hpp"
#include "samples\brdf\brdf_script.hpp"
#include "samples\sponza\sponza_scene.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "script\stats_script.hpp"
#include "script\switch_scene_script.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Game Definitions
//-----------------------------------------------------------------------------
namespace mage {

	BRDFScene::BRDFScene()
		: Scene("brdf_scene") {}
	
	BRDFScene::BRDFScene(BRDFScene &&scene) = default;
	
	BRDFScene::~BRDFScene() = default;

	void BRDFScene::Load() {

		//---------------------------------------------------------------------
		// Resources
		//---------------------------------------------------------------------
		ResourceManager * const factory = ResourceManager::Get();
		MeshDescriptor< VertexPositionNormalTexture > mesh_desc(true, true);

		auto teapot_model_desc = factory->GetOrCreate< ModelDescriptor >(
			L"assets/models/teapot/teapot.mdl", mesh_desc);
		auto skull_model_desc = factory->GetOrCreate< ModelDescriptor >(
			L"assets/models/skull/skull.mdl", mesh_desc);
		auto cone_model_desc = factory->GetOrCreate< ModelDescriptor >(
			L"assets/models/cone/cone.mdl", mesh_desc);
		auto cube_model_desc = factory->GetOrCreate< ModelDescriptor >(
			L"assets/models/cube/cube.mdl", mesh_desc);
		auto cylinder_model_desc = factory->GetOrCreate< ModelDescriptor >(
			L"assets/models/cylinder/cylinder.mdl", mesh_desc);
		auto plane_model_desc = factory->GetOrCreate< ModelDescriptor >(
			L"assets/models/plane/plane.mdl", mesh_desc);
		auto sphere_model_desc = factory->GetOrCreate< ModelDescriptor >(
			L"assets/models/sphere/sphere.mdl", mesh_desc);
		auto trous_model_desc = factory->GetOrCreate< ModelDescriptor >(
			L"assets/models/torus/torus.mdl", mesh_desc);
		auto sky_texture = factory->GetOrCreate< Texture >(
			L"assets/textures/sky/sky.dds");

		//---------------------------------------------------------------------
		// Cameras
		//---------------------------------------------------------------------
		auto camera = Create< PerspectiveCamera >();

		// Camera: Sky
		camera->GetSettings().GetSky().SetTexture(sky_texture);

		auto camera_node = Create< Node >();
		camera_node->AddComponent(camera);
		camera_node->GetTransform().SetTranslation(-0.66f, 20.0f, -15.23f);
		camera_node->GetTransform().SetRotationX(0.54f);

		//---------------------------------------------------------------------
		// Models
		//---------------------------------------------------------------------
		auto teapot_node   = Import(*teapot_model_desc);
		auto skull_node    = Import(*skull_model_desc);
		auto cone_node     = Import(*cone_model_desc);
		auto cube_node     = Import(*cube_model_desc);
		auto cylinder_node = Import(*cylinder_model_desc);
		auto plane_node    = Import(*plane_model_desc);
		auto sphere_node   = Import(*sphere_model_desc);
		auto torus_node    = Import(*trous_model_desc);

		teapot_node->GetTransform().SetScale(30.0f);
		teapot_node->GetTransform().SetTranslationY(10.0f);
		skull_node->GetTransform().SetScale(20.0f);
		skull_node->GetTransform().SetTranslationY(10.0f);
		cone_node->GetTransform().SetScale(10.0f);
		cone_node->GetTransform().SetTranslationY(10.0f);
		cube_node->GetTransform().SetScale(10.0f);
		cube_node->GetTransform().SetTranslationY(10.0f);
		cylinder_node->GetTransform().SetScale(10.0f);
		cylinder_node->GetTransform().SetTranslationY(10.0f);
		plane_node->GetTransform().SetScale(20.0f);
		plane_node->GetTransform().SetTranslationY(10.0f);
		sphere_node->GetTransform().SetScale(10.0f);
		sphere_node->GetTransform().SetTranslationY(10.0f);
		torus_node->GetTransform().SetScale(10.0f);
		torus_node->GetTransform().SetTranslationY(10.0f);

		//---------------------------------------------------------------------
		// Lights
		//---------------------------------------------------------------------
		auto omni_light = Create< OmniLight >();
		omni_light->SetRange(50.0f);
		omni_light->SetIntensity(50.0f);

		auto omni_light_node = Create< Node >();
		omni_light_node->AddComponent(omni_light);
		omni_light_node->GetTransform().SetTranslation(0.0f, 20.0f, -15.0f);
		
		//---------------------------------------------------------------------
		// Sprites
		//---------------------------------------------------------------------
		auto logo = Create< SpriteImage >();
		logo->SetBaseColorTexture(CreateMAGETexture());
		logo->GetSpriteTransform().SetScale(0.25f, 0.25f);
		logo->GetSpriteTransform().SetNormalizedTranslation(0.90f, 0.88f);

		auto text = Create< SpriteText >();

		camera_node->AddComponent(text);

		//---------------------------------------------------------------------
		// Scripts
		//---------------------------------------------------------------------
		Create< script::SwitchSceneScript< SponzaScene > >();
		camera_node->AddComponent(Create< script::StatsScript >());
		
		std::vector< ProxyPtr< Node > > models;
		models.push_back(teapot_node);
		models.push_back(skull_node);
		models.push_back(cone_node);
		models.push_back(cube_node);
		models.push_back(cylinder_node);
		models.push_back(plane_node);
		models.push_back(sphere_node);
		models.push_back(torus_node);
		
		camera_node->AddComponent(Create< script::BRDFScript >(std::move(models)));
	}
}