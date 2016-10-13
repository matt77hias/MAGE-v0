#pragma once

//-----------------------------------------------------------------------------
// Task
//-----------------------------------------------------------------------------
class Task {

public:
	virtual ~Task() {}
	virtual void Run() = 0;
};

//-----------------------------------------------------------------------------
// Declarations and Definitions
//-----------------------------------------------------------------------------
void TasksInit();
void TasksCleanup();

void EnqueueTasks(const vector<Task *> &tasks);
void WaitForAllTasks();