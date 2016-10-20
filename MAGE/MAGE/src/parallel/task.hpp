#pragma once

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	/**
	 A class of tasks.
	 */
	class Task {

	public:

		/**
		 Destructs this task.
		 */
		virtual ~Task() {}

		/*
		 Runs this task.
		 */
		virtual void Run() = 0;
	};

	/**
	 Initialize the tasks.
	 */
	void TasksInit();

	/**
	 Clean the tasks.
	 */
	void TasksCleanup();

	/**
	 Enqueues the given tasks.

	 @param[in]		tasks
					The tasks.
	 */
	void EnqueueTasks(const vector<Task *> &tasks);

	/**
	 Waits for all the tasks to finish.
	 */
	void WaitForAllTasks();
}