#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "memory\memory.hpp"
#include "rendering\rendering.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	/**
	 A class of constant buffers (for binding buffers to the rendering pipeline).

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

		 @pre			@a device is not equal to @c nullptr.
		 @pre			@a device_context is not equal to @c nullptr.
		 @param[in]		device
						A pointer to the device.
		 @param[in]		device_context
						A pointer to the device context.
		 */
		explicit ConstantBuffer(ID3D11Device2 *device, ID3D11DeviceContext2 *device_context);
		
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
		 @return		A reference to the copy of the given constant buffer
						(i.e. this constant buffer).
		 */
		ConstantBuffer &operator=(ConstantBuffer &&buffer) = delete;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Updates the data of constant buffer with the given data.

		 @param[in]		data
						A reference to the data.
		 */
		void UpdateData(const DataT &data) const;
		
		/**
		 Returns the buffer resource of this constant buffer.

		 @return		A pointer to the buffer resource 
						of this constant buffer.
		 */
		ID3D11Buffer *Get() const {
			return m_buffer.Get();
		}
		
		/**
		 Returns the address of the buffer resource of this constant buffer.

		 @return		A pointer to a pointer to the buffer resource 
						of this constant buffer.
		 */
		ID3D11Buffer * const *GetAddressOf() const {
			return m_buffer.GetAddressOf();
		}
		
		/**
		 Returns the address of the buffer resource of this constant buffer.

		 @return		A pointer to a pointer to the buffer resource 
						of this constant buffer.
		 */
		ID3D11Buffer **GetAddressOf() {
			return m_buffer.GetAddressOf();
		}

	private:

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------
		
		/**
		 Sets up the resource buffer of this constant buffer.

		 @throws		FormattedException
						Failed to setup this constant buffer.
		 */
		void SetupConstantBuffer();

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		/**
		 A pointer to the device of this constant buffer.
		 */
		ID3D11Device2 * const m_device;

		/**
		 A pointer to the device context of this constant buffer.
		 */
		ID3D11DeviceContext2 * const m_device_context;

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

#include "rendering\constant_buffer.tpp"

#pragma endregion