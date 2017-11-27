#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "core\engine.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Game Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage::script {

	class BRDFScript final : public BehaviorScript {

	public:

		BRDFScript(CameraSettings *settings, vector< ModelNode * > models);

		BRDFScript(const BRDFScript &script) = delete;

		BRDFScript(BRDFScript &&script);

		virtual ~BRDFScript();

		BRDFScript &operator=(const BRDFScript &script) = delete;

		BRDFScript &operator=(BRDFScript &&script) = delete;

	private:

		virtual void Update([[maybe_unused]] F64 time) override;

		CameraSettings * const m_settings;
		
		vector< ModelNode * > m_models;
		vector< const char * > m_model_names;
		int m_model_index;
		bool m_wireframe;
		bool m_aabb;

		Material m_material;
		bool m_tsnm;
		SharedPtr< const Texture > m_tsnm_texture;
		int m_brdf_index;
	};
}