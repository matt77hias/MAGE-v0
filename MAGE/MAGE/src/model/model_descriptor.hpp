#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "model\model_loader.hpp"
#include "mesh\static_mesh.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	/**
	 A class of model descriptors describing a complete model.
	 */
	class ModelDescriptor : public FileResource {

	public:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		/**
		 Constructs a model descriptor.

		 @pre			@a device is not equal to @c nullptr.
		 @pre			@a device_context is not equal to @c nullptr.
		 @tparam		VertexT
						The vertex type.
		 @param[in]		device
						A pointer to the device.
		 @param[in]		device_context
						A pointer to the device context.
		 @param[in]		fname
						A reference to the filename.
		 @param[in]		desc
						A reference to the mesh descriptor.
		 @throws		FormattedException
						Failed to initialize the model descriptor.
		 */
		template < typename VertexT >
		explicit ModelDescriptor(ID3D11Device2 *device, ID3D11DeviceContext2 *device_context,
			const wstring &fname, const MeshDescriptor< VertexT > &desc = MeshDescriptor< VertexT >());
		
		/**
		 Constructs a model descriptor from the given model descriptor.

		 @param[in]		desc
						A reference to the model descriptor to copy.
		 */
		ModelDescriptor(const ModelDescriptor &desc) = delete;

		/**
		 Constructs a model descriptor by moving the given model descriptor.

		 @param[in]		desc
						A reference to the model descriptor to move.
		 */
		ModelDescriptor(ModelDescriptor &&desc) = default;

		/**
		 Destructs a model descriptor.
		 */
		virtual ~ModelDescriptor();

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------

		/**
		 Copies the given model descriptor to this model descriptor.

		 @param[in]		desc
						A reference to the model descriptor to copy.
		 */
		ModelDescriptor &operator=(const ModelDescriptor &desc) = delete;

		/**
		 Moves the given model descriptor to this model descriptor.

		 @param[in]		desc
						A reference to the model descriptor to move.
		 */
		ModelDescriptor &operator=(ModelDescriptor &&desc) = delete;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Returns the mesh of this model descriptor.

		 @return		A pointer to the mesh of this model descriptor.
		 */
		SharedPtr< const StaticMesh > GetMesh() const {
			return m_mesh;
		}

		/**
		 Returns the material corresponding to the given name.

		 @param[in]		name
						A reference to the name of the material.
		 @return		@c nullptr if this model descriptor contains 
						no material matching the given name @a name.
		 @return		A pointer to the material of this model 
						descriptor matching the given name @a name.
		 */
		const Material *GetMaterial(const string &name) const;

		/**
		 Traverses all materials of this model descriptor.

		 @tparam		ActionT
						An action to perform on all materials
						of this model descriptor. The action 
						must accept @c const @c Material& values.
		*/
		template< typename ActionT >
		void ForEachMaterial(ActionT action) const;
		
		/**
		 Returns the model part corresponding to the given name.

		 @param[in]		name
						A reference to the name of the model part.
		 @return		@c nullptr if this model descriptor contains
						no model part matching the given name @a name.
		 @return		A pointer to the model part of this model 
						descriptor matching the given name @a name.
		 */
		const ModelPart *GetModelPart(const string &name) const;
		
		/**
		 Traverses all model parts of this model descriptor.

		 @tparam		ActionT
						An action to perform on all model parts
						of this model descriptor. The action
						must accept @c const @c ModelPart& values.
		 */
		template< typename ActionT >
		void ForEachModelPart(ActionT action) const;

	private:

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		/**
		 A pointer to the mesh of the model of this model descriptor.
		 */
		SharedPtr< StaticMesh > m_mesh;

		/**
		 A vector containing all the materials of the model of this model descriptor.
		 */
		vector< Material > m_materials;

		/**
		 A vector containing all the model parts of the model of this model descriptor.
		 */
		vector< ModelPart > m_model_parts;
	};

	/**
	 Creates a model descriptor.

	 @pre			The current engine must be loaded.
	 @tparam		VertexT
					The vertex type.
	 @param[in]		fname
					A reference to the filename.
	 @param[in]		desc
					A reference to the mesh descriptor.
	 @throws		FormattedException
					Failed to initialize the model descriptor.
	 */
	template < typename VertexT >
	SharedPtr< ModelDescriptor > CreateModelDescriptor(const wstring &fname, const MeshDescriptor< VertexT > &desc);
}

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "model\model_descriptor.tpp"

#pragma endregion