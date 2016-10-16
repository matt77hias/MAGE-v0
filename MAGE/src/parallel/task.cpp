//-----------------------------------------------------------------------------
// Includes
//-----------------------------------------------------------------------------
#include "stdafx.h"

//-----------------------------------------------------------------------------
// Declarations and Definitions
//-----------------------------------------------------------------------------
static HANDLE *threads;
static Mutex *task_queue_mutex = Mutex::Create();
static std::vector<Task *> task_queue;
static Semaphore *worker_semaphore;
static uint32_t nb_unfinished_tasks;
static ConditionVariable *tasks_running_condition;

static DWORD WINAPI task_entry(LPVOID) {
	while (true) {
		worker_semaphore->Wait();
		// Try to get task from task queue
		Task *my_task = NULL;
		{ 
			MutexLock lock(*task_queue_mutex);
			if (task_queue.size() == 0) {
				break;
			}
			my_task = task_queue.back();
			task_queue.pop_back();
		}

		my_task->Run();
		tasks_running_condition->Lock();
		int unfinished = --nb_unfinished_tasks;
		if (unfinished == 0) {
			tasks_running_condition->Signal();
		}
		tasks_running_condition->Unlock();
	}
	return 0;
}

void TasksInit() {
	static const int nb_threads = NumberOfSystemCores();
	worker_semaphore = new Semaphore();
	tasks_running_condition = new ConditionVariable();

	threads = new HANDLE[nb_threads];
	for (size_t i = 0; i < nb_threads; ++i) {
		threads[i] = CreateThread(NULL, 0, task_entry, reinterpret_cast<void *>(i), 0, NULL);
		if (threads[i] == NULL) {
			Severe("Error from CreateThread");
		}
	}
}

void TasksCleanup() {
	if (!task_queue_mutex || !worker_semaphore) {
		return;
	}
	
	{ 
		MutexLock lock(*task_queue_mutex);
		Assert(task_queue.size() == 0);
	}

	static const int nb_threads = NumberOfSystemCores();
	if (worker_semaphore != NULL) {
		worker_semaphore->Post(nb_threads);
	}

	if (threads != NULL) {
		WaitForMultipleObjects(nb_threads, threads, TRUE, INFINITE);
		for (size_t i = 0; i < nb_threads; ++i) {
			CloseHandle(threads[i]);
		}
		delete[] threads;
		threads = NULL;
	}
}

void EnqueueTasks(const vector<Task *> &tasks) {
	if (!threads) {
		TasksInit();
	}

	{ 
		MutexLock lock(*task_queue_mutex);
		for (size_t i = 0; i < tasks.size(); ++i) {
			task_queue.push_back(tasks[i]);
		}
	}
	tasks_running_condition->Lock();
	nb_unfinished_tasks += (uint32_t)tasks.size();
	tasks_running_condition->Unlock();

	worker_semaphore->Post((uint32_t)tasks.size());
}

void WaitForAllTasks() {
	if (!tasks_running_condition) {
		// no tasks have been enqueued, so TasksInit() never called
		return;
	}
	tasks_running_condition->Lock();
	while (nb_unfinished_tasks > 0) {
		tasks_running_condition->Wait();
	}
	tasks_running_condition->Unlock();
}
