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
		Assert(g_engine);
		Assert(g_engine->IsLoaded());

		const Renderer * const renderer = g_engine->GetRenderer();
		Assert(renderer);
		
		return x * static_cast< float >(renderer->GetWidth());
	}

	float ConvertNormalizedToAbsoluteScreenY(float y) {
		Assert(g_engine);
		Assert(g_engine->IsLoaded());

		const Renderer * const renderer = g_engine->GetRenderer();
		Assert(renderer);
		
		return y * static_cast< float >(renderer->GetHeight());
	}

	const XMVECTOR ConvertNormalizedToAbsoluteScreen(const XMVECTOR &position) {
		Assert(g_engine);
		Assert(g_engine->IsLoaded());
		
		const Renderer * const renderer = g_engine->GetRenderer();
		Assert(renderer);
		
		const XMVECTOR multiplier = XMVectorSet(
			static_cast< float >(renderer->GetWidth()),
			static_cast< float >(renderer->GetHeight()),
			0.0f,
			0.0f);
		return multiplier * position;
	}

	float ConvertAbsoluteToNormalizedScreenX(float x) {
		Assert(g_engine);
		Assert(g_engine->IsLoaded());
		
		const Renderer * const renderer = g_engine->GetRenderer();
		Assert(renderer);

		return x / static_cast< float >(renderer->GetWidth());
	}

	float ConvertAbsoluteToNormalizedScreenY(float y) {
		Assert(g_engine);
		Assert(g_engine->IsLoaded());
		
		const Renderer * const renderer = g_engine->GetRenderer();
		Assert(renderer);

		return y / static_cast<float>(renderer->GetHeight());
	}

	const XMVECTOR ConvertAbsoluteToNormalizedScreen(const XMVECTOR &position) {
		Assert(g_engine);
		Assert(g_engine->IsLoaded());
		
		const Renderer * const renderer = g_engine->GetRenderer();
		Assert(renderer);

		const XMVECTOR multiplier = XMVectorSet(
			1.0f / static_cast< float >(renderer->GetWidth()),
			1.0f / static_cast< float >(renderer->GetHeight()),
			0.0f,
			0.0f);
		return multiplier * position;
	}
}