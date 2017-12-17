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

#include "script\character_motor_script.hpp"
#include "script\mouse_look_script.hpp"
#include "script\render_mode_script.hpp"
#include "script\rotation_script.hpp"
#include "script\stats_script.hpp"
#include "script\switch_scene_script.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Game Definitions
//-----------------------------------------------------------------------------
namespace mage {

	ForrestScene::ForrestScene()
		: Scene("forrest_scene") {}

	ForrestScene::ForrestScene(ForrestScene &&scene) = default;

	ForrestScene::~ForrestScene() = default;

	void ForrestScene::Load() {

		//---------------------------------------------------------------------
		// Resources
		//---------------------------------------------------------------------
		ResourceManager * const factory = ResourceManager::Get();
		MeshDescriptor< VertexPositionNormalTexture > mesh_desc(true, true);

		auto plane_model_desc = factory->GetOrCreate< ModelDescriptor >(
			L"assets/models/plane/plane.mdl", mesh_desc);
		auto tree1_model_desc = factory->GetOrCreate< ModelDescriptor >(
			L"assets/models/tree/tree1a_lod0.mdl", mesh_desc);
		auto tree2_model_desc = factory->GetOrCreate< ModelDescriptor >(
			L"assets/models/tree/tree1b_lod0.mdl", mesh_desc);
		auto tree3_model_desc = factory->GetOrCreate< ModelDescriptor >(
			L"assets/models/tree/tree2a_lod0.mdl", mesh_desc);
		auto tree4_model_desc = factory->GetOrCreate< ModelDescriptor >(
			L"assets/models/tree/tree2b_lod0.mdl", mesh_desc);
		auto tree5_model_desc = factory->GetOrCreate< ModelDescriptor >(
			L"assets/models/tree/tree3a_lod0.mdl", mesh_desc);
		auto tree6_model_desc = factory->GetOrCreate< ModelDescriptor >(
			L"assets/models/tree/tree3b_lod0.mdl", mesh_desc);
		auto tree7_model_desc = factory->GetOrCreate< ModelDescriptor >(
			L"assets/models/tree/tree4a_lod0.mdl", mesh_desc);
		auto tree8_model_desc = factory->GetOrCreate< ModelDescriptor >(
			L"assets/models/tree/tree4b_lod0.mdl", mesh_desc);
		auto windmill_model_desc = factory->GetOrCreate< ModelDescriptor >(
			L"assets/models/windmill/windmill.mdl", mesh_desc);
		auto sky_texture = factory->GetOrCreate< Texture >(
			L"assets/textures/sky/sky.dds");

		//---------------------------------------------------------------------
		// Cameras
		//---------------------------------------------------------------------
		auto camera = Create< PerspectiveCamera >();

		// Camera: Lens
		// camera->GetLens().SetLensRadius(0.01f);
		// camera->GetLens().SetFocalLength(3.0f);
		// camera->GetLens().SetMaximumCoCRadius(2.0f);
		// Camera: Viewport
		// camera->GetViewport().SetNormalizedWidth(0.5f);
		// Camera: Fog
		camera->GetSettings().GetFog().SetDensity(0.001f);
		// Camera: Sky
		camera->GetSettings().GetSky().SetTexture(sky_texture);

		auto camera_node = Create< Node >();
		camera_node->AddComponent(camera);
		camera_node->GetTransform().SetTranslationY(2.0f);

		//---------------------------------------------------------------------
		// Models
		//---------------------------------------------------------------------
		auto plane_node = Import(*plane_model_desc);
		plane_node->GetTransform().SetScale(30.0f);
		
		auto tree1_node = Import(*tree1_model_desc);
		tree1_node->GetTransform().SetScale(5.0f);
		tree1_node->GetTransform().SetTranslation(-5.0f, 2.5f, -10.0f);
		auto tree2_node = Import(*tree2_model_desc);
		tree2_node->GetTransform().SetScale(5.0f);
		tree2_node->GetTransform().SetTranslation(-5.0f, 2.5f, -5.0f);
		auto tree3_node = Import(*tree3_model_desc);
		tree3_node->GetTransform().SetScale(5.0f);
		tree3_node->GetTransform().SetTranslation(-5.0f, 2.5f, 5.0f);
		auto tree4_node = Import(*tree4_model_desc);
		tree4_node->GetTransform().SetScale(5.0f);
		tree4_node->GetTransform().SetTranslation(-5.0f, 2.5f, 10.0f);
		auto tree5_node = Import(*tree5_model_desc);
		tree5_node->GetTransform().SetScale(5.0f);
		tree5_node->GetTransform().SetTranslation(-10.0f, 2.5f, -10.0f);
		auto tree6_node = Import(*tree6_model_desc);
		tree6_node->GetTransform().SetScale(5.0f);
		tree6_node->GetTransform().SetTranslation(-10.0f, 2.5f, -5.0f);
		auto tree7_node = Import(*tree7_model_desc);
		tree7_node->GetTransform().SetScale(5.0f);
		tree7_node->GetTransform().SetTranslation(-10.0f, 2.5f, 5.0f);
		auto tree8_node = Import(*tree8_model_desc);
		tree8_node->GetTransform().SetScale(5.0f);
		tree8_node->GetTransform().SetTranslation(-10.0f, 2.5f, 10.0f);
		
		std::vector< ProxyPtr< Node > >windmill_nodes;
		auto windmill_node = Import(*windmill_model_desc, windmill_nodes);
		windmill_node->GetTransform().SetScale(10.0f);
		windmill_node->GetTransform().SetTranslationY(4.25f);

		//---------------------------------------------------------------------
		// Lights
		//---------------------------------------------------------------------
		auto light = Create< SpotLight >();
		light->SetRange(20.0f);
		light->SetAngularCutoff(1.0f, sqrt(2.0f) / 2.0f);
		light->SetIntensity(40.0f);
		light->EnableShadows();

		auto light_node = Create< Node >();
		light_node->AddComponent(light);
		light_node->GetTransform().SetTranslationY(15.0f);
		light_node->GetTransform().SetRotationX(XM_PIDIV2);

		auto spot_light = Create< SpotLight >();
		spot_light->SetRange(5.0f);
		spot_light->SetAngularCutoff(1.0f, 0.5f);

		camera_node->AddComponent(spot_light);

		auto directional_light = Create< DirectionalLight >();
		directional_light->SetRadiance(4.0f);
		
		auto directional_light_node = Create< Node >();
		directional_light_node->AddComponent(directional_light);
		directional_light_node->GetTransform().SetTranslation(20.0f, 20.0f, 0.0f);
		directional_light_node->GetTransform().SetRotationZ(XM_PIDIV4);
		
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
		Create< script::SwitchSceneScript< BRDFScene > >();
		
		auto script = Create< script::RotationScript >();
		script->SetRotationAxis(script::RotationScript::RotationAxis::X);
		
		windmill_nodes[0]->AddComponent(script);
		
		camera_node->AddComponent(Create< script::MouseLookScript >());
		camera_node->AddComponent(Create< script::CharacterMotorScript >());
		camera_node->AddComponent(Create< script::RenderModeScript >());
		camera_node->AddComponent(Create< script::StatsScript >());
	}
}