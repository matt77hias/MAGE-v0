#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "memory\types.hpp"
#include "rendering\pipeline.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Defines
//-----------------------------------------------------------------------------
#pragma region

#define MAGE_DEFAULT_DISPLAY_GAMMA  2.2f

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	/**
	 A struct of display configurations.
	 */
	struct DisplayConfiguration final {

	public:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		/**
		 Constructs a display configuration.

		 @pre			@a display_mode must be compatible with
						@a adapter and @a output.
		 @param[in]		adapter
						A pointer to the adapter.
		 @param[in]		output
						A pointer to the output.
		 @param[in]		display_mode
						A reference to the display mode.
		 @param[in]		windowed
						The windowed/fullscreen mode.
		 @param[in]		vsync
						The V-sync mode.
		 @param[in]		nb_MSAA_samples
						The number of MSAA samples.
		 @param[in]		gamma
						The gamma value.
		 */
		explicit DisplayConfiguration(
			ComPtr< IDXGIAdapter2 > adapter, 
			ComPtr< IDXGIOutput2 > output,
			const DXGI_MODE_DESC1 &display_mode, 
			bool windowed, bool vsync, 
			UINT nb_MSAA_samples = 1,
			float gamma = MAGE_DEFAULT_DISPLAY_GAMMA)
			: m_adapter(adapter), m_output(output),
			m_display_mode(display_mode), m_MSAA_sample_desc{}, 
			m_windowed(windowed), m_vsync(vsync), m_gamma(gamma) {

			SetMSAASampleDesc(nb_MSAA_samples);
		}

		/**
		 Constructs a display configuration from the given display configuration.

		 @param[in]		display_configuration
						A reference to a display configuration to copy.
		 */
		DisplayConfiguration(const DisplayConfiguration &display_configuration) = default;

		/**
		 Constructs a display configuration by moving the given display configuration.

		 @param[in]		display_configuration
						A reference to a display configuration to move.
		 */
		DisplayConfiguration(DisplayConfiguration &&display_configuration) = default;

		/**
		 Destructs this display configuration.
		 */
		~DisplayConfiguration() = default;
		
		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------

		/**
		 Copies the given display configuration to this display configuration.

		 @param[in]		display_configuration
						A reference to a display configuration to copy.
		 @return		A reference to the copy of the given display configuration
						(i.e. this display configuration).
		 */
		DisplayConfiguration &operator=(const DisplayConfiguration &display_configuration) = default;

		/**
		 Moves the given display configuration to this display configuration.

		 @param[in]		display_configuration
						A reference to a display configuration to move.
		 @return		A reference to the moved display configuration
						(i.e. this display configuration).
		 */
		DisplayConfiguration &operator=(DisplayConfiguration &&display_configuration) = default;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Returns the adapter of this display configuration.

		 @return		A pointer to the adapter
						of this display configuration.
		 */
		IDXGIAdapter2 *GetAdapter() const noexcept {
			return m_adapter.Get();
		}

		/**
		 Returns the output of this display configuration.

		 @return		A pointer to the output
						of this display configuration.
		 */
		IDXGIOutput2 *GetOutput() const noexcept {
			return m_output.Get();
		}

		/**
		 Returns the display width in pixels of this display configuration.

		 @return		The display width in pixels of this display configuration.
		 */
		uint32_t GetDisplayWidth() const noexcept {
			return static_cast< uint32_t >(m_display_mode.Width);
		}

		/**
		 Returns the display height in pixels of this display configuration.

		 @return		The display height in pixels of this display configuration.
		 */
		uint32_t GetDisplayHeight() const noexcept {
			return static_cast< uint32_t >(m_display_mode.Height);
		}
		
		/**
		 Returns the rounded display refresh rate of this display configuration.

		 @return		The rounded display refresh rate of this display configuration.
		 */
		uint32_t GetDisplayRoundedRefreshRate() const noexcept {
			const float n = static_cast< float >(m_display_mode.RefreshRate.Numerator);
			const float d = static_cast< float >(m_display_mode.RefreshRate.Denominator);
			return static_cast< uint32_t >(round(n / d));
		}

		/**
		 Returns the display refresh rate of this display configuration.

		 @return		The display refresh rate of this display configuration.
		 */
		const DXGI_RATIONAL GetDisplayRefreshRate() const noexcept{
			return m_display_mode.RefreshRate;
		}
		
		/**
		 Returns the display format of this display configuration.

		 @return		The display format of this display configuration.
		 */
		DXGI_FORMAT GetDisplayFormat() const noexcept {
			return m_display_mode.Format;
		}

		/**
		 Returns the display mode of this display configuration.

		 @return		The display mode of this display configuration.
		 */
		const DXGI_MODE_DESC1 &GetDisplayMode() const noexcept {
			return m_display_mode;
		}

		/**
		 Sets the display mode of this display configuration to the given
		 display mode.

		 @pre			@a display_mode must be compatible with
						the adapter and output of this display configuration.
		 @param[in]		display_mode
						A reference to the display mode.
		 */
		void SetDisplayMode(const DXGI_MODE_DESC1 &display_mode) noexcept {
			m_display_mode = display_mode;
		}

		/**
		 Checks whether MSAA should be used for this display configuration.

		 @return		@c true if MSAA should be used for this display configuration.
						@c false otherwise.
		 */
		bool UseMSAA() const noexcept {
			return m_MSAA_sample_desc.Count != 1;
		}

		/**
		 Gets the MSAA sample descriptor of this display configuration.

		 @return		A reference to the MSAA sample descriptor 
						of this display configuration.
		 */
		const DXGI_SAMPLE_DESC &GetMSAASampleDesc() const noexcept {
			return m_MSAA_sample_desc;
		}

		/**
		 Sets the MSAA sample descriptor of this display configuration
		 to the given number of MSAA samples and quality level.

		 @param[in]		nb_MSAA_samples
						The number of MSAA samples.
		 @param[in]		MSAA_quality_level
						The MSAA quality level.
		 */
		void SetMSAASampleDesc(UINT nb_MSAA_samples, UINT MSAA_quality_level = 0) noexcept;

		/**
		 Sets the MSAA sample descriptor of this display configuration
		 to the given MSAA sample descriptor.

		 @param[in]		MSAA_sample_desc
						A reference to the MSAA sample descriptor
		 */
		void SetMSAASampleDesc(const DXGI_SAMPLE_DESC &MSAA_sample_desc) noexcept {
			SetMSAASampleDesc(MSAA_sample_desc.Count, MSAA_sample_desc.Quality);
		}

		/**
		 Updates the MSAA sample descriptor according to the given device.

		 @pre			@a device is not equal to @c nullptr.
		 @param[in]		device
						A pointer to the device.
		 */
		void UpdateMSAASampleDesc(ID3D11Device2 *device) noexcept;

		/**
		 Checks whether the application should run in windowed mode
		 for this display configuration.

		 @return		@c true if the application should run in windowed mode
						for this display configuration.
						@c false otherwise.
		 */
		bool IsWindowed() const noexcept {
			return m_windowed;
		}

		/**
		 Sets the windowed/fullscreen mode of this display configuration 
		 to the given windowed/fullscreen mode.

		 @param[in]		windowed
						@c true if windowed mode.
						@c false otherwise.
		 */
		void SetWindowed(bool windowed = true) noexcept {
			m_windowed = windowed;
		}

		/**
		 Checks whether the application should run in full screen mode
		 for this display configuration.

		 @return		@c true if the application should run in full screen mode
						for this display configuration.
						@c false otherwise.
		 */
		bool IsFullScreen() const noexcept {
			return !m_windowed;
		}

		/**
		 Sets the windowed/fullscreen mode of this display configuration
		 to the given windowed/fullscreen mode.

		 @param[in]		fullscreen
						@c true if fullscreen mode.
						@c false otherwise.
		 */
		void SetFullScreen(bool fullscreen = true) noexcept {
			SetWindowed(!fullscreen);
		}

		/**
		 Checks whether V-sync should be enabled
		 for this display configuration.

		 @return		@c true if v-sync should be enabled
						for this display configuration.
						@c false otherwise.
		 */
		bool IsVSynced() const noexcept {
			return m_vsync;
		}

		/**
		 Sets the V-sync mode of this display configuration
		 to the given V-sync mode.

		 @param[in]		vsync
						@c true if V-sync mode.
						@c false otherwise.
		 */
		void SetVSync(bool vsync = true) noexcept {
			m_vsync = vsync;
		}

		/**
		 Returns the gamma value used for gamma correction 
		 of this display configuration.

		 @return		The gamma value used for gamma correction 
						of this display configuration.
		 */
		float GetGamma() const noexcept {
			return m_gamma;
		}

		/**
		 Sets the gamma value used for gamma correction 
		 of this display configuration to the given value.

		 @param[in]		gamma
						The gamma value.
		 */
		void SetGamma(float gamma) noexcept {
			m_gamma = gamma;
		}

	private:

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		/**
		 A pointer to the adapter (e.g. video card) of this display configuration.
		 */
		ComPtr< IDXGIAdapter2 > m_adapter;

		/**
		A pointer to the output (e.g. screen monitor) of this display configuration.
		*/
		ComPtr< IDXGIOutput2 > m_output;

		/**
		 The display mode of this display configuration.
		 */
		DXGI_MODE_DESC1 m_display_mode;

		/**
		 The number of MSAA samples of this display configuration.
		 */
		DXGI_SAMPLE_DESC m_MSAA_sample_desc;

		/**
		 Flag indicating whether the application should run in windowed mode
		 for this display configuration.
		 */
		bool m_windowed;

		/**
		 Flag indicating whether V-sync should be enabled
		 for this display configuration.
		 */
		bool m_vsync;

		/**
		 The gamma value used for gamma correction of this display configuration.
		 */
		float m_gamma;
	};
}