#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "shader\shader.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	/**
	 A struct of shaded materials.
	 */
	struct ShadedMaterial final {

	public:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		/**
		 Constructs a shaded material.

		 @param[in]		shader
						A reference to the shader.
		 @param[in]		material
						A reference to the material.
		 */
		explicit ShadedMaterial(const CombinedShader &shader, const Material &material)
			: m_shader(shader), m_material(material) {}

		/**
		 Constructs a shaded material from the given shaded material.

		 @param[in]		shaded_material
						A reference to the shaded material to copy.
		 */
		ShadedMaterial(const ShadedMaterial &shaded_material) = default;

		/**
		 Constructs a shaded material by moving the given shaded material.

		 @param[in]		shaded_material
						A reference to the shaded material to move.
		 */
		ShadedMaterial(ShadedMaterial &&shaded_material) = default;

		/**
		 Destructs this shaded material.
		 */
		~ShadedMaterial() = default;

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------

		/**
		 Copies the given shaded material to this shaded material.

		 @param[in]		shaded_material
						A reference to the shaded material to copy.
		 @return		A reference to the copy of the given shaded material
						(i.e. this shaded material).
		 */
		ShadedMaterial &operator=(const ShadedMaterial &shaded_material) = default;

		/**
		 Moves the given shaded material to this shaded material.

		 @param[in]		shaded_material
						A reference to the shaded material to move.
		 @return		A reference to the moved shaded material
						(i.e. this shaded material).
		 */
		ShadedMaterial &operator=(ShadedMaterial &&shaded_material) = default;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Prepares this shaded material for shading.

		 @pre			@a transform is not equal to @c nullptr.
		 @param[in]		transform
						A pointer to the transform buffer.
		 @param[in]		lighting
						A reference to the lighting buffer.
		 */
		void PrepareShading(ID3D11Buffer *transform, const Lighting &lighting) const {
			m_shader.PrepareShading(transform, m_material, lighting);
		}

		/**
		 Returns the material of this shaded material.

		 @return		A reference to the material of this shaded material.
		 */
		Material &GetMaterial() {
			return m_material;
		}

		/**
		 Returns the material of this shaded material.

		 @return		A reference to the material of this shaded material.
		 */
		const Material &GetMaterial() const {
			return m_material;
		}

		/**
		 Sets the material of this shaded material to the given material.

		 @param[in]		material
						A reference to the material.
		 */
		void SetMaterial(const Material &material) {
			m_material = material;
		}

		/**
		 Returns the shader of this shaded material.

		 @return		A reference to the shader of this shaded material.
		 */
		const CombinedShader &GetShader() const {
			return m_shader;
		}

		/**
		 Sets the shader of this shaded material to the given shader.

		 @param[in]		shader
						A reference to the shader.
		 */
		void SetShader(const CombinedShader &shader) {
			m_shader = shader;
		}

	private:

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		/**
		 The shader of this shaded material.
		 */
		CombinedShader m_shader;

		/**
		 The material of this shaded material.
		 */
		Material m_material;
	};
}