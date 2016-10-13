#pragma once

//void TasksInit();
//void TasksCleanup();
//
//class Task {
//public:
//	virtual ~Task();
//	virtual void Run() = 0;
//};
//
//void EnqueueTasks(const vector<Task *> &tasks);
//void WaitForAllTasks();
//
//
//void TasksInit() {
//	static const int nThreads = NumSystemCores();
//	workerSemaphore = new Semaphore;
//	tasksRunningCondition = new ConditionVariable;
//
//
//	threads = new HANDLE[nThreads];
//	for (int i = 0; i < nThreads; ++i) {
//		threads[i] = CreateThread(NULL, 0, taskEntry, reinterpret_cast<void *>(i), 0, NULL);
//		if (threads[i] == NULL)
//			Severe("Error from CreateThread");
//	}
//}
//
//
//void TasksCleanup() {
//	if (!taskQueueMutex || !workerSemaphore)
//		return;
//	{ MutexLock lock(*taskQueueMutex);
//	Assert(taskQueue.size() == 0);
//	}
//
//	static const int nThreads = NumSystemCores();
//	if (workerSemaphore != NULL)
//		workerSemaphore->Post(nThreads);
//
//	if (threads != NULL) {
//		WaitForMultipleObjects(nThreads, threads, TRUE, INFINITE);
//		for (int i = 0; i < nThreads; ++i) {
//			CloseHandle(threads[i]);
//		}
//		delete[] threads;
//		threads = NULL;
//	}
//}
//
//
//Task::~Task() {
//}
//
//
//void EnqueueTasks(const vector<Task *> &tasks) {
//	if (!threads)
//		TasksInit();
//
//	{ MutexLock lock(*taskQueueMutex);
//	for (unsigned int i = 0; i < tasks.size(); ++i)
//		taskQueue.push_back(tasks[i]);
//	}
//	tasksRunningCondition->Lock();
//	numUnfinishedTasks += tasks.size();
//	tasksRunningCondition->Unlock();
//
//	workerSemaphore->Post(tasks.size());
//}
//
//
//
//void WaitForAllTasks() {
//	if (!tasksRunningCondition)
//		return;  // no tasks have been enqueued, so TasksInit() never called
//	tasksRunningCondition->Lock();
//	while (numUnfinishedTasks > 0)
//		tasksRunningCondition->Wait();
//	tasksRunningCondition->Unlock();
//}