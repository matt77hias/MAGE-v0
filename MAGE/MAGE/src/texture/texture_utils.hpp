#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "math\math.hpp"
#include "rendering\rendering.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations
//-----------------------------------------------------------------------------
namespace mage {
	
	/**
	 Returns the size of the given 2D texture.

	 @pre			@a texture_srv is not equal to @c nullptr.		
	 @param[in]		texture_srv
					A pointer to the (texture) shader resource view.
	 @return		The size of the given 2D texture as a
					@c XMVECTOR (width, height, width, height).
	 @throws		FormattedException
					The resource of the given shader resource view
					must be convertible to a @c ID3D11Texture2D.
	 */
	const XMVECTOR GetTexture2DSize(ID3D11ShaderResourceView *texture_srv);

	/**
	 Returns the size of the given 2D texture.

	 @pre			@a texture is not equal to @c nullptr.
	 @param[in]		texture
					A pointer to the 2D texture.
	 @return		The size of the given 2D texture as a
					@c XMVECTOR (width, height, width, height).
	 */
	const XMVECTOR GetTexture2DSize(ID3D11Texture2D *texture) noexcept;
}