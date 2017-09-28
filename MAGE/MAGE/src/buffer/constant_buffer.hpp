#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "rendering\pipeline.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	/**
	 A class of constant buffers (for binding buffers to the rendering 
	 pipeline).

	 @tparam		DataT
					The data type.
	 */
	template< typename DataT >
	struct ConstantBuffer final {

	public:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		/**
		 Constructs a constant buffer.

		 @pre			The device associated with the current engine must be 
						loaded.
		 @throws		FormattedException
						Failed to setup this constant buffer.
		 */
		ConstantBuffer();

		/**
		 Constructs a constant buffer.

		 @pre			@a device is not equal to @c nullptr.
		 @param[in]		device
						A pointer to the device.
		 @throws		FormattedException
						Failed to setup this constant buffer.
		 */
		explicit ConstantBuffer(ID3D11Device2 *device);
		
		/**
		 Constructs a constant buffer from the given constant buffer.

		 @param[in]		buffer
						A reference to the constant buffer to copy.
		 */
		ConstantBuffer(const ConstantBuffer &buffer) = delete;

		/**
		 Constructs a constant buffer by moving the given constant buffer.

		 @param[in]		buffer
						A reference to the constant buffer to move.
		 */
		ConstantBuffer(ConstantBuffer &&buffer) = default;
		
		/**
		 Destructs this constant buffer.
		 */
		~ConstantBuffer() = default;

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------	

		/**
		 Copies the given constant buffer to this constant buffer.

		 @param[in]		buffer
						A reference to the constant buffer to copy.
		 @return		A reference to the copy of the given constant buffer
						(i.e. this constant buffer).
		 */
		ConstantBuffer &operator=(const ConstantBuffer &buffer) = delete;

		/**
		 Moves the given constant buffer to this constant buffer.

		 @param[in]		buffer
						A reference to the constant buffer to move.
		 @return		A reference to the moved constant buffer (i.e. this 
						constant buffer).
		 */
		ConstantBuffer &operator=(ConstantBuffer &&buffer) = delete;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Updates the data of this constant buffer with the given data.

		 @pre			@a device_context is not equal to @c nullptr.
		 @param[in]		device_context
						A pointer to the device context.
		 @param[in]		data
						A reference to the data.
		 @throws		FormattedException
						Failed to update the data.
		 */
		void UpdateData(ID3D11DeviceContext2 *device_context, 
			const DataT &data);
		
		/**
		 Returns the buffer resource of this constant buffer.

		 @return		A pointer to the buffer resource 
						of this constant buffer.
		 */
		ID3D11Buffer *Get() const noexcept {
			return m_buffer.Get();
		}
		
		/**
		 Binds this constant buffer.

		 @pre			@a device_context is not equal to @c nullptr.
		 @pre			@a slot < 
						@c D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT.
		 @tparam		PipelineStageT
						The pipeline stage type.
		 @param[in]		device_context
						A pointer to the device context.
		 @param[in]		slot
						The index into the device's zero-based array to set the 
						constant buffer to (ranges from 0 to 
						@c D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT 
						- 1).
		 */
		template< typename PipelineStageT >
		void Bind(ID3D11DeviceContext2 *device_context, 
			U32 slot) const noexcept;

	private:

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------
		
		/**
		 Sets up the resource buffer of this constant buffer.

		 @pre			@a device is not equal to @c nullptr.
		 @param[in]		device
						A pointer to the device.
		 @throws		FormattedException
						Failed to setup this constant buffer.
		 */
		void SetupConstantBuffer(ID3D11Device2 *device);

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		/**
		 A pointer to the buffer resource of this constant buffer.
		 */
		ComPtr< ID3D11Buffer > m_buffer;
	};
}

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "buffer\constant_buffer.tpp"

#pragma endregion