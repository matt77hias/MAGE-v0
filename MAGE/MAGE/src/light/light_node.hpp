#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "scene\scene_node.hpp"

// Lights
#include "light\ambient_light.hpp"
#include "light\directional_light.hpp"
#include "light\omni_light.hpp"
#include "light\spot_light.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	class LightNode : public SceneNode {

	public:

		virtual ~LightNode();

		LightNode &operator=(const LightNode &light_node) = delete;

		LightNode &operator=(LightNode &&light_node) = delete;

		UniquePtr< LightNode > Clone() const {
			return static_pointer_cast< LightNode >(CloneImplementation());
		}

		Light *GetLight() noexcept {
			return m_light.get();
		}

		const Light *GetLight() const noexcept {
			return m_light.get();
		}

	protected:

		explicit LightNode(const string &name, UniquePtr< Light > &&light);

		LightNode(const LightNode &light_node);

		LightNode(LightNode &&light_node);

	private:

		virtual UniquePtr< Node > CloneImplementation() const override = 0;

		UniquePtr< Light > m_light;
	};

	template< typename LightT >
	class DerivedLightNode final : public LightNode {

	public:

		template< typename... ConstructorArgsT >
		explicit DerivedLightNode(const string &name, ConstructorArgsT&&... args);

		explicit DerivedLightNode(const string &name, UniquePtr< LightT > &&light);

		DerivedLightNode(const DerivedLightNode &light_node);

		DerivedLightNode(DerivedLightNode &&light_node);

		virtual ~DerivedLightNode();

		DerivedLightNode &operator=(const DerivedLightNode &light_node) = delete;

		DerivedLightNode &operator=(DerivedLightNode &&light_node) = delete;

		UniquePtr< DerivedLightNode > Clone() const {
			return static_pointer_cast< DerivedLightNode >(CloneImplementation());
		}

		LightT *GetLight() noexcept {
			return static_cast< LightT * >(LightNode::GetLight());
		}

		const LightT *GetLight() const noexcept {
			return static_cast< const LightT * >(LightNode::GetLight());
		}

	private:

		virtual UniquePtr< Node > CloneImplementation() const override;
	};

	/**
	 A class of ambient light nodes.
	 */
	using AmbientLightNode = DerivedLightNode< AmbientLight >;
	
	/**
	 A class of directional light nodes.
	 */
	using DirectionalLightNode = DerivedLightNode< DirectionalLight >;
	
	/**
	 A class of omni light nodes.
	 */
	using OmniLightNode = DerivedLightNode< OmniLight >;
	
	/**
	 A class of spotlight nodes.
	 */
	using SpotLightNode = DerivedLightNode< SpotLight >;
}

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "light\light_node.tpp"

#pragma endregion