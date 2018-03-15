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
	 A class of deferred passes for unpacking GBuffers and performing light 
	 calculations using the rendering or compute pipeline.
	 */
	class DeferredPass final {

	public:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		/**
		 Constructs a deferred pass.

		 @param[in]		device_context
						A reference to the device context.
		 @param[in]		state_manager
						A reference to the state manager.
		 @param[in]		resource_manager
						A reference to the resource manager.
		 */
		explicit DeferredPass(ID3D11DeviceContext& device_context, 
							  StateManager& state_manager, 
							  ResourceManager& resource_manager);

		/**
		 Constructs a deferred pass from the given deferred shading pass.

		 @param[in]		pass
						A reference to the deferred pass to copy.
		 */
		DeferredPass(const DeferredPass& pass) = delete;

		/**
		 Constructs a deferred pass by moving the given deferred pass.

		 @param[in]		pass
						A reference to the deferred pass to move.
		 */
		DeferredPass(DeferredPass&& pass) noexcept;

		/**
		 Destructs this deferred pass.
		 */
		~DeferredPass();

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------

		/**
		 Copies the given deferred pass to this deferred pass.

		 @param[in]		pass
						A reference to the deferred pass to copy.
		 @return		A reference to the copy of the given deferred shading 
						pass (i.e. this deferred pass).
		 */
		DeferredPass& operator=(const DeferredPass& pass) = delete;

		/**
		 Moves the given deferred pass to this deferred pass.

		 @param[in]		pass
						A reference to the deferred pass to move.
		 @return		A reference to the moved deferred pass (i.e. this 
						deferred pass).
		 */
		DeferredPass& operator=(DeferredPass&& pass) noexcept;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Renders.

		 @param[in]		brdf
						The BRDF.
		 @param[in]		vct
						@c true if voxel cone tracing should be enabled. @c false 
						otherwise.
		 @throws		Exception
						Failed to render the world.
		 */
		void Render(BRDFType brdf, bool vct);

		/**
		 Dispatches.

		 @param[in]		viewport_size
						A reference to the viewport size.
		 @param[in]		brdf
						The BRDF.
		 @param[in]		vct
						@c true if voxel cone tracing should be enabled. @c false 
						otherwise.
		 @throws		Exception
						Failed to dispatch.
		 */
		void Dispatch(const U32x2& viewport_size, BRDFType brdf, bool vct);
		
	private:

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Binds the fixed state of this deferred pass.
		 */
		void BindFixedState() const noexcept;
		
		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		/**
		 A reference to the device context of this deferred pass.
		 */
		std::reference_wrapper< ID3D11DeviceContext > m_device_context;

		/**
		 A reference to the state manager of this deferred pass.
		 */
		std::reference_wrapper< StateManager > m_state_manager;

		/**
		 A reference to the resource manager of this deferred pass.
		 */
		std::reference_wrapper< ResourceManager > m_resource_manager;

		/**
		 A pointer to the vertex shader of this deferred pass.
		 */
		VertexShaderPtr m_msaa_vs;
	};
}