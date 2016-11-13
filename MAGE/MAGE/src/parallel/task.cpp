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

	/**
	 The thread handles.
	 */
	static HANDLE *threads;
	
	/**
	 The mutex for exclusive access to the task queue.
	 */
	static Mutex *task_queue_mutex = Mutex::Create();

	/**
	 The task queue.
	 */
	static vector<Task *> task_queue;
	
	/**
	 The worker semaphore for being able to work.
	 */
	static Semaphore *worker_semaphore;
	
	/**
	 The number of unfinished tasks.
	 */
	static uint32_t nb_unfinished_tasks;

	/**
	 The running condition variable for exclusive
	 access to the number of unfinished tasks
	 and for signaling on updates. 
	 */
	static ConditionVariable *tasks_running_condition;

	/**
	 An application-defined function that serves as the starting address for a thread.
	
	 @param[in]		lpParameter
					The thread data passed to the function using 
					the @c lpParameter parameter of CreateThread.
	 @return		A value indicating success or failure.
	 */
	static DWORD WINAPI task_entry(LPVOID lpParameter) {
		// Supresses C4100: unreferenced formal parameter
		(void)lpParameter;

		while (true) {
			// Wait if no workers needed anymore.
			worker_semaphore->Wait();
			
			// Try to get a task from the task queue.
			Task *task = nullptr;
			{
				MutexLock lock(*task_queue_mutex);
				if (task_queue.size() == 0) {
					// Error: there should always be a task
					// available (due to worker_semaphore)
					break;
				}
				task = task_queue.back();
				task_queue.pop_back();
			}

			// Run the task.
			task->Run();
			
			// Decrease the number of tasks to execute.
			tasks_running_condition->Lock();
			--nb_unfinished_tasks;
			if (nb_unfinished_tasks == 0) {
				// Signal on all tasks finished.
				tasks_running_condition->Signal();
			}
			tasks_running_condition->Unlock();
		}
		return 0;
	}

	void TasksInit() {
		static const uint32_t nb_threads = NumberOfSystemCores();
		worker_semaphore = new Semaphore();
		tasks_running_condition = new ConditionVariable();

		threads = new HANDLE[nb_threads];
		for (size_t i = 0; i < nb_threads; ++i) {
			// 1. The returned handle cannot be inherited by child processes.
			// 2. The new thread uses the default size for the executable.
			// 3. A pointer to the application-defined function to be executed by the thread.
			// 4. A pointer to a variable to be passed to the thread (thread number).
			// 5. Flag specifying that the thread runs immediately after creation.
			// 6. The thread identifier will not be returned.
			threads[i] = CreateThread(nullptr, 0, task_entry, reinterpret_cast<void *>(i), 0, nullptr);
			if (threads[i] == nullptr) {
				Severe("Error from CreateThread");
			}
		}
	}

	void TasksCleanup() {
		if (!task_queue_mutex || !worker_semaphore) {
			return;
		}

		{
			// Check the queue.
			MutexLock lock(*task_queue_mutex);
			Assert(task_queue.size() == 0);
		}

		static const uint32_t nb_threads = NumberOfSystemCores();
		if (worker_semaphore != nullptr) {
			// Request workers.
			worker_semaphore->Post(nb_threads);
		}

		if (threads != nullptr) {
			// Wait until one or all of the specified objects are 
			// in the signaled state (available for use) or the time-out interval elapses.
			// 1. The number of object handles.
			// 2. An array of object handles.
			// 3. The function returns when the state of all objects is signaled.
			// 4. The function will return only when the specified objects are signaled.
			WaitForMultipleObjects(nb_threads, threads, TRUE, INFINITE);
			
			for (size_t i = 0; i < nb_threads; ++i) {
				// Closes an open object handle.
				CloseHandle(threads[i]);
			}
			delete[] threads;
			threads = nullptr;
		}
	}

	void EnqueueTasks(const vector<Task *> &tasks) {
		if (!threads) {
			// Initialize tasks.
			TasksInit();
		}

		{
			// Add tasks to the queue.
			MutexLock lock(*task_queue_mutex);
			for (size_t i = 0; i < tasks.size(); ++i) {
				task_queue.push_back(tasks[i]);
			}
		}

		// Increase the number of tasks to execute.
		tasks_running_condition->Lock();
		nb_unfinished_tasks += (uint32_t)tasks.size();
		tasks_running_condition->Unlock();

		// Request workers.
		worker_semaphore->Post((uint32_t)tasks.size());
	}

	void WaitForAllTasks() {
		if (!tasks_running_condition) {
			// No tasks have been enqueued (TasksInit() never called)
			return;
		}

		// Wait for completion.
		tasks_running_condition->Lock();
		// Wait for all tasks to finish.
		while (nb_unfinished_tasks > 0) {
			tasks_running_condition->Wait();
		}
		tasks_running_condition->Unlock();
	}
}