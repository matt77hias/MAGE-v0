#pragma once

// Forward declarations
struct MutexLock;
struct ReadWriteMutexLock;

//-----------------------------------------------------------------------------
// Mutex
//-----------------------------------------------------------------------------
class Mutex {

public:
	static Mutex *Create() {
		return new Mutex();
	}
	static void Destroy(Mutex *mutex) {
		delete mutex;
	}

private:
	friend struct MutexLock;

	Mutex() {
		InitializeCriticalSection(&m_critical_section);
	}
	~Mutex() {
		DeleteCriticalSection(&m_critical_section);
	}
	Mutex(Mutex &mutex);
	Mutex &operator=(const Mutex &mutex);

	CRITICAL_SECTION m_critical_section;
};

//-----------------------------------------------------------------------------
// MutexLock
//-----------------------------------------------------------------------------
struct MutexLock {

	MutexLock(Mutex &mutex) : m_mutex(mutex) {
		EnterCriticalSection(&m_mutex.m_critical_section);
	}
	~MutexLock() {
		LeaveCriticalSection(&m_mutex.m_critical_section);
	}

private:
	MutexLock(const MutexLock &mutex_lock);
	MutexLock &operator=(const MutexLock &mutex_lock);

	Mutex &m_mutex;
};


//-----------------------------------------------------------------------------
// ReadWriteMutex
//-----------------------------------------------------------------------------
class ReadWriteMutex {

public:
	static ReadWriteMutex *Create() {
		return new ReadWriteMutex();
	}
	static void Destroy(ReadWriteMutex *mutex) {
		delete mutex;
	}

private:
	friend struct ReadWriteMutexLock;

	ReadWriteMutex();
	~ReadWriteMutex();
	ReadWriteMutex(ReadWriteMutex &mutex);
	ReadWriteMutex &operator=(const ReadWriteMutex &mutex);

	void AcquireRead();
	void ReleaseRead();
	void AcquireWrite();
	void ReleaseWrite();

	LONG m_nb_writers_waiting;
	LONG m_nb_readers_waiting;

	// HIWORD is writer active flag;
	// LOWORD is readers active count;
	DWORD m_active_writer_readers;

	HANDLE m_ready_to_read_handle;
	HANDLE m_ready_to_write_handle;
	CRITICAL_SECTION m_critical_section;
};


//-----------------------------------------------------------------------------
// ReadWriteMutexLock
//-----------------------------------------------------------------------------
enum ReadWriteMutexLockType { READ, WRITE };

struct ReadWriteMutexLock {

	ReadWriteMutexLock(ReadWriteMutex &mutex, ReadWriteMutexLockType mutex_type);
	~ReadWriteMutexLock();
	
	void UpgradeToWrite();
	void DowngradeToRead();

private:

	ReadWriteMutexLock(const ReadWriteMutexLock &mutex);
	ReadWriteMutexLock &operator=(const ReadWriteMutexLock &mutex);
	
	ReadWriteMutexLockType m_type;
	ReadWriteMutex &m_mutex;
};

//-----------------------------------------------------------------------------
// Semaphore
//-----------------------------------------------------------------------------
class Semaphore {

public:

	Semaphore();
	~Semaphore();
	
	void Post(uint32_t count = 1);
	void Wait();
	bool TryWait();

private:

	HANDLE m_handle;
};

//-----------------------------------------------------------------------------
// ConditionVariable
//-----------------------------------------------------------------------------
class ConditionVariable {

public:

	ConditionVariable();
	~ConditionVariable();
	
	void Lock();
	void Unlock();
	void Wait();
	void Signal();

private:

	// Count of the number of waiters.
	uint32_t m_nb_waiters;
	CRITICAL_SECTION m_nb_waiters_mutex;
	CRITICAL_SECTION m_condition_mutex;

	// Signal and broadcast event HANDLEs.
	enum { SIGNAL = 0, BROADCAST = 1, NUM_EVENTS = 2 };
	HANDLE m_events[NUM_EVENTS];
};