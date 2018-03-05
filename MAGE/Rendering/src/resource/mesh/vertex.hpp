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
	struct VertexPosition final {

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
		// Constructors and Destructors
		//---------------------------------------------------------------------

		/**
		 Constructs a vertex.
		 */
		constexpr VertexPosition() noexcept = default;

		/**
		 Constructs a vertex.

		 @param[in]		p
						The position of the vertex.
		 */
		constexpr explicit VertexPosition(Point3 p) noexcept
			: m_p(std::move(p)) {}

		/**
		 Constructs a vertex from the given vertex.

		 @param[in]		vertex
						A reference to the vertex to copy.
		 */
		constexpr VertexPosition(const VertexPosition& vertex) noexcept = default;

		/**
		 Constructs a vertex by moving the given vertex.

		 @param[in]		vertex
						A reference to the vertex to move.
		 */
		constexpr VertexPosition(VertexPosition&& vertex) noexcept = default;

		/**
		 Destructs this vertex.
		 */
		~VertexPosition() = default;

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------

		/**
		 Copies the given vertex to this vertex.

		 @param[in]		vertex
						A reference to the vertex to copy.
		 @return		A reference to the copy of the given vertex  (i.e. this 
						vertex).
		 */
		constexpr VertexPosition& operator=(
			const VertexPosition& vertex) noexcept = default;

		/**
		 Moves the given vertex to this vertex.

		 @param[in]		vertex
						A reference to the vertex to move.
		 @return		A reference to the moved vertex (i.e. this vertex).
		 */
		constexpr VertexPosition& operator=(
			VertexPosition&& vertex) noexcept = default;

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
		static const D3D11_INPUT_ELEMENT_DESC s_input_element_descs[1];
	};

	/**
	 A struct of vertices containing position and normal coordinates.
	 */
	struct VertexPositionNormal final {

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
		// Constructors and Destructors
		//---------------------------------------------------------------------

		/**
		 Constructs a vertex.
		 */
		constexpr VertexPositionNormal() noexcept = default;

		/**
		 Constructs a vertex.

		 @param[in]		p
						The position of the vertex.
		 @param[in]		n
						The normal of the vertex.
		 */
		constexpr explicit VertexPositionNormal(Point3 p, 
			                                    Normal3 n) noexcept
			: m_p(std::move(p)), 
			m_n(std::move(n)) {}

		/**
		 Constructs a vertex from the given vertex.

		 @param[in]		vertex
						A reference to the vertex to copy.
		*/
		constexpr VertexPositionNormal(
			const VertexPositionNormal& vertex) noexcept = default;

		/**
		 Constructs a vertex by moving the given vertex.

		 @param[in]		vertex
						A reference to the vertex to move.
		 */
		constexpr VertexPositionNormal(
			VertexPositionNormal&& vertex) noexcept = default;

		/**
		 Destructs this vertex.
		 */
		~VertexPositionNormal() = default;

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------

		/**
		 Copies the given vertex to this vertex.

		 @param[in]		vertex
						A reference to the vertex to copy.
		 @return		A reference to the copy of the given vertex (i.e. this 
						vertex).
		 */
		constexpr VertexPositionNormal& operator=(
			const VertexPositionNormal& vertex) noexcept = default;

		/**
		 Moves the given vertex to this vertex.

		 @param[in]		vertex
						A reference to the vertex to move.
		 @return		A reference to the moved vertex (i.e. this vertex).
		 */
		constexpr VertexPositionNormal& operator=(
			VertexPositionNormal&& vertex) noexcept = default;

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
		static const D3D11_INPUT_ELEMENT_DESC s_input_element_descs[2];
	};

	/**
	 A struct of vertices containing position coordinates and a color.
	 */
	struct VertexPositionColor final {

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
		// Constructors and Destructors
		//---------------------------------------------------------------------

		/**
		 Constructs a vertex.
		 */
		constexpr VertexPositionColor() noexcept = default;

		/**
		 Constructs a vertex.

		 @param[in]		p
						The position of the vertex.
		 @param[in]		c
						The sRGB color of the vertex.
		 */
		constexpr explicit VertexPositionColor(Point3 p, 
			                                   SRGBA c) noexcept
			: m_p(std::move(p)), 
			m_c(std::move(c)) {}

		/**
		 Constructs a vertex from the given vertex.

		 @param[in]		vertex
						A reference to the vertex to copy.
		 */
		constexpr VertexPositionColor(
			const VertexPositionColor& vertex) noexcept = default;

		/**
		 Constructs a vertex by moving the given vertex.

		 @param[in]		vertex
						A reference to the vertex to move.
		 */
		constexpr VertexPositionColor(
			VertexPositionColor&& vertex) noexcept = default;

		/**
		 Destructs this vertex.
		 */
		~VertexPositionColor() = default;

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------

		/**
		 Copies the given vertex to this vertex.

		 @param[in]		vertex
						A reference to the vertex to copy.
		 @return		A reference to the copy of the given vertex (i.e. this 
						vertex).
		 */
		constexpr VertexPositionColor& operator=(
			const VertexPositionColor& vertex) noexcept = default;

		/**
		 Moves the given vertex to this vertex.

		 @param[in]		vertex
						A reference to the vertex to move.
		 @return		A reference to the moved vertex (i.e. this vertex).
		 */
		constexpr VertexPositionColor& operator=(
			VertexPositionColor&& vertex) noexcept = default;

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		/**
		 The position of this vertex.
		 */
		Point3 m_p;

		/**
		 The sRGB color of this vertex.
		 */
		SRGBA m_c;

		//---------------------------------------------------------------------
		// Class Member Variables
		//---------------------------------------------------------------------

		/**
		 The input element descriptors of a vertex.
		 */
		static const D3D11_INPUT_ELEMENT_DESC s_input_element_descs[2];
	};

	/**
	 A struct of vertices containing position and texture coordinates.
	 */
	struct VertexPositionTexture final {

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
		// Constructors and Destructors
		//---------------------------------------------------------------------

		/**
		 Constructs a vertex.
		 */
		constexpr VertexPositionTexture() noexcept = default;

		/**
		 Constructs a vertex.

		 @param[in]		p
						The position of the vertex.
		 @param[in]		tex
						The texture coordinates of the vertex.
		 */
		constexpr explicit VertexPositionTexture(Point3 p, 
			                                     UV tex) noexcept
			: m_p(std::move(p)), 
			m_tex(std::move(tex)) {}

		/**
		 Constructs a vertex from the given vertex.

		 @param[in]		vertex
						A reference to the vertex to copy.
		 */
		constexpr VertexPositionTexture(
			const VertexPositionTexture& vertex) noexcept = default;

		/**
		 Constructs a vertex by moving the given vertex.

		 @param[in]		vertex
						A reference to the vertex to move.
		 */
		constexpr VertexPositionTexture(
			VertexPositionTexture&& vertex) noexcept = default;

		/**
		 Destructs this vertex.
		 */
		~VertexPositionTexture() = default;

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------

		/**
		 Copies the given vertex to this vertex.

		 @param[in]		vertex
						A reference to the vertex to copy.
		 @return		A reference to the copy of the given vertex (i.e. this 
						vertex).
		 */
		constexpr VertexPositionTexture& operator=(
			const VertexPositionTexture& vertex) noexcept = default;

		/**
		 Moves the given vertex to this vertex.

		 @param[in]		vertex
						A reference to the vertex to move.
		 @return		A reference to the moved vertex (i.e. this vertex).
		 */
		constexpr VertexPositionTexture& operator=(
			VertexPositionTexture&& vertex) noexcept = default;

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
		static const D3D11_INPUT_ELEMENT_DESC s_input_element_descs[2];
	};

	/**
	 A struct of vertices containing position and normal coordinates and a 
	 color.
	 */
	struct VertexPositionNormalColor final {

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
		// Constructors and Destructors
		//---------------------------------------------------------------------

		/**
		 Constructs a vertex.
		 */
		constexpr VertexPositionNormalColor() noexcept = default;

		/**
		 Constructs a vertex.

		 @param[in]		p
						The position of the vertex.
		 @param[in]		n
						The normal of the vertex.
		 @param[in]		c
						The sRGB color of the vertex.
		 */
		constexpr explicit VertexPositionNormalColor(Point3 p, 
			                                         Normal3 n, 
			                                         SRGBA c) noexcept
			: m_p(std::move(p)), 
			m_n(std::move(n)), 
			m_c(std::move(c)) {}

		/**
		 Constructs a vertex from the given vertex.

		 @param[in]		vertex
						A reference to the vertex to copy.
		 */
		constexpr VertexPositionNormalColor(
			const VertexPositionNormalColor& vertex) noexcept = default;

		/**
		 Constructs a vertex by moving the given vertex.

		 @param[in]		vertex
						A reference to the vertex to move.
		 */
		constexpr VertexPositionNormalColor(
			VertexPositionNormalColor&& vertex) noexcept = default;

		/**
		 Destructs this vertex.
		 */
		~VertexPositionNormalColor() = default;

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------

		/**
		 Copies the given vertex to this vertex.

		 @param[in]		vertex
						A reference to the vertex to copy.
		 @return		A reference to the copy of the given vertex (i.e. this 
						vertex).
		 */
		constexpr VertexPositionNormalColor& operator=(
			const VertexPositionNormalColor& vertex) noexcept = default;

		/**
		 Moves the given vertex to this vertex.

		 @param[in]		vertex
						A reference to the vertex to move.
		 @return		A reference to the moved vertex (i.e. this vertex).
		 */
		constexpr VertexPositionNormalColor& operator=(
			VertexPositionNormalColor&& vertex) noexcept = default;

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
		 The sRGB color of this vertex.
		 */
		SRGBA m_c;

		//---------------------------------------------------------------------
		// Class Member Variables
		//---------------------------------------------------------------------

		/**
		 The input element descriptors of a vertex.
		 */
		static const D3D11_INPUT_ELEMENT_DESC s_input_element_descs[3];
	};

	/**
	 A struct of vertices containing position, normal and texture coordinates.
	 */
	struct VertexPositionNormalTexture final {

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
		// Constructors and Destructors
		//---------------------------------------------------------------------

		/**
		 Constructs a vertex.
		 */
		constexpr VertexPositionNormalTexture() noexcept = default;

		/**
		 Constructs a vertex.

		 @param[in]		p
						The position of the vertex.
		 @param[in]		n
						The normal of the vertex.
		 @param[in]		tex
						The texture coordinates of the vertex.
		 */
		constexpr explicit VertexPositionNormalTexture(Point3 p, 
			                                           Normal3 n, 
			                                           UV tex) noexcept
			: m_p(std::move(p)), 
			m_n(std::move(n)), 
			m_tex(std::move(tex)) {}

		/**
		 Constructs a vertex from the given vertex.

		 @param[in]		vertex
						A reference to the vertex to copy.
		 */
		constexpr VertexPositionNormalTexture(
			const VertexPositionNormalTexture& vertex) noexcept = default;

		/**
		 Constructs a vertex by moving the given vertex.

		 @param[in]		vertex
						A reference to the vertex to move.
		 */
		constexpr VertexPositionNormalTexture(
			VertexPositionNormalTexture&& vertex) noexcept = default;

		/**
		 Destructs this vertex.
		 */
		~VertexPositionNormalTexture() = default;

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------

		/**
		 Copies the given vertex to this vertex.

		 @param[in]		vertex
						A reference to the vertex to copy.
		 @return		A reference to the copy of the given vertex (i.e. this 
						vertex).
		 */
		constexpr VertexPositionNormalTexture& operator=(
			const VertexPositionNormalTexture& vertex) noexcept = default;

		/**
		 Moves the given vertex to this vertex.

		 @param[in]		vertex
						A reference to the vertex to move.
		 @return		A reference to the moved vertex (i.e. this vertex).
		 */
		constexpr VertexPositionNormalTexture& operator=(
			VertexPositionNormalTexture&& vertex) noexcept = default;

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
		static const D3D11_INPUT_ELEMENT_DESC s_input_element_descs[3];
	};

	/**
	 A struct of vertices containing position and texture coordinates and a 
	 color.
	 */
	struct VertexPositionColorTexture final {

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
		// Constructors and Destructors
		//---------------------------------------------------------------------

		/**
		 Constructs a vertex.
		 */
		constexpr VertexPositionColorTexture() noexcept = default;

		/**
		 Constructs a vertex.

		 @param[in]		p
						The position of the vertex.
		 @param[in]		c
						The sRGB color of the vertex.
		 @param[in]		tex
						The texture coordinates of the vertex.
		 */
		constexpr explicit VertexPositionColorTexture(Point3 p, 
			                                          SRGBA c, 
			                                          UV tex) noexcept
			: m_p(std::move(p)), 
			m_c(std::move(c)), 
			m_tex(std::move(tex)) {}

		/**
		 Constructs a vertex from the given vertex.

		 @param[in]		vertex
						A reference to the vertex to copy.
		 */
		constexpr VertexPositionColorTexture(
			const VertexPositionColorTexture& vertex) noexcept = default;

		/**
		 Constructs a vertex by moving the given vertex.

		 @param[in]		vertex
						A reference to the vertex to move.
		 */
		constexpr VertexPositionColorTexture(
			VertexPositionColorTexture&& vertex) noexcept = default;

		/**
		 Destructs this vertex.
		 */
		~VertexPositionColorTexture() = default;

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------

		/**
		 Copies the given vertex to this vertex.

		 @param[in]		vertex
						A reference to the vertex to copy.
		 @return		A reference to the copy of the given vertex (i.e. this 
						vertex).
		 */
		constexpr VertexPositionColorTexture& operator=(
			const VertexPositionColorTexture& vertex) noexcept = default;

		/**
		 Moves the given vertex to this vertex.

		 @param[in]		vertex
						A reference to the vertex to move.
		 @return		A reference to the moved vertex (i.e. this vertex).
		 */
		constexpr VertexPositionColorTexture& operator=(
			VertexPositionColorTexture&& vertex) noexcept = default;

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		/**
		 The position of this vertex.
		 */
		Point3 m_p;

		/**
		 The sRGB color of this vertex.
		 */
		SRGBA m_c;

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
		static const D3D11_INPUT_ELEMENT_DESC s_input_element_descs[3];
	};

	/**
	 A struct of vertices containing position, normal and texture coordinates 
	 and a color.
	 */
	struct VertexPositionNormalColorTexture final {

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
		// Constructors and Destructors
		//---------------------------------------------------------------------

		/**
		 Constructs a vertex.
		 */
		VertexPositionNormalColorTexture() noexcept = default;

		/**
		 Constructs a vertex.

		 @param[in]		p
						The position of the vertex.
		 @param[in]		n
						The normal of the vertex.
		 @param[in]		c
						The sRGB color of the vertex.
		 @param[in]		tex
						The texture coordinates of the vertex.
		 */
		constexpr explicit VertexPositionNormalColorTexture(Point3 p, 
			                                                Normal3 n, 
			                                                SRGBA c, 
			                                                UV tex) noexcept
			: m_p(std::move(p)), 
			m_n(std::move(n)), 
			m_c(std::move(c)), 
			m_tex(std::move(tex)) {}

		/**
		 Constructs a vertex from the given vertex.

		 @param[in]		vertex
						A reference to the vertex to copy.
		 */
		constexpr VertexPositionNormalColorTexture(
			const VertexPositionNormalColorTexture& vertex) noexcept = default;

		/**
		 Constructs a vertex by moving the given vertex.

		 @param[in]		vertex
						A reference to the vertex to move.
		 */
		constexpr VertexPositionNormalColorTexture(
			VertexPositionNormalColorTexture&& vertex) noexcept = default;

		/**
		 Destructs this vertex.
		 */
		~VertexPositionNormalColorTexture() = default;

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------

		/**
		 Copies the given vertex to this vertex.

		 @param[in]		vertex
						A reference to the vertex to copy.
		 @return		A reference to the copy of the given vertex (i.e. this 
						vertex).
		 */
		constexpr VertexPositionNormalColorTexture& operator=(
			const VertexPositionNormalColorTexture& vertex) noexcept = default;

		/**
		 Moves the given vertex to this vertex.

		 @param[in]		vertex
						A reference to the vertex to move.
		 @return		A reference to the moved vertex (i.e. this vertex).
		 */
		constexpr VertexPositionNormalColorTexture& operator=(
			VertexPositionNormalColorTexture&& vertex) noexcept = default;

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
		 The sRGB color of this vertex.
		 */
		SRGBA m_c;

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
		static const D3D11_INPUT_ELEMENT_DESC s_input_element_descs[4];
	};
}