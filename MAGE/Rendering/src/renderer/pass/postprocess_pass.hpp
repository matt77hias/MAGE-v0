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
	 A class of post-process passes for performing post-processing.
	 */
	class PostProcessPass {

	public:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		/**
		 Constructs a post-process pass.

		 @param[in]		device_context
						A reference to the device context.
		 @param[in]		state_manager
						A reference to the state manager.
		 @param[in]		resource_manager
						A reference to the resource manager.
		 */
		explicit PostProcessPass(ID3D11DeviceContext& device_context, 
								 StateManager& state_manager, 
								 ResourceManager& resource_manager);

		/**
		 Constructs a post-process pass from the given post-process pass.

		 @param[in]		pass
						A reference to the post-process pass to copy.
		 */
		PostProcessPass(const PostProcessPass& pass) = delete;

		/**
		 Constructs a post-process pass by moving the given post-process 
		 shading pass.

		 @param[in]		pass
						A reference to the post-process pass to move.
		 */
		PostProcessPass(PostProcessPass&& pass) noexcept;

		/**
		 Destructs this DOF pass.
		 */
		~PostProcessPass();

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------

		/**
		 Copies the given post-process pass to this post-process pass.

		 @param[in]		pass
						A reference to the post-process pass to copy.
		 @return		A reference to the copy of the given post-process pass 
						(i.e. this post-process pass).
		 */
		PostProcessPass& operator=(const PostProcessPass& pass) = delete;

		/**
		 Moves the given post-process pass to this post-process pass.

		 @param[in]		pass
						A reference to the post-process pass to move.
		 @return		A reference to the moved DOF pass (i.e. this 
						post-process pass).
		 */
		PostProcessPass& operator=(PostProcessPass&& pass) noexcept;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Dispatches an depth-of-field pass.

		 @param[in]		viewport_size
						A reference to the viewport size.
		 */
		void DispatchDOF(const U32x2& viewport_size) const noexcept;

		/**
		 Dispatches an low-dynamic-range pass.

		 @param[in]		viewport_size
						A reference to the viewport size.
		 @param[in]		tone_mapping
						The tone mapping type.
		 */
		void DispatchLDR(const U32x2& viewport_size, 
						 ToneMapping tone_mapping) const noexcept;

	private:

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		/**
		 A reference to the device context of this post-process pass.
		 */
		std::reference_wrapper< ID3D11DeviceContext > m_device_context;

		/**
		 A reference to the state manager of this post-process pass.
		 */
		std::reference_wrapper< StateManager > m_state_manager;

		/**
		 A reference to the resource manager of this post-process pass.
		 */
		std::reference_wrapper< ResourceManager > m_resource_manager;

		/**
		 A pointer to the compute shader of this post-process pass.
		 */
		ComputeShaderPtr m_dof_cs;
	};
}