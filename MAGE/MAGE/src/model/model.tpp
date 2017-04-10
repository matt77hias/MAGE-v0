#pragma once

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	template< typename ActionT >
	inline void Model::ForEachSubModel(ActionT action) const {
		for (vector< SubModel * >::const_iterator it = m_submodels.cbegin(); it != m_submodels.cend(); ++it) {
			action(**it);
		}
	}
}