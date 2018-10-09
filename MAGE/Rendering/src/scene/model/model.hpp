#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "scene\component.hpp"
#include "resource\mesh\mesh.hpp"
#include "resource\model\material.hpp"
#include "geometry\bounding_volume.hpp"
#include "transform\transform.hpp"
#include "renderer\buffer\constant_buffer.hpp"
#include "renderer\buffer\scene_buffer.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage::rendering {

	#pragma warning( push )
	#pragma warning( disable : 4324 ) // Added padding.

	/**
	 A class of models.
	 */
	class alignas(16) Model : public Component {

	public:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		/**
		 Constructs a model.

		 @param[in]		device
						A reference to the device.
		 */
		explicit Model(ID3D11Device& device);

		/**
		 Constructs a model from the given model.

		 @param[in]		model
						A reference to the model to copy.
		 */
		Model(const Model& model) = delete;

		/**
		 Constructs a model by moving the given model.

		 @param[in]		model
						A reference to the model to move.
		 */
		Model(Model&& model) noexcept;

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
		Model& operator=(const Model& model) = delete;

		/**
		 Moves the given model to this model.

		 @param[in]		model
						A reference to the model to move.
		 @return		A reference to the moved model (i.e. this model).
		 */
		Model& operator=(Model&& model) noexcept;

		//---------------------------------------------------------------------
		// Member Methods: Geometry
		//---------------------------------------------------------------------

		/**
		 Sets the mesh of this model to the given mesh.

		 @param[in]		mesh
						A pointer to the mesh.
		 @param[in]		start_index
						The start index in the mesh.
		 @param[in]		nb_indices
						The number of indices in the mesh.
		 @param[in]		aabb
						The AABB.
		 @param[in]		bs
						The bounding sphere.
		 */
		void SetMesh(SharedPtr< const Mesh > mesh,
					 std::size_t start_index,
					 std::size_t nb_indices,
					 AABB aabb,
					 BoundingSphere bs);

		/**
		 Returns the AABB of this model.

		 @return		A reference to the AABB of this model.
		 */
		[[nodiscard]]
		const AABB& GetAABB() const noexcept {
			return m_aabb;
		}

		/**
		 Returns the bounding sphere of this model.

		 @return		A reference to the bounding sphere of this model.
		 */
		[[nodiscard]]
		const BoundingSphere& GetBoundingSphere() const noexcept {
			return m_sphere;
		}

		/**
		 Returns the start index of this model in the mesh of this model.

		 @return		The start index of this model in the mesh of this model.
		 */
		[[nodiscard]]
		std::size_t GetStartIndex() const noexcept {
			return m_start_index;
		}

		/**
		 Returns the number of indices of this model in the mesh of this model.

		 @return		The number of indices of this model in the mesh of this
						model.
		 */
		[[nodiscard]]
		std::size_t GetNumberOfIndices() const noexcept {
			return m_nb_indices;
		}

		/**
		 Binds the mesh of this model.

		 @param[in]		device_context
						A reference to the device context.
		 */
		void BindMesh(ID3D11DeviceContext& device_context) const noexcept {
			m_mesh->BindMesh(device_context);
		}

		/**
		 Binds the mesh of this model with given primitive topology.

		 @param[in]		device_context
						A reference to the device context.
		 @param[in]		topology
						The primitive topology.
		 */
		void BindMesh(ID3D11DeviceContext& device_context,
			          D3D11_PRIMITIVE_TOPOLOGY topology) const noexcept {

			m_mesh->BindMesh(device_context, topology);
		}

		/**
		 Draws this model.

		 @param[in]		device_context
						A reference to the device context.
		 */
		void Draw(ID3D11DeviceContext& device_context) const noexcept {
			m_mesh->Draw(device_context, m_start_index, m_nb_indices);
		}

		//---------------------------------------------------------------------
		// Member Methods: Appearance
		//---------------------------------------------------------------------

		/**
		 Returns the texture transform of this model.

		 @return		A reference to the texture transform of this model.
		 */
		[[nodiscard]]
		TextureTransform2D& GetTextureTransform() noexcept {
			return m_texture_transform;
		}

		/**
		 Returns the texture transform of this model.

		 @return		A reference to the texture transform of this model.
		 */
		[[nodiscard]]
		const TextureTransform2D& GetTextureTransform() const noexcept {
			return m_texture_transform;
		}

		/**
		 Returns the material of this model.

		 @return		A reference to the material of this model.
		 */
		[[nodiscard]]
		Material& GetMaterial() noexcept {
			return m_material;
		}

		/**
		 Returns the material of this model.

		 @return		A reference to the material of this model.
		 */
		[[nodiscard]]
		const Material& GetMaterial() const noexcept {
			return m_material;
		}

		//---------------------------------------------------------------------
		// Member Methods: Occlusion
		//---------------------------------------------------------------------

		/**
		 Checks whether this model occludes light.

		 @return		@c true if this model occludes light. @c false
						otherwise.
		 */
		[[nodiscard]]
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
		void ToggleLightOcclusion() noexcept {
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
		// Member Methods: Buffer
		//---------------------------------------------------------------------

		/**
		 Updates the buffer of this model.

		 @param[in]		device_context
						A reference to the device context.
		 */
		void UpdateBuffer(ID3D11DeviceContext& device_context) const;

		/**
		 Binds the buffer of this model to the given pipeline stage.

		 @tparam		PipelineStageT
						The pipeline stage type.
		 @param[in]		device_context
						A reference to the device context.
		 @param[in]		slot
						The index into the device's zero-based array to set
						the constant buffer to (ranges from 0 to
						@c D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT - 1).
		 */
		template< typename PipelineStageT >
		void BindBuffer(ID3D11DeviceContext& device_context,
						U32 slot) const noexcept {

			m_buffer.Bind< PipelineStageT >(device_context, slot);
		}

	private:

		//---------------------------------------------------------------------
		// Member Variables: Buffer
		//---------------------------------------------------------------------

		/**
		 The buffer of this model.
		 */
		mutable ConstantBuffer< ModelBuffer > m_buffer;

		//---------------------------------------------------------------------
		// Member Variables: Geometry
		//---------------------------------------------------------------------

		/**
		 The AABB of this model.
		 */
		AABB m_aabb;

		/**
		 The bounding sphere of this model.
		 */
		BoundingSphere m_sphere;

		/**
		 A pointer to the mesh of this model.
		 */
		SharedPtr< const Mesh > m_mesh;

		/**
		 The start index of this model in the mesh of this model.
		 */
		std::size_t m_start_index;

		/**
		 The number of indices of this model in the mesh of this model.
		 */
		std::size_t m_nb_indices;

		//---------------------------------------------------------------------
		// Member Variables: Appearance
		//---------------------------------------------------------------------

		/**
		 The texture transform of this model.
		 */
		TextureTransform2D m_texture_transform;

		/**
		 The material of this model.
		 */
		Material m_material;

		//---------------------------------------------------------------------
		// Member Variables: Occlusion
		//---------------------------------------------------------------------

		/**
		 A flag indicating whether this model occludes light.
		 */
		bool m_light_occlusion;
	};

	#pragma warning( pop )
}