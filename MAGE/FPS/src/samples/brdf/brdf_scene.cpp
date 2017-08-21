//-----------------------------------------------------------------------------
// Game Includes
//-----------------------------------------------------------------------------
#pragma region

#include "samples\brdf\brdf_scene.hpp"
#include "samples\brdf\brdf_script.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "script\stats_script.hpp"

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
		// Fog
		//---------------------------------------------------------------------
		auto scene_fog = GetSceneFog();
		scene_fog->SetDistanceFalloff(FLT_MAX, FLT_MAX);

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
		auto model_cone     = CreateModel(*model_desc_cone);
		auto model_cube     = CreateModel(*model_desc_cube);
		auto model_cylinder = CreateModel(*model_desc_cylinder);
		auto model_plane    = CreateModel(*model_desc_plane);
		auto model_sphere   = CreateModel(*model_desc_sphere);
		auto model_torus    = CreateModel(*model_desc_torus);

		model_teapot->GetTransform()->SetScale(30.0f);
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
		omni_light->GetLight()->SetDistanceFalloff(0.0f, 50.0f);

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
			ResourceManager::Get()->GetOrCreateSpriteFont(L"assets/fonts/consolas.spritefont", SpriteFontDescriptor());
		//---------------------------------------------------------------------
		// Text
		//---------------------------------------------------------------------
		auto stats = Create< NormalSpriteTextNode >("stats", font);
		auto brdf  = Create< NormalSpriteTextNode >("brdf", font);

		//---------------------------------------------------------------------
		// Scripts
		//---------------------------------------------------------------------
		AddScript(MakeShared< StatsScript >(stats->GetSprite()));

		vector< ModelNode * > models;
		models.push_back(model_teapot.get());
		models.push_back(model_cone.get());
		models.push_back(model_cube.get());
		models.push_back(model_cylinder.get());
		models.push_back(model_plane.get());
		models.push_back(model_sphere.get());
		models.push_back(model_torus.get());
		AddScript(MakeShared< BRDFScript >(brdf->GetSprite(), models));
	}
}