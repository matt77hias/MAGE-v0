//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "core\engine.hpp"
#include "text\normal_sprite_text.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Game Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	class BRDFScript final : public BehaviorScript {

	public:

		BRDFScript(SpriteText *text, const vector< ModelNode * > &models);

		BRDFScript(const BRDFScript &script) = delete;

		BRDFScript(BRDFScript &&script);

		virtual ~BRDFScript();

		BRDFScript &operator=(const BRDFScript &script) = delete;

		BRDFScript &operator=(BRDFScript &&script) = delete;

	private:

		void SetShaders() const;

		virtual void Update(double time) override;

		SpriteText * const m_text;
		vector< ModelNode * > m_models;
		vector< CombinedShader > m_shaders;
		vector< wstring > m_shader_names;
		size_t m_model_index;
		size_t m_shader_index;
	};
}