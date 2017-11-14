#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "material\spectrum.hpp"
#include "texture\texture.hpp"
#include "logging\error.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	/**
	 A class of materials.
	 */
	class Material final {

	public:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		/**
		 Constructs a material.

		 @pre			The resource manager associated with the current engine 
						must be loaded.
		 @param[in]		name
						The name of the material.		
		 */
		explicit Material(string name = "material");
		
		/**
		 Constructs a material from the given material.

		 @param[in]		material
						A reference to the material to copy.
		 */
		Material(const Material &material) = default;
		
		/**
		 Constructs a material by moving the given material.
		 
		 @param[in]		material
						A reference to the material to move.
		 */
		Material(Material &&material) = default;
		
		/**
		 Destructs this material.
		 */
		~Material() = default;

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------	

		/**
		 Copies the given material to this material.

		 @param[in]		material
						A reference to the material to copy.
		 @return		A reference to the copy of the given material (i.e. 
						this material).
		 */
		Material &operator=(const Material &material) = default;

		/**
		 Moves the given material to this material.

		 @param[in]		material
						A reference to the material to move.
		 @return		A reference to the moved material (i.e. this material).
		 */
		Material &operator=(Material &&material) = default;

		//---------------------------------------------------------------------
		// Member Methods: Name
		//---------------------------------------------------------------------

		/**
		 Returns the name of this material.

		 @return		A reference to the name of this material.
		 */
		const string &GetName() const noexcept {
			return m_name;
		}
		
		/**
		 Sets the name of this material to the given name.

		 @param[in]		name
						The name.
		 */
		void SetName(string name) noexcept {
			m_name = std::move(name);
		}
		
		//---------------------------------------------------------------------
		// Member Methods: Light Interaction
		//---------------------------------------------------------------------

		/**
		 Checks whether this material interacts with light and light sources.

		 @return		@c true if this material interacts with light and 
						light sources. @c false otherwise.
		 */
		bool InteractsWithLight() const noexcept {
			return m_light_interaction;
		}

		/**
		 Enables this material to interact with light and light sources.
		 */
		void EnableLightInteraction() noexcept {
			SetLightInteraction(true);
		}

		/**
		 Dissables this material to interact with light and light sources.
		 */
		void DissableLightInteraction() noexcept {
			SetLightInteraction(false);
		}
		
		/**
		 Toggles the light interaction of this material.
		 */
		void ToggleLightInteraction() noexcept {
			SetLightInteraction(!InteractsWithLight());
		}

		/**
		 Sets the light interaction of this material to the given value.

		 @param[in]		light_interaction
						@c true if this material needs to interact with light 
						and light sources. @c false otherwise.
		 */
		void SetLightInteraction(bool light_interaction) noexcept {
			m_light_interaction = light_interaction;
		}
		
		//---------------------------------------------------------------------
		// Member Methods: Opacity/Transparency
		//---------------------------------------------------------------------

		/**
		 Checks whether this material is opaque (i.e. contains alpha channel 
		 equal to 1.0).

		 @return		@c true if and only if this material is opaque. 
						@c false otherwise.
		 */
		bool IsOpaque() const noexcept {
			return !IsTransparant();
		}
		
		/**
		 Checks whether this material is transparent (i.e. contains alpha 
		 channel not equal to 1.0).

		 @return		@c true if and only if this material is transparent.
						@c false otherwise.
		 */
		bool IsTransparant() const noexcept {
			return m_transparent;
		}
		
		/**
		 Makes this material opaque.
		 */
		void SetOpaque() noexcept {
			SetTransparent(false);
		}

		/**
		 Makes this material transparent.

		 @param[in]		transparent
						@c true if and only if this material is transparent.
						@c false otherwise.
		 */
		void SetTransparent(bool transparent = true) noexcept {
			m_transparent = transparent;
		}
		
		//---------------------------------------------------------------------
		// Member Methods: Base Color and Base Color Texture
		//---------------------------------------------------------------------

		/**
		 Returns the sRGB base color of this material.

		 @return		A reference to the sRGB base color of this material.
		 */
		SRGBA &GetBaseColor() noexcept {
			return m_base_color;
		}

		/**
		 Returns the sRGB base color of this material.

		 @return		A reference to the sRGB base color of this material.
		 */
		const SRGBA &GetBaseColor() const noexcept {
			return m_base_color;
		}

		/**
		 Returns the sRGB base color texture of this material.

		 @return		A pointer to the sRGB base color texture of this 
						material.
		 */
		SharedPtr< const Texture > GetBaseColorTexture() const noexcept {
			return m_base_color_texture;
		}
		
		/**
		 Returns the shader resource view of the sRGB base color texture of 
		 this material.

		 @return		@c nullptr, if this material has no sRGB base color 
						texture.
		 @return		A pointer to the shader resource view of the sRGB base 
						color texture of this material.
		 */
		ID3D11ShaderResourceView *GetBaseColorSRV() const noexcept {
			return m_base_color_texture ? m_base_color_texture->Get() : nullptr;
		}
		
		/**
		 Sets the sRGB base color texture of this material to the given base 
		 color texture.

		 @param[in]		base_color_texture
						A reference to the sRGB base color texture.
		 */
		void SetBaseColorTexture(
			const SharedPtr< const Texture > &base_color_texture) {
			
			m_base_color_texture = base_color_texture;
		}
		
		//---------------------------------------------------------------------
		// Member Variables: Material Parameters
		//---------------------------------------------------------------------

		/**
		 Returns the roughness of this material.
		
		 @return		The roughness of this material.			
		 */
		F32 GetRoughness() const noexcept {
			return m_roughness;
		}

		/**
		 Sets the roughness of this material to the given value.

		 @pre			@a roughness is an element of [0,1].
		 @param[in]		roughness
						The roughness.
		 */
		void SetRoughness(F32 roughness) noexcept {
			Assert(0.0f <= roughness && roughness <= 1.0f);
			m_roughness = roughness;
		}

		/**
		 Returns the metalness of this material.

		 @return		The metalness of this material.			
		 */
		F32 GetMetalness() const noexcept {
			return m_metalness;
		}

		/**
		 Sets the metalness of this material to the given value.

		 @pre			@a metalness is an element of [0,1].
		 @param[in]		metalness
						The metalness.
		 */
		void SetMetalness(F32 metalness) noexcept {
			Assert(0.0f <= metalness && metalness <= 1.0f);
			m_metalness = metalness;
		}

		/**
		 Returns the material RGBA channels of this material.

		 @return		The material RGBA channels of this material.
		 */
		const RGBA GetMaterialRGBA() const noexcept {
			return RGBA(GetRoughness(), GetMetalness(), 0.0f, 0.0f);
		}

		/**
		 Returns the material texture of this material.

		 @return		A pointer to the material texture of this material.
		 */
		SharedPtr< const Texture > GetMaterialTexture() const noexcept {
			return m_material_texture;
		}
		
		/**
		 Returns the shader resource view of the material texture of this 
		 material.

		 @return		@c nullptr, if this material has no material texture.
		 @return		A pointer to the shader resource view of the material 
						texture of this material.
		 */
		ID3D11ShaderResourceView *GetMaterialSRV() const noexcept {
			return m_material_texture ? m_material_texture->Get() : nullptr;
		}

		/**
		 Sets the material texture of this material to the given material 
		 texture.

		 @param[in]		material_texture
						A reference to the material texture.
		 */
		void SetMaterialTexture(
			const SharedPtr< const Texture > &material_texture) {
			
			m_material_texture = material_texture;
		}

		//---------------------------------------------------------------------
		// Member Methods: Normal Texture
		//---------------------------------------------------------------------
		
		/**
		 Returns the normal texture of this material.

		 @return		A pointer to the normal texture of this material.
		 */
		SharedPtr< const Texture > GetNormalTexture() const noexcept {
			return m_normal_texture;
		}
		
		/**
		 Returns the shader resource view of the normal texture of this 
		 material.

		 @return		@c nullptr, if this material has no normal texture.
		 @return		A pointer to the shader resource view of the normal 
						texture of this material.
		 */
		ID3D11ShaderResourceView *GetNormalSRV() const noexcept {
			return m_normal_texture ? m_normal_texture->Get() : nullptr;
		}

		/**
		 Sets the normal texture of this material to the given normal texture.

		 @param[in]		normal_texture
						A reference to the normal texture.
		 */
		void SetNormalTexture(
			const SharedPtr< const Texture > &normal_texture) {
			
			m_normal_texture = normal_texture;
		}
		
	private:

		//---------------------------------------------------------------------
		// Member Variables: Name
		//---------------------------------------------------------------------

		/**
		 The name of this material.
		 */
		string m_name;

		//---------------------------------------------------------------------
		// Member Variables: Light Interaction
		//---------------------------------------------------------------------

		/**
		 Flag indicating whether this material interacts with light and light 
		 sources.
		 */
		bool m_light_interaction;

		//---------------------------------------------------------------------
		// Member Variables: Opacity/Transparency
		//---------------------------------------------------------------------

		/**
		 Flag indicating whether this material is transparent. This flag is 
		 @c true if this material could contain transparent parts. @c false 
		 otherwise.
		 */
		bool m_transparent;

		//---------------------------------------------------------------------
		// Member Variables: Base Color and Base Color Texture
		//---------------------------------------------------------------------

		/**
		 The sRGB base color of this material.
		 */
		SRGBA m_base_color;

		/**
		 A pointer to the sRGB base color texture of this material.
		 */
		SharedPtr< const Texture > m_base_color_texture;

		//---------------------------------------------------------------------
		// Member Variables: Material Parameters
		//---------------------------------------------------------------------

		/**
		 The roughness of this material.
		 */
		F32 m_roughness;

		/**
		 The metalness of this material.
		 */
		F32 m_metalness;

		/**
		 A pointer to the material texture of this material.

		 The red channel contains the roughness of this material.
		 The blue channel contains the metalness of this material.
		 */
		SharedPtr< const Texture > m_material_texture;

		//---------------------------------------------------------------------
		// Member Variables: Normal Texture
		//---------------------------------------------------------------------

		/**
		 A pointer to the normal texture of this material.
		 */
		SharedPtr< const Texture > m_normal_texture;
	};
}