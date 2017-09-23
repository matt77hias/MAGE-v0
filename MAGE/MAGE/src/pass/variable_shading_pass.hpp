#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "pass\pass_buffer.hpp"
#include "buffer\constant_buffer.hpp"
#include "buffer\model_buffer.hpp"
#include "shader\shader.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations end Definitions
//-----------------------------------------------------------------------------
namespace mage {

	/**
	 A class of variable shading passes for rendering
	 models using a variable (material dependent) shading.
	 */
	class VariableShadingPass final {

	public:

		//---------------------------------------------------------------------
		// Class Member Methods
		//---------------------------------------------------------------------

		/**
		 Returns the variable shading pass associated with the current engine.

		 @pre			The scene renderer associated with the 
						current engine must be loaded.
		 @return		A pointer to the variable shading pass associated
						with the current engine.
		 */
		static VariableShadingPass *Get();

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		/**
		 Constructs a variable shading pass.

		 @pre			The renderer associated with the
						current engine must be loaded.
		 @pre			The resource manager associated with the
						current engine must be loaded.
		 */
		VariableShadingPass();

		/**
		 Constructs a variable shading pass from the given variable shading pass.

		 @param[in]		render_pass
						A reference to the variable shading pass to copy.
		 */
		VariableShadingPass(const VariableShadingPass &render_pass) = delete;

		/**
		 Constructs a variable shading pass by moving the given variable shading pass.

		 @param[in]		render_pass
						A reference to the variable shading pass to move.
		 */
		VariableShadingPass(VariableShadingPass &&render_pass);

		/**
		 Destructs this variable shading pass.
		 */
		~VariableShadingPass();

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------

		/**
		 Copies the given variable shading pass to this variable shading pass.

		 @param[in]		render_pass
						A reference to the variable shading pass to copy.
		 @return		A reference to the copy of the given variable shading pass
						(i.e. this variable shading pass).
		 */
		VariableShadingPass &operator=(const VariableShadingPass &render_pass) = delete;

		/**
		 Moves the given variable shading pass to this variable shading pass.

		 @param[in]		render_pass
						A reference to the variable shading pass to move.
		 @return		A reference to the moved variable shading pass
						(i.e. this variable shading pass).
		 */
		VariableShadingPass &operator=(VariableShadingPass &&render_pass) = delete;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Binds the fixed state of this variable shading pass.

		 @param[in]		brdf
						The BRDF.
		 @throws		FormattedException
						Failed to bind the fixed state 
						of this variable shading pass.
		 */
		void BindFixedState(BRDFType brdf);

		/**
		 Renders the scene (only the opaque models).

		 @pre			@a scene is not equal to @c nullptr.
		 @param[in]		scene
						A pointer to the scene.
		 @param[in]		world_to_projection
						The world-to-projection transformation matrix.
		 @param[in]		world_to_view
						The world-to-view transformation matrix.
		 @param[in]		view_to_world
						The view-to-world transformation matrix.
		 @param[in]		view_to_projection
						The view-to-projection transformation matrix.
		 @throws		FormattedException
						Failed to render the scene.
		 */
		void XM_CALLCONV RenderOpaque(
			const PassBuffer *scene,
			FXMMATRIX world_to_projection,
			CXMMATRIX world_to_view,
			CXMMATRIX view_to_world,
			CXMMATRIX view_to_projection);

		/**
		 Renders the scene (only the opaque emissive models).

		 @pre			@a scene is not equal to @c nullptr.
		 @param[in]		scene
						A pointer to the scene.
		 @param[in]		world_to_projection
						The world-to-projection transformation matrix.
		 @param[in]		world_to_view
						The world-to-view transformation matrix.
		 @param[in]		view_to_world
						The view-to-world transformation matrix.
		 @param[in]		view_to_projection
						The view-to-projection transformation matrix.
		 @throws		FormattedException
						Failed to render the scene.
		 */
		void XM_CALLCONV RenderOpaqueEmissive(
			const PassBuffer *scene,
			FXMMATRIX world_to_projection,
			CXMMATRIX world_to_view,
			CXMMATRIX view_to_world,
			CXMMATRIX view_to_projection);

