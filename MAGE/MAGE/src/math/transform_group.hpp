#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "math\transform.hpp"
#include "collection\collection.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	struct TransformGroup final {

	public:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		TransformGroup() = default;
		TransformGroup(Transform *transform)
			: TransformGroup() {
			AddTransform(transform);
		}
		TransformGroup(const TransformGroup &transform_group) = default;
		TransformGroup(TransformGroup &&transform_group) = default;
		~TransformGroup() {
			m_transforms.clear();
			m_transform_groups.clear();
		}

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------

		TransformGroup &operator=(const TransformGroup &transform_group) = delete;
		TransformGroup &operator=(TransformGroup &&transform_group) = delete;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		void AddTransform(Transform *transform) {
			m_transforms.push_back(transform);
		}
		void AddTransform(const TransformGroup &transform) {
			m_transform_groups.push_back(transform);
		}

		template< typename ActionT >
		void ForEachTransform(ActionT action) const;

	private:

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		vector< Transform * > m_transforms;
		vector< TransformGroup > m_transform_groups;
	};
}

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "math\transform_group.tpp"

#pragma endregion