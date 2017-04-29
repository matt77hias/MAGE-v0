//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "core\engine.hpp"
#include "logging\error.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	float ConvertNormalizedToAbsoluteScreenX(float x) {
		Assert(g_engine->GetRenderer());
		
		return x * static_cast< float >(g_engine->GetRenderer()->GetWidth());
	}

	float ConvertNormalizedToAbsoluteScreenY(float y) {
		Assert(g_engine->GetRenderer());
		
		return y * static_cast< float >(g_engine->GetRenderer()->GetHeight());
	}

	const XMVECTOR ConvertNormalizedToAbsoluteScreen(const XMVECTOR &position) {
		Assert(g_engine->GetRenderer());
		
		const XMVECTOR multiplier = XMVectorSet(
			static_cast< float >(g_engine->GetRenderer()->GetWidth()),
			static_cast< float >(g_engine->GetRenderer()->GetHeight()),
			0.0f,
			0.0f);
		return multiplier * position;
	}

	float ConvertAbsoluteToNormalizedScreenX(float x) {
		Assert(g_engine->GetRenderer());

		return x / static_cast< float >(g_engine->GetRenderer()->GetWidth());
	}

	float ConvertAbsoluteToNormalizedScreenY(float y) {
		Assert(g_engine->GetRenderer());

		return y / static_cast<float>(g_engine->GetRenderer()->GetHeight());
	}

	const XMVECTOR ConvertAbsoluteToNormalizedScreen(const XMVECTOR &position) {
		Assert(g_engine->GetRenderer());

		const XMVECTOR multiplier = XMVectorSet(
			1.0f / static_cast< float >(g_engine->GetRenderer()->GetWidth()),
			1.0f / static_cast< float >(g_engine->GetRenderer()->GetHeight()),
			0.0f,
			0.0f);
		return multiplier * position;
	}
}