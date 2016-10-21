#pragma once

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	// Forward declarations
	struct MutexLock;
	struct ReadWriteMutexLock;

	/**
	 A class of mutexes.
	 */
	class Mutex {

	public:

		/**
		 Creates a mutex.
		 */
		static Mutex *Create() {
			return new Mutex();
		}

		/**
		 Destroys a given mutex.

		 @param[in]		mutex
						The mutex to destroy.
		 */
		static void Destroy(Mutex *mutex) {
			delete mutex;
		}

	private:
		friend struct MutexLock;

		/**
		 Constructs a mutex.
		 */
		Mutex() {
			// Initialize a critical section object.
			InitializeCriticalSection(&m_critical_section);
		}

		/**
		 Destructs this mutex.
		 */
		~Mutex() {
			// Release all resources used by an unowned critical section object. 
			DeleteCriticalSection(&m_critical_section);
		}
		
		/**
		 Constructs a mutex from the given mutex.

		 @param[in]		mutex
						A reference to a mutex.
		 */
		Mutex(Mutex &mutex);

		/**
		 Copies the given mutex to this mutex.

		 @param[in]		mutex
						A reference to a mutex.
		 @return		A reference to the copy of @a mutex.
		 */
		Mutex &operator=(const Mutex &mutex);

		/**
		 The critical section object of this mutex.
		 */
		CRITICAL_SECTION m_critical_section;
	};

	/**
	 A struct of mutex locks.
	 */
	struct MutexLock {

		/**
		 Constructs a mutex lock for the given mutex.

		 @param[in]		mutex
						A reference to a mutex.
		 */
		MutexLock(Mutex &mutex) : m_mutex(mutex) {
			// Wait for ownership of the specified critical section object. 
			// The function returns when the calling thread is granted ownership.
			EnterCriticalSection(&m_mutex.m_critical_section);
		}

		/**
		 Destructs this mutex lock.
		 */
		~MutexLock() {
			// Release ownership of the specified critical section object.
			LeaveCriticalSection(&m_mutex.m_critical_section);
		}

	private:

		/**
		 Constructs a mutex lock from the given mutex lock.

		 @param[in]		mutex lock
						A reference to a mutex lock.
		 */
		MutexLock(const MutexLock &mutex_lock);

		/**
		 Copies the given mutex lock to this mutex lock.

		 @param[in]		mutex_lock
						A reference to a mutex lock.
		 @return		A reference to the copy of @a mutex lock.
		 */
		MutexLock &operator=(const MutexLock &mutex_lock);

		/**
		 The mutex of this mutex lock.
		 */
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

	/**
	 A class of semaphores.
	 */
	class Semaphore {

	public:

		/**
		 Constructs a semaphore.
		 */
		Semaphore();

		/**
		 Destructs this semaphore.
		 */
		~Semaphore();

		/**
		 Increments the value of this semaphore variable by the given value.
		 
		 The process executing wait is blocked until the value of the semaphore 
		 is greater or equal to 1.

		 @param[in]		count
						The increment value.
		 */
		void Post(uint32_t count = 1);
		
		/**
		 Decrements the value of this semaphore variable by one.

		 If the initial value of the semaphore is negative, the waiting queue is not
		 empty and thus one blocked process can be transferred to the ready queue.

		 */
		void Wait();
		
		/**
		 Checks whether waiting for this semaphore would be necessary.

		 @return		@c true if waiting for this semaphore would be necessary.
						@f otherwise.
		 */
		bool TryWait();

	private:

		/**
		 The handle of this semaphore.
		 */
		HANDLE m_handle;
	};

	/**
	 A class of condition variables.
	 */
	class ConditionVariable {

	public:

		/**
		 Constructs a condition variable.
		 */
		ConditionVariable();

		/**
		 Destructs this condition variable.
		 */
		~ConditionVariable();

		/**
		 Locks this condition variable.
		 */
		void Lock();

		/**
		 Unlocks this condition variable.
		 */
		void Unlock();

		/**
		 Wait for a signal indicating a condition change.
		 */
		void Wait();

		/**
		 Signal a condition change.
		 */
		void Signal();

	private:

		/** 
		 The number of waiters of this condition variable.
		 */
		uint32_t m_nb_waiters;

		/**
		 The critical section object for the mutex guarding @c m_nb_waiters
		 of this condition variable.
		 */
		CRITICAL_SECTION m_nb_waiters_mutex;

		/**
		 The critical section object for the mutex guarding the condition
		 of this condition variable.
		 */
		CRITICAL_SECTION m_condition_mutex;

		/**
		 Type of events (indices).
		 */
		enum { SIGNAL = 0, BROADCAST = 1, NUM_EVENTS = 2 };

		/**
		 Signal and broadcast event handles of this condition variable.
		 */
		HANDLE m_events[NUM_EVENTS];
	};
}