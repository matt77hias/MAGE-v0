#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "scene\scene.hpp"
#include "rendering\buffer\constant_buffer.hpp"
#include "rendering\buffer\model_buffer.hpp"
#include "shader\shader.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations end Definitions
//-----------------------------------------------------------------------------
namespace mage {

	/**
	 A class of variable shading passes for rendering models using a variable 
	 (material dependent) shading.
	 */
	class VariableShadingPass final {

	public:

		//---------------------------------------------------------------------
		// Class Member Methods
		//---------------------------------------------------------------------

		/**
		 Returns the variable shading pass associated with the current engine.

		 @pre			The scene renderer associated with the current engine 
						must be loaded.
		 @return		A pointer to the variable shading pass associated with 
						the current engine.
		 */
		static VariableShadingPass *Get();

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		/**
		 Constructs a variable shading pass.

		 @pre			The renderer associated with the current engine must be 
						loaded.
		 @pre			The resource manager associated with the current engine 
						must be loaded.
		 */
		VariableShadingPass();

		/**
		 Constructs a variable shading pass from the given variable shading 
		 pass.

		 @param[in]		pass
						A reference to the variable shading pass to copy.
		 */
		VariableShadingPass(const VariableShadingPass &pass) = delete;

		/**
		 Constructs a variable shading pass by moving the given variable 
		 shading pass.

		 @param[in]		pass
						A reference to the variable shading pass to move.
		 */
		VariableShadingPass(VariableShadingPass &&pass) noexcept;

		/**
		 Destructs this variable shading pass.
		 */
		~VariableShadingPass();

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------

		/**
		 Copies the given variable shading pass to this variable shading pass.

		 @param[in]		pass
						A reference to the variable shading pass to copy.
		 @return		A reference to the copy of the given variable shading 
						pass (i.e. this variable shading pass).
		 */
		VariableShadingPass &operator=(const VariableShadingPass &pass) = delete;

		/**
		 Moves the given variable shading pass to this variable shading pass.

		 @param[in]		pass
						A reference to the variable shading pass to move.
		 @return		A reference to the moved variable shading pass (i.e. 
						this variable shading pass).
		 */
		VariableShadingPass &operator=(VariableShadingPass &&pass) = delete;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

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
			                    CXMMATRIX world_to_view,
			                    CXMMATRIX view_to_world, 
								BRDFType brdf, 
								bool vct);

		/**
		 Renders the scene (only the emissive models).

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
		void XM_CALLCONV RenderEmissive(const Scene &scene,
			                            FXMMATRIX world_to_projection,
			                            CXMMATRIX world_to_view,
			                            CXMMATRIX view_to_world);

		/**
		 Renders the scene (only the transparent models).

		 @param[in]		scene
						A reference to the scene.
		 @param[in]		world_to_projection
						The world-to-projection transformation matrix.
		 @param[in]		world_to_view
						The world-to-view transformation matrix.
		 @param[in]		view_to_world
						The view-to-world transformation matrix.
		 @param[in]		brdf
						The BRDF.
		 @param[in]		vct
						@c true if voxel cone tracing should be enabled. @c false 
						otherwise.
		 @throws		Exception
						Failed to render the scene.
		 */
		void XM_CALLCONV RenderTransparent(const Scene &scene,
			                               FXMMATRIX world_to_projection,
			                               CXMMATRIX world_to_view,
			                               CXMMATRIX view_to_world, 
										   BRDFType brdf, 
										   bool vct);

	private:

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Binds the fixed opaque state of this variable shading pass.
		 */
		void BindFixedOpaqueState() const noexcept;

		/**
		 Binds the fixed transparent state of this variable shading pass.
		 */
		void BindFixedTransparentState() const noexcept;

		/**
		 An enumeration of the different pixel shader indices for variable 
		 shading passes.

		 This contains:
		 @c Emissive,
		 @c BRDF,
		 @c BRDF_TSNM,
		 @c Transparent_Emissive,
		 @c Transparent_BRDF and
		 @c Transparent_BRDF_TSNM.
		 */
		enum class PSIndex : U8 {
			Emissive              = 0,
			BRDF                  = 1,
			BRDF_TSNM             = 2,
			Transparent_Emissive  = 3,
			Transparent_BRDF      = 4,
			Transparent_BRDF_TSNM = 5,
			Count                 = 6
		};

		/**
		 Updates the pixel shaders of this variable shading pass for the given 
		 BRDF.

		 @pre			The resource manager associated with the current 
						engine must be loaded.
		 @param[in]		brdf
						The BRDF.
		 @param[in]		vct
						@c true if voxel cone tracing should be enabled. @c false 
						otherwise.
		 @throws		Exception
						Failed to update the pixel shaders of this variable 
						shading pass.
		 */
		void UpdatePSs(BRDFType brdf, bool vct);
		
		/**
		 Binds the pixel shader of this variable shading pass associated with 
		 the given pixel shader index.

		 @param[in]		index
						The pixel shader index.
		 */
		void BindPS(PSIndex index) noexcept;
		
		/**
		 Binds the opaque pixel shader of this variable shading pass associated 
		 with the given material.

		 @param[in]		material
						A reference to the material.
		 */
		void BindOpaquePS(const Material &material) noexcept;

		/**
		 Binds the transparent pixel shader of this variable shading pass 
		 associated with the given material.

		 @param[in]		material
						A reference to the material.
		 */
		void BindTransparentPS(const Material &material) noexcept;
		
		/**
		 Binds the model data of this variable shading pass.

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
						Failed to bind the model data of this variable shading 
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
		 A pointer to the device context of this variable shading pass. 
		 */
		ID3D11DeviceContext4 * const m_device_context;

		/**
		 A pointer to the vertex shader of this variable shading pass.
		 */
		const VertexShaderPtr m_vs;

		/**
		 An array containing pointers to the pixel shaders of this variable 
		 shading pass.
		 */
		PixelShaderPtr m_ps[static_cast< size_t >(PSIndex::Count)];
		
		/**
		 The pixel shader index of the bound pixel shader of this variable 
		 shading pass.
		 */
		PSIndex m_bound_ps;
		
		/**
		 The current BRDF of this variable shading pass.
		 */
		BRDFType m_brdf;

		/**
		 A flag indicating whether or not voxel cone tracing should be enabled 
		 for this variable shading pass.
		 */
		bool m_vct;

		/**
		 The model buffer of this variable shading pass.
		 */
		ConstantBuffer< ModelBuffer > m_model_buffer;
	};
}