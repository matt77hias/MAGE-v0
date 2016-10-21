//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "engine.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	//-----------------------------------------------------------------------------
	// ReadWriteMutex
	//-----------------------------------------------------------------------------
	ReadWriteMutex::ReadWriteMutex() : m_nb_writers_waiting(0), m_nb_readers_waiting(0),
		m_active_writer_readers(0) {

		InitializeCriticalSection(&m_critical_section);

		m_ready_to_read_handle = CreateEvent(NULL, TRUE, FALSE, NULL);
		if (m_ready_to_read_handle == NULL) {
			Severe("Error creating event for ReadWriteMutex: %d", GetLastError());
		}

		m_ready_to_write_handle = CreateSemaphore(NULL, 0, 1, NULL);
		if (m_ready_to_write_handle == NULL) {
			DWORD lastError = GetLastError();
			CloseHandle(m_ready_to_read_handle);
			Severe("Error creating semaphore for ReadWriteMutex: %d", lastError);
		}
	}

	ReadWriteMutex::~ReadWriteMutex() {
		if (m_ready_to_read_handle) {
			CloseHandle(m_ready_to_read_handle);
		}
		if (m_ready_to_write_handle) {
			CloseHandle(m_ready_to_write_handle);
		}

		DeleteCriticalSection(&m_critical_section);
	}

	void ReadWriteMutex::AcquireRead() {
		bool notify_readers = false;

		EnterCriticalSection(&m_critical_section);

		if ((m_nb_writers_waiting > 0) || (HIWORD(m_active_writer_readers) > 0)) {
			++m_nb_readers_waiting;

			while (true) {
				ResetEvent(m_ready_to_read_handle);
				LeaveCriticalSection(&m_critical_section);
				WaitForSingleObject(m_ready_to_read_handle, INFINITE);
				EnterCriticalSection(&m_critical_section);

				// The reader is only allowed to read if there aren't
				// any writers waiting and if a writer doesn't own the
				// lock.
				if ((m_nb_writers_waiting == 0) && (HIWORD(m_active_writer_readers) == 0)) {
					break;
				}
			}

			// Reader is done waiting.
			--m_nb_readers_waiting;

			// Reader can read.
			++m_active_writer_readers;
		}
		else {
			// Reader can read.
			if ((++m_active_writer_readers == 1) && (m_nb_readers_waiting != 0)) {
				// Set flag to notify other waiting readers
				// outside of the critical section
				// so that they don't when the threads
				// are dispatched by the scheduler they
				// don't immediately block on the critical
				// section that this thread is holding.
				notify_readers = true;
			}
		}

		Assert(HIWORD(m_active_writer_readers) == 0);
		LeaveCriticalSection(&m_critical_section);

		if (notify_readers) {
			SetEvent(m_ready_to_read_handle);
		}
	}

	void ReadWriteMutex::AcquireWrite() {
		EnterCriticalSection(&m_critical_section);

		// Are there active readers?
		if (m_active_writer_readers != 0) {
			++m_nb_writers_waiting;

			LeaveCriticalSection(&m_critical_section);
			WaitForSingleObject(m_ready_to_write_handle, INFINITE);

			// Upon wakeup theirs no need for the writer
			// to acquire the critical section.  It
			// already has been transfered ownership of the
			// lock by the signaler.
		}
		else {
			Assert(m_active_writer_readers == 0);

			// Set that the writer owns the lock.
			m_active_writer_readers = MAKELONG(0, 1);

			LeaveCriticalSection(&m_critical_section);
		}
	}

	void ReadWriteMutex::ReleaseRead() {
		EnterCriticalSection(&m_critical_section);

		// Assert that the lock isn't held by a writer.
		Assert(HIWORD(m_active_writer_readers) == 0);

		// Assert that the lock is held by readers.
		Assert(LOWORD(m_active_writer_readers > 0));

		// Decrement the number of active readers.
		if (--m_active_writer_readers == 0) {
			ResetEvent(m_ready_to_read_handle);
		}

		// if writers are waiting and this is the last reader
		// hand owneership over to a writer.
		if ((m_nb_writers_waiting != 0) && (m_active_writer_readers == 0)) {
			// Decrement the number of waiting writers
			--m_nb_writers_waiting;

			// Pass ownership to a writer thread.
			m_active_writer_readers = MAKELONG(0, 1);
			ReleaseSemaphore(m_ready_to_write_handle, 1, NULL);
		}

		LeaveCriticalSection(&m_critical_section);
	}

	void ReadWriteMutex::ReleaseWrite() {
		bool notify_writer = false;
		bool notify_readers = false;

		EnterCriticalSection(&m_critical_section);

		// Assert that the lock is owned by a writer.
		Assert(HIWORD(m_active_writer_readers) == 1);

		// Assert that the lock isn't owned by one or more readers
		Assert(LOWORD(m_active_writer_readers) == 0);

		if (m_nb_writers_waiting != 0) {
			// Writers waiting, decrement the number of
			// waiting writers and release the semaphore
			// which means ownership is passed to the thread
			// that has been released.
			--m_nb_writers_waiting;
			notify_writer = true;
		}
		else {
			// There aren't any writers waiting
			// Release the exclusive hold on the lock.
			m_active_writer_readers = 0;

			// if readers are waiting set the flag
			// that will cause the readers to be notified
			// once the critical section is released.  This
			// is done so that an awakened reader won't immediately
			// block on the critical section which is still being
			// held by this thread.
			if (m_nb_readers_waiting != 0) {
				notify_readers = true;
			}
		}

		LeaveCriticalSection(&m_critical_section);

		if (notify_writer) {
			ReleaseSemaphore(m_ready_to_write_handle, 1, NULL);
		}
		else if (notify_readers) {
			SetEvent(m_ready_to_read_handle);
		}
	}

	//-----------------------------------------------------------------------------
	// ReadWriteMutexLock
	//-----------------------------------------------------------------------------
	ReadWriteMutexLock::ReadWriteMutexLock(ReadWriteMutex &mutex, ReadWriteMutexLockType mutex_type)
		: m_type(mutex_type), m_mutex(mutex) {
		if (m_type == READ) {
			m_mutex.AcquireRead();
		}
		else {
			m_mutex.AcquireWrite();
		}
	}

	ReadWriteMutexLock::~ReadWriteMutexLock() {
		if (m_type == READ) {
			m_mutex.ReleaseRead();
		}
		else {
			m_mutex.ReleaseWrite();
		}
	}

	void ReadWriteMutexLock::UpgradeToWrite() {
		Assert(m_type == READ);
		m_mutex.ReleaseRead();
		m_mutex.AcquireWrite();
		m_type = WRITE;
	}

	void ReadWriteMutexLock::DowngradeToRead() {
		Assert(m_type == WRITE);
		m_mutex.ReleaseWrite();
		m_mutex.AcquireRead();
		m_type = READ;
	}

	//-----------------------------------------------------------------------------
	// Semaphore
	//-----------------------------------------------------------------------------
	Semaphore::Semaphore() {
		m_handle = CreateSemaphore(NULL, 0, LONG_MAX, NULL);
		if (!m_handle) {
			Severe("Error from CreateSemaphore: %d", GetLastError());
		}
	}

	Semaphore::~Semaphore() {
		CloseHandle(m_handle);
	}

	void Semaphore::Post(uint32_t count) {
		if (!ReleaseSemaphore(m_handle, count, NULL)) {
			Severe("Error from ReleaseSemaphore: %d", GetLastError());
		}
	}

	void Semaphore::Wait() {
		if (WaitForSingleObject(m_handle, INFINITE) == WAIT_FAILED) {
			Severe("Error from WaitForSingleObject: %d", GetLastError());
		}
	}

	bool Semaphore::TryWait() {
		return (WaitForSingleObject(m_handle, 0L) == WAIT_OBJECT_0);
	}

	//-----------------------------------------------------------------------------
	// ConditionVariable
	//-----------------------------------------------------------------------------
	ConditionVariable::ConditionVariable() : m_nb_waiters(0) {
		InitializeCriticalSection(&m_nb_waiters_mutex);
		InitializeCriticalSection(&m_condition_mutex);

		m_events[SIGNAL] = CreateEvent(NULL,  // no security
			FALSE, // auto-reset event
			FALSE, // non-signaled initially
			NULL); // unnamed
		m_events[BROADCAST] = CreateEvent(NULL,  // no security
			TRUE,  // manual-reset
			FALSE, // non-signaled initially
			NULL); // unnamed
	}

	ConditionVariable::~ConditionVariable() {
		CloseHandle(m_events[SIGNAL]);
		CloseHandle(m_events[BROADCAST]);
	}

	void ConditionVariable::Lock() {
		EnterCriticalSection(&m_condition_mutex);
	}

	void ConditionVariable::Unlock() {
		LeaveCriticalSection(&m_condition_mutex);
	}

	void ConditionVariable::Wait() {
		// Avoid race conditions.
		EnterCriticalSection(&m_nb_waiters_mutex);
		++m_nb_waiters;
		LeaveCriticalSection(&m_nb_waiters_mutex);

		// It's ok to release the <external_mutex> here since Win32
		// manual-reset events maintain state when used with
		// <SetEvent>.  This avoids the "lost wakeup" bug...
		LeaveCriticalSection(&m_condition_mutex);

		// Wait for either event to become signaled due to <pthread_cond_signal>
		// being called or <pthread_cond_broadcast> being called.
		const int result = WaitForMultipleObjects(2, m_events, FALSE, INFINITE);

		EnterCriticalSection(&m_nb_waiters_mutex);
		--m_nb_waiters;
		const int last_waiter = (result == WAIT_OBJECT_0 + BROADCAST) && (m_nb_waiters == 0);
		LeaveCriticalSection(&m_nb_waiters_mutex);

		if (last_waiter)
			// We're the last waiter to be notified or to stop waiting, so
			// reset the manual event.
			ResetEvent(m_events[BROADCAST]);

		EnterCriticalSection(&m_condition_mutex);
	}

	void ConditionVariable::Signal() {
		EnterCriticalSection(&m_nb_waiters_mutex);
		const int has_waiters = (m_nb_waiters > 0);
		LeaveCriticalSection(&m_nb_waiters_mutex);

		if (has_waiters) {
			SetEvent(m_events[SIGNAL]);
		}
	}

}