		/**
		 Renders the scene (only the transparent models).

		 @pre			@a scene is not equal to @c nullptr.
		 @param[in]		scene
						A pointer to the scene.
		 @param[in]		world_to_projection
						The world-to-projection transformation matrix.
		 @param[in]		world_to_view
						The world-to-view transformation matrix.
		 @param[in]		view_to_world
						The view-to-world transformation matrix.
		 @param[in]		view_to_projection
						The view-to-projection transformation matrix.
		 @throws		FormattedException
						Failed to render the scene.
		 */
		void XM_CALLCONV RenderTransparent(
			const PassBuffer *scene,
			FXMMATRIX world_to_projection,
			CXMMATRIX world_to_view,
			CXMMATRIX view_to_world,
			CXMMATRIX view_to_projection);

	private:

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 An enumeration of the different pixel shader indices 
		 for variable shading passes.

		 This contains:
		 @c Emissive,
		 @c BRDF and
		 @c BRDF_TSNM.
		 */
		enum struct PSIndex {
			Emissive  = 0,
			BRDF      = 1,
			BRDF_TSNM = 2,
			Count     = 3
		};

		/**
		 Updates the pixel shaders of this variable shading pass
		 for the given BRDF.

		 @pre			The resource manager associated with the
						current engine must be loaded.
		 @param[in]		brdf
						The BRDF.
		 @throws		FormattedException
						Failed to update the pixel shaders
						of this variable shading pass.
		 */
		void UpdatePSs(BRDFType brdf);
		
		/**
		 Binds the pixel shader of this variable shading pass
		 associated with the given pixel shader index.

		 @param[in]		index
						The pixel shader index.
		 */
		void BindPS(PSIndex index) noexcept;
		
		/**
		 Binds the pixel shader of this variable shading pass 
		 associated with the given material.

		 @pre			@a material is not equal to @c nullptr.
		 @param[in]		material
						A pointer to the material.
		 */
		void BindPS(const Material *material) noexcept;
		
		/**
		 Binds the projection data of this variable shading pass.

		 @param[in]		view_to_projection
						The view-to-projection transformation matrix used for
						transforming vertices.
		 @throws		FormattedException
						Failed to bind the projection data 
						of this variable shading pass.
		 */
		void XM_CALLCONV BindProjectionData(
			FXMMATRIX view_to_projection);
		
		/**
		 Binds the model data of this variable shading pass.

		 @pre			@a material is not equal to @c nullptr.
		 @param[in]		object_to_view
						The object-to-view transformation matrix used for
						transforming vertices.
		 @param[in]		view_to_object
						The view-to-object transformation matrix used for
						transforming normals.
		 @param[in]		texture_transform
						The texture transformation matrix used for
						transforming texture coordinates.
		 @param[in]		material
						A pointer to the material.
		 @throws		FormattedException
						Failed to bind the model data 
						of this variable shading pass.
		 */
		void XM_CALLCONV BindModelData(
			FXMMATRIX object_to_view, 
			CXMMATRIX view_to_object,
			CXMMATRIX texture_transform,
			const Material *material);
		
		/**
		 Process the given models.

		 @param[in]		models
						A reference to a vector containing the model pointers
						to process.
		 @param[in]		world_to_projection
						The world-to-projection transformation matrix.
						This transformation matrix will be used for 
						culling.
		 @param[in]		world_to_view
						The world-to-view transformation matrix.
						This transformation matrix will be chained with
						the object-to-view transformation matrix for
						transforming vertices.
		 @param[in]		view_to_world
						The view-to-world transformation matrix.
						This transformation matrix will be chained with
						the world-to-object transformation matrix for
						transforming normals.
		 @throws		FormattedException
						Failed to process the models.
		 */
		void XM_CALLCONV ProcessModels(
			const vector< const ModelNode * > &models,
			FXMMATRIX world_to_projection, 
			CXMMATRIX world_to_view, 
			CXMMATRIX view_to_world);

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		/**
		 A pointer to the device context of this variable shading pass. 
		 */
		ID3D11DeviceContext2 * const m_device_context;

		/**
		 A pointer to the vertex shader of this variable shading pass.
		 */
		const SharedPtr< const VertexShader > m_vs;

		/**
		 An array containing pointers to the pixel shaders
		 of this variable shading pass.
		 */
		SharedPtr< const PixelShader > m_ps[static_cast< size_t >(PSIndex::Count)];
		
		/**
		 The pixel shader index of the bound pixel shader
		 of this variable shading pass.
		 */
		PSIndex m_bound_ps;
		
		/**
		 The current BRDF of this variable shading pass.
		 */
		BRDFType m_brdf;

		/**
		 The projection buffer of this variable shading pass.
		 */
		ConstantBuffer< XMMATRIX > m_projection_buffer;

		/**
		 The model buffer of this variable shading pass.
		 */
		ConstantBuffer< ForwardModelBuffer > m_model_buffer;
	};
}