#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "scene\scene.hpp"
#include "rendering\buffer\constant_buffer.hpp"
#include "rendering\buffer\model_buffer.hpp"
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
		// Class Member Methods
		//---------------------------------------------------------------------

		/**
		 Returns the voxelization pass associated with the current engine.

		 @pre			The scene renderer associated with the current engine 
						must be loaded.
		 @return		A pointer to the voxelization pass associated with 
						the current engine.
		 */
		static VoxelizationPass *Get();

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

		 @param[in]		render_pass
						A reference to the voxelization pass to copy.
		 */
		VoxelizationPass(const VoxelizationPass &render_pass) = delete;

		/**
		 Constructs a voxelization pass by moving the given variable 
		 shading pass.

		 @param[in]		render_pass
						A reference to the voxelization pass to move.
		 */
		VoxelizationPass(VoxelizationPass &&render_pass) noexcept;

		/**
		 Destructs this voxelization pass.
		 */
		~VoxelizationPass();

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------

		/**
		 Copies the given voxelization pass to this voxelization pass.

		 @param[in]		render_pass
						A reference to the voxelization pass to copy.
		 @return		A reference to the copy of the given voxelization 
						pass (i.e. this voxelization pass).
		 */
		VoxelizationPass &operator=(
			const VoxelizationPass &render_pass) = delete;

		/**
		 Moves the given voxelization pass to this voxelization pass.

		 @param[in]		render_pass
						A reference to the voxelization pass to move.
		 @return		A reference to the moved voxelization pass (i.e. 
						this voxelization pass).
		 */
		VoxelizationPass &operator=(
			VoxelizationPass &&render_pass) = delete;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Binds the fixed state of this voxelization pass.

		 @param[in]		brdf
						The BRDF.
		 @throws		Exception
						Failed to bind the fixed state of this voxelization 
						pass.
		 */
		void BindFixedState(BRDFType brdf);

		/**
		 Renders the scene.

		 @param[in]		scene
						A reference to the scene.
		 @param[in]		world_to_projection
						The world-to-projection transformation matrix.
		 @param[in]		world_to_view
						The world-to-view transformation matrix.
		 @param[in]		view_to_world
						The view-to-world transformation matrix.
		 @throws		Exception
						Failed to render the scene.
		 */
		void XM_CALLCONV Render(const Scene &scene,
			                    FXMMATRIX world_to_projection,
			                    CXMMATRIX world_to_view,
			                    CXMMATRIX view_to_world);

	private:

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 An enumeration of the different pixel shader indices for variable 
		 shading passes.

		 This contains:
		 @c BRDF and
		 @c BRDF_TSNM.
		 */
		enum class PSIndex : U8 {
			BRDF       = 0,
			BRDF_TSNM  = 1,
			Count      = 2
		};

		/**
		 Updates the pixel shaders of this voxelization pass for the given 
		 BRDF.

		 @pre			The resource manager associated with the current 
						engine must be loaded.
		 @param[in]		brdf
						The BRDF.
		 @throws		Exception
						Failed to update the pixel shaders of this variable 
						shading pass.
		 */
		void UpdatePSs(BRDFType brdf);
		
		/**
		 Binds the pixel shader of this voxelization pass associated with 
		 the given pixel shader index.

		 @param[in]		index
						The pixel shader index.
		 */
		void BindPS(PSIndex index) noexcept;
		
		/**
		 Binds the pixel shader of this voxelization pass associated with 
		 the given material.

		 @param[in]		material
						A reference to the material.
		 @param[in]		transparency
						@c true if transparency should be enabled. @c false 
						otherwise.
		 */
		void BindPS(const Material &material, bool transparency) noexcept;
		
		/**
		 Binds the model data of this voxelization pass.

		 @param[in]		object_to_view
						The object-to-view transformation matrix used for
						transforming vertices.
		 @param[in]		view_to_object
						The view-to-object transformation matrix used for 
						transforming normals.
		 @param[in]		texture_transform
						The texture transformation matrix used for transforming 
						texture coordinates.
		 @param[in]		material
						A reference to the material.
		 @throws		Exception
						Failed to bind the model data of this voxelization 
						pass.
		 */
		void XM_CALLCONV BindModelData(FXMMATRIX object_to_view, 
			                           CXMMATRIX view_to_object,
			                           CXMMATRIX texture_transform,
			                           const Material &material);

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		/**
		 A pointer to the device context of this voxelization pass. 
		 */
		ID3D11DeviceContext4 * const m_device_context;

		/**
		 A pointer to the vertex shader of this voxelization pass.
		 */
		const VertexShaderPtr m_vs;

		/**
		 A pointer to the geometry shader of this voxelization pass.
		 */
		const GeometryShaderPtr m_gs;

		/**
		 An array containing pointers to the pixel shaders of this variable 
		 shading pass.
		 */
		PixelShaderPtr m_ps[static_cast< size_t >(PSIndex::Count)];

		/**
		 A pointer to the compute shader of this voxelization pass.
		 */
		const ComputeShaderPtr m_cs;
		
		/**
		 The pixel shader index of the bound pixel shader of this variable 
		 shading pass.
		 */
		PSIndex m_bound_ps;
		
		/**
		 The current BRDF of this voxelization pass.
		 */
		BRDFType m_brdf;

		/**
		 The model buffer of this voxelization pass.
		 */
		ConstantBuffer< ModelBuffer > m_model_buffer;
	};
}