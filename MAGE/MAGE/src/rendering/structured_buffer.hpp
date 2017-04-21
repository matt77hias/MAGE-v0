#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "memory\memory.hpp"
#include "rendering\rendering.hpp"
#include "collection\collection.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	template< typename DataT >
	struct StructuredBuffer final {

	public:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		explicit StructuredBuffer(ID3D11Device2 *device, ID3D11DeviceContext2 *device_context, 
			size_t nb_initial_data_elements);
		StructuredBuffer(const StructuredBuffer &buffer) = delete;
		StructuredBuffer(StructuredBuffer &&buffer) = default;
		~StructuredBuffer() = default;

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------	

		StructuredBuffer &operator=(const StructuredBuffer &buffer) = delete;
		StructuredBuffer &operator=(StructuredBuffer &&buffer) = delete;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		size_t GetNumberOfDataElements() const {
			return m_nb_data_elements;
		}
		void UpdateData(const vector< DataT > &data) const;
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
		HRESULT SetupStructuredBuffer(size_t nb_data_elements) const;

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		ID3D11Device2 * const m_device;
		ID3D11DeviceContext2 * const m_device_context;
		mutable ComPtr< ID3D11Buffer > m_buffer;
		mutable size_t m_nb_data_elements;
	};

}

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "rendering\structured_buffer.tpp"

#pragma endregion