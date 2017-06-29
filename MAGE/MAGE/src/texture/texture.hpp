#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "resource\resource.hpp"
#include "memory\memory.hpp"
#include "rendering\rendering.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	/**
	 A class of textures.
	 */
	class Texture : public Resource< Texture > {

	public:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		/**
		 Constructs a texture.

		 @pre			The current engine must be loaded.
		 @param[in]		fname
						A reference to the filename.
		 @throws		FormattedException
						Failed to initialize the texture.
		 */
		explicit Texture(const wstring &fname);

		/**
		 Constructs a texture.

		 @pre			@a device is not equal to @c nullptr.
		 @param[in]		device
						A pointer to the device.
		 @param[in]		fname
						A reference to the filename.
		 @throws		FormattedException
						Failed to initialize the texture.
		 */
		explicit Texture(ID3D11Device2 *device, const wstring &fname);

		/**
		 Constructs a 2D texture.

		 @pre			The current engine must be loaded.
		 @pre			@a desc is not equal to @c nullptr.
		 @pre			@a initial_data is not equal to @c nullptr.
		 @param[in]		guid
						A reference to the globally unique identifier.
		 @param[in]		desc
						A pointer to the texture descriptor.
		 @param[in]		initial_data
						A pointer to the initial data.
		 @throws		FormattedException
						Failed to initialize the texture.
		 */
		explicit Texture(const wstring &guid,
			const D3D11_TEXTURE2D_DESC *desc,
			const D3D11_SUBRESOURCE_DATA *initial_data);

		/**
		 Constructs a 2D texture.

		 @pre			@a device is not equal to @c nullptr.
		 @pre			@a desc is not equal to @c nullptr.
		 @pre			@a initial_data is not equal to @c nullptr.
		 @param[in]		device
						A pointer to the device.
		 @param[in]		guid
						A reference to the globally unique identifier.
		 @param[in]		desc
						A pointer to the texture descriptor.
		 @param[in]		initial_data
						A pointer to the initial data.
		 @throws		FormattedException
						Failed to initialize the texture.
		 */
		explicit Texture(ID3D11Device2 *device,
			const wstring &guid,
			const D3D11_TEXTURE2D_DESC *desc,
			const D3D11_SUBRESOURCE_DATA *initial_data);

		/**
		 Constructs a texture from the given texture.

		 @param[in]		texture
						A reference to the texture to copy.
		 */
		Texture(const Texture &texture) = delete;

		/**
		 Constructs a texture by moving the given texture.

		 @param[in]		texture
						A reference to the texture to move.
		 */
		Texture(Texture &&texture) = default;

		/**
		 Destructs this texture.
		 */
		virtual ~Texture() = default;

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------	

		/**
		 Copies the given texture to this texture.

		 @param[in]		texture
						A reference to the texture to copy.
		 @return		A reference to the copy of the given texture
						(i.e. this texture).
		 */
		Texture &operator=(const Texture &texture) = delete;

		/**
		 Moves the given texture to this texture.

		 @param[in]		texture
						A reference to the texture to move.
		 @return		A reference to the moved texture
						(i.e. this texture).
		 */
		Texture &operator=(Texture &&texture) = delete;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Returns a pointer to the shader resource view of this texture.

		 @return		A pointer to the shader resource view
						of this texture.
		 */
		ID3D11ShaderResourceView *Get() const noexcept {
			return m_texture_srv.Get();
		}
		
		/**
		 Returns the address of the shader resource view of this texture.

		 @return		A pointer to the pointer to the shader resource view
						of this texture.
		 */
		ID3D11ShaderResourceView * const *GetAddress() const noexcept {
			return m_texture_srv.GetAddressOf();
		}
		
		/**
		 Returns the address of the shader resource view of this texture.

		 @return		A pointer to the pointer to the shader resource view 
						of this texture.
		 */
		ID3D11ShaderResourceView **GetAddress() noexcept {
			return m_texture_srv.GetAddressOf();
		}

	private:

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		/**
		 A pointer to the device of this texture.
		 */
		ID3D11Device2 * const m_device;

		/**
		 A pointer to the shader resource view of this texture.
		 */
		ComPtr< ID3D11ShaderResourceView > m_texture_srv;
	};
}