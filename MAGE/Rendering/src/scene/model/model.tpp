#pragma region

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage::rendering {

	template< typename PipelineStageT >
	inline void Model::BindBuffer(ID3D11DeviceContext& device_context, 
								  U32 slot) const noexcept {

		m_buffer.Bind< PipelineStageT >(device_context, slot);
	}
}