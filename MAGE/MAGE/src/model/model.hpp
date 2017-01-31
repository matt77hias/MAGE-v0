//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "math\transform.hpp"
#include "mesh\mesh.hpp"
#include "material\material.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions and Declarations
//-----------------------------------------------------------------------------
namespace mage {

	class Model {

	public:



	private:

		Transform m_transform;
		list< pair< Mesh, Material > > m_childs;
	};



}
