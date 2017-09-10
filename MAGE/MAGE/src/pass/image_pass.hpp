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

	class ImagePass final {

	public:

		ImagePass();
		ImagePass(const ImagePass &render_pass) = delete;
		ImagePass(ImagePass &&render_pass);
		~ImagePass();

		ImagePass &operator=(const ImagePass &render_pass) = delete;
		ImagePass &operator=(ImagePass &&render_pass) = delete;

		void Render(bool transfer_depth = true);
		
	private:

		ID3D11DeviceContext2 * const m_device_context;

		SharedPtr< const VertexShader > m_vs;
		SharedPtr< const PixelShader > m_ps;
		SharedPtr< const PixelShader > m_ms_ps;
	};
}