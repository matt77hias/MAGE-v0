#pragma once

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	template< typename ActionT >
	void Model::ForEachSubModel(ActionT action) {
		for (set< SubModel * >::iterator it = m_submodels.begin(); it != m_submodels.end(); ++it) {
			action(*it);
		}
	}
	template< typename ActionT >
	void Model::ForEachSubModel(ActionT action) const {
		for (set< SubModel * >::const_iterator it = m_submodels.cbegin(); it != m_submodels.cend(); ++it) {
			action(*it);
		}
	}
}