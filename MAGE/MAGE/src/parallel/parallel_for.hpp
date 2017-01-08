#pragma once

#include <functional>
namespace mage {
	using std::function;
}

namespace mage {

	void ParallelFor(function< void(size_t) > func, size_t nb_work, size_t chunk_size = 1);

	extern thread_local size_t ThreadIndex;
	inline size_t MaxThreadIndex() {
		return NumberOfSystemCores();
	}

	void ParallelInit();
	void ParallelCleanup();
}