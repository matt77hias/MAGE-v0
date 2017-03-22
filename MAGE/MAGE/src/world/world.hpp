#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "rendering\rendering.hpp"
#include "world\transform_buffer.hpp"
#include "light\point_light.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	// Forward declaration
	class Model;

	class World {

	public:

		World() = default;
		virtual ~World() {
			RemoveAllModels();
			RemoveAllLights();
		}

		void Render(ID3D11DeviceContext2 &device_context, const TransformBuffer &transform_buffer);

		//-------------------------------------------------------------------------
		// Models
		//-------------------------------------------------------------------------

		set< SharedPtr< Model > >::iterator ModelsBegin() {
			return m_models.begin();
		}
		set< SharedPtr< Model > >::iterator ModelsEnd() {
			return m_models.end();
		}
		set< SharedPtr< Model > >::const_iterator ModelsBegin() const {
			return m_models.cbegin();
		}
		set< SharedPtr< Model > >::const_iterator ModelsEnd() const {
			return m_models.cend();
		}
		size_t GetNumberOfModels() const {
			return m_models.size();
		}
		SharedPtr< Model > GetModel(const string &name) const;
		bool HasModel(const string &name) const {
			return GetModel(name) != nullptr;
		}
		bool HasModel(const SharedPtr< Model > model) const;
		void AddModel(SharedPtr< Model > model) {
			if (!model) {
				return;
			}
			m_models.insert(model);
		}
		void RemoveModel(const string &name);
		void RemoveModel(SharedPtr< Model > model);
		void RemoveAllModels() {
			m_models.clear();
		}

		//-------------------------------------------------------------------------
		// Lights
		//-------------------------------------------------------------------------

		set< SharedPtr< PointLight > >::iterator LightsBegin() {
			return m_lights.begin();
		}
		set< SharedPtr< PointLight > >::iterator LightsEnd() {
			return m_lights.end();
		}
		set< SharedPtr< PointLight > >::const_iterator LightsBegin() const {
			return m_lights.cbegin();
		}
		set< SharedPtr< PointLight > >::const_iterator LightsEnd() const {
			return m_lights.cend();
		}
		size_t GetNumberOfLights() const {
			return m_lights.size();
		}
		SharedPtr< PointLight > GetLight(const string &name) const;
		bool HasLight(const string &name) const {
			return GetLight(name) != nullptr;
		}
		bool HasLight(const SharedPtr< PointLight > light) const;
		void AddLight(SharedPtr< PointLight > light) {
			if (!light) {
				return;
			}
			m_lights.insert(light);
		}
		void RemoveLight(const string &name);
		void RemoveLight(SharedPtr< PointLight > light);
		void RemoveAllLights() {
			m_lights.clear();
		}

	private:

		World(const World &world) = delete;
		World(World &&world) = delete;
		World &operator=(const World &world) = delete;
		World &operator=(World &&world) = delete;

		set< SharedPtr< Model >, std::less<> > m_models;
		set< SharedPtr< PointLight >, std::less<> > m_lights;
	};
}