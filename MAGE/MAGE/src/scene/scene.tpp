#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "utils\logging\error.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	//-------------------------------------------------------------------------
	// Scene: Creation
	//-------------------------------------------------------------------------
	#pragma region

	template< typename ElementT, typename... ConstructorArgsT >
	ProxyPtr< ElementT > Scene::AddElement(std::vector< ElementT > &elements,
		ConstructorArgsT&&... args) {
		
		size_t index = 0;
		for (auto &element : elements) {
			if (State::Terminated == element.GetState()) {
				element = ElementT(std::forward< ConstructorArgsT >(args)...);
				element.Set(ProxyPtr< ElementT >(elements, index));
				return ProxyPtr< ElementT >(elements, index);
			}
			++index;
		}

		elements.emplace_back(std::forward< ConstructorArgsT >(args)...);
		elements.end()->Set(ProxyPtr< ElementT >(elements, index));
		return ProxyPtr< ElementT >(elements, index);
	}

	template< typename ElementT, typename BaseT, typename... ConstructorArgsT >
	ProxyPtr< ElementT > Scene::AddElement(
		std::vector< UniquePtr< BaseT > > &elements, ConstructorArgsT&&... args) {

		size_t index = 0;
		for (auto &element : elements) {
			if (State::Terminated == element->GetState()) {
				element = MakeUnique< ElementT >(
					std::forward< ConstructorArgsT >(args)...);
				element->Set(ProxyPtr< ElementT >(
					[&elements, index]() noexcept {
					return elements[index].get();
				}
				));

				return ProxyPtr< ElementT >(
					[&elements, index]() noexcept {
					return elements[index].get();
				}
				);
			}

			++index;
		}

		m_scripts.emplace_back(MakeUnique< ElementT >(
			std::forward< ConstructorArgsT >(args)...));
		(*elements.end())->Set(ProxyPtr< ElementT >(
			[&elements, index]() noexcept {
			return elements[index].get();
		}
		));

		return ProxyPtr< ElementT >(
			[&elements, index]() noexcept {
			return elements[index].get();
		}
		);

	}

	template< typename ElementT, typename... ConstructorArgsT >
	inline ProxyPtr< ElementT > Scene::Create(ConstructorArgsT&&... args) {
		
		if constexpr (std::is_same_v< Node, ElementT >) {
			return AddElement(m_nodes, 
				std::forward< ConstructorArgsT >(args)...);
		}
		
		if constexpr (std::is_same_v< PerspectiveCamera, ElementT >) {
			return AddElement(m_perspective_cameras,
				std::forward< ConstructorArgsT >(args)...);
		}

		if constexpr (std::is_same_v< OrthographicCamera, ElementT >) {
			return AddElement(m_orthographic_cameras,
				std::forward< ConstructorArgsT >(args)...);
		}

		if constexpr (std::is_same_v< AmbientLight, ElementT >) {
			return AddElement(m_ambient_lights,
				std::forward< ConstructorArgsT >(args)...);
		}

		if constexpr (std::is_same_v< DirectionalLight, ElementT >) {
			return AddElement(m_directional_lights,
				std::forward< ConstructorArgsT >(args)...);
		}

		if constexpr (std::is_same_v< OmniLight, ElementT >) {
			return AddElement(m_omni_lights,
				std::forward< ConstructorArgsT >(args)...);
		}

		if constexpr (std::is_same_v< SpotLight, ElementT >) {
			return AddElement(m_spot_lights,
				std::forward< ConstructorArgsT >(args)...);
		}

		if constexpr (std::is_same_v< Model, ElementT >) {
			return AddElement(m_models,
				std::forward< ConstructorArgsT >(args)...);
		}

		if constexpr (std::is_same_v< SpriteImage, ElementT >) {
			return AddElement(m_sprite_images,
				std::forward< ConstructorArgsT >(args)...);
		}

		if constexpr (std::is_same_v< SpriteText, ElementT >) {
			return AddElement(m_sprite_texts,
				std::forward< ConstructorArgsT >(args)...);
		}

		if constexpr (std::is_base_of_v< BehaviorScript, ElementT >) {
			return AddElement(m_scripts,
				std::forward< ConstructorArgsT >(args)...);
		}
	}

	#pragma endregion

	//-------------------------------------------------------------------------
	// Scene: Retrieval
	//-------------------------------------------------------------------------
	#pragma region

	template<>
	inline Node &Scene::Get(size_t index) noexcept {
		Assert(index < m_nodes.size());
		return m_nodes[index];
	}

	template<>
	inline PerspectiveCamera &Scene::Get(size_t index) noexcept {
		Assert(index < m_perspective_cameras.size());
		return m_perspective_cameras[index];
	}

	template<>
	inline OrthographicCamera &Scene::Get(size_t index) noexcept {
		Assert(index < m_orthographic_cameras.size());
		return m_orthographic_cameras[index];
	}

	template<>
	inline AmbientLight &Scene::Get(size_t index) noexcept {
		Assert(index < m_ambient_lights.size());
		return m_ambient_lights[index];
	}

	template<>
	inline DirectionalLight &Scene::Get(size_t index) noexcept {
		Assert(index < m_directional_lights.size());
		return m_directional_lights[index];
	}

	template<>
	inline OmniLight &Scene::Get(size_t index) noexcept {
		Assert(index < m_omni_lights.size());
		return m_omni_lights[index];
	}

	template<>
	inline SpotLight &Scene::Get(size_t index) noexcept {
		Assert(index < m_spot_lights.size());
		return m_spot_lights[index];
	}

	template<>
	inline Model &Scene::Get(size_t index) noexcept {
		Assert(index < m_models.size());
		return m_models[index];
	}

	template<>
	inline SpriteImage &Scene::Get(size_t index) noexcept {
		Assert(index < m_sprite_images.size());
		return m_sprite_images[index];
	}
	
	template<>
	inline SpriteText &Scene::Get(size_t index) noexcept {
		Assert(index < m_sprite_texts.size());
		return m_sprite_texts[index];
	}

	template<>
	inline const Node &Scene::Get(size_t index) const noexcept {
		Assert(index < m_nodes.size());
		return m_nodes[index];
	}

	template<>
	inline const PerspectiveCamera &Scene::Get(size_t index) const noexcept {
		Assert(index < m_perspective_cameras.size());
		return m_perspective_cameras[index];
	}

	template<>
	inline const OrthographicCamera &Scene::Get(size_t index) const noexcept {
		Assert(index < m_orthographic_cameras.size());
		return m_orthographic_cameras[index];
	}

	template<>
	inline const AmbientLight &Scene::Get(size_t index) const noexcept {
		Assert(index < m_ambient_lights.size());
		return m_ambient_lights[index];
	}

	template<>
	inline const DirectionalLight &Scene::Get(size_t index) const noexcept {
		Assert(index < m_directional_lights.size());
		return m_directional_lights[index];
	}

	template<>
	inline const OmniLight &Scene::Get(size_t index) const noexcept {
		Assert(index < m_omni_lights.size());
		return m_omni_lights[index];
	}

	template<>
	inline const SpotLight &Scene::Get(size_t index) const noexcept {
		Assert(index < m_spot_lights.size());
		return m_spot_lights[index];
	}

	template<>
	inline const Model &Scene::Get(size_t index) const noexcept {
		Assert(index < m_models.size());
		return m_models[index];
	}

	template<>
	inline const SpriteImage &Scene::Get(size_t index) const noexcept {
		Assert(index < m_sprite_images.size());
		return m_sprite_images[index];
	}

	template<>
	inline const SpriteText &Scene::Get(size_t index) const noexcept {
		Assert(index < m_sprite_texts.size());
		return m_sprite_texts[index];
	}

	template<>
	inline const BehaviorScript &Scene::Get(size_t index) const noexcept {
		Assert(index < m_scripts.size());
		return *m_scripts[index].get();
	}

	#pragma endregion

	//-------------------------------------------------------------------------
	// Scene: Count
	//-------------------------------------------------------------------------
	#pragma region

	template<>
	inline size_t Scene::GetNumberOf< Node >() const noexcept {
		return m_nodes.size();
	}
	
	template<>
	inline size_t Scene::GetNumberOf< PerspectiveCamera >() const noexcept {
		return m_perspective_cameras.size();
	}
	
	template<>
	inline size_t Scene::GetNumberOf< OrthographicCamera >() const noexcept {
		return m_orthographic_cameras.size();
	}

	template<>
	inline size_t Scene::GetNumberOf< Camera >() const noexcept {
		return GetNumberOf< PerspectiveCamera >() 
			 + GetNumberOf< OrthographicCamera >();
	}

	template<>
	inline size_t Scene::GetNumberOf< AmbientLight >() const noexcept {
		return m_ambient_lights.size();
	}

	template<>
	inline size_t Scene::GetNumberOf< DirectionalLight >() const noexcept {
		return m_directional_lights.size();
	}

	template<>
	inline size_t Scene::GetNumberOf< OmniLight >() const noexcept {
		return m_omni_lights.size();
	}

	template<>
	inline size_t Scene::GetNumberOf< SpotLight >() const noexcept {
		return m_spot_lights.size();
	}

	template<>
	inline size_t Scene::GetNumberOf< Light >() const noexcept {
		return GetNumberOf< AmbientLight >()
			 + GetNumberOf< DirectionalLight >()
			 + GetNumberOf< OmniLight >()
			 + GetNumberOf< SpotLight >();
	}

	template<>
	inline size_t Scene::GetNumberOf< Model >() const noexcept {
		return m_models.size();
	}

	template<>
	inline size_t Scene::GetNumberOf< SpriteImage >() const noexcept {
		return m_sprite_images.size();
	}

	template<>
	inline size_t Scene::GetNumberOf< SpriteText >() const noexcept {
		return m_sprite_texts.size();
	}

	template<>
	inline size_t Scene::GetNumberOf< Sprite >() const noexcept {
		return GetNumberOf< SpriteImage >()
			 + GetNumberOf< SpriteText >();
	}

	template<>
	inline size_t Scene::GetNumberOf< BehaviorScript >() const noexcept {
		return m_scripts.size();
	}

	template<>
	inline size_t Scene::GetNumberOf< Component >() const noexcept {
		return GetNumberOf< Camera >() 
			 + GetNumberOf< Light >()
			 + GetNumberOf< Model >()
			 + GetNumberOf< Sprite >()
			 + GetNumberOf< BehaviorScript >();
	}

	#pragma endregion

	//-------------------------------------------------------------------------
	// Scene: Iteration
	//-------------------------------------------------------------------------
	#pragma region

	template< typename ElementT, typename ActionT >
	inline void Scene::ForEach(ActionT action) {

		if constexpr (std::is_same_v< Node, ElementT >) {
			for (auto &element : m_nodes) {
				action(element);
			}
		}

		if constexpr (std::is_same_v< PerspectiveCamera, ElementT >) {
			for (auto &element : m_perspective_cameras) {
				action(element);
			}
		}

		if constexpr (std::is_same_v< OrthographicCamera, ElementT >) {
			for (auto &element : m_orthographic_cameras) {
				action(element);
			}
		}

		if constexpr (std::is_same_v< Camera, ElementT >) {
			ForEach< PerspectiveCamera >(action);
			ForEach< OrthographicCamera >(action);
		}

		if constexpr (std::is_same_v< AmbientLight, ElementT >) {
			for (auto &element : m_ambient_lights) {
				action(element);
			}
		}

		if constexpr (std::is_same_v< DirectionalLight, ElementT >) {
			for (auto &element : m_directional_lights) {
				action(element);
			}
		}

		if constexpr (std::is_same_v< OmniLight, ElementT >) {
			for (auto &element : m_omni_lights) {
				action(element);
			}
		}

		if constexpr (std::is_same_v< SpotLight, ElementT >) {
			for (auto &element : m_spot_lights) {
				action(element);
			}
		}

		if constexpr (std::is_same_v< Light, ElementT >) {
			ForEach< AmbientLight >(action);
			ForEach< DirectionalLight >(action);
			ForEach< OmniLight >(action);
			ForEach< SpotLight >(action);
		}

		if constexpr (std::is_same_v< Model, ElementT >) {
			for (auto &element : m_models) {
				action(element);
			}
		}

		if constexpr (std::is_same_v< SpriteImage, ElementT >) {
			for (auto &element : m_sprite_images) {
				action(element);
			}
		}

		if constexpr (std::is_same_v< SpriteText, ElementT >) {
			for (auto &element : m_sprite_texts) {
				action(element);
			}
		}

		if constexpr (std::is_same_v< Sprite, ElementT >) {
			ForEach< SpriteImage >(action);
			ForEach< SpriteText >(action);
		}

		if constexpr (std::is_same_v< BehaviorScript, ElementT >) {
			for (auto &element : m_scripts) {
				action(*element);
			}
		}

		if constexpr (std::is_same_v< Component, ElementT >) {
			ForEach< Camera >(ActionT action);
			ForEach< Light >(ActionT action);
			ForEach< Model >(ActionT action);
			ForEach< Sprite >(ActionT action);
			ForEach< BehaviorScript >(ActionT action);
		}
	}

	template< typename ElementT, typename ActionT >
	inline void Scene::ForEach(ActionT action) const {

		if constexpr (std::is_same_v< Node, ElementT >) {
			for (const auto &element : m_nodes) {
				action(element);
			}
		}

		if constexpr (std::is_same_v< PerspectiveCamera, ElementT >) {
			for (const auto &element : m_perspective_cameras) {
				action(element);
			}
		}

		if constexpr (std::is_same_v< OrthographicCamera, ElementT >) {
			for (const auto &element : m_orthographic_cameras) {
				action(element);
			}
		}

		if constexpr (std::is_same_v< Camera, ElementT >) {
			ForEach< PerspectiveCamera >(action);
			ForEach< OrthographicCamera >(action);
		}

		if constexpr (std::is_same_v< AmbientLight, ElementT >) {
			for (const auto &element : m_ambient_lights) {
				action(element);
			}
		}

		if constexpr (std::is_same_v< DirectionalLight, ElementT >) {
			for (const auto &element : m_directional_lights) {
				action(element);
			}
		}

		if constexpr (std::is_same_v< OmniLight, ElementT >) {
			for (const auto &element : m_omni_lights) {
				action(element);
			}
		}

		if constexpr (std::is_same_v< SpotLight, ElementT >) {
			for (const auto &element : m_spot_lights) {
				action(element);
			}
		}

		if constexpr (std::is_same_v< Light, ElementT >) {
			ForEach< AmbientLight >(action);
			ForEach< DirectionalLight >(action);
			ForEach< OmniLight >(action);
			ForEach< SpotLight >(action);
		}

		if constexpr (std::is_same_v< Model, ElementT >) {
			for (const auto &element : m_models) {
				action(element);
			}
		}

		if constexpr (std::is_same_v< SpriteImage, ElementT >) {
			for (const auto &element : m_sprite_images) {
				action(element);
			}
		}

		if constexpr (std::is_same_v< SpriteText, ElementT >) {
			for (const auto &element : m_sprite_texts) {
				action(element);
			}
		}

		if constexpr (std::is_same_v< Sprite, ElementT >) {
			ForEach< SpriteImage >(action);
			ForEach< SpriteText >(action);
		}

		if constexpr (std::is_same_v< BehaviorScript, ElementT >) {
			for (const auto &element : m_scripts) {
				action(static_cast< const BehaviorScript & >(*element));
			}
		}

		if constexpr (std::is_same_v< Component, ElementT >) {
			ForEach< Camera >(ActionT action);
			ForEach< Light >(ActionT action);
			ForEach< Model >(ActionT action);
			ForEach< Sprite >(ActionT action);
			ForEach< BehaviorScript >(ActionT action);
		}
	}

	#pragma endregion
}