#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "string\string.hpp"
#include "math\transform.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	class WorldObject {

	public:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		explicit WorldObject(const string &name);
		WorldObject(const WorldObject &world_object);
		WorldObject(WorldObject &&world_object) = default;
		virtual ~WorldObject() = default;

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------	

		WorldObject &operator=(const WorldObject &world_object) = delete;
		WorldObject &operator=(WorldObject &&world_object) = delete;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		SharedPtr< WorldObject > Clone() const {
			return CloneImplementation();
		}

		const string &GetName() const {
			return m_name;
		}
		void SetName(const string &name) {
			m_name = name;
		}
		Transform *GetTransform() {
			return m_transform.get();
		}
		const Transform *GetTransform() const {
			return m_transform.get();
		}

		void UpdateTransform();

	protected:

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		void UpdateTransform(const XMMATRIX &world_to_parent, const XMMATRIX &parent_to_world, bool dirty_ancestor);

	private:

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		virtual void UpdateChildTransforms(bool dirty_ancestor);

		virtual SharedPtr< WorldObject > CloneImplementation() const {
			return SharedPtr< WorldObject >(new WorldObject(*this));
		}
		
		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		string m_name;
		UniquePtr< Transform > m_transform;
	};
}