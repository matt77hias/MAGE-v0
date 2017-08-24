#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "mesh\static_mesh.hpp"
#include "material\material.hpp"
#include "model\shadow_behavior.hpp"

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
		 */
		explicit Model(SharedPtr< const StaticMesh > mesh);

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
						A reference to the AABB.
		 @param[in]		bs
						A reference to the BS.
		 */
		explicit Model(SharedPtr< const Mesh > mesh, 
			size_t start_index, size_t nb_indices, 
			const AABB &aabb, const BS &bs);

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
		 @return		A reference to the copy of the given model
						(i.e. this model).
		 */
		Model &operator=(const Model &model) = delete;

		/**
		 Moves the given model to this model.

		 @param[in]		model
						A reference to the model to move.
		 @return		A reference to the moved model
						(i.e. this model).
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

		 @return		The number of indices of this model in the mesh of this model.
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
		void BindMesh(ID3D11DeviceContext2 *device_context) const noexcept {
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
		void BindMesh(ID3D11DeviceContext2 *device_context, 
			D3D11_PRIMITIVE_TOPOLOGY topology) const noexcept {

			m_mesh->BindMesh(device_context, topology);
		}

		/**
		 Draws this model.

		 @pre			@a device_context is not equal to @c nullptr.
		 @param[in]		device_context
						A pointer to the device context.
		 */
		void Draw(ID3D11DeviceContext2 *device_context) const noexcept {
			m_mesh->Draw(device_context, m_start_index, m_nb_indices);
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

		/**
		 Sets the material of this model to the given material.

		 @param[in]		material
						A reference to the material.
		 */
		void SetMaterial(const Material &material) noexcept {
			m_material = MakeUnique< Material >(material);
		}

		/**
		 Sets the material of this model to the given material.

		 @param[in]		material
						A reference to the material.
		 */
		void SetMaterial(Material &&material) noexcept {
			m_material = MakeUnique< Material >(std::move(material));
		}

		/**
		 Returns the shadow behavior of this model.

		 @return		A reference to the shadow behavior of this model.
		 */
		ShadowBehavior &GetShadowBehavior() noexcept {
			return m_shadow_behavior;
		}

		/**
		 Returns the shadow behavior of this model.

		 @return		A reference to the shadow behavior of this model.
		 */
		const ShadowBehavior &GetShadowBehavior() const noexcept {
			return m_shadow_behavior;
		}

		/**
		 Sets the shadow behavior of this model to the given shadow behavior.

		 @param[in]		shadow_behavior
						A reference to the shadow behavior.
		 */
		void SetShadowBehavior(const ShadowBehavior &shadow_behavior) noexcept {
			m_shadow_behavior = shadow_behavior;
		}

		/**
		 Sets the shadow behavior of this model to the given shadow behavior.

		 @param[in]		shadow_behavior
						A reference to the shadow behavior.
		 */
		void SetShadowBehavior(ShadowBehavior &&shadow_behavior) noexcept {
			m_shadow_behavior = std::move(shadow_behavior);
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
		 A pointer to the material of this model.
		 */
		UniquePtr< Material > m_material;

		/**
		 The shadow behavior of this model.
		 */
		ShadowBehavior m_shadow_behavior;
	};
}