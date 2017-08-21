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
			Phong,
			ModifiedPhong,
			BlinnPhong,
			ModifiedBlinnPhong,
			Ward,
			WardDuer,
			CookTorrance,
			TSNMLambertian,
			TSNMPhong,
			TSNMModifiedPhong,
			TSNMBlinnPhong,
			TSNMModifiedBlinnPhong,
			TSNMWard,
			TSNMWardDuer,
			TSNMCookTorrance
		};

		void InitMaterials();
		void InitModels() noexcept;
		void InitShaders() noexcept;
		void SetMaterial(const Material &material) noexcept;
		void SetShader() noexcept;
		void PrintText();

		virtual void Update(double time) override;

		CameraSettings * const m_settings;
		SpriteText * const m_text;
		
		vector< ModelNode * > m_models;
		vector< ShaderType > m_shaders;
		size_t m_model_index;
		size_t m_shader_index;
		
		Material m_mat_emissive;
		Material m_mat_basic;
		Material m_mat_tsnm;
	};
}