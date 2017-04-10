#pragma once

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	struct SpriteFontDescriptor final {

	public:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		explicit SpriteFontDescriptor(bool force_srgb = false)
			: m_force_srgb(force_srgb) {}
		SpriteFontDescriptor(const SpriteFontDescriptor &desc) = default;
		SpriteFontDescriptor(SpriteFontDescriptor &&desc) = default;
		~SpriteFontDescriptor() = default;

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------

		SpriteFontDescriptor &operator=(const SpriteFontDescriptor &desc) = default;
		SpriteFontDescriptor &operator=(SpriteFontDescriptor &&desc) = default;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		bool ForceSRGB() const {
			return m_force_srgb;
		}

	private:

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		bool m_force_srgb;
	};
}