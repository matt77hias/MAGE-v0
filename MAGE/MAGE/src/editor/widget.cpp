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
		F32 radius = lens.GetLensRadius();
		ImGui::InputFloat("Radius", &radius);
		lens.SetLensRadius(radius);

		// Focal length
		F32 focal_length = lens.GetFocalLength();
		ImGui::SliderFloat("Focal Length", &focal_length, 
			               clipping_planes.m_x, 
			               clipping_planes.m_y);
		lens.SetFocalLength(focal_length);

		// Maximum radius of the circle-of-confusion
		F32 coc = lens.GetMaximumCoCRadius();
		ImGui::SliderFloat("CoC", &coc, 0.0f, 10.0f);
		lens.SetMaximumCoCRadius(coc);
	}

	static void DrawWidget(Fog &fog) {
		ImGui::Text("Fog:");

		// Base color
		ImGui::ColorEdit3("Base Color", fog.GetBaseColor().GetData());

		// Radiance
		F32 density = fog.GetDensity();
		ImGui::DragFloat("Density", &density, 0.00001f, 0.0f, 1.0f, "%.5f");
		fog.SetDensity(density);
	}

	static void DrawWidget(Sky &sky) {
		ImGui::Text("Sky:");

		const wstring guid = sky.GetTexture()->GetGuid();
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

		int render_mode_index = static_cast< int >(settings.GetRenderMode());
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
		
		int brdf_index = static_cast< int >(settings.GetBRDF());
		ImGui::Combo("BRDF", &brdf_index, brdf_names,
			         static_cast<int>(std::size(brdf_names)));
		settings.SetBRDF(brdfs[brdf_index]);
	
		// Render Layers
		if (ImGui::Button("Render Layers")) {
			ImGui::OpenPopup("Render Layers");
		}
		if (ImGui::BeginPopup("Render Layers")) {
			
			if (bool wireframe = settings.ContainsRenderLayer(RenderLayer::Wireframe);
				ImGui::Checkbox("Wireframe", &wireframe)) {

				settings.ToggleRenderLayer(RenderLayer::Wireframe);
			}

			if (bool aabb = settings.ContainsRenderLayer(RenderLayer::AABB);
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
			F32x2 top_left = viewport.GetNormalizedTopLeft();
			ImGui::InputFloat2("Top Left", top_left.GetData());
			viewport.SetNormalizedTopLeft(top_left);

			// Width and height
			F32x2 resolution = viewport.GetNormalizedWidthAndHeight();
			ImGui::InputFloat2("Resolution", resolution.GetData());
			viewport.SetNormalizedWidthAndHeight(resolution);
		}
		else {
			// Top left
			F32x2 top_left = viewport.GetTopLeft();
			ImGui::InputFloat2("Top Left", top_left.GetData());
			viewport.SetTopLeft(top_left);

			// Width and height
			F32x2 resolution = viewport.GetWidthAndHeight();
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
		F32 width = camera.GetWidth();
		ImGui::InputFloat("Width", &width);
		F32 height = camera.GetHeight();
		ImGui::InputFloat("Height", &height);
		camera.SetWidthAndHeight(width, height);

		// Camera
		DrawWidget(static_cast< Camera & >(camera));
	}
	
	static void DrawWidget(PerspectiveCamera &camera) {
		// Aspect ratio
		F32 aspect_ratio = camera.GetAspectRatio();
		ImGui::InputFloat("Aspect Ratio", &aspect_ratio);
		camera.SetAspectRatio(aspect_ratio);

		// Vertical field-of-view
		F32 fov_y = camera.GetFOVY();
		ImGui::InputFloat("Vertical FOV", &fov_y);
		camera.SetFOVY(fov_y);

		// Camera
		DrawWidget(static_cast< Camera & >(camera));
	}

	static void DrawWidget(AmbientLight &light) {
		// Base color
		ImGui::ColorEdit3("Base Color", light.GetBaseColor().GetData());

		// Radiance
		F32 radiance = light.GetRadiance();
		ImGui::InputFloat("Radiance", &radiance);
		light.SetRadiance(radiance);
	}
	
	static void DrawWidget(DirectionalLight &light) {
		// Base color
		ImGui::ColorEdit3("Base Color", light.GetBaseColor().GetData());

		// Radiance
		F32 radiance = light.GetRadiance();
		ImGui::InputFloat("Radiance", &radiance);
		light.SetRadiance(radiance);
	}
	
	static void DrawWidget(OmniLight &light) {
		// Base color
		ImGui::ColorEdit3("Base Color", light.GetBaseColor().GetData());

		// Intensity
		F32 intensity = light.GetIntensity();
		ImGui::InputFloat("Intensity", &intensity);
		light.SetIntensity(intensity);

		// Power
		F32 power = light.GetPower();
		ImGui::InputFloat("Power", &power);
		light.SetPower(power);

		// Range
		F32 range = light.GetRange();
		ImGui::InputFloat("Range", &range);
		light.SetRange(range);

		// Shadows
		bool shadows = light.UseShadows();
		ImGui::Checkbox("Shadows", &shadows);
		light.SetShadows(shadows);
	}
	
	static void DrawWidget(SpotLight &light) {
		// Base color
		ImGui::ColorEdit3("Base Color", light.GetBaseColor().GetData());

		// Intensity
		F32 intensity = light.GetIntensity();
		ImGui::InputFloat("Intensity", &intensity);
		light.SetIntensity(intensity);

		// Power
		F32 power = light.GetPower();
		ImGui::InputFloat("Power", &power);
		light.SetPower(power);

		// Range
		F32 range = light.GetRange();
		ImGui::InputFloat("Range", &range);
		light.SetRange(range);

		// Cosine penumbra and umbra
		F32 cos_penumbra = light.GetStartAngularCutoff();
		ImGui::InputFloat("Cosine penumbra", &cos_penumbra);
		F32 cos_umbra = light.GetEndAngularCutoff();
		ImGui::InputFloat("Cosine umbra", &cos_umbra);
		light.SetAngularCutoff(cos_penumbra, cos_umbra);

		// Shadows
		bool shadows = light.UseShadows();
		ImGui::Checkbox("Shadows", &shadows);
		light.SetShadows(shadows);
	}

	static void DrawWidget(TextureTransform &transform) {
		ImGui::Text("Texture Transform:");

		// Translation
		F32x2 translation = transform.GetTranslation();
		ImGui::InputFloat2("Translation", translation.GetData());
		transform.SetTranslation(translation);

		// Rotation Origin
		F32x2 rotation_origin = transform.GetRotationOrigin();
		ImGui::InputFloat2("Rotation Origin", rotation_origin.GetData());
		transform.SetRotationOrigin(rotation_origin);

		// Rotation
		F32 rotation = transform.GetRotation();
		ImGui::InputFloat("Rotation", &rotation);
		transform.SetRotation(rotation);

		// Scale
		F32x2 scale = transform.GetScale();
		ImGui::InputFloat2("Scale", scale.GetData());
		transform.SetScale(scale);
	}

	static void DrawWidget(Material &material) {
		ImGui::Text("Material:");

		// Base Color
		ImGui::ColorEdit4("Base Color", material.GetBaseColor().GetData());

		// Base Color Texture
		const wstring base_color_guid = material.GetBaseColorTexture()->GetGuid();
		ImGui::Text(str_convert(base_color_guid).c_str());

		// Transparency
		bool transparency = material.IsTransparant();
		ImGui::Checkbox("Transparency", &transparency);
		material.SetTransparent(transparency);

		// Roughness
		F32 roughness = material.GetRoughness();
		ImGui::SliderFloat("Roughness", &roughness, 0.0f, 1.0f);
		material.SetRoughness(roughness);

		// Metalness
		F32 metalness = material.GetMetalness();
		ImGui::SliderFloat("Metalness", &metalness, 0.0f, 1.0f);
		material.SetMetalness(metalness);

		// Material Texture
		const wstring material_guid = material.GetMaterialTexture()->GetGuid();
		ImGui::Text(str_convert(material_guid).c_str());

		// Normal Texture
		if (material.GetNormalTexture()) {
			const wstring normal_guid = material.GetNormalTexture()->GetGuid();
			ImGui::LabelText("Normals", str_convert(normal_guid).c_str());
		}

		// Light Interaction
		bool light_interaction = material.InteractsWithLight();
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
		bool light_occlusion = model.OccludesLight();
		ImGui::Checkbox("Occludes Light", &light_occlusion);
		model.SetLightOcclusion(light_occlusion);
	}

	static void DrawWidget(SpriteTransform &transform) {
		ImGui::Text("Sprite Transform:");

		static bool normalization = false;

		// Translation
		if (normalization) {
			F32x2 translation = transform.GetNormalizedTranslation();
			ImGui::InputFloat2("Translation", translation.GetData());
			transform.SetNormalizedTranslation(translation);
		}
		else {
			F32x2 translation = transform.GetTranslation();
			ImGui::InputFloat2("Translation", translation.GetData());
			transform.SetTranslation(translation);
		}

		// Depth
		F32 depth = transform.GetDepth();
		ImGui::InputFloat("Depth", &depth);
		transform.SetDepth(depth);

		// Rotation Origin
		if (normalization) {
			F32x2 rotation_origin = transform.GetNormalizedRotationOrigin();
			ImGui::InputFloat2("Rotation Origin", rotation_origin.GetData());
			transform.SetNormalizedRotationOrigin(rotation_origin);
		}
		else {
			F32x2 rotation_origin = transform.GetRotationOrigin();
			ImGui::InputFloat2("Rotation Origin", rotation_origin.GetData());
			transform.SetRotationOrigin(rotation_origin);
		}

		// Rotation
		F32 rotation = transform.GetRotation();
		ImGui::InputFloat("Rotation", &rotation);
		transform.SetRotation(rotation);

		// Scale
		F32x2 scale = transform.GetScale();
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
		const wstring base_color_guid = sprite.GetBaseColorTexture()->GetGuid();
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

		int sprite_effect_index = static_cast< int >(sprite.GetSpriteEffects());
		ImGui::Combo("Sprite Effects", &sprite_effect_index, sprite_effect_names,
			         static_cast<int>(std::size(sprite_effect_names)));
		sprite.SetSpriteEffects(sprite_effects[sprite_effect_index]);
	}
	
	static void DrawWidget(SpriteText &sprite) {
		// Sprite transform
		DrawWidget(sprite.GetSpriteTransform());

		ImGui::Separator();

		// Sprite font
		const wstring font_guid = sprite.GetFont()->GetGuid();
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

		int sprite_effect_index = static_cast< int >(sprite.GetSpriteEffects());
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

		int text_effect_index = static_cast< int >(sprite.GetTextEffect());
		ImGui::Combo("Text Effect", &text_effect_index, text_effect_names,
			         static_cast<int>(std::size(text_effect_names)));
		sprite.SetTextEffect(text_effects[text_effect_index]);
	}

	static void DrawWidget(Transform &transform) {
		// Translation
		if (F32x3 translation = transform.GetTranslation(); 
			ImGui::InputFloat3("Translation", translation.GetData())) {

			transform.SetTranslation(translation);
		}
		
		// Rotation
		if (F32x3 rotation = transform.GetRotation(); 
			ImGui::InputFloat3("Rotation", rotation.GetData())) {

			transform.SetRotation(rotation);
		}
		
		// Scale
		if (F32x3 scale = transform.GetScale(); 
			ImGui::InputFloat3("Scale", scale.GetData())) {

			transform.SetScale(scale);
		}
	}

	static void DrawWidget(Node &node) {
		static char buffer[128];
		sprintf_s(buffer, std::size(buffer), "%s", node.GetName().c_str());
		if (ImGui::InputText("", buffer, std::size(buffer))) {
			node.SetName(string(buffer));
		}

		ImGui::SameLine();
		
		if (bool active = (State::Active == node.GetState());
			ImGui::Checkbox("Active", &active)) {
			node.SetState(active ? State::Active : State::Passive);
		}
		
		ImGui::Separator();

		if (ImGui::TreeNode("Transform")) {
			DrawWidget(node.GetTransform());
			ImGui::TreePop();
		}

		node.ForEach< OrthographicCamera >([](OrthographicCamera &camera) {
			if (const string id = std::to_string(camera.GetGuid()); 
				ImGui::TreeNode(id.c_str(), "Orthographic Camera")) {
				
				DrawWidget(camera);
				
				ImGui::TreePop();
			}
		});

		node.ForEach< PerspectiveCamera >([](PerspectiveCamera &camera) {
			if (const string id = std::to_string(camera.GetGuid()); 
				ImGui::TreeNode(id.c_str(), "Perspective Camera")) {
				
				DrawWidget(camera);
				
				ImGui::TreePop();
			}
		});

		node.ForEach< AmbientLight >([](AmbientLight &light) {
			if (const string id = std::to_string(light.GetGuid()); 
				ImGui::TreeNode(id.c_str(), "Ambient Light")) {

				DrawWidget(light);

				ImGui::TreePop();
			}
		});

		node.ForEach< DirectionalLight >([](DirectionalLight &light) {
			if (const string id = std::to_string(light.GetGuid()); 
				ImGui::TreeNode(id.c_str(), "Directional Light")) {

				DrawWidget(light);

				ImGui::TreePop();
			}
		});

		node.ForEach< OmniLight >([](OmniLight &light) {
			if (const string id = std::to_string(light.GetGuid()); 
				ImGui::TreeNode(id.c_str(), "Omni Light")) {

				DrawWidget(light);

				ImGui::TreePop();
			}
		});

		node.ForEach< SpotLight >([](SpotLight &light) {
			if (const string id = std::to_string(light.GetGuid()); 
				ImGui::TreeNode(id.c_str(), "Spotlight")) {

				DrawWidget(light);

				ImGui::TreePop();
			}
		});

		node.ForEach< Model >([](Model &model) {
			if (const string id = std::to_string(model.GetGuid());
				ImGui::TreeNode(id.c_str(), "Model")) {
				
				DrawWidget(model);

				ImGui::TreePop();
			}
		});

		node.ForEach< SpriteImage >([](SpriteImage &sprite) {
			if (const string id = std::to_string(sprite.GetGuid());
				ImGui::TreeNode(id.c_str(), "Sprite Image")) {

				DrawWidget(sprite);

				ImGui::TreePop();
			}
		});

		node.ForEach< SpriteText >([](SpriteText &sprite) {
			if (const string id = std::to_string(sprite.GetGuid());
				ImGui::TreeNode(id.c_str(), "Sprite Text")) {

				DrawWidget(sprite);

				ImGui::TreePop();
			}
		});
	}

	static void DrawGraph(Node &node) {
		const string id = std::to_string(node.GetGuid());
		const string &name = node.GetName();
		
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