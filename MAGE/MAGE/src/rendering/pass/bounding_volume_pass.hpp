#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "scene\scene.hpp"
#include "rendering\buffer\constant_buffer.hpp"
#include "shader\shader.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations end Definitions
//-----------------------------------------------------------------------------
namespace mage {

	/**
	 A class of bounding volume passes for rendering model and finite light 
	 volumes.
	 */
	class BoundingVolumePass final {

	public:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		/**
		 Constructs a bounding volume pass.

		 @pre			The renderer associated with the current engine must be 
						loaded.
		 @pre			The resource manager associated with the current engine 
						must be loaded.
		 */
		BoundingVolumePass();

		/**
		 Constructs a bounding volume pass from the given bounding volume pass.

		 @param[in]		pass
						A reference to the bounding volume pass to copy.
		 */
		BoundingVolumePass(const BoundingVolumePass &pass) = delete;

		/**
		 Constructs a bounding volume pass by moving the given bounding volume 
		 pass.

		 @param[in]		pass
						A reference to the bounding volume pass to move.
		 */
		BoundingVolumePass(BoundingVolumePass &&pass) noexcept;

		/**
		 Destructs this bounding volume pass.
		 */
		~BoundingVolumePass();

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------

		/**
		 Copies the given bounding volume pass to this bounding volume pass.

		 @param[in]		pass
						A reference to the bounding volume pass to copy.
		 @return		A reference to the copy of the given bounding volume 
						pass (i.e. this bounding volume pass).
		 */
		BoundingVolumePass &operator=(const BoundingVolumePass &pass) = delete;

		/**
		 Moves the given bounding volume pass to this bounding volume pass.

		 @param[in]		pass
						A reference to the bounding volume pass to move.
		 @return		A reference to the moved bounding volume pass (i.e. 
						this bounding volume pass).
		 */
		BoundingVolumePass &operator=(BoundingVolumePass &&pass) = delete;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Renders the scene.

		 @param[in]		scene
						A reference to the scene.
		 @param[in]		world_to_projection
						The world-to-projection transformation matrix.
		 @throws		Exception
						Failed to render the scene.
		 */
		void XM_CALLCONV Render(const Scene &scene,
			                    FXMMATRIX world_to_projection);

	private:

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Binds the fixed state of this bounding volume pass.
		 */
		void BindFixedState() const noexcept;

		/**
		 Binds the light color of this bounding volume pass.

		 @throws		Exception
						Failed to bind the light color of this bounding 
						volume pass.
		 */
		void BindLightColor();

		/**
		 Binds the model color of this bounding volume pass.
		 
		 @throws		Exception
						Failed to bind the model color of this bounding 
						volume pass.
		 */
		void BindModelColor();

		/**
		 Binds the color of this bounding volume pass.

		 @param[in]		color
						A reference to the color.
		 @throws		Exception
						Failed to bind the light color of this bounding 
						volume pass.
		 */
		void BindColor(const RGBA &color);

		/**
		 Binds the transform of this bounding volume pass.

		 @param[in]		cube_to_world
						The cube-to-world transformation matrix used for 
						transforming cube vertices.
		 @throws		Exception
						Failed to bind the transform of this bounding volume 
						pass.
		 */
		void XM_CALLCONV BindTransform(FXMMATRIX cube_to_world);

		/**
		 Renders the given AABB.

		 @param[in]		aabb
						A reference to the AABB.
		 @param[in]		object_to_world
						The object-to-world transformation matrix.
		 @throws		Exception
						Failed to bind the render the given AABB.
		 */
		void XM_CALLCONV Render(const AABB &aabb, FXMMATRIX object_to_world);
		
		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		/**
		 A pointer to the device context of this bounding volume pass.
		 */
		ID3D11DeviceContext * const m_device_context;

		/**
		 A pointer to the vertex shader of this bounding volume pass.
		 */
		const VertexShaderPtr m_vs;

		/**
		 A pointer to the pixel shader of this bounding volume pass.
		 */
		const PixelShaderPtr m_ps;

		/**
		 The color buffer of this bounding volume pass.
		 */
		ConstantBuffer< RGBA > m_color_buffer;

		/**
		 The transform buffer of this bounding volume pass.
		 */
		ConstantBuffer< XMMATRIX > m_transform_buffer;
	};
}
