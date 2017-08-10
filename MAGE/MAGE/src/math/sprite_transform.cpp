//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "math\sprite_transform.hpp"
#include "rendering\renderer.hpp"
#include "logging\error.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	float ConvertNormalizedToAbsoluteScreenX(float x) {
		const Renderer * const renderer = Renderer::Get();
		Assert(renderer);

		return x * static_cast< float >(renderer->GetWidth());
	}

	float ConvertNormalizedToAbsoluteScreenY(float y) {
		const Renderer * const renderer = Renderer::Get();
		Assert(renderer);

		return y * static_cast< float >(renderer->GetHeight());
	}

	const XMVECTOR XM_CALLCONV ConvertNormalizedToAbsoluteScreen(FXMVECTOR position) {
		const Renderer * const renderer = Renderer::Get();
		Assert(renderer);

		const XMVECTOR multiplier = XMVectorSet(
			static_cast< float >(renderer->GetWidth()),
			static_cast< float >(renderer->GetHeight()),
			0.0f,
			0.0f);
		return multiplier * position;
	}

	float ConvertAbsoluteToNormalizedScreenX(float x) {
		const Renderer * const renderer = Renderer::Get();
		Assert(renderer);

		return x / static_cast< float >(renderer->GetWidth());
	}

	float ConvertAbsoluteToNormalizedScreenY(float y) {
		const Renderer * const renderer = Renderer::Get();
		Assert(renderer);

		return y / static_cast<float>(renderer->GetHeight());
	}

	const XMVECTOR XM_CALLCONV ConvertAbsoluteToNormalizedScreen(FXMVECTOR position) {
		const Renderer * const renderer = Renderer::Get();
		Assert(renderer);

		const XMVECTOR multiplier = XMVectorSet(
			1.0f / static_cast< float >(renderer->GetWidth()),
			1.0f / static_cast< float >(renderer->GetHeight()),
			0.0f,
			0.0f);
		return multiplier * position;
	}
}