#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "shader\shader.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations end Definitions
//-----------------------------------------------------------------------------
namespace mage {

	/**
	 A class of voxel grid passes for rendering voxel grids to screen.
	 */
	class VoxelGridPass final {

	public:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		/**
		 Constructs a voxel grid pass.

		 @pre			The renderer associated with the current engine must be 
						loaded.
		 @pre			The resource manager associated with the current engine 
						must be loaded.
		 */
		VoxelGridPass();

		/**
		 Constructs a voxel grid pass from the given voxel grid pass.

		 @param[in]		pass
						A reference to the voxel grid pass to copy.
		 */
		VoxelGridPass(const VoxelGridPass &pass) = delete;

		/**
		 Constructs a voxel grid pass by moving the given voxel grid pass.

		 @param[in]		pass
						A reference to the voxel grid pass to move.
		 */
		VoxelGridPass(VoxelGridPass &&pass) noexcept;

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
		VoxelGridPass &operator=(const VoxelGridPass &pass) = delete;

		/**
		 Moves the given voxel grid pass to this voxel grid pass.

		 @param[in]		pass
						A reference to the voxel grid pass to move.
		 @return		A reference to the moved voxel grid pass (i.e. this 
						voxel grid pass).
		 */
		VoxelGridPass &operator=(VoxelGridPass &&pass) = delete;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Renders the given scene.

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
		 A pointer to the device context of this voxel grid pass.
		 */
		ID3D11DeviceContext * const m_device_context;

		/**
		 A pointer to the vertex shader of this voxel grid pass.
		 */
		const VertexShaderPtr m_vs;

		/**
		 A pointer to the geometry shader of this voxel grid pass.
		 */
		const GeometryShaderPtr m_gs;

		/**
		 A pointer to the pixel shader of this voxel grid pass.
		 */
		const PixelShaderPtr m_ps;
	};
}