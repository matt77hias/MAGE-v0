//-----------------------------------------------------------------------------
// System Includes
//-----------------------------------------------------------------------------
#pragma region

#include <mutex>
namespace mage {
	using std::mutex;
	using std::lock_guard;
	using std::unique_lock;
}

#include <condition_variable>
namespace mage {
	using std::condition_variable;
}

#include <thread>
namespace mage {
	using std::thread;
}

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "engine.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	class ParallelForLoop {
	public:
		ParallelForLoop(function< void(size_t) > func, size_t max_index, size_t chunk_size)
			: func(std::move(func)), m_next_index(0), m_max_index(max_index), m_chunk_size(chunk_size),
			m_next(nullptr), m_active_workers(0) {}

		bool IsFinished() const {
			return m_next_index >= m_max_index && m_active_workers == 0;
		}
		
	public:
		function< void(size_t) > func;
		size_t m_next_index;
		const size_t m_max_index;
		const size_t m_chunk_size;
		ParallelForLoop *m_next;
		size_t m_active_workers;
	};

	static vector< thread > workers;
	static bool shutdown_workers = false;
	static ParallelForLoop *work_list = nullptr;
	static mutex work_list_mutex;
	static condition_variable work_list_condition;
	/*
	static void WorkerThreadFunc(int index, std::shared_ptr<Barrier> barrier) {
		ThreadIndex = index;

		// Give the profiler a chance to do per-thread initialization for
		// the worker thread before the profiling system actually stops running.
		ProfilerWorkerThreadInit();

		// The main thread sets up a barrier so that it can be sure that all
		// workers have called ProfilerWorkerThreadInit() before it continues
		// (and actually starts the profiling system).
		barrier->Wait();

		// Release our reference to the Barrier so that it's freed once all of
		// the threads have cleared it.
		barrier.reset();

		std::unique_lock<std::mutex> lock(workListMutex);
		while (!shutdownThreads) {
			if (reportWorkerStats) {
				ReportThreadStats();
				if (--reporterCount == 0)
					// Once all worker threads have merged their stats, wake up
					// the main thread.
					reportDoneCondition.notify_one();
				// Now sleep again.
				workListCondition.wait(lock);
			}
			else if (!workList) {
				// Sleep until there are more tasks to run
				workListCondition.wait(lock);
			}
			else {
				// Get work from _workList_ and run loop iterations
				ParallelForLoop &loop = *workList;

				// Run a chunk of loop iterations for _loop_

				// Find the set of loop iterations to run next
				int64_t indexStart = loop.nextIndex;
				int64_t indexEnd = min(indexStart + loop.chunkSize, loop.maxIndex);

				// Update _loop_ to reflect iterations this thread will run
				loop.nextIndex = indexEnd;
				if (loop.nextIndex == loop.maxIndex) workList = loop.next;
				loop.activeWorkers++;

				// Run loop indices in _[indexStart, indexEnd)_
				lock.unlock();
				for (int64_t index = indexStart; index < indexEnd; ++index) {
					if (loop.func1D) {
						loop.func1D(index);
					}
				}
				lock.lock();

				// Update _loop_ to reflect completion of iterations
				loop.activeWorkers--;
				if (loop.Finished()) workListCondition.notify_all();
			}
		}
	}

	void ParallelFor(std::function<void(size_t)> func, size_t nb_work, size_t chunk_size) {
		// Check whether current thread should run this loop.
		if (nb_work < chunk_size) {
			for (size_t i = 0; i < nb_work; ++i) {
				func(i);
			}
			return;
		}

		// Create ParallelForLoop for this loop.
		ParallelForLoop loop(std::move(func), nb_work, chunk_size);
		
		// Enqueue ParallelForLoop for this loop.
		{
			lock_guard< mutex > lock(work_list_mutex);
			loop.m_next = work_list; //LIFO (DFS)
			work_list = &loop;
		}

		// Notify worker threads of work to be done
		unique_lock< mutex > lock(work_list_mutex);
		work_list_condition.notify_all();

		// Contribution of the current thread.
		while (!loop.IsFinished()) {
			// Find the set of loop iterations to run next
			const size_t index_start = loop.m_next_index;
			const size_t index_end = min(index_start + loop.m_chunk_size, loop.m_max_index);
			loop.m_next_index = index_end;
			if (loop.m_next_index == loop.m_max_index) {
				work_list = loop.m_next;
			}
			
			loop.m_active_workers++;
			lock.unlock();

			for (size_t i = index_start; i < index_end; ++i) {
				if (loop.func) {
					loop.func(i);
				}
			}

			lock.lock();
			loop.m_active_workers--;
		}
	}

	void ParallelInit() {
		if (!workers.empty()) {
			return;
		}
		
		const size_t nb_threads = MaxThreadIndex();
		ThreadIndex = 0;

		// Create a barrier so that we can be sure all worker threads get past
		// their call to ProfilerWorkerThreadInit() before we return from this
		// function.  In turn, we can be sure that the profiling system isn't
		// started until after all worker threads have done that.
		std::shared_ptr<Barrier> barrier = std::make_shared<Barrier>(nb_threads);

		// Launch one fewer worker thread than the total number, 
		// since the main thread helps out, too.
		for (size_t i = 1; i < nb_threads; ++i) {
			workers.push_back(thread(WorkerThreadFunc, i, barrier));
		}

		barrier->Wait();
	}

	void ParallelCleanup() {
		if (workers.empty()) {
			return;
		}

		{
			// lock_guard wraps a mutex and can be (un)locked only once.
			lock_guard< mutex > lock(work_list_mutex);
			shutdown_workers = true;
			work_list_condition.notify_all();
		}

		for (thread &worker : workers) {
			worker.join();
		}

		workers.erase(workers.begin(), workers.end());
		shutdown_workers = false;
	}
	*/
}