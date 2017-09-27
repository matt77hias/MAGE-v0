//-----------------------------------------------------------------------------f32
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

	f32 ConvertNormalizedToAbsoluteScreenX(f32 x) {
		const Renderer * const renderer = Renderer::Get();
		Assert(renderer);

		return x * static_cast< f32 >(renderer->GetWidth());
	}

	f32 ConvertNormalizedToAbsoluteScreenY(f32 y) {
		const Renderer * const renderer = Renderer::Get();
		Assert(renderer);

		return y * static_cast< f32 >(renderer->GetHeight());
	}

	const XMVECTOR XM_CALLCONV ConvertNormalizedToAbsoluteScreen(
		FXMVECTOR position) {
		
		const Renderer * const renderer = Renderer::Get();
		Assert(renderer);

		const XMVECTOR multiplier = XMVectorSet(
			static_cast< f32 >(renderer->GetWidth()),
			static_cast< f32 >(renderer->GetHeight()),
			0.0f,
			0.0f);
		return multiplier * position;
	}

	f32 ConvertAbsoluteToNormalizedScreenX(f32 x) {
		const Renderer * const renderer = Renderer::Get();
		Assert(renderer);

		return x / static_cast< f32 >(renderer->GetWidth());
	}

	f32 ConvertAbsoluteToNormalizedScreenY(f32 y) {
		const Renderer * const renderer = Renderer::Get();
		Assert(renderer);

		return y / static_cast< f32 >(renderer->GetHeight());
	}

	const XMVECTOR XM_CALLCONV ConvertAbsoluteToNormalizedScreen(
		FXMVECTOR position) {
		
		const Renderer * const renderer = Renderer::Get();
		Assert(renderer);

		const XMVECTOR multiplier = XMVectorSet(
			1.0f / static_cast< f32 >(renderer->GetWidth()),
			1.0f / static_cast< f32 >(renderer->GetHeight()),
			0.0f,
			0.0f);
		return multiplier * position;
	}
}