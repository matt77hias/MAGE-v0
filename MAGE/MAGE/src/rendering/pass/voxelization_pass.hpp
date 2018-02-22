#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "scene\scene.hpp"
#include "rendering\buffer\voxel_grid.hpp"
#include "shader\shader.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations end Definitions
//-----------------------------------------------------------------------------
namespace mage {

	/**
	 A class of voxelization passes for rendering models using a variable 
	 (material dependent) shading.
	 */
	class VoxelizationPass final {

	public:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		/**
		 Constructs a voxelization pass.

		 @pre			The renderer associated with the current engine must be 
						loaded.
		 @pre			The resource manager associated with the current engine 
						must be loaded.
		 */
		VoxelizationPass();

		/**
		 Constructs a voxelization pass from the given voxelization 
		 pass.

		 @param[in]		pass
						A reference to the voxelization pass to copy.
		 */
		VoxelizationPass(const VoxelizationPass &pass) = delete;

		/**
		 Constructs a voxelization pass by moving the given variable 
		 shading pass.

		 @param[in]		pass
						A reference to the voxelization pass to move.
		 */
		VoxelizationPass(VoxelizationPass &&pass) noexcept;

		/**
		 Destructs this voxelization pass.
		 */
		~VoxelizationPass();

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------

		/**
		 Copies the given voxelization pass to this voxelization pass.

		 @param[in]		pass
						A reference to the voxelization pass to copy.
		 @return		A reference to the copy of the given voxelization 
						pass (i.e. this voxelization pass).
		 */
		VoxelizationPass &operator=(const VoxelizationPass &pass) = delete;

		/**
		 Moves the given voxelization pass to this voxelization pass.

		 @param[in]		pass
						A reference to the voxelization pass to move.
		 @return		A reference to the moved voxelization pass (i.e. 
						this voxelization pass).
		 */
		VoxelizationPass &operator=(VoxelizationPass &&pass) = delete;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Renders the scene.

		 @param[in]		scene
						A reference to the scene.
		 @param[in]		world_to_projection
						The world-to-projection transformation matrix.
		 @param[in]		brdf
						The BRDF.
		 @param[in]		resolution
						The resolution of the regular voxel grid.
		 @throws		Exception
						Failed to render the scene.
		 */
		void XM_CALLCONV Render(const Scene &scene,
			                    FXMMATRIX world_to_projection,
								BRDFType brdf, size_t resolution);

	private:

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Sets up the voxel grid of this voxelization pass.

		 @param[in]		resolution
						The resolution of the regular voxel grid.
		 @throws		Exception
						Failed to render the scene.
		 */
		void SetupVoxelGrid(size_t resolution);

		/**
		 Binds the fixed state of this voxelization pass.
		 */
		void BindFixedState() const noexcept;

		/**
		 Renders the given scene.

		 @param[in]		scene
						A reference to the scene.
		 @param[in]		world_to_projection
						The world-to-projection transformation matrix.
		 @param[in]		brdf
						The BRDF.
		 @param[in]		vct
						@c true if voxel cone tracing should be enabled. @c false 
						otherwise.
		 @throws		Exception
						Failed to render the scene.
		 */
		void XM_CALLCONV Render(const Scene &scene,
			                    FXMMATRIX world_to_projection,
								BRDFType brdf) const;

		/**
		 Renders the given model.

		 @param[in]		model
						A reference to the model.
		 @param[in]		world_to_projection
						The world-to-projection transformation matrix.
		 */
		void XM_CALLCONV Render(const Model &model,
								FXMMATRIX world_to_projection) const noexcept;

		/**
		 Dispatches this voxelization pass.
		 */
		void Dispatch() const noexcept;
			
		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		/**
		 A pointer to the device context of this voxelization pass. 
		 */
		ID3D11DeviceContext * const m_device_context;

		/**
		 A pointer to the vertex shader of this voxelization pass.
		 */
		const VertexShaderPtr m_vs;

		/**
		 A pointer to the geometry shader of this voxelization pass.
		 */
		const GeometryShaderPtr m_gs;

		/**
		 A pointer to the compute shader of this voxelization pass.
		 */
		const ComputeShaderPtr m_cs;

		/**
		 The voxel grid of this voxelization pass. 
		 */
		UniquePtr< VoxelGrid > m_voxel_grid;
	};
}