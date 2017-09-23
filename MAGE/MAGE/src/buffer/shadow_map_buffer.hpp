#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "camera\viewport.hpp"
#include "collection\collection.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Defines
//-----------------------------------------------------------------------------
#pragma region

#define MAGE_DEFAULT_SHADOW_MAP_RESOLUTION 512

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	//-------------------------------------------------------------------------
	// DepthFormat
	//-------------------------------------------------------------------------

	enum struct DepthFormat {
		D16,
		D24
	};

	//-------------------------------------------------------------------------
	// ShadowMapBuffer
	//-------------------------------------------------------------------------

	struct ShadowMapBuffer final {

	public:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		explicit ShadowMapBuffer(
			size_t nb_shadow_maps = 1, 
			UINT width  = MAGE_DEFAULT_SHADOW_MAP_RESOLUTION,
			UINT height = MAGE_DEFAULT_SHADOW_MAP_RESOLUTION,
			DepthFormat format = DepthFormat::D16);
		explicit ShadowMapBuffer(ID3D11Device2 *device,
			size_t nb_shadow_maps = 1, 
			UINT width  = MAGE_DEFAULT_SHADOW_MAP_RESOLUTION,
			UINT height = MAGE_DEFAULT_SHADOW_MAP_RESOLUTION,
			DepthFormat format = DepthFormat::D16);
		ShadowMapBuffer(const ShadowMapBuffer &buffer) = delete;
		ShadowMapBuffer(ShadowMapBuffer &&buffer) = default;
		~ShadowMapBuffer() = default;

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------

		ShadowMapBuffer &operator=(const ShadowMapBuffer &buffer) = delete;
		ShadowMapBuffer &operator=(ShadowMapBuffer &&buffer) = delete;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		size_t GetNumberOfShadowMaps() const noexcept {
			return m_dsvs.size();
		}

		void BindViewport(ID3D11DeviceContext2 *device_context) const noexcept {
			m_viewport.BindViewport(device_context);
		}
		void ClearDSVs(ID3D11DeviceContext2 *device_context) const noexcept {

			for (const auto &dsv : m_dsvs) {
				Pipeline::OM::ClearDSV(device_context, dsv.Get());
			}
		}
		void BindDSV(ID3D11DeviceContext2 *device_context, 
			size_t dsv_index) const noexcept {

			Pipeline::OM::BindRTVAndDSV(device_context, nullptr, m_dsvs[dsv_index].Get());
		}
		ID3D11DepthStencilView *GetDSV(size_t dsv_index) const noexcept {
			return m_dsvs[dsv_index].Get();
		}
		ID3D11ShaderResourceView *GetSRV() const noexcept {
			return m_srv.Get();
		}

	private:

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		void SetupShadowMapBuffer(ID3D11Device2 *device,
			size_t nb_shadow_maps);
		void Setup16BitShadowMapArray(ID3D11Device2 *device,
			size_t nb_shadow_maps);
		void Setup24BitShadowMapArray(ID3D11Device2 *device,
			size_t nb_shadow_maps);
		void SetupShadowMapArray(ID3D11Device2 *device,
			size_t nb_shadow_maps, DXGI_FORMAT texture_format,
			DXGI_FORMAT dsv_format, DXGI_FORMAT srv_format);

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		UINT m_width;
		UINT m_height;
		DepthFormat m_format;
		Viewport m_viewport;
		
		vector< ComPtr< ID3D11DepthStencilView > > m_dsvs;
		ComPtr< ID3D11ShaderResourceView > m_srv;
	};

	//-------------------------------------------------------------------------
	// ShadowCubeMapBuffer
	//-------------------------------------------------------------------------

	struct ShadowCubeMapBuffer final {

	public:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		explicit ShadowCubeMapBuffer(
			size_t nb_shadow_cube_maps = 1, 
			UINT width  = MAGE_DEFAULT_SHADOW_MAP_RESOLUTION,
			UINT height = MAGE_DEFAULT_SHADOW_MAP_RESOLUTION,
			DepthFormat format = DepthFormat::D16);
		explicit ShadowCubeMapBuffer(ID3D11Device2 *device,
			size_t nb_shadow_cube_maps = 1,
			UINT width  = MAGE_DEFAULT_SHADOW_MAP_RESOLUTION,
			UINT height = MAGE_DEFAULT_SHADOW_MAP_RESOLUTION,
			DepthFormat format = DepthFormat::D16);
		ShadowCubeMapBuffer(const ShadowCubeMapBuffer &buffer) = delete;
		ShadowCubeMapBuffer(ShadowCubeMapBuffer &&buffer) = default;
		~ShadowCubeMapBuffer() = default;

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------

		ShadowCubeMapBuffer &operator=(const ShadowCubeMapBuffer &buffer) = delete;
		ShadowCubeMapBuffer &operator=(ShadowCubeMapBuffer &&buffer) = delete;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		size_t GetNumberOfShadowMaps() const noexcept {
			return m_dsvs.size();
		}
		size_t GetNumberOfShadowCubeMaps() const noexcept {
			return m_dsvs.size() / 6u;
		}

		void BindViewport(ID3D11DeviceContext2 *device_context) const noexcept {
			m_viewport.BindViewport(device_context);
		}
		void ClearDSVs(ID3D11DeviceContext2 *device_context) const noexcept {

			for (const auto &dsv : m_dsvs) {
				Pipeline::OM::ClearDSV(device_context, dsv.Get());
			}
		}
		void BindDSV(ID3D11DeviceContext2 *device_context, 
			size_t dsv_index) const noexcept {

			Pipeline::OM::BindRTVAndDSV(device_context, nullptr, m_dsvs[dsv_index].Get());
		}

		ID3D11DepthStencilView *GetDSV(size_t dsv_index) const noexcept {
			return m_dsvs[dsv_index].Get();
		}
		ID3D11ShaderResourceView *GetSRV() const noexcept {
			return m_srv.Get();
		}

	private:

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		void SetupShadowCubeMapBuffer(ID3D11Device2 *device,
			size_t nb_shadow_cube_maps);
		void Setup16BitShadowCubeMapArray(ID3D11Device2 *device,
			size_t nb_shadow_cube_maps);
		void Setup24BitShadowCubeMapArray(ID3D11Device2 *device,
			size_t nb_shadow_cube_maps);
		void SetupShadowCubeMapArray(ID3D11Device2 *device,
			size_t nb_shadow_cube_maps, DXGI_FORMAT texture_format,
			DXGI_FORMAT dsv_format, DXGI_FORMAT srv_format);

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		UINT m_width;
		UINT m_height;
		DepthFormat m_format;
		
		Viewport m_viewport;
		vector< ComPtr< ID3D11DepthStencilView > > m_dsvs;
		ComPtr< ID3D11ShaderResourceView > m_srv;
	};
}