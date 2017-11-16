#pragma once

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	/**
	 A struct of sprite font descriptors.
	 */
	struct SpriteFontDescriptor final {

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
		explicit SpriteFontDescriptor(bool force_srgb = false)
			: m_force_srgb(force_srgb) {}

		/**
		 Constructs a sprite font descriptor from the given sprite font 
		 descriptor.

		 @param[in]		desc
						A reference to the sprite font descriptor to copy.
		 */
		SpriteFontDescriptor(const SpriteFontDescriptor &desc) = default;

		/**
		 Constructs a sprite font descriptor by moving the given sprite font 
		 descriptor.

		 @param[in]		desc
						A reference to the sprite font descriptor to move.
		 */
		SpriteFontDescriptor(SpriteFontDescriptor &&desc) = default;

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
		SpriteFontDescriptor &operator=(
			const SpriteFontDescriptor &desc) = default;

		/**
		 Moves the given sprite font descriptor to this sprite font descriptor.

		 @param[in]		desc
						A reference to the sprite font descriptor to move.
		 @return		A reference to the moved sprite font descriptor (i.e. 
						this sprite font descriptor).
		 */
		SpriteFontDescriptor &operator=(
			SpriteFontDescriptor &&desc) = default;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Checks whether working around gamma issues is needed according to this 
		 sprite font descriptor.

		 @return		@c true if working around gamma issues is needed. 
						@c false if not.
		 */
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
		 space but are not encoded explicitly as an SRGB format.
		 */
		bool m_force_srgb;
	};
}