#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "rendering\pipeline.hpp"
#include "rendering\aa_descriptor.hpp"

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
		// Class Member Variables
		//---------------------------------------------------------------------

		/**
		 Returns the display configuration of the rendering manager associated 
		 with the current engine.

		 @pre			The rendering manager associated with the current 
						engine must be loaded.
		 @return		A pointer to the display configuration of the rendering 
						manager associated with the current engine.
		 */
		static const DisplayConfiguration *Get() noexcept;

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		/**
		 Constructs a display configuration.

		 @pre			@a display_mode must be compatible with @a adapter 
						and @a output.
		 @param[in]		adapter
						A pointer to the adapter.
		 @param[in]		output
						A pointer to the output.
		 @param[in]		display_mode
						A reference to the display mode.
		 */
		explicit DisplayConfiguration(
			ComPtr< IDXGIAdapter2 > adapter,
			ComPtr< IDXGIOutput2 > output,
			const DXGI_MODE_DESC1 &display_mode)
			: m_adapter(adapter),
			m_output(output),
			m_display_mode(display_mode),
			m_aa_desc(AADescriptor::None),
			m_windowed(true),
			m_vsync(false),
			m_gamma(2.2f) {}
		
		/**
		 Constructs a display configuration from the given display 
		 configuration.

		 @param[in]		display_configuration
						A reference to a display configuration to copy.
		 */
		DisplayConfiguration(
			const DisplayConfiguration &display_configuration) = default;

		/**
		 Constructs a display configuration by moving the given display 
		 configuration.

		 @param[in]		display_configuration
						A reference to a display configuration to move.
		 */
		DisplayConfiguration(
			DisplayConfiguration &&display_configuration) = default;

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
		 @return		A reference to the copy of the given display 
						configuration (i.e. this display configuration).
		 */
		DisplayConfiguration &operator=(
			const DisplayConfiguration &display_configuration) = default;

		/**
		 Moves the given display configuration to this display configuration.

		 @param[in]		display_configuration
						A reference to a display configuration to move.
		 @return		A reference to the moved display configuration (i.e. 
						this display configuration).
		 */
		DisplayConfiguration &operator=(
			DisplayConfiguration &&display_configuration) = default;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Returns the adapter of this display configuration.

		 @return		A pointer to the adapter of this display configuration.
		 */
		IDXGIAdapter2 *GetAdapter() const noexcept {
			return m_adapter.Get();
		}

		/**
		 Returns the output of this display configuration.

		 @return		A pointer to the output of this display configuration.
		 */
		IDXGIOutput2 *GetOutput() const noexcept {
			return m_output.Get();
		}

		/**
		 Returns the display width in pixels of this display configuration.

		 @return		The display width in pixels of this display 
						configuration.
		 */
		U32 GetDisplayWidth() const noexcept {
			return static_cast< U32 >(m_display_mode.Width);
		}
		
		/**
		 Returns the display height in pixels of this display configuration.

		 @return		The display height in pixels of this display 
						configuration.
		 */
		U32 GetDisplayHeight() const noexcept {
			return static_cast< U32 >(m_display_mode.Height);
		}
		
		/**
		 Returns the super-sampled display width in pixels of this display 
		 configuration.

		 @return		The super-sampled display width in pixels of this 
						display configuration.
		 */
		U32 GetSSDisplayWidth() const noexcept {
			const U32 multiplier = GetResolutionMultiplier(m_aa_desc);
			return multiplier * GetDisplayWidth();
		}
		
		/**
		 Returns the super-sampled height in pixels of this display 
		 configuration.

		 @return		The super-sampled height in pixels of this display 
						configuration.
		 */
		U32 GetSSDisplayHeight() const noexcept {
			const U32 multiplier = GetResolutionMultiplier(m_aa_desc);
			return multiplier * GetDisplayHeight();
		}
		
		/**
		 Returns the rounded display refresh rate of this display 
		 configuration.

		 @return		The rounded display refresh rate of this display 
						configuration.
		 */
		U32 GetDisplayRoundedRefreshRate() const noexcept {
			const F32 n = static_cast< F32 >(m_display_mode.RefreshRate.Numerator);
			const F32 d = static_cast< F32 >(m_display_mode.RefreshRate.Denominator);
			return static_cast< U32 >(round(n / d));
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

		 @pre			@a display_mode must be compatible with the adapter and 
						output of this display configuration.
		 @param[in]		display_mode
						A reference to the display mode.
		 */
		void SetDisplayMode(const DXGI_MODE_DESC1 &display_mode) noexcept {
			m_display_mode = display_mode;
		}

		/**
		 Returns the Anti-Aliasing descriptor of this display configuration.

		 @return		The Anti-Aliasing descriptor of this display 
						configuration.
		 */
		AADescriptor GetAADescriptor() const noexcept {
			return m_aa_desc;
		}
		
		/**
		 Sets the Anti-Aliasing descriptor of this display configuration to the
		 given Anti-Aliasing descriptor.

		 @param[in]		desc
						A reference to the Anti-Aliasing descriptor.
		 */
		void SetAADescriptor(AADescriptor desc) noexcept {
			m_aa_desc = desc;
		}
		
		/**
		 Checks whether the application should run in windowed mode for this 
		 display configuration.

		 @return		@c true if the application should run in windowed mode
						for this display configuration. @c false otherwise.
		 */
		bool IsWindowed() const noexcept {
			return m_windowed;
		}
		
		/**
		 Sets the windowed/fullscreen mode of this display configuration to the 
		 given windowed/fullscreen mode.

		 @param[in]		windowed
						@c true if windowed mode. @c false otherwise.
		 */
		void SetWindowed(bool windowed = true) noexcept {
			m_windowed = windowed;
		}
		
		/**
		 Checks whether the application should run in full screen mode for this 
		 display configuration.

		 @return		@c true if the application should run in full screen 
						mode for this display configuration. @c false 
						otherwise.
		 */
		bool IsFullScreen() const noexcept {
			return !m_windowed;
		}

		/**
		 Sets the windowed/fullscreen mode of this display configuration to the 
		 given windowed/fullscreen mode.

		 @param[in]		fullscreen
						@c true if fullscreen mode. @c false otherwise.
		 */
		void SetFullScreen(bool fullscreen = true) noexcept {
			SetWindowed(!fullscreen);
		}

		/**
		 Checks whether V-sync should be enabled for this display 
		 configuration.

		 @return		@c true if v-sync should be enabled for this display 
						configuration. @c false otherwise.
		 */
		bool IsVSynced() const noexcept {
			return m_vsync;
		}

		/**
		 Sets the V-sync mode of this display configuration to the given V-sync 
		 mode.

		 @param[in]		vsync
						@c true if V-sync mode. @c false otherwise.
		 */
		void SetVSync(bool vsync = true) noexcept {
			m_vsync = vsync;
		}
		
		/**
		 Returns the gamma value used for gamma correction of this display 
		 configuration.

		 @return		The gamma value used for gamma correction of this 
						display configuration.
		 */
		F32 GetGamma() const noexcept {
			return m_gamma;
		}
		
		/**
		 Sets the gamma value used for gamma correction of this display 
		 configuration to the given value.

		 @param[in]		gamma
						The gamma value.
		 */
		void SetGamma(F32 gamma) noexcept {
			m_gamma = gamma;
		}

	private:

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		/**
		 A pointer to the adapter (e.g. video card) of this display 
		 configuration.
		 */
		ComPtr< IDXGIAdapter2 > m_adapter;

		/**
		A pointer to the output (e.g. screen monitor) of this display 
		configuration.
		*/
		ComPtr< IDXGIOutput2 > m_output;

		/**
		 The display mode of this display configuration.
		 */
		DXGI_MODE_DESC1 m_display_mode;

		/**
		 The Anti-Aliasing sample descriptor of this display configuration.
		 */
		AADescriptor m_aa_desc;
		
		/**
		 Flag indicating whether the application should run in windowed mode
		 for this display configuration.
		 */
		bool m_windowed;

		/**
		 Flag indicating whether V-sync should be enabled for this display 
		 configuration.
		 */
		bool m_vsync;

		/**
		 The gamma value used for gamma correction of this display 
		 configuration.
		 */
		F32 m_gamma;
	};
}