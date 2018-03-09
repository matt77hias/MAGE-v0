#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "meta\targetver.hpp"

#include "core\engine_setup.hpp"
#include "input_manager.hpp"
#include "rendering_manager.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	//-------------------------------------------------------------------------
	// Factory Method
	//-------------------------------------------------------------------------
	#pragma region

	// Forward dclaration.
	class Scene;

	/**
	 A class of engines.
	 */
	class Engine final {

	public:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		/**
		 Constructs an engine from the given engine setup.

		 @param[in]		setup
						A reference to an engine setup.
		 @param[in]		display_config
						The display configuration.
		 @throws		Exception
						Failed to initialize the engine.
		 */
		explicit Engine(const EngineSetup& setup, 
						rendering::DisplayConfiguration display_config);

		/**
		 Constructs an engine from the given engine.

		 @param[in]		engine
						A reference to the engine to copy.
		 */
		Engine(const Engine& engine) = delete;

		/**
		 Constructs an engine by moving the given engine.

		 @param[in]		engine
						A reference to the engine to move.
		 */
		Engine(Engine&& engine) noexcept;

		/**
		 Destructs this engine.
		 */
		~Engine();

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------	

		/**
		 Copies the given engine to this engine.

		 @param[in]		engine
						A reference to the engine to copy.
		 @return		A reference to the copy of the given engine (i.e. this 
						engine).
		 */
		Engine& operator=(const Engine& engine) = delete;

		/**
		 Copies the given engine to this engine.

		 @param[in]		engine
						A reference to the engine to move.
		 @return		A reference to the moved engine (i.e. this engine).
		 */
		Engine& operator=(Engine&& engine) = delete;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Runs this engine.

		 @param[in]		scene
						A reference to the start scene.
		 @param[in]		nCmdShow
						Controls how the engine window is to be shown.
		 @return		@c 0, if the function terminates before entering the 
						message loop.
		 @return		The @c wParam parameter contained in the @c WM_QUIT 
						message.
		 */
		[[nodiscard]]
		int Run(UniquePtr< Scene >&& scene, int nCmdShow = SW_NORMAL);

		/**
		 Returns the input manager of this engine.

		 @return		A reference to the input manager of this engine.
		 */
		[[nodiscard]]
		input::Manager& GetInputManager() noexcept;

		/**
		 Returns the input manager of this engine.

		 @return		A reference to the input manager of this engine.
		 */
		[[nodiscard]]
		const input::Manager& GetInputManager() const noexcept;

		/**
		 Returns the rendering manager of this engine.

		 @return		A reference to the rendering manager of this engine.
		 */
		[[nodiscard]]
		rendering::Manager& GetRenderingManager() noexcept;

		/**
		 Returns the rendering manager of this engine.

		 @return		A reference to the rendering manager of this engine.
		 */
		[[nodiscard]]
		const rendering::Manager& GetRenderingManager() const noexcept;

		/**
		 Sets the scene of this engine to the given scene.

		 @param[in]		scene
						A reference to the start scene.
		 */
		void RequestScene(UniquePtr< Scene >&& scene) noexcept;

	private:

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		class Impl;

		/**
		 The implementation of this engine.
		 */
		UniquePtr< Impl > m_impl;
	};

	#pragma endregion

	//-------------------------------------------------------------------------
	// Factory Method
	//-------------------------------------------------------------------------
	#pragma region

	UniquePtr< Engine > CreateEngine(const EngineSetup& setup);

	#pragma endregion
}
