//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "editor\widget.hpp"
#include "imgui\imgui.hpp"
#include "scene\scene.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage::editor {

	static ProxyPtr< Node > g_selected = nullptr;

	void SetSelected(ProxyPtr< Node > node) noexcept {
		g_selected = std::move(node);
	}

	static void DrawWidget(CameraLens &lens, const F32x2 &clipping_planes) {
		ImGui::Text("Lens:");
		
		// Lens radius
		auto radius = lens.GetLensRadius();
		ImGui::InputFloat("Radius", &radius);
		lens.SetLensRadius(radius);

		// Focal length
		auto focal_length = lens.GetFocalLength();
		ImGui::SliderFloat("Focal Length", &focal_length, 
			               clipping_planes.m_x, 
			               clipping_planes.m_y);
		lens.SetFocalLength(focal_length);

		// Maximum radius of the circle-of-confusion
		auto coc = lens.GetMaximumCoCRadius();
		ImGui::SliderFloat("CoC", &coc, 0.0f, 10.0f);
		lens.SetMaximumCoCRadius(coc);
	}

	static void DrawWidget(Fog &fog) {
		ImGui::Text("Fog:");

		// Base color
		ImGui::ColorEdit3("Base Color", fog.GetBaseColor().GetData());

		// Radiance
		auto density = fog.GetDensity();
		ImGui::DragFloat("Density", &density, 0.00001f, 0.0f, 1.0f, "%.5f");
		fog.SetDensity(density);
	}

	static void DrawWidget(Sky &sky) {
		ImGui::Text("Sky:");

		const auto guid = sky.GetTexture()->GetGuid();
		ImGui::LabelText("Sky Texture", str_convert(guid).c_str());
	}

	static void DrawWidget(CameraSettings &settings) {
		ImGui::Text("Settings:");
		
		// Render Mode
		static constexpr const char *render_mode_names[] = {
			{ "None"                   },
			{ "Forward"                },
			{ "Deferred"               },
			{ "Solid"                  },
			{ "Base Color"             },
			{ "Base Color Coefficient" },
			{ "Base Color Texture"     },
			{ "Material"               },
			{ "Material Coefficient"   },
			{ "Material Texture"       },
			{ "Normal Texture"         },
			{ "UV Texture"             },
			{ "Distance"               },
			{ "Shading Normal"         },
			{ "TSNM Shading Normal"    } 
		};
		static constexpr RenderMode render_modes[] = {
			{ RenderMode::None                 },
			{ RenderMode::Forward              },
			{ RenderMode::Deferred             },
			{ RenderMode::Solid                },
			{ RenderMode::BaseColor            },
			{ RenderMode::BaseColorCoefficient },
			{ RenderMode::BaseColorTexture     },
			{ RenderMode::Material             },
			{ RenderMode::MaterialCoefficient  },
			{ RenderMode::MaterialTexture      },
			{ RenderMode::NormalTexture        },
			{ RenderMode::UVTexture            },
			{ RenderMode::Distance             },
			{ RenderMode::ShadingNormal        },
			{ RenderMode::TSNMShadingNormal    } 
		};
		static_assert(std::size(render_mode_names) == std::size(render_modes));

		auto render_mode_index = static_cast< int >(settings.GetRenderMode());
		ImGui::Combo("Render Mode", &render_mode_index, render_mode_names,
			         static_cast<int>(std::size(render_mode_names)));
		settings.SetRenderMode(render_modes[render_mode_index]);

		// BRDF
		static constexpr const char *brdf_names[] = {
			{ "Default"       },
			{ "Lambertian"    },
			{ "Blinn-Phong"   },
			{ "Cook-Torrance" },
			{ "Frostbite"     },
			{ "Ward-Duer"     }
		};
		static constexpr BRDFType brdfs[] = {
			{ BRDFType::Unknown      },
			{ BRDFType::Lambertian   },
			{ BRDFType::BlinnPhong   },
			{ BRDFType::CookTorrance },
			{ BRDFType::Frostbite    },
			{ BRDFType::WardDuer     }
		};
		static_assert(std::size(brdf_names) == std::size(brdfs));
		
		auto brdf_index = static_cast< int >(settings.GetBRDF());
		ImGui::Combo("BRDF", &brdf_index, brdf_names,
			         static_cast<int>(std::size(brdf_names)));
		settings.SetBRDF(brdfs[brdf_index]);
	
		// Render Layers
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

		// Fog
		DrawWidget(settings.GetFog());

		ImGui::Separator();

		// Sky
		DrawWidget(settings.GetSky());
	}

	static void DrawWidget(Viewport &viewport) {
		static bool normalization = false;

		ImGui::Text("Viewport:");

		if (normalization) {
			// Top left
			auto top_left = viewport.GetNormalizedTopLeft();
			ImGui::InputFloat2("Top Left", top_left.GetData());
			viewport.SetNormalizedTopLeft(top_left);

			// Width and height
			auto resolution = viewport.GetNormalizedWidthAndHeight();
			ImGui::InputFloat2("Resolution", resolution.GetData());
			viewport.SetNormalizedWidthAndHeight(resolution);
		}
		else {
			// Top left
			auto top_left = viewport.GetTopLeft();
			ImGui::InputFloat2("Top Left", top_left.GetData());
			viewport.SetTopLeft(top_left);

			// Width and height
			auto resolution = viewport.GetWidthAndHeight();
			ImGui::InputFloat2("Resolution", resolution.GetData());
			viewport.SetWidthAndHeight(resolution);
		}

		ImGui::Checkbox("Normalization", &normalization);
	}

	static void DrawWidget(Camera &camera) {
		// Near and far
		F32x2 clipping_planes(camera.GetNearZ(), camera.GetFarZ());
		ImGui::InputFloat2("Clipping Planes", clipping_planes.GetData());
		camera.SetNearAndFarZ(clipping_planes.m_x, clipping_planes.m_y);

		ImGui::Separator();

		// Lens
		DrawWidget(camera.GetLens(), clipping_planes);

		ImGui::Separator();

		// Viewport
		DrawWidget(camera.GetViewport());

		ImGui::Separator();

		// Settings
		DrawWidget(camera.GetSettings());
	}

	static void DrawWidget(OrthographicCamera &camera) {
		// Width and height
		auto width = camera.GetWidth();
		ImGui::InputFloat("Width", &width);
		auto height = camera.GetHeight();
		ImGui::InputFloat("Height", &height);
		camera.SetWidthAndHeight(width, height);

		// Camera
		DrawWidget(static_cast< Camera & >(camera));
	}
	
	static void DrawWidget(PerspectiveCamera &camera) {
		// Aspect ratio
		auto aspect_ratio = camera.GetAspectRatio();
		ImGui::InputFloat("Aspect Ratio", &aspect_ratio);
		camera.SetAspectRatio(aspect_ratio);

		// Vertical field-of-view
		auto fov_y = camera.GetFOVY();
		ImGui::InputFloat("Vertical FOV", &fov_y);
		camera.SetFOVY(fov_y);

		// Camera
		DrawWidget(static_cast< Camera & >(camera));
	}

	static void DrawWidget(AmbientLight &light) {
		// Base color
		ImGui::ColorEdit3("Base Color", light.GetBaseColor().GetData());

		// Radiance
		auto radiance = light.GetRadiance();
		ImGui::InputFloat("Radiance", &radiance);
		light.SetRadiance(radiance);
	}
	
	static void DrawWidget(DirectionalLight &light) {
		// Base color
		ImGui::ColorEdit3("Base Color", light.GetBaseColor().GetData());

		// Radiance
		auto radiance = light.GetRadiance();
		ImGui::InputFloat("Radiance", &radiance);
		light.SetRadiance(radiance);
	}
	
	static void DrawWidget(OmniLight &light) {
		// Base color
		ImGui::ColorEdit3("Base Color", light.GetBaseColor().GetData());

		// Intensity
		auto intensity = light.GetIntensity();
		ImGui::InputFloat("Intensity", &intensity);
		light.SetIntensity(intensity);

		// Power
		auto power = light.GetPower();
		ImGui::InputFloat("Power", &power);
		light.SetPower(power);

		// Range
		auto range = light.GetRange();
		ImGui::InputFloat("Range", &range);
		light.SetRange(range);

		// Shadows
		auto shadows = light.UseShadows();
		ImGui::Checkbox("Shadows", &shadows);
		light.SetShadows(shadows);
	}
	
	static void DrawWidget(SpotLight &light) {
		// Base color
		ImGui::ColorEdit3("Base Color", light.GetBaseColor().GetData());

		// Intensity
		auto intensity = light.GetIntensity();
		ImGui::InputFloat("Intensity", &intensity);
		light.SetIntensity(intensity);

		// Power
		auto power = light.GetPower();
		ImGui::InputFloat("Power", &power);
		light.SetPower(power);

		// Range
		auto range = light.GetRange();
		ImGui::InputFloat("Range", &range);
		light.SetRange(range);

		// Cosine penumbra and umbra
		auto cos_penumbra = light.GetStartAngularCutoff();
		ImGui::InputFloat("Cosine penumbra", &cos_penumbra);
		auto cos_umbra = light.GetEndAngularCutoff();
		ImGui::InputFloat("Cosine umbra", &cos_umbra);
		light.SetAngularCutoff(cos_penumbra, cos_umbra);

		// Shadows
		auto shadows = light.UseShadows();
		ImGui::Checkbox("Shadows", &shadows);
		light.SetShadows(shadows);
	}

	static void DrawWidget(TextureTransform &transform) {
		ImGui::Text("Texture Transform:");

		// Translation
		auto translation = transform.GetTranslation();
		ImGui::InputFloat2("Translation", translation.GetData());
		transform.SetTranslation(translation);

		// Rotation Origin
		auto rotation_origin = transform.GetRotationOrigin();
		ImGui::InputFloat2("Rotation Origin", rotation_origin.GetData());
		transform.SetRotationOrigin(rotation_origin);

		// Rotation
		auto rotation = transform.GetRotation();
		ImGui::InputFloat("Rotation", &rotation);
		transform.SetRotation(rotation);

		// Scale
		auto scale = transform.GetScale();
		ImGui::InputFloat2("Scale", scale.GetData());
		transform.SetScale(scale);
	}

	static void DrawWidget(Material &material) {
		ImGui::Text("Material:");

		// Base Color
		ImGui::ColorEdit4("Base Color", material.GetBaseColor().GetData());

		// Base Color Texture
		const auto base_color_guid = material.GetBaseColorTexture()->GetGuid();
		ImGui::Text(str_convert(base_color_guid).c_str());

		// Transparency
		auto transparency = material.IsTransparant();
		ImGui::Checkbox("Transparency", &transparency);
		material.SetTransparent(transparency);

		// Roughness
		auto roughness = material.GetRoughness();
		ImGui::SliderFloat("Roughness", &roughness, 0.0f, 1.0f);
		material.SetRoughness(roughness);

		// Metalness
		auto metalness = material.GetMetalness();
		ImGui::SliderFloat("Metalness", &metalness, 0.0f, 1.0f);
		material.SetMetalness(metalness);

		// Material Texture
		const auto material_guid = material.GetMaterialTexture()->GetGuid();
		ImGui::Text(str_convert(material_guid).c_str());

		// Normal Texture
		if (material.GetNormalTexture()) {
			const auto normal_guid = material.GetNormalTexture()->GetGuid();
			ImGui::LabelText("Normals", str_convert(normal_guid).c_str());
		}

		// Light Interaction
		auto light_interaction = material.InteractsWithLight();
		ImGui::Checkbox("Interacts with Light", &light_interaction);
		material.SetLightInteraction(light_interaction);
	}

	static void DrawWidget(Model &model) {
		// Texture transform
		DrawWidget(model.GetTextureTransform());

		ImGui::Separator();

		// Material
		DrawWidget(model.GetMaterial());

		// Occlusion
		auto light_occlusion = model.OccludesLight();
		ImGui::Checkbox("Occludes Light", &light_occlusion);
		model.SetLightOcclusion(light_occlusion);
	}

	static void DrawWidget(SpriteTransform &transform) {
		ImGui::Text("Sprite Transform:");

		static bool normalization = false;

		// Translation
		if (normalization) {
			auto translation = transform.GetNormalizedTranslation();
			ImGui::InputFloat2("Translation", translation.GetData());
			transform.SetNormalizedTranslation(translation);
		}
		else {
			auto translation = transform.GetTranslation();
			ImGui::InputFloat2("Translation", translation.GetData());
			transform.SetTranslation(translation);
		}

		// Depth
		auto depth = transform.GetDepth();
		ImGui::InputFloat("Depth", &depth);
		transform.SetDepth(depth);

		// Rotation Origin
		if (normalization) {
			auto rotation_origin = transform.GetNormalizedRotationOrigin();
			ImGui::InputFloat2("Rotation Origin", rotation_origin.GetData());
			transform.SetNormalizedRotationOrigin(rotation_origin);
		}
		else {
			auto rotation_origin = transform.GetRotationOrigin();
			ImGui::InputFloat2("Rotation Origin", rotation_origin.GetData());
			transform.SetRotationOrigin(rotation_origin);
		}

		// Rotation
		auto rotation = transform.GetRotation();
		ImGui::InputFloat("Rotation", &rotation);
		transform.SetRotation(rotation);

		// Scale
		auto scale = transform.GetScale();
		ImGui::InputFloat2("Scale", scale.GetData());
		transform.SetScale(scale);

		ImGui::Checkbox("Normalization", &normalization);
	}

	static void DrawWidget(SpriteImage &sprite) {
		// Sprite transform
		DrawWidget(sprite.GetSpriteTransform());

		ImGui::Separator();

		// Base color
		ImGui::ColorEdit4("Base Color", sprite.GetBaseColor().GetData());

		// Base color texture
		const auto base_color_guid = sprite.GetBaseColorTexture()->GetGuid();
		ImGui::LabelText("Base Color Texture", str_convert(base_color_guid).c_str());

		// Sprite effects
		static constexpr const char *sprite_effect_names[] = {
			{ "None"              },
			{ "Flip Horizontally" },
			{ "Flip Vertically"   },
			{ "Flip Both"         }
		};
		static constexpr SpriteEffect sprite_effects[] = {
			{ SpriteEffect::None             },
			{ SpriteEffect::FlipHorizontally },
			{ SpriteEffect::FlipVertically   },
			{ SpriteEffect::FlipBoth         }
		};
		static_assert(std::size(sprite_effect_names) == std::size(sprite_effects));

		auto sprite_effect_index = static_cast< int >(sprite.GetSpriteEffects());
		ImGui::Combo("Sprite Effects", &sprite_effect_index, sprite_effect_names,
			         static_cast<int>(std::size(sprite_effect_names)));
		sprite.SetSpriteEffects(sprite_effects[sprite_effect_index]);
	}
	
	static void DrawWidget(SpriteText &sprite) {
		// Sprite transform
		DrawWidget(sprite.GetSpriteTransform());

		ImGui::Separator();

		// Sprite font
		const auto font_guid = sprite.GetFont()->GetGuid();
		ImGui::LabelText("Font", str_convert(font_guid).c_str());

		// Sprite effects
		static constexpr const char *sprite_effect_names[] = {
			{ "None"              },
			{ "Flip Horizontally" },
			{ "Flip Vertically"   },
			{ "Flip Both"         }
		};
		static constexpr SpriteEffect sprite_effects[] = {
			{ SpriteEffect::None             },
			{ SpriteEffect::FlipHorizontally },
			{ SpriteEffect::FlipVertically   },
			{ SpriteEffect::FlipBoth         }
		};
		static_assert(std::size(sprite_effect_names) == std::size(sprite_effects));

		auto sprite_effect_index = static_cast< int >(sprite.GetSpriteEffects());
		ImGui::Combo("Sprite Effects", &sprite_effect_index, sprite_effect_names,
			         static_cast<int>(std::size(sprite_effect_names)));
		sprite.SetSpriteEffects(sprite_effects[sprite_effect_index]);

		// Text effect color
		ImGui::ColorEdit4("Text Effect Color", sprite.GetTextEffectColor().GetData());

		// Text effects
		static constexpr const char *text_effect_names[] = {
			{ "None"       },
			{ "DropShadow" },
			{ "Outline"    }
		};
		static constexpr SpriteText::TextEffect text_effects[] = {
			{ SpriteText::TextEffect::None       },
			{ SpriteText::TextEffect::DropShadow },
			{ SpriteText::TextEffect::Outline    }
		};
		static_assert(std::size(text_effect_names) == std::size(text_effects));

		auto text_effect_index = static_cast< int >(sprite.GetTextEffect());
		ImGui::Combo("Text Effect", &text_effect_index, text_effect_names,
			         static_cast<int>(std::size(text_effect_names)));
		sprite.SetTextEffect(text_effects[text_effect_index]);
	}

	static void DrawWidget(Transform &transform) {
		// Translation
		if (auto translation = transform.GetTranslation();
			ImGui::InputFloat3("Translation", translation.GetData())) {

			transform.SetTranslation(translation);
		}
		
		// Rotation
		if (auto rotation = transform.GetRotation();
			ImGui::InputFloat3("Rotation", rotation.GetData())) {

			transform.SetRotation(rotation);
		}
		
		// Scale
		if (auto scale = transform.GetScale();
			ImGui::InputFloat3("Scale", scale.GetData())) {

			transform.SetScale(scale);
		}
	}

	static void DrawWidget(Node &node) {
		char buffer[128];
		sprintf_s(buffer, std::size(buffer), "%s", node.GetName().c_str());
		if (ImGui::InputText("", buffer, std::size(buffer))) {
			node.SetName(string(buffer));
		}

		ImGui::SameLine();
		
		if (auto active = (State::Active == node.GetState());
			ImGui::Checkbox("Active", &active)) {
			node.SetState(active ? State::Active : State::Passive);
		}
		
		ImGui::Separator();

		if (ImGui::TreeNode("Transform")) {
			DrawWidget(node.GetTransform());
			ImGui::TreePop();
		}

		node.ForEach< OrthographicCamera >([](OrthographicCamera &camera) {
			if (const auto id = std::to_string(camera.GetGuid());
				ImGui::TreeNode(id.c_str(), "Orthographic Camera")) {
				
				DrawWidget(camera);
				
				ImGui::TreePop();
			}
		});

		node.ForEach< PerspectiveCamera >([](PerspectiveCamera &camera) {
			if (const auto id = std::to_string(camera.GetGuid());
				ImGui::TreeNode(id.c_str(), "Perspective Camera")) {
				
				DrawWidget(camera);
				
				ImGui::TreePop();
			}
		});

		node.ForEach< AmbientLight >([](AmbientLight &light) {
			if (const auto id = std::to_string(light.GetGuid());
				ImGui::TreeNode(id.c_str(), "Ambient Light")) {

				DrawWidget(light);

				ImGui::TreePop();
			}
		});

		node.ForEach< DirectionalLight >([](DirectionalLight &light) {
			if (const auto id = std::to_string(light.GetGuid());
				ImGui::TreeNode(id.c_str(), "Directional Light")) {

				DrawWidget(light);

				ImGui::TreePop();
			}
		});

		node.ForEach< OmniLight >([](OmniLight &light) {
			if (const auto id = std::to_string(light.GetGuid());
				ImGui::TreeNode(id.c_str(), "Omni Light")) {

				DrawWidget(light);

				ImGui::TreePop();
			}
		});

		node.ForEach< SpotLight >([](SpotLight &light) {
			if (const auto id = std::to_string(light.GetGuid());
				ImGui::TreeNode(id.c_str(), "Spotlight")) {

				DrawWidget(light);

				ImGui::TreePop();
			}
		});

		node.ForEach< Model >([](Model &model) {
			if (const auto id = std::to_string(model.GetGuid());
				ImGui::TreeNode(id.c_str(), "Model")) {
				
				DrawWidget(model);

				ImGui::TreePop();
			}
		});

		node.ForEach< SpriteImage >([](SpriteImage &sprite) {
			if (const auto id = std::to_string(sprite.GetGuid());
				ImGui::TreeNode(id.c_str(), "Sprite Image")) {

				DrawWidget(sprite);

				ImGui::TreePop();
			}
		});

		node.ForEach< SpriteText >([](SpriteText &sprite) {
			if (const auto id = std::to_string(sprite.GetGuid());
				ImGui::TreeNode(id.c_str(), "Sprite Text")) {

				DrawWidget(sprite);

				ImGui::TreePop();
			}
		});
	}

	static void DrawGraph(Node &node) {
		const auto id = std::to_string(node.GetGuid());
		const auto &name = node.GetName();
		
		if (node.ContainsChilds()) {
			static constexpr ImGuiTreeNodeFlags node_flags
				= ImGuiTreeNodeFlags_OpenOnArrow
				| ImGuiTreeNodeFlags_OpenOnDoubleClick;
			
			const ImGuiTreeNodeFlags flags = (node.Get() == g_selected)
				? node_flags | ImGuiTreeNodeFlags_Selected : node_flags;

			if (ImGui::TreeNodeEx(id.c_str(), flags, name.c_str())) {

				node.ForEachChild([](Node &child) {
					DrawGraph(child);
				});

				ImGui::TreePop();
			}

			if (ImGui::IsItemClicked()) {
				SetSelected(node.Get());
			}
		}
		else {
			static constexpr ImGuiTreeNodeFlags node_flags
				= ImGuiTreeNodeFlags_OpenOnArrow
				| ImGuiTreeNodeFlags_OpenOnDoubleClick
				| ImGuiTreeNodeFlags_Leaf
				| ImGuiTreeNodeFlags_NoTreePushOnOpen;
			
			const ImGuiTreeNodeFlags flags = (node.Get() == g_selected)
				? node_flags | ImGuiTreeNodeFlags_Selected : node_flags;

			ImGui::TreeNodeEx(id.c_str(), flags, name.c_str());
			if (ImGui::IsItemClicked()) {
				SetSelected(node.Get());
			}
		}
	}

	void DrawGraph(Scene &scene) {
		ImGui::Begin("Scene Graph");
		// Increase spacing to differentiate leaves from expanded contents.
		ImGui::PushStyleVar(ImGuiStyleVar_IndentSpacing, ImGui::GetFontSize() * 3.0f);
		
		scene.ForEach< Node >([](Node &node) {
			if (!node.HasParent()) {
				DrawGraph(node);
			}
		});

		ImGui::PopStyleVar();
		ImGui::End();
	}

	void DrawInspector() {
		ImGui::Begin("Inspector");
		
		if (g_selected && State::Terminated != g_selected->GetState()) {
			DrawWidget(*g_selected);
		}
		
		ImGui::End();
	}
}