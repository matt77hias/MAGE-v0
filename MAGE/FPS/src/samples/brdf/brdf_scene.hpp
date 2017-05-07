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

	class BRDFScene final : public Scene {

	public:

		BRDFScene();

		BRDFScene(const BRDFScene &scene) = delete;

		BRDFScene(BRDFScene &&scene);

		virtual ~BRDFScene();

		BRDFScene &operator=(const BRDFScene &scene) = delete;

		BRDFScene &operator=(BRDFScene &&scene) = delete;

	private:

		virtual void Load() override;
	};
}