#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "memory\allocation.hpp"
#include "math\math.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	_declspec(align(16)) struct MaterialBuffer final : public AlignedData< MaterialBuffer > {

	public:

		MaterialBuffer() = default;
		MaterialBuffer(const MaterialBuffer &buffer) = default;
		MaterialBuffer(MaterialBuffer &&buffer) = default;
		~MaterialBuffer() = default;
		MaterialBuffer &operator=(const MaterialBuffer &buffer) = default;
		MaterialBuffer &operator=(MaterialBuffer &&buffer) = default;

		XMFLOAT3 Kd;
		float    dissolve;
		XMFLOAT3 Ks;
		float    Ns;
	};

	static_assert(sizeof(MaterialBuffer) == 32, "CPU/GPU struct mismatch");
}