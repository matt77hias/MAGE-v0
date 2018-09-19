#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "scene\scene_utils.hpp"
#include "resource\font\sprite_font_factory.hpp"
#include "resource\model\material_factory.hpp"
#include "resource\texture\texture_factory.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage::rendering {

	//-------------------------------------------------------------------------
	// World: Creation
	//-------------------------------------------------------------------------
	#pragma region

	template<>
	inline ProxyPtr< PerspectiveCamera > World::Create() {
		const auto ptr = AddElement(m_perspective_cameras, m_device);

		const auto resolution 
			= m_display_configuration.get().GetDisplayResolution();
		ptr->SetAspectRatio(static_cast< F32 >(resolution[0]), 
							static_cast< F32 >(resolution[1]));
		ptr->GetViewport() = Viewport(resolution);

		return ptr;
	}

	template<>
	inline ProxyPtr< OrthographicCamera > World::Create() {
		const auto ptr = AddElement(m_orthographic_cameras, m_device);

		const auto resolution
			= m_display_configuration.get().GetDisplayResolution();
		ptr->GetViewport() = Viewport(resolution);

		return ptr;
	}

	template<>
	inline ProxyPtr< AmbientLight > World::Create() {
		return AddElement(m_ambient_lights);
	}

	template<>
	inline ProxyPtr< DirectionalLight > World::Create() {
		return AddElement(m_directional_lights);
	}

	template<>
	inline ProxyPtr< OmniLight > World::Create() {
		return AddElement(m_omni_lights);
	}

	template<>
	inline ProxyPtr< SpotLight > World::Create() {
		return AddElement(m_spot_lights);
	}

	template<>
	inline ProxyPtr< Model > World::Create() {
		return AddElement(m_models, m_device);
	}

	template<>
	inline ProxyPtr< SpriteImage > World::Create() {
		const auto ptr = AddElement(m_sprite_images);

		ptr->SetBaseColorTexture(CreateWhiteTexture(m_resource_manager));
		
		return ptr;
	}

	template<>
	inline ProxyPtr< SpriteText > World::Create() {
		const auto ptr = AddElement(m_sprite_texts);
		
		ptr->SetFont(CreateConsolasFont(m_resource_manager));
		
		return ptr;
	}

	#pragma endregion

	//-------------------------------------------------------------------------
	// Scene: Count
	//-------------------------------------------------------------------------
	#pragma region

	template< typename ElementT >
	[[nodiscard]]
	inline std::size_t World::GetNumberOf() const noexcept {
		std::size_t count = 0u;
		ForEach< ElementT >([&count](
			[[maybe_unused]] const ElementT& element) noexcept {
				++count;
			}
		);
		
		return count;
	}
	
	#pragma endregion

	//-------------------------------------------------------------------------
	// Scene: Iteration
	//-------------------------------------------------------------------------
	#pragma region

	template< typename ComponentT, typename ActionT >
	void World::ForEach(ActionT&& action) {

		if constexpr (std::is_same_v< PerspectiveCamera, ComponentT >) {
			for (auto& component : m_perspective_cameras) {
				if (State::Terminated != component.GetState()) {
					action(component);
				}
			}
		}

		if constexpr (std::is_same_v< OrthographicCamera, ComponentT >) {
			for (auto& component : m_orthographic_cameras) {
				if (State::Terminated != component.GetState()) {
					action(component);
				}
			}
		}

		if constexpr (std::is_same_v< Camera, ComponentT >) {
			ForEach< PerspectiveCamera >(action);
			ForEach< OrthographicCamera >(action);
		}

		if constexpr (std::is_same_v< AmbientLight, ComponentT >) {
			for (auto& component : m_ambient_lights) {
				if (State::Terminated != component.GetState()) {
					action(component);
				}
			}
		}

		if constexpr (std::is_same_v< DirectionalLight, ComponentT >) {
			for (auto& component : m_directional_lights) {
				if (State::Terminated != component.GetState()) {
					action(component);
				}
			}
		}

		if constexpr (std::is_same_v< OmniLight, ComponentT >) {
			for (auto& component : m_omni_lights) {
				if (State::Terminated != component.GetState()) {
					action(component);
				}
			}
		}

		if constexpr (std::is_same_v< SpotLight, ComponentT >) {
			for (auto& component : m_spot_lights) {
				if (State::Terminated != component.GetState()) {
					action(component);
				}
			}
		}

		if constexpr (std::is_same_v< Model, ComponentT >) {
			for (auto& component : m_models) {
				if (State::Terminated != component.GetState()) {
					action(component);
				}
			}
		}

		if constexpr (std::is_same_v< SpriteImage, ComponentT >) {
			for (auto& component : m_sprite_images) {
				if (State::Terminated != component.GetState()) {
					action(component);
				}
			}
		}

		if constexpr (std::is_same_v< SpriteText, ComponentT >) {
			for (auto& component : m_sprite_texts) {
				if (State::Terminated != component.GetState()) {
					action(component);
				}
			}
		}

		if constexpr (std::is_same_v< Component, ComponentT >) {
			ForEach< Camera >(action);
			ForEach< AmbientLight >(action);
			ForEach< DirectionalLight >(action);
			ForEach< OmniLight >(action);
			ForEach< SpotLight >(action);
			ForEach< Model >(action);
			ForEach< SpriteImage >(action);
			ForEach< SpriteText >(action);
		}
	}

	template< typename ComponentT, typename ActionT >
	void World::ForEach(ActionT&& action) const {

		if constexpr (std::is_same_v< PerspectiveCamera, ComponentT >) {
			for (const auto& component : m_perspective_cameras) {
				if (State::Terminated != component.GetState()) {
					action(component);
				}
			}
		}

		if constexpr (std::is_same_v< OrthographicCamera, ComponentT >) {
			for (const auto& component : m_orthographic_cameras) {
				if (State::Terminated != component.GetState()) {
					action(component);
				}
			}
		}

		if constexpr (std::is_same_v< Camera, ComponentT >) {
			ForEach< PerspectiveCamera >(action);
			ForEach< OrthographicCamera >(action);
		}

		if constexpr (std::is_same_v< AmbientLight, ComponentT >) {
			for (const auto& component : m_ambient_lights) {
				if (State::Terminated != component.GetState()) {
					action(component);
				}
			}
		}

		if constexpr (std::is_same_v< DirectionalLight, ComponentT >) {
			for (const auto& component : m_directional_lights) {
				if (State::Terminated != component.GetState()) {
					action(component);
				}
			}
		}

		if constexpr (std::is_same_v< OmniLight, ComponentT >) {
			for (const auto& component : m_omni_lights) {
				if (State::Terminated != component.GetState()) {
					action(component);
				}
			}
		}

		if constexpr (std::is_same_v< SpotLight, ComponentT >) {
			for (const auto& component : m_spot_lights) {
				if (State::Terminated != component.GetState()) {
					action(component);
				}
			}
		}

		if constexpr (std::is_same_v< Model, ComponentT >) {
			for (const auto& component : m_models) {
				if (State::Terminated != component.GetState()) {
					action(component);
				}
			}
		}

		if constexpr (std::is_same_v< SpriteImage, ComponentT >) {
			for (const auto& component : m_sprite_images) {
				if (State::Terminated != component.GetState()) {
					action(component);
				}
			}
		}

		if constexpr (std::is_same_v< SpriteText, ComponentT >) {
			for (const auto& component : m_sprite_texts) {
				if (State::Terminated != component.GetState()) {
					action(component);
				}
			}
		}

		if constexpr (std::is_same_v< Component, ComponentT >) {
			ForEach< Camera >(action);
			ForEach< AmbientLight >(action);
			ForEach< DirectionalLight >(action);
			ForEach< OmniLight >(action);
			ForEach< SpotLight >(action);
			ForEach< Model >(action);
			ForEach< SpriteImage >(action);
			ForEach< SpriteText >(action);
		}
	}

	#pragma endregion
}