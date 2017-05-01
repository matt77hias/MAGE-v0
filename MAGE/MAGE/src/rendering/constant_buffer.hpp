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

	template< typename DataT >
	struct ConstantBuffer final {

	public:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		explicit ConstantBuffer(ID3D11Device2 *device, ID3D11DeviceContext2 *device_context);
		ConstantBuffer(const ConstantBuffer &buffer) = delete;
		ConstantBuffer(ConstantBuffer &&buffer) = default;
		~ConstantBuffer() = default;

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------	

		ConstantBuffer &operator=(const ConstantBuffer &buffer) = delete;
		ConstantBuffer &operator=(ConstantBuffer &&buffer) = delete;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		void UpdateData(const DataT &data) const;
		ID3D11Buffer *Get() const {
			return m_buffer.Get();
		}
		ID3D11Buffer * const *GetAddressOf() const {
			return m_buffer.GetAddressOf();
		}
		ID3D11Buffer **GetAddressOf() {
			return m_buffer.GetAddressOf();
		}

	private:

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------
		void SetupConstantBuffer();

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		ID3D11Device2 * const m_device;
		ID3D11DeviceContext2 * const m_device_context;
		ComPtr< ID3D11Buffer > m_buffer;
	};

}

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "rendering\constant_buffer.tpp"

#pragma endregion