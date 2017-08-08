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

#include "sprite\sprite_image.hpp"
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
		SceneFog *scene_fog = GetSceneFog();
		scene_fog->SetDistanceFalloff(1000.0f, 1000.0f);

		//---------------------------------------------------------------------
		// Camera
		//---------------------------------------------------------------------
		SharedPtr< PerspectiveCameraNode > camera = CreatePerspectiveCameraNode();
		camera->GetTransform()->SetTranslation(-0.66f, 20.0f, -15.23f);
		camera->GetTransform()->SetRotationX(0.54f);
		SetCamera(camera);

		//---------------------------------------------------------------------
		// ModelDescriptors
		//---------------------------------------------------------------------
		MeshDescriptor< VertexPositionNormalTexture > mesh_desc(true, true);
		SharedPtr< ModelDescriptor > model_desc_teapot   = GetOrCreateModelDescriptor(L"assets/models/teapot/teapot.mdl",     mesh_desc);
		SharedPtr< ModelDescriptor > model_desc_cone     = GetOrCreateModelDescriptor(L"assets/models/cone/cone.mdl",         mesh_desc);
		SharedPtr< ModelDescriptor > model_desc_cube     = GetOrCreateModelDescriptor(L"assets/models/cube/cube.mdl",         mesh_desc);
		SharedPtr< ModelDescriptor > model_desc_cylinder = GetOrCreateModelDescriptor(L"assets/models/cylinder/cylinder.mdl", mesh_desc);
		SharedPtr< ModelDescriptor > model_desc_plane    = GetOrCreateModelDescriptor(L"assets/models/plane/plane.mdl",       mesh_desc);
		SharedPtr< ModelDescriptor > model_desc_sphere   = GetOrCreateModelDescriptor(L"assets/models/sphere/sphere.mdl",     mesh_desc);
		SharedPtr< ModelDescriptor > model_desc_torus    = GetOrCreateModelDescriptor(L"assets/models/torus/torus.mdl",       mesh_desc);
		//---------------------------------------------------------------------
		// Models
		//---------------------------------------------------------------------
		SharedPtr< ModelNode > model_teapot   = CreateModelNode(*model_desc_teapot);
		SharedPtr< ModelNode > model_cone     = CreateModelNode(*model_desc_cone);
		SharedPtr< ModelNode > model_cube     = CreateModelNode(*model_desc_cube);
		SharedPtr< ModelNode > model_cylinder = CreateModelNode(*model_desc_cylinder);
		SharedPtr< ModelNode > model_plane    = CreateModelNode(*model_desc_plane);
		SharedPtr< ModelNode > model_sphere   = CreateModelNode(*model_desc_sphere);
		SharedPtr< ModelNode > model_torus    = CreateModelNode(*model_desc_torus);

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
		SharedPtr< OmniLightNode > omni_light = CreateOmniLightNode();
		omni_light->GetTransform()->SetTranslation(0.0f, 20.0f, -15.0f);
		omni_light->GetLight()->SetDistanceFalloff(0.0f, 50.0f);

		//---------------------------------------------------------------------
		// Texture
		//---------------------------------------------------------------------
		SharedPtr< Texture > texture_logo = GetOrCreateTexture(L"assets/sprites/mage.dds");
		//---------------------------------------------------------------------
		// Image
		//---------------------------------------------------------------------
		SharedPtr< SpriteImage > logo = std::make_shared< SpriteImage >("logo", texture_logo);
		logo->GetTransform()->SetScale(0.25f, 0.25f);
		logo->GetTransform()->SetNormalizedTranslation(0.90f, 0.88f);
		AddSprite(logo);

		//---------------------------------------------------------------------
		// Font
		//---------------------------------------------------------------------
		SharedPtr< SpriteFont > font = GetOrCreateSpriteFont(L"assets/fonts/consolas.spritefont", SpriteFontDescriptor());
		//---------------------------------------------------------------------
		// Text
		//---------------------------------------------------------------------
		SharedPtr< SpriteText > stats_text = std::make_shared< NormalSpriteText >("stats_text", font);
		AddSprite(stats_text);
		SharedPtr< SpriteText > brdf_text  = std::make_shared< NormalSpriteText >("brdf_text", font);
		AddSprite(brdf_text);

		//---------------------------------------------------------------------
		// Scripts
		//---------------------------------------------------------------------
		AddScript(std::make_shared< StatsScript >(stats_text));

		vector< ModelNode * > models;
		models.push_back(model_teapot.get());
		models.push_back(model_cone.get());
		models.push_back(model_cube.get());
		models.push_back(model_cylinder.get());
		models.push_back(model_plane.get());
		models.push_back(model_sphere.get());
		models.push_back(model_torus.get());
		AddScript(std::make_shared< BRDFScript >(brdf_text.get(), models));
	}
}