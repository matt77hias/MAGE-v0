#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "memory\memory.hpp"
#include "shader\vertex_shader.hpp"
#include "shader\pixel_shader.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	struct CombinedShader final {

	public:

		CombinedShader(SharedPtr< VertexShader > vertex_shader, SharedPtr< PixelShader > pixel_shader)
			: m_vertex_shader(vertex_shader), m_pixel_shader(pixel_shader) {}
		CombinedShader(const CombinedShader &shader) = default;
		~CombinedShader() = default;

		CombinedShader &operator=(const CombinedShader &shader) = default;

		SharedPtr< VertexShader > GetVertexShader() const {
			return m_vertex_shader;
		}
		void SetVertexShader(SharedPtr< VertexShader > vertex_shader) {
			m_vertex_shader = vertex_shader;
		}

		SharedPtr< PixelShader > GetPixelShader() const {
			return m_pixel_shader;
		}
		void SetPixelShader(SharedPtr< PixelShader > pixel_shader) {
			m_pixel_shader = pixel_shader;
		}

		void Render(ComPtr< ID3D11DeviceContext2 > device_context, const Material &material, const World &world, const TransformBuffer &transform_buffer) {
			m_vertex_shader->Render(device_context, material, world, transform_buffer);
			m_pixel_shader->Render(device_context, material, world);
		}

	private:

		SharedPtr< VertexShader > m_vertex_shader;
		SharedPtr< PixelShader > m_pixel_shader;
	};
}