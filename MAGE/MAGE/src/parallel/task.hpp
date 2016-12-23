#pragma once

//-----------------------------------------------------------------------------
// Engine Declarations
//-----------------------------------------------------------------------------
namespace mage {

class Task {

	public:

		virtual ~Task() {}

		virtual void Run() = 0;
	};

void TasksInit();

void TasksCleanup();

void EnqueueTasks(const vector< Task * > &tasks);

void WaitForAllTasks();

}