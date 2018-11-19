#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "renderer\pipeline.hpp"
#include "geometry\geometry.hpp"
#include "spectrum\spectrum.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage::rendering {

	/**
	 A struct of vertices containing position coordinates.
	 */
	struct VertexPosition {

	public:

		//---------------------------------------------------------------------
		// Class Member Methods
		//---------------------------------------------------------------------

		/**
		 Checks whether vertices have a position.

		 @return		@c true if vertices have a position. @c false otherwise.
		 */
		[[nodiscard]]
		static constexpr bool HasPosition() noexcept {
			return true;
		}

		/**
		 Checks whether vertices have a normal.

		 @return		@c true if vertices have a normal. @c false otherwise.
		 */
		[[nodiscard]]
		static constexpr bool HasNormal() noexcept {
			return false;
		}

		/**
		 Checks whether vertices have a texture.

		 @return		@c true if vertices have a texture. @c false otherwise.
		 */
		[[nodiscard]]
		static constexpr bool HasTexture() noexcept {
			return false;
		}

		/**
		 Checks whether vertices have a color.

		 @return		@c true if vertices have a color. @c false otherwise.
		 */
		[[nodiscard]]
		static constexpr bool HasColor() noexcept {
			return false;
		}

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		/**
		 The position of this vertex.
		 */
		Point3 m_p;

		//---------------------------------------------------------------------
		// Class Member Variables
		//---------------------------------------------------------------------

		/**
		 The input element descriptors of a vertex.
		 */
		static const D3D11_INPUT_ELEMENT_DESC s_input_element_descs[1u];
	};

	static_assert(12u == sizeof(VertexPosition),
				  "Vertex struct/layout mismatch");

	/**
	 A struct of vertices containing position and normal coordinates.
	 */
	struct VertexPositionNormal {

	public:

		//---------------------------------------------------------------------
		// Class Member Methods
		//---------------------------------------------------------------------

		/**
		 Checks whether vertices have a position.

		 @return		@c true if vertices have a position. @c false otherwise.
		 */
		[[nodiscard]]
		static constexpr bool HasPosition() noexcept {
			return true;
		}

		/**
		 Checks whether vertices have a normal.

		 @return		@c true if vertices have a normal. @c false otherwise.
		 */
		[[nodiscard]]
		static constexpr bool HasNormal() noexcept {
			return true;
		}

		/**
		 Checks whether vertices have a texture.

		 @return		@c true if vertices have a texture. @c false otherwise.
		 */
		[[nodiscard]]
		static constexpr bool HasTexture() noexcept {
			return false;
		}

		/**
		 Checks whether vertices have a color.

		 @return		@c true if vertices have a color. @c false otherwise.
		 */
		[[nodiscard]]
		static constexpr bool HasColor() noexcept {
			return false;
		}

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		/**
		 The position of this vertex.
		 */
		Point3 m_p;

		/**
		 The normal of this vertex.
		 */
		Normal3 m_n;

		//---------------------------------------------------------------------
		// Class Member Variables
		//---------------------------------------------------------------------

		/**
		 The input element descriptors of a vertex.
		 */
		static const D3D11_INPUT_ELEMENT_DESC s_input_element_descs[2u];
	};

	static_assert(24u == sizeof(VertexPositionNormal),
				  "Vertex struct/layout mismatch");

	/**
	 A struct of vertices containing position coordinates and a color.
	 */
	struct VertexPositionColor {

	public:

		//---------------------------------------------------------------------
		// Class Member Methods
		//---------------------------------------------------------------------

		/**
		 Checks whether vertices have a position.

		 @return		@c true if vertices have a position. @c false otherwise.
		 */
		[[nodiscard]]
		static constexpr bool HasPosition() noexcept {
			return true;
		}

		/**
		 Checks whether vertices have a normal.

		 @return		@c true if vertices have a normal. @c false otherwise.
		 */
		[[nodiscard]]
		static constexpr bool HasNormal() noexcept {
			return false;
		}

		/**
		 Checks whether vertices have a texture.

		 @return		@c true if vertices have a texture. @c false otherwise.
		 */
		[[nodiscard]]
		static constexpr bool HasTexture() noexcept {
			return false;
		}

		/**
		 Checks whether vertices have a color.

		 @return		@c true if vertices have a color. @c false otherwise.
		 */
		[[nodiscard]]
		static constexpr bool HasColor() noexcept {
			return true;
		}

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		/**
		 The position of this vertex.
		 */
		Point3 m_p;

		/**
		 The (linear) color of this vertex.
		 */
		RGBA m_c;

		//---------------------------------------------------------------------
		// Class Member Variables
		//---------------------------------------------------------------------

		/**
		 The input element descriptors of a vertex.
		 */
		static const D3D11_INPUT_ELEMENT_DESC s_input_element_descs[2u];
	};

	static_assert(28u == sizeof(VertexPositionColor),
				  "Vertex struct/layout mismatch");

	/**
	 A struct of vertices containing position and texture coordinates.
	 */
	struct VertexPositionTexture {

	public:

		//---------------------------------------------------------------------
		// Class Member Methods
		//---------------------------------------------------------------------

		/**
		 Checks whether vertices have a position.

		 @return		@c true if vertices have a position. @c false otherwise.
		 */
		[[nodiscard]]
		static constexpr bool HasPosition() noexcept {
			return true;
		}

		/**
		 Checks whether vertices have a normal.

		 @return		@c true if vertices have a normal. @c false otherwise.
		 */
		[[nodiscard]]
		static constexpr bool HasNormal() noexcept {
			return false;
		}

		/**
		 Checks whether vertices have a texture.

		 @return		@c true if vertices have a texture. @c false otherwise.
		 */
		[[nodiscard]]
		static constexpr bool HasTexture() noexcept {
			return true;
		}

		/**
		 Checks whether vertices have a color.

		 @return		@c true if vertices have a color. @c false otherwise.
		 */
		[[nodiscard]]
		static constexpr bool HasColor() noexcept {
			return false;
		}

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		/**
		 The position of this vertex.
		 */
		Point3 m_p;

		/**
		 The texture coordinates of this vertex.
		 */
		UV m_tex;

		//---------------------------------------------------------------------
		// Class Member Variables
		//---------------------------------------------------------------------

		/**
		 The input element descriptors of a vertex.
		 */
		static const D3D11_INPUT_ELEMENT_DESC s_input_element_descs[2u];
	};

	static_assert(20u == sizeof(VertexPositionTexture),
				  "Vertex struct/layout mismatch");

	/**
	 A struct of vertices containing position and normal coordinates and a
	 color.
	 */
	struct VertexPositionNormalColor {

	public:

		//---------------------------------------------------------------------
		// Class Member Methods
		//---------------------------------------------------------------------

		/**
		 Checks whether vertices have a position.

		 @return		@c true if vertices have a position. @c false otherwise.
		 */
		[[nodiscard]]
		static constexpr bool HasPosition() noexcept {
			return true;
		}

		/**
		 Checks whether vertices have a normal.

		 @return		@c true if vertices have a normal. @c false otherwise.
		 */
		[[nodiscard]]
		static constexpr bool HasNormal() noexcept {
			return true;
		}

		/**
		 Checks whether vertices have a texture.

		 @return		@c true if vertices have a texture. @c false otherwise.
		 */
		[[nodiscard]]
		static constexpr bool HasTexture() noexcept {
			return false;
		}

		/**
		 Checks whether vertices have a color.

		 @return		@c true if vertices have a color. @c false otherwise.
		 */
		[[nodiscard]]
		static constexpr bool HasColor() noexcept {
			return true;
		}

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		/**
		 The position of this vertex.
		 */
		Point3 m_p;

		/**
		 The normal of this vertex.
		 */
		Normal3 m_n;

		/**
		 The (linear) color of this vertex.
		 */
		RGBA m_c;

		//---------------------------------------------------------------------
		// Class Member Variables
		//---------------------------------------------------------------------

		/**
		 The input element descriptors of a vertex.
		 */
		static const D3D11_INPUT_ELEMENT_DESC s_input_element_descs[3u];
	};

	static_assert(40u == sizeof(VertexPositionNormalColor),
				  "Vertex struct/layout mismatch");

	/**
	 A struct of vertices containing position, normal and texture coordinates.
	 */
	struct VertexPositionNormalTexture {

	public:

		//---------------------------------------------------------------------
		// Class Member Methods
		//---------------------------------------------------------------------

		/**
		 Checks whether vertices have a position.

		 @return		@c true if vertices have a position. @c false otherwise.
		 */
		[[nodiscard]]
		static constexpr bool HasPosition() noexcept {
			return true;
		}

		/**
		 Checks whether vertices have a normal.

		 @return		@c true if vertices have a normal. @c false otherwise.
		 */
		[[nodiscard]]
		static constexpr bool HasNormal() noexcept {
			return true;
		}

		/**
		 Checks whether vertices have a texture.

		 @return		@c true if vertices have a texture. @c false otherwise.
		 */
		[[nodiscard]]
		static constexpr bool HasTexture() noexcept {
			return true;
		}

		/**
		 Checks whether vertices have a color.

		 @return		@c true if vertices have a color. @c false otherwise.
		 */
		[[nodiscard]]
		static constexpr bool HasColor() noexcept {
			return false;
		}

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		/**
		 The position of this vertex.
		 */
		Point3 m_p;

		/**
		 The normal of this vertex.
		 */
		Normal3 m_n;

		/**
		 The texture coordinates of this vertex.
		 */
		UV m_tex;

		//---------------------------------------------------------------------
		// Class Member Variables
		//---------------------------------------------------------------------

		/**
		 The input element descriptors of a vertex.
		 */
		static const D3D11_INPUT_ELEMENT_DESC s_input_element_descs[3u];
	};

	static_assert(32u == sizeof(VertexPositionNormalTexture),
				  "Vertex struct/layout mismatch");

	/**
	 A struct of vertices containing position and texture coordinates and a
	 color.
	 */
	struct VertexPositionColorTexture {

	public:

		//---------------------------------------------------------------------
		// Class Member Methods
		//---------------------------------------------------------------------

		/**
		 Checks whether vertices have a position.

		 @return		@c true if vertices have a position. @c false otherwise.
		 */
		[[nodiscard]]
		static constexpr bool HasPosition() noexcept {
			return true;
		}

		/**
		 Checks whether vertices have a normal.

		 @return		@c true if vertices have a normal. @c false otherwise.
		 */
		[[nodiscard]]
		static constexpr bool HasNormal() noexcept {
			return false;
		}

		/**
		 Checks whether vertices have a texture.

		 @return		@c true if vertices have a texture. @c false otherwise.
		 */
		[[nodiscard]]
		static constexpr bool HasTexture() noexcept {
			return true;
		}

		/**
		 Checks whether vertices have a color.

		 @return		@c true if vertices have a color. @c false otherwise.
		 */
		[[nodiscard]]
		static constexpr bool HasColor() noexcept {
			return true;
		}

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		/**
		 The position of this vertex.
		 */
		Point3 m_p;

		/**
		 The (linear) color of this vertex.
		 */
		RGBA m_c;

		/**
		 The texture coordinates of this vertex.
		 */
		UV m_tex;

		//---------------------------------------------------------------------
		// Class Member Variables
		//---------------------------------------------------------------------

		/**
		 The input element descriptors of a vertex.
		 */
		static const D3D11_INPUT_ELEMENT_DESC s_input_element_descs[3u];
	};

	static_assert(36u == sizeof(VertexPositionColorTexture),
				  "Vertex struct/layout mismatch");

	/**
	 A struct of vertices containing position, normal and texture coordinates
	 and a color.
	 */
	struct VertexPositionNormalColorTexture {

	public:

		//---------------------------------------------------------------------
		// Class Member Methods
		//---------------------------------------------------------------------

		/**
		 Checks whether vertices have a position.

		 @return		@c true if vertices have a position. @c false otherwise.
		 */
		[[nodiscard]]
		static constexpr bool HasPosition() noexcept {
			return true;
		}

		/**
		 Checks whether vertices have a normal.

		 @return		@c true if vertices have a normal. @c false otherwise.
		 */
		[[nodiscard]]
		static constexpr bool HasNormal() noexcept {
			return true;
		}

		/**
		 Checks whether vertices have a texture.

		 @return		@c true if vertices have a texture. @c false otherwise.
		 */
		[[nodiscard]]
		static constexpr bool HasTexture() noexcept {
			return true;
		}

		/**
		 Checks whether vertices have a color.

		 @return		@c true if vertices have a color. @c false otherwise.
		 */
		[[nodiscard]]
		static constexpr bool HasColor() noexcept {
			return true;
		}

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		/**
		 The position of this vertex.
		 */
		Point3 m_p;

		/**
		 The normal of this vertex.
		 */
		Normal3 m_n;

		/**
		 The (linear) color of this vertex.
		 */
		RGBA m_c;

		/**
		 The texture coordinates of this vertex.
		 */
		UV m_tex;

		//---------------------------------------------------------------------
		// Class Member Variables
		//---------------------------------------------------------------------

		/**
		 The input element descriptors of a vertex.
		 */
		static const D3D11_INPUT_ELEMENT_DESC s_input_element_descs[4u];
	};

	static_assert(48u == sizeof(VertexPositionNormalColorTexture),
				  "Vertex struct/layout mismatch");
}