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

	struct ShadedMaterial final {

	public:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		explicit ShadedMaterial(const CombinedShader &shader, const Material &material)
			: m_shader(shader), m_material(material) {}
		ShadedMaterial(const ShadedMaterial &shaded_material) = default;
		ShadedMaterial(ShadedMaterial &&shaded_material) = default;
		~ShadedMaterial() = default;

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------

		ShadedMaterial &operator=(const ShadedMaterial &shaded_material) = default;
		ShadedMaterial &operator=(ShadedMaterial &&shaded_material) = default;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		void PrepareShading(const World &world, const TransformBuffer &transform_buffer) const {
			m_shader.PrepareShading(m_material, world, transform_buffer);
		}

		Material &GetMaterial() {
			return m_material;
		}
		const Material &GetMaterial() const {
			return m_material;
		}

		CombinedShader &GetShader() {
			return m_shader;
		}
		const CombinedShader &GetShader() const {
			return m_shader;
		}

	private:

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		CombinedShader m_shader;
		Material m_material;
	};
}