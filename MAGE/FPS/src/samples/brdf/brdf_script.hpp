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

		BRDFScript(CameraSettings *settings,
			SpriteText *text, const vector< ModelNode * > &models);

		BRDFScript(const BRDFScript &script) = delete;

		BRDFScript(BRDFScript &&script);

		virtual ~BRDFScript();

		BRDFScript &operator=(const BRDFScript &script) = delete;

		BRDFScript &operator=(BRDFScript &&script) = delete;

	private:

		struct Mode final {

		public:

			explicit Mode(const wstring &name, 
				const Material &material, BRDFType brdf)
				: m_name(name), m_material(material), m_brdf(brdf) {}
			explicit Mode(wstring &&name, 
				const Material &material, BRDFType brdf)
				: m_name(std::move(name)), m_material(material), m_brdf(brdf) {}
			Mode(const Mode &mode) = default;
			Mode(Mode &&mode) = default;
			~Mode() = default;

			Mode &operator=(const Mode &mode) = default;
			Mode &operator=(Mode &&mode) = default;

			wstring m_name;
			Material m_material;
			BRDFType m_brdf;
		};

		void InitModels() noexcept;
		void InitModes();
		void SetMode() noexcept;

		virtual void Update([[maybe_unused]] F64 time) override;

		CameraSettings * const m_settings;
		SpriteText * const m_text;
		
		vector< ModelNode * > m_models;
		size_t m_model_index;
		vector< Mode > m_modes;
		size_t m_mode_index;
	};
}