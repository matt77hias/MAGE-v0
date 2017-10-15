//-----------------------------------------------------------------------------F32
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "math\sprite_transform.hpp"
#include "rendering\rendering_manager.hpp"
#include "logging\error.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	F32 ConvertNormalizedToAbsoluteScreenX(F32 x) {
		const RenderingManager * const rendering_manager 
			= RenderingManager::Get();
		Assert(rendering_manager);

		return x * static_cast< F32 >(rendering_manager->GetWidth());
	}

	F32 ConvertNormalizedToAbsoluteScreenY(F32 y) {
		const RenderingManager * const rendering_manager 
			= RenderingManager::Get();
		Assert(rendering_manager);

		return y * static_cast< F32 >(rendering_manager->GetHeight());
	}

	const XMVECTOR XM_CALLCONV ConvertNormalizedToAbsoluteScreen(
		FXMVECTOR position) {
		
		const RenderingManager * const rendering_manager 
			= RenderingManager::Get();
		Assert(rendering_manager);

		const XMVECTOR multiplier = XMVectorSet(
			static_cast< F32 >(rendering_manager->GetWidth()),
			static_cast< F32 >(rendering_manager->GetHeight()),
			0.0f,
			0.0f);
		return multiplier * position;
	}

	F32 ConvertAbsoluteToNormalizedScreenX(F32 x) {
		const RenderingManager * const rendering_manager 
			= RenderingManager::Get();
		Assert(rendering_manager);

		return x / static_cast< F32 >(rendering_manager->GetWidth());
	}

	F32 ConvertAbsoluteToNormalizedScreenY(F32 y) {
		const RenderingManager * const rendering_manager 
			= RenderingManager::Get();
		Assert(rendering_manager);

		return y / static_cast< F32 >(rendering_manager->GetHeight());
	}

	const XMVECTOR XM_CALLCONV ConvertAbsoluteToNormalizedScreen(
		FXMVECTOR position) {
		
		const RenderingManager * const rendering_manager 
			= RenderingManager::Get();
		Assert(rendering_manager);

		const XMVECTOR multiplier = XMVectorSet(
			1.0f / static_cast< F32 >(rendering_manager->GetWidth()),
			1.0f / static_cast< F32 >(rendering_manager->GetHeight()),
			0.0f,
			0.0f);
		return multiplier * position;
	}
}