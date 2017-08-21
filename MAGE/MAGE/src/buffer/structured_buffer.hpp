#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "memory\memory.hpp"
#include "rendering\pipeline.hpp"
#include "collection\collection.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	/**
	 A class of structured buffers (for binding arrays of buffers to the rendering pipeline).

	 @tparam		DataT
					The data type.
	 */
	template< typename DataT >
	struct StructuredBuffer final {

	public:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		/**
		 Constructs a structured buffer.

		 @pre			The renderer associated with the current engine 
						must be loaded.
		 @param[in]		nb_initial_data_elements
						The initial number of slots for storing data elements to provide.
		 */
		explicit StructuredBuffer(size_t nb_initial_data_elements);

		/**
		 Constructs a structured buffer.

		 @pre			@a device is not equal to @c nullptr.
		 @pre			@a device_context is not equal to @c nullptr.
		 @pre			The renderer associated with the current engine
						must be loaded.
		 @param[in]		device
						A pointer to the device.
		 @param[in]		device_context
						A pointer to the device context.
		 @param[in]		nb_initial_data_elements
						The initial number of slots for storing data elements to provide.
		 */
		explicit StructuredBuffer(ID3D11Device2 *device, ID3D11DeviceContext2 *device_context, 
			size_t nb_initial_data_elements);
		
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
		StructuredBuffer(StructuredBuffer &&buffer) = default;

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
		 @return		A reference to the copy of the given structured buffer
						(i.e. this structured buffer).
		 */
		StructuredBuffer &operator=(StructuredBuffer &&buffer) = delete;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Updates the data of structured buffer with the given data.

		 @param[in]		data
						A reference to a vector with the data elements.
		 */
		void UpdateData(const vector< DataT > &data) const;

		/**
		 Returns the shader resource view of this structured buffer.

		 @return		A pointer to the shader resource view
						of this structured buffer.
		 */
		ID3D11ShaderResourceView *Get() const noexcept {
			return m_buffer_srv.Get();
		}

	private:

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------
		
		/**
		 Sets up the resource buffer and shader resource view of this structured buffer.

		 @param[in]		nb_data_elements
						The number of slots for storing data elements to provide.
		 @throws		FormattedException
						Failed to setup this structured buffer.
		 */
		void SetupStructuredBuffer(size_t nb_data_elements) const;

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		/**
		 A pointer to the device of this structured buffer.
		 */
		ID3D11Device2 * const m_device;

		/**
		 A pointer to the device context of this structured buffer.
		 */
		ID3D11DeviceContext2 * const m_device_context;

		/**
		 A pointer to the buffer resource of this structured buffer.
		 */
		mutable ComPtr< ID3D11Buffer > m_buffer;

		/**
		 The number of slots available for storing data elements
		 in the current buffer resource of this structured buffer.
		 */
		mutable size_t m_nb_data_elements;

		/**
		 A pointer to the shader resource view of this structured buffer.
		 */
		mutable ComPtr< ID3D11ShaderResourceView > m_buffer_srv;
	};
}

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "buffer\structured_buffer.tpp"

#pragma endregion