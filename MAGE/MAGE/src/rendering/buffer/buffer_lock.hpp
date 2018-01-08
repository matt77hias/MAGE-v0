#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "rendering\pipeline.hpp"
#include "logging\error.hpp"
#include "exception\exception.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	/**
	 A class of buffer locks.
	 */
	class BufferLock final {

	public:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		/**
		 Constructs a buffer lock.

		 @pre			The device associated with the current engine
						must be loaded.
		 @pre			@a device_context is not equal to @c nullptr.
		 @pre			@a buffer is not equal to @c nullptr.
		 @pre			@a mapped_buffer is not equal to @c nullptr.
		 @param[in]		buffer
						A pointer to the buffer.
		 @param[in]		map_type
						The map type specifying the CPU's read and write 
						permissions for the buffer of this buffer lock.
		 @param[out]	mapped_buffer
						A pointer to map the buffer of this buffer lock to.
		 @throws		Exception
						Failed to map the buffer.
		 */
		explicit BufferLock(ID3D11Buffer *buffer,
			                D3D11_MAP map_type,
			                D3D11_MAPPED_SUBRESOURCE *mapped_buffer)
			: BufferLock(Pipeline::GetImmediateDeviceContext(),
				         buffer, map_type, mapped_buffer) {}

		/**
		 Constructs a buffer lock.

		 @pre			@a device_context is not equal to @c nullptr.
		 @pre			@a buffer is not equal to @c nullptr.
		 @pre			@a mapped_buffer is not equal to @c nullptr.
		 @param[in]		device_context
						A pointer to the device context.
		 @param[in]		buffer
						A pointer to the buffer.
		 @param[in]		map_type
						The map type specifying the CPU's read and write 
						permissions for the buffer of this buffer lock.
		 @param[out]	mapped_buffer
						A pointer to map the buffer of this buffer lock to.
		 @throws		Exception
						Failed to map the buffer.
		 */
		explicit BufferLock(ID3D11DeviceContext4 *device_context,
			                ID3D11Buffer *buffer,
			                D3D11_MAP map_type,
			                D3D11_MAPPED_SUBRESOURCE *mapped_buffer)
			: m_device_context(device_context),
			m_buffer(buffer) {

			Assert(device_context);
			Assert(buffer);
			Assert(mapped_buffer);

			MapBuffer(map_type, mapped_buffer);
		}

		/**
		 Constructs a buffer lock from the given buffer lock.

		 @param[in]		buffer_lock
						A reference to the buffer lock to copy.
		 */
		BufferLock(const BufferLock &buffer_lock) = delete;

		/**
		 Constructs a buffer lock by moving the given buffer lock.

		 @param[in]		buffer_lock
						A reference to the buffer lock to move.
		 */
		BufferLock(BufferLock &&buffer_lock) noexcept = default;

		/**
		 Destructs this buffer lock.
		 */
		~BufferLock() {
			UnmapBuffer();
		}

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------

		/**
		 Copies the given buffer lock to this buffer lock.

		 @param[in]		buffer_lock
						A reference to the buffer lock to copy.
		 @return		A reference to the copy of the given buffer lock (i.e. 
						this buffer lock)
		 */
		BufferLock &operator=(const BufferLock &buffer_lock) = delete;

		/**
		 Moves the given buffer lock to this buffer lock.

		 @param[in]		buffer_lock
						A reference to the buffer lock to move.
		 @return		A reference to the moved buffer lock (i.e. this buffer 
						lock)
		 */
		BufferLock &operator=(BufferLock &&buffer_lock) noexcept = default;

	private:

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Maps the buffer of this buffer lock.

		 @pre			@a mapped_buffer is not equal to @c nullptr.
		 @param[in]		map_type
						The map type specifying the CPU's read and write 
						permissions for the buffer of this buffer lock.
		 @param[out]	mapped_buffer
						A pointer to map the buffer of this buffer lock to.
		 @throws		Exception
						Failed to map the buffer.
		 */
		void MapBuffer(D3D11_MAP map_type, 
			           D3D11_MAPPED_SUBRESOURCE *mapped_buffer) {

			Assert(mapped_buffer);

			const HRESULT result = Pipeline::Map(m_device_context, m_buffer,
				                                 0u, map_type, 0u, mapped_buffer);
			ThrowIfFailed(result, "Buffer mapping failed: %08X.", result);
		}

		/**
		 Unmaps the buffer of this buffer lock.

		 @pre			The buffer of this buffer lock must be mapped with
						{@link mage::BufferLock::MapBuffer(D3D11_MAP, D3D11_MAPPED_SUBRESOURCE*)} 
						before it can be unmapped.
		 */
		void UnmapBuffer() const noexcept {
			Pipeline::Unmap(m_device_context, m_buffer, 0u);
		}

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		/**
		 A pointer to the device context of this buffer lock.
		 */
		ID3D11DeviceContext4 *m_device_context;

		/**
		 A pointer to the buffer of this lock.
		 */
		ID3D11Buffer *m_buffer;
	};
}