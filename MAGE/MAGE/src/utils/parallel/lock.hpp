#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "utils\type\types.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	//-------------------------------------------------------------------------
	// Mutex
	//-------------------------------------------------------------------------
	#pragma region

	/**
	 A class of mutexes.
	 */
	class Mutex final {

	public:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		/**
		 Constructs a mutex.
		 */
		Mutex() noexcept;

		/**
		 Constructs a mutex from the given mutex.

		 @param[in]		mutex
						A reference to the mutex to copy.
		 */
		Mutex(const Mutex &mutex) = delete;

		/**
		 Constructs a mutex by moving the given mutex.

		 @param[in]		mutex
						A reference to the mutex to move.
		 */
		Mutex(Mutex &&mutex) noexcept = default;

		/**
		 Destructs this mutex.
		 */
		~Mutex();

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------	

		/**
		 Copies the given mutex to this mutex.

		 @param[in]		mutex
						A reference to the mutex to copy.
		 @return		A reference to the copy of the given mutex (i.e. this 
						mutex).
		 */
		Mutex &operator=(const Mutex &mutex) = delete;

		/**
		 Moves the given mutex to this mutex.

		 @param[in]		mutex
						A reference to the mutex to move.
		 @return		A reference to the moved mutex (i.e. this mutex).
		 */
		Mutex &operator=(Mutex &&mutex) noexcept = default;

	private:

		//---------------------------------------------------------------------
		// Friends
		//---------------------------------------------------------------------

		friend class MutexLock;

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		/**
		 The critical section object of this mutex.
		 */
		CRITICAL_SECTION m_critical_section;
	};

	#pragma endregion

	//-------------------------------------------------------------------------
	// MutexLock
	//-------------------------------------------------------------------------
	#pragma region

	/**
	 A class of mutex locks.
	 */
	class MutexLock final {

	public:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		/**
		 Constructs a mutex lock for the given mutex.

		 @param[in]		mutex
						A reference to the mutex.
		 */
		explicit MutexLock(Mutex &mutex) noexcept;

		/**
		 Constructs a mutex lock from the given mutex lock.

		 @param[in]		mutex_lock
						A reference to the mutex lock to copy.
		 */
		MutexLock(const MutexLock &mutex_lock) = delete;

		/**
		 Constructs a mutex lock by moving the given mutex lock.

		 @param[in]		mutex_lock
						A reference to the mutex lock to move.
		 */
		MutexLock(MutexLock &&mutex_lock) noexcept = default;

		/**
		 Destructs this mutex lock.
		 */
		~MutexLock();

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------	

		/**
		 Copies the given mutex lock to this mutex lock.

		 @param[in]		mutex_lock
						A reference to the mutex lock to copy.
		 @return		A reference to the copy of the given mutex lock (i.e. 
						this mutex lock)
		 */
		MutexLock &operator=(const MutexLock &mutex_lock) = delete;

		/**
		 Moves the given mutex lock to this mutex lock.

		 @param[in]		mutex_lock
						A reference to the mutex lock to move.
		 @return		A reference to the moved mutex lock (i.e. this mutex 
						lock)
		 */
		MutexLock &operator=(MutexLock &&mutex_lock) noexcept = default;

	private:

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 A reference to the mutex of this mutex lock.
		 */
		Mutex &m_mutex;
	};

	#pragma endregion

	//-------------------------------------------------------------------------
	// ReadWriteMutex
	//-------------------------------------------------------------------------
	#pragma region

	/**
	 A class of read write mutexes.
	 */
	class ReadWriteMutex final {

	public:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		/**
		 Constructs a read write mutex.
		 */
		ReadWriteMutex() noexcept;

		/**
		 Constructs a read write mutex from the given read write mutex.

		 @param[in]		mutex
						A reference to the read write mutex to copy.
		 */
		ReadWriteMutex(const ReadWriteMutex &mutex) = delete;

		/**
		 Constructs a read write mutex by moving the given read write mutex.

		 @param[in]		mutex
						A reference to the read write mutex to move.
		 */
		ReadWriteMutex(ReadWriteMutex &&mutex) noexcept = default;

		/**
		 Destructs this read write mutex.
		 */
		~ReadWriteMutex();

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------	

		/**
		 Copies the given read write mutex to this read write mutex.

		 @param[in]		mutex
						A reference to a read write mutex to copy.
		 @return		A reference to the copy of the given read write mutex
						(i.e. this read write mutex).
		 */
		ReadWriteMutex &operator=(const ReadWriteMutex &mutex) = delete;

		/**
		 Moves the given read write mutex to this read write mutex.

		 @param[in]		mutex
						A reference to a read write mutex to move.
		 @return		A reference to the moved read write mutex (i.e. this 
						read write mutex).
		 */
		ReadWriteMutex &operator=(ReadWriteMutex &&mutex) noexcept = default;

	private:

		//---------------------------------------------------------------------
		// Friends
		//---------------------------------------------------------------------

		friend class ReadWriteMutexLock;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Acquires a read.
		 */
		void AcquireRead() noexcept;

		/**
		 Releases a read.
		 */
		void ReleaseRead() noexcept;

		/**
		 Acquires a write.
		 */
		void AcquireWrite() noexcept;

		/**
		 Releases a write.
		 */
		void ReleaseWrite() noexcept;

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		/**
		 The number of writers waiting for this read write mutex.
		 */
		LONG m_nb_writers_waiting;

		/**
		 The number of readers waiting for this read write mutex.
		 */
		LONG m_nb_readers_waiting;

		/**
		 The active group of this read write mutex.

		 @c HIWORD is the flag indicating a writer is active.
		 @c LOWORD is the number of active readers.
		 */
		DWORD m_active_writer_readers;

		/**
		 The handle of this read write mutex if ready for reading.
		 */
		HANDLE m_ready_to_read_handle;

		/**
		 The handle of this read write mutex if ready for writing.
		 */
		HANDLE m_ready_to_write_handle;

		/**
		 The critical section object of this read write mutex.
		 */
		CRITICAL_SECTION m_critical_section;
	};

	#pragma endregion

	//-------------------------------------------------------------------------
	// ReadWriteMutexLock
	//-------------------------------------------------------------------------
	#pragma region

	/**
	 A class of read write mutex locks.
	 */
	class ReadWriteMutexLock final {

	public:

		/**
		 An enumeration of the different read write mutex lock types.

		 This contains:
		 @c Read and @c Write.
		 */
		enum class LockType {
			Read,
			Write
		};

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		/**
		 Constructs a read write mutex lock for the given read write mutex and 
		 lock type.

		 @param[in]		mutex
						A reference to a read write mutex.
		 @param[in]		lock_type
						The lock type.
		 */
		explicit ReadWriteMutexLock(
			ReadWriteMutex &mutex, LockType lock_type) noexcept;

		/**
		 Constructs a read write mutex lock from the given read write mutex 
		 lock.

		 @param[in]		mutex_lock
						A reference to the read write mutex lock to copy.
		 */
		ReadWriteMutexLock(const ReadWriteMutexLock &mutex_lock) = delete;

		/**
		 Constructs a read write mutex lock by moving the given read write 
		 mutex lock.

		 @param[in]		mutex_lock
						A reference to the read write mutex lock to move.
		 */
		ReadWriteMutexLock(ReadWriteMutexLock &&mutex_lock) noexcept = default;

		/**
		 Destructs this read write mutex lock.
		 */
		~ReadWriteMutexLock();

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------	

		/**
		 Copies the given read write mutex lock to this read write mutex lock.

		 @param[in]		mutex_lock
						A reference to the read write mutex lock to copy.
		 @return		A reference to the copy of the given read write mutex 
						lock (i.e. this read write mutex lock).
		 */
		ReadWriteMutexLock &operator=(
			const ReadWriteMutexLock &mutex_lock) = delete;

		/**
		 Moves the given read write mutex lock to this read write mutex lock.

		 @param[in]		mutex_lock
						A reference to the read write mutex lock to move.
		 @return		A reference to the moved read write mutex lock (i.e. 
						this read write mutex lock).
		 */
		ReadWriteMutexLock &operator=(
			ReadWriteMutexLock &&mutex_lock) noexcept = default;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Upgrades this read write lock to write.
		 */
		void UpgradeToWrite() noexcept;

		/**
		 Downgrades this read write lock to read.
		 */
		void DowngradeToRead() noexcept;

	private:

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		/**
		 The lock type of this read write mutex lock. 
		 */
		LockType m_type;

		/**
		 A reference to the read write mutex of this read write mutex lock. 
		 */
		ReadWriteMutex &m_mutex;
	};

	#pragma endregion

	//-------------------------------------------------------------------------
	// Semaphore
	//-------------------------------------------------------------------------
	#pragma region

	/**
	 A class of semaphores.
	 */
	class Semaphore final {

	public:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		/**
		 Constructs a semaphore.
		 */
		Semaphore() noexcept;

		/**
		 Constructs a semaphore from the given semaphore.

		 @param[in]		semaphore
						A reference to the semaphore to copy.
		 */
		Semaphore(const Semaphore &semaphore) = delete;

		/**
		 Constructs a semaphore by moving the given semaphore.

		 @param[in]		semaphore
						A reference to the semaphore to move.
		 */
		Semaphore(Semaphore &&semaphore) noexcept = default;

		/**
		 Destructs this semaphore.
		 */
		~Semaphore();

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------	

		/**
		 Copies the given semaphore to this semaphore.

		 @param[in]		semaphore
						A reference to the semaphore to copy.
		 @return		A reference to the copy of the given semaphore (i.e. 
						this semaphore)
		 */
		Semaphore &operator=(const Semaphore &semaphore) = delete;

		/**
		 Copies the given semaphore to this semaphore.

		 @param[in]		semaphore
						A reference to the semaphore to move.
		 @return		A reference to the moved semaphore (i.e. this semaphore)
		 */
		Semaphore &operator=(Semaphore &&semaphore) noexcept = default;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Increments the value of this semaphore variable by the given value.
		 
		 If the initial value of the semaphore is negative, the waiting queue 
		 is not empty and thus one blocked process can be transferred to the 
		 ready queue.

		 @param[in]		count
						The increment value.
		 */
		void Signal(U32 count = 1) noexcept;
		
		/**
		 Decrements the value of this semaphore variable by one.

		 The process executing wait is blocked until the value of the semaphore
		 is greater or equal to 1.
		 */
		void Wait() noexcept;
		
		/**
		 Checks whether waiting for this semaphore would be necessary.

		 @return		@c true if waiting for this semaphore would be 
						necessary. @c false otherwise.
		 */
		bool TryWait() noexcept;

	private:

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		/**
		 The handle of this semaphore.
		 */
		HANDLE m_handle;
	};

	#pragma endregion

	//-------------------------------------------------------------------------
	// ConditionVariable
	//-------------------------------------------------------------------------
	#pragma region

	/**
	 A class of condition variables.
	 */
	class ConditionVariable final {

	public:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		/**
		 Constructs a condition variable.
		 */
		ConditionVariable() noexcept;

		/**
		 Constructs a condition variable from the given condition variable.

		 @param[in]		condition_variable
						A reference to the condition variable to copy.
		 */
		ConditionVariable(
			const ConditionVariable &condition_variable) = delete;

		/**
		 Constructs a condition variable by moving the given condition 
		 variable.

		 @param[in]		condition_variable
						A reference to the condition variable to move.
		 */
		ConditionVariable(
			ConditionVariable &&condition_variable) noexcept = default;

		/**
		 Destructs this condition variable.
		 */
		~ConditionVariable();

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------	

		/**
		 Copies the given condition variable to this condition variable.

		 @param[in]		condition_variable
						A reference to the condition variable to copy.
		 @return		A reference to the copy of the given condition 
						variable (i.e. this condition variable)
		 */
		ConditionVariable &operator=(
			const ConditionVariable &condition_variable) = delete;

		/**
		 Moves the given condition variable to this condition variable.

		 @param[in]		condition_variable
						A reference to the condition variable to move.
		 @return		A reference to the moved condition variable (i.e. this 
						condition variable)
		 */
		ConditionVariable &operator=(
			ConditionVariable &&condition_variable) noexcept = default;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Locks this condition variable.
		 */
		void Lock() noexcept;

		/**
		 Unlocks this condition variable.
		 */
		void Unlock() noexcept;

		/**
		 Signals a condition change.
		 */
		void Signal() noexcept;

		/**
		 Waits for a signal indicating a condition change.
		 */
		void Wait() noexcept;

	private:

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		/** 
		 The number of waiters of this condition variable.
		 */
		U32 m_nb_waiters;

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
		 An enumeration of the different types of events of this condition 
		 variable.
		 */
		enum Event { 
			SIGNAL    = 0, 
			BROADCAST = 1, 
			COUNT     = 2 
		};

		/**
		 The signal and broadcast event handles of this condition variable.
		 */
		HANDLE m_events[COUNT];
	};

	#pragma endregion
}