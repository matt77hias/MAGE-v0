#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "renderer\state_manager.hpp"
#include "resource\rendering_resource_manager.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations end Definitions
//-----------------------------------------------------------------------------
namespace mage::rendering {

	/**
	 A class of DOF passes for performing DOF.
	 */
	class DOFPass final {

	public:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		/**
		 Constructs a DOF pass.

		 @param[in]		device_context
						A reference to the device context.
		 @param[in]		state_manager
						A reference to the state manager.
		 @param[in]		resource_manager
						A reference to the resource manager.
		 */
		explicit DOFPass(ID3D11DeviceContext& device_context, 
						 StateManager& state_manager, 
						 ResourceManager& resource_manager);

		/**
		 Constructs a DOF pass from the given DOF 
		 pass.

		 @param[in]		pass
						A reference to the DOF pass to copy.
		 */
		DOFPass(const DOFPass& pass) = delete;

		/**
		 Constructs a DOF pass by moving the given DOF 
		 shading pass.

		 @param[in]		pass
						A reference to the DOF pass to move.
		 */
		DOFPass(DOFPass&& pass) noexcept;

		/**
		 Destructs this DOF pass.
		 */
		~DOFPass();

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------

		/**
		 Copies the given DOF pass to this DOF pass.

		 @param[in]		pass
						A reference to the DOF pass to copy.
		 @return		A reference to the copy of the given DOF pass (i.e. 
						this DOF pass).
		 */
		DOFPass& operator=(const DOFPass& pass) = delete;

		/**
		 Moves the given DOF pass to this DOF pass.

		 @param[in]		pass
						A reference to the DOF pass to move.
		 @return		A reference to the moved DOF pass (i.e. this DOF pass).
		 */
		DOFPass& operator=(DOFPass&& pass) noexcept;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Dispatches an DOF pass.

		 @param[in]		resolution
						A reference to the viewport size.
		 */
		void Dispatch(const U32x2& viewport_size) const noexcept;

	private:

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		/**
		 A reference to the device context of this DOF pass.
		 */
		std::reference_wrapper< ID3D11DeviceContext > m_device_context;

		/**
		 A reference to the state manager of this DOF pass.
		 */
		std::reference_wrapper< StateManager > m_state_manager;

		/**
		 A pointer to the compute shader of this DOF pass.
		 */
		ComputeShaderPtr m_cs;
	};
}