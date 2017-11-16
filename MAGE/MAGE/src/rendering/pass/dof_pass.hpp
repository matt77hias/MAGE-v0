#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "camera\viewport.hpp"
#include "shader\shader.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations end Definitions
//-----------------------------------------------------------------------------
namespace mage {

	/**
	 A class of DOF passes for performing DOF.
	 */
	class DOFPass final {

	public:

		//---------------------------------------------------------------------
		// Class Member Methods
		//---------------------------------------------------------------------

		/**
		 Returns the DOF pass associated with the current engine.

		 @pre			The scene renderer associated with the current engine 
						must be loaded.
		 @return		A pointer to the DOF pass associated with the current
						engine.
		 */
		static DOFPass *Get();

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		/**
		 Constructs a DOF pass.

		 @pre			The renderer associated with the current engine must be 
						loaded.
		 @pre			The resource manager associated with the current engine 
						must be loaded.
		 */
		DOFPass();

		/**
		 Constructs a DOF pass from the given DOF 
		 pass.

		 @param[in]		render_pass
						A reference to the DOF pass to copy.
		 */
		DOFPass(const DOFPass &render_pass) = delete;

		/**
		 Constructs a DOF pass by moving the given DOF 
		 shading pass.

		 @param[in]		render_pass
						A reference to the DOF pass to move.
		 */
		DOFPass(DOFPass &&render_pass);

		/**
		 Destructs this DOF pass.
		 */
		~DOFPass();

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------

		/**
		 Copies the given DOF pass to this DOF pass.

		 @param[in]		render_pass
						A reference to the DOF pass to copy.
		 @return		A reference to the copy of the given DOF pass (i.e. 
						this DOF pass).
		 */
		DOFPass &operator=(const DOFPass &render_pass) = delete;

		/**
		 Moves the given DOF pass to this DOF pass.

		 @param[in]		render_pass
						A reference to the DOF pass to move.
		 @return		A reference to the moved DOF pass (i.e. this DOF pass).
		 */
		DOFPass &operator=(DOFPass &&render_pass) = delete;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Dispatches an DOF pass.

		 @param[in]		viewport
						A reference to the viewport.
		 */
		void Dispatch(const Viewport &viewport) const noexcept;

	private:

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		/**
		 A pointer to the device context of this DOF pass.
		 */
		ID3D11DeviceContext4 * const m_device_context;

		/**
		 A pointer to the compute shader of this DOF pass.
		 */
		SharedPtr< const ComputeShader > m_cs;
	};
}