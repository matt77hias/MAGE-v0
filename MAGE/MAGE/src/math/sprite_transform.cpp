//-----------------------------------------------------------------------------F32
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

	F32 ConvertNormalizedToAbsoluteScreenX(F32 x) {
		const Renderer * const renderer = Renderer::Get();
		Assert(renderer);

		return x * static_cast< F32 >(renderer->GetWidth());
	}

	F32 ConvertNormalizedToAbsoluteScreenY(F32 y) {
		const Renderer * const renderer = Renderer::Get();
		Assert(renderer);

		return y * static_cast< F32 >(renderer->GetHeight());
	}

	const XMVECTOR XM_CALLCONV ConvertNormalizedToAbsoluteScreen(
		FXMVECTOR position) {
		
		const Renderer * const renderer = Renderer::Get();
		Assert(renderer);

		const XMVECTOR multiplier = XMVectorSet(
			static_cast< F32 >(renderer->GetWidth()),
			static_cast< F32 >(renderer->GetHeight()),
			0.0f,
			0.0f);
		return multiplier * position;
	}

	F32 ConvertAbsoluteToNormalizedScreenX(F32 x) {
		const Renderer * const renderer = Renderer::Get();
		Assert(renderer);

		return x / static_cast< F32 >(renderer->GetWidth());
	}

	F32 ConvertAbsoluteToNormalizedScreenY(F32 y) {
		const Renderer * const renderer = Renderer::Get();
		Assert(renderer);

		return y / static_cast< F32 >(renderer->GetHeight());
	}

	const XMVECTOR XM_CALLCONV ConvertAbsoluteToNormalizedScreen(
		FXMVECTOR position) {
		
		const Renderer * const renderer = Renderer::Get();
		Assert(renderer);

		const XMVECTOR multiplier = XMVectorSet(
			1.0f / static_cast< F32 >(renderer->GetWidth()),
			1.0f / static_cast< F32 >(renderer->GetHeight()),
			0.0f,
			0.0f);
		return multiplier * position;
	}
}