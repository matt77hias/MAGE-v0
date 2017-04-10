#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "mesh\mesh.hpp"
#include "world\world_object.hpp"
#include "shader\shaded_material.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	// Forward declaration
	class SubModel;

	//-------------------------------------------------------------------------
	// Model
	//-------------------------------------------------------------------------
	
	/**
	 A class of models.
	 */
	class Model : public WorldObject {

	public:

		//---------------------------------------------------------------------
		// Destructors
		//---------------------------------------------------------------------

		virtual ~Model();

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------

		Model &operator=(const Model &model) = delete;
		Model &operator=(Model &&model) = delete;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		virtual Model *Clone() const = 0;

		virtual void Draw(const World &world, const TransformBuffer &transform_buffer) const;
		
		size_t GetNumberOfSubModels() const {
			return m_submodels.size();
		}
		SubModel *GetSubModel(const string &name) const;
		bool HasSubModel(const string &name) const {
			return GetSubModel(name) != nullptr;
		}
		void AddSubModel(SubModel *submodel);
		template< typename ActionT >
		void ForEachSubModel(ActionT action) const;

	protected:

		//---------------------------------------------------------------------
		// Constructors
		//---------------------------------------------------------------------

		explicit Model(const string &name);
		Model(const Model &model);
		Model(Model &&model) = default;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		virtual void UpdateChildTransforms(bool dirty_ancestor) override;
		
	private:

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		vector< SubModel * > m_submodels;
	};

	//-------------------------------------------------------------------------
	// SubModel
	//-------------------------------------------------------------------------

	/**
	 A class of submodels.
	 */
	class SubModel : public Model {

	public:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		explicit SubModel(const string &name, size_t start_index, size_t nb_indices, const ShadedMaterial &material);
		SubModel(const SubModel &submodel);
		SubModel(SubModel &&submodel) = default;
		virtual ~SubModel() = default;

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------

		SubModel &operator=(const SubModel &submodel) = delete;
		SubModel &operator=(SubModel &&submodel) = delete;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		virtual SubModel *Clone() const {
			return new SubModel(*this);
		}

		void Draw(const Mesh &mesh, const World &world, const TransformBuffer &transform_buffer) const;

		size_t GetStartIndex() const {
			return m_start_index;
		}
		size_t GetNumberOfIndices() const {
			return m_nb_indices;
		}
		Material &GetMaterial() const {
			m_material->GetMaterial();
		}

	private:

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		const size_t m_start_index;
		const size_t m_nb_indices;
		UniquePtr< ShadedMaterial > m_material;
	};
}

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "model\model.tpp"

#pragma endregion