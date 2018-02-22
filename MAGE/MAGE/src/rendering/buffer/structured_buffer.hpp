#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "rendering\buffer\buffer_lock.hpp"
#include "collection\vector.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	/**
	 A class of structured buffers.

	 @tparam		DataT
					The data type.
	 */
	template< typename DataT >
	class StructuredBuffer final {

	public:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		/**
		 Constructs a structured buffer.

		 @pre			The device associated of the rendering manager 
						associated with the current engine must be loaded.
		 @param[in]		capacity
						The initial capacity.
		 @throws		Exception
						Failed to setup this structured buffer.
		 */
		explicit StructuredBuffer(size_t capacity);
		
		/**
		 Constructs a structured buffer.

		 @pre			@a device is not equal to @c nullptr.
		 @param[in]		device
						A pointer to the device.
		 @param[in]		capacity
						The initial capacity.
		 @throws		Exception
						Failed to setup this structured buffer.
		 */
		explicit StructuredBuffer(ID3D11Device *device, size_t capacity);
		
		/**
		 Constructs a structured buffer from the given structured buffer.

		 @param[in]		buffer
						A reference to the structured buffer to copy.
		 */
		StructuredBuffer(const StructuredBuffer &buffer) = delete;

		/**
		 Constructs a structured buffer by moving the given structured buffer.

		 @param[in]		buffer
						A reference to the structured buffer to move.
		 */
		StructuredBuffer(StructuredBuffer &&buffer) noexcept = default;

		/**
		 Destructs this structured buffer.
		 */
		~StructuredBuffer() = default;

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------	

		/**
		 Copies the given structured buffer to this structured buffer.

		 @param[in]		buffer
						A reference to the structured buffer to copy.
		 @return		A reference to the copy of the given structured buffer
						(i.e. this structured buffer).
		 */
		StructuredBuffer &operator=(const StructuredBuffer &buffer) = delete;

		/**
		 Moves the given structured buffer to this structured buffer.

		 @param[in]		buffer
						A reference to the structured buffer to move.
		 @return		A reference to the moved structured buffer (i.e. this 
						structured buffer).
		 */
		StructuredBuffer &operator=(StructuredBuffer &&buffer) noexcept = default;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Returns the size of this structured buffer.

		 @return		The size of this structured buffer.
		 */
		[[nodiscard]] size_t size() const noexcept {
			return m_size;
		}

		/**
		 Returns the capacity of this structured buffer.

		 @return		The capacity of this structured buffer.
		 */
		[[nodiscard]] size_t capacity() const noexcept {
			return m_capacity;
		}

		/**
		 Updates the data of this structured buffer with the given data.

		 @pre			The device associated of the rendering manager 
						associated with the current engine must be loaded.
		 @pre			@a device_context is not equal to @c nullptr.
		 @param[in]		device_context
						A pointer to the device context.
		 @param[in]		data
						A reference to a vector containing the data elements.
		  @throws		Exception
						Failed to update the data.
		 */
		void UpdateData(ID3D11DeviceContext *device_context, 
			            const AlignedVector< DataT > &data);

		/**
		 Updates the data of this structured buffer with the given data.

		 @pre			@a device is not equal to @c nullptr.
		 @pre			@a device_context is not equal to @c nullptr.
		 @param[in]		device
						A pointer to the device.
		 @param[in]		device_context
						A pointer to the device context.
		 @param[in]		data
						A reference to a vector containing the data elements.
	     @throws		Exception
						Failed to update the data.
		 */
		void UpdateData(ID3D11Device *device, 
			            ID3D11DeviceContext *device_context,
			            const AlignedVector< DataT > &data);

		/**
		 Returns the shader resource view of this structured buffer.

		 @return		A pointer to the shader resource view
						of this structured buffer.
		 */
		[[nodiscard]] ID3D11ShaderResourceView *Get() const noexcept {
			return m_buffer_srv.Get();
		}

		/**
		 Binds this structured buffer.

		 @pre			@a device_context is not equal to @c nullptr.
		 @pre			@a slot < 
						@c D3D11_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT.
		 @tparam		PipelineStageT
						The pipeline stage type.
		 @param[in]		device_context
						A pointer to the device context.
		 @param[in]		slot
						The index into the device's zero-based array to set 
						the shader resource view to (ranges from 0 to 
						@c D3D11_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT - 1).
		 */
		template< typename PipelineStageT >
		void Bind(ID3D11DeviceContext *device_context, U32 slot) const noexcept;

	private:

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------
		
		/**
		 Sets up the resource buffer and shader resource view of this 
		 structured buffer.

		 @pre			@a device is not equal to @c nullptr.
		 @param[in]		device
						A pointer to the device.
		 @param[in]		capacity
						The capacity.
		 @throws		Exception
						Failed to setup this structured buffer.
		 */
		void SetupStructuredBuffer(ID3D11Device *device, size_t capacity);

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		/**
		 A pointer to the buffer resource of this structured buffer.
		 */
		ComPtr< ID3D11Buffer > m_buffer;

		/**
		 A pointer to the shader resource view of this structured buffer.
		 */
		ComPtr< ID3D11ShaderResourceView > m_buffer_srv;

		/**
		 The number of available slots for storing data elements in the current 
		 buffer resource of this structured buffer (i.e. the capacity).
		 */
		size_t m_capacity;

		/**
		 The number of used slots for storing data elements in the current buffer 
		 resource of this structured buffer (i.e. the size).
		 */
		size_t m_size;
	};
}

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "rendering\buffer\structured_buffer.tpp"

#pragma endregion