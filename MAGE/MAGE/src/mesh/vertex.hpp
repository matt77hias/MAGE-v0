#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "rendering\rendering.hpp"
#include "math\math.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Defines
//-----------------------------------------------------------------------------
#pragma region

#define MAGE_VERTEX_SEMANTIC_NAME_POSITION "POSITION"
#define MAGE_VERTEX_SEMANTIC_NAME_NORMAL "NORMAL"
#define MAGE_VERTEX_SEMANTIC_NAME_COLOR "COLOR"
#define MAGE_VERTEX_SEMANTIC_NAME_TEXTURE "TEXCOORD"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	struct VertexPosition final {

	public:

		/**
		 Constructs a vertex.
		 */
		VertexPosition() = default;

		/**
		 Constructs a vertex.

		 @param[in]		p
						A reference to the position of the vertex.
		 */
		explicit VertexPosition(const Point3 &p)
			: p(p) {}

		/**
		 Constructs a vertex from the given vertex.

		 @param[in]		vertex
						A reference to a vertex.
		 */
		VertexPosition(const VertexPosition &vertex) = default;

		/**
		 Constructs a vertex from the given vertex.

		 @param[in]		vertex
						A reference to a vertex.
		 */
		VertexPosition(VertexPosition &&vertex) = default;

		/**
		 Destructs this vertex.
		 */
		~VertexPosition() = default;

		/**
		Copies the given vertex to this vertex.

		 @param[in]		vertex
						A reference to a vertex.
		 @return		A reference to the copy of the given vertex (i.e. this vertex).
		 */
		VertexPosition &operator=(const VertexPosition &vertex) = default;

		/**
		 Copies the given vertex to this vertex.

		 @param[in]		vertex
						A reference to a vertex.
		 @return		A reference to the copy of the given vertex (i.e. this vertex).
		 */
		VertexPosition &operator=(VertexPosition &&vertex) = default;

		/**
		 The position of this vertex.
		 */
		Point3 p;

		/**
		 The number of elements in the input element descriptor of a vertex.
		 */
		static const uint32_t nb_input_elements = 1;

		/**
		 The input element descriptor of a vertex.
		 */
		static const D3D11_INPUT_ELEMENT_DESC input_element_desc[nb_input_elements];
	};

	struct VertexPositionNormal final {

	public:

		/**
		 Constructs a vertex.
		 */
		VertexPositionNormal() = default;

		/**
		 Constructs a vertex.

		 @param[in]		p
						A reference to the position of the vertex.
		 @param[in]		n
						A reference to the normal of the vertex.
		 */
		explicit VertexPositionNormal(const Point3 &p, const Normal3 &n)
			: p(p), n(n) {}

		/**
		 Constructs a vertex from the given vertex.

		 @param[in]		vertex
						A reference to a vertex.
		*/
		VertexPositionNormal(const VertexPositionNormal &vertex) = default;

		/**
		 Constructs a vertex from the given vertex.

		 @param[in]		vertex
						A reference to a vertex.
		 */
		VertexPositionNormal(VertexPositionNormal &&vertex) = default;

		/**
		 Destructs this vertex.
		 */
		~VertexPositionNormal() = default;

		/**
		 Copies the given vertex to this vertex.

		 @param[in]		vertex
						A reference to a vertex.
		 @return		A reference to the copy of the given vertex (i.e. this vertex).
		 */
		VertexPositionNormal &operator=(const VertexPositionNormal &vertex) = default;

		/**
		 Copies the given vertex to this vertex.

		 @param[in]		vertex
						A reference to a vertex.
		 @return		A reference to the copy of the given vertex (i.e. this vertex).
		 */
		VertexPositionNormal &operator=(VertexPositionNormal &&vertex) = default;

		/**
		 The position of this vertex.
		 */
		Point3 p;

		/**
		 The normal of this vertex.
		 */
		Normal3 n;

		/**
		 The number of elements in the input element descriptor of a vertex.
		 */
		static const uint32_t nb_input_elements = 2;

		/**
		 The input element descriptor of a vertex.
		 */
		static const D3D11_INPUT_ELEMENT_DESC input_element_desc[nb_input_elements];
	};

	struct VertexPositionColor final {

	public:

		/**
		 Constructs a vertex.
		 */
		VertexPositionColor() = default;

		/**
		 Constructs a vertex.

		 @param[in]		p
						A reference to the position of the vertex.
		 @param[in]		c
						A reference to the color of the vertex.
		 */
		explicit VertexPositionColor(const Point3 &p, const Color &c)
			: p(p), c(c) {}

		/**
		 Constructs a vertex from the given vertex.

		 @param[in]		vertex
						A reference to a vertex.
		 */
		VertexPositionColor(const VertexPositionColor &vertex) = default;

		/**
		 Constructs a vertex from the given vertex.

		 @param[in]		vertex
						A reference to a vertex.
		 */
		VertexPositionColor(VertexPositionColor &&vertex) = default;

		/**
		 Destructs this vertex.
		 */
		~VertexPositionColor() = default;

		/**
		 Copies the given vertex to this vertex.

		 @param[in]		vertex
						A reference to a vertex.
		 @return		A reference to the copy of the given vertex (i.e. this vertex).
		 */
		VertexPositionColor &operator=(const VertexPositionColor &vertex) = default;

		/**
		 Copies the given vertex to this vertex.

		 @param[in]		vertex
						A reference to a vertex.
		 @return		A reference to the copy of the given vertex (i.e. this vertex).
		 */
		VertexPositionColor &operator=(VertexPositionColor &&vertex) = default;

		/**
		 The position of this vertex.
		 */
		Point3 p;

		/**
		 The color of this vertex.
		 */
		Color c;

		/**
		 The number of elements in the input element descriptor of a vertex.
		 */
		static const uint32_t nb_input_elements = 2;

		/**
		 The input element descriptor of a vertex.
		 */
		static const D3D11_INPUT_ELEMENT_DESC input_element_desc[nb_input_elements];
	};

	struct VertexPositionTexture final {

	public:

		/**
		 Constructs a vertex.
		 */
		VertexPositionTexture() = default;

		/**
		 Constructs a vertex.

		 @param[in]		p
						A reference to the position of the vertex.
		 @param[in]		tex
						A reference to the texture coordinates of the vertex.
		 */
		explicit VertexPositionTexture(const Point3 &p, const UV &tex)
			: p(p), tex(tex) {}

		/**
		 Constructs a vertex from the given vertex.

		 @param[in]		vertex
						A reference to a vertex.
		 */
		VertexPositionTexture(const VertexPositionTexture &vertex) = default;

		/**
		 Constructs a vertex from the given vertex.

		 @param[in]		vertex
						A reference to a vertex.
		 */
		VertexPositionTexture(VertexPositionTexture &&vertex) = default;

		/**
		 Destructs this vertex.
		 */
		~VertexPositionTexture() = default;

		/**
		 Copies the given vertex to this vertex.

		 @param[in]		vertex
						A reference to a vertex.
		 @return		A reference to the copy of the given vertex (i.e. this vertex).
		 */
		VertexPositionTexture &operator=(const VertexPositionTexture &vertex) = default;

		/**
		 Copies the given vertex to this vertex.

		 @param[in]		vertex
						A reference to a vertex.
		 @return		A reference to the copy of the given vertex (i.e. this vertex).
		 */
		VertexPositionTexture &operator=(VertexPositionTexture &&vertex) = default;

		/**
		 The position of this vertex.
		 */
		Point3 p;

		/**
		 The texture coordinates of this vertex.
		 */
		UV tex;

		/**
		 The number of elements in the input element descriptor of a vertex.
		 */
		static const uint32_t nb_input_elements = 2;

		/**
		 The input element descriptor of a vertex.
		 */
		static const D3D11_INPUT_ELEMENT_DESC input_element_desc[nb_input_elements];
	};

	struct VertexPositionNormalColor final {

	public:

		/**
		 Constructs a vertex.
		 */
		VertexPositionNormalColor() = default;

		/**
		 Constructs a vertex.

		 @param[in]		p
						A reference to the position of the vertex.
		 @param[in]		n
						A reference to the normal of the vertex.
		 @param[in]		c
						A reference to the color of the vertex.
		 */
		explicit VertexPositionNormalColor(const Point3 &p, const Normal3 &n, const Color &c)
			: p(p), n(n), c(c) {}

		/**
		 Constructs a vertex from the given vertex.

		 @param[in]		vertex
						A reference to a vertex.
		 */
		VertexPositionNormalColor(const VertexPositionNormalColor &vertex) = default;

		/**
		 Constructs a vertex from the given vertex.

		 @param[in]		vertex
						A reference to a vertex.
		 */
		VertexPositionNormalColor(VertexPositionNormalColor &&vertex) = default;

		/**
		 Destructs this vertex.
		 */
		~VertexPositionNormalColor() = default;

		/**
		 Copies the given vertex to this vertex.

		 @param[in]		vertex
						A reference to a vertex.
		 @return		A reference to the copy of the given vertex (i.e. this vertex).
		 */
		VertexPositionNormalColor &operator=(const VertexPositionNormalColor &vertex) = default;

		/**
		 Copies the given vertex to this vertex.

		 @param[in]		vertex
						A reference to a vertex.
		 @return		A reference to the copy of the given vertex (i.e. this vertex).
		 */
		VertexPositionNormalColor &operator=(VertexPositionNormalColor &&vertex) = default;

		/**
		 The position of this vertex.
		 */
		Point3 p;

		/**
		 The normal of this vertex.
		 */
		Normal3 n;

		/**
		 The color of this vertex.
		 */
		Color c;

		/**
		 The number of elements in the input element descriptor of a vertex.
		 */
		static const uint32_t nb_input_elements = 3;

		/**
		 The input element descriptor of a vertex.
		 */
		static const D3D11_INPUT_ELEMENT_DESC input_element_desc[nb_input_elements];
	};

	struct VertexPositionNormalTexture final {

	public:

		/**
		 Constructs a vertex.
		 */
		VertexPositionNormalTexture() = default;

		/**
		 Constructs a vertex.

		 @param[in]		p
						A reference to the position of the vertex.
		 @param[in]		n
						A reference to the normal of the vertex.
		 @param[in]		tex
						A reference to the texture coordinates of the vertex.
		 */
		explicit VertexPositionNormalTexture(const Point3 &p, const Normal3 &n, const UV &tex)
			: p(p), n(n), tex(tex) {}

		/**
		 Constructs a vertex from the given vertex.

		 @param[in]		vertex
						A reference to a vertex.
		 */
		VertexPositionNormalTexture(const VertexPositionNormalTexture &vertex) = default;

		/**
		 Constructs a vertex from the given vertex.

		 @param[in]		vertex
						A reference to a vertex.
		 */
		VertexPositionNormalTexture(VertexPositionNormalTexture &&vertex) = default;

		/**
		 Destructs this vertex.
		 */
		~VertexPositionNormalTexture() = default;

		/**
		 Copies the given vertex to this vertex.

		 @param[in]		vertex
						A reference to a vertex.
		 @return		A reference to the copy of the given vertex (i.e. this vertex).
		 */
		VertexPositionNormalTexture &operator=(const VertexPositionNormalTexture &vertex) = default;

		/**
		 Copies the given vertex to this vertex.

		 @param[in]		vertex
						A reference to a vertex.
		 @return		A reference to the copy of the given vertex (i.e. this vertex).
		 */
		VertexPositionNormalTexture &operator=(VertexPositionNormalTexture &&vertex) = default;

		/**
		 The position of this vertex.
		 */
		Point3 p;

		/**
		 The normal of this vertex.
		 */
		Normal3 n;

		/**
		 The texture coordinates of this vertex.
		 */
		UV tex;

		/**
		 The number of elements in the input element descriptor of a vertex.
		 */
		static const uint32_t nb_input_elements = 3;

		/**
		 The input element descriptor of a vertex.
		 */
		static const D3D11_INPUT_ELEMENT_DESC input_element_desc[nb_input_elements];
	};

	struct VertexPositionColorTexture final {

	public:

		/**
		 Constructs a vertex.
		 */
		VertexPositionColorTexture() = default;

		/**
		 Constructs a vertex.

		 @param[in]		p
						A reference to the position of the vertex.
		 @param[in]		c
						A reference to the color of the vertex.
		 @param[in]		tex
						A reference to the texture coordinates of the vertex.
		 */
		explicit VertexPositionColorTexture(const Point3 &p, const Color &c, const UV &tex)
			: p(p), c(c), tex(tex) {}

		/**
		 Constructs a vertex from the given vertex.

		 @param[in]		vertex
						A reference to a vertex.
		 */
		VertexPositionColorTexture(const VertexPositionColorTexture &vertex) = default;

		/**
		 Constructs a vertex from the given vertex.

		 @param[in]		vertex
						A reference to a vertex.
		 */
		VertexPositionColorTexture(VertexPositionColorTexture &&vertex) = default;

		/**
		 Destructs this vertex.
		 */
		~VertexPositionColorTexture() = default;

		/**
		 Copies the given vertex to this vertex.

		 @param[in]		vertex
						A reference to a vertex.
		 @return		A reference to the copy of the given vertex (i.e. this vertex).
		 */
		VertexPositionColorTexture &operator=(const VertexPositionColorTexture &vertex) = default;

		/**
		 Copies the given vertex to this vertex.

		 @param[in]		vertex
						A reference to a vertex.
		 @return		A reference to the copy of the given vertex (i.e. this vertex).
		 */
		VertexPositionColorTexture &operator=(VertexPositionColorTexture &&vertex) = default;

		/**
		 The position of this vertex.
		 */
		Point3 p;

		/**
		 The color of this vertex.
		 */
		Color c;

		/**
		 The texture coordinates of this vertex.
		 */
		UV tex;

		/**
		 The number of elements in the input element descriptor of a vertex.
		 */
		static const uint32_t nb_input_elements = 3;

		/**
		 The input element descriptor of a vertex.
		 */
		static const D3D11_INPUT_ELEMENT_DESC input_element_desc[nb_input_elements];
	};

	struct VertexPositionNormalColorTexture final {

	public:

		/**
		 Constructs a vertex.
		 */
		VertexPositionNormalColorTexture() = default;

		/**
		 Constructs a vertex.

		 @param[in]		p
						A reference to the position of the vertex.
		 @param[in]		n
						A reference to the normal of the vertex.
		 @param[in]		c
						A reference to the color of the vertex.
		 @param[in]		tex
						A reference to the texture coordinates of the vertex.
		 */
		explicit VertexPositionNormalColorTexture(const Point3 &p, const Normal3 &n, const Color &c, const UV &tex)
			: p(p), n(n), c(c), tex(tex) {}

		/**
		 Constructs a vertex from the given vertex.

		 @param[in]		vertex
						A reference to a vertex.
		 */
		VertexPositionNormalColorTexture(const VertexPositionNormalColorTexture &vertex) = default;

		/**
		 Constructs a vertex from the given vertex.

		 @param[in]		vertex
						A reference to a vertex.
		 */
		VertexPositionNormalColorTexture(VertexPositionNormalColorTexture &&vertex) = default;

		/**
		 Destructs this vertex.
		 */
		~VertexPositionNormalColorTexture() = default;

		/**
		 Copies the given vertex to this vertex.

		 @param[in]		vertex
						A reference to a vertex.
		 @return		A reference to the copy of the given vertex (i.e. this vertex).
		 */
		VertexPositionNormalColorTexture &operator=(const VertexPositionNormalColorTexture &vertex) = default;

		/**
		 Copies the given vertex to this vertex.

		 @param[in]		vertex
						A reference to a vertex.
		 @return		A reference to the copy of the given vertex (i.e. this vertex).
		 */
		VertexPositionNormalColorTexture &operator=(VertexPositionNormalColorTexture &&vertex) = default;

		/**
		 The position of this vertex.
		 */
		Point3 p;

		/**
		 The normal of this vertex.
		 */
		Normal3 n;

		/**
		 The color of this vertex.
		 */
		Color c;

		/**
		 The texture coordinates of this vertex.
		 */
		UV tex;

		/**
		 The number of elements in the input element descriptor of a vertex.
		 */
		static const int nb_input_elements = 4;

		/**
		 The input element descriptor of a vertex.
		 */
		static const D3D11_INPUT_ELEMENT_DESC input_element_desc[nb_input_elements];
	};

	struct VertexPositionTextureTexture final {

	public:

		/**
		 Constructs a vertex.
		 */
		VertexPositionTextureTexture() = default;

		/**
		 Constructs a vertex.

		 @param[in]		p
						A reference to the position of the vertex.
		 @param[in]		tex1
						A reference to the first texture coordinates of the vertex.
		 @param[in]		tex2
						A reference to the second texture coordinates of the vertex.
		 */
		explicit VertexPositionTextureTexture(const Point3 &p, const UV &tex1, const UV &tex2)
			: p(p), tex1(tex1), tex2(tex2) {}

		/**
		 Constructs a vertex from the given vertex.

		 @param[in]		vertex
						A reference to a vertex.
		 */
		VertexPositionTextureTexture(const VertexPositionTextureTexture &vertex) = default;

		/**
		 Constructs a vertex from the given vertex.

		 @param[in]		vertex
						A reference to a vertex.
		 */
		VertexPositionTextureTexture(VertexPositionTextureTexture &&vertex) = default;
		
		/**
		 Destructs this vertex.
		 */
		~VertexPositionTextureTexture() = default;

		/**
		 Copies the given vertex to this vertex.

		 @param[in]		vertex
						A reference to a vertex.
		 @return		A reference to the copy of the given vertex (i.e. this vertex).
		 */
		VertexPositionTextureTexture &operator=(const VertexPositionTextureTexture &vertex) = default;

		/**
		 Copies the given vertex to this vertex.

		 @param[in]		vertex
						A reference to a vertex.
		 @return		A reference to the copy of the given vertex (i.e. this vertex).
		 */
		VertexPositionTextureTexture &operator=(VertexPositionTextureTexture &&vertex) = default;

		/**
		 The position of this vertex.
		 */
		Point3 p;

		/**
		 The first texture coordinates of this vertex.
		 */
		UV tex1;

		/**
		 The second texture coordinates of this vertex.
		 */
		UV tex2;

		/**
		 The number of elements in the input element descriptor of a vertex.
		 */
		static const int nb_input_elements = 3;

		/**
		 The input element descriptor of a vertex.
		 */
		static const D3D11_INPUT_ELEMENT_DESC input_element_desc[nb_input_elements];
	};
}