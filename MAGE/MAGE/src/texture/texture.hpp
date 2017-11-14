#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "resource\resource.hpp"
#include "rendering\pipeline.hpp"

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

		 @pre			The device associated of the rendering manager 
						associated with the current engine must be loaded.
		 @param[in]		fname
						The filename (the globally unique identifier).
		 @throws		FormattedException
						Failed to initialize the texture.
		 */
		explicit Texture(wstring fname);

		/**
		 Constructs a texture.

		 @pre			@a device is not equal to @c nullptr.
		 @pre			The renderer associated with the current engine must be 
						loaded.
		 @param[in]		fname
						The filename (the globally unique identifier).
		 @param[in]		device
						A pointer to the device.
		 @throws		FormattedException
						Failed to initialize the texture.
		 */
		explicit Texture(wstring fname, ID3D11Device5 *device);

		/**
		 Constructs a 2D texture.

		 @pre			The device associated of the rendering manager 
						associated with the current engine must be loaded.
		 @pre			@a desc is not equal to @c nullptr.
		 @pre			@a initial_data is not equal to @c nullptr.
		 @param[in]		guid
						The globally unique identifier.
		 @param[in]		desc
						A pointer to the texture descriptor.
		 @param[in]		initial_data
						A pointer to the initial data.
		 @throws		FormattedException
						Failed to initialize the texture.
		 */
		explicit Texture(wstring guid,
			const D3D11_TEXTURE2D_DESC *desc,
			const D3D11_SUBRESOURCE_DATA *initial_data);

		/**
		 Constructs a 2D texture.

		 @pre			@a device is not equal to @c nullptr.
		 @pre			@a desc is not equal to @c nullptr.
		 @pre			@a initial_data is not equal to @c nullptr.
		 @param[in]		guid
						The globally unique identifier.
		 @param[in]		device
						A pointer to the device.
		 @param[in]		desc
						A pointer to the texture descriptor.
		 @param[in]		initial_data
						A pointer to the initial data.
		 @throws		FormattedException
						Failed to initialize the texture.
		 */
		explicit Texture(wstring guid, ID3D11Device5 *device,
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
		 @return		A reference to the copy of the given texture (i.e. this 
						texture).
		 */
		Texture &operator=(const Texture &texture) = delete;

		/**
		 Moves the given texture to this texture.

		 @param[in]		texture
						A reference to the texture to move.
		 @return		A reference to the moved texture (i.e. this texture).
		 */
		Texture &operator=(Texture &&texture) = delete;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Returns a pointer to the shader resource view of this texture.

		 @return		A pointer to the shader resource view of this texture.
		 */
		ID3D11ShaderResourceView *Get() const noexcept {
			return m_texture_srv.Get();
		}
		
		/**
		 Binds this texture.

		 @pre			@a device_context is not equal to @c nullptr.
		 @pre			@a slot < @c D3D11_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT.
		 @tparam		PipelineStageT
						The pipeline stage type.
		 @param[in]		device_context
						A pointer to the device context.
		 @param[in]		slot
						The index into the device's zero-based array to set 
						the shader resource view to (ranges from 0 to 
						@c D3D11_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT - 1).
		 */
		template< typename PipelineStageT >
		void Bind(ID3D11DeviceContext4 *device_context, 
			U32 slot) const noexcept;

	private:

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		/**
		 A pointer to the shader resource view of this texture.
		 */
		ComPtr< ID3D11ShaderResourceView > m_texture_srv;
	};
}

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "texture\texture.tpp"

#pragma endregion