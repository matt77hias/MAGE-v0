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
	 A class of GBuffer passes for packing GBuffers.
	 */
	class GBufferPass final {

	public:

		//---------------------------------------------------------------------
		// Class Member Methods
		//---------------------------------------------------------------------

		/**
		 Returns the GBuffer pass associated with the current engine.

		 @pre			The scene renderer associated with the current engine 
						must be loaded.
		 @return		A pointer to the GBuffer pass associated with the 
						current engine.
		 */
		static GBufferPass *Get();

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		/**
		 Constructs a GBuffer pass.

		 @pre			The renderer associated with the current engine must be 
						loaded.
		 @pre			The resource manager associated with the current engine 
						must be loaded.
		 */
		GBufferPass();

		/**
		 Constructs a GBuffer pass from the given GBuffer pass.

		 @param[in]		render_pass
						A reference to the GBuffer pass to copy.
		 */
		GBufferPass(const GBufferPass &render_pass) = delete;

		/**
		 Constructs a GBuffer pass by moving the given GBuffer pass.

		 @param[in]		render_pass
						A reference to the GBuffer pass to move.
		 */
		GBufferPass(GBufferPass &&render_pass);

		/**
		 Destructs this GBuffer pass.
		 */
		~GBufferPass();

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------

		/**
		 Copies the given GBuffer pass to this GBuffer pass.

		 @param[in]		render_pass
						A reference to the GBuffer pass to copy.
		 @return		A reference to the copy of the given GBuffer pass (i.e. 
						this GBuffer pass).
		 */
		GBufferPass &operator=(const GBufferPass &render_pass) = delete;

		/**
		 Moves the given GBuffer pass to this GBuffer pass.

		 @param[in]		render_pass
						A reference to the GBuffer pass to move.
		 @return		A reference to the moved GBuffer pass (i.e. this 
						GBuffer pass).
		 */
		GBufferPass &operator=(GBufferPass &&render_pass) = delete;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Binds the fixed state of this GBuffer pass.

		 @throws		FormattedException
						Failed to bind the fixed state of this GBuffer pass.
		 */
		void BindFixedState();

		/**
		 Renders the scene.

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
		void XM_CALLCONV Render(
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
		 Updates the material coefficient data of this GBuffer pass from the 
		 given scene.

		 @pre			@a scene is not equal to @c nullptr.
		 @param[in]		scene
						A pointer to the scene.
		 */
		void UpdateMaterialCoefficientData(const PassBuffer *scene) noexcept;
		
		/**
		 Normalizes the material coefficient of the given material at the given 
		 material coefficient index.

		 @pre			@a index < 
						{@link mage::PassBuffer::s_nb_material_coefficients}.
		 @pre			@a material is not equal to @c nullptr.
		 @param[in]		index
						The material coefficient index.
		 @param[in]		material
						A pointer to the material.
		 */
		f32 NormalizeMaterialCoefficient(
			u8 index, const Material *material) const noexcept;

		/**
		 An enumeration of the different pixel shader indices for GBuffer 
		 passes.

		 This contains:
		 @c Default and
		 @c TSNM.
		 */
		enum struct PSIndex {
			Default = 0,
			TSNM    = 1,
			Count   = 2
		};

		/**
		 Binds the pixel shader of this GBuffer pass associated with the given 
		 pixel shader index.

		 @param[in]		index
						The pixel shader index.
		 */
		void BindPS(PSIndex index) noexcept;
		
		/**
		 Binds the pixel shader of this GBuffer pass associated with the given 
		 material.

		 @pre			@a material is not equal to @c nullptr.
		 @param[in]		material
						A pointer to the material.
		 */
		void BindPS(const Material *material) noexcept;
		
		/**
		 Binds the projection data of this GBuffer pass.

		 @param[in]		view_to_projection
						The view-to-projection transformation matrix used for
						transforming vertices.
		 @throws		FormattedException
						Failed to bind the projection data of this GBuffer 
						pass.
		 */
		void XM_CALLCONV BindProjectionData(FXMMATRIX view_to_projection);
		
		/**
		 Binds the model data of this GBuffer pass.

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
						of this GBuffer pass.
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
						The world-to-projection transformation matrix. This 
						transformation matrix will be used for culling.
		 @param[in]		world_to_view
						The world-to-view transformation matrix. This 
						transformation matrix will be chained with the 
						object-to-view transformation matrix for transforming 
						vertices.
		 @param[in]		view_to_world
						The view-to-world transformation matrix. This 
						transformation matrix will be chained with the 
						world-to-object transformation matrix for transforming 
						normals.
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
		 A pointer to the device context of this GBuffer pass. 
		 */
		ID3D11DeviceContext2 * const m_device_context;

		/**
		 A pointer to the vertex shader of this GBuffer pass.
		 */
		const SharedPtr< const VertexShader > m_vs;
		
		/**
		 An array containing pointers to the pixel shaders of this GBuffer 
		 pass.
		 */
		const SharedPtr< const PixelShader > m_ps[static_cast< size_t >(PSIndex::Count)];
		
		/**
		 The pixel shader index of the bound pixel shader of this GBuffer pass.
		 */
		PSIndex m_bound_ps;

		/**
		 The projection buffer of this GBuffer pass.
		 */
		ConstantBuffer< XMMATRIX > m_projection_buffer;

		/**
		 The model buffer of this GBuffer pass.
		 */
		ConstantBuffer< DeferredModelBuffer > m_model_buffer;
		
		/**
		 The current minima of the material coefficients of this GBuffer pass.
		 */
		f32 m_material_coefficient_min[PassBuffer::s_nb_material_coefficients];

		/**
		 The current ranges of the material coefficients of this GBuffer pass.
		 */
		f32 m_material_coefficient_range[PassBuffer::s_nb_material_coefficients];
	};
}