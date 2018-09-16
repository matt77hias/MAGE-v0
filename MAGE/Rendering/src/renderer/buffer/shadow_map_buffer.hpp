#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "scene\camera\viewport.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// System Includes
//-----------------------------------------------------------------------------
#pragma region

#include <vector>

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Defines
//-----------------------------------------------------------------------------
#pragma region

//TODO: make configurable
#define MAGE_DEFAULT_DEPTH_BIAS               100
#define MAGE_DEFAULT_SLOPE_SCALED_DEPTH_BIAS  1.0f
#define MAGE_DEFAULT_DEPTH_BIAS_CLAMP         0.0f

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage::rendering {

	//-------------------------------------------------------------------------
	// DepthFormat
	//-------------------------------------------------------------------------

	enum class DepthFormat : U8 {
		D16,
		D32
	};

	//-------------------------------------------------------------------------
	// ShadowMapBuffer
	//-------------------------------------------------------------------------
	#pragma region

	class ShadowMapBuffer {

	public:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		explicit ShadowMapBuffer(ID3D11Device& device,
								 std::size_t nb_shadow_maps,
								 const U32x2& resolution = { 512u, 512u }, 
			                     DepthFormat format = DepthFormat::D16);
		ShadowMapBuffer(const ShadowMapBuffer& buffer) = delete;
		ShadowMapBuffer(ShadowMapBuffer&& buffer) noexcept;
		~ShadowMapBuffer();

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------

		ShadowMapBuffer& operator=(const ShadowMapBuffer& buffer) = delete;
		ShadowMapBuffer& operator=(ShadowMapBuffer&& buffer) noexcept;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		[[nodiscard]]
		std::size_t GetNumberOfShadowMaps() const noexcept {
			using std::size;
			return size(m_dsvs);
		}

		void Bind(ID3D11DeviceContext& device_context) const noexcept {
			m_viewport.Bind(device_context);
		}
		void BindRasterizerState(ID3D11DeviceContext& device_context) const noexcept {
			Pipeline::RS::BindState(device_context, m_rasterizer_state.Get());
		}
		
		void ClearDSVs(ID3D11DeviceContext& device_context) const noexcept {
			for (const auto& dsv : m_dsvs) {
				Pipeline::OM::ClearDepthOfDSV(device_context, dsv.Get());
			}
		}
		void BindDSV(ID3D11DeviceContext& device_context, 
					 std::size_t dsv_index) const noexcept {

			Pipeline::OM::BindRTVAndDSV(device_context, nullptr, m_dsvs[dsv_index].Get());
		}
		[[nodiscard]]
		ID3D11DepthStencilView& GetDSV(std::size_t dsv_index) const noexcept {
			return *m_dsvs[dsv_index].Get();
		}
		[[nodiscard]]
		ID3D11ShaderResourceView& GetSRV() const noexcept {
			return *m_srv.Get();
		}

	private:

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		void SetupRasterizerState(ID3D11Device& device);

		void SetupShadowMapBuffer(ID3D11Device& device,
								  std::size_t nb_shadow_maps);
		void SetupShadowMapArray(ID3D11Device& device,
								 std::size_t nb_shadow_maps,
			                     DXGI_FORMAT texture_format,
			                     DXGI_FORMAT dsv_format, 
			                     DXGI_FORMAT srv_format);

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		DepthFormat m_format;
		Viewport m_viewport;
		ComPtr< ID3D11RasterizerState > m_rasterizer_state;
		
		std::vector< ComPtr< ID3D11DepthStencilView > > m_dsvs;
		ComPtr< ID3D11ShaderResourceView > m_srv;
	};

	#pragma endregion

	//-------------------------------------------------------------------------
	// ShadowCubeMapBuffer
	//-------------------------------------------------------------------------
	#pragma region

	class ShadowCubeMapBuffer {

	public:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		explicit ShadowCubeMapBuffer(ID3D11Device& device,
									 std::size_t nb_shadow_cube_maps,
									 const U32x2& resolution = { 512u, 512u },
			                         DepthFormat format = DepthFormat::D16);
		ShadowCubeMapBuffer(const ShadowCubeMapBuffer& buffer) = delete;
		ShadowCubeMapBuffer(ShadowCubeMapBuffer&& buffer) noexcept;
		~ShadowCubeMapBuffer();

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------

		ShadowCubeMapBuffer& operator=(const ShadowCubeMapBuffer& buffer) = delete;
		ShadowCubeMapBuffer& operator=(ShadowCubeMapBuffer&& buffer) noexcept;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		[[nodiscard]]
		std::size_t GetNumberOfShadowMaps() const noexcept {
			using std::size;
			return size(m_dsvs);
		}
		[[nodiscard]]
		std::size_t GetNumberOfShadowCubeMaps() const noexcept {
			using std::size;
			return size(m_dsvs) / 6u;
		}

		void Bind(ID3D11DeviceContext& device_context) const noexcept {
			m_viewport.Bind(device_context);
		}
		void BindRasterizerState(ID3D11DeviceContext& device_context) const noexcept {
			Pipeline::RS::BindState(device_context, m_rasterizer_state.Get());
		}
		
		void ClearDSVs(ID3D11DeviceContext& device_context) const noexcept {
			for (const auto& dsv : m_dsvs) {
				Pipeline::OM::ClearDepthOfDSV(device_context, dsv.Get());
			}
		}
		void BindDSV(ID3D11DeviceContext& device_context, 
					 std::size_t dsv_index) const noexcept {

			Pipeline::OM::BindRTVAndDSV(device_context, nullptr, m_dsvs[dsv_index].Get());
		}
		[[nodiscard]]
		ID3D11DepthStencilView& GetDSV(std::size_t dsv_index) const noexcept {
			return *m_dsvs[dsv_index].Get();
		}
		[[nodiscard]]
		ID3D11ShaderResourceView& GetSRV() const noexcept {
			return *m_srv.Get();
		}

	private:

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		void SetupRasterizerState(ID3D11Device& device);

		void SetupShadowCubeMapBuffer(ID3D11Device& device,
									  std::size_t nb_shadow_cube_maps);
		void SetupShadowCubeMapArray(ID3D11Device& device,
									 std::size_t nb_shadow_cube_maps,
			                         DXGI_FORMAT texture_format,
			                         DXGI_FORMAT dsv_format, 
			                         DXGI_FORMAT srv_format);

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		DepthFormat m_format;
		Viewport m_viewport;
		ComPtr< ID3D11RasterizerState > m_rasterizer_state;
		
		std::vector< ComPtr< ID3D11DepthStencilView > > m_dsvs;
		ComPtr< ID3D11ShaderResourceView > m_srv;
	};

	#pragma endregion
}