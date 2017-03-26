#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "memory\memory.hpp"
#include "rendering\rendering_factory.hpp"
#include "collection\collection.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions and Declarations
//-----------------------------------------------------------------------------
namespace mage {

	/**
	 A class of indexed sprite meshes.
	 */
	class SpriteMesh {

	public:

		/**
		 Constructs a sprite mesh.
		 */
		SpriteMesh();

		/**
		 Destructs this sprite mesh.
		 */
		virtual ~SpriteMesh() = default;

	private:

		/**
		 Constructs a sprite mesh from the given sprite mesh.

		 @param[in]		sprite_mesh
						A reference to the sprite mesh.
		 */
		SpriteMesh(const SpriteMesh &sprite_mesh) = delete;

		/**
		 Constructs a sprite mesh from the given sprite mesh.

		 @param[in]		sprite_mesh
						A reference to the sprite mesh.
		 */
		SpriteMesh(SpriteMesh &&sprite_mesh) = delete;

		/**
		 Copies the given sprite mesh to this sprite mesh.

		 @param[in]		sprite_mesh
						A reference to the sprite mesh to copy from.
		 @return		A reference to the copy of the given sprite mesh
						(i.e. this sprite mesh).
		*/
		SpriteMesh &operator=(const SpriteMesh &sprite_mesh) = delete;

		/**
		 Copies the given sprite mesh to this sprite mesh.

		 @param[in]		sprite_mesh
						A reference to the sprite mesh to copy from.
		 @return		A reference to the copy of the given sprite mesh
						(i.e. this sprite mesh).
		 */
		SpriteMesh &operator=(SpriteMesh &&sprite_mesh) = delete;
	};
}