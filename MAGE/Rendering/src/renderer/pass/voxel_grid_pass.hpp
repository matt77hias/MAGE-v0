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
	 A class of voxel grid passes for rendering voxel grids to screen.
	 */
	class VoxelGridPass {

	public:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		/**
		 Constructs a voxel grid pass.

		 @param[in]		device_context
						A reference to the device context.
		 @param[in]		state_manager
						A reference to the state manager.
		 @param[in]		resource_manager
						A reference to the resource manager.
		 */
		explicit VoxelGridPass(ID3D11DeviceContext& device_context, 
							   StateManager& state_manager, 
							   ResourceManager& resource_manager);

		/**
		 Constructs a voxel grid pass from the given voxel grid pass.

		 @param[in]		pass
						A reference to the voxel grid pass to copy.
		 */
		VoxelGridPass(const VoxelGridPass& pass) = delete;

		/**
		 Constructs a voxel grid pass by moving the given voxel grid pass.

		 @param[in]		pass
						A reference to the voxel grid pass to move.
		 */
		VoxelGridPass(VoxelGridPass&& pass) noexcept;

		/**
		 Destructs this voxel grid pass.
		 */
		~VoxelGridPass();

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------

		/**
		 Copies the given voxel grid pass to this voxel grid pass.

		 @param[in]		pass
						A reference to the voxel grid pass to copy.
		 @return		A reference to the copy of the given voxel grid pass 
						(i.e. this voxel grid pass).
		 */
		VoxelGridPass& operator=(const VoxelGridPass& pass) = delete;

		/**
		 Moves the given voxel grid pass to this voxel grid pass.

		 @param[in]		pass
						A reference to the voxel grid pass to move.
		 @return		A reference to the moved voxel grid pass (i.e. this 
						voxel grid pass).
		 */
		VoxelGridPass& operator=(VoxelGridPass&& pass) noexcept;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Renders the given world.

		 @param[in]		resolution
						The resolution of the regular voxel grid.
		 */
		void Render(size_t resolution) const noexcept;
		
	private:

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Binds the fixed state of this voxel grid pass.
		 */
		void BindFixedState() const noexcept;

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		/**
		 A reference to the device context of this voxel grid pass.
		 */
		std::reference_wrapper< ID3D11DeviceContext > m_device_context;

		/**
		 A reference to the state manager of this voxel grid pass.
		 */
		std::reference_wrapper< StateManager > m_state_manager;

		/**
		 A pointer to the vertex shader of this voxel grid pass.
		 */
		VertexShaderPtr m_vs;

		/**
		 A pointer to the geometry shader of this voxel grid pass.
		 */
		GeometryShaderPtr m_gs;

		/**
		 A pointer to the pixel shader of this voxel grid pass.
		 */
		PixelShaderPtr m_ps;
	};
}