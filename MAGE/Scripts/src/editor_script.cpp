//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "editor_script.hpp"
#include "scene\scene.hpp"
#include "imgui.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage::script {

	//-------------------------------------------------------------------------
	// Editor Utilities
	//-------------------------------------------------------------------------
	namespace {

		void DrawWidget(rendering::CameraLens& lens,
						const F32x2& clipping_planes) {

			ImGui::Text("Lens:");
		
			//-----------------------------------------------------------------
			// Lens Radius
			//-----------------------------------------------------------------
			auto radius = lens.GetLensRadius();
			ImGui::InputFloat("Radius", &radius);
			lens.SetLensRadius(radius);

			//-----------------------------------------------------------------
			// Focal Length
			//-----------------------------------------------------------------
			auto focal_length = lens.GetFocalLength();
			ImGui::SliderFloat("Focal Length", &focal_length, 
							   clipping_planes.m_x, 
							   clipping_planes.m_y);
			lens.SetFocalLength(focal_length);

			//-----------------------------------------------------------------
			// Maximum Radius of the Circle-of-Confusion
			//-----------------------------------------------------------------
			auto coc = lens.GetMaximumCoCRadius();
			ImGui::SliderFloat("CoC", &coc, 0.0f, 10.0f);
			lens.SetMaximumCoCRadius(coc);
		}

		void DrawWidget(rendering::Fog& fog) {
			ImGui::Text("Fog:");

			//-----------------------------------------------------------------
			// Base Color
			//-----------------------------------------------------------------
			ImGui::ColorEdit3("Base Color", fog.GetBaseColor().GetData());

			//-----------------------------------------------------------------
			// Density
			//-----------------------------------------------------------------
			auto density = fog.GetDensity();
			ImGui::DragFloat("Density", &density, 0.00001f, 0.0f, 1.0f, "%.5f");
			fog.SetDensity(density);
		}

		void DrawWidget(rendering::Sky& sky) {
			ImGui::Text("Sky:");

			const auto& guid = sky.GetTexture()->GetGuid();
			ImGui::LabelText("Sky Texture", str_convert(guid).c_str());
		}

		void DrawWidget(rendering::CameraSettings& settings) {
			using rendering::RenderMode;
			using rendering::BRDFType;
			using rendering::ToneMapping;
			using rendering::RenderLayer;
			
			ImGui::Text("Settings:");
		
			//-----------------------------------------------------------------
			// Render Mode
			//-----------------------------------------------------------------
			static constexpr const char* render_mode_names[] = {
				"None",
				"Forward",
				"Deferred",
				"Solid",
				"Voxel Grid",
				"Base Color",
				"Base Color Coefficient",
				"Base Color Texture",
				"Material",
				"Material Coefficient",
				"Material Texture",
				"Roughness",
				"Roughness Coefficient",
				"Roughness Texture",
				"Metalness",
				"Metalness Coefficient",
				"Metalness Texture",
				"Shading Normal",
				"TSNM Shading Normal",
				"Depth",
				"Distance",
				"UV"
			};
			static constexpr RenderMode render_modes[] = {
				RenderMode::None,
				RenderMode::Forward,
				RenderMode::Deferred,
				RenderMode::Solid,
				RenderMode::VoxelGrid,
				RenderMode::FalseColor_BaseColor,
				RenderMode::FalseColor_BaseColorCoefficient,
				RenderMode::FalseColor_BaseColorTexture,
				RenderMode::FalseColor_Material,
				RenderMode::FalseColor_MaterialCoefficient,
				RenderMode::FalseColor_MaterialTexture,
				RenderMode::FalseColor_Roughness,
				RenderMode::FalseColor_RoughnessCoefficient,
				RenderMode::FalseColor_RoughnessTexture,
				RenderMode::FalseColor_Metalness,
				RenderMode::FalseColor_MetalnessCoefficient,
				RenderMode::FalseColor_MetalnessTexture,
				RenderMode::FalseColor_ShadingNormal,
				RenderMode::FalseColor_TSNMShadingNormal,
				RenderMode::FalseColor_Depth,
				RenderMode::FalseColor_Distance,
				RenderMode::FalseColor_UV
			};
			static_assert(std::size(render_mode_names) == std::size(render_modes));

			auto render_mode_index = static_cast< int >(settings.GetRenderMode());
			ImGui::Combo("Render Mode", &render_mode_index, render_mode_names,
						 static_cast< int >(std::size(render_mode_names)));
			settings.SetRenderMode(render_modes[render_mode_index]);

			//-----------------------------------------------------------------
			// BRDF
			//-----------------------------------------------------------------
			static constexpr const char* brdf_names[] = {
				"Default",
				"Lambertian",
				"Blinn-Phong",
				"Cook-Torrance",
				"Frostbite",
				"Ward-Duer"
			};
			static constexpr BRDFType brdfs[] = {
				BRDFType::Default,
				BRDFType::Lambertian,
				BRDFType::BlinnPhong,
				BRDFType::CookTorrance,
				BRDFType::Frostbite,
				BRDFType::WardDuer
			};
			static_assert(std::size(brdf_names) == std::size(brdfs));
		
			auto brdf_index = static_cast< int >(settings.GetBRDF());
			ImGui::Combo("BRDF", &brdf_index, brdf_names,
						 static_cast< int >(std::size(brdf_names)));
			settings.SetBRDF(brdfs[brdf_index]);
	
			//-----------------------------------------------------------------
			// Tone Mapping
			//-----------------------------------------------------------------
			static constexpr const char* tone_mapping_names[] = {
				"Default",
				"ACES Filmic",
				"Reinhard",
				"Uncharted"
			};
			static constexpr ToneMapping tone_mappings[] = {
				ToneMapping::Default,
				ToneMapping::ACESFilmic,
				ToneMapping::Reinhard,
				ToneMapping::Uncharted
			};
			static_assert(std::size(tone_mapping_names) == std::size(tone_mappings));
		
			auto tone_mapping_index = static_cast< int >(settings.GetToneMapping());
			ImGui::Combo("Tone Mapping", &tone_mapping_index, tone_mapping_names,
						 static_cast< int >(std::size(tone_mappings)));
			settings.SetToneMapping(tone_mappings[tone_mapping_index]);

			//-----------------------------------------------------------------
			// Gamma Exponent
			//-----------------------------------------------------------------
			auto gamma = settings.GetGamma();
			ImGui::DragFloat("Gamma", &gamma, 0.01f, 0.01f, 4.0f, "%.2f");
			settings.SetGamma(gamma);

			//-----------------------------------------------------------------
			// Render Layers
			//-----------------------------------------------------------------
			if (ImGui::Button("Render Layers")) {
				ImGui::OpenPopup("Render Layers");
			}
			if (ImGui::BeginPopup("Render Layers")) {
			
				if (auto wireframe = settings.ContainsRenderLayer(RenderLayer::Wireframe);
					ImGui::Checkbox("Wireframe", &wireframe)) {

					settings.ToggleRenderLayer(RenderLayer::Wireframe);
				}

				if (auto aabb = settings.ContainsRenderLayer(RenderLayer::AABB);
					ImGui::Checkbox("AABB", &aabb)) {

					settings.ToggleRenderLayer(RenderLayer::AABB);
				}

				ImGui::EndPopup();
			}
	
			ImGui::Separator();

			//-----------------------------------------------------------------
			// Fog
			//-----------------------------------------------------------------
			DrawWidget(settings.GetFog());

			ImGui::Separator();

			//-----------------------------------------------------------------
			// Sky
			//-----------------------------------------------------------------
			DrawWidget(settings.GetSky());
		}

		void DrawWidget(rendering::Viewport& viewport, 
						const F32x2& display_resolution) {
			
			static bool normalization = false;

			ImGui::Text("Viewport:");

			if (normalization) {
				//-------------------------------------------------------------
				// Top Left
				//-------------------------------------------------------------
				auto top_left 
					= AbsoluteToNormalized(F32x2(viewport.GetTopLeft()), 
										   display_resolution);
				ImGui::InputFloat2("Top Left", top_left.GetData());
				viewport.SetTopLeft(U32x2(
					NormalizedToAbsolute(top_left, display_resolution)));

				//-------------------------------------------------------------
				// Width and Height
				//-------------------------------------------------------------
				auto resolution 
					= AbsoluteToNormalized(F32x2(viewport.GetResolution()),
										   display_resolution);
				ImGui::InputFloat2("Resolution", resolution.GetData());
				viewport.SetResolution(U32x2(
					NormalizedToAbsolute(resolution, display_resolution)));
			}
			else {
				//-------------------------------------------------------------
				// Top Left
				//-------------------------------------------------------------
				auto top_left = S32x2(viewport.GetTopLeft());
				ImGui::InputInt2("Top Left", top_left.GetData());
				viewport.SetTopLeft(U32x2(top_left));

				//-------------------------------------------------------------
				// Width and Height
				//-------------------------------------------------------------
				auto resolution = S32x2(viewport.GetResolution());
				ImGui::InputInt2("Resolution", resolution.GetData());
				viewport.SetResolution(U32x2(resolution));
			}

			ImGui::Checkbox("Normalization", &normalization);
		}

		void DrawWidget(rendering::Camera& camera,
						const U32x2& display_resolution) {

			//-----------------------------------------------------------------
			// Near and Far
			//-----------------------------------------------------------------
			F32x2 clipping_planes(camera.GetNearZ(), camera.GetFarZ());
			ImGui::InputFloat2("Clipping Planes", clipping_planes.GetData());
			camera.SetNearAndFarZ(clipping_planes.m_x, clipping_planes.m_y);

			ImGui::Separator();

			//-----------------------------------------------------------------
			// Lens
			//-----------------------------------------------------------------
			DrawWidget(camera.GetLens(), clipping_planes);

			ImGui::Separator();

			//-----------------------------------------------------------------
			// Viewport
			//-----------------------------------------------------------------
			DrawWidget(camera.GetViewport(), 
					   static_cast< F32x2 >(display_resolution));

			ImGui::Separator();

			//-----------------------------------------------------------------
			// Settings
			//-----------------------------------------------------------------
			DrawWidget(camera.GetSettings());
		}

		void DrawWidget(rendering::OrthographicCamera& camera,
						const U32x2& display_resolution) {
			
			//-----------------------------------------------------------------
			// Size
			//-----------------------------------------------------------------
			auto size = camera.GetSize();
			ImGui::InputFloat2("Resolution", size.GetData());
			camera.SetSize(std::move(size));

			//-----------------------------------------------------------------
			// Camera
			//-----------------------------------------------------------------
			DrawWidget(static_cast< rendering::Camera& >(camera), 
					   display_resolution);
		}
	
		void DrawWidget(rendering::PerspectiveCamera& camera,
						const U32x2& display_resolution) {
			
			//-----------------------------------------------------------------
			// Aspect Ratio
			//-----------------------------------------------------------------
			auto aspect_ratio = camera.GetAspectRatio();
			ImGui::InputFloat("Aspect Ratio", &aspect_ratio);
			camera.SetAspectRatio(aspect_ratio);

			//-----------------------------------------------------------------
			// Vertical Field-of-View
			//-----------------------------------------------------------------
			auto fov_y = camera.GetFOVY();
			ImGui::InputFloat("Vertical FOV", &fov_y);
			camera.SetFOVY(fov_y);

			//-----------------------------------------------------------------
			// Camera
			//-----------------------------------------------------------------
			DrawWidget(static_cast< rendering::Camera& >(camera), 
					   display_resolution);
		}

		void DrawWidget(rendering::AmbientLight& light) {
			//-----------------------------------------------------------------
			// Base Color
			//-----------------------------------------------------------------
			ImGui::ColorEdit3("Base Color", light.GetBaseColor().GetData());

			//-----------------------------------------------------------------
			// Radiance
			//-----------------------------------------------------------------
			auto radiance = light.GetRadiance();
			ImGui::InputFloat("Radiance", &radiance);
			light.SetRadiance(radiance);
		}
	
		void DrawWidget(rendering::DirectionalLight& light) {
			//-----------------------------------------------------------------
			// Base Color
			//-----------------------------------------------------------------
			ImGui::ColorEdit3("Base Color", light.GetBaseColor().GetData());

			//-----------------------------------------------------------------
			// Irradiance
			//-----------------------------------------------------------------
			auto irradiance = light.GetIrradiance();
			ImGui::InputFloat("Irradiance", &irradiance);
			light.SetIrradiance(irradiance);
		}
	
		void DrawWidget(rendering::OmniLight& light) {
			//-----------------------------------------------------------------
			// Base Color
			//-----------------------------------------------------------------
			ImGui::ColorEdit3("Base Color", light.GetBaseColor().GetData());

			//-----------------------------------------------------------------
			// Intensity
			//-----------------------------------------------------------------
			auto intensity = light.GetIntensity();
			ImGui::InputFloat("Intensity", &intensity);
			light.SetIntensity(intensity);

			//-----------------------------------------------------------------
			// Power
			//-----------------------------------------------------------------
			auto power = light.GetPower();
			ImGui::InputFloat("Power", &power);
			light.SetPower(power);

			//-----------------------------------------------------------------
			// Range
			//-----------------------------------------------------------------
			auto range = light.GetRange();
			ImGui::InputFloat("Range", &range);
			light.SetRange(range);

			//-----------------------------------------------------------------
			// Shadows
			//-----------------------------------------------------------------
			auto shadows = light.UseShadows();
			ImGui::Checkbox("Shadows", &shadows);
			light.SetShadows(shadows);
		}
	
		void DrawWidget(rendering::SpotLight& light) {
			//-----------------------------------------------------------------
			// Base Color
			//-----------------------------------------------------------------
			ImGui::ColorEdit3("Base Color", light.GetBaseColor().GetData());

			//-----------------------------------------------------------------
			// Intensity
			//-----------------------------------------------------------------
			auto intensity = light.GetIntensity();
			ImGui::InputFloat("Intensity", &intensity);
			light.SetIntensity(intensity);

			//-----------------------------------------------------------------
			// Power
			//-----------------------------------------------------------------
			auto power = light.GetPower();
			ImGui::InputFloat("Power", &power);
			light.SetPower(power);

			//-----------------------------------------------------------------
			// Range
			//-----------------------------------------------------------------
			auto range = light.GetRange();
			ImGui::InputFloat("Range", &range);
			light.SetRange(range);

			//-----------------------------------------------------------------
			// Cosine Penumbra and Umbra
			//-----------------------------------------------------------------
			auto cos_penumbra = light.GetStartAngularCutoff();
			ImGui::InputFloat("Cosine penumbra", &cos_penumbra);
			auto cos_umbra = light.GetEndAngularCutoff();
			ImGui::InputFloat("Cosine umbra", &cos_umbra);
			light.SetAngularCutoff(cos_penumbra, cos_umbra);

			//-----------------------------------------------------------------
			// Shadows
			//-----------------------------------------------------------------
			auto shadows = light.UseShadows();
			ImGui::Checkbox("Shadows", &shadows);
			light.SetShadows(shadows);
		}

		void DrawWidget(TextureTransform& transform) {
			ImGui::Text("Texture Transform:");

			//-----------------------------------------------------------------
			// Translation
			//-----------------------------------------------------------------
			auto translation = transform.GetTranslation();
			ImGui::InputFloat2("Translation", translation.GetData());
			transform.SetTranslation(std::move(translation));

			//-----------------------------------------------------------------
			// Rotation Origin
			//-----------------------------------------------------------------
			auto rotation_origin = transform.GetRotationOrigin();
			ImGui::InputFloat2("Rotation Origin", rotation_origin.GetData());
			transform.SetRotationOrigin(std::move(rotation_origin));

			//-----------------------------------------------------------------
			// Rotation
			//-----------------------------------------------------------------
			auto rotation = transform.GetRotation();
			ImGui::DragFloat("Rotation", &rotation, 0.0001f, -XM_PI, XM_PI);
			transform.SetRotation(ClampAngleRadians(rotation));

			//-----------------------------------------------------------------
			// Scale
			//-----------------------------------------------------------------
			auto scale = transform.GetScale();
			ImGui::InputFloat2("Scale", scale.GetData());
			transform.SetScale(std::move(scale));
		}

		void DrawWidget(rendering::Material& material) {
			ImGui::Text("Material:");

			//-----------------------------------------------------------------
			// Base Color
			//-----------------------------------------------------------------
			ImGui::ColorEdit4("Base Color", material.GetBaseColor().GetData());

			//-----------------------------------------------------------------
			// Base Color Texture
			//-----------------------------------------------------------------
			const auto base_color_tex = material.GetBaseColorTexture();
			if (base_color_tex) {
				const auto& guid = base_color_tex->GetGuid();
				ImGui::Text(str_convert(guid).c_str());
				const auto resolution
					= rendering::GetTexture2DSize(*material.GetBaseColorSRV());
				ImGui::Text("%u x %u texels", resolution.m_x, resolution.m_y);
			}
			else {
				ImGui::Text("mage_black_texture");
				ImGui::Text("1 x 1 texels");
			}

			//-----------------------------------------------------------------
			// Transparency
			//-----------------------------------------------------------------
			auto transparency = material.IsTransparant();
			ImGui::Checkbox("Transparency", &transparency);
			material.SetTransparent(transparency);

			//-----------------------------------------------------------------
			// Roughness
			//-----------------------------------------------------------------
			auto roughness = material.GetRoughness();
			ImGui::SliderFloat("Roughness", &roughness, 0.0f, 1.0f);
			material.SetRoughness(roughness);

			//-----------------------------------------------------------------
			// Metalness
			//-----------------------------------------------------------------
			auto metalness = material.GetMetalness();
			ImGui::SliderFloat("Metalness", &metalness, 0.0f, 1.0f);
			material.SetMetalness(metalness);

			//-----------------------------------------------------------------
			// Material Texture
			//-----------------------------------------------------------------
			const auto material_tex = material.GetMaterialTexture();
			if (material_tex) {
				const auto& guid = material_tex->GetGuid();
				ImGui::Text(str_convert(guid).c_str());
				const auto resolution
					= rendering::GetTexture2DSize(*material.GetMaterialSRV());
				ImGui::Text("%u x %u texels", resolution.m_x, resolution.m_y);
			}
			else {
				ImGui::Text("mage_black_texture");
				ImGui::Text("1 x 1 texels");
			}

			//-----------------------------------------------------------------
			// Normal Texture
			//-----------------------------------------------------------------
			const auto normal_tex = material.GetNormalTexture();
			if (normal_tex) {
				const auto& guid = normal_tex->GetGuid();
				ImGui::Text(str_convert(guid).c_str());
				const auto resolution
					= rendering::GetTexture2DSize(*material.GetNormalSRV());
				ImGui::Text("%u x %u texels", resolution.m_x, resolution.m_y);
			}

			//-----------------------------------------------------------------
			// Light Interaction
			//-----------------------------------------------------------------
			auto light_interaction = material.InteractsWithLight();
			ImGui::Checkbox("Interacts with Light", &light_interaction);
			material.SetLightInteraction(light_interaction);
		}

		void DrawWidget(rendering::Model& model) {
			//-----------------------------------------------------------------
			// Texture transform
			//-----------------------------------------------------------------
			DrawWidget(model.GetTextureTransform());

			ImGui::Separator();

			//-----------------------------------------------------------------
			// Material
			//-----------------------------------------------------------------
			DrawWidget(model.GetMaterial());

			//-----------------------------------------------------------------
			// Occlusion
			//-----------------------------------------------------------------
			auto light_occlusion = model.OccludesLight();
			ImGui::Checkbox("Occludes Light", &light_occlusion);
			model.SetLightOcclusion(light_occlusion);
		}

		void DrawWidget(SpriteTransform& transform, 
						const F32x2& display_resolution, 
						const F32x2& texture_resolution) {
			
			ImGui::Text("Sprite Transform:");

			static bool normalization = false;

			//-----------------------------------------------------------------
			// Translation
			//-----------------------------------------------------------------
			if (normalization) {
				auto translation = AbsoluteToNormalized(transform.GetTranslation(), 
														display_resolution);
				ImGui::InputFloat2("Translation", translation.GetData());
				transform.SetTranslation(
					NormalizedToAbsolute(translation, display_resolution));
			}
			else {
				auto translation = transform.GetTranslation();
				ImGui::InputFloat2("Translation", translation.GetData());
				transform.SetTranslation(std::move(translation));
			}

			//-----------------------------------------------------------------
			// Depth
			//-----------------------------------------------------------------
			auto depth = transform.GetDepth();
			ImGui::InputFloat("Depth", &depth);
			transform.SetDepth(depth);

			//-----------------------------------------------------------------
			// Rotation Origin
			//-----------------------------------------------------------------
			if (normalization) {
				auto rotation_origin = AbsoluteToNormalized(
					transform.GetRotationOrigin(), texture_resolution);
				ImGui::InputFloat2("Rotation Origin", rotation_origin.GetData());
				transform.SetRotationOrigin(
					NormalizedToAbsolute(rotation_origin, texture_resolution));
			}
			else {
				auto rotation_origin = transform.GetRotationOrigin();
				ImGui::InputFloat2("Rotation Origin", rotation_origin.GetData());
				transform.SetRotationOrigin(std::move(rotation_origin));
			}

			//-----------------------------------------------------------------
			// Rotation
			//-----------------------------------------------------------------
			auto rotation = transform.GetRotation();
			ImGui::DragFloat("Rotation", &rotation, 0.0001f, -XM_PI, XM_PI);
			transform.SetRotation(ClampAngleRadians(rotation));

			//-----------------------------------------------------------------
			// Scale
			//-----------------------------------------------------------------
			auto scale = transform.GetScale();
			ImGui::InputFloat2("Scale", scale.GetData());
			transform.SetScale(std::move(scale));

			ImGui::Checkbox("Normalization", &normalization);
		}

		void DrawWidget(rendering::SpriteImage& sprite,
						const U32x2& display_resolution) {
			
			using rendering::SpriteEffect;
			
			const auto base_color_tex = sprite.GetBaseColorTexture();
			const auto texture_resolution = !base_color_tex ? U32x2(1u, 1u)
				: rendering::GetTexture2DSize(*sprite.GetBaseColorSRV());
				
			//-----------------------------------------------------------------
			// Sprite transform
			//-----------------------------------------------------------------
			DrawWidget(sprite.GetSpriteTransform(), 
					   static_cast< F32x2 >(display_resolution),
					   static_cast< F32x2 >(texture_resolution));

			ImGui::Separator();

			//-----------------------------------------------------------------
			// Base Color
			//-----------------------------------------------------------------
			ImGui::ColorEdit4("Base Color", sprite.GetBaseColor().GetData());

			//-----------------------------------------------------------------
			// Base Color Texture
			//-----------------------------------------------------------------
			if (base_color_tex) {
				const auto& guid = base_color_tex->GetGuid();
				ImGui::Text(str_convert(guid).c_str());
				ImGui::Text("%u x %u texels", 
							texture_resolution.m_x, texture_resolution.m_y);
			}
			else {
				ImGui::Text("mage_black_texture");
				ImGui::Text("1 x 1 texels");
			}

			//-----------------------------------------------------------------
			// Sprite Effects
			//-----------------------------------------------------------------
			static constexpr const char* sprite_effect_names[] = {
				"None",
				"Mirror X",
				"Mirror Y",
				"Mirror XY"
			};
			static constexpr SpriteEffect sprite_effects[] = {
				SpriteEffect::None,
				SpriteEffect::MirrorX,
				SpriteEffect::MirrorY,
				SpriteEffect::MirrorXY
			};
			static_assert(std::size(sprite_effect_names) == std::size(sprite_effects));

			auto sprite_effect_index = static_cast< int >(sprite.GetSpriteEffects());
			ImGui::Combo("Sprite Effects", &sprite_effect_index, sprite_effect_names,
						 static_cast< int >(std::size(sprite_effect_names)));
			sprite.SetSpriteEffects(sprite_effects[sprite_effect_index]);
		}
	
		void DrawWidget(rendering::SpriteText& sprite,
						const U32x2& display_resolution) {

			using rendering::SpriteEffect;
			using rendering::SpriteText;
			
			const auto font = sprite.GetFont();
			const auto texture_resolution = !font ? U32x2(1, 1)
				: rendering::GetTexture2DSize(*sprite.GetFontSRV());

			//-----------------------------------------------------------------
			// Sprite transform
			//-----------------------------------------------------------------
			DrawWidget(sprite.GetSpriteTransform(),
					   static_cast< F32x2 >(display_resolution),
					   static_cast< F32x2 >(texture_resolution));

			ImGui::Separator();

			//-----------------------------------------------------------------
			// Sprite font
			//-----------------------------------------------------------------
			if (font) {
				const auto& guid = font->GetGuid();
				ImGui::Text(str_convert(guid).c_str());
				ImGui::Text("%u x %u texels",
							texture_resolution.m_x, texture_resolution.m_y);
			}
			else {
				ImGui::Text("no font");
				ImGui::Text("1 x 1 texels");
			}

			//-----------------------------------------------------------------
			// Sprite effects
			//-----------------------------------------------------------------
			static constexpr const char* sprite_effect_names[] = {
				{ "None"    },
				{ "Flip X"  },
				{ "Flip Y"  },
				{ "Flip XY" }
			};
			static constexpr SpriteEffect sprite_effects[] = {
				{ SpriteEffect::None     },
				{ SpriteEffect::MirrorX  },
				{ SpriteEffect::MirrorY  },
				{ SpriteEffect::MirrorXY }
			};
			static_assert(std::size(sprite_effect_names) == std::size(sprite_effects));

			auto sprite_effect_index = static_cast< int >(sprite.GetSpriteEffects());
			ImGui::Combo("Sprite Effects", &sprite_effect_index, sprite_effect_names,
						 static_cast< int >(std::size(sprite_effect_names)));
			sprite.SetSpriteEffects(sprite_effects[sprite_effect_index]);

			//-----------------------------------------------------------------
			// Text effect color
			//-----------------------------------------------------------------
			ImGui::ColorEdit4("Text Effect Color", sprite.GetTextEffectColor().GetData());

			//-----------------------------------------------------------------
			// Text effects
			//-----------------------------------------------------------------
			static constexpr const char* text_effect_names[] = {
				"None",
				"Drop Shadow",
				"Outline"
			};
			static constexpr SpriteText::TextEffect text_effects[] = {
				SpriteText::TextEffect::None,
				SpriteText::TextEffect::DropShadow,
				SpriteText::TextEffect::Outline
			};
			static_assert(std::size(text_effect_names) == std::size(text_effects));

			auto text_effect_index = static_cast< int >(sprite.GetTextEffect());
			ImGui::Combo("Text Effect", &text_effect_index, text_effect_names,
						 static_cast< int >(std::size(text_effect_names)));
			sprite.SetTextEffect(text_effects[text_effect_index]);
		}

		void DrawWidget(Transform& transform) {
			//-----------------------------------------------------------------
			// Translation
			//-----------------------------------------------------------------
			if (auto translation = transform.GetTranslation();
				ImGui::InputFloat3("Translation", translation.GetData())) {

				transform.SetTranslation(std::move(translation));
			}
		
			//-----------------------------------------------------------------
			// Rotation
			//-----------------------------------------------------------------
			if (auto rotation = transform.GetRotation();
				ImGui::InputFloat3("Rotation", rotation.GetData())) {

				transform.SetRotation(std::move(rotation));
			}
		
			//-----------------------------------------------------------------
			// Scale
			//-----------------------------------------------------------------
			if (auto scale = transform.GetScale();
				ImGui::InputFloat3("Scale", scale.GetData())) {

				transform.SetScale(std::move(scale));
			}
		}

		void DrawWidget(Node& node, 
						const U32x2& display_resolution) {
			
			using rendering::OrthographicCamera;
			using rendering::PerspectiveCamera;
			using rendering::AmbientLight;
			using rendering::DirectionalLight;
			using rendering::OmniLight;
			using rendering::SpotLight;
			using rendering::Model;
			using rendering::SpriteImage;
			using rendering::SpriteText;

			//-----------------------------------------------------------------
			// Name
			//-----------------------------------------------------------------
			char buffer[128];
			sprintf_s(buffer, std::size(buffer), "%s", node.GetName().c_str());
			if (ImGui::InputText("", buffer, std::size(buffer))) {
				node.SetName(string(buffer));
			}

			ImGui::SameLine();
		
			//-----------------------------------------------------------------
			// State
			//-----------------------------------------------------------------
			if (auto active = (State::Active == node.GetState());
				ImGui::Checkbox("Active", &active)) {
				node.SetState(active ? State::Active : State::Passive);
			}
		
			ImGui::Separator();

			//-----------------------------------------------------------------
			// Transform
			//-----------------------------------------------------------------
			if (ImGui::TreeNode("Transform")) {
				DrawWidget(node.GetTransform());
				ImGui::TreePop();
			}

			//-----------------------------------------------------------------
			// OrthographicCameras
			//-----------------------------------------------------------------
			node.ForEach< OrthographicCamera >([&display_resolution]
			(OrthographicCamera& camera) {
				if (const auto id = std::to_string(camera.GetGuid());
					ImGui::TreeNode(id.c_str(), "Orthographic Camera")) {
				
					DrawWidget(camera, display_resolution);
				
					ImGui::TreePop();
				}
			});

			//-----------------------------------------------------------------
			// PerspectiveCameras
			//-----------------------------------------------------------------
			node.ForEach< PerspectiveCamera >([&display_resolution]
			(PerspectiveCamera& camera) {
				if (const auto id = std::to_string(camera.GetGuid());
					ImGui::TreeNode(id.c_str(), "Perspective Camera")) {
				
					DrawWidget(camera, display_resolution);
				
					ImGui::TreePop();
				}
			});

			//-----------------------------------------------------------------
			// AmbientLights
			//-----------------------------------------------------------------
			node.ForEach< AmbientLight >([](AmbientLight& light) {
				if (const auto id = std::to_string(light.GetGuid());
					ImGui::TreeNode(id.c_str(), "Ambient Light")) {

					DrawWidget(light);

					ImGui::TreePop();
				}
			});

			//-----------------------------------------------------------------
			// DirectionalLights
			//-----------------------------------------------------------------
			node.ForEach< DirectionalLight >([](DirectionalLight& light) {
				if (const auto id = std::to_string(light.GetGuid());
					ImGui::TreeNode(id.c_str(), "Directional Light")) {

					DrawWidget(light);

					ImGui::TreePop();
				}
			});

			//-----------------------------------------------------------------
			// OmniLights
			//-----------------------------------------------------------------
			node.ForEach< OmniLight >([](OmniLight& light) {
				if (const auto id = std::to_string(light.GetGuid());
					ImGui::TreeNode(id.c_str(), "Omni Light")) {

					DrawWidget(light);

					ImGui::TreePop();
				}
			});

			//-----------------------------------------------------------------
			// SpotLights
			//-----------------------------------------------------------------
			node.ForEach< SpotLight >([](SpotLight& light) {
				if (const auto id = std::to_string(light.GetGuid());
					ImGui::TreeNode(id.c_str(), "Spotlight")) {

					DrawWidget(light);

					ImGui::TreePop();
				}
			});

			//-----------------------------------------------------------------
			// Models
			//-----------------------------------------------------------------
			node.ForEach< Model >([](Model& model) {
				if (const auto id = std::to_string(model.GetGuid());
					ImGui::TreeNode(id.c_str(), "Model")) {
				
					DrawWidget(model);

					ImGui::TreePop();
				}
			});

			//-----------------------------------------------------------------
			// SpriteImages
			//-----------------------------------------------------------------
			node.ForEach< SpriteImage >([&display_resolution]
			(SpriteImage& sprite) {
				if (const auto id = std::to_string(sprite.GetGuid());
					ImGui::TreeNode(id.c_str(), "Sprite Image")) {

					DrawWidget(sprite, display_resolution);

					ImGui::TreePop();
				}
			});

			//-----------------------------------------------------------------
			// SpriteTexts
			//-----------------------------------------------------------------
			node.ForEach< SpriteText >([&display_resolution]
			(SpriteText& sprite) {
				if (const auto id = std::to_string(sprite.GetGuid());
					ImGui::TreeNode(id.c_str(), "Sprite Text")) {

					DrawWidget(sprite, display_resolution);

					ImGui::TreePop();
				}
			});
		}

		void DrawGraph(Node& node,
					   ProxyPtr< Node >& selected) {
			
			const auto  id   = std::to_string(node.GetGuid());
			const auto& name = node.GetName();

			if (node.ContainsChilds()) {
				static constexpr ImGuiTreeNodeFlags node_flags
					= ImGuiTreeNodeFlags_OpenOnArrow
					| ImGuiTreeNodeFlags_OpenOnDoubleClick;

				const ImGuiTreeNodeFlags flags = (node.Get() == selected)
					? node_flags | ImGuiTreeNodeFlags_Selected : node_flags;

				const auto node_open = ImGui::TreeNodeEx(id.c_str(), flags, name.c_str());

				if (ImGui::IsItemClicked()) {
					selected = node.Get();
				}

				if (node_open) {
					node.ForEachChild([&selected](Node& child) {
						DrawGraph(child, selected);
					});

					ImGui::TreePop();
				}
			}
			else {
				static constexpr ImGuiTreeNodeFlags node_flags
					= ImGuiTreeNodeFlags_OpenOnArrow
					| ImGuiTreeNodeFlags_OpenOnDoubleClick
					| ImGuiTreeNodeFlags_Leaf
					| ImGuiTreeNodeFlags_NoTreePushOnOpen;

				const ImGuiTreeNodeFlags flags = (node.Get() == selected)
					? node_flags | ImGuiTreeNodeFlags_Selected : node_flags;

				ImGui::TreeNodeEx(id.c_str(), flags, name.c_str());
				if (ImGui::IsItemClicked()) {
					selected = node.Get();
				}
			}
		}

		void DrawGraph(Scene& scene, 
					   ProxyPtr< Node >& selected) {

			ImGui::Begin("Scene Graph");
			// Increase spacing to differentiate leaves from expanded contents.
			ImGui::PushStyleVar(ImGuiStyleVar_IndentSpacing, 
								ImGui::GetFontSize() * 3.0f);

			scene.ForEach< Node >([&selected](Node& node) {
				if (!node.HasParent()) {
					DrawGraph(node, selected);
				}
			});

			ImGui::PopStyleVar();
			ImGui::End();
		}

		void DrawInspector(ProxyPtr< Node >& selected,
						   const U32x2& display_resolution) {

			ImGui::Begin("Inspector");

			if (selected && State::Terminated != selected->GetState()) {
				DrawWidget(*selected, display_resolution);
			}

			ImGui::End();
		}
	}

	//-------------------------------------------------------------------------
	// EditorScript
	//-------------------------------------------------------------------------
	#pragma region

	EditorScript::EditorScript() noexcept = default;

	EditorScript::EditorScript(const EditorScript& script) noexcept = default;

	EditorScript::EditorScript(EditorScript&& script) noexcept = default;
	
	EditorScript::~EditorScript() = default;

	EditorScript& EditorScript
		::operator=(const EditorScript& script) noexcept = default;

	EditorScript& EditorScript
		::operator=(EditorScript&& script) noexcept = default;

	void EditorScript::Load([[maybe_unused]] Engine& engine) {
		m_selected = nullptr;
	}

	void EditorScript::Update([[maybe_unused]] Engine& engine,
							  [[maybe_unused]] F64 delta_time) {
		
		const auto scene = engine.GetScene();
		DrawGraph(*scene, m_selected);

		const auto config = engine.GetRenderingManager().GetDisplayConfiguration();
		const auto display_resolution = config.GetDisplayResolution();
		DrawInspector(m_selected, display_resolution);
	}

	#pragma endregion
}