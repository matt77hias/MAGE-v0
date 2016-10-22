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
	class Mutex final {

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
		 Constructs a mutex from the given mutex.

		 @param[in]		mutex
						A reference to a mutex.
		 */
		Mutex(Mutex &mutex);

		/**
		 Destructs this mutex.
		 */
		~Mutex() {
			// Release all resources used by an unowned critical section object. 
			DeleteCriticalSection(&m_critical_section);
		}
		
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
	struct MutexLock final {

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

		 @param[in]		mutex_lock
						A reference to a mutex lock.
		 */
		MutexLock(const MutexLock &mutex_lock);

		/**
		 Copies the given mutex lock to this mutex lock.

		 @param[in]		mutex_lock
						A reference to a mutex lock.
		 @return		A reference to the copy of @a mutex_lock.
		 */
		MutexLock &operator=(const MutexLock &mutex_lock);

		/**
		 The mutex of this mutex lock.
		 */
		Mutex &m_mutex;
	};

	/**
	 A class of read write mutexes.
	 */
	class ReadWriteMutex final {

	public:

		/**
		 Creates a mutex.
		 */
		static ReadWriteMutex *Create() {
			return new ReadWriteMutex();
		}

		/**
		 Destroys a given read write mutex.

		 @param[in]		mutex
						The read write mutex to destroy.
		 */
		static void Destroy(ReadWriteMutex *mutex) {
			delete mutex;
		}

	private:

		friend struct ReadWriteMutexLock;

		/**
		 Constructs a read write mutex.
		 */
		ReadWriteMutex();

		/**
		 Constructs a read write mutex from the given read write mutex.

		 @param[in]		mutex
						The read write mutex.
		 */
		ReadWriteMutex(ReadWriteMutex &mutex);

		/**
		 Destructs this read write mutex.
		 */
		~ReadWriteMutex() {
			if (m_ready_to_read_handle) {
				// Close the open event handle.
				CloseHandle(m_ready_to_read_handle);
			}
			if (m_ready_to_write_handle) {
				// Close the open event handle.
				CloseHandle(m_ready_to_write_handle);
			}

			// Release all resources used by an unowned critical section object. 
			DeleteCriticalSection(&m_critical_section);
		}
		
		/**
		 Copies the given read write mutex to this read write mutex.

		 @param[in]		mutex
						A reference to a read write mutex.
		 @return		A reference to the copy of @a mutex.
		 */
		ReadWriteMutex &operator=(const ReadWriteMutex &mutex);

		/**
		 Acquires a read.
		 */
		void AcquireRead();

		/**
		 Release a read.
		 */
		void ReleaseRead();

		/**
		 Acquires a write.
		 */
		void AcquireWrite();

		/**
		 Release a write.
		 */
		void ReleaseWrite();

		/**
		 The number of writers waiting for this read write mutex lock.
		 */
		LONG m_nb_writers_waiting;

		/**
		 The number of readers waiting for this read write mutex lock.
		 */
		LONG m_nb_readers_waiting;

		/**
		 The active group of this read write mutex lock.

		 HIWORD is the flag indicating a writer is active.
		 LOWORD is the number of active readers.
		 */
		DWORD m_active_writer_readers;

		/**
		 The handle of this read write mutex lock if ready for reading.
		 */
		HANDLE m_ready_to_read_handle;

		/**
		 The handle of this read write mutex lock if ready for writing.
		 */
		HANDLE m_ready_to_write_handle;

		/**
		 The critical section object of this read write mutex.
		 */
		CRITICAL_SECTION m_critical_section;
	};

	/**
	 Type of read write mutex locks.
	 */
	enum ReadWriteMutexLockType { READ, WRITE };

	/**
	 A struct of read write mutex locks.
	 */
	struct ReadWriteMutexLock final {

		/**
		 Constructs a read write mutex lock for the given read write mutex and lock type.

		 @param[in]		mutex
						A reference to a read write mutex.
		 @param[in]		lock_type
						The lock type.
		 */
		ReadWriteMutexLock(ReadWriteMutex &mutex, ReadWriteMutexLockType lock_type) 
			: m_type(lock_type), m_mutex(mutex) {
			if (m_type == READ) {
				m_mutex.AcquireRead();
			}
			else {
				m_mutex.AcquireWrite();
			}
		}

		/**
		 Destructs this read write mutex lock.
		 */
		~ReadWriteMutexLock() {
			if (m_type == READ) {
				m_mutex.ReleaseRead();
			}
			else {
				m_mutex.ReleaseWrite();
			}
		}

		/**
		 Upgrades this read write lock to write.
		 */
		void UpgradeToWrite();

		/**
		 Downgrades this read write lock to read.
		 */
		void DowngradeToRead();

	private:

		/**
		 Constructs a read write mutex lock from the given read write mutex lock.

		 @param[in]		mutex_lock
						A reference to a read write mutex lock.
		 */
		ReadWriteMutexLock(const ReadWriteMutexLock &mutex_lock);

		/**
		 Copies the given read write mutex lock to this read write mutex lock.

		 @param[in]		mutex_lock
						A reference to a read write mutex lock.
		 @return		A reference to the copy of @a mutex_lock.
		 */
		ReadWriteMutexLock &operator=(const ReadWriteMutexLock &mutex_lock);

		/**
		 The lock type of this read write mutex lock. 
		 */
		ReadWriteMutexLockType m_type;

		/**
		 The read write mutex of this read write mutex lock. 
		 */
		ReadWriteMutex &m_mutex;
	};

	/**
	 A class of semaphores.
	 */
	class Semaphore final {

	public:

		/**
		 Constructs a semaphore.
		 */
		Semaphore();

		/**
		 Destructs this semaphore.
		 */
		~Semaphore() {
			// Closes an open object handle.
			CloseHandle(m_handle);
		}

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
						@c false otherwise.
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
	class ConditionVariable final {

	public:

		/**
		 Constructs a condition variable.
		 */
		ConditionVariable() : m_nb_waiters(0) {
			// Initialize the critical section objects
			// for the number of waiters and condition.
			InitializeCriticalSection(&m_nb_waiters_mutex);
			InitializeCriticalSection(&m_condition_mutex);

			// Creates or opens a named or unnamed event object.
			// On success, a handle to the event object is returned.
			m_events[SIGNAL] = CreateEvent(
									NULL,  // no security
									FALSE, // auto-reset event object
									FALSE, // non-signaled initial state
									NULL); // unnamed event object
			m_events[BROADCAST] = CreateEvent(
									NULL,  // no security
									TRUE,  // manual-reset event object
									FALSE, // non-signaled initial state
									NULL); // unnamed event object
		}

		/**
		 Destructs this condition variable.
		 */
		~ConditionVariable() {
			// Release all resources used by an unowned critical section object. 
			DeleteCriticalSection(&m_nb_waiters_mutex);
			DeleteCriticalSection(&m_condition_mutex);

			// Close the open event handles.
			CloseHandle(m_events[SIGNAL]);
			CloseHandle(m_events[BROADCAST]);
		}

		/**
		 Locks this condition variable.
		 */
		void Lock() {
			// Wait for ownership of the specified critical section object. 
			// The function returns when the calling thread is granted ownership.
			EnterCriticalSection(&m_condition_mutex);
		}

		/**
		 Unlocks this condition variable.
		 */
		void Unlock() {
			// Release ownership of the specified critical section object.
			LeaveCriticalSection(&m_condition_mutex);
		}

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