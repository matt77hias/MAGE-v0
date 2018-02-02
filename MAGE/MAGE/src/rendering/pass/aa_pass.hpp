#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "camera\viewport.hpp"
#include "shader\shader.hpp"
#include "rendering\aa_descriptor.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations end Definitions
//-----------------------------------------------------------------------------
namespace mage {

	/**
	 A class of AA passes for performing AA.
	 */
	class AAPass final {

	public:

		//---------------------------------------------------------------------
		// Class Member Methods
		//---------------------------------------------------------------------

		/**
		 Returns the AA pass associated with the current engine.

		 @pre			The scene renderer associated with the current engine 
						must be loaded.
		 @return		A pointer to the AA pass associated with the current
						engine.
		 */
		static AAPass *Get();

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		/**
		 Constructs a AA pass.

		 @pre			The renderer associated with the current engine must be 
						loaded.
		 @pre			The resource manager associated with the current engine 
						must be loaded.
		 */
		AAPass();

		/**
		 Constructs a AA pass from the given AA 
		 pass.

		 @param[in]		pass
						A reference to the AA pass to copy.
		 */
		AAPass(const AAPass &pass) = delete;

		/**
		 Constructs a AA pass by moving the given AA 
		 shading pass.

		 @param[in]		pass
						A reference to the AA pass to move.
		 */
		AAPass(AAPass &&pass) noexcept;

		/**
		 Destructs this AA pass.
		 */
		~AAPass();

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------

		/**
		 Copies the given AA pass to this AA pass.

		 @param[in]		pass
						A reference to the AA pass to copy.
		 @return		A reference to the copy of the given AA pass (i.e. 
						this AA pass).
		 */
		AAPass &operator=(const AAPass &pass) = delete;

		/**
		 Moves the given AA pass to this AA pass.

		 @param[in]		pass
						A reference to the AA pass to move.
		 @return		A reference to the moved AA pass (i.e. this AA pass).
		 */
		AAPass &operator=(AAPass &&pass) = delete;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Dispatches an AA preprocess.

		 @param[in]		viewport
						A reference to the viewport.
		 @param[in]		desc
						The AA descriptor.
		 @throws		Exception
						Failed to render the scene.
		 */
		void DispatchPreprocess(const Viewport &viewport, AADescriptor desc);

		/**
		 Dispatches an AA pass.

		 @param[in]		viewport
						A reference to the viewport.
		 @param[in]		desc
						The AA descriptor.
		 @throws		Exception
						Failed to render the scene.
		 */
		void Dispatch(const Viewport &viewport, AADescriptor desc);

	private:

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Updates the compute shaders of this AA pass.

		 @pre			The resource manager associated with the current 
						engine must be loaded.
		 @param[in]		desc
						The AA descriptor.
		 @throws		Exception
						Failed to update the compute shaders of this AA pass.
		 */
		void UpdateCSs(AADescriptor desc);

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		/**
		 A pointer to the device context of this AA pass.
		 */
		ID3D11DeviceContext4 * const m_device_context;

		/**
		 A pointer to the AA preprocess compute shader of this AA pass.
		 */
		ComputeShaderPtr m_preprocess_cs;

		/**
		 A pointer to the AA compute shader of this AA pass.
		 */
		ComputeShaderPtr m_cs;

		/**
		 The current BRDF of this variable shading pass.
		 */
		AADescriptor m_aa_desc;
	};
}