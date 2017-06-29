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
		// Camera
		//---------------------------------------------------------------------
		SharedPtr< PerspectiveCameraNode > camera = CreatePerspectiveCameraNode();
		camera->GetTransform()->SetTranslationY(2.0f);
		SetCamera(camera);

		//---------------------------------------------------------------------
		// ModelDescriptors
		//---------------------------------------------------------------------
		MeshDescriptor< VertexPositionNormalTexture > mesh_desc(true, true);
		SharedPtr< ModelDescriptor > model_desc_sponza = CreateModelDescriptor(
			L"assets/models/sponza/sponza.mdl", L"assets/models/sponza/sponza.mdl", mesh_desc);
		SharedPtr< ModelDescriptor > model_desc_sphere = CreateModelDescriptor(
			L"assets/models/sphere/sphere.mdl", L"assets/models/sphere/sphere.mdl", mesh_desc);
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
		SharedPtr< Texture > texture_logo = CreateTexture(
			L"assets/sprites/mage.dds", L"assets/sprites/mage.dds");
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
		SharedPtr< SpriteFont > font = CreateFont(
			L"assets/fonts/consolas.spritefont", L"assets/fonts/consolas.spritefont", SpriteFontDescriptor());
		//---------------------------------------------------------------------
		// Text
		//---------------------------------------------------------------------
		SharedPtr< SpriteText > text = std::make_shared< NormalSpriteText >("text", font);
		AddSprite(text);

		//---------------------------------------------------------------------
		// Scripts
		//---------------------------------------------------------------------
		AddScript(std::make_shared< RotationYScript >(model_sphere->GetTransform()));
		AddScript(std::make_shared< FPSInputControllerScript >(camera->GetTransform()));
		AddScript(std::make_shared< StatsScript >(text));
		AddScript(std::make_shared< WireframeScript >());
	}
}