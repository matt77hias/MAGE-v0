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
				return ProxyPtr< ElementT >(elements, index);
			}
			++index;
		}

		elements.emplace_back(std::forward< ConstructorArgsT >(args)...);
		return ProxyPtr< ElementT >(elements, index);
	}

	template< typename ElementT, typename BaseT, typename... ConstructorArgsT >
	ProxyPtr< ElementT > Scene::AddElementPtr(
		std::vector< UniquePtr< BaseT > > &elements, ConstructorArgsT&&... args) {

		size_t index = 0;
		for (auto &element : elements) {
			if (State::Terminated == element->GetState()) {
				element = MakeUnique< ElementT >(
					std::forward< ConstructorArgsT >(args)...);
				return ProxyPtr< ElementT >(
					[&elements, index]() noexcept {
						return static_cast< ElementT * >(elements[index].get());
					}
				);
			}

			++index;
		}

		elements.push_back(MakeUnique< ElementT >(
			std::forward< ConstructorArgsT >(args)...));
		return ProxyPtr< ElementT >(
			[&elements, index]() noexcept {
				return static_cast< ElementT * >(elements[index].get());
			}
		);
	}

	template< typename ElementT, typename... ConstructorArgsT >
	inline typename std::enable_if_t< std::is_same_v< Node, ElementT >,
		ProxyPtr< ElementT > > Scene::Create(ConstructorArgsT&&... args) {

		auto ptr = AddElement(m_nodes, std::forward< ConstructorArgsT >(args)...);
		ptr->Set(ptr);
		return ptr;
	}

	template< typename ElementT, typename... ConstructorArgsT >
	inline typename std::enable_if_t< std::is_same_v< PerspectiveCamera, ElementT >,
		ProxyPtr< ElementT > > Scene::Create(ConstructorArgsT&&... args) {

		return AddElement(m_perspective_cameras, 
			std::forward< ConstructorArgsT >(args)...);
	}

	template< typename ElementT, typename... ConstructorArgsT >
	inline typename std::enable_if_t< std::is_same_v< OrthographicCamera, ElementT >,
		ProxyPtr< ElementT > > Scene::Create(ConstructorArgsT&&... args) {

		return AddElement(m_orthographic_cameras,
			std::forward< ConstructorArgsT >(args)...);
	}

	template< typename ElementT, typename... ConstructorArgsT >
	inline typename std::enable_if_t< std::is_same_v< AmbientLight, ElementT >,
		ProxyPtr< ElementT > > Scene::Create(ConstructorArgsT&&... args) {

		return AddElement(m_ambient_lights,
			std::forward< ConstructorArgsT >(args)...);
	}

	template< typename ElementT, typename... ConstructorArgsT >
	inline typename std::enable_if_t< std::is_same_v< DirectionalLight, ElementT >,
		ProxyPtr< ElementT > > Scene::Create(ConstructorArgsT&&... args) {

		return AddElement(m_directional_lights,
			std::forward< ConstructorArgsT >(args)...);
	}

	template< typename ElementT, typename... ConstructorArgsT >
	inline typename std::enable_if_t< std::is_same_v< OmniLight, ElementT >,
		ProxyPtr< ElementT > > Scene::Create(ConstructorArgsT&&... args) {

		return AddElement(m_omni_lights,
			std::forward< ConstructorArgsT >(args)...);
	}

	template< typename ElementT, typename... ConstructorArgsT >
	inline typename std::enable_if_t< std::is_same_v< SpotLight, ElementT >,
		ProxyPtr< ElementT > > Scene::Create(ConstructorArgsT&&... args) {

		return AddElement(m_spot_lights,
			std::forward< ConstructorArgsT >(args)...);
	}

	template< typename ElementT, typename... ConstructorArgsT >
	inline typename std::enable_if_t< std::is_same_v< Model, ElementT >,
		ProxyPtr< ElementT > > Scene::Create(ConstructorArgsT&&... args) {

		return AddElement(m_models,
			std::forward< ConstructorArgsT >(args)...);
	}

	template< typename ElementT, typename... ConstructorArgsT >
	inline typename std::enable_if_t< std::is_same_v< SpriteImage, ElementT >,
		ProxyPtr< ElementT > > Scene::Create(ConstructorArgsT&&... args) {

		return AddElement(m_sprite_images,
			std::forward< ConstructorArgsT >(args)...);
	}

	template< typename ElementT, typename... ConstructorArgsT >
	inline typename std::enable_if_t< std::is_same_v< SpriteText, ElementT >,
		ProxyPtr< ElementT > > Scene::Create(ConstructorArgsT&&... args) {

		return AddElement(m_sprite_texts,
			std::forward< ConstructorArgsT >(args)...);
	}

	template< typename ElementT, typename... ConstructorArgsT >
	inline typename std::enable_if_t< std::is_base_of_v< BehaviorScript, ElementT >,
		ProxyPtr< ElementT > > Scene::Create(ConstructorArgsT&&... args) {

		return AddElementPtr< ElementT >(m_scripts,
			std::forward< ConstructorArgsT >(args)...);
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

	template< typename ElementT >
	inline size_t Scene::GetNumberOf() const noexcept {
		size_t count = 0;
		ForEach< ElementT >([&count](
			[[maybe_unused]] const ElementT &element) noexcept {
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

	template< typename ElementT, typename ActionT >
	inline void Scene::ForEach(ActionT action) {

		if constexpr (std::is_same_v< Node, ElementT >) {
			for (auto &element : m_nodes) {
				if (State::Terminated != element.GetState()) {
					action(element);
				}
			}
		}

		if constexpr (std::is_same_v< PerspectiveCamera, ElementT >) {
			for (auto &element : m_perspective_cameras) {
				if (State::Terminated != element.GetState()) {
					action(element);
				}
			}
		}

		if constexpr (std::is_same_v< OrthographicCamera, ElementT >) {
			for (auto &element : m_orthographic_cameras) {
				if (State::Terminated != element.GetState()) {
					action(element);
				}
			}
		}

		if constexpr (std::is_same_v< Camera, ElementT >) {
			ForEach< PerspectiveCamera >(action);
			ForEach< OrthographicCamera >(action);
		}

		if constexpr (std::is_same_v< AmbientLight, ElementT >) {
			for (auto &element : m_ambient_lights) {
				if (State::Terminated != element.GetState()) {
					action(element);
				}
			}
		}

		if constexpr (std::is_same_v< DirectionalLight, ElementT >) {
			for (auto &element : m_directional_lights) {
				if (State::Terminated != element.GetState()) {
					action(element);
				}
			}
		}

		if constexpr (std::is_same_v< OmniLight, ElementT >) {
			for (auto &element : m_omni_lights) {
				if (State::Terminated != element.GetState()) {
					action(element);
				}
			}
		}

		if constexpr (std::is_same_v< SpotLight, ElementT >) {
			for (auto &element : m_spot_lights) {
				if (State::Terminated != element.GetState()) {
					action(element);
				}
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
				if (State::Terminated != element.GetState()) {
					action(element);
				}
			}
		}

		if constexpr (std::is_same_v< SpriteImage, ElementT >) {
			for (auto &element : m_sprite_images) {
				if (State::Terminated != element.GetState()) {
					action(element);
				}
			}
		}

		if constexpr (std::is_same_v< SpriteText, ElementT >) {
			for (auto &element : m_sprite_texts) {
				if (State::Terminated != element.GetState()) {
					action(element);
				}
			}
		}

		if constexpr (std::is_same_v< Sprite, ElementT >) {
			ForEach< SpriteImage >(action);
			ForEach< SpriteText >(action);
		}

		if constexpr (std::is_same_v< BehaviorScript, ElementT >) {
			for (auto &element : m_scripts) {
				if (State::Terminated != element->GetState()) {
					action(*element);
				}
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
				if (State::Terminated != element.GetState()) {
					action(element);
				}
			}
		}

		if constexpr (std::is_same_v< PerspectiveCamera, ElementT >) {
			for (const auto &element : m_perspective_cameras) {
				if (State::Terminated != element.GetState()) {
					action(element);
				}
			}
		}

		if constexpr (std::is_same_v< OrthographicCamera, ElementT >) {
			for (const auto &element : m_orthographic_cameras) {
				if (State::Terminated != element.GetState()) {
					action(element);
				}
			}
		}

		if constexpr (std::is_same_v< Camera, ElementT >) {
			ForEach< PerspectiveCamera >(action);
			ForEach< OrthographicCamera >(action);
		}

		if constexpr (std::is_same_v< AmbientLight, ElementT >) {
			for (const auto &element : m_ambient_lights) {
				if (State::Terminated != element.GetState()) {
					action(element);
				}
			}
		}

		if constexpr (std::is_same_v< DirectionalLight, ElementT >) {
			for (const auto &element : m_directional_lights) {
				if (State::Terminated != element.GetState()) {
					action(element);
				}
			}
		}

		if constexpr (std::is_same_v< OmniLight, ElementT >) {
			for (const auto &element : m_omni_lights) {
				if (State::Terminated != element.GetState()) {
					action(element);
				}
			}
		}

		if constexpr (std::is_same_v< SpotLight, ElementT >) {
			for (const auto &element : m_spot_lights) {
				if (State::Terminated != element.GetState()) {
					action(element);
				}
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
				if (State::Terminated != element.GetState()) {
					action(element);
				}
			}
		}

		if constexpr (std::is_same_v< SpriteImage, ElementT >) {
			for (const auto &element : m_sprite_images) {
				if (State::Terminated != element.GetState()) {
					action(element);
				}
			}
		}

		if constexpr (std::is_same_v< SpriteText, ElementT >) {
			for (const auto &element : m_sprite_texts) {
				if (State::Terminated != element.GetState()) {
					action(element);
				}
			}
		}

		if constexpr (std::is_same_v< Sprite, ElementT >) {
			ForEach< SpriteImage >(action);
			ForEach< SpriteText >(action);
		}

		if constexpr (std::is_same_v< BehaviorScript, ElementT >) {
			for (const auto &element : m_scripts) {
				if (State::Terminated != element->GetState()) {
					action(static_cast< const BehaviorScript & >(*element));
				}
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