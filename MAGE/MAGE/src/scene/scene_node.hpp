#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "string\string.hpp"
#include "math\transform_node.hpp"

// SceneObjects: Cameras
#include "camera\orthographic_camera.hpp"
#include "camera\perspective_camera.hpp"
// SceneObjects: Lights
#include "light\ambient_light.hpp"
#include "light\directional_light.hpp"
#include "light\omni_light.hpp"
#include "light\spot_light.hpp"
// SceneObjects: Models
#include "model\model.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {













	template< typename SceneObjectT >
	class SceneNode : public Node {

	public:

		explicit SceneNode(const string &name, SharedPtr< SceneObjectT > scene_object) 
			: Node(), m_name(name), 
			m_scene_object(scene_object) {}
		SceneNode(const SceneNode< SceneObjectT > &scene_node)
			: Node(scene_node), m_name(scene_node.m_name), 
			m_scene_object(scene_node.m_scene_object->Clone()) {}
		SceneNode(SceneNode< SceneObjectT > &&scene_node) = default;
		virtual ~SceneNode() = default;

		SceneNode &operator=(const SceneNode< SceneObjectT > &scene_node) = delete;
		SceneNode &operator=(SceneNode< SceneObjectT > &&scene_node) = delete;

		UniquePtr< SceneNode< SceneObjectT > > Clone() const {
			return static_pointer_cast< SceneNode< SceneObjectT > >(CloneImplementation());
		}

		const string &GetName() const {
			return m_name;
		}
		void SetName(const string &name) {
			m_name = name;
		}

		SceneObjectT *GetObject() {
			return m_scene_object.get();
		}
		const SceneObjectT *GetObject() const {
			return m_scene_object.get();
		}
		SharedPtr< SceneObjectT > *GetSharedObject() {
			return m_scene_object;
		}

	private:

		virtual UniquePtr< Node > CloneImplementation() const override {
			return UniquePtr< SceneNode< SceneObjectT > >(new SceneNode< SceneObjectT >(*this));
		}

		string m_name;
		SharedPtr< SceneObjectT > m_scene_object;
	};

	typedef SceneNode< Camera > CameraNode;
	typedef SceneNode< OrthographicCamera > OrthographicCameraNode;
	typedef SceneNode< PerspectiveCamera > PerspectiveCameraNode;

	typedef SceneNode< Light > LightNode;
	typedef SceneNode< AmbientLight > AmbientLightNode;
	typedef SceneNode< DirectionalLight > DirectionalLightNode;
	typedef SceneNode< OmniLight > OmniLightNode;
	typedef SceneNode< SpotLight > SpotLightNode;

	typedef SceneNode< Model > ModelNode;
}