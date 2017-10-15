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
	 A struct of materials.
	 */
	struct Material final {

	public:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		/**
		 Constructs a material.

		 @pre			The resource manager associated with the current engine 
						must be loaded.		
		 @param[in]		name
						A reference to the name of the material.		
		 */
		explicit Material(const string &name = "material");
		
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
						A reference to the name.
		 */
		void SetName(const string &name) {
			m_name = name;
		}
		
		/**
		 Sets the name of this material to the given name.

		 @param[in]		name
						A reference to the name.
		 */
		void SetName(string &&name) {
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
		 Returns the red channel of the base color of this material.

		 @return		The red channel of the base color of this material.
		 */
		F32 GetBaseColorR() const noexcept {
			return m_base_color.x;
		}
		
		/**
		 Returns the green channel of the base color of this material.

		 @return		The green channel of the base color of this material.
		 */
		F32 GetBaseColorG() const noexcept {
			return m_base_color.y;
		}
		
		/**
		 Returns the blue channel of the base color of this material.

		 @return		The blue channel of the base color of this material.
		 */
		F32 GetBaseColorB() const noexcept {
			return m_base_color.z;
		}
		
		/**
		 Returns the alpha channel of the base color of this material.

		 @return		The alpha channel of the base color of this material.
		 */
		F32 GetBaseColorA() const noexcept {
			return m_base_color.w;
		}
		
		/**
		 Returns the RGB channels of the base color of this material.

		 @return		The RGB channels of the base color of this material.
		 */
		const RGBSpectrum GetBaseColorRGB() const noexcept {
			return RGBSpectrum(m_base_color.x, m_base_color.y, m_base_color.z);
		}
		
		/**
		 Returns the RGBA channels of the base color of this material.

		 @return		The RGBA channels of the base color of this material.
		 */
		const RGBASpectrum GetBaseColorRGBA() const noexcept {
			return m_base_color;
		}

		/**
		 Sets the red channel of the base color of this material to the given 
		 value.

		 @param[in]		red
						The red channel of the base color.
		 */
		void SetBaseColorR(F32 red) noexcept {
			m_base_color.x = red;
		}
		
		/**
		 Sets the green channel of the base color of this material to the given 
		 value.

		 @param[in]		green
						The green channel of the base color.
		 */
		void SetBaseColorG(F32 green) noexcept {
			m_base_color.y = green;
		}
		
		/**
		 Sets the blue channel of the base color of this material to the given 
		 value.

		 @param[in]		blue
						The blue channel of the base color.
		 */
		void SetBaseColorB(F32 blue) noexcept {
			m_base_color.z = blue;
		}
		
		/**
		 Sets the alpha channel of the base color of this material to the given 
		 value.

		 @param[in]		alpha
						The alpha channel of the base color.
		 */
		void SetBaseColorA(F32 alpha) noexcept {
			m_base_color.w = alpha;
		}
		
		/**
		 Sets the RGB channels of the base color of this material to the given 
		 values.

		 @param[in]		red
						The red channel of the base color.
		 @param[in]		green
						The green channel of the base color.
		 @param[in]		blue
						The blue channel of the base color.
		 */
		void SetBaseColorRGB(F32 red, F32 green, F32 blue) noexcept {
			SetBaseColorR(red);
			SetBaseColorG(green);
			SetBaseColorB(blue);
		}
		
		/**
		 Sets the RGB channels of the base color of this material to the given 
		 value.

		 @param[in]		rgb
						A reference to the RGB channels of the base color.
		 */
		void SetBaseColorRGB(const RGBSpectrum &rgb) noexcept {
			SetBaseColorRGB(rgb.x, rgb.y, rgb.z);
		}
		
		/**
		 Sets the RGB channels of the base color of this material to the given 
		 values.

		 @param[in]		red
						The red channel of the base color.
		 @param[in]		green
						The green channel of the base color.
		 @param[in]		blue
						The blue channel of the base color.
		 @param[in]		alpha
						The alpha channel of the base color.
		 */
		void SetBaseColorRGBA(F32 red, F32 green, F32 blue, F32 alpha) noexcept {
			SetBaseColorR(red);
			SetBaseColorG(green);
			SetBaseColorB(blue);
			SetBaseColorA(alpha);
		}
		
		/**
		 Sets the RGBA channels of the base color of this material to the given 
		 value.

		 @param[in]		rgba
						A reference to the RGBA channels of the base color.
		 */
		void SetBaseColorRGBA(const RGBASpectrum &rgba) noexcept {
			m_base_color = rgba;
		}

		/**
		 Sets the RGBA channels of the base color of this material to the given 
		 value.

		 @param[in]		rgba
						A reference to the RGBA channels of the base color.
		 */
		void SetBaseColorRGBA(RGBASpectrum &&rgba) noexcept {
			m_base_color = std::move(rgba);
		}

		/**
		 Returns the base color texture of this material.

		 @return		A pointer to the base color texture of this material.
		 */
		SharedPtr< const Texture > GetBaseColorTexture() const noexcept {
			return m_base_color_texture;
		}
		
		/**
		 Returns the shader resource view of the base color texture of this 
		 material.

		 @return		@c nullptr, if this material has no base color 
						texture.
		 @return		A pointer to the shader resource view of the base color 
						texture of this material.
		 */
		ID3D11ShaderResourceView *GetBaseColorSRV() const noexcept {
			return m_base_color_texture ? m_base_color_texture->Get() : nullptr;
		}
		
		/**
		 Sets the base color texture of this material to the given base color
		 texture.

		 @param[in]		base_color_texture
						A reference to the base color texture.
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

		 @param[in]		roughness
						The roughness.
		 */
		void SetRoughness(F32 roughness) noexcept {
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

		 @param[in]		metalness
						The metalness.
		 */
		void SetMetalness(F32 metalness) noexcept {
			m_metalness = metalness;
		}

		/**
		 Returns the material RGBA channels of this material.

		 @return		The material RGBA channels of this material.
		 */
		const RGBASpectrum GetMaterialRGBA() const noexcept {
			return RGBASpectrum(GetRoughness(), GetMetalness(), 0.0f, 0.0f);
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
		 The base color of this material.
		 */
		RGBASpectrum m_base_color;

		/**
		 A pointer to the base color texture of this material.
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