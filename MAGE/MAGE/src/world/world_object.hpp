#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "string\string.hpp"
#include "math\transform.hpp"
#include "collection\collection.hpp"

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
		virtual ~WorldObject();

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------	

		WorldObject &operator=(const WorldObject &world_object) = delete;
		WorldObject &operator=(WorldObject &&world_object) = delete;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		virtual WorldObject *Clone() const {
			return new WorldObject(*this);
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

		size_t GetNumberOfChilds() const {
			return m_childs.size();
		}
		bool HasChild(const SharedPtr< WorldObject > child) const;
		void AddChild(SharedPtr< WorldObject > child);
		void RemoveChild(SharedPtr< WorldObject > child);
		void RemoveAllChilds();
		template< typename ActionT >
		void ForEachChild(ActionT action) const;

	protected:

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		void UpdateTransform(const XMMATRIX &world_to_parent, const XMMATRIX &parent_to_world, bool dirty_ancestor);
		virtual void UpdateChildTransforms(bool dirty_ancestor);

	private:
		
		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		string m_name;
		UniquePtr< Transform > m_transform;
		vector< SharedPtr< WorldObject > > m_childs;
	};
}

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "world\world_object.tpp"

#pragma endregion