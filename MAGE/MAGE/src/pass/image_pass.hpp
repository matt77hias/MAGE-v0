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

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		ImagePass();
		ImagePass(const ImagePass &render_pass) = delete;
		ImagePass(ImagePass &&render_pass);
		~ImagePass();

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------

		ImagePass &operator=(const ImagePass &render_pass) = delete;
		ImagePass &operator=(ImagePass &&render_pass) = delete;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		void BindFixedState(bool transfer_depth = true);

		void Render();
		
	private:

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		ID3D11DeviceContext2 * const m_device_context;

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		SharedPtr< const VertexShader > m_vs;
		SharedPtr< const PixelShader > m_ps;
		SharedPtr< const PixelShader > m_ms_ps;
	};
}