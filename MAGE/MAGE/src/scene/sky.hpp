#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "texture\texture.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	/**
	 A struct of skies.
	 */
	struct Sky final {

	public:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------	

		/**
		 Constructs a sky.
		 */
		Sky() = default;

		/**
		 Constructs a sky from the given sky.

		 @param[in]		sky
						A reference to the sky to copy.
		 */
		Sky(const Sky &sky) = default;

		/**
		 Constructs a sky by moving the given sky.

		 @param[in]		sky
						A reference to the sky to move.
		 */
		Sky(Sky &&sky) = default;

		/**
		 Destructs this sky.
		 */
		~Sky() = default;

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------	

		/**
		 Copies the given sky to this sky.

		 @param[in]		sky
						A reference to the sky to copy.
		 @return		A reference to the copy of the given sky (i.e. this 
						sky).
		 */
		Sky &operator=(const Sky &sky) = delete;

		/**
		 Moves the given sky to this sky.

		 @param[in]		sky
						A reference to the sky to move.
		 @return		A reference to the moved sky (i.e. this sky).
		 */
		Sky &operator=(Sky &&sky) = delete;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Returns the texture of this sky.

		 @return		A pointer to the texture of this sky.
		 */
		SharedPtr< const Texture > GetTexture() const noexcept {
			return m_texture;
		}
		
		/**
		 Returns the shader resource view of the texture of this sky.

		 @return		@c nullptr, if this sky has no texture.
		 @return		A pointer to the shader resource view of the texture of 
						this sky.
		 */
		ID3D11ShaderResourceView *GetSRV() const noexcept {
			return m_texture ? m_texture->Get() : nullptr;
		}
		
		/**
		 Sets the texture of this sky to the given texture.

		 @param[in]		texture
						A reference to the texture of this sky.
		 */
		void SetTexture(const SharedPtr< const Texture > &texture) {
			m_texture = texture;
		}

	private:

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		/**
		 The cube map texture of this sky.
		 */
		SharedPtr< const Texture > m_texture;
	};
}