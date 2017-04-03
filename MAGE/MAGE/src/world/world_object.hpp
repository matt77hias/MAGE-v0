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

		explicit WorldObject(const string &name) 
			: m_name(name),
			m_transform(new Transform()) {}
		WorldObject(const WorldObject &world_object)
			: m_name(world_object.m_name), 
			m_transform(new Transform(*world_object.m_transform)) {}
		WorldObject(WorldObject &&world_object) = default;
		virtual ~WorldObject() = default;

		WorldObject &operator=(const WorldObject &world_object) {
			m_name = world_object.m_name;
			m_transform.reset(new Transform(*world_object.m_transform));
			return (*this);
		}
		WorldObject &operator=(WorldObject &&world_object) = default;

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

		void UpdateTransform() {
			if (m_transform->IsDirty()) {
				m_transform->Update();
				UpdateChildTransforms(true);
			}
			else {
				UpdateChildTransforms(false);
			}
		}
		void UpdateTransform(const XMMATRIX &world_to_parent, const XMMATRIX &parent_to_world, bool dirty_ancestor) {
			if (dirty_ancestor || m_transform->IsDirty()) {
				m_transform->Update(world_to_parent, parent_to_world);
				UpdateChildTransforms(true);
			}
			else {
				UpdateChildTransforms(false);
			}
		}
		
	protected:
		
		virtual void UpdateChildTransforms(bool dirty_ancestor) {
			UNUSED(dirty_ancestor);
		}

	private:

		string m_name;
		UniquePtr< Transform > m_transform;
	};
}