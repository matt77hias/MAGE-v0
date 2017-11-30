#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "mesh\static_mesh.hpp"
#include "math\geometry\bounding_volume.hpp"
#include "material\material.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	/**
	 A class of models.
	 */
	class Model {

	public:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		/**
		 Constructs a model.

		 @pre			@a mesh is not equal to @c nullptr.
		 @param[in]		mesh
						A pointer to the mesh.
		 @param[in]		start_index
						The start index in the mesh.
		 @param[in]		nb_indices
						The number of indices in the mesh.
		 @param[in]		aabb
						The AABB.
		 @param[in]		bs
						The BS.
		 */
		explicit Model(SharedPtr< const Mesh > mesh, 
			size_t start_index, size_t nb_indices, 
			AABB aabb, BS bs);

		/**
		 Constructs a model from the given model.

		 @param[in]		model
						A reference to the model to copy.
		 */
		Model(const Model &model);

		/**
		 Constructs a model by moving the given model.

		 @param[in]		model
						A reference to the model to move.
		 */
		Model(Model &&model);

		/**
		 Destructs this model.
		 */
		virtual ~Model();

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------

		/**
		 Copies the given model to this model.

		 @param[in]		model
						A reference to the model to copy.
		 @return		A reference to the copy of the given model (i.e. this 
						model).
		 */
		Model &operator=(const Model &model) = delete;

		/**
		 Moves the given model to this model.

		 @param[in]		model
						A reference to the model to move.
		 @return		A reference to the moved model (i.e. this model).
		 */
		Model &operator=(Model &&model) = delete;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Clones this model.

		 @return		A pointer to the clone of this model.
		 */
		UniquePtr< Model > Clone() const {
			return CloneImplementation();
		}

		//---------------------------------------------------------------------
		// Member Methods: Geometry
		//---------------------------------------------------------------------

		/**
		 Returns the AABB of this model.

		 @return		A reference to the AABB of this model.
		 */
		const AABB &GetAABB() const noexcept {
			return m_aabb;
		}

		/**
		 Returns the BS of this model.

		 @return		A reference to the BS of this model.
		 */
		const BS &GetBS() const noexcept {
			return m_bs;
		}

		/**
		 Returns the start index of this model in the mesh of this model.

		 @return		The start index of this model in the mesh of this model.
		 */
		size_t GetStartIndex() const noexcept {
			return m_start_index;
		}

		/**
		 Returns the number of indices of this model in the mesh of this model.

		 @return		The number of indices of this model in the mesh of this 
						model.
		 */
		size_t GetNumberOfIndices() const noexcept {
			return m_nb_indices;
		}

		/**
		 Binds the mesh of this model.

		 @pre			@a device_context is not equal to @c nullptr.
		 @param[in]		device_context
						A pointer to the device context.
		 */
		void BindMesh(ID3D11DeviceContext4 *device_context) const noexcept {
			m_mesh->BindMesh(device_context);
		}

		/**
		 Binds the mesh of this model with given primitive topology.

		 @pre			@a device_context is not equal to @c nullptr.
		 @param[in]		device_context
						A pointer to the device context.
		 @param[in]		topology
						The primitive topology.
		 */
		void BindMesh(ID3D11DeviceContext4 *device_context, 
			D3D11_PRIMITIVE_TOPOLOGY topology) const noexcept {

			m_mesh->BindMesh(device_context, topology);
		}

		/**
		 Draws this model.

		 @pre			@a device_context is not equal to @c nullptr.
		 @param[in]		device_context
						A pointer to the device context.
		 */
		void Draw(ID3D11DeviceContext4 *device_context) const noexcept {
			m_mesh->Draw(device_context, m_start_index, m_nb_indices);
		}

		//---------------------------------------------------------------------
		// Member Methods: Occlusion
		//---------------------------------------------------------------------

		/**
		 Checks whether this model occludes light.

		 @return		@c true if this model occludes light. @c false 
						otherwise.
		 */
		bool OccludesLight() const noexcept {
			return m_light_occlusion;
		}

		/**
		 Enbales the occlusion of light by this model.
		 */
		void EnableLightOcclusion() noexcept {
			SetLightOcclusion(true);
		}

		/**
		 Dissables the occlusion of light by this model.
		 */
		void DissableLightOcclusion() noexcept {
			SetLightOcclusion(false);
		}

		/**
		 Toggles the occlusion of light by this model.
		 */
		bool ToggleLightOcclusion() noexcept {
			SetLightOcclusion(!m_light_occlusion);
		}

		/**
		 Sets the occlusion of light by this model to the given value.

		 @param[in]		light_occlusion
						@c true if this model needs to occlude light. @c false 
						otherwise.
		 */
		void SetLightOcclusion(bool light_occlusion) noexcept {
			m_light_occlusion = light_occlusion;
		}

		//---------------------------------------------------------------------
		// Member Methods: Appearance
		//---------------------------------------------------------------------

		/**
		 Returns the material of this model.

		 @return		A pointer to the material of this model.
		 */
		Material *GetMaterial() noexcept {
			return m_material.get();
		}

		/**
		 Returns the material of this model.

		 @return		A pointer to the material of this model.
		 */
		const Material *GetMaterial() const noexcept {
			return m_material.get();
		}

	private:

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Clones this model.

		 @return		A pointer to the clone of this model.
		 */
		virtual UniquePtr< Model > CloneImplementation() const;

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		/**
		 A pointer to the mesh of this model.
		 */
		SharedPtr< const Mesh > m_mesh;

		/**
		 The start index of this model in the mesh of this model.
		 */
		const size_t m_start_index;

		/**
		 The number of indices of this model in the mesh of this model.
		 */
		const size_t m_nb_indices;

		/**
		 The AABB of this model.
		 */
		const AABB m_aabb;

		/**
		 The BS of this model.
		 */
		const BS m_bs;

		/**
		 A flag indicating whether this model occludes light.
		 */
		bool m_light_occlusion;

		/**
		 A pointer to the material of this model.
		 */
		UniquePtr< Material > m_material;
	};
}