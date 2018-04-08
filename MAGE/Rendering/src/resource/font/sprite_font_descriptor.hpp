#pragma once

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage::rendering {

	/**
	 A class of sprite font descriptors.
	 */
	class SpriteFontDescriptor final {

	public:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		/**
		 Constructs a sprite font descriptor.

		 @param[in]		force_srgb
						A flag indicating whether working around gamma issues 
						is needed. 
		 */
		constexpr explicit SpriteFontDescriptor(bool force_srgb = false) noexcept
			: m_force_srgb(force_srgb) {}

		/**
		 Constructs a sprite font descriptor from the given sprite font 
		 descriptor.

		 @param[in]		desc
						A reference to the sprite font descriptor to copy.
		 */
		constexpr SpriteFontDescriptor(
			const SpriteFontDescriptor& desc) noexcept = default;

		/**
		 Constructs a sprite font descriptor by moving the given sprite font 
		 descriptor.

		 @param[in]		desc
						A reference to the sprite font descriptor to move.
		 */
		constexpr SpriteFontDescriptor(
			SpriteFontDescriptor&& desc) noexcept = default;

		/**
		Destructs this sprite font descriptor.
		*/
		~SpriteFontDescriptor() = default;

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------

		/**
		 Copies the given sprite font descriptor to this sprite font 
		 descriptor.

		 @param[in]		desc
						A reference to the sprite font descriptor to copy.
		 @return		A reference to the copy of the given sprite font 
						descriptor (i.e. this sprite font descriptor).
		 */
		constexpr SpriteFontDescriptor& operator=(
			const SpriteFontDescriptor& desc) noexcept = default;

		/**
		 Moves the given sprite font descriptor to this sprite font descriptor.

		 @param[in]		desc
						A reference to the sprite font descriptor to move.
		 @return		A reference to the moved sprite font descriptor (i.e. 
						this sprite font descriptor).
		 */
		constexpr SpriteFontDescriptor& operator=(
			SpriteFontDescriptor&& desc) noexcept = default;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Checks whether working around gamma issues is needed according to this 
		 sprite font descriptor.

		 @return		@c true if working around gamma issues is needed. 
						@c false if not.
		 */
		[[nodiscard]]
		bool ForceSRGB() const noexcept {
			return m_force_srgb;
		}

	private:

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		/**
		 A flag indicating whether working around gamma issues is needed for 
		 this sprite font descriptor. 
		 
		 This is helpful for color fonts that are in the sRGB or similar color 
		 space but are not encoded explicitly as a SRGB format.
		 */
		bool m_force_srgb;
	};
}