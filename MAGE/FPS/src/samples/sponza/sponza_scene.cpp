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
		auto scene_fog = GetSceneFog();
		scene_fog->SetDistanceFalloff(0.0f, 17.0f);

		//---------------------------------------------------------------------
		// Camera
		//---------------------------------------------------------------------
		auto camera = CreatePerspectiveCamera("camera");
		camera->GetTransform()->SetTranslationY(2.0f);

		//---------------------------------------------------------------------
		// ModelDescriptors
		//---------------------------------------------------------------------
		MeshDescriptor< VertexPositionNormalTexture > mesh_desc(true, true);
		auto model_desc_sponza = 
			ResourceManager::Get()->GetOrCreateModelDescriptor(L"assets/models/sponza/sponza.mdl", mesh_desc);
		auto model_desc_sphere = 
			ResourceManager::Get()->GetOrCreateModelDescriptor(L"assets/models/sphere/sphere.mdl", mesh_desc);
		//---------------------------------------------------------------------
		// Models
		//---------------------------------------------------------------------
		auto model_sponza = CreateModel(*model_desc_sponza);
		model_sponza->GetTransform()->SetScale(10.0f);
		auto model_sphere = CreateModel(*model_desc_sphere);
		model_sphere->GetTransform()->AddTranslationY(0.5f);

		//---------------------------------------------------------------------
		// Lights
		//---------------------------------------------------------------------
		auto omni_light = CreateOmniLight("light");
		omni_light->GetTransform()->SetTranslationY(2.0f);
		omni_light->GetLight()->SetDistanceFalloff(0.0f, 2.0f);
		auto spot_light = CreateSpotLight("light");
		spot_light->GetLight()->SetAngularCutoff(0.0f, 0.0f);// 0.86602540f);
		spot_light->GetLight()->SetDistanceFalloff(0.0f, 5.0f);
		camera->AddChildNode(spot_light);

		//---------------------------------------------------------------------
		// Texture
		//---------------------------------------------------------------------
		auto texture_logo = 
			ResourceManager::Get()->GetOrCreateTexture(L"assets/sprites/mage.dds");
		//---------------------------------------------------------------------
		// Image
		//---------------------------------------------------------------------
		auto logo = CreateSpriteImage("logo", texture_logo);
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
		auto text = CreateNormalSpriteText("stats", font);

		//---------------------------------------------------------------------
		// Scripts
		//---------------------------------------------------------------------
		AddScript(MakeShared< RotationYScript >(model_sphere->GetTransform()));
		AddScript(MakeShared< FPSInputControllerScript >(camera->GetTransform()));
		AddScript(MakeShared< StatsScript >(text->GetSprite()));
		AddScript(MakeShared< WireframeScript >());
	}
}