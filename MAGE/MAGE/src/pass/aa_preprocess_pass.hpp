#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "pass\pass_buffer.hpp"
#include "shader\shader.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations end Definitions
//-----------------------------------------------------------------------------
namespace mage {

	/**
	 A class of AA preprocess passes for performing AA.
	 */
	class AAPreprocessPass final {

	public:

		//---------------------------------------------------------------------
		// Class Member Methods
		//---------------------------------------------------------------------

		/**
		 Returns the AA preprocess pass associated with the current 
		 engine.

		 @pre			The scene renderer associated with the current engine 
						must be loaded.
		 @return		A pointer to the AA preprocess pass associated 
						with the current engine.
		 */
		static AAPreprocessPass *Get();

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		/**
		 Constructs a AA preprocess pass.

		 @pre			The renderer associated with the current engine must be 
						loaded.
		 @pre			The resource manager associated with the current engine 
						must be loaded.
		 */
		AAPreprocessPass();

		/**
		 Constructs a AA preprocess pass from the given AA preprocess pass 
		 pass.

		 @param[in]		render_pass
						A reference to the AA preprocess pass to copy.
		 */
		AAPreprocessPass(const AAPreprocessPass &render_pass) = delete;

		/**
		 Constructs a AA preprocess pass by moving the given AA preprocess 
		 pass.

		 @param[in]		render_pass
						A reference to the AA preprocess pass to move.
		 */
		AAPreprocessPass(AAPreprocessPass &&render_pass);

		/**
		 Destructs this AA preprocess pass.
		 */
		~AAPreprocessPass();

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------

		/**
		 Copies the given AA preprocess pass to this AA preprocess pass.

		 @param[in]		render_pass
						A reference to the AA preprocess pass to copy.
		 @return		A reference to the copy of the given AA preprocess pass 
						(i.e. this AA preprocess pass).
		 */
		AAPreprocessPass &operator=(
			const AAPreprocessPass &render_pass) = delete;

		/**
		 Moves the given AA preprocess pass to this AA preprocess pass.

		 @param[in]		render_pass
						A reference to the AA preprocess pass to move.
		 @return		A reference to the moved AA preprocess pass (i.e. this 
						AA preprocess pass).
		 */
		AAPreprocessPass &operator=(
			AAPreprocessPass &&render_pass) = delete;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Binds the fixed state of this AA preprocess pass.
		 */
		void BindFixedState() const noexcept;

		/**
		 Render.

		 @param[in]		viewport
						A reference to the viewport.
		 @throws		FormattedException
						Failed to render the scene.
		 */
		void Render(const Viewport &viewport);
		
	private:

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		/**
		 A pointer to the device context of this AA preprocess pass.
		 */
		ID3D11DeviceContext2 * const m_device_context;

		/**
		 A pointer to the compute shader of this AA preprocess pass.
		 */
		SharedPtr< const ComputeShader > m_cs;
	};
}