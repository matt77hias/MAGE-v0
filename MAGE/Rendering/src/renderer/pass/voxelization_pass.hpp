#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "renderer\buffer\voxel_grid.hpp"
#include "renderer\state_manager.hpp"
#include "resource\rendering_resource_manager.hpp"
#include "scene\rendering_world.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations end Definitions
//-----------------------------------------------------------------------------
namespace mage::rendering {

	/**
	 A class of voxelization passes for rendering models using a variable
	 (material dependent) shading.
	 */
	class VoxelizationPass {

	public:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		/**
		 Constructs a voxelization pass.

		 @param[in]		device
						A reference to the device.
		 @param[in]		device_context
						A reference to the device context.
		 @param[in]		state_manager
						A reference to the state manager.
		 @param[in]		resource_manager
						A reference to the resource manager.
		 */
		explicit VoxelizationPass(ID3D11Device& device,
								  ID3D11DeviceContext& device_context,
								  StateManager& state_manager,
								  ResourceManager& resource_manager);

		/**
		 Constructs a voxelization pass from the given voxelization
		 pass.

		 @param[in]		pass
						A reference to the voxelization pass to copy.
		 */
		VoxelizationPass(const VoxelizationPass& pass) = delete;

		/**
		 Constructs a voxelization pass by moving the given variable
		 shading pass.

		 @param[in]		pass
						A reference to the voxelization pass to move.
		 */
		VoxelizationPass(VoxelizationPass&& pass) noexcept;

		/**
		 Destructs this voxelization pass.
		 */
		~VoxelizationPass();

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------

		/**
		 Copies the given voxelization pass to this voxelization pass.

		 @param[in]		pass
						A reference to the voxelization pass to copy.
		 @return		A reference to the copy of the given voxelization
						pass (i.e. this voxelization pass).
		 */
		VoxelizationPass& operator=(const VoxelizationPass& pass) = delete;

		/**
		 Moves the given voxelization pass to this voxelization pass.

		 @param[in]		pass
						A reference to the voxelization pass to move.
		 @return		A reference to the moved voxelization pass (i.e.
						this voxelization pass).
		 */
		VoxelizationPass& operator=(VoxelizationPass&& pass) noexcept;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Renders the world.

		 @param[in]		world
						A reference to the world.
		 @param[in]		world_to_projection
						The world-to-projection transformation matrix.
		 @param[in]		resolution
						The resolution of the regular voxel grid.
		 @throws		Exception
						Failed to render the world.
		 */
		void XM_CALLCONV Render(const World& world,
			                    FXMMATRIX world_to_projection,
								std::size_t resolution);

	private:

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		void SetupRasterizerState(ID3D11Device& device);

		/**
		 Sets up the voxel grid of this voxelization pass.

		 @param[in]		resolution
						The resolution of the regular voxel grid.
		 @throws		Exception
						Failed to render the world.
		 */
		void SetupVoxelGrid(std::size_t resolution);

		/**
		 Binds the fixed state of this voxelization pass.
		 */
		void BindFixedState() const noexcept;

		/**
		 Renders the given world.

		 @param[in]		world
						A reference to the world.
		 @param[in]		world_to_projection
						The world-to-projection transformation matrix.
		 @throws		Exception
						Failed to render the world.
		 */
		void XM_CALLCONV Render(const World& world,
			                    FXMMATRIX world_to_projection) const;

		/**
		 Renders the given model.

		 @param[in]		model
						A reference to the model.
		 @param[in]		world_to_projection
						The world-to-projection transformation matrix.
		 */
		void XM_CALLCONV Render(const Model& model,
								FXMMATRIX world_to_projection) const noexcept;

		/**
		 Dispatches this voxelization pass.
		 */
		void Dispatch() const noexcept;

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		/**
		 A reference to the device context of this voxelization pass.
		 */
		std::reference_wrapper< ID3D11DeviceContext > m_device_context;

		/**
		 A reference to the state manager of this voxelization pass.
		 */
		std::reference_wrapper< StateManager > m_state_manager;

		/**
		 A reference to the resource manager of this voxelization pass.
		 */
		std::reference_wrapper< ResourceManager > m_resource_manager;

		/**
		 A pointer to the rasterizer state of this voxelization pass.
		 */
		ComPtr< ID3D11RasterizerState2 > m_rs;

		/**
		 A pointer to the vertex shader of this voxelization pass.
		 */
		VertexShaderPtr m_vs;

		/**
		 A pointer to the geometry shader of this voxelization pass.
		 */
		GeometryShaderPtr m_gs;

		/**
		 A pointer to the compute shader of this voxelization pass.
		 */
		ComputeShaderPtr m_cs;

		/**
		 The voxel grid of this voxelization pass.
		 */
		UniquePtr< VoxelGrid > m_voxel_grid;
	};
}