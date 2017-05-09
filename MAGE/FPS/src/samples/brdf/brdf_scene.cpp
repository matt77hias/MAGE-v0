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
#include "script\fps_input_controller_script.hpp"

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
		SharedPtr< PerspectiveCameraNode > camera = CreatePerspectiveCameraNode();
		camera->GetTransform()->SetTranslation(0.0f, 20.0f, -15.0f);
		SetCamera(camera);

		//---------------------------------------------------------------------
		// ModelDescriptors
		//---------------------------------------------------------------------
		MeshDescriptor< VertexPositionNormalTexture > mesh_desc(true, true);
		SharedPtr< ModelDescriptor > model_desc_cone     = CreateModelDescriptor(L"assets/models/cone/cone.mdl",         mesh_desc);
		SharedPtr< ModelDescriptor > model_desc_cube     = CreateModelDescriptor(L"assets/models/cube/cube.mdl",         mesh_desc);
		SharedPtr< ModelDescriptor > model_desc_cylinder = CreateModelDescriptor(L"assets/models/cylinder/cylinder.mdl", mesh_desc);
		SharedPtr< ModelDescriptor > model_desc_plane    = CreateModelDescriptor(L"assets/models/plane/plane.mdl",       mesh_desc);
		SharedPtr< ModelDescriptor > model_desc_sphere   = CreateModelDescriptor(L"assets/models/sphere/sphere.mdl",     mesh_desc);
		SharedPtr< ModelDescriptor > model_desc_teapot   = CreateModelDescriptor(L"assets/models/teapot/teapot.mdl",     mesh_desc);
		SharedPtr< ModelDescriptor > model_desc_torus    = CreateModelDescriptor(L"assets/models/torus/torus.mdl",       mesh_desc);
		//---------------------------------------------------------------------
		// Models
		//---------------------------------------------------------------------
		SharedPtr< ModelNode > model_cone     = CreateModelNode(*model_desc_cone);
		SharedPtr< ModelNode > model_cube     = CreateModelNode(*model_desc_cube);
		SharedPtr< ModelNode > model_cylinder = CreateModelNode(*model_desc_cylinder);
		SharedPtr< ModelNode > model_plane    = CreateModelNode(*model_desc_plane);
		SharedPtr< ModelNode > model_sphere   = CreateModelNode(*model_desc_sphere);
		SharedPtr< ModelNode > model_teapot   = CreateModelNode(*model_desc_teapot);
		SharedPtr< ModelNode > model_torus    = CreateModelNode(*model_desc_torus);

		model_cone->GetTransform()->SetScale(10.0f);
		model_cube->GetTransform()->SetScale(10.0f);
		model_cylinder->GetTransform()->SetScale(10.0f);
		model_plane->GetTransform()->SetScale(20.0f);
		model_sphere->GetTransform()->SetScale(10.0f);
		model_teapot->GetTransform()->SetScale(30.0f);
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
		SharedPtr< Texture > texture_logo = CreateTexture(L"assets/sprites/mage.dds");
		//---------------------------------------------------------------------
		// Image
		//---------------------------------------------------------------------
		SharedPtr< SpriteImage > logo(new SpriteImage("logo", texture_logo));
		logo->GetTransform()->SetScale(0.25f, 0.25f);
		logo->GetTransform()->SetNormalizedTranslation(0.90f, 0.88f);
		AddSprite(logo);

		//---------------------------------------------------------------------
		// Font
		//---------------------------------------------------------------------
		SharedPtr< SpriteFont > font = CreateFont(L"assets/fonts/consolas.spritefont", SpriteFontDescriptor());
		//---------------------------------------------------------------------
		// Text
		//---------------------------------------------------------------------
		SharedPtr< SpriteText > stats_text(new NormalSpriteText("stats_text", font));
		AddSprite(stats_text);
		SharedPtr< SpriteText > brdf_text(new NormalSpriteText("brdf_text", font));
		AddSprite(brdf_text);

		//---------------------------------------------------------------------
		// Scripts
		//---------------------------------------------------------------------
		SharedPtr< BehaviorScript > stats_script(new StatsScript(stats_text));
		AddScript(stats_script);
		SharedPtr< BehaviorScript > controller_script(new FPSInputControllerScript(camera->GetTransform()));
		AddScript(controller_script);


		vector< ModelNode * > models;
		models.push_back(model_cone.get());
		models.push_back(model_cube.get());
		models.push_back(model_cylinder.get());
		models.push_back(model_plane.get());
		models.push_back(model_sphere.get());
		models.push_back(model_teapot.get());
		models.push_back(model_torus.get());
		SharedPtr< BehaviorScript > brdf_script(new BRDFScript(brdf_text.get(), models));
		AddScript(brdf_script);
	}
}