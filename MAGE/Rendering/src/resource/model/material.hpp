#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "math_utils.hpp"
#include "spectrum\spectrum.hpp"
#include "resource\texture\texture.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage::rendering {

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

		 @param[in]		name
						The name of the material.		
		 */
		explicit Material(std::string name = "material")
			: m_base_color(RGBA(1.0f)),
			m_base_color_texture(),
			m_roughness(0.5f),
			m_metalness(0.0f),
			m_material_texture(),
			m_normal_texture(),
			m_transparent(false),
			m_radiance(0.0f),
			m_name(std::move(name)) {}
		
		/**
		 Constructs a material from the given material.

		 @param[in]		material
						A reference to the material to copy.
		 */
		Material(const Material& material) = default;
		
		/**
		 Constructs a material by moving the given material.
		 
		 @param[in]		material
						A reference to the material to move.
		 */
		Material(Material&& material) noexcept = default;
		
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
		Material& operator=(const Material& material) = default;

		/**
		 Moves the given material to this material.

		 @param[in]		material
						A reference to the material to move.
		 @return		A reference to the moved material (i.e. this material).
		 */
		Material& operator=(Material&& material) noexcept = default;

		//---------------------------------------------------------------------
		// Member Methods: Base Color and Base Color Texture
		//---------------------------------------------------------------------

		/**
		 Returns the (linear) base color of this material.

		 @return		A reference to the (linear) base color of this material.
		 */
		[[nodiscard]]
		RGBA& GetBaseColor() noexcept {
			return m_base_color;
		}

		/**
		 Returns the (linear) base color of this material.

		 @return		A reference to the (linear) base color of this material.
		 */
		[[nodiscard]]
		const RGBA& GetBaseColor() const noexcept {
			return m_base_color;
		}

		/**
		 Returns the base color texture of this material.

		 @return		A pointer to the base color texture of this material.
		 */
		[[nodiscard]]
		TexturePtr GetBaseColorTexture() const noexcept {
			return m_base_color_texture;
		}
		
		/**
		 Returns the shader resource view of the base color texture of this 
		 material.

		 @return		@c nullptr, if this material has no base color texture.
		 @return		A pointer to the shader resource view of the base color 
						texture of this material.
		 */
		[[nodiscard]]
		ID3D11ShaderResourceView* GetBaseColorSRV() const noexcept {
			return m_base_color_texture ? m_base_color_texture->Get() : nullptr;
		}
		
		/**
		 Sets the base color texture of this material to the given base color 
		 texture.

		 @param[in]		base_color_texture
						A pointer to the base color texture.
		 */
		void SetBaseColorTexture(TexturePtr base_color_texture) noexcept {
			m_base_color_texture = std::move(base_color_texture);
		}
		
		//---------------------------------------------------------------------
		// Member Variables: Material Parameters
		//---------------------------------------------------------------------

		/**
		 Returns the roughness of this material.
		
		 @return		The roughness of this material.			
		 */
		[[nodiscard]]
		F32 GetRoughness() const noexcept {
			return m_roughness;
		}

		/**
		 Sets the roughness of this material to the given value.

		 @param[in]		roughness
						The roughness.
		 */
		void SetRoughness(F32 roughness) noexcept {
			m_roughness = Saturate(roughness);
		}

		/**
		 Returns the metalness of this material.

		 @return		The metalness of this material.			
		 */
		[[nodiscard]]
		F32 GetMetalness() const noexcept {
			return m_metalness;
		}

		/**
		 Sets the metalness of this material to the given value.

		 @param[in]		metalness
						The metalness.
		 */
		void SetMetalness(F32 metalness) noexcept {
			m_metalness = Saturate(metalness);
		}

		/**
		 Returns the material RGBA channels of this material.

		 @return		The material RGBA channels of this material.
		 */
		[[nodiscard]]
		const RGBA GetMaterialRGBA() const noexcept {
			return { GetRoughness(), GetMetalness(), 0.0f, 0.0f };
		}

		/**
		 Returns the material texture of this material.

		 @return		A pointer to the material texture of this material.
		 */
		[[nodiscard]]
		TexturePtr GetMaterialTexture() const noexcept {
			return m_material_texture;
		}
		
		/**
		 Returns the shader resource view of the material texture of this 
		 material.

		 @return		@c nullptr, if this material has no material texture.
		 @return		A pointer to the shader resource view of the material 
						texture of this material.
		 */
		[[nodiscard]]
		ID3D11ShaderResourceView* GetMaterialSRV() const noexcept {
			return m_material_texture ? m_material_texture->Get() : nullptr;
		}

		/**
		 Sets the material texture of this material to the given material 
		 texture.

		 @param[in]		material_texture
						A pointer to the material texture.
		 */
		void SetMaterialTexture(TexturePtr material_texture) noexcept {
			m_material_texture = std::move(material_texture);
		}

		//---------------------------------------------------------------------
		// Member Methods: Normal Texture
		//---------------------------------------------------------------------
		
		/**
		 Returns the normal texture of this material.

		 @return		A pointer to the normal texture of this material.
		 */
		[[nodiscard]]
		TexturePtr GetNormalTexture() const noexcept {
			return m_normal_texture;
		}
		
		/**
		 Returns the shader resource view of the normal texture of this 
		 material.

		 @return		@c nullptr, if this material has no normal texture.
		 @return		A pointer to the shader resource view of the normal 
						texture of this material.
		 */
		[[nodiscard]]
		ID3D11ShaderResourceView* GetNormalSRV() const noexcept {
			return m_normal_texture ? m_normal_texture->Get() : nullptr;
		}

		/**
		 Sets the normal texture of this material to the given normal texture.

		 @param[in]		normal_texture
						The normal texture.
		 */
		void SetNormalTexture(TexturePtr normal_texture) {
			m_normal_texture = std::move(normal_texture);
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
		[[nodiscard]]
		bool IsOpaque() const noexcept {
			return !IsTransparant();
		}
		
		/**
		 Checks whether this material is transparent (i.e. contains alpha 
		 channel not equal to 1.0).

		 @return		@c true if and only if this material is transparent.
						@c false otherwise.
		 */
		[[nodiscard]]
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
		// Member Methods: Emission Parameters
		//---------------------------------------------------------------------

		/**
		 Returns the radiance of this material.

		 @return		The radiance in watts per square meter per steradians 
						of this material.
		 */
		[[nodiscard]]
		F32 GetRadiance() const noexcept {
			return m_radiance;
		}

		/**
		 Sets the radiance of this material to the given radiance.
		 
		 @param[in]		radiance
						The radiance in watts per square meter per steradians.
		 */
		void SetRadiance(F32 radiance) noexcept {
			m_radiance = std::abs(radiance);
		}

		/**
		 Returns the radiance spectrum of this material.

		 @return		The radiance spectrum of this material.
		 */
		[[nodiscard]]
		const RGB GetRadianceSpectrum() const noexcept {
			const auto L = m_radiance * XMLoad(m_base_color);
			return RGB(XMStore< F32x3 >(L));
		}

		/**
		 Checks whether this material is emissive and acts as a black body.

		 @return		@c true if this material is emissive and acts as a 
						black body. @c false otherwise.
		 */
		[[nodiscard]]
		bool IsEmissive() const noexcept {
			return 0.0f < m_radiance;
		}

		//---------------------------------------------------------------------
		// Member Methods: Identification
		//---------------------------------------------------------------------

		/**
		 Returns the name of this material.

		 @return		A reference to the name of this material.
		 */
		[[nodiscard]]
		const std::string& GetName() const noexcept {
			return m_name;
		}
		
		/**
		 Sets the name of this material to the given name.

		 @param[in]		name
						The name.
		 */
		void SetName(std::string name) noexcept {
			m_name = std::move(name);
		}

	private:

		//---------------------------------------------------------------------
		// Member Variables: Base Color and Base Color Texture
		//---------------------------------------------------------------------

		/**
		 The (linear) base color of this material.
		 */
		RGBA m_base_color;

		/**
		 A pointer to the base color texture of this material.
		 */
		TexturePtr m_base_color_texture;

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
		TexturePtr m_material_texture;

		//---------------------------------------------------------------------
		// Member Variables: Normal Texture
		//---------------------------------------------------------------------

		/**
		 A pointer to the normal texture of this material.
		 */
		TexturePtr m_normal_texture;

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
		// Member Variables: Emission Parameters
		//---------------------------------------------------------------------

		/**
		 The radiance in watts per square meter per steradians of this 
		 material.
		 */
		F32 m_radiance;

		//---------------------------------------------------------------------
		// Member Variables: Identification
		//---------------------------------------------------------------------

		/**
		 The name of this material.
		 */
		std::string m_name;
	};
}