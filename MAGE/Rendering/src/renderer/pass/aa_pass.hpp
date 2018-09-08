#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "renderer\configuration.hpp"
#include "renderer\state_manager.hpp"
#include "resource\rendering_resource_manager.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations end Definitions
//-----------------------------------------------------------------------------
namespace mage::rendering {

	/**
	 A class of AA passes for performing AA.
	 */
	class AAPass {

	public:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		/**
		 Constructs a AA pass.

		 @param[in]		device_context
						A reference to the device context.
		 @param[in]		state_manager
						A reference to the state manager.
		 @param[in]		resource_manager
						A reference to the resource manager.
		 */
		explicit AAPass(ID3D11DeviceContext& device_context, 
						StateManager& state_manager,
						ResourceManager& resource_manager);

		/**
		 Constructs a AA pass from the given AA 
		 pass.

		 @param[in]		pass
						A reference to the AA pass to copy.
		 */
		AAPass(const AAPass& pass) = delete;

		/**
		 Constructs a AA pass by moving the given AA 
		 shading pass.

		 @param[in]		pass
						A reference to the AA pass to move.
		 */
		AAPass(AAPass&& pass) noexcept;

		/**
		 Destructs this AA pass.
		 */
		~AAPass();

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------

		/**
		 Copies the given AA pass to this AA pass.

		 @param[in]		pass
						A reference to the AA pass to copy.
		 @return		A reference to the copy of the given AA pass (i.e. 
						this AA pass).
		 */
		AAPass& operator=(const AAPass& pass) = delete;

		/**
		 Moves the given AA pass to this AA pass.

		 @param[in]		pass
						A reference to the AA pass to move.
		 @return		A reference to the moved AA pass (i.e. this AA pass).
		 */
		AAPass& operator=(AAPass&& pass) noexcept;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Dispatches an AA preprocess.

		 @param[in]		viewport_size
						A reference to the viewport size.
		 @param[in]		aa
						The anti-aliasing mode.
		 @throws		Exception
						Failed to render the world.
		 */
		void DispatchPreprocess(const U32x2& viewport_size, AntiAliasing aa);

		/**
		 Dispatches an AA pass.

		 @param[in]		viewport_size
						A reference to the viewport size.
		 @param[in]		aa
						The anti-aliasing mode.
		 @throws		Exception
						Failed to render the world.
		 */
		void Dispatch(const U32x2& viewport_size, AntiAliasing aa);

	private:

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		/**
		 A reference to the device context of this AA pass.
		 */
		std::reference_wrapper< ID3D11DeviceContext > m_device_context;

		/**
		 A reference to the state manager of this AA pass.
		 */
		std::reference_wrapper< StateManager > m_state_manager;

		/**
		 A reference to the resource manager of this AA pass.
		 */
		std::reference_wrapper< ResourceManager > m_resource_manager;
	};
}