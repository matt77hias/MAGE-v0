#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "resource\texture\texture.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage::rendering {

	/**
	 A class of sky domes.
	 */
	class Sky final {

	public:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------	

		/**
		 Constructs a sky.
		 */
		Sky() 
			: m_texture(), 
			m_scale_z(1.5f) {}

		/**
		 Constructs a sky from the given sky.

		 @param[in]		sky
						A reference to the sky to copy.
		 */
		Sky(const Sky& sky) = default;

		/**
		 Constructs a sky by moving the given sky.

		 @param[in]		sky
						A reference to the sky to move.
		 */
		Sky(Sky&& sky) noexcept = default;

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
		Sky& operator=(const Sky& sky) noexcept = default;

		/**
		 Moves the given sky to this sky.

		 @param[in]		sky
						A reference to the sky to move.
		 @return		A reference to the moved sky (i.e. this sky).
		 */
		Sky& operator=(Sky&& sky) noexcept = default;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Returns the texture of this sky.

		 @return		A pointer to the texture of this sky.
		 */
		[[nodiscard]]
		TexturePtr GetTexture() const noexcept {
			return m_texture;
		}
		
		/**
		 Returns the shader resource view of the texture of this sky.

		 @return		@c nullptr, if this sky has no texture.
		 @return		A pointer to the shader resource view of the texture of 
						this sky.
		 */
		[[nodiscard]]
		ID3D11ShaderResourceView* GetSRV() const noexcept {
			return m_texture ? m_texture->Get() : nullptr;
		}
		
		/**
		 Sets the texture of this sky to the given texture.

		 @param[in]		texture
						The texture of this sky.
		 */
		void SetTexture(TexturePtr texture) {
			m_texture = std::move(texture);
		}

		/**
		 Returns the scaling factor of the z component of the sky domes of this 
		 sky.
		
		 @return		The scaling factor of the z component of the sky domes 
						of this sky.
		 */
		[[nodiscard]]
		F32 GetScaleZ() const noexcept {
			return m_scale_z;
		}

		/**
		 Sets scaling factor of the z component of the sky domes of this sky to 
		 the given value.

		 @param[in]		scale_z
						The scaling factor.
		 */
		void SetScaleZ(F32 scale_z) noexcept {
			m_scale_z = std::abs(scale_z);
		}

	private:

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		/**
		 The cube map texture of this sky.
		 */
		TexturePtr m_texture;

		/**
		 The scaling factor of the z component of the sky domes of this sky.
		 */
		F32 m_scale_z;
	};
}