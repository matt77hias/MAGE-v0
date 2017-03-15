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

		WorldObject(const string &name) 
			: m_name(name),
			m_transform(new Transform()) {}
		WorldObject(const WorldObject &world_object)
			: m_name(world_object.m_name), 
			m_transform(new Transform(*world_object.m_transform)) {}
		virtual ~WorldObject() = default;

		WorldObject &operator=(const WorldObject &world_object) {
			m_name = world_object.m_name;
			m_transform = SharedPtr< Transform >(new Transform(*world_object.m_transform));
			return *this;
		}

		WorldObject *Clone() const {
			return new WorldObject(*this);
		}

		const string &GetName() const {
			return m_name;
		}
		void SetName(const string &name) {
			m_name = name;
		}
		Transform &GetTransform() const {
			return *m_transform;
		}

	protected:

		void AddChildTransform(const WorldObject &world_object) const {
			m_transform->AddChild(world_object.m_transform);
		}

	private:

		string m_name;
		SharedPtr< Transform > m_transform;
	};
}