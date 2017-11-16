//-----------------------------------------------------------------------------F32
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "math\sprite_transform.hpp"
#include "rendering\display_configuration.hpp"
#include "utils\logging\error.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	F32 ConvertNormalizedToAbsoluteScreenX(F32 x) {
		const DisplayConfiguration * const config = DisplayConfiguration::Get();
		Assert(config);

		return x * static_cast< F32 >(config->GetDisplayWidth());
	}

	F32 ConvertNormalizedToAbsoluteScreenY(F32 y) {
		const DisplayConfiguration * const config = DisplayConfiguration::Get();
		Assert(config);

		return y * static_cast< F32 >(config->GetDisplayHeight());
	}

	const XMVECTOR XM_CALLCONV ConvertNormalizedToAbsoluteScreen(
		FXMVECTOR position) {
		
		const DisplayConfiguration * const config = DisplayConfiguration::Get();
		Assert(config);

		const XMVECTOR multiplier = XMVectorSet(
			static_cast< F32 >(config->GetDisplayWidth()),
			static_cast< F32 >(config->GetDisplayHeight()),
			0.0f,
			0.0f);
		return multiplier * position;
	}

	F32 ConvertAbsoluteToNormalizedScreenX(F32 x) {
		const DisplayConfiguration * const config = DisplayConfiguration::Get();
		Assert(config);

		return x / static_cast< F32 >(config->GetDisplayWidth());
	}

	F32 ConvertAbsoluteToNormalizedScreenY(F32 y) {
		const DisplayConfiguration * const config = DisplayConfiguration::Get();
		Assert(config);

		return y / static_cast< F32 >(config->GetDisplayHeight());
	}

	const XMVECTOR XM_CALLCONV ConvertAbsoluteToNormalizedScreen(
		FXMVECTOR position) {
		
		const DisplayConfiguration * const config = DisplayConfiguration::Get();
		Assert(config);

		const XMVECTOR multiplier = XMVectorSet(
			1.0f / static_cast< F32 >(config->GetDisplayWidth()),
			1.0f / static_cast< F32 >(config->GetDisplayHeight()),
			0.0f,
			0.0f);
		return multiplier * position;
	}
}