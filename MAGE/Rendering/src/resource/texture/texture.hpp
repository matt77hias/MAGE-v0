#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "resource\resource.hpp"
#include "renderer\pipeline.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage::rendering {

	//-------------------------------------------------------------------------
	// Texture
	//-------------------------------------------------------------------------
	#pragma region

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

		 @param[in]		device
						A reference to the device.
		 @param[in]		fname
						The filename (the globally unique identifier).
		 @throws		Exception
						Failed to construct the texture.
		 */
		explicit Texture(ID3D11Device& device, wstring fname);

		/**
		 Constructs a 2D texture.

		 @param[in]		device
						A reference to the device.
		 @param[in]		guid
						The globally unique identifier.
		 @param[in]		desc
						A reference to the texture descriptor.
		 @param[in]		initial_data
						A reference to the initial data.
		 @throws		Exception
						Failed to construct the texture.
		 */
		explicit Texture(ID3D11Device& device,
						 wstring guid, 
			             const D3D11_TEXTURE2D_DESC& desc,
			             const D3D11_SUBRESOURCE_DATA& initial_data);

		/**
		 Constructs a texture from the given texture.

		 @param[in]		texture
						A reference to the texture to copy.
		 */
		Texture(const Texture& texture) = delete;

		/**
		 Constructs a texture by moving the given texture.

		 @param[in]		texture
						A reference to the texture to move.
		 */
		Texture(Texture&& texture) noexcept;

		/**
		 Destructs this texture.
		 */
		virtual ~Texture();

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
		Texture& operator=(const Texture& texture) = delete;

		/**
		 Moves the given texture to this texture.

		 @param[in]		texture
						A reference to the texture to move.
		 @return		A reference to the moved texture (i.e. this texture).
		 */
		Texture& operator=(Texture&& texture) noexcept;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Returns a pointer to the shader resource view of this texture.

		 @return		A pointer to the shader resource view of this texture.
		 */
		[[nodiscard]]
		ID3D11ShaderResourceView* Get() const noexcept {
			return m_texture_srv.Get();
		}
		
		/**
		 Binds this texture.

		 @pre			@a slot < @c D3D11_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT.
		 @tparam		PipelineStageT
						The pipeline stage type.
		 @param[in]		device_context
						A reference to the device context.
		 @param[in]		slot
						The index into the device's zero-based array to set 
						the shader resource view to (ranges from 0 to 
						@c D3D11_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT - 1).
		 */
		template< typename PipelineStageT >
		void Bind(ID3D11DeviceContext& device_context, U32 slot) const noexcept;

	private:

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		/**
		 A pointer to the shader resource view of this texture.
		 */
		ComPtr< ID3D11ShaderResourceView > m_texture_srv;
	};

	#pragma endregion

	//-------------------------------------------------------------------------
	// Type Declarations and Definitions
	//-------------------------------------------------------------------------
	#pragma region

	/**
	 A pointer to a texture resource.
	 */
	using TexturePtr = SharedPtr< const Texture >;

	#pragma endregion
}

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "resource\texture\texture.tpp"

#pragma endregion