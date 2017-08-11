//-----------------------------------------------------------------------------
// Game Includes
//-----------------------------------------------------------------------------
#pragma region

#include "samples\sponza\sponza_scene.hpp"
#include "script\rotation_script.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "text\normal_sprite_text.hpp"
#include "sprite\sprite_image.hpp"
#include "script\stats_script.hpp"
#include "script\fps_input_controller_script.hpp"
#include "script\wireframe_script.hpp"

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
		// Fog
		//---------------------------------------------------------------------
		SceneFog *scene_fog = GetSceneFog();
		scene_fog->SetDistanceFalloff(0.0f, 17.0f);

		//---------------------------------------------------------------------
		// Camera
		//---------------------------------------------------------------------
		SharedPtr< PerspectiveCameraNode > camera = CreatePerspectiveCameraNode();
		camera->GetTransform()->SetTranslationY(2.0f);
		SetCamera(camera);

		//---------------------------------------------------------------------
		// ModelDescriptors
		//---------------------------------------------------------------------
		MeshDescriptor< VertexPositionNormalTexture > mesh_desc(true, true);
		SharedPtr< ModelDescriptor > model_desc_sponza = 
			ResourceManager::Get()->GetOrCreateModelDescriptor(L"assets/models/sponza/sponza.mdl", mesh_desc);
		SharedPtr< ModelDescriptor > model_desc_sphere = 
			ResourceManager::Get()->GetOrCreateModelDescriptor(L"assets/models/sphere/sphere.mdl", mesh_desc);
		//---------------------------------------------------------------------
		// Models
		//---------------------------------------------------------------------
		SharedPtr< ModelNode > model_sponza = CreateModelNode(*model_desc_sponza);
		model_sponza->GetTransform()->SetScale(10.0f);
		SharedPtr< ModelNode > model_sphere = CreateModelNode(*model_desc_sphere);
		model_sphere->GetTransform()->AddTranslationY(0.5f);

		//---------------------------------------------------------------------
		// Lights
		//---------------------------------------------------------------------
		SharedPtr< OmniLightNode > omni_light = CreateOmniLightNode();
		omni_light->GetTransform()->SetTranslationY(2.0f);
		omni_light->GetLight()->SetDistanceFalloff(0.0f, 2.0f);
		SharedPtr< SpotLightNode > spot_light = CreateSpotLightNode();
		spot_light->GetLight()->SetAngularCutoff(0.0f, 0.0f);// 0.86602540f);
		spot_light->GetLight()->SetDistanceFalloff(0.0f, 5.0f);
		camera->AddChildNode(spot_light);

		//---------------------------------------------------------------------
		// Texture
		//---------------------------------------------------------------------
		SharedPtr< Texture > texture_logo = 
			ResourceManager::Get()->GetOrCreateTexture(L"assets/sprites/mage.dds");
		//---------------------------------------------------------------------
		// Image
		//---------------------------------------------------------------------
		SharedPtr< SpriteImage > logo = MakeShared< SpriteImage >("logo", texture_logo);
		logo->GetTransform()->SetScale(0.25f, 0.25f);
		logo->GetTransform()->SetNormalizedTranslation(0.90f, 0.88f);
		AddSprite(logo);

		//---------------------------------------------------------------------
		// Font
		//---------------------------------------------------------------------
		SharedPtr< SpriteFont > font = 
			ResourceManager::Get()->GetOrCreateSpriteFont(L"assets/fonts/consolas.spritefont", SpriteFontDescriptor());
		//---------------------------------------------------------------------
		// Text
		//---------------------------------------------------------------------
		SharedPtr< SpriteText > text = MakeShared< NormalSpriteText >("text", font);
		AddSprite(text);

		//---------------------------------------------------------------------
		// Scripts
		//---------------------------------------------------------------------
		AddScript(MakeShared< RotationYScript >(model_sphere->GetTransform()));
		AddScript(MakeShared< FPSInputControllerScript >(camera->GetTransform()));
		AddScript(MakeShared< StatsScript >(text));
		AddScript(MakeShared< WireframeScript >());
	}
}