//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "engine.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	float ConvertNormalizedToAbsoluteScreenX(float x) {
		return x * static_cast<float>(g_engine->GetRenderer()->GetWidth());
	}
	float ConvertNormalizedToAbsoluteScreenY(float y) {
		return y * static_cast<float>(g_engine->GetRenderer()->GetHeight());
	}
	const XMVECTOR ConvertNormalizedToAbsoluteScreen(const XMVECTOR &position) {
		const XMVECTOR multiplier = XMVectorSet(
			static_cast<float>(g_engine->GetRenderer()->GetWidth()),
			static_cast<float>(g_engine->GetRenderer()->GetHeight()),
			0.0f,
			0.0f);
		return multiplier * position;
	}

	float ConvertAbsoluteToNormalizedScreenX(float x) {
		return x / static_cast<float>(g_engine->GetRenderer()->GetWidth());
	}
	float ConvertAbsoluteToNormalizedScreenY(float y) {
		return y / static_cast<float>(g_engine->GetRenderer()->GetHeight());
	}
	const XMVECTOR ConvertAbsoluteToNormalizedScreen(const XMVECTOR &position) {
		const XMVECTOR multiplier = XMVectorSet(
			1.0f / static_cast<float>(g_engine->GetRenderer()->GetWidth()),
			1.0f / static_cast<float>(g_engine->GetRenderer()->GetHeight()),
			0.0f,
			0.0f);
		return multiplier * position;
	}
}