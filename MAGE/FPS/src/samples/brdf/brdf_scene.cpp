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
		// Camera
		//---------------------------------------------------------------------
		auto camera = Create< PerspectiveCameraNode >("camera");
		camera->GetTransform()->SetTranslation(-0.66f, 20.0f, -15.23f);
		camera->GetTransform()->SetRotationX(0.54f);

		//---------------------------------------------------------------------
		// ModelDescriptors
		//---------------------------------------------------------------------
		MeshDescriptor< VertexPositionNormalTexture > mesh_desc(true, true);
		auto model_desc_teapot
			= ResourceManager::Get()->GetOrCreateModelDescriptor(L"assets/models/teapot/teapot.mdl",     mesh_desc);
		auto model_desc_skull
			= ResourceManager::Get()->GetOrCreateModelDescriptor(L"assets/models/skull/skull.mdl",       mesh_desc);
		auto model_desc_cone
			= ResourceManager::Get()->GetOrCreateModelDescriptor(L"assets/models/cone/cone.mdl",         mesh_desc);
		auto model_desc_cube
			= ResourceManager::Get()->GetOrCreateModelDescriptor(L"assets/models/cube/cube.mdl",         mesh_desc);
		auto model_desc_cylinder
			= ResourceManager::Get()->GetOrCreateModelDescriptor(L"assets/models/cylinder/cylinder.mdl", mesh_desc);
		auto model_desc_plane
			= ResourceManager::Get()->GetOrCreateModelDescriptor(L"assets/models/plane/plane.mdl",       mesh_desc);
		auto model_desc_sphere
			= ResourceManager::Get()->GetOrCreateModelDescriptor(L"assets/models/sphere/sphere.mdl",     mesh_desc);
		auto model_desc_torus
			= ResourceManager::Get()->GetOrCreateModelDescriptor(L"assets/models/torus/torus.mdl",       mesh_desc);
		//---------------------------------------------------------------------
		// Models
		//---------------------------------------------------------------------
		auto model_teapot   = CreateModel(*model_desc_teapot);
		auto model_skull    = CreateModel(*model_desc_skull);
		auto model_cone     = CreateModel(*model_desc_cone);
		auto model_cube     = CreateModel(*model_desc_cube);
		auto model_cylinder = CreateModel(*model_desc_cylinder);
		auto model_plane    = CreateModel(*model_desc_plane);
		auto model_sphere   = CreateModel(*model_desc_sphere);
		auto model_torus    = CreateModel(*model_desc_torus);

		model_teapot->GetTransform()->SetScale(30.0f);
		model_skull->GetTransform()->SetScale(20.0f);
		model_skull->GetTransform()->SetRotationY(XM_PI);
		model_cone->GetTransform()->SetScale(10.0f);
		model_cube->GetTransform()->SetScale(10.0f);
		model_cylinder->GetTransform()->SetScale(10.0f);
		model_plane->GetTransform()->SetScale(20.0f);
		model_sphere->GetTransform()->SetScale(10.0f);
		model_torus->GetTransform()->SetScale(10.0f);
		
		//---------------------------------------------------------------------
		// Lights
		//---------------------------------------------------------------------
		auto omni_light = Create< OmniLightNode >("light");
		omni_light->GetTransform()->SetTranslation(0.0f, 20.0f, -15.0f);
		omni_light->GetLight()->SetRange(50.0f);
		omni_light->GetLight()->SetIntensity(50.0f);

		//---------------------------------------------------------------------
		// Image
		//---------------------------------------------------------------------
		auto logo = Create< SpriteImageNode >("logo");
		logo->GetSprite()->SetBaseColorTexture(CreateMAGETexture());
		logo->GetSpriteTransform()->SetScale(0.25f, 0.25f);
		logo->GetSpriteTransform()->SetNormalizedTranslation(0.90f, 0.88f);

		//---------------------------------------------------------------------
		// Text
		//---------------------------------------------------------------------
		auto stats = Create< NormalSpriteTextNode >("stats");
		auto brdf  = Create< NormalSpriteTextNode >("brdf");

		//---------------------------------------------------------------------
		// Scripts
		//---------------------------------------------------------------------
		AddScript(MakeShared< script::SwitchSceneScript< SponzaScene > >());
		AddScript(MakeShared< script::StatsScript >(stats->GetSprite()));

		vector< ModelNode * > models;
		models.push_back(model_teapot.get());
		models.push_back(model_skull.get());
		models.push_back(model_cone.get());
		models.push_back(model_cube.get());
		models.push_back(model_cylinder.get());
		models.push_back(model_plane.get());
		models.push_back(model_sphere.get());
		models.push_back(model_torus.get());
		AddScript(MakeShared< script::BRDFScript >(
			camera->GetSettings(), brdf->GetSprite(), models));
	}
}