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
namespace mage {

	class BRDFScript final : public BehaviorScript {

	public:

		BRDFScript(CameraSettings *settings,
			SpriteText *text, const vector< ModelNode * > &models);

		BRDFScript(const BRDFScript &script) = delete;

		BRDFScript(BRDFScript &&script);

		virtual ~BRDFScript();

		BRDFScript &operator=(const BRDFScript &script) = delete;

		BRDFScript &operator=(BRDFScript &&script) = delete;

	private:

		enum struct ShaderType {
			Emissive = 0,
			Lambertian,
			CookTorrance,
			TSNMLambertian,
			TSNMCookTorrance
		};

		void InitModels() noexcept;
		void InitShaders();
		void SetMaterial() noexcept;
		void SetShader() noexcept;
		void PrintText();

		virtual void Update(F64 time) override;

		CameraSettings * const m_settings;
		SpriteText * const m_text;
		
		vector< ModelNode * > m_models;
		vector< pair< ShaderType, Material > > m_shaders;
		size_t m_model_index;
		size_t m_shader_index;
	};
}