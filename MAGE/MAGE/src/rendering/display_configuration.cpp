//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "rendering\display_configuration.hpp"
#include "math\math_utils.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	void DisplayConfiguration::SetMSAASampleDesc(UINT nb_MSAA_samples, UINT MSAA_quality_level) noexcept {
		m_MSAA_sample_desc.Count   = Clamp(nb_MSAA_samples, 1u, 32u);
		m_MSAA_sample_desc.Quality = MSAA_quality_level;
	}

	void DisplayConfiguration::UpdateMSAASampleDesc(ID3D11Device2 *device) noexcept {
		Assert(device);
		const DXGI_FORMAT format = GetDisplayFormat();

		do {
			device->CheckMultisampleQualityLevels(
				format, m_MSAA_sample_desc.Count, &m_MSAA_sample_desc.Quality);

			if (m_MSAA_sample_desc.Quality) {
				--m_MSAA_sample_desc.Quality;
				break;
			}

			--m_MSAA_sample_desc.Count;

		} while (true);
	}
}