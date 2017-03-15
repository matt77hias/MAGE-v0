#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "platform\windows.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// System Includes
//-----------------------------------------------------------------------------
#pragma region

#include <stdint.h>

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	/**
	 A class of mutexes.
	 */
	class Mutex final {

	friend struct MutexLock;

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

		/**
		 Constructs a mutex.
		 */
		Mutex();

		/**
		 Constructs a mutex from the given mutex.

		 @param[in]		mutex
						A reference to a mutex.
		 */
		Mutex(const Mutex &mutex) = delete;

		/**
		 Destructs this mutex.
		 */
		~Mutex();
		
		/**
		 Copies the given mutex to this mutex.

		 @param[in]		mutex
						A reference to a mutex.
		 @return		A reference to the copy of the given mutex 
						(i.e. this mutex).
		 */
		Mutex &operator=(const Mutex &mutex) = delete;

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
		MutexLock(Mutex &mutex);

		/**
		 Destructs this mutex lock.
		 */
		~MutexLock();

	private:

		/**
		 Constructs a mutex lock from the given mutex lock.

		 @param[in]		mutex_lock
						A reference to a mutex lock.
		 */
		MutexLock(const MutexLock &mutex_lock) = delete;

		/**
		 Copies the given mutex lock to this mutex lock.

		 @param[in]		mutex_lock
						A reference to a mutex lock.
		 @return		A reference to the copy of the given mutex lock 
						(i.e. this mutex lock)
		 */
		MutexLock &operator=(const MutexLock &mutex_lock) = delete;

		/**
		 The mutex of this mutex lock.
		 */
		Mutex &m_mutex;
	};

	/**
	 A class of read write mutexes.
	 */
	class ReadWriteMutex final {

	friend struct ReadWriteMutexLock;

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

		/**
		 Constructs a read write mutex.
		 */
		ReadWriteMutex();

		/**
		 Constructs a read write mutex from the given read write mutex.

		 @param[in]		mutex
						The read write mutex.
		 */
		ReadWriteMutex(const ReadWriteMutex &mutex) = delete;

		/**
		 Destructs this read write mutex.
		 */
		~ReadWriteMutex();
		
		/**
		 Copies the given read write mutex to this read write mutex.

		 @param[in]		mutex
						A reference to a read write mutex.
		 @return		A reference to the copy of @a mutex.
		 */
		ReadWriteMutex &operator=(const ReadWriteMutex &mutex) = delete;

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
		ReadWriteMutexLock(ReadWriteMutex &mutex, ReadWriteMutexLockType lock_type);

		/**
		 Destructs this read write mutex lock.
		 */
		~ReadWriteMutexLock();

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
		ReadWriteMutexLock(const ReadWriteMutexLock &mutex_lock) = delete;

		/**
		 Copies the given read write mutex lock to this read write mutex lock.

		 @param[in]		mutex_lock
						A reference to a read write mutex lock.
		 @return		A reference to the copy of the given mutex lock
						(i.e. this mutex lock).
		 */
		ReadWriteMutexLock &operator=(const ReadWriteMutexLock &mutex_lock) = delete;

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
						@c false otherwise.
		 */
		bool TryWait();

	private:

		/**
		 Constructs a semaphore from the given semaphore.

		 @param[in]		semaphore
						A reference to a semaphore.
		 */
		Semaphore(const Semaphore &semaphore) = delete;

		/**
		 Copies the given semaphore to this semaphore.

		 @param[in]		semaphore
						A reference to a semaphore.
		 @return		A reference to the copy of the given semaphore
						(i.e. this semaphore)
		 */
		Semaphore &operator=(const Semaphore &semaphore) = delete;

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
		 Constructs a condition variable from the given condition variable.

		 @param[in]		condition_variable
						A reference to a condition variable.
		 */
		ConditionVariable(const ConditionVariable &condition_variable) = delete;

		/**
		 Copies the given condition variable to this condition variable.

		 @param[in]		condition_variable
						A reference to a condition variable.
		 @return		A reference to the copy of the given condition variable
						(i.e. this condition variable)
		 */
		ConditionVariable &operator=(const ConditionVariable &condition_variable) = delete;

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