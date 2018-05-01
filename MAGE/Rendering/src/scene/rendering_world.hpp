#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "display\display_configuration.hpp"
#include "resource\rendering_resource_manager.hpp"
#include "scene\node.hpp"
#include "scene\camera\orthographic_camera.hpp"
#include "scene\camera\perspective_camera.hpp"
#include "scene\light\ambient_light.hpp"
#include "scene\light\directional_light.hpp"
#include "scene\light\omni_light.hpp"
#include "scene\light\spot_light.hpp"
#include "scene\model\model.hpp"
#include "scene\sprite\sprite_image.hpp"
#include "scene\sprite\sprite_text.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage::rendering {

	/**
	 A class of world.
	 */
	class World final {

	public:
	
		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		/**
		 Constructs a world.

		 @param[in]		device
						A reference to the device.
		 @param[in]		display_configuration
						A reference to the display configuration.
		 @param[in]		resource_manager
						A reference to the resource manager.
		 */
		explicit World(ID3D11Device& device, 
					   DisplayConfiguration& display_configuration,
					   ResourceManager& resource_manager);

		/**
		 Constructs a world from the given world.

		 @param[in]		world
						A reference to the world.
		 */
		World(const World& world) = delete;

		/**
		 Constructs a world by moving the given world.

		 @param[in]		world
						A reference to the world to move.
		 */
		World(World&& world) noexcept;

		/**
		 Destructs this world.
		 */
		virtual ~World();

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------	

		/**
		 Copies the given world to this world.

		 @param[in]		world
						A reference to the world to copy.
		 @return		A reference to the copy of the given world (i.e. this 
						world).
		 */
		World& operator=(const World& world) = delete;

		/**
		 Moves the given world to this world.

		 @param[in]		world
						A reference to the world to move.
		 @return		A reference to the moved world (i.e. this world).
		 */
		World& operator=(World&& world) noexcept;

		//---------------------------------------------------------------------
		// Member Methods: Nodes and Components
		//---------------------------------------------------------------------

		template< typename ComponentT >
		ProxyPtr< ComponentT > Create();

		template< typename ComponentT >
		[[nodiscard]]
		size_t GetNumberOf() const noexcept;

		template< typename ComponentT, typename ActionT >
		void ForEach(ActionT&& action);

		template< typename ComponentT, typename ActionT >
		void ForEach(ActionT&& action) const;
		
		/**
		 Clears this world.
		 */
		void Clear() noexcept;
		
	private:

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------
		
		/**
		 A reference to the device of this world.
		 */
		std::reference_wrapper< ID3D11Device > m_device;
		
		/**
		 A reference to the display configuration manager of this world.
		 */
		std::reference_wrapper< DisplayConfiguration > m_display_configuration;

		/**
		 A reference to the resource manager of this world.
		 */
		std::reference_wrapper< ResourceManager > m_resource_manager;
		
		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------
		
		/**
		 A vector containing the perspective cameras of this world.
		 */
		AlignedVector< PerspectiveCamera > m_perspective_cameras;

		/**
		 A vector containing the orthographic cameras of this world.
		 */
		AlignedVector< OrthographicCamera > m_orthographic_cameras;

		/**
		 A vector containing the ambient lights of this world.
		 */
		AlignedVector< AmbientLight > m_ambient_lights;

		/**
		 A vector containing the directional lights of this world.
		 */
		AlignedVector< DirectionalLight > m_directional_lights;

		/**
		 A vector containing the omni lights of this world.
		 */
		AlignedVector< OmniLight > m_omni_lights;

		/**
		 A vector containing the spot lights of this world.
		 */
		AlignedVector< SpotLight > m_spot_lights;

		/**
		 A vector containing the models of this world.
		 */
		AlignedVector< Model > m_models;

		/**
		 A vector containing the sprite images of this world.
		 */
		AlignedVector< SpriteImage > m_sprite_images;

		/**
		 A vector containing the sprite texts of this world.
		 */
		AlignedVector< SpriteText > m_sprite_texts;
	};
}

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "scene\rendering_world.tpp"

#pragma endregion